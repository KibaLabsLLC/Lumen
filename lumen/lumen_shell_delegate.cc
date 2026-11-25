// Copyright 2025 The Lumen Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "lumen/lumen_shell_delegate.h"

#include <utility>

#include "ash/api/tasks/tasks_client.h"
#include "ash/api/tasks/tasks_delegate.h"
#include "ash/capture_mode/capture_mode_metrics.h"
#include "ash/public/cpp/capture_mode/capture_mode_delegate.h"
#include "ash/public/cpp/clipboard_image_model_factory.h"
#include "ash/public/cpp/coral_delegate.h"
#include "ash/public/cpp/nearby_share_delegate.h"
#include "ash/public/cpp/scanner/scanner_delegate.h"
#include "ash/public/cpp/scanner/scanner_feedback_info.h"
#include "ash/public/cpp/tab_strip_delegate.h"
#include "ash/system/media/media_notification_provider.h"
#include "ash/system/video_conference/video_conference_common.h"
#include "base/files/file_path.h"
#include "base/functional/callback.h"
#include "base/time/time.h"
#include "chromeos/ash/components/audio/system_sounds_delegate.h"
#include "chromeos/ash/services/coral/public/mojom/coral_service.mojom.h"
#include "chromeos/ash/services/nearby/public/mojom/nearby_share_settings.mojom.h"
#include "components/account_id/account_id.h"
#include "components/user_education/common/tutorial/tutorial_description.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "services/metrics/public/cpp/ukm_source_id.h"
#include "ui/base/interaction/element_identifier.h"
#include "ui/base/models/image_model.h"
#include "ui/gfx/vector_icon_types.h"
#include "ui/views/view.h"
#include "url/gurl.h"

namespace ash {
namespace {

// ---------------------------------------------------------------------------
// Capture Mode.
// ---------------------------------------------------------------------------

class LumenCaptureModeDelegate : public CaptureModeDelegate {
 public:
  LumenCaptureModeDelegate() = default;
  ~LumenCaptureModeDelegate() override = default;

  base::FilePath GetUserDefaultDownloadsFolder() const override {
    return base::FilePath();
  }
  void OpenScreenCaptureItem(const base::FilePath& file_path) override {}
  void OpenScreenshotInImageEditor(const base::FilePath& file_path) override {}
  bool Uses24HourFormat() const override { return false; }

  void CheckCaptureModeInitRestrictionByDlp(
      bool shutting_down,
      OnCaptureModeDlpRestrictionChecked callback) override {
    std::move(callback).Run(/*proceed=*/true);
  }
  void CheckCaptureOperationRestrictionByDlp(
      const aura::Window* window,
      const gfx::Rect& bounds,
      OnCaptureModeDlpRestrictionChecked callback) override {
    std::move(callback).Run(/*proceed=*/true);
  }
  bool IsCaptureAllowedByPolicy() const override { return true; }
  bool IsSearchAllowedByPolicy() const override { return false; }

  void StartObservingRestrictedContent(
      const aura::Window* window,
      const gfx::Rect& bounds,
      base::OnceClosure on_area_restricted_callback) override {}
  void StopObservingRestrictedContent(
      OnCaptureModeDlpRestrictionChecked callback) override {
    std::move(callback).Run(/*proceed=*/true);
  }
  void OnCaptureImageAttempted(const aura::Window* window,
                               const gfx::Rect& bounds) override {}

  mojo::Remote<recording::mojom::RecordingService> LaunchRecordingService()
      override {
    return mojo::Remote<recording::mojom::RecordingService>();
  }
  void BindAudioStreamFactory(
      mojo::PendingReceiver<media::mojom::AudioStreamFactory> receiver)
      override {}

  void OnSessionStateChanged(bool started) override {}
  void OnServiceRemoteReset() override {}

  bool GetDriveFsMountPointPath(base::FilePath* path) const override {
    return false;
  }
  base::FilePath GetAndroidFilesPath() const override {
    return base::FilePath();
  }
  base::FilePath GetLinuxFilesPath() const override {
    return base::FilePath();
  }
  base::FilePath GetOneDriveMountPointPath() const override {
    return base::FilePath();
  }
  base::FilePath GetOneDriveVirtualPath() const override {
    return base::FilePath();
  }
  PolicyCapturePath GetPolicyCapturePath() const override { return {}; }

