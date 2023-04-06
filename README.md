
Attempt to compile Tiled [https://github.com/mapeditor/tiled] into a WASM web based application.

### Requirements
- Docker, compatible machine with  [https://docs.docker.com/assets/images/download.svg]
- Recommended Docker Setup, at least 4GB disk, 6GB RAM

### Building the multi-threaded Qt6.5 docker image using aqt [https://github.com/miurahr/aqtinstall]
Modified image of [https://github.com/state-of-the-art/qt6-docker]
(from root directory)
```
  cd qt6.5-wasm-multithread-aqt
  sh docker-build.sh
```

### Building the WASM build
(from root directory)
```
  sh docker-run.sh
```

### Running the WASM build
Final build is located at `/cmake/build/tiledapp/tiledapp.html`
Due to the project compiling with Qt Concurrent, the multi-threaded Qt requires WASM SharedArrayBuffer support.
For Chrome, this requires hosting on a server with the headers:

```
'Cross-Origin-Embedder-Policy': 'require-corp'
'Cross-Origin-Opener-Policy': 'same-origin'
```

With NodeJS, you can run a simple static express server to do this:
```
  npm install
  npm run start
```