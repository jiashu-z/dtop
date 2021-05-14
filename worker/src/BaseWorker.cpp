#include "BaseWorker.h"

dtop::worker::BaseWorker::BaseWorker(dtop::worker::WorkerType type,
                                     std::string worker_name,
                                     const WorkerConfig& config)
    : worker_type(type), worker_name(std::move(worker_name)), config(config) {}

std::string dtop::worker::BaseWorker::to_string() const {
  return this->worker_name;
}

long long dtop::worker::BaseWorker::compute_timestamp() {
  timeval tv{};
  gettimeofday(&tv, nullptr);
  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
