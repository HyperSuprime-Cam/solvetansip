//------------------------------------------------------------
//WCS_CSIP.h
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#ifndef WCS_CSIP_H
#define WCS_CSIP_H
class CL_CSIP{//CHIP PROPERTY
private:
public:
    int ID;
    int FITNUM;
    int REFNUM;
    double GPOS[3];//CPROP has same parameter

    double OAVAL[2];
    double OAPIX[2];
    double CRVAL[2];
    double CRPIX[2];
    double CD[2][2];
    double InvCD[2][2];
    double *SIP_AB[2];
    double SIP_AB_GERR[2][2];//difference between SIPxy and xy from refference RADEC
    double SIP_AB_LERR[2][2];//difference between SIPxy and xy from refference RADEC
    double *SIP_ABP[2];
    double SIP_ABP_GERR[2][2];//difference between SIPxy and xy from refference RADEC
    double SIP_ABP_LERR[2][2];//difference between SIPxy and xy from refference RADEC
    double ANGLE;
//for CALC
    double *Coef[2];
    double *PCoef[2];
    double *LCoef[2];
//for check
    double *SIP_MAG;
    double *SIP_SHEAR[2];
    double *SIP_ROT;
    double *PSIP_MAG;
    double *PSIP_SHEAR[2];
    double *PSIP_ROT;

    int POSID[2];
/*DEL*/
/*    int ALIGN;
    int PHASE;*/

};
class CL_GSIP{//GLOBAL SIP
private:
public:
    CL_CSIP *CSIP;
    char CRPIXMODE[11];//AUTO or PIX or VAL or LAXIS
    char OAMODE[11];//MIN or REV
    int CCDPOSMODE;
    int CCDNUM;
    int ALLREFNUM;
    int ALLFITNUM;
    int SIP_ORDER;
    int SIP_P_ORDER;
    int SIP_L_ORDER;
    int STDOUT;
    double CLIP_SIGMA;
    double OAVAL[2];
    double OAPIX[2];
    double CRVAL[2];
    double CRPIX[2];
    double CD[2][2];
    double InvCD[2][2];
    double ANGLE;
/*DEL*/
    double *TSIP_AB[2];
    double *TSIP_ABP[2];
    double *TCoef[2];
    double *TPCoef[2];
    double *TLCoef[2];
//MAIN
    void F_WCSA_GSIP_CALCLOCALSIP();
    void F_WCSA_GSIP_LOCALSIP();
    void F_WCSA_GSIP_SETSIP();
    void F_WCSA_GSIP_SETPSIP();

//
    void F_WCSA_GSIP_SET0();
    void F_WCSA_GSIP_SHOWGSIP();
    void F_WCSA_GSIP_SHOWCSIP(int);
    void F_WCSA_GSIP_SHOWGLOBAL();
    void F_WCSA_GSIP_CHECKCCDPOSITION();
    void F_WCSA_GSIP_SETINITIAL();
    void F_WCSA_GSIP_SETDEFAULTPOSITIONS_SC();
    void F_WCSA_GSIP_SETDEFAULTPOSITIONS_HSC();
    void F_WCSA_GSIP_SETDEFAULTPOSITIONS_SCfromPAF();
    void F_WCSA_GSIP_SETDEFAULTPOSITIONS_HSCfromPAF();
    void F_WCSA_GSIP_PIXELtoRADEC(double *PIXEL,double *RADEC);
    void F_WCSA_GSIP_RADECtoPIXEL(double *RADEC,double *PIXEL);
};
#endif
