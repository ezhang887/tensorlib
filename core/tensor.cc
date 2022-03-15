#include "tensor.h"

#include <memory>

using std::vector;

Tensor::Tensor(vector<size_t> dims) {
    dims_ = dims;
    offset_ = 0;

    strides_ = dims;
    strides_[dims.size() - 1] = 1;

    // TODO: include dtypes here
    size_t total_bytes = 1;
    for (size_t dim : dims) {
        total_bytes *= dim;
    }

    storage_ = std::make_shared<Storage>(Storage(total_bytes));
}
