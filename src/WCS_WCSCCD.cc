//------------------------------------------------------------
//WCS_WCSCCD.cc
//main program for wcs in pipeline
//
//Last modification : 2011/02/22
//------------------------------------------------------------
#include<iostream>
#include<fstream>//test
#include<cmath>
#include "hsc/meas/tansip/WCS_PL_MAIN.h"
#include "hsc/meas/tansip/WCS_TANSIP.h"

#define PI (4*atan(1.0))
using namespace std;
void    F_SIPROT(CL_APROP,CL_CPROP *,CL_CSIP *,double **Coef[2],double **CoefP[2]);
void    F_SIP(int FR,int Order,double x[],double xSIP[],double CR[],double *SIP[2]);
void    F_PIXWCS_TAN(double x[],double CR[],double CD[][2]);
void    F_WCSPIX_TAN(double x[],double CR[],double CD[][2]);
void    F_WCS_WCSCCD(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP* CSIP){
    int i,j,ij,ID;
    double **Coef[2],**CoefP[2];

    Coef[0]  = new double*[APROP.SIP_ORDER+1];
    Coef[1]  = new double*[APROP.SIP_ORDER+1];
    CoefP[0] = new double*[APROP.SIP_P_ORDER+1];
    CoefP[1] = new double*[APROP.SIP_P_ORDER+1];

    for(i=0;i<APROP.SIP_ORDER+1;i++){
        Coef[0][i]  = new double[APROP.SIP_ORDER+1];
        Coef[1][i]  = new double[APROP.SIP_ORDER+1];
    }
    for(i=0;i<APROP.SIP_P_ORDER+1;i++){
        CoefP[0][i] = new double[APROP.SIP_P_ORDER+1];
        CoefP[1][i] = new double[APROP.SIP_P_ORDER+1];
    }

    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    Coef[0][i][j]=Coef[1][i][j]=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    CoefP[0][i][j]=CoefP[1][i][j]=0;


// SIP -> Polynomial --------------------------------------------------
cout << endl;
cout << "--- F_WCS_TANSIP : Global SIP TO Polynomial ---" << endl;
    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        Coef[0][i][j] =CSIP[APROP.CCDNUM].CD[0][0]*CSIP[APROP.CCDNUM].SIP_AB[0][ij]+CSIP[APROP.CCDNUM].CD[0][1] *CSIP[APROP.CCDNUM].SIP_AB[1][ij];
        Coef[1][i][j] =CSIP[APROP.CCDNUM].CD[1][0]*CSIP[APROP.CCDNUM].SIP_AB[0][ij]+CSIP[APROP.CCDNUM].CD[1][1] *CSIP[APROP.CCDNUM].SIP_AB[1][ij];
        ij++;
    }
    Coef[0][1][0]+=CSIP[APROP.CCDNUM].CD[0][0];
    Coef[1][0][1]+=CSIP[APROP.CCDNUM].CD[1][1];

    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        CoefP[0][i][j]=CSIP[APROP.CCDNUM].CD[0][0]*CSIP[APROP.CCDNUM].SIP_ABP[0][ij]+CSIP[APROP.CCDNUM].CD[0][1]*CSIP[APROP.CCDNUM].SIP_ABP[1][ij];
        CoefP[1][i][j]=CSIP[APROP.CCDNUM].CD[1][0]*CSIP[APROP.CCDNUM].SIP_ABP[0][ij]+CSIP[APROP.CCDNUM].CD[1][1]*CSIP[APROP.CCDNUM].SIP_ABP[1][ij];
        ij++;	
    }
    CoefP[0][1][0]+=CSIP[APROP.CCDNUM].CD[0][0];
    CoefP[1][0][1]+=CSIP[APROP.CCDNUM].CD[1][1];

// WCS CCD --------------------------------------------------
cout << "--- F_WCS_TANSIP : Polynomial TO CCD's SIP ---" << endl;

    for(ID=0;ID<APROP.CCDNUM;ID++){
        F_SIPROT(APROP,&CPROP[ID],&CSIP[ID],Coef,CoefP);

        CSIP[ID].ID=ID;
        CSIP[ID].FITNUM=CPROP[ID].NUMREF;
        CSIP[ID].CRVAL[0]=CSIP[APROP.CCDNUM].CRVAL[0];
        CSIP[ID].CRVAL[1]=CSIP[APROP.CCDNUM].CRVAL[1];
        CSIP[ID].CRPIX[0]=-(CPROP[ID].GLOB_POS[0]-CSIP[APROP.CCDNUM].CRPIX[0])*cos(CPROP[ID].GLOB_POS[2]/180.0*PI)-(CPROP[ID].GLOB_POS[1]-CSIP[APROP.CCDNUM].CRPIX[1])*sin(CPROP[ID].GLOB_POS[2]/180.0*PI);
        CSIP[ID].CRPIX[1]=-(CPROP[ID].GLOB_POS[1]-CSIP[APROP.CCDNUM].CRPIX[1])*cos(CPROP[ID].GLOB_POS[2]/180.0*PI)+(CPROP[ID].GLOB_POS[0]-CSIP[APROP.CCDNUM].CRPIX[0])*sin(CPROP[ID].GLOB_POS[2]/180.0*PI);
        CSIP[ID].SIP_AB_ORDER =CSIP[APROP.CCDNUM].SIP_AB_ORDER;
        CSIP[ID].SIP_ABP_ORDER=CSIP[APROP.CCDNUM].SIP_ABP_ORDER;
    }
// AVE RMS --------------------------------------------------
cout << "--- CALC. RMS ---" << endl;
    int k,l;
    double ****SUM;
    double x[4],Lx[4],xSIP[4],LxSIP[4],CR[4],RADEC[4],LRADEC[4];
    SUM = new double***[APROP.CCDNUM+1];
    for(i=0;i<APROP.CCDNUM+1;i++){
    SUM[i] = new double**[2];
    for(j=0;j<2;j++){
    SUM[i][j] = new double*[2];
    for(k=0;k<2;k++)
    SUM[i][j][k] = new double[3];
    }}

    for(i=0;i<APROP.CCDNUM+1;i++)
    for(j=0;j<2;j++)
    for(k=0;k<2;k++)
    for(l=0;l<3;l++)
    SUM[i][j][k][l]=0;

