// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LUMEN_KIBAOS_SHELL_GLUE_H_
#define LUMEN_KIBAOS_SHELL_GLUE_H_

// KibaOS shell glue: owns the objects that bridge the Ash shell to the
// KibaOS platform layer. Create one instance before ash::Shell::CreateInstance
// and destroy it after ash::Shell::DeleteInstance.
//
// Responsibilities:
//  - Instantiates LumenShellDelegate and passes it to Ash.
//  - Initialises KibaOS path and environment utilities.
//  - Provides typed accessors so other Lumen code doesn't depend on global
//    state.

#include <memory>

namespace ash {
class LumenShellDelegate;
}

namespace kibaos {

class ShellGlue {
 public:
  ShellGlue();
  ~ShellGlue();

  ShellGlue(const ShellGlue&) = delete;
  ShellGlue& operator=(const ShellGlue&) = delete;

  // Initialise the glue layer. Must be called before Ash shell creation.
  // Returns true on success.
  bool Init();

  // Transfer ownership of the shell delegate to the caller (ash::Shell).
  // May only be called once and only after Init().
  std::unique_ptr<ash::LumenShellDelegate> TakeShellDelegate();

 private:
  std::unique_ptr<ash::LumenShellDelegate> shell_delegate_;
  bool initialised_ = false;
};

}  // namespace kibaos

#endif  // LUMEN_KIBAOS_SHELL_GLUE_H_
