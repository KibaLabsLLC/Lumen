// -*- c++ -*-
// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

// Author: kenton@google.com (Kenton Varda)
//  Based on original Protocol Buffers design by
//  Sanjay Ghemawat, Jeff Dean, and others.
//
// This file needs to be included as .inc as it depends on certain macros being
// defined prior to its inclusion.

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cmath>
#include <functional>
#include <limits>
#include <vector>

#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <fstream>
#include <sstream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Must be included last.

namespace google {
namespace protobuf {

TEST(MESSAGE_TEST_NAME, LegacySetMethodsOnStringField) {
  UNITTEST::TestAllTypes msg;

  msg.set_optional_string("std::string value 4", 5);
  EXPECT_EQ(msg.optional_string(), "std::");
}

TEST(MESSAGE_TEST_NAME, LegacySetMethodsOnRepeatedStringField) {
  UNITTEST::TestAllTypes msg;

  msg.add_repeated_string("");
  msg.set_repeated_string(0, "std::string value 4", 5);
  EXPECT_EQ(msg.repeated_string(0), "std::");
}

TEST(MESSAGE_TEST_NAME, LegacyAddMethodsOnRepeatedStringField) {
  UNITTEST::TestAllTypes msg;

  msg.add_repeated_string("std::string value 4", 5);
  EXPECT_EQ(msg.repeated_string(0), "std::");
  msg.clear_repeated_string();
}


namespace {
template <typename T>
static const internal::TcParseTableBase* GetTableIfAvailable(...) {
  return nullptr;
}

template <typename T>
static const internal::TcParseTableBase* GetTableIfAvailable(
    decltype(internal::TcParser::GetTable<T>())) {
  return internal::TcParser::GetTable<T>();
}
}  // namespace

}  // namespace protobuf
}  // namespace google

