// Copyright 2012 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#import <Foundation/Foundation.h>


namespace partition_alloc::internal::base {

// static
void SysInfo::OperatingSystemVersionNumbers(int32_t* major_version,
                                            int32_t* minor_version,
                                            int32_t* bugfix_version) {
  NSOperatingSystemVersion version =
      [[NSProcessInfo processInfo] operatingSystemVersion];
  *major_version = saturated_cast<int32_t>(version.majorVersion);
  *minor_version = saturated_cast<int32_t>(version.minorVersion);
  *bugfix_version = saturated_cast<int32_t>(version.patchVersion);
}

}  // namespace partition_alloc::internal::base
