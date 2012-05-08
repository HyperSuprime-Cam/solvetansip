//------------------------------------------------------------
//WCS_PAIR.h
//
//Last modification : 2011/12/20
//------------------------------------------------------------
#ifndef WCS_PAIR_H
#define WCS_PAIR_H

//#include "lsst/afw/table/misc.h"

class CL_PAIR{
private:
public:
//    long ID;    //OUTPUT INFO
//  boost::int64_t ID;    //OUTPUT INFO    
    long long int ID;
    int CHIPID;//OUTPUT INFO
    int FLAG;  //OUTPUT INFO
    double X_LOCAL[2];//OUTPUT INFO
    double X_RADEC[2];//OUTPUT INFO
    double X_LOCALERR[2];
    double X_RADECERR[2];

    double X_GLOBAL[2];     //OUTPUT INFO
    double X_GLOBALCRPIX[2];//OUTPUT INFO
    double X_LOCALCRPIX[2]; //OUTPUT INFO
    double X_IM_PIXEL[2];   //OUTPUT INFO
    double X_LOCALIM_PIXEL[2]; //
    double X_IM_WORLD[2];   //OUTPUT INFO
    double X_CRPIX[2];

    double X_SIP_IM_PIXEL[2];
    double X_PSIP_GLOBALCRPIX[2];

    double X_CENTER_GLOBAL[2];
    double X_CENTER_IM_PIXEL[2];
    double X_CENTER_IM_WORLD[2];
    double X_CENTER_RADEC[2];
    double CAMERA_CONVROT[2];    //OUTPUT INFO//Convergence by camera
    double CAMERA_SHEAR[2];      //OUTPUT INFO//Shear by camera
    double CAMERA_MAGNIFICATION; //OUTPUT INFO//Magnification by camera
    double CAMERA_JACOBIAN;      //OUTPUT INFO//JACOBIAN by camera
    double CAMERA_PIXELAREA;      //OUTPUT INFO//JACOBIAN by camera
    double CAMERA_PCONVROT[2];   //OUTPUT INFO//Convergence by camera
    double CAMERA_PSHEAR[2];     //OUTPUT INFO//Shear by camera
    double CAMERA_PMAGNIFICATION;//OUTPUT INFO//Magnification by camera
    double CAMERA_PJACOBIAN;     //OUTPUT INFO//JACOBIAN by camera
    double CAMERA_PPIXELAREA;      //OUTPUT INFO//JACOBIAN by camera
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
    int REJMODE;//REJECTION MODE
    int CCDNUM;
    int ALLREFNUM;
    int ALLFITNUM;
    int *REJNUM;
    int SIP_ORDER;
    int SIP_P_ORDER;
    int SIP_L_ORDER;
    int IterNUM_XY;
    int IterNUM_T;
    int STDOUT;
    double MAXDRAD;
    double MAXFRAD;
    double MINFRAD;
    double **GPOS;
    double GPOS_AVE[3];
    double BASISPOS[3];
    double CLIP_SIGMA;
    double CENTER_PIXEL[2];
    double CENTER_RADEC[2];
    double OAVAL[2];
    double OAPIX[2];
    double CRVAL[2];
    double CRPIX[2];
    double CD[2][2];
    double InvCD[2][2];
    double *SIP_AB[2];
    double *SIP_ABP[2];
    double *CDSIP_AB[2];//CD*SIP
    double *CDSIP_ABP[2];//InvCD*SIP
    double ANGLE;
    double AVERMS[2][2];
    double  SIPRMS[2][3];
    double PSIPRMS[2][3];
/*REJECT*/    double *TCoef[2];
/*REJECT*/    double *TdCoef[2][2];
/*REJECT*/    double *TPCoef[2];
/*REJECT*/    double *TdPCoef[2][2];
/*REJECT*/    double **TLCoef[2];
/*REJECT*/    double **TdLCoef[2][2];

//MAIN
    void F_WCSA_APAIR_NEWAPAIR();
    void F_WCSA_APAIR_DELAPAIR();
    void F_WCSA_APAIR_GPOS();
    void F_WCSA_APAIR_REJECTION();
    void F_WCSA_APAIR_WCS();
//X
    void F_WCSA_APAIR_SETX();
    void F_WCSA_APAIR_SETXG();
    void F_WCSA_APAIR_SETXCRPIX();
    void F_WCSA_APAIR_SETXIM();
    void F_WCSA_APAIR_SETXSIP();
    void F_WCSA_APAIR_CALCMAXR();
    void F_WCSA_APAIR_PROJECTION();
    void F_WCSA_APAIR_CENTERPROJECTION();
    void F_WCSA_APAIR_CENTERofOBJECTS();
    void F_WCSA_APAIR_CALCCR();
    void F_WCSA_APAIR_CALCCRVAL();
    void F_WCSA_APAIR_CALCCRPIX();

//FITTING
    void F_WCSA_APAIR_FITTING();
    void F_WCSA_APAIR_GFITTING(int ORDER,int VARIABLE,int FUNCTION, double **Coef);
    void F_WCSA_APAIR_LFITTING(int, int);//(FUNCTION), 
    void F_WCSA_APAIR_CALCRMS(int ORDER,int,int);//(ORDER,VALUE,FUNCTION)
    void F_WCSA_APAIR_SETCDSIP();
    void F_WCSA_APAIR_SETCDPSIP();
    void F_WCSA_APAIR_CHANGEVARIABLE(int, double CD[2][2],double *F,double *G);
    void F_WCSA_APAIR_CALCSIPRMS();//(ORDER,VALUE,FUNCTION), ORDER=(SIP_ORDER,SIP_P_ORDER,SIP_ORDER-1,SIP_L_ORDER)
    void F_WCSA_APAIR_CALCPSIPRMS();//(ORDER,VALUE,FUNCTION), ORDER=(SIP_ORDER,SIP_P_ORDER,SIP_ORDER-1,SIP_L_ORDER)
    void F_WCSA_APAIR_CALCCONVROTSHEARMAG();
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
    void F_WCSA_APAIR_SHOWCCDPOS();

};
#endif
