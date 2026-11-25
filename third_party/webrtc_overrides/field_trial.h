// Copyright 2025 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string>
#include <string_view>


class RTC_EXPORT WebRtcFieldTrials : public webrtc::FieldTrialsView {
 public:
  std::string Lookup(std::string_view trial) const override;
};
