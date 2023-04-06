cmake_minimum_required(VERSION 3.21.1)

set(TARGET_NAME tiledapp)

find_package(Qt6 COMPONENTS Core Gui Widgets Network Concurrent Qml Svg OpenGLWidgets REQUIRED)

SET(SOURCE_DIR ${TILED_BASE_DIR}/src/tiledapp)

SET("${TARGET_NAME}_PATH" ${SOURCE_DIR} PARENT_SCOPE)

INCLUDE_DIRECTORIES(
  ${tilededitor_PATH}
  ${libtiled_PATH}
  ${qtsingleapplication_PATH}
  ${qtpropertybrowser_PATH}

  ${SOURCE_DIR})

SET(SOURCE_FILES
        commandlineparser.cpp
        main.cpp
)
string(REGEX REPLACE "([^;]+)" "${SOURCE_DIR}/\\1" SOURCE_FILES "${SOURCE_FILES}")

qt_add_executable(${TARGET_NAME}
        ${SOURCE_FILES}
)
target_link_libraries(
  ${TARGET_NAME} PRIVATE
  libtiled
  qtpropertybrowser
  qtsingleapplication
  tilededitor
  Qt::Core
  Qt::Gui
  Qt::Widgets
  Qt::Network
  Qt::Concurrent
  Qt::Qml
  Qt::Svg
  Qt::OpenGLWidgets
)

target_link_options(${TARGET_NAME} PUBLIC -sASYNCIFY -Os)
target_compile_options(${TARGET_NAME} PUBLIC "-pthread")
set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
