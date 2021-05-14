#include "Server.h"
#include <grpcpp/security/credentials.h>
#include <grpcpp/server_builder.h>
#include <memory>
#include <sstream>
#include <string>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

std::string dtop::server::Server::to_string() const {
  return this->server_property->to_string();
}

std::string dtop::server::Server::get_ip() const {
  return this->server_property->get_ip();
}

int dtop::server::Server::get_port() const {
  return this->server_property->get_port();
}

std::string dtop::server::Server::get_addr() const {
  return this->server_property->get_addr();
}

void dtop::server::Server::run() {
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  this->grpc_service = std::make_unique<ConcreteGRPCService>();
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  grpc::EnableDefaultHealthCheckService(true);
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  grpc::ServerBuilder builder;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  builder.AddListeningPort(this->get_addr(), grpc::InsecureServerCredentials());
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  builder.RegisterService(this->grpc_service.get());
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  this->grpc_server = builder.BuildAndStart();
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  this->grpc_service->server = this;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  this->grpc_server->Wait();
}

void dtop::server::Server::init_config() {
  this->server_property = std::make_unique<ServerProperty>(this->config_file_path);
}

dtop::server::Server::Server(const std::string &config_file_path) {
  this->config_file_path = config_file_path;
  this->init_config();
}