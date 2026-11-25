// Copyright 2018 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Test fuzzer that when built successfully proves that fuzzable_proto_library
// is working. Building this fuzzer without using fuzzable_proto_library will
// fail because of test_fuzzer_input.proto

#include <cstdlib>
#include <iostream>



DEFINE_PROTO_FUZZER(
    const fuzzable::lpm_test_fuzzer::TestFuzzerInput& fuzzable_input) {
  std::string serialized;
  if (!fuzzable_input.SerializeToString(&serialized)) {
    std::abort();
  }
  lpm_test_fuzzer::TestFuzzerInput input;
  if (!input.ParseFromString(serialized)) {
    std::abort();
  }

  std::cout << input.imported().imported_publicly().input() << std::endl;
}
