//------------------------------------------------------------
//WCS_APROP.h
//
//Last modification : 2011/02/22
//------------------------------------------------------------
#ifndef WCS_APROP_H
#define WCS_APROP_H
#include<string>

class CL_APROP{//Analysis property
private:
public:
//    std::string CRPIXMODE;//AUTO or MANUAL	
    char CRPIXMODE[11];//AUTO or MANUAL	
    int  CCDPOSMODE;
    int  CCDNUM;
    int  NUMREFALL;
    int  SIP_L_ORDER;
    int  SIP_ORDER;
    int  SIP_P_ORDER;
    int  CHECKFILE;
    double CRPIX[2];//for Manual MODE
    double CLIP_SIGMA;
};

#endif
