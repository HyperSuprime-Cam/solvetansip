//------------------------------------------------------------
//WCS_APROP.h
//
//Last modification : 2011/02/22
//------------------------------------------------------------
#ifndef WCS_APROP_H
#define WCS_APROP_H

class CL_APROP{//Analysis property
private:
public:
    char CRPIXMODE[11];//AUTO or PIX or VAL or LAXIS
    int  CCDPOSMODE;
    int  CCDNUM;
    int  BASISCID;
    int  NUMREFALL;
    int  SIP_L_ORDER;
    int  SIP_ORDER;
    int  SIP_P_ORDER;
    int  ALIGNAXIS;//0=x,1=y
    int  CHECKPARAM;
    double CRPIX[2];//for Manual MODE
    double CRVAL[2];//for Manual MODE
    double CLIP_SIGMA;
    double BASIS_POS[3];
    int STDOUT;
};

#endif
