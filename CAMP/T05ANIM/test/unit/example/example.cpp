#include <gtest/gtest.h>

TEST(example, test)
{
  int a = 30, b = 12;

  ASSERT_EQ(a + b, 42);
}