//ofstream fout,fLout,f1out;
//fout.open("test/fit.dat");
//fLout.open("test/fitL.dat");
//f1out.open("test/fit1.dat");
double *SIP1[2];
SIP1[0] = new double[3];
SIP1[1] = new double[3];
SIP1[0][0]=SIP1[0][1]=SIP1[0][2]=SIP1[1][0]=SIP1[1][1]=SIP1[1][2]=0;
double *SIPN[2];
SIPN[0] = new double[10];
SIPN[1] = new double[10];
for(i=0;i<10;i++)
SIPN[0][i]=SIPN[1][i]=0;
    for(i=0;i<APROP.NUMREFALL;i++)
    if(PAIR[i].FLAG==1){
        Lx[0]=PAIR[i].xL;
        Lx[1]=PAIR[i].yL;
        Lx[2]=0;
        Lx[3]=0;
        x[0]=PAIR[i].xG;
        x[1]=PAIR[i].yG;
        x[2]=0;
        x[3]=0;
        LRADEC[0]=0;
        LRADEC[1]=0;
        LRADEC[2]=PAIR[i].RA;
        LRADEC[3]=PAIR[i].DEC;
        RADEC[0]=0;
        RADEC[1]=0;
        RADEC[2]=PAIR[i].RA;
        RADEC[3]=PAIR[i].DEC;
        CR[0]=CSIP[APROP.CCDNUM].CRPIX[0];
        CR[1]=CSIP[APROP.CCDNUM].CRPIX[1];
        CR[2]=CSIP[APROP.CCDNUM].CRVAL[0];
        CR[3]=CSIP[APROP.CCDNUM].CRVAL[1];
        F_SIP(0,APROP.SIP_ORDER,x,xSIP,CR,CSIP[APROP.CCDNUM].SIP_AB);//Global
        F_WCSPIX_TAN(RADEC,CR,CSIP[APROP.CCDNUM].CD);
//if(PAIR[i].FLAG == 1)
//fout << fixed << x[0] << "	" << x[1] << "	" << xSIP[0]-RADEC[0] << "	" << xSIP[1]-RADEC[1] << "	" << xSIP[0] << "	" << xSIP[1] << "	" << RADEC[0] << "	" << RADEC[1] << endl;
//        F_SIP(0,1,x,xSIP,CR,SIP1);//Global
//        F_SIP(0,APROP.SIP_ORDER,x,xSIP,CR,SIPN);//Global
//        F_WCSPIX_TAN(RADEC,CR,CSIP[APROP.CCDNUM].CD);
//if(PAIR[i].FLAG == 1)
//f1out << fixed << x[0] << "	" << x[1] << "	" << xSIP[0]-RADEC[0] << "	" << xSIP[1]-RADEC[1] << "	" << xSIP[0] << "	" << xSIP[1] << "	" << RADEC[0] << "	" << RADEC[1] << endl;
        CR[0]=CSIP[PAIR[i].CHIPID].CRPIX[0];
        CR[1]=CSIP[PAIR[i].CHIPID].CRPIX[1];
        CR[2]=CSIP[PAIR[i].CHIPID].CRVAL[0];
        CR[3]=CSIP[PAIR[i].CHIPID].CRVAL[1];
        F_SIP(0,APROP.SIP_ORDER,Lx,LxSIP,CR,CSIP[PAIR[i].CHIPID].SIP_AB);//Global
        F_WCSPIX_TAN(LRADEC,CR,CSIP[PAIR[i].CHIPID].CD);
//if(PAIR[i].FLAG == 1)
//fLout << x[0] << "	" << x[1] << "	" << LxSIP[0]-LRADEC[0] << "	" << LxSIP[1]-LRADEC[1] << endl;

        SUM[PAIR[i].CHIPID][0][0][0]+=1;//Local
        SUM[PAIR[i].CHIPID][0][0][1]+=(LxSIP[0]-LRADEC[0]);
        SUM[PAIR[i].CHIPID][0][0][2]+=(LxSIP[0]-LRADEC[0])*(LxSIP[0]-LRADEC[0]);
        SUM[PAIR[i].CHIPID][0][1][0]+=1;
        SUM[PAIR[i].CHIPID][0][1][1]+=(LxSIP[1]-LRADEC[1]);
        SUM[PAIR[i].CHIPID][0][1][2]+=(LxSIP[1]-LRADEC[1])*(LxSIP[1]-LRADEC[1]);
        SUM[APROP.CCDNUM][1][0][0]+=1;//Global
        SUM[APROP.CCDNUM][1][0][1]+=(xSIP[0]-RADEC[0]);
        SUM[APROP.CCDNUM][1][0][2]+=(xSIP[0]-RADEC[0])*(xSIP[0]-RADEC[0]);
        SUM[APROP.CCDNUM][1][1][0]+=1;
        SUM[APROP.CCDNUM][1][1][1]+=(xSIP[1]-RADEC[1]);
        SUM[APROP.CCDNUM][1][1][2]+=(xSIP[1]-RADEC[1])*(xSIP[1]-RADEC[1]);
    }

    for(ID=0;ID<APROP.CCDNUM;ID++){
        CSIP[ID].SIP_AB_AVE[0]=SUM[ID][0][0][1]/SUM[ID][0][0][0];
        CSIP[ID].SIP_AB_AVE[1]=SUM[ID][0][1][1]/SUM[ID][0][1][0];
        CSIP[ID].SIP_AB_RMS[0]=sqrt((SUM[ID][0][0][2]-SUM[ID][0][0][1]*SUM[ID][0][0][1]/SUM[ID][0][0][0])/(SUM[ID][0][0][0]-1));
        CSIP[ID].SIP_AB_RMS[1]=sqrt((SUM[ID][0][0][2]-SUM[ID][0][1][1]*SUM[ID][0][1][1]/SUM[ID][0][1][0])/(SUM[ID][0][1][0]-1));
    }
        ID=APROP.CCDNUM;
        CSIP[ID].SIP_AB_AVE[0]=SUM[ID][1][0][1]/SUM[ID][1][0][0];
        CSIP[ID].SIP_AB_AVE[1]=SUM[ID][1][1][1]/SUM[ID][1][1][0];
        CSIP[ID].SIP_AB_RMS[0]=sqrt((SUM[ID][1][0][2]-SUM[ID][1][0][1]*SUM[ID][1][0][1]/SUM[ID][1][0][0])/(SUM[ID][1][0][0]-1));
        CSIP[ID].SIP_AB_RMS[1]=sqrt((SUM[ID][1][0][2]-SUM[ID][1][1][1]*SUM[ID][1][1][1]/SUM[ID][1][1][0])/(SUM[ID][1][1][0]-1));
cout << "AVE of RESIDUAL x : " << CSIP[ID].SIP_AB_AVE[0] << " (pix)" <<endl;
cout << "AVE of RESIDUAL y : " << CSIP[ID].SIP_AB_AVE[1] << " (pix)" <<endl;
cout << "RMS of RESIDUAL x : " << CSIP[ID].SIP_AB_RMS[0] << " (pix)" <<endl;
cout << "RMS of RESIDUAL y : " << CSIP[ID].SIP_AB_RMS[1] << " (pix)" <<endl;   
    for(i=0;i<APROP.CCDNUM+1;i++)
    for(j=0;j<2;j++)
    for(k=0;k<2;k++)
    delete [] SUM[i][j][k];
    for(i=0;i<APROP.CCDNUM+1;i++)
    for(j=0;j<2;j++)
    delete [] SUM[i][j];
    for(i=0;i<APROP.CCDNUM+1;i++)
    delete [] SUM[i];
    delete [] SUM;
