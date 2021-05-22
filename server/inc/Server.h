#ifndef DTOP_SERVER_SERVER_H
#define DTOP_SERVER_SERVER_H

#include <Manager.h>
#include <grpcpp/server.h>
#include <unistd.h>

#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>

#include "Client.h"
#include "ConcreteAPIService.h"
#include "ConcreteGRPCService.h"
#include "ManagerMeta.h"
#include "ServerProperty.h"
#include "pslib.h"

namespace dtop {
namespace server {

class ConcreteGRPCService;

/**
 * @brief An encapsulation of grpc server and monitor guards.
 *
 */
class Server {
 private:
 public:
  static void test_virtual_mem_info() {
    VmemInfo r;
    // Empty out to prevent garbage in platform-specific fields
    memset(&r, 0, sizeof(VmemInfo));
    if (!virtual_memory(&r)) {
      printf("Aborting\n");
      return;
    }
    printf(" -- virtual_memory\n");
    printf("Total: %" PRIu64 "\n", r.total);
    printf("Available: %" PRIu64 "\n", r.available);
    printf("Percent: %.1f\n", r.percent);
    printf("Used: %" PRIu64 "\n", r.used);
    printf("Free: %" PRIu64 "\n", r.free);
    printf("Active: %" PRIu64 "\n", r.active);
    printf("Inactive: %" PRIu64 "\n", r.inactive);
    printf("Buffers: %" PRIu64 "\n", r.buffers);
    printf("Cached: %" PRIu64 "\n", r.cached);
    printf("Wired: %" PRIu64 "\n", r.wired);
    printf("\n");
  }

  /**
   * @brief Path to config xml file.
   *
   */
  std::string config_file_path;

  /**
   * @brief Pointer to the grpc service.
   *
   */
  std::unique_ptr<ConcreteGRPCService> grpc_service;

  std::unique_ptr<ConcreteAPIService> api_service;

  /**
   * @brief Pointer to the grpc server.
   *
   */
  std::unique_ptr<grpc::Server> grpc_server;

  dtop::client::Client client;

  void client_add_target();

  worker::Manager manager;

  /**
   * @brief Pointer to ServerProperty object.
   */
  std::unique_ptr<ServerProperty> server_property;

  /**
   * @brief Returns a string that describes this Server object.
   *
   * @return std::string The description string.
   */
  std::string to_string() const;

  /**
   * @brief Construct a new Server object
   *
   * @param config_file_path path to config xml.
   */
  explicit Server(const std::string& config_file_path);

  ~Server() = default;

  /**
   * @brief Run this server.
   *
   */
  void run();

  /**
   * @brief Get the ip of this server.
   *
   * @return std::string The ip address.
   */
  std::string get_ip() const;

  /**
   * @brief Get the port this server binds to.
   *
   * @return int The port number.
   */
  int get_port() const;

  /**
   * @brief Get the address object: ip:port
   *
   * @return std::string The address string.
   */
  std::string get_addr() const;

	/**
	 * @brief Process control message from center server.
	 *
	 * @param request
	 * @param reply
	 * @return bool True if no error occurs.
	 */
	bool exec_command(const CommandArrayMessage* request, StringArrayMessage* reply);

  /**
   * @brief Process get_server_metric query from center server.
   *
   * @param request
   * @param reply
   * @return bool True if no error occurs.
   */
  bool get_server_metric(const FetchRequestMessage* request, FetchReplyMessage* reply);

  /**
   * @brief Get the server status.
   *
   * @param request
   * @param reply
   */
  void get_server_status(const StringArrayMessage* request,
                         ServerStatusMessage* reply);

  /**
   * @brief Init config according to config xml.
   *
   */
  void init_config();
};

}  // namespace server
}  // namespace dtop

#endif