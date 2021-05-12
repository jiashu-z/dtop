#include <iostream>
#include "Server.h"

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "Hello world!" << std::endl;
    dtop::server::Server server("localhost", 8080);
    server.run();
    std::cout << "Server quit." << std::endl;
  }
}