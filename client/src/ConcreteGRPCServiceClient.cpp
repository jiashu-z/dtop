#include "ConcreteGRPCServiceClient.h"

#include "google/protobuf/empty.pb.h"
#include "grpcpp/impl/codegen/client_context.h"
#include "message.pb.h"

std::string dtop::client::ConcreteGRPCServiceClient::get_addr() {
  grpc::ClientContext context;
  auto empty = ::google::protobuf::Empty();
  ::StringMessage response;
  grpc::Status status = this->stub->GetIP(&context, empty, &response);
  return response.val();
}