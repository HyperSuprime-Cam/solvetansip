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
%}

%include <std_vector.i>
%include <std_string.i>
%include <boost_shared_ptr.i>

%shared_ptr(hsc::meas::tansip::CL_SLVTS);
%shared_ptr(hsc::meas::tansip::SourceMatch);

// begin: These definitions must be before typemaps are smirched
// by the labyrinthian swig libraries that'll be included later.

%template(VS)   std::vector<std::string>;
%template(VVS)  std::vector< std::vector<std::string> >;
%template(VVVS) std::vector< std::vector< std::vector<std::string> > >;

%template(VD)  std::vector<double>;
%template(VVD) std::vector< std::vector<double> >;

%template(VI) std::vector<int>;
%template(VQ) std::vector<long long int>;

namespace hsc { namespace meas { namespace tansip
{
    struct CL_SLVTS{};
    boost::shared_ptr<CL_SLVTS> SOLVETANSIP(std::vector< std::vector< std::vector< std::string > > > SLVTS_Argvs);
}}} // hsc::meas::tansip
// end

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

%include "SLVTS_SWIG.i"