  void ConnectToVideoSourceProvider(
      mojo::PendingReceiver<video_capture::mojom::VideoSourceProvider> receiver)
      override {}
  void GetDriveFsFreeSpaceBytes(OnGotDriveFsFreeSpace callback) override {
    std::move(callback).Run(/*free_remaining_bytes=*/-1);
  }

  bool IsCameraDisabledByPolicy() const override { return false; }
  bool IsAudioCaptureDisabledByPolicy() const override { return false; }

  void RegisterVideoConferenceManagerClient(
      VideoConferenceManagerClient* client,
      const base::UnguessableToken& client_id) override {}
  void UnregisterVideoConferenceManagerClient(
      const base::UnguessableToken& client_id) override {}
  void UpdateVideoConferenceManager(
      VideoConferenceMediaUsageStatus status) override {}
  void NotifyDeviceUsedWhileDisabled(VideoConferenceMediaDevice device)
      override {}

  void FinalizeSavedFile(
      base::OnceCallback<void(bool, const base::FilePath&)> callback,
      const base::FilePath& path,
      const gfx::Image& thumbnail,
      bool for_video) override {
    std::move(callback).Run(/*success=*/false, path);
  }
  base::FilePath RedirectFilePath(const base::FilePath& path) override {
    return path;
  }

  std::unique_ptr<AshWebView> CreateSearchResultsView() const override {
    return nullptr;
  }

  void DetectTextInImage(const SkBitmap& image,
                         OnTextDetectionComplete callback) override {
    std::move(callback).Run(std::string());
  }

  void SendLensWebRegionSearch(
      const gfx::Image& image,
      const bool is_standalone_session,
      const AccountId& account_id,
      OnSearchUrlFetchedCallback search_callback,
      OnTextDetectionComplete text_callback,
      OnLensErrorCallback error_callback) override {
    std::move(error_callback)
        .Run(CaptureModeImageSearchResult::kFailureUnsuccessfulStatusCode,
             CaptureModeTextDetectionResult::kUnreached);
  }

  bool IsNetworkConnectionOffline() const override { return false; }

  void DeleteRemoteFile(const base::FilePath& path,
                        base::OnceCallback<void(bool)> callback) override {
    std::move(callback).Run(/*success=*/true);
  }
  bool ActiveUserDefaultSearchProviderIsGoogle() const override {
    return false;
  }
};

// ---------------------------------------------------------------------------
// Clipboard.
// ---------------------------------------------------------------------------

class LumenClipboardHistoryControllerDelegate
    : public ClipboardHistoryControllerDelegate {
 public:
  LumenClipboardHistoryControllerDelegate() = default;
  ~LumenClipboardHistoryControllerDelegate() override = default;

  bool Paste() const override { return false; }
};

class LumenClipboardImageModelFactory : public ClipboardImageModelFactory {
 public:
  LumenClipboardImageModelFactory() = default;
  ~LumenClipboardImageModelFactory() override = default;

  void Render(const base::UnguessableToken& id,
              const std::string& html_markup,
              const gfx::Size& bounding_box_size,
              const std::optional<ui::DataTransferEndpoint>& data_src,
              ImageModelCallback callback) override {
    std::move(callback).Run(ui::ImageModel());
  }
  void CancelRequest(const base::UnguessableToken& id) override {}
  void CancelAllRequests() override {}
  void Activate() override {}
  void Deactivate() override {}
  void RenderCurrentPendingRequests() override {}
  void OnShutdown() override {}
};

// ---------------------------------------------------------------------------
// Coral.
// ---------------------------------------------------------------------------

class LumenCoralDelegate : public CoralDelegate {
 public:
  LumenCoralDelegate() = default;
  ~LumenCoralDelegate() override = default;

  void LaunchPostLoginGroup(coral::mojom::GroupPtr group) override {}
  void MoveTabsInGroupToNewDesk(const std::vector<coral::mojom::Tab>& tabs,
                                size_t src_desk_index) override {}
  int GetChromeDefaultRestoreId() override { return 0; }
  void OpenFeedbackDialog(
      const std::string& group_description,
      ScannerDelegate::SendFeedbackCallback send_feedback_callback) override {}
  bool GetGenAILocationAvailability() override { return false; }
  std::string GetSystemLanguage() override { return "en"; }
};

// ---------------------------------------------------------------------------
// Game Dashboard.
// ---------------------------------------------------------------------------

class LumenGameDashboardDelegate : public GameDashboardDelegate {
 public:
  LumenGameDashboardDelegate() = default;
  ~LumenGameDashboardDelegate() override = default;

