#ifndef DTOP_CLIENT_CONCRETEAPISERVICECLIENT_H
#define DTOP_CLIENT_CONCRETEAPISERVICECLIENT_H

#include <grpcpp/grpcpp.h>

#include <memory>

#include "api.grpc.pb.h"

namespace dtop {
namespace client {

class Client;

class ConcreteAPIServiceClient {
 private:
  std::unique_ptr<APIService::Stub> stub;

  Client *client;

 public:
  explicit ConcreteAPIServiceClient(
      const std::shared_ptr<grpc::Channel> &channel)
      : stub(APIService::NewStub(channel)) {
    this->client = nullptr;
  };

  /**
   * @brief
   *
   * TODO: Return what?
   */
  void get_status_arr();

  void get_stats();
};

}  // namespace client
}  // namespace dtop

#endif