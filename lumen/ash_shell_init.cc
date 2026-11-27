// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "lumen/ash_shell_init.h"

#include <memory>
#include <utility>

#include "ash/keyboard/ui/test/test_keyboard_ui_factory.h"
#include "ash/shell.h"
#include "ash/shell_init_params.h"
#include "base/check.h"
#include "base/command_line.h"
#include "base/logging.h"
#include "base/run_loop.h"
#include "lumen/kibaos_shell_glue.h"
#include "ui/compositor/test/test_context_factories.h"
#include "ui/display/manager/test/fake_display_delegate.h"

namespace kibaos {

namespace {

constexpr char kEnablePixelOutputSwitch[] = "lumen-enable-pixel-output";

}  // namespace

AshShellInit::AshShellInit() = default;

AshShellInit::~AshShellInit() {
  Shutdown();
}

bool AshShellInit::Init(ShellGlue* glue) {
  CHECK(glue);
  CHECK(!initialised_) << "AshShellInit::Init() called more than once";

  glue_ = glue;

  // Set up an in-process compositor context. Lumen does not include the
  // content/ layer, so we reuse the test compositor infrastructure as an
  // interim headless/off-device graphics transport.
  // TODO(b/123456789): Replace with a production KibaOS compositor transport.
  const bool enable_pixel_output =
      base::CommandLine::ForCurrentProcess()->HasSwitch(
          kEnablePixelOutputSwitch);
  context_factories_ =
      std::make_unique<ui::TestContextFactories>(enable_pixel_output);

  // Virtual keyboard UI factory. Required by ash::Shell::Init().
  keyboard_ui_factory_ = std::make_unique<keyboard::TestKeyboardUIFactory>(
      /*input_method=*/nullptr);

  // Fake display delegate provides a simulated display for off-device runs.
  display_delegate_ = std::make_unique<display::FakeDisplayDelegate>();

  ash::ShellInitParams shell_init_params;
  shell_init_params.delegate = glue_->TakeShellDelegate();
  shell_init_params.context_factory = context_factories_->GetContextFactory();
  shell_init_params.keyboard_ui_factory = std::move(keyboard_ui_factory_);
  shell_init_params.native_display_delegate = std::move(display_delegate_);

  LOG(INFO) << "Creating Ash shell...";
  ash::Shell::CreateInstance(std::move(shell_init_params));

  initialised_ = true;
  LOG(INFO) << "Ash shell created and initialised.";
  return true;
}

int AshShellInit::Run() {
  CHECK(initialised_) << "AshShellInit::Run() called before Init()";
  CHECK(!run_loop_) << "AshShellInit::Run() called more than once";

  LOG(INFO) << "Running Ash shell message loop.";
  run_loop_ = std::make_unique<base::RunLoop>();
  run_loop_->Run();
  run_loop_.reset();

  LOG(INFO) << "Ash shell message loop exited with code " << exit_code_;
  return exit_code_;
}

void AshShellInit::Quit(int exit_code) {
  exit_code_ = exit_code;
  if (run_loop_) {
    run_loop_->Quit();
  }
}

void AshShellInit::Shutdown() {
  if (!initialised_) {
    return;
  }

  if (run_loop_) {
    Quit(/*exit_code=*/0);
  }

  LOG(INFO) << "Shutting down Ash shell...";
  ash::Shell::DeleteInstance();

  context_factories_.reset();
  keyboard_ui_factory_.reset();
  display_delegate_.reset();
  glue_ = nullptr;
  initialised_ = false;
  LOG(INFO) << "Ash shell shut down.";
}

}  // namespace kibaos
