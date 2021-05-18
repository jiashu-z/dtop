#include "Client.h"

#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "ConcreteGRPCServiceClient.h"
#include "grpcpp/create_channel.h"
#include "grpcpp/security/credentials.h"

dtop::client::Client::Client() = default;

std::string dtop::client::Client::to_string() {
  std::stringstream ss;
  ss << "grpc client addresses: ";
  for (auto &iter : this->grpc_client_map) {
    ss << iter.first << "; ";
  }
  return ss.str();
}

void dtop::client::Client::add_grpc_target(const std::string& addr) {
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  std::shared_ptr<ConcreteGRPCServiceClient> ptr =
      std::make_shared<ConcreteGRPCServiceClient>(
          grpc::CreateChannel(addr, grpc::InsecureChannelCredentials()));
  dtop::client::Client::add_target_to_map<ConcreteGRPCServiceClient>(this->grpc_client_map, addr, ptr);
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
}

void dtop::client::Client::remove_target(const std::string& addr) {
  this->grpc_client_map.erase(addr);
}

std::vector<std::string> dtop::client::Client::get_all_targets_addr() {
  std::vector<std::string> addr_vector;
  for (const auto& iter : this->grpc_client_map) {
    addr_vector.push_back(iter.second->get_addr());
  }
  return addr_vector;
}

void dtop::client::Client::add_api_target(const std::string &addr) {
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  std::shared_ptr<ConcreteAPIServiceClient> ptr = std::make_shared<ConcreteAPIServiceClient>(grpc::CreateChannel(addr, grpc::InsecureChannelCredentials()));
  dtop::client::Client::add_target_to_map<ConcreteAPIServiceClient>(this->api_client_map, addr, ptr);
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
}

std::string dtop::client::Client::get_cluster_stats() {
	throw "Not implemented!";
}

void dtop::client::Client::get_cluster_stats(FetchReplyArrayMessage *response, const FetchRequestMessage *request) {
	std::cout << __FILE__ << ": " << __LINE__ << std::endl;
	for (const auto& iter : this->grpc_client_map) {
		std::cout << __FILE__ << ": " << __LINE__ << std::endl;
		std::cout << iter.first << std::endl;
		::grpc::ClientContext context;
		FetchReplyMessage local_response;
		iter.second->stub->Profile(&context, *request, &local_response);
		auto* reply_ptr = response->mutable_fetch_reply()->Add();
		reply_ptr->CopyFrom(local_response);
		std::cout << __FILE__ << ": " << __LINE__ << std::endl;
	}
}