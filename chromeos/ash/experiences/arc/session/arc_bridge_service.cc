// Copyright 2015 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chromeos/ash/experiences/arc/session/arc_bridge_service.h"

// These header is necessary for instantiation of ConnectionHolder.

namespace arc {

ArcBridgeService::ArcBridgeService() = default;

ArcBridgeService::~ArcBridgeService() = default;

void ArcBridgeService::AddObserver(Observer* observer) {
  observer_list_.AddObserver(observer);
}

void ArcBridgeService::RemoveObserver(Observer* observer) {
  observer_list_.RemoveObserver(observer);
}

void ArcBridgeService::ObserveBeforeArcBridgeClosed() {
  for (auto& observer : observer_list_) {
    observer.BeforeArcBridgeClosed();
  }
}

void ArcBridgeService::ObserveAfterArcBridgeClosed() {
  for (auto& observer : observer_list_) {
    observer.AfterArcBridgeClosed();
  }
}

}  // namespace arc
