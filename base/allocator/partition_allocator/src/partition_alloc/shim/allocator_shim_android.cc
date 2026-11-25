// Copyright 2023 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <unistd.h>


#if PA_BUILDFLAG(USE_PARTITION_ALLOC_AS_MALLOC)
#endif

// No calls to malloc / new in this file. They would cause re-entrancy of
// the shim, which is hard to deal with. Keep this code as simple as possible
// and don't use any external C++ object here, not even //base ones. Even if
// they are safe to use today, in future they might be refactored.


// Cpp symbols (new / delete) should always be routed through the shim layer
// except on Windows and macOS (except for PartitionAlloc-Everywhere) where the
// malloc intercept is deep enough that it also catches the cpp calls.
//
// In case of PartitionAlloc-Everywhere on macOS, malloc backed by
// allocator_shim::internal::PartitionMalloc crashes on OOM, and we need to
// avoid crashes in case of operator new() noexcept.  Thus, operator new()
// noexcept needs to be routed to
// allocator_shim::internal::PartitionMallocUnchecked through the shim layer.

// Android does not support symbol interposition. The way malloc symbols are
// intercepted on Android is by using link-time -wrap flags.
#if PA_BUILDFLAG(SHIM_SUPPORTS_ALLOC_TOKEN)
#endif

// Cross-checks.

#if PA_BUILDFLAG(MEMORY_TOOL_REPLACES_ALLOCATOR)
#error The allocator shim should not be compiled when building for memory tools.
#endif

#if (defined(__GNUC__) && defined(__EXCEPTIONS)) || \
    (defined(_MSC_VER) && defined(_CPPUNWIND))
#error This code cannot be used when exceptions are turned on.
#endif
