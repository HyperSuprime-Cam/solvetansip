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
void    F_WCS_TANSIP_WCS_SETBASE(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_PROJECTIONPOINT(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_PROJECTION(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_CR(int DIR,CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_SIPFIT (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_PSIPFIT(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_REJECTION(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_GCHECK(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

    F_WCS_TANSIP_WCS_SETBASE(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    if(strcmp(APROP.CRPIXMODE,"VAL")==0){
    F_WCS_TANSIP_WCS_CR(1,APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    }else{
    F_WCS_TANSIP_WCS_CR(0,APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    F_WCS_TANSIP_GPOS_PROJECTION(APROP,CPROP,PAIR,CSIP);
    }
    F_WCS_TANSIP_WCS_SIPFIT (APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    F_WCS_TANSIP_WCS_PSIPFIT(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    cout << "--- WCS_TANSIP : CALCULATING GLOVAL WCS : REJECTION ---" << endl;
    cout << "SKIP" << endl;
    cout << "--- WCS_TANSIP : CALCULATING GLOVAL WCS : Re-SIP FITTING---" << endl;
    cout << "SKIP" << endl;
    cout << "--- WCS_TANSIP : CALCULATING GLOVAL WCS : Re-PSIP FITTING---" << endl;
    cout << "SKIP" << endl;
    cout <<endl;
    F_WCS_TANSIP_WCS_GCHECK(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
//--------------------------------------------------
}
void    F_WCS_TANSIP_WCS_SETBASE(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,FNUM;
    double CRPIXAVE[2]={0};

    cout << "--- WCS_TANSIP : CALCULATING GLOVAL WCS : SET BASE ---" << endl;

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
void    F_WCS_TANSIP_WCS_CR(int DIR,CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,NUM,FNUM;
    double **dx[2],*Coef[2];

    cout << "--- WCS_TANSIP : CALCULATING GLOVAL WCS : SET CRPIX and CRVAL ---" << endl;
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
    cout << "--- WCS_TANSIP : CALCULATING GLOVAL WCS :  SIP FITTING ---" << endl;
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
    cout << "--- WCS_TANSIP : CALCULATING GLOVAL WCS : PSIP FITTING ---" << endl;
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
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    delete [] dx[0][NUM];
    delete [] dx[1][NUM];
    }
    delete [] dx[0];
    delete [] dx[1];
    
//--------------------------------------------------
}
void    F_WCS_TANSIP_WCS_GCHECK(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,FNUM;
    double X[2],Y[2],Z[2];
    double *RMS[4];

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
        Y[0]=CSIP->CD[0][0]*(F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[0],X)+X[0])+CSIP->CD[0][1]*(F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[1],X)+X[1]);
        Y[1]=CSIP->CD[1][0]*(F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[0],X)+X[0])+CSIP->CD[1][1]*(F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[1],X)+X[1]);
        PAIR[NUM].GxSIPErr=Y[0]-PAIR[NUM].xI;
        PAIR[NUM].GySIPErr=Y[1]-PAIR[NUM].yI;
        RMS[0][FNUM]=PAIR[NUM].GxSIPErr;
        RMS[1][FNUM]=PAIR[NUM].GySIPErr;
        Z[0]=CSIP->InvCD[0][0]*Y[0]+CSIP->InvCD[0][1]*Y[1];
        Z[1]=CSIP->InvCD[1][0]*Y[0]+CSIP->InvCD[1][1]*Y[1];
        PAIR[NUM].GxLErr=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP->SIP_ABP[0],Z)+Z[0]-PAIR[NUM].xCRPIX;
        PAIR[NUM].GyLErr=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP->SIP_ABP[1],Z)+Z[1]-PAIR[NUM].yCRPIX;
//
        X[0]=CSIP->InvCD[0][0]*PAIR[NUM].xI+CSIP->InvCD[0][1]*PAIR[NUM].yI;
        X[1]=CSIP->InvCD[1][0]*PAIR[NUM].xI+CSIP->InvCD[1][1]*PAIR[NUM].yI;
        Y[0]=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP->SIP_ABP[0],X)+X[0];
        Y[1]=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP->SIP_ABP[1],X)+X[1];
        PAIR[NUM].GxPSIPErr=Y[0]-PAIR[NUM].xCRPIX;
        PAIR[NUM].GyPSIPErr=Y[1]-PAIR[NUM].yCRPIX;
        RMS[2][FNUM]=PAIR[NUM].GxPSIPErr;
        RMS[3][FNUM]=PAIR[NUM].GyPSIPErr;
        Z[0]=CSIP->CD[0][0]*(F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[0],Y)+Y[0])+CSIP->CD[0][1]*(F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[1],Y)+Y[1]);
        Z[1]=CSIP->CD[1][0]*(F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[0],Y)+Y[0])+CSIP->CD[1][1]*(F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[1],Y)+Y[1]);
        PAIR[NUM].GxIErr=Z[0]-PAIR[NUM].xI;
        PAIR[NUM].GyIErr=Z[1]-PAIR[NUM].yI;
//cout << PAIR[NUM].GxSIPErr << "	"  << PAIR[NUM].GySIPErr << "	"  << PAIR[NUM].GxPSIPErr << "	"  << PAIR[NUM].GyPSIPErr << endl;
//cout << PAIR[NUM].GxLErr << "	"  << PAIR[NUM].GyLErr << "	"  << PAIR[NUM].GxIErr << "	"  << PAIR[NUM].GyIErr << endl;
//predict check 
        X[0]=PAIR[NUM].xI;
        X[1]=PAIR[NUM].yI;
        PAIR[NUM].PREDICTxErr=F_CALCVALUE(CSIP->PREDICT_SIP_P_ORDER,CSIP->PREDICT_SIP_ABP[0],X)-PAIR[NUM].xCRPIX;
        PAIR[NUM].PREDICTyErr=F_CALCVALUE(CSIP->PREDICT_SIP_P_ORDER,CSIP->PREDICT_SIP_ABP[1],X)-PAIR[NUM].yCRPIX;
//cout << PAIR[NUM].PREDICTxErr << "	" << PAIR[NUM].PREDICTyErr <<endl;
//
        FNUM++;
    }


    F_RMS(FNUM,RMS[0],CSIP->SIP_AB_GErr[0]);
    F_RMS(FNUM,RMS[1],CSIP->SIP_AB_GErr[1]);
    F_RMS(FNUM,RMS[2],CSIP->SIP_ABP_GErr[0]);
    F_RMS(FNUM,RMS[3],CSIP->SIP_ABP_GErr[1]);
//--------------------------------------------------
    cout << "--- GLOBAL FITTING STATISTICS --------------------" <<endl;
    cout << scientific;
    cout << "REFERENCE NUM: " << FNUM<< endl;
    cout << "CRPIX(pix)   : " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1]<< endl;
    cout << "CRVAL(dec)   : " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1]<< endl;
    cout << "CD_1_1       : " << CSIP->CD[0][0] << endl;
    cout << "CD_1_2       : " << CSIP->CD[0][1] << endl;
    cout << "CD_2_1       : " << CSIP->CD[1][0] << endl;
    cout << "CD_2_2       : " << CSIP->CD[1][1] << endl;
    cout << "InvCD_1_1    : " << CSIP->InvCD[0][0] << endl;
    cout << "InvCD_1_2    : " << CSIP->InvCD[0][1] << endl;
    cout << "InvCD_2_1    : " << CSIP->InvCD[1][0] << endl;
    cout << "InvCD_2_2    : " << CSIP->InvCD[1][1] << endl;
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
    cout << " SIPGxErrAVE : " << CSIP->SIP_AB_GErr[0][0] << "	(dec)"<< endl;
    cout << " SIPGxErrRMS : " << CSIP->SIP_AB_GErr[0][1] << "	(dec)" << endl;
    cout << " SIPGyErrAVE : " << CSIP->SIP_AB_GErr[1][0] << "	(dec)" << endl;
    cout << " SIPGyErrRMS : " << CSIP->SIP_AB_GErr[1][1] << "	(dec)" << endl;
    cout << "PSIPGxErrAVE : " << CSIP->SIP_ABP_GErr[0][0] << "	(pix)" << endl;
    cout << "PSIPGxErrRMS : " << CSIP->SIP_ABP_GErr[0][1] << "	(pix)" << endl;
    cout << "PSIPGyErrAVE : " << CSIP->SIP_ABP_GErr[1][0] << "	(pix)" << endl;
    cout << "PSIPGyErrRMS : " << CSIP->SIP_ABP_GErr[1][1] << "	(pix)" << endl;
    cout << "--------------------------------------------------" <<endl;
    cout << endl;

//--------------------------------------------------
    for(NUM=0;NUM<4;NUM++)
    delete [] RMS[NUM];
}
