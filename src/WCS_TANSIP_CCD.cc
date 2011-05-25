//------------------------------------------------------------
//WCS_TANSIP_CCD.cc
//Calculating WCS of each CCD from global
//
//Last modification : 2010/04/01
//------------------------------------------------------------
#include<iostream>
#include<cmath>
#include "hsc/meas/tansip/WCS_TANSIP.h"

#define PI (4*atan(1.0))
using namespace std;
void    F_SIPROT(int ORDER, double Theta, double *InCoef, double *OutCoef);
void    F_WCS_TANSIP_SETSIP(CL_APROP APROP,CL_CSIP* CSIP);
void    F_WCS_TANSIP_SETPSIP(CL_APROP APROP,CL_CSIP* CSIP);
void    F_WCS_TANSIP_CCD_LSIP(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_CCD_LCHECK(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_CCD(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

    F_WCS_TANSIP_CCD_LSIP(APROP,CPROP,PAIR,CSIP);
    F_WCS_TANSIP_CCD_LCHECK(APROP,CPROP,PAIR,CSIP);
}
void    F_WCS_TANSIP_CCD_LSIP(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,j,ij,ID,NUM;

    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        CSIP[APROP.CCDNUM].TCoef[0][ij]=CSIP[APROP.CCDNUM].CD[0][0]*CSIP[APROP.CCDNUM].SIP_AB[0][ij]+CSIP[APROP.CCDNUM].CD[0][1]*CSIP[APROP.CCDNUM].SIP_AB[1][ij];
        CSIP[APROP.CCDNUM].TCoef[1][ij]=CSIP[APROP.CCDNUM].CD[1][0]*CSIP[APROP.CCDNUM].SIP_AB[0][ij]+CSIP[APROP.CCDNUM].CD[1][1]*CSIP[APROP.CCDNUM].SIP_AB[1][ij];
        ij++;
    }
    CSIP[APROP.CCDNUM].TCoef[0][1*(APROP.SIP_ORDER+1)+0]+=CSIP[APROP.CCDNUM].CD[0][0];
    CSIP[APROP.CCDNUM].TCoef[0][0*(APROP.SIP_ORDER+1)+1]+=CSIP[APROP.CCDNUM].CD[0][1];
    CSIP[APROP.CCDNUM].TCoef[1][1*(APROP.SIP_ORDER+1)+0]+=CSIP[APROP.CCDNUM].CD[1][0];
    CSIP[APROP.CCDNUM].TCoef[1][0*(APROP.SIP_ORDER+1)+1]+=CSIP[APROP.CCDNUM].CD[1][1];

    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        CSIP[APROP.CCDNUM].TPCoef[0][ij]=CSIP[APROP.CCDNUM].SIP_ABP[0][ij];
        CSIP[APROP.CCDNUM].TPCoef[1][ij]=CSIP[APROP.CCDNUM].SIP_ABP[1][ij];
        ij++;
    }

    CSIP[APROP.CCDNUM].TPCoef[0][1*(APROP.SIP_P_ORDER+1)+0]+=1.0;
    CSIP[APROP.CCDNUM].TPCoef[1][0*(APROP.SIP_P_ORDER+1)+1]+=1.0;

    double IABP[2];

    for(ID=0;ID<APROP.CCDNUM;ID++){
        F_SIPROT(APROP.SIP_ORDER  ,CPROP[ID].GLOB_POS[2],CSIP[APROP.CCDNUM].TCoef[0] ,CSIP[ID].TCoef[0] );
        F_SIPROT(APROP.SIP_ORDER  ,CPROP[ID].GLOB_POS[2],CSIP[APROP.CCDNUM].TCoef[1] ,CSIP[ID].TCoef[1] );
        F_WCS_TANSIP_SETSIP(APROP,&CSIP[ID]);

        F_SIPROT(APROP.SIP_P_ORDER,CPROP[ID].GLOB_POS[2],CSIP[APROP.CCDNUM].TPCoef[0],CSIP[ID].TPCoef[0]);
        F_SIPROT(APROP.SIP_P_ORDER,CPROP[ID].GLOB_POS[2],CSIP[APROP.CCDNUM].TPCoef[1],CSIP[ID].TPCoef[1]);
        ij=0;
        for(i=0;i<APROP.SIP_P_ORDER+1;i++)
        for(j=0;j<APROP.SIP_P_ORDER+1;j++)
        if(i+j<APROP.SIP_P_ORDER+1){
            IABP[0]=CSIP[APROP.CCDNUM].CD[0][0]*CSIP[ID].TPCoef[0][ij]+CSIP[APROP.CCDNUM].CD[0][1]*CSIP[ID].TPCoef[1][ij];
            IABP[1]=CSIP[APROP.CCDNUM].CD[1][0]*CSIP[ID].TPCoef[0][ij]+CSIP[APROP.CCDNUM].CD[1][1]*CSIP[ID].TPCoef[1][ij];
            CSIP[ID].TPCoef[0][ij]=CSIP[ID].InvCD[0][0]*IABP[0]+CSIP[ID].InvCD[0][1]*IABP[1];
            CSIP[ID].TPCoef[1][ij]=CSIP[ID].InvCD[1][0]*IABP[0]+CSIP[ID].InvCD[1][1]*IABP[1];
            ij++;	
        }
        F_WCS_TANSIP_SETPSIP(APROP,&CSIP[ID]);

        F_SIPROT(APROP.SIP_P_ORDER,CPROP[ID].GLOB_POS[2],CSIP[APROP.CCDNUM].SIP_MAG,CSIP[ID].SIP_MAG);
        F_SIPROT(APROP.SIP_P_ORDER,CPROP[ID].GLOB_POS[2],CSIP[APROP.CCDNUM].SIP_SHEAR[0],CSIP[ID].SIP_SHEAR[0]);
        F_SIPROT(APROP.SIP_P_ORDER,CPROP[ID].GLOB_POS[2],CSIP[APROP.CCDNUM].SIP_SHEAR[1],CSIP[ID].SIP_SHEAR[1]);
        F_SIPROT(APROP.SIP_P_ORDER,CPROP[ID].GLOB_POS[2],CSIP[APROP.CCDNUM].SIP_ROT,CSIP[ID].SIP_ROT);

        CSIP[ID].ID=ID;
        CSIP[ID].REFNUM=CPROP[ID].NUMREF;
        CSIP[ID].CRVAL[0]=CSIP[APROP.CCDNUM].CRVAL[0];
        CSIP[ID].CRVAL[1]=CSIP[APROP.CCDNUM].CRVAL[1];
        CSIP[ID].OAVAL[0]=CSIP[APROP.CCDNUM].OAVAL[0];
        CSIP[ID].OAVAL[1]=CSIP[APROP.CCDNUM].OAVAL[1];
        CSIP[ID].CRPIX[0]=-(CPROP[ID].GLOB_POS[0]-CSIP[APROP.CCDNUM].CRPIX[0])*cos(CPROP[ID].GLOB_POS[2])-(CPROP[ID].GLOB_POS[1]-CSIP[APROP.CCDNUM].CRPIX[1])*sin(CPROP[ID].GLOB_POS[2]);
        CSIP[ID].CRPIX[1]=-(CPROP[ID].GLOB_POS[1]-CSIP[APROP.CCDNUM].CRPIX[1])*cos(CPROP[ID].GLOB_POS[2])+(CPROP[ID].GLOB_POS[0]-CSIP[APROP.CCDNUM].CRPIX[0])*sin(CPROP[ID].GLOB_POS[2]);
        CSIP[ID].OAPIX[0]=-(CPROP[ID].GLOB_POS[0]-CSIP[APROP.CCDNUM].OAPIX[0])*cos(CPROP[ID].GLOB_POS[2])-(CPROP[ID].GLOB_POS[1]-CSIP[APROP.CCDNUM].OAPIX[1])*sin(CPROP[ID].GLOB_POS[2]);
        CSIP[ID].OAPIX[1]=-(CPROP[ID].GLOB_POS[1]-CSIP[APROP.CCDNUM].OAPIX[1])*cos(CPROP[ID].GLOB_POS[2])+(CPROP[ID].GLOB_POS[0]-CSIP[APROP.CCDNUM].OAPIX[0])*sin(CPROP[ID].GLOB_POS[2]);
        CSIP[ID].SIP_AB_ORDER =CSIP[APROP.CCDNUM].SIP_AB_ORDER;
        CSIP[ID].SIP_ABP_ORDER=CSIP[APROP.CCDNUM].SIP_ABP_ORDER;
    }

//--------------------------------------------------
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        ID=PAIR[NUM].CHIPID;
        PAIR[NUM].xLCRPIX=PAIR[NUM].xL-CSIP[ID].CRPIX[0];
        PAIR[NUM].yLCRPIX=PAIR[NUM].yL-CSIP[ID].CRPIX[1];
        PAIR[NUM].xLCRVAL=CSIP[ID].InvCD[0][0]*PAIR[NUM].xI+CSIP[ID].InvCD[0][1]*PAIR[NUM].yI;
        PAIR[NUM].yLCRVAL=CSIP[ID].InvCD[1][0]*PAIR[NUM].xI+CSIP[ID].InvCD[1][1]*PAIR[NUM].yI;
    }

}
void    F_WCS_TANSIP_CCD_LCHECK(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int ID,NUM,*STNUM;
    double **RMS[4];

    cout << "--- WCS_TANSIP : CALCULATING LOCAL CCD : CALCULATING Err STATISTICS ---" << endl;    
//--------------------------------------------------
//Global Statictics of each CCD
    RMS[0] = new double*[APROP.CCDNUM+1];
    RMS[1] = new double*[APROP.CCDNUM+1];
    RMS[2] = new double*[APROP.CCDNUM+1];
    RMS[3] = new double*[APROP.CCDNUM+1];
    for(ID=0;ID<APROP.CCDNUM+1;ID++){
        RMS[0][ID] = new double[APROP.NUMREFALL];
        RMS[1][ID] = new double[APROP.NUMREFALL];
        RMS[2][ID] = new double[APROP.NUMREFALL];
        RMS[3][ID] = new double[APROP.NUMREFALL];
    }
    STNUM = new int[APROP.CCDNUM+1];
    for(ID=0;ID<APROP.CCDNUM+1;ID++)
    STNUM[ID]=0;

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
        ID=PAIR[NUM].CHIPID;
        RMS[0][ID][STNUM[ID]]=PAIR[NUM].GxSIPErr;
        RMS[1][ID][STNUM[ID]]=PAIR[NUM].GySIPErr;
        RMS[2][ID][STNUM[ID]]=PAIR[NUM].GxPSIPErr;
        RMS[3][ID][STNUM[ID]]=PAIR[NUM].GyPSIPErr;
        STNUM[ID]++;
    }
    for(ID=0;ID<APROP.CCDNUM;ID++){
        F_RMS(STNUM[ID],RMS[0][ID],CSIP[ID].SIP_AB_GErr[0]);
        F_RMS(STNUM[ID],RMS[1][ID],CSIP[ID].SIP_AB_GErr[1]);
        F_RMS(STNUM[ID],RMS[2][ID],CSIP[ID].SIP_ABP_GErr[0]);
        F_RMS(STNUM[ID],RMS[3][ID],CSIP[ID].SIP_ABP_GErr[1]); 
        CSIP[ID].FITNUM=STNUM[ID];
//cout << "  SIPxErr AVE : " << ID << " , "<< CSIP[ID].SIP_AB_GErr[0][0] << "	" << CSIP[ID].SIP_AB_GErr[0][1] << endl;
//cout << " PSIPxGErrAVE : " << ID << " , "<< CSIP[ID].SIP_ABP_GErr[0][0] << "	" << CSIP[ID].SIP_ABP_GErr[0][1] << endl;
    }
