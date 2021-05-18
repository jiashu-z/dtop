#include "ConcreteAPIService.h"

#include <grpcpp/impl/codegen/status.h>

#include "Server.h"

::grpc::Status dtop::server::ConcreteAPIService::GetServerStatus(
    ::grpc::ServerContext *context, const ::google::protobuf::Empty *request,
    ::ServerStatusArrMessage *response) {
  return ::grpc::Status::OK;
}

::grpc::Status dtop::server::ConcreteAPIService::GetServerAddresses(
    ::grpc::ServerContext *context, const ::google::protobuf::Empty *request,
    ::StringArrayMessage *response) {
  // for (auto iter : this->server->)
  return ::grpc::Status::OK;
}

::grpc::Status dtop::server::ConcreteAPIService::GetStats(
    ::grpc::ServerContext *context, const ::FetchRequestMessage *request,
    ::FetchReplyArrayMessage *response) {
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  this->server->client.get_cluster_stats(response, request);
  std::cout << __FILE__ << ": " << __LINE__ << std::endl;
  return ::grpc::Status::OK;
}

inline void set_all_int64_to_value(MemUsageMessage& message, const int64_t value) {
	int field_count = MemUsageMessage::GetDescriptor()->field_count();
	for (int i = 0; i < field_count; ++i) {
		MemUsageMessage::GetReflection()->SetInt64(&message, MemUsageMessage::GetDescriptor()->field(i), value);
	}
}

inline void sum_mem_usage(MemUsageMessage& aggregated, const MemUsageMessage& single) {
	int field_count = MemUsageMessage::GetDescriptor()->field_count();
	for (int i = 0; i < field_count; ++i) {
		int64_t old = MemUsageMessage::GetReflection()->GetInt64(aggregated, MemUsageMessage::GetDescriptor()->field(i));
		int64_t inc = MemUsageMessage::GetReflection()->GetInt64(single, MemUsageMessage::GetDescriptor()->field(i));
		MemUsageMessage::GetReflection()->SetInt64(&aggregated, MemUsageMessage::GetDescriptor()->field(i), old + inc);
	}
}

::grpc::Status dtop::server::ConcreteAPIService::GetAggregatedVirtualMemInfo(::grpc::ServerContext *context,
                                                                             const ::FetchRequestMessage *request,
                                                                             ::FetchReplyArrayMessage *response) {
	auto *local_response = new ::FetchReplyArrayMessage();
	this->server->client.get_cluster_stats(local_response, request);
	int size = local_response->fetch_reply_size();
	MemUsageMessage aggregated_mem_usage;
	set_all_int64_to_value(aggregated_mem_usage, 0);
	for (int i = 0; i < size; ++i) {
		auto mem_usage_from_one_server = local_response->fetch_reply(i).mem_usage_message();
		sum_mem_usage(aggregated_mem_usage, mem_usage_from_one_server);
	}
	auto fetch_reply = response->add_fetch_reply();
	fetch_reply->mutable_mem_usage_message()->CopyFrom(aggregated_mem_usage);
	return ::grpc::Status::OK;
}

dtop::server::ConcreteAPIService::~ConcreteAPIService() = default;