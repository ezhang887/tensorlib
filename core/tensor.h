#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <cassert>

#include "storage.h"
#include "dtypes.h"
#include "accessor.h"

class Tensor {
    private:
        size_t *dims_;
        size_t *strides_;
        size_t offset_;
        Dtype dtype_;
        size_t num_dims_;
        std::shared_ptr<Storage> storage_;
        Tensor(size_t *dims, size_t *strides, size_t offset, Dtype dtype, size_t num_dims, std::shared_ptr<Storage> storage);

    public:
        Tensor() = delete;
        ~Tensor();
        Tensor(std::vector<size_t> dims, Dtype dtype, bool clear_memory = false);

        Tensor operator[](size_t i);

        template <typename T, size_t N>
        TensorAccessor<T, N> accessor() const {
            assert (N == num_dims_);
            // TODO: verify type matches?

            return TensorAccessor<T, N>((T *)((char *)storage_->data() + offset_), strides_, dims_);
        }
};
