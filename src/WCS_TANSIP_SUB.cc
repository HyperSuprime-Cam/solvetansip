//------------------------------------------------------------
//WCS_TANSIP_SUB.cc
//Sub routines
//
//Last modification : 2010/04/01
//------------------------------------------------------------
#include <stdlib.h>
#include<cmath>
//#include "hsc/meas/tansip/WCS_TANSIP.h"

#define PI (4*atan(1.0))
#define LP 180
#define INFMIN pow(10,-10)

int*	F_NEWint1(int SIZE1){
	int *MAT;
	int i;

	MAT = new int[SIZE1];
	for(i=0;i<SIZE1;i++)
	MAT[i]=0;

	return MAT;
}
double*	F_NEWdouble1(int SIZE1){
	double *MAT;
	int i;

	MAT = new double[SIZE1];
	for(i=0;i<SIZE1;i++)
	MAT[i]=0;

	return MAT;
}
double**	F_NEWdouble2(int SIZE1,int SIZE2){
	double **MAT;
	int i,j;

	MAT = new double*[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new double[SIZE2];
	for(j=0;j<SIZE2;j++)
	MAT[i][j]=0;
	}

	return MAT;
}
double***	F_NEWdouble3(int SIZE1,int SIZE2,int SIZE3){
	double ***MAT;
	int i,j,k;

	MAT = new double**[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new double*[SIZE2];
	for(j=0;j<SIZE2;j++){
	MAT[i][j] = new double[SIZE3];
	for(k=0;k<SIZE3;k++)
	MAT[i][j][k]=0;
	}}

	return MAT;
}
double****	F_NEWdouble4(int SIZE1,int SIZE2,int SIZE3,int SIZE4){
	double ****MAT;
	int i,j,k,l;

	MAT = new double***[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new double**[SIZE2];
	for(j=0;j<SIZE2;j++){
	MAT[i][j] = new double*[SIZE3];
	for(k=0;k<SIZE3;k++){
	MAT[i][j][k] = new double[SIZE4];
	for(l=0;l<SIZE4;l++)
	MAT[i][j][k][l]=0;
	}}}

	return MAT;
}
double*****	F_NEWdouble5(int SIZE1,int SIZE2,int SIZE3,int SIZE4,int SIZE5){
	double *****MAT;
	int i,j,k,l,m;

	MAT = new double****[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new double***[SIZE2];
	for(j=0;j<SIZE2;j++){
	MAT[i][j] = new double**[SIZE3];
	for(k=0;k<SIZE3;k++){
	MAT[i][j][k] = new double*[SIZE4];
	for(l=0;l<SIZE4;l++){
	MAT[i][j][k][l] = new double[SIZE5];
	for(m=0;m<SIZE5;m++)
	MAT[i][j][k][l][m]=0;
	}}}}

	return MAT;
}
char***	F_NEWchar3(int SIZE1,int SIZE2,int SIZE3){
	char ***MAT;
	int i,j,k;

	MAT = new char**[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new char*[SIZE2];
	for(j=0;j<SIZE2;j++){
	MAT[i][j] = new char[SIZE3];
	for(k=0;k<SIZE3;k++)
	MAT[i][j][k]=0;
	}}

	return MAT;
}
void	F_DELint1(int *MAT){
	delete [] MAT;
}
void	F_DELdouble1(double *MAT){
	delete [] MAT;
}
void	F_DELdouble2(int SIZE1,double **MAT){
	int i;

	for(i=0;i<SIZE1;i++)
	delete [] MAT[i];
	delete [] MAT;
}
void	F_DELdouble3(int SIZE1,int SIZE2,double ***MAT){
	int i,j;

	for(i=0;i<SIZE1;i++){
	for(j=0;j<SIZE2;j++)
	delete [] MAT[i][j];
	delete [] MAT[i];
        }
	delete [] MAT;
}
void	F_DELdouble4(int SIZE1,int SIZE2,int SIZE3,double ****MAT){
	int i,j,k;

	for(i=0;i<SIZE1;i++){
	for(j=0;j<SIZE2;j++){
	for(k=0;k<SIZE3;k++)
	delete [] MAT[i][j][k];
	delete [] MAT[i][j];
        }
	delete [] MAT[i];
        }
	delete [] MAT;
}
void	F_DELdouble5(int SIZE1,int SIZE2,int SIZE3,int SIZE4,double *****MAT){
	int i,j,k,l;

	for(i=0;i<SIZE1;i++){
	for(j=0;j<SIZE2;j++){
	for(k=0;k<SIZE3;k++){
	for(l=0;l<SIZE4;l++)
	delete [] MAT[i][j][k][l];
	delete [] MAT[i][j][k];
        }
	delete [] MAT[i][j];
        }
	delete [] MAT[i];
        }
	delete [] MAT;
}
void	F_DELchar3(int SIZE1,int SIZE2,char ***MAT){
	int i,j;

	for(i=0;i<SIZE1;i++){
	for(j=0;j<SIZE2;j++)
	delete [] MAT[i][j];
	delete [] MAT[i];
        }
	delete [] MAT;
}

