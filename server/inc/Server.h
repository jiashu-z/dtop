#ifndef DTOP_SERVER_SERVER_H
#define DTOP_SERVER_SERVER_H

#include <iostream>
#include <memory>
#include "ConcreteGRPCService.h"
#include <grpcpp/server.h>
#include "ServerProperty.h"

namespace dtop {
namespace server {

class ConcreteGRPCService;

/**
 * @brief An encapsulation of grpc server and monitor guards.
 * 
 */
class Server {
 private:

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

  /**
   * @brief Pointer to the grpc server.
   * 
   */
  std::unique_ptr<grpc::Server> grpc_server;

 public:

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
  explicit Server(const std::string &config_file_path);

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
   * @brief Init config according to config xml.
   * 
   */
  void init_config();
};

}
}

#endif