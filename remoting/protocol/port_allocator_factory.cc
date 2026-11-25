// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "remoting/protocol/port_allocator_factory.h"


namespace remoting::protocol {

PortAllocatorFactory::CreatePortAllocatorResult::CreatePortAllocatorResult() =
    default;
PortAllocatorFactory::CreatePortAllocatorResult::CreatePortAllocatorResult(
    CreatePortAllocatorResult&&) = default;
PortAllocatorFactory::CreatePortAllocatorResult::~CreatePortAllocatorResult() =
    default;

}  // namespace remoting::protocol
