%module  WCS_PL_MAIN
%{
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include "hsc/meas/tansip/WCS_PL_MAIN.h"
#include "lsst/afw/cameraGeom.h"
#include "lsst/pex/logging.h"
%}

%include "std_vector.i"
%include "std_string.i"
%include "std_map.i"

%template(resultWcs_V) std::vector<lsst::afw::image::TanWcs::Ptr>;
%template(APAIR_V)  std::vector<CL_APAIR* >;
%template(GSIP_V)  std::vector<CL_GSIP* >;
%template(SourceMatchVector) std::vector<PTR(hsc::meas::tansip::SourceMatch)>;
%template(SourceMatchVectorVector) std::vector<std::vector<PTR(hsc::meas::tansip::SourceMatch)> >;
%shared_ptr(hsc::meas::tansip::SourceMatch)

%include "hsc/meas/tansip/SourceMatch.h"
%include "hsc/meas/tansip/WCS_PL_MAIN.h"
