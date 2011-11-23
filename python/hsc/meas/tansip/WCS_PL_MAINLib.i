// -*- lsst-c++ -*-
%define tansip_DOCSTRING
"
Python interface to hsc::meas::tansip
"
%enddef

%feature("autodoc", "1");
%module(package="hsc.meas.tansip", docstring=tansip_DOCSTRING) WCS_PL_MAINLib

%{
#include "lsst/afw/image.h"
%}

%include "lsst/p_lsstSwig.i"

%pythoncode %{
import lsst.utils

def version(HeadURL = r"$HeadURL: ssh://hsc-gw2.mtk.nao.ac.jp/ana/hgrepo/hscAstrom/python/hsc/meas/read/okura_read.i $"):
    version_svn = lsst.utils.guessSvnVersion(HeadURL)

    try:
        import eups
    except ImportError:
        return version_svn
    else:
        try:
            version_eups = eups.setup("solvetansip")
        except AttributeError:
            return version_svn

    if version_eups == version_svn:
        return version_svn
    else:
        return "%s (setup: %s)" % (version_svn, version_eups)
%}

%import "lsst/afw/image/imageLib.i"
%import "lsst/afw/geom/geomLib.i"
%import "lsst/afw/detection/detectionLib.i"

%include "WCS_PL_MAIN.i"

