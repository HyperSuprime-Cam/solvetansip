//------------------------------------------------------------
//WCS_PL_MAIN.cc
//main program for wcs in pipeline
//
//Last modification : 2011/12/20
//------------------------------------------------------------
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include "hsc/meas/tansip/WCS_PL_MAIN.h"
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
namespace afwImage = lsst::afw::image;
namespace afwGeom = lsst::afw::geom; 
namespace afwCoord = lsst::afw::coord;
namespace camGeom = lsst::afw::cameraGeom;
namespace dafbase = lsst::daf::base;

void    F_WCSA_MAKEAPROP(lsst::pex::policy::Policy::Ptr &,CL_APROP*);
void    F_WCSA_SHOWAPROP(CL_APROP*);
void    F_WCSA_MAKEGSIP(lsst::pex::policy::Policy::Ptr &,lsst::afw::cameraGeom::Camera::Ptr &,CL_APROP*,CL_GSIP*);
//void    F_WCSA_SETSIZE(vector<vector<PTR(hsc::meas::tansip::SourceMatch)> > const &,CL_APROP*,CL_GSIP*);
//void    F_WCSA_SETSIZE_local(string matchlist, CL_APROP*);
void    F_WCSA_SETREFSIZE(vector<vector<PTR(hsc::meas::tansip::SourceMatch)> > const &,CL_APROP*);
void    F_WCSA_SETREFSIZE_local(string matchlist, CL_APROP*);
void    F_WCSA_MAKEPAIR(vector<vector<PTR(hsc::meas::tansip::SourceMatch)> > const &, CL_APROP*,CL_APAIR*);
void    F_WCSA_MAKEPAIR_local(string matchlist,CL_APAIR*);

void    F_WCS_DISTORTION(int ,CL_APROP *APROP);

