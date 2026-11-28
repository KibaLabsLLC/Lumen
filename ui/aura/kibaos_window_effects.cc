// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/aura/kibaos_window_effects.h"

#include <algorithm>

#include "base/check.h"
#include "ui/aura/window.h"
#include "ui/compositor/layer.h"
#include "ui/gfx/geometry/rounded_corners_f.h"

namespace aura::kibaos {

namespace {

// At or above this alpha a KibaOS surface is fully opaque, so it does not pay
// for a backdrop blur nobody can see.
constexpr float kOpaqueSurfaceAlpha = 0.995f;

// The compositor rejects blur qualities outside of this range.
constexpr float kMinBackdropBlurQuality = 0.1f;
constexpr float kMaxBackdropBlurQuality = 1.0f;

}  // namespace

void ApplySurfaceStyle(Window* window, const SurfaceStyle& style) {
  CHECK(window);

  ui::Layer* layer = window->layer();
  if (!layer) {
    return;
  }

  const float corner_radius = std::max(0.0f, style.corner_radius);
  const bool translucent = style.surface_alpha < kOpaqueSurfaceAlpha;

  layer->SetRoundedCornerRadius(gfx::RoundedCornersF(corner_radius));
  // `SetTransparent()` keeps the layer in sync with `Window::transparent()` and
  // makes the compositor blend the window over what is behind it.
  window->SetTransparent(translucent);

  if (translucent && style.backdrop_blur_sigma > 0.0f) {
    layer->SetBackgroundBlur(style.backdrop_blur_sigma);
    layer->SetBackdropFilterQuality(std::clamp(
        style.backdrop_blur_quality, kMinBackdropBlurQuality,
        kMaxBackdropBlurQuality));
  } else {
    layer->SetBackgroundBlur(0.0f);
  }
}

}  // namespace aura::kibaos
