// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_BROWSER_FUSEBOX_ACTION_MOJO_UTILS_H_
#define COMPONENTS_OMNIBOX_BROWSER_FUSEBOX_ACTION_MOJO_UTILS_H_


namespace fusebox_action {

// Converts a FuseboxAction Proto object into a FuseboxAction Mojom object.
mojom::FuseboxActionPtr SyncFuseboxActionProtoToMojo(
    const omnibox::SuggestTemplateInfo::FuseboxAction& proto);

}  // namespace fusebox_action

#endif  // COMPONENTS_OMNIBOX_BROWSER_FUSEBOX_ACTION_MOJO_UTILS_H_
