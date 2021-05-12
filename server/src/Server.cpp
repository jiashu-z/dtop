#include "Server.h"
#include <grpcpp/security/credentials.h>
#include <grpcpp/server_builder.h>
#include <memory>
#include <sstream>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

std::string dtop::server::Server::to_string() const {
  std::stringstream ss;
  ss << "ip: " << this->ip << "\n";
  ss << "port: " << this->port << "\n";
  std::string str;
  ss >> str;
  return str;
}

dtop::server::Server::Server(const std::string &ip_addr, const int& port) {
  this->ip = ip_addr;
  this->port = port;
}

std::string dtop::server::Server::get_ip() const {
  return this->ip;
}

int dtop::server::Server::get_port() const {
  return this->port;
}

std::string dtop::server::Server::get_address() const {
  return this->get_ip() + ":" + std::to_string(this->get_port());
}

void dtop::server::Server::run() {
  this->grpc_service = std::make_unique<ConcreteGRPCService>();
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  grpc::ServerBuilder builder;
  builder.AddListeningPort(this->get_address(), grpc::InsecureServerCredentials());
  builder.RegisterService(this->grpc_service.get());
  this->grpc_server = builder.BuildAndStart();
  this->grpc_server->Wait();
}