// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/editing/ime/character_bounds_update_event.h"


namespace blink {

CharacterBoundsUpdateEvent::CharacterBoundsUpdateEvent(
    const AtomicString& type,
    const CharacterBoundsUpdateEventInit* initializer)
    : Event(type, initializer) {
  if (initializer->hasRangeStart())
    range_start_ = initializer->rangeStart();

  if (initializer->hasRangeEnd())
    range_end_ = initializer->rangeEnd();
}

CharacterBoundsUpdateEvent::CharacterBoundsUpdateEvent(const AtomicString& type,
                                                       uint32_t range_start,
                                                       uint32_t range_end)
    : Event(type,
            Bubbles::kNo,
            Cancelable::kNo,
            ComposedMode::kComposed,
            base::TimeTicks::Now()),
      range_start_(range_start),
      range_end_(range_end) {}

CharacterBoundsUpdateEvent* CharacterBoundsUpdateEvent::Create(
    const AtomicString& type,
    const CharacterBoundsUpdateEventInit* initializer) {
  return MakeGarbageCollected<CharacterBoundsUpdateEvent>(type, initializer);
}

CharacterBoundsUpdateEvent::~CharacterBoundsUpdateEvent() = default;

uint32_t CharacterBoundsUpdateEvent::rangeStart() const {
  return range_start_;
}

uint32_t CharacterBoundsUpdateEvent::rangeEnd() const {
  return range_end_;
}

const AtomicString& CharacterBoundsUpdateEvent::InterfaceName() const {
  return event_interface_names::kTextUpdateEvent;
}

}  // namespace blink