PTR(CL_WCSA_ASP) F_WCSA_TANSIP_V(vector<vector<PTR(hsc::meas::tansip::SourceMatch)> > const &matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/){
    PTR(CL_WCSA_ASP) WCSA_ASP(new CL_WCSA_ASP());

    cout << "--- solvetansip : START ---" << endl;
    WCSA_ASP->F_WCS_PLMAIN_NEWWCSA_ASP();

//CCDNUM
    F_WCSA_MAKEAPROP(APROPPolicy, WCSA_ASP->APROP);
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_APROP ---" << endl;
    WCSA_ASP->APAIR->CCDNUM=WCSA_ASP->GSIP->CCDNUM=WCSA_ASP->APROP->CCDNUM;
    WCSA_ASP->APROP->F_WCSA_APROP_NEWAPROP();

//ALLREFNUM
    F_WCSA_SETREFSIZE(matchlist,WCSA_ASP->APROP);
    WCSA_ASP->APAIR->ALLREFNUM=WCSA_ASP->GSIP->ALLREFNUM=WCSA_ASP->APROP->ALLREFNUM;
    WCSA_ASP->APAIR->ALLFITNUM=WCSA_ASP->GSIP->ALLFITNUM=WCSA_ASP->APROP->ALLFITNUM;

//SIP ORDER
    WCSA_ASP->APAIR->SIP_ORDER  =WCSA_ASP->GSIP->SIP_ORDER  =WCSA_ASP->APROP->SIP_ORDER;
    WCSA_ASP->APAIR->SIP_P_ORDER=WCSA_ASP->GSIP->SIP_P_ORDER=WCSA_ASP->APROP->SIP_P_ORDER;
    WCSA_ASP->APAIR->SIP_L_ORDER=WCSA_ASP->GSIP->SIP_L_ORDER=WCSA_ASP->APROP->SIP_L_ORDER;
    WCSA_ASP->GSIP->SIP_ORDER_INIT  =WCSA_ASP->APROP->SIP_ORDER_INIT;
    WCSA_ASP->GSIP->SIP_P_ORDER_INIT=WCSA_ASP->APROP->SIP_P_ORDER_INIT;

    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APROP->F_WCSA_APROP_SHOWAPROP();

//NEW
    WCSA_ASP->APAIR->F_WCSA_APAIR_NEWAPAIR();
    WCSA_ASP->GSIP ->F_WCSA_GSIP_NEWGSIP();

//GSIP
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_GSIP ---" << endl;
    F_WCSA_MAKEGSIP(APROPPolicy,camera,WCSA_ASP->APROP,WCSA_ASP->GSIP);
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->GSIP->F_WCSA_GSIP_SHOWGSIP();
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->GSIP->F_WCSA_GSIP_SHOWGPOS();
//    F_WCSA_SETSIZE_local(matchlist,WCSA_ASP->APROP,WCSA_ASP->GSIP);

//APAIR
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_PAIR ---" << endl;
    F_WCSA_MAKEPAIR(matchlist,WCSA_ASP->APROP,WCSA_ASP->APAIR);
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APAIR->F_WCSA_APAIR_SHOWAPAIR();

//TANSIP
    F_WCSA_TANSIP(WCSA_ASP->APROP,WCSA_ASP->APAIR,WCSA_ASP->GSIP);

    setMetadata(WCSA_ASP,metaTANSIP);
    WCSA_ASP->F_WCS_PLMAIN_SETWCSA_ASP();

    cout << "--- solvetansip : END ---" << endl;
    return WCSA_ASP;
/*
    cout << "--- solvetansip : START ---" << endl;
    WCSA_ASP = new CL_WCSA_ASP[1];

    WCSA_ASP->APROP = new CL_APROP[1];
    F_WCSA_MAKEAPROP(APROPPolicy, WCSA_ASP->APROP);
    WCSA_ASP->APROP->REFNUM = new int[WCSA_ASP->APROP->CCDNUM];
    WCSA_ASP->APROP->FITNUM = new int[WCSA_ASP->APROP->CCDNUM];

    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_APROP ---" << endl;
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APROP->F_WCSA_APROP_SHOWAPROP();
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_GSIP ---" << endl;

    WCSA_ASP->GSIP = new CL_GSIP[1];
    WCSA_ASP->GSIP->CSIP = new CL_CSIP[WCSA_ASP->APROP->CCDNUM+1];
    F_WCSA_MAKEGSIP(camera,WCSA_ASP->APROP,WCSA_ASP->GSIP);
    F_WCSA_SETSIZE(matchlist,WCSA_ASP->APROP,WCSA_ASP->GSIP);
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "ALLREFNUM : " << WCSA_ASP->APROP->ALLREFNUM << endl;

    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_PAIR ---" << endl;
    WCSA_ASP->APAIR = new CL_APAIR[1];
    WCSA_ASP->APAIR->PAIR = new CL_PAIR[WCSA_ASP->APROP->ALLREFNUM];
    WCSA_ASP->APAIR->GPOS = F_NEWdouble2(WCSA_ASP->APROP->CCDNUM,3);
    F_WCSA_MAKEPAIR(matchlist,WCSA_ASP->GSIP,WCSA_ASP->APAIR);

    F_WCSA_TANSIP(WCSA_ASP->APROP,WCSA_ASP->APAIR,WCSA_ASP->GSIP);

    WCSA_ASP->F_WCS_PLMAIN_SETWCSA_ASP();

    cout << "--- solvetansip : END ---" << endl;
    return *WCSA_ASP;*/
}
PTR(CL_WCSA_ASP) F_WCSA_TANSIP_V_local(string matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/){
    PTR(CL_WCSA_ASP) WCSA_ASP(new CL_WCSA_ASP());

    cout << "--- solvetansip : START(local) ---" << endl;
    WCSA_ASP->F_WCS_PLMAIN_NEWWCSA_ASP();
//CCDNUM
    F_WCSA_MAKEAPROP(APROPPolicy, WCSA_ASP->APROP);
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_APROP ---" << endl;
    WCSA_ASP->APAIR->CCDNUM=WCSA_ASP->GSIP->CCDNUM=WCSA_ASP->APROP->CCDNUM;
    WCSA_ASP->APROP->F_WCSA_APROP_NEWAPROP();
//ALLREFNUM
    F_WCSA_SETREFSIZE_local(matchlist,WCSA_ASP->APROP);
    WCSA_ASP->APAIR->ALLREFNUM=WCSA_ASP->GSIP->ALLREFNUM=WCSA_ASP->APROP->ALLREFNUM;
    WCSA_ASP->APAIR->ALLFITNUM=WCSA_ASP->GSIP->ALLFITNUM=WCSA_ASP->APROP->ALLFITNUM;

//SIP ORDER
    WCSA_ASP->APAIR->SIP_ORDER  =WCSA_ASP->GSIP->SIP_ORDER  =WCSA_ASP->APROP->SIP_ORDER;
    WCSA_ASP->APAIR->SIP_P_ORDER=WCSA_ASP->GSIP->SIP_P_ORDER=WCSA_ASP->APROP->SIP_P_ORDER;
    WCSA_ASP->APAIR->SIP_L_ORDER=WCSA_ASP->GSIP->SIP_L_ORDER=WCSA_ASP->APROP->SIP_L_ORDER;
    WCSA_ASP->GSIP->SIP_ORDER_INIT  =WCSA_ASP->APROP->SIP_ORDER_INIT;
    WCSA_ASP->GSIP->SIP_P_ORDER_INIT=WCSA_ASP->APROP->SIP_P_ORDER_INIT;

    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APROP->F_WCSA_APROP_SHOWAPROP();

//NEW
    WCSA_ASP->APAIR->F_WCSA_APAIR_NEWAPAIR();
    WCSA_ASP->GSIP ->F_WCSA_GSIP_NEWGSIP();

//GSIP
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_GSIP ---" << endl;
    F_WCSA_MAKEGSIP(APROPPolicy, camera,WCSA_ASP->APROP,WCSA_ASP->GSIP);
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->GSIP->F_WCSA_GSIP_SHOWGSIP();
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->GSIP->F_WCSA_GSIP_SHOWGPOS();
//    F_WCSA_SETSIZE_local(matchlist,WCSA_ASP->APROP,WCSA_ASP->GSIP);cout << "AAH" << endl;


//APAIR
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_PAIR ---" << endl;
    F_WCSA_MAKEPAIR_local(matchlist,WCSA_ASP->APAIR);
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APAIR->F_WCSA_APAIR_SHOWAPAIR();

//TANSIP
    F_WCSA_TANSIP(WCSA_ASP->APROP,WCSA_ASP->APAIR,WCSA_ASP->GSIP);

    WCSA_ASP->F_WCS_PLMAIN_SETWCSA_ASP();

    setMetadata(WCSA_ASP,metaTANSIP);
//WCSA_ASP->GSIP->F_WCSA_GSIP_SHOWGSIP();
//WCSA_ASP->GSIP->F_WCSA_GSIP_SHOWGPOS();
    cout << "--- solvetansip : END(local) ---" << endl;
    return WCSA_ASP;
/*    CL_WCSA_ASP *WCSA_ASP;

    cout << "--- solvetansip : START(local) ---" << endl;
    WCSA_ASP = new CL_WCSA_ASP[1];

    WCSA_ASP->APROP = new CL_APROP[1];
    F_WCSA_MAKEAPROP(APROPPolicy, WCSA_ASP->APROP);
    WCSA_ASP->APROP->REFNUM = new int[WCSA_ASP->APROP->CCDNUM];
    WCSA_ASP->APROP->FITNUM = new int[WCSA_ASP->APROP->CCDNUM];

    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_APROP ---" << endl;
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APROP->F_WCSA_APROP_SHOWAPROP();
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_GSIP ---" << endl;

    WCSA_ASP->GSIP = new CL_GSIP[1];
    WCSA_ASP->GSIP->CSIP = new CL_CSIP[WCSA_ASP->APROP->CCDNUM+1];
    F_WCSA_MAKEGSIP(camera,WCSA_ASP->APROP,WCSA_ASP->GSIP);
    F_WCSA_SETSIZE_local(matchlist,WCSA_ASP->APROP,WCSA_ASP->GSIP);
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "ALLREFNUM : " << WCSA_ASP->APROP->ALLREFNUM << endl;

    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_PAIR ---" << endl;

    WCSA_ASP->APAIR = new CL_APAIR[1];
    WCSA_ASP->APAIR->PAIR = new CL_PAIR[WCSA_ASP->APROP->ALLREFNUM];
    WCSA_ASP->APAIR->GPOS = F_NEWdouble2(WCSA_ASP->APROP->CCDNUM,3);
    F_WCSA_MAKEPAIR_local(matchlist,WCSA_ASP->GSIP,WCSA_ASP->APAIR);



    F_WCSA_TANSIP(WCSA_ASP->APROP,WCSA_ASP->APAIR,WCSA_ASP->GSIP);


    WCSA_ASP->F_WCS_PLMAIN_SETWCSA_ASP();

    cout << "--- solvetansip : END(local) ---" << endl;
    return *WCSA_ASP;*/
}
CL_WCSA_ASP::~CL_WCSA_ASP() {
    F_WCSA_PLMAIN_MEMORYDELETE(this);
}
void CL_WCSA_ASP::F_WCS_PLMAIN_NEWWCSA_ASP(){
    APROP= new CL_APROP;
    GSIP = new CL_GSIP;
    APAIR= new CL_APAIR;
}
void CL_WCSA_ASP::F_WCS_PLMAIN_DELWCSA_ASP(){
    delete APROP;
    delete GSIP ;
    delete APAIR;
}
void F_WCSA_PLMAIN_MEMORYDELETE(CL_WCSA_ASP* WCSA_ASP){
    cout << "--- solvetansip : DELETE MEMORY ---" << endl;
    WCSA_ASP->APROP->F_WCSA_APROP_DELAPROP();
    WCSA_ASP->APAIR->F_WCSA_APAIR_DELAPAIR();
    WCSA_ASP->GSIP ->F_WCSA_GSIP_DELGSIP();
    WCSA_ASP->       F_WCS_PLMAIN_DELWCSA_ASP();
//    delete [] WCSA_ASP;
}
void    F_WCSA_MAKEAPROP(lsst::pex::policy::Policy::Ptr &APROPPolicy, CL_APROP *APROP){
    string INSTR,CMODE,OAMODE,SNAME,CNAME,PNAME,DNAME;

    // Validate policy with dictionary
    lsst::pex::policy::DefaultPolicyFile const defaultsFile("solvetansip", "WCS_MAKEAPROP_Dictionary.paf",
                                                            "policy");
    lsst::pex::policy::Policy const defaults(defaultsFile);
    APROPPolicy->mergeDefaults(defaults);

//    INSTR              =APROPPolicy->getString("INSTR");
//    strncpy(APROP->INSTRUMENT,INSTR.c_str(), CL_APROP::STRING_LENGTH);
    CMODE              =APROPPolicy->getString("CRPIXMODE");
    strncpy(APROP->CRPIXMODE,CMODE.c_str(), CL_APROP::STRING_LENGTH);
    OAMODE             =APROPPolicy->getString("OAMODE");
    strncpy(APROP->OAMODE,OAMODE.c_str(), CL_APROP::STRING_LENGTH);
    APROP->CCDNUM      =APROPPolicy->getInt("NCCD");
    APROP->CCDPOSMODE  =APROPPolicy->getInt("CCDPMODE");
    APROP->REJMODE     =APROPPolicy->getInt("REJMODE");
    APROP->CRPIX[0]    =APROPPolicy->getDouble("CRPIX1");
    APROP->CRPIX[1]    =APROPPolicy->getDouble("CRPIX2");
    APROP->CRVAL[0]    =APROPPolicy->getDouble("CRVAL1");
    APROP->CRVAL[1]    =APROPPolicy->getDouble("CRVAL2");
    APROP->SIP_L_ORDER =APROPPolicy->getInt("LSIPORDER");
    APROP->SIP_ORDER   =APROPPolicy->getInt("SIPORDER");
    APROP->SIP_P_ORDER =APROPPolicy->getInt("PSIPORDER");
    APROP->SIP_ORDER_INIT  =APROPPolicy->getInt("ISIPORDER");
    APROP->SIP_P_ORDER_INIT=APROPPolicy->getInt("IPSIPORDER");
    APROP->CLIP_SIGMA  =APROPPolicy->getDouble("CLIPSIGMA");
    APROP->BASISPOS[0] =APROPPolicy->getDouble("BASISPOSX");
    APROP->BASISPOS[1] =APROPPolicy->getDouble("BASISPOSY");
    APROP->BASISPOS[2] =APROPPolicy->getDouble("BASISPOST");
    APROP->STDOUT      =APROPPolicy->getInt("STDOUT");
    APROP->CHECKPARAM  = 0;
    APROP->ALLREFNUM   = 0;
    APROP->ALLFITNUM   = 0;
}
void    F_WCSA_MAKEGSIP(lsst::pex::policy::Policy::Ptr &APROPPolicy, lsst::afw::cameraGeom::Camera::Ptr &camera, CL_APROP *APROP, CL_GSIP *GSIP){
    int CID;

    GSIP->F_WCSA_GSIP_SET0();

//double GPOSAVE[2];
//GPOSAVE[0]=GPOSAVE[1]=0;
    for(camGeom::Camera::const_iterator iter(camera->begin()); iter != camera->end(); ++iter) { 
        camGeom::DetectorMosaic::Ptr detMosaic = boost::shared_dynamic_cast<camGeom::DetectorMosaic>(*iter);

        for(CID=0;CID<APROP->CCDNUM;CID++){
            camGeom::Id detId = camGeom::Id(CID);//serial
            camGeom::Detector::Ptr det = detMosaic->findDetector(detId);
            afwGeom::Point2D offsetXY = det->getCenter().getPixels(det->getPixelSize());
//            double ccdTiltYaw = (det->getOrientation()).getYaw();
  //          int ccdTiltNQuarter = (det->getOrientation()).getNQuarter();

            GSIP->CSIP[CID].ID=detId.getSerial();
            GSIP->CSIP[CID].GPOS[0]=offsetXY[0];
            GSIP->CSIP[CID].GPOS[1]=offsetXY[1];
            GSIP->CSIP[CID].GPOS[2]=0;//ccdTiltNQuarter * 90.0;//?
            GSIP->CSIP[CID].POSID[0]=detId.getIndex().first;
            GSIP->CSIP[CID].POSID[1]=detId.getIndex().second;
        }
    }
//INITIAL POSITION
    lsst::pex::policy::DefaultPolicyFile const defaultsFile("solvetansip", "WCS_MAKEAPROP_Dictionary.paf","policy");
    lsst::pex::policy::Policy const defaults(defaultsFile);
    APROPPolicy->mergeDefaults(defaults);

    char GPOSX[100],GPOSY[100],GPOST[100];
    
    if(APROP->CCDNUM<11){
        for(CID=0;CID<APROP->CCDNUM;CID++){
            sprintf(GPOSX,"SCIGPOS%03d_X",CID);
            sprintf(GPOSY,"SCIGPOS%03d_Y",CID);
            sprintf(GPOST,"SCIGPOS%03d_T",CID);
            GSIP->CSIP[CID].GPOS[0]=GSIP->CSIP[CID].GPOS_INIT[0]=APROPPolicy->getDouble(GPOSX);
            GSIP->CSIP[CID].GPOS[1]=GSIP->CSIP[CID].GPOS_INIT[1]=APROPPolicy->getDouble(GPOSY);
            GSIP->CSIP[CID].GPOS[2]=GSIP->CSIP[CID].GPOS_INIT[2]=APROPPolicy->getDouble(GPOST);
        }
    }else{
        for(CID=0;CID<APROP->CCDNUM;CID++){
            sprintf(GPOSX,"HSCIGPOS%03d_X",CID);
            sprintf(GPOSY,"HSCIGPOS%03d_Y",CID);
            sprintf(GPOST,"HSCIGPOS%03d_T",CID);
            GSIP->CSIP[CID].GPOS[0]=GSIP->CSIP[CID].GPOS_INIT[0]=APROPPolicy->getDouble(GPOSX);
            GSIP->CSIP[CID].GPOS[1]=GSIP->CSIP[CID].GPOS_INIT[1]=APROPPolicy->getDouble(GPOSY);
            GSIP->CSIP[CID].GPOS[2]=GSIP->CSIP[CID].GPOS_INIT[2]=APROPPolicy->getDouble(GPOST);
        }
    }

//INITIAL DISTORTION
    if(APROP->CCDNUM<11){
    GSIP->SIP_ORDER_INIT     =5;
    GSIP->SIP_P_ORDER_INIT   =5;
    GSIP->CD_INIT[0][0]      =-5.6e-9;
    GSIP->CD_INIT[0][1]      = 0;
    GSIP->CD_INIT[1][0]      = 0;
    GSIP->CD_INIT[1][1]      = 5.6e-9;
    }else{
    GSIP->SIP_ORDER_INIT     =APROPPolicy->getInt("ISIPORDER");
    GSIP->SIP_P_ORDER_INIT   =APROPPolicy->getInt("IPSIPORDER");
    GSIP->MAXFRAD_INIT       =APROPPolicy->getDouble("IMAXFRAD");
    GSIP->CD_INIT[0][0]      =APROPPolicy->getDouble("ICD_1_1");
    GSIP->CD_INIT[0][1]      =APROPPolicy->getDouble("ICD_1_2");
    GSIP->CD_INIT[1][0]      =APROPPolicy->getDouble("ICD_2_1");
    GSIP->CD_INIT[1][1]      =APROPPolicy->getDouble("ICD_2_2");
    GSIP->InvCD_INIT[0][0]   = GSIP->CD_INIT[1][1]/(GSIP->CD_INIT[0][0]*GSIP->CD_INIT[1][1]-GSIP->CD_INIT[1][0]*GSIP->CD_INIT[0][1]);
    GSIP->InvCD_INIT[0][1]   =-GSIP->CD_INIT[0][1]/(GSIP->CD_INIT[0][0]*GSIP->CD_INIT[1][1]-GSIP->CD_INIT[1][0]*GSIP->CD_INIT[0][1]);
    GSIP->InvCD_INIT[1][0]   =-GSIP->CD_INIT[1][0]/(GSIP->CD_INIT[0][0]*GSIP->CD_INIT[1][1]-GSIP->CD_INIT[1][0]*GSIP->CD_INIT[0][1]);
    GSIP->InvCD_INIT[1][1]   = GSIP->CD_INIT[0][0]/(GSIP->CD_INIT[0][0]*GSIP->CD_INIT[1][1]-GSIP->CD_INIT[1][0]*GSIP->CD_INIT[0][1]);
    GSIP->SIP_AB_INIT[0][ 0] =APROPPolicy->getDouble("IA_0_0");
    GSIP->SIP_AB_INIT[0][ 1] =APROPPolicy->getDouble("IA_0_1");
    GSIP->SIP_AB_INIT[0][ 2] =APROPPolicy->getDouble("IA_0_2");
    GSIP->SIP_AB_INIT[0][ 3] =APROPPolicy->getDouble("IA_0_3");
    GSIP->SIP_AB_INIT[0][ 4] =APROPPolicy->getDouble("IA_0_4");
    GSIP->SIP_AB_INIT[0][ 5] =APROPPolicy->getDouble("IA_0_5");
    GSIP->SIP_AB_INIT[0][ 6] =APROPPolicy->getDouble("IA_0_6");
    GSIP->SIP_AB_INIT[0][ 7] =APROPPolicy->getDouble("IA_0_7");
    GSIP->SIP_AB_INIT[0][ 8] =APROPPolicy->getDouble("IA_0_8");
    GSIP->SIP_AB_INIT[0][ 9] =APROPPolicy->getDouble("IA_0_9");
    GSIP->SIP_AB_INIT[0][10] =APROPPolicy->getDouble("IA_1_0");
    GSIP->SIP_AB_INIT[0][11] =APROPPolicy->getDouble("IA_1_1");
    GSIP->SIP_AB_INIT[0][12] =APROPPolicy->getDouble("IA_1_2");
    GSIP->SIP_AB_INIT[0][13] =APROPPolicy->getDouble("IA_1_3");
    GSIP->SIP_AB_INIT[0][14] =APROPPolicy->getDouble("IA_1_4");
    GSIP->SIP_AB_INIT[0][15] =APROPPolicy->getDouble("IA_1_5");
    GSIP->SIP_AB_INIT[0][16] =APROPPolicy->getDouble("IA_1_6");
    GSIP->SIP_AB_INIT[0][17] =APROPPolicy->getDouble("IA_1_7");
    GSIP->SIP_AB_INIT[0][18] =APROPPolicy->getDouble("IA_1_8");
    GSIP->SIP_AB_INIT[0][19] =APROPPolicy->getDouble("IA_2_0");
    GSIP->SIP_AB_INIT[0][10] =APROPPolicy->getDouble("IA_2_1");
    GSIP->SIP_AB_INIT[0][21] =APROPPolicy->getDouble("IA_2_2");
    GSIP->SIP_AB_INIT[0][22] =APROPPolicy->getDouble("IA_2_3");
    GSIP->SIP_AB_INIT[0][23] =APROPPolicy->getDouble("IA_2_4");
    GSIP->SIP_AB_INIT[0][24] =APROPPolicy->getDouble("IA_2_5");
    GSIP->SIP_AB_INIT[0][25] =APROPPolicy->getDouble("IA_2_6");
    GSIP->SIP_AB_INIT[0][26] =APROPPolicy->getDouble("IA_2_7");
    GSIP->SIP_AB_INIT[0][27] =APROPPolicy->getDouble("IA_3_0");
    GSIP->SIP_AB_INIT[0][28] =APROPPolicy->getDouble("IA_3_1");
    GSIP->SIP_AB_INIT[0][29] =APROPPolicy->getDouble("IA_3_2");
    GSIP->SIP_AB_INIT[0][30] =APROPPolicy->getDouble("IA_3_3");
    GSIP->SIP_AB_INIT[0][31] =APROPPolicy->getDouble("IA_3_4");
    GSIP->SIP_AB_INIT[0][32] =APROPPolicy->getDouble("IA_3_5");
    GSIP->SIP_AB_INIT[0][33] =APROPPolicy->getDouble("IA_3_6");
    GSIP->SIP_AB_INIT[0][34] =APROPPolicy->getDouble("IA_4_0");
    GSIP->SIP_AB_INIT[0][35] =APROPPolicy->getDouble("IA_4_1");
    GSIP->SIP_AB_INIT[0][36] =APROPPolicy->getDouble("IA_4_2");
    GSIP->SIP_AB_INIT[0][37] =APROPPolicy->getDouble("IA_4_3");
    GSIP->SIP_AB_INIT[0][38] =APROPPolicy->getDouble("IA_4_4");
    GSIP->SIP_AB_INIT[0][39] =APROPPolicy->getDouble("IA_4_5");
    GSIP->SIP_AB_INIT[0][40] =APROPPolicy->getDouble("IA_5_0");
    GSIP->SIP_AB_INIT[0][41] =APROPPolicy->getDouble("IA_5_1");
    GSIP->SIP_AB_INIT[0][42] =APROPPolicy->getDouble("IA_5_2");
    GSIP->SIP_AB_INIT[0][43] =APROPPolicy->getDouble("IA_5_3");
    GSIP->SIP_AB_INIT[0][44] =APROPPolicy->getDouble("IA_5_4");
    GSIP->SIP_AB_INIT[0][45] =APROPPolicy->getDouble("IA_6_0");
    GSIP->SIP_AB_INIT[0][46] =APROPPolicy->getDouble("IA_6_1");
    GSIP->SIP_AB_INIT[0][47] =APROPPolicy->getDouble("IA_6_2");
    GSIP->SIP_AB_INIT[0][48] =APROPPolicy->getDouble("IA_6_3");
    GSIP->SIP_AB_INIT[0][49] =APROPPolicy->getDouble("IA_7_0");
    GSIP->SIP_AB_INIT[0][50] =APROPPolicy->getDouble("IA_7_1");
    GSIP->SIP_AB_INIT[0][51] =APROPPolicy->getDouble("IA_7_2");
    GSIP->SIP_AB_INIT[0][52] =APROPPolicy->getDouble("IA_8_0");
    GSIP->SIP_AB_INIT[0][53] =APROPPolicy->getDouble("IA_8_1");
    GSIP->SIP_AB_INIT[0][54] =APROPPolicy->getDouble("IA_9_0");
    GSIP->SIP_AB_INIT[1][ 0] =APROPPolicy->getDouble("IB_0_0");
    GSIP->SIP_AB_INIT[1][ 1] =APROPPolicy->getDouble("IB_0_1");
    GSIP->SIP_AB_INIT[1][ 2] =APROPPolicy->getDouble("IB_0_2");
    GSIP->SIP_AB_INIT[1][ 3] =APROPPolicy->getDouble("IB_0_3");
    GSIP->SIP_AB_INIT[1][ 4] =APROPPolicy->getDouble("IB_0_4");
    GSIP->SIP_AB_INIT[1][ 5] =APROPPolicy->getDouble("IB_0_5");
    GSIP->SIP_AB_INIT[1][ 6] =APROPPolicy->getDouble("IB_0_6");
    GSIP->SIP_AB_INIT[1][ 7] =APROPPolicy->getDouble("IB_0_7");
    GSIP->SIP_AB_INIT[1][ 8] =APROPPolicy->getDouble("IB_0_8");
    GSIP->SIP_AB_INIT[1][ 9] =APROPPolicy->getDouble("IB_0_9");
    GSIP->SIP_AB_INIT[1][10] =APROPPolicy->getDouble("IB_1_0");
    GSIP->SIP_AB_INIT[1][11] =APROPPolicy->getDouble("IB_1_1");
    GSIP->SIP_AB_INIT[1][12] =APROPPolicy->getDouble("IB_1_2");
    GSIP->SIP_AB_INIT[1][13] =APROPPolicy->getDouble("IB_1_3");
    GSIP->SIP_AB_INIT[1][14] =APROPPolicy->getDouble("IB_1_4");
    GSIP->SIP_AB_INIT[1][15] =APROPPolicy->getDouble("IB_1_5");
    GSIP->SIP_AB_INIT[1][16] =APROPPolicy->getDouble("IB_1_6");
    GSIP->SIP_AB_INIT[1][17] =APROPPolicy->getDouble("IB_1_7");
    GSIP->SIP_AB_INIT[1][18] =APROPPolicy->getDouble("IB_1_8");
    GSIP->SIP_AB_INIT[1][19] =APROPPolicy->getDouble("IB_2_0");
    GSIP->SIP_AB_INIT[1][10] =APROPPolicy->getDouble("IB_2_1");
    GSIP->SIP_AB_INIT[1][21] =APROPPolicy->getDouble("IB_2_2");
    GSIP->SIP_AB_INIT[1][22] =APROPPolicy->getDouble("IB_2_3");
    GSIP->SIP_AB_INIT[1][23] =APROPPolicy->getDouble("IB_2_4");
    GSIP->SIP_AB_INIT[1][24] =APROPPolicy->getDouble("IB_2_5");
    GSIP->SIP_AB_INIT[1][25] =APROPPolicy->getDouble("IB_2_6");
    GSIP->SIP_AB_INIT[1][26] =APROPPolicy->getDouble("IB_2_7");
    GSIP->SIP_AB_INIT[1][27] =APROPPolicy->getDouble("IB_3_0");
    GSIP->SIP_AB_INIT[1][28] =APROPPolicy->getDouble("IB_3_1");
    GSIP->SIP_AB_INIT[1][29] =APROPPolicy->getDouble("IB_3_2");
    GSIP->SIP_AB_INIT[1][30] =APROPPolicy->getDouble("IB_3_3");
    GSIP->SIP_AB_INIT[1][31] =APROPPolicy->getDouble("IB_3_4");
    GSIP->SIP_AB_INIT[1][32] =APROPPolicy->getDouble("IB_3_5");
    GSIP->SIP_AB_INIT[1][33] =APROPPolicy->getDouble("IB_3_6");
    GSIP->SIP_AB_INIT[1][34] =APROPPolicy->getDouble("IB_4_0");
    GSIP->SIP_AB_INIT[1][35] =APROPPolicy->getDouble("IB_4_1");
    GSIP->SIP_AB_INIT[1][36] =APROPPolicy->getDouble("IB_4_2");
    GSIP->SIP_AB_INIT[1][37] =APROPPolicy->getDouble("IB_4_3");
    GSIP->SIP_AB_INIT[1][38] =APROPPolicy->getDouble("IB_4_4");
    GSIP->SIP_AB_INIT[1][39] =APROPPolicy->getDouble("IB_4_5");
    GSIP->SIP_AB_INIT[1][40] =APROPPolicy->getDouble("IB_5_0");
    GSIP->SIP_AB_INIT[1][41] =APROPPolicy->getDouble("IB_5_1");
    GSIP->SIP_AB_INIT[1][42] =APROPPolicy->getDouble("IB_5_2");
    GSIP->SIP_AB_INIT[1][43] =APROPPolicy->getDouble("IB_5_3");
    GSIP->SIP_AB_INIT[1][44] =APROPPolicy->getDouble("IB_5_4");
    GSIP->SIP_AB_INIT[1][45] =APROPPolicy->getDouble("IB_6_0");
    GSIP->SIP_AB_INIT[1][46] =APROPPolicy->getDouble("IB_6_1");
    GSIP->SIP_AB_INIT[1][47] =APROPPolicy->getDouble("IB_6_2");
    GSIP->SIP_AB_INIT[1][48] =APROPPolicy->getDouble("IB_6_3");
    GSIP->SIP_AB_INIT[1][49] =APROPPolicy->getDouble("IB_7_0");
    GSIP->SIP_AB_INIT[1][50] =APROPPolicy->getDouble("IB_7_1");
    GSIP->SIP_AB_INIT[1][51] =APROPPolicy->getDouble("IB_7_2");
    GSIP->SIP_AB_INIT[1][52] =APROPPolicy->getDouble("IB_8_0");
    GSIP->SIP_AB_INIT[1][53] =APROPPolicy->getDouble("IB_8_1");
    GSIP->SIP_AB_INIT[1][54] =APROPPolicy->getDouble("IB_9_0");
    GSIP->SIP_ABP_INIT[0][ 0]=APROPPolicy->getDouble("IAP_0_0");
    GSIP->SIP_ABP_INIT[0][ 1]=APROPPolicy->getDouble("IAP_0_1");
    GSIP->SIP_ABP_INIT[0][ 2]=APROPPolicy->getDouble("IAP_0_2");
    GSIP->SIP_ABP_INIT[0][ 3]=APROPPolicy->getDouble("IAP_0_3");
    GSIP->SIP_ABP_INIT[0][ 4]=APROPPolicy->getDouble("IAP_0_4");
    GSIP->SIP_ABP_INIT[0][ 5]=APROPPolicy->getDouble("IAP_0_5");
    GSIP->SIP_ABP_INIT[0][ 6]=APROPPolicy->getDouble("IAP_0_6");
    GSIP->SIP_ABP_INIT[0][ 7]=APROPPolicy->getDouble("IAP_0_7");
    GSIP->SIP_ABP_INIT[0][ 8]=APROPPolicy->getDouble("IAP_0_8");
    GSIP->SIP_ABP_INIT[0][ 9]=APROPPolicy->getDouble("IAP_0_9");
    GSIP->SIP_ABP_INIT[0][10]=APROPPolicy->getDouble("IAP_1_0");
    GSIP->SIP_ABP_INIT[0][11]=APROPPolicy->getDouble("IAP_1_1");
    GSIP->SIP_ABP_INIT[0][12]=APROPPolicy->getDouble("IAP_1_2");
    GSIP->SIP_ABP_INIT[0][13]=APROPPolicy->getDouble("IAP_1_3");
    GSIP->SIP_ABP_INIT[0][14]=APROPPolicy->getDouble("IAP_1_4");
    GSIP->SIP_ABP_INIT[0][15]=APROPPolicy->getDouble("IAP_1_5");
    GSIP->SIP_ABP_INIT[0][16]=APROPPolicy->getDouble("IAP_1_6");
    GSIP->SIP_ABP_INIT[0][17]=APROPPolicy->getDouble("IAP_1_7");
    GSIP->SIP_ABP_INIT[0][18]=APROPPolicy->getDouble("IAP_1_8");
    GSIP->SIP_ABP_INIT[0][19]=APROPPolicy->getDouble("IAP_2_0");
    GSIP->SIP_ABP_INIT[0][10]=APROPPolicy->getDouble("IAP_2_1");
    GSIP->SIP_ABP_INIT[0][21]=APROPPolicy->getDouble("IAP_2_2");
    GSIP->SIP_ABP_INIT[0][22]=APROPPolicy->getDouble("IAP_2_3");
    GSIP->SIP_ABP_INIT[0][23]=APROPPolicy->getDouble("IAP_2_4");
    GSIP->SIP_ABP_INIT[0][24]=APROPPolicy->getDouble("IAP_2_5");
    GSIP->SIP_ABP_INIT[0][25]=APROPPolicy->getDouble("IAP_2_6");
    GSIP->SIP_ABP_INIT[0][26]=APROPPolicy->getDouble("IAP_2_7");
    GSIP->SIP_ABP_INIT[0][27]=APROPPolicy->getDouble("IAP_3_0");
    GSIP->SIP_ABP_INIT[0][28]=APROPPolicy->getDouble("IAP_3_1");
    GSIP->SIP_ABP_INIT[0][29]=APROPPolicy->getDouble("IAP_3_2");
    GSIP->SIP_ABP_INIT[0][30]=APROPPolicy->getDouble("IAP_3_3");
    GSIP->SIP_ABP_INIT[0][31]=APROPPolicy->getDouble("IAP_3_4");
    GSIP->SIP_ABP_INIT[0][32]=APROPPolicy->getDouble("IAP_3_5");
    GSIP->SIP_ABP_INIT[0][33]=APROPPolicy->getDouble("IAP_3_6");
    GSIP->SIP_ABP_INIT[0][34]=APROPPolicy->getDouble("IAP_4_0");
    GSIP->SIP_ABP_INIT[0][35]=APROPPolicy->getDouble("IAP_4_1");
    GSIP->SIP_ABP_INIT[0][36]=APROPPolicy->getDouble("IAP_4_2");
    GSIP->SIP_ABP_INIT[0][37]=APROPPolicy->getDouble("IAP_4_3");
    GSIP->SIP_ABP_INIT[0][38]=APROPPolicy->getDouble("IAP_4_4");
    GSIP->SIP_ABP_INIT[0][39]=APROPPolicy->getDouble("IAP_4_5");
    GSIP->SIP_ABP_INIT[0][40]=APROPPolicy->getDouble("IAP_5_0");
    GSIP->SIP_ABP_INIT[0][41]=APROPPolicy->getDouble("IAP_5_1");
    GSIP->SIP_ABP_INIT[0][42]=APROPPolicy->getDouble("IAP_5_2");
    GSIP->SIP_ABP_INIT[0][43]=APROPPolicy->getDouble("IAP_5_3");
    GSIP->SIP_ABP_INIT[0][44]=APROPPolicy->getDouble("IAP_5_4");
    GSIP->SIP_ABP_INIT[0][45]=APROPPolicy->getDouble("IAP_6_0");
    GSIP->SIP_ABP_INIT[0][46]=APROPPolicy->getDouble("IAP_6_1");
    GSIP->SIP_ABP_INIT[0][47]=APROPPolicy->getDouble("IAP_6_2");
    GSIP->SIP_ABP_INIT[0][48]=APROPPolicy->getDouble("IAP_6_3");
    GSIP->SIP_ABP_INIT[0][49]=APROPPolicy->getDouble("IAP_7_0");
    GSIP->SIP_ABP_INIT[0][50]=APROPPolicy->getDouble("IAP_7_1");
    GSIP->SIP_ABP_INIT[0][51]=APROPPolicy->getDouble("IAP_7_2");
    GSIP->SIP_ABP_INIT[0][52]=APROPPolicy->getDouble("IAP_8_0");
    GSIP->SIP_ABP_INIT[0][53]=APROPPolicy->getDouble("IAP_8_1");
    GSIP->SIP_ABP_INIT[0][54]=APROPPolicy->getDouble("IAP_9_0");
    GSIP->SIP_ABP_INIT[1][ 0]=APROPPolicy->getDouble("IBP_0_0");
    GSIP->SIP_ABP_INIT[1][ 1]=APROPPolicy->getDouble("IBP_0_1");
    GSIP->SIP_ABP_INIT[1][ 2]=APROPPolicy->getDouble("IBP_0_2");
    GSIP->SIP_ABP_INIT[1][ 3]=APROPPolicy->getDouble("IBP_0_3");
    GSIP->SIP_ABP_INIT[1][ 4]=APROPPolicy->getDouble("IBP_0_4");
    GSIP->SIP_ABP_INIT[1][ 5]=APROPPolicy->getDouble("IBP_0_5");
    GSIP->SIP_ABP_INIT[1][ 6]=APROPPolicy->getDouble("IBP_0_6");
    GSIP->SIP_ABP_INIT[1][ 7]=APROPPolicy->getDouble("IBP_0_7");
    GSIP->SIP_ABP_INIT[1][ 8]=APROPPolicy->getDouble("IBP_0_8");
    GSIP->SIP_ABP_INIT[1][ 9]=APROPPolicy->getDouble("IBP_0_9");
    GSIP->SIP_ABP_INIT[1][10]=APROPPolicy->getDouble("IBP_1_0");
    GSIP->SIP_ABP_INIT[1][11]=APROPPolicy->getDouble("IBP_1_1");
    GSIP->SIP_ABP_INIT[1][12]=APROPPolicy->getDouble("IBP_1_2");
    GSIP->SIP_ABP_INIT[1][13]=APROPPolicy->getDouble("IBP_1_3");
    GSIP->SIP_ABP_INIT[1][14]=APROPPolicy->getDouble("IBP_1_4");
    GSIP->SIP_ABP_INIT[1][15]=APROPPolicy->getDouble("IBP_1_5");
    GSIP->SIP_ABP_INIT[1][16]=APROPPolicy->getDouble("IBP_1_6");
    GSIP->SIP_ABP_INIT[1][17]=APROPPolicy->getDouble("IBP_1_7");
    GSIP->SIP_ABP_INIT[1][18]=APROPPolicy->getDouble("IBP_1_8");
    GSIP->SIP_ABP_INIT[1][19]=APROPPolicy->getDouble("IBP_2_0");
    GSIP->SIP_ABP_INIT[1][10]=APROPPolicy->getDouble("IBP_2_1");
    GSIP->SIP_ABP_INIT[1][21]=APROPPolicy->getDouble("IBP_2_2");
    GSIP->SIP_ABP_INIT[1][22]=APROPPolicy->getDouble("IBP_2_3");
    GSIP->SIP_ABP_INIT[1][23]=APROPPolicy->getDouble("IBP_2_4");
    GSIP->SIP_ABP_INIT[1][24]=APROPPolicy->getDouble("IBP_2_5");
    GSIP->SIP_ABP_INIT[1][25]=APROPPolicy->getDouble("IBP_2_6");
    GSIP->SIP_ABP_INIT[1][26]=APROPPolicy->getDouble("IBP_2_7");
    GSIP->SIP_ABP_INIT[1][27]=APROPPolicy->getDouble("IBP_3_0");
    GSIP->SIP_ABP_INIT[1][28]=APROPPolicy->getDouble("IBP_3_1");
    GSIP->SIP_ABP_INIT[1][29]=APROPPolicy->getDouble("IBP_3_2");
    GSIP->SIP_ABP_INIT[1][30]=APROPPolicy->getDouble("IBP_3_3");
    GSIP->SIP_ABP_INIT[1][31]=APROPPolicy->getDouble("IBP_3_4");
    GSIP->SIP_ABP_INIT[1][32]=APROPPolicy->getDouble("IBP_3_5");
    GSIP->SIP_ABP_INIT[1][33]=APROPPolicy->getDouble("IBP_3_6");
    GSIP->SIP_ABP_INIT[1][34]=APROPPolicy->getDouble("IBP_4_0");
    GSIP->SIP_ABP_INIT[1][35]=APROPPolicy->getDouble("IBP_4_1");
    GSIP->SIP_ABP_INIT[1][36]=APROPPolicy->getDouble("IBP_4_2");
    GSIP->SIP_ABP_INIT[1][37]=APROPPolicy->getDouble("IBP_4_3");
    GSIP->SIP_ABP_INIT[1][38]=APROPPolicy->getDouble("IBP_4_4");
    GSIP->SIP_ABP_INIT[1][39]=APROPPolicy->getDouble("IBP_4_5");
    GSIP->SIP_ABP_INIT[1][40]=APROPPolicy->getDouble("IBP_5_0");
    GSIP->SIP_ABP_INIT[1][41]=APROPPolicy->getDouble("IBP_5_1");
    GSIP->SIP_ABP_INIT[1][42]=APROPPolicy->getDouble("IBP_5_2");
    GSIP->SIP_ABP_INIT[1][43]=APROPPolicy->getDouble("IBP_5_3");
    GSIP->SIP_ABP_INIT[1][44]=APROPPolicy->getDouble("IBP_5_4");
    GSIP->SIP_ABP_INIT[1][45]=APROPPolicy->getDouble("IBP_6_0");
    GSIP->SIP_ABP_INIT[1][46]=APROPPolicy->getDouble("IBP_6_1");
    GSIP->SIP_ABP_INIT[1][47]=APROPPolicy->getDouble("IBP_6_2");
    GSIP->SIP_ABP_INIT[1][48]=APROPPolicy->getDouble("IBP_6_3");
    GSIP->SIP_ABP_INIT[1][49]=APROPPolicy->getDouble("IBP_7_0");
    GSIP->SIP_ABP_INIT[1][50]=APROPPolicy->getDouble("IBP_7_1");
    GSIP->SIP_ABP_INIT[1][51]=APROPPolicy->getDouble("IBP_7_2");
    GSIP->SIP_ABP_INIT[1][52]=APROPPolicy->getDouble("IBP_8_0");
    GSIP->SIP_ABP_INIT[1][53]=APROPPolicy->getDouble("IBP_8_1");
    GSIP->SIP_ABP_INIT[1][54]=APROPPolicy->getDouble("IBP_9_0");
    }
/*
cout << "INIT" << endl;
cout << GSIP->SIP_ORDER_INIT      << endl;
cout << GSIP->SIP_P_ORDER_INIT    << endl;
cout << GSIP->MAXFRAD_INIT        << endl;
cout << GSIP->CD_INIT[0][0]       << endl;
cout << GSIP->CD_INIT[0][1]       << endl;
cout << GSIP->CD_INIT[1][0]       << endl;
cout << GSIP->CD_INIT[1][1]       << endl;
cout << GSIP->InvCD_INIT[0][0]    << endl;
cout << GSIP->InvCD_INIT[0][1]    << endl;
cout << GSIP->InvCD_INIT[1][0]    << endl;
cout << GSIP->InvCD_INIT[1][1]    << endl;
int i,j;
for(i=0;i<2;i++)
for(j=0;j<55;j++)
cout << GSIP->SIP_AB_INIT[i][j] << endl;
for(i=0;i<2;i++)
for(j=0;j<55;j++)
cout << GSIP->SIP_ABP_INIT[i][j] << endl;
*/
}
void    F_WCSA_SETREFSIZE(vector<vector<PTR(hsc::meas::tansip::SourceMatch)> > const &matchlist, CL_APROP* APROP){
    int ID;
    for(ID=0;ID<APROP->CCDNUM;ID++){
        APROP->REFNUM[ID]     =matchlist[ID].size();
        APROP->FITNUM[ID]     =matchlist[ID].size();
        APROP->ALLREFNUM     +=matchlist[ID].size();
    }
        APROP->ALLFITNUM=APROP->ALLREFNUM;
    if(APROP->STDOUT==2)cout << "ALLREFNUM:" << APROP->ALLREFNUM << endl;
}
/*DEL*/
/*void    F_WCSA_SETSIZE(vector<vector<PTR(hsc::meas::tansip::SourceMatch)> > const &matchlist, CL_APROP* APROP, CL_GSIP *GSIP){
    int ID;
    for(ID=0;ID<APROP->CCDNUM;ID++){
        APROP->REFNUM[ID]     =matchlist[ID].size();
        APROP->FITNUM[ID]     =matchlist[ID].size();
        APROP->ALLREFNUM     +=matchlist[ID].size();
        GSIP->CSIP[ID].REFNUM =matchlist[ID].size();
        GSIP->CSIP[ID].FITNUM =matchlist[ID].size();
    }
        APROP->ALLFITNUM=APROP->ALLREFNUM;
         GSIP->ALLREFNUM=APROP->ALLREFNUM;
         GSIP->ALLFITNUM=APROP->ALLFITNUM;
}*/
void    F_WCSA_SETREFSIZE_local(string matchlist, CL_APROP* APROP){
    int CID,*CIDNUM;
    char cID[100],cCID[100],cx[100],cy[100],cRA[100],cDEC[100];
    ifstream in;

    CIDNUM = new int[APROP->CCDNUM+1];
    for(CID=0;CID<APROP->CCDNUM+1;CID++)
    CIDNUM[CID]=0;

    in.open(matchlist.c_str());
    while((in >> cID >> cCID >> cx >> cy >> cRA >> cDEC)!=0){
	CID=atoi(cCID);
        CIDNUM[CID]++;
        CIDNUM[APROP->CCDNUM]++;
    }

    for(CID=0;CID<APROP->CCDNUM;CID++){
    APROP->REFNUM[CID]     = CIDNUM[CID];
    APROP->FITNUM[CID]     = CIDNUM[CID];
    }

    APROP->ALLREFNUM = CIDNUM[APROP->CCDNUM];
    APROP->ALLFITNUM = CIDNUM[APROP->CCDNUM];
    in.close();
    if(APROP->STDOUT==2)cout << "ALLREFNUM:" << APROP->ALLREFNUM << endl;

    delete [] CIDNUM;
}
/*DEL*/
/*void    F_WCSA_SETSIZE_local(string matchlist, CL_APROP* APROP, CL_GSIP *GSIP){
    int ID,CID,*CIDNUM;
    double x,y,RA,DEC;
    ifstream in;

    CIDNUM = new int[APROP->CCDNUM+1];
    for(CID=0;CID<APROP->CCDNUM+1;CID++)
    CIDNUM[CID]=0;

    in.open(matchlist.c_str());
    while((in >> ID >> CID >> x >> y >> RA >> DEC)!=0){
        CIDNUM[CID]++;
        CIDNUM[APROP->CCDNUM]++;
    }

    for(CID=0;CID<APROP->CCDNUM;CID++){
    APROP->REFNUM[CID]     = CIDNUM[CID];
    APROP->FITNUM[CID]     = CIDNUM[CID];
    GSIP->CSIP[CID].REFNUM = CIDNUM[CID];
    GSIP->CSIP[CID].FITNUM = CIDNUM[CID];
    }

    APROP->ALLREFNUM = CIDNUM[APROP->CCDNUM];
    APROP->ALLFITNUM = CIDNUM[APROP->CCDNUM];
    GSIP->ALLREFNUM  = APROP->ALLREFNUM;
    GSIP->ALLFITNUM  = APROP->ALLFITNUM;
    in.close();

    delete [] CIDNUM;
}*/
#define PI (4*atan(1.0))
void    F_WCSA_MAKEPAIR(vector<vector<PTR(hsc::meas::tansip::SourceMatch)> > const &matchlist,CL_APROP* APROP,CL_APAIR* APAIR){
    int CID,NUM,ALLNUM;

    APAIR->F_WCSA_APAIR_SET0();
    ALLNUM=0;

    for(CID=0;CID<APAIR->CCDNUM;CID++)
    for(NUM=0;NUM<APROP->REFNUM[CID];NUM++){
        APAIR->PAIR[ALLNUM].ID            = matchlist[CID][NUM]->getId();
        APAIR->PAIR[ALLNUM].CHIPID        = CID;
        APAIR->PAIR[ALLNUM].FLAG          = 1;
        APAIR->PAIR[ALLNUM].X_RADEC[0]    = matchlist[CID][NUM]->getRa();
        APAIR->PAIR[ALLNUM].X_RADEC[1]    = matchlist[CID][NUM]->getDec();
        APAIR->PAIR[ALLNUM].X_LOCAL[0]    = matchlist[CID][NUM]->getX();
        APAIR->PAIR[ALLNUM].X_LOCAL[1]    = matchlist[CID][NUM]->getY();
        APAIR->PAIR[ALLNUM].X_LOCALERR[0] = matchlist[CID][NUM]->getXErr();
        APAIR->PAIR[ALLNUM].X_LOCALERR[1] = matchlist[CID][NUM]->getYErr();
        APAIR->PAIR[ALLNUM].X_RADECERR[0] = 1;
        APAIR->PAIR[ALLNUM].X_RADECERR[1] = 1;
        if(isnan(APAIR->PAIR[ALLNUM].ID)||isinf(APAIR->PAIR[ALLNUM].ID)||
           isnan(APAIR->PAIR[ALLNUM].CHIPID)||isinf(APAIR->PAIR[ALLNUM].CHIPID)||
           isnan(APAIR->PAIR[ALLNUM].X_RADEC[0])||isinf(APAIR->PAIR[ALLNUM].X_RADEC[0])||
           isnan(APAIR->PAIR[ALLNUM].X_RADEC[1])||isinf(APAIR->PAIR[ALLNUM].X_RADEC[1])||
           isnan(APAIR->PAIR[ALLNUM].X_LOCAL[0])||isinf(APAIR->PAIR[ALLNUM].X_LOCAL[0])||
           isnan(APAIR->PAIR[ALLNUM].X_LOCAL[1])||isinf(APAIR->PAIR[ALLNUM].X_LOCAL[1]))
        APAIR->PAIR[ALLNUM].FLAG=0;
//cout << fixed << APAIR->PAIR[ALLNUM].ID << "	" << APAIR->PAIR[ALLNUM].CHIPID << "	" << APAIR->PAIR[ALLNUM].X_LOCAL[0] << "	" << APAIR->PAIR[ALLNUM].X_LOCAL[1] << "	" << APAIR->PAIR[ALLNUM].X_RADEC[0] << "	" << APAIR->PAIR[ALLNUM].X_RADEC[1] << endl;
        ALLNUM+=1;
    }
}
void    F_WCSA_MAKEPAIR_local(string matchlist,CL_APAIR* APAIR){
    int ALLNUM;
    char cID[100],cCID[100],cx[100],cy[100],cRA[100],cDEC[100];
    ifstream in;

    APAIR->F_WCSA_APAIR_SET0();
    in.open(matchlist.c_str());
    cout << matchlist.c_str() << endl;
    ALLNUM=0;
    while((in >> cID >> cCID >> cx >> cy >> cRA >> cDEC)!=0){
        APAIR->PAIR[ALLNUM].ID           =atoi(cID);
        APAIR->PAIR[ALLNUM].CHIPID       =atoi(cCID);
        APAIR->PAIR[ALLNUM].FLAG         =1;
        APAIR->PAIR[ALLNUM].X_LOCAL[0]   =atof(cx);
        APAIR->PAIR[ALLNUM].X_LOCAL[1]   =atof(cy);
        APAIR->PAIR[ALLNUM].X_RADEC[0]   =atof(cRA);
        APAIR->PAIR[ALLNUM].X_RADEC[1]   =atof(cDEC);
        APAIR->PAIR[ALLNUM].X_LOCALERR[0]=1;
        APAIR->PAIR[ALLNUM].X_LOCALERR[1]=1;
        APAIR->PAIR[ALLNUM].X_RADECERR[0]=1;
        APAIR->PAIR[ALLNUM].X_RADECERR[1]=1;
        if(isnan(APAIR->PAIR[ALLNUM].ID)||isinf(APAIR->PAIR[ALLNUM].ID)||
           isnan(APAIR->PAIR[ALLNUM].CHIPID)||isinf(APAIR->PAIR[ALLNUM].CHIPID)||
           isnan(APAIR->PAIR[ALLNUM].X_RADEC[0])||isinf(APAIR->PAIR[ALLNUM].X_RADEC[0])||
           isnan(APAIR->PAIR[ALLNUM].X_RADEC[1])||isinf(APAIR->PAIR[ALLNUM].X_RADEC[1])||
           isnan(APAIR->PAIR[ALLNUM].X_LOCAL[0])||isinf(APAIR->PAIR[ALLNUM].X_LOCAL[0])||
           isnan(APAIR->PAIR[ALLNUM].X_LOCAL[1])||isinf(APAIR->PAIR[ALLNUM].X_LOCAL[1]))
        APAIR->PAIR[ALLNUM].FLAG=0;
//cout << fixed << APAIR->PAIR[ALLNUM].ID << "	" << APAIR->PAIR[ALLNUM].CHIPID << "	" <<APAIR->PAIR[ALLNUM].FLAG <<"	" << APAIR->PAIR[ALLNUM].X_LOCAL[0] << "	" << APAIR->PAIR[ALLNUM].X_LOCAL[1] << "	" << APAIR->PAIR[ALLNUM].X_RADEC[0] << "	" << APAIR->PAIR[ALLNUM].X_RADEC[1] << endl;
        ALLNUM++;
    }
}
dafbase::PropertySet::Ptr F_WCS_EMPTYMETADATA(){
    dafbase::PropertySet::Ptr metadata(new dafbase::PropertySet);
    return metadata;
}
#undef PI
afwImage::TanWcs::Ptr CL_WCSA_ASP::F_WCSA_PLMAIN_SETWCSPtr(int CID){
    int i,j;

    afwGeom::PointD crpix = afwGeom::PointD(GSIP->CSIP[CID].CRPIX[0], GSIP->CSIP[CID].CRPIX[1]);
    afwGeom::PointD crval = afwGeom::PointD(GSIP->CSIP[CID].CRVAL[0], GSIP->CSIP[CID].CRVAL[1]);

    Eigen::Matrix2d cdMatrix;
    cdMatrix << GSIP->CSIP[CID].CD[0][0], GSIP->CSIP[CID].CD[0][1], GSIP->CSIP[CID].CD[1][0], GSIP->CSIP[CID].CD[1][1];
    Eigen::MatrixXd sipA  = Eigen::MatrixXd::Zero(GSIP->SIP_ORDER+1, GSIP->SIP_ORDER+1 );
    Eigen::MatrixXd sipB  = Eigen::MatrixXd::Zero(GSIP->SIP_ORDER+1, GSIP->SIP_ORDER+1 );
    Eigen::MatrixXd sipAp = Eigen::MatrixXd::Zero(GSIP->SIP_P_ORDER+1,GSIP->SIP_P_ORDER+1);
    Eigen::MatrixXd sipBp = Eigen::MatrixXd::Zero(GSIP->SIP_P_ORDER+1,GSIP->SIP_P_ORDER+1);

    int ij=0;
    for(i=0;i<GSIP->SIP_ORDER+1;i++)
    for(j=0;j<GSIP->SIP_ORDER+1;j++)
    if(i+j<   GSIP->SIP_ORDER+1){
        sipA(i,j) = GSIP->CSIP[CID].SIP_AB[0][ij];
        sipB(i,j) = GSIP->CSIP[CID].SIP_AB[1][ij];
        ij++;
    }else{
        sipA(i,j) = 0.0;
        sipB(i,j) = 0.0;
    }

    ij=0;
    for(i=0;i<GSIP->SIP_P_ORDER+1;i++)
    for(j=0;j<GSIP->SIP_P_ORDER+1;j++)
    if(i+j<   GSIP->SIP_P_ORDER+1){
        sipAp(i,j) = GSIP->CSIP[CID].SIP_ABP[0][ij];
        sipBp(i,j) = GSIP->CSIP[CID].SIP_ABP[1][ij];
        ij++;
    }else{
        sipAp(i,j) = 0.0;
        sipBp(i,j) = 0.0;
    }

    afwImage::TanWcs::Ptr    resultTanWcs(new afwImage::TanWcs(crval, crpix, cdMatrix, sipA, sipB, sipAp, sipBp));
    return resultTanWcs;
}
void CL_WCSA_ASP::F_WCS_PLMAIN_SETWCSA_ASP(){
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_PLMAIN_SETWCSA_ASP ---" << endl;
    int CID;

    for(CID=0;CID<APROP->CCDNUM+1;CID++)
    WCSPtr.push_back(F_WCSA_PLMAIN_SETWCSPtr(CID));
}
std::vector <lsst::afw::image::TanWcs::Ptr> F_WCSA_PLMAIN_GETWCSLIST(PTR(CL_WCSA_ASP) WCSA_ASP){
    return WCSA_ASP->WCSPtr;
}

