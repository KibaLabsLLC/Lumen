// Copyright 2018 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/loader/fetch_priority_attribute.h"

namespace blink {

mojom::blink::FetchPriorityHint GetFetchPriorityAttributeValue(
    const String& value) {
  if (EqualIgnoringAsciiCase(value, "low")) {
    return mojom::blink::FetchPriorityHint::kLow;
  }
  if (EqualIgnoringAsciiCase(value, "high")) {
    return mojom::blink::FetchPriorityHint::kHigh;
  }
  return mojom::blink::FetchPriorityHint::kAuto;
}

}  // namespace blink
