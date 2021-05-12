#ifndef DEMO_GRPC_MEMUSAGEWORKER_H
#define DEMO_GRPC_MEMUSAGEWORKER_H

#include <string>
#include "BaseWorker.hpp"

namespace dtop {
namespace worker {

	class MemUsageWorker : public BaseWorker {
	private:
		long long max_mem;
		long long used_mem;
		long long timestamp;

		static long long compute_max_mem();

	public:
		bool setup() override;
		bool shutdown() override;

		long long get_max_mem() const;
		long long get_used_mem();
	};

}
}


#endif //DEMO_GRPC_MEMUSAGEWORKER_H
