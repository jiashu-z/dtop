#ifndef DTOP_SERVER_SERVER_H
#define DTOP_SERVER_SERVER_H

#include <iostream>
#include <memory>
#include "ConcreteGRPCServer.h"

namespace dtop {
namespace server {

class ConcreteGRPCServer;

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
  std::string ip_addr;

  /**
   * @brief The port number this sever binds. By default 8080.
   * 
   */
  int port;

  /**
   * @brief Pointer to the grpc server.
   * 
   */
  std::unique_ptr<dtop::server::ConcreteGRPCServer> grpc_server;

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

  friend class ConcreteGRPCServer;
};


}
}

#endif