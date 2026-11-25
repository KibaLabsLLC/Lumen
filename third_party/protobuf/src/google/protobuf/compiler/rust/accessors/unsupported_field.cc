// Protocol Buffers - Google's data interchange format
// Copyright 2023 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd


namespace google {
namespace protobuf {
namespace compiler {
namespace rust {

void UnsupportedField::InMsgImpl(Context& ctx, const FieldDescriptor& field,
                                 AccessorCase accessor_case) const {
  ctx.Emit(R"rs(
    // Unsupported field! :(

    )rs");
}

}  // namespace rust
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
