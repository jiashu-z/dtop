#ifndef DTOP_SERVER_SERVER_H
#define DTOP_SERVER_SERVER_H

#include <iostream>
#include <memory>
#include "ConcreteGRPCService.h"
#include <grpcpp/server.h>

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
   * @brief The ip addr of this server. By default "localhost".
   * 
   */
  std::string ip;

  /**
   * @brief The port number this sever binds. By default 8080.
   * 
   */
  int port;

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
   * @brief Returns a string that describes this Server object.
   * 
   * @return std::string The description string.
   */
  std::string to_string() const;

  /**
   * @brief Construct a new Server object
   * 
   * @param ip_addr The ip addr of this server. 
   * @param port The port this server binds.
   */
  Server(const std::string &ip_addr, const int& port);

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
  std::string get_address() const;
};


}
}

#endif