//--------------------------------------------------
    for(i=0;i<APROP.SIP_ORDER+1;i++){
         delete [] Coef[0][i];
         delete [] Coef[1][i];
    }
    for(i=0;i<APROP.SIP_P_ORDER+1;i++){
         delete [] CoefP[0][i];
         delete [] CoefP[1][i];
    }
    delete [] Coef[0];
    delete [] Coef[1];
    delete [] CoefP[0];
    delete [] CoefP[1];

}
void    F_SIPROT(CL_APROP APROP,CL_CPROP *CPROP,CL_CSIP *CSIP,double **Coef[2],double **CoefP[2]){
    int i,j,ij,xy;
    double **CoefCCD[2],**CoefPCCD[2];

    CoefCCD[0]  = new double*[APROP.SIP_ORDER+1];
    CoefCCD[1]  = new double*[APROP.SIP_ORDER+1];
    CoefPCCD[0] = new double*[APROP.SIP_P_ORDER+1];
    CoefPCCD[1] = new double*[APROP.SIP_P_ORDER+1];

    for(i=0;i<APROP.SIP_ORDER+1;i++){
        CoefCCD[0][i]  = new double[APROP.SIP_ORDER+1];
        CoefCCD[1][i]  = new double[APROP.SIP_ORDER+1];
    }
    for(i=0;i<APROP.SIP_P_ORDER+1;i++){
        CoefPCCD[0][i] = new double[APROP.SIP_P_ORDER+1];
        CoefPCCD[1][i] = new double[APROP.SIP_P_ORDER+1];
    }

//--------------------------------------------------

    double ABS[10],PHI[10],Z[10][2],THETA;
    THETA=(CPROP->GLOB_POS[2])*PI/180;

for(i=0;i<2;i++)
for(j=0;j<APROP.SIP_ORDER+1;j++)
for(ij=0;ij<APROP.SIP_ORDER+1;ij++){
CoefCCD[i][j][ij]=Coef[i][j][ij];
CoefPCCD[i][j][ij]=CoefP[i][j][ij];
}   

   for(xy=0;xy<2;xy++){
// 0 -----
        if(APROP.SIP_ORDER   > -0.5)
        CoefCCD[xy][0][0] =Coef[xy][0][0];

        if(APROP.SIP_P_ORDER > -0.5)
        CoefPCCD[xy][0][0]=CoefP[xy][0][0];
// 1 -----
        if(APROP.SIP_ORDER   >  0.5){
            ABS[1]=hypot(Coef[xy][0][1],Coef[xy][1][0]);
            PHI[1]=atan2(Coef[xy][0][1],Coef[xy][1][0]);
            CoefCCD[xy][1][0]=ABS[1]*cos(PHI[1]-1*THETA);
            CoefCCD[xy][0][1]=ABS[1]*sin(PHI[1]-1*THETA);
        }

        if(APROP.SIP_P_ORDER >  0.5){
            ABS[1]=hypot(CoefP[xy][0][1],CoefP[xy][1][0]);
            PHI[1]=atan2(CoefP[xy][0][1],CoefP[xy][1][0]);
            CoefPCCD[xy][1][0]=ABS[1]*cos(PHI[1]-1*THETA);
            CoefPCCD[xy][0][1]=ABS[1]*sin(PHI[1]-1*THETA);
        }

// 2 -----
        if(APROP.SIP_ORDER   >  1.5){
            Z[2][0]=0.5*(Coef[xy][2][0]-Coef[xy][0][2]);
            Z[2][1]=0.5*(Coef[xy][1][1]);
            ABS[0]=0.5*(Coef[xy][2][0]+Coef[xy][0][2]);
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            CoefCCD[xy][2][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA);
            CoefCCD[xy][1][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA);
            CoefCCD[xy][0][2]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA);
        }

        if(APROP.SIP_P_ORDER >  1.5){
            Z[2][0]=0.5*(CoefP[xy][2][0]-CoefP[xy][0][2]);
            Z[2][1]=0.5*(CoefP[xy][1][1]);
            ABS[0]=0.5*(CoefP[xy][2][0]+CoefP[xy][0][2]);
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            CoefPCCD[xy][2][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA);
            CoefPCCD[xy][1][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA);
            CoefPCCD[xy][0][2]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA);
        }

// 3 -----
        if(APROP.SIP_ORDER   >  2.5){
            Z[1][0]=0.25*(3*Coef[xy][3][0]+  Coef[xy][1][2]);
            Z[1][1]=0.25*(  Coef[xy][2][1]+3*Coef[xy][0][3]);
            Z[3][0]=0.25*(  Coef[xy][3][0]-  Coef[xy][1][2]);
            Z[3][1]=0.25*(  Coef[xy][2][1]-  Coef[xy][0][3]);
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            CoefCCD[xy][3][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA);
            CoefCCD[xy][2][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA);
            CoefCCD[xy][1][2]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA);
            CoefCCD[xy][0][3]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA);
        }

        if(APROP.SIP_P_ORDER >  2.5){
            Z[1][0]=0.25*(3*CoefP[xy][3][0]+  CoefP[xy][1][2]);
            Z[1][1]=0.25*(  CoefP[xy][2][1]+3*CoefP[xy][0][3]);
            Z[3][0]=0.25*(  CoefP[xy][3][0]-  CoefP[xy][1][2]);
            Z[3][1]=0.25*(  CoefP[xy][2][1]-  CoefP[xy][0][3]);
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            CoefPCCD[xy][3][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA);
            CoefPCCD[xy][2][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA);
            CoefPCCD[xy][1][2]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA);
            CoefPCCD[xy][0][3]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA);
        }

// 4 -----
        if(APROP.SIP_ORDER   >  3.5){
            Z[2][0]=  0.5*(Coef[xy][4][0]-Coef[xy][0][4]);
            Z[2][1]= 0.25*(Coef[xy][3][1]+Coef[xy][1][3]);
            Z[4][0]=0.125*(Coef[xy][4][0]-Coef[xy][2][2]+Coef[xy][0][4]);
            Z[4][1]=0.125*(Coef[xy][3][1]-Coef[xy][1][3]);
            ABS[0]=0.125*(3*Coef[xy][4][0]+Coef[xy][2][2]+3*Coef[xy][0][4]);
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            CoefCCD[xy][4][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA);
            CoefCCD[xy][3][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+4*ABS[4]*sin(PHI[4]-4*THETA);
            CoefCCD[xy][2][2]=2*ABS[0]+0*ABS[2]*cos(PHI[2]-2*THETA)-6*ABS[4]*cos(PHI[4]-4*THETA);
            CoefCCD[xy][1][3]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)-4*ABS[4]*sin(PHI[4]-4*THETA);
            CoefCCD[xy][0][4]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA);
        }

        if(APROP.SIP_P_ORDER >  3.5){
            Z[2][0]=  0.5*(CoefP[xy][4][0]-CoefP[xy][0][4]);
            Z[2][1]= 0.25*(CoefP[xy][3][1]+CoefP[xy][1][3]);
            Z[4][0]=0.125*(CoefP[xy][4][0]-CoefP[xy][2][2]+CoefP[xy][0][4]);
            Z[4][1]=0.125*(CoefP[xy][3][1]-CoefP[xy][1][3]);
            ABS[0]=0.125*(3*CoefP[xy][4][0]+CoefP[xy][2][2]+3*CoefP[xy][0][4]);
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            CoefPCCD[xy][4][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA);
            CoefPCCD[xy][3][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+4*ABS[4]*sin(PHI[4]-4*THETA);
            CoefPCCD[xy][2][2]=2*ABS[0]+0*ABS[2]*cos(PHI[2]-2*THETA)-6*ABS[4]*cos(PHI[4]-4*THETA);
            CoefPCCD[xy][1][3]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)-4*ABS[4]*sin(PHI[4]-4*THETA);
            CoefPCCD[xy][0][4]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA);
        }

