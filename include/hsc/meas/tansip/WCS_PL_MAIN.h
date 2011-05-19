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
class CL_WCSCCP{//Chip property
private:
public:
    std::vector <lsst::afw::image::TanWcs::Ptr> WCSPtr;
    CL_CPROP* CPROP;
    CL_CSIP* CSIP;
    CL_PAIR* PAIR;
};
#endif

CL_WCSCCP F_WCS_TANSIP_V(std::vector< std::vector<lsst::afw::detection::SourceMatch> > const &,lsst::daf::base::PropertySet::Ptr &,lsst::pex::policy::Policy::Ptr &,lsst::afw::cameraGeom::Camera::Ptr &/*,lsst::daf::base::PropertySet::Ptr &,bool*/);
lsst::daf::base::PropertySet::Ptr F_WCS_EMPTYMETADATA();
CL_CPROP* F_WCS_EMPTYCPROP();
CL_CSIP*  F_WCS_EMPTYCSIP();
CL_PAIR*  F_WCS_EMPTYPAIR();

