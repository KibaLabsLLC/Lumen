// Copyright 2017 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "components/crash/android/pure_java_exception_handler.h"

// Must come after all headers that specialize FromJniType() / ToJniType().

void UninstallPureJavaExceptionHandler() {
  Java_PureJavaExceptionHandler_uninstallHandler(
      jni_zero::AttachCurrentThread());
}

DEFINE_JNI(PureJavaExceptionHandler)
