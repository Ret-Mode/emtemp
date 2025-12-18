const http = require("http");
const fs = require('fs');

const server = http.createServer((req,res) => {
  let url = "." + req.url;
  if (url === "./") {
    url = "./template.html"
  }
  if (fs.existsSync(url)){
    fs.readFile(url, (err, data) => {
      if (err) {
        res.writeHead(200);
        res.end("Error");
      }
      if (url.endsWith('wasm')){
        res.writeHead(200, {'content-type':'application/wasm'});
      } else if (url.endsWith('html')){
        res.writeHead(200, {'content-type':'text/html'});
      } else {
        res.writeHead(200);
      }
      
      res.end(data);
    })
  } else {
    res.writeHead(200);
    res.end();
  }
});
server.listen(9876);