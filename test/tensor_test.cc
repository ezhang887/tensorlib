#include <gtest/gtest.h>

#include "core/tensor.h"

TEST(TensorTest, BasicProperties) {
  Tensor t({10, 20, 30, 40}, Dtype::INT32, true);

  auto dims = t.dims();
  EXPECT_EQ(dims[0], 10);
  EXPECT_EQ(dims[1], 20);
  EXPECT_EQ(dims[2], 30);
  EXPECT_EQ(dims[3], 40);

  auto strides = t.strides();
  EXPECT_EQ(strides[3], 1);
  EXPECT_EQ(strides[2], 40);
  EXPECT_EQ(strides[1], 1200);
  EXPECT_EQ(strides[0], 24000);

  EXPECT_TRUE(t.is_contiguous());
}

TEST(TensorTest, Accessing) {
  Tensor t({10, 20}, Dtype::INT32, false);
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 20; j++) {
      t[i][j] = (int32_t)(i * 32 + j * 56);
    }
  }

  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 20; j++) {
      EXPECT_EQ(t[i][j].get_value<int32_t>(), i * 32 + j * 56);
    }
  }
}

TEST(TensorTest, Copying) {
  Tensor t({10, 20}, Dtype::INT32, false);
  Tensor u = t;

  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 20; j++) {
      t[i][j] = (int32_t)(i * 32 + j * 56);
    }
  }

  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 20; j++) {
      EXPECT_EQ(u[i][j].get_value<int32_t>(), i * 32 + j * 56);
    }
  }
}
