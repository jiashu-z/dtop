#ifndef DTOP_RPC_WORKERSTATUS_H
#define DTOP_RPC_WORKERSTATUS_H

namespace dtop {
namespace worker {

	enum WorkerStatus {
			NEW, READY, RUNNING, SHUTDOWN
	};
}
}

#endif //DTOP_RPC_WORKERSTATUS_H