// 5 -----
        if(APROP.SIP_ORDER   >  4.5){
            Z[1][0]=(5*Coef[xy][5][0]+  Coef[xy][3][2]+  Coef[xy][1][4])/16.0*2.0;
            Z[1][1]=(  Coef[xy][4][1]+  Coef[xy][2][3]+5*Coef[xy][0][5])/16.0*2.0;
            Z[3][0]=(5*Coef[xy][5][0]-  Coef[xy][3][2]-3*Coef[xy][1][4])/16.0;
            Z[3][1]=(3*Coef[xy][4][1]+  Coef[xy][2][3]-5*Coef[xy][0][5])/16.0;
            Z[5][0]=(  Coef[xy][5][0]-  Coef[xy][3][2]+  Coef[xy][1][4])/16.0;
            Z[5][1]=(  Coef[xy][4][1]-  Coef[xy][2][3]+  Coef[xy][0][5])/16.0;
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            ABS[5]=hypot(Z[5][1],Z[5][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            PHI[5]=atan2(Z[5][1],Z[5][0]);
            CoefCCD[xy][5][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA);
            CoefCCD[xy][4][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA);
            CoefCCD[xy][3][2]=2*ABS[1]*cos(PHI[1]-1*THETA)-2*ABS[3]*cos(PHI[3]-3*THETA)-10*ABS[5]*cos(PHI[5]-5*THETA);
            CoefCCD[xy][2][3]=2*ABS[1]*sin(PHI[1]-1*THETA)+2*ABS[3]*sin(PHI[3]-3*THETA)-10*ABS[5]*sin(PHI[5]-5*THETA);
            CoefCCD[xy][1][4]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA);
            CoefCCD[xy][0][5]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA);
        }

        if(APROP.SIP_P_ORDER >  4.5){
            Z[1][0]=(5*CoefP[xy][5][0]+  CoefP[xy][3][2]+  CoefP[xy][1][4])/16.0*2.0;
            Z[1][1]=(  CoefP[xy][4][1]+  CoefP[xy][2][3]+5*CoefP[xy][0][5])/16.0*2.0;
            Z[3][0]=(5*CoefP[xy][5][0]-  CoefP[xy][3][2]-3*CoefP[xy][1][4])/16.0;
            Z[3][1]=(3*CoefP[xy][4][1]+  CoefP[xy][2][3]-5*CoefP[xy][0][5])/16.0;
            Z[5][0]=(  CoefP[xy][5][0]-  CoefP[xy][3][2]+  CoefP[xy][1][4])/16.0;
            Z[5][1]=(  CoefP[xy][4][1]-  CoefP[xy][2][3]+  CoefP[xy][0][5])/16.0;
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            ABS[5]=hypot(Z[5][1],Z[5][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            PHI[5]=atan2(Z[5][1],Z[5][0]);
            CoefPCCD[xy][5][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA);
            CoefPCCD[xy][4][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA);
            CoefPCCD[xy][3][2]=2*ABS[1]*cos(PHI[1]-1*THETA)-2*ABS[3]*cos(PHI[3]-3*THETA)-10*ABS[5]*cos(PHI[5]-5*THETA);
            CoefPCCD[xy][2][3]=2*ABS[1]*sin(PHI[1]-1*THETA)+2*ABS[3]*sin(PHI[3]-3*THETA)-10*ABS[5]*sin(PHI[5]-5*THETA);
            CoefPCCD[xy][1][4]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA);
            CoefPCCD[xy][0][5]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA);
        }
 

// 6 -----
        if(APROP.SIP_ORDER   >  5.5){
            Z[2][0]=(15*Coef[xy][6][0]+  Coef[xy][4][2]-  Coef[xy][2][4]-15*Coef[xy][0][6])/32.0;
            Z[2][1]=( 5*Coef[xy][5][1]+3*Coef[xy][3][3]+5*Coef[xy][1][5])/32.0;
            Z[4][0]=( 3*Coef[xy][6][0]-  Coef[xy][4][2]-  Coef[xy][2][4]+ 3*Coef[xy][0][6])/32.0*2.0;
            Z[4][1]=( 4*Coef[xy][5][1]+0*Coef[xy][3][3]-4*Coef[xy][1][5])/32.0;
            Z[6][0]=( 1*Coef[xy][6][0]-  Coef[xy][4][2]+  Coef[xy][2][4]-   Coef[xy][0][6])/32.0;
            Z[6][1]=( 1*Coef[xy][5][1]-1*Coef[xy][3][3]+1*Coef[xy][1][5])/32.0;
            ABS[0]= ( 5*Coef[xy][6][0]+  Coef[xy][4][2]+  Coef[xy][2][4]+ 5*Coef[xy][0][6])/32.0*2.0;
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            ABS[6]=hypot(Z[6][1],Z[6][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            PHI[6]=atan2(Z[6][1],Z[6][0]);
            CoefCCD[xy][6][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA)+ 1*ABS[6]*cos(PHI[6]-6*THETA);
            CoefCCD[xy][5][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA);
            CoefCCD[xy][4][2]=3*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)-5*ABS[4]*cos(PHI[4]-4*THETA)-15*ABS[6]*cos(PHI[6]-6*THETA);
            CoefCCD[xy][3][3]=0*ABS[0]+4*ABS[2]*sin(PHI[2]-2*THETA)+0*ABS[4]*sin(PHI[4]-4*THETA)-20*ABS[6]*sin(PHI[6]-6*THETA);
            CoefCCD[xy][2][4]=3*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)-5*ABS[4]*cos(PHI[4]-4*THETA)+15*ABS[6]*cos(PHI[6]-6*THETA);
            CoefCCD[xy][1][5]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)-4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA);
            CoefCCD[xy][0][6]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA)- 1*ABS[6]*cos(PHI[6]-6*THETA);
        }

        if(APROP.SIP_P_ORDER >  5.5){
            Z[2][0]=(15*CoefP[xy][6][0]+  CoefP[xy][4][2]-  CoefP[xy][2][4]-15*CoefP[xy][0][6])/32.0;
            Z[2][1]=( 5*CoefP[xy][5][1]+3*CoefP[xy][3][3]+5*CoefP[xy][1][5])/32.0;
            Z[4][0]=( 3*CoefP[xy][6][0]-  CoefP[xy][4][2]-  CoefP[xy][2][4]+ 3*CoefP[xy][0][6])/32.0*2.0;
            Z[4][1]=( 4*CoefP[xy][5][1]+0*CoefP[xy][3][3]-4*CoefP[xy][1][5])/32.0;
            Z[6][0]=( 1*CoefP[xy][6][0]-  CoefP[xy][4][2]+  CoefP[xy][2][4]-   CoefP[xy][0][6])/32.0;
            Z[6][1]=( 1*CoefP[xy][5][1]-1*CoefP[xy][3][3]+1*CoefP[xy][1][5])/32.0;
            ABS[0]= ( 5*CoefP[xy][6][0]+  CoefP[xy][4][2]+  CoefP[xy][2][4]+ 5*CoefP[xy][0][6])/32.0*2.0;
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            ABS[6]=hypot(Z[6][1],Z[6][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            PHI[6]=atan2(Z[6][1],Z[6][0]);
            CoefPCCD[xy][6][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA)+ 1*ABS[6]*cos(PHI[6]-6*THETA);
            CoefPCCD[xy][5][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA);
            CoefPCCD[xy][4][2]=3*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)-5*ABS[4]*cos(PHI[4]-4*THETA)-15*ABS[6]*cos(PHI[6]-6*THETA);
            CoefPCCD[xy][3][3]=0*ABS[0]+4*ABS[2]*sin(PHI[2]-2*THETA)+0*ABS[4]*sin(PHI[4]-4*THETA)-20*ABS[6]*sin(PHI[6]-6*THETA);
            CoefPCCD[xy][2][4]=3*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)-5*ABS[4]*cos(PHI[4]-4*THETA)+15*ABS[6]*cos(PHI[6]-6*THETA);
            CoefPCCD[xy][1][5]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)-4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA);
            CoefPCCD[xy][0][6]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA)- 1*ABS[6]*cos(PHI[6]-6*THETA);
        }

