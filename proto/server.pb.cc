// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: server.proto

#include "server.pb.h"

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
static constexpr ::PROTOBUF_NAMESPACE_ID::Metadata* file_level_metadata_server_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_server_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_server_2eproto = nullptr;
const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_server_2eproto::offsets[1] = {};
static constexpr ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema* schemas = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::Message* const* file_default_instances = nullptr;

const char descriptor_table_protodef_server_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014server.proto\032\rmessage.proto\032\033google/pr"
  "otobuf/empty.proto2\245\001\n\013GRPCService\022/\n\005Ge"
  "tIP\022\026.google.protobuf.Empty\032\016.StringMess"
  "age\0222\n\007GetPort\022\026.google.protobuf.Empty\032\017"
  ".IntegerMessage\0221\n\007GetAddr\022\026.google.prot"
  "obuf.Empty\032\016.StringMessageb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_server_2eproto_deps[2] = {
  &::descriptor_table_google_2fprotobuf_2fempty_2eproto,
  &::descriptor_table_message_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_server_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_server_2eproto = {
  false, false, 234, descriptor_table_protodef_server_2eproto, "server.proto", 
  &descriptor_table_server_2eproto_once, descriptor_table_server_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_server_2eproto::offsets,
  file_level_metadata_server_2eproto, file_level_enum_descriptors_server_2eproto, file_level_service_descriptors_server_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK ::PROTOBUF_NAMESPACE_ID::Metadata
descriptor_table_server_2eproto_metadata_getter(int index) {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_server_2eproto);
  return descriptor_table_server_2eproto.file_level_metadata[index];
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_server_2eproto(&descriptor_table_server_2eproto);

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>