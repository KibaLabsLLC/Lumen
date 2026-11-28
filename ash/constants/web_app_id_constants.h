// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_CONSTANTS_WEB_APP_ID_CONSTANTS_H_
#define ASH_CONSTANTS_WEB_APP_ID_CONSTANTS_H_

namespace ash {

// The URLs used to generate the app IDs MUST match the start_url field of the
// manifest served by the PWA.
// Please maintain the alphabetical order when adding new app IDs.
//
// KibaOS ships only first-party system apps; the Google web apps that upstream
// Chromium pins (Gmail, Google Drive, Google Docs, YouTube, ...) are not part
// of the OS and have no app IDs here.

// Generated as: web_app::GenerateAppId(/*manifest_id=*/"/", GURL(
//     "https://new.express.adobe.com/"))
inline constexpr char kAdobeExpressAppId[] = "jbgdhngddinepfilfcmbcioimbgcolma";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "https://calculator.apps.chrome/"))
inline constexpr char kCalculatorAppId[] = "oabkinaljpjeilageghcdlnekhphhphl";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://camera-app/views/main.html"))
inline constexpr char kCameraAppId[] = "njfbnohfdkmbmnjapinfcopialeghnmh";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "https://canvas.apps.chrome/"))
inline constexpr char kCanvasAppId[] = "ieailfmhaghpphfffooibmlghaeopach";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome-untrusted://crosh/"))
inline constexpr char kCroshAppId[] = "cgfnfgkafmcdkdgilmojlnaadileaach";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "https://cursive.apps.chrome/"))
inline constexpr char kCursiveAppId[] = "apignacaigpffemhdbhmnajajaccbckh";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt,
// GURL("chrome://diagnostics/"))
inline constexpr char kDiagnosticsAppId[] = "keejpcfcpecjhmepmpcfgjemkmlicpam";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt,
// GURL("chrome://accessory-update/"))
inline constexpr char kFirmwareUpdateAppId[] =
    "nedcdcceagjbkiaecmdbpafcmlhkiifa";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://graduation/"))
inline constexpr char kGraduationAppId[] = "dcmgllglecpogfcjmdkdncendnjphdcd";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://help-app/"))
inline constexpr char kHelpAppId[] = "nbljnnecbjbmifnoehiemkgefbnpoeak";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://media-app/"))
inline constexpr char kMediaAppId[] = "jhdjimmaggjajfjphpljagpgkidjilnj";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "https://www.microsoft365.com/?from=Homescreen"))
inline constexpr char kMicrosoft365AppId[] = "onhfoihkhodaeblmangmjjgfpfehnlkm";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://test-system-app/pwa.html"))
inline constexpr char kMockSystemAppId[] = "maphiehpiinjgiaepbljmopkodkadcbh";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://os-feedback/"))
inline constexpr char kOsFeedbackAppId[] = "iffgohomcomlpmkfikfffagkkoojjffm";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://os-settings/"))
inline constexpr char kOsSettingsAppId[] = "odknhmnlageboeamepcngndbggdpaobj";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://personalization/"))
inline constexpr char kPersonalizationAppId[] =
    "glenkcidjgckcomnliblmkokolehpckn";

// Generated as:web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//      "chrome://print-management/"))
inline constexpr char kPrintManagementAppId[] =
    "fglkccnmnaankjodgccmiodmlkpaiodc";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome-untrusted://projector/"))
// LINT.IfChange
inline constexpr char kChromeUIUntrustedProjectorSwaAppId[] =
    "hohmppfoilmflgicnofelkdablfahbnl";

// Also update the Projector app id in the file below.
// LINT.ThenChange(
// src/platform/tast-tests/src/chromiumos/tast/local/apps/apps.go)
inline constexpr char kChromeUIUntrustedProjectorPwaUrl[] =
    "https://screencast.apps.chrome";

// Generated as:web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//      "chrome://recorder-app/"))
inline constexpr char kRecorderAppId[] = "aegafoechlhchmknlbhmofidaodfkhhk";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt,
// GURL("chrome://sanitize/"))
inline constexpr char kSanitizeAppId[] = "kochjemhjheifpfhkppkameonoheenjk";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt,
// GURL("chrome://scanning/"))
inline constexpr char kScanningAppId[] = "cdkahakpgkdaoffdmfgnhgomkelkocfo";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://settings/"))
inline constexpr char kSettingsAppId[] = "inogagmajamaleonmanpkpkkigmklfad";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://shortcut-customization"))
inline constexpr char kShortcutCustomizationAppId[] =
    "ihgeegogifolehadhdgelgcnbnmemikp";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://shimless-rma/"))
inline constexpr char kShimlessRMAAppId[] = "ijolhdommgkkhpenofmpkkhlepahelcm";

// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "https://www.showtime.com/"))
inline constexpr char kShowtimeAppId[] = "eoccpgmpiempcflglfokeengliildkag";

#if !defined(OFFICIAL_BUILD)
// Generated as: web_app::GenerateAppId(/*manifest_id=*/std::nullopt, GURL(
//     "chrome://sample-system-web-app"))
inline constexpr char kSampleSystemWebAppId[] =
    "jalmdcokfklmaoadompgacjlcomfckcf";
#endif  // !OFFICIAL_BUILD

// Generated as: web_app::GenerateAppId(/*manifest_id=*/"", GURL(
//     "chrome://password-manager/?source=pwa"))
inline constexpr char kPasswordManagerAppId[] =
    "kajebgjangihfbkjfejcanhanjmmbcfd";

}  // namespace ash

#endif  // ASH_CONSTANTS_WEB_APP_ID_CONSTANTS_H_
