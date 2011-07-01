//------------------------------------------------------------
//WCS_TANSIP_WCS.cc
//Calculating WCS of global
//
//Last modification : 2010/04/01
//------------------------------------------------------------
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<string.h>
#include<omp.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
void    F_WCS_TANSIP_SETxG              (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_SETxCRVAL          (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_SETxCRPIX          (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_CENTERofOBJECTS    (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOLYNOMIALFITTING (int NUMALL,int ORDER, int VARIABLE, int FUNCTION, CL_PAIR *PAIR, double *Coef[2]);
void    F_WCS_TANSIP_PROJECTION         (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_CR         (int DIR,CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_SETSIP             (CL_APROP APROP,CL_CSIP* CSIP);
void    F_WCS_TANSIP_SETPSIP            (CL_APROP APROP,CL_CSIP* CSIP);
void    F_WCS_TANSIP_PIXTOSKY           (double X[2],double Y[2],CL_APROP APROP,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_SETBASE        (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_SIPFIT         (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_PSIPFIT        (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_REJECTION      (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_CAMERADIST     (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_SIPDIST        (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_PSIPDIST       (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_OPTICAXIS      (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_GCHECK         (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET GLOBAL POSITION ---" << endl;
    F_WCS_TANSIP_SETxG(APROP,CPROP,PAIR,CSIP);

//-----
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET BASE ---" << endl;
    F_WCS_TANSIP_WCS_SETBASE(APROP,CPROP,PAIR,CSIP);
    if(strcmp(APROP.CRPIXMODE,"VAL")==0||strcmp(APROP.CRPIXMODE,"OAXIS")==0){
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PROJECTION and xI ---" << endl;
        F_WCS_TANSIP_PROJECTION(APROP,CPROP,PAIR,CSIP);
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : OBTAINING CRPIX ---" << endl;
        F_WCS_TANSIP_CR(1,APROP,CPROP,PAIR,CSIP);
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRPIX POSITION ---" << endl;
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
    }else{
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRPIX POSITION ---" << endl;
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : OBTAINING CRVAL ---" << endl;
        F_WCS_TANSIP_CR(0,APROP,CPROP,PAIR,CSIP);
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PROJECTION and xI ---" << endl;
        F_WCS_TANSIP_PROJECTION(APROP,CPROP,PAIR,CSIP);
    }
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SIP FITTING---" << endl;
    F_WCS_TANSIP_WCS_SIPFIT (APROP,CPROP,PAIR,CSIP);
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRVAL POSITION ---" << endl;
    F_WCS_TANSIP_SETxCRVAL(APROP,CPROP,PAIR,CSIP);
//-----

    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : REJECTION ---" << endl;
    F_WCS_TANSIP_WCS_REJECTION(APROP,CPROP,PAIR,CSIP);

//-----
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET BASE ---" << endl;
    F_WCS_TANSIP_WCS_SETBASE(APROP,CPROP,PAIR,CSIP);
    if(strcmp(APROP.CRPIXMODE,"VAL")==0||strcmp(APROP.CRPIXMODE,"OAXIS")==0){
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PROJECTION and xI ---" << endl;
        F_WCS_TANSIP_PROJECTION(APROP,CPROP,PAIR,CSIP);
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : OBTAINING CRPIX ---" << endl;
        F_WCS_TANSIP_CR(1,APROP,CPROP,PAIR,CSIP);
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRPIX POSITION ---" << endl;
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
    }else{
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRPIX POSITION ---" << endl;
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : OBTAINING CRVAL ---" << endl;
        F_WCS_TANSIP_CR(0,APROP,CPROP,PAIR,CSIP);
        if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PROJECTION and xI ---" << endl;
        F_WCS_TANSIP_PROJECTION(APROP,CPROP,PAIR,CSIP);
    }
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SIP FITTING---" << endl;
    F_WCS_TANSIP_WCS_SIPFIT (APROP,CPROP,PAIR,CSIP);
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRVAL POSITION ---" << endl;
    F_WCS_TANSIP_SETxCRVAL(APROP,CPROP,PAIR,CSIP);
//-----

    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : Re-SIP FITTING---" << endl;
    F_WCS_TANSIP_WCS_SIPFIT (APROP,CPROP,PAIR,CSIP);
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRVAL POSITION ---" << endl;
    F_WCS_TANSIP_SETxCRVAL(APROP,CPROP,PAIR,CSIP);
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PSIP FITTING---" << endl;
    F_WCS_TANSIP_WCS_PSIPFIT(APROP,CPROP,PAIR,CSIP);
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : CAMERA DISTORTION---" << endl;
    F_WCS_TANSIP_WCS_CAMERADIST(APROP,CPROP,PAIR,CSIP);
    F_WCS_TANSIP_WCS_SIPDIST(APROP,CPROP,PAIR,CSIP);
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : OBTAINING OPTIC AXIS---" << endl;
    F_WCS_TANSIP_WCS_OPTICAXIS(APROP,CPROP,PAIR,CSIP);
    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : GLOBAL CHECK---" << endl;
    F_WCS_TANSIP_WCS_GCHECK(APROP,CPROP,PAIR,CSIP);

//--------------------------------------------------
//--------------------------------------------------
}
void    F_WCS_TANSIP_WCS_SETBASE(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
//SET CSIP parameters
    CSIP->SIP_AB_ORDER=APROP.SIP_ORDER;
    CSIP->SIP_ABP_ORDER=APROP.SIP_P_ORDER;
    CSIP->ID=APROP.CCDNUM;
    CSIP->REFNUM=APROP.NUMREFALL;

//SET CR
          if(strcmp(APROP.CRPIXMODE,"PIX")==0){
        CSIP->CRPIX[0]=APROP.CRPIX[0];
        CSIP->CRPIX[1]=APROP.CRPIX[1];
        if(APROP.STDOUT==2)cout << "ASSIGNED CRPIX ( " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1] << " )"<< endl;
    }else if(strcmp(APROP.CRPIXMODE,"VAL")==0){
        CSIP->CRVAL[0]=APROP.CRVAL[0];
        CSIP->CRVAL[1]=APROP.CRVAL[1];
        if(APROP.STDOUT==2)cout << "ASSIGNED CRVAL ( " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1] << " )"<< endl;
    }else if(strcmp(APROP.CRPIXMODE,"AUTO")==0){
        F_WCS_TANSIP_CENTERofOBJECTS(APROP,CPROP,PAIR,CSIP);
        if(APROP.STDOUT==2)cout << "AUTO MODE CRPIX ( " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1] << " )"<< endl;
    }else if(strcmp(APROP.CRPIXMODE,"OAXIS")==0){
        F_WCS_TANSIP_CENTERofOBJECTS(APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_CR(0,APROP,CPROP,PAIR,CSIP);

        for(;;){
            F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_PROJECTION(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_WCS_SIPFIT (APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_SETxCRVAL(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_WCS_PSIPFIT(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_WCS_CAMERADIST(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_WCS_SIPDIST(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_WCS_OPTICAXIS(APROP,CPROP,PAIR,CSIP);
            if(hypot(CSIP->CRPIX[0]-CSIP->OAPIX[0],CSIP->CRPIX[1]-CSIP->OAPIX[1])<pow(10.0,-3))
            break;
            CSIP->CRVAL[0]=CSIP->OAVAL[0];
            CSIP->CRVAL[1]=CSIP->OAVAL[1];
            CSIP->CRPIX[0]=CSIP->OAPIX[0];
            CSIP->CRPIX[1]=CSIP->OAPIX[1];
        }
        if(APROP.STDOUT==2)cout << "OAXIS MODE CRVAL ( " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1] << " )"<< endl;
        if(APROP.STDOUT==2)cout << "OAXIS MODE CRPIX ( " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1] << " )"<< endl;
    }
//--------------------------------------------------
}
void    F_WCS_TANSIP_WCS_SIPFIT (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,FNUM;

    F_WCS_TANSIP_GPOLYNOMIALFITTING(APROP.NUMREFALL,APROP.SIP_ORDER  ,3,1,PAIR,CSIP->TCoef);
    F_WCS_TANSIP_SETSIP(APROP,CSIP);

    FNUM=0;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1)
    FNUM++;
    CSIP->FITNUM=FNUM;
}
void    F_WCS_TANSIP_WCS_PSIPFIT(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

    F_WCS_TANSIP_GPOLYNOMIALFITTING(APROP.NUMREFALL,APROP.SIP_P_ORDER,2,3,PAIR,CSIP->TPCoef);
    F_WCS_TANSIP_SETPSIP(APROP,CSIP);

}
void    F_WCS_TANSIP_WCS_REJECTION(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,FNUM;
    double X[2],Y[2];
    double **RMS;

    RMS = F_NEWdouble2(2,APROP.NUMREFALL);

    FNUM=0;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
        X[0]=PAIR[NUM].xCRPIX;
        X[1]=PAIR[NUM].yCRPIX;
        Y[0]=F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[0],X)+X[0];
        Y[1]=F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[1],X)+X[1];
        PAIR[NUM].GxSIPErr=Y[0]-PAIR[NUM].xCRVAL;
        PAIR[NUM].GySIPErr=Y[1]-PAIR[NUM].yCRVAL;
        RMS[0][FNUM]=PAIR[NUM].GxSIPErr;
        RMS[1][FNUM]=PAIR[NUM].GySIPErr;
        FNUM++;
    }
    F_RMS(FNUM,RMS[0],CSIP->SIP_AB_GErr[0]);
    F_RMS(FNUM,RMS[1],CSIP->SIP_AB_GErr[1]);

    int REJNUM=0;

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1)
    if(fabs(PAIR[NUM].GxSIPErr)>APROP.CLIP_SIGMA*CSIP->SIP_AB_GErr[0][1]||fabs(PAIR[NUM].GySIPErr)>APROP.CLIP_SIGMA*CSIP->SIP_AB_GErr[1][1]){
        PAIR[NUM].FLAG=0;
        REJNUM++;
    }

    if(APROP.STDOUT==1||APROP.STDOUT==2)cout << "REJECTED NUM : " << REJNUM << endl;
//--------------------------------------------------
    F_DELdouble2(2,RMS);
}void    F_WCS_TANSIP_WCS_CAMERADIST(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM;

    int i,j,ij;
    double ***dPSIP,**PSIP,xI[2];
    dPSIP = F_NEWdouble3(2,2,(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2));
     PSIP = F_NEWdouble2(2,(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2));

    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        PSIP[0][ij]=CSIP->SIP_ABP[0][ij];
        PSIP[1][ij]=CSIP->SIP_ABP[1][ij];
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
    }

//--------------------------------------------------
    F_DELdouble3(2,2,dPSIP);
    F_DELdouble2(2,PSIP);
}
void    F_WCS_TANSIP_WCS_SIPDIST(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
//--------------------------------------------------
    int i,j,ij;
    F_WCS_TANSIP_GPOLYNOMIALFITTING(APROP.NUMREFALL,APROP.SIP_ORDER  ,3,6,PAIR,CSIP->TCoef);
    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        CSIP->SIP_MAG[ij]=CSIP->TCoef[0][ij];
        CSIP->SIP_ROT[ij]=CSIP->TCoef[1][ij];
        ij++;	
    }

    F_WCS_TANSIP_GPOLYNOMIALFITTING(APROP.NUMREFALL,APROP.SIP_ORDER  ,3,7,PAIR,CSIP->TCoef);
    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        CSIP->SIP_SHEAR[0][ij]=CSIP->TCoef[0][ij];
        CSIP->SIP_SHEAR[1][ij]=CSIP->TCoef[1][ij];
        ij++;	
    }
}
void    F_WCS_TANSIP_WCS_PSIPDIST(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
//--------------------------------------------------
    int i,j,ij;
    F_WCS_TANSIP_GPOLYNOMIALFITTING(APROP.NUMREFALL,APROP.SIP_P_ORDER  ,2,6,PAIR,CSIP->TPCoef);
    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        CSIP->PSIP_MAG[ij]=CSIP->TPCoef[0][ij];
        CSIP->PSIP_ROT[ij]=CSIP->TPCoef[1][ij];
        ij++;	
    }

    F_WCS_TANSIP_GPOLYNOMIALFITTING(APROP.NUMREFALL,APROP.SIP_P_ORDER  ,2,7,PAIR,CSIP->TPCoef);
    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        CSIP->PSIP_SHEAR[0][ij]=CSIP->TPCoef[0][ij];
        CSIP->PSIP_SHEAR[1][ij]=CSIP->TPCoef[1][ij];
        ij++;	
    }
}
void    F_WCS_TANSIP_WCS_OPTICAXIS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,j,ij;
    double *PSIP,**dPSIP,***ddPSIP;
    double X[2],dX[2],ddX[2];

      PSIP = F_NEWdouble1((APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2));
     dPSIP = F_NEWdouble2(2,(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2));
    ddPSIP = F_NEWdouble3(2,2,(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2));

    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
    PSIP[ij]=CSIP->SIP_MAG[ij];
    ij++;
    }

    F_DIFFSIP(APROP.SIP_ORDER, PSIP,dPSIP[0],dPSIP[1]);
    F_DIFFSIP(APROP.SIP_ORDER,dPSIP[0],ddPSIP[0][0],ddPSIP[0][1]);
    F_DIFFSIP(APROP.SIP_ORDER,dPSIP[1],ddPSIP[1][0],ddPSIP[1][1]);

    X[0]=0;
    X[1]=0;
    for(i=0;i<10;i++){
         dX[0]=F_CALCVALUE(APROP.SIP_ORDER, dPSIP[0],X);
         dX[1]=F_CALCVALUE(APROP.SIP_ORDER, dPSIP[1],X);
        ddX[0]=F_CALCVALUE(APROP.SIP_ORDER,ddPSIP[0][0],X);
        ddX[1]=F_CALCVALUE(APROP.SIP_ORDER,ddPSIP[1][1],X);
        if(hypot(dX[0]/ddX[0],dX[1]/ddX[1])<pow(10.0,-3.0))
        break;
        X[0]-=dX[0]/ddX[0];
        X[1]-=dX[1]/ddX[1];
    }
    CSIP->OAPIX[0]=X[0]+CSIP->CRPIX[0];
    CSIP->OAPIX[1]=X[1]+CSIP->CRPIX[1];
    F_WCS_TANSIP_PIXTOSKY(CSIP->OAPIX,CSIP->OAVAL,APROP,CSIP);

//--------------------------------------------------
    F_DELdouble1(PSIP);
    F_DELdouble2(2,dPSIP);
    F_DELdouble3(2,2,ddPSIP);
}
void    F_WCS_TANSIP_WCS_GCHECK(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,FNUM;
    double X[2],Y[2];
    double **RMS;

//--------------------------------------------------
    RMS = F_NEWdouble2(4,APROP.NUMREFALL);

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

        FNUM++;
    }

    F_RMS(FNUM,RMS[0],CSIP->SIP_AB_GErr[0]);
    F_RMS(FNUM,RMS[1],CSIP->SIP_AB_GErr[1]);
    F_RMS(FNUM,RMS[2],CSIP->SIP_ABP_GErr[0]);
    F_RMS(FNUM,RMS[3],CSIP->SIP_ABP_GErr[1]);
//--------------------------------------------------

    if(APROP.STDOUT==2){
    cout << "--- GLOBAL FITTING STATISTICS --------------------" <<endl;
    cout << "REFERENCE NUM: " << CSIP->REFNUM<< endl;
    cout << "FITTING   NUM: " << CSIP->FITNUM<< endl;
    cout << fixed;
    cout << "CRPIX(pix)   : " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1]<< endl;
    cout << "CRVAL(deg)   : " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1]<< endl;
    cout << "OAPIX(pix)   : " << CSIP->OAPIX[0] << " , " << CSIP->OAPIX[1]<< endl;
    cout << "OAVAL(deg)   : " << CSIP->OAVAL[0] << " , " << CSIP->OAVAL[1]<< endl;
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
    int i,j,ij;
    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1)
    cout << "  SIPx["<<i<<"]["<<j<<"] : "<< CSIP->SIP_AB[0][ij++]<<endl;
    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1)
    cout << "  SIPy["<<i<<"]["<<j<<"] : "<< CSIP->SIP_AB[1][ij++]<<endl;
    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1)
    cout << " PSIPx["<<i<<"]["<<j<<"] : "<< CSIP->SIP_ABP[0][ij++]<<endl;
    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1)
    cout << " PSIPy["<<i<<"]["<<j<<"] : "<< CSIP->SIP_ABP[1][ij++]<<endl;
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
    }
//--------------------------------------------------
    F_DELdouble2(4,RMS);
}
