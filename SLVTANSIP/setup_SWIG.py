from distutils.core import setup, Extension

setup(
    ext_modules = [
        Extension('_SLVTANSIP_SWIG', ['SLVTANSIP_SWIG.i',
	'SLVTANSIP_SWIG.cc',
	'SLVTANSIP_ANA_CCD.cc',
	'SLVTANSIP_ANA_DIST.cc',
	'SLVTANSIP_ANA_EXT.cc',
	'SLVTANSIP_ANA_FIT.cc',
	'SLVTANSIP_ANA_OUT.cc',
	'SLVTANSIP_ANA_POS.cc',
	'SLVTANSIP_ANA_SET.cc',
	'SLVTANSIP_ANA_SLV.cc',
	'SLVTANSIP_CCD.cc',
	'SLVTANSIP_OBJ.cc',
	'SLVTANSIP_SUB.cc',
#	'SLVTANSIP_TOOL.cc',
	'Statistics.cc',
	'LeastSquares.cc'],
        library_dirs=['.'],
        libraries=['cfitsio'],
        extra_compile_args=[],
        extra_link_args=[],
        swig_opts=['-c++'])
    ])
