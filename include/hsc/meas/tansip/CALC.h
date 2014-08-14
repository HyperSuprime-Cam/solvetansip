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

//CALC_FIT
ndarray::Array<double, 1, 1>
SOLVE_LINEAR_EQUATION(ndarray::Array<double, 2, 1> const& A, ndarray::Array<double, 1, 1> const& b);
ndarray::Array<double, 1, 1> // Return coefficients
CALC_FIT_LS2(int dataNUM, int Order, ndarray::Array<double, 2, 1> const& data);

#endif
