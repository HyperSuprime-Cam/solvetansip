// -*- lsst-c++ -*-
%define tansip_DOCSTRING
"
Python interface to hsc::meas::tansip
"
%enddef

%feature("autodoc", "1");
%module(package="hsc.meas.tansip", docstring=tansip_DOCSTRING) SLVTS_SWIGLib

%{
#include "lsst/afw/image.h"
#include "hsc/meas/tansip/CCDPosition.h"
#include "hsc/meas/tansip/ReferenceMatch.h"
%}

%include <std_vector.i>
%include <std_string.i>

// [begin: These definitions must be before typemaps are smirched
// by the labyrinthian swig libraries that'll be included later.

%template(VD)  std::vector<double>;
%template(VVD) std::vector< std::vector<double> >;

%template(VI) std::vector<int>;

%template(ReferenceMatchList) std::vector<hsc::meas::tansip::ReferenceMatch>;
%template(CCDPositionList   ) std::vector<hsc::meas::tansip::CCDPosition   >;

// :end]

%include "lsst/p_lsstSwig.i"

%import "lsst/afw/image/imageLib.i"
%import "lsst/afw/geom/geomLib.i"
%import "lsst/afw/table/tableLib.i"
%import "lsst/pex/policy/policyLib.i"

%include "SLVTS_SWIG.i"

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
