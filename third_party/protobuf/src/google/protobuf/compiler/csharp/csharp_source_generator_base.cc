// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd


#include <sstream>


namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

SourceGeneratorBase::SourceGeneratorBase(
    const Options *options) : options_(options) {
}

SourceGeneratorBase::~SourceGeneratorBase() = default;

void SourceGeneratorBase::WriteGeneratedCodeAttributes(io::Printer* printer) {
  printer->Print("[global::System.Diagnostics.DebuggerNonUserCodeAttribute]\n");
  // The second argument of the [GeneratedCode] attribute could be set to current protoc
  // version, but that would cause excessive code churn in the pre-generated
  // code in the repository every time the protobuf version number is updated.
  printer->Print("[global::System.CodeDom.Compiler.GeneratedCode(\"protoc\", null)]\n");
}

std::string SourceGeneratorBase::class_access_level() {
  return this->options()->internal_access ? "internal" : "public";
}

const Options* SourceGeneratorBase::options() {
  return this->options_;
}

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
