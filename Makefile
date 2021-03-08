all: server client

server:
	g++ -std=c++11 lib/erproc.cpp lib/package.cpp server.cpp -o bin/server
client: 
	g++ -std=c++11 lib/erproc.cpp lib/package.cpp client.cpp -o bin/client

