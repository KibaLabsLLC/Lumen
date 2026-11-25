// Copyright 2025 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "components/permissions/contexts/local_network_permission_context.h"

#include "components/content_settings/core/common/content_settings_types.h"
#include "content/public/browser/browser_context.h"

namespace permissions {

LocalNetworkPermissionContext::LocalNetworkPermissionContext(
    content::BrowserContext* browser_context)
    : ContentSettingPermissionContextBase(
          browser_context,
          ContentSettingsType::LOCAL_NETWORK,
          network::mojom::PermissionsPolicyFeature::kLocalNetwork) {}

LocalNetworkPermissionContext::~LocalNetworkPermissionContext() = default;

}  // namespace permissions
