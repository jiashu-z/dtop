#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <iostream>

namespace dtop {
namespace client {

class Client {
  private:
  std::string server_name;
  std::string server_ip;
  int server_port;
  public:
  explicit Client();
  std::string to_string();
};

}
}

#endif