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
void    F_WCS_MAKECPROP(lsst::afw::cameraGeom::Camera::Ptr &,vector< vector< afwdetect::SourceMatch  >  > const &, CL_APROP*, CL_CPROP *);
void    F_WCS_SETCC_PRECSIPfromFILE(CL_APROP, char *, char *,CL_CSIP *);
void    F_WCS_MAKEPAIR(vector< vector< afwdetect::SourceMatch  >  > const &, CL_APROP *, CL_CPROP *,CL_PAIR *);
void    F_WCS_SETDEFAULTDISTORTION(CL_CSIP *);
dafbase::PropertySet::Ptr F_WCS_EMPTYMETADATA();
CL_CPROP* F_WCS_EMPTYCPROP();
CL_CSIP*  F_WCS_EMPTYCSIP();
CL_PAIR*  F_WCS_EMPTYPAIR();
afwImage::TanWcs::Ptr    F_WCS_MAKERESULTWCS(CL_CSIP *);
//vector<afwImage::TanWcs::Ptr>    F_WCS_TANSIP_V(vector< vector<afwdetect::SourceMatch> > const &matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/,CL_CPROP *CPROPout,CL_CSIP *CSIPout, CL_PAIR *PAIRout){
CL_WCSCCP F_WCS_TANSIP_V(vector< vector<afwdetect::SourceMatch> > const &matchlist,dafbase::PropertySet::Ptr &metaTANSIP,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/){
    cout <<endl<< "--- WCS_PL_MAIN :AAA ---" << endl;

//------------------------------------------------------
//MAKING PROPERTY FILE
    CL_APROP  APROP;
    CL_CPROP *CPROP;
    CL_PAIR  *PAIR;
    CL_CSIP  *CSIP;
    cout << "--- WCS_PL_MAIN : F_WCS_MAKE_APROP ---" << endl;
    F_WCS_MAKEAPROP(APROPPolicy, &APROP);
    cout << "-- APROP CHECK --" << endl;
    cout << "CRPIXMODE   : " << APROP.CRPIXMODE   << endl;
    cout << "CCDPOSMODE  : " << APROP.CCDPOSMODE  << endl;
    cout << "CRPIX1      : " << APROP.CRPIX[0]    << endl;
    cout << "CRPIX2      : " << APROP.CRPIX[1]    << endl;
    cout << "CRVAL1      : " << APROP.CRVAL[0]    << endl;
    cout << "CRVAL2      : " << APROP.CRVAL[1]    << endl;
    cout << "SIP_L_ORDER : " << APROP.SIP_L_ORDER << endl;
    cout << "SIP_ORDER   : " << APROP.SIP_ORDER   << endl;
    cout << "SIP_PORDER  : " << APROP.SIP_P_ORDER << endl;
    cout << "CRIP_SIGMA  : " << APROP.CLIP_SIGMA  << endl;
    cout << "CCDNUM      : " << APROP.CCDNUM      << endl;
    cout << "CHECKFILE   : " << APROP.CHECKFILE   << endl;
    cout << "BASISCCD    : " << APROP.BASISCID    << endl;
    cout << "BASISPOSX   : " << APROP.BASIS_POS[0]<< endl;
    cout << "BASISPOSY   : " << APROP.BASIS_POS[1]<< endl;
    cout << "BASISPOST   : " << APROP.BASIS_POS[2]<< endl;
    cout <<endl;
    
    cout << "--- WCS_PL_MAIN : F_WCS_MAKE_CPROP ---" << endl;
    CPROP = new CL_CPROP[APROP.CCDNUM];
    F_WCS_MAKECPROP(camera, matchlist, &APROP, CPROP);
    cout << "-- APROP CHECK --" << endl;
    cout << "NUMREFALL   : " << APROP.NUMREFALL   << endl;
    cout << "-- CPROP CHECK --" << endl;
    cout << "- CCD : " << setw(3) << setfill('0') << CPROP[0].ID  << " -"<< endl;
    cout << "ID          : " << CPROP[0].ID       << endl;
    cout << "Index X     : " << CPROP[0].POSID[0] << endl;
    cout << "Index Y     : " << CPROP[0].POSID[1] << endl;
    cout << "NUMREF      : " << CPROP[0].NUMREF   << endl;
    cout << "PHASE       : " << CPROP[0].PHASE    << endl;
    cout << "INITIAL X   : " << CPROP[0].GLOB_POS[0] << endl;
    cout << "INITIAL Y   : " << CPROP[0].GLOB_POS[1] << endl;
    cout << "INITIAL T   : " << CPROP[0].GLOB_POS[2] << endl;
    cout << "- CCD : " << setw(3) << setfill('0') << CPROP[APROP.CCDNUM-1].ID << " -" <<endl;
    cout << "ID          : " << CPROP[APROP.CCDNUM-1].ID     << endl;
    cout << "Index X     : " << CPROP[APROP.CCDNUM-1].POSID[0] << endl;
    cout << "Index Y     : " << CPROP[APROP.CCDNUM-1].POSID[1] << endl;
    cout << "NUMREF      : " << CPROP[APROP.CCDNUM-1].NUMREF << endl;
    cout << "PHASE       : " << CPROP[APROP.CCDNUM-1].PHASE  << endl;
    cout << "INITIAL X   : " << CPROP[APROP.CCDNUM-1].GLOB_POS[0] << endl;
    cout << "INITIAL Y   : " << CPROP[APROP.CCDNUM-1].GLOB_POS[1] << endl;
    cout << "INITIAL T   : " << CPROP[APROP.CCDNUM-1].GLOB_POS[2] << endl; 
    cout <<endl;

    cout << "--- WCS_PL_MAIN : F_WCS_MAKE_PAIR ---" << endl;
    PAIR = new CL_PAIR[APROP.NUMREFALL];
    F_WCS_MAKEPAIR(matchlist, &APROP, CPROP, PAIR);

    cout << "--- WCS_PL_MAIN : MAKE_CSIP ---" << endl;
    int CID;
    CSIP = new CL_CSIP[APROP.CCDNUM+1];
    for(CID=0;CID<APROP.CCDNUM+1;CID++){
        CSIP[CID].SIP_AB[0]    = new double[(APROP.SIP_ORDER  +1)*(APROP.SIP_ORDER  +2)];
        CSIP[CID].SIP_AB[1]    = new double[(APROP.SIP_ORDER  +1)*(APROP.SIP_ORDER  +2)];
        CSIP[CID].SIP_ABP[0]   = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].SIP_ABP[1]   = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].SIP_ABD[0]   = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].SIP_ABD[1]   = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].TCoef[0]     = new double[(APROP.SIP_ORDER  +1)*(APROP.SIP_ORDER  +2)];
        CSIP[CID].TCoef[1]     = new double[(APROP.SIP_ORDER  +1)*(APROP.SIP_ORDER  +2)];
        CSIP[CID].TPCoef[0]    = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].TPCoef[1]    = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].TLCoef[0]    = new double[(APROP.SIP_L_ORDER+1)*(APROP.SIP_L_ORDER+2)];
        CSIP[CID].TLCoef[1]    = new double[(APROP.SIP_L_ORDER+1)*(APROP.SIP_L_ORDER+2)];
        CSIP[CID].SIP_MAG      = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].SIP_SHEAR[0] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].SIP_SHEAR[1] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].SIP_ROT      = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].PSIP_MAG     = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].PSIP_SHEAR[0]= new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].PSIP_SHEAR[1]= new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
        CSIP[CID].PSIP_ROT     = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    }
    CSIP[APROP.CCDNUM].PREDICT_SIP_ABD[0] = new double[(APROP.PREDICT_SIP_D_ORDER+2)*(APROP.PREDICT_SIP_D_ORDER+1)];
    CSIP[APROP.CCDNUM].PREDICT_SIP_ABD[1] = new double[(APROP.PREDICT_SIP_D_ORDER+2)*(APROP.PREDICT_SIP_D_ORDER+1)];

