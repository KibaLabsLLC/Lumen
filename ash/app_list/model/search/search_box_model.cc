// Copyright 2012 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ash/app_list/model/search/search_box_model.h"

#include "ash/app_list/model/search/search_box_model_observer.h"

namespace ash {

SearchBoxModel::SearchBoxModel() = default;

SearchBoxModel::~SearchBoxModel() = default;

void SearchBoxModel::SetSunfishButtonVisibility(
    SearchBoxModel::SunfishButtonVisibility show) {
  if (sunfish_button_visibility_ == show) {
    return;
  }
  sunfish_button_visibility_ = show;
  for (SearchBoxModelObserver& observer : observers_) {
    observer.SunfishButtonVisibilityChanged();
  }
}

void SearchBoxModel::SetSearchEngineIsGoogle(bool is_google) {
  if (is_google == search_engine_is_google_)
    return;
  search_engine_is_google_ = is_google;
  for (auto& observer : observers_)
    observer.SearchEngineChanged();
}

void SearchBoxModel::AddObserver(SearchBoxModelObserver* observer) {
  observers_.AddObserver(observer);
}

void SearchBoxModel::RemoveObserver(SearchBoxModelObserver* observer) {
  observers_.RemoveObserver(observer);
}

}  // namespace ash
