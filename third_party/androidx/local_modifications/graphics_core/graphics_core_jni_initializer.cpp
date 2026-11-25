// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <jni.h>


extern "C" jint GraphicsCore_JNI_OnLoad(JNIEnv* env);

static void JNI_GraphicsCoreJniLoader_Init(JNIEnv* env) {
    GraphicsCore_JNI_OnLoad(env);
}

DEFINE_JNI_FOR_GraphicsCoreJniLoader()