int	F_FACTORIAL2(int X){
	int Y,Z;

	Z=1;
	for(Y=X;Y>1.5;Y-=2)
	Z*=Y;
	return Z;
}
double	F_INTEGRAL_R(int ORDER, double MAX_R, double **FUNCTION){
	int i,j;
	double X,Y,Z;
	Z=0;
	for(i=0;i<ORDER+1;i+=2)
	for(j=0;j<ORDER+1;j+=2){
		X=pow(MAX_R,i+j+2)/(2+i+j);
		Y=2*PI*FUNCTION[i][j]*F_FACTORIAL2(i-1)*F_FACTORIAL2(j-1)/F_FACTORIAL2(i+j);

		Z+=X*Y;
	}

	return Z;
}
double  F_CALCVALUE(int ORDER,double *Coef,double *X){
    int i,j,ij;
    double Z;

    Z=ij=0;
    for(i=0;i<ORDER+1;i++)
    for(j=0;j<ORDER+1;j++)
    if(i+j<ORDER+1){
        Z+=Coef[ij]*pow(X[0],i)*pow(X[1],j);
        ij++;
    }
    return Z;
}
void    F_PROJECTION(double *Cdeg,double *Pdeg,double *PPOINT){
    double NRAD[2];//native psi,theta (RAD)
	
    NRAD[1]=asin(sin(Cdeg[1]/180*PI)*sin(PPOINT[1]/180*PI)+cos(Cdeg[1]/180*PI)*cos(PPOINT[1]/180*PI)*cos(Cdeg[0]/180*PI-PPOINT[0]/180*PI));
    NRAD[0]=atan2(-cos(Cdeg[1]/180*PI)*sin(Cdeg[0]/180*PI-PPOINT[0]/180*PI),sin(Cdeg[1]/180*PI)*cos(PPOINT[1]/180*PI)-cos(Cdeg[1]/180*PI)*sin(PPOINT[1]/180*PI)*cos(Cdeg[0]/180*PI-PPOINT[0]/180*PI))+LP/180*PI;

    Pdeg[0]= 180/PI/tan(NRAD[1])*sin(NRAD[0]);//+PPOINT[0];
    Pdeg[1]=-180/PI/tan(NRAD[1])*cos(NRAD[0]);//+PPOINT[1];
}
void    F_InvPROJECTION(double *Pdeg,double *Cdeg,double *PPOINT){
    double NRAD[2];//native psi,theta (RAD)
	
    NRAD[0]=atan2(Pdeg[0],-Pdeg[1]);	
    NRAD[1]=atan(180/PI/sqrt(Pdeg[0]*Pdeg[0]+Pdeg[1]*Pdeg[1]));
    if(NRAD[0]<0)
    NRAD[0]+=2*PI;                                     
    if(NRAD[0]>2*PI)
    NRAD[0]-=2*PI;

    Cdeg[1]=180/PI*asin(sin(NRAD[1])*sin(PPOINT[1]/180*PI)+cos(NRAD[1])*cos(NRAD[0]-LP/180*PI)*cos(PPOINT[1]/180*PI));//-90deg - 90deg
    Cdeg[0]=180/PI*atan2(-cos(NRAD[1])*sin(NRAD[0]-LP/180*PI),sin(NRAD[1])*cos(PPOINT[1]/180*PI)-cos(NRAD[1])*cos(NRAD[0]-LP/180*PI)*sin(PPOINT[1]/180*PI))+PPOINT[0];
}
void    F_DIFFSIP(int ORDER,double *Coef,double *dxCoef,double *dyCoef){
    int i,j,ij=0;
    double **Coef2,**dxCoef2,**dyCoef2;

      Coef2 = F_NEWdouble2(ORDER+1,ORDER+1);
    dxCoef2 = F_NEWdouble2(ORDER+1,ORDER+1);
    dyCoef2 = F_NEWdouble2(ORDER+1,ORDER+1);

    for(i=0;i<ORDER+1;i++)
    for(j=0;j<ORDER+1;j++)
    if(i+j<ORDER+1){
        Coef2[i][j]=Coef[ij];
        ij++;
    }
    for(i=0;i<ORDER+1;i++)
    for(j=0;j<ORDER+1;j++){
        if(i<(ORDER+1)-1)
        dxCoef2[i][j]=(i+1)*Coef2[i+1][j];
        if(j<(ORDER+1)-1)
        dyCoef2[i][j]=(j+1)*Coef2[i][j+1];
    }
    ij=0;
    for(i=0;i<ORDER+1;i++)
    for(j=0;j<ORDER+1;j++)
    if(i+j<ORDER+1){
        dxCoef[ij]=dxCoef2[i][j];
        dyCoef[ij]=dyCoef2[i][j];
        ij++;
    }
 
    F_DELdouble2(ORDER+1,  Coef2);
    F_DELdouble2(ORDER+1,dxCoef2);
    F_DELdouble2(ORDER+1,dyCoef2);
}
void    F_INTSIP(int ORDER,double *dxCoef,double *dyCoef,double *Coef){
    int i,j,ij,CoefNUM;
    double **dxCoef2,**dyCoef2,**xCoef2,**yCoef2,**Coef2;

    CoefNUM=(int)((ORDER+1)*(ORDER+2)+0.1);

      Coef2 = F_NEWdouble2(ORDER+1,ORDER+1);
     xCoef2 = F_NEWdouble2(ORDER+1,ORDER+1);
     yCoef2 = F_NEWdouble2(ORDER+1,ORDER+1);
    dxCoef2 = F_NEWdouble2(ORDER+1,ORDER+1);
    dyCoef2 = F_NEWdouble2(ORDER+1,ORDER+1);

    ij=0;
    for(i=0;i<ORDER+1-1;i++)
    for(j=0;j<ORDER+1-1;j++)
    if(i+j<ORDER+1-1){
        dxCoef2[i][j]=dxCoef[ij];
        dyCoef2[i][j]=dyCoef[ij];
        ij++;
    }
    for(i=0;i<ORDER+1;i++)
    for(j=0;j<ORDER+1;j++){
        if(i>0)
        xCoef2[i][j]=1.0/i*dxCoef2[i-1][j];
        if(j>0)
        yCoef2[i][j]=1.0/j*dyCoef2[i][j-1];
    }
    for(i=0;i<ORDER+1;i++)
    for(j=0;j<ORDER+1;j++){
        if(i==0&&j==0)
        Coef2[i][j]=0;
        if(i==0&&j!=0)
        Coef2[i][j]=yCoef2[i][j];
        if(i!=0&&j==0)
        Coef2[i][j]=xCoef2[i][j];
        if(i!=0&&j!=0)
        Coef2[i][j]=0.5*(xCoef2[i][j]+yCoef2[i][j]);
    }
    ij=0;
    for(i=0;i<ORDER+1;i++)
    for(j=0;j<ORDER+1;j++)
    if(i+j<ORDER+1){
        Coef[ij]=Coef2[i][j];
        ij++;
    }

    F_DELdouble2(ORDER+1,  Coef2);
    F_DELdouble2(ORDER+1, xCoef2);
    F_DELdouble2(ORDER+1, yCoef2);
    F_DELdouble2(ORDER+1,dxCoef2);
    F_DELdouble2(ORDER+1,dyCoef2);
}
#undef LP
#undef PI
#undef INFMIN
void    F_SIPROT(int ORDER, double THETA, double *InCoef, double *OutCoef){
    int i,j,ij;
    double ***Coef;

    Coef = F_NEWdouble3(2,ORDER+1,ORDER+1);
//--------------------------------------------------

    double ABS[10],PHI[10],Z[10][2];

    ij=0;
    for(i=0;i<ORDER+1;i++)
    for(j=0;j<ORDER+1;j++)
    if(i+j<ORDER+1)
    Coef[0][i][j]=InCoef[ij++];

// 0 -----
        if(ORDER > -0.5)
        Coef[1][0][0] =Coef[0][0][0];

// 1 -----
        if(ORDER >  0.5){
            ABS[1]=hypot(Coef[0][0][1],Coef[0][1][0]);
            PHI[1]=atan2(Coef[0][0][1],Coef[0][1][0]);
            Coef[1][1][0]=ABS[1]*cos(PHI[1]-1*THETA);
            Coef[1][0][1]=ABS[1]*sin(PHI[1]-1*THETA);
        }

// 2 -----
        if(ORDER >  1.5){
            Z[2][0]=0.5*(Coef[0][2][0]-Coef[0][0][2]);
            Z[2][1]=0.5*(Coef[0][1][1]);
            ABS[0]=0.5*(Coef[0][2][0]+Coef[0][0][2]);
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            Coef[1][2][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA);
            Coef[1][1][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA);
            Coef[1][0][2]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA);
        }