  void GetIsGame(const std::string& app_id, IsGameCallback callback) override {
    std::move(callback).Run(/*is_game=*/false);
  }
  std::string GetArcAppName(const std::string& app_id) const override {
    return std::string();
  }
  void RecordGameWindowOpenedEvent(aura::Window* window) override {}
  void ShowResizeToggleMenu(aura::Window* window) override {}
  ukm::SourceId GetUkmSourceId(const std::string& app_id) override {
    return ukm::kInvalidSourceId;
  }
};

// ---------------------------------------------------------------------------
// Accelerators.
// ---------------------------------------------------------------------------

class LumenAcceleratorPrefsDelegate : public AcceleratorPrefsDelegate {
 public:
  LumenAcceleratorPrefsDelegate() = default;
  ~LumenAcceleratorPrefsDelegate() override = default;

  bool IsUserEnterpriseManaged() const override { return false; }
};

// ---------------------------------------------------------------------------
// Accessibility.
// ---------------------------------------------------------------------------

class LumenAccessibilityDelegate : public AccessibilityDelegate {
 public:
  LumenAccessibilityDelegate() = default;
  ~LumenAccessibilityDelegate() override = default;

  void SetMagnifierEnabled(bool enabled) override {}
  bool IsMagnifierEnabled() const override { return false; }
  bool ShouldShowAccessibilityMenu() const override { return false; }
  void SaveScreenMagnifierScale(double scale) override {}
  double GetSavedScreenMagnifierScale() override { return -1.0; }
  std::unique_ptr<AccessibilityPrefsCustomAssociator>
  CreatePrefsCustomAssociator(PrefService* pref_service) override {
    return nullptr;
  }
};

// ---------------------------------------------------------------------------
// Back gesture nudge.
// ---------------------------------------------------------------------------

class LumenBackGestureContextualNudgeDelegate
    : public BackGestureContextualNudgeDelegate {
 public:
  LumenBackGestureContextualNudgeDelegate() = default;
  ~LumenBackGestureContextualNudgeDelegate() override = default;

  void MaybeStartTrackingNavigation(aura::Window* window) override {}
};

// ---------------------------------------------------------------------------
// Media notifications.
// ---------------------------------------------------------------------------

class LumenMediaNotificationProvider : public MediaNotificationProvider {
 public:
  LumenMediaNotificationProvider() = default;
  ~LumenMediaNotificationProvider() override = default;

  void AddObserver(MediaNotificationProviderObserver* observer) override {}
  void RemoveObserver(MediaNotificationProviderObserver* observer) override {}

  bool HasActiveNotifications() override { return false; }
  bool HasFrozenNotifications() override { return false; }

  std::unique_ptr<views::View> GetMediaNotificationListView(
      int separator_thickness,
      bool should_clip_height,
      global_media_controls::GlobalMediaControlsEntryPoint entry_point,
      const std::string& show_devices_for_item_id = "") override {
    return std::make_unique<views::View>();
  }

  void OnBubbleClosing() override {}
  global_media_controls::MediaItemManager* GetMediaItemManager() override {
    return nullptr;
  }

  std::unique_ptr<global_media_controls::MediaItemUIDeviceSelector>
  BuildDeviceSelectorView(
      const std::string& id,
      base::WeakPtr<media_message_center::MediaNotificationItem> item,
      global_media_controls::GlobalMediaControlsEntryPoint entry_point,
      bool show_devices = false) override {
    return nullptr;
  }
  std::unique_ptr<global_media_controls::MediaItemUIFooter> BuildFooterView(
      const std::string& id,
      base::WeakPtr<media_message_center::MediaNotificationItem> item)
      override {
    return nullptr;
  }
  void UpdateMediaItemSourceOrigin(
      const std::string& id,
      const std::optional<url::Origin>& origin) override {}
};

// ---------------------------------------------------------------------------
// Nearby Share.
// ---------------------------------------------------------------------------

class LumenNearbyShareDelegate : public NearbyShareDelegate {
 public:
  LumenNearbyShareDelegate() = default;
  ~LumenNearbyShareDelegate() override = default;

