from distutils.core import setup, Extension
import os

setup(
    ext_modules = [
        Extension('_SLVTS_SWIG', ['SLVTS_SWIG.i',
	'../../src/SLVTS.cc',
	'../../src/SLVTS_GET.cc',
	'../../src/APRM.cc',
	'../../src/CCD.cc',
	'../../src/REF.cc',
	'../../src/CPP_MEMORY.cc',
	'../../src/CALC_FIT.cc',
	'../../src/CALC_STAT.cc',
	],
	['../../include', os.environ['NDARRAY_DIR'] + '/include'],
        library_dirs=['.', os.environ['OPENBLAS_DIR'] + '/lib'],
        libraries=['openblas'],
        extra_compile_args=[],
        extra_link_args=[],
        swig_opts=['-c++'])
    ])
