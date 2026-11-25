// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BROWSER_APIS_TAB_STRIP_ADAPTERS_TRANSLATION_ADAPTER_H_
#define COMPONENTS_BROWSER_APIS_TAB_STRIP_ADAPTERS_TRANSLATION_ADAPTER_H_

#include "base/types/expected.h"
#include "components/browser_apis/tab_strip/types/tab.h"
#include "components/tabs/public/tab_collection.h"
#include "components/tabs/public/tab_interface.h"

namespace tabs_api {

// Provides an interface to encode tabs to mojo representations.
class TranslationAdapter {
 public:
  virtual base::expected<Tab, mojo_base::mojom::ErrorPtr> ToMojoTab(
      tabs::TabHandle handle) = 0;

  virtual base::expected<mojom::DataPtr, mojo_base::mojom::ErrorPtr> ToMojoData(
      tabs::TabCollectionHandle handle) = 0;

  virtual ~TranslationAdapter() = default;
};

}  // namespace tabs_api

#endif  // COMPONENTS_BROWSER_APIS_TAB_STRIP_ADAPTERS_TRANSLATION_ADAPTER_H_
