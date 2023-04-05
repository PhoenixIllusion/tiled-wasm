docker run \
  --rm -it \
  --name qt-webassembly \
  --mount type=bind,source="$(pwd)/tiled-src",target=/tiled-src/ \
  --mount type=bind,source="$(pwd)/cmake",target=/cmake/ \
  phoenixillusion/qt6:6.5-wasm-multithread-aqt /bin/bash
