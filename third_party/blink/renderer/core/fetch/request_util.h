// Copyright 2023 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_FETCH_REQUEST_UTIL_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_FETCH_REQUEST_UTIL_H_

#include "third_party/blink/renderer/core/core_export.h"

namespace blink {

CORE_EXPORT network::mojom::RequestMode V8RequestModeToMojom(
    const V8RequestMode& mode);
CORE_EXPORT network::mojom::RequestDestination V8RequestDestinationToMojom(
    const V8RequestDestination& destination);

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_FETCH_REQUEST_UTIL_H_