//-----------------------------------------------------------------
//Output Functions : WCSA_ASP : METADATA
//-----------------------------------------------------------------

void setMetadata(PTR(CL_WCSA_ASP) WCSA_ASP, dafbase::PropertySet::Ptr &metaTANSIP){
//    metaTANSIP->add("ST_A_CRPIXMODE" ,WCSA_ASP->APROP->CRPIXMODE);
    metaTANSIP->add("ST_A_CCDPOSMODE",WCSA_ASP->APROP->CCDPOSMODE);
    metaTANSIP->add("ST_A_REJMODE"   ,WCSA_ASP->APROP->REJMODE);
    metaTANSIP->add("ST_A_CCDNUM"    ,WCSA_ASP->APROP->CCDNUM);
    metaTANSIP->add("ST_A_ALLREFNUM" ,WCSA_ASP->APROP->ALLREFNUM);
    metaTANSIP->add("ST_A_ALLFITNUM" ,WCSA_ASP->APROP->ALLFITNUM);
    if(strcmp(WCSA_ASP->APROP->CRPIXMODE,"PIX")==0){
    metaTANSIP->add("ST_A_CRPIX_1"   ,WCSA_ASP->APROP->CRPIX[0]);
    metaTANSIP->add("ST_A_CRPIX_2"   ,WCSA_ASP->APROP->CRPIX[1]);
    }
    if(strcmp(WCSA_ASP->APROP->CRPIXMODE,"VAL")==0){
    metaTANSIP->add("ST_A_CRVAL_1"   ,WCSA_ASP->APROP->CRVAL[0]);
    metaTANSIP->add("ST_A_CRVAL_2"   ,WCSA_ASP->APROP->CRVAL[1]);
    }
    if(WCSA_ASP->APROP->REJMODE==1)
    metaTANSIP->add("ST_A_CLIPSIGMA" ,WCSA_ASP->APROP->CLIP_SIGMA);
    if(WCSA_ASP->APROP->CCDPOSMODE==1){
    metaTANSIP->add("ST_A_BASISPOS_X",WCSA_ASP->APROP->BASISPOS[0]);
    metaTANSIP->add("ST_A_BASISPOS_Y",WCSA_ASP->APROP->BASISPOS[1]);
    metaTANSIP->add("ST_A_BASISPOS_T",WCSA_ASP->APROP->BASISPOS[2]);
    }

    int CID;
    int i,j,ij;
    char METAKEY[100];
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM+1;CID++){
    sprintf(METAKEY,"ST_C%03d_ID",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].ID);
    sprintf(METAKEY,"ST_C%03d_FITNUM",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].FITNUM);
    sprintf(METAKEY,"ST_C%03d_REFNUM",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].REFNUM);
    sprintf(METAKEY,"ST_C%03d_GPOS_X",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].GPOS[0]);
    sprintf(METAKEY,"ST_C%03d_GPOS_Y",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].GPOS[1]);
    sprintf(METAKEY,"ST_C%03d_GPOS_T",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
    sprintf(METAKEY,"ST_C%03d_CRPIX_1",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].CRPIX[0]);
    sprintf(METAKEY,"ST_C%03d_CRPIX_2",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].CRPIX[1]);
    sprintf(METAKEY,"ST_C%03d_CRVAL_1",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].CRVAL[0]);
    sprintf(METAKEY,"ST_C%03d_CRVAL_2",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].CRVAL[1]);
    sprintf(METAKEY,"ST_C%03d_CD_1_1",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].CD[0][0]);
    sprintf(METAKEY,"ST_C%03d_CD_1_2",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].CD[0][1]);
    sprintf(METAKEY,"ST_C%03d_CD_2_1",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].CD[1][0]);
    sprintf(METAKEY,"ST_C%03d_CD_2_2",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].CD[1][1]);
    sprintf(METAKEY,"ST_C%03d_InvCD_1_1",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].InvCD[0][0]);
    sprintf(METAKEY,"ST_C%03d_InvCD_1_2",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].InvCD[0][1]);
    sprintf(METAKEY,"ST_C%03d_InvCD_2_1",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].InvCD[1][0]);
    sprintf(METAKEY,"ST_C%03d_InvCD_2_2",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].InvCD[1][1]);

    sprintf(METAKEY,"ST_C%03d_SIP_ORDER",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER);
    ij=0;
    for(i=0;i<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1;i++)
    for(j=0;j<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1;j++)
    if(i+j<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1){
    sprintf(METAKEY,"ST_C%03d_SIP_X_%d_%d",CID,i,j);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_AB[0][ij]);
    ij++;
    }
    ij=0;
    for(i=0;i<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1;i++)
    for(j=0;j<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1;j++)
    if(i+j<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1){
    sprintf(METAKEY,"ST_C%03d_SIP_Y_%d_%d",CID,i,j);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_AB[1][ij]);
    ij++;
    }
    sprintf(METAKEY,"ST_C%03d_SIP_AVERES_X",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[0][0]);
    sprintf(METAKEY,"ST_C%03d_SIP_RMSRES_X",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[0][1]);
    sprintf(METAKEY,"ST_C%03d_SIP_MAXRES_X",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[0][2]);
    sprintf(METAKEY,"ST_C%03d_SIP_AVERES_Y",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[1][0]);
    sprintf(METAKEY,"ST_C%03d_SIP_RMSRES_Y",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[1][1]);
    sprintf(METAKEY,"ST_C%03d_SIP_MAXRES_Y",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[1][2]);

    sprintf(METAKEY,"ST_C%03d_SIP_P_ORDER",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_P_ORDER);
    ij=0;
    for(i=0;i<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1;i++)
    for(j=0;j<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1;j++)
    if(i+j<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1){
    sprintf(METAKEY,"ST_C%03d_PSIP_X_%d_%d",CID,i,j);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_ABP[0][ij]);
    ij++;
    }
    ij=0;
    for(i=0;i<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1;i++)
    for(j=0;j<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1;j++)
    if(i+j<WCSA_ASP->GSIP->CSIP[CID].SIP_ORDER+1){
    sprintf(METAKEY,"ST_C%03d_PSIP_Y_%d_%d",CID,i,j);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_ABP[1][ij]);
    ij++;
    }
    sprintf(METAKEY,"ST_C%03d_PSIP_AVERES_X",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[0][0]);
    sprintf(METAKEY,"ST_C%03d_PSIP_RMSRES_X",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[0][1]);
    sprintf(METAKEY,"ST_C%03d_PSIP_MAXRES_X",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[0][2]);
    sprintf(METAKEY,"ST_C%03d_PSIP_AVERES_Y",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[1][0]);
    sprintf(METAKEY,"ST_C%03d_PSIP_RMSRES_Y",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[1][1]);
    sprintf(METAKEY,"ST_C%03d_PSIP_MAXRES_Y",CID);
    metaTANSIP->add(METAKEY,WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[1][2]);

    }
}

