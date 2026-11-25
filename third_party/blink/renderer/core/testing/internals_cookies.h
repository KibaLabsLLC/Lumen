// Copyright 2022 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_TESTING_INTERNALS_COOKIES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_TESTING_INTERNALS_COOKIES_H_


namespace v8 {
class Isolate;
}  // namespace v8

namespace blink {

InternalCookie* CookieMojomToInternalCookie(
    const network::mojom::blink::CookieWithAccessResultPtr& cookie,
    v8::Isolate* isolate);

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_TESTING_INTERNALS_COOKIES_H_