//--------------------------------------------------
//Err of local fitting
    double X[2],Y[2];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
        ID=PAIR[NUM].CHIPID;
        X[0]=PAIR[NUM].xLCRPIX;
        X[1]=PAIR[NUM].yLCRPIX;
        Y[0]=F_CALCVALUE(APROP.SIP_ORDER,CSIP[ID].SIP_AB[0],X)+X[0];
        Y[1]=F_CALCVALUE(APROP.SIP_ORDER,CSIP[ID].SIP_AB[1],X)+X[1];
        PAIR[NUM].LxSIPErr=Y[0]-PAIR[NUM].xLCRVAL;
        PAIR[NUM].LySIPErr=Y[1]-PAIR[NUM].yLCRVAL;
        PAIR[NUM].LxLErr=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP[ID].SIP_ABP[0],Y)+Y[0]-X[0];
        PAIR[NUM].LyLErr=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP[ID].SIP_ABP[1],Y)+Y[1]-X[1];
//
        X[0]=PAIR[NUM].xLCRVAL;
        X[1]=PAIR[NUM].yLCRVAL;
        Y[0]=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP[ID].SIP_ABP[0],X)+X[0];
        Y[1]=F_CALCVALUE(APROP.SIP_P_ORDER,CSIP[ID].SIP_ABP[1],X)+X[1];
        PAIR[NUM].LxPSIPErr=Y[0]-PAIR[NUM].xLCRPIX;
        PAIR[NUM].LyPSIPErr=Y[1]-PAIR[NUM].yLCRPIX;
        PAIR[NUM].LxIErr=F_CALCVALUE(APROP.SIP_ORDER,CSIP[ID].SIP_AB[0],Y)+Y[0]-X[0];
        PAIR[NUM].LyIErr=F_CALCVALUE(APROP.SIP_ORDER,CSIP[ID].SIP_AB[1],Y)+Y[1]-X[1];
