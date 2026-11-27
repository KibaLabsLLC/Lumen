// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "lumen/kibaos_paths.h"

#include "base/environment.h"
#include "base/files/file_path.h"
#include "base/path_service.h"
#include "base/strings/string_util.h"

namespace kibaos {
namespace {

constexpr char kRuntimeRoot[] = "/run/kibaos";
constexpr char kLinuxFilesSubdir[] = "linux-files";
constexpr char kAndroidFilesSubdir[] = "android-files";
constexpr char kDriveFsSubdir[] = "drivefs";

}  // namespace

base::FilePath GetRuntimeRoot() {
  return base::FilePath(kRuntimeRoot);
}

base::FilePath GetPrimaryUserDownloadsPath() {
  base::FilePath home;
  if (!base::PathService::Get(base::DIR_HOME, &home)) {
    return base::FilePath();
  }
  return home.Append("Downloads");
}

base::FilePath GetLinuxContainerFilesPath() {
  return GetRuntimeRoot().Append(kLinuxFilesSubdir);
}

base::FilePath GetAndroidFilesPath() {
  return GetRuntimeRoot().Append(kAndroidFilesSubdir);
}

bool GetDriveFsMountPoint(base::FilePath* path) {
  base::FilePath candidate = GetRuntimeRoot().Append(kDriveFsSubdir);
  // In a real KibaOS session the mount would be verified via stat(); here we
  // report unmounted so callers degrade gracefully without a running daemon.
  if (path) {
    *path = candidate;
  }
  return false;
}

base::FilePath CrackFileSystemUrl(const std::string& url) {
  // Minimal cracker: strip the well-known virtual-filesystem prefix and return
  // the remainder as a path under the KibaOS runtime root. A production
  // implementation would call into the File System Access API.
  constexpr std::string_view kVirtualPrefix = "filesystem:chrome-extension://";
  if (base::StartsWith(url, kVirtualPrefix,
                        base::CompareCase::INSENSITIVE_ASCII)) {
    return GetRuntimeRoot().Append(url.substr(kVirtualPrefix.size()));
  }
  return base::FilePath();
}

}  // namespace kibaos
