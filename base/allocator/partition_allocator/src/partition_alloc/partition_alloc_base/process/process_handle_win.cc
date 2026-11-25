// Copyright 2013 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <windows.h>

namespace partition_alloc::internal::base {

ProcessId GetCurrentProcId() {
  return ::GetCurrentProcessId();
}

}  // namespace partition_alloc::internal::base
