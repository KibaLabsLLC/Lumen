// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "media/webrtc/constants.h"


namespace media {

int WebRtcAudioProcessingSampleRateHz() {
  return webrtc::AudioProcessing::kSampleRate48kHz;
}

}  // namespace media
