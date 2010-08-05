//------------------------------------------------------------
//WCS_APROP.h
//
//Last modification : 2010/07/22
//------------------------------------------------------------
#include<string>

class CL_APROP{//Analysis property
private:
public:
    std::string CRPIXMODE;//AUTO or MANUAL	
    int  CCDNUM;
    int  refNUM;
    int  SIP_ORDER;
    int  SIP_P_ORDER;
    int  CHECKFILE;
    double CRPIX[2];//for Manual MODE
    double CLIP_SIGMA;
};


