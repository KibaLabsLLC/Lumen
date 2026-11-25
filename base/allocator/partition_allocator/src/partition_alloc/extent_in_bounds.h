// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PARTITION_ALLOC_EXTENT_IN_BOUNDS_H_
#define PARTITION_ALLOC_EXTENT_IN_BOUNDS_H_

// This is the same as `bounds_checks.h`, but kept in a separate header
// to avoid bloating consumers of the widely included `span.h`.

#include <cstddef>


namespace partition_alloc {

// Like `IsExtentOutOfBounds()`, but without the negative logic.
//
// Has the same caveats as `IsExtentOutOfBounds()` (but inverted).
//
// Given a `T* elems` and a max `index`, call
// ```
// CHECK(IsExtentInBounds(elems, index));
// ```
template <typename T>
bool IsExtentInBounds(const T* ptr,
                      internal::base::StrictNumeric<size_t> index) {
  internal::base::CheckedNumeric<size_t> size_bytes = index;
  size_bytes *= sizeof(T);
  return !IsExtentOutOfBounds(ptr, size_bytes.ValueOrDie(), sizeof(T));
}

}  // namespace partition_alloc

#endif  // PARTITION_ALLOC_EXTENT_IN_BOUNDS_H_
