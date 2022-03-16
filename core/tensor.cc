#include "tensor.h"

#include <cstring>
#include <iostream>
#include <memory>

Tensor::Tensor(std::vector<size_t> dims, Dtype dtype, bool clear_memory) {
  num_dims_ = dims.size();
  dims_ = (size_t *)malloc(num_dims_ * sizeof(size_t));
  for (size_t i = 0; i < num_dims_; i++) {
    dims_[i] = dims[i];
  }
  strides_ = (size_t *)malloc(num_dims_ * sizeof(size_t));
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
  if (dims_ && num_dims_ > 0)
    free(dims_);
  if (strides_ && num_dims_ > 0)
    free(strides_);
}

Tensor::Tensor(size_t *dims, size_t *strides, size_t offset, Dtype dtype,
               size_t num_dims, std::shared_ptr<Storage> storage) {
  if (num_dims > 0) {
    dims_ = (size_t *)malloc(num_dims * sizeof(size_t));
    memcpy(dims_, dims, num_dims * sizeof(size_t));
    strides_ = (size_t *)malloc(num_dims * sizeof(size_t));
    memcpy(strides_, strides, num_dims * sizeof(size_t));
  } else {
    dims_ = nullptr;
    strides_ = nullptr;
  }

  offset_ = offset;
  dtype_ = dtype;
  num_dims_ = num_dims;
  storage_ = storage;
}

Tensor Tensor::operator[](size_t i) {
  return Tensor(dims_ + 1, strides_ + 1,
                offset_ + i * strides_[0] * dtype_to_size(dtype_), dtype_,
                num_dims_ - 1, storage_);
}

Tensor::Tensor(const Tensor &other) {
  num_dims_ = other.num_dims_;
  offset_ = other.offset_;
  dtype_ = other.dtype_;
  storage_ = other.storage_;

  if (other.dims_) {
    dims_ = (size_t *)malloc(num_dims_ * sizeof(size_t));
    memcpy(dims_, other.dims_, num_dims_ * sizeof(size_t));
  }
  if (other.strides_) {
    strides_ = (size_t *)malloc(num_dims_ * sizeof(size_t));
    memcpy(strides_, other.strides_, num_dims_ * sizeof(size_t));
  }
}

void Tensor::operator=(const Tensor &other) {
  num_dims_ = other.num_dims_;
  offset_ = other.offset_;
  dtype_ = other.dtype_;
  storage_ = other.storage_;

  if (other.dims_) {
    dims_ = (size_t *)realloc(dims_, num_dims_ * sizeof(size_t));
    memcpy(dims_, other.dims_, num_dims_ * sizeof(size_t));
  } else {
    free(dims_);
    dims_ = NULL;
  }
  if (other.strides_) {
    strides_ = (size_t *)realloc(strides_, num_dims_ * sizeof(size_t));
    memcpy(strides_, other.strides_, num_dims_ * sizeof(size_t));
  } else {
    free(strides_);
    strides_ = NULL;
  }
}

std::ostream &operator<<(std::ostream &os, const Tensor &t) {
  if (t.num_dims_ == 0) {
    void *data_raw = (char *)t.storage_->data() + t.offset_;
    switch (t.dtype_) {
    case Dtype::INT8:
      os << *((int8_t *)data_raw);
      return os;
    case Dtype::INT16:
      os << *((int16_t *)data_raw);
      return os;
    case Dtype::INT32:
      os << *((int32_t *)data_raw);
      return os;
    case Dtype::INT64:
      os << *((int64_t *)data_raw);
      return os;
    case Dtype::FLOAT:
      os << *((float *)data_raw);
      return os;
    case Dtype::DOUBLE:
      os << *((double *)data_raw);
      return os;
    default:
      return os;
    }
  } else {
    // TODO?
  }
  return os;
}

bool Tensor::is_contiguous() const {
  if (strides_[num_dims_ - 1] != 1) {
    return false;
  }

  for (size_t i = 0; i < num_dims_ - 1; i++) {
    if (strides_[i] != strides_[i + 1] * dims_[i + 1]) {
      return false;
    }
  }
  return true;
}

std::vector<size_t> Tensor::strides() const {
  return std::vector<size_t>(strides_, strides_ + num_dims_);
}

std::vector<size_t> Tensor::dims() const {
  return std::vector<size_t>(dims_, dims_ + num_dims_);
}
