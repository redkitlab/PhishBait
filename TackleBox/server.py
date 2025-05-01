import http.server
import socketserver
import os
import sys

os.chdir(os.path.dirname(os.path.abspath(__file__)))

PORT = 8080
Handler = http.server.SimpleHTTPRequestHandler

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    with open("server.pid", "w") as f:
        f.write(str(os.getpid()))
    print(f"Serving at port {PORT}")
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
