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
void    F_WCS_TANSIP_WCS_PREDICTCHECK   (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET GLOBAL POSITION ---" << endl;
    F_WCS_TANSIP_SETxG(APROP,CPROP,PAIR,CSIP);
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET BASE ---" << endl;
    F_WCS_TANSIP_WCS_SETBASE(APROP,CPROP,PAIR,CSIP);
    if(strcmp(APROP.CRPIXMODE,"VAL")==0||strcmp(APROP.CRPIXMODE,"OAXIS")==0){
        cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PROJECTION and xI ---" << endl;
        F_WCS_TANSIP_PROJECTION(APROP,CPROP,PAIR,CSIP);
        cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : OBTAINING CRPIX ---" << endl;
        F_WCS_TANSIP_CR(1,APROP,CPROP,PAIR,CSIP);
        cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRPIX POSITION ---" << endl;
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
    }else{
        cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRPIX POSITION ---" << endl;
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
        cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : OBTAINING CRVAL ---" << endl;
        F_WCS_TANSIP_CR(0,APROP,CPROP,PAIR,CSIP);
        cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PROJECTION and xI ---" << endl;
        F_WCS_TANSIP_PROJECTION(APROP,CPROP,PAIR,CSIP);
    }
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SIP FITTING---" << endl;
    F_WCS_TANSIP_WCS_SIPFIT (APROP,CPROP,PAIR,CSIP);
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRVAL POSITION ---" << endl;
    F_WCS_TANSIP_SETxCRVAL(APROP,CPROP,PAIR,CSIP);

    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : REJECTION ---" << endl;
    F_WCS_TANSIP_WCS_REJECTION(APROP,CPROP,PAIR,CSIP);
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : Re-SIP FITTING---" << endl;
    F_WCS_TANSIP_WCS_SIPFIT (APROP,CPROP,PAIR,CSIP);
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET CRVAL POSITION ---" << endl;
    F_WCS_TANSIP_SETxCRVAL(APROP,CPROP,PAIR,CSIP);
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : PSIP FITTING---" << endl;
    F_WCS_TANSIP_WCS_PSIPFIT(APROP,CPROP,PAIR,CSIP);
    cout <<endl;
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : CAMERA DISTORTION---" << endl;
    F_WCS_TANSIP_WCS_CAMERADIST(APROP,CPROP,PAIR,CSIP);
    F_WCS_TANSIP_WCS_SIPDIST(APROP,CPROP,PAIR,CSIP);
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : OBTAINING OPTIC AXIS---" << endl;
    F_WCS_TANSIP_WCS_OPTICAXIS(APROP,CPROP,PAIR,CSIP);
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : GLOBAL CHECK---" << endl;
    F_WCS_TANSIP_WCS_GCHECK(APROP,CPROP,PAIR,CSIP);
    F_WCS_TANSIP_WCS_PREDICTCHECK(APROP,CPROP,PAIR,CSIP);
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
        cout << "ASSIGNED CRPIX ( " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1] << " )"<< endl;
    }else if(strcmp(APROP.CRPIXMODE,"VAL")==0){
        CSIP->CRVAL[0]=APROP.CRVAL[0];
        CSIP->CRVAL[1]=APROP.CRVAL[1];
        cout << "ASSIGNED CRVAL ( " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1] << " )"<< endl;
    }else if(strcmp(APROP.CRPIXMODE,"AUTO")==0){
        F_WCS_TANSIP_CENTERofOBJECTS(APROP,CPROP,PAIR,CSIP);
        cout << "AUTO MODE CRPIX ( " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1] << " )"<< endl;
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
        cout << "OAXIS MODE CRVAL ( " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1] << " )"<< endl;
        cout << "OAXIS MODE CRPIX ( " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1] << " )"<< endl;
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
    double *RMS[2];

    for(NUM=0;NUM<2;NUM++)
    RMS[NUM] = new double[APROP.NUMREFALL];

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

    cout << "REJECTED NUM : " << REJNUM << endl;
//--------------------------------------------------
    for(NUM=0;NUM<2;NUM++)
    delete [] RMS[NUM];
}
#include<fstream>
void    F_WCS_TANSIP_WCS_CAMERADIST(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM;
/*char fout[100];
ofstream temp;

sprintf(fout,"distortion_check.dat");
temp.open(fout);
cout << "temprary output : " << fout << endl;*/

    int i,j,ij;
    double *dPSIP[2][2],*PSIP[2],xI[2];
     PSIP[0]    = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
     PSIP[1]    = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    dPSIP[0][0] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    dPSIP[0][1] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    dPSIP[1][0] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];
    dPSIP[1][1] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+2)];

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
//temp << PAIR[NUM].ID << "	" << PAIR[NUM].CHIPID << "	" << PAIR[NUM].xL << "	" << PAIR[NUM].yL << "	" << PAIR[NUM].RA << "	" << PAIR[NUM].DEC << "	" << PAIR[NUM].xG << "	" << PAIR[NUM].yG << "	" << PAIR[NUM].CAMERA_MAGNIFICATION << "	" << PAIR[NUM].CAMERA_SHEAR[0] << "	" << PAIR[NUM].CAMERA_SHEAR[1] << "	" << PAIR[NUM].CAMERA_ROTATION << endl;
    }
