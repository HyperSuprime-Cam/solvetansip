//------------------------------------------------------------
//WCS_TANSIP.cc
//main program for wcs in pipeline
//
//Last modification : 2010/04/01
//------------------------------------------------------------
#include<iostream>
#include<cmath>
#include<string.h>
#include<omp.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
void    F_WCS_TANSIP_GPOLYNOMIALFITTING(int NUMALL,int ORDER, int VARIABLE, int FUNCTION, CL_PAIR *PAIR, double *Coef[2]);
void    F_InvPROJECTION(double *Pdeg,double *Cdeg,double *PPOINT);
void    F_WCS_TANSIP(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    cout << "--------------------------------------------------" << endl;
    cout << "--- WCS_TANSIP ---" << endl;

//--------------------------------------------------
    cout << "--- WCS_TANSIP : SET ---" << endl;
    F_WCS_TANSIP_SET(&APROP,CPROP,PAIR,CSIP);
    if(APROP.CHECKPARAM == 1){
    cout << "Error : in parameters" << endl;
    }else{
//--------------------------------------------------
    cout << "--- WCS_TANSIP : DETERMINING CCD POSITION ---" << endl;
    F_WCS_TANSIP_GPOS(&APROP,CPROP,PAIR,CSIP);

//--------------------------------------------------
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS ---" << endl;
    F_WCS_TANSIP_WCS(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);

//--------------------------------------------------
    cout << "--- WCS_TANSIP : CALCULATING LOCAL CCD ---" << endl;
    F_WCS_TANSIP_CCD(APROP,CPROP,PAIR,CSIP);

//--------------------------------------------------
    }
}
void    F_WCS_TANSIP_SETxG              (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].xG=CPROP[PAIR[NUM].CHIPID].GLOB_POS[0]+PAIR[NUM].xL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].yL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].yG=CPROP[PAIR[NUM].CHIPID].GLOB_POS[1]+PAIR[NUM].yL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].xL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
    }
}
void    F_WCS_TANSIP_SETxCRVAL          (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].xCRVAL=CSIP->InvCD[0][0]*PAIR[NUM].xI+CSIP->InvCD[0][1]*PAIR[NUM].yI;
        PAIR[NUM].yCRVAL=CSIP->InvCD[1][0]*PAIR[NUM].xI+CSIP->InvCD[1][1]*PAIR[NUM].yI;
    }
}
void    F_WCS_TANSIP_SETxCRPIX          (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].xCRPIX=PAIR[NUM].xG-CSIP->CRPIX[0];
        PAIR[NUM].yCRPIX=PAIR[NUM].yG-CSIP->CRPIX[1];
    }
}
void    F_WCS_TANSIP_CENTERofOBJECTS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,FNUM=0;
    double CRPIXAVE[2]={0};

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
        CRPIXAVE[0]+=PAIR[NUM].xG;
        CRPIXAVE[1]+=PAIR[NUM].yG;
        FNUM++;
    }
    CSIP->CRPIX[0]=CRPIXAVE[0]/FNUM;
    CSIP->CRPIX[1]=CRPIXAVE[1]/FNUM;
}
void    F_WCS_TANSIP_CR(int DIR,CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

    if(DIR==0){
    F_WCS_TANSIP_GPOLYNOMIALFITTING(APROP.NUMREFALL,APROP.SIP_ORDER,3,0,PAIR,CSIP->TCoef);
    }else{
    F_WCS_TANSIP_GPOLYNOMIALFITTING(APROP.NUMREFALL,APROP.SIP_P_ORDER,1,4,PAIR,CSIP->TPCoef);
    }

    if(DIR==0){
        CSIP->CRVAL[0]=CSIP->TCoef[0][0];
        CSIP->CRVAL[1]=CSIP->TCoef[1][0];
    }else{
        CSIP->CRPIX[0]=CSIP->TPCoef[0][0];
        CSIP->CRPIX[1]=CSIP->TPCoef[1][0];
    }

}
void    F_WCS_TANSIP_PROJECTION(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM;
    double PPOINT[2],Pdeg[2],Cdeg[2];

    PPOINT[0]=CSIP->CRVAL[0];
    PPOINT[1]=CSIP->CRVAL[1];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        Cdeg[0]=PAIR[NUM].RA;
        Cdeg[1]=PAIR[NUM].DEC;
        F_PROJECTION(Cdeg,Pdeg,PPOINT);
        PAIR[NUM].xI=Pdeg[0];
        PAIR[NUM].yI=Pdeg[1];
    }
}
void    F_WCS_TANSIP_GPOLYNOMIALFITTING(int NUMALL,int ORDER, int VARIABLE, int FUNCTION, CL_PAIR *PAIR, double *Coef[2]){
//cout <<"F_WCS_TANSIP_GPOLYNOMIALFITTING"<<endl;
    int NUM,FNUM=0,ERROR=0;
    double **dx[2];

//--------------------------------------------------
    dx[0]=new double*[NUMALL];
    dx[1]=new double*[NUMALL];
    for(NUM=0;NUM<NUMALL;NUM++){
    dx[0][NUM]=new double[3];
    dx[1][NUM]=new double[3];
    }
    for(NUM=0;NUM<(ORDER+1)*(ORDER+2);NUM++)
    Coef[0][NUM]=Coef[1][NUM]=0;

//--------------------------------------------------
    if(VARIABLE==0||VARIABLE==1||VARIABLE==2||VARIABLE==3||VARIABLE==4||VARIABLE==5){
    }else{
    ERROR=1;
    }
    if(FUNCTION==0||FUNCTION==1||FUNCTION==2||FUNCTION==3||FUNCTION==4||FUNCTION==5||FUNCTION==6||FUNCTION==7){
    }else{
    ERROR=1;
    }

    if(ERROR==0){
    for(NUM=0;NUM<NUMALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
	      if(VARIABLE==0){
            dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].RA;
            dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].DEC;
        }else if(VARIABLE==1){
            dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].xI;
            dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].yI;
        }else if(VARIABLE==2){
            dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].xCRVAL;
            dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].yCRVAL;
        }else if(VARIABLE==3){
            dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].xCRPIX;
            dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].yCRPIX;
        }else if(VARIABLE==4){
            dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].xG;
            dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].yG;
        }else if(VARIABLE==5){
            dx[0][FNUM][0]=dx[1][FNUM][0]=PAIR[NUM].xL;
            dx[0][FNUM][1]=dx[1][FNUM][1]=PAIR[NUM].yL;
        }
	      if(FUNCTION==0){
            dx[0][FNUM][2]=PAIR[NUM].RA;
            dx[1][FNUM][2]=PAIR[NUM].DEC;
        }else if(FUNCTION==1){
            dx[0][FNUM][2]=PAIR[NUM].xI;
            dx[1][FNUM][2]=PAIR[NUM].yI;
        }else if(FUNCTION==2){
            dx[0][FNUM][2]=PAIR[NUM].xCRVAL;
            dx[1][FNUM][2]=PAIR[NUM].yCRVAL;
        }else if(FUNCTION==3){
            dx[0][FNUM][2]=PAIR[NUM].xCRPIX;
            dx[1][FNUM][2]=PAIR[NUM].yCRPIX;
        }else if(FUNCTION==4){
            dx[0][FNUM][2]=PAIR[NUM].xG;
            dx[1][FNUM][2]=PAIR[NUM].yG;
        }else if(FUNCTION==5){
            dx[0][FNUM][2]=PAIR[NUM].xL;
            dx[1][FNUM][2]=PAIR[NUM].yL;
        }else if(FUNCTION==6){
            dx[0][FNUM][2]=PAIR[NUM].CAMERA_MAGNIFICATION;
            dx[1][FNUM][2]=PAIR[NUM].CAMERA_ROTATION;
        }else if(FUNCTION==7){
            dx[0][FNUM][2]=PAIR[NUM].CAMERA_SHEAR[0];
            dx[1][FNUM][2]=PAIR[NUM].CAMERA_SHEAR[1];
        }
        FNUM++;
    }
        #pragma omp parallel num_threads(2)
        #pragma omp sections
        {
            #pragma omp section
            {
                F_LS2(FNUM,ORDER,dx[0],Coef[0]);
            }
            #pragma omp section
            {
                F_LS2(FNUM,ORDER,dx[1],Coef[1]);
            }
        }
    }else{
        cout << "---------------------------------------------" << endl;
        cout << "ERROR : in F_WCS_TANSIP_GPOLYNOMIALFITTING" << endl;
        cout << "        VARIBLE or FUNCTION" << endl;
        cout << "---------------------------------------------" << endl;
    }

