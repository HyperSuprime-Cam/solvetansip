%module  WCS_PL_MAIN
%{
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include "hsc/meas/tansip/WCS_PL_MAIN.h"
#include "lsst/afw/cameraGeom.h"
#include "lsst/afw/detection.h"
#include "lsst/pex/logging.h"
%}

%include "std_vector.i"
%include "std_string.i"
%include "std_map.i"

%template(SourceGroup) std::vector<lsst::afw::detection::SourceSet>;
%template(vvSourceMatch) std::vector<std::vector<lsst::afw::detection::SourceMatch> >;
%template(resultWcs_V) std::vector<lsst::afw::image::TanWcs::Ptr>;
%template(APAIR_V)  std::vector<CL_APAIR* >;
%template(GSIP_V)  std::vector<CL_GSIP* >;

%include "hsc/meas/tansip/WCS_PL_MAIN.h"
