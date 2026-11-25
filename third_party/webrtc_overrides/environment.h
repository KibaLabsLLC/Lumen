// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_WEBRTC_OVERRIDES_ENVIRONMENT_H_
#define THIRD_PARTY_WEBRTC_OVERRIDES_ENVIRONMENT_H_


// Certain WebRTC classes require Environment provided at construction.
// When such class is created within a PeerConnectionFactory, it is
// responsibility of the PeerConnectionFactory to create appropriate Environment
// based on PeerConnectionFactoryDependencies. This class is an alternative
// way to get chromium specific webrtc::Environment similar to what
// webrtc::PeerConnectionFactory creates.
RTC_EXPORT webrtc::Environment WebRtcEnvironment();

#endif  // THIRD_PARTY_WEBRTC_OVERRIDES_ENVIRONMENT_H_
