// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_PEERCONNECTION_TESTING_MOCK_RTP_SENDER_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_PEERCONNECTION_TESTING_MOCK_RTP_SENDER_H_

#include "testing/gmock/include/gmock/gmock.h"

namespace blink {

class MockRtpSender : public webrtc::RefCountedObject<webrtc::MockRtpSender> {
 public:
  // TODO(crbug.com/510487701): Remove once webrtc::MockRtpSender mocks this.
  MOCK_METHOD(webrtc::RTCErrorOr<
                  webrtc::scoped_refptr<webrtc::SframeEncryptorInterface>>,
              CreateSframeEncryptorOrError,
              (const webrtc::SframeEncryptorInit&),
              (override));
  MOCK_METHOD(webrtc::RTCError,
              GenerateKeyFrame,
              (const std::vector<std::string>&),
              (override));
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_PEERCONNECTION_TESTING_MOCK_RTP_SENDER_H_
