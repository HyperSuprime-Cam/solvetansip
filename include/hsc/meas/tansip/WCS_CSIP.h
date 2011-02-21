//------------------------------------------------------------
//WCS_CSIP.h
//
//Last modification : 2010/07/23
//------------------------------------------------------------
#ifndef WCS_CSIP_H
#define WCS_CSIP_H
class CL_CSIP{
private:
public:
    int ID;
    int FITNUM;
    double CRVAL[2];
    double CRPIX[2];
    double CD[2][2];
    int SIP_ABL_ORDER;
    int SIP_AB_ORDER;
    double *SIP_AB[2];
    double SIP_AB_AVE[2];//difference between SIPxy and xy from refference RADEC
    double SIP_AB_RMS[2];//1sigma of difference between SIPxy and xy from refference RADEC
    //double SIP_AB_DISP[2];//1sigma of difference between SIPxy and xy from refference RADEC
    int SIP_ABP_ORDER;
    double *SIP_ABP[2];
//    double SIP_ABP_AVE[2];
  //  double SIP_ABP_SIGMA[2];
    //double SIP_ABP_DISP[2];
};
#endif
