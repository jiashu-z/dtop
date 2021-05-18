#include "MemUsageWorker.h"

#include "pslib.h"

dtop::worker::MemUsageWorker::MemUsageWorker() : BaseWorker("Memory usage worker") {}

void dtop::worker::MemUsageWorker::init_futures() {
	futures.push_back(new Future("MEM_USAGE", "The overall memory usage"));
	futures.push_back(new Future("MEM_PER_PROC", "The detail memory info of processes"));
}

bool dtop::worker::MemUsageWorker::setup_config(dtop::worker::WorkerConfig& worker_config) {
	return true;
}

bool dtop::worker::MemUsageWorker::handle_start() {
  return true;
}

bool dtop::worker::MemUsageWorker::handle_process(dtop::worker::ProfileQuery* query,
                                                  FetchReplyMessage* reply) {
	std::cout << __FILE__ << ": " << __LINE__ << std::endl;
	std::cout << query->to_string() << std::endl;
	std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  VmemInfo info;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  memset(&info, 0, sizeof(VmemInfo));
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  if (!virtual_memory(&info)) {
    return false;
  }
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  auto used = (int64_t)info.used;
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  auto total = (int64_t)info.total;
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  std::cout << "used: " << used << std::endl;
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  std::cout << "total: " << total << std::endl;
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  auto mem_usage_message = MemUsageMessage();
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  mem_usage_message.set_max_mem(total);
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  mem_usage_message.set_used_mem(used);
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  reply->mutable_mem_usage_message()->set_used_mem(used);
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//  reply->mutable_mem_usage_message()->set_max_mem(total);
//  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
/**
 *   int64 total = 1;
  int64 available = 2;
  int64 used = 3;
  int64 free = 4;
  int64 active = 5;
  int64 inactive = 6;
  int64 buffers = 7;
  int64 cached = 8;
  int64 wired = 9;
 */

	auto mut = reply->mutable_mem_usage_message();
	mut->set_total(info.total);
	mut->set_available(info.available);
	mut->set_used(info.used);
	mut->set_free(info.free);
	mut->set_active(info.active);
	mut->set_inactive(info.inactive);
	mut->set_buffers(info.buffers);
	mut->set_cached(info.cached);
	mut->set_wired(info.wired);

  return true;
}

bool dtop::worker::MemUsageWorker::handle_pause() {
	return true;
}

bool dtop::worker::MemUsageWorker::handle_stop() {
	return true;
}
