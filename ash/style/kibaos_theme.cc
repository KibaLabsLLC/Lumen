// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/style/kibaos_theme.h"

#include <array>

#include "ash/style/ash_color_id.h"
#include "base/containers/span.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/color/color_id.h"
#include "ui/color/color_mixer.h"
#include "ui/color/color_provider.h"
#include "ui/color/color_provider_key.h"
#include "ui/color/color_recipe.h"
#include "ui/gfx/geometry/rounded_corners_f.h"

namespace ash::kibaos {

namespace {

// The accent dots of the KibaOS color palette, left to right.
constexpr std::array<SkColor, kAccentColorCount> kAccentColors = {
    SkColorSetRGB(0x2F, 0x6B, 0xEA),  // Royal blue
    SkColorSetRGB(0x4D, 0x6F, 0xE8),  // Periwinkle
    SkColorSetRGB(0x7A, 0x8B, 0xF0),  // Lilac
    SkColorSetRGB(0x2B, 0xB8, 0xB0),  // Teal
    SkColorSetRGB(0x29, 0xB6, 0xD8),  // Aqua
    SkColorSetRGB(0x39, 0xA9, 0xDC),  // Sky
    SkColorSetRGB(0x2A, 0x93, 0xD4),  // Azure
    SkColorSetRGB(0x0F, 0x7B, 0xC4),  // Deep blue
};

// Glass surfaces. `SkColorSetARGB` alphas are intentionally below opaque: the
// surfaces are rendered over a blurred backdrop (see
// ui/aura/kibaos_window_effects.h).
constexpr SkColor kGlassSurfaceLight = SkColorSetARGB(0xF2, 0xFF, 0xFF, 0xFF);
constexpr SkColor kGlassSurfaceDark = SkColorSetARGB(0xF2, 0x1E, 0x28, 0x3C);
constexpr SkColor kGlassSurfaceInactiveLight =
    SkColorSetARGB(0xF2, 0xF5, 0xF8, 0xFF);
constexpr SkColor kGlassSurfaceInactiveDark =
    SkColorSetARGB(0xF2, 0x17, 0x1F, 0x30);

// Dialogs are the most translucent KibaOS surface: they are painted over the
// backdrop blur installed by ui/aura/kibaos_window_effects.h.
constexpr SkColor kGlassDialogLight = SkColorSetARGB(0xF2, 0xFF, 0xFF, 0xFF);
constexpr SkColor kGlassDialogDark = SkColorSetARGB(0xF2, 0x1E, 0x28, 0x3C);

// Menus and tooltips are more opaque so that labels stay readable.
constexpr SkColor kMenuSurfaceLight = SkColorSetARGB(0xF7, 0xFB, 0xFC, 0xFF);
constexpr SkColor kMenuSurfaceDark = SkColorSetARGB(0xF7, 0x23, 0x2B, 0x39);

constexpr SkColor kTooltipBackground = SkColorSetRGB(0x16, 0x21, 0x4A);
constexpr SkColor kTooltipForeground = SkColorSetRGB(0xEC, 0xF3, 0xFE);

// KibaOS shadows are wide and navy instead of neutral black.
constexpr SkColor kShadowAmbient = SkColorSetARGB(0x1A, 0x1E, 0x28, 0x3C);
constexpr SkColor kShadowKey = SkColorSetARGB(0x33, 0x1E, 0x28, 0x3C);

bool IsDarkMode(const ui::ColorProviderKey& key) {
  return key.color_mode == ui::ColorProviderKey::ColorMode::kDark;
}

}  // namespace

base::span<const SkColor> AccentColors() {
  return kAccentColors;
}

SkColor GetAccentColor(size_t index) {
  return kAccentColors[index % kAccentColors.size()];
}

gfx::RoundedCornersF WindowRoundedCorners() {
  return gfx::RoundedCornersF(kWindowCornerRadius);
}

void AddKibaosColorMixer(ui::ColorProvider* provider,
                         const ui::ColorProviderKey& key) {
  ui::ColorMixer& mixer = provider->AddMixer();
  const bool dark = IsDarkMode(key);

  // Window frames and other floating surfaces are KibaOS glass panels. A
  // user-selected custom theme owns the frame colors, so only apply the KibaOS
  // frame when there is no custom theme.
  if (!key.custom_theme) {
    mixer[ui::kColorFrameActive] = {dark ? kGlassSurfaceDark
                                         : kGlassSurfaceLight};
    mixer[ui::kColorFrameInactive] = {dark ? kGlassSurfaceInactiveDark
                                           : kGlassSurfaceInactiveLight};
  }
  mixer[kColorAshKibaosDialogBackgroundColor] = {dark ? kGlassDialogDark
                                                      : kGlassDialogLight};
  mixer[kColorAshSystemUIMenuBackground] = {dark ? kMenuSurfaceDark
                                                 : kMenuSurfaceLight};
  mixer[kColorAshWindowHeaderStrokeColor] = {kHairline};

  // Text and icons on the specialized surfaces.
  mixer[ui::kColorTooltipBackground] = {kTooltipBackground};
  mixer[ui::kColorTooltipForeground] = {kTooltipForeground};

  // Prominent controls use the Kiba Blue seed directly. Off switches are the
  // pale blue track of the design sheet with a white knob.
  mixer[ui::kColorToggleButtonTrackOn] = {kPrimary};
  mixer[ui::kColorToggleButtonTrackOff] = {
      dark ? SkColorSetRGB(0x33, 0x3D, 0x52) : SkColorSetRGB(0xE3, 0xEA, 0xF6)};
  mixer[ui::kColorToggleButtonThumbOn] = {SK_ColorWHITE};
  mixer[ui::kColorToggleButtonThumbOff] = {SK_ColorWHITE};
  mixer[ui::kColorRadioButtonForegroundChecked] = {kPrimary};
  mixer[kColorAshFolderItemCountBackgroundColor] = {kPrimary};
  mixer[kColorAshMultiSelectTextColor] = {kPrimary};

  // Elevation shadows, tinted with the KibaOS navy.
  mixer[ui::kColorShadowValueAmbientShadowElevationFour] = {kShadowAmbient};
  mixer[ui::kColorShadowValueAmbientShadowElevationTwelve] = {kShadowAmbient};
  mixer[ui::kColorShadowValueAmbientShadowElevationTwentyFour] = {
      kShadowAmbient};
  mixer[ui::kColorShadowValueKeyShadowElevationFour] = {kShadowKey};
  mixer[ui::kColorShadowValueKeyShadowElevationTwelve] = {kShadowKey};
  mixer[ui::kColorShadowValueKeyShadowElevationTwentyFour] = {kShadowKey};
}

}  // namespace ash::kibaos
