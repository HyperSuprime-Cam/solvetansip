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
    if(CCDNUM<11){
    F_WCSA_GSIP_SETDEFAULTPOSITIONS_SC();
    }else{
    F_WCSA_GSIP_SETDEFAULTPOSITIONS_HSC();
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
    CSIP[0].GPOS[0]=	1.486108e+04;
    CSIP[0].GPOS[1]=	-6.629289e+03;
    CSIP[0].GPOS[2]=	7.469120e-05;
    CSIP[1].GPOS[0]=	1.486125e+04;
    CSIP[1].GPOS[1]=	-2.150709e+03;
    CSIP[1].GPOS[2]=	-1.665659e-05;
    CSIP[2].GPOS[0]=	1.486161e+04;
    CSIP[2].GPOS[1]=	2.324134e+03;
    CSIP[2].GPOS[2]=	1.735006e-04;
    CSIP[3].GPOS[0]=	1.486090e+04;
    CSIP[3].GPOS[1]=	6.801658e+03;
    CSIP[3].GPOS[2]=	-1.144805e-04;
    CSIP[4].GPOS[0]=	1.273652e+04;
    CSIP[4].GPOS[1]=	-1.110421e+04;
    CSIP[4].GPOS[2]=	1.039587e-04;
    CSIP[5].GPOS[0]=	1.273710e+04;
    CSIP[5].GPOS[1]=	-6.627903e+03;
    CSIP[5].GPOS[2]=	-3.420824e-04;
    CSIP[6].GPOS[0]=	1.273760e+04;
    CSIP[6].GPOS[1]=	-2.151590e+03;
    CSIP[6].GPOS[2]=	-4.923060e-04;
    CSIP[7].GPOS[0]=	1.274074e+04;
    CSIP[7].GPOS[1]=	2.322939e+03;
    CSIP[7].GPOS[2]=	6.835955e-04;
    CSIP[8].GPOS[0]=	1.273840e+04;
    CSIP[8].GPOS[1]=	6.802133e+03;
    CSIP[8].GPOS[2]=	-4.340825e-04;
    CSIP[9].GPOS[0]=	1.273800e+04;
    CSIP[9].GPOS[1]=	1.127768e+04;
    CSIP[9].GPOS[2]=	-7.389672e-04;
    CSIP[10].GPOS[0]=	1.061427e+04;
    CSIP[10].GPOS[1]=	-1.110346e+04;
    CSIP[10].GPOS[2]=	-5.760984e-05;
    CSIP[11].GPOS[0]=	1.061606e+04;
    CSIP[11].GPOS[1]=	-6.629147e+03;
    CSIP[11].GPOS[2]=	7.082408e-04;
    CSIP[12].GPOS[0]=	1.061416e+04;
    CSIP[12].GPOS[1]=	-2.147633e+03;
    CSIP[12].GPOS[2]=	-5.876495e-04;
    CSIP[13].GPOS[0]=	1.061355e+04;
    CSIP[13].GPOS[1]=	2.324776e+03;
    CSIP[13].GPOS[2]=	-4.771578e-04;
    CSIP[14].GPOS[0]=	1.061791e+04;
    CSIP[14].GPOS[1]=	6.800253e+03;
    CSIP[14].GPOS[2]=	5.834373e-04;
    CSIP[15].GPOS[0]=	1.061543e+04;
    CSIP[15].GPOS[1]=	1.127741e+04;
    CSIP[15].GPOS[2]=	-2.777713e-04;
    CSIP[16].GPOS[0]=	8.489367e+03;
    CSIP[16].GPOS[1]=	-1.088157e+04;
    CSIP[16].GPOS[2]=	-3.123849e-04;
    CSIP[17].GPOS[0]=	8.490197e+03;
    CSIP[17].GPOS[1]=	-6.401940e+03;
    CSIP[17].GPOS[2]=	-3.672525e-04;
    CSIP[18].GPOS[0]=	8.491331e+03;
    CSIP[18].GPOS[1]=	-1.927578e+03;
    CSIP[18].GPOS[2]=	-1.974577e-04;
    CSIP[19].GPOS[0]=	8.492639e+03;
    CSIP[19].GPOS[1]=	2.323789e+03;
    CSIP[19].GPOS[2]=	2.371703e-04;
    CSIP[20].GPOS[0]=	8.490856e+03;
    CSIP[20].GPOS[1]=	6.801582e+03;
    CSIP[20].GPOS[2]=	-1.322223e-04;
    CSIP[21].GPOS[0]=	8.495416e+03;
    CSIP[21].GPOS[1]=	1.127463e+04;
    CSIP[21].GPOS[2]=	1.081670e-03;
    CSIP[22].GPOS[0]=	6.365743e+03;
    CSIP[22].GPOS[1]=	-1.535345e+04;
    CSIP[22].GPOS[2]=	-7.541164e-05;
    CSIP[23].GPOS[0]=	6.369727e+03;
    CSIP[23].GPOS[1]=	-1.087872e+04;
    CSIP[23].GPOS[2]=	3.835604e-04;
    CSIP[24].GPOS[0]=	6.370052e+03;
    CSIP[24].GPOS[1]=	-6.402196e+03;
    CSIP[24].GPOS[2]=	5.322733e-04;
    CSIP[25].GPOS[0]=	6.369029e+03;
    CSIP[25].GPOS[1]=	-1.924566e+03;
    CSIP[25].GPOS[2]=	3.251958e-04;
    CSIP[26].GPOS[0]=	6.369543e+03;
    CSIP[26].GPOS[1]=	2.323597e+03;
    CSIP[26].GPOS[2]=	-1.868312e-04;
    CSIP[27].GPOS[0]=	6.370544e+03;
    CSIP[27].GPOS[1]=	6.801207e+03;
    CSIP[27].GPOS[2]=	2.946728e-04;
    CSIP[28].GPOS[0]=	6.373215e+03;
    CSIP[28].GPOS[1]=	1.127595e+04;
    CSIP[28].GPOS[2]=	8.433430e-04;
    CSIP[29].GPOS[0]=	6.368581e+03;
    CSIP[29].GPOS[1]=	1.575383e+04;
    CSIP[29].GPOS[2]=	-1.318643e-04;
    CSIP[30].GPOS[0]=	4.245906e+03;
    CSIP[30].GPOS[1]=	-1.535381e+04;
    CSIP[30].GPOS[2]=	3.511800e-04;
    CSIP[31].GPOS[0]=	4.243724e+03;
    CSIP[31].GPOS[1]=	-1.087982e+04;
    CSIP[31].GPOS[2]=	-4.412036e-04;
    CSIP[32].GPOS[0]=	4.243289e+03;
    CSIP[32].GPOS[1]=	-6.403098e+03;
    CSIP[32].GPOS[2]=	1.390213e-04;
    CSIP[33].GPOS[0]=	4.247594e+03;
    CSIP[33].GPOS[1]=	-1.926098e+03;
    CSIP[33].GPOS[2]=	5.160676e-04;
    CSIP[34].GPOS[0]=	4.246040e+03;
    CSIP[34].GPOS[1]=	2.323651e+03;
    CSIP[34].GPOS[2]=	-1.498324e-04;
    CSIP[35].GPOS[0]=	4.244970e+03;
    CSIP[35].GPOS[1]=	6.801103e+03;
    CSIP[35].GPOS[2]=	-3.111269e-04;
    CSIP[36].GPOS[0]=	4.247171e+03;
    CSIP[36].GPOS[1]=	1.127593e+04;
    CSIP[36].GPOS[2]=	5.129104e-06;
    CSIP[37].GPOS[0]=	4.245836e+03;
    CSIP[37].GPOS[1]=	1.575411e+04;
    CSIP[37].GPOS[2]=	-1.861300e-04;
    CSIP[38].GPOS[0]=	2.122033e+03;
    CSIP[38].GPOS[1]=	-1.535388e+04;
    CSIP[38].GPOS[2]=	-5.070104e-06;
    CSIP[39].GPOS[0]=	2.119635e+03;
    CSIP[39].GPOS[1]=	-1.087739e+04;
    CSIP[39].GPOS[2]=	-4.703346e-04;
    CSIP[40].GPOS[0]=	2.121781e+03;
    CSIP[40].GPOS[1]=	-6.401973e+03;
    CSIP[40].GPOS[2]=	-1.584045e-04;
    CSIP[41].GPOS[0]=	2.123015e+03;
    CSIP[41].GPOS[1]=	-1.923937e+03;
    CSIP[41].GPOS[2]=	1.386608e-04;
    CSIP[42].GPOS[0]=	2.125345e+03;
    CSIP[42].GPOS[1]=	2.324091e+03;
    CSIP[42].GPOS[2]=	2.757609e-04;
    CSIP[43].GPOS[0]=	2.123677e+03;
    CSIP[43].GPOS[1]=	6.801509e+03;
    CSIP[43].GPOS[2]=	4.620884e-04;
    CSIP[44].GPOS[0]=	2.124324e+03;
    CSIP[44].GPOS[1]=	1.127840e+04;
    CSIP[44].GPOS[2]=	2.144049e-04;
    CSIP[45].GPOS[0]=	2.123586e+03;
    CSIP[45].GPOS[1]=	1.575362e+04;
    CSIP[45].GPOS[2]=	1.243761e-04;
    CSIP[46].GPOS[0]=	-1.622000e+00;
    CSIP[46].GPOS[1]=	-1.535440e+04;
    CSIP[46].GPOS[2]=	-1.225479e-04;
    CSIP[47].GPOS[0]=	-2.982000e+00;
    CSIP[47].GPOS[1]=	-1.087812e+04;
    CSIP[47].GPOS[2]=	1.246569e-04;
    CSIP[48].GPOS[0]=	-6.580000e-01;
    CSIP[48].GPOS[1]=	-6.402647e+03;
    CSIP[48].GPOS[2]=	-6.138172e-05;
    CSIP[49].GPOS[0]=	2.800000e-01;
    CSIP[49].GPOS[1]=	-1.925763e+03;
    CSIP[49].GPOS[2]=	1.279247e-04;
    CSIP[50].GPOS[0]=	6.980000e-01;
    CSIP[50].GPOS[1]=	2.325482e+03;
    CSIP[50].GPOS[2]=	8.989901e-04;
    CSIP[51].GPOS[0]=	2.297000e+00;
    CSIP[51].GPOS[1]=	6.800678e+03;
    CSIP[51].GPOS[2]=	9.342271e-04;
    CSIP[52].GPOS[0]=	-1.510000e-01;
    CSIP[52].GPOS[1]=	1.127973e+04;
    CSIP[52].GPOS[2]=	-3.044300e-04;
    CSIP[53].GPOS[0]=	1.231000e+00;
    CSIP[53].GPOS[1]=	1.575302e+04;
    CSIP[53].GPOS[2]=	1.719886e-04;
    CSIP[54].GPOS[0]=	-2.124058e+03;
    CSIP[54].GPOS[1]=	-1.535502e+04;
    CSIP[54].GPOS[2]=	-3.529640e-04;
    CSIP[55].GPOS[0]=	-2.125016e+03;
    CSIP[55].GPOS[1]=	-1.087759e+04;
    CSIP[55].GPOS[2]=	-5.494005e-04;
    CSIP[56].GPOS[0]=	-2.122674e+03;
    CSIP[56].GPOS[1]=	-6.400984e+03;
    CSIP[56].GPOS[2]=	1.976112e-05;
    CSIP[57].GPOS[0]=	-2.123826e+03;
    CSIP[57].GPOS[1]=	-1.926794e+03;
    CSIP[57].GPOS[2]=	-6.041518e-04;
    CSIP[58].GPOS[0]=	-2.121869e+03;
    CSIP[58].GPOS[1]=	2.324642e+03;
    CSIP[58].GPOS[2]=	9.691851e-05;
    CSIP[59].GPOS[0]=	-2.121573e+03;
    CSIP[59].GPOS[1]=	6.802566e+03;
    CSIP[59].GPOS[2]=	-2.873973e-05;
    CSIP[60].GPOS[0]=	-2.119818e+03;
    CSIP[60].GPOS[1]=	1.127865e+04;
    CSIP[60].GPOS[2]=	4.373105e-05;
    CSIP[61].GPOS[0]=	-2.121767e+03;
    CSIP[61].GPOS[1]=	1.575423e+04;
    CSIP[61].GPOS[2]=	1.547509e-04;
    CSIP[62].GPOS[0]=	-4.245144e+03;
    CSIP[62].GPOS[1]=	-1.535447e+04;
    CSIP[62].GPOS[2]=	2.673054e-04;
    CSIP[63].GPOS[0]=	-4.247683e+03;
    CSIP[63].GPOS[1]=	-1.087823e+04;
    CSIP[63].GPOS[2]=	-1.448919e-05;
    CSIP[64].GPOS[0]=	-4.247112e+03;
    CSIP[64].GPOS[1]=	-6.400356e+03;
    CSIP[64].GPOS[2]=	-2.587416e-04;
    CSIP[65].GPOS[0]=	-4.245933e+03;
    CSIP[65].GPOS[1]=	-1.924770e+03;
    CSIP[65].GPOS[2]=	-1.756895e-04;
    CSIP[66].GPOS[0]=	-4.244823e+03;
    CSIP[66].GPOS[1]=	2.325297e+03;
    CSIP[66].GPOS[2]=	2.153425e-05;
    CSIP[67].GPOS[0]=	-4.244552e+03;
    CSIP[67].GPOS[1]=	6.803698e+03;
    CSIP[67].GPOS[2]=	-1.449532e-04;
    CSIP[68].GPOS[0]=	-4.244477e+03;
    CSIP[68].GPOS[1]=	1.127726e+04;
    CSIP[68].GPOS[2]=	1.572254e-04;
    CSIP[69].GPOS[0]=	-4.243977e+03;
    CSIP[69].GPOS[1]=	1.575440e+04;
    CSIP[69].GPOS[2]=	-3.912938e-04;
    CSIP[70].GPOS[0]=	-6.373222e+03;
    CSIP[70].GPOS[1]=	-1.535297e+04;
    CSIP[70].GPOS[2]=	-1.082959e-03;
    CSIP[71].GPOS[0]=	-6.369967e+03;
    CSIP[71].GPOS[1]=	-1.087790e+04;
    CSIP[71].GPOS[2]=	6.438946e-06;
    CSIP[72].GPOS[0]=	-6.368159e+03;
    CSIP[72].GPOS[1]=	-6.400994e+03;
    CSIP[72].GPOS[2]=	4.045629e-05;
    CSIP[73].GPOS[0]=	-6.371083e+03;
    CSIP[73].GPOS[1]=	-1.926520e+03;
    CSIP[73].GPOS[2]=	1.736262e-04;
    CSIP[74].GPOS[0]=	-6.367540e+03;
    CSIP[74].GPOS[1]=	2.326123e+03;
    CSIP[74].GPOS[2]=	1.490976e-04;
    CSIP[75].GPOS[0]=	-6.368010e+03;
    CSIP[75].GPOS[1]=	6.803557e+03;
    CSIP[75].GPOS[2]=	3.881749e-05;
    CSIP[76].GPOS[0]=	-6.368879e+03;
    CSIP[76].GPOS[1]=	1.127999e+04;
    CSIP[76].GPOS[2]=	-4.336736e-04;
    CSIP[77].GPOS[0]=	-6.367362e+03;
    CSIP[77].GPOS[1]=	1.575472e+04;
    CSIP[77].GPOS[2]=	4.134590e-05;
    CSIP[78].GPOS[0]=	-8.490694e+03;
    CSIP[78].GPOS[1]=	-1.088012e+04;
    CSIP[78].GPOS[2]=	6.998628e-04;
    CSIP[79].GPOS[0]=	-8.491390e+03;
    CSIP[79].GPOS[1]=	-6.399940e+03;
    CSIP[79].GPOS[2]=	3.412708e-04;
    CSIP[80].GPOS[0]=	-8.491610e+03;
    CSIP[80].GPOS[1]=	-1.924081e+03;
    CSIP[80].GPOS[2]=	-1.098505e-04;
    CSIP[81].GPOS[0]=	-8.492593e+03;
    CSIP[81].GPOS[1]=	2.328357e+03;
    CSIP[81].GPOS[2]=	-4.349314e-06;
    CSIP[82].GPOS[0]=	-8.491897e+03;
    CSIP[82].GPOS[1]=	6.801949e+03;
    CSIP[82].GPOS[2]=	3.251606e-04;
    CSIP[83].GPOS[0]=	-8.490914e+03;
    CSIP[83].GPOS[1]=	1.127815e+04;
    CSIP[83].GPOS[2]=	1.356535e-04;
    CSIP[84].GPOS[0]=	-1.061441e+04;
    CSIP[84].GPOS[1]=	-1.087758e+04;
    CSIP[84].GPOS[2]=	6.704231e-04;
    CSIP[85].GPOS[0]=	-1.061465e+04;
    CSIP[85].GPOS[1]=	-6.401008e+03;
    CSIP[85].GPOS[2]=	2.038970e-04;
    CSIP[86].GPOS[0]=	-1.061567e+04;
    CSIP[86].GPOS[1]=	-1.922497e+03;
    CSIP[86].GPOS[2]=	-2.859758e-05;
    CSIP[87].GPOS[0]=	-1.061799e+04;
    CSIP[87].GPOS[1]=	2.549734e+03;
    CSIP[87].GPOS[2]=	-6.376717e-04;
    CSIP[88].GPOS[0]=	-1.061610e+04;
    CSIP[88].GPOS[1]=	7.028126e+03;
    CSIP[88].GPOS[2]=	-4.552432e-04;
    CSIP[89].GPOS[0]=	-1.061450e+04;
    CSIP[89].GPOS[1]=	1.150376e+04;
    CSIP[89].GPOS[2]=	-2.390071e-04;
    CSIP[90].GPOS[0]=	-1.273789e+04;
    CSIP[90].GPOS[1]=	-1.087550e+04;
    CSIP[90].GPOS[2]=	7.863410e-05;
    CSIP[91].GPOS[0]=	-1.273851e+04;
    CSIP[91].GPOS[1]=	-6.400981e+03;
    CSIP[91].GPOS[2]=	5.826972e-04;
    CSIP[92].GPOS[0]=	-1.273775e+04;
    CSIP[92].GPOS[1]=	-1.923333e+03;
    CSIP[92].GPOS[2]=	1.706390e-05;
    CSIP[93].GPOS[0]=	-1.273982e+04;
    CSIP[93].GPOS[1]=	2.551599e+03;
    CSIP[93].GPOS[2]=	-4.476174e-04;
    CSIP[94].GPOS[0]=	-1.273714e+04;
    CSIP[94].GPOS[1]=	7.029697e+03;
    CSIP[94].GPOS[2]=	-1.008064e-04;
    CSIP[95].GPOS[0]=	-1.273672e+04;
    CSIP[95].GPOS[1]=	1.150426e+04;
    CSIP[95].GPOS[2]=	-1.063618e-04;
    CSIP[96].GPOS[0]=	-1.486160e+04;
    CSIP[96].GPOS[1]=	-6.401364e+03;
    CSIP[96].GPOS[2]=	2.716953e-05;
    CSIP[97].GPOS[0]=	-1.486173e+04;
    CSIP[97].GPOS[1]=	-1.923300e+03;
    CSIP[97].GPOS[2]=	2.226470e-05;
    CSIP[98].GPOS[0]=	-1.486299e+04;
    CSIP[98].GPOS[1]=	2.552967e+03;
    CSIP[98].GPOS[2]=	-7.377701e-04;
    CSIP[99].GPOS[0]=	-1.486274e+04;
    CSIP[99].GPOS[1]=	7.030615e+03;
    CSIP[99].GPOS[2]=	-7.679112e-04;
    CSIP[100].GPOS[0]=	9.588256e+03;
    CSIP[100].GPOS[1]=	-1.428916e+04;
    CSIP[100].GPOS[2]=	-1.965054e-04;
    CSIP[101].GPOS[0]=	9.591732e+03;
    CSIP[101].GPOS[1]=	1.469027e+04;
    CSIP[101].GPOS[2]=	-1.154499e-05;
    CSIP[102].GPOS[0]=	-9.591840e+03;
    CSIP[102].GPOS[1]=	-1.429021e+04;
    CSIP[102].GPOS[2]=	5.178032e-04;
    CSIP[103].GPOS[0]=	-9.588180e+03;
    CSIP[103].GPOS[1]=	1.468929e+04;
    CSIP[103].GPOS[2]=	3.193213e-04;
    for(CID=0;CID<CCDNUM;CID++){
        CSIP[CID].ID=CID;
        CSIP[CID].GPOS_INIT[0]=CSIP[CID].GPOS[0];
        CSIP[CID].GPOS_INIT[1]=CSIP[CID].GPOS[1];
        CSIP[CID].GPOS_INIT[2]=CSIP[CID].GPOS[2];
    }

}
