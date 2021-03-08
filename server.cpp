#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "lib/erproc.hpp"
#include "lib/package.hpp"

#define THREADS 3
std::vector<int> Connections;

// attepm to send simple message to client
void SendHello(int fd) {
  std::string msg = "Hello from server";
  Package *p = new Package(P_MSG, msg.size(), msg);
  p->PSend(fd);
  delete p;
}

// loop for client handle
void ClientHandler(int fd, int index) {
  SendHello(fd);
  int i = 0;
  while (i < 10) {
    Package *p = Package::Resive(fd);
    for (size_t i = 0; i < Connections.size(); i++) {
      if (i == index) {
        continue;
      } else {
        p->PSend(Connections[i]);
      }
    }
    delete p;
    i++;
  }
}

int main() {
  // resolve server adress

  struct sockaddr_in server_addres;
  server_addres.sin_family = AF_INET;
  server_addres.sin_port = htons(3001);
  server_addres.sin_addr.s_addr = INADDR_ANY;
  socklen_t addr_size = sizeof(server_addres);

  // Create socket and bind her on server_addres
  int server = Socket(AF_INET, SOCK_STREAM, 0);
  Bind(server, (sockaddr *)&server_addres, addr_size);

  // prepare vector of threads and start listen soket until
  // client attepm to connect
  Listen(server, THREADS);
  std::vector<std::thread> threads;

  // try to accept connection and put this in thread
  for (int i = 0; i < THREADS; i++) {
    int fd = Accept(server, (sockaddr *)&server_addres, &addr_size);
    Connections.push_back(fd);
    threads.push_back(std::thread(ClientHandler, Connections[i], i));
  }

  // wait for complite all threads and close server
  for (auto &x : threads) {
    x.join();
  }
  return 0;
}
