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

void dtop::worker::MemLeakWorker::update_map(dtop::worker::MemLeakWorker* self)  {
  malloc_free_msg_t msg;
  void *buf = (void *)&msg;

  // Keeps the thread running until pause or stop.
  while (self->should_break) {

    // Iterate the map of all pids.
    self->mut.lock();
    for (auto iter : self->pid_map_) {
      if (self->should_break) {
        break;
      }

      auto& pid = iter.first;
      const std::string fifo_path = "/tmp/fifo" + std::to_string(pid);
      int fd = open(fifo_path.c_str(), O_RDONLY | O_NONBLOCK);
      if (fd == -1) {
        continue;
      }

      // Read until FIFO is empty or error, or until pause or stop.
      while (self->should_break) {
        size_t ret = read(fd, buf, malloc_msg_size);
        if (ret == 0 || ret == -1) {
          break;
        }
        assert(msg.mode == mode_malloc || msg.mode == mode_free);
        if (msg.mode == mode_malloc) {
          msg_ts_pair_t msg_ts_pair = std::pair<malloc_free_msg_t, int64_t>(msg, std::time(nullptr));
          assert(iter.first == msg.pid);
          self->pid_map_[iter.first].insert(std::pair<int64_t, msg_ts_pair_t>(msg.addr, msg_ts_pair));
        }
        else {
          self->pid_map_[iter.first].erase(msg.addr);
        }
      }
      
      if (fd > 0) {
        close(fd);
      }
    }
    self->mut.unlock();
  }
}
