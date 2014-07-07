//------------------------------------------------------------
//CALC.h
//
//Last Update 2014/07/07
//Originally by Yuki Okura : yuki.okura@nao.ac.jp
//------------------------------------------------------------
#ifndef CALC_H
#define CALC_H

#include <ndarray.h>

//CALC_STAT
void	CALC_STAT_GAUSSUNIT(int srandNUM, int RNDNUM, double *RNDSET);
int	CALC_STAT_RMS(int NUM,double *data,double *STAT);
int	CALC_STAT_RMS(int NUM,float  *data,double *STAT);
double	CALC_MEDIAN(int NUM,double *data);
int	CALC_STAT_RMSMAX(int NUM,double *data,double *STAT);
//CALC_MATRIX
ndarray::Array<double, 1, 1>
SOLVE_LINEAR_EQUATION(ndarray::Array<double, 2, 1> const& A, ndarray::Array<double, 1, 1> const& b);
//CALC_FIT
//void    CALC_FIT_LS1(int dataNUM,int Order,double **data,double *Coef);
ndarray::Array<double, 1, 1> // Return coefficients
CALC_FIT_LS2(int dataNUM, int Order, ndarray::Array<double, 2, 1> const& data);
//void    CALC_FIT_LS3(int dataNUM,int Order,double **data,double *Coef);
//void    CALC_FIT_LS3_2(int dataNUM,int Order,double **data,double *Coef);
//double  CALC_FIT_VALUE2(int ORDER,double *Coef,double *X);
//CALC_COMPLEX
void CALC_COMPLEX_ADD2(double *INPUT1,double *INPUT2,double *RETURN);
void CALC_COMPLEX_ADD3(double *INPUT1,double *INPUT2,double *INPUT3,double *RETURN);
void CALC_COMPLEX_ADD4(double *INPUT1,double *INPUT2,double *INPUT3,double *INPUT4,double *RETURN);
void CALC_COMPLEX_ADD5(double *INPUT1,double *INPUT2,double *INPUT3,double *INPUT4,double *INPUT5,double *RETURN);
void CALC_COMPLEX_MUL2(int CONJU1,double *INPUT1,int CONJU2,double *INPUT2,double *RETURN);
void CALC_COMPLEX_MUL3(int CONJU1,double *INPUT1,int CONJU2,double *INPUT2,int CONJU3,double *INPUT3,double *RETURN);
void CALC_COMPLEX_MUL4(int CONJU1,double *INPUT1,int CONJU2,double *INPUT2,int CONJU3,double *INPUT3,int CONJU4,double *INPUT4,double *RETURN);
void CALC_COMPLEX_MUL5(int CONJU1,double *INPUT1,int CONJU2,double *INPUT2,int CONJU3,double *INPUT3,int CONJU4,double *INPUT4,int CONJU5,double *INPUT5,double *RETURN);
//FFT
void	fourn(float data[], unsigned long nn[], int ndim, int isign);
#endif
