#ifndef DTOP_SERVER_CONCRETEGRPCSERVER
#define DTOP_SERVER_CONCRETEGRPCSERVER

#include <memory>

#include "server.grpc.pb.h"

namespace dtop {
namespace server {

class Server;

class ConcreteGRPCService final : public GRPCService::Service {
 private:
 public:
  /**
   * @brief Pointer to the Server object, for calling guards.
   *
   */
  Server* server = nullptr;

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
   * @brief Execute the command on target server
   *
   * @param context
   * @param request
   * @param response
   * @return ::grpc::Status
   */
  ::grpc::Status ExecCommand(::grpc::ServerContext *context,
														 const ::CommandArrayMessage *request,
														 ::StringArrayMessage *response) override;

  /**
   * @brief Collect profiling data of current machine.
   *        Called by another server.
   *
   * @param context
   * @param request
   * @param response
   * @return ::grpc::Status
   */
  ::grpc::Status GetServerMetric(::grpc::ServerContext* context,
                                 const ::FetchRequestMessage* request,
                                 ::FetchReplyMessage* response) override;

  /**
   * @brief Get the running status of current server
   *
   * @param context
   * @param request flags: -wf with futures; -wfd with future description
   * @param response
   * @return ::grpc::Status
   */
  ::grpc::Status GetServerStatus(::grpc::ServerContext* context,
                                 const ::StringArrayMessage* request,
                                 ::ServerStatusMessage* response) override;

  /**
   * @brief Run the grpc server.
   *
   */
  void run();
};

}  // namespace server
}  // namespace dtop

#endif