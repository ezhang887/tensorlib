#include <gtest/gtest.h>

#include "core/tensor.h"

TEST(AccessorTest, BasicFunctionality) {
  Tensor t({10, 20, 30, 40}, Dtype::INT32, true);

  auto accessor = t.accessor<int32_t, 4>();
  accessor[0][0][0][0] = 254;
  accessor[3][18][29][1] = 1678;

  EXPECT_EQ(accessor[0][0][0][0], 254);
  EXPECT_EQ(accessor[3][18][29][1], 1678);
  EXPECT_EQ(accessor[0][0][0][1], 0);

  EXPECT_EQ(t[0][0][0][0].get_value<int32_t>(), 254);
  EXPECT_EQ(t[3][18][29][1].get_value<int32_t>(), 1678);
  EXPECT_EQ(t[0][0][0][1].get_value<int32_t>(), 0);
}
