docker run \
  --rm -it \
  --name qt-webassembly \
  --mount type=bind,source="$(pwd)/tiled-src/src",target=/src/ \
  --mount type=bind,source="$(pwd)/cmake",target=/cmake/ \
  stateoftheartio/qt6:6.4-wasm-aqt /bin/bash /cmake/cmake.sh
