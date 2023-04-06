cmake_minimum_required(VERSION 3.21.1)

set(QT_MAJOR_VERSION 6)
set(TARGET_NAME tiled)
project(${TARGET_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(TILED_BASE_DIR ../../tiled-src)
add_subdirectory(./libtiled)
add_subdirectory(./translations)
add_subdirectory(./qtpropertybrowser)
add_subdirectory(./qtsingleapplication)
add_subdirectory(./tilededitor)

add_subdirectory(./tiledapp)