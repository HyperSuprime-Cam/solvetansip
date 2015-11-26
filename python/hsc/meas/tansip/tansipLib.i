// -*- lsst-c++ -*-
%define tansip_DOCSTRING
"
Python interface to solvetansip
"
%enddef

%feature("autodoc", "1");
%module(package="hsc.meas.tansip", docstring=tansip_DOCSTRING) tansipLib

%include "SLVTS.i"

%{
#include "hsc/meas/tansip/LSSTInterface.h"
#include "hsc/meas/tansip/SLVTS_LSST.h"
#include "lsst/pex/logging.h"
#include "lsst/afw.h"
#include "lsst/afw/geom/polygon.h"
%}


%include "lsst/p_lsstSwig.i"

%import "lsst/afw/image/imageLib.i"
%import "lsst/afw/geom/geomLib.i"
%import "lsst/afw/table/tableLib.i"
%import "lsst/pex/policy/policyLib.i"
%import "lsst/daf/base/baseLib.i"

%include "hsc/meas/tansip/LSSTInterface.h"
%include "hsc/meas/tansip/SLVTS_LSST.h"

%template(TanWcsList) std::vector<lsst::afw::image::TanWcs::Ptr>;

%pythoncode %{
def toReferenceMatchList(matchLists):
    """
    Convert matchLists expressed in LSST objects to a list that can be passed
    into solvetansip.

    @param matchLists
        A list of lists of lsst.afw.table.ReferenceMatch.
        For a ccdId, matchLists[ccdId] is a list of
        lsst.afw.table.ReferenceMatch in the CCD ccdId.
        matchLists[ccdId] can be either None or [] if no match in it.

    @return ReferenceMatchList
    """

    refMatchLists = ReferenceMatchList()

    for ccdId, matchList in enumerate(matchLists):
        if matchList is None: continue

        refMatchLists[len(refMatchLists):] = [
            toReferenceMatch(m, ccdId)
            for m in matchList if (m.first and m.second) # both ref and src to have valid values
        ]

    return refMatchLists
%}
