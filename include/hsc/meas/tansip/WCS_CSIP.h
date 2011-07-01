//------------------------------------------------------------
//WCS_CSIP.h
//
//Last modification : 2011/04/04
//------------------------------------------------------------
#ifndef WCS_CSIP_H
#define WCS_CSIP_H
class CL_CSIP{//CHIP PROPERTY
private:
public:
    int ID;
    int REFNUM;
    int FITNUM;
    double OAVAL[2];
    double OAPIX[2];
    double CRVAL[2];
    double CRPIX[2];
    double CD[2][2];
    double InvCD[2][2];
    int SIP_ABL_ORDER;
    int SIP_AB_ORDER;
    double *SIP_AB[2];
    double SIP_AB_GErr[2][2];//difference between SIPxy and xy from refference RADEC
    double SIP_AB_LErr[2][2];//difference between SIPxy and xy from refference RADEC
    int SIP_ABP_ORDER;
    double *SIP_ABP[2];
    double SIP_ABP_GErr[2][2];//difference between SIPxy and xy from refference RADEC
    double SIP_ABP_LErr[2][2];//difference between SIPxy and xy from refference RADEC
    double ANGLE;
//for CALC
    double *TCoef[2];
    double *TPCoef[2];
    double *TLCoef[2];
//for check
    double *SIP_MAG;
    double *SIP_SHEAR[2];
    double *SIP_ROT;
    double *PSIP_MAG;
    double *PSIP_SHEAR[2];
    double *PSIP_ROT;
};
#endif
