#include "ConcreteGRPCService.h"
#include "grpcpp/impl/codegen/status.h"
#include "Server.h"
#include <cassert>

::grpc::Status dtop::server::ConcreteGRPCService::GetIP(::grpc::ServerContext *context,
                                                        const ::google::protobuf::Empty *request,
                                                        ::StringMessage *response) {
  response->set_val(this->server->get_ip());
  return ::grpc::Status::OK;
}

::grpc::Status dtop::server::ConcreteGRPCService::GetPort(::grpc::ServerContext *context,
                                                          const ::google::protobuf::Empty *request,
                                                          ::IntegerMessage *response) {
  response->set_val(this->server->get_port());
  return ::grpc::Status::OK;
}

::grpc::Status dtop::server::ConcreteGRPCService::GetAddr(::grpc::ServerContext *context,
                                                          const ::google::protobuf::Empty *request,
                                                          ::StringMessage *response) {
  assert(this->server != nullptr);
  response->set_val(this->server->get_addr());
  return ::grpc::Status::OK;
}

::grpc::Status dtop::server::ConcreteGRPCService::Profile(::grpc::ServerContext *context,
                                                          const ::FetchRequestMessage *request,
                                                          ::FetchReplyMessage *response) {
  return ::grpc::Status::OK;
}
