#ifndef DTOP_SERVER_CONCRETEAPISERVICE_H
#define DTOP_SERVER_CONCRETEAPISERVICE_H

#include <grpcpp/impl/codegen/server_context.h>

#include "api.grpc.pb.h"
#include "api.pb.h"

namespace dtop {
namespace server {

class Server;

class ConcreteAPIService final : public APIService::Service {
 private:
 public:
  Server* server = nullptr;

  ~ConcreteAPIService();

  ::grpc::Status GetClusterStatus(::grpc::ServerContext* context,
                                  const ::StringArrayMessage* request,
                                  ::ServerStatusArrayMessage* response) override;

  ::grpc::Status GetServerAddresses(::grpc::ServerContext* context,
                                    const ::google::protobuf::Empty* request,
                                    ::StringArrayMessage* response) override;

	::grpc::Status ExecClusterCommand(::grpc::ServerContext* context,
	                                  const ::CommandArrayMessage* request,
	                                  ::StringArrayMessage* response) override;

  ::grpc::Status GetClusterMetric(::grpc::ServerContext* context,
                                  const ::FetchRequestMessage* request,
                                  ::FetchReplyArrayMessage* response) override;

  ::grpc::Status GetAggregatedVirtualMemInfo(
      ::grpc::ServerContext* context, const ::FetchRequestMessage* request,
      ::FetchReplyArrayMessage* response) override;
};

}  // namespace server
}  // namespace dtop

#endif