from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import os

startupFolder = os.getcwd()
smoFlowFolder = os.path.join(startupFolder, "../bin/")
smoFlowFolder = os.path.abspath(smoFlowFolder)
print smoFlowFolder

os.environ['LD_RUN_PATH'] = smoFlowFolder
CXXFLAGS = ["-I../src",  "-I../../../coolprop"]
LDFLAGS = ["-L" + smoFlowFolder]


smoMedia = Extension(
       "Media", 
       ['Media.pyx'], # our Cython source
       language="c++",   # generate C++ code
       extra_compile_args = CXXFLAGS,
       extra_link_args = LDFLAGS,
       libraries = ["SmoFlow"]
)

setup(
      name = "SmoFlow3D",
      ext_modules = cythonize([
           smoMedia
      ])
)

# Build with
# python setup.py build_ext --inplace