//--------------------------------------------------
    for(NUM=0;NUM<NUMALL;NUM++){
    delete [] dx[0][NUM];
    delete [] dx[1][NUM];
    }
    delete [] dx[0];
    delete [] dx[1];
}
void    F_WCS_TANSIP_SETSIP(CL_APROP APROP,CL_CSIP* CSIP){

    CSIP->CD[0][0]=CSIP->TCoef[0][1*(APROP.SIP_ORDER+1)+0];
    CSIP->CD[0][1]=CSIP->TCoef[0][0*(APROP.SIP_ORDER+1)+1];
    CSIP->CD[1][0]=CSIP->TCoef[1][1*(APROP.SIP_ORDER+1)+0];
    CSIP->CD[1][1]=CSIP->TCoef[1][0*(APROP.SIP_ORDER+1)+1]; 

    CSIP->InvCD[0][0]= CSIP->CD[1][1]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    CSIP->InvCD[0][1]=-CSIP->CD[0][1]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    CSIP->InvCD[1][0]=-CSIP->CD[1][0]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    CSIP->InvCD[1][1]= CSIP->CD[0][0]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);

    int i,j,ij;
    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        CSIP->SIP_AB[0][ij]=CSIP->InvCD[0][0]*CSIP->TCoef[0][ij]+CSIP->InvCD[0][1]*CSIP->TCoef[1][ij];
        CSIP->SIP_AB[1][ij]=CSIP->InvCD[1][0]*CSIP->TCoef[0][ij]+CSIP->InvCD[1][1]*CSIP->TCoef[1][ij];
        ij++;	
    }
    CSIP->SIP_AB[0][1*(APROP.SIP_ORDER+1)+0]-=1.0;
    CSIP->SIP_AB[1][0*(APROP.SIP_ORDER+1)+1]-=1.0;
}
void    F_WCS_TANSIP_SETPSIP(CL_APROP APROP,CL_CSIP* CSIP){
    int i,j,ij;
    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        CSIP->SIP_ABP[0][ij]=CSIP->TPCoef[0][ij];
        CSIP->SIP_ABP[1][ij]=CSIP->TPCoef[1][ij];
        ij++;	
    }

    CSIP->SIP_ABP[0][1*(APROP.SIP_P_ORDER+1)+0]-=1.0;
    CSIP->SIP_ABP[1][0*(APROP.SIP_P_ORDER+1)+1]-=1.0;
}
void    F_WCS_TANSIP_PIXTOSKY(double X[2],double Y[2],CL_APROP APROP,CL_CSIP *CSIP){
    double XX[2],YY[2],PPOINT[2];

    XX[0]=X[0]-CSIP->CRPIX[0];
    XX[1]=X[1]-CSIP->CRPIX[1];
    YY[0]=F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(APROP.SIP_ORDER,CSIP->SIP_AB[1],XX)+XX[1];
    XX[0]=CSIP->CD[0][0]*YY[0]+CSIP->CD[0][1]*YY[1];
    XX[1]=CSIP->CD[1][0]*YY[0]+CSIP->CD[1][1]*YY[1];
    PPOINT[0]=CSIP->CRVAL[0];
    PPOINT[1]=CSIP->CRVAL[1];
    F_InvPROJECTION(XX,Y,PPOINT);
}
void    F_WCS_TANSIP_SKYTOPIX(double X[2],double Y[2],CL_APROP APROP,CL_CSIP *CSIP){
    double XX[2],YY[2],PPOINT[2];

    PPOINT[0]=CSIP->CRVAL[0];
    PPOINT[1]=CSIP->CRVAL[1];
    F_PROJECTION(X,YY,PPOINT);
    XX[0]=CSIP->InvCD[0][0]*YY[0]+CSIP->InvCD[0][1]*YY[1];
    XX[1]=CSIP->InvCD[1][0]*YY[0]+CSIP->InvCD[1][1]*YY[1];
    YY[0]=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP->SIP_ABP[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP->SIP_ABP[1],XX)+XX[1];
    Y[0]=XX[0]+CSIP->CRPIX[0];
    Y[1]=XX[1]+CSIP->CRPIX[1];
}
