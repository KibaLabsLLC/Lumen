// Copyright 2017 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/modules/animationworklet/animator_definition.h"


namespace blink {

AnimatorDefinition::AnimatorDefinition(V8AnimatorConstructor* constructor,
                                       V8AnimateCallback* animate,
                                       V8StateCallback* state)
    : constructor_(constructor), animate_(animate), state_(state) {
  DCHECK(constructor_);
  DCHECK(animate_);
}

void AnimatorDefinition::Trace(Visitor* visitor) const {
  visitor->Trace(constructor_);
  visitor->Trace(animate_);
  visitor->Trace(state_);
}

}  // namespace blink
