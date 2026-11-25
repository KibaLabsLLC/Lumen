// Protocol Buffers - Google's data interchange format
// Copyright 2023 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef UPB_UPB_GENERATOR_PLUGIN_H_
#define UPB_UPB_GENERATOR_PLUGIN_H_

#include <stdio.h>

#include <cstring>
#include <string>
#include <utility>
#include <vector>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif


// Must be last.

namespace upb {
namespace generator {

inline std::vector<std::pair<std::string, std::string>> ParseGeneratorParameter(
    const absl::string_view text) {
  std::vector<std::pair<std::string, std::string>> ret;
  google::protobuf::compiler::ParseGeneratorParameter(text, &ret);
  return ret;
}

// Recursively populates the DefPool with the given FileDescriptor.
void PopulateDefPool(const google::protobuf::FileDescriptor* file, upb::Arena* arena,
                     DefPool* pool,
                     absl::flat_hash_set<std::string>* files_seen);

// Recursively populates the DefPoolPair with the given FileDescriptor.
void PopulateDefPool(const google::protobuf::FileDescriptor* file, upb::Arena* arena,
                     DefPoolPair* pools,
                     absl::flat_hash_set<std::string>* files_seen);

}  // namespace generator
}  // namespace upb


#endif  // UPB_UPB_GENERATOR_PLUGIN_H_
