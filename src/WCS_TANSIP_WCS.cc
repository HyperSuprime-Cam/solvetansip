//------------------------------------------------------------
//WCS_TANSIP_WCS.cc
//Calculating WCS of global
//
//Last modification : 2010/04/01
//------------------------------------------------------------
#include<iostream>
#include<cmath>
#include <string.h>
#include<omp.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
void    F_WCS_TANSIP_WCS_SETBASE        (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_PROJECTIONPOINT(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_PROJECTION     (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_CR     (int DIR,CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_SIPFIT         (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_PSIPFIT        (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_REJECTION      (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_GCHECK         (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_PREDICTCHECK   (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_CAMERADIST     (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

    F_WCS_TANSIP_WCS_SETBASE(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    if(strcmp(APROP.CRPIXMODE,"VAL")==0){
    F_WCS_TANSIP_WCS_CR(1,APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    }else{
    F_WCS_TANSIP_WCS_CR(0,APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    F_WCS_TANSIP_WCS_PROJECTION(APROP,CPROP,PAIR,CSIP);
    }
    F_WCS_TANSIP_WCS_SIPFIT (APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    F_WCS_TANSIP_WCS_PSIPFIT(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : REJECTION ---" << endl;
    cout << "SKIP" << endl;
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : Re-SIP FITTING---" << endl;
    cout << "SKIP" << endl;
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : Re-PSIP FITTING---" << endl;
    cout << "SKIP" << endl;
    cout <<endl;
    F_WCS_TANSIP_WCS_GCHECK(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    F_WCS_TANSIP_WCS_PREDICTCHECK(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    F_WCS_TANSIP_WCS_CAMERADIST(APROP,CPROP,PAIR,CSIP);
//--------------------------------------------------
//--------------------------------------------------
}
void    F_WCS_TANSIP_WCS_SETBASE(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,FNUM;
    double CRPIXAVE[2]={0};

    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET BASE ---" << endl;

//SET CSIP parameters
    CSIP->SIP_AB_ORDER=APROP.SIP_ORDER;
    CSIP->SIP_ABP_ORDER=APROP.SIP_P_ORDER;
    CSIP->ID=APROP.CCDNUM;
//SET Global position
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].xG=CPROP[PAIR[NUM].CHIPID].GLOB_POS[0]+PAIR[NUM].xL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].yL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].yG=CPROP[PAIR[NUM].CHIPID].GLOB_POS[1]+PAIR[NUM].yL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].xL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
    }

//SET CR
          if(strcmp(APROP.CRPIXMODE,"PIX")==0){
        CSIP->CRPIX[0]=APROP.CRPIX[0];
        CSIP->CRPIX[1]=APROP.CRPIX[1];
        cout << "ASSIGNED CRPIX ( " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1] << " )"<< endl;
    }else if(strcmp(APROP.CRPIXMODE,"VAL")==0){
        CSIP->CRVAL[0]=APROP.CRVAL[0];
        CSIP->CRVAL[1]=APROP.CRVAL[1];
        cout << "ASSIGNED CRVAL ( " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1] << " )"<< endl;
    }else{
        FNUM=0;
        for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
        if(PAIR[NUM].FLAG == 1){
            CRPIXAVE[0]+=PAIR[NUM].xG;
            CRPIXAVE[1]+=PAIR[NUM].yG;
            FNUM++;
         }
        CSIP->CRPIX[0]=CRPIXAVE[0]/FNUM;
        CSIP->CRPIX[1]=CRPIXAVE[1]/FNUM;
        cout << "AUTO MODE CRPIX ( " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1] << " )"<< endl;
    }
//--------------------------------------------------
}
void    F_WCS_TANSIP_WCS_PROJECTIONPOINT(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,NUM,FNUM;
    double **dx[2],*Coef[2];
//--------------------------------------------------
    Coef[0]=new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    Coef[1]=new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    for(i=0;i<(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2);i++)
    Coef[0][i]=Coef[1][i]=0;
    dx[0]=new double*[APROP.NUMREFALL];
    dx[1]=new double*[APROP.NUMREFALL];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    dx[0][NUM]=new double[3];
    dx[1][NUM]=new double[3];
    }
//--------------------------------------------------
    CSIP[APROP.CCDNUM].CRPIX[0]=APROP.CRPIX[0];
    CSIP[APROP.CCDNUM].CRPIX[1]=APROP.CRPIX[1];

    FNUM=0;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
        PAIR[NUM].xCRPIX=PAIR[NUM].xG-CSIP[APROP.CCDNUM].CRPIX[0];
        PAIR[NUM].yCRPIX=PAIR[NUM].yG-CSIP[APROP.CCDNUM].CRPIX[1];
        dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].xCRPIX;
        dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].yCRPIX;
        dx[0][FNUM][2]=PAIR[NUM].RA;
        dx[1][FNUM][2]=PAIR[NUM].DEC;
        FNUM++;
    }
    F_LS2(FNUM,APROP.SIP_ORDER,dx[0],Coef[0]);
    F_LS2(FNUM,APROP.SIP_ORDER,dx[1],Coef[1]);

    cout << "RA and DEC at CRPIX : ( " << Coef[0][0] << " , " << Coef[1][0] << " )\n";
    CSIP[APROP.CCDNUM].CRVAL[0]=Coef[0][0];
    CSIP[APROP.CCDNUM].CRVAL[1]=Coef[1][0];
    cout << "CRVAL      at CRPIX : ( " << CSIP[APROP.CCDNUM].CRVAL[0] << " , " << CSIP[APROP.CCDNUM].CRVAL[1] << " )\n";
    cout << endl;
//--------------------------------------------------
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    delete [] dx[0][NUM];
    delete [] dx[1][NUM];
    }
    delete [] dx[0];
    delete [] dx[1];
}
void    F_WCS_TANSIP_WCS_PROJECTION(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM;
    double PPOINT[2],Pdeg[2],Cdeg[2];
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PROJECTION ---" << endl;

//    cout << "PROJECTION : CRPIX : ( " << CSIP[APROP.CCDNUM].CRPIX[0] << " , " << CSIP[APROP.CCDNUM].CRPIX[1] << " )(pix)\n";
    cout << "PROJECTION : CRVAL : ( " << CSIP[APROP.CCDNUM].CRVAL[0] << " , " << CSIP[APROP.CCDNUM].CRVAL[1] << " )(deg)\n";
    PPOINT[0]=CSIP[APROP.CCDNUM].CRVAL[0];
    PPOINT[1]=CSIP[APROP.CCDNUM].CRVAL[1];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        Cdeg[0]=PAIR[NUM].RA;
        Cdeg[1]=PAIR[NUM].DEC;
        F_PROJECTION(Cdeg,Pdeg,PPOINT);
        PAIR[NUM].xI=Pdeg[0];
        PAIR[NUM].yI=Pdeg[1];
//cout << PAIR[NUM].RA << "	" << PAIR[NUM].xI << endl;
//cout << PAIR[NUM].DEC<< "	" << PAIR[NUM].yI << endl;
    }
cout << endl;
}
void    F_WCS_TANSIP_WCS_CR(int DIR,CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,NUM,FNUM;
    double **dx[2],*Coef[2];

    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRPIX and CRVAL ---" << endl;
//--------------------------------------------------
    Coef[0]=new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    Coef[1]=new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    for(i=0;i<(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2);i++)
    Coef[0][i]=Coef[1][i]=0;
    dx[0]=new double*[APROP.NUMREFALL];
    dx[1]=new double*[APROP.NUMREFALL];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    dx[0][NUM]=new double[3];
    dx[1][NUM]=new double[3];
    }

//--------------------------------------------------
    FNUM=0;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
        if(DIR==0){
            PAIR[NUM].xCRPIX=PAIR[NUM].xG-CSIP->CRPIX[0];
            PAIR[NUM].yCRPIX=PAIR[NUM].yG-CSIP->CRPIX[1];
            dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].xCRPIX;
            dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].yCRPIX;
            dx[0][FNUM][2]=PAIR[NUM].RA;
            dx[1][FNUM][2]=PAIR[NUM].DEC;
         }else{
//cout << PAIR[NUM].xI << "	" << PAIR[NUM].yI << "	" << PAIR[NUM].xG << "	" << PAIR[NUM].yG<<endl;
            dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].xI;
            dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].yI;
            dx[0][FNUM][2]=PAIR[NUM].xG;
            dx[1][FNUM][2]=PAIR[NUM].yG;
        }
        FNUM++;
    }
    if(DIR==0){
    #pragma omp parallel num_threads(2)
    #pragma omp sections
    {
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_ORDER,dx[0],Coef[0]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_ORDER,dx[1],Coef[1]);
        }
    }
    }else{
    #pragma omp parallel num_threads(2)
    #pragma omp sections
    {
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_P_ORDER,dx[0],Coef[0]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_P_ORDER,dx[1],Coef[1]);
        }
    }
    }

    if(DIR==0){
    cout << "RA and DEC at CRPIX : ( " << Coef[0][0] << " , " << Coef[1][0] << " )\n";
        CSIP->CRVAL[0]=Coef[0][0];
        CSIP->CRVAL[1]=Coef[1][0];
    cout << "CRVAL      at CRPIX : ( " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1] << " )\n";
    }else{
    cout << "xG and yG  at CRVAL : ( " << Coef[0][0] << " , " << Coef[1][0] << " )\n";
        CSIP->CRPIX[0]=Coef[0][0];
        CSIP->CRPIX[1]=Coef[1][0];
    cout << "CRPIX      at CRVAL : ( " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1] << " )\n";
    }
