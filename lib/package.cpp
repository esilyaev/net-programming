#include "package.hpp"

Package::Package(PackageType p_type, int msg_size, std::string msg)
    : p_type(p_type), msg_size(msg_size), msg(msg) {}

Package::~Package() {}

Package* Package::Resive(int filedescriptor) {
  PackageType rcv_type;
  int rcv_size = 0;

  // recive package tipe and len of message
  Recv(filedescriptor, &rcv_type, sizeof(PackageType), 0);
  Recv(filedescriptor, &rcv_size, sizeof(int), 0);

  // recive message and put her in array
  char* rcv_msg = new char[rcv_size];
  Recv(filedescriptor, rcv_msg, rcv_size, 0);

  delete[] rcv_msg;
  Package* p = new Package(rcv_type, rcv_size, std::string(rcv_msg));
  return p;
}

void Package::PSend(int filedescriptor) {
  Send(filedescriptor, &p_type, sizeof(PackageType), 0);
  Send(filedescriptor, &msg_size, sizeof(int), 0);
  Send(filedescriptor, msg.c_str(), msg_size, 0);
}

std::string Package::GetMessage() { return msg; }
