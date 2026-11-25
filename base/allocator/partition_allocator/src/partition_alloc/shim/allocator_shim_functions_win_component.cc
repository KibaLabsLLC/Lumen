// Copyright 2023 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


// Cross-checks.
#if !PA_BUILDFLAG(IS_COMPONENT_BUILD) || !PA_BUILDFLAG(IS_WIN)
#error This code is only for Windows component build.
#endif
