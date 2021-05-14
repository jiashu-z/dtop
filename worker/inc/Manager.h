#ifndef DTOP_RPC_MANAGER_H
#define DTOP_RPC_MANAGER_H

#include <vector>
#include <memory>
#include "BaseWorker.h"
#include "ManagerMeta.h"

namespace dtop {
namespace worker {

	class Manager {
	private:
		std::vector<BaseWorker> workers;
	public:

	};
}
}

#endif //DTOP_RPC_MANAGER_H