// 3 -----
        if(ORDER >  2.5){
            Z[1][0]=0.25*(3*Coef[0][3][0]+  Coef[0][1][2]);
            Z[1][1]=0.25*(  Coef[0][2][1]+3*Coef[0][0][3]);
            Z[3][0]=0.25*(  Coef[0][3][0]-  Coef[0][1][2]);
            Z[3][1]=0.25*(  Coef[0][2][1]-  Coef[0][0][3]);
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            Coef[1][3][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA);
            Coef[1][2][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA);
            Coef[1][1][2]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA);
            Coef[1][0][3]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA);
        }

// 4 -----
        if(ORDER >  3.5){
            Z[2][0]=  0.5*(Coef[0][4][0]-Coef[0][0][4]);
            Z[2][1]= 0.25*(Coef[0][3][1]+Coef[0][1][3]);
            Z[4][0]=0.125*(Coef[0][4][0]-Coef[0][2][2]+Coef[0][0][4]);
            Z[4][1]=0.125*(Coef[0][3][1]-Coef[0][1][3]);
            ABS[0]=0.125*(3*Coef[0][4][0]+Coef[0][2][2]+3*Coef[0][0][4]);
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            Coef[1][4][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA);
            Coef[1][3][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+4*ABS[4]*sin(PHI[4]-4*THETA);
            Coef[1][2][2]=2*ABS[0]+0*ABS[2]*cos(PHI[2]-2*THETA)-6*ABS[4]*cos(PHI[4]-4*THETA);
            Coef[1][1][3]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)-4*ABS[4]*sin(PHI[4]-4*THETA);
            Coef[1][0][4]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA);
        }

