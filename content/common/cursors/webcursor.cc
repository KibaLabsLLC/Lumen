// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/common/cursors/webcursor.h"


namespace content {

WebCursor::WebCursor() = default;

WebCursor::~WebCursor() = default;

WebCursor::WebCursor(const ui::Cursor& cursor) : cursor_(cursor) {}

}  // namespace content
