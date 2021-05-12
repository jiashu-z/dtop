#include "Client.h"
#include "ConcreteGRPCServiceClient.h"
#include "grpcpp/create_channel.h"
#include "grpcpp/security/credentials.h"
#include <memory>
#include <sstream>
#include <string>
#include <utility>

dtop::client::Client::Client() {
  
}

std::string dtop::client::Client::to_string() {
  return "unimplemented!";
}

void dtop::client::Client::add_target(const std::string& addr) {
  std::string s = addr;
  ConcreteGRPCServiceClient client(grpc::CreateChannel(addr, grpc::InsecureChannelCredentials()));
  std::shared_ptr<ConcreteGRPCServiceClient> ptr = std::make_shared<ConcreteGRPCServiceClient>(grpc::CreateChannel(addr, grpc::InsecureChannelCredentials()));
  this->client_map.insert(std::pair<std::string, std::shared_ptr<ConcreteGRPCServiceClient>>(s, ptr));
}

void dtop::client::Client::remove_target(const std::string &addr) {
  this->client_map.erase(addr);
}

std::vector<std::string> dtop::client::Client::get_all_targets_addr() {
  std::vector<std::string> addr_vector;
  for (auto iter : this->client_map) {
    addr_vector.push_back(iter.second->get_addr());
  }
  return addr_vector;
}