#include "LibNet.h"

bool is_ipv4_valid(const std::string &ip_str) {
  std::vector<std::string> tokens;
  boost::split(tokens, ip_str, boost::is_any_of("."));
  for (const auto &iter : tokens) {
    int i = -1;
    try {
      i = std::stoi(iter);
    } catch (std::exception e) {
      std::cout << e.what() << std::endl;
      return false;
    }
    if (!dtop::common::between_nonstrict(0, 255, i)) {
      return false;
    }
  }
  return true;
}