void setSummaryToMetadata(PTR(CL_WCSA_ASP) WCSA_ASP, dafbase::PropertySet::Ptr &metaTANSIP)
{
    metaTANSIP->add("sip_residuals_rms_x", WCSA_ASP->APAIR->SIPRMS[0][1]);
    metaTANSIP->add("sip_residuals_rms_y", WCSA_ASP->APAIR->SIPRMS[1][1]);        
    metaTANSIP->add("sip_residuals_ave_x", WCSA_ASP->APAIR->SIPRMS[0][0]);        
    metaTANSIP->add("sip_residuals_ave_y", WCSA_ASP->APAIR->SIPRMS[1][0]);        
    metaTANSIP->add("psip_residuals_rms_x", WCSA_ASP->APAIR->PSIPRMS[0][1]);
    metaTANSIP->add("psip_residuals_rms_y", WCSA_ASP->APAIR->PSIPRMS[1][1]);        
    metaTANSIP->add("psip_residuals_ave_x", WCSA_ASP->APAIR->PSIPRMS[0][0]);        
    metaTANSIP->add("psip_residuals_ave_y", WCSA_ASP->APAIR->PSIPRMS[1][0]);        
    metaTANSIP->add("nref_all", WCSA_ASP->APAIR->ALLREFNUM);        
    metaTANSIP->add("nref_fitting", WCSA_ASP->APAIR->ALLFITNUM);        
}
//-----------------------------------------------------------------
//Output Functions : WCSA_ASP : SIP
//-----------------------------------------------------------------
void F_WCSA_PLMAIN_OUTPUTREFERENCES(CL_WCSA_ASP* WCSA_ASP, string REFERENCESFILENAME){
    cout << "F_WCSA_PLMAIN_OUTPUTREFERENCES" << endl;
    cout << REFERENCESFILENAME << endl;
    ofstream fout;
    fout.open(REFERENCESFILENAME.c_str());
    fout << fixed;

    int NUM;
    for(NUM=0;NUM<WCSA_ASP->APROP->ALLREFNUM;NUM++)
    fout << WCSA_ASP->APAIR->PAIR[NUM].ID << "	" 
         << WCSA_ASP->APAIR->PAIR[NUM].CHIPID << "	"
         << WCSA_ASP->APAIR->PAIR[NUM].FLAG << "	"
         << WCSA_ASP->APAIR->PAIR[NUM].X_LOCAL[0] << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_LOCAL[1] << "	"
         << WCSA_ASP->APAIR->PAIR[NUM].X_GLOBAL[0] << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_GLOBAL[1] << "	"
         << WCSA_ASP->APAIR->PAIR[NUM].X_GLOBALCRPIX[0] << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_GLOBALCRPIX[1] << "	"
         << WCSA_ASP->APAIR->PAIR[NUM].X_PSIP_GLOBALCRPIX[0] << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_PSIP_GLOBALCRPIX[1] << "	"
         << WCSA_ASP->APAIR->PAIR[NUM].X_SIP_IM_PIXEL[0] << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_SIP_IM_PIXEL[1] << "	"
         << WCSA_ASP->APAIR->PAIR[NUM].X_IM_PIXEL[0] << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_IM_PIXEL[1] << "	"
         << WCSA_ASP->APAIR->PAIR[NUM].X_IM_WORLD[0] << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_IM_WORLD[1] << "	"
         << WCSA_ASP->APAIR->PAIR[NUM].X_RADEC[0] << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_RADEC[1] << "	"
         << WCSA_ASP->APAIR->GPOS[WCSA_ASP->APAIR->PAIR[NUM].CHIPID][0] << "	" << WCSA_ASP->APAIR->GPOS[WCSA_ASP->APAIR->PAIR[NUM].CHIPID][1] << "	" << WCSA_ASP->APAIR->GPOS[WCSA_ASP->APAIR->PAIR[NUM].CHIPID][2] << "	"
         << WCSA_ASP->APAIR->CRPIX[0] << "	" << WCSA_ASP->APAIR->CRPIX[1] << "	"
         << WCSA_ASP->APAIR->CRVAL[0] << "	" << WCSA_ASP->APAIR->CRVAL[1] << "	"
         << WCSA_ASP->APAIR->CD[0][0] << "	" << WCSA_ASP->APAIR->CD[0][1] << "	"
         << WCSA_ASP->APAIR->CD[1][0] << "	" << WCSA_ASP->APAIR->CD[1][1] << endl;
}
void F_WCSA_PLMAIN_OUTPUTSIPFIT(CL_WCSA_ASP* WCSA_ASP, string SIPFITFILENAME){
    int NUM;
    double RD[2];
    cout << "F_WCSA_PLMAIN_OUTPUTSIPFIT" << endl;
    cout << SIPFITFILENAME << endl;
    ofstream fout;
    fout.open(SIPFITFILENAME.c_str());
    fout << fixed;

    for(NUM=0;NUM<WCSA_ASP->APROP->ALLREFNUM;NUM++)
    if(WCSA_ASP->APAIR->PAIR[NUM].FLAG==1){
        WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(WCSA_ASP->APROP->CCDNUM,WCSA_ASP->APAIR->PAIR[NUM].X_GLOBAL,RD);
        fout << WCSA_ASP->APAIR->PAIR[NUM].ID << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_RADEC[0] << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_RADEC[1] << "	" << RD[0] << "	" << RD[1] << endl;
    }
}
void F_WCSA_PLMAIN_OUTPUTPSIPFIT(CL_WCSA_ASP* WCSA_ASP, string PSIPFITFILENAME){
    int NUM;
    double RD[2];
    cout << "F_WCSA_PLMAIN_OUTPUTPSIPFIT" << endl;
    cout << PSIPFITFILENAME << endl;
    ofstream fout;
    fout.open(PSIPFITFILENAME.c_str());
    fout << fixed;

    for(NUM=0;NUM<WCSA_ASP->APROP->ALLREFNUM;NUM++)
    if(WCSA_ASP->APAIR->PAIR[NUM].FLAG==1){
        WCSA_ASP->GSIP->F_WCSA_GSIP_XRADECtoXLOCAL(WCSA_ASP->APROP->CCDNUM,WCSA_ASP->APAIR->PAIR[NUM].X_RADEC,RD);
        fout << WCSA_ASP->APAIR->PAIR[NUM].ID << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_GLOBAL[0] << "	" << WCSA_ASP->APAIR->PAIR[NUM].X_GLOBAL[1] << "	" << RD[0] << "	" << RD[1] << endl;
    }
}
void F_WCSA_PLMAIN_OUTPUTSIP(CL_WCSA_ASP* WCSA_ASP, string SIPFILENAME){
    int i,j,ij;
    int TCCDNUM,SORDER,SPORDER;
    cout << "F_WCSA_PLMAIN_OUTPUTSIP" << endl;
    cout << SIPFILENAME << endl;
    ofstream fout;

    TCCDNUM = WCSA_ASP->APROP->CCDNUM;
    SORDER  = WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ORDER;
    SPORDER = WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_P_ORDER;

    fout.open(SIPFILENAME.c_str());
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].ID << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].REFNUM << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].FITNUM << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ORDER << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_P_ORDER << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].GPOS[0] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].GPOS[1] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].GPOS[2] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].MAXDRAD << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].MAXFRAD << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].CRPIX[0] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].CRPIX[1] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].CRVAL[0] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].CRVAL[1] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].CD[0][0] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].CD[0][1] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].CD[1][0] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].CD[1][1] << endl;

    ij=0;
    for(i=0;i<SORDER+1;i++)
    for(j=0;j<SORDER+1;j++)
    if(i+j<SORDER+1)
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB[0][ij++] << endl;
    ij=0;
    for(i=0;i<SORDER+1;i++)
    for(j=0;j<SORDER+1;j++)
    if(i+j<SORDER+1)
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB[1][ij++] << endl;
    ij=0;
    for(i=0;i<SPORDER+1;i++)
    for(j=0;j<SPORDER+1;j++)
    if(i+j<SPORDER+1)
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP[0][ij++] << endl;
    ij=0;
    for(i=0;i<SPORDER+1;i++)
    for(j=0;j<SPORDER+1;j++)
    if(i+j<SPORDER+1)
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP[1][ij++] << endl;

    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[0][0] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[0][1] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[0][2] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[1][0] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[1][1] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[1][2] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[0][0] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[0][1] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[0][2] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[1][0] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[1][1] << endl;
    fout << WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[1][2] << endl;
}
void F_WCSA_PLMAIN_INPUTSIP(CL_WCSA_ASP* WCSA_ASP, string SIPFILENAME){
    int i,j,ij;
    int TCCDNUM,SORDER,SPORDER;
    cout << "F_WCSA_PLMAIN_INPUTSIP" << endl;
    cout << SIPFILENAME << endl;
    ifstream fin;

    fin.open(SIPFILENAME.c_str());
    TCCDNUM = WCSA_ASP->APROP->CCDNUM;
    
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].ID;
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].REFNUM;
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].FITNUM;
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ORDER;
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_P_ORDER;
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].GPOS[0];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].GPOS[1];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].GPOS[2];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].MAXDRAD;
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].MAXFRAD;
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].CRPIX[0];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].CRPIX[1];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].CRVAL[0];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].CRVAL[1];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].CD[0][0];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].CD[0][1];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].CD[1][0];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].CD[1][1];

    SORDER  = WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ORDER;
    SPORDER = WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_P_ORDER;


    ij=0;
    for(i=0;i<SORDER+1;i++)
    for(j=0;j<SORDER+1;j++)
    if(i+j<SORDER+1)
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB[0][ij++];
    ij=0;
    for(i=0;i<SORDER+1;i++)
    for(j=0;j<SORDER+1;j++)
    if(i+j<SORDER+1)
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB[1][ij++];
    ij=0;
    for(i=0;i<SPORDER+1;i++)
    for(j=0;j<SPORDER+1;j++)
    if(i+j<SPORDER+1)
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP[0][ij++];
    ij=0;
    for(i=0;i<SPORDER+1;i++)
    for(j=0;j<SPORDER+1;j++)
    if(i+j<SPORDER+1)
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP[1][ij++];

    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[0][0];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[0][1];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[0][2];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[1][0];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[1][1];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_AB_ERR[1][2];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[0][0];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[0][1];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[0][2];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[1][0];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[1][1];
    fin >> WCSA_ASP->GSIP->CSIP[TCCDNUM].SIP_ABP_ERR[1][2];

