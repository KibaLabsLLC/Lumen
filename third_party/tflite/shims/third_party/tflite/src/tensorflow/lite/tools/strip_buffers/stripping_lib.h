// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_TFLITE_SHIMS_THIRD_PARTY_TFLITE_SRC_TENSORFLOW_LITE_TOOLS_STRIP_BUFFERS_STRIPPING_LIB_H_
#define THIRD_PARTY_TFLITE_SHIMS_THIRD_PARTY_TFLITE_SRC_TENSORFLOW_LITE_TOOLS_STRIP_BUFFERS_STRIPPING_LIB_H_

#include "build/buildflag.h"

#if BUILDFLAG(USE_LITERT_TFLITE)
#else
#include_next "tensorflow/lite/tools/strip_buffers/stripping_lib.h"
#endif

#endif  // THIRD_PARTY_TFLITE_SHIMS_THIRD_PARTY_TFLITE_SRC_TENSORFLOW_LITE_TOOLS_STRIP_BUFFERS_STRIPPING_LIB_H_
