const express = require('express');
const http = require('http');
const argv = require('yargs').argv;

const port = argv.port? (1*argv.port) : 8e3;
const app = express();

app.use(express.static('./cmake/build/tiledapp/'));
app.use((req,res,next)=>{
  res.setHeader('Cross-Origin-Embedder-Policy', 'require-corp');
  res.setHeader('Cross-Origin-Opener-Policy', 'same-origin');
  next();
})

const httpServer = http.createServer(app);
httpServer.listen(port, argv.host);

console.log("Static file server running at\n"+
                "  => http://localhost:"+port+"/tiledapp.html\n"+
                "  CTRL + C to shutdown");