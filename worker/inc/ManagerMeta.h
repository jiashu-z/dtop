#ifndef DTOP_RPC_MANAGERMETA_H
#define DTOP_RPC_MANAGERMETA_H

#include "BaseWorker.h"
#include "WorkerType.h"
#include "MetricType.h"

namespace dtop {
namespace worker {

	class ManagerMeta final {
	private:
		typedef std::unordered_map<WorkerType, BaseWorker*> WorkerMap;

		WorkerConfig& worker_config;

			/**
				 * @brief Map worker type to worker obj.
				 *        Developer need to register worker in init function.
				 */
		WorkerMap registered_worker_map;
		void init_registered_worker_map();

	public:
		std::shared_ptr<BaseWorker> get_worker(WorkerType type);

			~ManagerMeta();

			explicit ManagerMeta(WorkerConfig& config);
	};

}
}


#endif //DTOP_RPC_MANAGERMETA_H
