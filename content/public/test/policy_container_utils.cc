// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/public/test/policy_container_utils.h"

#include <tuple>


namespace content {

blink::mojom::PolicyContainerPtr CreateStubPolicyContainer() {
  mojo::PendingAssociatedRemote<blink::mojom::PolicyContainerHost>
      stub_policy_container_remote;
  std::ignore =
      stub_policy_container_remote.InitWithNewEndpointAndPassReceiver();
  return blink::mojom::PolicyContainer::New(
      blink::mojom::PolicyContainerPolicies::New(),
      std::move(stub_policy_container_remote));
}

}  // namespace content
