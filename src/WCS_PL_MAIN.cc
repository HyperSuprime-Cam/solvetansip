//------------------------------------------------------------
//WCS_PL_MAIN.cc
//main program for wcs in pipeline
//
//Last modification : 2011/05/20
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

void    F_WCS_MAKEAPROP(lsst::pex::policy::Policy::Ptr &,CL_APROP*);
void    F_WCS_MAKECPROP(lsst::afw::cameraGeom::Camera::Ptr &, CL_APROP*, CL_CPROP *);
void    F_WCS_SETSIZE(vector< vector< afwdetect::SourceMatch  >  > const &, CL_APROP*, CL_CPROP *);
void    F_WCS_SETCSIP(CL_APROP*, CL_CSIP *);
void    F_WCS_MAKEPAIR(vector< vector< afwdetect::SourceMatch  >  > const &, CL_APROP *, CL_CPROP *,CL_PAIR *);
void    F_WCS_SETSIZE_local(string matchlist, CL_APROP*, CL_CPROP *);
void    F_WCS_MAKEPAIR_local(string matchlist, CL_APROP *, CL_CPROP *,CL_PAIR *);
CL_WCSACCP F_WCS_MAKE_WCSACCP(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
dafbase::PropertySet::Ptr F_WCS_EMPTYMETADATA();
afwImage::TanWcs::Ptr    F_WCS_MAKERESULTWCS(CL_CSIP *);
//vector<afwImage::TanWcs::Ptr>    F_WCS_TANSIP_V(vector< vector<afwdetect::SourceMatch> > const &matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/,CL_CPROP *CPROPout,CL_CSIP *CSIPout, CL_PAIR *PAIRout){
CL_WCSACCP F_WCS_TANSIP_V(vector< vector<afwdetect::SourceMatch> > const &matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/){
    cout <<endl<< "--- solvetansip : START ---" << endl;

//------------------------------------------------------
//MAKING PROPERTY FILE
    CL_APROP *APROP;
    CL_CPROP *CPROP;
    CL_PAIR  *PAIR;
    CL_CSIP  *CSIP;
    CL_WCSACCP WCSACCP;

    APROP = new CL_APROP[1];
    F_WCS_MAKEAPROP(APROPPolicy, APROP);
    
    CPROP = new CL_CPROP[APROP->CCDNUM];
    F_WCS_MAKECPROP(camera, APROP, CPROP);
    F_WCS_SETSIZE(matchlist, APROP, CPROP);

    PAIR = new CL_PAIR[APROP->NUMREFALL];
    F_WCS_MAKEPAIR(matchlist, APROP, CPROP, PAIR);

    CSIP = new CL_CSIP[APROP->CCDNUM+1];
    F_WCS_SETCSIP(APROP, CSIP);

//------------------------------------------------------
//solve TANSIP
    F_WCS_TANSIP(APROP,CPROP,PAIR,CSIP);

// ------------------------------------------------------
//SET METADATA
//------------------------------------------------------
//MAKING WCSACCP
    WCSACCP = F_WCS_MAKE_WCSACCP(APROP,CPROP,PAIR,CSIP);

    cout << "--- solvetansip : END ---" << endl;
    return WCSACCP;

}
CL_WCSACCP F_WCS_TANSIP_V_local(string matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/){
    cout <<endl<< "--- solvetansip_local : START ---" << endl;

//------------------------------------------------------
//MAKING PROPERTY FILE
    CL_APROP *APROP;
    CL_CPROP *CPROP;
    CL_PAIR  *PAIR;
    CL_CSIP  *CSIP;
    CL_WCSACCP WCSACCP;

    APROP = new CL_APROP[1];
    F_WCS_MAKEAPROP(APROPPolicy, APROP);
    
    CPROP = new CL_CPROP[APROP->CCDNUM];
    F_WCS_SETSIZE_local(matchlist, APROP, CPROP);
    F_WCS_MAKECPROP(camera, APROP, CPROP);

    PAIR = new CL_PAIR[APROP->NUMREFALL];
    F_WCS_MAKEPAIR_local(matchlist, APROP, CPROP, PAIR);

    CSIP = new CL_CSIP[APROP->CCDNUM+1];
    F_WCS_SETCSIP(APROP, CSIP);

//------------------------------------------------------
//solve TANSIP
    F_WCS_TANSIP(APROP,CPROP,PAIR,CSIP);

// ------------------------------------------------------
//SET METADATA
//------------------------------------------------------
//MAKING WCSACCP
    WCSACCP = F_WCS_MAKE_WCSACCP(APROP,CPROP,PAIR,CSIP);

    cout << "--- solvetansip : END ---" << endl;
    return WCSACCP;

}
//SUB ROUTINES
void    F_WCS_MAKEAPROP(lsst::pex::policy::Policy::Ptr &APROPPolicy, CL_APROP *APROP){
    string CMODE;
    CMODE              =APROPPolicy->getString("CRPIXMODE");
    strcpy(APROP->CRPIXMODE,CMODE.c_str());
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
    APROP->BASISCID    =APROPPolicy->getInt("BASISCCD");
    APROP->BASIS_POS[0]=APROPPolicy->getDouble("BASISPOSX");
    APROP->BASIS_POS[1]=APROPPolicy->getDouble("BASISPOSY");
    APROP->BASIS_POS[2]=APROPPolicy->getDouble("BASISPOST");
    APROP->STDOUT      =APROPPolicy->getInt("STDOUT");
    APROP->NUMREFALL   = 0;

    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_APROP ---" << endl;
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "-- APROP CHECK --" << endl;
    if(APROP->STDOUT==2){
    cout << "CRPIXMODE   : " << APROP->CRPIXMODE   << endl;
    cout << "CCDPOSMODE  : " << APROP->CCDPOSMODE  << endl;
    cout << "CRPIX1      : " << APROP->CRPIX[0]    << endl;
    cout << "CRPIX2      : " << APROP->CRPIX[1]    << endl;
    cout << "CRVAL1      : " << APROP->CRVAL[0]    << endl;
    cout << "CRVAL2      : " << APROP->CRVAL[1]    << endl;
    cout << "SIP_L_ORDER : " << APROP->SIP_L_ORDER << endl;
    cout << "SIP_ORDER   : " << APROP->SIP_ORDER   << endl;
    cout << "SIP_PORDER  : " << APROP->SIP_P_ORDER << endl;
    cout << "CRIP_SIGMA  : " << APROP->CLIP_SIGMA  << endl;
    cout << "CCDNUM      : " << APROP->CCDNUM      << endl;
    cout << "BASISCCD    : " << APROP->BASISCID    << endl;
    cout << "BASISPOSX   : " << APROP->BASIS_POS[0]<< endl;
    cout << "BASISPOSY   : " << APROP->BASIS_POS[1]<< endl;
    cout << "BASISPOST   : " << APROP->BASIS_POS[2]<< endl;
    cout <<endl;
    }
}
void    F_WCS_MAKECPROP(lsst::afw::cameraGeom::Camera::Ptr &camera, CL_APROP *APROP, CL_CPROP *CPROP){
    int ID;

    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_CPROP ---" << endl;

    for(camGeom::Camera::const_iterator iter(camera->begin()); iter != camera->end(); ++iter) { 
        camGeom::DetectorMosaic::Ptr detMosaic = boost::shared_dynamic_cast<camGeom::DetectorMosaic>(*iter);

        for(ID=0;ID<APROP->CCDNUM;ID++){
            camGeom::Id detId = camGeom::Id(ID);//serial
            camGeom::Detector::Ptr det = detMosaic->findDetector(detId);
            afwGeom::Point2D offsetXY = det->getCenter();
//            double ccdTiltYaw = (det->getOrientation()).getYaw();
  //          int ccdTiltNQuarter = (det->getOrientation()).getNQuarter();

            CPROP[ID].ID=detId.getSerial();
            CPROP[ID].GLOB_POS[0]=offsetXY[0];
            CPROP[ID].GLOB_POS[1]=offsetXY[1];
            CPROP[ID].GLOB_POS[2]=0;//ccdTiltNQuarter * 90.0;//?
            CPROP[ID].POSID[0]=detId.getIndex().first;
            CPROP[ID].POSID[1]=detId.getIndex().second;
        }
    }

//--------------------------------------------------
    char CPROPIDFILE[100];
    int POSID[2],ALIGN;
    ifstream fin;

    if(APROP->CCDNUM<11){
    sprintf(CPROPIDFILE,"../policy/WCS_MAKECPROP_POSIDALIGN_SC.paf");
    }else{
    sprintf(CPROPIDFILE,"../policy/WCS_MAKECPROP_POSIDALIGN_HSC.paf");
    }

    fin.open(CPROPIDFILE);
    if(!fin){
        cout << "Warning : Can't read " << CPROPIDFILE << endl;
        cout << "          Using 000 - 009 CCDs for CCD alignment" << endl;
        CPROP[0].ALIGN=CPROP[1].ALIGN=CPROP[2].ALIGN=CPROP[3].ALIGN=CPROP[4].ALIGN=CPROP[5].ALIGN=CPROP[6].ALIGN=CPROP[7].ALIGN=CPROP[8].ALIGN=CPROP[9].ALIGN=1;
    }
    while((fin >> ID >> POSID[0] >> POSID[1] >> ALIGN) !=0){
    if(ID<APROP->CCDNUM){
        CPROP[ID].POSID[0]=POSID[0];
        CPROP[ID].POSID[1]=POSID[1];
        CPROP[ID].ALIGN=ALIGN;
    }}
    fin.close();
//--------------------------------------------------

    if(APROP->STDOUT==2)cout << "NUMREFALL   : " << APROP->NUMREFALL   << endl;
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "-- CPROP CHECK --" << endl;
    if(APROP->STDOUT==2){
    cout << "- CCD : " << setw(3) << setfill('0') << CPROP[0].ID  << " -"<< endl;
    cout << "ID          : " << CPROP[0].ID       << endl;
    cout << "Index X     : " << CPROP[0].POSID[0] << endl;
    cout << "Index Y     : " << CPROP[0].POSID[1] << endl;
    cout << "NUMREF      : " << CPROP[0].NUMREF   << endl;
    cout << "PHASE       : " << CPROP[0].PHASE    << endl;
    cout << "INITIAL X   : " << CPROP[0].GLOB_POS[0] << endl;
    cout << "INITIAL Y   : " << CPROP[0].GLOB_POS[1] << endl;
    cout << "INITIAL T   : " << CPROP[0].GLOB_POS[2] << endl;
    cout << "- CCD : " << setw(3) << setfill('0') << CPROP[APROP->CCDNUM-1].ID << " -" <<endl;
    cout << "ID          : " << CPROP[APROP->CCDNUM-1].ID     << endl;
    cout << "Index X     : " << CPROP[APROP->CCDNUM-1].POSID[0] << endl;
    cout << "Index Y     : " << CPROP[APROP->CCDNUM-1].POSID[1] << endl;
    cout << "NUMREF      : " << CPROP[APROP->CCDNUM-1].NUMREF << endl;
    cout << "PHASE       : " << CPROP[APROP->CCDNUM-1].PHASE  << endl;
    cout << "INITIAL X   : " << CPROP[APROP->CCDNUM-1].GLOB_POS[0] << endl;
    cout << "INITIAL Y   : " << CPROP[APROP->CCDNUM-1].GLOB_POS[1] << endl;
    cout << "INITIAL T   : " << CPROP[APROP->CCDNUM-1].GLOB_POS[2] << endl; 
    cout <<endl;
    }
}
void    F_WCS_SETSIZE(vector< vector< afwdetect::SourceMatch  >  > const &matchlist, CL_APROP* APROP, CL_CPROP *CPROP){
    int ID;
    for(ID=0;ID<APROP->CCDNUM;ID++){
        CPROP[ID].NUMREF =matchlist[ID].size();
        APROP->NUMREFALL+=matchlist[ID].size();
    }
}
void    F_WCS_SETSIZE_local(string matchlist, CL_APROP* APROP, CL_CPROP *CPROP){
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
    for(CID=0;CID<APROP->CCDNUM;CID++)
    CPROP[CID].NUMREF = CIDNUM[CID];
    APROP->NUMREFALL = CIDNUM[APROP->CCDNUM];
    in.close();

    delete [] CIDNUM;
}
#define PI (4*atan(1.0))
void    F_WCS_MAKEPAIR(vector< vector<afwdetect::SourceMatch> > const &matchlist,CL_APROP *APROP,CL_CPROP* CPROP,CL_PAIR* PAIR){
    int CID,NUM,ALLNUM;

    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_PAIR ---" << endl;
ofstream PAIRout;
PAIRout.open("PAIR.dat");//temp

    ALLNUM=0;
    for(CID=0;CID<APROP->CCDNUM;CID++)
    for(NUM=0;NUM<CPROP[CID].NUMREF;NUM++){
        PAIR[ALLNUM].ID    =matchlist[CID][NUM].first->getId();
        PAIR[ALLNUM].CHIPID=CID;
        PAIR[ALLNUM].FLAG  =1;
//        afwCoord::Coord::Ptr radec = matchlist[CID][NUM].first->getRaDec();
//        PAIR[ALLNUM].RA    = radec->getLongitude(afwCoord::DEGREES);
//        PAIR[ALLNUM].DEC   = radec->getLatitude(afwCoord::DEGREES);
        PAIR[ALLNUM].RA    = 180.0/PI*matchlist[CID][NUM].first->getRa();
        PAIR[ALLNUM].DEC   = 180.0/PI*matchlist[CID][NUM].first->getDec();
        PAIR[ALLNUM].xL    =matchlist[CID][NUM].second->getXAstrom();
        PAIR[ALLNUM].yL    =matchlist[CID][NUM].second->getYAstrom();
        PAIR[ALLNUM].xErr  =matchlist[CID][NUM].second->getXAstromErr();
        PAIR[ALLNUM].yErr  =matchlist[CID][NUM].second->getYAstromErr();
        PAIR[ALLNUM].RAErr =1;
        PAIR[ALLNUM].DECErr=1;
PAIRout << PAIR[ALLNUM].ID << "     " << PAIR[ALLNUM].CHIPID << "     " << PAIR[ALLNUM].FLAG << "    " << PAIR[ALLNUM].xL << "       " << PAIR[ALLNUM].yL << "       " << PAIR[ALLNUM].RA << "      " << PAIR[ALLNUM].DEC << endl;//temp
        ALLNUM+=1;
    }
    APROP->NUMREFALL=ALLNUM;
//cout <<ALLNUM<<endl;
PAIRout.close();//temp
}
void    F_WCS_MAKEPAIR_local(string matchlist,CL_APROP *APROP,CL_CPROP* CPROP,CL_PAIR* PAIR){
    int ID,CID,NUM,ALLNUM;
    double x,y,RA,DEC;
    ifstream in;

    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_PAIR ---" << endl;
ofstream PAIRout;
PAIRout.open("PAIR.dat");//temp

    in.open(matchlist.c_str());
    cout << matchlist.c_str() << endl;
    ALLNUM=0;
    while((in >> ID >> CID >> x >> y >> RA >> DEC)!=0){
        PAIR[ALLNUM].ID    =ID;
        PAIR[ALLNUM].CHIPID=CID;
        PAIR[ALLNUM].FLAG  =1;
        PAIR[ALLNUM].RA    =RA;
        PAIR[ALLNUM].DEC   =DEC;
        PAIR[ALLNUM].xL    =x;
        PAIR[ALLNUM].yL    =y;
        PAIR[ALLNUM].xErr  =1;
        PAIR[ALLNUM].yErr  =1;
        PAIR[ALLNUM].RAErr =1;
        PAIR[ALLNUM].DECErr=1;
        ALLNUM++;
PAIRout << PAIR[ALLNUM].ID << "     " << PAIR[ALLNUM].CHIPID << "     " << PAIR[ALLNUM].FLAG << "    " << PAIR[ALLNUM].xL << "       " << PAIR[ALLNUM].yL << "       " << PAIR[ALLNUM].RA << "      " << PAIR[ALLNUM].DEC << endl;//temp        ALLNUM+=1;
    }

    APROP->NUMREFALL=ALLNUM;

PAIRout.close();//temp
}
#undef PI
void    F_WCS_SETCSIP(CL_APROP* APROP, CL_CSIP *CSIP){
    int CID,i;

    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : SET_CSIP ---" << endl;

    for(CID=0;CID<APROP->CCDNUM+1;CID++){
    for(i=0;i<2;i++){
        CSIP[CID].SIP_AB[i]    = F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
        CSIP[CID].SIP_ABP[i]   = F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
        CSIP[CID].TCoef[i]     = F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
        CSIP[CID].TPCoef[i]    = F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
        CSIP[CID].TLCoef[i]    = F_NEWdouble1((APROP->SIP_L_ORDER+1)*(APROP->SIP_L_ORDER+2));
    }
//        CSIP[CID].SIP_ABD[0]   = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
  //      CSIP[CID].SIP_ABD[1]   = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        CSIP[CID].SIP_MAG      = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        CSIP[CID].SIP_SHEAR[0] = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        CSIP[CID].SIP_SHEAR[1] = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        CSIP[CID].SIP_ROT      = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        CSIP[CID].PSIP_MAG     = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        CSIP[CID].PSIP_SHEAR[0]= new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        CSIP[CID].PSIP_SHEAR[1]= new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        CSIP[CID].PSIP_ROT     = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
    }
}
CL_WCSACCP F_WCS_MAKE_WCSACCP(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_WCSACCP ---" << endl;
    vector <afwImage::TanWcs::Ptr> resultWcs_V;
    vector <CL_CPROP*> CPROP_V;
    vector <CL_CSIP*> CSIP_V;
    CL_WCSACCP WCSACCP;
    afwImage::TanWcs::Ptr resultWcs;

    int CID;
    for(CID=0;CID<APROP->CCDNUM+1;CID++){
    resultWcs = F_WCS_MAKERESULTWCS(&CSIP[CID]);
    resultWcs_V.push_back(resultWcs);
    CPROP_V.push_back(&CPROP[CID]);
    CSIP_V.push_back(&CSIP[CID]);
    }

    WCSACCP.WCSPtr = resultWcs_V;
    WCSACCP.APROP = APROP;
    WCSACCP.CPROP = CPROP;
    WCSACCP.CSIP  = CSIP;
    WCSACCP.PAIR  = PAIR;
    WCSACCP.CPROPList = CPROP_V;
    WCSACCP.CSIPList  = CSIP_V;

    return WCSACCP;
}
afwImage::TanWcs::Ptr    F_WCS_MAKERESULTWCS(CL_CSIP *CSIP){
    int i,j;

    afwGeom::PointD crpix = afwGeom::PointD(CSIP->CRPIX[0], CSIP->CRPIX[1]);
    afwGeom::PointD crval = afwGeom::PointD(CSIP->CRVAL[0], CSIP->CRVAL[1]);

    Eigen::Matrix2d cdMatrix;
    cdMatrix << CSIP->CD[0][0], CSIP->CD[0][1], CSIP->CD[1][0], CSIP->CD[1][1];
    Eigen::MatrixXd sipA  = Eigen::MatrixXd::Zero(CSIP->SIP_AB_ORDER+1, CSIP->SIP_AB_ORDER+1);
    Eigen::MatrixXd sipB  = Eigen::MatrixXd::Zero(CSIP->SIP_AB_ORDER+1, CSIP->SIP_AB_ORDER+1);
    Eigen::MatrixXd sipAp = Eigen::MatrixXd::Zero(CSIP->SIP_ABP_ORDER+1,CSIP->SIP_ABP_ORDER+1);
    Eigen::MatrixXd sipBp = Eigen::MatrixXd::Zero(CSIP->SIP_ABP_ORDER+1,CSIP->SIP_ABP_ORDER+1);

    int ij=0;
    for(i=0;i<CSIP->SIP_AB_ORDER+1;i++)
    for(j=0;j<CSIP->SIP_AB_ORDER+1;j++)
    if(i+j<CSIP->SIP_AB_ORDER+1){
        sipA(i,j) = CSIP->SIP_AB[0][ij];
        sipB(i,j) = CSIP->SIP_AB[1][ij];
        ij++;
    }else{
        sipA(i,j) = 0.0;
        sipB(i,j) = 0.0;
    }
    ij=0;
    for(i=0;i<CSIP->SIP_ABP_ORDER+1;i++)
    for(j=0;j<CSIP->SIP_ABP_ORDER+1;j++)
    if(i+j<CSIP->SIP_ABP_ORDER+1){
        sipAp(i,j) = CSIP->SIP_ABP[0][ij];
        sipBp(i,j) = CSIP->SIP_ABP[1][ij];
        ij++;
    }else{
        sipAp(i,j) = 0.0;
        sipBp(i,j) = 0.0;
    }

    afwImage::TanWcs::Ptr    resultTanWcs(new afwImage::TanWcs(crval, crpix, cdMatrix, sipA, sipB, sipAp, sipBp));
    return resultTanWcs;
}
dafbase::PropertySet::Ptr F_WCS_EMPTYMETADATA(){
    dafbase::PropertySet::Ptr metadata(new dafbase::PropertySet);
    return metadata;
}
std::vector <lsst::afw::image::TanWcs::Ptr> F_WCS_GETWCSLIST(CL_WCSACCP* WCSACCP){
    return WCSACCP->WCSPtr;
}
CL_APROP* F_WCS_GETAPROP(CL_WCSACCP* WCSACCP){
    return WCSACCP->APROP;
}
CL_CPROP* F_WCS_GETCPROP(CL_WCSACCP* WCSACCP){
    return WCSACCP->CPROP;
}
CL_CSIP*  F_WCS_GETCSIP(CL_WCSACCP* WCSACCP){
    return WCSACCP->CSIP;
}
CL_PAIR*  F_WCS_GETPAIR(CL_WCSACCP* WCSACCP){
    return WCSACCP->PAIR;
}
std::vector <CL_CPROP*> F_WCS_GETCPROPLIST(CL_WCSACCP* WCSACCP){
    return WCSACCP->CPROPList;
}
std::vector <CL_CSIP*>  F_WCS_GETCSIPLIST(CL_WCSACCP* WCSACCP){
    return WCSACCP->CSIPList;
}
