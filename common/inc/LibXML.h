#ifndef DTOP_COMMON_LIBXML_H
#define DTOP_COMMON_LIBXML_H

#include "pugixml.hpp"
#include <list>

namespace dtop {
namespace common {

/**
 * @brief Check the existence of xml_node name and fetch it from node.
 *
 * @param node The parent node.
 * @param name The child node.
 * @return pugi::xml_node The child node if it exists.
 */
pugi::xml_node check_and_fetch_xml_node(const pugi::xml_node &node,
                                        const std::string &name);

std::list<pugi::xml_node> fetch_child_list(const pugi::xml_node &node);

}  // namespace common
}  // namespace dtop

#endif