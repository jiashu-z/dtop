#ifndef DEMO_GRPC_MEMLEAKWORKER_H
#define DEMO_GRPC_MEMLEAKWORKER_H

#include <string>
#include <map>

#include "BaseWorker.h"
#include <mutex>
#include <map>
#include <thread>
#include <memory>
#include <fcntl.h>
#include <cassert>
#include <atomic>
#include <list>

#define malloc_msg_size sizeof(malloc_free_msg_t)
#define mode_malloc 0
#define mode_free 1
#define leak_threshold 5

namespace dtop {
namespace worker {

class MemLeakWorker : public BaseWorker {
 private:
  class MemTraceEntry {
  private:
  public:
    int64_t addr;
    int64_t time;
    int64_t size;
    MemTraceEntry() = default;
    MemTraceEntry(int64_t addr, int64_t time, int64_t size) : addr(addr), time(time), size(size) {}
  };

  void init_futures() override;
  bool setup_config(WorkerConfig& worker_config) override;

  bool handle_start() override;
  bool handle_process(ProfileQuery* query, FetchReplyMessage* reply) override;
  bool handle_pause() override;
  bool handle_stop() override;

  static std::map<int, std::map<int64_t, MemTraceEntry>> mem_map;

  struct malloc_free_msg_t {
    int64_t mode;
    int64_t pid;
    int64_t size;
    int64_t addr;
    int64_t caller;
  };

  std::mutex mut;
  
  typedef std::pair<struct malloc_free_msg_t, int64_t> msg_ts_pair_t;
  typedef std::map<int64_t, msg_ts_pair_t> addr_map_t;
  typedef std::map<int64_t, addr_map_t> pid_map_t;

  pid_map_t pid_map_;

  std::unique_ptr<std::thread> map_thread_ptr;

  std::atomic<bool> should_break{};

  static void update_map(MemLeakWorker *self);

  /**
   * @brief Please to not add and remove the same pid!
   * 
   * @param to_add 
   * @param to_rm
   */
  void update_pids(const std::list<int64_t>& to_add, const std::list<int64_t>& to_rm);

  void add_pids(const std::list<int64_t>& to_add);

  void rm_pids(const std::list<int64_t>& to_rm);

  typedef struct malloc_entry_t {
    int64_t time;
    int64_t pid;
    int64_t size;
    int64_t addr;
    int64_t caller;
  } malloc_entry_t;

  std::list<malloc_entry_t> scan_and_find_leaks() const;

 public:

  static void record_malloc(int pid, int64_t addr, int64_t size) {
    if (mem_map.find(pid) == mem_map.end()) {
      std::map<int64_t, MemTraceEntry> map;
      mem_map.insert(std::pair<int, std::map<int64_t, MemTraceEntry>>(pid, map));
    }
    int64_t time = std::time(nullptr);
    MemTraceEntry malloc_entry(addr, time, size);
    mem_map[pid].insert(std::pair<int64_t, MemTraceEntry>(addr, malloc_entry));
  };

  static void record_free(int pid, int64_t addr) {
    if (mem_map.find(pid) == mem_map.end()) {
      return;
    }
    auto &proc_map = mem_map[pid];
    proc_map.erase(addr);
  }

  MemLeakWorker();
};

}  // namespace worker
}  // namespace dtop

#endif  // DEMO_GRPC_MEMLEAKWORKER_H