//
//cout << Y[0] << "	" << PAIR[NUM].xCRPIX << endl;
//cout << "A:"<< PAIR[NUM].LxSIPErr << "	"  << PAIR[NUM].LySIPErr << "	"  << PAIR[NUM].LxPSIPErr << "	"  << PAIR[NUM].LyPSIPErr << endl;
//cout << "B:"<< PAIR[NUM].LxLErr << "	"  << PAIR[NUM].LyLErr << "	"  << PAIR[NUM].LxIErr << "	"  << PAIR[NUM].LyIErr << endl;
    }
//--------------------------------------------------
//ALL and EACH Local Statistics
    for(ID=0;ID<APROP.CCDNUM+1;ID++)
    STNUM[ID]=0;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    if(PAIR[NUM].FLAG == 1){
        ID=PAIR[NUM].CHIPID;
        RMS[0][ID][STNUM[ID]]=PAIR[NUM].LxSIPErr;
        RMS[1][ID][STNUM[ID]]=PAIR[NUM].LySIPErr;
        RMS[2][ID][STNUM[ID]]=PAIR[NUM].LxPSIPErr;
        RMS[3][ID][STNUM[ID]]=PAIR[NUM].LyPSIPErr;
        STNUM[ID]++;
        RMS[0][APROP.CCDNUM][STNUM[APROP.CCDNUM]]=PAIR[NUM].LxSIPErr;
        RMS[1][APROP.CCDNUM][STNUM[APROP.CCDNUM]]=PAIR[NUM].LySIPErr;
        RMS[2][APROP.CCDNUM][STNUM[APROP.CCDNUM]]=PAIR[NUM].LxPSIPErr;
        RMS[3][APROP.CCDNUM][STNUM[APROP.CCDNUM]]=PAIR[NUM].LyPSIPErr;
        STNUM[APROP.CCDNUM]++;
    }
    for(ID=0;ID<APROP.CCDNUM+1;ID++){
        F_RMS(STNUM[ID],RMS[0][ID],CSIP[ID].SIP_AB_LErr[0]);
        F_RMS(STNUM[ID],RMS[1][ID],CSIP[ID].SIP_AB_LErr[1]);
        F_RMS(STNUM[ID],RMS[2][ID],CSIP[ID].SIP_ABP_LErr[0]);
        F_RMS(STNUM[ID],RMS[3][ID],CSIP[ID].SIP_ABP_LErr[1]);    
//cout << " PSIPxLErrAVE : " << ID << " , "<< CSIP[ID].SIP_ABP_LErr[0][0] << "	" << CSIP[ID].SIP_ABP_LErr[0][1] << endl;
    }
