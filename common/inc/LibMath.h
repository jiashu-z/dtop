#ifndef DTOP_COMMON_LIBMATH_H
#define DTOP_COMMON_LIBMATH_H

#include <exception>
#include <iostream>

namespace dtop {
namespace common {

/**
 * @brief Check if str can be converted to a valid integer.
 * @deprecated
 * @param str The input str to check.
 * @return true str can be converted to a valid integer.
 * @return false str cannot be converted to a valid integer.
 */
bool is_valid_int(const std::string& str);

/**
 * @brief Check if left < mid && mid < right.
 * 
 * @tparam T The type name.
 * @param left smaller bond.
 * @param right greater bond.
 * @param mid The input number to check.
 * @return true left < mid < right
 * @return false !(left < mid < right)
 */
template<class T>
bool between_strict(const T& left, const T& right, const T& mid) {
  return left < mid && mid < right;
}

/**
 * @brief Check if left <= mid && mid <= right.
 * 
 * @tparam T The type name.
 * @param left smaller bond.
 * @param right greater bond.
 * @param mid The input number to check.
 * @return true left < mid < right
 * @return false !(left < mid < right)
 */
template<class T>
bool between_nonstrict(const T& left, const T& right, const T& mid) {
  return left <= mid && mid <= right;
}

}
}

#endif