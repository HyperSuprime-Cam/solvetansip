//------------------------------------------------------------
//WCS_TANSIP.cc
//called in Pipeline
//
//Last modification : 2010/08/03
//------------------------------------------------------------
#include<iostream>//temp?
#include<fstream>//temp?
#include<cstring>//temp?
#include<iomanip>//temp
#include<vector>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
namespace afwdetect = lsst::afw::detection;
namespace afwImage = lsst::afw::image;
namespace afwGeom = lsst::afw::geom; 
namespace camGeom = lsst::afw::cameraGeom;
void    F_MAKEAPROP(lsst::pex::policy::Policy::Ptr &,CL_APROP*);
void    F_MAKECPROP(lsst::afw::cameraGeom::Camera::Ptr &,vector< vector<afwdetect::SourceMatch> > const &,CL_APROP*,CL_CPROP*);
void    F_MAKEPAIR(vector< vector<afwdetect::SourceMatch> > const &,CL_APROP*,CL_CPROP*,CL_PAIR*);
void    F_WCS_FIT(CL_APROP ,CL_PAIR *,CL_CSIP *);
void    F_WSC_eachCHIP(CL_APROP,CL_CPROP*, CL_PAIR,CL_CSIP*);
afwImage::TanWcs::Ptr    F_CLWCSfromCSIP(CL_CSIP *);

