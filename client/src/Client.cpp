#include "Client.h"
#include <sstream>

dtop::client::Client::Client() {
  this->server_name = "default";
  this->server_ip = "0.0.0.0";
  this->server_port = 0;
}

std::string dtop::client::Client::to_string() {
  std::stringstream ss;
  ss << "name: " << this->server_name << "\n";
  ss << "ip: " << this->server_ip << "\n";
  ss << "port: " << this->server_port << "\n";
  std::string str;
  ss >> str;
  return str;
}