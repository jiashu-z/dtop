#include "ConcreteAPIService.h"
#include <grpcpp/impl/codegen/status.h>

::grpc::Status dtop::server::ConcreteAPIService::GetServerStatus(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::ServerStatusArrMessage *response) {
  return ::grpc::Status::OK;
}

::grpc::Status dtop::server::ConcreteAPIService::GetServerAddresses(::grpc::ServerContext *context, const ::google::protobuf::Empty *request, ::StringArrayMessage *response) {
  // for (auto iter : this->server->)
  return ::grpc::Status::OK;
}

dtop::server::ConcreteAPIService::~ConcreteAPIService() = default;