  bool IsEnabled() override { return false; }
  void SetEnabled(bool enabled) override {}
  bool IsPodButtonVisible() override { return false; }
  bool IsHighVisibilityOn() override { return false; }
  bool IsOnboardingComplete() override { return false; }
  bool IsEnableHighVisibilityRequestActive() const override { return false; }
  base::TimeTicks HighVisibilityShutoffTime() const override {
    return base::TimeTicks();
  }
  void EnableHighVisibility() override {}
  void DisableHighVisibility() override {}
  void ShowNearbyShareSettings() const override {}
  void ShowOnboardingPage() const override {}
  const gfx::VectorIcon& GetIcon(bool on_icon) const override {
    return gfx::VectorIcon::EmptyIcon();
  }
  std::u16string GetPlaceholderFeatureName() const override {
    return std::u16string();
  }
  ::nearby_share::mojom::Visibility GetVisibility() const override {
    return ::nearby_share::mojom::Visibility::kUnknown;
  }
  void SetVisibility(::nearby_share::mojom::Visibility visibility) override {}
};

// ---------------------------------------------------------------------------
// Saved desks.
// ---------------------------------------------------------------------------

class LumenSavedDeskDelegate : public SavedDeskDelegate {
 public:
  LumenSavedDeskDelegate() = default;
  ~LumenSavedDeskDelegate() override = default;

  void GetAppLaunchDataForSavedDesk(
      aura::Window* window,
      GetAppLaunchDataCallback callback) const override {
    std::move(callback).Run(nullptr);
  }
  desks_storage::DeskModel* GetDeskModel() override { return nullptr; }
  desks_storage::AdminTemplateService* GetAdminTemplateService() override {
    return nullptr;
  }
  bool IsWindowPersistable(aura::Window* window) const override {
    return false;
  }
  std::optional<gfx::ImageSkia> MaybeRetrieveIconForSpecialIdentifier(
      const std::string& icon_identifier,
      const ui::ColorProvider* color_provider) const override {
    return std::nullopt;
  }
  void GetIconForAppId(
      const std::string& app_id,
      int desired_icon_size,
      base::OnceCallback<void(const gfx::ImageSkia&)> callback) const override {
  }
  void LaunchAppsFromSavedDesk(
      std::unique_ptr<DeskTemplate> saved_desk) override {}
  bool IsWindowSupportedForSavedDesk(aura::Window* window) const override {
    return false;
  }
  std::string GetAppShortName(const std::string& app_id) override {
    return std::string();
  }
  bool IsAppAvailable(const std::string& app_id) const override {
    return false;
  }
};

// ---------------------------------------------------------------------------
// Tasks.
// ---------------------------------------------------------------------------

class LumenTasksDelegate : public api::TasksDelegate {
 public:
  LumenTasksDelegate() = default;
  ~LumenTasksDelegate() override = default;

  void UpdateClientForProfileSwitch(const AccountId& account_id) override {}

  void GetTaskLists(bool force_fetch,
                    api::TasksClient::GetTaskListsCallback callback) override {
    std::move(callback).Run(/*success=*/false, google_apis::OTHER_ERROR,
                            /*task_lists=*/nullptr);
  }
  void GetTasks(const std::string& task_list_id,
                bool force_fetch,
                api::TasksClient::GetTasksCallback callback) override {
    std::move(callback).Run(/*success=*/false, google_apis::OTHER_ERROR,
                            /*tasks=*/nullptr);
  }
  void AddTask(const std::string& task_list_id,
               const std::string& title,
               api::TasksClient::OnTaskSavedCallback callback) override {
    std::move(callback).Run(google_apis::OTHER_ERROR, /*task=*/nullptr);
  }
  void UpdateTask(const std::string& task_list_id,
                  const std::string& task_id,
                  const std::string& title,
                  bool completed,
                  api::TasksClient::OnTaskSavedCallback callback) override {
    std::move(callback).Run(google_apis::OTHER_ERROR, /*task=*/nullptr);
  }
};

// ---------------------------------------------------------------------------
// Tab strip.
// ---------------------------------------------------------------------------

class LumenTabStripDelegate : public TabStripDelegate {
 public:
  LumenTabStripDelegate() = default;
  ~LumenTabStripDelegate() override = default;