cout << endl;

//--------------------------------------------------
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    delete [] dx[0][NUM];
    delete [] dx[1][NUM];
    }
    delete [] dx[0];
    delete [] dx[1];
    
//--------------------------------------------------
}
void    F_WCS_TANSIP_WCS_SIPFIT (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS :  SIP FITTING ---" << endl;
    int i,NUM,FNUM;
    double **dx[2],*Coef[2];

    Coef[0]=new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    Coef[1]=new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    for(i=0;i<(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2);i++)
    Coef[0][i]=Coef[1][i]=0;
    dx[0]=new double*[APROP.NUMREFALL];
    dx[1]=new double*[APROP.NUMREFALL];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    dx[0][NUM]=new double[3];
    dx[1][NUM]=new double[3];
    }

//--------------------------------------------------
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].xCRPIX=PAIR[NUM].xG-CSIP->CRPIX[0];
        PAIR[NUM].yCRPIX=PAIR[NUM].yG-CSIP->CRPIX[1];
    }

    FNUM=0;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
        dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].xCRPIX;
        dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].yCRPIX;
        dx[0][FNUM][2]=PAIR[NUM].xI;
        dx[1][FNUM][2]=PAIR[NUM].yI;
        FNUM++;
    }
    #pragma omp parallel num_threads(2)
    #pragma omp sections
    {
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_ORDER,dx[0],Coef[0]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_ORDER,dx[1],Coef[1]);
        }
    }

