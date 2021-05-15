#include "Manager.h"

#include <iostream>

#define PRINT_INFO(__MSG__) (std::cout << (__MSG__) << std::endl);

#define PRINT_ERROR(__MSG__, __EXCEPTION__) \
std::cout << "Error occur when " << (__MSG__) \
					<< " : " << (__EXCEPTION__).what() << std::endl;


dtop::worker::Manager::Manager() {
	this->manager_meta = std::make_unique<ManagerMeta>();
}

bool dtop::worker::Manager::initialize(dtop::worker::WorkerConfig& config) {
	bool success;

	success = this->manager_meta->initialize();
	if (!success) {
		PRINT_INFO("Init manager meta failed")
		return false;
	}

	for (BaseWorker* worker_ptr : manager_meta->get_workers()) {
		try {
			worker_ptr->setup(config);
		} catch (std::exception& e) {
			PRINT_ERROR("setup config in " + worker_ptr->worker_name, e)
			success = false;
		}
	}

	return success;
}

bool dtop::worker::Manager::handle_auto_start() {
	bool success;
	// auto start all worker for now
	for (BaseWorker* worker_ptr : manager_meta->get_workers()) {
		try {
			if (!worker_ptr->start()) {
				success = false;
			}
		} catch (std::exception& e) {
			PRINT_ERROR("setup config in " + worker_ptr->worker_name, e)
			success = false;
		}
	}
	return success;
}

bool dtop::worker::Manager::process_query(const FetchRequestMessage* request, FetchReplyMessage* reply) {
	bool success;

	ProfileQuery query;
	query.decode(request);

	for (BaseWorker* worker_ptr : manager_meta->get_workers()) {
		try {
			if (!worker_ptr->process(&query, reply)) {
				success = false;
			}
		} catch (std::exception& e) {
			PRINT_ERROR("setup config in " + worker_ptr->worker_name, e)
			success = false;
		}
	}
	return success;
}
