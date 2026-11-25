#ifndef LUMEN_LUMEN_SHELL_DELEGATE_H_
#define LUMEN_LUMEN_SHELL_DELEGATE_H_

#include "ash/shell_delegate.h"

namespace ash {

// Minimal ShellDelegate. Delegates return nullptr, and other methods
// return safe defaults. Shell code that dereferences a nullptr delegate
// will crash at runtime. Replace those first.
class LumenShellDelegate : public ShellDelegate {
 public:
  LumenShellDelegate() = default;
  ~LumenShellDelegate() override = default;

  bool CanShowWindowForUser(const aura::Window*) const override { return true; }

  std::unique_ptr<CaptureModeDelegate> CreateCaptureModeDelegate(
      PrefService*) const override {
    return nullptr;
  }
  std::unique_ptr<ClipboardHistoryControllerDelegate>
  CreateClipboardHistoryControllerDelegate() const override {
    return nullptr;
  }
  std::unique_ptr<ClipboardImageModelFactory>
  CreateClipboardImageModelFactory() const override {
    return nullptr;
  }
  std::unique_ptr<CoralDelegate> CreateCoralDelegate() const override {
    return nullptr;
  }
  std::unique_ptr<GameDashboardDelegate> CreateGameDashboardDelegate()
      const override {
    return nullptr;
  }
  std::unique_ptr<AcceleratorPrefsDelegate> CreateAcceleratorPrefsDelegate()
      const override {
    return nullptr;
  }
  AccessibilityDelegate* CreateAccessibilityDelegate() override {
    return nullptr;
  }
  std::unique_ptr<BackGestureContextualNudgeDelegate>
  CreateBackGestureContextualNudgeDelegate(
      BackGestureContextualNudgeController*) override {
    return nullptr;
  }
  std::unique_ptr<MediaNotificationProvider> CreateMediaNotificationProvider()
      override {
    return nullptr;
  }
  std::unique_ptr<NearbyShareDelegate> CreateNearbyShareDelegate(
      NearbyShareController*) const override {
    return nullptr;
  }
  std::unique_ptr<SavedDeskDelegate> CreateSavedDeskDelegate() const override {
    return nullptr;
  }
  std::unique_ptr<api::TasksDelegate> CreateTasksDelegate() const override {
    return nullptr;
  }
  std::unique_ptr<TabStripDelegate> CreateTabStripDelegate() const override {
    return nullptr;
  }
  std::unique_ptr<FocusModeDelegate> CreateFocusModeDelegate() const override {
    return nullptr;
  }
  std::unique_ptr<SystemSoundsDelegate> CreateSystemSoundsDelegate()
      const override {
    return nullptr;
  }
  std::unique_ptr<UserEducationDelegate> CreateUserEducationDelegate()
      const override {
    return nullptr;
  }
  std::unique_ptr<ScannerDelegate> CreateScannerDelegate() const override {
    return nullptr;
  }

  scoped_refptr<network::SharedURLLoaderFactory>
  GetBrowserProcessUrlLoaderFactory() const override {
    return nullptr;
  }
  bool CanGoBack(gfx::NativeWindow) const override { return false; }
  void SetTabScrubberEnabled(bool) override {}
  int GetBrowserWebUITabStripHeight() override { return 0; }

  void BindMultiDeviceSetup(
      mojo::PendingReceiver<multidevice_setup::mojom::MultiDeviceSetup>)
      override {}

  bool IsSessionRestoreInProgress() const override { return false; }
  void SetUpEnvironmentForLockedFullscreen(const WindowState&) override {}
  bool IsLoggingRedirectDisabled() const override { return false; }
  base::FilePath GetPrimaryUserDownloadsFolder() const override {
    return base::FilePath();
  }
  void OpenFeedbackDialog(FeedbackSource, const std::string&,
                          const std::string&) override {}
  bool SendSpecializedFeatureFeedback(const AccountId&, int, std::string,
                                      std::optional<std::string>,
                                      std::optional<std::string>) override {
    return false;
  }
  void OpenProfileManager() override {}
  version_info::Channel GetChannel() override {
    return version_info::Channel::UNKNOWN;
  }
  void ForceSkipWarningUserOnClose(
      const std::vector<raw_ptr<aura::Window, VectorExperimental>>&) override {}
  std::string GetVersionString() override { return "0.0.0"; }
  void OpenMultitaskingSettings() override {}
};

}  // namespace ash

#endif  // LUMEN_LUMEN_SHELL_DELEGATE_H_
