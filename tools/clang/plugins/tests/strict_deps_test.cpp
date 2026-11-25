// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <atomic>  // Simulate header in system include missing from modulemap
#include <not_in_modulemap>  // Header in sysroot missing from modulemap
#include <private>  // Simulate header in sysroot private in the modulemap
#include <string>   // OK (from system include)
#include <valid>    // OK (from sysroot)

