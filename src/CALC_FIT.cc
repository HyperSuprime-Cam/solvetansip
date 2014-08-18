//--------------------------------------------------
//CALC_FIT.cc
//
//Calculating Coefficients of Least Squares Fitting
//Output coefficients of F_LS2 are
//x^0y^0, x^0y^1, x^0y^2, x^0y^3, x^1y^0, x^1y^1, x^1y^2, x^2y^0, x^2y^1, x^3y^0 (in Order = 3)
//
//Last modification : 2014/01/01
//Yuki Okura : yuki.okura@nao.ac.jp
//--------------------------------------------------

#include <cmath>
#include <iostream>
#include <stdexcept>
#include "hsc/meas/tansip/CALC.h"
#include "LAPACK_FUNCS.h"

using namespace std;

ndarray::Array<double, 1, 1>
SOLVE_LINEAR_EQUATION(ndarray::Array<double, 2, 1> const& A, ndarray::Array<double, 1, 1> const& b){

	int N = A.getSize<1>();
	if(A.getSize<0>() != N || b.getSize<0>() != N){
		throw std::logic_error("SOLVE_LINEAR_EQUATION: dimensions are inconsistent");
	}

	ndarray::Array<double, 2, 2> AF    = ndarray::allocate(N, N);
	ndarray::Array<int   , 1, 1> ipiv  = ndarray::allocate(N);
	ndarray::Array<double, 1, 1> r     = ndarray::allocate(N);
	ndarray::Array<double, 1, 1> c     = ndarray::allocate(N);
	ndarray::Array<double, 1, 1> x     = ndarray::allocate(N);
	ndarray::Array<double, 1, 1> work  = ndarray::allocate(4 * N);
	ndarray::Array<int   , 1, 1> iwork = ndarray::allocate(N);

	int    nrhs = 1;
	int    lda = A.getStride<0>();
	char   equed;
	double rcond;
	double ferr ;
	double berr ;
	int    info ;
	dgesvx_(
		*"Equilibrate",
		*"Transpose", // because row majar
		N,
		nrhs,
		A.getData(),
		lda,
		AF.getData(),
		N,
		ipiv.getData(),
		&equed,
		r.getData(),
		c.getData(),
		b.getData(),
		N,
		x.getData(),
		N,
		&rcond,
		&ferr,
		&berr,
		work.getData(),
		iwork.getData(),
		&info
	);

	if(info == 0){
		; // OK
	}
	else if(info > N){
		// the matrix is extremely bad, but not exactly irregular
		cout << "warning: SOLVE_LINEAR_EQUATION: linear equation is extremely bad." << endl;
	}
	else{
		throw std::runtime_error("SOLVE_LINEAR_EQUATION: irregular linear equation");
	}

	return x;
}


ndarray::Array<double, 1, 1> // Return coefficients
CALC_FIT_LS2(int dataNUM, int Order, ndarray::Array<double, 2, 1> const& data){
	ndarray::Array<double, 2, 2> XA = ndarray::allocate((Order+1)*(Order+2)/2, (Order+1)*(Order+2)/2);
	ndarray::Array<double, 1, 1>  Z = ndarray::allocate((Order+1)*(Order+2)/2);
	ndarray::Array<double, 1, 1> XN = ndarray::allocate((Order+1)*(Order+1));
	ndarray::Array<double, 1, 1> YN = ndarray::allocate((Order+1)*(Order+1));

	XA.deep() = 0;
	Z.deep()  = 0;

	for(int NUM=0;NUM<dataNUM;NUM++){
		XN[0]=YN[0]=1;
		for(int i=1;i<(Order+1)*(Order+1);i++){
			XN[i]=XN[i-1]*data[NUM][0];
			YN[i]=YN[i-1]*data[NUM][1];
		}

		int ij=0;
		for(int i=0;i<Order+1  ;i++)
		for(int j=0;j<Order+1-i;j++){
			int kl=0;
			for(int k=0;k<Order+1  ;k++)
			for(int l=0;l<Order+1-k;l++){
				XA[ij][kl]+=XN[i+k]*YN[j+l];
				kl+=1;
			}
			Z[ij]+=data[NUM][2]*XN[i]*YN[j];
			ij+=1;
		}
	}

	return SOLVE_LINEAR_EQUATION(XA, Z);
}

