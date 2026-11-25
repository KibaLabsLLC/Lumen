// Copyright 2016 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/proxy_resolution/proxy_list.h"

namespace {

void TestOneInput(const std::string& input) {
  net::ProxyList list;
  list.Set(input);
}

}  // namespace

FUZZ_TEST(ParseProxyListFuzzer, TestOneInput);
