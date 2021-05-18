#include "ConcreteGRPCService.h"

#include <cassert>

#include "ProfileQuery.h"
#include "Server.h"
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
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  dtop::worker::ProfileQuery q;
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  auto s = this->server;
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  auto meta = server->manager_meta;
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  auto worker = meta.get_worker(dtop::worker::WorkerType::MEM_USAGE_WORKER);
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  assert(worker != nullptr);
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  worker->handle_process(q, *response);
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;

	this->server->profile(request, response);
	std::cout << __FILE__ << ": " << __LINE__ << std::endl;
	std::cout << request->SerializeAsString() << std::endl;
	std::cout << response->SerializeAsString() << std::endl;
	std::cout << __FILE__ << ": " << __LINE__ << std::endl;
	return ::grpc::Status::OK;
}

::grpc::Status dtop::server::ConcreteGRPCService::GetServerStatus(
		::grpc::ServerContext *context, const ::StringArrayMessage *request,
    ::ServerStatusMessage *response) {
	this->server->get_server_status(request, response);
	return grpc::Status::OK;
}
