%module  tansip
%{
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include "hsc/meas/tansip/WCS_TANSIP.h"
%}

%include "std_vector.i"
%include "std_string.i"
%include "std_map.i"

%template(SourceGroup) std::vector<lsst::afw::detection::SourceSet>;
#%template(WcsDic) std::map<int, lsst::afw::image::Wcs::Ptr>;
%template(vvSourceMatch) std::vector<std::vector<lsst::afw::detection::SourceMatch> >;
%template(resultWcs_V) std::vector<lsst::afw::image::TanWcs::Ptr>;

%include "hsc/meas/tansip/WCS_TANSIP.h"
