#include "server.h"
#include <sstream>

std::string dtop::server::Server::to_string() {
  std::stringstream ss;
  ss << "ip: " << this->ip_addr << "\n";
  ss << "port: " << this->port << "\n";
  std::string str;
  ss >> str;
  return str;
}