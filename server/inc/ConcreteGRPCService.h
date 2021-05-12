#ifndef DTOP_SERVER_CONCRETEGRPCSERVER
#define DTOP_SERVER_CONCRETEGRPCSERVER

#include "server.grpc.pb.h"
#include <memory>

namespace dtop {
namespace server {

class Server;

class ConcreteGRPCService final : public GRPCService::Service {
 private:
  
  /**
   * @brief Pointer to the Server object, for calling guards.
   * 
   */
  const Server* server;
 public:
  /**
   * @brief Get current IP address.
   * 
   * @param context 
   * @param request 
   * @param response 
   * @return ::grpc::Status 
   */
  ::grpc::Status GetIP(::grpc::ServerContext* context, 
  const ::google::protobuf::Empty* request, 
  ::StringMessage* response) override;

  /**
   * @brief Get the Port number.
   * 
   * @param context 
   * @param request 
   * @param response 
   * @return ::grpc::Status 
   */
  ::grpc::Status GetPort(::grpc::ServerContext* context, 
  const ::google::protobuf::Empty* request, 
  ::IntegerMessage* response) override;

  /**
   * @brief Get the Addr string ip:port
   * 
   * @param context 
   * @param request 
   * @param response 
   * @return ::grpc::Status 
   */
  ::grpc::Status GetAddr(::grpc::ServerContext* context, 
  const ::google::protobuf::Empty* request, 
  ::StringMessage* response) override;

  /**
   * @brief Run the grpc server.
   * 
   */
  void run();
};

}
}

#endif