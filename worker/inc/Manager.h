#ifndef DTOP_RPC_MANAGER_H
#define DTOP_RPC_MANAGER_H

#include <memory>
#include <vector>

#include "BaseWorker.h"
#include "ManagerMeta.h"
#include "api.grpc.pb.h"
#include "WorkerCmdType.h"

namespace dtop {
namespace worker {

class Manager {
 private:
  std::unique_ptr<ManagerMeta> manager_meta;

 public:
  Manager();

  /**
   * @brief Create registered workers. Set worker config.
   *
   * @return True if no error occurs.
   */
  bool initialize(WorkerConfig& config);

  /**
   * @brief If auto execution config of a worker is set, start this worker.
   *
   * @return True if no error occurs.
   */
  bool handle_auto_start();

  /**
   * @brief Handle query using workers in manager meta.
   *
   * @param request
   * @param reply
   * @return True if no error occurs.
   */
  bool process_query(const FetchRequestMessage* request,
                     FetchReplyMessage* reply);

  /**
   * @brief Get the worker status maintained by current manager.
   *
   * @param with_futures Require name of supported futures
   * @param with_future_desc Require name and description of supported futures
   *
   * @return The repeated pointer field rof worker status message.
   */
  google::protobuf::RepeatedPtrField<WorkerStatusMessage>* get_worker_status(
      bool with_futures = false, bool with_future_desc = false);

  bool switch_worker_status(std::string& worker_name, WorkerCmdType cmd_type);
};

}  // namespace worker
}  // namespace dtop

#endif  // DTOP_RPC_MANAGER_H
