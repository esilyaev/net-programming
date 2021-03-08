#include "erproc.hpp"

int Socket(int domain, int type, int protocol) {
  int res = socket(domain, type, protocol);
  if (res == -1) {
    std::cout << "socket creation error, exit\n";
    exit(-1);
  } else {
    std::cout << "socket created\n";
    return res;
  }
}

void Bind(int socket, const sockaddr *address, socklen_t address_len) {
  int res = bind(socket, address, address_len);
  if (res == -1) {
    std::cout << "socket bind error, exit\n";
    exit(-1);
  } else {
    std::cout << "socket binded\n";
    return;
  }
}

void Listen(int socket, int backlog) {
  int res = listen(socket, backlog);
  if (res == -1) {
    std::cout << "socket listen error, exit\n";
    exit(-1);
  } else {
    std::cout << "socket listen\n";
    return;
  }
}

void Connect(int socket, const sockaddr *address, socklen_t address_len) {
  int res = connect(socket, address, address_len);
  if (res == -1) {
    std::cout << "socket connection error, exit\n";
    exit(-1);
  } else {
    std::cout << "connection established\n";
    return;
  }
}

int Accept(int socket, sockaddr *address, socklen_t *address_len) {
  int res = accept(socket, address, address_len);
  if (res == -1) {
    std::cout << "attempt acception connection error, exit\n";
    exit(-1);
  } else {
    std::cout << "connection accepted\n";
    return res;
  }
}

void Send(int socket, const void *buffer, size_t length, int flags) {
  int res = send(socket, buffer, length, flags);
  if (res == -1) {
    std::cout << "send data to soket error, exit\n";
    exit(-1);
  }
}

void Recv(int socket, void *buffer, size_t length, int flags) {
  int res = recv(socket, buffer, length, flags);
  if (res == -1) {
    std::cout << "recv data error\n";
    exit(-1);
  }
}