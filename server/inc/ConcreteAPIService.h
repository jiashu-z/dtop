#ifndef DTOP_SERVER_CONCRETEAPISERVICE_H
#define DTOP_SERVER_CONCRETEAPISERVICE_H

#include "api.grpc.pb.h"
#include "api.pb.h"

namespace dtop {
namespace server {

class Server;

class ConcreteAPIService final : public APIService::Service {
 private:

 public:
  Server* server = nullptr;

  ::grpc::Status GetServerStatus(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::ServerStatusArrMessage* response) override;
};

}
}

#endif