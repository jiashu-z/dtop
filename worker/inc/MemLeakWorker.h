#ifndef DEMO_GRPC_MEMLEAKWORKER_H
#define DEMO_GRPC_MEMLEAKWORKER_H

#include <string>
#include <map>

#include "BaseWorker.h"

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
