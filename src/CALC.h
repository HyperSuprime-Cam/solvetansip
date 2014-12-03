//------------------------------------------------------------
//CALC.h
//
//Last Update 2014/07/07
//Originally by Yuki Okura : yuki.okura@nao.ac.jp
//------------------------------------------------------------
#ifndef  g599a60b9_5b86_4a72_a0ca_e47479c8e738
#define  g599a60b9_5b86_4a72_a0ca_e47479c8e738

#include <ndarray.h>
#include "Polynomial.h"

namespace hsc { namespace meas {
namespace tansip {

//CALC_STAT
int  CALC_STAT_RMS(int NUM,double *data,double *STAT);
int  CALC_STAT_RMS(int NUM,float  *data,double *STAT);
double  CALC_MEDIAN(int NUM,double *data);
int  CALC_STAT_RMSMAX(int NUM,double *data,double *STAT);

//CALC_FIT
ndarray::Array<double, 1, 1>
SOLVE_LINEAR_EQUATION(ndarray::Array<double, 2, 1> const& A, ndarray::Array<double, 1, 1> const& b);
Polynomial2D
CALC_FIT_LS2(int dataNUM, int Order, ndarray::Array<double, 2, 1> const& data);

} // namespace tansip
}} // namespace hsc::meas
#endif //g599a60b9_5b86_4a72_a0ca_e47479c8e738