// 7 -----
        if(APROP.SIP_ORDER   >  6.5){
            Z[1][0]=(35*Coef[xy][7][0]+5*Coef[xy][5][2]+3*Coef[xy][3][4]+ 5*Coef[xy][1][6])/64.0;
            Z[1][1]=( 5*Coef[xy][6][1]+3*Coef[xy][4][3]+5*Coef[xy][2][5]+35*Coef[xy][0][7])/64.0;
            Z[3][0]=(21*Coef[xy][7][0]-1*Coef[xy][5][2]-3*Coef[xy][3][4]- 9*Coef[xy][1][6])/64.0;
            Z[3][1]=( 9*Coef[xy][6][1]+3*Coef[xy][4][3]+1*Coef[xy][2][5]-21*Coef[xy][0][7])/64.0;
            Z[5][0]=( 7*Coef[xy][7][0]-3*Coef[xy][5][2]-1*Coef[xy][3][4]+ 5*Coef[xy][1][6])/64.0;
            Z[5][1]=( 5*Coef[xy][6][1]-1*Coef[xy][4][3]-3*Coef[xy][2][5]+ 7*Coef[xy][0][7])/64.0;
            Z[7][0]=( 1*Coef[xy][7][0]-1*Coef[xy][5][2]+1*Coef[xy][3][4]- 1*Coef[xy][1][6])/64.0;
            Z[7][1]=( 1*Coef[xy][6][1]-1*Coef[xy][4][3]+1*Coef[xy][2][5]- 1*Coef[xy][0][7])/64.0;
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            ABS[5]=hypot(Z[5][1],Z[5][0]);
            ABS[7]=hypot(Z[7][1],Z[7][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            PHI[5]=atan2(Z[5][1],Z[5][0]);
            PHI[7]=atan2(Z[7][1],Z[7][0]);
            CoefCCD[xy][7][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA)+ 1*ABS[7]*cos(PHI[7]-7*THETA);
            CoefCCD[xy][6][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA)+ 7*ABS[7]*sin(PHI[7]-7*THETA);
            CoefCCD[xy][5][2]=3*ABS[1]*cos(PHI[1]-1*THETA)-1*ABS[3]*cos(PHI[3]-3*THETA)- 9*ABS[5]*cos(PHI[5]-5*THETA)-21*ABS[7]*cos(PHI[7]-7*THETA);
            CoefCCD[xy][4][3]=3*ABS[1]*sin(PHI[1]-1*THETA)+5*ABS[3]*sin(PHI[3]-3*THETA)- 5*ABS[5]*sin(PHI[5]-5*THETA)-35*ABS[7]*sin(PHI[7]-7*THETA);
            CoefCCD[xy][3][4]=3*ABS[1]*cos(PHI[1]-1*THETA)-5*ABS[3]*cos(PHI[3]-3*THETA)- 5*ABS[5]*cos(PHI[5]-5*THETA)+35*ABS[7]*cos(PHI[7]-7*THETA);
            CoefCCD[xy][2][5]=3*ABS[1]*sin(PHI[1]-1*THETA)+1*ABS[3]*sin(PHI[3]-3*THETA)- 9*ABS[5]*sin(PHI[5]-5*THETA)+21*ABS[7]*sin(PHI[7]-7*THETA);
            CoefCCD[xy][1][6]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA)- 7*ABS[7]*cos(PHI[7]-7*THETA);
            CoefCCD[xy][0][7]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA)- 1*ABS[7]*sin(PHI[7]-7*THETA);
        }

        if(APROP.SIP_P_ORDER   >  6.5){
            Z[1][0]=(35*CoefP[xy][7][0]+5*CoefP[xy][5][2]+3*CoefP[xy][3][4]+ 5*CoefP[xy][1][6])/64.0;
            Z[1][1]=( 5*CoefP[xy][6][1]+3*CoefP[xy][4][3]+5*CoefP[xy][2][5]+35*CoefP[xy][0][7])/64.0;
            Z[3][0]=(21*CoefP[xy][7][0]-1*CoefP[xy][5][2]-3*CoefP[xy][3][4]- 9*CoefP[xy][1][6])/64.0;
            Z[3][1]=( 9*CoefP[xy][6][1]+3*CoefP[xy][4][3]+1*CoefP[xy][2][5]-21*CoefP[xy][0][7])/64.0;
            Z[5][0]=( 7*CoefP[xy][7][0]-3*CoefP[xy][5][2]-1*CoefP[xy][3][4]+ 5*CoefP[xy][1][6])/64.0;
            Z[5][1]=( 5*CoefP[xy][6][1]-1*CoefP[xy][4][3]-3*CoefP[xy][2][5]+ 7*CoefP[xy][0][7])/64.0;
            Z[7][0]=( 1*CoefP[xy][7][0]-1*CoefP[xy][5][2]+1*CoefP[xy][3][4]- 1*CoefP[xy][1][6])/64.0;
            Z[7][1]=( 1*CoefP[xy][6][1]-1*CoefP[xy][4][3]+1*CoefP[xy][2][5]- 1*CoefP[xy][0][7])/64.0;
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            ABS[5]=hypot(Z[5][1],Z[5][0]);
            ABS[7]=hypot(Z[7][1],Z[7][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            PHI[5]=atan2(Z[5][1],Z[5][0]);
            PHI[7]=atan2(Z[7][1],Z[7][0]);
            CoefPCCD[xy][7][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA)+ 1*ABS[7]*cos(PHI[7]-7*THETA);
            CoefPCCD[xy][6][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA)+ 7*ABS[7]*sin(PHI[7]-7*THETA);
            CoefPCCD[xy][5][2]=3*ABS[1]*cos(PHI[1]-1*THETA)-1*ABS[3]*cos(PHI[3]-3*THETA)- 9*ABS[5]*cos(PHI[5]-5*THETA)-21*ABS[7]*cos(PHI[7]-7*THETA);
            CoefPCCD[xy][4][3]=3*ABS[1]*sin(PHI[1]-1*THETA)+5*ABS[3]*sin(PHI[3]-3*THETA)- 5*ABS[5]*sin(PHI[5]-5*THETA)-35*ABS[7]*sin(PHI[7]-7*THETA);
            CoefPCCD[xy][3][4]=3*ABS[1]*cos(PHI[1]-1*THETA)-5*ABS[3]*cos(PHI[3]-3*THETA)- 5*ABS[5]*cos(PHI[5]-5*THETA)+35*ABS[7]*cos(PHI[7]-7*THETA);
            CoefPCCD[xy][2][5]=3*ABS[1]*sin(PHI[1]-1*THETA)+1*ABS[3]*sin(PHI[3]-3*THETA)- 9*ABS[5]*sin(PHI[5]-5*THETA)+21*ABS[7]*sin(PHI[7]-7*THETA);
            CoefPCCD[xy][1][6]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA)- 7*ABS[7]*cos(PHI[7]-7*THETA);
            CoefPCCD[xy][0][7]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA)- 1*ABS[7]*sin(PHI[7]-7*THETA);
        }

