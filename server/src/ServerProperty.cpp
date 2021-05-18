#include "ServerProperty.h"

#include <boost/algorithm/string.hpp>
#include <sstream>

#include "LibNet.h"
#include "LibXML.h"

dtop::server::ServerProperty::ServerProperty(
    const std::string &config_file_path) {
  this->config_file_path = config_file_path;
  this->config();
}

inline void dtop::server::ServerProperty::config() {
  // Load config file.
  if (!this->config_file.load_file(this->config_file_path.c_str())) {
    throw "Config file does not exist!";
  }

  // Fetch properties.
  auto properties =
      dtop::common::check_and_fetch_xml_node(this->config_file, "properties");

  // Fetch server-addr.
  auto server_addr_node =
      dtop::common::check_and_fetch_xml_node(properties, "server-addr");
  this->ip = server_addr_node.child_value();
  boost::trim(this->ip);

  assert(is_ipv4_valid(this->ip));

  // Fetch server-port.
  auto server_port_node =
      dtop::common::check_and_fetch_xml_node(properties, "server-port");
  this->port = std::stoi(server_port_node.child_value());

  // Fetch thread-num.
  auto thread_num_node =
      dtop::common::check_and_fetch_xml_node(properties, "thread-num");
  this->thread_num = std::stoi(thread_num_node.child_value());
  assert(this->thread_num > 0);

  // TODO: Simplify here. Plenty of useless work.
  auto other_servers_node =
      dtop::common::check_and_fetch_xml_node(properties, "other-servers");
  std::list<pugi::xml_node> child_list =
      dtop::common::fetch_child_list(other_servers_node);
  for (auto iter : child_list) {
    std::string str;
    str += iter.child_value("addr");
    str += ":";
    str += iter.child_value("port");
    this->other_server_addr_list.push_back(str);
  }

  std::cout << "END" << std::endl;
}

std::string dtop::server::ServerProperty::get_addr() {
  return this->ip + ":" + std::to_string(this->port);
}

int dtop::server::ServerProperty::get_thread_num() const {
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  std::cout << "thread_num: " << this->thread_num << std::endl;
  return this->thread_num;
}

std::string dtop::server::ServerProperty::get_ip() const { return this->ip; }

int dtop::server::ServerProperty::get_port() const { return this->port; }

std::string dtop::server::ServerProperty::to_string() const {
  std::stringstream ss;
  ss << "ip: " << this->ip << "; ";
  ss << "port: " << std::to_string(this->port) << "; ";
  return ss.str();
}