//    WCSA_ASP->GSIP->F_WCSA_GSIP_SHOWCSIP(TCCDNUM);
}
void F_WCSA_PLMAIN_OUTPUTCCD(CL_WCSA_ASP* WCSA_ASP, string CCDFILENAME){
    int CID,TCCDNUM;
    cout << "F_WCSA_PLMAIN_OUTPUTCCD" << endl;
    cout << CCDFILENAME << endl;
    ofstream fout;

    fout.open(CCDFILENAME.c_str());
    TCCDNUM = WCSA_ASP->APROP->CCDNUM;
    for(CID=0;CID<TCCDNUM;CID++){
        fout << WCSA_ASP->GSIP->CSIP[CID].ID      << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].GPOS[0] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].GPOS[1] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].GPOS[2] << endl;
    }
}
void F_WCSA_PLMAIN_INPUTCCD(CL_WCSA_ASP* WCSA_ASP, string CCDFILENAME){
    int CID,TCCDNUM;
    cout << "F_WCSA_PLMAIN_INPUTCCD" << endl;
    cout << CCDFILENAME << endl;
    ifstream fin;

    fin.open(CCDFILENAME.c_str());
    TCCDNUM = WCSA_ASP->APROP->CCDNUM;
    for(CID=0;CID<TCCDNUM;CID++){
        fin >> WCSA_ASP->GSIP->CSIP[CID].ID     ;
        fin >> WCSA_ASP->GSIP->CSIP[CID].GPOS[0];
        fin >> WCSA_ASP->GSIP->CSIP[CID].GPOS[1];
        fin >> WCSA_ASP->GSIP->CSIP[CID].GPOS[2];
//    cout << WCSA_ASP->GSIP->CSIP[CID].ID << "	" << WCSA_ASP->GSIP->CSIP[CID].GPOS[0] << "	" << WCSA_ASP->GSIP->CSIP[CID].GPOS[1] << "	" << WCSA_ASP->GSIP->CSIP[CID].GPOS[2] << endl;
    }

}
void F_WCSA_PLMAIN_OUTPUTCCDRMS(CL_WCSA_ASP* WCSA_ASP, string CCDRMSFILENAME){
    int CID,TCCDNUM;
    cout << "F_WCSA_PLMAIN_OUTPUTCCDEMS" << endl;
    cout << CCDRMSFILENAME << endl;
    ofstream fout;

    fout.open(CCDRMSFILENAME.c_str());
    TCCDNUM = WCSA_ASP->APROP->CCDNUM;
    for(CID=0;CID<TCCDNUM+1;CID++){
        fout << WCSA_ASP->GSIP->CSIP[CID].ID      << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].GPOS_INIT[0] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].GPOS_INIT[1] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].GPOS_INIT[2] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].GPOS[0] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].GPOS[1] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].GPOS[2] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[0][0] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[1][0] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[0][1] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[1][1] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[0][2] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[1][2] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[0][0] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[1][0] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[0][1] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[1][1] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[0][2] << "	";
        fout << WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[1][2] << endl;
    }
}
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : POSITION
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : GRID POSITION 
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : GRID JACOBIAN 
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : GRID DISTORTION 
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//Simulation Functions : WCSA_ASP
//-----------------------------------------------------------------

