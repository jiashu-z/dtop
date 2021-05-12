#include "Server.h"
#include <sstream>

std::string dtop::server::Server::to_string() const {
  std::stringstream ss;
  ss << "ip: " << this->ip_addr << "\n";
  ss << "port: " << this->port << "\n";
  std::string str;
  ss >> str;
  return str;
}

dtop::server::Server::Server(const std::string &ip_addr, const int& port) {
  this->ip_addr = ip_addr;
  this->port = port;
}