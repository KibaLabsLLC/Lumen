// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "skia/ext/test_fonts_fuchsia.h"

#include <fuchsia/fonts/cpp/fidl.h>

#include "skia/ext/font_utils.h"

namespace skia {

void InitializeSkFontMgrForTest() {
  OverrideDefaultSkFontMgr(SkFontMgr_New_Fuchsia(
      GetTestFontsProvider().BindSync(), SkFontScanner_Make_Fontations()));
}

}  // namespace skia
