//------------------------------------------------------------
//WCS_CSIP.cc
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<cmath>
#include<string.h>
#include "hsc/meas/tansip/WCS_CSIP.h"
#include "hsc/meas/tansip/WCS_SUB.h"

using namespace std;
//MAIN
void CL_GSIP::F_WCSA_GSIP_NEWGSIP(){
//1
    CSIP = new CL_CSIP[CCDNUM+1];
//2
    int CID,i;
    for(CID=0;CID<CCDNUM+1;CID++){
        for(i=0;i<2;i++){
            CSIP[CID].SIP_AB[i]  = F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
            CSIP[CID].SIP_ABP[i] = F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
            CSIP[CID].Coef[i]    = F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
            CSIP[CID].PCoef[i]   = F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
            CSIP[CID].LCoef[i]   = F_NEWdouble1((SIP_L_ORDER+1)*(SIP_L_ORDER+2));
        }
        CSIP[CID].SIP_MAG    = F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
        CSIP[CID].SIP_CRS[0] = F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
        CSIP[CID].SIP_CRS[1] = F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
        CSIP[CID].SIP_CRS[2] = F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
        CSIP[CID].SIP_CRS[3] = F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
        CSIP[CID].PSIP_MAG   = F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
        CSIP[CID].PSIP_CRS[0]= F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
        CSIP[CID].PSIP_CRS[1]= F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
        CSIP[CID].PSIP_CRS[2]= F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
        CSIP[CID].PSIP_CRS[3]= F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    }
    SIP_AB_INIT[0]  = F_NEWdouble1((SIP_ORDER_INIT  +1)*(SIP_ORDER_INIT  +2));
    SIP_AB_INIT[1]  = F_NEWdouble1((SIP_ORDER_INIT  +1)*(SIP_ORDER_INIT  +2));
    SIP_ABP_INIT[0] = F_NEWdouble1((SIP_P_ORDER_INIT+1)*(SIP_P_ORDER_INIT+2));
    SIP_ABP_INIT[1] = F_NEWdouble1((SIP_P_ORDER_INIT+1)*(SIP_P_ORDER_INIT+2));

}
void CL_GSIP::F_WCSA_GSIP_DELGSIP(){
//2
    int CID,i;
    for(CID=0;CID<CCDNUM+1;CID++){
        for(i=0;i<2;i++){
            F_DELdouble1(CSIP[CID].SIP_AB[i] );
            F_DELdouble1(CSIP[CID].SIP_ABP[i]);
            F_DELdouble1(CSIP[CID].Coef[i]   );
            F_DELdouble1(CSIP[CID].PCoef[i]  );
            F_DELdouble1(CSIP[CID].LCoef[i]  );
        }
    
        F_DELdouble1(CSIP[CID].SIP_MAG    );
        F_DELdouble1(CSIP[CID].SIP_CRS[0] );
        F_DELdouble1(CSIP[CID].SIP_CRS[1] );
        F_DELdouble1(CSIP[CID].SIP_CRS[2] );
        F_DELdouble1(CSIP[CID].SIP_CRS[3] );
        F_DELdouble1(CSIP[CID].PSIP_MAG   );
        F_DELdouble1(CSIP[CID].PSIP_CRS[0]);
        F_DELdouble1(CSIP[CID].PSIP_CRS[1]);
        F_DELdouble1(CSIP[CID].PSIP_CRS[2]);
        F_DELdouble1(CSIP[CID].PSIP_CRS[3]);
    }  
        F_DELdouble1(SIP_AB_INIT[0] );
        F_DELdouble1(SIP_AB_INIT[1] );
        F_DELdouble1(SIP_ABP_INIT[0]);
        F_DELdouble1(SIP_ABP_INIT[1]);
//1
    delete [] CSIP;
}
void CL_GSIP::F_WCSA_GSIP_SET0(){
    sprintf(CRPIXMODE,"AUTO");
    sprintf(   OAMODE,"MIN");
    CCDPOSMODE =0;
    STDOUT     =0;
    CLIP_SIGMA =0;
    OAVAL[0]=OAVAL[1]=0;
    OAPIX[0]=OAPIX[1]=0;
    CRVAL[0]=CRVAL[1]=0;
    CRPIX[0]=CRPIX[1]=0;
    CD[0][0]=CD[0][1]=CD[1][0]=CD[1][1]=0;
    InvCD[0][0]=InvCD[0][1]=InvCD[1][0]=InvCD[1][1]=0;
    ANGLE      =0;

    int CID;
    for(CID=0;CID<CCDNUM+1;CID++){
        CSIP[CID].ID          =0;
        CSIP[CID].FITNUM      =0;
        CSIP[CID].REFNUM      =0;
        CSIP[CID].SIP_ORDER   =0;
        CSIP[CID].SIP_P_ORDER =0;
        CSIP[CID].SIP_L_ORDER =0;
        CSIP[CID].GPOS[0]     =0;
        CSIP[CID].GPOS[1]     =0;
        CSIP[CID].GPOS[2]     =0;
        CSIP[CID].GPOS_INIT[0]=0;
        CSIP[CID].GPOS_INIT[1]=0;
        CSIP[CID].GPOS_INIT[2]=0;
        CSIP[CID].MAXDRAD     =0;
        CSIP[CID].MAXFRAD     =0;
        CSIP[CID].OAVAL[0]    =0;
        CSIP[CID].OAVAL[1]    =0;
        CSIP[CID].OAPIX[0]    =0;
        CSIP[CID].OAPIX[1]    =0;
        CSIP[CID].CRVAL[0]    =0;
        CSIP[CID].CRVAL[1]    =0;
        CSIP[CID].CRPIX[0]    =0;
        CSIP[CID].CRPIX[1]    =0;
        CSIP[CID].CD[0][0]    =0;
        CSIP[CID].CD[0][1]    =0;
        CSIP[CID].CD[1][0]    =0;
        CSIP[CID].CD[1][1]    =0;
        CSIP[CID].InvCD[0][0] =0;
        CSIP[CID].InvCD[0][1] =0;
        CSIP[CID].InvCD[1][0] =0;
        CSIP[CID].InvCD[1][1] =0;
        CSIP[CID].SIP_AB_ERR[0][0] =0;
        CSIP[CID].SIP_AB_ERR[0][1] =0;
        CSIP[CID].SIP_AB_ERR[0][2] =0;
        CSIP[CID].SIP_AB_ERR[1][0] =0;
        CSIP[CID].SIP_AB_ERR[1][1] =0;
        CSIP[CID].SIP_AB_ERR[1][2] =0;
        CSIP[CID].SIP_ABP_ERR[0][0]=0;
        CSIP[CID].SIP_ABP_ERR[0][1]=0;
        CSIP[CID].SIP_ABP_ERR[0][2]=0;
        CSIP[CID].SIP_ABP_ERR[1][0]=0;
        CSIP[CID].SIP_ABP_ERR[1][1]=0;
        CSIP[CID].SIP_ABP_ERR[1][2]=0;
        CSIP[CID].ANGLE       =0;
        CSIP[CID].POSID[0]    =0;
        CSIP[CID].POSID[1]    =0;
    }
}

void CL_GSIP::F_WCSA_GSIP_CALCLOCALSIP(){
    F_WCSA_GSIP_LOCALSIP();
}


