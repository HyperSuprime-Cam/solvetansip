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
namespace afwdetect = lsst::afw::detection;
namespace afwImage = lsst::afw::image;
namespace afwGeom = lsst::afw::geom; 
namespace afwCoord = lsst::afw::coord;
namespace camGeom = lsst::afw::cameraGeom;
namespace dafbase = lsst::daf::base;

void    F_WCSA_MAKEAPROP(lsst::pex::policy::Policy::Ptr &,CL_APROP*);
void    F_WCSA_SHOWAPROP(CL_APROP*);
void    F_WCSA_MAKEGSIP(lsst::afw::cameraGeom::Camera::Ptr &,CL_APROP*,CL_GSIP*);
void    F_WCSA_SETSIZE(vector< vector< afwdetect::SourceMatch  >  > const &,CL_APROP*,CL_GSIP*);
void    F_WCSA_SETSIZE_local(string matchlist, CL_APROP*, CL_GSIP *);
void    F_WCSA_MAKEPAIR(vector< vector< afwdetect::SourceMatch  >  > const &,CL_GSIP*,CL_APAIR*);
void    F_WCSA_MAKEPAIR_local(string matchlist,CL_GSIP*,CL_APAIR*);

void    F_WCS_DISTORTION(int ,CL_APROP *APROP);