  std::vector<TabInfo> GetTabsListForWindow(
      aura::Window* window) const override {
    return {};
  }
};

// ---------------------------------------------------------------------------
// Focus Mode.
// ---------------------------------------------------------------------------

class LumenFocusModeDelegate : public FocusModeDelegate {
 public:
  LumenFocusModeDelegate() = default;
  ~LumenFocusModeDelegate() override = default;

  std::unique_ptr<youtube_music::YouTubeMusicClient> CreateYouTubeMusicClient(
      const AccountId& account_id,
      const std::string& device_id) override {
    return nullptr;
  }
  const std::string& GetLocale() override { return locale_; }
  bool IsMinorUser() override { return false; }

 private:
  const std::string locale_ = "en-US";
};

// ---------------------------------------------------------------------------
// System sounds.
// ---------------------------------------------------------------------------

class LumenSystemSoundsDelegate : public SystemSoundsDelegate {
 public:
  LumenSystemSoundsDelegate() = default;
  ~LumenSystemSoundsDelegate() override = default;

  void Init() override {}
  void Play(Sound sound_key) override {}
};

// ---------------------------------------------------------------------------
// User education.
// ---------------------------------------------------------------------------

class LumenUserEducationDelegate : public UserEducationDelegate {
 public:
  LumenUserEducationDelegate() = default;
  ~LumenUserEducationDelegate() override = default;

  std::optional<ui::ElementIdentifier> GetElementIdentifierForAppId(
      const std::string& app_id) const override {
    return std::nullopt;
  }
  const std::optional<bool>& IsNewUser(
      const AccountId& account_id) const override {
    return new_user_;
  }
  bool IsTutorialRegistered(const AccountId& account_id,
                            TutorialId tutorial_id) const override {
    return false;
  }
  void RegisterTutorial(
      const AccountId& account_id,
      TutorialId tutorial_id,
      user_education::TutorialDescription tutorial_description) override {}
  void StartTutorial(const AccountId& account_id,
                     TutorialId tutorial_id,
                     ui::ElementContext element_context,
                     base::OnceClosure completed_callback,
                     base::OnceClosure aborted_callback) override {
    std::move(aborted_callback).Run();
  }
  void AbortTutorial(const AccountId& account_id,
                     std::optional<TutorialId> tutorial_id) override {}
  void LaunchSystemWebAppAsync(const AccountId& account_id,
                               SystemWebAppType system_web_app_type,
                               apps::LaunchSource launch_source,
                               int64_t display_id) override {}
  bool IsRunningTutorial(const AccountId& account_id,
                         std::optional<TutorialId> tutorial_id) const override {
    return false;
  }

 private:
  std::optional<bool> new_user_;
};

// ---------------------------------------------------------------------------
// Scanner.
// ---------------------------------------------------------------------------

class LumenScannerDelegate : public ScannerDelegate {
 public:
  LumenScannerDelegate() = default;
  ~LumenScannerDelegate() override = default;

