//------------------------------------------------------------
//WCS_PL_MAIN.cc
//main program for wcs in pipeline
//
//Last modification : 2011/02/22
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
namespace camGeom = lsst::afw::cameraGeom;

void    F_WCS_MAKEAPROP(lsst::pex::policy::Policy::Ptr &,CL_APROP*);
void    F_WCS_MAKECPROP(lsst::afw::cameraGeom::Camera::Ptr &,vector< vector< afwdetect::SourceMatch  >  > const &, CL_APROP*, CL_CPROP *);
void    F_WCS_SETCC_PRECSIPfromFILE(CL_APROP, char *,CL_CSIP *);
void    F_WCS_MAKEPAIR(vector< vector< afwdetect::SourceMatch  >  > const &, CL_APROP *, CL_CPROP *,CL_PAIR *);
afwImage::TanWcs::Ptr    F_WCS_MAKERESULTWCS(CL_CSIP *);
vector<afwImage::TanWcs::Ptr>    F_WCS_TANSIP_V(vector< vector<afwdetect::SourceMatch> > const &matchlist,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera/*,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose*/){
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
        CSIP[CID].SIP_AB[0]  = new double[APROP.SIP_ORDER*APROP.SIP_ORDER+1];
        CSIP[CID].SIP_AB[1]  = new double[APROP.SIP_ORDER*APROP.SIP_ORDER+1];
        CSIP[CID].SIP_ABP[0] = new double[APROP.SIP_P_ORDER*APROP.SIP_P_ORDER+1];
        CSIP[CID].SIP_ABP[1] = new double[APROP.SIP_P_ORDER*APROP.SIP_P_ORDER+1];
    }
    CSIP[APROP.CCDNUM].PREDICT_SIP_ABP[0] = new double[(APROP.PREDICT_SIP_P_ORDER+2)*(APROP.PREDICT_SIP_P_ORDER+1)];
    CSIP[APROP.CCDNUM].PREDICT_SIP_ABP[1] = new double[(APROP.PREDICT_SIP_P_ORDER+2)*(APROP.PREDICT_SIP_P_ORDER+1)];

//PREDICT CSIP
    char PRECSIPFILE[100];
    sprintf(PRECSIPFILE,"../policy/WCS_CSIP_PREDICT.paf");
    F_WCS_SETCC_PRECSIPfromFILE(APROP, PRECSIPFILE, &CSIP[APROP.CCDNUM]);
//------------------------------------------------------
    cout << "--- WCS_PL_MAIN : F_WCS_TANSIP ---" << endl;
    F_WCS_TANSIP(APROP,CPROP,PAIR,CSIP);

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

//------------------------------------------------------
    delete [] CPROP;
    delete [] PAIR;
    for(CID=0;CID<APROP.CCDNUM+1;CID++){
    delete [] CSIP[CID].SIP_AB[0];
    delete [] CSIP[CID].SIP_AB[1];
    delete [] CSIP[CID].SIP_ABP[0];
    delete [] CSIP[CID].SIP_ABP[1];
    }
    delete [] CSIP[APROP.CCDNUM].PREDICT_SIP_ABP[0];
    delete [] CSIP[APROP.CCDNUM].PREDICT_SIP_ABP[1];
    delete [] CSIP;
//------------------------------------------------------
    cout << "--- F_WCS_PL_MAIN : ZZZ ---" << endl;
    return resultWcs_V;
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
    APROP->SIP_L_ORDER =APROPPolicy->getInt("LSIPORDER");
    APROP->SIP_ORDER   =APROPPolicy->getInt("SIPORDER");
    APROP->SIP_P_ORDER =APROPPolicy->getInt("PSIPORDER");
    APROP->PREDICT_SIP_P_ORDER =APROPPolicy->getInt("PREORDER");
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
        cout << "ERROR : Can't read " << CPROPIDFILE << endl;
        return;
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
        PAIR[ALLNUM].RA    =matchlist[CID][NUM].first->getRa();
        PAIR[ALLNUM].DEC   =matchlist[CID][NUM].first->getDec();
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

    afwGeom::PointD crpix = afwGeom::makePointD(CSIP->CRPIX[0], CSIP->CRPIX[1]);
    afwGeom::PointD crval = afwGeom::makePointD(CSIP->CRVAL[0], CSIP->CRVAL[1]);

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
void    F_WCS_SETCC_PRECSIPfromFILE(CL_APROP APROP, char *CSIPFILE,CL_CSIP *CSIP){
    int XY,X,Y;
    double A,**SIP[2];

    SIP[0] = new double*[APROP.PREDICT_SIP_P_ORDER+1];
    SIP[1] = new double*[APROP.PREDICT_SIP_P_ORDER+1];
    for(XY=0;XY<APROP.PREDICT_SIP_P_ORDER+1;XY++){
        SIP[0][XY] = new double[APROP.PREDICT_SIP_P_ORDER+1];
        SIP[1][XY] = new double[APROP.PREDICT_SIP_P_ORDER+1];
    }
//-----
    CSIP->PREDICT_SIP_P_ORDER=APROP.PREDICT_SIP_P_ORDER;

    ifstream fin;

    fin.open(CSIPFILE);
    while((fin >> XY >> X >> Y >> A) != 0)
    SIP[XY][X][Y]=A;

    XY=0;
    for(X=0;X<CSIP->PREDICT_SIP_P_ORDER+1;X++)
    for(Y=0;Y<CSIP->PREDICT_SIP_P_ORDER+1;Y++)
    if(X+Y<CSIP->PREDICT_SIP_P_ORDER+1){
        CSIP->PREDICT_SIP_ABP[0][XY]=SIP[0][X][Y];
        CSIP->PREDICT_SIP_ABP[1][XY]=SIP[1][X][Y];
        XY++;
    }
    
//-----
    for(XY=0;XY<APROP.PREDICT_SIP_P_ORDER+1;XY++){
        delete [] SIP[0][XY];
        delete [] SIP[1][XY];
    }
    delete [] SIP[0];
    delete [] SIP[1];
}

