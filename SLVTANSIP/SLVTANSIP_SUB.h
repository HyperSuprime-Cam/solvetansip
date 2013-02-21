//------------------------------------------------------------
//SLVTANSIP_FITTING.h
//
//Last modification : 2013/02/01
//------------------------------------------------------------
#ifndef SLVTANSIP_SUB_H
#define SLVTANSIP_SUB_H

int*    F_NEWint1(int SIZE1);
double*     F_NEWdouble1(int SIZE1);
double**    F_NEWdouble2(int SIZE1,int SIZE2);
double***   F_NEWdouble3(int SIZE1,int SIZE2,int SIZE3);
double****  F_NEWdouble4(int SIZE1,int SIZE2,int SIZE3,int SIZE4);
double***** F_NEWdouble5(int SIZE1,int SIZE2,int SIZE3,int SIZE4,int SIZE5);
char*** F_NEWchar3(int SIZE1,int SIZE2,int SIZE3);
int	F_FACTORIAL2(int X);
double	F_INTEGRAL_R(int ORDER, double MAX_R, double **FUNCTION);
void    F_DELint1(int *MAT);
void    F_DELdouble1(double *MAT);
void    F_DELdouble2(int SIZE1,double **MAT);
void    F_DELdouble3(int SIZE1,int SIZE2,double ***MAT);
void    F_DELdouble4(int SIZE1,int SIZE2,int SIZE3,double ****MAT);
void    F_DELdouble5(int SIZE1,int SIZE2,int SIZE3,int SIZE4,double *****MAT);
void    F_DELchar3(int SIZE1,int SIZE2,char ***MAT);
double  F_CALCVALUE(int ORDER,double *Coef,double *X);
void    F_PROJECTION(double *Cdeg,double *Pdeg,double *PPOINT);
void    F_InvPROJECTION(double *Pdeg,double *Cdeg,double *PPOINT);
void    F_DIFFSIP(int ORDER,double *Coef,double *dxCoef,double *dyCoef);  
void    F_INTSIP(int ORDER,double *dxCoef,double *dyCoef,double *Coef);
void    F_SIPROT(int ORDER, double Theta, double *InCoef, double *OutCoef);
void    F_GaussUnit(int srandNUM, int RNDNUM, double *RNDSET);
#endif
