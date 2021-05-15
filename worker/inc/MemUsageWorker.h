#ifndef DEMO_GRPC_MEMUSAGEWORKER_H
#define DEMO_GRPC_MEMUSAGEWORKER_H

#include <string>

#include "BaseWorker.h"

namespace dtop {
namespace worker {

class MemUsageWorker : public BaseWorker {
 private:
  void init_futures() override;
  bool setup_config(WorkerConfig& worker_config) override;

	bool handle_start() override;
	bool handle_process(ProfileQuery* query, FetchReplyMessage* reply) override;
	bool handle_pause() override;
	bool handle_stop() override;

 public:
	MemUsageWorker();
};

}  // namespace worker
}  // namespace dtop

#endif  // DEMO_GRPC_MEMUSAGEWORKER_H
