//-----------------------------------------------------------
//WCS_PL_MAIN.h
//
//Last modification : 2011/05/20
//------------------------------------------------------------
#include<vector>
#include "lsst/pex/policy/Policy.h"
#include "lsst/afw/detection/SourceMatch.h"
#include "lsst/afw/cameraGeom/Camera.h"
#include "lsst/afw/image/TanWcs.h"
//#include "lsst/daf/base/PropertySet.h"
#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_CPROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"
//#include "lsst/afw/detection/Source.h"
#ifndef WCS_PL_MAIN_H
#define WCS_PL_MAIN_H
class CL_WCSACCP{//Chip property
private:
public:
    std::vector <lsst::afw::image::TanWcs::Ptr> WCSPtr;
    CL_APROP* APROP;
    CL_CPROP* CPROP;
    CL_CSIP*  CSIP;
    CL_PAIR*  PAIR;
    std::vector <CL_CPROP*> CPROPList;
    std::vector <CL_CSIP*> CSIPList;
};
#endif

CL_WCSACCP F_WCS_TANSIP_V(std::vector< std::vector<lsst::afw::detection::SourceMatch> > const &,lsst::daf::base::PropertySet::Ptr &,lsst::pex::policy::Policy::Ptr &,lsst::afw::cameraGeom::Camera::Ptr &/*,lsst::daf::base::PropertySet::Ptr &,bool*/);
std::vector <lsst::afw::image::TanWcs::Ptr> F_WCS_GETWCSLIST(CL_WCSACCP*);
CL_APROP* F_WCS_GETAPROP(CL_WCSACCP*);
CL_CPROP* F_WCS_GETCPROP(CL_WCSACCP*);
CL_CSIP*  F_WCS_GETCSIP(CL_WCSACCP*);
CL_PAIR*  F_WCS_GETPAIR(CL_WCSACCP*);
std::vector <CL_CPROP*> F_WCS_GETCPROPLIST(CL_WCSACCP*);
std::vector <CL_CSIP*>  F_WCS_GETCSIPLIST(CL_WCSACCP*);
lsst::daf::base::PropertySet::Ptr F_WCS_EMPTYMETADATA();

