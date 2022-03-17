import setuptools
from setuptools import setup
from setuptools.command import build_ext

import os
import posixpath
import shutil

__version__ = "0.0.1"

# Based on: https://github.com/OpenMined/PSI/blob/master/setup.py
class BazelExtension(setuptools.Extension):
    """A C/C++ extension that is defined as a Bazel BUILD target."""

    def __init__(self, name, bazel_target):
        self.bazel_target = bazel_target
        self.relpath, self.target_name = posixpath.relpath(bazel_target, "//").split(":")
        setuptools.Extension.__init__(self, name, sources=[])

class BuildBazelExtension(build_ext.build_ext):
    """A command that runs Bazel to build a C/C++ extension."""

    def run(self):
        for ext in self.extensions:
            self.bazel_build(ext)
        build_ext.build_ext.run(self)

    def bazel_build(self, ext):
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        bazel_argv = [
            "bazel",
            "build",
            ext.bazel_target,
            "--symlink_prefix=" + os.path.join(self.build_temp, "bazel-"),
            "--compilation_mode=" + ("dbg" if self.debug else "opt"),
        ]
        self.spawn(bazel_argv)

        shared_lib_ext = ".so"
        shared_lib = ext.name + shared_lib_ext
        ext_bazel_bin_path = os.path.join(self.build_temp, "bazel-bin", ext.relpath, shared_lib)

        ext_dest_path = self.get_ext_fullpath(ext.name)
        ext_dest_dir = os.path.dirname(ext_dest_path)

        if not os.path.exists(ext_dest_dir):
            os.makedirs(ext_dest_dir)
        shutil.copyfile(ext_bazel_bin_path, ext_dest_path)

setup(
    name="pytensorlib",
    version=__version__,
    ext_modules=[BazelExtension("pytensorlib", "//python:pytensorlib")],
    cmdclass=dict(build_ext=BuildBazelExtension),
    zip_safe=False,
    python_requires=">=3.6",
)