// 8 -----
        if(APROP.SIP_ORDER   >  7.5){
            Z[2][0]=(56*Coef[xy][8][0]+4*Coef[xy][6][2]+0*Coef[xy][4][4]- 4*Coef[xy][2][6]-56*Coef[xy][0][8])/128.0;
            Z[2][1]=(14*Coef[xy][7][1]+6*Coef[xy][5][3]+6*Coef[xy][3][5]+14*Coef[xy][1][7])/128.0;
            Z[4][0]=(28*Coef[xy][8][0]-4*Coef[xy][6][2]-4*Coef[xy][4][4]- 4*Coef[xy][2][6]+28*Coef[xy][0][8])/128.0;
            Z[4][1]=(14*Coef[xy][7][1]+2*Coef[xy][5][3]-2*Coef[xy][3][5]-14*Coef[xy][1][7])/128.0;
            Z[6][0]=( 8*Coef[xy][8][0]-4*Coef[xy][6][2]+0*Coef[xy][4][4]+ 4*Coef[xy][2][6]- 8*Coef[xy][0][8])/128.0;
            Z[6][1]=( 6*Coef[xy][7][1]-2*Coef[xy][5][3]-2*Coef[xy][3][5]+ 6*Coef[xy][1][7])/128.0;
            Z[8][0]=( 1*Coef[xy][8][0]-1*Coef[xy][6][2]+1*Coef[xy][4][4]- 1*Coef[xy][2][6]+ 1*Coef[xy][0][8])/128.0;
            Z[8][1]=( 1*Coef[xy][7][1]-1*Coef[xy][5][3]+1*Coef[xy][3][5]- 1*Coef[xy][1][7])/128.0;
            ABS[0]= (35*Coef[xy][8][0]+5*Coef[xy][6][2]+3*Coef[xy][4][4]+ 5*Coef[xy][2][6]+35*Coef[xy][0][8])/128.0;
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            ABS[6]=hypot(Z[6][1],Z[6][0]);
            ABS[8]=hypot(Z[8][1],Z[8][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            PHI[6]=atan2(Z[6][1],Z[6][0]);
            PHI[8]=atan2(Z[8][1],Z[8][0]);
            CoefCCD[xy][8][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+ 1*ABS[4]*cos(PHI[4]-4*THETA)+ 1*ABS[6]*cos(PHI[6]-6*THETA)+ 1*ABS[8]*cos(PHI[8]-8*THETA);
            CoefCCD[xy][7][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+ 4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA)+ 8*ABS[8]*sin(PHI[8]-8*THETA);
            CoefCCD[xy][6][2]=4*ABS[0]+2*ABS[2]*cos(PHI[2]-2*THETA)- 4*ABS[4]*cos(PHI[4]-4*THETA)-14*ABS[6]*cos(PHI[6]-6*THETA)-28*ABS[8]*cos(PHI[8]-8*THETA);
            CoefCCD[xy][5][3]=0*ABS[0]+6*ABS[2]*sin(PHI[2]-2*THETA)+ 4*ABS[4]*sin(PHI[4]-4*THETA)-14*ABS[6]*sin(PHI[6]-6*THETA)-56*ABS[8]*sin(PHI[8]-8*THETA);
            CoefCCD[xy][4][4]=6*ABS[0]+0*ABS[2]*cos(PHI[2]-2*THETA)-10*ABS[4]*cos(PHI[4]-4*THETA)+ 0*ABS[6]*cos(PHI[6]-6*THETA)+70*ABS[8]*cos(PHI[8]-8*THETA);
            CoefCCD[xy][3][5]=0*ABS[0]+6*ABS[2]*sin(PHI[2]-2*THETA)- 4*ABS[4]*sin(PHI[4]-4*THETA)-14*ABS[6]*sin(PHI[6]-6*THETA)+56*ABS[8]*sin(PHI[8]-8*THETA);
            CoefCCD[xy][2][6]=4*ABS[0]-2*ABS[2]*cos(PHI[2]-2*THETA)- 4*ABS[4]*cos(PHI[4]-4*THETA)+14*ABS[6]*cos(PHI[6]-6*THETA)-28*ABS[8]*cos(PHI[8]-8*THETA);
            CoefCCD[xy][1][7]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)- 4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA)- 8*ABS[8]*sin(PHI[8]-8*THETA);
            CoefCCD[xy][0][8]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+ 1*ABS[4]*cos(PHI[4]-4*THETA)- 1*ABS[6]*cos(PHI[6]-6*THETA)+ 1*ABS[8]*cos(PHI[8]-8*THETA);
        }

        if(APROP.SIP_P_ORDER >  7.5){
            Z[2][0]=(56*CoefP[xy][8][0]+4*CoefP[xy][6][2]+0*CoefP[xy][4][4]- 4*CoefP[xy][2][6]-56*CoefP[xy][0][8])/128.0;
            Z[2][1]=(14*CoefP[xy][7][1]+6*CoefP[xy][5][3]+6*CoefP[xy][3][5]+14*CoefP[xy][1][7])/128.0;
            Z[4][0]=(28*CoefP[xy][8][0]-4*CoefP[xy][6][2]-4*CoefP[xy][4][4]- 4*CoefP[xy][2][6]+28*CoefP[xy][0][8])/128.0;
            Z[4][1]=(14*CoefP[xy][7][1]+2*CoefP[xy][5][3]-2*CoefP[xy][3][5]-14*CoefP[xy][1][7])/128.0;
            Z[6][0]=( 8*CoefP[xy][8][0]-4*CoefP[xy][6][2]+0*CoefP[xy][4][4]+ 4*CoefP[xy][2][6]- 8*CoefP[xy][0][8])/128.0;
            Z[6][1]=( 6*CoefP[xy][7][1]-2*CoefP[xy][5][3]-2*CoefP[xy][3][5]+ 6*CoefP[xy][1][7])/128.0;
            Z[8][0]=( 1*CoefP[xy][8][0]-1*CoefP[xy][6][2]+1*CoefP[xy][4][4]- 1*CoefP[xy][2][6]+ 1*CoefP[xy][0][8])/128.0;
            Z[8][1]=( 1*CoefP[xy][7][1]-1*CoefP[xy][5][3]+1*CoefP[xy][3][5]- 1*CoefP[xy][1][7])/128.0;
            ABS[0]= (35*CoefP[xy][8][0]+5*CoefP[xy][6][2]+3*CoefP[xy][4][4]+ 5*CoefP[xy][2][6]+35*CoefP[xy][0][8])/128.0;
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            ABS[6]=hypot(Z[6][1],Z[6][0]);
            ABS[8]=hypot(Z[8][1],Z[8][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            PHI[6]=atan2(Z[6][1],Z[6][0]);
            PHI[8]=atan2(Z[8][1],Z[8][0]);
            CoefPCCD[xy][8][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+ 1*ABS[4]*cos(PHI[4]-4*THETA)+ 1*ABS[6]*cos(PHI[6]-6*THETA)+ 1*ABS[8]*cos(PHI[8]-8*THETA);
            CoefPCCD[xy][7][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+ 4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA)+ 8*ABS[8]*sin(PHI[8]-8*THETA);
            CoefPCCD[xy][6][2]=4*ABS[0]+2*ABS[2]*cos(PHI[2]-2*THETA)- 4*ABS[4]*cos(PHI[4]-4*THETA)-14*ABS[6]*cos(PHI[6]-6*THETA)-28*ABS[8]*cos(PHI[8]-8*THETA);
            CoefPCCD[xy][5][3]=0*ABS[0]+6*ABS[2]*sin(PHI[2]-2*THETA)+ 4*ABS[4]*sin(PHI[4]-4*THETA)-14*ABS[6]*sin(PHI[6]-6*THETA)-56*ABS[8]*sin(PHI[8]-8*THETA);
            CoefPCCD[xy][4][4]=6*ABS[0]+0*ABS[2]*cos(PHI[2]-2*THETA)-10*ABS[4]*cos(PHI[4]-4*THETA)+ 0*ABS[6]*cos(PHI[6]-6*THETA)+70*ABS[8]*cos(PHI[8]-8*THETA);
            CoefPCCD[xy][3][5]=0*ABS[0]+6*ABS[2]*sin(PHI[2]-2*THETA)- 4*ABS[4]*sin(PHI[4]-4*THETA)-14*ABS[6]*sin(PHI[6]-6*THETA)+56*ABS[8]*sin(PHI[8]-8*THETA);
            CoefPCCD[xy][2][6]=4*ABS[0]-2*ABS[2]*cos(PHI[2]-2*THETA)- 4*ABS[4]*cos(PHI[4]-4*THETA)+14*ABS[6]*cos(PHI[6]-6*THETA)-28*ABS[8]*cos(PHI[8]-8*THETA);
            CoefPCCD[xy][1][7]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)- 4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA)- 8*ABS[8]*sin(PHI[8]-8*THETA);
            CoefPCCD[xy][0][8]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+ 1*ABS[4]*cos(PHI[4]-4*THETA)- 1*ABS[6]*cos(PHI[6]-6*THETA)+ 1*ABS[8]*cos(PHI[8]-8*THETA);
        }
// 9 -----
        if(APROP.SIP_ORDER   >  8.5){
            Z[1][0]=(126*Coef[xy][9][0]+14*Coef[xy][7][2]+6*Coef[xy][5][4]+ 6*Coef[xy][3][6]+ 14*Coef[xy][1][8])/256.0;
            Z[1][1]=( 14*Coef[xy][8][1]+ 6*Coef[xy][6][3]+6*Coef[xy][4][5]+14*Coef[xy][2][7]+126*Coef[xy][0][9])/256.0;
            Z[3][0]=( 84*Coef[xy][9][0]+ 0*Coef[xy][7][2]-4*Coef[xy][5][4]- 8*Coef[xy][3][6]- 28*Coef[xy][1][8])/256.0;
            Z[3][1]=( 28*Coef[xy][8][1]+ 8*Coef[xy][6][3]+4*Coef[xy][4][5]+ 0*Coef[xy][2][7]- 84*Coef[xy][0][9])/256.0;
            Z[5][0]=( 36*Coef[xy][9][0]- 8*Coef[xy][7][2]-4*Coef[xy][5][4]+ 0*Coef[xy][3][6]+ 20*Coef[xy][1][8])/256.0;
            Z[5][1]=( 20*Coef[xy][8][1]- 4*Coef[xy][6][3]+0*Coef[xy][4][5]- 8*Coef[xy][2][7]+ 36*Coef[xy][0][9])/256.0;
            Z[7][0]=(  9*Coef[xy][9][0]- 5*Coef[xy][7][2]+1*Coef[xy][5][4]+ 3*Coef[xy][3][6]-  7*Coef[xy][1][8])/256.0;
            Z[7][1]=(  7*Coef[xy][8][1]- 3*Coef[xy][6][3]-1*Coef[xy][4][5]+ 5*Coef[xy][2][7]-  9*Coef[xy][0][9])/256.0;
            Z[9][0]=(  1*Coef[xy][9][0]- 1*Coef[xy][7][2]+1*Coef[xy][5][4]- 1*Coef[xy][3][6]+  1*Coef[xy][1][8])/256.0;
            Z[9][1]=(  1*Coef[xy][8][1]- 1*Coef[xy][6][3]+1*Coef[xy][4][5]- 1*Coef[xy][2][7]+  1*Coef[xy][0][9])/256.0;
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
            CoefCCD[xy][9][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA)+ 1*ABS[7]*cos(PHI[7]-7*THETA)+  1*ABS[9]*cos(PHI[9]-9*THETA);
            CoefCCD[xy][8][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA)+ 7*ABS[7]*sin(PHI[7]-7*THETA)+  9*ABS[9]*sin(PHI[9]-9*THETA);
            CoefCCD[xy][7][2]=4*ABS[1]*cos(PHI[1]-1*THETA)+0*ABS[3]*cos(PHI[3]-3*THETA)- 8*ABS[5]*cos(PHI[5]-5*THETA)-20*ABS[7]*cos(PHI[7]-7*THETA)- 36*ABS[9]*cos(PHI[9]-9*THETA);
            CoefCCD[xy][6][3]=4*ABS[1]*sin(PHI[1]-1*THETA)+8*ABS[3]*sin(PHI[3]-3*THETA)+ 0*ABS[5]*sin(PHI[5]-5*THETA)-28*ABS[7]*sin(PHI[7]-7*THETA)- 84*ABS[9]*sin(PHI[9]-9*THETA);
            CoefCCD[xy][5][4]=6*ABS[1]*cos(PHI[1]-1*THETA)-6*ABS[3]*cos(PHI[3]-3*THETA)-14*ABS[5]*cos(PHI[5]-5*THETA)+14*ABS[7]*cos(PHI[7]-7*THETA)+126*ABS[9]*cos(PHI[9]-9*THETA);
            CoefCCD[xy][4][5]=6*ABS[1]*sin(PHI[1]-1*THETA)+6*ABS[3]*sin(PHI[3]-3*THETA)-14*ABS[5]*sin(PHI[5]-5*THETA)-14*ABS[7]*sin(PHI[7]-7*THETA)+126*ABS[9]*sin(PHI[9]-9*THETA);
            CoefCCD[xy][3][6]=4*ABS[1]*cos(PHI[1]-1*THETA)-8*ABS[3]*cos(PHI[3]-3*THETA)+ 0*ABS[5]*cos(PHI[5]-5*THETA)+28*ABS[7]*cos(PHI[7]-7*THETA)- 84*ABS[9]*cos(PHI[9]-9*THETA);
            CoefCCD[xy][2][7]=4*ABS[1]*sin(PHI[1]-1*THETA)+0*ABS[3]*sin(PHI[3]-3*THETA)- 8*ABS[5]*sin(PHI[5]-5*THETA)+20*ABS[7]*sin(PHI[7]-7*THETA)- 36*ABS[9]*sin(PHI[9]-9*THETA);
            CoefCCD[xy][1][8]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA)- 7*ABS[7]*cos(PHI[7]-7*THETA)+  9*ABS[9]*cos(PHI[9]-9*THETA);
            CoefCCD[xy][0][9]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA)- 1*ABS[7]*sin(PHI[7]-7*THETA)+  1*ABS[9]*sin(PHI[9]-9*THETA);
        }

        if(APROP.SIP_P_ORDER   >  8.5){
            Z[1][0]=(126*CoefP[xy][9][0]+14*CoefP[xy][7][2]+6*CoefP[xy][5][4]+ 6*CoefP[xy][3][6]+ 14*CoefP[xy][1][8])/256.0;
            Z[1][1]=( 14*CoefP[xy][8][1]+ 6*CoefP[xy][6][3]+6*CoefP[xy][4][5]+14*CoefP[xy][2][7]+126*CoefP[xy][0][9])/256.0;
            Z[3][0]=( 84*CoefP[xy][9][0]+ 0*CoefP[xy][7][2]-4*CoefP[xy][5][4]- 8*CoefP[xy][3][6]- 28*CoefP[xy][1][8])/256.0;
            Z[3][1]=( 28*CoefP[xy][8][1]+ 8*CoefP[xy][6][3]+4*CoefP[xy][4][5]+ 0*CoefP[xy][2][7]- 84*CoefP[xy][0][9])/256.0;
            Z[5][0]=( 36*CoefP[xy][9][0]- 8*CoefP[xy][7][2]-4*CoefP[xy][5][4]+ 0*CoefP[xy][3][6]+ 20*CoefP[xy][1][8])/256.0;
            Z[5][1]=( 20*CoefP[xy][8][1]- 0*CoefP[xy][6][3]-4*CoefP[xy][4][5]- 8*CoefP[xy][2][7]+ 36*CoefP[xy][0][9])/256.0;
            Z[7][0]=(  9*CoefP[xy][9][0]- 5*CoefP[xy][7][2]+1*CoefP[xy][5][4]+ 3*CoefP[xy][3][6]-  7*CoefP[xy][1][8])/256.0;
            Z[7][1]=(  7*CoefP[xy][8][1]- 3*CoefP[xy][6][3]-1*CoefP[xy][4][5]+ 5*CoefP[xy][2][7]-  9*CoefP[xy][0][9])/256.0;
            Z[9][0]=(  1*CoefP[xy][9][0]- 1*CoefP[xy][7][2]+1*CoefP[xy][5][4]- 1*CoefP[xy][3][6]+  1*CoefP[xy][1][8])/256.0;
            Z[9][1]=(  1*CoefP[xy][8][1]- 1*CoefP[xy][6][3]+1*CoefP[xy][4][5]- 1*CoefP[xy][2][7]+  1*CoefP[xy][0][9])/256.0;
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
            CoefPCCD[xy][9][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA)+ 1*ABS[7]*cos(PHI[7]-7*THETA)+  1*ABS[9]*cos(PHI[9]-9*THETA);
            CoefPCCD[xy][8][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA)+ 7*ABS[7]*sin(PHI[7]-7*THETA)+  9*ABS[9]*sin(PHI[9]-9*THETA);
            CoefPCCD[xy][7][2]=4*ABS[1]*cos(PHI[1]-1*THETA)+0*ABS[3]*cos(PHI[3]-3*THETA)- 8*ABS[5]*cos(PHI[5]-5*THETA)-20*ABS[7]*cos(PHI[7]-7*THETA)- 36*ABS[9]*cos(PHI[9]-9*THETA);
            CoefPCCD[xy][6][3]=4*ABS[1]*sin(PHI[1]-1*THETA)+8*ABS[3]*sin(PHI[3]-3*THETA)+ 0*ABS[5]*sin(PHI[5]-5*THETA)-28*ABS[7]*sin(PHI[7]-7*THETA)- 84*ABS[9]*sin(PHI[9]-9*THETA);
            CoefPCCD[xy][5][4]=6*ABS[1]*cos(PHI[1]-1*THETA)-6*ABS[3]*cos(PHI[3]-3*THETA)-14*ABS[5]*cos(PHI[5]-5*THETA)+14*ABS[7]*cos(PHI[7]-7*THETA)+126*ABS[9]*cos(PHI[9]-9*THETA);
            CoefPCCD[xy][4][5]=6*ABS[1]*sin(PHI[1]-1*THETA)+6*ABS[3]*sin(PHI[3]-3*THETA)-14*ABS[5]*sin(PHI[5]-5*THETA)-14*ABS[7]*sin(PHI[7]-7*THETA)+126*ABS[9]*sin(PHI[9]-9*THETA);
            CoefPCCD[xy][3][6]=4*ABS[1]*cos(PHI[1]-1*THETA)-8*ABS[3]*cos(PHI[3]-3*THETA)+ 0*ABS[5]*cos(PHI[5]-5*THETA)+28*ABS[7]*cos(PHI[7]-7*THETA)- 84*ABS[9]*cos(PHI[9]-9*THETA);
            CoefPCCD[xy][2][7]=4*ABS[1]*sin(PHI[1]-1*THETA)+0*ABS[3]*sin(PHI[3]-3*THETA)- 8*ABS[5]*sin(PHI[5]-5*THETA)+20*ABS[7]*sin(PHI[7]-7*THETA)- 36*ABS[9]*sin(PHI[9]-9*THETA);
            CoefPCCD[xy][1][8]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA)- 7*ABS[7]*cos(PHI[7]-7*THETA)+  9*ABS[9]*cos(PHI[9]-9*THETA);
            CoefPCCD[xy][0][9]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA)- 1*ABS[7]*sin(PHI[7]-7*THETA)+  1*ABS[9]*sin(PHI[9]-9*THETA);
        }
    }


