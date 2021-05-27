#include "MemLeakWorker.h"

#include <unistd.h>

#include <boost/algorithm/string.hpp>
#include <cassert>
#include <memory>
#include <string>
#include <thread>

#include "pslib.h"

#define add_and_rm_delimiter "|"

std::map<int, std::map<int64_t, dtop::worker::MemLeakWorker::MemTraceEntry>>
    dtop::worker::MemLeakWorker::mem_map = {};

dtop::worker::MemLeakWorker::MemLeakWorker()
    : BaseWorker("Memory leak worker"), should_break(true) {}

void dtop::worker::MemLeakWorker::init_futures() {
  futures.push_back(new Future("REPORT_MEM_LEAK", "Report the memory leak"));
  futures.push_back(
      new Future("UPDATE_TRACE_PROC", "Modify the processes to trace"));
  futures.push_back(
      new Future("REPORT_TRACE_PROC", "Report the processes to trace"));
}

bool dtop::worker::MemLeakWorker::setup_config(
    dtop::worker::WorkerConfig& worker_config) {
  return true;
}

bool dtop::worker::MemLeakWorker::handle_start() {
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  this->should_break = false;
  this->map_thread_ptr = std::make_unique<std::thread>(update_map, this);
  this->map_thread_ptr->detach();
  return true;
}

bool dtop::worker::MemLeakWorker::handle_process(
    dtop::worker::ProfileQuery* query, FetchReplyMessage* reply) {
  std::cout << query->to_string() << std::endl;

  const auto& it1 = query->req_map.find("UPDATE_TRACE_PROC");
  if (it1 != query->req_map.end()) {
    std::vector<std::string> add_and_rm;
    boost::split(add_and_rm, it1->second,
                 boost::is_any_of(add_and_rm_delimiter));
    assert(add_and_rm.size() == 2);

    std::list<std::string> add_tokens;
    std::list<std::string> rm_tokens;
    boost::split(add_tokens, add_and_rm[0], boost::is_any_of(" "));
    boost::split(rm_tokens, add_and_rm[1], boost::is_any_of(" "));
    std::list<int64_t> to_add;
    std::list<int64_t> to_rm;
    for (const auto& iter : add_tokens) {
      int64_t pid = std::stoll(iter);
      if (0 == pid) {
        continue;
      }
      to_add.push_back(pid);
    }
    for (const auto& iter : rm_tokens) {
      int64_t pid = std::stoll(iter);
      if (0 == pid) {
        continue;
      }
      to_rm.push_back(pid);
    }
    update_pids(to_add, to_rm);
    reply->add_infos("process update");
  }
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;

  const auto& it2 = query->req_map.find("REPORT_MEM_LEAK");
  if (it2 != query->req_map.end()) {
    std::cout << "REPORT_MEM_LEAK REPORT_MEM_LEAK" << std::endl;
    auto leaks = scan_and_find_leaks();
    auto mem_leak_msg = reply->mutable_mem_leak_message();
    auto malloc_entries = mem_leak_msg->mutable_malloc_entry_arr();
    for (auto& entry : leaks) {
      auto* entry_ptr = malloc_entries->Add();
      std::cout << entry.pid << std::endl;
      entry_ptr->set_time(entry.time);
      entry_ptr->set_pid(entry.pid);
      entry_ptr->set_size(entry.size);
      entry_ptr->set_addr(entry.addr);
      entry_ptr->set_caller(entry.caller);
    }
  } else {
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    for (auto iter : query->req_map) {
      std::cout << iter.first << std::endl;
    }
  }
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;

  const auto& it3 = query->req_map.find("REPORT_TRACE_PROC");
  if (it3 != query->req_map.end()) {
    std::cout << "REPORT_TRACE_PROC" << std::endl;
    std::string pids_str;
    for (const auto& pid_iter : this->pid_map_) {
      pids_str += std::to_string(pid_iter.first) + "";
    }
    reply->add_infos(pids_str);
  }

  return true;
}

