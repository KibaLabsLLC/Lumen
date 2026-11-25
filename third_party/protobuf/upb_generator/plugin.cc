// Protocol Buffers - Google's data interchange format
// Copyright 2025 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd


#include <string>


// Must be last.

namespace upb {
namespace generator {

namespace {
absl::string_view ToStringView(upb_StringView str) {
  return absl::string_view(str.data, str.size);
}
}  // namespace

template <typename DefPoolType>
void PopulateDefPoolImpl(const google::protobuf::FileDescriptor* file, upb::Arena* arena,
                         DefPoolType* pool,
                         absl::flat_hash_set<std::string>* files_seen) {
  bool new_file = files_seen->insert(std::string(file->name())).second;
  if (new_file) {
    for (int i = 0; i < file->dependency_count(); ++i) {
      PopulateDefPool(file->dependency(i), arena, pool, files_seen);
    }
    google::protobuf::FileDescriptorProto raw_proto;
    file->CopyTo(&raw_proto);
    std::string serialized = raw_proto.SerializeAsString();
    auto* file_proto = google_protobuf_FileDescriptorProto_parse(
        serialized.data(), serialized.size(), arena->ptr());
    upb::Status status;
    upb::FileDefPtr upb_file = pool->AddFile(file_proto, &status);
    if (!upb_file) {
      absl::string_view name =
          ToStringView(google_protobuf_FileDescriptorProto_name(file_proto));
      ABSL_LOG(FATAL) << "Couldn't add file " << name
                      << " to DefPool: " << status.error_message();
    }
  }
}

void PopulateDefPool(const google::protobuf::FileDescriptor* file, upb::Arena* arena,
                     DefPool* pool,
                     absl::flat_hash_set<std::string>* files_seen) {
  PopulateDefPoolImpl(file, arena, pool, files_seen);
}

void PopulateDefPool(const google::protobuf::FileDescriptor* file, upb::Arena* arena,
                     DefPoolPair* pools,
                     absl::flat_hash_set<std::string>* files_seen) {
  PopulateDefPoolImpl(file, arena, pools, files_seen);
}

}  // namespace generator
}  // namespace upb
