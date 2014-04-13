%module  SLVTS_SWIG
%{
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include "lsst/afw/cameraGeom.h" 
#include "lsst/pex/logging.h"    
#include "lsst/pex/policy/Policy.h"
#include "lsst/afw/cameraGeom/Camera.h"
#include "lsst/afw/image/TanWcs.h"
#include "lsst/daf/base/PropertySet.h"
#include"hsc/meas/tansip/SourceMatch.h"
#include"hsc/meas/tansip/SLVTS_GET.h"
#include"hsc/meas/tansip/SLVTS_LSST.h"
%}

%include "std_vector.i"
%include "std_string.i"
%include "std_map.i"

%template(VS)  std::vector<std::string>;
%template(VVS) std::vector< std::vector<std::string> >;
%template(VVVS) std::vector< std::vector< std::vector<std::string> > >;
%template(VSLVTS)  std::vector<CL_SLVTS*>;
std::vector< CL_SLVTS* > SOLVETANSIP(std::vector< std::vector< std::vector< std::string > > > SLVTS_Argvs);
void SET_END(std::vector< CL_SLVTS* > SOLVETANSIP);
%template(resultWcs_V) std::vector<lsst::afw::image::TanWcs::Ptr>;

%template(SourceMatchVector) std::vector<PTR(hsc::meas::tansip::SourceMatch)>;
%template(SourceMatchVectorVector) std::vector<std::vector<PTR(hsc::meas::tansip::SourceMatch)> >;
%shared_ptr(hsc::meas::tansip::SourceMatch);

%include "lsst/daf/base/PropertySet.h"
%include "hsc/meas/tansip/SourceMatch.h"
%include"hsc/meas/tansip/SLVTS_GET.h"
%include "hsc/meas/tansip/SLVTS_LSST.h"

