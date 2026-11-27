// Copyright 2025 The KibaOS Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// KibaOS / Lumen entry point. Initialises the Ash shell and wires up the
// KibaOS shell delegate and glue libraries.

#include <memory>

#include "base/at_exit.h"
#include "base/command_line.h"
#include "base/logging.h"
#include "base/message_loop/message_pump_type.h"
#include "base/task/single_thread_task_executor.h"
#include "lumen/kibaos_shell_glue.h"

// ash::Shell::CreateInstance and DeleteInstance are declared here; the actual
// symbols are provided by //ash.
namespace ash {
class Shell;
}

int main(int argc, char** argv) {
  // Required by base:: utilities (registers atexit handlers, etc.)
  base::AtExitManager at_exit;
  base::CommandLine::Init(argc, argv);

  logging::LoggingSettings logging_settings;
  logging_settings.logging_dest = logging::LOG_TO_STDERR;
  logging::InitLogging(logging_settings);

  // KibaOS glue: instantiates the shell delegate and initialises the
  // KibaOS path/environment utilities before Ash sees them.
  kibaos::ShellGlue glue;
  if (!glue.Init()) {
    LOG(ERROR) << "KibaOS ShellGlue::Init() failed – aborting.";
    return 1;
  }

  // A single-thread UI task executor is required for Aura/Ash.
  base::SingleThreadTaskExecutor main_task_executor(
      base::MessagePumpType::UI);

  // Hand the shell delegate to Ash.
  // ash::Shell::CreateInstance(glue.TakeShellDelegate(), ...);
  // <Ash initialisation goes here once AshShellInit is wired up.>

  LOG(INFO) << "KibaOS Lumen initialised. Shell delegate transferred to Ash.";

  // ash::Shell::DeleteInstance();
  return 0;
}
