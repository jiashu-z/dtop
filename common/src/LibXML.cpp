#include "LibXML.h"

#include <sstream>

#include "iostream"

pugi::xml_node dtop::common::check_and_fetch_xml_node(
    const pugi::xml_node &node, const std::string &name) {
  auto result = node.child(name.c_str());
  if (result) {
    return node.child(name.c_str());
  }
  std::stringstream ss;
  ss << "xml_node " << node.name() << " does not have child " << name << "!";
  std::string error_msg;
  ss >> error_msg;
  throw error_msg;
}

std::list<pugi::xml_node> dtop::common::fetch_child_list(
    const pugi::xml_node &node) {
  std::list<pugi::xml_node> child_list;
  for (auto iter : node.children()) {
    child_list.push_back(iter);
  }
  return child_list;
}