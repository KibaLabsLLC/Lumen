// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LUMEN_KIBAOS_ENVIRONMENT_H_
#define LUMEN_KIBAOS_ENVIRONMENT_H_

#include <string>

#include "components/version_info/channel.h"

namespace kibaos {

// KibaOS release information.

// Returns the human-readable KibaOS version string, e.g. "KibaOS 1.0.0".
std::string GetVersionString();

// Returns the KibaOS release channel (STABLE, BETA, DEV, or CANARY).
// Reads the KIBAOS_CHANNEL environment variable if set, otherwise returns
// UNKNOWN.
version_info::Channel GetChannel();

// Sets up the process environment for a trusted-pinned (locked-fullscreen)
// window. In a full KibaOS session this would, e.g., disable virtual terminal
// switching. Currently a no-op skeleton.
void SetUpLockedFullscreenEnvironment();

// Returns true when the KIBAOS_LOGGING_REDIRECT_DISABLED environment variable
// is set to "1". Corresponds to the --disable-logging-redirect CLI flag on
// ChromeOS.
bool IsLoggingRedirectDisabled();

}  // namespace kibaos

#endif  // LUMEN_KIBAOS_ENVIRONMENT_H_
