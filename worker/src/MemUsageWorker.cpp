#include "MemUsageWorker.h"

long long dtop::worker::MemUsageWorker::compute_max_mem() {
	return 0;
}

bool dtop::worker::MemUsageWorker::setup() {
	max_mem = compute_max_mem();
	return true;
}

bool dtop::worker::MemUsageWorker::act(dtop::worker::ProfileQuery &query,
																			 FetchReplyMessage &reply) {
	return false;
}

bool dtop::worker::MemUsageWorker::shutdown() {
	return true;
}

long long dtop::worker::MemUsageWorker::compute_used_mem() {
	if (compute_timestamp() - timestamp >= config.cache_time) {
		timestamp = compute_timestamp();
		used_mem = 0;
	}
	return used_mem;
}


