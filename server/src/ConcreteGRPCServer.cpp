#include "ConcreteGRPCServer.h"
#include "grpcpp/impl/codegen/status.h"
#include "Server.h"
#include <sstream>

::grpc::Status dtop::server::ConcreteGRPCServer::GetIP(::grpc::ServerContext* context, 
const ::google::protobuf::Empty* request, 
::StringMessage* response) {
  response->set_val(this->server->ip_addr);
  return ::grpc::Status::OK;
}