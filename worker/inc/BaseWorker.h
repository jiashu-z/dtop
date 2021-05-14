#ifndef DEMO_GRPC_BASEWORKER_H
#define DEMO_GRPC_BASEWORKER_H

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <sys/time.h>
#include "WorkerConfig.h"
#include "WorkerCtrlBlock.h"
#include "ProfileQuery.h"
#include "message.grpc.pb.h"
#include "WorkerType.h"

namespace dtop {
namespace worker {

	class BaseWorker {
	protected:
		const WorkerConfig& config;

		explicit BaseWorker(WorkerType type, std::string worker_name, const WorkerConfig& config);
		static long long compute_timestamp();

	public:
		const WorkerType worker_type;
		const std::string worker_name;

		virtual bool setup() = 0;
		virtual bool act(ProfileQuery& query, FetchReplyMessage& reply) = 0;
		virtual bool shutdown() = 0;

		std::string to_string() const;
	};

}
}

#endif //DEMO_GRPC_BASEWORKER_H
