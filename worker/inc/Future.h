#ifndef DTOP_RPC_FUTURE_H
#define DTOP_RPC_FUTURE_H

#include <string>

namespace dtop {
namespace worker {

class Future {
 public:
  explicit Future(std::string label, std::string description);

  /**
   * @brief The label that declare this future.
   *        Duplication is NOT allowed, otherwise the result may be incorrect
   */
  const std::string label;

  /**
   * @brief The description of this future.
   */
  const std::string desc;

  std::string to_string() const;
};

}  // namespace worker
}  // namespace dtop

#endif  // DTOP_RPC_FUTURE_H
