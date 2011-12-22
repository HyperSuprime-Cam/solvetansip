//-----------------------------------------------------------
//WCS_PL_MAIN.h
//
//Last modification : 2011/12/20
//------------------------------------------------------------
#include<vector>
#include<string>
#include "lsst/pex/policy/Policy.h"
#include "lsst/afw/detection/SourceMatch.h"
#include "lsst/afw/cameraGeom/Camera.h"
#include "lsst/afw/image/TanWcs.h"
#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"
#ifndef WCS_PL_MAIN_H
#define WCS_PL_MAIN_H
class CL_WCSA_ASP{//Chip property
private:
public:
    std::vector <lsst::afw::image::TanWcs::Ptr> WCSPtr;
    CL_APROP* APROP;
    CL_GSIP*  GSIP;
    CL_APAIR* APAIR;
    std::vector <CL_CSIP*>  CSIPList;
 
    lsst::afw::image::TanWcs::Ptr F_WCSA_PLMAIN_SETWCSPtr(int);
    void F_WCS_PLMAIN_SETWCSA_ASP();
};
CL_WCSA_ASP F_WCSA_TANSIP_V(std::vector< std::vector<lsst::afw::detection::SourceMatch> > const &,lsst::daf::base::PropertySet::Ptr &,lsst::pex::policy::Policy::Ptr &,lsst::afw::cameraGeom::Camera::Ptr &/*,lsst::daf::base::PropertySet::Ptr &,bool*/);
CL_WCSA_ASP F_WCSA_TANSIP_V_local(std::string,lsst::daf::base::PropertySet::Ptr &,lsst::pex::policy::Policy::Ptr &,lsst::afw::cameraGeom::Camera::Ptr &/*,lsst::daf::base::PropertySet::Ptr &,bool*/);
lsst::daf::base::PropertySet::Ptr F_WCS_EMPTYMETADATA();
std::vector <lsst::afw::image::TanWcs::Ptr> F_WCSA_PLMAIN_GETWCSLIST(CL_WCSA_ASP* WCSA_ASP);
//-----------------------------------------------------------------
//Getting Functions : WCS : REFERENCE
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLMAIN_GETREFALL_ID(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CHIPID(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_FLAG(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYLOCAL(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYRADEC(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYGLOBAL(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYGLOBALCRPIX(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYLOCALCRPIX(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYIMPIXEL(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYIMWORLD(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERACONV(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAROT(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERASHEAR1(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERASHEAR2(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAPCONV(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAPROT(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAPSHEAR1(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAPSHEAR2(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAPMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP);

std::vector< double > F_WCSA_PLMAIN_GETREFCCD_ID(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CHIPID(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_FLAG(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYLOCAL(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYRADEC(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYGLOBAL(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYGLOBALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYLOCALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYIMPIXEL(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYIMWORLD(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERACONV(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAROT(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERASHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERASHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAPCONV(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAPROT(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAPSHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAPSHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAPMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID);

std::vector< double > F_WCSA_PLMAIN_GETREF(CL_WCSA_ASP* WCSA_ASP,int REFID);
//-----------------------------------------------------------------
//Getting Functions : WCS : CCD
//-----------------------------------------------------------------
std::vector< std::vector< double > >F_WCSA_PLMAIN_GETCCDPOSITIONS(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETCCDPOSITION(CL_WCSA_ASP* WCSA_ASP, int CID);
//-----------------------------------------------------------------
//Getting Functions : OLD
//-----------------------------------------------------------------

std::vector< std::vector< double > >F_WCSA_PLMAIN_GETREFERENCES(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETRADEC(std::vector< double > X_GLOBAL,CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETX_GLOBAL(std::vector< double > RADEC,CL_WCSA_ASP* WCSA_ASP);

//GET PAIR
std::vector< double > F_WCSA_PLMAIN_GETPAIR_ID(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_CHIPID(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_FLAG(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_RA(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_DEC(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_IM_WORLD_X(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_IM_WORLD_Y(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_IM_PIXEL_X(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_IM_PIXEL_Y(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_CRPIX_X(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_CRPIX_Y(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_GLOBAL_X(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_GLOBAL_Y(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_LOCAL_X(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GETPAIR_LOCAL_Y(CL_WCSA_ASP* WCSA_ASP);
#endif
