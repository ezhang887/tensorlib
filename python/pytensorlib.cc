#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "core/dtypes.h"
#include "core/tensor.h"

namespace py = pybind11;

PYBIND11_MODULE(pytensorlib, m) {
  py::enum_<Dtype>(m, "Dtype")
      .value("int8", Dtype::INT8)
      .value("int16", Dtype::INT16)
      .value("int32", Dtype::INT32)
      .value("int64", Dtype::INT64)
      .value("float", Dtype::FLOAT)
      .value("double", Dtype::DOUBLE)
      .export_values();

  py::class_<Tensor>(m, "Tensor")
      .def(py::init<std::vector<size_t>, Dtype, bool>())
      .def("is_contiguous", &Tensor::is_contiguous)
      .def("strides", &Tensor::strides)
      .def("dims", &Tensor::dims);
}