// 5 -----
        if(ORDER >  4.5){
            Z[1][0]=(5*Coef[0][5][0]+  Coef[0][3][2]+  Coef[0][1][4])/16.0*2.0;
            Z[1][1]=(  Coef[0][4][1]+  Coef[0][2][3]+5*Coef[0][0][5])/16.0*2.0;
            Z[3][0]=(5*Coef[0][5][0]-  Coef[0][3][2]-3*Coef[0][1][4])/16.0;
            Z[3][1]=(3*Coef[0][4][1]+  Coef[0][2][3]-5*Coef[0][0][5])/16.0;
            Z[5][0]=(  Coef[0][5][0]-  Coef[0][3][2]+  Coef[0][1][4])/16.0;
            Z[5][1]=(  Coef[0][4][1]-  Coef[0][2][3]+  Coef[0][0][5])/16.0;
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            ABS[5]=hypot(Z[5][1],Z[5][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            PHI[5]=atan2(Z[5][1],Z[5][0]);
            Coef[1][5][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA);
            Coef[1][4][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA);
            Coef[1][3][2]=2*ABS[1]*cos(PHI[1]-1*THETA)-2*ABS[3]*cos(PHI[3]-3*THETA)-10*ABS[5]*cos(PHI[5]-5*THETA);
            Coef[1][2][3]=2*ABS[1]*sin(PHI[1]-1*THETA)+2*ABS[3]*sin(PHI[3]-3*THETA)-10*ABS[5]*sin(PHI[5]-5*THETA);
            Coef[1][1][4]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA);
            Coef[1][0][5]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA);
        }