/*
void CL_CSIP::F_WCSA_CSIP_XLOCALtoXRADEC(double *PIXEL,double *RADEC){
    double XX[2],YY[2];

    XX[0]=PIXEL[0]-CRPIX[0];
    XX[1]=PIXEL[1]-CRPIX[1];
    YY[0]=F_CALCVALUE(SIP_ORDER,SIP_AB[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(SIP_ORDER,SIP_AB[1],XX)+XX[1];
    XX[0]=CD[0][0]*YY[0]+CD[0][1]*YY[1];
    XX[1]=CD[1][0]*YY[0]+CD[1][1]*YY[1];
    F_InvPROJECTION(XX,RADEC,CRVAL);
}
void CL_CSIP::F_WCSA_CSIP_XCRPIXtoXRADEC(double *PIXEL,double *RADEC){
    double XX[2],YY[2];

    XX[0]=PIXEL[0];
    XX[1]=PIXEL[1];
    YY[0]=F_CALCVALUE(SIP_ORDER,SIP_AB[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(SIP_ORDER,SIP_AB[1],XX)+XX[1];
    XX[0]=CD[0][0]*YY[0]+CD[0][1]*YY[1];
    XX[1]=CD[1][0]*YY[0]+CD[1][1]*YY[1];
    F_InvPROJECTION(XX,RADEC,CRVAL);
}
void CL_CSIP::F_WCSA_CSIP_XRADECtoXLOCAL(double *RADEC,double *PIXEL){
    double XX[2],YY[2];

    F_PROJECTION(RADEC,YY,CRVAL);
    XX[0]=InvCD[0][0]*YY[0]+InvCD[0][1]*YY[1];
    XX[1]=InvCD[1][0]*YY[0]+InvCD[1][1]*YY[1];
    YY[0]=F_CALCVALUE(SIP_P_ORDER,SIP_ABP[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(SIP_P_ORDER,SIP_ABP[1],XX)+XX[1];
    PIXEL[0]=YY[0]+CRPIX[0];
    PIXEL[1]=YY[1]+CRPIX[1];
}
void CL_CSIP::F_WCSA_CSIP_XRADECtoXCRPIX(double *RADEC,double *PIXEL){
    double XX[2],YY[2];

    F_PROJECTION(RADEC,YY,CRVAL);
    XX[0]=InvCD[0][0]*YY[0]+InvCD[0][1]*YY[1];
    XX[1]=InvCD[1][0]*YY[0]+InvCD[1][1]*YY[1];
    YY[0]=F_CALCVALUE(SIP_P_ORDER,SIP_ABP[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(SIP_P_ORDER,SIP_ABP[1],XX)+XX[1];
    PIXEL[0]=YY[0];
    PIXEL[1]=YY[1];
}*/
void CL_GSIP::F_WCSA_GSIP_XLOCALtoXRADEC(int CID, double *PIXEL,double *RADEC){
    double XX[2],YY[2];

    XX[0]=PIXEL[0]-CSIP[CID].CRPIX[0];
    XX[1]=PIXEL[1]-CSIP[CID].CRPIX[1];
    YY[0]=F_CALCVALUE(SIP_ORDER,CSIP[CID].SIP_AB[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(SIP_ORDER,CSIP[CID].SIP_AB[1],XX)+XX[1];
    XX[0]=CSIP[CID].CD[0][0]*YY[0]+CSIP[CID].CD[0][1]*YY[1];
    XX[1]=CSIP[CID].CD[1][0]*YY[0]+CSIP[CID].CD[1][1]*YY[1];
    F_InvPROJECTION(XX,RADEC,CRVAL);
}
void CL_GSIP::F_WCSA_GSIP_XLOCALtoXIMPIXEL(int CID, double *PIXEL,double *IMPIXEL){
    double XX[2],YY[2];

    XX[0]=PIXEL[0]-CSIP[CID].CRPIX[0];
    XX[1]=PIXEL[1]-CSIP[CID].CRPIX[1];
    YY[0]=F_CALCVALUE(SIP_ORDER,CSIP[CID].SIP_AB[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(SIP_ORDER,CSIP[CID].SIP_AB[1],XX)+XX[1];
    IMPIXEL[0]=YY[0]+CSIP[CID].CRPIX[0];
    IMPIXEL[1]=YY[1]+CSIP[CID].CRPIX[1];
}
void CL_GSIP::F_WCSA_GSIP_XRADECtoXLOCAL(int CID, double *RADEC,double *PIXEL){
    double XX[2],YY[2];

    F_PROJECTION(RADEC,YY,CRVAL);
    XX[0]=CSIP[CID].InvCD[0][0]*YY[0]+CSIP[CID].InvCD[0][1]*YY[1];
    XX[1]=CSIP[CID].InvCD[1][0]*YY[0]+CSIP[CID].InvCD[1][1]*YY[1];
    YY[0]=F_CALCVALUE(SIP_P_ORDER,CSIP[CID].SIP_ABP[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(SIP_P_ORDER,CSIP[CID].SIP_ABP[1],XX)+XX[1];
    PIXEL[0]=YY[0]+CSIP[CID].CRPIX[0];
    PIXEL[1]=YY[1]+CSIP[CID].CRPIX[1];
}
void CL_GSIP::F_WCSA_GSIP_XIMPIXELtoXLOCAL(int CID,double *IMPIXEL, double *PIXEL){
    double XX[2],YY[2];

    XX[0]=IMPIXEL[0]-CSIP[CID].CRPIX[0];
    XX[1]=IMPIXEL[1]-CSIP[CID].CRPIX[1];
    YY[0]=F_CALCVALUE(SIP_P_ORDER,CSIP[CID].SIP_ABP[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(SIP_P_ORDER,CSIP[CID].SIP_ABP[1],XX)+XX[1];
    PIXEL[0]=YY[0]+CSIP[CID].CRPIX[0];
    PIXEL[1]=YY[1]+CSIP[CID].CRPIX[1];
}
void CL_GSIP::F_WCSA_GSIP_XCRPIXtoXRADEC(int CID, double *CRPIX,double *RADEC){
    double XX[2],YY[2];

    if(CID==-1){//Initital
        YY[0]=F_CALCVALUE(SIP_ORDER_INIT,SIP_AB_INIT[0],CRPIX)+CRPIX[0];
        YY[1]=F_CALCVALUE(SIP_ORDER_INIT,SIP_AB_INIT[1],CRPIX)+CRPIX[1];
        XX[0]=CD_INIT[0][0]*YY[0]+CD_INIT[0][1]*YY[1];
        XX[1]=CD_INIT[1][0]*YY[0]+CD_INIT[1][1]*YY[1];
    }else{
        YY[0]=F_CALCVALUE(SIP_ORDER,CSIP[CID].SIP_AB[0],CRPIX)+CRPIX[0];
        YY[1]=F_CALCVALUE(SIP_ORDER,CSIP[CID].SIP_AB[1],CRPIX)+CRPIX[1];
        XX[0]=CSIP[CID].CD[0][0]*YY[0]+CSIP[CID].CD[0][1]*YY[1];
        XX[1]=CSIP[CID].CD[1][0]*YY[0]+CSIP[CID].CD[1][1]*YY[1];
    }
    F_InvPROJECTION(XX,RADEC,CRVAL);
}
void CL_GSIP::F_WCSA_GSIP_XRADECtoXCRPIX(int CID, double *RADEC,double *CRPIX){
    double XX[2],YY[2];

    F_PROJECTION(RADEC,YY,CRVAL);
    if(CID==-1){//Initital
        XX[0]=InvCD_INIT[0][0]*YY[0]+InvCD_INIT[0][1]*YY[1];
        XX[1]=InvCD_INIT[1][0]*YY[0]+InvCD_INIT[1][1]*YY[1];
        CRPIX[0]=F_CALCVALUE(SIP_P_ORDER_INIT,SIP_ABP_INIT[0],XX)+XX[0];
        CRPIX[1]=F_CALCVALUE(SIP_P_ORDER_INIT,SIP_ABP_INIT[1],XX)+XX[1];
    }else{
        XX[0]=CSIP[CID].InvCD[0][0]*YY[0]+CSIP[CID].InvCD[0][1]*YY[1];
        XX[1]=CSIP[CID].InvCD[1][0]*YY[0]+CSIP[CID].InvCD[1][1]*YY[1];
        CRPIX[0]=F_CALCVALUE(SIP_P_ORDER,CSIP[CID].SIP_ABP[0],XX)+XX[0];
        CRPIX[1]=F_CALCVALUE(SIP_P_ORDER,CSIP[CID].SIP_ABP[1],XX)+XX[1];
    }
}
void CL_GSIP::F_WCSA_GSIP_CRSMAatXLOCAL(int CID,double *LOCAL, double *CRSMA){
    double X_CRPIX[2];
    double dGdI[2][2],InvdGdI[2][2];
    double *TdCoef[2][2];
  
    X_CRPIX[0]=LOCAL[0]-CSIP[CID].CRPIX[0];
    X_CRPIX[1]=LOCAL[1]-CSIP[CID].CRPIX[1];

    TdCoef[0][0]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
    TdCoef[0][1]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
    TdCoef[1][0]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
    TdCoef[1][1]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));

    F_DIFFSIP(SIP_ORDER,CSIP[CID].SIP_AB[0],TdCoef[0][0],TdCoef[0][1]);
    F_DIFFSIP(SIP_ORDER,CSIP[CID].SIP_AB[1],TdCoef[1][0],TdCoef[1][1]);

    dGdI[0][0]=F_CALCVALUE(SIP_ORDER,TdCoef[0][0],X_CRPIX);
    dGdI[0][1]=F_CALCVALUE(SIP_ORDER,TdCoef[0][1],X_CRPIX);
    dGdI[1][0]=F_CALCVALUE(SIP_ORDER,TdCoef[1][0],X_CRPIX);
    dGdI[1][1]=F_CALCVALUE(SIP_ORDER,TdCoef[1][1],X_CRPIX);
    InvdGdI[0][0]=(1+dGdI[1][1])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0])-1;
    InvdGdI[0][1]=( -dGdI[0][1])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0]);
    InvdGdI[1][0]=( -dGdI[1][0])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0]);
    InvdGdI[1][1]=(1+dGdI[0][0])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0])-1;
    CRSMA[0]=0.5*(1+InvdGdI[0][0]+1+InvdGdI[1][1]);
    CRSMA[1]=0.5*(  InvdGdI[0][1]-  InvdGdI[1][0]);
    CRSMA[2]=0.5*(  InvdGdI[0][0]-  InvdGdI[1][1]);
    CRSMA[3]=0.5*(  InvdGdI[0][1]+  InvdGdI[1][0]);
    CRSMA[4]=(CRSMA[0]*CRSMA[0]-(CRSMA[2]*CRSMA[2]+CRSMA[3]*CRSMA[3]));
    CRSMA[5]=(1+InvdGdI[0][0])*(1+InvdGdI[1][1])-InvdGdI[0][1]*InvdGdI[1][0];

    F_DELdouble1(TdCoef[0][0]);
    F_DELdouble1(TdCoef[0][1]);
    F_DELdouble1(TdCoef[1][0]);
    F_DELdouble1(TdCoef[1][1]);
}
void CL_GSIP::F_WCSA_GSIP_CRSMAatXCRPIX(int CID,double *CRPIX, double *CRSMA){
    double X_CRPIX[2];
    double dGdI[2][2],InvdGdI[2][2];
    double *TdCoef[2][2];
  
    X_CRPIX[0]=CRPIX[0];
    X_CRPIX[1]=CRPIX[1];

    TdCoef[0][0]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
    TdCoef[0][1]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
    TdCoef[1][0]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
    TdCoef[1][1]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));

    F_DIFFSIP(SIP_ORDER,CSIP[CID].SIP_AB[0],TdCoef[0][0],TdCoef[0][1]);
    F_DIFFSIP(SIP_ORDER,CSIP[CID].SIP_AB[1],TdCoef[1][0],TdCoef[1][1]);

    dGdI[0][0]=F_CALCVALUE(SIP_ORDER,TdCoef[0][0],X_CRPIX);
    dGdI[0][1]=F_CALCVALUE(SIP_ORDER,TdCoef[0][1],X_CRPIX);
    dGdI[1][0]=F_CALCVALUE(SIP_ORDER,TdCoef[1][0],X_CRPIX);
    dGdI[1][1]=F_CALCVALUE(SIP_ORDER,TdCoef[1][1],X_CRPIX);
    InvdGdI[0][0]=(1+dGdI[1][1])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0])-1;
    InvdGdI[0][1]=( -dGdI[0][1])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0]);
    InvdGdI[1][0]=( -dGdI[1][0])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0]);
    InvdGdI[1][1]=(1+dGdI[0][0])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0])-1;
    CRSMA[0]=0.5*(InvdGdI[0][0]+InvdGdI[1][1]);
    CRSMA[1]=0.5*(InvdGdI[0][1]-InvdGdI[1][0]);
    CRSMA[2]=0.5*(InvdGdI[0][0]-InvdGdI[1][1]);
    CRSMA[3]=0.5*(InvdGdI[0][1]+InvdGdI[1][0]);
    CRSMA[4]=((1+CRSMA[0])*(1+CRSMA[0])-(CRSMA[2]*CRSMA[2]+CRSMA[3]*CRSMA[3]));
    CRSMA[5]=(1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0];

    F_DELdouble1(TdCoef[0][0]);
    F_DELdouble1(TdCoef[0][1]);
    F_DELdouble1(TdCoef[1][0]);
    F_DELdouble1(TdCoef[1][1]);
}
void CL_GSIP::F_WCSA_GSIP_CRSMAatXRADEC(int CID,double *RADEC, double *CRSMA){
    double X_IM_WORLD[2],X_IM_PIXEL[2];
    double dIdG[2][2],InvdIdG[2][2];
    double *TdPCoef[2][2];
  
    F_PROJECTION(RADEC,X_IM_WORLD,CSIP[CID].CRVAL);
    X_IM_PIXEL[0]=CSIP[CID].InvCD[0][0]*X_IM_WORLD[0]+CSIP[CID].InvCD[0][1]*X_IM_WORLD[1];
    X_IM_PIXEL[1]=CSIP[CID].InvCD[1][0]*X_IM_WORLD[0]+CSIP[CID].InvCD[1][1]*X_IM_WORLD[1];

    TdPCoef[0][0]=F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TdPCoef[0][1]=F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TdPCoef[1][0]=F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TdPCoef[1][1]=F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));

    F_DIFFSIP(SIP_P_ORDER,CSIP[CID].SIP_ABP[0],TdPCoef[0][0],TdPCoef[0][1]);
    F_DIFFSIP(SIP_P_ORDER,CSIP[CID].SIP_ABP[1],TdPCoef[1][0],TdPCoef[1][1]);

    dIdG[0][0]=F_CALCVALUE(SIP_P_ORDER,TdPCoef[0][0],X_IM_PIXEL);
    dIdG[0][1]=F_CALCVALUE(SIP_P_ORDER,TdPCoef[0][1],X_IM_PIXEL);
    dIdG[1][0]=F_CALCVALUE(SIP_P_ORDER,TdPCoef[1][0],X_IM_PIXEL);
    dIdG[1][1]=F_CALCVALUE(SIP_P_ORDER,TdPCoef[1][1],X_IM_PIXEL);
    InvdIdG[0][0]=(1+dIdG[1][1])/((1+dIdG[0][0])*(1+dIdG[1][1])-dIdG[0][1]*dIdG[1][0])-1;
    InvdIdG[0][1]=( -dIdG[0][1])/((1+dIdG[0][0])*(1+dIdG[1][1])-dIdG[0][1]*dIdG[1][0]);
    InvdIdG[1][0]=( -dIdG[1][0])/((1+dIdG[0][0])*(1+dIdG[1][1])-dIdG[0][1]*dIdG[1][0]);
    InvdIdG[1][1]=(1+dIdG[0][0])/((1+dIdG[0][0])*(1+dIdG[1][1])-dIdG[0][1]*dIdG[1][0])-1;
    CRSMA[0]=0.5*(dIdG[0][0]+dIdG[1][1]);
    CRSMA[1]=0.5*(dIdG[0][1]-dIdG[1][0]);
    CRSMA[2]=0.5*(dIdG[0][0]-dIdG[1][1]);
    CRSMA[3]=0.5*(dIdG[0][1]+dIdG[1][0]);
    CRSMA[4]=((1+CRSMA[0])*(1+CRSMA[0])-(CRSMA[2]*CRSMA[2]+CRSMA[3]*CRSMA[3]));
    CRSMA[5]=(1+InvdIdG[0][0])*(1+InvdIdG[1][1])-InvdIdG[0][1]*InvdIdG[1][0];

    F_DELdouble1(TdPCoef[0][0]);
    F_DELdouble1(TdPCoef[0][1]);
    F_DELdouble1(TdPCoef[1][0]);
    F_DELdouble1(TdPCoef[1][1]);
}
void CL_GSIP::F_WCSA_GSIP_LOCALSIP(){
    int i,j,ij,CID;

    ij=0;
    for(i=0;i<SIP_ORDER+1;i++)
    for(j=0;j<SIP_ORDER+1;j++)
    if(i+j<SIP_ORDER+1){
        CSIP[CCDNUM].Coef[0][ij]=CSIP[CCDNUM].CD[0][0]*CSIP[CCDNUM].SIP_AB[0][ij]+CSIP[CCDNUM].CD[0][1]*CSIP[CCDNUM].SIP_AB[1][ij];
        CSIP[CCDNUM].Coef[1][ij]=CSIP[CCDNUM].CD[1][0]*CSIP[CCDNUM].SIP_AB[0][ij]+CSIP[CCDNUM].CD[1][1]*CSIP[CCDNUM].SIP_AB[1][ij];
        ij++;
    }

    CSIP[CCDNUM].Coef[0][1*(SIP_ORDER+1)+0]+=CSIP[CCDNUM].CD[0][0];
    CSIP[CCDNUM].Coef[0][0*(SIP_ORDER+1)+1]+=CSIP[CCDNUM].CD[0][1];
    CSIP[CCDNUM].Coef[1][1*(SIP_ORDER+1)+0]+=CSIP[CCDNUM].CD[1][0];
    CSIP[CCDNUM].Coef[1][0*(SIP_ORDER+1)+1]+=CSIP[CCDNUM].CD[1][1];

    ij=0;
    for(i=0;i<SIP_P_ORDER+1;i++)
    for(j=0;j<SIP_P_ORDER+1;j++)
    if(i+j<SIP_P_ORDER+1){
        CSIP[CCDNUM].PCoef[0][ij]=CSIP[CCDNUM].SIP_ABP[0][ij];
        CSIP[CCDNUM].PCoef[1][ij]=CSIP[CCDNUM].SIP_ABP[1][ij];
        ij++;
    }

    CSIP[CCDNUM].PCoef[0][1*(SIP_P_ORDER+1)+0]+=1.0;
    CSIP[CCDNUM].PCoef[1][0*(SIP_P_ORDER+1)+1]+=1.0;

    double IABP[2];

    for(CID=0;CID<CCDNUM;CID++){
        F_SIPROT(SIP_ORDER  ,CSIP[CID].GPOS[2],CSIP[CCDNUM].Coef[0] ,CSIP[CID].Coef[0] );
        F_SIPROT(SIP_ORDER  ,CSIP[CID].GPOS[2],CSIP[CCDNUM].Coef[1] ,CSIP[CID].Coef[1] );

        F_SIPROT(SIP_P_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].PCoef[0],CSIP[CID].PCoef[0]);
        F_SIPROT(SIP_P_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].PCoef[1],CSIP[CID].PCoef[1]);

        CSIP[CID].CD[0][0]=CSIP[CID].Coef[0][1*(SIP_ORDER+1)+0];
        CSIP[CID].CD[0][1]=CSIP[CID].Coef[0][0*(SIP_ORDER+1)+1];
        CSIP[CID].CD[1][0]=CSIP[CID].Coef[1][1*(SIP_ORDER+1)+0];
        CSIP[CID].CD[1][1]=CSIP[CID].Coef[1][0*(SIP_ORDER+1)+1]; 
        CSIP[CID].ANGLE=atan2(CSIP[CID].CD[1][0]-(-1)*CSIP[CID].CD[0][1],(-1)*CSIP[CID].CD[0][0]+CSIP[CID].CD[1][1]);

        CSIP[CID].InvCD[0][0]= CSIP[CID].CD[1][1]/(CSIP[CID].CD[0][0]*CSIP[CID].CD[1][1]-CSIP[CID].CD[1][0]*CSIP[CID].CD[0][1]);
        CSIP[CID].InvCD[0][1]=-CSIP[CID].CD[0][1]/(CSIP[CID].CD[0][0]*CSIP[CID].CD[1][1]-CSIP[CID].CD[1][0]*CSIP[CID].CD[0][1]);
        CSIP[CID].InvCD[1][0]=-CSIP[CID].CD[1][0]/(CSIP[CID].CD[0][0]*CSIP[CID].CD[1][1]-CSIP[CID].CD[1][0]*CSIP[CID].CD[0][1]);
        CSIP[CID].InvCD[1][1]= CSIP[CID].CD[0][0]/(CSIP[CID].CD[0][0]*CSIP[CID].CD[1][1]-CSIP[CID].CD[1][0]*CSIP[CID].CD[0][1]);

        ij=0;
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1){
            IABP[0]=CSIP[CCDNUM].CD[0][0]*CSIP[CID].PCoef[0][ij]+CSIP[CCDNUM].CD[0][1]*CSIP[CID].PCoef[1][ij];
            IABP[1]=CSIP[CCDNUM].CD[1][0]*CSIP[CID].PCoef[0][ij]+CSIP[CCDNUM].CD[1][1]*CSIP[CID].PCoef[1][ij];
            CSIP[CID].PCoef[0][ij]=CSIP[CID].InvCD[0][0]*IABP[0]+CSIP[CID].InvCD[0][1]*IABP[1];
            CSIP[CID].PCoef[1][ij]=CSIP[CID].InvCD[1][0]*IABP[0]+CSIP[CID].InvCD[1][1]*IABP[1];
            ij++;	
        }

        F_SIPROT(SIP_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].SIP_MAG,CSIP[CID].SIP_MAG);
        F_SIPROT(SIP_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].SIP_CRS[0],CSIP[CID].SIP_CRS[0]);
        F_SIPROT(SIP_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].SIP_CRS[1],CSIP[CID].SIP_CRS[1]);
        F_SIPROT(SIP_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].SIP_CRS[2],CSIP[CID].SIP_CRS[2]);
        F_SIPROT(SIP_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].SIP_CRS[3],CSIP[CID].SIP_CRS[3]);
        F_SIPROT(SIP_P_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].PSIP_MAG,CSIP[CID].PSIP_MAG);
        F_SIPROT(SIP_P_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].PSIP_CRS[0],CSIP[CID].PSIP_CRS[0]);
        F_SIPROT(SIP_P_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].PSIP_CRS[1],CSIP[CID].PSIP_CRS[1]);
        F_SIPROT(SIP_P_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].PSIP_CRS[2],CSIP[CID].PSIP_CRS[2]);
        F_SIPROT(SIP_P_ORDER,CSIP[CID].GPOS[2],CSIP[CCDNUM].PSIP_CRS[3],CSIP[CID].PSIP_CRS[3]);

        CSIP[CID].MAXFRAD =CSIP[CCDNUM].MAXFRAD;
        CSIP[CID].MAXDRAD =CSIP[CCDNUM].MAXDRAD;
        CSIP[CID].CRVAL[0]=CSIP[CCDNUM].CRVAL[0];
        CSIP[CID].CRVAL[1]=CSIP[CCDNUM].CRVAL[1];
        CSIP[CID].OAVAL[0]=CSIP[CCDNUM].OAVAL[0];
        CSIP[CID].OAVAL[1]=CSIP[CCDNUM].OAVAL[1];
        CSIP[CID].CRPIX[0]=-(CSIP[CID].GPOS[0]-CSIP[CCDNUM].CRPIX[0])*cos(CSIP[CID].GPOS[2])-(CSIP[CID].GPOS[1]-CSIP[CCDNUM].CRPIX[1])*sin(CSIP[CID].GPOS[2]);
        CSIP[CID].CRPIX[1]=-(CSIP[CID].GPOS[1]-CSIP[CCDNUM].CRPIX[1])*cos(CSIP[CID].GPOS[2])+(CSIP[CID].GPOS[0]-CSIP[CCDNUM].CRPIX[0])*sin(CSIP[CID].GPOS[2]);
        CSIP[CID].OAPIX[0]=-(CSIP[CID].GPOS[0]-CSIP[CCDNUM].OAPIX[0])*cos(CSIP[CID].GPOS[2])-(CSIP[CID].GPOS[1]-CSIP[CCDNUM].OAPIX[1])*sin(CSIP[CID].GPOS[2]);
        CSIP[CID].OAPIX[1]=-(CSIP[CID].GPOS[1]-CSIP[CCDNUM].OAPIX[1])*cos(CSIP[CID].GPOS[2])+(CSIP[CID].GPOS[0]-CSIP[CCDNUM].OAPIX[0])*sin(CSIP[CID].GPOS[2]);
    }

    F_WCSA_GSIP_SETSIP();
    F_WCSA_GSIP_SETPSIP();
}

