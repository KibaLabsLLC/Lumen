// Copyright 2012 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <windows.h>

#include <cstddef>


namespace partition_alloc::internal::base {

// static
PlatformThreadId PlatformThread::CurrentId() {
  return ::GetCurrentThreadId();
}

// static
PlatformThreadRef PlatformThread::CurrentRef() {
  return PlatformThreadRef(::GetCurrentThreadId());
}

// static
PlatformThreadHandle PlatformThread::CurrentHandle() {
  return PlatformThreadHandle(::GetCurrentThread());
}

// static
void PlatformThread::Sleep(TimeDelta duration) {
  // When measured with a high resolution clock, Sleep() sometimes returns much
  // too early. We may need to call it repeatedly to get the desired duration.
  // PlatformThread::Sleep doesn't support mock-time, so this always uses
  // real-time.
  const TimeTicks end = subtle::TimeTicksNowIgnoringOverride() + duration;
  for (TimeTicks now = subtle::TimeTicksNowIgnoringOverride(); now < end;
       now = subtle::TimeTicksNowIgnoringOverride()) {
    ::Sleep(static_cast<DWORD>((end - now).InMillisecondsRoundedUp()));
  }
}

}  // namespace partition_alloc::internal::base
