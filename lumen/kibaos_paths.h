// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LUMEN_KIBAOS_PATHS_H_
#define LUMEN_KIBAOS_PATHS_H_

#include "base/files/file_path.h"

namespace kibaos {

// Well-known KibaOS filesystem paths. These mirror the layout used by
// ChromeOS but under a KibaOS-branded hierarchy rooted at /run/kibaos.

// Returns the root of the KibaOS runtime directory (default: /run/kibaos).
base::FilePath GetRuntimeRoot();

// Returns the path where the primary user's Downloads are stored.
// Falls back to ~/Downloads when no session is active.
base::FilePath GetPrimaryUserDownloadsPath();

// Returns the path of the KibaOS Linux (Crostini) container's shared files.
// This is exposed through the shell delegate as GetLinuxFilesPath().
base::FilePath GetLinuxContainerFilesPath();

// Returns the path to the Android files directory (ARC) within KibaOS.
base::FilePath GetAndroidFilesPath();

// Returns the Drivefs mount point inside KibaOS.
// |path| is set to the mount point and true is returned when mounted.
bool GetDriveFsMountPoint(base::FilePath* path);

// Converts a file-system URL (filesystem:chrome-extension:// scheme) to a
// real file path under the KibaOS virtual filesystem.
base::FilePath CrackFileSystemUrl(const std::string& url);

}  // namespace kibaos

#endif  // LUMEN_KIBAOS_PATHS_H_