void    F_WCS_TANSIP_TEST(vector<afwImage::TanWcs::Ptr> resultWcs_V){//check
cout << "--- F_WCS_TANSIP_TEST ---" << endl;
cout << "--- F_WCS_TANSIP_TEST:CCD000 ---" << endl;
cout << resultWcs_V[0] << endl;
cout << (resultWcs_V[0]->getFitsMetadata())->toString() << endl;
cout << "--- F_WCS_TANSIP_TEST:CCD010 = global ---" << endl;
cout << resultWcs_V[10] << endl;
cout << (resultWcs_V[10]->getFitsMetadata())->toString() << endl;
}//check
vector<afwImage::TanWcs::Ptr>    F_WCS_TANSIP_V(vector< vector<afwdetect::SourceMatch> > const &matchlist,lsst::pex::policy::Policy::Ptr &APROPPolicy,lsst::afw::cameraGeom::Camera::Ptr &camera,lsst::daf::base::PropertySet::Ptr &metadata,bool verbose){
    int CID;
    CL_APROP  APROP;
    CL_CPROP *CPROP;
    CL_PAIR   PAIR;
    CL_CSIP  *CSIP;

//APROP--------------------------------------------------
cout << "--- F_WCS_TANSIP:APROP ---" << endl;// check
    F_MAKEAPROP(APROPPolicy,&APROP);
cout << "CRPIXMODE   : " << APROP.CRPIXMODE << endl;// check
cout << "CRPIX1      : " << APROP.CRPIX[0] << endl;// check
cout << "CRPIX2      : " << APROP.CRPIX[1] << endl;// check
cout << "SIP_ORDER   : " << APROP.SIP_ORDER << endl;// check
cout << "SIP_P_ORDER : " << APROP.SIP_P_ORDER << endl;// check
cout << "CLIP_SIGMA  : " << APROP.CLIP_SIGMA << endl;// check
cout << "CHECKFILE   : " << APROP.CHECKFILE << endl;// check
cout << "CCDNUM      : " << APROP.CCDNUM << endl;// check

//CPROP--------------------------------------------------
    CPROP = new CL_CPROP[APROP.CCDNUM];
    F_MAKECPROP(camera,matchlist,&APROP,CPROP);
cout << "refNUM      : " << APROP.refNUM << endl;// check
cout << "--- F_WCS_TANSIP:CPROP ---" << endl;// check
cout << "--- F_WCS_TANSIP:CPROP:CCD" << setw(3) << setfill('0') << CPROP[0].ID <<" ---" << endl;// check
cout << "ID          : " << CPROP[0].ID << endl;// check
cout << "NUM         : " << CPROP[0].NUM << endl;// check
cout << "GLOBAL POS X: " << CPROP[0].GLOB_POS[0] << endl;// check
cout << "GLOBAL POS Y: " << CPROP[0].GLOB_POS[1] << endl;// check
cout << "GLOBAL POS T: " << CPROP[0].GLOB_POS[2] << endl;// check
cout << "--- F_WCS_TANSIP:CPROP:CCD" << setw(3) << setfill('0') << CPROP[APROP.CCDNUM-1].ID <<" ---" << endl;// check
cout << "ID          : " << CPROP[APROP.CCDNUM-1].ID << endl;// check
cout << "NUM         : " << CPROP[APROP.CCDNUM-1].NUM << endl;// check
cout << "GLOBAL POS X: " << CPROP[APROP.CCDNUM-1].GLOB_POS[0] << endl;// check
cout << "GLOBAL POS Y: " << CPROP[APROP.CCDNUM-1].GLOB_POS[1] << endl;// check
cout << "GLOBAL POS T: " << CPROP[APROP.CCDNUM-1].GLOB_POS[2] << endl;// check

//PIAR--------------------------------------------------
    PAIR.refID = new int[APROP.refNUM];
    PAIR.CHIPID= new int[APROP.refNUM];
    PAIR.FLAG  = new int[APROP.refNUM];
    PAIR.x   = new double[APROP.refNUM];
    PAIR.y   = new double[APROP.refNUM];
    PAIR.RA  = new double[APROP.refNUM];
    PAIR.DEC = new double[APROP.refNUM];
    PAIR.xSIP   = new double[APROP.refNUM];
    PAIR.ySIP   = new double[APROP.refNUM];
    PAIR.RAfit  = new double[APROP.refNUM];
    PAIR.DECfit = new double[APROP.refNUM];
    PAIR.xErr   = new double[APROP.refNUM];
    PAIR.yErr   = new double[APROP.refNUM];
    PAIR.RAErr  = new double[APROP.refNUM];
    PAIR.DECErr = new double[APROP.refNUM];
    F_MAKEPAIR(matchlist,&APROP,CPROP,&PAIR);

cout << "--- F_WCS_TANSIP:PAIR ---" << endl;// check
cout << "output : data/PAIR.dat" << endl;// check

//FIT--------------------------------------------------
    CSIP = new CL_CSIP[APROP.CCDNUM+1];
    for(CID=0;CID<APROP.CCDNUM+1;CID++){
        CSIP[CID].SIP_AB[0]  = new double[APROP.SIP_ORDER*APROP.SIP_ORDER+1];
        CSIP[CID].SIP_AB[1]  = new double[APROP.SIP_ORDER*APROP.SIP_ORDER+1];
        CSIP[CID].SIP_ABP[0] = new double[APROP.SIP_P_ORDER*APROP.SIP_P_ORDER+1];
        CSIP[CID].SIP_ABP[1] = new double[APROP.SIP_P_ORDER*APROP.SIP_P_ORDER+1];
    }
cout << "--- F_WCS_TANSIP:FIT ---" << endl;// check
    F_WCS_FIT(APROP,&PAIR,&CSIP[APROP.CCDNUM]);
    F_WSC_eachCHIP(APROP,CPROP,PAIR,CSIP);
cout << "CRVAL1      : " << CSIP[APROP.CCDNUM].CRVAL[0] << endl;// check
cout << "CRVAL2      : " << CSIP[APROP.CCDNUM].CRVAL[1] << endl;// check
cout << "CD1_1       : " << CSIP[APROP.CCDNUM].CD[0][0] << endl;// check
cout << "CD1_2       : " << CSIP[APROP.CCDNUM].CD[0][1] << endl;// check
cout << "CD2_1       : " << CSIP[APROP.CCDNUM].CD[1][0] << endl;// check
cout << "CD2_2       : " << CSIP[APROP.CCDNUM].CD[1][1] << endl;// check
cout << "A_ORDER     : " << CSIP[APROP.CCDNUM].SIP_AB_ORDER << endl;// check
cout << "B_ORDER     : " << CSIP[APROP.CCDNUM].SIP_AB_ORDER << endl;// check
cout << "A_DISP(deg) : " << CSIP[APROP.CCDNUM].SIP_AB_DISP[0] << endl;// check
cout << "B_DISP(deg) : " << CSIP[APROP.CCDNUM].SIP_AB_DISP[1] << endl;// check
cout << "A_AVE(pix)  : " << CSIP[APROP.CCDNUM].SIP_AB_AVE[0] << endl;// check
cout << "B_AVE(pix)  : " << CSIP[APROP.CCDNUM].SIP_AB_AVE[1] << endl;// check
cout << "A_SIGMA(pix): " << CSIP[APROP.CCDNUM].SIP_AB_SIGMA[0] << endl;// check
cout << "B_SIGMA(pix): " << CSIP[APROP.CCDNUM].SIP_AB_SIGMA[1] << endl;// check
cout << "AP_ORDER    : " << CSIP[APROP.CCDNUM].SIP_ABP_ORDER << endl;// check
cout << "BP_ORDER    : " << CSIP[APROP.CCDNUM].SIP_ABP_ORDER << endl;// check
cout << "AP_DISP     : " << CSIP[APROP.CCDNUM].SIP_ABP_DISP[0] << endl;// check
cout << "BP_DISP     : " << CSIP[APROP.CCDNUM].SIP_ABP_DISP[1] << endl;// check
cout << "A_AVE_0     : " << CSIP[0].SIP_AB_AVE[0] << endl;// check
cout << "B_AVE_0     : " << CSIP[0].SIP_AB_AVE[1] << endl;// check
cout << "A_SIGMA_0   : " << CSIP[0].SIP_AB_SIGMA[0] << endl;// check
cout << "B_SIGMA_0   : " << CSIP[0].SIP_AB_SIGMA[1] << endl;// check
cout << "A_AVE_5     : " << CSIP[5].SIP_AB_AVE[0] << endl;// check
cout << "B_AVE_5     : " << CSIP[5].SIP_AB_AVE[1] << endl;// check
cout << "A_SIGMA_5   : " << CSIP[5].SIP_AB_SIGMA[0] << endl;// check
cout << "B_SIGMA_5   : " << CSIP[5].SIP_AB_SIGMA[1] << endl;// check

//--------------------------------------------------
//check ->
/*cout << "----------------------------------------------------------------------------------------------------" << endl;
int i,j,ij;
    cout << "FITNUM  =" << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].FITNUM << "/" <<endl;
    cout << "CRVAL1  =" << fixed << setfill(' ') << right<< setw(20) << CSIP[APROP.CCDNUM].CRVAL[0] << "/ [deg] RA  at (CRPIX1,CRPIX2)" <<endl;
    cout << "CRVAL2  =" << fixed << setfill(' ') << right<< setw(20) << CSIP[APROP.CCDNUM].CRVAL[1] << "/ [deg] DEC at (CRPIX1,CRPIX2)" <<endl;
    cout << "CRPIX1  =" << fixed << setfill(' ') << right<< setw(20) << CSIP[APROP.CCDNUM].CRPIX[0] << "/ Reference pixel along axis 1" <<endl;
    cout << "CRPIX2  =" << fixed << setfill(' ') << right<< setw(20) << CSIP[APROP.CCDNUM].CRPIX[1] << "/ Reference pixel along axis 2" <<endl;
    cout << scientific ;
    cout << "CD1_1   =" << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].CD[0][0] << "/ CD matrix element" <<endl;
    cout << "CD1_2   =" << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].CD[0][1] << "/ CD matrix element" <<endl;
    cout << "CD2_1   =" << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].CD[1][0] << "/ CD matrix element" <<endl;
    cout << "CD2_2   =" << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].CD[1][1] << "/ CD matrix element" <<endl;
    cout << "A_ORDER =" << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].SIP_AB_ORDER << "/ polynomial order of axis 1, detector to sky" <<endl;
    ij=0;
    for(i=0;i<CSIP[APROP.CCDNUM].SIP_AB_ORDER+1;i++)
    for(j=0;j<CSIP[APROP.CCDNUM].SIP_AB_ORDER+1;j++)
    if(i+j<CSIP[APROP.CCDNUM].SIP_AB_ORDER+1){
        cout << "A_" << i << "_" << j << "   =" << scientific << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].SIP_AB[0][ij] << "/ distortion coefficient (A_" << i << "_" << j << " x^" << i << " y^" << j << ")" <<endl;
        ij+=1;
    }
    cout << "B_ORDER =" << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].SIP_AB_ORDER << "/ polynomial order of axis 2, detector to sky" <<endl;
    ij=0;
    for(i=0;i<CSIP[APROP.CCDNUM].SIP_AB_ORDER+1;i++)
    for(j=0;j<CSIP[APROP.CCDNUM].SIP_AB_ORDER+1;j++)
    if(i+j<CSIP[APROP.CCDNUM].SIP_AB_ORDER+1){
        cout << "B_" << i << "_" << j << "   =" << scientific << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].SIP_AB[1][ij] << "/ distortion coefficient (A_" << i << "_" << j << " x^" << i << " y^" << j << ")" <<endl;
        ij+=1;
    }
    cout << "AP_ORDER=" << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].SIP_ABP_ORDER << "/ polynomial order of axis 1, sky to detector" <<endl;
    ij=0;
    for(i=0;i<CSIP[APROP.CCDNUM].SIP_ABP_ORDER+1;i++)
    for(j=0;j<CSIP[APROP.CCDNUM].SIP_ABP_ORDER+1;j++)
    if(i+j<CSIP[APROP.CCDNUM].SIP_ABP_ORDER+1){
        cout << "AP_" << i << "_" << j << "  =" << scientific << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].SIP_ABP[0][ij] << "/ distortion coefficient (AP_" << i << "_" << j << " x^" << i << " y^" << j << ")" <<endl;
        ij+=1;
    }
    cout << "BP_ORDER=" << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].SIP_ABP_ORDER << "/ polynomial order of axis 2, sky to detector" <<endl;
    ij=0;
    for(i=0;i<CSIP[APROP.CCDNUM].SIP_ABP_ORDER+1;i++)
    for(j=0;j<CSIP[APROP.CCDNUM].SIP_ABP_ORDER+1;j++)
    if(i+j<CSIP[APROP.CCDNUM].SIP_ABP_ORDER+1){
        cout << "BP_" << i << "_" << j << "  =" << scientific << setw(20) << setfill(' ') << right << CSIP[APROP.CCDNUM].SIP_ABP[1][ij] << "/ distortion coefficient (BP_" << i << "_" << j << " x^" << i << " y^" << j << ")" <<endl;
        ij+=1;
    }
cout << "----------------------------------------------------------------------------------------------------" << endl;
//check <-
//check ->
cout << "----------------------------------------------------------------------------------------------------" << endl;

    cout << "FITNUM  =" << setw(20) << setfill(' ') << right << CSIP[5].FITNUM << "/" <<endl;
    cout << "CRVAL1  =" << fixed << setfill(' ') << right<< setw(20) << CSIP[5].CRVAL[0] << "/ [deg] RA  at (CRPIX1,CRPIX2)" <<endl;
    cout << "CRVAL2  =" << fixed << setfill(' ') << right<< setw(20) << CSIP[5].CRVAL[1] << "/ [deg] DEC at (CRPIX1,CRPIX2)" <<endl;
    cout << "CRPIX1  =" << fixed << setfill(' ') << right<< setw(20) << CSIP[5].CRPIX[0] << "/ Reference pixel along axis 1" <<endl;
    cout << "CRPIX2  =" << fixed << setfill(' ') << right<< setw(20) << CSIP[5].CRPIX[1] << "/ Reference pixel along axis 2" <<endl;
    cout << scientific ;
    cout << "CD1_1   =" << setw(20) << setfill(' ') << right << CSIP[5].CD[0][0] << "/ CD matrix element" <<endl;
    cout << "CD1_2   =" << setw(20) << setfill(' ') << right << CSIP[5].CD[0][1] << "/ CD matrix element" <<endl;
    cout << "CD2_1   =" << setw(20) << setfill(' ') << right << CSIP[5].CD[1][0] << "/ CD matrix element" <<endl;
    cout << "CD2_2   =" << setw(20) << setfill(' ') << right << CSIP[5].CD[1][1] << "/ CD matrix element" <<endl;
    cout << "A_ORDER =" << setw(20) << setfill(' ') << right << CSIP[5].SIP_AB_ORDER << "/ polynomial order of axis 1, detector to sky" <<endl;
    ij=0;
    for(i=0;i<CSIP[5].SIP_AB_ORDER+1;i++)
    for(j=0;j<CSIP[5].SIP_AB_ORDER+1;j++)
    if(i+j<CSIP[5].SIP_AB_ORDER+1){
        cout << "A_" << i << "_" << j << "   =" << scientific << setw(20) << setfill(' ') << right << CSIP[5].SIP_AB[0][ij] << "/ distortion coefficient (A_" << i << "_" << j << " x^" << i << " y^" << j << ")" <<endl;
        ij+=1;
    }
    cout << "B_ORDER =" << setw(20) << setfill(' ') << right << CSIP[5].SIP_AB_ORDER << "/ polynomial order of axis 2, detector to sky" <<endl;
    ij=0;
    for(i=0;i<CSIP[5].SIP_AB_ORDER+1;i++)
    for(j=0;j<CSIP[5].SIP_AB_ORDER+1;j++)
    if(i+j<CSIP[5].SIP_AB_ORDER+1){
        cout << "B_" << i << "_" << j << "   =" << scientific << setw(20) << setfill(' ') << right << CSIP[5].SIP_AB[1][ij] << "/ distortion coefficient (A_" << i << "_" << j << " x^" << i << " y^" << j << ")" <<endl;
        ij+=1;
    }
    cout << "AP_ORDER=" << setw(20) << setfill(' ') << right << CSIP[5].SIP_ABP_ORDER << "/ polynomial order of axis 1, sky to detector" <<endl;
    ij=0;
    for(i=0;i<CSIP[5].SIP_ABP_ORDER+1;i++)
    for(j=0;j<CSIP[5].SIP_ABP_ORDER+1;j++)
    if(i+j<CSIP[5].SIP_ABP_ORDER+1){
        cout << "AP_" << i << "_" << j << "  =" << scientific << setw(20) << setfill(' ') << right << CSIP[5].SIP_ABP[0][ij] << "/ distortion coefficient (AP_" << i << "_" << j << " x^" << i << " y^" << j << ")" <<endl;
        ij+=1;
    }
    cout << "BP_ORDER=" << setw(20) << setfill(' ') << right << CSIP[5].SIP_ABP_ORDER << "/ polynomial order of axis 2, sky to detector" <<endl;
    ij=0;
    for(i=0;i<CSIP[5].SIP_ABP_ORDER+1;i++)
    for(j=0;j<CSIP[5].SIP_ABP_ORDER+1;j++)
    if(i+j<CSIP[5].SIP_ABP_ORDER+1){
        cout << "BP_" << i << "_" << j << "  =" << scientific << setw(20) << setfill(' ') << right << CSIP[5].SIP_ABP[1][ij] << "/ distortion coefficient (BP_" << i << "_" << j << " x^" << i << " y^" << j << ")" <<endl;
        ij+=1;
    }
cout << "----------------------------------------------------------------------------------------------------" << endl;
*///check <-
//output format --------------------------------------------------
    afwImage::TanWcs::Ptr resultWcs;
    vector <afwImage::TanWcs::Ptr> resultWcs_V;
    for(CID=0;CID<APROP.CCDNUM+1;CID++){
        resultWcs = F_CLWCSfromCSIP(&CSIP[CID]);
        resultWcs_V.push_back(resultWcs);
    }
//--------------------------------------------------
    delete [] CPROP;
    delete [] PAIR.refID;
    delete [] PAIR.CHIPID;
    delete [] PAIR.FLAG;
    delete [] PAIR.x;
    delete [] PAIR.y;
    delete [] PAIR.RA;
    delete [] PAIR.DEC;
    delete [] PAIR.xSIP;
    delete [] PAIR.ySIP;
    delete [] PAIR.RAfit;
    delete [] PAIR.DECfit;
    delete [] PAIR.xErr;
    delete [] PAIR.yErr;
    delete [] PAIR.RAErr;
    delete [] PAIR.DECErr;
    for(CID=0;CID<APROP.CCDNUM+1;CID++){
        delete [] CSIP[CID].SIP_AB[0];
        delete [] CSIP[CID].SIP_AB[1];
        delete [] CSIP[CID].SIP_ABP[0];
        delete [] CSIP[CID].SIP_ABP[1];
    }
    delete [] CSIP;
    return resultWcs_V;
//    return resultWcs
}
afwImage::TanWcs::Ptr	F_CLWCSfromCSIP(CL_CSIP *CSIP){
    int i,j;

    afwGeom::PointD crpix = afwGeom::makePointD(CSIP->CRPIX[0], CSIP->CRPIX[1]);
    afwGeom::PointD crval = afwGeom::makePointD(CSIP->CRVAL[0], CSIP->CRVAL[1]);

    Eigen::Matrix2d cdMatrix;
    cdMatrix << CSIP->CD[0][0],CSIP->CD[0][1],CSIP->CD[1][0], CSIP->CD[1][1];

    Eigen::MatrixXd sipA  = Eigen::MatrixXd::Zero(CSIP->SIP_AB_ORDER+1 ,CSIP->SIP_AB_ORDER+1);
    Eigen::MatrixXd sipB  = Eigen::MatrixXd::Zero(CSIP->SIP_AB_ORDER+1 ,CSIP->SIP_AB_ORDER+1);
    Eigen::MatrixXd sipAp = Eigen::MatrixXd::Zero(CSIP->SIP_ABP_ORDER+1,CSIP->SIP_ABP_ORDER+1);
    Eigen::MatrixXd sipBp = Eigen::MatrixXd::Zero(CSIP->SIP_ABP_ORDER+1,CSIP->SIP_ABP_ORDER+1);

    int ij=0;
    for(i=0;i<CSIP->SIP_AB_ORDER+1;i++)
    for(j=0;j<CSIP->SIP_AB_ORDER+1;j++)
    if(i+j<CSIP->SIP_AB_ORDER+1) {
        sipA(i,j) = CSIP->SIP_AB[0][ij];
        sipB(i,j) = CSIP->SIP_AB[1][ij];
        ij+=1;
    }else{
        sipA(i,j) = 0.0;
        sipB(i,j) = 0.0;
    }
    ij=0;
    for(i=0;i<CSIP->SIP_ABP_ORDER+1;i++)
    for(j=0;j<CSIP->SIP_ABP_ORDER+1;j++)
    if(i+j<CSIP->SIP_ABP_ORDER+1) {
        sipAp(i,j) = CSIP->SIP_ABP[0][ij];
        sipBp(i,j) = CSIP->SIP_ABP[1][ij];
        ij+=1;
    }else{
        sipAp(i,j) = 0.0;
        sipBp(i,j) = 0.0;
    }

    afwImage::TanWcs::Ptr resultTanWcs(new afwImage::TanWcs(crval, crpix, cdMatrix, sipA, sipB, sipAp, sipBp));
    return resultTanWcs;
}
