// Protocol Buffers - Google's data interchange format
// Copyright 2023 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd


#include <stdint.h>
#include <string.h>


// Must be last.

UPB_NORETURN UPB_NOINLINE void UPB_PRIVATE(
    upb_EpsCopyInputStream_ThrowMalformed)(upb_EpsCopyInputStream* e) {
  e->error = true;
  upb_ErrorHandler_ThrowError(e->err, kUpb_ErrorCode_Malformed);
}

const char* UPB_PRIVATE(upb_EpsCopyInputStream_IsDoneFallback)(
    struct upb_EpsCopyInputStream* e, const char* ptr, int overrun) {
  if (overrun < e->limit) {
    // Need to copy remaining data into patch buffer.
    UPB_ASSERT(overrun < kUpb_EpsCopyInputStream_SlopBytes);
    const char* old_end = ptr;
    const char* new_start = &e->patch[overrun];
    memset(&e->patch[kUpb_EpsCopyInputStream_SlopBytes], 0,
           kUpb_EpsCopyInputStream_SlopBytes);
    memcpy(e->patch, e->end, kUpb_EpsCopyInputStream_SlopBytes);
    ptr = new_start;
    e->end = &e->patch[kUpb_EpsCopyInputStream_SlopBytes];
    e->limit -= kUpb_EpsCopyInputStream_SlopBytes;
    e->limit_ptr = e->end + e->limit;
    UPB_ASSERT(ptr < e->limit_ptr);
    e->input_delta = (uintptr_t)old_end - (uintptr_t)new_start;
    UPB_PRIVATE(upb_EpsCopyInputStream_BoundsChecked)(e);
    return new_start;
  } else {
    UPB_ASSERT(overrun > e->limit);
    return UPB_PRIVATE(upb_EpsCopyInputStream_ReturnError)(e);
  }
}
