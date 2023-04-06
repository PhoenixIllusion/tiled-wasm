cmake_minimum_required(VERSION 3.21.1)

set(TARGET_NAME qtsingleapplication)

find_package(Qt6 COMPONENTS Core Widgets Network REQUIRED)

SET(SOURCE_DIR ${TILED_BASE_DIR}/src/qtsingleapplication/src/)
SET("${TARGET_NAME}_PATH" ${SOURCE_DIR} PARENT_SCOPE)
INCLUDE_DIRECTORIES(
  ${Qt6Core_INCLUDE_DIRS}
  ${Qt6Widgets_INCLUDE_DIRS}
  ${Qt6Network_INCLUDE_DIRS}
  ${SOURCE_DIR})

SET(SOURCE_FILES
        qtlocalpeer.cpp
        qtsingleapplication.cpp
)
string(REGEX REPLACE "([^;]+)" "${SOURCE_DIR}/\\1" SOURCE_FILES "${SOURCE_FILES}")

qt_add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES}
)

target_compile_options(${TARGET_NAME} PUBLIC "-pthread")
set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
