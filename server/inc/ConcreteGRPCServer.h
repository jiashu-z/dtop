#ifndef DTOP_SERVER_CONCRETEGRPCSERVER
#define DTOP_SERVER_CONCRETEGRPCSERVER

#include "server.grpc.pb.h"
#include <memory>

namespace dtop {
namespace server {

class Server;

class ConcreteGRPCServer final : public GRPCService::Service {
 private:
  const Server* server;
 public:
  /**
   * @brief Get current IP.
   * 
   * @param context 
   * @param request 
   * @param response 
   * @return ::grpc::Status 
   */
  ::grpc::Status GetIP(::grpc::ServerContext* context, 
  const ::google::protobuf::Empty* request, 
  ::StringMessage* response) override;
};

}
}

#endif