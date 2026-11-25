// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_NETWORK_SANDBOX_GRANT_RESULT_HELPER_H_
#define CONTENT_BROWSER_NETWORK_SANDBOX_GRANT_RESULT_HELPER_H_

#include "content/common/content_export.h"

namespace content {

enum class SandboxGrantResult;

// Helper to process the sandbox grant result and update the parameters
// accordingly.
CONTENT_EXPORT void ProcessSandboxGrantResult(
    network::mojom::NetworkContextParams& params,
    SandboxGrantResult grant_access_result);

}  // namespace content

#endif  // CONTENT_BROWSER_NETWORK_SANDBOX_GRANT_RESULT_HELPER_H_
