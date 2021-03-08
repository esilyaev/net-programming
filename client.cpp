#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <thread>

#include "lib/erproc.hpp"
#include "lib/package.hpp"

// attemp to recive and print simple msg
void GetMsg(int server) {
  Package* p = Package::Resive(server);
  std::cout << p->GetMessage() << std::endl;
  delete p;
}

void SendMsg(int server) {
  std::string msg;
  std::getline(std::cin, msg);

  auto* p = new Package(P_MSG, msg.size(), msg);
  p->PSend(server);
  delete p;
}

// main loop for handle server socket
void ServerHandler(int server) {
  GetMsg(server);
  int i = 0;
  while (i < 10) {
    GetMsg(server);

    i++;
  }
}

int main() {
  // resolve server adress

  struct sockaddr_in server_addres;
  server_addres.sin_family = AF_INET;
  server_addres.sin_port = htons(3001);
  inet_pton(AF_INET, "127.0.0.1", &server_addres.sin_addr.s_addr);
  socklen_t addr_size = sizeof(server_addres);

  // Socket creation and attempt to connect
  int server = Socket(AF_INET, SOCK_STREAM, 0);
  Connect(server, (sockaddr*)&server_addres, addr_size);
  std::thread sh(ServerHandler, server);

  bool flag = true;
  int j = 0;
  while (flag) {
    if (j == 10) flag = false;
    SendMsg(server);
    j++;
  }

  return 0;
}