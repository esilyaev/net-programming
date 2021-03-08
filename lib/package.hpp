#pragma once
#include <sys/socket.h>

#include <iostream>
#include <string>

#include "erproc.hpp"

enum PackageType { P_MSG, P_INFO, P_QUIT };

class Package {
 private:
  PackageType p_type;
  std::string msg;
  int msg_size;

 public:
  Package(PackageType p_type, int msg_size, std::string msg);
  ~Package();

  // send package to filedescriptor
  void PSend(int filedescriptor);

  // Getting Package from fd
  // return new pointer on package if success
  // don't foget delete

  static Package* Resive(int filedescriptor);

  std::string GetMessage();
};