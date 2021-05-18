#include "Future.h"

#include <sstream>

dtop::worker::Future::Future(std::string label, std::string description)
    : label(std::move(label)), desc(std::move(description)) {}

std::string dtop::worker::Future::to_string() const {
  std::ostringstream oss;
  oss << "Future[" << label << "]: " << desc;
  return oss.str();
}
