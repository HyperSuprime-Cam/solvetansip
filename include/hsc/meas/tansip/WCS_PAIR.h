//------------------------------------------------------------
//WCS_PAIR.h
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#ifndef WCS_PAIR_H
#define WCS_PAIR_H
class CL_PAIR{
private:
public:
    int ID;
    int CHIPID;
    int FLAG;
    double X_LOCAL[2];
    double X_RADEC[2];
    double X_LOCALERR[2];
    double X_RADECERR[2];

    double X_GLOBAL[2];
    double X_IM_PIXEL[2];
    double X_IM_WORLD[2];
    double X_CRPIX[2];

    double X_CENTER_GLOBAL[2];
    double X_CENTER_IM_PIXEL[2];
    double X_CENTER_IM_WORLD[2];
    double X_CENTER_RADEC[2];
    double CAMERA_MAGROT[2];//Magnification by camera, calculated in only CCD determination mode
    double CAMERA_SHEAR[2];//Shear by camera
    double dxLdxI;//Diferential value of xL by xCRPIX
    double dxLdyI;
    double dyLdxI;
    double dyLdyI;
    double dxGdxI;//Diferential value of xG by xCRPIX
    double dxGdyI;
    double dyGdxI;
    double dyGdyI;
    double Zxx;//Fitting value of SIP dxGdxI 
    double Zyx;
    double Zxy;
    double Zyy;
};
class CL_APAIR{
private:
public:
    CL_PAIR *PAIR;
    char CRPIXMODE[11];//AUTO or PIX or VAL or LAXIS
    char OAMODE[11];//MIN or REV
    int CCDPOSMODE;
    int CCDNUM;
    int ALLREFNUM;
    int ALLFITNUM;
    int REJNUM;
    int SIP_ORDER;
    int SIP_P_ORDER;
    int SIP_L_ORDER;
    int IterNUM_XY;
    int IterNUM_T;
    int STDOUT;
    double **GPOS;
    double GPOS_AVE[3];
    double CLIP_SIGMA;
    double CENTER_PIXEL[2];
    double CENTER_RADEC[2];
    double OAVAL[2];
    double OAPIX[2];
    double CRVAL[2];
    double CRPIX[2];
    double CD[2][2];
    double InvCD[2][2];
    double ANGLE;
    double AVERMS[2][2];
    double  SIPRMS[2][2];
    double PSIPRMS[2][2];
    double *TCoef[2];
    double *TdCoef[2][2];
    double *TPCoef[2];
    double *TdPCoef[2][2];
    double **TLCoef[2];
    double **TdLCoef[2][2];
    double *TSIP_AB[2];
    double *TSIP_ABP[2];

//MAIN
    void F_WCSA_APAIR_GPOS();
    void F_WCSA_APAIR_REJECTION();
    void F_WCSA_APAIR_WCS();
//X
    void F_WCSA_APAIR_SETX();
    void F_WCSA_APAIR_SETXG();
    void F_WCSA_APAIR_SETCRPIX();
    void F_WCSA_APAIR_SETIM();
    void F_WCSA_APAIR_PROJECTION();
    void F_WCSA_APAIR_CENTERPROJECTION();
    void F_WCSA_APAIR_CENTERofOBJECTS();
    void F_WCSA_APAIR_CALCCR();
    void F_WCSA_APAIR_CALCCRVAL();
    void F_WCSA_APAIR_CALCCRPIX();

//FITTING
    void F_WCSA_APAIR_GFITTING(int,int,int);//(ORDER,VALUE,FUNCTION), ORDER=(SIP_ORDER,SIP_P_ORDER,SIP_ORDER-1,SIP_L_ORDER)
    void F_WCSA_APAIR_LFITTING(int, int);//(FUNCTION), 
    void F_WCSA_APAIR_CALCRMS(int,int,int);//(ORDER,VALUE,FUNCTION), ORDER=(SIP_ORDER,SIP_P_ORDER,SIP_ORDER-1,SIP_L_ORDER)
    void F_WCSA_APAIR_SETSIP();
    void F_WCSA_APAIR_SETPSIP();
    void F_WCSA_APAIR_CALCSIPRMS();//(ORDER,VALUE,FUNCTION), ORDER=(SIP_ORDER,SIP_P_ORDER,SIP_ORDER-1,SIP_L_ORDER)
    void F_WCSA_APAIR_FITSIP();
    void F_WCSA_APAIR_FITPSIP();
    void F_WCSA_APAIR_CALCPSIPRMS();//(ORDER,VALUE,FUNCTION), ORDER=(SIP_ORDER,SIP_P_ORDER,SIP_ORDER-1,SIP_L_ORDER)
    void F_WCSA_APAIR_CALCMAGROTSHEAR();
    void F_WCSA_APAIR_CALCMAGROTSHEARfromTCoef();
    void F_WCSA_APAIR_LDIFFVALUES();
    void F_WCSA_APAIR_GDIFFVALUES();
    void F_WCSA_APAIR_CCDPOSITIONS_T();
    void F_WCSA_APAIR_CCDPOSITIONS_T_MAT();
    void F_WCSA_APAIR_CCDPOSITIONS_T_SETAVERAGE();
    void F_WCSA_APAIR_CCDPOSITIONS_XY();
    void F_WCSA_APAIR_CCDPOSITIONS_XY_SETAVERAGE();
//ETC
    void F_WCSA_APAIR_SET0();
    void F_WCSA_APAIR_SHOWAPAIR();
};
#endif
