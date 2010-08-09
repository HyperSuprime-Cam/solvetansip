//------------------------------------------------------------
//WCS_TANSIP.h
//
//Last modification : 2010/07/23
//------------------------------------------------------------
#include<vector>
#include "lsst/daf/base/PropertySet.h"
#include "lsst/pex/policy/Policy.h"
#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_CPROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"
#include "lsst/afw/image/TanWcs.h"
#include "lsst/afw/detection/Source.h"
#include "lsst/afw/detection/SourceMatch.h"
#include "lsst/afw/cameraGeom/Camera.h"
//namespace hsc {
  //namespace meas {
    //namespace tansip {

std::vector <lsst::afw::image::TanWcs::Ptr>    F_WCS_TANSIP_V(std::vector< std::vector<lsst::afw::detection::SourceMatch> > const &,lsst::pex::policy::Policy::Ptr &,lsst::afw::cameraGeom::Camera::Ptr &,lsst::daf::base::PropertySet::Ptr &,bool);
void    F_WCS_TANSIP_TEST(std::vector <lsst::afw::image::TanWcs::Ptr>);
//}}}
