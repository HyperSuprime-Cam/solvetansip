%module  WCS_PL_MAIN
%{
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include "hsc/meas/tansip/WCS_PL_MAIN.h"
%}

%include "std_vector.i"
%include "std_string.i"
%include "std_map.i"

%template(SourceGroup) std::vector<lsst::afw::detection::SourceSet>;
#%template(WcsDic) std::map<int, lsst::afw::image::Wcs::Ptr>;
%template(vvSourceMatch) std::vector<std::vector<lsst::afw::detection::SourceMatch> >;
%template(resultWcs_V) std::vector<lsst::afw::image::TanWcs::Ptr>;
#%template(CPROP_V) std::vector<CL_CPROP*>;
%template(APAIR_V)  std::vector<CL_APAIR* >;
%template(GSIP_V)  std::vector<CL_GSIP* >;
#%template(CSIP_V)  std::vector<CL_CSIP* >;
#%template(PAIR_V)  std::vector<CL_PAIR* >;

%include "hsc/meas/tansip/WCS_PL_MAIN.h"
