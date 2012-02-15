//------------------------------------------------------------
//WCS_APROP.h
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#ifndef WCS_APROP_H
#define WCS_APROP_H

class CL_APROP{//Analysis property
private:
public:
    char CRPIXMODE[11];//AUTO or PIX or VAL or LAXIS
    char OAMODE[11];//MIN or REV
    int  CCDPOSMODE;
    int  CCDNUM;//CSIP has same parameter
    int  ALLREFNUM;
    int  ALLFITNUM;
    int  *REFNUM;
    int  *FITNUM;
    int  SIP_L_ORDER;//CSIP has same parameter 
    int  SIP_ORDER;//CSIP has same parameter
    int  SIP_P_ORDER;//CSIP has same parameter
    double CLIP_SIGMA;
    double CRPIX[2];//for Manual MODE
    double CRVAL[2];//for Manual MODE
    double BASISPOS[3];
    int STDOUT;
    int CHECKPARAM;

    void F_WCSA_APROP_SHOWAPROP();
    void F_WCSA_APROP_CHECKCRPIXMODE();
    void F_WCSA_APROP_CHECKCCDPOSMODE();
    void F_WCSA_APROP_CHECKSIPORDER();
    void F_WCSA_APROP_CHECKPSIPORDER();
    void F_WCSA_APROP_CHECKLSIPORDER();
    void F_WCSA_APROP_CHECKFITNUM();
    void F_WCSA_APROP_CHECKCCDFITNUM();
};

#endif
