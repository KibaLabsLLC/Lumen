// Copyright 2023 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEGMENTATION_PLATFORM_INTERNAL_LOGGING_H_
#define COMPONENTS_SEGMENTATION_PLATFORM_INTERNAL_LOGGING_H_

#include <string>


namespace segmentation_platform {

std::string PredictionResultToDebugString(proto::PredictionResult result);

}

#endif  // COMPONENTS_SEGMENTATION_PLATFORM_INTERNAL_LOGGING_H_
