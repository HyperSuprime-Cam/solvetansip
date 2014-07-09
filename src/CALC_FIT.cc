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


#if 0
ndarray::Array<double, 1, 1> // Return coefficients
CALC_FIT_LS1(int dataNUM, int Order, ndarray::Array<double, 2, 1> const& data){
	int i,j,NUM;

	ndarray::Array<double, 2, 2> XA = ndarray::allocate(Order+1, Order+1);
	ndarray::Array<double, 1, 1>  Z = ndarray::allocate(Order+1);
	ndarray::Array<double, 1, 1> XN = ndarray::allocate(Order+1);

	XA.deep() = 0;
	Z.deep() = 0;

	for(NUM=0;NUM<dataNUM;NUM++){
		XN[0]=1;
		for(i=1;i<Order+1;i++){
			XN[i]=XN[i-1]*data[NUM][0];
		}
		for(i=0;i<Order+1;i++){
			for(j=0;j<Order+1;j++)
			XA[i][j]+=XN[i]*XN[j];
			Z[i]+=data[NUM][1]*XN[i];
		}
	}

	return SOLVE_LINEAR_EQUATION(XA, Z);
}
#endif

ndarray::Array<double, 1, 1> // Return coefficients
CALC_FIT_LS2(int dataNUM, int Order, ndarray::Array<double, 2, 1> const& data){
	int i,j,k,l,ij,kl,NUM;

	ndarray::Array<double, 2, 2> XA = ndarray::allocate((Order+1)*(Order+2)/2, (Order+1)*(Order+2)/2);
	ndarray::Array<double, 1, 1>  Z = ndarray::allocate((Order+1)*(Order+2)/2);
	ndarray::Array<double, 1, 1> XN = ndarray::allocate((Order+1)*(Order+1));
	ndarray::Array<double, 1, 1> YN = ndarray::allocate((Order+1)*(Order+1));

	XA.deep() = 0;
	Z.deep()  = 0;

	for(NUM=0;NUM<dataNUM;NUM++){
		XN[0]=YN[0]=1;
		for(i=1;i<(Order+1)*(Order+1);i++){
			XN[i]=XN[i-1]*data[NUM][0];
			YN[i]=YN[i-1]*data[NUM][1];
		}

		ij=0;
		for(i=0;i<Order+1  ;i++)
		for(j=0;j<Order+1-i;j++){
			kl=0;
			for(k=0;k<Order+1  ;k++)
			for(l=0;l<Order+1-k;l++){
				XA[ij][kl]+=XN[i+k]*YN[j+l];
				kl+=1;
			}
			Z[ij]+=data[NUM][2]*XN[i]*YN[j];
			ij+=1;
		}
	}

	return SOLVE_LINEAR_EQUATION(XA, Z);
}