//--------------------------------------------------
    CSIP->CD[0][0]=Coef[0][1*(APROP.SIP_ORDER+1)+0];
    CSIP->CD[0][1]=Coef[0][0*(APROP.SIP_ORDER+1)+1];
    CSIP->CD[1][0]=Coef[1][1*(APROP.SIP_ORDER+1)+0];
    CSIP->CD[1][1]=Coef[1][0*(APROP.SIP_ORDER+1)+1]; 

    CSIP->InvCD[0][0]= CSIP->CD[1][1]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    CSIP->InvCD[0][1]=-CSIP->CD[0][1]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    CSIP->InvCD[1][0]=-CSIP->CD[1][0]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    CSIP->InvCD[1][1]= CSIP->CD[0][0]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);

    int j,ij;
    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        CSIP->SIP_AB[0][ij]=CSIP->InvCD[0][0]*Coef[0][ij]+CSIP->InvCD[0][1]*Coef[1][ij];
        CSIP->SIP_AB[1][ij]=CSIP->InvCD[1][0]*Coef[0][ij]+CSIP->InvCD[1][1]*Coef[1][ij];
        ij++;	
    }
    CSIP->SIP_AB[0][1*(APROP.SIP_ORDER+1)+0]-=1.0;
    CSIP->SIP_AB[1][0*(APROP.SIP_ORDER+1)+1]-=1.0;
    CSIP->FITNUM=FNUM;
