#ifndef DTOP_SERVER_CONCRETEAPISERVICE_H
#define DTOP_SERVER_CONCRETEAPISERVICE_H

#include "api.grpc.pb.h"
#include "api.pb.h"
#include <grpcpp/impl/codegen/server_context.h>

namespace dtop {
namespace server {

class Server;

class ConcreteAPIService final : public APIService::Service {
 private:

 public:
  Server* server = nullptr;
  
  ~ConcreteAPIService();

  ::grpc::Status GetServerStatus(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::ServerStatusArrMessage* response) override;

  ::grpc::Status GetServerAddresses(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::StringArrayMessage* response) override;

  ::grpc::Status GetStats(::grpc::ServerContext* context, const ::FetchRequestMessage* request, ::FetchReplyArrayMessage* response) override;
};

}
}

#endif