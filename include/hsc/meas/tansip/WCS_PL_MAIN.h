//-----------------------------------------------------------
//WCS_PL_MAIN.h
//
//Last modification : 2011/12/20
//------------------------------------------------------------
#include<vector>
#include<string>
#include "lsst/pex/policy/Policy.h"
#include "lsst/afw/cameraGeom/Camera.h"
#include "lsst/afw/image/TanWcs.h"
//#include "lsst/afw/table/misc.h"   // to use int64_t
#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"
#include "hsc/meas/tansip/WCS_SIMULATION.h"
#include "hsc/meas/tansip/SourceMatch.h"
namespace dafbase = lsst::daf::base;
#ifndef WCS_PL_MAIN_H
#define WCS_PL_MAIN_H

//typedef boost::int64_t IntT;

class CL_WCSA_ASP{//Chip property
private:
public:
    std::vector <lsst::afw::image::TanWcs::Ptr> WCSPtr;
    CL_APROP* APROP;
    CL_GSIP*  GSIP;
    CL_APAIR* APAIR;

    CL_WCSA_ASP(): APROP(), GSIP(), APAIR() {}
    lsst::afw::image::TanWcs::Ptr F_WCSA_PLMAIN_SETWCSPtr(int);
    void F_WCS_PLMAIN_NEWWCSA_ASP();
    void F_WCS_PLMAIN_DELWCSA_ASP();
    void F_WCS_PLMAIN_SETWCSA_ASP();

    ~CL_WCSA_ASP();
};
PTR(CL_WCSA_ASP) F_WCSA_TANSIP_V(std::vector< std::vector<PTR(hsc::meas::tansip::SourceMatch)> > const &,lsst::daf::base::PropertySet::Ptr &,lsst::pex::policy::Policy::Ptr &,lsst::afw::cameraGeom::Camera::Ptr &/*,lsst::daf::base::PropertySet::Ptr &,bool*/);
PTR(CL_WCSA_ASP) F_WCSA_TANSIP_V_local(std::string,lsst::daf::base::PropertySet::Ptr &,lsst::pex::policy::Policy::Ptr &,lsst::afw::cameraGeom::Camera::Ptr &/*,lsst::daf::base::PropertySet::Ptr &,bool*/);
lsst::daf::base::PropertySet::Ptr F_WCS_EMPTYMETADATA();
std::vector <lsst::afw::image::TanWcs::Ptr> F_WCSA_PLMAIN_GETWCSLIST(PTR(CL_WCSA_ASP) WCSA_ASP);
void F_WCSA_PLMAIN_MEMORYDELETE(CL_WCSA_ASP* WCSA_ASP);
//-----------------------------------------------------------------
//Output Functions : WCSA_ASP : METADATA
//-----------------------------------------------------------------
void setMetadata(PTR(CL_WCSA_ASP) WCSA_ASP, dafbase::PropertySet::Ptr &metaTANSIP);
void setSummaryToMetadata(PTR(CL_WCSA_ASP) WCSA_ASP, dafbase::PropertySet::Ptr &metaTANSIP);
//-----------------------------------------------------------------
//Output Functions : WCSA_ASP
//-----------------------------------------------------------------
void F_WCSA_PLMAIN_OUTPUTREFERENCES(CL_WCSA_ASP* WCSA_ASP, std::string REFERENCESFILENAME);
void F_WCSA_PLMAIN_OUTPUTSIPFIT (CL_WCSA_ASP* WCSA_ASP, std::string  SIPFITFILENAME);
void F_WCSA_PLMAIN_OUTPUTPSIPFIT(CL_WCSA_ASP* WCSA_ASP, std::string PSIPFITFILENAME);
void F_WCSA_PLMAIN_OUTPUTSIP(CL_WCSA_ASP* WCSA_ASP, std::string SIPFILENAME);
void F_WCSA_PLMAIN_INPUTSIP (CL_WCSA_ASP* WCSA_ASP, std::string SIPFILENAME);
void F_WCSA_PLMAIN_OUTPUTCCD(CL_WCSA_ASP* WCSA_ASP, std::string CCDFILENAME);
void F_WCSA_PLMAIN_INPUTCCD (CL_WCSA_ASP* WCSA_ASP, std::string CCDFILENAME);
void F_WCSA_PLMAIN_OUTPUTCCDRMS(CL_WCSA_ASP* WCSA_ASP, std::string CCDRMSFILENAME);
//-----------------------------------------------------------------
//Simulation Functions : WCSA_ASP
//-----------------------------------------------------------------
void F_WCSA_PLMAIN_SIMULATION(int HARD,std::string CCDPOSfile,std::string DISTfile,double NSCALE,int RANNUM,int REFNUM);
void F_WCSA_PLMAIN_SIMULATIONDIFF(int HARD,std::string CCDPOSfile,std::string DISTfile,std::string CCDoutfile,std::string RESoutfile,CL_WCSA_ASP* WCSA_ASP);
void F_WCSA_PLMAIN_SIMULATION2(lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera,double NSCALE,int RANNUM,int REFNUM);
void F_WCSA_PLMAIN_SIMULATIONDIFF2(std::string CCDoutfile,std::string RESoutfile,CL_WCSA_ASP* WCSA_ASP);
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : APROP
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : POSITION
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : POSITION GRID
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : JACOBIAN GRID
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : DSITORTION GRID
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : REFERENCE
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : CCD
//-----------------------------------------------------------------
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


