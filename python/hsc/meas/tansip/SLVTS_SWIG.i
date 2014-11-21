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
    #include "hsc/meas/tansip/LSSTInterface.h"
    #include "hsc/meas/tansip/SLVTS_GET.h"
    #include "hsc/meas/tansip/SLVTS_LSST.h"
%}

%import "lsst/daf/base/baseLib.i"
%include "hsc/meas/tansip/APRM.h"
%include "hsc/meas/tansip/CCDPosition.h"
%include "hsc/meas/tansip/ReferenceMatch.h"
%include "hsc/meas/tansip/LSSTInterface.h"
%include "hsc/meas/tansip/SLVTS.h"

%include"hsc/meas/tansip/SLVTS_GET.h"
%include "hsc/meas/tansip/SLVTS_LSST.h"

%template(TanWcsList) std::vector<lsst::afw::image::TanWcs::Ptr>;