//--------------------------------------------------
int i,j,ij;
    ID=0;
    cout << "--- LOCAL FITTING STATISTICS --------------------" <<endl;
    cout << "CHIPID       : " << ID << endl;
    cout << "REFERENCE NUM: " << CSIP[ID].REFNUM<< endl;
    cout << "FITTING   NUM: " << CSIP[ID].FITNUM<< endl;
    cout << "CRPIX(pix)   : " << CSIP[ID].CRPIX[0] << " , " << CSIP[ID].CRPIX[1]<< endl;
    cout << "CRVAL(dec)   : " << CSIP[ID].CRVAL[0] << " , " << CSIP[ID].CRVAL[1]<< endl;
    cout << "OAPIX(pix)   : " << CSIP[ID].OAPIX[0] << " , " << CSIP[ID].OAPIX[1]<< endl;
    cout << "OAVAL(dec)   : " << CSIP[ID].OAVAL[0] << " , " << CSIP[ID].OAVAL[1]<< endl;
    cout << "CD_1_1       : " << CSIP[ID].CD[0][0] << endl;
    cout << "CD_1_2       : " << CSIP[ID].CD[0][1] << endl;
    cout << "CD_2_1       : " << CSIP[ID].CD[1][0] << endl;
    cout << "CD_2_2       : " << CSIP[ID].CD[1][1] << endl;
    cout << "InvCD_1_1    : " << CSIP[ID].InvCD[0][0] << endl;
    cout << "InvCD_1_2    : " << CSIP[ID].InvCD[0][1] << endl;
    cout << "InvCD_2_1    : " << CSIP[ID].InvCD[1][0] << endl;
    cout << "InvCD_2_2    : " << CSIP[ID].InvCD[1][1] << endl;
