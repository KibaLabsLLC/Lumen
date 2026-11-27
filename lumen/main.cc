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
#include "lumen/ash_shell_init.h"
#include "lumen/kibaos_shell_glue.h"

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

  // Create Ash and hand the shell delegate over.
  kibaos::AshShellInit ash_shell_init;
  if (!ash_shell_init.Init(&glue)) {
    LOG(ERROR) << "KibaOS AshShellInit::Init() failed – aborting.";
    return 1;
  }

  // Run the Ash shell until it is asked to quit.
  const int exit_code = ash_shell_init.Run();

  // Explicit shutdown before returning so destructors run in a well-defined
  // order.
  ash_shell_init.Shutdown();

  return exit_code;
}
