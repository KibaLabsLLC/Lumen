// Copyright 2022 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "printing/client_info_helpers.h"

#include "base/no_destructor.h"
#include "base/types/optional_util.h"

namespace printing {

namespace {

bool ValidateClientType(mojom::IppClientInfo::ClientType type) {
  return type >= mojom::IppClientInfo::ClientType::kMinValue &&
         type <= mojom::IppClientInfo::ClientType::kMaxValue;
}

bool ValidateStringMember(const std::string* value, size_t max_length) {
  static const base::NoDestructor<RE2> kStringRegex("[a-zA-Z0-9_.-]*");
  return value == nullptr ||
         (value->size() <= max_length && RE2::FullMatch(*value, *kStringRegex));
}

}  // namespace

bool ValidateClientInfoItem(const mojom::IppClientInfo& client_info) {
  return ValidateClientType(client_info.client_type) &&
         ValidateStringMember(&client_info.client_name,
                              kClientInfoMaxNameLength) &&
         ValidateStringMember(&client_info.client_string_version,
                              kClientInfoMaxStringVersionLength) &&
         ValidateStringMember(base::OptionalToPtr(client_info.client_patches),
                              kClientInfoMaxPatchesLength) &&
         ValidateStringMember(base::OptionalToPtr(client_info.client_version),
                              kClientInfoMaxVersionLength);
}

}  // namespace printing