//--------------------------------------------------

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    delete [] dx[0][NUM];
    delete [] dx[1][NUM];
    }
    delete [] dx[0];
    delete [] dx[1];
    
//--------------------------------------------------
}

void    F_WCS_TANSIP_WCS_PSIPFIT (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PSIP FITTING ---" << endl;
    int i,NUM,FNUM;
    double **dx[2],*Coef[2];

    Coef[0]=new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    Coef[1]=new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    for(i=0;i<(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2);i++)
    Coef[0][i]=Coef[1][i]=0;
    dx[0]=new double*[APROP.NUMREFALL];
    dx[1]=new double*[APROP.NUMREFALL];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    dx[0][NUM]=new double[3];
    dx[1][NUM]=new double[3];
    }

//--------------------------------------------------
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].xCRVAL=CSIP->InvCD[0][0]*PAIR[NUM].xI+CSIP->InvCD[0][1]*PAIR[NUM].yI;
        PAIR[NUM].yCRVAL=CSIP->InvCD[1][0]*PAIR[NUM].xI+CSIP->InvCD[1][1]*PAIR[NUM].yI;
    }
    FNUM=0;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
        dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].xCRVAL;
        dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].yCRVAL;
        dx[0][FNUM][2]=PAIR[NUM].xCRPIX;
        dx[1][FNUM][2]=PAIR[NUM].yCRPIX;
        FNUM++;
    }
    #pragma omp parallel num_threads(2)
    #pragma omp sections
    {
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_P_ORDER,dx[0],Coef[0]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_P_ORDER,dx[1],Coef[1]);
        }
    }

//--------------------------------------------------
    int j,ij;
    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        CSIP->SIP_ABP[0][ij]=Coef[0][ij];
        CSIP->SIP_ABP[1][ij]=Coef[1][ij];
        ij++;	
    }

    CSIP->SIP_ABP[0][1*(APROP.SIP_ORDER+1)+0]-=1.0;
    CSIP->SIP_ABP[1][0*(APROP.SIP_ORDER+1)+1]-=1.0;
    CSIP->FITNUM=FNUM;
//--------------------------------------------------
//--------------------------------------------------
    delete [] Coef[0];
    delete [] Coef[1];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    delete [] dx[0][NUM];
    delete [] dx[1][NUM];
    }
    delete [] dx[0];
    delete [] dx[1];
    
//--------------------------------------------------
}
#include<fstream>
void    F_WCS_TANSIP_WCS_GCHECK(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,FNUM;
    double X[2],Y[2];
    double *RMS[4];
char fout [100];
ofstream temp;

sprintf(fout,"reference_check.dat");
temp.open(fout);
cout << "temprary output : " << fout << endl;

    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : GLOBAL CHECK---" << endl;
//--------------------------------------------------
    for(NUM=0;NUM<4;NUM++)
    RMS[NUM] = new double[APROP.NUMREFALL];

//--------------------------------------------------
    FNUM=0;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
//fitting check 
        X[0]=PAIR[NUM].xCRPIX;
        X[1]=PAIR[NUM].yCRPIX;
        Y[0]=F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[0],X)+X[0];
        Y[1]=F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[1],X)+X[1];
        PAIR[NUM].GxSIPErr=Y[0]-PAIR[NUM].xCRVAL;
        PAIR[NUM].GySIPErr=Y[1]-PAIR[NUM].yCRVAL;
        RMS[0][FNUM]=PAIR[NUM].GxSIPErr;
        RMS[1][FNUM]=PAIR[NUM].GySIPErr;
        PAIR[NUM].GxLErr=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP->SIP_ABP[0],Y)+Y[0]-PAIR[NUM].xCRPIX;
        PAIR[NUM].GyLErr=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP->SIP_ABP[1],Y)+Y[1]-PAIR[NUM].yCRPIX;
