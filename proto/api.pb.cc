// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: api.proto

#include "api.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
static constexpr ::PROTOBUF_NAMESPACE_ID::Metadata* file_level_metadata_api_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_api_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_api_2eproto = nullptr;
const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_api_2eproto::offsets[1] = {};
static constexpr ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema* schemas = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::Message* const* file_default_instances = nullptr;

const char descriptor_table_protodef_api_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\tapi.proto\032\rmessage.proto\032\033google/proto"
  "buf/empty.proto2\335\002\n\nAPIService\022B\n\017GetSer"
  "verStatus\022\026.google.protobuf.Empty\032\027.Serv"
  "erStatusArrMessage\022A\n\022GetServerAddresses"
  "\022\026.google.protobuf.Empty\032\023.StringArrayMe"
  "ssage\022\?\n\022ExecClusterCommand\022\024.CommandArr"
  "ayMessage\032\023.StringArrayMessage\0229\n\010GetSta"
  "ts\022\024.FetchRequestMessage\032\027.FetchReplyArr"
  "ayMessage\022L\n\033GetAggregatedVirtualMemInfo"
  "\022\024.FetchRequestMessage\032\027.FetchReplyArray"
  "MessageB\031\n\027grp.dtop.dtopjava.protob\006prot"
  "o3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_api_2eproto_deps[2] = {
  &::descriptor_table_google_2fprotobuf_2fempty_2eproto,
  &::descriptor_table_message_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_api_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_api_2eproto = {
  false, false, 442, descriptor_table_protodef_api_2eproto, "api.proto", 
  &descriptor_table_api_2eproto_once, descriptor_table_api_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_api_2eproto::offsets,
  file_level_metadata_api_2eproto, file_level_enum_descriptors_api_2eproto, file_level_service_descriptors_api_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK ::PROTOBUF_NAMESPACE_ID::Metadata
descriptor_table_api_2eproto_metadata_getter(int index) {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_api_2eproto);
  return descriptor_table_api_2eproto.file_level_metadata[index];
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_api_2eproto(&descriptor_table_api_2eproto);

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
