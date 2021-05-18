#include <iostream>

#include "Server.h"

int main(int argc, char **argv) {
  std::string config_file_path = "/home/zjs/dtop-grpc/config.xml";
  if (argc == 2) {
    config_file_path = argv[1];
  } else if (argc > 2) {
    throw "Argument error";
  }
  std::cout << "Hello world!" << std::endl;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  dtop::server::Server server(config_file_path);
  std::cout << server.to_string() << std::endl;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  server.run();
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  std::cout << "Server quit." << std::endl;
}