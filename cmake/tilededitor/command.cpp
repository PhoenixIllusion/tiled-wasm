/*
 * command.cpp
 * Copyright 2011, Jeff Bland <jksb@member.fsf.org>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "command.h"

#include "actionmanager.h"
#include "commandmanager.h"
#include "documentmanager.h"
#include "logginginterface.h"
#include "mapdocument.h"
#include "mapobject.h"
#include "projectmanager.h"
#include "worlddocument.h"
#include "worldmanager.h"

#include <QAction>
#include <QDir>
#include <QMessageBox>
#include <QProcess>
#include <QStandardPaths>
#include <QUndoStack>

#include <emscripten.h>
EM_JS(void, js__executeCommand,
  (bool isEnabled, const char * name, const char * executable, const char * arguments, const char * workingDirectory, bool showOutput, bool saveBeforeExecute, bool inTerminalO, bool showOutputO), {
    const command = {
      isEnabled,
      name: UTF8ToString(name),
      executable: UTF8ToString(executable),
      arguments: UTF8ToString(arguments),
      workingDirectory: UTF8ToString(workingDirectory), 
      showOutput, saveBeforeExecute};
    const flags = { inTerminal, showOutput};
    console.log("Execute: ", command, flags);
})

void executeCommand(const Tiled::Command &command, bool inTerminal = false, bool showOutput = true) {
    js__executeCommand(
      command.isEnabled,
      command.name.toStdString().c_str(),
      command.executable.toStdString().c_str(),
      command.arguments.toStdString().c_str(),
      command.workingDirectory.toStdString().c_str(),
      command.showOutput,
      command.saveBeforeExecute,
      inTerminal, showOutput);
}

using namespace Tiled;

namespace Tiled {


static QString replaceVariables(const QString &string, bool quoteValues = true)
{
    QString finalString = string;
    QString replaceString = quoteValues ? QStringLiteral("\"%1\"") :
                                          QStringLiteral("%1");

    // Perform variable replacement
    if (Document *document = DocumentManager::instance()->currentDocument()) {
        const QString fileName = document->fileName();
        QFileInfo fileInfo(fileName);
        const QString mapPath = fileInfo.absolutePath();
        const QString projectPath = QFileInfo(ProjectManager::instance()->project().fileName()).absolutePath();

        finalString.replace(QLatin1String("%mapfile"), replaceString.arg(fileName));
        finalString.replace(QLatin1String("%mappath"), replaceString.arg(mapPath));
        finalString.replace(QLatin1String("%projectpath"), replaceString.arg(projectPath));

        if (MapDocument *mapDocument = qobject_cast<MapDocument*>(document)) {
            if (const Layer *layer = mapDocument->currentLayer()) {
                finalString.replace(QLatin1String("%layername"),
                                    replaceString.arg(layer->name()));
            }
        } else if (TilesetDocument *tilesetDocument = qobject_cast<TilesetDocument*>(document)) {
            QStringList selectedTileIds;
            for (const Tile *tile : tilesetDocument->selectedTiles())
                selectedTileIds.append(QString::number(tile->id()));

            finalString.replace(QLatin1String("%tileid"),
                                replaceString.arg(selectedTileIds.join(QLatin1Char(','))));
        }

        if (const MapObject *currentObject = dynamic_cast<MapObject *>(document->currentObject())) {
            // For compatility with Tiled < 1.9
            finalString.replace(QLatin1String("%objecttype"),
                                replaceString.arg(currentObject->className()));

            finalString.replace(QLatin1String("%objectclass"),
                                replaceString.arg(currentObject->className()));
            finalString.replace(QLatin1String("%objectid"),
                                replaceString.arg(currentObject->id()));
        }

        if (const World *world = WorldManager::instance().worldForMap(fileName)) {
            finalString.replace(QLatin1String("%worldfile"), replaceString.arg(world->fileName));
        }
    }

    return finalString;
}

} // namespace Tiled


QString Command::finalWorkingDirectory() const
{
    QString finalWorkingDirectory = replaceVariables(workingDirectory, false);
    QString finalExecutable = replaceVariables(executable);
    QFileInfo mFile(finalExecutable);

    if (!mFile.exists())
        mFile = QFileInfo(QStandardPaths::findExecutable(finalExecutable));

    finalWorkingDirectory.replace(QLatin1String("%executablepath"),
                                  mFile.absolutePath());

    return finalWorkingDirectory;
}

/**
 * Returns the final command with replaced tokens.
 */
QString Command::finalCommand() const
{
    QString exe = executable.trimmed();

    // Quote the executable when not already done, to make it work even when
    // the path contains spaces.
    if (!exe.startsWith(QLatin1Char('"')) && !exe.startsWith(QLatin1Char('\'')))
        exe.prepend(QLatin1Char('"')).append(QLatin1Char('"'));

    QString finalCommand = QStringLiteral("%1 %2").arg(exe, arguments);
    return replaceVariables(finalCommand);
}

/**
 * Executes the command in the operating system shell or terminal
 * application.
 */
void Command::execute(bool inTerminal) const
{
    if (saveBeforeExecute) {
        ActionManager::instance()->action("Save")->trigger();

        if (Document *document = DocumentManager::instance()->currentDocument())
            if (document->type() == Document::MapDocumentType)
                if (const World *world = WorldManager::instance().worldForMap(document->fileName()))
                    WorldManager::instance().saveWorld(world->fileName);
    }

    // Start the process
    executeCommand(*this, inTerminal, showOutput);
}

/**
 * Stores this command in a QVariant.
 */
QVariantHash Command::toVariant() const
{
    return QVariantHash {
        { QStringLiteral("arguments"), arguments },
        { QStringLiteral("command"), executable },
        { QStringLiteral("enabled"), isEnabled },
        { QStringLiteral("name"), name },
        { QStringLiteral("saveBeforeExecute"), saveBeforeExecute },
        { QStringLiteral("shortcut"), shortcut },
        { QStringLiteral("showOutput"), showOutput },
        { QStringLiteral("workingDirectory"), workingDirectory },
    };
}

/**
 * Generates a command from a QVariant.
 */
Command Command::fromVariant(const QVariant &variant)
{
    const auto hash = variant.toHash();

    auto read = [&] (const QString &prop) {
        if (hash.contains(prop))
            return hash.value(prop);

        QString oldProp = prop.at(0).toUpper() + prop.mid(1);
        return hash.value(oldProp);
    };

    const QVariant arguments = read(QStringLiteral("arguments"));
    const QVariant enable = read(QStringLiteral("enabled"));
    const QVariant executable = read(QStringLiteral("command"));
    const QVariant name = read(QStringLiteral("name"));
    const QVariant saveBeforeExecute = read(QStringLiteral("saveBeforeExecute"));
    const QVariant shortcut = read(QStringLiteral("shortcut"));
    const QVariant showOutput = read(QStringLiteral("showOutput"));
    const QVariant workingDirectory = read(QStringLiteral("workingDirectory"));

    Command command;

    command.arguments = arguments.toString();
    command.isEnabled = enable.toBool();
    command.executable = executable.toString();
    command.name = name.toString();
    command.saveBeforeExecute = saveBeforeExecute.toBool();
    command.shortcut = shortcut.value<QKeySequence>();
    command.showOutput = showOutput.toBool();
    command.workingDirectory = workingDirectory.toString();

    return command;
}

#include "command.moc"
