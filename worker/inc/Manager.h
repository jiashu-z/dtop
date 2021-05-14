#ifndef DTOP_RPC_MANAGER_H
#define DTOP_RPC_MANAGER_H

#include <memory>
#include <vector>

#include "BaseWorker.h"
#include "ManagerMeta.h"

namespace dtop {
namespace worker {

class Manager {
 private:
  std::vector<BaseWorker> workers;

 public:
};
}  // namespace worker
}  // namespace dtop

#endif  // DTOP_RPC_MANAGER_H
