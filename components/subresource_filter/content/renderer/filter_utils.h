// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SUBRESOURCE_FILTER_CONTENT_RENDERER_FILTER_UTILS_H_
#define COMPONENTS_SUBRESOURCE_FILTER_CONTENT_RENDERER_FILTER_UTILS_H_


namespace subresource_filter {

// Converts from network `RequestDestination` to an `ElementType` that can be
// used to determine `LoadPolicy` via a `DocumentSubresourceFilter`.
url_pattern_index::proto::ElementType ToElementType(
    network::mojom::RequestDestination request_context);

}  // namespace subresource_filter

#endif  // COMPONENTS_SUBRESOURCE_FILTER_CONTENT_RENDERER_FILTER_UTILS_H_
