#include "MemoryMonitorWorker.h"

#include "pslib.h"

dtop::worker::MemoryMonitorWorker::MemoryMonitorWorker()
        : BaseWorker("Memory monitor worker") {}

void dtop::worker::MemoryMonitorWorker::init_futures() {
    futures.push_back(new Future("MEM_USAGE", "The overall memory usage"));
    futures.push_back(
            new Future("MEM_PER_PROC", "The detail memory info of processes"));
}

bool dtop::worker::MemoryMonitorWorker::setup_config(
        dtop::worker::WorkerConfig& worker_config) {
    return true;
}

bool dtop::worker::MemoryMonitorWorker::handle_start() { return true; }

bool dtop::worker::MemoryMonitorWorker::handle_process(
        dtop::worker::ProfileQuery* query, FetchReplyMessage* reply) {
//    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//    std::cout << query->to_string() << std::endl;
//    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//
//    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
//    std::cout << __FILE__ << ": " << __LINE__ << std::endl;
    std::vector<int> process_ids;
    std::vector<Process *> process_info;
    get_processes_ids(process_ids);
    get_processes_info(process_info,process_ids);
    auto mut = reply->mutable_memory_monitor_message();
    auto process_arr = mut->mutable_process_arr();
    for (auto i = process_info.begin(); i != process_info.end(); ++i) {
        auto p_ptr = process_arr->Add();
        p_ptr->set_pid((*i)->pid);
        p_ptr->set_ppid((*i)->ppid);
        p_ptr->set_name((*i)->name);
        p_ptr->set_cmdline((*i)->cmdline);
        p_ptr->set_create_time((*i)->create_time);
        p_ptr->set_uid((*i)->uid);
        p_ptr->set_uid((*i)->uid);
        p_ptr->set_username((*i)->username);
        for (auto j = (*i)->threads->begin(); j < (*i)->threads->end(); ++j) {
            auto t_ptr = p_ptr->mutable_threads()->Add();
            t_ptr->set_tid((*j).thread_id);
            t_ptr->set_rss((*j).memoryInfo.rss);
            t_ptr->set_vms((*j).memoryInfo.vms);
            t_ptr->set_shared((*j).memoryInfo.shared);
            t_ptr->set_text((*j).memoryInfo.text);
            t_ptr->set_lib((*j).memoryInfo.lib);
            t_ptr->set_data((*j).memoryInfo.data);
            t_ptr->set_dirty((*j).memoryInfo.dirty);
        }
        free_process(*i);
    }
    return true;
}

bool dtop::worker::MemoryMonitorWorker::handle_pause() { return true; }

bool dtop::worker::MemoryMonitorWorker::handle_stop() { return true; }