//PREDICT CSIP
    char PRESSFILE[100],PREDSIPFILE[100];
    sprintf(PRESSFILE,"../policy/WCS_SS_PREDICT.paf");
    sprintf(PREDSIPFILE,"../policy/WCS_DSIP_PREDICT.paf");
    F_WCS_SETCC_PRECSIPfromFILE(APROP, PRESSFILE, PREDSIPFILE, &CSIP[APROP.CCDNUM]);
//------------------------------------------------------
    cout << "--- WCS_PL_MAIN : F_WCS_TANSIP ---" << endl;
    F_WCS_TANSIP(APROP,CPROP,PAIR,CSIP);

// ------------------------------------------------------
//SET METADATA
//------------------------------------------------------
//MAKING VECTOR OF WCS CLASS
    vector <afwImage::TanWcs::Ptr> resultWcs_V;
    cout << "--- WCS_PL_MAIN : F_WCS_MAKE_WCSVECTOR ---" << endl;
    afwImage::TanWcs::Ptr resultWcs;
    for(CID=0;CID<APROP.CCDNUM+1;CID++){
    resultWcs = F_WCS_MAKERESULTWCS(&CSIP[CID]);
    resultWcs_V.push_back(resultWcs);
//    resultWcs_V.push_back(F_WCS_MAKERESULTWCS(&CSIP[CID]));
    }

    CL_WCSCCP WCSCCP;
    WCSCCP.WCSPtr = resultWcs_V;
    WCSCCP.CPROP = CPROP;
    WCSCCP.CSIP  = CSIP;
    WCSCCP.PAIR  = PAIR;
    cout << "--- F_WCS_PL_MAIN : ZZZ ---" << endl;
