#include "ConcreteGRPCService.h"

#include <cassert>

#include "ProfileQuery.h"
#include "Server.h"
#include "WorkerType.h"
#include "grpcpp/impl/codegen/status.h"
#include "ManagerMeta.h"

::grpc::Status dtop::server::ConcreteGRPCService::GetIP(
    ::grpc::ServerContext *context, const ::google::protobuf::Empty *request,
    ::StringMessage *response) {
  response->set_val(this->server->get_ip());
  return ::grpc::Status::OK;
}

::grpc::Status dtop::server::ConcreteGRPCService::GetPort(
    ::grpc::ServerContext *context, const ::google::protobuf::Empty *request,
    ::IntegerMessage *response) {
  response->set_val(this->server->get_port());
  return ::grpc::Status::OK;
}

::grpc::Status dtop::server::ConcreteGRPCService::GetAddr(
    ::grpc::ServerContext *context, const ::google::protobuf::Empty *request,
    ::StringMessage *response) {
  assert(this->server != nullptr);
  response->set_val(this->server->get_addr());
  return ::grpc::Status::OK;
}

::grpc::Status dtop::server::ConcreteGRPCService::Profile(
    ::grpc::ServerContext *context, const ::FetchRequestMessage *request,
    ::FetchReplyMessage *response) {
  dtop::worker::ProfileQuery q;
  auto s = this->server;
  auto meta = server->manager_meta;
  meta.get_worker(dtop::worker::WorkerType::MEM_USAGE_WORKER)->act(q, *response);
  return ::grpc::Status::OK;
}
