#ifndef DTOP_RPC_MANAGERMETA_H
#define DTOP_RPC_MANAGERMETA_H

#include "BaseWorker.h"

namespace dtop {

namespace metric {
	enum MetricType {
		MEM_USAGE,
	};
}

namespace worker {

	enum WorkerType {
		MEM_USAGE_WORKER,
	};

	class ManagerMeta final {
	private:
		ManagerMeta();
		static ManagerMeta create_meta();

//		typedef std::unordered_map<WorkerType, >
		/**
		 * @brief Map worker type to worker obj.
		 *        Developer need to register worker in init function.
		 */
		std::unordered_map<WorkerType, WorkerCreator> registered_worker_map;
		std::unordered_map<WorkerType, WorkerCreator> init_registered_worker_map();

		std::unordered_map<WorkerType, std::vector<dtop::metric::MetricType>> metrics_map;
		std::unordered_map<WorkerType, std::vector<dtop::metric::MetricType>>


	public:
		static ManagerMeta get_meta();

		std::shared_ptr<BaseWorker> create_worker(WorkerType worker_type);
		std::string get_worker_name(WorkerType worker_type);
	};

}
}


#endif //DTOP_RPC_MANAGERMETA_H