  ScannerProfileScopedDelegate* GetProfileScopedDelegate() override {
    return nullptr;
  }
  void OpenFeedbackDialog(
      const AccountId& account_id,
      ScannerFeedbackInfo feedback_info,
      SendFeedbackCallback send_feedback_callback) override {}
};

}  // namespace

// ---------------------------------------------------------------------------
// LumenShellDelegate.
// ---------------------------------------------------------------------------

LumenShellDelegate::LumenShellDelegate() = default;

LumenShellDelegate::~LumenShellDelegate() = default;

std::unique_ptr<CaptureModeDelegate>
LumenShellDelegate::CreateCaptureModeDelegate(PrefService* local_state) const {
  return std::make_unique<LumenCaptureModeDelegate>();
}

std::unique_ptr<ClipboardHistoryControllerDelegate>
LumenShellDelegate::CreateClipboardHistoryControllerDelegate() const {
  return std::make_unique<LumenClipboardHistoryControllerDelegate>();
}

std::unique_ptr<ClipboardImageModelFactory>
LumenShellDelegate::CreateClipboardImageModelFactory() const {
  return std::make_unique<LumenClipboardImageModelFactory>();
}

std::unique_ptr<CoralDelegate> LumenShellDelegate::CreateCoralDelegate() const {
  return std::make_unique<LumenCoralDelegate>();
}

std::unique_ptr<GameDashboardDelegate>
LumenShellDelegate::CreateGameDashboardDelegate() const {
  return std::make_unique<LumenGameDashboardDelegate>();
}

std::unique_ptr<AcceleratorPrefsDelegate>
LumenShellDelegate::CreateAcceleratorPrefsDelegate() const {
  return std::make_unique<LumenAcceleratorPrefsDelegate>();
}

AccessibilityDelegate* LumenShellDelegate::CreateAccessibilityDelegate() {
  return new LumenAccessibilityDelegate();
}

std::unique_ptr<BackGestureContextualNudgeDelegate>
LumenShellDelegate::CreateBackGestureContextualNudgeDelegate(
    BackGestureContextualNudgeController* controller) {
  return std::make_unique<LumenBackGestureContextualNudgeDelegate>();
}

std::unique_ptr<MediaNotificationProvider>
LumenShellDelegate::CreateMediaNotificationProvider() {
  return std::make_unique<LumenMediaNotificationProvider>();
}

std::unique_ptr<NearbyShareDelegate>
LumenShellDelegate::CreateNearbyShareDelegate(
    NearbyShareController* controller) const {
  return std::make_unique<LumenNearbyShareDelegate>();
}

std::unique_ptr<SavedDeskDelegate> LumenShellDelegate::CreateSavedDeskDelegate()
    const {
  return std::make_unique<LumenSavedDeskDelegate>();
}

std::unique_ptr<SystemSoundsDelegate>
LumenShellDelegate::CreateSystemSoundsDelegate() const {
  return std::make_unique<LumenSystemSoundsDelegate>();
}

std::unique_ptr<api::TasksDelegate> LumenShellDelegate::CreateTasksDelegate()
    const {
  return std::make_unique<LumenTasksDelegate>();
}

std::unique_ptr<TabStripDelegate> LumenShellDelegate::CreateTabStripDelegate()
    const {
  return std::make_unique<LumenTabStripDelegate>();
}

std::unique_ptr<FocusModeDelegate> LumenShellDelegate::CreateFocusModeDelegate()
    const {
  return std::make_unique<LumenFocusModeDelegate>();
}

std::unique_ptr<UserEducationDelegate>
LumenShellDelegate::CreateUserEducationDelegate() const {
  return std::make_unique<LumenUserEducationDelegate>();
}

std::unique_ptr<ScannerDelegate> LumenShellDelegate::CreateScannerDelegate()
    const {
  return std::make_unique<LumenScannerDelegate>();
}

scoped_refptr<network::SharedURLLoaderFactory>
LumenShellDelegate::GetBrowserProcessUrlLoaderFactory() {
  return nullptr;
}

bool LumenShellDelegate::CanGoBack(gfx::NativeWindow window) const {
  return false;
}

void LumenShellDelegate::SetTabScrubberEnabled(bool enabled) {}

void LumenShellDelegate::BindMultiDeviceSetup(
    mojo::PendingReceiver<multidevice_setup::mojom::MultiDeviceSetup>
        receiver) {}

bool LumenShellDelegate::IsSessionRestoreInProgress() const {
  return false;
}

void LumenShellDelegate::SetUpEnvironmentForLockedFullscreen(
    const WindowState& window_state) {}

bool LumenShellDelegate::IsLoggingRedirectDisabled() const {
  return false;
}

base::FilePath LumenShellDelegate::GetPrimaryUserDownloadsFolder() const {
  return base::FilePath();
}

base::FilePath LumenShellDelegate::CrackFileSystemUrl(
    const GURL& file_system_url) const {
  return base::FilePath();
}

void LumenShellDelegate::OpenFeedbackDialog(
    FeedbackSource source,
    const std::string& description_template,
    const std::string& category_tag) {}

bool LumenShellDelegate::SendSpecializedFeatureFeedback(
    const AccountId& account_id,
    int product_id,
    std::string description,
    std::optional<std::string> image,
    std::optional<std::string> image_mime_type) {
  return false;
}

void LumenShellDelegate::OpenProfileManager() {}

version_info::Channel LumenShellDelegate::GetChannel() {
  return version_info::Channel::UNKNOWN;
}

void LumenShellDelegate::ForceSkipWarningUserOnClose(
    const std::vector<raw_ptr<aura::Window, DanglingUntriaged>>& windows) {}

std::string LumenShellDelegate::GetVersionString() {
  return "0.0.0";
}

void LumenShellDelegate::OpenMultitaskingSettings() {}

}  // namespace ash
