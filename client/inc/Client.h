#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <iostream>
#include <grpcpp/grpcpp.h>
#include "server.grpc.pb.h"
#include <map>
#include "ConcreteGRPCServiceClient.h"
#include <vector>

namespace dtop {
namespace client {

class Client {
  private:
  std::map<std::string, std::shared_ptr<ConcreteGRPCServiceClient>> client_map;

  public:
  explicit Client();

  std::string to_string();

  void add_target(const std::string& addr);

  void remove_target(const std::string& addr);

  std::vector<std::string> get_all_targets_addr();
};

}
}

#endif