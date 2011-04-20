//------------------------------------------------------------
//WCS_TANSIP_SUB.cc
//Sub routines
//
//Last modification : 2010/04/01
//------------------------------------------------------------
#include<cmath>
//#include "hsc/meas/tansip/WCS_TANSIP.h"

#define PI (4*atan(1.0))
#define LP 180
#define INFMIN pow(10,-10)

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

      Coef2 = new double*[ORDER+1];
    dxCoef2 = new double*[ORDER+1];
    dyCoef2 = new double*[ORDER+1];
    for(i=0;i<ORDER+1;i++){
      Coef2[i] = new double[ORDER+1];
    dxCoef2[i] = new double[ORDER+1];
    dyCoef2[i] = new double[ORDER+1];
    for(j=0;j<ORDER+1;j++){
      Coef2[i][j] = 0;
    dxCoef2[i][j] = 0;
    dyCoef2[i][j] = 0;
    }}

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
 
    for(i=0;i<ORDER+1;i++){
    delete []   Coef2[i];
    delete [] dxCoef2[i];
    delete [] dyCoef2[i];
    }
    delete []   Coef2;
    delete [] dxCoef2;
    delete [] dyCoef2;
}
void    F_INTSIP(int ORDER,double *dxCoef,double *dyCoef,double *Coef){
    int i,j,ij,CoefNUM;
    double **dxCoef2,**dyCoef2,**xCoef2,**yCoef2,**Coef2;

    CoefNUM=(int)((ORDER+1)*(ORDER+2)+0.1);

    dxCoef2=new double*[ORDER+1];
    dyCoef2=new double*[ORDER+1];
     xCoef2=new double*[ORDER+1];
     yCoef2=new double*[ORDER+1];
      Coef2=new double*[ORDER+1];
    for(i=0;i<ORDER+1;i++){
    dxCoef2[i]=new double[ORDER+1];
    dyCoef2[i]=new double[ORDER+1];
     xCoef2[i]=new double[ORDER+1];
     yCoef2[i]=new double[ORDER+1];
      Coef2[i]=new double[ORDER+1];
    for(j=0;j<ORDER+1;j++){
    dxCoef2[i][j]=0;
    dyCoef2[i][j]=0;
     xCoef2[i][j]=0;
     yCoef2[i][j]=0;
      Coef2[i][j]=0;
    }}

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

    for(i=0;i<ORDER+1;i++){
    delete []   Coef2[i];
    delete []  xCoef2[i];
    delete []  yCoef2[i];
    delete [] dxCoef2[i];
    delete [] dyCoef2[i];
    }
    delete []   Coef2;
    delete []  xCoef2;
    delete []  yCoef2;
    delete [] dxCoef2;
    delete [] dyCoef2;
}
#undef LP
#undef PI
#undef INFMIN
