#include <pybind11/pybind11.h>

#include "core/tensor.h"

namespace py = pybind11;

PYBIND11_MODULE(pytensorlib, m) {
    py::class_<Tensor>(m, "Tensor");
}
