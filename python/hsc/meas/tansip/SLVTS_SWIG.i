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
#include "hsc/meas/tansip/SourceMatch.h"
#include "hsc/meas/tansip/SLVTS_GET.h"
#include "hsc/meas/tansip/SLVTS_LSST.h"
%}


%template(resultWcs_V) std::vector<lsst::afw::image::TanWcs::Ptr>;
%template(SourceMatchVector) std::vector<PTR(hsc::meas::tansip::SourceMatch)>;
%template(SourceMatchVectorVector) std::vector<std::vector<PTR(hsc::meas::tansip::SourceMatch)> >;

%include "lsst/daf/base/PropertySet.h"
%include "hsc/meas/tansip/SourceMatch.h"
%include"hsc/meas/tansip/SLVTS_GET.h"
%include "hsc/meas/tansip/SLVTS_LSST.h"