//temp.close();

//--------------------------------------------------
    delete []  PSIP[0];
    delete []  PSIP[1];
    delete [] dPSIP[0][0];
    delete [] dPSIP[0][1];
    delete [] dPSIP[1][0];
    delete [] dPSIP[1][1];
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
    double *dPSIP[2],*ddPSIP[2][2],*PSIP;
    double X[2],dX[2],ddX[2];

     PSIP    = new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    dPSIP[0] = new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    dPSIP[1] = new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    ddPSIP[0][0] = new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    ddPSIP[0][1] = new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    ddPSIP[1][0] = new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];
    ddPSIP[1][1] = new double[(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2)];

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
    delete []  PSIP;
    delete [] dPSIP[0];
    delete [] dPSIP[1];
    delete [] ddPSIP[0][0];
    delete [] ddPSIP[0][1];
    delete [] ddPSIP[1][0];
    delete [] ddPSIP[1][1];
}
void    F_WCS_TANSIP_WCS_GCHECK(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,FNUM;
    double X[2],Y[2];
    double *RMS[4];
char fout [100];
ofstream temp;

sprintf(fout,"reference_check.dat");
temp.open(fout);
cout << "temprary output : " << fout << endl;

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
    cout << "REFERENCE NUM: " << CSIP->REFNUM<< endl;
    cout << "FITTING   NUM: " << CSIP->FITNUM<< endl;
    cout << fixed;
    cout << "CRPIX(pix)   : " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1]<< endl;
    cout << "CRVAL(dec)   : " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1]<< endl;
    cout << "OAPIX(pix)   : " << CSIP->OAPIX[0] << " , " << CSIP->OAPIX[1]<< endl;
    cout << "OAVAL(dec)   : " << CSIP->OAVAL[0] << " , " << CSIP->OAVAL[1]<< endl;
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
/*    cout << "  SIPx[0][0] : " << CSIP->SIP_AB[0][0] << endl;
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
*/    cout << " SIPGxErrAVE : " << CSIP->SIP_AB_GErr[0][0] << "	(pix)"<< endl;
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
    double **Dx[2];
char fout[100];
ofstream temp;

sprintf(fout,"predict_check.dat");
temp.open(fout);
cout << "temprary output : " << fout << endl;

    for(i=0;i<APROP.SIP_P_ORDER*APROP.SIP_P_ORDER+1;i++)
    CSIP->TPCoef[0][i]=CSIP->TPCoef[1][i]=0;

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
            F_LS2(FNUM,APROP.SIP_P_ORDER,Dx[0],CSIP->TPCoef[0]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,APROP.SIP_P_ORDER,Dx[1],CSIP->TPCoef[1]);
        }
    }

    CSIP->InvSS[0][0]=CSIP->TPCoef[0][1*(APROP.SIP_P_ORDER+1)+0];
    CSIP->InvSS[0][1]=CSIP->TPCoef[0][0*(APROP.SIP_P_ORDER+1)+1];
    CSIP->InvSS[1][0]=CSIP->TPCoef[1][1*(APROP.SIP_P_ORDER+1)+0];
    CSIP->InvSS[1][1]=CSIP->TPCoef[1][0*(APROP.SIP_P_ORDER+1)+1];

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
        CSIP->SIP_ABD[0][ij]= CSIP->SS[0][0]*CSIP->TPCoef[0][ij]+ CSIP->SS[0][1]*CSIP->TPCoef[1][ij];
        CSIP->SIP_ABD[1][ij]= CSIP->SS[1][0]*CSIP->TPCoef[0][ij]+ CSIP->SS[1][1]*CSIP->TPCoef[1][ij];
//cout << CSIP->SIP_ABD[0][ij] << "	" << CSIP->SIP_ABD[1][ij] << endl;
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

    for(FNUM=0;FNUM<APROP.NUMREFALL;FNUM++){
    delete [] Dx[0][FNUM];
    delete [] Dx[1][FNUM];
    }
    delete [] Dx[0];
    delete [] Dx[1];
}