//
        X[0]=PAIR[NUM].xCRVAL;
        X[1]=PAIR[NUM].yCRVAL;
        Y[0]=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP->SIP_ABP[0],X)+X[0];
        Y[1]=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP->SIP_ABP[1],X)+X[1];
        PAIR[NUM].GxPSIPErr=Y[0]-PAIR[NUM].xCRPIX;
        PAIR[NUM].GyPSIPErr=Y[1]-PAIR[NUM].yCRPIX;
        RMS[2][FNUM]=PAIR[NUM].GxPSIPErr;
        RMS[3][FNUM]=PAIR[NUM].GyPSIPErr;
        PAIR[NUM].GxIErr=F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[0],Y)+Y[0]-X[0];
        PAIR[NUM].GyIErr=F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[1],Y)+Y[1]-X[1];

temp << PAIR[NUM].ID << "	" << PAIR[NUM].CHIPID << "	" << PAIR[NUM].xL << "	" << PAIR[NUM].yL << "	" << PAIR[NUM].RA << "	" << PAIR[NUM].DEC << "	" << PAIR[NUM].xG << "	" << PAIR[NUM].yG << "	" << PAIR[NUM].GxSIPErr << "	" << PAIR[NUM].GySIPErr << "	" << PAIR[NUM].GxPSIPErr << "	" << PAIR[NUM].GyPSIPErr << "	" << PAIR[NUM].GxLErr << "	" << PAIR[NUM].GyLErr << "	" << PAIR[NUM].GxIErr << "	" << PAIR[NUM].GyIErr << "	" << endl;
        FNUM++;
    }
temp.close();

    F_RMS(FNUM,RMS[0],CSIP->SIP_AB_GErr[0]);
    F_RMS(FNUM,RMS[1],CSIP->SIP_AB_GErr[1]);
    F_RMS(FNUM,RMS[2],CSIP->SIP_ABP_GErr[0]);
    F_RMS(FNUM,RMS[3],CSIP->SIP_ABP_GErr[1]);
//--------------------------------------------------
    cout << "--- GLOBAL FITTING STATISTICS --------------------" <<endl;
    cout << "REFERENCE NUM: " << FNUM<< endl;
    cout << fixed;
    cout << "CRPIX(pix)   : " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1]<< endl;
    cout << "CRVAL(dec)   : " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1]<< endl;
    cout.unsetf(ios::fixed);
    cout << "CD_1_1       : " << CSIP->CD[0][0] << endl;
    cout << "CD_1_2       : " << CSIP->CD[0][1] << endl;
    cout << "CD_2_1       : " << CSIP->CD[1][0] << endl;
    cout << "CD_2_2       : " << CSIP->CD[1][1] << endl;
    cout << "InvCD_1_1    : " << CSIP->InvCD[0][0] << endl;
    cout << "InvCD_1_2    : " << CSIP->InvCD[0][1] << endl;
    cout << "InvCD_2_1    : " << CSIP->InvCD[1][0] << endl;
    cout << "InvCD_2_2    : " << CSIP->InvCD[1][1] << endl;
    cout << scientific;
    cout << "  SIPx[0][0] : " << CSIP->SIP_AB[0][0] << endl;
    cout << "  SIPx[0][1] : " << CSIP->SIP_AB[0][1] << endl;
    cout << "  SIPx[1][0] : " << CSIP->SIP_AB[0][APROP.SIP_ORDER+1] << endl;
    cout << "  SIPx[1][1] : " << CSIP->SIP_AB[0][APROP.SIP_ORDER+2] << endl;
    cout << "  SIPy[0][0] : " << CSIP->SIP_AB[1][0] << endl;
    cout << "  SIPy[0][1] : " << CSIP->SIP_AB[1][1] << endl;
    cout << "  SIPy[1][0] : " << CSIP->SIP_AB[1][APROP.SIP_ORDER+1] << endl;
    cout << "  SIPy[1][1] : " << CSIP->SIP_AB[1][APROP.SIP_ORDER+2] << endl;
    cout << " PSIPx[0][0] : " << CSIP->SIP_ABP[0][0] << endl;
    cout << " PSIPx[0][1] : " << CSIP->SIP_ABP[0][1] << endl;
    cout << " PSIPx[1][0] : " << CSIP->SIP_ABP[0][APROP.SIP_ORDER+1] << endl;
    cout << " PSIPx[1][1] : " << CSIP->SIP_ABP[0][APROP.SIP_ORDER+2] << endl;
    cout << " PSIPy[0][0] : " << CSIP->SIP_ABP[1][0] << endl;
    cout << " PSIPy[0][1] : " << CSIP->SIP_ABP[1][1] << endl;
    cout << " PSIPy[1][0] : " << CSIP->SIP_ABP[1][APROP.SIP_ORDER+1] << endl;
    cout << " PSIPy[1][1] : " << CSIP->SIP_ABP[1][APROP.SIP_ORDER+2] << endl;
    cout << " SIPGxErrAVE : " << CSIP->SIP_AB_GErr[0][0] << "	(pix)"<< endl;
    cout << " SIPGxErrRMS : " << CSIP->SIP_AB_GErr[0][1] << "	(pix)" << endl;
    cout << " SIPGyErrAVE : " << CSIP->SIP_AB_GErr[1][0] << "	(pix)" << endl;
    cout << " SIPGyErrRMS : " << CSIP->SIP_AB_GErr[1][1] << "	(pix)" << endl;
    cout << "PSIPGxErrAVE : " << CSIP->SIP_ABP_GErr[0][0] << "	(pix)" << endl;
    cout << "PSIPGxErrRMS : " << CSIP->SIP_ABP_GErr[0][1] << "	(pix)" << endl;
    cout << "PSIPGyErrAVE : " << CSIP->SIP_ABP_GErr[1][0] << "	(pix)" << endl;
    cout << "PSIPGyErrRMS : " << CSIP->SIP_ABP_GErr[1][1] << "	(pix)" << endl;
    cout << "--------------------------------------------------" <<endl;
    cout.unsetf(ios::scientific);
    cout << endl;

