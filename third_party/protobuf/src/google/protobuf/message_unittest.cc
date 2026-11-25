// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

// Author: kenton@google.com (Kenton Varda)
//  Based on original Protocol Buffers design by
//  Sanjay Ghemawat, Jeff Dean, and others.

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#define MESSAGE_TEST_NAME MessageTest
#define MESSAGE_FACTORY_TEST_NAME MessageFactoryTest
#define UNITTEST_PACKAGE_NAME "proto2_unittest"
#define UNITTEST ::proto2_unittest
#define UNITTEST_IMPORT ::proto2_unittest_import

// Must include after the above macros.
// clang-format off
// clang-format on
