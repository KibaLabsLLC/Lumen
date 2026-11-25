// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_MODULES_PEERCONNECTION_TESTING_MOCK_PEER_CONNECTION_INTERFACE_H_
#define THIRD_PARTY_BLINK_RENDERER_MODULES_PEERCONNECTION_TESTING_MOCK_PEER_CONNECTION_INTERFACE_H_

#include <type_traits>


namespace blink {

class MockPeerConnectionInterface
    : public webrtc::RefCountedObject<webrtc::MockPeerConnectionInterface> {};

static_assert(!std::is_abstract<MockPeerConnectionInterface>::value, "");

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_MODULES_PEERCONNECTION_TESTING_MOCK_PEER_CONNECTION_INTERFACE_H_