CL_WCSA_ASP F_WCSA_TANSIP_V(vector< vector<afwdetect::SourceMatch> > const &matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/){
    CL_WCSA_ASP *WCSA_ASP;

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
    return *WCSA_ASP;
}
CL_WCSA_ASP F_WCSA_TANSIP_V_local(string matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/){
    CL_WCSA_ASP *WCSA_ASP;

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
    return *WCSA_ASP;
}
void    F_WCSA_MAKEAPROP(lsst::pex::policy::Policy::Ptr &APROPPolicy, CL_APROP *APROP){
    string CMODE,OAMODE,SNAME,CNAME,PNAME,DNAME;
    CMODE              =APROPPolicy->getString("CRPIXMODE");
    strcpy(APROP->CRPIXMODE,CMODE.c_str());
    OAMODE             =APROPPolicy->getString("OAMODE");
    strcpy(APROP->OAMODE,OAMODE.c_str());
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
    APROP->STDOUT      =APROPPolicy->getInt("STDOUT");
    APROP->ALLREFNUM   = 0;
    APROP->ALLFITNUM   = 0;
}
void    F_WCSA_MAKEGSIP(lsst::afw::cameraGeom::Camera::Ptr &camera, CL_APROP *APROP, CL_GSIP *GSIP){
    int CID;

    GSIP->F_WCSA_GSIP_SET0();
    GSIP->CCDNUM=APROP->CCDNUM;

    for(camGeom::Camera::const_iterator iter(camera->begin()); iter != camera->end(); ++iter) { 
        camGeom::DetectorMosaic::Ptr detMosaic = boost::shared_dynamic_cast<camGeom::DetectorMosaic>(*iter);

        for(CID=0;CID<APROP->CCDNUM;CID++){
            camGeom::Id detId = camGeom::Id(CID);//serial
            camGeom::Detector::Ptr det = detMosaic->findDetector(detId);
            afwGeom::Point2D offsetXY = det->getCenter();
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
void    F_WCSA_SETSIZE(vector< vector< afwdetect::SourceMatch  >  > const &matchlist, CL_APROP* APROP, CL_GSIP *GSIP){
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
}
void    F_WCSA_SETSIZE_local(string matchlist, CL_APROP* APROP, CL_GSIP *GSIP){
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
}
#define PI (4*atan(1.0))
void    F_WCSA_MAKEPAIR(vector< vector<afwdetect::SourceMatch> > const &matchlist,CL_GSIP* GSIP,CL_APAIR* APAIR){
    int CID,NUM,ALLNUM;

    APAIR->F_WCSA_APAIR_SET0();
    ALLNUM=0;

    for(CID=0;CID<GSIP->CCDNUM;CID++)
    for(NUM=0;NUM<GSIP->CSIP[CID].REFNUM;NUM++){
        APAIR->PAIR[ALLNUM].ID            =matchlist[CID][NUM].first->getId();
        APAIR->PAIR[ALLNUM].CHIPID        =CID;
        APAIR->PAIR[ALLNUM].FLAG          =1;
//        afwCoord::Coord::Ptr radec = matchlist[CID][NUM].first->getRaDec();
//        APAIR->PAIR[ALLNUM].RA    = radec->getLongitude(afwCoord::DEGREES);
//        APAIR->PAIR[ALLNUM].DEC   = radec->getLatitude(afwCoord::DEGREES);
        APAIR->PAIR[ALLNUM].X_RADEC[0]    = 180.0/PI*matchlist[CID][NUM].first->getRa();
        APAIR->PAIR[ALLNUM].X_RADEC[1]    = 180.0/PI*matchlist[CID][NUM].first->getDec();
        APAIR->PAIR[ALLNUM].X_LOCAL[0]    =matchlist[CID][NUM].second->getXAstrom();
        APAIR->PAIR[ALLNUM].X_LOCAL[1]    =matchlist[CID][NUM].second->getYAstrom();
        APAIR->PAIR[ALLNUM].X_LOCALERR[0] =matchlist[CID][NUM].second->getXAstromErr();
        APAIR->PAIR[ALLNUM].X_LOCALERR[1] =matchlist[CID][NUM].second->getYAstromErr();
        APAIR->PAIR[ALLNUM].X_RADECERR[0] =1;
        APAIR->PAIR[ALLNUM].X_RADECERR[1] =1;
        ALLNUM+=1;
    }
}
void    F_WCSA_MAKEPAIR_local(string matchlist,CL_GSIP* GSIP,CL_APAIR* APAIR){
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
//Getting Functions : WCS : REFERNCE
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLMAIN_GETREFALL_ID(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_ID;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_ID.push_back(WCSA_ASP->APAIR->PAIR[RID].ID);

    return ALLREFINFO_ID;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CHIPID(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CHIPID;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CHIPID.push_back(WCSA_ASP->APAIR->PAIR[RID].CHIPID);

    return ALLREFINFO_CHIPID;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_FLAG(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_FLAG;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_FLAG.push_back(WCSA_ASP->APAIR->PAIR[RID].FLAG);

    return ALLREFINFO_FLAG;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYLOCAL(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_XYLOCAL(2);
    std::vector< std::vector< double > > ALLREFINFO_XYLOCALS;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
    ALLREFINFO_XYLOCAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[0];
    ALLREFINFO_XYLOCAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[1];
    ALLREFINFO_XYLOCALS.push_back(ALLREFINFO_XYLOCAL);
    }

    return ALLREFINFO_XYLOCALS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYRADEC(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_XYRADEC(2);
    std::vector< std::vector< double > > ALLREFINFO_XYRADECS;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
    ALLREFINFO_XYRADEC[0]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[0];
    ALLREFINFO_XYRADEC[1]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[1];
    ALLREFINFO_XYRADECS.push_back(ALLREFINFO_XYRADEC);
    }

    return ALLREFINFO_XYRADECS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYGLOBAL(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_XYGLOBAL(2);
    std::vector< std::vector< double > > ALLREFINFO_XYGLOBALS;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
    ALLREFINFO_XYGLOBAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[0];
    ALLREFINFO_XYGLOBAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[1];
    ALLREFINFO_XYGLOBALS.push_back(ALLREFINFO_XYGLOBAL);
    }

    return ALLREFINFO_XYGLOBALS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYGLOBALCRPIX(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_XYGLOBALCRPIX(2);
    std::vector< std::vector< double > > ALLREFINFO_XYGLOBALCRPIXS;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
    ALLREFINFO_XYGLOBALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[0];
    ALLREFINFO_XYGLOBALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[1];
    ALLREFINFO_XYGLOBALCRPIXS.push_back(ALLREFINFO_XYGLOBALCRPIX);
    }

    return ALLREFINFO_XYGLOBALCRPIXS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYLOCALCRPIX(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_XYLOCALCRPIX(2);
    std::vector< std::vector< double > > ALLREFINFO_XYLOCALCRPIXS;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
    ALLREFINFO_XYLOCALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[0];
    ALLREFINFO_XYLOCALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[1];
    ALLREFINFO_XYLOCALCRPIXS.push_back(ALLREFINFO_XYLOCALCRPIX);
    }

    return ALLREFINFO_XYLOCALCRPIXS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYIMPIXEL(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_XYIMPIXEL(2);
    std::vector< std::vector< double > > ALLREFINFO_XYIMPIXELS;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
    ALLREFINFO_XYIMPIXEL[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[0];
    ALLREFINFO_XYIMPIXEL[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[1];
    ALLREFINFO_XYIMPIXELS.push_back(ALLREFINFO_XYIMPIXEL);
    }

    return ALLREFINFO_XYIMPIXELS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFALL_XYIMWORLD(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_XYIMWORLD(2);
    std::vector< std::vector< double > > ALLREFINFO_XYIMWORLDS;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
    ALLREFINFO_XYIMWORLD[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[0];
    ALLREFINFO_XYIMWORLD[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[1];
    ALLREFINFO_XYIMWORLDS.push_back(ALLREFINFO_XYIMWORLD);
    }

    return ALLREFINFO_XYIMWORLDS;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERACONV(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CAMERACONV;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CAMERACONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[0]);

    return ALLREFINFO_CAMERACONV;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAROT(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CAMERAROT;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CAMERAROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[1]);

    return ALLREFINFO_CAMERAROT;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERASHEAR1(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CAMERASHEAR1;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CAMERASHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[0]);

    return ALLREFINFO_CAMERASHEAR1;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERASHEAR2(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CAMERASHEAR2;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CAMERASHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[1]);

    return ALLREFINFO_CAMERASHEAR2;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CAMERAMAGNIFICATION;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CAMERAMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_MAGNIFICATION);

    return ALLREFINFO_CAMERAMAGNIFICATION;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAPCONV(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CAMERAPCONV;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CAMERAPCONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[0]);

    return ALLREFINFO_CAMERAPCONV;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAPROT(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CAMERAPROT;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CAMERAPROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[1]);

    return ALLREFINFO_CAMERAPROT;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAPSHEAR1(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CAMERAPSHEAR1;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CAMERAPSHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[0]);

    return ALLREFINFO_CAMERAPSHEAR1;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAPSHEAR2(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CAMERAPSHEAR2;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CAMERAPSHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[1]);

    return ALLREFINFO_CAMERAPSHEAR2;
}
std::vector< double > F_WCSA_PLMAIN_GETREFALL_CAMERAPMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP){
    int RID;
    std::vector< double > ALLREFINFO_CAMERAPMAGNIFICATION;

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    ALLREFINFO_CAMERAPMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PMAGNIFICATION);

    return ALLREFINFO_CAMERAPMAGNIFICATION;
}

std::vector< double > F_WCSA_PLMAIN_GETREFCCD_ID(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_ID;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_ID.push_back(WCSA_ASP->APAIR->PAIR[RID].ID);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_ID(F_WCSA_PLMAIN_GETREFCCD_ID)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_ID.push_back(0);
    }

    return CCDREFINFO_ID;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CHIPID(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CHIPID;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CHIPID.push_back(WCSA_ASP->APAIR->PAIR[RID].CHIPID);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CHIPID(F_WCSA_PLMAIN_GETREFCCD_CHIPID)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CHIPID.push_back(0);
    }

    return CCDREFINFO_CHIPID;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_FLAG(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_FLAG;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_FLAG.push_back(WCSA_ASP->APAIR->PAIR[RID].FLAG);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_FLAG(F_WCSA_PLMAIN_GETREFCCD_FLAG)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_FLAG.push_back(0);
    }

    return CCDREFINFO_FLAG;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYLOCAL(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_XYLOCAL(2);
    std::vector< std::vector< double > > CCDREFINFO_XYLOCALS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            CCDREFINFO_XYLOCAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[0];
            CCDREFINFO_XYLOCAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[1];
            CCDREFINFO_XYLOCALS.push_back(CCDREFINFO_XYLOCAL);
        }
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_XYLOCAL(F_WCSA_PLMAIN_GETREFCCD_XYLOCAL)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_XYLOCAL.push_back(0);
        CCDREFINFO_XYLOCALS.push_back(CCDREFINFO_XYLOCAL);
    }

    return CCDREFINFO_XYLOCALS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYRADEC(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_XYRADEC(2);
    std::vector< std::vector< double > > CCDREFINFO_XYRADECS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            CCDREFINFO_XYRADEC[0]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[0];
            CCDREFINFO_XYRADEC[1]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[1];
            CCDREFINFO_XYRADECS.push_back(CCDREFINFO_XYRADEC);
        }
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_XYRADEC(F_WCSA_PLMAIN_GETREFCCD_XYRADEC)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_XYRADEC.push_back(0);
        CCDREFINFO_XYRADECS.push_back(CCDREFINFO_XYRADEC);
    }

    return CCDREFINFO_XYRADECS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYGLOBAL(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_XYGLOBAL(2);
    std::vector< std::vector< double > > CCDREFINFO_XYGLOBALS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            CCDREFINFO_XYGLOBAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[0];
            CCDREFINFO_XYGLOBAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[1];
            CCDREFINFO_XYGLOBALS.push_back(CCDREFINFO_XYGLOBAL);
        }
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_XYGLOBAL(F_WCSA_PLMAIN_GETREFCCD_XYGLOBAL)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_XYGLOBAL.push_back(0);
        CCDREFINFO_XYGLOBALS.push_back(CCDREFINFO_XYGLOBAL);
    }

    return CCDREFINFO_XYGLOBALS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYGLOBALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_XYGLOBALCRPIX(2);
    std::vector< std::vector< double > > CCDREFINFO_XYGLOBALCRPIXS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            CCDREFINFO_XYGLOBALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[0];
            CCDREFINFO_XYGLOBALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[1];
            CCDREFINFO_XYGLOBALCRPIXS.push_back(CCDREFINFO_XYGLOBALCRPIX);
        }
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_XYGLOBALCRPIX(F_WCSA_PLMAIN_GETREFCCD_XYGLOBALCRPIX)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_XYGLOBALCRPIX.push_back(0);
        CCDREFINFO_XYGLOBALCRPIXS.push_back(CCDREFINFO_XYGLOBALCRPIX);
    }

    return CCDREFINFO_XYGLOBALCRPIXS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYLOCALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_XYLOCALCRPIX(2);
    std::vector< std::vector< double > > CCDREFINFO_XYLOCALCRPIXS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            CCDREFINFO_XYLOCALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[0];
            CCDREFINFO_XYLOCALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[1];
            CCDREFINFO_XYLOCALCRPIXS.push_back(CCDREFINFO_XYLOCALCRPIX);
        }
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_XYLOCALCRPIX(F_WCSA_PLMAIN_GETREFCCD_XYLOCALCRPIX)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_XYLOCALCRPIX.push_back(0);
        CCDREFINFO_XYLOCALCRPIXS.push_back(CCDREFINFO_XYLOCALCRPIX);
    }

    return CCDREFINFO_XYLOCALCRPIXS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYIMPIXEL(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_XYIMPIXEL(2);
    std::vector< std::vector< double > > CCDREFINFO_XYIMPIXELS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            CCDREFINFO_XYIMPIXEL[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[0];
            CCDREFINFO_XYIMPIXEL[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[1];
            CCDREFINFO_XYIMPIXELS.push_back(CCDREFINFO_XYIMPIXEL);
        }
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_XYIMPIXEL(F_WCSA_PLMAIN_GETREFCCD_XYIMPIXEL)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_XYIMPIXEL.push_back(0);
        CCDREFINFO_XYIMPIXELS.push_back(CCDREFINFO_XYIMPIXEL);
    }

    return CCDREFINFO_XYIMPIXELS;
}
std::vector< std::vector< double > > F_WCSA_PLMAIN_GETREFCCD_XYIMWORLD(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_XYIMWORLD(2);
    std::vector< std::vector< double > > CCDREFINFO_XYIMWORLDS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            CCDREFINFO_XYIMWORLD[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[0];
            CCDREFINFO_XYIMWORLD[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[1];
            CCDREFINFO_XYIMWORLDS.push_back(CCDREFINFO_XYIMWORLD);
        }
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_XYIMWORLD(F_WCSA_PLMAIN_GETREFCCD_XYIMWORLD)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_XYIMWORLD.push_back(0);
        CCDREFINFO_XYIMWORLDS.push_back(CCDREFINFO_XYIMWORLD);
    }

    return CCDREFINFO_XYIMWORLDS;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERACONV(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CAMERACONV;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CAMERACONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[0]);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CAMERA_CONVERGENCE(F_WCSA_PLMAIN_GETREFCCD_CAMERACONV)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CAMERACONV.push_back(0);
    }

    return CCDREFINFO_CAMERACONV;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAROT(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CAMERAROT;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CAMERAROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[1]);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CAMERA_ROTATION(F_WCSA_PLMAIN_GETREFCCD_CAMERAROT)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CAMERAROT.push_back(0);
    }

    return CCDREFINFO_CAMERAROT;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERASHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CAMERASHEAR1;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CAMERASHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[0]);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CAMERA_SHEAR1(F_WCSA_PLMAIN_GETREFCCD_CAMERASHEAR1)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CAMERASHEAR1.push_back(0);
    }

    return CCDREFINFO_CAMERASHEAR1;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERASHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CAMERASHEAR2;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CAMERASHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[1]);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CAMERA_SHEAR2(F_WCSA_PLMAIN_GETREFCCD_CAMERASHEAR2)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CAMERASHEAR2.push_back(0);
    }

    return CCDREFINFO_CAMERASHEAR2;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CAMERAMAGNIFICATION;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CAMERAMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_MAGNIFICATION);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CAMERA_MAGNIFICATION(F_WCSA_PLMAIN_GETREFCCD_CAMERAMAGNIFICATION)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CAMERAMAGNIFICATION.push_back(0);
    }

    return CCDREFINFO_CAMERAMAGNIFICATION;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAPCONV(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CAMERAPCONV;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CAMERAPCONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[0]);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CAMERA_PCONVERGENCE(F_WCSA_PLMAIN_GETREFCCD_CAMERAPCONV)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CAMERAPCONV.push_back(0);
    }

    return CCDREFINFO_CAMERAPCONV;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAPROT(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CAMERAPROT;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CAMERAPROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[1]);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CAMERA_PROTATION(F_WCSA_PLMAIN_GETREFCCD_CAMERAPROT)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CAMERAPROT.push_back(0);
    }

    return CCDREFINFO_CAMERAPROT;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAPSHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CAMERAPSHEAR1;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CAMERAPSHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[0]);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CAMERA_PSHEAR1(F_WCSA_PLMAIN_GETREFCCD_CAMERAPSHEAR1)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CAMERAPSHEAR1.push_back(0);
    }

    return CCDREFINFO_CAMERAPSHEAR1;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAPSHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CAMERAPSHEAR2;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CAMERAPSHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[1]);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CAMERA_PSHEAR2(F_WCSA_PLMAIN_GETREFCCD_CAMERAPSHEAR2)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CAMERAPSHEAR2.push_back(0);
    }

    return CCDREFINFO_CAMERAPSHEAR2;
}
std::vector< double > F_WCSA_PLMAIN_GETREFCCD_CAMERAPMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > CCDREFINFO_CAMERAPMAGNIFICATION;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        CCDREFINFO_CAMERAPMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PMAGNIFICATION);
    }else{
        cout << "Warning : in WCS_GET_REFERENCE_CCD_CAMERA_PMAGNIFICATION(F_WCSA_PLMAIN_GETREFCCD_CAMERAPMAGNIFICATION)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDREFINFO_CAMERAPMAGNIFICATION.push_back(0);
    }

    return CCDREFINFO_CAMERAPMAGNIFICATION;
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
//Getting Functions : WCS : CCD
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
    std::vector< double > REFERENCE(19);
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
        REFERENCE[15]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_MAGROT[0];
        REFERENCE[16]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_MAGROT[1];
        REFERENCE[17]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_SHEAR[0];
        REFERENCE[18]=WCSA_ASP->APAIR->PAIR[NUM].CAMERA_SHEAR[1];
        REFERENCES.push_back(REFERENCE);
/*test ->*/
for(i=0;i<19;i++)
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
