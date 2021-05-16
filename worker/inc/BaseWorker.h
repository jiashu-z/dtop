#ifndef DEMO_GRPC_BASEWORKER_H
#define DEMO_GRPC_BASEWORKER_H

#include <sys/time.h>

#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "ProfileQuery.h"
#include "WorkerConfig.h"
#include "message.grpc.pb.h"
#include "Future.h"
#include "WorkerStatus.h"

namespace dtop {
namespace worker {

class BaseWorker {
 protected:
  /**
   * @brief All futures that this worker provides.
   *        Modification is not allowed except initialization function.
   */
	std::vector<const Future*> futures;

	/**
	 * @brief Current lifecycle status of the worker.
	 */
	WorkerStatus status;

  explicit BaseWorker(std::string worker_name);

	/**
	 * @brief Set futures provided by this worker.
	 */
	virtual void init_futures() = 0;

	/**
	 * @brief Setup worker by config.
	 *
	 * @param worker_config
	 * @return True if no error occurs.
	 */
	virtual bool setup_config(WorkerConfig& worker_config) = 0;

	/**
	 * @brief Start the worker.
	 *
	 * @return True if it starts successfully.
	 */
	virtual bool handle_start() = 0;

	/**
	 * @brief Process the profiling query
	 *
	 * @param query
	 * @param reply
	 * @return True if no error occurs.
	 */
	virtual bool handle_process(ProfileQuery* query, FetchReplyMessage* reply) = 0;

	/**
	 * @brief Pause the worker.
	 *
	 * @return True if no error occurs.
	 */
	virtual bool handle_pause() = 0;

	/**
	 * @brief Stop the worker.
	 *
	 * @return True if it stops successfully.
	 */
	virtual bool handle_stop() = 0;

 public:
	virtual ~BaseWorker();

  const std::string worker_name;

  /**
   * @brief Setup futures and configs. Switch from NEW to READY.
   *
   * @param worker_config
   * @return True if no error occurs.
   */
  bool setup(WorkerConfig& worker_config);

  /**
   * @brief Start this worker. Switch from READY to RUNNING.
   *
   * @return True if no error occurs.
   */
  bool start();

  /**
   * @brief Process the profiling query.
   *
   * @param query
   * @param reply
   * @return True if no error occurs.
   */
  bool process(ProfileQuery* query, FetchReplyMessage* reply);

  /**
   * @brief Pause this worker. Switch from RUNNING to READY.
   *
   * @return True if no error occurs.
   */
  bool pause();

  /**
   * @brief Stop this worker. Switch from READY/RUNNING to STOPPED
   *
   * @return True if no error occurs.
   */
  bool stop();

	const std::vector<const Future*>& get_futures() const;
	WorkerStatus get_status() const;
  std::string to_string() const;

	static std::string get_status_str(WorkerStatus status);
};

}  // namespace worker
}  // namespace dtop

#endif  // DEMO_GRPC_BASEWORKER_H
