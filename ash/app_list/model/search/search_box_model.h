// Copyright 2012 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_APP_LIST_MODEL_SEARCH_SEARCH_BOX_MODEL_H_
#define ASH_APP_LIST_MODEL_SEARCH_SEARCH_BOX_MODEL_H_

#include "ash/app_list/model/app_list_model_export.h"
#include "base/observer_list.h"

namespace ash {

class SearchBoxModelObserver;

// SearchBoxModel provides the user entered text, and the system state that
// influences the search box behavior.
class APP_LIST_MODEL_EXPORT SearchBoxModel {
 public:
  // How the Sunfish-session button should appear in the search box.
  enum class SunfishButtonVisibility {
    kHidden = 0,
    kShownWithScannerIcon = 1,
    kShownWithSunfishIcon = 2,
  };

  SearchBoxModel();
  SearchBoxModel(const SearchBoxModel&) = delete;
  SearchBoxModel& operator=(const SearchBoxModel&) = delete;
  ~SearchBoxModel();

  void SetSunfishButtonVisibility(SunfishButtonVisibility show);
  SunfishButtonVisibility sunfish_button_visibility() const {
    return sunfish_button_visibility_;
  }

  void SetSearchEngineIsGoogle(bool is_google);
  bool search_engine_is_google() const { return search_engine_is_google_; }

  void AddObserver(SearchBoxModelObserver* observer);
  void RemoveObserver(SearchBoxModelObserver* observer);

 private:
  bool search_engine_is_google_ = false;
  SunfishButtonVisibility sunfish_button_visibility_ =
      SunfishButtonVisibility::kHidden;

  base::ObserverList<SearchBoxModelObserver> observers_;
};

}  // namespace ash

#endif  // ASH_APP_LIST_MODEL_SEARCH_SEARCH_BOX_MODEL_H_
