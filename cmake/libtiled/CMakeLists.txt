cmake_minimum_required(VERSION 3.21.1)

set(TARGET_NAME libtiled)
project(${TARGET_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Gui REQUIRED)
INCLUDE_DIRECTORIES(${Qt6Core_INCLUDE_DIRS} ${Qt6Gui_INCLUDE_DIRS} ../../src/libtiled/)

qt_add_library(${TARGET_NAME} STATIC
    ../../src/libtiled/mapobject.cpp
    ../../src/libtiled/tiled.cpp
    ../../src/libtiled/objecttemplate.cpp
    ../../src/libtiled/isometricrenderer.cpp
    ../../src/libtiled/fileformat.cpp
    ../../src/libtiled/tileset.cpp
    ../../src/libtiled/wangset.cpp
    ../../src/libtiled/tilesetmanager.cpp
    ../../src/libtiled/gidmapper.cpp
    ../../src/libtiled/hexagonalrenderer.cpp
    ../../src/libtiled/maptovariantconverter.cpp
    ../../src/libtiled/layer.cpp
    ../../src/libtiled/object.cpp
    ../../src/libtiled/tileanimationdriver.cpp
    ../../src/libtiled/maprenderer.cpp
    ../../src/libtiled/objectgroup.cpp
    ../../src/libtiled/imagecache.cpp
    ../../src/libtiled/minimaprenderer.cpp
    ../../src/libtiled/mapformat.cpp
    ../../src/libtiled/pluginmanager.cpp
    ../../src/libtiled/compression.cpp
    ../../src/libtiled/tilesetformat.cpp
    ../../src/libtiled/objecttypes.cpp
    ../../src/libtiled/savefile.cpp
    ../../src/libtiled/tilelayer.cpp
    ../../src/libtiled/imagereference.cpp
    ../../src/libtiled/plugin.cpp
    ../../src/libtiled/map.cpp
    ../../src/libtiled/properties.cpp
    ../../src/libtiled/mapwriter.cpp
    ../../src/libtiled/hex.cpp
    ../../src/libtiled/imagelayer.cpp
    ../../src/libtiled/worldmanager.cpp
    ../../src/libtiled/logginginterface.cpp
    ../../src/libtiled/filesystemwatcher.cpp
    ../../src/libtiled/grouplayer.cpp
    ../../src/libtiled/tile.cpp
    ../../src/libtiled/orthogonalrenderer.cpp
    ../../src/libtiled/staggeredrenderer.cpp
    ../../src/libtiled/objecttemplateformat.cpp
    ../../src/libtiled/varianttomapconverter.cpp
    ../../src/libtiled/templatemanager.cpp
    ../../src/libtiled/propertytype.cpp
    ../../src/libtiled/mapreader.cpp
)

set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")