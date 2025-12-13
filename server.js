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
      res.writeHead(200);
      res.end(data);
    })
  } else {
    res.writeHead(200);
    res.end(data);
  }
});
server.listen(9876);