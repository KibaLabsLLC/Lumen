// Protocol Buffers - Google's data interchange format
// Copyright 2024 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd


#include <string>


namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {

namespace {

std::string MakeIfdefGuardIdentifier(const absl::string_view header_path) {
  return absl::StrCat(absl::AsciiStrToUpper(absl::StrReplaceAll(header_path,
                                                                {
                                                                    {"/", "_"},
                                                                    {".", "_"},
                                                                    {"-", "_"},
                                                                })),
                      "_");
}

}  // namespace

IfdefGuardPrinter::IfdefGuardPrinter(google::protobuf::io::Printer* const p,
                                     const absl::string_view filename)
    : IfdefGuardPrinter(p, filename, MakeIfdefGuardIdentifier) {}

IfdefGuardPrinter::IfdefGuardPrinter(
    google::protobuf::io::Printer* const p, const absl::string_view filename,
    absl::AnyInvocable<std::string(absl::string_view)> make_ifdef_identifier)
    : p_(ABSL_DIE_IF_NULL(p)),
      ifdef_identifier_(make_ifdef_identifier(filename)) {
  // We can't use variable substitution, because we don't know what delimiter
  // to use.
  p->Print(absl::Substitute(
      R"(#ifndef $0
#define $0

)",
      ifdef_identifier_));
}

IfdefGuardPrinter::~IfdefGuardPrinter() {
  // We can't use variable substitution, because we don't know what delimiter
  // to use.
  p_->Print(absl::Substitute(
      R"(
#endif  // $0
)",
      ifdef_identifier_));
}

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
