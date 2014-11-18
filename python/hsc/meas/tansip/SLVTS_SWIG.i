%module  SLVTS_SWIG
%{
    #include <iostream>
    #include <fstream>
    #include <cstring>
    #include <iomanip>
    #include "lsst/afw/cameraGeom.h"
    #include "lsst/pex/logging.h"
    #include "lsst/pex/policy/Policy.h"
    #include "lsst/afw/cameraGeom/Camera.h"
    #include "lsst/afw/image/TanWcs.h"
    #include "lsst/daf/base/PropertySet.h"
    #include "hsc/meas/tansip/SLVTS_GET.h"
    #include "hsc/meas/tansip/SLVTS_LSST.h"
    #include "hsc/meas/tansip/SLVTS.h"
%}

%include "lsst/daf/base/PropertySet.h"
%include "hsc/meas/tansip/ReferenceMatch.h"
%include "hsc/meas/tansip/ReferenceMatchLSST.h"

namespace hsc { namespace meas { namespace tansip
{
    struct CL_SLVTS{};
    boost::shared_ptr<CL_SLVTS> SOLVETANSIP(
        std::vector< std::vector< std::string > > const& APRM,
        std::vector< std::vector< std::string > > const& CCD,
        std::vector<ReferenceMatch>               const& matchList
    );

}}} // hsc::meas::tansip

%include"hsc/meas/tansip/SLVTS_GET.h"
%include "hsc/meas/tansip/SLVTS_LSST.h"

%template(resultWcs_V) std::vector<lsst::afw::image::TanWcs::Ptr>;
