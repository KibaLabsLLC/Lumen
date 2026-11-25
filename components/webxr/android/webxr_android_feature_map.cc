// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#if BUILDFLAG(ENABLE_VR)
#include "device/vr/public/cpp/features.h"
#endif

// Must come after all headers that specialize FromJniType() / ToJniType().

namespace webxr {
static bool JNI_WebXrAndroidFeatureMap_IsOpenXrEnabled(JNIEnv* env) {
#if BUILDFLAG(ENABLE_OPENXR)
  return device::features::IsOpenXrEnabled();
#else
  return false;
#endif
}

static bool JNI_WebXrAndroidFeatureMap_IsHandTrackingEnabled(JNIEnv* env) {
#if BUILDFLAG(ENABLE_OPENXR)
  return device::features::IsHandTrackingEnabled();
#else
  return false;
#endif
}

static bool JNI_WebXrAndroidFeatureMap_IsOpenXrAndroidSystemKeyboardEnabled(
    JNIEnv* env) {
#if BUILDFLAG(ENABLE_OPENXR)
  return base::FeatureList::IsEnabled(
      device::features::kOpenXrAndroidSystemKeyboard);
#else
  return false;
#endif
}

}  // namespace webxr

DEFINE_JNI(WebXrAndroidFeatureMap)