void F_WCSA_PLMAIN_SIMULATION(int HARD,string CCDPOSfile,string DISTfile,double NSCALE,int RANNUM,int REFNUM){
    F_WCSA_SIMULATION_MAIN(HARD,CCDPOSfile,DISTfile,NSCALE,RANNUM,REFNUM);
}
void F_WCSA_PLMAIN_SIMULATIONDIFF(int HARD,string CCDPOSfile,string DISTfile,std::string CCDoutfile,std::string RESoutfile,CL_WCSA_ASP* WCSA_ASP){
    F_WCSA_SIMULATION_DIFF(HARD,CCDPOSfile,DISTfile,CCDoutfile,RESoutfile,WCSA_ASP);
}
void F_WCSA_PLMAIN_SIMULATION2(lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera,double NSCALE,int RANNUM,int REFNUM){
    CL_APROP *APROP;
    CL_GSIP  *GSIP;
    APROP = new CL_APROP[1];
    GSIP  = new CL_GSIP[1];

    F_WCSA_MAKEAPROP(APROPPolicy,APROP);
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_APROP ---" << endl;
    GSIP->CCDNUM=APROP->CCDNUM;
    APROP->F_WCSA_APROP_NEWAPROP();

//ALLREFNUM
    GSIP->ALLREFNUM=APROP->ALLREFNUM=REFNUM*APROP->CCDNUM;
    GSIP->ALLFITNUM=APROP->ALLFITNUM=REFNUM*APROP->CCDNUM;

//SIP ORDER
    GSIP->SIP_ORDER  =APROP->SIP_ORDER;
    GSIP->SIP_P_ORDER=APROP->SIP_P_ORDER;
    GSIP->SIP_L_ORDER=APROP->SIP_L_ORDER;
    GSIP->SIP_ORDER_INIT  =APROP->SIP_ORDER_INIT;
    GSIP->SIP_P_ORDER_INIT=APROP->SIP_P_ORDER_INIT;

    if(APROP->STDOUT==2) APROP->F_WCSA_APROP_SHOWAPROP();

//NEW
    GSIP ->F_WCSA_GSIP_NEWGSIP();

//GSIP
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_GSIP ---" << endl;
    F_WCSA_MAKEGSIP(APROPPolicy,camera,APROP,GSIP);
    if(APROP->STDOUT==2) GSIP->F_WCSA_GSIP_SHOWGSIP();
    if(APROP->STDOUT==2) GSIP->F_WCSA_GSIP_SHOWGPOS();
//for(int CID=0;CID<APROP->CCDNUM;CID++)
//cout<<scientific << GSIP->CSIP[CID].GPOS[0] << "	"  << GSIP->CSIP[CID].GPOS[1] << "	"  << GSIP->CSIP[CID].GPOS[2] << endl;

    F_WCSA_SIMULATION_MAIN2(APROP,GSIP,NSCALE,RANNUM,REFNUM);
}
void F_WCSA_PLMAIN_SIMULATIONDIFF2(std::string CCDoutfile,std::string RESoutfile,CL_WCSA_ASP* WCSA_ASP){

    F_WCSA_SIMULATION_DIFF2(CCDoutfile,RESoutfile,WCSA_ASP);
}
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : REFERNCE
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : CCD
//-----------------------------------------------------------------
/*std::vector< std::vector< double > >F_WCSA_PLMAIN_GETCCDPOSITIONS(CL_WCSA_ASP* WCSA_ASP){
    std::vector< std::vector< double > > CCDPOSITIONS;
    std::vector< double > CCDPOSITION(4);
    int CID;

    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++){
        CCDPOSITION[0]=WCSA_ASP->GSIP->CSIP[CID].ID;
        CCDPOSITION[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0];
        CCDPOSITION[2]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1];
        CCDPOSITION[3]=WCSA_ASP->GSIP->CSIP[CID].GPOS[2];
        CCDPOSITIONS.push_back(CCDPOSITION);

    }
    
    return CCDPOSITIONS;
}
std::vector< double > F_WCSA_PLMAIN_GETCCDPOSITION(CL_WCSA_ASP* WCSA_ASP,int CID){
    std::vector< double > CCDPOSITION(4);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CCDPOSITION[0]=WCSA_ASP->GSIP->CSIP[CID].ID;
        CCDPOSITION[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0];
        CCDPOSITION[2]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1];
        CCDPOSITION[3]=WCSA_ASP->GSIP->CSIP[CID].GPOS[2];
    }else{
        cout << "Warning : in WCS_GET_CCD_CCD_CCDPOS(F_WCSA_PLMAIN_GETCCDPOSITIONS)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDPOSITION[0]=CCDPOSITION[1]=CCDPOSITION[2]=CCDPOSITION[3]=0;
    }
    
    return CCDPOSITION;
}*/
//-----------------------------------------------------------------
//Getting Functions : OLD
//-----------------------------------------------------------------

