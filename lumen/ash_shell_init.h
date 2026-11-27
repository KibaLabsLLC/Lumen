// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LUMEN_ASH_SHELL_INIT_H_
#define LUMEN_ASH_SHELL_INIT_H_

// AshShellInit owns the lifetime of the Ash shell for the Lumen executable.
// It bridges the KibaOS ShellGlue layer to ash::Shell by creating the
// ShellInitParams, starting Ash, running the UI message loop, and tearing
// everything down on exit.
//
// TODO(b/123456789): Replace the test compositor and fake display delegates
// with production KibaOS graphics/display transports once they exist.

#include <memory>

#include "base/memory/raw_ptr.h"

namespace base {
class RunLoop;
}

namespace display {
class FakeDisplayDelegate;
}

namespace keyboard {
class TestKeyboardUIFactory;
}

namespace ui {
class TestContextFactories;
}

namespace kibaos {

class ShellGlue;

class AshShellInit {
 public:
  AshShellInit();
  ~AshShellInit();

  AshShellInit(const AshShellInit&) = delete;
  AshShellInit& operator=(const AshShellInit&) = delete;

  // Creates ash::Shell using the delegate owned by |glue|. Must be called on
  // the UI thread after ShellGlue::Init() has succeeded. Returns true on
  // success.
  bool Init(ShellGlue* glue);

  // Runs the Ash UI message loop until Shutdown() or Quit() is called.
  // Returns the exit code supplied to Quit() or 0 if the loop exits cleanly.
  int Run();

  // Quits the message loop started by Run() with the given |exit_code|.
  void Quit(int exit_code);

  // Destroys ash::Shell and all Ash-owned subsystems. Safe to call more than
  // once and from the destructor.
  void Shutdown();

 private:
  std::unique_ptr<ui::TestContextFactories> context_factories_;
  std::unique_ptr<keyboard::TestKeyboardUIFactory> keyboard_ui_factory_;
  std::unique_ptr<display::FakeDisplayDelegate> display_delegate_;
  std::unique_ptr<base::RunLoop> run_loop_;
  raw_ptr<ShellGlue> glue_ = nullptr;
  bool initialised_ = false;
  int exit_code_ = 0;
};

}  // namespace kibaos

#endif  // LUMEN_ASH_SHELL_INIT_H_