//--------------------------------------------------
    for(NUM=0;NUM<4;NUM++)
    delete [] RMS[NUM];
}
void    F_WCS_TANSIP_WCS_PREDICTCHECK(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,NUM,FNUM;
    double **Dx[2],*DCoef[2];
char fout[100];
ofstream temp;

sprintf(fout,"predict_check.dat");
temp.open(fout);
cout << "temprary output : " << fout << endl;

    DCoef[0]=new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    DCoef[1]=new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    for(i=0;i<(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2);i++)
    DCoef[0][i]=DCoef[1][i]=0;
    Dx[0]=new double*[APROP.NUMREFALL];
    Dx[1]=new double*[APROP.NUMREFALL];
    for(FNUM=0;FNUM<APROP.NUMREFALL;FNUM++){
    Dx[0][FNUM]=new double[3];
    Dx[1][FNUM]=new double[3];
    }

    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PREDICT CHECK---" << endl;

    CSIP->ANGLE=atan2(CSIP->CD[1][0]+CSIP->CD[0][1],-CSIP->CD[0][0]+CSIP->CD[1][1]);//with reverse
    cout << "FOV ANGLE : " << CSIP->ANGLE << endl;

    FNUM=0;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
        PAIR[NUM].xDIST=PAIR[NUM].xCRPIX*cos(CSIP->ANGLE)-PAIR[NUM].yCRPIX*sin(CSIP->ANGLE);
        PAIR[NUM].yDIST=PAIR[NUM].xCRPIX*sin(CSIP->ANGLE)+PAIR[NUM].yCRPIX*cos(CSIP->ANGLE);

        Dx[0][FNUM][0]=Dx[1][FNUM][0]=PAIR[NUM].xI;
        Dx[0][FNUM][1]=Dx[1][FNUM][1]=PAIR[NUM].yI;
        Dx[0][FNUM][2]=PAIR[NUM].xDIST;
        Dx[1][FNUM][2]=PAIR[NUM].yDIST;
        FNUM++;
    }

    #pragma omp parallel num_threads(2)
    #pragma omp sections
    {
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_P_ORDER,Dx[0],DCoef[0]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_P_ORDER,Dx[1],DCoef[1]);
        }
    }

    CSIP->InvSS[0][0]=DCoef[0][1*(APROP.SIP_P_ORDER+1)+0];
    CSIP->InvSS[0][1]=DCoef[0][0*(APROP.SIP_P_ORDER+1)+1];
    CSIP->InvSS[1][0]=DCoef[1][1*(APROP.SIP_P_ORDER+1)+0];
    CSIP->InvSS[1][1]=DCoef[1][0*(APROP.SIP_P_ORDER+1)+1];

    cout << "MEASURED InvSS" << endl;
    cout << CSIP->InvSS[0][0] << endl;
    cout << CSIP->InvSS[0][1] << endl;
    cout << CSIP->InvSS[1][0] << endl;
    cout << CSIP->InvSS[1][1] << endl;

    CSIP->SS[0][0]= CSIP->InvSS[1][1]/(CSIP->InvSS[0][0]*CSIP->InvSS[1][1]-CSIP->InvSS[1][0]*CSIP->InvSS[0][1]);
    CSIP->SS[0][1]=-CSIP->InvSS[0][1]/(CSIP->InvSS[0][0]*CSIP->InvSS[1][1]-CSIP->InvSS[1][0]*CSIP->InvSS[0][1]);
    CSIP->SS[1][0]=-CSIP->InvSS[1][0]/(CSIP->InvSS[0][0]*CSIP->InvSS[1][1]-CSIP->InvSS[1][0]*CSIP->InvSS[0][1]);
    CSIP->SS[1][1]= CSIP->InvSS[0][0]/(CSIP->InvSS[0][0]*CSIP->InvSS[1][1]-CSIP->InvSS[1][0]*CSIP->InvSS[0][1]);

    int j,ij;
    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        CSIP->SIP_ABD[0][ij]= CSIP->SS[0][0]*DCoef[0][ij]+ CSIP->SS[0][1]*DCoef[1][ij];
        CSIP->SIP_ABD[1][ij]= CSIP->SS[1][0]*DCoef[0][ij]+ CSIP->SS[1][1]*DCoef[1][ij];
