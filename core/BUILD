load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "tensorlib",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    copts = ["-std=c++17"],
    visibility = ["//visibility:public"]
)
