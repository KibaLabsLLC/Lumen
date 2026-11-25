// Copyright 2018 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



namespace partition_alloc::internal {

OomFunction g_oom_handling_function = nullptr;

PA_NOINLINE PA_NOT_TAIL_CALLED void PartitionExcessiveAllocationSize(
    size_t size) {
  PA_NO_CODE_FOLDING();
  OOM_CRASH(size);
}

#if !PA_BUILDFLAG(PA_ARCH_CPU_64_BITS)
PA_NOINLINE PA_NOT_TAIL_CALLED void
PartitionOutOfMemoryWithLotsOfUncommitedPages(size_t size) {
  PA_NO_CODE_FOLDING();
  OOM_CRASH(size);
}

[[noreturn]] PA_NOT_TAIL_CALLED PA_NOINLINE void
PartitionOutOfMemoryWithLargeVirtualSize(size_t virtual_size) {
  PA_NO_CODE_FOLDING();
  OOM_CRASH(virtual_size);
}

#endif  // !PA_BUILDFLAG(PA_ARCH_CPU_64_BITS)

}  // namespace partition_alloc::internal
