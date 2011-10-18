//------------------------------------------------------------
//WCS_TANSIP_SET.cc
//Checking and setting parameters
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;

void    F_WCSA_TANSIP_SET_GETAPROP(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP);
void    F_WCSA_TANSIP_SET(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    APROP->F_WCSA_APROP_CHECKCRPIXMODE();
    APROP->F_WCSA_APROP_CHECKCCDPOSMODE();
    APROP->F_WCSA_APROP_CHECKSIPORDER();
    APROP->F_WCSA_APROP_CHECKPSIPORDER();
    APROP->F_WCSA_APROP_CHECKLSIPORDER();
//    APROP->F_WCSA_APROP_CHECKBASISCID();
    APROP->F_WCSA_APROP_CHECKFITNUM();
    APROP->F_WCSA_APROP_CHECKCCDFITNUM();

    F_WCSA_TANSIP_SET_GETAPROP(APROP,APAIR,GSIP);

    GSIP->F_WCSA_GSIP_CHECKCCDPOSITION();
    GSIP->F_WCSA_GSIP_SETINITIAL();

    int CID;
    for(CID=0;CID<APROP->CCDNUM;CID++){
        APAIR->GPOS[CID][0]=GSIP->CSIP[CID].GPOS[0];
        APAIR->GPOS[CID][1]=GSIP->CSIP[CID].GPOS[1];
        APAIR->GPOS[CID][2]=GSIP->CSIP[CID].GPOS[2];
    }
    APAIR->F_WCSA_APAIR_SETXG();

    if(APROP->STDOUT==2)GSIP->F_WCSA_GSIP_SHOWGSIP();
    if(APROP->STDOUT==2)APAIR->F_WCSA_APAIR_SHOWAPAIR();
}
void    F_WCSA_TANSIP_SET_GETAPROP(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    sprintf(GSIP->CRPIXMODE,APROP->CRPIXMODE);
    sprintf(GSIP->OAMODE,APROP->OAMODE);
    GSIP->STDOUT     =APROP->STDOUT;
    GSIP->CCDPOSMODE =APROP->CCDPOSMODE;
    GSIP->CCDNUM     =APROP->CCDNUM;
    GSIP->ALLREFNUM  =APROP->ALLREFNUM;
    GSIP->ALLFITNUM  =APROP->ALLFITNUM;
    GSIP->SIP_ORDER  =APROP->SIP_ORDER;
    GSIP->SIP_P_ORDER=APROP->SIP_P_ORDER;
    GSIP->SIP_L_ORDER=APROP->SIP_L_ORDER;
    GSIP->CLIP_SIGMA =APROP->CLIP_SIGMA;
    GSIP->CRPIX[0]=APROP->CRPIX[0];
    GSIP->CRPIX[1]=APROP->CRPIX[1];
    GSIP->CRVAL[0]=APROP->CRVAL[0];
    GSIP->CRVAL[1]=APROP->CRVAL[1];
    GSIP->OAPIX[0]=APROP->CRPIX[0];
    GSIP->OAPIX[1]=APROP->CRPIX[1];
    GSIP->OAVAL[0]=APROP->CRVAL[0];
    GSIP->OAVAL[1]=APROP->CRVAL[1];

    sprintf(APAIR->CRPIXMODE,APROP->CRPIXMODE);
    sprintf(APAIR->OAMODE,APROP->OAMODE);
    APAIR->STDOUT      =APROP->STDOUT;
    APAIR->CCDNUM      =APROP->CCDNUM;
    APAIR->CCDPOSMODE  =APROP->CCDPOSMODE;
    APAIR->ALLREFNUM   =APROP->ALLREFNUM;
    APAIR->ALLFITNUM   =APROP->ALLFITNUM;
    APAIR->SIP_ORDER   =APROP->SIP_ORDER;
    APAIR->SIP_P_ORDER =APROP->SIP_P_ORDER;
    APAIR->SIP_L_ORDER =APROP->SIP_L_ORDER;
    APAIR->CLIP_SIGMA  =APROP->CLIP_SIGMA;
    APAIR->CRPIX[0]    =APROP->CRPIX[0];
    APAIR->CRPIX[1]    =APROP->CRPIX[1];
    APAIR->CRVAL[0]    =APROP->CRVAL[0];
    APAIR->CRVAL[1]    =APROP->CRVAL[1];
    APAIR->OAPIX[0]    =APAIR->CRPIX[0];
    APAIR->OAPIX[1]    =APAIR->CRPIX[1];
    APAIR->OAVAL[0]    =APAIR->CRVAL[0];
    APAIR->OAVAL[1]    =APAIR->CRVAL[1];
    APAIR->TSIP_AB[0]   =F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
    APAIR->TSIP_AB[1]   =F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
    APAIR->TSIP_ABP[0]  =F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
    APAIR->TSIP_ABP[1]  =F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
    APAIR->TCoef[0]     =F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
    APAIR->TCoef[1]     =F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
    APAIR->TdCoef[0][0] =F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
    APAIR->TdCoef[0][1] =F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
    APAIR->TdCoef[1][0] =F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
    APAIR->TdCoef[1][1] =F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
    APAIR->TPCoef[0]    =F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
    APAIR->TPCoef[1]    =F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
    APAIR->TdPCoef[0][0]=F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
    APAIR->TdPCoef[0][1]=F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
    APAIR->TdPCoef[1][0]=F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
    APAIR->TdPCoef[1][1]=F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
    APAIR->TLCoef[0]    =F_NEWdouble2(APROP->CCDNUM,(APROP->SIP_L_ORDER+1)*(APROP->SIP_L_ORDER+2));
    APAIR->TLCoef[1]    =F_NEWdouble2(APROP->CCDNUM,(APROP->SIP_L_ORDER+1)*(APROP->SIP_L_ORDER+2));
    APAIR->TdLCoef[0][0]=F_NEWdouble2(APROP->CCDNUM,(APROP->SIP_L_ORDER+1)*(APROP->SIP_L_ORDER+2));
    APAIR->TdLCoef[0][1]=F_NEWdouble2(APROP->CCDNUM,(APROP->SIP_L_ORDER+1)*(APROP->SIP_L_ORDER+2));
    APAIR->TdLCoef[1][0]=F_NEWdouble2(APROP->CCDNUM,(APROP->SIP_L_ORDER+1)*(APROP->SIP_L_ORDER+2));
    APAIR->TdLCoef[1][1]=F_NEWdouble2(APROP->CCDNUM,(APROP->SIP_L_ORDER+1)*(APROP->SIP_L_ORDER+2));

    int CID,i;
    for(CID=0;CID<APROP->CCDNUM+1;CID++){
    for(i=0;i<2;i++){
        GSIP->CSIP[CID].SIP_AB[i]    = F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
        GSIP->CSIP[CID].SIP_ABP[i]   = F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
        GSIP->CSIP[CID].Coef[i]     = F_NEWdouble1((APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2));
        GSIP->CSIP[CID].PCoef[i]    = F_NEWdouble1((APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2));
        GSIP->CSIP[CID].LCoef[i]    = F_NEWdouble1((APROP->SIP_L_ORDER+1)*(APROP->SIP_L_ORDER+2));
    }

        GSIP->CSIP[CID].SIP_MAG      = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        GSIP->CSIP[CID].SIP_SHEAR[0] = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        GSIP->CSIP[CID].SIP_SHEAR[1] = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        GSIP->CSIP[CID].SIP_ROT      = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        GSIP->CSIP[CID].PSIP_MAG     = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        GSIP->CSIP[CID].PSIP_SHEAR[0]= new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        GSIP->CSIP[CID].PSIP_SHEAR[1]= new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
        GSIP->CSIP[CID].PSIP_ROT     = new double[(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)];
    }

}

