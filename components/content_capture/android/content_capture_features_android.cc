// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "components/content_capture/common/content_capture_features.h"

// Must come after all headers that specialize FromJniType() / ToJniType().

static bool JNI_ContentCaptureFeatures_IsEnabled(JNIEnv* env) {
  return content_capture::features::IsContentCaptureEnabled();
}

DEFINE_JNI(ContentCaptureFeatures)
