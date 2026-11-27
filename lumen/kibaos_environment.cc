// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "lumen/kibaos_environment.h"

#include <string>

#include "base/environment.h"
#include "base/strings/string_number_conversions.h"
#include "build/chromeos_buildflags.h"
#include "components/version_info/channel.h"

namespace kibaos {
namespace {

constexpr char kVersionString[] = "KibaOS 1.0.0";

constexpr char kChannelEnvVar[] = "KIBAOS_CHANNEL";
constexpr char kLoggingRedirectDisabledEnvVar[] =
    "KIBAOS_LOGGING_REDIRECT_DISABLED";

}  // namespace

std::string GetVersionString() {
  return kVersionString;
}

version_info::Channel GetChannel() {
  auto env = base::Environment::Create();
  std::string channel_str;
  if (!env->GetVar(kChannelEnvVar, &channel_str)) {
    return version_info::Channel::UNKNOWN;
  }

  if (channel_str == "stable") return version_info::Channel::STABLE;
  if (channel_str == "beta")   return version_info::Channel::BETA;
  if (channel_str == "dev")    return version_info::Channel::DEV;
  if (channel_str == "canary") return version_info::Channel::CANARY;
  return version_info::Channel::UNKNOWN;
}

void SetUpLockedFullscreenEnvironment() {
  // In a full KibaOS session: disable VT switching, blank other TTYs,
  // suppress D-Bus notifications to the lock screen, etc.
  // These operations require root or CAP_SYS_TTY_CONFIG; in Lumen's
  // non-root development mode this is intentionally a no-op.
}

bool IsLoggingRedirectDisabled() {
  auto env = base::Environment::Create();
  std::string val;
  return env->GetVar(kLoggingRedirectDisabledEnvVar, &val) && val == "1";
}

}  // namespace kibaos
