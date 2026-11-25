// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/html/install_result_event.h"


namespace blink {

InstallResultEvent::InstallResultEvent(
    const AtomicString& type,
    const InstallResultEventInit* initializer)
    : Event(type, initializer) {
  result_ = initializer->result().AsEnum();
}

InstallResultEvent::~InstallResultEvent() = default;

const AtomicString& InstallResultEvent::InterfaceName() const {
  return event_interface_names::kInstallResultEvent;
}

void InstallResultEvent::Trace(Visitor* visitor) const {
  Event::Trace(visitor);
}

}  // namespace blink