//------------------------------------------------------
/*    for(CID=0;CID<APROP.CCDNUM+1;CID++){
        delete [] CSIP[CID].TCoef[0];
        delete [] CSIP[CID].TCoef[1];
        delete [] CSIP[CID].TPCoef[0];
        delete [] CSIP[CID].TPCoef[1];
    }*/
//------------------------------------------------------
    return WCSCCP;

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
    APROP->PREDICT_SIP_D_ORDER =APROPPolicy->getInt("PREORDER");
    APROP->CLIP_SIGMA  =APROPPolicy->getDouble("CLIPSIGMA");
    APROP->CHECKFILE   =APROPPolicy->getInt("CHECKFILE");
    APROP->BASISCID    =APROPPolicy->getInt("BASISCCD");
    APROP->BASIS_POS[0]=APROPPolicy->getDouble("BASISPOSX");
    APROP->BASIS_POS[1]=APROPPolicy->getDouble("BASISPOSY");
    APROP->BASIS_POS[2]=APROPPolicy->getDouble("BASISPOST");
}
void    F_WCS_MAKECPROP(lsst::afw::cameraGeom::Camera::Ptr &camera, vector< vector< afwdetect::SourceMatch > > const &matchlist, CL_APROP *APROP, CL_CPROP *CPROP){
    int ID;

    APROP->NUMREFALL=0;
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
            CPROP[ID].NUMREF =matchlist[ID].size();
            APROP->NUMREFALL+=matchlist[ID].size();
        }
    }

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
}
#define PI (2*atan(1.0))
void    F_WCS_MAKEPAIR(vector< vector<afwdetect::SourceMatch> > const &matchlist,CL_APROP *APROP,CL_CPROP* CPROP,CL_PAIR* PAIR){
    int CID,NUM,ALLNUM;
ofstream PAIRout("supa_cfhqs/PAIR.dat");//temp

    ALLNUM=0;
    for(CID=0;CID<APROP->CCDNUM;CID++)
    for(NUM=0;NUM<CPROP[CID].NUMREF;NUM++){
        PAIR[ALLNUM].ID    =matchlist[CID][NUM].first->getId();
        PAIR[ALLNUM].CHIPID=CID;
        PAIR[ALLNUM].FLAG  =1;
        afwCoord::Coord::Ptr radec = matchlist[CID][NUM].first->getRaDec();
        PAIR[ALLNUM].RA    = radec->getLongitude(afwCoord::DEGREES);
        PAIR[ALLNUM].DEC   = radec->getLatitude(afwCoord::DEGREES);
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
#undef PI
afwImage::TanWcs::Ptr    F_WCS_MAKERESULTWCS(CL_CSIP *CSIP){
    int i,j;

    afwGeom::Point2D crpix = afwGeom::Point2D(CSIP->CRPIX[0], CSIP->CRPIX[1]);
    afwGeom::Point2D crval = afwGeom::Point2D(CSIP->CRVAL[0], CSIP->CRVAL[1]);

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
void    F_WCS_SETCC_PRECSIPfromFILE(CL_APROP APROP, char *SSFILE, char *DSIPFILE,CL_CSIP *CSIP){
    int XY,X,Y;
    double A,**DSIP[2];

    DSIP[0] = new double*[APROP.PREDICT_SIP_D_ORDER+1];
    DSIP[1] = new double*[APROP.PREDICT_SIP_D_ORDER+1];
    for(X=0;X<APROP.PREDICT_SIP_D_ORDER+1;X++){
        DSIP[0][X] = new double[APROP.PREDICT_SIP_D_ORDER+1];
        DSIP[1][X] = new double[APROP.PREDICT_SIP_D_ORDER+1];
        for(Y=0;Y<APROP.PREDICT_SIP_D_ORDER+1;Y++)
        DSIP[0][X][Y]=DSIP[1][X][Y]=0;
    }
//-----
    CSIP->PREDICT_SIP_ABD_ORDER=APROP.PREDICT_SIP_D_ORDER;

    ifstream finS,finD;

    finS.open(SSFILE);
    finD.open(DSIPFILE);
    if(!finS||!finD){
        cout << "Warning : Can't read " << SSFILE << " or " << DSIPFILE << endl;        
        CSIP->PREDICT_SIP_ABD_ORDER=9;
        F_WCS_SETDEFAULTDISTORTION(CSIP);
        CSIP->PREDICT_InvSS[0][0]= CSIP->PREDICT_SS[1][1]/(CSIP->PREDICT_SS[0][0]*CSIP->PREDICT_SS[1][1]-CSIP->PREDICT_SS[1][0]*CSIP->PREDICT_SS[0][1]);
        CSIP->PREDICT_InvSS[0][1]=-CSIP->PREDICT_SS[0][1]/(CSIP->PREDICT_SS[0][0]*CSIP->PREDICT_SS[1][1]-CSIP->PREDICT_SS[1][0]*CSIP->PREDICT_SS[0][1]);
        CSIP->PREDICT_InvSS[1][0]=-CSIP->PREDICT_SS[1][0]/(CSIP->PREDICT_SS[0][0]*CSIP->PREDICT_SS[1][1]-CSIP->PREDICT_SS[1][0]*CSIP->PREDICT_SS[0][1]);
        CSIP->PREDICT_InvSS[1][1]= CSIP->PREDICT_SS[0][0]/(CSIP->PREDICT_SS[0][0]*CSIP->PREDICT_SS[1][1]-CSIP->PREDICT_SS[1][0]*CSIP->PREDICT_SS[0][1]);
        cout << "          SET PREDICT_DIP_D_ORDER : " << CSIP->PREDICT_SIP_ABD_ORDER << endl;
        cout << "          USING DEFAULT VALUES FOR PREDICT DISTORTION " << endl;
    }else{
        while((finS >> CSIP->PREDICT_SS[0][0] >> CSIP->PREDICT_SS[0][1] >> CSIP->PREDICT_SS[1][0] >> CSIP->PREDICT_SS[1][1] ) != 0){
        CSIP->PREDICT_InvSS[0][0]= CSIP->PREDICT_SS[1][1]/(CSIP->PREDICT_SS[0][0]*CSIP->PREDICT_SS[1][1]-CSIP->PREDICT_SS[1][0]*CSIP->PREDICT_SS[0][1]);
        CSIP->PREDICT_InvSS[0][1]=-CSIP->PREDICT_SS[0][1]/(CSIP->PREDICT_SS[0][0]*CSIP->PREDICT_SS[1][1]-CSIP->PREDICT_SS[1][0]*CSIP->PREDICT_SS[0][1]);
        CSIP->PREDICT_InvSS[1][0]=-CSIP->PREDICT_SS[1][0]/(CSIP->PREDICT_SS[0][0]*CSIP->PREDICT_SS[1][1]-CSIP->PREDICT_SS[1][0]*CSIP->PREDICT_SS[0][1]);
        CSIP->PREDICT_InvSS[1][1]= CSIP->PREDICT_SS[0][0]/(CSIP->PREDICT_SS[0][0]*CSIP->PREDICT_SS[1][1]-CSIP->PREDICT_SS[1][0]*CSIP->PREDICT_SS[0][1]);
        }

        while((finD >> XY >> X >> Y >> A) != 0)
        if(X+Y<CSIP->PREDICT_SIP_ABD_ORDER+1)
        DSIP[XY][X][Y]=A;

        XY=0;
        for(X=0;X<CSIP->PREDICT_SIP_ABD_ORDER+1;X++)
        for(Y=0;Y<CSIP->PREDICT_SIP_ABD_ORDER+1;Y++)
        if(X + Y <CSIP->PREDICT_SIP_ABD_ORDER+1){
            CSIP->PREDICT_SIP_ABD[0][XY]=DSIP[0][X][Y];
            CSIP->PREDICT_SIP_ABD[1][XY]=DSIP[1][X][Y];
            XY++;
        }
    }

    cout << "PREDICT SS" << endl;
    cout << CSIP->PREDICT_SS[0][0] << "	" << CSIP->PREDICT_SS[0][1] << endl;
    cout << CSIP->PREDICT_SS[1][0] << "	" << CSIP->PREDICT_SS[1][1] << endl;
//-----
    for(XY=0;XY<APROP.PREDICT_SIP_D_ORDER+1;XY++){
        delete [] DSIP[0][XY];
        delete [] DSIP[1][XY];
    }
    delete [] DSIP[0];
    delete [] DSIP[1];
}
void    F_WCS_SETDEFAULTDISTORTION(CL_CSIP *CSIP){
    CSIP->PREDICT_SS[0][0]=-0.000047;
    CSIP->PREDICT_SS[0][1]= 0.000000;
    CSIP->PREDICT_SS[1][0]= 0.000000;
    CSIP->PREDICT_SS[1][1]= 0.000047;

    CSIP->PREDICT_SIP_ABD[0][ 0]=0;
    CSIP->PREDICT_SIP_ABD[0][ 1]=0;
    CSIP->PREDICT_SIP_ABD[0][ 2]=0;
    CSIP->PREDICT_SIP_ABD[0][ 3]=0;
    CSIP->PREDICT_SIP_ABD[0][ 4]=0;
    CSIP->PREDICT_SIP_ABD[0][ 5]=0;
    CSIP->PREDICT_SIP_ABD[0][ 6]=0;
    CSIP->PREDICT_SIP_ABD[0][ 7]=0;
    CSIP->PREDICT_SIP_ABD[0][ 8]=0;
    CSIP->PREDICT_SIP_ABD[0][ 9]=0;
    CSIP->PREDICT_SIP_ABD[0][10]=0;
    CSIP->PREDICT_SIP_ABD[0][11]=0;
    CSIP->PREDICT_SIP_ABD[0][12]=1.030000e-10;
    CSIP->PREDICT_SIP_ABD[0][13]=0;
    CSIP->PREDICT_SIP_ABD[0][14]=7.750000e-20;
    CSIP->PREDICT_SIP_ABD[0][15]=0;
    CSIP->PREDICT_SIP_ABD[0][16]=-7.300000e-29;
    CSIP->PREDICT_SIP_ABD[0][17]=0;
    CSIP->PREDICT_SIP_ABD[0][18]=0;
    CSIP->PREDICT_SIP_ABD[0][19]=0;
    CSIP->PREDICT_SIP_ABD[0][20]=0;
    CSIP->PREDICT_SIP_ABD[0][21]=0;
    CSIP->PREDICT_SIP_ABD[0][22]=0;
    CSIP->PREDICT_SIP_ABD[0][23]=0;
    CSIP->PREDICT_SIP_ABD[0][24]=0;
    CSIP->PREDICT_SIP_ABD[0][25]=0;
    CSIP->PREDICT_SIP_ABD[0][26]=0;
    CSIP->PREDICT_SIP_ABD[0][27]=1.030000e-10;
    CSIP->PREDICT_SIP_ABD[0][28]=0;
    CSIP->PREDICT_SIP_ABD[0][29]=1.550000e-19;
    CSIP->PREDICT_SIP_ABD[0][30]=0;
    CSIP->PREDICT_SIP_ABD[0][31]=-2.190000e-28;
    CSIP->PREDICT_SIP_ABD[0][32]=0;
    CSIP->PREDICT_SIP_ABD[0][33]=0;
    CSIP->PREDICT_SIP_ABD[0][34]=0;
    CSIP->PREDICT_SIP_ABD[0][35]=0;
    CSIP->PREDICT_SIP_ABD[0][36]=0;
    CSIP->PREDICT_SIP_ABD[0][37]=0;
    CSIP->PREDICT_SIP_ABD[0][38]=0;
    CSIP->PREDICT_SIP_ABD[0][39]=0;
    CSIP->PREDICT_SIP_ABD[0][40]=7.750000e-20;
    CSIP->PREDICT_SIP_ABD[0][41]=0;
    CSIP->PREDICT_SIP_ABD[0][42]=-2.190000e-28;
    CSIP->PREDICT_SIP_ABD[0][43]=0;
    CSIP->PREDICT_SIP_ABD[0][44]=0;
    CSIP->PREDICT_SIP_ABD[0][45]=0;
    CSIP->PREDICT_SIP_ABD[0][46]=0;
    CSIP->PREDICT_SIP_ABD[0][47]=0;
    CSIP->PREDICT_SIP_ABD[0][48]=0;
    CSIP->PREDICT_SIP_ABD[0][49]=-7.300000e-29;
    CSIP->PREDICT_SIP_ABD[0][50]=0;
    CSIP->PREDICT_SIP_ABD[0][51]=0;
    CSIP->PREDICT_SIP_ABD[0][52]=0;
    CSIP->PREDICT_SIP_ABD[0][53]=0;
    CSIP->PREDICT_SIP_ABD[0][54]=0;

    CSIP->PREDICT_SIP_ABD[0][ 0]=0;
    CSIP->PREDICT_SIP_ABD[0][ 1]=0;
    CSIP->PREDICT_SIP_ABD[0][ 2]=0;
    CSIP->PREDICT_SIP_ABD[0][ 3]=-1.030000e-10;
    CSIP->PREDICT_SIP_ABD[0][ 4]=0;
    CSIP->PREDICT_SIP_ABD[0][ 5]=-7.750000e-20;
    CSIP->PREDICT_SIP_ABD[0][ 6]=0;
    CSIP->PREDICT_SIP_ABD[0][ 7]=7.300000e-29;
    CSIP->PREDICT_SIP_ABD[0][ 8]=0;
    CSIP->PREDICT_SIP_ABD[0][ 9]=0;
    CSIP->PREDICT_SIP_ABD[0][10]=0;
    CSIP->PREDICT_SIP_ABD[0][11]=0;
    CSIP->PREDICT_SIP_ABD[0][12]=0;
    CSIP->PREDICT_SIP_ABD[0][13]=0;
    CSIP->PREDICT_SIP_ABD[0][14]=0;
    CSIP->PREDICT_SIP_ABD[0][15]=0;
    CSIP->PREDICT_SIP_ABD[0][16]=0;
    CSIP->PREDICT_SIP_ABD[0][17]=0;
    CSIP->PREDICT_SIP_ABD[0][18]=0;
    CSIP->PREDICT_SIP_ABD[0][19]=0;
    CSIP->PREDICT_SIP_ABD[0][20]=-1.030000e-10;
    CSIP->PREDICT_SIP_ABD[0][21]=0;
    CSIP->PREDICT_SIP_ABD[0][22]=-1.550000e-19;
    CSIP->PREDICT_SIP_ABD[0][23]=0;
    CSIP->PREDICT_SIP_ABD[0][24]=2.190000e-28;
    CSIP->PREDICT_SIP_ABD[0][25]=0;
    CSIP->PREDICT_SIP_ABD[0][26]=0;
    CSIP->PREDICT_SIP_ABD[0][27]=0;
    CSIP->PREDICT_SIP_ABD[0][28]=0;
    CSIP->PREDICT_SIP_ABD[0][29]=0;
    CSIP->PREDICT_SIP_ABD[0][30]=0;
    CSIP->PREDICT_SIP_ABD[0][31]=0;
    CSIP->PREDICT_SIP_ABD[0][32]=0;
    CSIP->PREDICT_SIP_ABD[0][33]=0;
    CSIP->PREDICT_SIP_ABD[0][34]=0;
    CSIP->PREDICT_SIP_ABD[0][35]=-7.750000e-20;
    CSIP->PREDICT_SIP_ABD[0][36]=0;
    CSIP->PREDICT_SIP_ABD[0][37]=2.190000e-28;
    CSIP->PREDICT_SIP_ABD[0][38]=0;
    CSIP->PREDICT_SIP_ABD[0][39]=0;
    CSIP->PREDICT_SIP_ABD[0][40]=0;
    CSIP->PREDICT_SIP_ABD[0][41]=0;
    CSIP->PREDICT_SIP_ABD[0][42]=0;
    CSIP->PREDICT_SIP_ABD[0][43]=0;
    CSIP->PREDICT_SIP_ABD[0][44]=0;
    CSIP->PREDICT_SIP_ABD[0][45]=0;
    CSIP->PREDICT_SIP_ABD[0][46]=7.300000e-29;
    CSIP->PREDICT_SIP_ABD[0][47]=0;
    CSIP->PREDICT_SIP_ABD[0][48]=0;
    CSIP->PREDICT_SIP_ABD[0][49]=0;
    CSIP->PREDICT_SIP_ABD[0][50]=0;
    CSIP->PREDICT_SIP_ABD[0][51]=0;
    CSIP->PREDICT_SIP_ABD[0][52]=0;
    CSIP->PREDICT_SIP_ABD[0][53]=0;
    CSIP->PREDICT_SIP_ABD[0][54]=0;
}
dafbase::PropertySet::Ptr F_WCS_EMPTYMETADATA(){
    dafbase::PropertySet::Ptr metadata(new dafbase::PropertySet);

    return metadata;
}
CL_CPROP* F_WCS_EMPTYCPROP(){
    CL_CPROP *CPROPout;

    CPROPout = new CL_CPROP;
    return CPROPout;
}
CL_CSIP*  F_WCS_EMPTYCSIP(){
    CL_CSIP *CSIPout;

    CSIPout = new CL_CSIP;
    return CSIPout;
}
CL_PAIR* F_WCS_EMPTYPAIR(){
    CL_PAIR *PAIRout;

    PAIRout = new CL_PAIR;
    return PAIRout;
}
