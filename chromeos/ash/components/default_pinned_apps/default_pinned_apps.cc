// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chromeos/ash/components/default_pinned_apps/default_pinned_apps.h"

#include "ash/constants/ash_switches.h"
#include "ash/constants/web_app_id_constants.h"
#include "chromeos/ash/components/file_manager/app_id.h"
#include "content/public/browser/browser_context.h"

namespace {

// KibaOS pins only apps that ship with the OS. The default shelf is the four
// KibaOS dock items (Files, Settings, Terminal and Gallery) followed by the
// image and capture apps.
std::vector<StaticAppId> GetKibaOSDefaultPinnedApps() {
  return {
      file_manager::kFileManagerSwaAppId,
      ash::kOsSettingsAppId,
      ash::kCroshAppId,
      ash::kMediaAppId,
      ash::kCameraAppId,
      ash::kHelpAppId,
  };
}

std::vector<StaticAppId> GetKibaOSTabletDefaultPinnedApps() {
  return {
      file_manager::kFileManagerSwaAppId,
      ash::kOsSettingsAppId,
      ash::kMediaAppId,
      ash::kCameraAppId,
  };
}

}  // namespace

std::vector<StaticAppId> GetDefaultPinnedAppsForFormFactor(
    content::BrowserContext* /*browser_context*/) {
  if (ash::switches::IsTabletFormFactor()) {
    return GetKibaOSTabletDefaultPinnedApps();
  }

  return GetKibaOSDefaultPinnedApps();
}
