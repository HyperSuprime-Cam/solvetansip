//------------------------------------------------------------
//LeastSqaures.h
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#ifndef LEASTSQUARES_H
#define LEASTSQUARES_H

void    F_LS2(int dataNUM,int Order,double **data,double *Coef);
void    F_LS2_FAST(int dataNUM,int Order,double **data,double *Coef);
void    F_LS1(int dataNUM,int Order,double **data,double *Coef);
void	F_RMS(int NUM,double *data,double *STAT);
void	F_RMSMAX(int NUM,double *data,double *STAT);
void    F_InvM(int MNUM,double **Min,double **Mout);

#endif