ij=0;
for(i=0;i<APROP.SIP_ORDER+1;i++)
for(j=0;j<APROP.SIP_ORDER+1;j++)
if(i+j<APROP.SIP_ORDER+1)
cout << "  SIPx["<<i<<"]["<<j<<"] : "<< CSIP[ID].SIP_AB[0][ij++]<<endl;
ij=0;
for(i=0;i<APROP.SIP_ORDER+1;i++)
for(j=0;j<APROP.SIP_ORDER+1;j++)
if(i+j<APROP.SIP_ORDER+1)
cout << "  SIPy["<<i<<"]["<<j<<"] : "<< CSIP[ID].SIP_AB[1][ij++]<<endl;
ij=0;
for(i=0;i<APROP.SIP_P_ORDER+1;i++)
for(j=0;j<APROP.SIP_P_ORDER+1;j++)
if(i+j<APROP.SIP_ORDER+1)
cout << " PSIPx["<<i<<"]["<<j<<"] : "<< CSIP[ID].SIP_ABP[0][ij++]<<endl;
ij=0;
for(i=0;i<APROP.SIP_P_ORDER+1;i++)
for(j=0;j<APROP.SIP_P_ORDER+1;j++)
if(i+j<APROP.SIP_ORDER+1)
cout << " PSIPy["<<i<<"]["<<j<<"] : "<< CSIP[ID].SIP_ABP[1][ij++]<<endl;
/*    cout << "  SIPx[0][0] : " << CSIP[ID].SIP_AB[0][0] << endl;
    cout << "  SIPx[0][1] : " << CSIP[ID].SIP_AB[0][1] << endl;
    cout << "  SIPx[1][0] : " << CSIP[ID].SIP_AB[0][APROP.SIP_ORDER+1] << endl;
    cout << "  SIPx[1][1] : " << CSIP[ID].SIP_AB[0][APROP.SIP_ORDER+2] << endl;
    cout << "  SIPy[0][0] : " << CSIP[ID].SIP_AB[1][0] << endl;
    cout << "  SIPy[0][1] : " << CSIP[ID].SIP_AB[1][1] << endl;
    cout << "  SIPy[1][0] : " << CSIP[ID].SIP_AB[1][APROP.SIP_ORDER+1] << endl;
    cout << "  SIPy[1][1] : " << CSIP[ID].SIP_AB[1][APROP.SIP_ORDER+2] << endl;
    cout << " PSIPx[0][0] : " << CSIP[ID].SIP_ABP[0][0] << endl;
    cout << " PSIPx[0][1] : " << CSIP[ID].SIP_ABP[0][1] << endl;
    cout << " PSIPx[1][0] : " << CSIP[ID].SIP_ABP[0][APROP.SIP_ORDER+1] << endl;
    cout << " PSIPx[1][1] : " << CSIP[ID].SIP_ABP[0][APROP.SIP_ORDER+2] << endl;
    cout << " PSIPy[0][0] : " << CSIP[ID].SIP_ABP[1][0] << endl;
    cout << " PSIPy[0][1] : " << CSIP[ID].SIP_ABP[1][1] << endl;
    cout << " PSIPy[1][0] : " << CSIP[ID].SIP_ABP[1][APROP.SIP_ORDER+1] << endl;
    cout << " PSIPy[1][1] : " << CSIP[ID].SIP_ABP[1][APROP.SIP_ORDER+2] << endl;
*/    cout << " SIPGxErrAVE : " << CSIP[ID].SIP_AB_GErr[0][0] << "	(pix)"<< endl;
    cout << " SIPGxErrRMS : " << CSIP[ID].SIP_AB_GErr[0][1] << "	(pix)" << endl;
    cout << " SIPGyErrAVE : " << CSIP[ID].SIP_AB_GErr[1][0] << "	(pix)" << endl;
    cout << " SIPGyErrRMS : " << CSIP[ID].SIP_AB_GErr[1][1] << "	(pix)" << endl;
    cout << "PSIPGxErrAVE : " << CSIP[ID].SIP_ABP_GErr[0][0] << "	(pix)" << endl;
    cout << "PSIPGxErrRMS : " << CSIP[ID].SIP_ABP_GErr[0][1] << "	(pix)" << endl;
    cout << "PSIPGyErrAVE : " << CSIP[ID].SIP_ABP_GErr[1][0] << "	(pix)" << endl;
    cout << "PSIPGyErrRMS : " << CSIP[ID].SIP_ABP_GErr[1][1] << "	(pix)" << endl;
    cout << " SIPLxErrAVE : " << CSIP[ID].SIP_AB_LErr[0][0] << "	(pix)"<< endl;
    cout << " SIPLxErrRMS : " << CSIP[ID].SIP_AB_LErr[0][1] << "	(pix)" << endl;
    cout << " SIPLyErrAVE : " << CSIP[ID].SIP_AB_LErr[1][0] << "	(pix)" << endl;
    cout << " SIPLyErrRMS : " << CSIP[ID].SIP_AB_LErr[1][1] << "	(pix)" << endl;
    cout << "PSIPLxErrAVE : " << CSIP[ID].SIP_ABP_LErr[0][0] << "	(pix)" << endl;
    cout << "PSIPLxErrRMS : " << CSIP[ID].SIP_ABP_LErr[0][1] << "	(pix)" << endl;
    cout << "PSIPLyErrAVE : " << CSIP[ID].SIP_ABP_LErr[1][0] << "	(pix)" << endl;
    cout << "PSIPLyErrRMS : " << CSIP[ID].SIP_ABP_LErr[1][1] << "	(pix)" << endl;
    cout << "--------------------------------------------------" <<endl;
    cout << endl;
