#include "MemUsageWorker.h"

#include <utility>

#include "pslib.h"

long long dtop::worker::MemUsageWorker::compute_max_mem() { return 0; }

dtop::worker::MemUsageWorker::MemUsageWorker(
    dtop::worker::WorkerType type, std::string worker_name,
    const dtop::worker::WorkerConfig &config)
    : BaseWorker(type, std::move(worker_name), config) {}

bool dtop::worker::MemUsageWorker::setup() {
  max_mem = compute_max_mem();
  return true;
}

bool dtop::worker::MemUsageWorker::act(dtop::worker::ProfileQuery &query,
                                       FetchReplyMessage &reply) {
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  VmemInfo info;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  memset(&info, 0, sizeof(VmemInfo));
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  if (!virtual_memory(&info)) {
    return false;
  }
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  auto used = (int64_t)info.used;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  auto total = (int64_t)info.total;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  std::cout << "used: " << used << std::endl;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  std::cout << "total: " << total << std::endl;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  auto mem_usage_message = MemUsageMessage();
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  mem_usage_message.set_max_mem(total);
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  mem_usage_message.set_used_mem(used);
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  reply.mutable_mem_usage_message()->set_used_mem(used);
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  reply.mutable_mem_usage_message()->set_max_mem(total);
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  return true;
}

bool dtop::worker::MemUsageWorker::shutdown() { return true; }

long long dtop::worker::MemUsageWorker::compute_used_mem() {
  if (compute_timestamp() - timestamp >= config.cache_time) {
    timestamp = compute_timestamp();
    used_mem = 0;
  }
  return used_mem;
}
