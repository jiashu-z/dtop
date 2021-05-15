#include <iostream>

#include "Server.h"

int main(int argc, char **argv) {
  if (argc == 1) {
    std::cout << "Hello world!" << std::endl;
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    dtop::server::Server server("/home/carl/vmware_share/projects/dtop/dtop-grpc/config.xml");
    std::cout << server.to_string() << std::endl;
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    server.run();
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    std::cout << "Server quit." << std::endl;
  }
}