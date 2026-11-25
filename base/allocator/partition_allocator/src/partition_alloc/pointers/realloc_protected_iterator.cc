// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <optional>


#if PA_BUILDFLAG(ENABLE_BACKUP_REF_PTR_SUPPORT)
#endif

namespace base::internal {

std::optional<partition_alloc::SlotAddressAndSize> WrapBackingSlot(
    [[maybe_unused]] const void* p) {
#if PA_BUILDFLAG(ENABLE_BACKUP_REF_PTR_SUPPORT)
  if (!p) {
    return std::nullopt;
  }
  const uintptr_t addr = partition_alloc::UntagPtr(p);
  if (!partition_alloc::IsManagedByPartitionAllocBRPPool(addr)) {
    return std::nullopt;
  }
  const auto slot_and_size =
      partition_alloc::SlotAddressAndSize::FromBRPPool(addr);
  partition_alloc::internal::InSlotMetadata::From(slot_and_size)
      ->AcquireFromUnprotectedPtr();
  return slot_and_size;
#else
  return std::nullopt;
#endif
}

void UnwrapBackingSlot(
    [[maybe_unused]] std::optional<partition_alloc::SlotAddressAndSize> slot) {
#if PA_BUILDFLAG(ENABLE_BACKUP_REF_PTR_SUPPORT)
  if (!slot) {
    return;
  }
  auto* metadata = partition_alloc::internal::InSlotMetadata::From(*slot);

  // Security check: if the backing was freed while the wrapper held its ref,
  // the slot's "allocated" bit in InSlotMetadata is clear. That means the
  // container reallocated (or otherwise freed its backing) while iteration
  // was in progress -- a classic iterator-UAF setup. PA's BRP quarantine
  // kept the slot from being reused, but rather than let the caller continue
  // reading zapped memory, crash now.
  PA_BASE_CHECK(metadata->IsAlive());

  if (metadata->ReleaseFromUnprotectedPtr()) {
    partition_alloc::PartitionRoot::FreeAfterBRPQuarantine(*slot);
  }
#endif
}

}  // namespace base::internal
