// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/process/memory.h"

#include <string.h>

#include "base/debug/alias.h"
#include "base/immediate_crash.h"
#include "base/logging.h"
#include "build/build_config.h"

#if PA_BUILDFLAG(USE_ALLOCATOR_SHIM)
#endif

#if PA_BUILDFLAG(USE_PARTITION_ALLOC)
#endif

#if BUILDFLAG(IS_WIN)
#include <windows.h>
#else
#include <unistd.h>
#endif  // BUILDFLAG(IS_WIN)

namespace base::internal {
bool ReleaseAddressSpaceReservation() {
#if PA_BUILDFLAG(USE_PARTITION_ALLOC)
  return partition_alloc::ReleaseReservation();
#else
  return false;
#endif
}
}  // namespace base::internal
