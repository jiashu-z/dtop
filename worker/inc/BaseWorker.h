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

namespace dtop {
namespace worker {

	class BaseWorker {
	protected:
		explicit BaseWorker(std::string worker_name, const WorkerConfig& config);
		static long long compute_timestamp();
		const WorkerConfig& config;

	public:
		const std::string worker_name;
		virtual bool create() = 0;
		virtual bool setup() = 0;
		virtual bool act(ProfileQuery& query, FetchReplyMessage& reply) = 0;
		virtual bool shutdown() = 0;

		std::string to_string() const;
	};

	typedef std::shared_ptr<BaseWorker> (*WorkerCreator)();

}
}

#endif //DEMO_GRPC_BASEWORKER_H
