// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chromeos/ash/components/growth/campaigns_utils.h"

#include <map>
#include <string>
#include <string_view>

#include "base/notreached.h"
#include "base/strings/cstring_view.h"
#include "base/strings/strcat.h"
#include "base/strings/stringprintf.h"
#include "chromeos/ash/components/growth/campaigns_constants.h"
#include "url/gurl.h"

namespace growth {

namespace {

// NOTE: Do not change the number.
// The number of `campaign_id`s can be stored in the sparse histograms.
constexpr int kCampaignsCountPerHistogram = 500;

}  // namespace

std::string_view GetGrowthCampaignsEventNamePrefix() {
  // Only event name with this prefix can be processed by the Feature Engagement
  // framework.
  return "ChromeOSAshGrowthCampaigns_";
}

std::string GetEventName(CampaignEvent event, std::string_view id) {
  switch (event) {
    case CampaignEvent::kImpression:
      return base::StrCat({"Campaign", id, "_Impression"});
    case CampaignEvent::kDismissed:
      return base::StrCat({"Campaign", id, "_Dismissed"});
    case CampaignEvent::kAppOpened:
      // TODO: b/342282901 - Migrate `CampaignEvent::kAppOpened` to
      // `CampaignEvent::kEvent`, which can be used instead for similar case.
      return base::StrCat({"AppOpened_AppId_", id});
    case CampaignEvent::kEvent:
      return base::StrCat({"Event_", id});
    case CampaignEvent::kGroupImpression:
      return base::StrCat({"Group", id, "_Impression"});
    case CampaignEvent::kGroupDismissed:
      return base::StrCat({"Group", id, "_Dismissed"});
  }
  NOTREACHED();
}

// KibaOS ships no Google web apps, so campaigns trigger on explicit app ids,
// plain app-opened events and event names only; no app belongs to a group.
std::string_view GetAppGroupId(std::string_view /*app_id*/) {
  return {};
}

std::string_view GetAppGroupId(const GURL& /*url*/) {
  return {};
}

std::map<std::string, std::string> CreateBasicConditionParams() {
  std::map<std::string, std::string> conditions_params;
  // `event_used` and `event_trigger` are required for feature_engagement
  // config, although they are not used in campaign matching.
  static constexpr char kTemplate[] =
      "name:ChromeOSAshGrowthCampaigns_Event%s;comparator:any;window:1;storage:"
      "1";
  conditions_params["event_used"] = base::StringPrintf(kTemplate, "Used");
  conditions_params["event_trigger"] = base::StringPrintf(kTemplate, "Trigger");

  return conditions_params;
}

std::string CreateConditionParamForCap(base::cstring_view campaign_type,
                                       int id,
                                       base::cstring_view event_type,
                                       int cap) {
  return base::StringPrintf(
      "name:ChromeOSAshGrowthCampaigns_%s%d_%s;comparator:<%d;window:3650;"
      "storage:3650",
      campaign_type.c_str(), id, event_type.c_str(), cap);
}

int GetHistogramMaxCampaignId(int campaign_id) {
  // `campaign_id` starts at 0.
  return (campaign_id / kCampaignsCountPerHistogram + 1) *
         kCampaignsCountPerHistogram;
}

std::string ToString(bool value) {
  return value ? "true" : "false";
}

}  // namespace growth