std::vector< std::vector< double > >F_WCSA_PLMAIN_GETREFERENCES(CL_WCSA_ASP* WCSA_ASP){
    std::vector< std::vector< double > > REFERENCES;
    std::vector< double > REFERENCE(25);
    int NUM;
 
/*test ->*/
int i;
ofstream out;
out.open("PAIR00000.dat");
/*<- test */
    for(NUM=0;NUM<WCSA_ASP->APROP->ALLREFNUM;NUM++){
        REFERENCE[ 0]=WCSA_ASP->APAIR->PAIR[NUM].ID;
        REFERENCE[ 1]=WCSA_ASP->APAIR->PAIR[NUM].CHIPID;
        REFERENCE[ 2]=WCSA_ASP->APAIR->PAIR[NUM].FLAG;
        REFERENCE[ 3]=WCSA_ASP->APAIR->PAIR[NUM].X_LOCAL[0];
        REFERENCE[ 4]=WCSA_ASP->APAIR->PAIR[NUM].X_LOCAL[1];
        REFERENCE[ 5]=WCSA_ASP->APAIR->PAIR[NUM].X_GLOBAL[0];
        REFERENCE[ 6]=WCSA_ASP->APAIR->PAIR[NUM].X_GLOBAL[1];
        REFERENCE[ 7]=WCSA_ASP->APAIR->PAIR[NUM].X_CRPIX[0];
        REFERENCE[ 8]=WCSA_ASP->APAIR->PAIR[NUM].X_CRPIX[1];
        REFERENCE[ 9]=WCSA_ASP->APAIR->PAIR[NUM].X_IM_PIXEL[0];
        REFERENCE[10]=WCSA_ASP->APAIR->PAIR[NUM].X_IM_PIXEL[1];
        REFERENCE[11]=WCSA_ASP->APAIR->PAIR[NUM].X_IM_WORLD[0];
        REFERENCE[12]=WCSA_ASP->APAIR->PAIR[NUM].X_IM_WORLD[1];
        REFERENCE[13]=WCSA_ASP->APAIR->PAIR[NUM].X_RADEC[0];
        REFERENCE[14]=WCSA_ASP->APAIR->PAIR[NUM].X_RADEC[1];
        REFERENCE[15]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_CONVROT[0];
        REFERENCE[16]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_CONVROT[1];
        REFERENCE[17]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_SHEAR[0];
        REFERENCE[18]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_SHEAR[1];
        REFERENCE[19]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_MAGNIFICATION;
        REFERENCE[20]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_PCONVROT[0];
        REFERENCE[21]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_PCONVROT[1];
        REFERENCE[22]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_PSHEAR[0];
        REFERENCE[23]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_PSHEAR[1];
        REFERENCE[24]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_PMAGNIFICATION;
        REFERENCES.push_back(REFERENCE);
/*test ->*/
for(i=0;i<25;i++)
out << REFERENCE[i] << "	" ;
out << endl;
/*<- test */
    }

    return REFERENCES;
}
std::vector< double > F_WCSA_PLMAIN_GETRADEC(std::vector< double > X_GLOBAL,CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > RADEC(2);
    double XX[2],YY[2];
    
    XX[0]=X_GLOBAL[0];
    XX[1]=X_GLOBAL[1];
    WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(WCSA_ASP->APROP->CCDNUM,XX,YY);
    RADEC[0]=YY[0];
    RADEC[1]=YY[1];    

    return RADEC;
}
std::vector< double > F_WCSA_PLMAIN_GETX_GLOBAL(std::vector< double > RADEC,CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X_GLOBAL(2);
    double XX[2],YY[2];
    
    XX[0]=RADEC[0];
    XX[1]=RADEC[1];
    WCSA_ASP->GSIP->F_WCSA_GSIP_XRADECtoXLOCAL(WCSA_ASP->APROP->CCDNUM,XX,YY);
    X_GLOBAL[0]=YY[0];
    X_GLOBAL[1]=YY[1];    

    return X_GLOBAL;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_ID(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].ID);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_CHIPID(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].CHIPID);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_FLAG(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].FLAG);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_RA(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_RADEC[0]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_DEC(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_RADEC[1]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_IM_WORLD_X(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_IM_WORLD[0]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_IM_WORLD_Y(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_IM_WORLD[1]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_IM_PIXEL_X(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_IM_PIXEL[0]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_IM_PIXEL_Y(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_IM_PIXEL[1]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_CRPIX_X(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_CRPIX[0]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_CRPIX_Y(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_CRPIX[1]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_GLOBAL_X(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_GLOBAL[0]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_GLOBAL_Y(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_GLOBAL[1]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_LOCAL_X(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_LOCAL[0]);
    }

    return X;
}
std::vector< double > F_WCSA_PLMAIN_GETPAIR_LOCAL_Y(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X;
    int NUM;

    for(NUM=0;NUM<WCSA_ASP->APAIR->ALLREFNUM;NUM++){
        X.push_back(WCSA_ASP->APAIR->PAIR[NUM].X_LOCAL[1]);
    }

    return X;
}
