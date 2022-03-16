#pragma once

template <typename T, size_t N> class TensorAccessorBase {
protected:
  T *data_;
  size_t *strides_;
  size_t *dims_;

  TensorAccessorBase(T *data, size_t *strides, size_t *dims) {
    data_ = data;
    strides_ = strides;
    dims_ = dims;
  }
};

template <typename T, size_t N>
class TensorAccessor : public TensorAccessorBase<T, N> {
public:
  TensorAccessor(T *data, size_t *strides, size_t *dims)
      : TensorAccessorBase<T, N>(data, strides, dims) {}

  TensorAccessor<T, N - 1> operator[](size_t i) {
    return TensorAccessor<T, N - 1>(this->data_ + this->strides_[0] * i,
                                    this->strides_ + 1, this->dims_ + 1);
  }
};

template <typename T>
class TensorAccessor<T, 1> : public TensorAccessorBase<T, 1> {
public:
  TensorAccessor(T *data, size_t *strides, size_t *dims)
      : TensorAccessorBase<T, 1>(data, strides, dims) {}

  T &operator[](size_t i) { return this->data_[this->strides_[0] * i]; }
};
