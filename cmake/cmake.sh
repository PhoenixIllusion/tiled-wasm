cd /cmake
mkdir -p build
qt-cmake -G Ninja -B ./build;
cmake --build ./build
