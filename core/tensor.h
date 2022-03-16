#pragma once

#include <vector>
#include <memory>
#include <cassert>

#include "storage.h"
#include "dtypes.h"
#include "accessor.h"

using std::vector;

class Tensor {
    private:
        size_t *dims_;
        size_t *strides_;
        size_t offset_;
        Dtype dtype_;
        size_t num_dims_;
        std::shared_ptr<Storage> storage_;

    public:
        Tensor() = delete;
        Tensor(Dtype dtype);
        ~Tensor();
        Tensor(vector<size_t> dims, Dtype dtype);

        template <typename T, size_t N>
        TensorAccessor<T, N> accessor() const {
            assert (N == num_dims_);
            // TODO: verify type matches?

            return TensorAccessor<T, N>((T *)((char *)storage_->data() + offset_), strides_, dims_);
        }
};
