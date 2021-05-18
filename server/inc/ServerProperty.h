#ifndef DTOP_SERVER_SERVERPROPERTY_H
#define DTOP_SERVER_SERVERPROPERTY_H

#include <iostream>
#include <list>
#include <pugixml.hpp>

namespace dtop {
namespace server {

class ServerProperty {
 private:
  std::string config_file_path;
  pugi::xml_document config_file;
  std::string ip;
  int port{};
  int thread_num{};

 public:
  std::list<std::string> other_server_addr_list{};

  /**
   * @brief Construct a new Server Property object
   *
   * @param config_file_path The path to config xml file.
   */
  explicit ServerProperty(const std::string &config_file_path);

  /**
   * @brief Config according to xml file path.
   *
   */
  inline void config();

  /**
   * @brief Get ip:port address.
   *
   * @return The address string.
   */
  std::string get_addr();

  int get_thread_num() const;

  std::string get_ip() const;

  int get_port() const;

  std::string to_string() const;
};

}  // namespace server
}  // namespace dtop

#endif