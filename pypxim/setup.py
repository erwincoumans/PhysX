
import os
import subprocess
import sys
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

class CMakeBuild(build_ext):
    def run(self):
        try:
            subprocess.check_call(['cmake', '--version'])
        except OSError:
            raise RuntimeError("CMake must be installed to build the extension")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        cmake_args = [
            f'-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}',
            f'-DPYTHON_EXECUTABLE={sys.executable}',
        ]

        build_temp = self.build_temp
        print("build_temp=", build_temp)
        if not os.path.exists(build_temp):
            os.makedirs(build_temp)

        try:
            subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=build_temp)
            print("CMake configuration completed successfully.")
        except subprocess.CalledProcessError as e:
            print("Error during CMake configuration:", e)
            raise

        try:
            subprocess.check_call(['cmake', '--build', '.'], cwd=build_temp)
            print("CMake build completed successfully.")
        except subprocess.CalledProcessError as e:
            print("Error during CMake build:", e)
            raise

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        super().__init__(name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)

setup(
    name="pypxim",
    version="0.1.0",
    description="An example pybind11 module with PhysX integration",
    author="Your Name",
    license="MIT",
    ext_modules=[CMakeExtension('pypxim', sourcedir='.')],
    cmdclass={'build_ext': CMakeBuild},
    zip_safe=False,
)