// 6 -----
        if(ORDER >  5.5){
            Z[2][0]=(15*Coef[0][6][0]+  Coef[0][4][2]-  Coef[0][2][4]-15*Coef[0][0][6])/32.0;
            Z[2][1]=( 5*Coef[0][5][1]+3*Coef[0][3][3]+5*Coef[0][1][5])/32.0;
            Z[4][0]=( 3*Coef[0][6][0]-  Coef[0][4][2]-  Coef[0][2][4]+ 3*Coef[0][0][6])/32.0*2.0;
            Z[4][1]=( 4*Coef[0][5][1]+0*Coef[0][3][3]-4*Coef[0][1][5])/32.0;
            Z[6][0]=( 1*Coef[0][6][0]-  Coef[0][4][2]+  Coef[0][2][4]-   Coef[0][0][6])/32.0;
            Z[6][1]=( 1*Coef[0][5][1]-1*Coef[0][3][3]+1*Coef[0][1][5])/32.0;
            ABS[0]= ( 5*Coef[0][6][0]+  Coef[0][4][2]+  Coef[0][2][4]+ 5*Coef[0][0][6])/32.0*2.0;
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            ABS[6]=hypot(Z[6][1],Z[6][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            PHI[6]=atan2(Z[6][1],Z[6][0]);
            Coef[1][6][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA)+ 1*ABS[6]*cos(PHI[6]-6*THETA);
            Coef[1][5][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA);
            Coef[1][4][2]=3*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)-5*ABS[4]*cos(PHI[4]-4*THETA)-15*ABS[6]*cos(PHI[6]-6*THETA);
            Coef[1][3][3]=0*ABS[0]+4*ABS[2]*sin(PHI[2]-2*THETA)+0*ABS[4]*sin(PHI[4]-4*THETA)-20*ABS[6]*sin(PHI[6]-6*THETA);
            Coef[1][2][4]=3*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)-5*ABS[4]*cos(PHI[4]-4*THETA)+15*ABS[6]*cos(PHI[6]-6*THETA);
            Coef[1][1][5]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)-4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA);
            Coef[1][0][6]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA)- 1*ABS[6]*cos(PHI[6]-6*THETA);
        }

// 7 -----
        if(ORDER >  6.5){
            Z[1][0]=(35*Coef[0][7][0]+5*Coef[0][5][2]+3*Coef[0][3][4]+ 5*Coef[0][1][6])/64.0;
            Z[1][1]=( 5*Coef[0][6][1]+3*Coef[0][4][3]+5*Coef[0][2][5]+35*Coef[0][0][7])/64.0;
            Z[3][0]=(21*Coef[0][7][0]-1*Coef[0][5][2]-3*Coef[0][3][4]- 9*Coef[0][1][6])/64.0;
            Z[3][1]=( 9*Coef[0][6][1]+3*Coef[0][4][3]+1*Coef[0][2][5]-21*Coef[0][0][7])/64.0;
            Z[5][0]=( 7*Coef[0][7][0]-3*Coef[0][5][2]-1*Coef[0][3][4]+ 5*Coef[0][1][6])/64.0;
            Z[5][1]=( 5*Coef[0][6][1]-1*Coef[0][4][3]-3*Coef[0][2][5]+ 7*Coef[0][0][7])/64.0;
            Z[7][0]=( 1*Coef[0][7][0]-1*Coef[0][5][2]+1*Coef[0][3][4]- 1*Coef[0][1][6])/64.0;
            Z[7][1]=( 1*Coef[0][6][1]-1*Coef[0][4][3]+1*Coef[0][2][5]- 1*Coef[0][0][7])/64.0;
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            ABS[5]=hypot(Z[5][1],Z[5][0]);
            ABS[7]=hypot(Z[7][1],Z[7][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            PHI[5]=atan2(Z[5][1],Z[5][0]);
            PHI[7]=atan2(Z[7][1],Z[7][0]);
            Coef[1][7][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA)+ 1*ABS[7]*cos(PHI[7]-7*THETA);
            Coef[1][6][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA)+ 7*ABS[7]*sin(PHI[7]-7*THETA);
            Coef[1][5][2]=3*ABS[1]*cos(PHI[1]-1*THETA)-1*ABS[3]*cos(PHI[3]-3*THETA)- 9*ABS[5]*cos(PHI[5]-5*THETA)-21*ABS[7]*cos(PHI[7]-7*THETA);
            Coef[1][4][3]=3*ABS[1]*sin(PHI[1]-1*THETA)+5*ABS[3]*sin(PHI[3]-3*THETA)- 5*ABS[5]*sin(PHI[5]-5*THETA)-35*ABS[7]*sin(PHI[7]-7*THETA);
            Coef[1][3][4]=3*ABS[1]*cos(PHI[1]-1*THETA)-5*ABS[3]*cos(PHI[3]-3*THETA)- 5*ABS[5]*cos(PHI[5]-5*THETA)+35*ABS[7]*cos(PHI[7]-7*THETA);
            Coef[1][2][5]=3*ABS[1]*sin(PHI[1]-1*THETA)+1*ABS[3]*sin(PHI[3]-3*THETA)- 9*ABS[5]*sin(PHI[5]-5*THETA)+21*ABS[7]*sin(PHI[7]-7*THETA);
            Coef[1][1][6]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA)- 7*ABS[7]*cos(PHI[7]-7*THETA);
            Coef[1][0][7]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA)- 1*ABS[7]*sin(PHI[7]-7*THETA);
        }

