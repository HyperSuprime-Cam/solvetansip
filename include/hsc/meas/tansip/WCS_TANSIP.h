//------------------------------------------------------------
//WCS_TANSIP.h
//
//Last modification : 2011/04/01
//------------------------------------------------------------

#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_CPROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"

void    F_WCS_TANSIP(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
//MAIN
void    F_WCS_TANSIP_SET (CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_CCD (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
//SUB
int*    F_NEWint1(int SIZE1);
double*     F_NEWdouble1(int SIZE1);
double**    F_NEWdouble2(int SIZE1,int SIZE2);
double***   F_NEWdouble3(int SIZE1,int SIZE2,int SIZE3);
double****  F_NEWdouble4(int SIZE1,int SIZE2,int SIZE3,int SIZE4);
char*** F_NEWchar3(int SIZE1,int SIZE2,int SIZE3);
void    F_DELint1(int *MAT);
void    F_DELdouble1(double *MAT);
void    F_DELdouble2(int SIZE1,double **MAT);
void    F_DELdouble3(int SIZE1,int SIZE2,double ***MAT);
void    F_DELdouble4(int SIZE1,int SIZE2,int SIZE3,double ****MAT);
void    F_DELchar3(int SIZE1,int SIZE2,char ***MAT);
double  F_CALCVALUE(int ORDER,double *Coef,double *X);
void    F_PROJECTION(double *Cdeg,double *Pdeg,double *PPOINT);
void    F_InvPROJECTION(double *Pdeg,double *Cdeg,double *PPOINT);
void    F_DIFFSIP(int ORDER,double *Coef,double *dxCoef,double *dyCoef);  
void    F_INTSIP(int ORDER,double *dxCoef,double *dyCoef,double *Coef);
//etc
void    F_LS2(int dataNUM,int Order,double **data,double *Coef);
void    F_LS1(int dataNUM,int Order,double **data,double *Coef);
void	F_RMS(int NUM,double *data,double *STAT);
void    F_InvM(int MNUM,double **Min,double **Mout);
