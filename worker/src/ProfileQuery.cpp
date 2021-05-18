#include "ProfileQuery.h"

#include <sstream>

bool dtop::worker::ProfileQuery::decode(const FetchRequestMessage* request) {
  if (request->request_arr_size() != request->param_arr_size()) {
    return false;
  }
  int idx = 0;
  for (auto& req : request->request_arr()) {
    // suppose no conflict for now
    req_map[req] = request->param_arr()[idx++];
  }
  return true;
}

std::string dtop::worker::ProfileQuery::to_string() {
  std::ostringstream oss;
  oss << "ProfileQuery[";
  unsigned long cnt = req_map.size();
  for (auto& it : req_map) {
    oss << "{" << it.first;
    if (!it.second.empty()) {
      oss << "," << it.second;
    }
    oss << "}";
    if (cnt-- > 1) {
      oss << ",";
    }
  }
  oss << "]";
  return oss.str();
}
