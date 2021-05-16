#include "BaseWorker.h"

#include <utility>

#define PRINT_ERROR(__WHEN__, __EXCEPTION__) \
std::cout << "Error occur when " << (__WHEN__) << " in " << this->worker_name \
					<< " : " << (__EXCEPTION__).what() << std::endl;

dtop::worker::BaseWorker::BaseWorker(std::string worker_name) :
				worker_name(std::move(worker_name)){
	this->status = WorkerStatus::NEW;
}

dtop::worker::BaseWorker::~BaseWorker() {
	for (auto future_ptr : this->futures) {
		delete future_ptr;
	}
}

bool dtop::worker::BaseWorker::setup(dtop::worker::WorkerConfig &worker_config) {
	if (this->status != NEW) {
		return false;
	}
	this->init_futures();
	try {
		if (this->setup_config(worker_config)) {
			this->status = READY;
		}
	} catch (std::exception& e) {
		PRINT_ERROR("set config", e)
		return false;
	}
	return true;
}

bool dtop::worker::BaseWorker::start() {
	if (this->status != READY) {
		return false;
	}
	try {
		if (this->handle_start()) {
			this->status = RUNNING;
		}
	} catch (std::exception& e) {
		PRINT_ERROR("start worker", e)
		return false;
	}
	return true;
}

bool dtop::worker::BaseWorker::process(dtop::worker::ProfileQuery* query,
                                       FetchReplyMessage* reply) {
	if (this->status != RUNNING) {
		return false;
	}
	try {
		this->handle_process(query, reply);
	} catch (std::exception& e) {
		PRINT_ERROR("process query", e)
		return false;
	}
	return true;
}

bool dtop::worker::BaseWorker::pause() {
	if (this->status != RUNNING) {
		return false;
	}
	try {
		if (this->handle_pause()) {
			this->status = READY;
		}
	} catch (std::exception& e) {
		PRINT_ERROR("pause worker", e)
		return false;
	}
	return true;
}

bool dtop::worker::BaseWorker::stop() {
	if (this->status != READY && this->status != RUNNING) {
		return false;
	}
	try {
		if (this->handle_stop()) {
			this->status = SHUTDOWN;
		}
	} catch (std::exception& e) {
		PRINT_ERROR("stop worker", e)
		return false;
	}
	return true;
}

const std::vector<const dtop::worker::Future *> &dtop::worker::BaseWorker::get_futures() const {
	return this->futures;
}

dtop::worker::WorkerStatus dtop::worker::BaseWorker::get_status() const {
	return this->status;
}

std::string dtop::worker::BaseWorker::to_string() const {
	return this->worker_name;
}

std::string dtop::worker::BaseWorker::get_status_str(dtop::worker::WorkerStatus status)  {
	switch (status) {
		case NEW: return "NEW";
		case READY: return "READY";
		case RUNNING: return "RUNNING";
		case SHUTDOWN: return "SHUTDOWN";
	}
	return "UNKNOWN";
}
