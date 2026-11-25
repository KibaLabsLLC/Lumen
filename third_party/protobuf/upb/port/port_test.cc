#include <gtest/gtest.h>

// Must be last.

namespace {

TEST(PortTest, UnreachableTrapsInDebugMode) {
#if !defined(GTEST_HAS_DEATH_TEST)
  GTEST_SKIP() << "Death test not supported.";
#endif
#if NDEBUG
  GTEST_SKIP() << "NDEBUG is set.";
#endif

  EXPECT_DEATH(
      { UPB_UNREACHABLE(); },
      "port_test.cc:.*: Reached unreachable statement in function "
      "`.*UnreachableTrapsInDebugMode");
}

}  // namespace
