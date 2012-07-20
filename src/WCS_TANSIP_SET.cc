//------------------------------------------------------------
//WCS_TANSIP_SET.cc
//Checking and setting parameters
//
//Last modification : 2011/12/20
//------------------------------------------------------------
#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"


using namespace std;

void    F_WCSA_TANSIP_SET_GETAPROP(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP);
void    F_WCSA_TANSIP_SET_APROP(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    APROP->F_WCSA_APROP_CHECKCRPIXMODE();
    APROP->F_WCSA_APROP_CHECKCCDPOSMODE();
    APROP->F_WCSA_APROP_CHECKSIPORDER();
    APROP->F_WCSA_APROP_CHECKPSIPORDER();
    APROP->F_WCSA_APROP_CHECKLSIPORDER();
//    APROP->F_WCSA_APROP_CHECKBASISCID();
    APROP->F_WCSA_APROP_CHECKFITNUM();
    APROP->F_WCSA_APROP_CHECKCCDFITNUM();

    F_WCSA_TANSIP_SET_GETAPROP(APROP,APAIR,GSIP);
}
void    F_WCSA_TANSIP_SET_GSIP(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    GSIP->F_WCSA_GSIP_SETINITIAL();
    GSIP->F_WCSA_GSIP_CHECKCCDPOSITION();

    int CID;
    for(CID=0;CID<APROP->CCDNUM;CID++){
        APAIR->GPOS[CID][0]=GSIP->CSIP[CID].GPOS[0];
        APAIR->GPOS[CID][1]=GSIP->CSIP[CID].GPOS[1];
        APAIR->GPOS[CID][2]=GSIP->CSIP[CID].GPOS[2];
    }
}
void    F_WCSA_TANSIP_SET_APAIR(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    if(APROP->STDOUT==2)APAIR->F_WCSA_APAIR_SHOWCCDPOS();
    APAIR->F_WCSA_APAIR_SETXG();

    if(APROP->STDOUT==2)APROP->F_WCSA_APROP_SHOWAPROP();
    if(APROP->STDOUT==2)GSIP->F_WCSA_GSIP_SHOWGSIP();
    if(APROP->STDOUT==2)APAIR->F_WCSA_APAIR_SHOWAPAIR();
}
void    F_WCSA_TANSIP_SET_GETAPROP(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    sprintf(GSIP->CRPIXMODE,APROP->CRPIXMODE);
    sprintf(GSIP->OAMODE,APROP->OAMODE);
    GSIP->STDOUT     =APROP->STDOUT;
    GSIP->CCDPOSMODE =APROP->CCDPOSMODE;
    GSIP->ALLFITNUM  =APROP->ALLFITNUM;
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
    APAIR->CCDPOSMODE  =APROP->CCDPOSMODE;
    APAIR->CCDPOSHMODE =APROP->CCDPOSHMODE;
    APAIR->REJMODE  =APROP->REJMODE;
    APAIR->ALLFITNUM   =APROP->ALLFITNUM;
    APAIR->CLIP_SIGMA  =APROP->CLIP_SIGMA;
    APAIR->CRPIX[0]    =APROP->CRPIX[0];
    APAIR->CRPIX[1]    =APROP->CRPIX[1];
    APAIR->CRVAL[0]    =APROP->CRVAL[0];
    APAIR->CRVAL[1]    =APROP->CRVAL[1];
    APAIR->OAPIX[0]    =APAIR->CRPIX[0];
    APAIR->OAPIX[1]    =APAIR->CRPIX[1];
    APAIR->OAVAL[0]    =APAIR->CRVAL[0];
    APAIR->OAVAL[1]    =APAIR->CRVAL[1];
    APAIR->BASISPOS[0] =APROP->BASISPOS[0];
    APAIR->BASISPOS[1] =APROP->BASISPOS[1];
    APAIR->BASISPOS[2] =APROP->BASISPOS[2];
}
void F_WCSA_TANSIP_SET_GETREJECTIONRESULT(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    int CID;

    APROP->ALLFITNUM=0;
    for(CID=0;CID<APROP->CCDNUM;CID++){
    APROP->FITNUM[CID]=APROP->FITNUM[CID]-APAIR->REJNUM[CID];
    APROP->ALLFITNUM+=APROP->FITNUM[CID];
    }
}
void F_WCSA_TANSIP_SET_GETWCS(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    int i,j,CID,NUM;

    GSIP->ALLREFNUM=APAIR->ALLREFNUM;
    GSIP->ALLFITNUM=APAIR->ALLFITNUM;
    GSIP->CSIP[APROP->CCDNUM].ID=999;
    GSIP->CSIP[APROP->CCDNUM].POSID[0]=999;
    GSIP->CSIP[APROP->CCDNUM].POSID[1]=999;
    GSIP->CSIP[APROP->CCDNUM].REFNUM=APAIR->ALLREFNUM;
    GSIP->CSIP[APROP->CCDNUM].FITNUM=APAIR->ALLFITNUM;
    GSIP->CSIP[APROP->CCDNUM].MAXFRAD=APAIR->MAXFRAD;
    GSIP->CSIP[APROP->CCDNUM].MAXDRAD=APAIR->MAXDRAD;
    GSIP->CSIP[APROP->CCDNUM].CRPIX[0]=GSIP->CRPIX[0]=APAIR->CRPIX[0];
    GSIP->CSIP[APROP->CCDNUM].CRPIX[1]=GSIP->CRPIX[1]=APAIR->CRPIX[1];
    GSIP->CSIP[APROP->CCDNUM].CRVAL[0]=GSIP->CRVAL[0]=APAIR->CRVAL[0];
    GSIP->CSIP[APROP->CCDNUM].CRVAL[1]=GSIP->CRVAL[1]=APAIR->CRVAL[1];
    GSIP->CSIP[APROP->CCDNUM].OAPIX[0]=GSIP->OAPIX[0]=APAIR->CRPIX[0];
    GSIP->CSIP[APROP->CCDNUM].OAPIX[1]=GSIP->OAPIX[1]=APAIR->CRPIX[1];
    GSIP->CSIP[APROP->CCDNUM].OAVAL[0]=GSIP->OAVAL[0]=APAIR->CRVAL[0];
    GSIP->CSIP[APROP->CCDNUM].OAVAL[1]=GSIP->OAVAL[1]=APAIR->CRVAL[1];
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
    GSIP->CSIP[APROP->CCDNUM].SIP_AB[i][j]=APAIR->SIP_AB[i][j];
    for(i=0;i<2;i++)
    for(j=0;j<(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2);j++)
    GSIP->CSIP[APROP->CCDNUM].SIP_ABP[i][j]=APAIR->SIP_ABP[i][j];

    for(i=0;i<2;i++)
    for(j=0;j<3;j++){
    GSIP->CSIP[APROP->CCDNUM].SIP_AB_ERR[i][j] =APAIR-> SIPRMS[i][j];
    GSIP->CSIP[APROP->CCDNUM].SIP_ABP_ERR[i][j]=APAIR->PSIPRMS[i][j];
    }

    for(CID=0;CID<APROP->CCDNUM+1;CID++){
        GSIP->CSIP[CID].SIP_ORDER=GSIP->SIP_ORDER;
        GSIP->CSIP[CID].SIP_P_ORDER=GSIP->SIP_P_ORDER;
        GSIP->CSIP[CID].SIP_L_ORDER=GSIP->SIP_L_ORDER;
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
void    F_WCSA_TANSIP_SET_CALCREFPARAMLOCAL(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    int NUM,CID,*FNUM,*PFNUM;
    double ***data,***Pdata,***MAXDIFF;

    for(NUM=0;NUM<APROP->ALLREFNUM;NUM++){
        APAIR->PAIR[NUM].X_LOCALCRPIX[0]=APAIR->PAIR[NUM].X_LOCAL[0]-GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].CRPIX[0];
        APAIR->PAIR[NUM].X_LOCALCRPIX[1]=APAIR->PAIR[NUM].X_LOCAL[1]-GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].CRPIX[1];
        APAIR->PAIR[NUM].X_LOCALIM_PIXEL[0]=GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].InvCD[0][0]*APAIR->PAIR[NUM].X_IM_WORLD[0]+GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].InvCD[0][1]*APAIR->PAIR[NUM].X_IM_WORLD[1];
        APAIR->PAIR[NUM].X_LOCALIM_PIXEL[1]=GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].InvCD[1][0]*APAIR->PAIR[NUM].X_IM_WORLD[0]+GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].InvCD[1][1]*APAIR->PAIR[NUM].X_IM_WORLD[1];
    }
