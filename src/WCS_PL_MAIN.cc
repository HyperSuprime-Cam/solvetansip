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
void    F_WCSA_MAKEGSIP(lsst::afw::cameraGeom::Camera::Ptr &,CL_APROP*,CL_GSIP*);
//void    F_WCSA_SETSIZE(vector<vector<hsc::meas::tansip::SourceMatch> > const &,CL_APROP*,CL_GSIP*);
//void    F_WCSA_SETSIZE_local(string matchlist, CL_APROP*);
void    F_WCSA_SETREFSIZE(vector<vector<hsc::meas::tansip::SourceMatch> > const &,CL_APROP*);
void    F_WCSA_SETREFSIZE_local(string matchlist, CL_APROP*);
void    F_WCSA_MAKEPAIR(vector<vector<hsc::meas::tansip::SourceMatch> > const &, CL_APROP*,CL_APAIR*);
void    F_WCSA_MAKEPAIR_local(string matchlist,CL_APAIR*);

void    F_WCS_DISTORTION(int ,CL_APROP *APROP);

CL_WCSA_ASP F_WCSA_TANSIP_V(vector<vector<hsc::meas::tansip::SourceMatch> > const &matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/){
    CL_WCSA_ASP *WCSA_ASP;

    cout << "--- solvetansip : START(local) ---" << endl;
    WCSA_ASP = new CL_WCSA_ASP[1];
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

    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APROP->F_WCSA_APROP_SHOWAPROP();

//NEW
    WCSA_ASP->APAIR->F_WCSA_APAIR_NEWAPAIR();
    WCSA_ASP->GSIP ->F_WCSA_GSIP_NEWGSIP();

//GSIP
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_GSIP ---" << endl;
    F_WCSA_MAKEGSIP(camera,WCSA_ASP->APROP,WCSA_ASP->GSIP);
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->GSIP->F_WCSA_GSIP_SHOWGSIP();
//    F_WCSA_SETSIZE_local(matchlist,WCSA_ASP->APROP,WCSA_ASP->GSIP);

//APAIR
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_PAIR ---" << endl;
    F_WCSA_MAKEPAIR(matchlist,WCSA_ASP->APROP,WCSA_ASP->APAIR);
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APAIR->F_WCSA_APAIR_SHOWAPAIR();

//TANSIP
    F_WCSA_TANSIP(WCSA_ASP->APROP,WCSA_ASP->APAIR,WCSA_ASP->GSIP);

    WCSA_ASP->F_WCS_PLMAIN_SETWCSA_ASP();

    cout << "--- solvetansip : END(local) ---" << endl;
    return *WCSA_ASP;
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
CL_WCSA_ASP F_WCSA_TANSIP_V_local(string matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/){
    CL_WCSA_ASP *WCSA_ASP;

    cout << "--- solvetansip : START(local) ---" << endl;
    WCSA_ASP = new CL_WCSA_ASP[1];
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

    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APROP->F_WCSA_APROP_SHOWAPROP();

//NEW
    WCSA_ASP->APAIR->F_WCSA_APAIR_NEWAPAIR();
    WCSA_ASP->GSIP ->F_WCSA_GSIP_NEWGSIP();

//GSIP
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_GSIP ---" << endl;
    F_WCSA_MAKEGSIP(camera,WCSA_ASP->APROP,WCSA_ASP->GSIP);
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->GSIP->F_WCSA_GSIP_SHOWGSIP();
//    F_WCSA_SETSIZE_local(matchlist,WCSA_ASP->APROP,WCSA_ASP->GSIP);

//APAIR
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_PAIR ---" << endl;
    F_WCSA_MAKEPAIR_local(matchlist,WCSA_ASP->APAIR);
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APAIR->F_WCSA_APAIR_SHOWAPAIR();

//TANSIP
    F_WCSA_TANSIP(WCSA_ASP->APROP,WCSA_ASP->APAIR,WCSA_ASP->GSIP);

    WCSA_ASP->F_WCS_PLMAIN_SETWCSA_ASP();

    cout << "--- solvetansip : END(local) ---" << endl;
    return *WCSA_ASP;
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
void CL_WCSA_ASP::F_WCS_PLMAIN_NEWWCSA_ASP(){
    APROP= new CL_APROP[1];
    GSIP = new CL_GSIP[1];
    APAIR= new CL_APAIR[1];
}
void CL_WCSA_ASP::F_WCS_PLMAIN_DELWCSA_ASP(){
    delete [] APROP;
    delete [] GSIP ;
    delete [] APAIR;
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
    string CMODE,OAMODE,SNAME,CNAME,PNAME,DNAME;

    // Validate policy with dictionary
    lsst::pex::policy::DefaultPolicyFile const defaultsFile("solvetansip", "WCS_MAKEAPROP_Dictionary.paf",
                                                            "policy");
    lsst::pex::policy::Policy const defaults(defaultsFile);
    APROPPolicy->mergeDefaults(defaults);

    CMODE              =APROPPolicy->getString("CRPIXMODE");
    strncpy(APROP->CRPIXMODE,CMODE.c_str(), CL_APROP::STRING_LENGTH);
    OAMODE             =APROPPolicy->getString("OAMODE");
    strncpy(APROP->OAMODE,OAMODE.c_str(), CL_APROP::STRING_LENGTH);
    APROP->CCDNUM      =APROPPolicy->getInt("NCCD");
    APROP->CCDPOSMODE  =APROPPolicy->getInt("CCDPMODE");
    APROP->CRPIX[0]    =APROPPolicy->getDouble("CRPIX1");
    APROP->CRPIX[1]    =APROPPolicy->getDouble("CRPIX2");
    APROP->CRVAL[0]    =APROPPolicy->getDouble("CRVAL1");
    APROP->CRVAL[1]    =APROPPolicy->getDouble("CRVAL2");
    APROP->SIP_L_ORDER =APROPPolicy->getInt("LSIPORDER");
    APROP->SIP_ORDER   =APROPPolicy->getInt("SIPORDER");
    APROP->SIP_P_ORDER =APROPPolicy->getInt("PSIPORDER");
    APROP->CLIP_SIGMA  =APROPPolicy->getDouble("CLIPSIGMA");
    APROP->BASISPOS[0] =APROPPolicy->getDouble("BASISPOSX");
    APROP->BASISPOS[1] =APROPPolicy->getDouble("BASISPOSY");
    APROP->BASISPOS[2] =APROPPolicy->getDouble("BASISPOST");
    APROP->STDOUT      =APROPPolicy->getInt("STDOUT");
    APROP->CHECKPARAM  = 0;
    APROP->ALLREFNUM   = 0;
    APROP->ALLFITNUM   = 0;
}
void    F_WCSA_MAKEGSIP(lsst::afw::cameraGeom::Camera::Ptr &camera, CL_APROP *APROP, CL_GSIP *GSIP){
    int CID;

    GSIP->F_WCSA_GSIP_SET0();

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
}
void    F_WCSA_SETREFSIZE(vector<vector<hsc::meas::tansip::SourceMatch> > const &matchlist, CL_APROP* APROP){
    int ID;
    for(ID=0;ID<APROP->CCDNUM;ID++){
        APROP->REFNUM[ID]     =matchlist[ID].size();
        APROP->FITNUM[ID]     =matchlist[ID].size();
        APROP->ALLREFNUM     +=matchlist[ID].size();
    }
        APROP->ALLFITNUM=APROP->ALLREFNUM;
}
/*DEL*/
/*void    F_WCSA_SETSIZE(vector<vector<hsc::meas::tansip::SourceMatch> > const &matchlist, CL_APROP* APROP, CL_GSIP *GSIP){
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
    }

    APROP->ALLREFNUM = CIDNUM[APROP->CCDNUM];
    APROP->ALLFITNUM = CIDNUM[APROP->CCDNUM];
    in.close();

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
void    F_WCSA_MAKEPAIR(vector<vector<hsc::meas::tansip::SourceMatch> > const &matchlist,CL_APROP* APROP,CL_APAIR* APAIR){
    int CID,NUM,ALLNUM;

    APAIR->F_WCSA_APAIR_SET0();
    ALLNUM=0;

    for(CID=0;CID<APAIR->CCDNUM;CID++)
    for(NUM=0;NUM<APROP->REFNUM[CID];NUM++){
        APAIR->PAIR[ALLNUM].ID            =matchlist[CID][NUM].getId();
        APAIR->PAIR[ALLNUM].CHIPID        =CID;
        APAIR->PAIR[ALLNUM].FLAG          =1;
        APAIR->PAIR[ALLNUM].X_RADEC[0]    = matchlist[CID][NUM].getRa();
        APAIR->PAIR[ALLNUM].X_RADEC[1]    = matchlist[CID][NUM].getDec();
        APAIR->PAIR[ALLNUM].X_LOCAL[0]    =matchlist[CID][NUM].getX();
        APAIR->PAIR[ALLNUM].X_LOCAL[1]    =matchlist[CID][NUM].getY();
        APAIR->PAIR[ALLNUM].X_LOCALERR[0] =matchlist[CID][NUM].getXErr();
        APAIR->PAIR[ALLNUM].X_LOCALERR[1] =matchlist[CID][NUM].getYErr();
        APAIR->PAIR[ALLNUM].X_RADECERR[0] =1;
        APAIR->PAIR[ALLNUM].X_RADECERR[1] =1;
        ALLNUM+=1;
    }
}
void    F_WCSA_MAKEPAIR_local(string matchlist,CL_APAIR* APAIR){
    int ID,CID,ALLNUM;
    double x,y,RA,DEC;
    ifstream in;

    APAIR->F_WCSA_APAIR_SET0();
    in.open(matchlist.c_str());
    cout << matchlist.c_str() << endl;
    ALLNUM=0;
    while((in >> ID >> CID >> x >> y >> RA >> DEC)!=0){
        APAIR->PAIR[ALLNUM].ID           =ID;
        APAIR->PAIR[ALLNUM].CHIPID       =CID;
        APAIR->PAIR[ALLNUM].FLAG         =1;
        APAIR->PAIR[ALLNUM].X_LOCAL[0]   =x;
        APAIR->PAIR[ALLNUM].X_LOCAL[1]   =y;
        APAIR->PAIR[ALLNUM].X_RADEC[0]   =RA;
        APAIR->PAIR[ALLNUM].X_RADEC[1]   =DEC;
        APAIR->PAIR[ALLNUM].X_LOCALERR[0]=1;
        APAIR->PAIR[ALLNUM].X_LOCALERR[1]=1;
        APAIR->PAIR[ALLNUM].X_RADECERR[0]=1;
        APAIR->PAIR[ALLNUM].X_RADECERR[1]=1;
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
std::vector <lsst::afw::image::TanWcs::Ptr> F_WCSA_PLMAIN_GETWCSLIST(CL_WCSA_ASP* WCSA_ASP){
    return WCSA_ASP->WCSPtr;
}
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : POSITION
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_RADECfromLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    int CHIPID;
    double LOCAL[2],RD[2];
    std::vector< double > RADEC(2);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    LOCAL[0]=XY[0];
    LOCAL[1]=XY[1];
    WCSA_ASP->GSIP->CSIP[CHIPID].F_WCSA_CSIP_XLOCALtoXRADEC(LOCAL,RD);
    RADEC[0]=RD[0];
    RADEC[1]=RD[1];

    return RADEC;
}
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_RADECfromCRPIX(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    int CHIPID;
    double XCRPIX[2],RD[2];
    std::vector< double > RADEC(2);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    XCRPIX[0]=XY[0];
    XCRPIX[1]=XY[1];
    WCSA_ASP->GSIP->CSIP[CHIPID].F_WCSA_CSIP_XCRPIXtoXRADEC(XCRPIX,RD);
    RADEC[0]=RD[0];
    RADEC[1]=RD[1];

    return RADEC;
}
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_LOCALfromRADEC(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    int CHIPID;
    double RADEC[2],RD[2];
    std::vector< double > LOCAL(2);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    RADEC[0]=XY[0];
    RADEC[1]=XY[1];
    WCSA_ASP->GSIP->CSIP[CHIPID].F_WCSA_CSIP_XRADECtoXLOCAL(RADEC,RD);
    LOCAL[0]=RD[0];
    LOCAL[1]=RD[1];

    return LOCAL;
}
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_CRPIXfromRADEC(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    int CHIPID;
    double RADEC[2],RD[2];
    std::vector< double > XCRPIX(2);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    RADEC[0]=XY[0];
    RADEC[1]=XY[1];
    WCSA_ASP->GSIP->CSIP[CHIPID].F_WCSA_CSIP_XRADECtoXCRPIX(RADEC,RD);
    XCRPIX[0]=RD[0];
    XCRPIX[1]=RD[1];

    return XCRPIX;
}

std::vector< double > F_WCSA_PLMAIN_GETPOSITION_GLOBALfromCCDIDLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    std::vector< double > X_GLOBAL(2);
    int CCDID=(int)(CID+0.5);
    X_GLOBAL[0]=WCSA_ASP->GSIP->CSIP[CCDID].GPOS[0]+XY[0]*cos(WCSA_ASP->GSIP->CSIP[CCDID].GPOS[2])-XY[1]*sin(WCSA_ASP->GSIP->CSIP[CCDID].GPOS[2]);
    X_GLOBAL[1]=WCSA_ASP->GSIP->CSIP[CCDID].GPOS[1]+XY[1]*cos(WCSA_ASP->GSIP->CSIP[CCDID].GPOS[2])+XY[0]*sin(WCSA_ASP->GSIP->CSIP[CCDID].GPOS[2]);

    return X_GLOBAL;
}
std::vector< double > F_WCSA_PLMAIN_GETPOSITION_CCDIDLOCALfromGLOBAL(CL_WCSA_ASP* WCSA_ASP,std::vector< double > XY){
    std::vector< double > CCDIDLOCAL(3);
    int CID,CHECK=0;
    double XLOCAL[2];
cout << XY[0] << "	" << XY[1] << endl;
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++){
        XLOCAL[0]=(XY[0]-WCSA_ASP->GSIP->CSIP[CID].GPOS[0])*cos(-WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-(XY[1]-WCSA_ASP->GSIP->CSIP[CID].GPOS[1])*sin(-WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
        XLOCAL[1]=(XY[1]-WCSA_ASP->GSIP->CSIP[CID].GPOS[1])*cos(-WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+(XY[0]-WCSA_ASP->GSIP->CSIP[CID].GPOS[0])*sin(-WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
cout << CID << "	" << XLOCAL[0] << "	" << XLOCAL[1] << endl;
        if(XLOCAL[0]>0&&XLOCAL[0]<2048&&XLOCAL[1]>0&&XLOCAL[1]<4096){
            CCDIDLOCAL[0]=CID;
            CCDIDLOCAL[1]=XLOCAL[0];
            CCDIDLOCAL[2]=XLOCAL[1];
            CHECK=1;
            break;
        }
    }
cout << CHECK << "	" << CID << "	" << XLOCAL[0] << "	" << XLOCAL[1] << endl;
    if(CHECK==0){
        cout << "No CCDs(2048,4096) have the global position : " << XY[0] << " , " << XY[1]<<endl;
            CCDIDLOCAL[0]=0;
            CCDIDLOCAL[1]=0;
            CCDIDLOCAL[2]=0;
    }
cout << CHECK << "	" << CID << "	" << XLOCAL[0] << "	" << XLOCAL[1] << endl;

    return CCDIDLOCAL;
}
//-----------------------------------------------------------------
//Output Functions : WCSA_ASP : SIP
//-----------------------------------------------------------------
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
    cout << WCSA_ASP->GSIP->CSIP[CID].ID << "	" << WCSA_ASP->GSIP->CSIP[CID].GPOS[0] << "	" << WCSA_ASP->GSIP->CSIP[CID].GPOS[1] << "	" << WCSA_ASP->GSIP->CSIP[CID].GPOS[2] << endl;
    }

}
//-----------------------------------------------------------------
//Simulation Functions : WCSA_ASP
//-----------------------------------------------------------------

void F_WCSA_PLMAIN_SIMULATION(int HARD,string CCDPOSfile,string DISTfile,double NSCALE,int RANNUM,int REFNUM){
    F_WCSA_SIMULATION_MAIN(HARD,CCDPOSfile,DISTfile,NSCALE,RANNUM,REFNUM);
}
void F_WCSA_PLMAIN_SIMULATIONDIFF(int HARD,string CCDPOSfile,string DISTfile,std::string CCDoutfile,std::string RESoutfile,CL_WCSA_ASP* WCSA_ASP){
    F_WCSA_SIMULATION_DIFF(HARD,CCDPOSfile,DISTfile,CCDoutfile,RESoutfile,WCSA_ASP);
}
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : REFERNCE
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLMAIN_GETREF_ID(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_ID;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_ID.push_back(WCSA_ASP->APAIR->PAIR[RID].ID);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_ID.push_back(WCSA_ASP->APAIR->PAIR[RID].ID);
    }

    return REFINFO_ID;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CHIPID(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CHIPID;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CHIPID.push_back(WCSA_ASP->APAIR->PAIR[RID].CHIPID);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CHIPID.push_back(WCSA_ASP->APAIR->PAIR[RID].CHIPID);
    }

    return REFINFO_CHIPID;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_FLAG(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_FLAG;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_FLAG.push_back(WCSA_ASP->APAIR->PAIR[RID].FLAG);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_FLAG.push_back(WCSA_ASP->APAIR->PAIR[RID].FLAG);
    }

    return REFINFO_FLAG;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYLOCAL(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYLOCAL(2);
    std::vector< std::vector< double > > REFINFO_XYLOCALS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYLOCAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[0];
            REFINFO_XYLOCAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[1];
            REFINFO_XYLOCALS.push_back(REFINFO_XYLOCAL);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYLOCAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[0];
            REFINFO_XYLOCAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[1];
            REFINFO_XYLOCALS.push_back(REFINFO_XYLOCAL);
        }
    }

    return REFINFO_XYLOCALS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYRADEC(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYRADEC(2);
    std::vector< std::vector< double > > REFINFO_XYRADECS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYRADEC[0]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[0];
            REFINFO_XYRADEC[1]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[1];
            REFINFO_XYRADECS.push_back(REFINFO_XYRADEC);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYRADEC[0]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[0];
            REFINFO_XYRADEC[1]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[1];
            REFINFO_XYRADECS.push_back(REFINFO_XYRADEC);
        }
    }

    return REFINFO_XYRADECS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYGLOBAL(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYGLOBAL(2);
    std::vector< std::vector< double > > REFINFO_XYGLOBALS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYGLOBAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[0];
            REFINFO_XYGLOBAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[1];
            REFINFO_XYGLOBALS.push_back(REFINFO_XYGLOBAL);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYGLOBAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[0];
            REFINFO_XYGLOBAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[1];
            REFINFO_XYGLOBALS.push_back(REFINFO_XYGLOBAL);
        }
    }

    return REFINFO_XYGLOBALS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYGLOBALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYGLOBALCRPIX(2);
    std::vector< std::vector< double > > REFINFO_XYGLOBALCRPIXS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYGLOBALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[0];
            REFINFO_XYGLOBALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[1];
            REFINFO_XYGLOBALCRPIXS.push_back(REFINFO_XYGLOBALCRPIX);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYGLOBALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[0];
            REFINFO_XYGLOBALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[1];
            REFINFO_XYGLOBALCRPIXS.push_back(REFINFO_XYGLOBALCRPIX);
        }
    }

    return REFINFO_XYGLOBALCRPIXS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYLOCALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYLOCALCRPIX(2);
    std::vector< std::vector< double > > REFINFO_XYLOCALCRPIXS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYLOCALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[0];
            REFINFO_XYLOCALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[1];
            REFINFO_XYLOCALCRPIXS.push_back(REFINFO_XYLOCALCRPIX);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYLOCALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[0];
            REFINFO_XYLOCALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[1];
            REFINFO_XYLOCALCRPIXS.push_back(REFINFO_XYLOCALCRPIX);
        }
    }

    return REFINFO_XYLOCALCRPIXS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYIMPIXEL(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYIMPIXEL(2);
    std::vector< std::vector< double > > REFINFO_XYIMPIXELS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYIMPIXEL[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[0];
            REFINFO_XYIMPIXEL[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[1];
            REFINFO_XYIMPIXELS.push_back(REFINFO_XYIMPIXEL);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYIMPIXEL[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[0];
            REFINFO_XYIMPIXEL[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[1];
            REFINFO_XYIMPIXELS.push_back(REFINFO_XYIMPIXEL);
        }
    }

    return REFINFO_XYIMPIXELS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREF_XYIMWORLD(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYIMWORLD(2);
    std::vector< std::vector< double > > REFINFO_XYIMWORLDS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYIMWORLD[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[0];
            REFINFO_XYIMWORLD[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[1];
            REFINFO_XYIMWORLDS.push_back(REFINFO_XYIMWORLD);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYIMWORLD[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[0];
            REFINFO_XYIMWORLD[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[1];
            REFINFO_XYIMWORLDS.push_back(REFINFO_XYIMWORLD);
        }
    }

    return REFINFO_XYIMWORLDS;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERACONV(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERACONV;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERACONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[0]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERACONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[0]);
    }

    return REFINFO_CAMERACONV;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAROT(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAROT;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[1]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[1]);
    }

    return REFINFO_CAMERAROT;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERASHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERASHEAR1;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERASHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[0]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERASHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[0]);
    }

    return REFINFO_CAMERASHEAR1;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERASHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERASHEAR2;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERASHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[1]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERASHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[1]);
    }

    return REFINFO_CAMERASHEAR2;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAMAGNIFICATION;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_MAGNIFICATION);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_MAGNIFICATION);
    }

    return REFINFO_CAMERAMAGNIFICATION;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAPCONV(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAPCONV;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAPCONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[0]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAPCONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[0]);
    }

    return REFINFO_CAMERAPCONV;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAPROT(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAPROT;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAPROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[1]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAPROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[1]);
    }

    return REFINFO_CAMERAPROT;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAPSHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAPSHEAR1;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAPSHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[0]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAPSHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[0]);
    }

    return REFINFO_CAMERAPSHEAR1;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAPSHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAPSHEAR2;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAPSHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[1]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAPSHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[1]);
    }

    return REFINFO_CAMERAPSHEAR2;
}
std::vector< double > F_WCSA_PLMAIN_GETREF_CAMERAPMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAPMAGNIFICATION;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAPMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PMAGNIFICATION);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAPMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PMAGNIFICATION);
    }

    return REFINFO_CAMERAPMAGNIFICATION;
}

std::vector< double > F_WCSA_PLMAIN_GETREF(CL_WCSA_ASP* WCSA_ASP,int REFID){
    int RID,CHECK=0,i;
    std::vector< double > REFINFO(27);

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    if(REFID==WCSA_ASP->APAIR->PAIR[RID].ID){
        REFINFO[ 0]=WCSA_ASP->APAIR->PAIR[RID].ID;
        REFINFO[ 1]=WCSA_ASP->APAIR->PAIR[RID].CHIPID;
        REFINFO[ 2]=WCSA_ASP->APAIR->PAIR[RID].FLAG;
        REFINFO[ 3]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[0];
        REFINFO[ 4]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[1];
        REFINFO[ 5]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[0];
        REFINFO[ 6]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[1];
        REFINFO[ 7]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[0];
        REFINFO[ 8]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[1];
        REFINFO[ 9]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[0];
        REFINFO[10]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[1];
        REFINFO[11]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[0];
        REFINFO[12]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[1];
        REFINFO[13]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[0];
        REFINFO[14]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[1];
        REFINFO[15]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[0];
        REFINFO[16]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[1];
        REFINFO[17]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[0];
        REFINFO[18]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[1];
        REFINFO[19]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[0];
        REFINFO[20]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[1];
        REFINFO[21]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_MAGNIFICATION;
        REFINFO[22]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[0];
        REFINFO[23]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[1];
        REFINFO[24]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[0];
        REFINFO[25]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[1];
        REFINFO[26]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_PMAGNIFICATION;
        CHECK=1;
        break;
    }
    if(CHECK==0){
        cout << "Warning : in WCS_GET_REFERENCE_INIDIVIDUAL(F_WCSA_PLMAIN_GETREF)" << endl;
        cout << "        : There is no reference having ID = " << REFID << endl;
        for(i=0;i<27;i++)
        REFINFO[i]=0;
    }

    return REFINFO;
}

//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : CCD
//-----------------------------------------------------------------
std::vector< std::vector< double > >F_WCSA_PLMAIN_GETCCDPOSITIONS(CL_WCSA_ASP* WCSA_ASP){
    std::vector< std::vector< double > > CCDPOSITIONS;
    std::vector< double > CCDPOSITION(4);
    int CID;
/*test ->*/
int i;
ofstream out;
out.open("CCDPOS00000.dat");
/*<- test */
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++){
        CCDPOSITION[0]=WCSA_ASP->GSIP->CSIP[CID].ID;
        CCDPOSITION[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0];
        CCDPOSITION[2]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1];
        CCDPOSITION[3]=WCSA_ASP->GSIP->CSIP[CID].GPOS[2];
        CCDPOSITIONS.push_back(CCDPOSITION);
/*test ->*/
for(i=0;i<4;i++)
out << CCDPOSITION[i] << "	" ;
out << endl;
/*<- test */
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
}

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
    WCSA_ASP->GSIP->F_WCSA_GSIP_PIXELtoRADEC(XX,YY);
    RADEC[0]=YY[0];
    RADEC[1]=YY[1];    

    return RADEC;
}
std::vector< double > F_WCSA_PLMAIN_GETX_GLOBAL(std::vector< double > RADEC,CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > X_GLOBAL(2);
    double XX[2],YY[2];
    
    XX[0]=RADEC[0];
    XX[1]=RADEC[1];
    WCSA_ASP->GSIP->F_WCSA_GSIP_RADECtoPIXEL(XX,YY);
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
