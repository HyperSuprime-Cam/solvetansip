from distutils.core import setup, Extension

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
	['../../include'],
        library_dirs=['.'],
        libraries=[],
        extra_compile_args=[],
        extra_link_args=[],
        swig_opts=['-c++'])
    ])
