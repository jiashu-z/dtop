#include "LibMath.h"

#include <exception>

bool dtop::common::is_valid_int(const std::string &str) {
  try {
    std::stoi(str);
  } catch (const std::exception &) {
    return false;
  }
  return true;
}