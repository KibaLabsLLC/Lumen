// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_STYLE_KIBAOS_THEME_H_
#define ASH_STYLE_KIBAOS_THEME_H_

#include "ash/ash_export.h"
#include "base/containers/span.h"
#include "ui/color/color_provider_key.h"
#include "ui/gfx/color_palette.h"
#include "ui/gfx/geometry/rounded_corners_f.h"

namespace ui {
class ColorProvider;
}  // namespace ui

namespace ash::kibaos {

// The KibaOS design system: a single royal-blue seed ("Kiba Blue"), cool
// navy-tinted neutrals, 24 px corners and translucent, blurred surfaces.
//
// The colors here mirror ui/chromeos/styles/cros_ref_colors.json5 and
// cros_palette.json5. Code that paints its own layers should prefer the color
// provider; these constants exist for the compositor-level surfaces (window
// frames, shields, artwork) that cannot resolve a color id.

// Brand colors.
ASH_EXPORT inline constexpr SkColor kPrimary = SkColorSetRGB(0x0B, 0x5B, 0xE6);
ASH_EXPORT inline constexpr SkColor kPrimaryHover =
    SkColorSetRGB(0x1E, 0x6B, 0xF2);
ASH_EXPORT inline constexpr SkColor kPrimaryPressed =
    SkColorSetRGB(0x08, 0x47, 0xB8);
ASH_EXPORT inline constexpr SkColor kOnPrimary = SK_ColorWHITE;

// The navy swatches of the KibaOS color palette.
ASH_EXPORT inline constexpr SkColor kNavyDeep = SkColorSetRGB(0x16, 0x21, 0x4A);
ASH_EXPORT inline constexpr SkColor kNavy = SkColorSetRGB(0x3B, 0x4A, 0x6B);
ASH_EXPORT inline constexpr SkColor kNavySoft = SkColorSetRGB(0x6E, 0x82, 0xA8);
ASH_EXPORT inline constexpr SkColor kNavyMist = SkColorSetRGB(0xC3, 0xD2, 0xE8);

// The sky tints of the KibaOS color palette.
ASH_EXPORT inline constexpr SkColor kSkyStrong = SkColorSetRGB(0x1A, 0x6B, 0xF0);
ASH_EXPORT inline constexpr SkColor kSky = SkColorSetRGB(0x7F, 0xA9, 0xF2);
ASH_EXPORT inline constexpr SkColor kSkySoft = SkColorSetRGB(0xA9, 0xC4, 0xF7);
ASH_EXPORT inline constexpr SkColor kSkyMist = SkColorSetRGB(0xCB, 0xDF, 0xFB);

// The default desktop backdrop: a vertical blue gradient.
ASH_EXPORT inline constexpr SkColor kCanvasTop = SkColorSetRGB(0xDC, 0xE8, 0xFB);
ASH_EXPORT inline constexpr SkColor kCanvasBottom =
    SkColorSetRGB(0xEE, 0xF4, 0xFE);

// Text on KibaOS surfaces.
ASH_EXPORT inline constexpr SkColor kTextPrimary = SkColorSetRGB(0x0F, 0x1B, 0x33);
ASH_EXPORT inline constexpr SkColor kTextSecondary =
    SkColorSetRGB(0x5B, 0x6B, 0x85);

// One-pixel hairline used for window and card outlines.
ASH_EXPORT inline constexpr SkColor kHairline =
    SkColorSetARGB(0x1F, 0x0F, 0x1B, 0x33);

// Metrics. KibaOS uses a single 24 px corner radius for windows, panels and
// cards, and 16 px for controls.
ASH_EXPORT inline constexpr int kWindowCornerRadius = 24;
ASH_EXPORT inline constexpr int kPanelCornerRadius = 24;
ASH_EXPORT inline constexpr int kCardCornerRadius = 24;
ASH_EXPORT inline constexpr int kControlCornerRadius = 16;

// Window frame metrics.
ASH_EXPORT inline constexpr int kWindowHeaderHeight = 48;
ASH_EXPORT inline constexpr int kWindowControlSize = 32;
ASH_EXPORT inline constexpr int kWindowHeaderInset = 12;

// The surface model: windows and panels are 88% opaque glass over a 30 px
// backdrop blur.
ASH_EXPORT inline constexpr float kSurfaceAlpha = 0.88f;
ASH_EXPORT inline constexpr float kBackdropBlurSigma = 30.0f;
ASH_EXPORT inline constexpr float kBackdropBlurQuality = 0.33f;

// The number of accent colors in the KibaOS color palette.
ASH_EXPORT inline constexpr size_t kAccentColorCount = 8;

// The eight accent dots of the KibaOS color palette, in palette order.
ASH_EXPORT base::span<const SkColor> AccentColors();

// Returns the accent color at `index`, wrapping around the palette.
ASH_EXPORT SkColor GetAccentColor(size_t index);

// The corner radii applied to a KibaOS window.
ASH_EXPORT gfx::RoundedCornersF WindowRoundedCorners();

// Adds the KibaOS surface and glass colors on top of the stock Ash mixers.
// Must be added after `AddAshColorMixer()`'s own recipes so that the KibaOS
// values win.
ASH_EXPORT void AddKibaosColorMixer(ui::ColorProvider* provider,
                                    const ui::ColorProviderKey& key);

}  // namespace ash::kibaos

#endif  // ASH_STYLE_KIBAOS_THEME_H_