//--------------------------------------------------
    FNUM = F_NEWint1(APROP->CCDNUM);
    PFNUM= F_NEWint1(APROP->CCDNUM);
    data = F_NEWdouble3(APROP->CCDNUM,2,APROP->ALLREFNUM);
    Pdata= F_NEWdouble3(APROP->CCDNUM,2,APROP->ALLREFNUM);
    MAXDIFF= F_NEWdouble3(APROP->CCDNUM,2,2);
//--------------------------------------------------
    for(NUM=0;NUM<APROP->ALLREFNUM;NUM++)
    if(APAIR->PAIR[NUM].FLAG == 1){
         data[APAIR->PAIR[NUM].CHIPID][0][ FNUM[APAIR->PAIR[NUM].CHIPID]]=APAIR->PAIR[NUM].X_LOCALIM_PIXEL[0]  -(F_CALCVALUE(APROP->SIP_ORDER  ,GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].SIP_AB[0] ,APAIR->PAIR[NUM].X_LOCALCRPIX)+APAIR->PAIR[NUM].X_LOCALCRPIX[0]);
         data[APAIR->PAIR[NUM].CHIPID][1][ FNUM[APAIR->PAIR[NUM].CHIPID]]=APAIR->PAIR[NUM].X_LOCALIM_PIXEL[1]  -(F_CALCVALUE(APROP->SIP_ORDER  ,GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].SIP_AB[1] ,APAIR->PAIR[NUM].X_LOCALCRPIX)+APAIR->PAIR[NUM].X_LOCALCRPIX[1]);
        if(fabs( data[APAIR->PAIR[NUM].CHIPID][0][ FNUM[APAIR->PAIR[NUM].CHIPID]])>fabs(MAXDIFF[APAIR->PAIR[NUM].CHIPID][0][0]))
        MAXDIFF[APAIR->PAIR[NUM].CHIPID][0][0]= data[APAIR->PAIR[NUM].CHIPID][0][ FNUM[APAIR->PAIR[NUM].CHIPID]];
        if(fabs( data[APAIR->PAIR[NUM].CHIPID][1][ FNUM[APAIR->PAIR[NUM].CHIPID]])>fabs(MAXDIFF[APAIR->PAIR[NUM].CHIPID][0][1]))
        MAXDIFF[APAIR->PAIR[NUM].CHIPID][0][1]= data[APAIR->PAIR[NUM].CHIPID][1][ FNUM[APAIR->PAIR[NUM].CHIPID]];
         FNUM[APAIR->PAIR[NUM].CHIPID]++;

        Pdata[APAIR->PAIR[NUM].CHIPID][0][PFNUM[APAIR->PAIR[NUM].CHIPID]]=APAIR->PAIR[NUM].X_LOCALCRPIX[0]-(F_CALCVALUE(APROP->SIP_P_ORDER,GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].SIP_ABP[0],APAIR->PAIR[NUM].X_LOCALIM_PIXEL  )+APAIR->PAIR[NUM].X_LOCALIM_PIXEL[0]);
        Pdata[APAIR->PAIR[NUM].CHIPID][1][PFNUM[APAIR->PAIR[NUM].CHIPID]]=APAIR->PAIR[NUM].X_LOCALCRPIX[1]-(F_CALCVALUE(APROP->SIP_P_ORDER,GSIP->CSIP[APAIR->PAIR[NUM].CHIPID].SIP_ABP[1],APAIR->PAIR[NUM].X_LOCALIM_PIXEL  )+APAIR->PAIR[NUM].X_LOCALIM_PIXEL[1]);
        if(fabs(Pdata[APAIR->PAIR[NUM].CHIPID][0][PFNUM[APAIR->PAIR[NUM].CHIPID]])>fabs(MAXDIFF[APAIR->PAIR[NUM].CHIPID][1][0]))
        MAXDIFF[APAIR->PAIR[NUM].CHIPID][1][0]=Pdata[APAIR->PAIR[NUM].CHIPID][0][PFNUM[APAIR->PAIR[NUM].CHIPID]];
        if(fabs(Pdata[APAIR->PAIR[NUM].CHIPID][1][PFNUM[APAIR->PAIR[NUM].CHIPID]])>fabs(MAXDIFF[APAIR->PAIR[NUM].CHIPID][1][1]))
        MAXDIFF[APAIR->PAIR[NUM].CHIPID][1][1]=Pdata[APAIR->PAIR[NUM].CHIPID][1][PFNUM[APAIR->PAIR[NUM].CHIPID]];
        PFNUM[APAIR->PAIR[NUM].CHIPID]++;
    }
    for(CID=0;CID<APROP->CCDNUM;CID++){
        F_RMS( FNUM[CID], data[CID][0], GSIP->CSIP[CID].SIP_AB_ERR[0]);
        F_RMS( FNUM[CID], data[CID][1], GSIP->CSIP[CID].SIP_AB_ERR[1]);
        GSIP->CSIP[CID].SIP_AB_ERR[0][2]=MAXDIFF[CID][0][0];
        GSIP->CSIP[CID].SIP_AB_ERR[1][2]=MAXDIFF[CID][0][1];
        F_RMS(PFNUM[CID],Pdata[CID][0],GSIP->CSIP[CID].SIP_ABP_ERR[0]);
        F_RMS(PFNUM[CID],Pdata[CID][1],GSIP->CSIP[CID].SIP_ABP_ERR[1]);
        GSIP->CSIP[CID].SIP_ABP_ERR[0][2]=MAXDIFF[CID][1][0];
        GSIP->CSIP[CID].SIP_ABP_ERR[1][2]=MAXDIFF[CID][1][1];
    }

//--------------------------------------------------
    if(APROP->STDOUT==2)for(CID=0;CID<APROP->CCDNUM+1;CID++)GSIP->F_WCSA_GSIP_SHOWCSIP(CID);
//--------------------------------------------------
    F_DELint1(FNUM);
    F_DELint1(PFNUM);
    F_DELdouble3(APROP->CCDNUM,2,data);
    F_DELdouble3(APROP->CCDNUM,2,Pdata);
    F_DELdouble3(APROP->CCDNUM,2,MAXDIFF);

}
