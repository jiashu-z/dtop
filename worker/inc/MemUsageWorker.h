#ifndef DEMO_GRPC_MEMUSAGEWORKER_H
#define DEMO_GRPC_MEMUSAGEWORKER_H

#include <string>

#include "BaseWorker.h"

namespace dtop {
namespace worker {

class MemUsageWorker : public BaseWorker {
 private:
  long long max_mem;
  long long used_mem;
  long long timestamp;

  static long long compute_max_mem();
  long long compute_used_mem();

 public:
  explicit MemUsageWorker(WorkerType type, std::string worker_name,
                          const WorkerConfig& config);
  bool setup() override;
  bool act(ProfileQuery& query, FetchReplyMessage& reply) override;
  bool shutdown() override;
};

}  // namespace worker
}  // namespace dtop

#endif  // DEMO_GRPC_MEMUSAGEWORKER_H
