#include "ManagerMeta.h"
#include "MemUsageWorker.h"
#include "MemLeakWorker.h"
#include "MemoryMonitorWorker.h"
#include "MemLeakWorker.h"

void dtop::worker::ManagerMeta::register_workers() {
  workers.push_back(new MemUsageWorker());
  workers.push_back(new MemoryMonitorWorker());
  workers.push_back(new MemLeakWorker());
}

dtop::worker::ManagerMeta::ManagerMeta() = default;

dtop::worker::ManagerMeta::~ManagerMeta() {
  for (auto& worker : this->workers) {
    delete worker;
  }
}

bool dtop::worker::ManagerMeta::initialize() {
  try {
    register_workers();
  } catch (std::exception& e) {
    std::cout << "Error when initialize ManagerMeta: " << e.what() << std::endl;
    return false;
  }
  return true;
}

const std::vector<dtop::worker::BaseWorker*>&
dtop::worker::ManagerMeta::get_workers() const {
  return this->workers;
}

dtop::worker::BaseWorker* dtop::worker::ManagerMeta::get_worker_by_name(
    const std::string& worker_name) {
  for (BaseWorker* worker_ptr : this->workers) {
    if (worker_ptr->worker_name == worker_name) {
      return worker_ptr;
    }
  }
  return nullptr;
}