#if 0
void    CALC_FIT_LS3_2(int dataNUM,double **data,double *Coef){
	int i,j;
	double **XA,**XB,Z[10];

	XA = new double*[10];
	XB = new double*[10];
	for(i=0;i<10;i++){
		XA[i] = new double[10];
		XB[i] = new double[10];
	}

	for(i=0;i<10;i++){
		Z[i]=Coef[i]=0;
		for(j=0;j<10;j++)
		XA[i][j]=XB[i][j]=0;
	}

	for(i=0;i<dataNUM;i++){
		Z[0]+=data[i][3]*1;
		Z[1]+=data[i][3]*data[i][2];
		Z[2]+=data[i][3]*data[i][2]*data[i][2];
		Z[3]+=data[i][3]*data[i][1];
		Z[4]+=data[i][3]*data[i][1]*data[i][2];
		Z[5]+=data[i][3]*data[i][1]*data[i][1];
		Z[6]+=data[i][3]*data[i][0];
		Z[7]+=data[i][3]*data[i][0]*data[i][2];
		Z[8]+=data[i][3]*data[i][0]*data[i][1];
		Z[9]+=data[i][3]*data[i][0]*data[i][0];

		XA[0][0]+=1*1;
		XA[0][1]+=1*data[i][2];
		XA[0][2]+=1*data[i][2]*data[i][2];
		XA[0][3]+=1*data[i][1];
		XA[0][4]+=1*data[i][1]*data[i][2];
		XA[0][5]+=1*data[i][1]*data[i][1];
		XA[0][6]+=1*data[i][0];
		XA[0][7]+=1*data[i][0]*data[i][2];
		XA[0][8]+=1*data[i][0]*data[i][1];
		XA[0][9]+=1*data[i][0]*data[i][0];
		XA[1][1]+=data[i][2]*data[i][2];
		XA[1][2]+=data[i][2]*data[i][2]*data[i][2];
		XA[1][3]+=data[i][2]*data[i][1];
		XA[1][4]+=data[i][2]*data[i][1]*data[i][2];
		XA[1][5]+=data[i][2]*data[i][1]*data[i][1];
		XA[1][6]+=data[i][2]*data[i][0];
		XA[1][7]+=data[i][2]*data[i][0]*data[i][2];
		XA[1][8]+=data[i][2]*data[i][0]*data[i][1];
		XA[1][9]+=data[i][2]*data[i][0]*data[i][0];
		XA[2][2]+=data[i][2]*data[i][2]*data[i][2]*data[i][2];
		XA[2][3]+=data[i][2]*data[i][2]*data[i][1];
		XA[2][4]+=data[i][2]*data[i][2]*data[i][1]*data[i][2];
		XA[2][5]+=data[i][2]*data[i][2]*data[i][1]*data[i][1];
		XA[2][6]+=data[i][2]*data[i][2]*data[i][0];
		XA[2][7]+=data[i][2]*data[i][2]*data[i][0]*data[i][2];
		XA[2][8]+=data[i][2]*data[i][2]*data[i][0]*data[i][1];
		XA[2][9]+=data[i][2]*data[i][2]*data[i][0]*data[i][0];
		XA[3][3]+=data[i][1]*data[i][1];
		XA[3][4]+=data[i][1]*data[i][1]*data[i][2];
		XA[3][5]+=data[i][1]*data[i][1]*data[i][1];
		XA[3][6]+=data[i][1]*data[i][0];
		XA[3][7]+=data[i][1]*data[i][0]*data[i][2];
		XA[3][8]+=data[i][1]*data[i][0]*data[i][1];
		XA[3][9]+=data[i][1]*data[i][0]*data[i][0];
		XA[4][4]+=data[i][1]*data[i][2]*data[i][1]*data[i][2];
		XA[4][5]+=data[i][1]*data[i][2]*data[i][1]*data[i][1];
		XA[4][6]+=data[i][1]*data[i][2]*data[i][0];
		XA[4][7]+=data[i][1]*data[i][2]*data[i][0]*data[i][2];
		XA[4][8]+=data[i][1]*data[i][2]*data[i][0]*data[i][1];
		XA[4][9]+=data[i][1]*data[i][2]*data[i][0]*data[i][0];
		XA[5][5]+=data[i][1]*data[i][1]*data[i][1]*data[i][1];
		XA[5][6]+=data[i][1]*data[i][1]*data[i][0];
		XA[5][7]+=data[i][1]*data[i][1]*data[i][0]*data[i][2];
		XA[5][8]+=data[i][1]*data[i][1]*data[i][0]*data[i][1];
		XA[5][9]+=data[i][1]*data[i][1]*data[i][0]*data[i][0];
		XA[6][6]+=data[i][0]*data[i][0];
		XA[6][7]+=data[i][0]*data[i][0]*data[i][2];
		XA[6][8]+=data[i][0]*data[i][0]*data[i][1];
		XA[6][9]+=data[i][0]*data[i][0]*data[i][0];
		XA[7][7]+=data[i][0]*data[i][2]*data[i][0]*data[i][2];
		XA[7][8]+=data[i][0]*data[i][2]*data[i][0]*data[i][1];
		XA[7][9]+=data[i][0]*data[i][2]*data[i][0]*data[i][0];
		XA[8][8]+=data[i][0]*data[i][1]*data[i][0]*data[i][1];
		XA[8][9]+=data[i][0]*data[i][1]*data[i][0]*data[i][0];
		XA[9][9]+=data[i][0]*data[i][0]*data[i][0]*data[i][0];
	}
	for(i=1;i<10;i++)
	for(j=0;j< i;j++)
	XA[i][j]=XA[j][i];

	CALC_MATRIX_INVERSE(10,XA,XB);

	for(i=0;i<10;i++)
	for(j=0;j<10;j++)
	Coef[i]+=XB[i][j]*Z[j];

	for(i=0;i<10;i++){
		delete [] XA[i];
		delete [] XB[i];
	}
	delete [] XA;
	delete [] XB;
}
void    CALC_FIT_LS3(int dataNUM,int Order,double **data,double *Coef){
	int i,j,k,l,m,n,ijk,lmn,NUM;
	double **XA,**XB,*Z;
	double *XN,*YN,*ZN;

	XA = new double*[(Order+1)*(Order+1)*(Order+1)];
	XB = new double*[(Order+1)*(Order+1)*(Order+1)];
	 Z = new double[(Order+1)*(Order+1)*(Order+1)];
	XN = new double[(Order+1)*(Order+1)*(Order+1)];
	YN = new double[(Order+1)*(Order+1)*(Order+1)];
	ZN = new double[(Order+1)*(Order+1)*(Order+1)];
	for(i=0;i<(Order+1)*(Order+1)*(Order+1);i++){
		XA[i] = new double[(Order+1)*(Order+1)*(Order+1)];
		XB[i] = new double[(Order+1)*(Order+1)*(Order+1)];
	}

	for(i=0;i<(Order+1)*(Order+1)*(Order+1);i++){
		for(j=0;j<(Order+1)*(Order+1)*(Order+1);j++)
		XA[i][j]=XB[i][j]=0;
		Z[i]=0;
	}

	ijk=0;
	for(i=0;i<Order+1;i++)
	for(j=0;j<Order+1;j++)
	for(k=0;k<Order+1;k++)
	if(i+j+k<Order+1){
		Coef[ijk]=0;
		ijk++;
	}

	for(NUM=0;NUM<dataNUM;NUM++){
		XN[0]=YN[0]=ZN[0]=1;
		for(i=1;i<(Order+1)*(Order+1)*(Order+1);i++){
			XN[i]=XN[i-1]*data[NUM][0];
			YN[i]=YN[i-1]*data[NUM][1];
			ZN[i]=ZN[i-1]*data[NUM][2];
		}

		ijk=0;
		for(i=0;i<Order+1;i++)
		for(j=0;j<Order+1;j++)
		for(k=0;k<Order+1;k++)
		if(i+j+k<Order+1){
			lmn=0;
			for(l=0;l<Order+1;l++)
			for(m=0;m<Order+1;m++)
			for(n=0;n<Order+1;n++)
			if(l+m+n<Order+1){
				XA[ijk][lmn]+=XN[i+k]*YN[j+l]*ZN[k+n];
				lmn+=1;
			}
			Z[ijk]+=data[NUM][3]*XN[i]*YN[j]*ZN[k];
			ijk+=1;
		}
	}


	CALC_MATRIX_INVERSE((int)((Order+1)*(Order+2)*(Order+3)/2.0/3.0+0.1),XA,XB);

	ijk=0;
	for(i=0;i<Order+1;i++)
	for(j=0;j<Order+1;j++)
	for(k=0;k<Order+1;k++)
	if(i+j+k<Order+1){
		lmn=0;
		for(l=0;l<Order+1;l++)
		for(m=0;m<Order+1;m++)
		for(n=0;n<Order+1;n++)
		if(l+m+n<Order+1){
		Coef[ijk]+=XB[ijk][lmn]*Z[lmn];
		lmn+=1;
		}
		ijk+=1;
	}

	for(i=0;i<(Order+1)*(Order+1);i++){
		delete [] XA[i];
		delete [] XB[i];
	}
	delete [] XN;
	delete [] YN;
	delete [] ZN;
	delete [] XA;
	delete [] XB;
	delete [] Z;
}
double  CALC_FIT_VALUE2(int Order,double *Coef,double *X){
	int i,j,ij;
	double Z;
	double *XN,*YN;

	XN = new double [(Order+1)];
	YN = new double [(Order+1)];
	XN[0]=YN[0]=1;
	for(i=0;i<Order+1;i++){
		XN[i]=XN[i-1]*X[0];
		YN[i]=YN[i-1]*X[1];
	}

	Z=ij=0;
	for(i=0;i<Order+1  ;i++)
	for(j=0;j<Order+1-i;j++){
		Z+=Coef[ij]*XN[i]*YN[j];
		ij++;
	}
	delete [] XN;
	return Z;
}
#endif
