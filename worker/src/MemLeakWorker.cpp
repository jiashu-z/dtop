#include "MemLeakWorker.h"

#include "pslib.h"
#include <memory>
#include <thread>

std::map<int, std::map<int64_t, dtop::worker::MemLeakWorker::MemTraceEntry>> dtop::worker::MemLeakWorker::mem_map = {};

dtop::worker::MemLeakWorker::MemLeakWorker() : BaseWorker("Memory usage worker") {};

void dtop::worker::MemLeakWorker::init_futures() {
  this->should_break = true;
  futures.push_back(new Future("MEM_USAGE", "The overall memory usage"));
  futures.push_back(
      new Future("MEM_PER_PROC", "The detail memory info of processes"));
}

bool dtop::worker::MemLeakWorker::setup_config(
    dtop::worker::WorkerConfig& worker_config) {
  return true;
}

bool dtop::worker::MemLeakWorker::handle_start() { 
  this->should_break = false;
  this->map_thread_ptr = std::make_unique<std::thread>(update_map, this);
  return true; 
}

bool dtop::worker::MemLeakWorker::handle_process(
    dtop::worker::ProfileQuery* query, FetchReplyMessage* reply) {
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

  auto mut_msg = reply->mutable_mem_usage_message();
  mut_msg->set_total(info.total);
  mut_msg->set_available(info.available);
  mut_msg->set_used(info.used);
  mut_msg->set_free(info.free);
  mut_msg->set_active(info.active);
  mut_msg->set_inactive(info.inactive);
  mut_msg->set_buffers(info.buffers);
  mut_msg->set_cached(info.cached);
  mut_msg->set_wired(info.wired);

  return true;
}

bool dtop::worker::MemLeakWorker::handle_pause() { 
  this->should_break = true;
  this->map_thread_ptr->join();
  this->map_thread_ptr = nullptr;
  return true; 
}

bool dtop::worker::MemLeakWorker::handle_stop() { 
  this->should_break = true;
  if (this->map_thread_ptr) {
    this->map_thread_ptr->join();
    this->map_thread_ptr = nullptr;
  }
  return true; 
}
