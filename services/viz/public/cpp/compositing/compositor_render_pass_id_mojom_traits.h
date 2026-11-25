// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SERVICES_VIZ_PUBLIC_CPP_COMPOSITING_COMPOSITOR_RENDER_PASS_ID_MOJOM_TRAITS_H_
#define SERVICES_VIZ_PUBLIC_CPP_COMPOSITING_COMPOSITOR_RENDER_PASS_ID_MOJOM_TRAITS_H_

#include "components/viz/common/quads/compositor_render_pass.h"

namespace mojo {

template <>
struct StructTraits<viz::mojom::CompositorRenderPassIdDataView,
                    viz::CompositorRenderPassId> {
  static uint64_t value(const viz::CompositorRenderPassId& id);

  static bool Read(viz::mojom::CompositorRenderPassIdDataView data,
                   viz::CompositorRenderPassId* out);
};

}  // namespace mojo

#endif  // SERVICES_VIZ_PUBLIC_CPP_COMPOSITING_COMPOSITOR_RENDER_PASS_ID_MOJOM_TRAITS_H_