bool dtop::worker::MemLeakWorker::handle_pause() {
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  this->should_break = true;
  // std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  // this->map_thread_ptr->join();
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  this->map_thread_ptr = nullptr;
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
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

void dtop::worker::MemLeakWorker::update_map(
    dtop::worker::MemLeakWorker* self) {
  malloc_free_msg_t msg;
  void* buf = (void*)&msg;
  // Keeps the thread running until pause or stop.
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  while (!self->should_break) {
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    sleep(1);
    // Iterate the map of all pids.
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    self->mut.lock();
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    for (auto iter : self->pid_map_) {
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;
      if (self->should_break) {
        std::cout << __FILE__ << ": " << __LINE__ << std::endl;
        break;
      }
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;
      auto& pid = iter.first;
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;
      const std::string fifo_path = "/tmp/fifo" + std::to_string(pid);
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;
      int fd = open(fifo_path.c_str(), O_RDONLY | O_NONBLOCK);
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;
      if (fd == -1) {
        std::cout << __FILE__ << ": " << __LINE__ << std::endl;
        continue;
      }
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;

      // Read until FIFO is empty or error, or until pause or stop.
      while (!self->should_break) {
        std::cout << __FILE__ << ": " << __LINE__ << std::endl;
        size_t ret = read(fd, buf, malloc_msg_size);
        std::cout << __FILE__ << ": " << __LINE__ << std::endl;
        if (ret == 0 || ret == -1) {
          std::cout << __FILE__ << ": " << __LINE__ << std::endl;
          break;
        }
        std::cout << __FILE__ << ": " << __LINE__ << std::endl;
        assert(msg.mode == mode_malloc || msg.mode == mode_free);
        std::cout << __FILE__ << ": " << __LINE__ << std::endl;
        if (msg.mode == mode_malloc) {
          std::cout << __FILE__ << ": " << __LINE__ << std::endl;
          msg_ts_pair_t msg_ts_pair =
              std::pair<malloc_free_msg_t, int64_t>(msg, std::time(nullptr));
          std::cout << __FILE__ << ": " << __LINE__ << std::endl;
          assert(iter.first == msg.pid);
          std::cout << __FILE__ << ": " << __LINE__ << std::endl;
          self->pid_map_[iter.first].insert(
              std::pair<int64_t, msg_ts_pair_t>(msg.addr, msg_ts_pair));
          std::cout << __FILE__ << ": " << __LINE__ << std::endl;
        } else {
          std::cout << __FILE__ << ": " << __LINE__ << std::endl;
          self->pid_map_[iter.first].erase(msg.addr);
          std::cout << __FILE__ << ": " << __LINE__ << std::endl;
        }
      }
      std::cout << __FILE__ << ": " << __LINE__ << std::endl;

      if (fd > 0) {
        std::cout << __FILE__ << ": " << __LINE__ << std::endl;
        close(fd);
        std::cout << __FILE__ << ": " << __LINE__ << std::endl;
      }
    }
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;

    self->mut.unlock();
    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  }
}

void dtop::worker::MemLeakWorker::update_pids(const std::list<int64_t>& to_add,
                                              const std::list<int64_t>& to_rm) {
  this->add_pids(to_add);
  this->rm_pids(to_rm);
}

void dtop::worker::MemLeakWorker::add_pids(const std::list<int64_t>& to_add) {
  this->mut.lock();
  for (const auto& iter : to_add) {
    if (pid_map_.find(iter) == pid_map_.end()) {
      addr_map_t m;
      pid_map_.insert(std::pair<int64_t, addr_map_t>(iter, m));
    }
  }
  this->mut.unlock();
}

void dtop::worker::MemLeakWorker::rm_pids(const std::list<int64_t>& to_rm) {
  this->mut.lock();
  for (const auto& iter : to_rm) {
    if (pid_map_.find(iter) != pid_map_.end()) {
      pid_map_.erase(iter);
    }
  }
  this->mut.unlock();
}

std::list<dtop::worker::MemLeakWorker::malloc_entry_t>
dtop::worker::MemLeakWorker::scan_and_find_leaks() const {
  std::list<dtop::worker::MemLeakWorker::malloc_entry_t> leaks;
  int64_t time = std::time(nullptr);
  for (const auto& pid_iter : pid_map_) {
    for (const auto& addr_iter : pid_iter.second) {
      const auto& p = addr_iter.second;
      if (time - p.second > leak_threshold) {
        dtop::worker::MemLeakWorker::malloc_entry_t entry{
            p.second, p.first.pid, p.first.size, p.first.addr, p.first.caller};
        leaks.push_back(entry);
      }
    }
  }
  return leaks;
}
