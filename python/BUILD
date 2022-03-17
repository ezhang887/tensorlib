load("@pybind11_bazel//:build_defs.bzl", "pybind_extension", "pybind_library")

pybind_extension(
    name = "pytensorlib",
    srcs = ["pytensorlib.cc"],
    deps = ["//core:tensorlib"],
)

pybind_library(
    name = "pytensorlib",
    data = [":pytensorlib.so"],
)
