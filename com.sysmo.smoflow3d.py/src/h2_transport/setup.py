from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

setup(
    name = 'H2 transport properties',
    ext_modules = cythonize([
       Extension("h2_transport", ["h2_transport.pyx", "CalcH2TransportProps.c"])
    ])
)