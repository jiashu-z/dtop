#ifndef DTOP_CLIENT_CLIENT_H
#define DTOP_CLIENT_CLIENT_H

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <map>
#include <vector>

#include "ConcreteAPIServiceClient.h"
#include "ConcreteGRPCServiceClient.h"
#include "server.grpc.pb.h"

namespace dtop {
namespace client {

class Client {
 private:
  template <typename T>
  static void add_target_to_map(
      std::map<const std::string, std::shared_ptr<T>>& map,
      const std::string& addr, std::shared_ptr<T> ptr) {
    if (map.template find(addr) != map.end()) {
      map[addr] = ptr;
    } else {
      map.insert(std::pair<const std::string, std::shared_ptr<T>>(addr, ptr));
    }
  }

 public:
  std::map<const std::string, std::shared_ptr<ConcreteGRPCServiceClient>>
      grpc_client_map;

  std::map<const std::string, std::shared_ptr<ConcreteAPIServiceClient>>
      api_client_map;

  explicit Client();

  std::string to_string();

  void add_grpc_target(const std::string& addr);

  void add_api_target(const std::string& addr);

  void remove_target(const std::string& addr);

  std::vector<std::string> get_all_targets_addr();

  void get_cluster_status(ServerStatusArrayMessage *response,
												  const StringArrayMessage* request);

  void exec_cluster_command(StringArrayMessage* response,
														const CommandArrayMessage* request);

  void get_cluster_metric(FetchReplyArrayMessage* response,
                          const FetchRequestMessage* request);
};

}  // namespace client
}  // namespace dtop

#endif