//--------------------------------------------------
    ID=APROP.CCDNUM-1;
    cout << "--- LOCAL FITTING STATISTICS --------------------" <<endl;
    cout << "CHIPID       : " << ID << endl;
    cout << "REFERENCE NUM: " << CSIP[ID].REFNUM<< endl;
    cout << "FITTING   NUM: " << CSIP[ID].FITNUM<< endl;
    cout << "CRPIX(pix)   : " << CSIP[ID].CRPIX[0] << " , " << CSIP[ID].CRPIX[1]<< endl;
    cout << "CRVAL(dec)   : " << CSIP[ID].CRVAL[0] << " , " << CSIP[ID].CRVAL[1]<< endl;
    cout << "OAPIX(pix)   : " << CSIP[ID].OAPIX[0] << " , " << CSIP[ID].OAPIX[1]<< endl;
    cout << "OAVAL(dec)   : " << CSIP[ID].OAVAL[0] << " , " << CSIP[ID].OAVAL[1]<< endl;
    cout << "CD_1_1       : " << CSIP[ID].CD[0][0] << endl;
    cout << "CD_1_2       : " << CSIP[ID].CD[0][1] << endl;
    cout << "CD_2_1       : " << CSIP[ID].CD[1][0] << endl;
    cout << "CD_2_2       : " << CSIP[ID].CD[1][1] << endl;
    cout << "InvCD_1_1    : " << CSIP[ID].InvCD[0][0] << endl;
    cout << "InvCD_1_2    : " << CSIP[ID].InvCD[0][1] << endl;
    cout << "InvCD_2_1    : " << CSIP[ID].InvCD[1][0] << endl;
    cout << "InvCD_2_2    : " << CSIP[ID].InvCD[1][1] << endl;
