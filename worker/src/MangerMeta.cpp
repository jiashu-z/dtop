#include <MemUsageWorker.h>

#include "ManagerMeta.h"

typedef std::unordered_map<dtop::worker::WorkerType, dtop::worker::BaseWorker*>
    WorkerMap;

dtop::worker::ManagerMeta::ManagerMeta(WorkerConfig& config)
    : worker_config(config) {
  init_registered_worker_map();
}

dtop::worker::ManagerMeta::~ManagerMeta() {
  //	for (auto& pair: this->registered_worker_map) {
  //		delete pair.second;
  //	}
}

void dtop::worker::ManagerMeta::init_registered_worker_map() {
  this->registered_worker_map[MEM_USAGE_WORKER] =
      new dtop::worker::MemUsageWorker(MEM_USAGE_WORKER, "Memory usage worker",
                                       worker_config);
}

dtop::worker::BaseWorker* dtop::worker::ManagerMeta::get_worker(
    dtop::worker::WorkerType type) {
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  auto* base_ptr = (dtop::worker::BaseWorker*)this->registered_worker_map[type];
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  return base_ptr;
}
