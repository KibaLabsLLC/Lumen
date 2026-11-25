// Copyright 2018 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdint.h>


// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::string input(reinterpret_cast<const char*>(data), size);
  std::vector<i18n::addressinput::FormatElement> format_element;
  i18n::addressinput::ParseFormatRule(input, &format_element);
  return 0;
}
