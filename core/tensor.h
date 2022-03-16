#pragma once

#include <cassert>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "accessor.h"
#include "dtypes.h"
#include "storage.h"

class Tensor {
private:
  size_t *dims_;
  size_t *strides_;
  size_t offset_;
  Dtype dtype_;
  size_t num_dims_;
  std::shared_ptr<Storage> storage_;
  Tensor(size_t *dims, size_t *strides, size_t offset, Dtype dtype,
         size_t num_dims, std::shared_ptr<Storage> storage);

public:
  Tensor() = delete;
  ~Tensor();
  Tensor(std::vector<size_t> dims, Dtype dtype, bool clear_memory = false);

  Tensor operator[](size_t i);
  friend std::ostream &operator<<(std::ostream &os, const Tensor &t);

  template <typename T> void operator=(const T &other) {
    if (num_dims_ == 0) {
      assert(is_of_type<T>(dtype_));
      void *data_raw = (char *)storage_->data() + offset_;
      memcpy(data_raw, &other, sizeof(T));
    } else {
      // TODO?
    }
  }

  template <typename T, size_t N> TensorAccessor<T, N> accessor() const {
    assert(N == num_dims_);
    assert(is_of_type<T>(dtype_));

    return TensorAccessor<T, N>((T *)((char *)storage_->data() + offset_),
                                strides_, dims_);
  }

  bool is_contiguous() const;
};
