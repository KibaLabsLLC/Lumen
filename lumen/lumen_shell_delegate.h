// Copyright 2025 The Lumen Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LUMEN_LUMEN_SHELL_DELEGATE_H_
#define LUMEN_LUMEN_SHELL_DELEGATE_H_

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "ash/shell_delegate.h"
#include "base/memory/raw_ptr.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "url/gurl.h"

class AccountId;
class PrefService;

namespace aura {
class Window;
}

namespace ash {

// Lumen's `ShellDelegate`. Every `Create*()` factory returns a minimal
// implementation so the shell starts without an embedded browser: features
// degrade gracefully (empty lists, null child delegates, no-op actions)
// instead of crashing on a null delegate. Browser-backed behavior (tasks,
// nearby share, capture mode upload, etc.) is intentionally inert until a
// browser is wired in.
class LumenShellDelegate : public ShellDelegate {
 public:
  LumenShellDelegate();

  LumenShellDelegate(const LumenShellDelegate&) = delete;
  LumenShellDelegate& operator=(const LumenShellDelegate&) = delete;

  ~LumenShellDelegate() override;

  // ShellDelegate:
  std::unique_ptr<CaptureModeDelegate> CreateCaptureModeDelegate(
      PrefService* local_state) const override;
  std::unique_ptr<ClipboardHistoryControllerDelegate>
  CreateClipboardHistoryControllerDelegate() const override;
  std::unique_ptr<ClipboardImageModelFactory> CreateClipboardImageModelFactory()
      const override;
  std::unique_ptr<CoralDelegate> CreateCoralDelegate() const override;
  std::unique_ptr<GameDashboardDelegate> CreateGameDashboardDelegate()
      const override;
  std::unique_ptr<AcceleratorPrefsDelegate> CreateAcceleratorPrefsDelegate()
      const override;
  AccessibilityDelegate* CreateAccessibilityDelegate() override;
  std::unique_ptr<BackGestureContextualNudgeDelegate>
  CreateBackGestureContextualNudgeDelegate(
      BackGestureContextualNudgeController* controller) override;
  std::unique_ptr<MediaNotificationProvider> CreateMediaNotificationProvider()
      override;
  std::unique_ptr<NearbyShareDelegate> CreateNearbyShareDelegate(
      NearbyShareController* controller) const override;
  std::unique_ptr<SavedDeskDelegate> CreateSavedDeskDelegate() const override;
  std::unique_ptr<SystemSoundsDelegate> CreateSystemSoundsDelegate()
      const override;
  std::unique_ptr<api::TasksDelegate> CreateTasksDelegate() const override;
  std::unique_ptr<TabStripDelegate> CreateTabStripDelegate() const override;
  std::unique_ptr<FocusModeDelegate> CreateFocusModeDelegate() const override;
  std::unique_ptr<UserEducationDelegate> CreateUserEducationDelegate()
      const override;
  std::unique_ptr<ScannerDelegate> CreateScannerDelegate() const override;

  scoped_refptr<network::SharedURLLoaderFactory>
  GetBrowserProcessUrlLoaderFactory() override;
  bool CanGoBack(gfx::NativeWindow window) const override;
  void SetTabScrubberEnabled(bool enabled) override;

  void BindMultiDeviceSetup(
      mojo::PendingReceiver<multidevice_setup::mojom::MultiDeviceSetup>
          receiver) override;

  bool IsSessionRestoreInProgress() const override;
  void SetUpEnvironmentForLockedFullscreen(
      const WindowState& window_state) override;
  bool IsLoggingRedirectDisabled() const override;
  base::FilePath GetPrimaryUserDownloadsFolder() const override;
  base::FilePath CrackFileSystemUrl(const GURL& file_system_url) const override;
  void OpenFeedbackDialog(FeedbackSource source,
                          const std::string& description_template,
                          const std::string& category_tag) override;
  bool SendSpecializedFeatureFeedback(
      const AccountId& account_id,
      int product_id,
      std::string description,
      std::optional<std::string> image,
      std::optional<std::string> image_mime_type) override;
  void OpenProfileManager() override;
  version_info::Channel GetChannel() override;
  void ForceSkipWarningUserOnClose(
      const std::vector<raw_ptr<aura::Window, DanglingUntriaged>>& windows)
      override;
  std::string GetVersionString() override;
  void OpenMultitaskingSettings() override;
};

}  // namespace ash

#endif  // LUMEN_LUMEN_SHELL_DELEGATE_H_
