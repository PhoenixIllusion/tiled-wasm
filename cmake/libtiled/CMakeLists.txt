cmake_minimum_required(VERSION 3.21.1)

SET(TARGET_NAME libtiled)
project(${TARGET_NAME} VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core Gui REQUIRED)

add_compile_definitions(
    "TILED_LIBRARY"
    "QT_NO_CAST_FROM_ASCII"
    "QT_NO_CAST_TO_ASCII"
    "QT_NO_URL_CAST_FROM_STRING"
    "QT_DISABLE_DEPRECATED_BEFORE=QT_VERSION_CHECK(5,15,0)"
    "QT_NO_DEPRECATED_WARNINGS"
    "_USE_MATH_DEFINES"
)

SET(SOURCE_DIR ${TILED_BASE_DIR}/src/libtiled/)
SET("${TARGET_NAME}_PATH" ${SOURCE_DIR} PARENT_SCOPE)

INCLUDE_DIRECTORIES(
    ${Qt6Core_INCLUDE_DIRS}
    ${Qt6Gui_INCLUDE_DIRS}
    ${SOURCE_DIR})
    
SET(SOURCE_FILES
    mapobject.cpp
    tiled.cpp
    objecttemplate.cpp
    isometricrenderer.cpp
    fileformat.cpp
    tileset.cpp
    wangset.cpp
    tilesetmanager.cpp
    gidmapper.cpp
    hexagonalrenderer.cpp
    maptovariantconverter.cpp
    layer.cpp
    object.cpp
    tileanimationdriver.cpp
    maprenderer.cpp
    objectgroup.cpp
    imagecache.cpp
    minimaprenderer.cpp
    mapformat.cpp
    pluginmanager.cpp
    compression.cpp
    tilesetformat.cpp
    objecttypes.cpp
    savefile.cpp
    tilelayer.cpp
    imagereference.cpp
    plugin.cpp
    map.cpp
    properties.cpp
    mapwriter.cpp
    hex.cpp
    imagelayer.cpp
    worldmanager.cpp
    logginginterface.cpp
    filesystemwatcher.cpp
    grouplayer.cpp
    tile.cpp
    orthogonalrenderer.cpp
    staggeredrenderer.cpp
    objecttemplateformat.cpp
    varianttomapconverter.cpp
    templatemanager.cpp
    propertytype.cpp
    mapreader.cpp
)

string(REGEX REPLACE "([^;]+)" "${SOURCE_DIR}/\\1" SOURCE_FILES "${SOURCE_FILES}")
qt_add_library(${TARGET_NAME} STATIC
    ${SOURCE_FILES}
)

set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
    PREFIX ""
)
