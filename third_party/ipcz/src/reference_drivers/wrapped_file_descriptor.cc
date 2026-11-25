// Copyright 2022 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "third_party/abseil-cpp/absl/base/macros.h"

namespace ipcz::reference_drivers {

WrappedFileDescriptor::WrappedFileDescriptor(FileDescriptor fd)
    : fd_(std::move(fd)) {}

WrappedFileDescriptor::~WrappedFileDescriptor() = default;

}  // namespace ipcz::reference_drivers