// Polynial -> SIP --------------------------------------------------
    double *SIP1,*SIP2,*PSIP1,*PSIP2,InvCD[2][2];

    SIP1 = new double[(APROP.SIP_ORDER+2)*(APROP.SIP_ORDER+1)];
    SIP2 = new double[(APROP.SIP_ORDER+2)*(APROP.SIP_ORDER+1)];
    PSIP1= new double[(APROP.SIP_P_ORDER+2)*(APROP.SIP_P_ORDER+1)];
    PSIP2= new double[(APROP.SIP_P_ORDER+2)*(APROP.SIP_P_ORDER+1)];

    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        SIP1[ij]=CoefCCD[0][i][j];
        SIP2[ij]=CoefCCD[1][i][j];
        ij++;
    }

    CSIP->CD[0][0]=SIP1[1*(APROP.SIP_ORDER+1)+0];
    CSIP->CD[0][1]=SIP1[0*(APROP.SIP_ORDER+1)+1];
    CSIP->CD[1][0]=SIP2[1*(APROP.SIP_ORDER+1)+0];
    CSIP->CD[1][1]=SIP2[0*(APROP.SIP_ORDER+1)+1];
    InvCD[0][0]= CSIP->CD[1][1]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    InvCD[0][1]=-CSIP->CD[0][1]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    InvCD[1][0]=-CSIP->CD[1][0]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    InvCD[1][1]= CSIP->CD[0][0]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);

    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        CSIP->SIP_AB[0][ij]=InvCD[0][0]*SIP1[ij]+InvCD[0][1]*SIP2[ij];
        CSIP->SIP_AB[1][ij]=InvCD[1][0]*SIP1[ij]+InvCD[1][1]*SIP2[ij];
        ij++;	
    }
    CSIP->SIP_AB[0][1*(APROP.SIP_ORDER+1)+0]-=1;
    CSIP->SIP_AB[1][0*(APROP.SIP_ORDER+1)+1]-=1;

    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        PSIP1[ij]=CoefPCCD[0][i][j];
        PSIP2[ij]=CoefPCCD[1][i][j];
        ij++;
    }

    InvCD[0][0]= CSIP->CD[1][1]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    InvCD[0][1]=-CSIP->CD[0][1]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    InvCD[1][0]=-CSIP->CD[1][0]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    InvCD[1][1]= CSIP->CD[0][0]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);

    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        CSIP->SIP_ABP[0][ij]=InvCD[0][0]*PSIP1[ij]+InvCD[0][1]*PSIP2[ij];
        CSIP->SIP_ABP[1][ij]=InvCD[1][0]*PSIP1[ij]+InvCD[1][1]*PSIP2[ij];
        ij++;	
    }
    CSIP->SIP_ABP[0][1*(APROP.SIP_ORDER+1)+0]-=1;
    CSIP->SIP_ABP[1][0*(APROP.SIP_ORDER+1)+1]-=1;
//--------------------------------------------------
    for(i=0;i<APROP.SIP_ORDER+1;i++){
         delete [] CoefCCD[0][i];
         delete [] CoefCCD[1][i];
    }
    for(i=0;i<APROP.SIP_P_ORDER+1;i++){
         delete [] CoefPCCD[0][i];
         delete [] CoefPCCD[1][i];
    }
    delete [] CoefCCD[0];
    delete [] CoefCCD[1];
    delete [] CoefPCCD[0];
    delete [] CoefPCCD[1];
    delete [] SIP1;
    delete [] SIP2;
    delete [] PSIP1;
    delete [] PSIP2;
}
#undef PI
