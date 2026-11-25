// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ENUM_H__
#define GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ENUM_H__

#include <string>
#include <vector>


namespace google {
namespace protobuf {
namespace compiler {
namespace objectivec {

class EnumGenerator {
 public:
  EnumGenerator(const EnumDescriptor* descriptor,
                const GenerationOptions& generation_options);
  ~EnumGenerator() = default;

  EnumGenerator(const EnumGenerator&) = delete;
  EnumGenerator& operator=(const EnumGenerator&) = delete;

  void GenerateHeader(io::Printer* printer) const;
  void GenerateSource(io::Printer* printer) const;

  const std::string& name() const { return name_; }

 private:
  const EnumDescriptor* descriptor_;
  const GenerationOptions& generation_options_;
  std::vector<const EnumValueDescriptor*> base_values_;
  std::vector<const EnumValueDescriptor*> all_values_;
  absl::flat_hash_set<const EnumValueDescriptor*> alias_values_to_skip_;
  const std::string name_;
};

}  // namespace objectivec
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_OBJECTIVEC_ENUM_H__