void CL_GSIP::F_WCSA_GSIP_SETSIP(){
    int i,j,ij;
    int CID;

    for(CID=0;CID<CCDNUM;CID++){
        ij=0;
        for(i=0;i<SIP_ORDER+1;i++)
        for(j=0;j<SIP_ORDER+1;j++)
        if(i+j<SIP_ORDER+1){
            CSIP[CID].SIP_AB[0][ij]=CSIP[CID].InvCD[0][0]*CSIP[CID].Coef[0][ij]+CSIP[CID].InvCD[0][1]*CSIP[CID].Coef[1][ij];
            CSIP[CID].SIP_AB[1][ij]=CSIP[CID].InvCD[1][0]*CSIP[CID].Coef[0][ij]+CSIP[CID].InvCD[1][1]*CSIP[CID].Coef[1][ij];
            ij++;	
        }
        CSIP[CID].SIP_AB[0][1*(SIP_ORDER+1)+0]-=1.0;
        CSIP[CID].SIP_AB[1][0*(SIP_ORDER+1)+1]-=1.0;
    }
}
void CL_GSIP::F_WCSA_GSIP_SETPSIP(){
    int i,j,ij;
    int CID;

    for(CID=0;CID<CCDNUM;CID++){
        ij=0;
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1){
            CSIP[CID].SIP_ABP[0][ij]=CSIP[CID].PCoef[0][ij];
            CSIP[CID].SIP_ABP[1][ij]=CSIP[CID].PCoef[1][ij];
            ij++;	
        }
        CSIP[CID].SIP_ABP[0][1*(SIP_P_ORDER+1)+0]-=1.0;
        CSIP[CID].SIP_ABP[1][0*(SIP_P_ORDER+1)+1]-=1.0;
    }
}
void CL_GSIP::F_WCSA_GSIP_SHOWGPOS(){
    cout << "-- CCD POSITIONS --" << endl;
    int CID;
    for(CID=0;CID<CCDNUM+1;CID++)
    cout << CSIP[CID].ID << "	" << CSIP[CID].GPOS_INIT[0]
                         << "	" << CSIP[CID].GPOS_INIT[1]
                         << "	" << CSIP[CID].GPOS_INIT[2]
                         << "	" << CSIP[CID].GPOS[0]
                         << "	" << CSIP[CID].GPOS[1]
                         << "	" << CSIP[CID].GPOS[2] << endl;
double A[3]={0};
    for(CID=0;CID<CCDNUM;CID++){
    A[0]+=1;
    A[1]+=(CSIP[CID].GPOS_INIT[0]-CSIP[CID].GPOS[0]);
    A[2]+=(CSIP[CID].GPOS_INIT[0]-CSIP[CID].GPOS[0])*(CSIP[CID].GPOS_INIT[0]-CSIP[CID].GPOS[0]);
    }
    cout << "AVE : " << A[1]/A[0] << endl;
    cout << "RMS : " << sqrt((A[2]-A[1]*A[1]/A[0])/(A[0]-1)) << endl;
}
void CL_GSIP::F_WCSA_GSIP_SHOWGSIP(){
    cout << "-- GSIP CHECK --" << endl;
    cout << fixed;
    cout.unsetf(ios::fixed);
    cout << "CCDNUM      : " << CCDNUM      << endl;
    cout << "ALLREFNUM   : " << ALLREFNUM   << endl;
    cout << "CRPIXMODE   : " << CRPIXMODE   << endl;
    cout << "OAMODE      : " << OAMODE      << endl;
    cout << "CCDPOSMODE  : " << CCDPOSMODE  << endl;
    cout << "ANGLE       : " << ANGLE       << endl;
    cout << "SIP_L_ORDER : " << SIP_L_ORDER << endl;
    cout << "SIP_ORDER   : " << SIP_ORDER   << endl;
    cout << "SIP_PORDER  : " << SIP_P_ORDER << endl;
    cout << "ID          : " << CSIP[CCDNUM].ID       << endl;
    cout << "Index X     : " << CSIP[CCDNUM].POSID[0] << endl;
    cout << "Index Y     : " << CSIP[CCDNUM].POSID[1] << endl;
    cout << "REFNUM      : " << CSIP[CCDNUM].REFNUM   << endl;
    cout << "FITNUM      : " << CSIP[CCDNUM].FITNUM   << endl;
    cout << "MAXFITRAD   : " << CSIP[CCDNUM].MAXFRAD  << endl;
    cout << "MAXDATARAD  : " << CSIP[CCDNUM].MAXDRAD  << endl;
    cout << "GLOBAL POS_X: " << CSIP[CCDNUM].GPOS[0]  << endl;
    cout << "GLOBAL POS_Y: " << CSIP[CCDNUM].GPOS[1]  << endl;
    cout << "GLOBAL POS_T: " << CSIP[CCDNUM].GPOS[2]  << endl; 
    cout << "CRPIX1      : " << CSIP[CCDNUM].CRPIX[0] << endl;
    cout << "CRPIX2      : " << CSIP[CCDNUM].CRPIX[1] << endl;
    cout << "CRVAL1      : " << CSIP[CCDNUM].CRVAL[0] << endl;
    cout << "CRVAL2      : " << CSIP[CCDNUM].CRVAL[1] << endl;
    cout << "CD_1_1      : " << CSIP[CCDNUM].CD[0][0] << endl;
    cout << "CD_1_2      : " << CSIP[CCDNUM].CD[0][1] << endl;
    cout << "CD_2_1      : " << CSIP[CCDNUM].CD[1][0] << endl;
    cout << "CD_2_2      : " << CSIP[CCDNUM].CD[1][1] << endl;
    cout << "InvCD_1_1   : " << CSIP[CCDNUM].InvCD[0][0] << endl;
    cout << "InvCD_1_2   : " << CSIP[CCDNUM].InvCD[0][1] << endl;
    cout << "InvCD_2_1   : " << CSIP[CCDNUM].InvCD[1][0] << endl;
    cout << "InvCD_2_2   : " << CSIP[CCDNUM].InvCD[1][1] << endl;
    cout << fixed;
    cout <<endl;
}
void CL_GSIP::F_WCSA_GSIP_SHOWCSIP(int CID){
    cout << "-- CSIP CHECK : CCD : " << setw(3) << setfill('0') << CSIP[CID].ID  << " -"<< endl;
    cout << "ID          : " << CSIP[CID].ID       << endl;
    cout << "Index X     : " << CSIP[CID].POSID[0] << endl;
    cout << "Index Y     : " << CSIP[CID].POSID[1] << endl;
    cout << "REFNUM      : " << CSIP[CID].REFNUM   << endl;
    cout << "FITNUM      : " << CSIP[CID].FITNUM   << endl;
    cout << "MAXFITRAD   : " << CSIP[CID].MAXFRAD  << endl;
    cout << "MAXDATARAD  : " << CSIP[CID].MAXDRAD  << endl;
//    cout << "PHASE       : " << CSIP[CID].PHASE    << endl;
    cout << "GLOBAL POS_X: " << CSIP[CID].GPOS[0]  << endl;
    cout << "GLOBAL POS_Y: " << CSIP[CID].GPOS[1]  << endl;
    cout << "GLOBAL POS_T: " << CSIP[CID].GPOS[2]  << endl;
    cout << "CRPIX1      : " << CSIP[CID].CRPIX[0] << endl;
    cout << "CRPIX2      : " << CSIP[CID].CRPIX[1] << endl;
    cout << "CRVAL1      : " << CSIP[CID].CRVAL[0] << endl;
    cout << "CRVAL2      : " << CSIP[CID].CRVAL[1] << endl;
    cout.unsetf(ios::fixed);
    cout << "CD_1_1      : " << CSIP[CID].CD[0][0] << endl;
    cout << "CD_1_2      : " << CSIP[CID].CD[0][1] << endl;
    cout << "CD_2_1      : " << CSIP[CID].CD[1][0] << endl;
    cout << "CD_2_2      : " << CSIP[CID].CD[1][1] << endl;
    cout << "InvCD_1_1   : " << CSIP[CID].InvCD[0][0] << endl;
    cout << "InvCD_1_2   : " << CSIP[CID].InvCD[0][1] << endl;
    cout << "InvCD_2_1   : " << CSIP[CID].InvCD[1][0] << endl;
    cout << "InvCD_2_2   : " << CSIP[CID].InvCD[1][1] << endl;
    cout << scientific;
    int i,j,ij;
    ij=0;
    for(i=0;i<SIP_ORDER+1;i++)
    for(j=0;j<SIP_ORDER+1;j++)
    if(i+j<SIP_ORDER+1)
    cout << " SIPx["<<i<<"]["<<j<<"] : "<< CSIP[CID].SIP_AB[0][ij++]<<endl;
    ij=0;
    for(i=0;i<SIP_ORDER+1;i++)
    for(j=0;j<SIP_ORDER+1;j++)
    if(i+j<SIP_ORDER+1)
    cout << " SIPy["<<i<<"]["<<j<<"] : "<< CSIP[CID].SIP_AB[1][ij++]<<endl;
    ij=0;
    for(i=0;i<SIP_P_ORDER+1;i++)
    for(j=0;j<SIP_P_ORDER+1;j++)
    if(i+j<SIP_P_ORDER+1)
    cout << "PSIPx["<<i<<"]["<<j<<"] : "<< CSIP[CID].SIP_ABP[0][ij++]<<endl;
    ij=0;
    for(i=0;i<SIP_P_ORDER+1;i++)
    for(j=0;j<SIP_P_ORDER+1;j++)
    if(i+j<SIP_P_ORDER+1)
    cout << "PSIPy["<<i<<"]["<<j<<"] : "<< CSIP[CID].SIP_ABP[1][ij++]<<endl;
    cout << " SIPGxErrAVE: " << CSIP[CID].SIP_AB_ERR[0][0] << "	(pix)"<< endl;
    cout << " SIPGxErrRMS: " << CSIP[CID].SIP_AB_ERR[0][1] << "	(pix)" << endl;
    cout << " SIPGxErrMAX: " << CSIP[CID].SIP_AB_ERR[0][2] << "	(pix)" << endl;
    cout << " SIPGyErrAVE: " << CSIP[CID].SIP_AB_ERR[1][0] << "	(pix)" << endl;
    cout << " SIPGyErrRMS: " << CSIP[CID].SIP_AB_ERR[1][1] << "	(pix)" << endl;
    cout << " SIPGyErrMAX: " << CSIP[CID].SIP_AB_ERR[1][2] << "	(pix)" << endl;
    cout << "PSIPGxErrAVE: " << CSIP[CID].SIP_ABP_ERR[0][0] << "	(pix)" << endl;
    cout << "PSIPGxErrRMS: " << CSIP[CID].SIP_ABP_ERR[0][1] << "	(pix)" << endl;
    cout << "PSIPGxErrMAX: " << CSIP[CID].SIP_ABP_ERR[0][2] << "	(pix)" << endl;
    cout << "PSIPGyErrAVE: " << CSIP[CID].SIP_ABP_ERR[1][0] << "	(pix)" << endl;
    cout << "PSIPGyErrRMS: " << CSIP[CID].SIP_ABP_ERR[1][1] << "	(pix)" << endl;
    cout << "PSIPGyErrMAX: " << CSIP[CID].SIP_ABP_ERR[1][2] << "	(pix)" << endl;
    cout << "--------------------------------------------------" <<endl;
    cout.unsetf(ios::scientific);
    cout << endl;
}
void CL_GSIP::F_WCSA_GSIP_SHOWGLOBAL(){
    cout << "--- GLOBAL FITTING STATISTICS --------------------" <<endl;
    cout << "REFERENCE NUM: " << ALLREFNUM<< endl;
    cout << "FITTING   NUM: " << ALLFITNUM<< endl;
    cout << fixed;
    cout << "CRPIX(pix)   : " << CSIP[CCDNUM].CRPIX[0] << " , " << CSIP[CCDNUM].CRPIX[1]<< endl;
    cout << "CRVAL(deg)   : " << CSIP[CCDNUM].CRVAL[0] << " , " << CSIP[CCDNUM].CRVAL[1]<< endl;
    cout << "OAPIX(pix)   : " << CSIP[CCDNUM].OAPIX[0] << " , " << CSIP[CCDNUM].OAPIX[1]<< endl;
    cout << "OAVAL(deg)   : " << CSIP[CCDNUM].OAVAL[0] << " , " << CSIP[CCDNUM].OAVAL[1]<< endl;
    cout.unsetf(ios::fixed);
    cout << "CD_1_1       : " << CSIP[CCDNUM].CD[0][0] << endl;
    cout << "CD_1_2       : " << CSIP[CCDNUM].CD[0][1] << endl;
    cout << "CD_2_1       : " << CSIP[CCDNUM].CD[1][0] << endl;
    cout << "CD_2_2       : " << CSIP[CCDNUM].CD[1][1] << endl;
    cout << "InvCD_1_1    : " << CSIP[CCDNUM].InvCD[0][0] << endl;
    cout << "InvCD_1_2    : " << CSIP[CCDNUM].InvCD[0][1] << endl;
    cout << "InvCD_2_1    : " << CSIP[CCDNUM].InvCD[1][0] << endl;
    cout << "InvCD_2_2    : " << CSIP[CCDNUM].InvCD[1][1] << endl;
    cout << scientific;
    int i,j,ij;
    ij=0;
    for(i=0;i<SIP_ORDER+1;i++)
    for(j=0;j<SIP_ORDER+1;j++)
    if(i+j<SIP_ORDER+1)
    cout << " SIPx["<<i<<"]["<<j<<"] : "<< CSIP[CCDNUM].SIP_AB[0][ij++]<<endl;
    ij=0;
    for(i=0;i<SIP_ORDER+1;i++)
    for(j=0;j<SIP_ORDER+1;j++)
    if(i+j<SIP_ORDER+1)
    cout << " SIPy["<<i<<"]["<<j<<"] : "<< CSIP[CCDNUM].SIP_AB[1][ij++]<<endl;
    ij=0;
    for(i=0;i<SIP_P_ORDER+1;i++)
    for(j=0;j<SIP_P_ORDER+1;j++)
    if(i+j<SIP_P_ORDER+1)
    cout << "PSIPx["<<i<<"]["<<j<<"] : "<< CSIP[CCDNUM].SIP_ABP[0][ij++]<<endl;
    ij=0;
    for(i=0;i<SIP_P_ORDER+1;i++)
    for(j=0;j<SIP_P_ORDER+1;j++)
    if(i+j<SIP_P_ORDER+1)
    cout << "PSIPy["<<i<<"]["<<j<<"] : "<< CSIP[CCDNUM].SIP_ABP[1][ij++]<<endl;
    cout << " SIPGxErrAVE: " << CSIP[CCDNUM].SIP_AB_ERR[0][0] << "	(pix)"<< endl;
    cout << " SIPGxErrRMS: " << CSIP[CCDNUM].SIP_AB_ERR[0][1] << "	(pix)" << endl;
    cout << " SIPGxErrMAX: " << CSIP[CCDNUM].SIP_AB_ERR[0][2] << "	(pix)" << endl;
    cout << " SIPGyErrAVE: " << CSIP[CCDNUM].SIP_AB_ERR[1][0] << "	(pix)" << endl;
    cout << " SIPGyErrRMS: " << CSIP[CCDNUM].SIP_AB_ERR[1][1] << "	(pix)" << endl;
    cout << " SIPGyErrMAX: " << CSIP[CCDNUM].SIP_AB_ERR[1][2] << "	(pix)" << endl;
    cout << "PSIPGxErrAVE: " << CSIP[CCDNUM].SIP_ABP_ERR[0][0] << "	(pix)" << endl;
    cout << "PSIPGxErrRMS: " << CSIP[CCDNUM].SIP_ABP_ERR[0][1] << "	(pix)" << endl;
    cout << "PSIPGxErrMAX: " << CSIP[CCDNUM].SIP_ABP_ERR[0][2] << "	(pix)" << endl;
    cout << "PSIPGyErrAVE: " << CSIP[CCDNUM].SIP_ABP_ERR[1][0] << "	(pix)" << endl;
    cout << "PSIPGyErrRMS: " << CSIP[CCDNUM].SIP_ABP_ERR[1][1] << "	(pix)" << endl;
    cout << "PSIPGyErrMAX: " << CSIP[CCDNUM].SIP_ABP_ERR[1][2] << "	(pix)" << endl;
    cout << "--------------------------------------------------" <<endl;
    cout.unsetf(ios::scientific);
    cout << endl;
}
void CL_GSIP::F_WCSA_GSIP_CHECKCCDPOSITION(){
    int CID,CID2;

    for(CID=0;CID<CCDNUM;CID++)
    if(CID<100)
    for(CID2=CID+1;CID2<CCDNUM;CID2++)
    if(CID2<100)
    if(hypot(CSIP[CID].GPOS[0]-CSIP[CID2].GPOS[0],CSIP[CID].GPOS[1]-CSIP[CID2].GPOS[1])<2000){
        cout << "CID ;  " << CID << " : GPOS x : " << CSIP[CID].GPOS[0] << " : GPOS y : " << CSIP[CID].GPOS[1] << endl;
        cout << "CID ;  " << CID2 << " : GPOS x : " << CSIP[CID2].GPOS[0] << " : GPOS y : " << CSIP[CID2].GPOS[1] << endl;
        if(CCDNUM<11){
        F_WCSA_GSIP_SETDEFAULTPOSITIONS_SC();
        }else{
        F_WCSA_GSIP_SETDEFAULTPOSITIONS_HSC();
        }
        cout << "---------------------------------------------" << endl;
        cout << "Warning : Separation between CHIPID : " << CID << " and " << CID2 << " is under 2000" << endl;
        cout << "          USING DEFAULT VALUES FOR CCD POSITIONS " << endl;
        cout << "---------------------------------------------" << endl;
        break;
    }
}
void CL_GSIP::F_WCSA_GSIP_SETINITIAL(){
    int CID;

    ANGLE=0;
    CD[0][0]=-4.7e-5;
    CD[0][1]= 0.0;
    CD[1][0]= 0.0;
    CD[1][1]= 4.7e-5;
    InvCD[0][0]=-21429;
    InvCD[0][1]= 0.0;
    InvCD[1][0]= 0.0;
    InvCD[1][1]= 21429;


    for(CID=0;CID<CCDNUM+1;CID++){
    CSIP[CID].FITNUM=0;
    CSIP[CID].REFNUM=0;
    CSIP[CID].OAVAL[0]=CSIP[CID].OAVAL[1]=0;
    CSIP[CID].OAPIX[0]=CSIP[CID].OAPIX[1]=0;
    CSIP[CID].CRVAL[0]=CSIP[CID].CRVAL[1]=0;
    CSIP[CID].CRPIX[0]=CSIP[CID].CRPIX[1]=0;
    CSIP[CID].ANGLE=0;
    CSIP[CID].POSID[0]=CSIP[CID].POSID[1]=0;

    CSIP[CID].CD[0][0]=CD[0][0];
    CSIP[CID].CD[0][1]=CD[0][1];
    CSIP[CID].CD[1][0]=CD[1][0];
    CSIP[CID].CD[1][1]=CD[1][1];
    CSIP[CID].InvCD[0][0]=InvCD[0][0];
    CSIP[CID].InvCD[0][1]=InvCD[0][1];
    CSIP[CID].InvCD[1][0]=InvCD[1][0];
    CSIP[CID].InvCD[1][1]=InvCD[1][1];
    CSIP[CID].SIP_AB_ERR[0][0]=0;
    CSIP[CID].SIP_AB_ERR[0][1]=0;
    CSIP[CID].SIP_AB_ERR[1][0]=0;
    CSIP[CID].SIP_AB_ERR[1][1]=0;
    CSIP[CID].SIP_ABP_ERR[0][0]=0;
    CSIP[CID].SIP_ABP_ERR[0][1]=0;
    CSIP[CID].SIP_ABP_ERR[1][0]=0;
    CSIP[CID].SIP_ABP_ERR[1][1]=0;
    }
}
void CL_GSIP::F_WCSA_GSIP_SETDEFAULTPOSITIONS_SC(){
    int CID;
    CSIP[  0].GPOS[0]= 3272.00;
    CSIP[  0].GPOS[1]=   50.00;
    CSIP[  0].GPOS[2]= 0.00000;
    CSIP[  1].GPOS[0]= 1124.00;
    CSIP[  1].GPOS[1]=   50.00;
    CSIP[  1].GPOS[2]= 0.00000;
    CSIP[  2].GPOS[0]=-1024.00;
    CSIP[  2].GPOS[1]=   50.00;
    CSIP[  2].GPOS[2]= 0.00000;
    CSIP[  3].GPOS[0]= 3272.00;
    CSIP[  3].GPOS[1]=-4146.00;
    CSIP[  3].GPOS[2]= 0.00000;
    CSIP[  4].GPOS[0]= 1124.00;
    CSIP[  4].GPOS[1]=-4146.00;
    CSIP[  4].GPOS[2]= 0.00000;
    CSIP[  5].GPOS[0]=-1024.00;
    CSIP[  5].GPOS[1]=-4146.00;
    CSIP[  5].GPOS[2]= 0.00000;
    CSIP[  6].GPOS[0]=-5320.00;
    CSIP[  6].GPOS[1]=   50.00;
    CSIP[  6].GPOS[2]= 0.00000;
    CSIP[  7].GPOS[0]=-3172.00;
    CSIP[  7].GPOS[1]=   50.00;
    CSIP[  7].GPOS[2]= 0.00000;
    CSIP[  8].GPOS[0]=-5320.00;
    CSIP[  8].GPOS[1]=-4146.00;
    CSIP[  8].GPOS[2]= 0.00000;
    CSIP[  9].GPOS[0]=-3172.00;
    CSIP[  9].GPOS[1]=-4146.00;
    for(CID=0;CID<CCDNUM;CID++){
        CSIP[CID].ID=CID;
        CSIP[CID].GPOS_INIT[0]=CSIP[CID].GPOS[0];
        CSIP[CID].GPOS_INIT[1]=CSIP[CID].GPOS[1];
        CSIP[CID].GPOS_INIT[2]=CSIP[CID].GPOS[2];
    }

}
void CL_GSIP::F_WCSA_GSIP_SETDEFAULTPOSITIONS_HSC(){
    int CID;
    CSIP[0].GPOS[0]=	13835.7;
    CSIP[0].GPOS[1]=	-8918.13;
    CSIP[0].GPOS[2]=	-4.54687e-05;
    CSIP[1].GPOS[0]=	13836.5;
    CSIP[1].GPOS[1]=	-4439.67;
    CSIP[1].GPOS[2]=	-0.000112826;
    CSIP[2].GPOS[0]=	13837.3;
    CSIP[2].GPOS[1]=	35.1634;
    CSIP[2].GPOS[2]=	-9.53666e-05;
    CSIP[3].GPOS[0]=	13838.1;
    CSIP[3].GPOS[1]=	4512.62;
    CSIP[3].GPOS[2]=	-0.000241431;
    CSIP[4].GPOS[0]=	11711;
    CSIP[4].GPOS[1]=	-13392.7;
    CSIP[4].GPOS[2]=	2.83549e-06;
    CSIP[5].GPOS[0]=	11711.8;
    CSIP[5].GPOS[1]=	-8916.35;
    CSIP[5].GPOS[2]=	-0.000510185;
    CSIP[6].GPOS[0]=	11712.9;
    CSIP[6].GPOS[1]=	-4440.07;
    CSIP[6].GPOS[2]=	-0.00062244;
    CSIP[7].GPOS[0]=	11716.8;
    CSIP[7].GPOS[1]=	34.3342;
    CSIP[7].GPOS[2]=	0.000614981;
    CSIP[8].GPOS[0]=	11715.4;
    CSIP[8].GPOS[1]=	4513.46;
    CSIP[8].GPOS[2]=	-0.000646452;
    CSIP[9].GPOS[0]=	11716.1;
    CSIP[9].GPOS[1]=	8989.21;
    CSIP[9].GPOS[2]=	-0.00078577;
    CSIP[10].GPOS[0]=	9588.69;
    CSIP[10].GPOS[1]=	-13391.9;
    CSIP[10].GPOS[2]=	-0.000183744;
    CSIP[11].GPOS[0]=	9590.86;
    CSIP[11].GPOS[1]=	-8917.01;
    CSIP[11].GPOS[2]=	0.000576925;
    CSIP[12].GPOS[0]=	9589.48;
    CSIP[12].GPOS[1]=	-4435.47;
    CSIP[12].GPOS[2]=	-0.000681665;
    CSIP[13].GPOS[0]=	9589.01;
    CSIP[13].GPOS[1]=	36.828;
    CSIP[13].GPOS[2]=	-0.000667003;
    CSIP[14].GPOS[0]=	9594.49;
    CSIP[14].GPOS[1]=	4512;
    CSIP[14].GPOS[2]=	0.000230797;
    CSIP[15].GPOS[0]=	9593.56;
    CSIP[15].GPOS[1]=	8988.86;
    CSIP[15].GPOS[2]=	-0.000332099;
    CSIP[16].GPOS[0]=	7464.16;
    CSIP[16].GPOS[1]=	-13169.2;
    CSIP[16].GPOS[2]=	-0.000334858;
    CSIP[17].GPOS[0]=	7465.65;
    CSIP[17].GPOS[1]=	-8689.21;
    CSIP[17].GPOS[2]=	-0.000340941;
    CSIP[18].GPOS[0]=	7465.93;
    CSIP[18].GPOS[1]=	-4214.43;
    CSIP[18].GPOS[2]=	-0.000414322;
    CSIP[19].GPOS[0]=	7467.17;
    CSIP[19].GPOS[1]=	36.645;
    CSIP[19].GPOS[2]=	-7.34564e-05;
    CSIP[20].GPOS[0]=	7467.3;
    CSIP[20].GPOS[1]=	4513.84;
    CSIP[20].GPOS[2]=	-0.000535604;
    CSIP[21].GPOS[0]=	7473.86;
    CSIP[21].GPOS[1]=	8986.12;
    CSIP[21].GPOS[2]=	0.00115436;
    CSIP[22].GPOS[0]=	5340.47;
    CSIP[22].GPOS[1]=	-17642.2;
    CSIP[22].GPOS[2]=	-0.000126147;
    CSIP[23].GPOS[0]=	5344.79;
    CSIP[23].GPOS[1]=	-13166;
    CSIP[23].GPOS[2]=	0.00027998;
    CSIP[24].GPOS[0]=	5345.81;
    CSIP[24].GPOS[1]=	-8689.51;
    CSIP[24].GPOS[2]=	0.000616083;
    CSIP[25].GPOS[0]=	5343.96;
    CSIP[25].GPOS[1]=	-4211.39;
    CSIP[25].GPOS[2]=	0.000503702;
    CSIP[26].GPOS[0]=	5343.8;
    CSIP[26].GPOS[1]=	36.4384;
    CSIP[26].GPOS[2]=	-0.000469916;
    CSIP[27].GPOS[0]=	5347;
    CSIP[27].GPOS[1]=	4513.36;
    CSIP[27].GPOS[2]=	-0.000225362;
    CSIP[28].GPOS[0]=	5351.97;
    CSIP[28].GPOS[1]=	8987.31;
    CSIP[28].GPOS[2]=	0.000947141;
    CSIP[29].GPOS[0]=	5347.01;
    CSIP[29].GPOS[1]=	13465;
    CSIP[29].GPOS[2]=	-7.73811e-05;
    CSIP[30].GPOS[0]=	3220.82;
    CSIP[30].GPOS[1]=	-17642.3;
    CSIP[30].GPOS[2]=	0.000335482;
    CSIP[31].GPOS[0]=	3219.1;
    CSIP[31].GPOS[1]=	-13167.4;
    CSIP[31].GPOS[2]=	-0.000594003;
    CSIP[32].GPOS[0]=	3219.24;
    CSIP[32].GPOS[1]=	-8690.65;
    CSIP[32].GPOS[2]=	0.000281838;
    CSIP[33].GPOS[0]=	3222.43;
    CSIP[33].GPOS[1]=	-4213.31;
    CSIP[33].GPOS[2]=	0.000760842;
    CSIP[34].GPOS[0]=	3225.26;
    CSIP[34].GPOS[1]=	33.188;
    CSIP[34].GPOS[2]=	0.00383119;
    CSIP[35].GPOS[0]=	3222.06;
    CSIP[35].GPOS[1]=	4512.6;
    CSIP[35].GPOS[2]=	-0.00069161;
    CSIP[36].GPOS[0]=	3226.2;
    CSIP[36].GPOS[1]=	8986.99;
    CSIP[36].GPOS[2]=	0.000125877;
    CSIP[37].GPOS[0]=	3224.14;
    CSIP[37].GPOS[1]=	13465.3;
    CSIP[37].GPOS[2]=	-0.000270292;
    CSIP[38].GPOS[0]=	1096.79;
    CSIP[38].GPOS[1]=	-17641.8;
    CSIP[38].GPOS[2]=	-0.000226312;
    CSIP[39].GPOS[0]=	1095.48;
    CSIP[39].GPOS[1]=	-13165.3;
    CSIP[39].GPOS[2]=	-0.000422965;
    CSIP[40].GPOS[0]=	1097.47;
    CSIP[40].GPOS[1]=	-8689.95;
    CSIP[40].GPOS[2]=	1.55976e-05;
    CSIP[41].GPOS[0]=	1097.81;
    CSIP[41].GPOS[1]=	-4211.98;
    CSIP[41].GPOS[2]=	0.000353446;
    CSIP[42].GPOS[0]=	1099.38;
    CSIP[42].GPOS[1]=	36.0517;
    CSIP[42].GPOS[2]=	-0.000107356;
    CSIP[43].GPOS[0]=	1100.66;
    CSIP[43].GPOS[1]=	4512.63;
    CSIP[43].GPOS[2]=	5.24356e-05;
    CSIP[44].GPOS[0]=	1103.17;
    CSIP[44].GPOS[1]=	8989.36;
    CSIP[44].GPOS[2]=	0.000296259;
    CSIP[45].GPOS[0]=	1101.91;
    CSIP[45].GPOS[1]=	13464.9;
    CSIP[45].GPOS[2]=	-2.53376e-05;
    CSIP[46].GPOS[0]=	-1026.74;
    CSIP[46].GPOS[1]=	-17641.9;
    CSIP[46].GPOS[2]=	-0.000320893;
    CSIP[47].GPOS[0]=	-1027.89;
    CSIP[47].GPOS[1]=	-13165.7;
    CSIP[47].GPOS[2]=	4.94989e-05;
    CSIP[48].GPOS[0]=	-1025.51;
    CSIP[48].GPOS[1]=	-8690.7;
    CSIP[48].GPOS[2]=	3.2887e-06;
    CSIP[49].GPOS[0]=	-1025;
    CSIP[49].GPOS[1]=	-4214.12;
    CSIP[49].GPOS[2]=	0.000197968;
    CSIP[50].GPOS[0]=	-1024.96;
    CSIP[50].GPOS[1]=	36.9914;
    CSIP[50].GPOS[2]=	0.000499231;
    CSIP[51].GPOS[0]=	-1020.94;
    CSIP[51].GPOS[1]=	4511.93;
    CSIP[51].GPOS[2]=	0.00049229;
    CSIP[52].GPOS[0]=	-1021.65;
    CSIP[52].GPOS[1]=	8990.84;
    CSIP[52].GPOS[2]=	-0.00024973;
    CSIP[53].GPOS[0]=	-1020.64;
    CSIP[53].GPOS[1]=	13464.7;
    CSIP[53].GPOS[2]=	-0.000168522;
    CSIP[54].GPOS[0]=	-3148.99;
    CSIP[54].GPOS[1]=	-17642.3;
    CSIP[54].GPOS[2]=	-0.000504373;
    CSIP[55].GPOS[0]=	-3150.38;
    CSIP[55].GPOS[1]=	-13165.1;
    CSIP[55].GPOS[2]=	-0.00062316;
    CSIP[56].GPOS[0]=	-3147.94;
    CSIP[56].GPOS[1]=	-8688.81;
    CSIP[56].GPOS[2]=	-6.55715e-06;
    CSIP[57].GPOS[0]=	-3149.12;
    CSIP[57].GPOS[1]=	-4214.89;
    CSIP[57].GPOS[2]=	-0.000568245;
    CSIP[58].GPOS[0]=	-3147.36;
    CSIP[58].GPOS[1]=	36.5786;
    CSIP[58].GPOS[2]=	-0.000283492;
    CSIP[59].GPOS[0]=	-3145.11;
    CSIP[59].GPOS[1]=	4514.52;
    CSIP[59].GPOS[2]=	-0.000532731;
    CSIP[60].GPOS[0]=	-3141.72;
    CSIP[60].GPOS[1]=	8990.33;
    CSIP[60].GPOS[2]=	7.47808e-05;
    CSIP[61].GPOS[0]=	-3143.63;
    CSIP[61].GPOS[1]=	13466.3;
    CSIP[61].GPOS[2]=	-0.000128148;
    CSIP[62].GPOS[0]=	-5270.04;
    CSIP[62].GPOS[1]=	-17641.6;
    CSIP[62].GPOS[2]=	0.000180646;
    CSIP[63].GPOS[0]=	-5273.04;
    CSIP[63].GPOS[1]=	-13165.5;
    CSIP[63].GPOS[2]=	-2.14473e-05;
    CSIP[64].GPOS[0]=	-5272.53;
    CSIP[64].GPOS[1]=	-8687.67;
    CSIP[64].GPOS[2]=	-0.000325514;
    CSIP[65].GPOS[0]=	-5271.81;
    CSIP[65].GPOS[1]=	-4212.03;
    CSIP[65].GPOS[2]=	-0.00036776;
    CSIP[66].GPOS[0]=	-5270.5;
    CSIP[66].GPOS[1]=	38.163;
    CSIP[66].GPOS[2]=	-0.000383271;
    CSIP[67].GPOS[0]=	-5267.78;
    CSIP[67].GPOS[1]=	4516.3;
    CSIP[67].GPOS[2]=	-0.000379431;
    CSIP[68].GPOS[0]=	-5266.31;
    CSIP[68].GPOS[1]=	8989.46;
    CSIP[68].GPOS[2]=	0.000193886;
    CSIP[69].GPOS[0]=	-5265.91;
    CSIP[69].GPOS[1]=	13466.7;
    CSIP[69].GPOS[2]=	-0.000607749;
    CSIP[70].GPOS[0]=	-7398.07;
    CSIP[70].GPOS[1]=	-17640.1;
    CSIP[70].GPOS[2]=	-0.00117201;
    CSIP[71].GPOS[0]=	-7394.84;
    CSIP[71].GPOS[1]=	-13164.9;
    CSIP[71].GPOS[2]=	-6.90706e-06;
    CSIP[72].GPOS[0]=	-7393.47;
    CSIP[72].GPOS[1]=	-8687.95;
    CSIP[72].GPOS[2]=	1.62334e-05;
    CSIP[73].GPOS[0]=	-7397.11;
    CSIP[73].GPOS[1]=	-4213.17;
    CSIP[73].GPOS[2]=	8.62186e-05;
    CSIP[74].GPOS[0]=	-7393.47;
    CSIP[74].GPOS[1]=	39.9441;
    CSIP[74].GPOS[2]=	-0.00024495;
    CSIP[75].GPOS[0]=	-7391.15;
    CSIP[75].GPOS[1]=	4517.26;
    CSIP[75].GPOS[2]=	-0.000441489;
    CSIP[76].GPOS[0]=	-7389.91;
    CSIP[76].GPOS[1]=	8992.49;
    CSIP[76].GPOS[2]=	-0.000291533;
    CSIP[77].GPOS[0]=	-7389.2;
    CSIP[77].GPOS[1]=	13467.2;
    CSIP[77].GPOS[2]=	-1.10801e-05;
    CSIP[78].GPOS[0]=	-9514.89;
    CSIP[78].GPOS[1]=	-13167.7;
    CSIP[78].GPOS[2]=	0.000840672;
    CSIP[79].GPOS[0]=	-9515.81;
    CSIP[79].GPOS[1]=	-8687.35;
    CSIP[79].GPOS[2]=	0.000577452;
    CSIP[80].GPOS[0]=	-9517.41;
    CSIP[80].GPOS[1]=	-4211.12;
    CSIP[80].GPOS[2]=	9.24942e-05;
    CSIP[81].GPOS[0]=	-9518.8;
    CSIP[81].GPOS[1]=	42.2764;
    CSIP[81].GPOS[2]=	-0.000368123;
    CSIP[82].GPOS[0]=	-9514.79;
    CSIP[82].GPOS[1]=	4515.56;
    CSIP[82].GPOS[2]=	-0.000143378;
    CSIP[83].GPOS[0]=	-9511.23;
    CSIP[83].GPOS[1]=	8990.2;
    CSIP[83].GPOS[2]=	0.000421181;
    CSIP[84].GPOS[0]=	-11638.8;
    CSIP[84].GPOS[1]=	-13165.4;
    CSIP[84].GPOS[2]=	0.000659965;
    CSIP[85].GPOS[0]=	-11638.7;
    CSIP[85].GPOS[1]=	-8689.14;
    CSIP[85].GPOS[2]=	0.000493703;
    CSIP[86].GPOS[0]=	-11641.3;
    CSIP[86].GPOS[1]=	-4210.68;
    CSIP[86].GPOS[2]=	0.000362076;
    CSIP[87].GPOS[0]=	-11637.3;
    CSIP[87].GPOS[1]=	257.02;
    CSIP[87].GPOS[2]=	0.00496935;
    CSIP[88].GPOS[0]=	-11638.2;
    CSIP[88].GPOS[1]=	4740.52;
    CSIP[88].GPOS[2]=	-0.000876723;
    CSIP[89].GPOS[0]=	-11634.8;
    CSIP[89].GPOS[1]=	9214.94;
    CSIP[89].GPOS[2]=	0.000313883;
    CSIP[90].GPOS[0]=	-13762.2;
    CSIP[90].GPOS[1]=	-13163.7;
    CSIP[90].GPOS[2]=	9.79203e-05;
    CSIP[91].GPOS[0]=	-13762.8;
    CSIP[91].GPOS[1]=	-8689.54;
    CSIP[91].GPOS[2]=	0.000796186;
    CSIP[92].GPOS[0]=	-13763.6;
    CSIP[92].GPOS[1]=	-4212.59;
    CSIP[92].GPOS[2]=	0.000321249;
    CSIP[93].GPOS[0]=	-13766.4;
    CSIP[93].GPOS[1]=	263.342;
    CSIP[93].GPOS[2]=	-0.000982624;
    CSIP[94].GPOS[0]=	-13759.8;
    CSIP[94].GPOS[1]=	4742.02;
    CSIP[94].GPOS[2]=	-0.000555047;
    CSIP[95].GPOS[0]=	-13758.5;
    CSIP[95].GPOS[1]=	9215.67;
    CSIP[95].GPOS[2]=	7.65291e-05;
    CSIP[96].GPOS[0]=	-15886.3;
    CSIP[96].GPOS[1]=	-8690.38;
    CSIP[96].GPOS[2]=	0.000227137;
    CSIP[97].GPOS[0]=	-15888;
    CSIP[97].GPOS[1]=	-4212.33;
    CSIP[97].GPOS[2]=	8.64849e-05;
    CSIP[98].GPOS[0]=	-15889.9;
    CSIP[98].GPOS[1]=	265.318;
    CSIP[98].GPOS[2]=	-0.00144577;
    CSIP[99].GPOS[0]=	-15886.3;
    CSIP[99].GPOS[1]=	4743.51;
    CSIP[99].GPOS[2]=	-0.00123912;

if(CCDNUM>100){
    CSIP[100].GPOS[0]=	7498.91;
    CSIP[100].GPOS[1]=	-15513.9;
    CSIP[100].GPOS[2]=	-0.000238638;
    CSIP[101].GPOS[0]=	7505.99;
    CSIP[101].GPOS[1]=	13465.7;
    CSIP[101].GPOS[2]=	-3.28791e-05;
    CSIP[102].GPOS[0]=	-11680.1;
    CSIP[102].GPOS[1]=	-15514;
    CSIP[102].GPOS[2]=	0.000560241;
    CSIP[103].GPOS[0]=	-11675;
    CSIP[103].GPOS[1]=	13466.8;
    CSIP[103].GPOS[2]=	2.41631e-05;

}
    for(CID=0;CID<CCDNUM;CID++){
        CSIP[CID].ID=CID;
        CSIP[CID].GPOS_INIT[0]=CSIP[CID].GPOS[0];
        CSIP[CID].GPOS_INIT[1]=CSIP[CID].GPOS[1];
        CSIP[CID].GPOS_INIT[2]=CSIP[CID].GPOS[2];
    }

}
