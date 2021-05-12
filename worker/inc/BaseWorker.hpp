#ifndef DEMO_GRPC_BASEWORKER_HPP
#define DEMO_GRPC_BASEWORKER_HPP

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <sys/time.h>
#include "WorkerConfig.hpp"

namespace dtop {
namespace worker {

	class BaseWorker {
	protected:
		explicit BaseWorker(std::string worker_name, const WorkerConfig& config);
		static long long compute_timestamp();
		const WorkerConfig& config;

	public:
		const std::string worker_name;
		virtual bool setup() = 0;
		virtual bool act(const QueryParam& params, EchoResponse& response) = 0;
		virtual bool shutdown() = 0;

		std::string to_string() const;
	};

}
}

dtop::worker::BaseWorker::BaseWorker(std::string worker_name,
											 const WorkerConfig& config) :
		worker_name(std::move(worker_name)),
		config(config) {}

std::string dtop::worker::BaseWorker::to_string() const {
	return this->worker_name;
}

long long dtop::worker::BaseWorker::compute_timestamp() {
	timeval tv{};
	gettimeofday(&tv, nullptr);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#endif //DEMO_GRPC_BASEWORKER_HPP
