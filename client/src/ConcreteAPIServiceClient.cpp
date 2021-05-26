#include "ConcreteAPIServiceClient.h"

#include "Client.h"

void dtop::client::ConcreteAPIServiceClient::get_status_arr() {
  grpc::ClientContext context;
  ::StringArrayMessage request;
  ::ServerStatusArrayMessage response;
  ::grpc::Status status =
      this->stub->GetClusterStatus(&context, request, &response);
}

void dtop::client::ConcreteAPIServiceClient::get_stats() {
  grpc::ClientContext context;
  ::FetchRequestArrayMessage request;
  ::FetchReplyArrayMessage response;
  this->stub->GetClusterMetric(&context, request, &response);
}