cout << CSIP->SIP_ABD[0][ij] << "	" << CSIP->SIP_ABD[1][ij] << endl;
        ij++;	
    }

    CSIP->SIP_ABD[0][1*(APROP.SIP_P_ORDER+1)+0]-=1.0;
    CSIP->SIP_ABD[1][0*(APROP.SIP_P_ORDER+1)+1]-=1.0;
//--------------------------------------------------
   double dDEC,dRA,xI[2],xPI[2],xDI[2],PREDICT_D[2],MEASURE_D[2];

   for(dRA =-1;dRA <1;dRA +=0.05)
   for(dDEC=-1;dDEC<1;dDEC+=0.05)
   if(hypot(dRA,dDEC)<0.8){
        xI[0]=dRA;
        xI[1]=dDEC;
        xDI[0]=CSIP->InvSS[0][0]*xI[0]+CSIP->InvSS[0][1]*xI[1];
        xDI[1]=CSIP->InvSS[1][0]*xI[0]+CSIP->InvSS[1][1]*xI[1];
        xPI[0]=CSIP->PREDICT_InvSS[0][0]*xI[0]+CSIP->PREDICT_InvSS[0][1]*xI[1];
        xPI[1]=CSIP->PREDICT_InvSS[1][0]*xI[0]+CSIP->PREDICT_InvSS[1][1]*xI[1];
        MEASURE_D[0]=F_CALCVALUE(APROP.SIP_P_ORDER          ,CSIP->SIP_ABD[0]        ,xDI)+xDI[0];
        MEASURE_D[1]=F_CALCVALUE(APROP.SIP_P_ORDER          ,CSIP->SIP_ABD[1]        ,xDI)+xDI[1];
        PREDICT_D[0]=F_CALCVALUE(CSIP->PREDICT_SIP_ABD_ORDER,CSIP->PREDICT_SIP_ABD[0],xPI)+xPI[0];
        PREDICT_D[1]=F_CALCVALUE(CSIP->PREDICT_SIP_ABD_ORDER,CSIP->PREDICT_SIP_ABD[1],xPI)+xPI[1];
temp << xI[0] << "	" << xI[1] << "	" << PREDICT_D[0] << "	" << PREDICT_D[1] << "	" << MEASURE_D[0] << "	" << MEASURE_D[1] << endl;
   }