// 8 -----
        if(ORDER >  7.5){
            Z[2][0]=(56*Coef[0][8][0]+4*Coef[0][6][2]+0*Coef[0][4][4]- 4*Coef[0][2][6]-56*Coef[0][0][8])/128.0;
            Z[2][1]=(14*Coef[0][7][1]+6*Coef[0][5][3]+6*Coef[0][3][5]+14*Coef[0][1][7])/128.0;
            Z[4][0]=(28*Coef[0][8][0]-4*Coef[0][6][2]-4*Coef[0][4][4]- 4*Coef[0][2][6]+28*Coef[0][0][8])/128.0;
            Z[4][1]=(14*Coef[0][7][1]+2*Coef[0][5][3]-2*Coef[0][3][5]-14*Coef[0][1][7])/128.0;
            Z[6][0]=( 8*Coef[0][8][0]-4*Coef[0][6][2]+0*Coef[0][4][4]+ 4*Coef[0][2][6]- 8*Coef[0][0][8])/128.0;
            Z[6][1]=( 6*Coef[0][7][1]-2*Coef[0][5][3]-2*Coef[0][3][5]+ 6*Coef[0][1][7])/128.0;
            Z[8][0]=( 1*Coef[0][8][0]-1*Coef[0][6][2]+1*Coef[0][4][4]- 1*Coef[0][2][6]+ 1*Coef[0][0][8])/128.0;
            Z[8][1]=( 1*Coef[0][7][1]-1*Coef[0][5][3]+1*Coef[0][3][5]- 1*Coef[0][1][7])/128.0;
            ABS[0]= (35*Coef[0][8][0]+5*Coef[0][6][2]+3*Coef[0][4][4]+ 5*Coef[0][2][6]+35*Coef[0][0][8])/128.0;
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            ABS[6]=hypot(Z[6][1],Z[6][0]);
            ABS[8]=hypot(Z[8][1],Z[8][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            PHI[6]=atan2(Z[6][1],Z[6][0]);
            PHI[8]=atan2(Z[8][1],Z[8][0]);
            Coef[1][8][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+ 1*ABS[4]*cos(PHI[4]-4*THETA)+ 1*ABS[6]*cos(PHI[6]-6*THETA)+ 1*ABS[8]*cos(PHI[8]-8*THETA);
            Coef[1][7][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+ 4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA)+ 8*ABS[8]*sin(PHI[8]-8*THETA);
            Coef[1][6][2]=4*ABS[0]+2*ABS[2]*cos(PHI[2]-2*THETA)- 4*ABS[4]*cos(PHI[4]-4*THETA)-14*ABS[6]*cos(PHI[6]-6*THETA)-28*ABS[8]*cos(PHI[8]-8*THETA);
            Coef[1][5][3]=0*ABS[0]+6*ABS[2]*sin(PHI[2]-2*THETA)+ 4*ABS[4]*sin(PHI[4]-4*THETA)-14*ABS[6]*sin(PHI[6]-6*THETA)-56*ABS[8]*sin(PHI[8]-8*THETA);
            Coef[1][4][4]=6*ABS[0]+0*ABS[2]*cos(PHI[2]-2*THETA)-10*ABS[4]*cos(PHI[4]-4*THETA)+ 0*ABS[6]*cos(PHI[6]-6*THETA)+70*ABS[8]*cos(PHI[8]-8*THETA);
            Coef[1][3][5]=0*ABS[0]+6*ABS[2]*sin(PHI[2]-2*THETA)- 4*ABS[4]*sin(PHI[4]-4*THETA)-14*ABS[6]*sin(PHI[6]-6*THETA)+56*ABS[8]*sin(PHI[8]-8*THETA);
            Coef[1][2][6]=4*ABS[0]-2*ABS[2]*cos(PHI[2]-2*THETA)- 4*ABS[4]*cos(PHI[4]-4*THETA)+14*ABS[6]*cos(PHI[6]-6*THETA)-28*ABS[8]*cos(PHI[8]-8*THETA);
            Coef[1][1][7]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)- 4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA)- 8*ABS[8]*sin(PHI[8]-8*THETA);
            Coef[1][0][8]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+ 1*ABS[4]*cos(PHI[4]-4*THETA)- 1*ABS[6]*cos(PHI[6]-6*THETA)+ 1*ABS[8]*cos(PHI[8]-8*THETA);
        }

// 9 -----
        if(ORDER >  8.5){
            Z[1][0]=(126*Coef[0][9][0]+14*Coef[0][7][2]+6*Coef[0][5][4]+ 6*Coef[0][3][6]+ 14*Coef[0][1][8])/256.0;
            Z[1][1]=( 14*Coef[0][8][1]+ 6*Coef[0][6][3]+6*Coef[0][4][5]+14*Coef[0][2][7]+126*Coef[0][0][9])/256.0;
            Z[3][0]=( 84*Coef[0][9][0]+ 0*Coef[0][7][2]-4*Coef[0][5][4]- 8*Coef[0][3][6]- 28*Coef[0][1][8])/256.0;
            Z[3][1]=( 28*Coef[0][8][1]+ 8*Coef[0][6][3]+4*Coef[0][4][5]+ 0*Coef[0][2][7]- 84*Coef[0][0][9])/256.0;
            Z[5][0]=( 36*Coef[0][9][0]- 8*Coef[0][7][2]-4*Coef[0][5][4]+ 0*Coef[0][3][6]+ 20*Coef[0][1][8])/256.0;
            Z[5][1]=( 20*Coef[0][8][1]- 0*Coef[0][6][3]-4*Coef[0][4][5]- 8*Coef[0][2][7]+ 36*Coef[0][0][9])/256.0;
            Z[7][0]=(  9*Coef[0][9][0]- 5*Coef[0][7][2]+1*Coef[0][5][4]+ 3*Coef[0][3][6]-  7*Coef[0][1][8])/256.0;
            Z[7][1]=(  7*Coef[0][8][1]- 3*Coef[0][6][3]-1*Coef[0][4][5]+ 5*Coef[0][2][7]-  9*Coef[0][0][9])/256.0;
            Z[9][0]=(  1*Coef[0][9][0]- 1*Coef[0][7][2]+1*Coef[0][5][4]- 1*Coef[0][3][6]+  1*Coef[0][1][8])/256.0;
            Z[9][1]=(  1*Coef[0][8][1]- 1*Coef[0][6][3]+1*Coef[0][4][5]- 1*Coef[0][2][7]+  1*Coef[0][0][9])/256.0;
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            ABS[5]=hypot(Z[5][1],Z[5][0]);
            ABS[7]=hypot(Z[7][1],Z[7][0]);
            ABS[9]=hypot(Z[9][1],Z[9][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            PHI[5]=atan2(Z[5][1],Z[5][0]);
            PHI[7]=atan2(Z[7][1],Z[7][0]);
            PHI[9]=atan2(Z[9][1],Z[9][0]);
            Coef[1][9][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA)+ 1*ABS[7]*cos(PHI[7]-7*THETA)+  1*ABS[9]*cos(PHI[9]-9*THETA);
            Coef[1][8][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA)+ 7*ABS[7]*sin(PHI[7]-7*THETA)+  9*ABS[9]*sin(PHI[9]-9*THETA);
            Coef[1][7][2]=4*ABS[1]*cos(PHI[1]-1*THETA)+0*ABS[3]*cos(PHI[3]-3*THETA)- 8*ABS[5]*cos(PHI[5]-5*THETA)-20*ABS[7]*cos(PHI[7]-7*THETA)- 36*ABS[9]*cos(PHI[9]-9*THETA);
            Coef[1][6][3]=4*ABS[1]*sin(PHI[1]-1*THETA)+8*ABS[3]*sin(PHI[3]-3*THETA)+ 0*ABS[5]*sin(PHI[5]-5*THETA)-28*ABS[7]*sin(PHI[7]-7*THETA)- 84*ABS[9]*sin(PHI[9]-9*THETA);
            Coef[1][5][4]=6*ABS[1]*cos(PHI[1]-1*THETA)-6*ABS[3]*cos(PHI[3]-3*THETA)-14*ABS[5]*cos(PHI[5]-5*THETA)+14*ABS[7]*cos(PHI[7]-7*THETA)+126*ABS[9]*cos(PHI[9]-9*THETA);
            Coef[1][4][5]=6*ABS[1]*sin(PHI[1]-1*THETA)+6*ABS[3]*sin(PHI[3]-3*THETA)-14*ABS[5]*sin(PHI[5]-5*THETA)-14*ABS[7]*sin(PHI[7]-7*THETA)+126*ABS[9]*sin(PHI[9]-9*THETA);
            Coef[1][3][6]=4*ABS[1]*cos(PHI[1]-1*THETA)-8*ABS[3]*cos(PHI[3]-3*THETA)+ 0*ABS[5]*cos(PHI[5]-5*THETA)+28*ABS[7]*cos(PHI[7]-7*THETA)- 84*ABS[9]*cos(PHI[9]-9*THETA);
            Coef[1][2][7]=4*ABS[1]*sin(PHI[1]-1*THETA)+0*ABS[3]*sin(PHI[3]-3*THETA)- 8*ABS[5]*sin(PHI[5]-5*THETA)+20*ABS[7]*sin(PHI[7]-7*THETA)- 36*ABS[9]*sin(PHI[9]-9*THETA);
            Coef[1][1][8]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA)- 7*ABS[7]*cos(PHI[7]-7*THETA)+  9*ABS[9]*cos(PHI[9]-9*THETA);
            Coef[1][0][9]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA)- 1*ABS[7]*sin(PHI[7]-7*THETA)+  1*ABS[9]*sin(PHI[9]-9*THETA);
        }


    ij=0;
    for(i=0;i<ORDER+1;i++)
    for(j=0;j<ORDER+1;j++)
    if(i+j<ORDER+1){
        OutCoef[ij]=Coef[1][i][j];
        ij++;
    }
//--------------------------------------------------
    F_DELdouble3(2,ORDER+1,Coef);

}
#define INFMIN pow(10.0,-10.0)
void    F_GaussUnit(int srandNUM, int RNDNUM, double *RNDSET){
        int NUM,DIV;
        double RNDValue,RNDValue2;
        srand(srandNUM);

        for(NUM=0;NUM<RNDNUM;NUM++)
        RNDSET[NUM]=0;

        NUM=0;
        DIV=1000000;
        for(;;){
                RNDValue =10.0/DIV*(rand()%(DIV*2)-DIV);
                RNDValue2=1.0/DIV*(rand()%DIV);
                if(RNDValue2>INFMIN)
                if(RNDValue2<exp(-RNDValue*RNDValue)-exp(-10*10)){
                        RNDSET[NUM]=RNDValue*sqrt(2);
                        NUM++;
                }
                if(NUM > RNDNUM-0.5)
                break;
        }
}
#undef INFMIN
