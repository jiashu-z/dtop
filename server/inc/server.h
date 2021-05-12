#ifndef DTOP_SERVER_SERVER_H
#define DTOP_SERVER_SERVER_H

#include <iostream>

namespace dtop {
namespace server {

class Server {
 private:
  std::string ip_addr;
  int port;

 public:
  std::string to_string();
};

}
}

#endif