temp.close();

    cout << endl;
//--------------------------------------------------
    delete [] DCoef[0];
    delete [] DCoef[1];
    for(FNUM=0;FNUM<APROP.NUMREFALL;FNUM++){
    delete [] Dx[0][FNUM];
    delete [] Dx[1][FNUM];
    }
    delete [] Dx[0];
    delete [] Dx[1];
}
void    F_WCS_TANSIP_WCS_CAMERADIST(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM;
char fout[100];
ofstream temp;

sprintf(fout,"distortion_check.dat");
temp.open(fout);
cout << "temprary output : " << fout << endl;

    int i,j,ij;
    double *dPSIP[2][2],*PSIP[2],xI[2];
     PSIP[0]    = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
     PSIP[1]    = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    dPSIP[0][0] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    dPSIP[0][1] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    dPSIP[1][0] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    dPSIP[1][1] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];

    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        PSIP[0][ij]=CSIP[APROP.CCDNUM].SIP_ABP[0][ij];
        PSIP[1][ij]=CSIP[APROP.CCDNUM].SIP_ABP[1][ij];
        ij++;	
    }
    PSIP[0][1*(APROP.SIP_P_ORDER+1)+0]+=1;
    PSIP[1][0*(APROP.SIP_P_ORDER+1)+1]+=1;

    F_DIFFSIP(APROP.SIP_P_ORDER,PSIP[0],dPSIP[0][0],dPSIP[0][1]);
    F_DIFFSIP(APROP.SIP_P_ORDER,PSIP[1],dPSIP[1][0],dPSIP[1][1]);

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        xI[0]=PAIR[NUM].xCRVAL;
        xI[1]=PAIR[NUM].yCRVAL;
        PAIR[NUM].dxGdxI=F_CALCVALUE(APROP.SIP_P_ORDER,dPSIP[0][0],xI);
        PAIR[NUM].dxGdyI=F_CALCVALUE(APROP.SIP_P_ORDER,dPSIP[0][1],xI);
        PAIR[NUM].dyGdxI=F_CALCVALUE(APROP.SIP_P_ORDER,dPSIP[1][0],xI);
        PAIR[NUM].dyGdyI=F_CALCVALUE(APROP.SIP_P_ORDER,dPSIP[1][1],xI);

        PAIR[NUM].CAMERA_MAGNIFICATION=0.5*hypot(PAIR[NUM].dxGdxI+PAIR[NUM].dyGdyI,PAIR[NUM].dyGdxI-PAIR[NUM].dxGdyI);
        PAIR[NUM].CAMERA_SHEAR[0]     =0.5*(PAIR[NUM].dxGdxI-PAIR[NUM].dyGdyI)/PAIR[NUM].CAMERA_MAGNIFICATION;
        PAIR[NUM].CAMERA_SHEAR[1]     =0.5*(PAIR[NUM].dyGdxI+PAIR[NUM].dxGdyI)/PAIR[NUM].CAMERA_MAGNIFICATION;
        PAIR[NUM].CAMERA_ROTATION     =atan2((PAIR[NUM].dyGdxI-PAIR[NUM].dxGdyI),(PAIR[NUM].dxGdxI+PAIR[NUM].dyGdyI));
temp << PAIR[NUM].ID << "	" << PAIR[NUM].CHIPID << "	" << PAIR[NUM].xL << "	" << PAIR[NUM].yL << "	" << PAIR[NUM].RA << "	" << PAIR[NUM].DEC << "	" << PAIR[NUM].xG << "	" << PAIR[NUM].yG << "	" << PAIR[NUM].CAMERA_MAGNIFICATION << "	" << PAIR[NUM].CAMERA_SHEAR[0] << "	" << PAIR[NUM].CAMERA_SHEAR[1] << "	" << PAIR[NUM].CAMERA_ROTATION << endl;
    }
temp.close();

    delete []  PSIP[0];
    delete []  PSIP[1];
    delete [] dPSIP[0][0];
    delete [] dPSIP[0][1];
    delete [] dPSIP[1][0];
    delete [] dPSIP[1][1];
}
