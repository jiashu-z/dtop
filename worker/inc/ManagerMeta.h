#ifndef DTOP_RPC_MANAGERMETA_H
#define DTOP_RPC_MANAGERMETA_H

#include "BaseWorker.h"

namespace dtop {
namespace worker {

class ManagerMeta final {
 private:
  /**
   * @brief Save all worker obj.
   */
  std::vector<BaseWorker*> workers;

  /**
   * @brief Register workers. These workers will be maintained by the container.
   */
  void register_workers();

 public:
  ManagerMeta();
  ~ManagerMeta();

  /**
   * @brief Creat all registered workers.
   *
   * @return True if initialize successfully. Otherwise one or more worker
   * failed to creat.
   */
  bool initialize();

  /**
   * @brief Get the vector of the workers maintained by container.
   *        This vector can't be modified.
   *
   * @return The registered worker vector.
   */
  const std::vector<BaseWorker*>& get_workers() const;

  /**
   * @brief Get one worker by worker name.
   *
   * @return The pointer to worker or nullptr if no worker matched.
   */
  BaseWorker* get_worker_by_name(const std::string& worker_name);
};

}  // namespace worker
}  // namespace dtop

#endif  // DTOP_RPC_MANAGERMETA_H