ij=0;
for(i=0;i<APROP.SIP_ORDER+1;i++)
for(j=0;j<APROP.SIP_ORDER+1;j++)
if(i+j<APROP.SIP_ORDER+1)
cout << "  SIPx["<<i<<"]["<<j<<"] : "<< CSIP[ID].SIP_AB[0][ij++]<<endl;
ij=0;
for(i=0;i<APROP.SIP_ORDER+1;i++)
for(j=0;j<APROP.SIP_ORDER+1;j++)
if(i+j<APROP.SIP_ORDER+1)
cout << "  SIPy["<<i<<"]["<<j<<"] : "<< CSIP[ID].SIP_AB[1][ij++]<<endl;
ij=0;
for(i=0;i<APROP.SIP_P_ORDER+1;i++)
for(j=0;j<APROP.SIP_P_ORDER+1;j++)
if(i+j<APROP.SIP_ORDER+1)
cout << " PSIPx["<<i<<"]["<<j<<"] : "<< CSIP[ID].SIP_ABP[0][ij++]<<endl;
ij=0;
for(i=0;i<APROP.SIP_P_ORDER+1;i++)
for(j=0;j<APROP.SIP_P_ORDER+1;j++)
if(i+j<APROP.SIP_ORDER+1)
cout << " PSIPy["<<i<<"]["<<j<<"] : "<< CSIP[ID].SIP_ABP[1][ij++]<<endl;
/*    cout << "  SIPx[0][0] : " << CSIP[ID].SIP_AB[0][0] << endl;
    cout << "  SIPx[0][1] : " << CSIP[ID].SIP_AB[0][1] << endl;
    cout << "  SIPx[1][0] : " << CSIP[ID].SIP_AB[0][APROP.SIP_ORDER+1] << endl;
    cout << "  SIPx[1][1] : " << CSIP[ID].SIP_AB[0][APROP.SIP_ORDER+2] << endl;
    cout << "  SIPy[0][0] : " << CSIP[ID].SIP_AB[1][0] << endl;
    cout << "  SIPy[0][1] : " << CSIP[ID].SIP_AB[1][1] << endl;
    cout << "  SIPy[1][0] : " << CSIP[ID].SIP_AB[1][APROP.SIP_ORDER+1] << endl;
    cout << "  SIPy[1][1] : " << CSIP[ID].SIP_AB[1][APROP.SIP_ORDER+2] << endl;
    cout << " PSIPx[0][0] : " << CSIP[ID].SIP_ABP[0][0] << endl;
    cout << " PSIPx[0][1] : " << CSIP[ID].SIP_ABP[0][1] << endl;
    cout << " PSIPx[1][0] : " << CSIP[ID].SIP_ABP[0][APROP.SIP_ORDER+1] << endl;
    cout << " PSIPx[1][1] : " << CSIP[ID].SIP_ABP[0][APROP.SIP_ORDER+2] << endl;
    cout << " PSIPy[0][0] : " << CSIP[ID].SIP_ABP[1][0] << endl;
    cout << " PSIPy[0][1] : " << CSIP[ID].SIP_ABP[1][1] << endl;
    cout << " PSIPy[1][0] : " << CSIP[ID].SIP_ABP[1][APROP.SIP_ORDER+1] << endl;
    cout << " PSIPy[1][1] : " << CSIP[ID].SIP_ABP[1][APROP.SIP_ORDER+2] << endl;
*/    cout << " SIPGxErrAVE : " << CSIP[ID].SIP_AB_GErr[0][0] << "	(pix)"<< endl;
    cout << " SIPGxErrRMS : " << CSIP[ID].SIP_AB_GErr[0][1] << "	(pix)" << endl;
    cout << " SIPGyErrAVE : " << CSIP[ID].SIP_AB_GErr[1][0] << "	(pix)" << endl;
    cout << " SIPGyErrRMS : " << CSIP[ID].SIP_AB_GErr[1][1] << "	(pix)" << endl;
    cout << "PSIPGxErrAVE : " << CSIP[ID].SIP_ABP_GErr[0][0] << "	(pix)" << endl;
    cout << "PSIPGxErrRMS : " << CSIP[ID].SIP_ABP_GErr[0][1] << "	(pix)" << endl;
    cout << "PSIPGyErrAVE : " << CSIP[ID].SIP_ABP_GErr[1][0] << "	(pix)" << endl;
    cout << "PSIPGyErrRMS : " << CSIP[ID].SIP_ABP_GErr[1][1] << "	(pix)" << endl;
    cout << " SIPLxErrAVE : " << CSIP[ID].SIP_AB_LErr[0][0] << "	(pix)"<< endl;
    cout << " SIPLxErrRMS : " << CSIP[ID].SIP_AB_LErr[0][1] << "	(pix)" << endl;
    cout << " SIPLyErrAVE : " << CSIP[ID].SIP_AB_LErr[1][0] << "	(pix)" << endl;
    cout << " SIPLyErrRMS : " << CSIP[ID].SIP_AB_LErr[1][1] << "	(pix)" << endl;
    cout << "PSIPLxErrAVE : " << CSIP[ID].SIP_ABP_LErr[0][0] << "	(pix)" << endl;
    cout << "PSIPLxErrRMS : " << CSIP[ID].SIP_ABP_LErr[0][1] << "	(pix)" << endl;
    cout << "PSIPLyErrAVE : " << CSIP[ID].SIP_ABP_LErr[1][0] << "	(pix)" << endl;
    cout << "PSIPLyErrRMS : " << CSIP[ID].SIP_ABP_LErr[1][1] << "	(pix)" << endl;
    cout << "--------------------------------------------------" <<endl;
    cout << endl;
//--------------------------------------------------
    for(ID=0;ID<APROP.CCDNUM+1;ID++){
        delete [] RMS[0][ID];
        delete [] RMS[1][ID];
        delete [] RMS[2][ID];
        delete [] RMS[3][ID];
    }
    delete [] RMS[0];
    delete [] RMS[1];
    delete [] RMS[2];
    delete [] RMS[3];

    delete [] STNUM;
}
#undef PI

