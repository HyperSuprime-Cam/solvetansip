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
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : APROP
//-----------------------------------------------------------------
int F_WCSA_PLMAIN_GET_CCDNUM(CL_WCSA_ASP* WCSA_ASP);
int F_WCSA_PLMAIN_GET_ALLREFNUM(CL_WCSA_ASP* WCSA_ASP);
int F_WCSA_PLMAIN_GET_ALLFITNUM(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GET_CRPIX(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GET_CRVAL(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GET_REFNUM(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GET_FITNUM(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GET_SIPRMSX(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GET_SIPRMSY(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GET_PSIPRMSX(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLMAIN_GET_PSIPRMSY(CL_WCSA_ASP* WCSA_ASP);
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : POSITION
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_RADECfromLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_RADECfromCRPIX(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_LOCALfromRADEC(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_CRPIXfromRADEC(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_CCDIDLOCALfromGLOBAL(CL_WCSA_ASP* WCSA_ASP,std::vector< double > XY);
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_GLOBALfromCCDIDLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_IMPIXELfromLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_LOCALfromIMPIXEL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : POSITION GRID
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETPOSITION_RADECfromLOCALGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETPOSITION_RADECfromCRPIXGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETPOSITION_LOCALfromRADECGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETPOSITION_CRPIXfromRADECGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : JACOBIAN GRID
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETCRSMA_atLOCALGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETCRSMA_atCRPIXGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETCRSMA_atRADECGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETCRSM_atLOCALGRID(CL_WCSA_ASP* WCSA_ASP,int CID,int CRSMID,std::vector< double > X,std::vector< double > Y);
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : DSITORTION GRID
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETDISTORTION_atCRPIXGRID(CL_WCSA_ASP* WCSA_ASP,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETDISTORTION_atRADECGRID(CL_WCSA_ASP* WCSA_ASP,std::vector< double > GRID);
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : REFERENCE
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLMAIN_GETREF_ID(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CHIPID(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_FLAG(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYLOCAL(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYRADEC(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYGLOBAL(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYGLOBALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYLOCALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYIMPIXEL(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYIMWORLD(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERACONV(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAROT(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERASHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERASHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAPCONV(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAPROT(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAPSHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAPSHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAPMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID);

std::vector< double > F_WCSA_PLMAIN_GETREF(CL_WCSA_ASP* WCSA_ASP, boost::int64_t REFID);
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : CCD
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETCCDPOSITIONS(CL_WCSA_ASP* WCSA_ASP, int CID);
//-----------------------------------------------------------------
//Plotting Regions : WCSA_ASP : CCD
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLMAIN_GET_CORNAR(CL_WCSA_ASP* WCSA_ASP,int CID);
std::vector< double > F_WCSA_PLMAIN_GET_DISTCORRCORNAR(CL_WCSA_ASP* WCSA_ASP,int CID);
std::vector< double > F_WCSA_PLMAIN_GET_DISTCORRCORNAR_N(CL_WCSA_ASP* WCSA_ASP,int CID,int N);
std::vector< double > F_WCSA_PLMAIN_GET_RADECCORNAR(CL_WCSA_ASP* WCSA_ASP,int CID);
std::vector< int > F_WCSA_PLMAIN_GET_INDEX(CL_WCSA_ASP *WCSA_ASP);
//std::vector< double > F_WCSA_PLMAIN_GETCCDPOSITION(CL_WCSA_ASP* WCSA_ASP, int CID);
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
