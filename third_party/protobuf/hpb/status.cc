// Protocol Buffers - Google's data interchange format
// Copyright 2024 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd


#include <cstdint>


namespace hpb {
absl::Status MessageAllocationError(SourceLocation loc) {
  return absl::Status(absl::StatusCode::kUnknown,
                      "Upb message allocation error");
}

absl::Status ExtensionNotFoundError(uint32_t ext_number, SourceLocation loc)
{
  return absl::Status(absl::StatusCode::kUnknown,
                      absl::StrFormat("Extension %d not found", ext_number));
}

absl::Status MessageEncodeError(upb_EncodeStatus s, SourceLocation loc) {
  return absl::Status(absl::StatusCode::kUnknown, "Encoding error");
}

absl::Status MessageDecodeError(upb_DecodeStatus status, SourceLocation loc

) {
  return absl::Status(absl::StatusCode::kUnknown, "Upb message parse error");
}

}  // namespace hpb
