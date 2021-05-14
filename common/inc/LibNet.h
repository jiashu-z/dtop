#ifndef DTOP_COMMON_LIBNET_H
#define DTOP_COMMON_LIBNET_H

#include <iostream>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <exception>
#include <string>
#include "LibMath.h"

/**
 * @brief Check the validity of ipv4 address. 
 * This function does not trim input string.
 * 
 * @param ip_str ipv4 address string.
 * @return true The address is valid.
 * @return false The address is not valid.
 */
bool is_ipv4_valid(const std::string& ip_str);

#endif