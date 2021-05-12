#ifndef DTOP_CLIENT_CONCRETEGRPCSERVICECLIENT
#define DTOP_CLIENT_CONCRETEGRPCSERVICECLIENT

#include <memory>
#include "server.grpc.pb.h"
#include <grpcpp/grpcpp.h>

namespace dtop {
namespace client {

class Client;

class ConcreteGRPCServiceClient {
 private:
  std::unique_ptr<GRPCService::Stub> stub;

  Client * client;
 public:
  explicit ConcreteGRPCServiceClient(const std::shared_ptr<grpc::Channel> &channel) : stub(GRPCService::NewStub(channel)) {};

  std::string get_addr();
};

}
}

#endif