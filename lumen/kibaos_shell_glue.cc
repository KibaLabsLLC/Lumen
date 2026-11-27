// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "lumen/kibaos_shell_glue.h"

#include <memory>

#include "base/check.h"
#include "base/logging.h"
#include "lumen/kibaos_environment.h"
#include "lumen/kibaos_paths.h"
#include "lumen/lumen_shell_delegate.h"

namespace kibaos {

ShellGlue::ShellGlue() = default;
ShellGlue::~ShellGlue() = default;

bool ShellGlue::Init() {
  CHECK(!initialised_) << "ShellGlue::Init() called more than once";

  LOG(INFO) << "KibaOS Lumen starting – version: " << GetVersionString();
  LOG(INFO) << "KibaOS runtime root: " << GetRuntimeRoot().value();

  shell_delegate_ = std::make_unique<ash::LumenShellDelegate>();
  initialised_ = true;
  return true;
}

std::unique_ptr<ash::LumenShellDelegate> ShellGlue::TakeShellDelegate() {
  CHECK(initialised_) << "TakeShellDelegate() called before Init()";
  CHECK(shell_delegate_) << "TakeShellDelegate() called more than once";
  return std::move(shell_delegate_);
}

}  // namespace kibaos
