// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_AURA_KIBAOS_WINDOW_EFFECTS_H_
#define UI_AURA_KIBAOS_WINDOW_EFFECTS_H_

#include "ui/aura/aura_export.h"

namespace aura {

class Window;

namespace kibaos {

// The radius of a KibaOS window corner, in DIP.
inline constexpr float kWindowCornerRadius = 24.0f;

// The KibaOS window surface model.
//
// KibaOS windows are 24 px rounded glass panels: the compositor rounds the
// window's layer and blurs whatever is behind the window, while the window
// surface itself paints at `surface_alpha`. This is the compositor-level
// counterpart of ash::kibaos (ash/style/kibaos_theme.h), which owns the colors
// and metrics.
struct SurfaceStyle {
  // The radius applied to all four corners of the window layer, in DIP.
  float corner_radius = kWindowCornerRadius;
  // The sigma of the backdrop blur, in DIP. Zero disables the backdrop filter.
  float backdrop_blur_sigma = 30.0f;
  // The backdrop blur quality in (0, 1]. Lower values are cheaper to draw.
  float backdrop_blur_quality = 0.33f;
  // The alpha of the window surface. Values below 1.0 make the window
  // translucent and enable the backdrop blur; the surface color itself is
  // painted by the UI layer (see ash/style/kibaos_theme.h).
  float surface_alpha = 0.88f;
};

// Applies the KibaOS surface model to `window`'s compositor layer: the layer
// is rounded to `style.corner_radius`, the window is made translucent so the
// compositor blends it over the desktop, and the backdrop behind the window is
// blurred when the surface is translucent.
//
// The Ash system dialogs call this for their window (see
// ash/style/system_dialog_delegate_view.cc), so dialogs are rendered as glass
// panels.
AURA_EXPORT void ApplySurfaceStyle(Window* window, const SurfaceStyle& style);

}  // namespace kibaos
}  // namespace aura

#endif  // UI_AURA_KIBAOS_WINDOW_EFFECTS_H_
