// spc main
#include <iostream>

#include "spc.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "usage: spc config_path" << std::endl;
    return -1;
  }
  std::cout << "start container..." << std::endl;
  spc::Container container(argv[1]);
  container.Start();
  std::cout << "container is stopped" << std::endl;
  return 0;
}

