#include "Manager.h"

#include <iostream>

#define PRINT_INFO(__MSG__) (std::cout << (__MSG__) << std::endl);

#define PRINT_ERROR(__MSG__, __EXCEPTION__)              \
  std::cout << "Error occur when " << (__MSG__) << " : " \
            << (__EXCEPTION__).what() << std::endl;

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

bool dtop::worker::Manager::process_query(const FetchRequestMessage* request,
                                          FetchReplyMessage* reply) {
  bool success;

  ProfileQuery query;
  if (!query.decode(request)) {
    PRINT_INFO("Request format error. Result may be incorrect.")
  }

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

google::protobuf::RepeatedPtrField<WorkerStatusMessage>*
dtop::worker::Manager::get_worker_status(bool with_futures,
                                         bool with_future_desc) {
  auto rpf_ptr = new google::protobuf::RepeatedPtrField<WorkerStatusMessage>();
  for (auto& worker_ptr : this->manager_meta->get_workers()) {
    auto* wsm_ptr = rpf_ptr->Add();
    wsm_ptr->set_worker_name(worker_ptr->worker_name);
    wsm_ptr->set_status(BaseWorker::get_status_str(worker_ptr->get_status()));
    if (with_futures || with_future_desc) {
      for (auto& future : worker_ptr->get_futures()) {
        auto* future_ptr = wsm_ptr->add_future();
        future_ptr->set_label(future->label);
        if (with_future_desc) {
          future_ptr->set_desc(future->desc);
        }
      }
    }
  }
  return rpf_ptr;
}
