# KibaOS / Lumen

KibaOS is a modern desktop operating system built on the Chromium project. Lumen is the KibaOS windowing compositor: an experimental fork of Chromium keeping the Ash window manager, the Aura windowing library, and their dependencies. The chrome/ directory is removed. The executable target in lumen/ is named chrome.

## Architecture

```
KibaOS
└── Lumen (this repo)
    ├── ash/          – Ash window manager (Chrome OS shell)
    ├── aura/         – Aura windowing library
    ├── lumen/        – KibaOS-specific shell delegate and glue libraries
    └── chromeos/     – ChromeOS platform components (rebranded as KibaOS)
```

## Shell Delegation

Lumen implements `ash::ShellDelegate` via `LumenShellDelegate`. Each sub-delegate covers a specific Ash feature (capture mode, clipboard, coral, game dashboard, accessibility, nearby share, saved desks, tasks, focus mode, system sounds, scanner, user education). KibaOS-specific glue libraries live in `lumen/kibaos_*.{h,cc}`.

## License

KibaOS is derived from Chromium and ChromiumOS and retains their BSD-style license. See `LICENSE` and `LICENSE.chromium_os`.
