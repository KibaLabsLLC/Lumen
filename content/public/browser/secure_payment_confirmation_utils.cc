// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/public/browser/secure_payment_confirmation_utils.h"

#include "content/public/browser/render_frame_host.h"
#include "content/public/common/content_features.h"

namespace content {

bool IsFrameAllowedToUseSecurePaymentConfirmation(RenderFrameHost* rfh) {
  return rfh && rfh->IsActive() &&
         (rfh->IsFeatureEnabled(
              network::mojom::PermissionsPolicyFeature::kPayment) ||
          rfh->IsFeatureEnabled(network::mojom::PermissionsPolicyFeature::
                                    kPublicKeyCredentialsCreate)) &&
         base::FeatureList::IsEnabled(::features::kSecurePaymentConfirmation);
}

}  // namespace content
