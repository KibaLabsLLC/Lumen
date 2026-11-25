// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_TRACE_UTIL_H_
#define EXTENSIONS_COMMON_TRACE_UTIL_H_

#include "extensions/common/extension_id.h"

namespace extensions {

// Helper for logging extension id in go/chrometto traces like so:
//
//     #include "base/trace_event/typed_macros.h"
//     #include "extensions/common/trace_util.h"
//
//     using perfetto::protos::pbzero::ChromeTrackEvent;
//
//     TRACE_EVENT(
//         "extensions", "event name", ...,
//         ChromeTrackEvent::kChromeExtensionId,
//         ExtensionIdForTracing(extension_id),
//         ...);
class ExtensionIdForTracing {
 public:
  explicit ExtensionIdForTracing(const ExtensionId& extension_id)
      : extension_id_(extension_id) {}

  ~ExtensionIdForTracing() = default;

  void WriteIntoTrace(
      perfetto::TracedProto<perfetto::protos::pbzero::ChromeExtensionId> proto)
      const;

 private:
  const ExtensionId extension_id_;
};

}  // namespace extensions

#endif  // EXTENSIONS_COMMON_TRACE_UTIL_H_
