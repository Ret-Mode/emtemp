const http = require("http");
const fs = require('fs');

const server = http.createServer((req,res) => {
  let url = "." + req.url;
  if (url === "./") {
    url = "./template.html"
  }
  console.log(url);
  if (fs.existsSync(url)){
    fs.readFile(url, (err, data) => {
      if (err) {
        console.log("error");
        res.writeHead(400);
      }
      else {
        if (url.endsWith('wasm')){
          res.writeHead(200, {'content-type':'application/wasm'});
          console.log("wasm");
        } else if (url.endsWith('html')){
          res.writeHead(200, {'content-type':'text/html'});
          console.log("html");
        } else if (url.endsWith('js')){
          res.writeHead(200, {'content-type':'text/javascript'});
          console.log("js");
        } else if (url.endsWith('css')){
          res.writeHead(200, {'content-type':'text/css'});
          console.log("css");
        } else {
          res.writeHead(200);
          console.log("other " + url);
        }
        console.log(data);
        res.end(data);
        }
    });
  } else {
    res.writeHead(200);
    res.end("");
  }
});
server.listen(9876);