void F_WCSA_TANSIP_SET_GETWCS(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    int i,j,CID,NUM;

    GSIP->ALLREFNUM=APAIR->ALLREFNUM;
    GSIP->ALLFITNUM=APAIR->ALLFITNUM;
    GSIP->CRPIX[0]=APAIR->CRPIX[0];
    GSIP->CRPIX[1]=APAIR->CRPIX[1];
    GSIP->CRVAL[0]=APAIR->CRVAL[0];
    GSIP->CRVAL[1]=APAIR->CRVAL[1];
    GSIP->OAPIX[0]=APAIR->CRPIX[0];
    GSIP->OAPIX[1]=APAIR->CRPIX[1];
    GSIP->OAVAL[0]=APAIR->CRVAL[0];
    GSIP->OAVAL[1]=APAIR->CRVAL[1];
    GSIP->CSIP[APROP->CCDNUM].CD[0][0]=GSIP->CD[0][0]=APAIR->CD[0][0];
    GSIP->CSIP[APROP->CCDNUM].CD[0][1]=GSIP->CD[0][1]=APAIR->CD[0][1];
    GSIP->CSIP[APROP->CCDNUM].CD[1][0]=GSIP->CD[1][0]=APAIR->CD[1][0];
    GSIP->CSIP[APROP->CCDNUM].CD[1][1]=GSIP->CD[1][1]=APAIR->CD[1][1];
    GSIP->CSIP[APROP->CCDNUM].InvCD[0][0]=GSIP->InvCD[0][0]=APAIR->InvCD[0][0];
    GSIP->CSIP[APROP->CCDNUM].InvCD[0][1]=GSIP->InvCD[0][1]=APAIR->InvCD[0][1];
    GSIP->CSIP[APROP->CCDNUM].InvCD[1][0]=GSIP->InvCD[1][0]=APAIR->InvCD[1][0];
    GSIP->CSIP[APROP->CCDNUM].InvCD[1][1]=GSIP->InvCD[1][1]=APAIR->InvCD[1][1];

    for(i=0;i<2;i++)
    for(j=0;j<(APROP->SIP_ORDER  +1)*(APROP->SIP_ORDER  +2);j++)
    GSIP->CSIP[APROP->CCDNUM].SIP_AB[i][j]=APAIR->TSIP_AB[i][j];
    for(i=0;i<2;i++)
    for(j=0;j<(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2);j++)
    GSIP->CSIP[APROP->CCDNUM].SIP_ABP[i][j]=APAIR->TSIP_ABP[i][j];

    for(i=0;i<2;i++)
    for(j=0;j<2;j++){
    GSIP->CSIP[APROP->CCDNUM].SIP_AB_GERR[i][j] =APAIR-> SIPRMS[i][j];
    GSIP->CSIP[APROP->CCDNUM].SIP_ABP_GERR[i][j]=APAIR->PSIPRMS[i][j];
    }

    for(CID=0;CID<APROP->CCDNUM;CID++)
    for(i=0;i<3;i++)
    GSIP->CSIP[CID].GPOS[i]=APAIR->GPOS[CID][i];

    for(CID=0;CID<APROP->CCDNUM;CID++)
    GSIP->CSIP[CID].FITNUM=GSIP->CSIP[CID].REFNUM=0;

    for(NUM=0;NUM<APROP->ALLREFNUM;NUM++){
    GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].REFNUM++;
    if(APAIR->PAIR[NUM].FLAG==1)
    GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].FITNUM++;
    }
//--------------------------------------------------
    if(APROP->STDOUT==2)
    GSIP->F_WCSA_GSIP_SHOWGSIP();
    if(APROP->STDOUT==2)
    GSIP->F_WCSA_GSIP_SHOWGLOBAL();

//--------------------------------------------------
}
