// Copyright 2013 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "init_webrtc.h"


bool InitializeWebRtcModuleBeforeSandbox() {
  // Workaround for crbug.com/176522
  // On Linux, we can't fetch the number of cores after the sandbox has been
  // initialized, so we call DetectNumberOfCores() here, to cache the value.
  webrtc::cpu_info::DetectNumberOfCores();
  return true;
}

void InitializeWebRtcModule() {
  webrtc::RegisterPerfettoTrackEvents();
}

const perfetto::internal::TrackEventCategoryRegistry&
GetWebRtcTrackEventCategoryRegistry() {
  return webrtc::perfetto_track_event::internal::kCategoryRegistry;
}
