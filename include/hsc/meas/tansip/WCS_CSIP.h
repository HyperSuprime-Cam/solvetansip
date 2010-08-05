//------------------------------------------------------------
//WCS_CSIP.h
//
//Last modification : 2010/07/23
//------------------------------------------------------------
class CL_CSIP{
private:
public:
    int ID;
    int FITNUM;
    double CRVAL[2];
    double CRPIX[2];
    double CD[2][2];
    int SIP_AB_ORDER;
    double *SIP_AB[2];
    double SIP_AB_DISP[2];
    int SIP_ABP_ORDER;
    double *SIP_ABP[2];
    double SIP_ABP_DISP[2];
};
