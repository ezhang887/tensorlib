#include "tensor.h"

#include <memory>
#include <iostream>

using std::vector;

Tensor::Tensor(vector<size_t> dims, Dtype dtype, bool clear_memory) {
    num_dims_ = dims.size();
    dims_ = new size_t[num_dims_];
    for (size_t i = 0; i < num_dims_; i++) {
        dims_[i] = dims[i];
    }
    strides_ = new size_t[num_dims_];
    offset_ = 0;
    dtype_ = dtype;

    strides_[num_dims_ - 1] = 1;
    for (size_t i = num_dims_ - 2; i <= num_dims_; i--) {
        strides_[i] = strides_[i + 1] * dims_[i + 1];
    }

    size_t total_bytes = dtype_to_size(dtype);
    for (size_t dim : dims) {
        total_bytes *= dim;
    }

    storage_ = std::make_shared<Storage>(Storage(total_bytes, clear_memory));
}

Tensor::~Tensor() {
    delete[] dims_;
    delete[] strides_;
}
