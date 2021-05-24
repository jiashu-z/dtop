#ifndef DTOP_RPC_MEMORYMONITORWORKER_H
#define DTOP_RPC_MEMORYMONITORWORKER_H

#include <string>
#include "BaseWorker.h"

namespace dtop {
namespace worker {

class MemoryMonitorWorker : public BaseWorker {
private:
    void init_futures() override;
    bool setup_config(WorkerConfig& worker_config) override;

    bool handle_start() override;
    bool handle_process(ProfileQuery* query, FetchReplyMessage* reply) override;
    bool handle_pause() override;
    bool handle_stop() override;
public:
    MemoryMonitorWorker();
};

}  // namespace worker
}  // namespace dtop


#endif //DTOP_RPC_MEMORYMONITORWORKER_H
