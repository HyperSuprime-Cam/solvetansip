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
/*            delete [] CSIP[CID].SIP_AB[i] ;
            delete [] CSIP[CID].SIP_ABP[i];
            delete [] CSIP[CID].Coef[i]   ;
            delete [] CSIP[CID].PCoef[i]  ;
            delete [] CSIP[CID].LCoef[i]  ;*/
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
//1
    delete [] CSIP;
}
void CL_GSIP::F_WCSA_GSIP_SET0(){
    sprintf(CRPIXMODE,"AUTO");
    sprintf(   OAMODE,"MIN");
    CCDPOSMODE =0;
//    CCDNUM     =0;
//    ALLREFNUM  =0;
//    ALLFITNUM  =0;
//    SIP_ORDER  =0;
//    SIP_P_ORDER=0;
//    SIP_L_ORDER=0;
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
        CSIP[CID].ID         =0;
        CSIP[CID].FITNUM     =0;
        CSIP[CID].REFNUM     =0;
        CSIP[CID].SIP_ORDER  =0;
        CSIP[CID].SIP_P_ORDER=0;
        CSIP[CID].SIP_L_ORDER=0;
        CSIP[CID].GPOS[0]    =0;
        CSIP[CID].GPOS[1]    =0;
        CSIP[CID].GPOS[2]    =0;
        CSIP[CID].MAXDRAD    =0;
        CSIP[CID].MAXFRAD    =0;
        CSIP[CID].OAVAL[0]   =0;
        CSIP[CID].OAVAL[1]   =0;
        CSIP[CID].OAPIX[0]   =0;
        CSIP[CID].OAPIX[1]   =0;
        CSIP[CID].CRVAL[0]   =0;
        CSIP[CID].CRVAL[1]   =0;
        CSIP[CID].CRPIX[0]   =0;
        CSIP[CID].CRPIX[1]   =0;
        CSIP[CID].CD[0][0]   =0;
        CSIP[CID].CD[0][1]   =0;
        CSIP[CID].CD[1][0]   =0;
        CSIP[CID].CD[1][1]   =0;
        CSIP[CID].InvCD[0][0]=0;
        CSIP[CID].InvCD[0][1]=0;
        CSIP[CID].InvCD[1][0]=0;
        CSIP[CID].InvCD[1][1]=0;
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
        CSIP[CID].ANGLE      =0;
        CSIP[CID].POSID[0]   =0;
        CSIP[CID].POSID[1]   =0;
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

    XX[0]=PIXEL[0]-CRPIX[0];
    XX[1]=PIXEL[1]-CRPIX[1];
    YY[0]=F_CALCVALUE(SIP_ORDER,CSIP[CID].SIP_AB[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(SIP_ORDER,CSIP[CID].SIP_AB[1],XX)+XX[1];
    XX[0]=CD[0][0]*YY[0]+CD[0][1]*YY[1];
    XX[1]=CD[1][0]*YY[0]+CD[1][1]*YY[1];
    F_InvPROJECTION(XX,RADEC,CRVAL);
}
void CL_GSIP::F_WCSA_GSIP_XRADECtoXLOCAL(int CID, double *RADEC,double *PIXEL){
    double XX[2],YY[2];

    F_PROJECTION(RADEC,YY,CRVAL);
    XX[0]=InvCD[0][0]*YY[0]+InvCD[0][1]*YY[1];
    XX[1]=InvCD[1][0]*YY[0]+InvCD[1][1]*YY[1];
    YY[0]=F_CALCVALUE(SIP_P_ORDER,CSIP[CID].SIP_ABP[0],XX)+XX[0];
    YY[1]=F_CALCVALUE(SIP_P_ORDER,CSIP[CID].SIP_ABP[1],XX)+XX[1];
    PIXEL[0]=YY[0]+CRPIX[0];
    PIXEL[1]=YY[1]+CRPIX[1];
}
void CL_GSIP::F_WCSA_GSIP_XCRPIXtoXRADEC(int CID, double *CRPIX,double *RADEC){
    double XX[2],YY[2];

    YY[0]=F_CALCVALUE(SIP_ORDER,CSIP[CID].SIP_AB[0],CRPIX)+CRPIX[0];
    YY[1]=F_CALCVALUE(SIP_ORDER,CSIP[CID].SIP_AB[1],CRPIX)+CRPIX[1];
    XX[0]=CD[0][0]*YY[0]+CD[0][1]*YY[1];
    XX[1]=CD[1][0]*YY[0]+CD[1][1]*YY[1];
    F_InvPROJECTION(XX,RADEC,CRVAL);
}
void CL_GSIP::F_WCSA_GSIP_XRADECtoXCRPIX(int CID, double *RADEC,double *CRPIX){
    double XX[2],YY[2];

    F_PROJECTION(RADEC,YY,CRVAL);
    XX[0]=InvCD[0][0]*YY[0]+InvCD[0][1]*YY[1];
    XX[1]=InvCD[1][0]*YY[0]+InvCD[1][1]*YY[1];
    CRPIX[0]=F_CALCVALUE(SIP_P_ORDER,CSIP[CID].SIP_ABP[0],XX)+XX[0];
    CRPIX[1]=F_CALCVALUE(SIP_P_ORDER,CSIP[CID].SIP_ABP[1],XX)+XX[1];
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
    CRSMA[5]=(1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0];

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
    cout << "CRPIX(pix)   : " << CRPIX[0] << " , " << CRPIX[1]<< endl;
    cout << "CRVAL(deg)   : " << CRVAL[0] << " , " << CRVAL[1]<< endl;
    cout << "OAPIX(pix)   : " << OAPIX[0] << " , " << OAPIX[1]<< endl;
    cout << "OAVAL(deg)   : " << OAVAL[0] << " , " << OAVAL[1]<< endl;
    cout.unsetf(ios::fixed);
    cout << "CD_1_1       : " << CD[0][0] << endl;
    cout << "CD_1_2       : " << CD[0][1] << endl;
    cout << "CD_2_1       : " << CD[1][0] << endl;
    cout << "CD_2_2       : " << CD[1][1] << endl;
    cout << "InvCD_1_1    : " << InvCD[0][0] << endl;
    cout << "InvCD_1_2    : " << InvCD[0][1] << endl;
    cout << "InvCD_2_1    : " << InvCD[1][0] << endl;
    cout << "InvCD_2_2    : " << InvCD[1][1] << endl;
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
    CSIP[CID].ID=0;
    CSIP[CID].FITNUM=0;
    CSIP[CID].REFNUM=0;
    CSIP[CID].GPOS[0] =CSIP[CID].GPOS[1] =CSIP[CID].GPOS[2]=0;
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

    if(CCDNUM<11){
    F_WCSA_GSIP_SETDEFAULTPOSITIONS_SCfromPAF();
    }else{
    F_WCSA_GSIP_SETDEFAULTPOSITIONS_HSCfromPAF();
    }

    
}
void CL_GSIP::F_WCSA_GSIP_SETDEFAULTPOSITIONS_SC(){
    int CID;
    for(CID=0;CID<10;CID++)
    CSIP[CID].ID=CID;
/*    CSIP[  0].GPOS[0]=   4243.45;
    CSIP[  0].GPOS[1]=   1951.42;
    CSIP[  0].GPOS[2]=9.42553e-05;
    CSIP[  1].GPOS[0]=   2121.68;
    CSIP[  1].GPOS[1]=   1951.15;
    CSIP[  1].GPOS[2]=0.000213211;
    CSIP[  2].GPOS[0]=- 0.632341;
    CSIP[  2].GPOS[1]=   1952.32;
    CSIP[  2].GPOS[2]=0.000308735;
    CSIP[  3].GPOS[0]=   4244.21;
    CSIP[  3].GPOS[1]=  -2300.46;
    CSIP[  3].GPOS[2]=0.000100736;
    CSIP[  4].GPOS[0]=   2126.83;
    CSIP[  4].GPOS[1]=  -2299.38;
    CSIP[  4].GPOS[2]=0.000100736;
    CSIP[  5].GPOS[0]=  -2.09345;
    CSIP[  5].GPOS[1]=  -2305.18;
    CSIP[  5].GPOS[2]=-6.8067e-05;
    CSIP[  6].GPOS[0]=  -4246.74;
    CSIP[  6].GPOS[1]=   1950.66;
    CSIP[  6].GPOS[2]=0.000425587;
    CSIP[  7].GPOS[0]=  -2123.46;
    CSIP[  7].GPOS[1]=   1952.01;
    CSIP[  7].GPOS[2]=0.000272656;
    CSIP[  8].GPOS[0]=  -4244.22;
    CSIP[  8].GPOS[1]=  -2299.95;
    CSIP[  8].GPOS[2]=-2.88434e-05;
    CSIP[  9].GPOS[0]=  -2122.81;
    CSIP[  9].GPOS[1]=  -2299.69;
    CSIP[  9].GPOS[2]=0.00026042;*/
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
}
void CL_GSIP::F_WCSA_GSIP_SETDEFAULTPOSITIONS_HSC(){
    int CID;
    for(CID=0;CID<CCDNUM;CID++)
    CSIP[CID].ID=CID;
    CSIP[  0].GPOS[0]=- 9514.700;
    CSIP[  0].GPOS[1]=    37.350;
    CSIP[  0].GPOS[2]=  0.000000;
    CSIP[  1].GPOS[0]=  7466.700;
    CSIP[  1].GPOS[1]=- 4133.350;
    CSIP[  1].GPOS[2]=  0.000000;
    CSIP[  2].GPOS[0]=- 7392.000;
    CSIP[  2].GPOS[1]=    37.350;
    CSIP[  2].GPOS[2]=  0.000000;
    CSIP[  3].GPOS[0]=  5344.000;
    CSIP[  3].GPOS[1]=- 4133.350;
    CSIP[  3].GPOS[2]=  0.000000;
    CSIP[  4].GPOS[0]=- 5269.300;
    CSIP[  4].GPOS[1]=    37.350;
    CSIP[  4].GPOS[2]=  0.000000;
    CSIP[  5].GPOS[0]=  3221.300;
    CSIP[  5].GPOS[1]=- 4133.350;
    CSIP[  5].GPOS[2]=  0.000000;
    CSIP[  6].GPOS[0]=- 3146.700;
    CSIP[  6].GPOS[1]=    37.350;
    CSIP[  6].GPOS[2]=  0.000000;
    CSIP[  7].GPOS[0]=  1098.700;
    CSIP[  7].GPOS[1]=- 4133.350;
    CSIP[  7].GPOS[2]=  0.000000;
    CSIP[  8].GPOS[0]=- 1024.000;
    CSIP[  8].GPOS[1]=    37.350;
    CSIP[  8].GPOS[2]=  0.000000;
    CSIP[  9].GPOS[0]=- 1024.000;
    CSIP[  9].GPOS[1]=- 4133.350;
    CSIP[  9].GPOS[2]=  0.000000;
    CSIP[ 10].GPOS[0]=  1098.700;
    CSIP[ 10].GPOS[1]=    37.350;
    CSIP[ 10].GPOS[2]=  0.000000;
    CSIP[ 11].GPOS[0]=- 3146.700;
    CSIP[ 11].GPOS[1]=- 4133.350;
    CSIP[ 11].GPOS[2]=  0.000000;
    CSIP[ 12].GPOS[0]=  3221.300;
    CSIP[ 12].GPOS[1]=    37.350;
    CSIP[ 12].GPOS[2]=  0.000000;
    CSIP[ 13].GPOS[0]=- 5269.300;
    CSIP[ 13].GPOS[1]=- 4133.350;
    CSIP[ 13].GPOS[2]=  0.000000;
    CSIP[ 14].GPOS[0]=  5344.000;
    CSIP[ 14].GPOS[1]=    37.350;
    CSIP[ 14].GPOS[2]=  0.000000;
    CSIP[ 15].GPOS[0]=- 7392.000;
    CSIP[ 15].GPOS[1]=- 4133.350;
    CSIP[ 15].GPOS[2]=  0.000000;
    CSIP[ 16].GPOS[0]=  7466.700;
    CSIP[ 16].GPOS[1]=    37.350;
    CSIP[ 16].GPOS[2]=  0.000000;
    CSIP[ 17].GPOS[0]=- 9514.700;
    CSIP[ 17].GPOS[1]=- 4133.350;
    CSIP[ 17].GPOS[2]=  0.000000;
    CSIP[ 18].GPOS[0]=  9589.300;
    CSIP[ 18].GPOS[1]=    37.350;
    CSIP[ 18].GPOS[2]=  0.000000;
    CSIP[ 19].GPOS[0]=-11637.300;
    CSIP[ 19].GPOS[1]=- 4133.350;
    CSIP[ 19].GPOS[2]=  0.000000;
    CSIP[ 20].GPOS[0]= 11712.000;
    CSIP[ 20].GPOS[1]=    37.350;
    CSIP[ 20].GPOS[2]=  0.000000;
    CSIP[ 21].GPOS[0]=-13760.000;
    CSIP[ 21].GPOS[1]=- 4133.350;
    CSIP[ 21].GPOS[2]=  0.000000;
    CSIP[ 22].GPOS[0]= 13834.700;
    CSIP[ 22].GPOS[1]=    37.350;
    CSIP[ 22].GPOS[2]=  0.000000;
    CSIP[ 23].GPOS[0]=-15882.700;
    CSIP[ 23].GPOS[1]=- 4133.350;
    CSIP[ 23].GPOS[2]=  0.000000;
    CSIP[ 24].GPOS[0]=- 9514.700;
    CSIP[ 24].GPOS[1]=  4512.350;
    CSIP[ 24].GPOS[2]=  0.000000;
    CSIP[ 25].GPOS[0]=  7466.700;
    CSIP[ 25].GPOS[1]=- 8608.350;
    CSIP[ 25].GPOS[2]=  0.000000;
    CSIP[ 26].GPOS[0]=- 7392.000;
    CSIP[ 26].GPOS[1]=  4512.350;
    CSIP[ 26].GPOS[2]=  0.000000;
    CSIP[ 27].GPOS[0]=  5344.000;
    CSIP[ 27].GPOS[1]=- 8608.350;
    CSIP[ 27].GPOS[2]=  0.000000;
    CSIP[ 28].GPOS[0]=- 5269.300;
    CSIP[ 28].GPOS[1]=  4512.350;
    CSIP[ 28].GPOS[2]=  0.000000;
    CSIP[ 29].GPOS[0]=  3221.300;
    CSIP[ 29].GPOS[1]=- 8608.350;
    CSIP[ 29].GPOS[2]=  0.000000;
    CSIP[ 30].GPOS[0]=- 3146.700;
    CSIP[ 30].GPOS[1]=  4512.350;
    CSIP[ 30].GPOS[2]=  0.000000;
    CSIP[ 31].GPOS[0]=  1098.700;
    CSIP[ 31].GPOS[1]=- 8608.350;
    CSIP[ 31].GPOS[2]=  0.000000;
    CSIP[ 32].GPOS[0]=- 1024.000;
    CSIP[ 32].GPOS[1]=  4512.350;
    CSIP[ 32].GPOS[2]=  0.000000;
    CSIP[ 33].GPOS[0]=- 1024.000;
    CSIP[ 33].GPOS[1]=- 8608.350;
    CSIP[ 33].GPOS[2]=  0.000000;
    CSIP[ 34].GPOS[0]=  1098.700;
    CSIP[ 34].GPOS[1]=  4512.350;
    CSIP[ 34].GPOS[2]=  0.000000;
    CSIP[ 35].GPOS[0]=- 3146.700;
    CSIP[ 35].GPOS[1]=- 8608.350;
    CSIP[ 35].GPOS[2]=  0.000000;
    CSIP[ 36].GPOS[0]=  3221.300;
    CSIP[ 36].GPOS[1]=  4512.350;
    CSIP[ 36].GPOS[2]=  0.000000;
    CSIP[ 37].GPOS[0]=- 5269.300;
    CSIP[ 37].GPOS[1]=- 8608.350;
    CSIP[ 37].GPOS[2]=  0.000000;
    CSIP[ 38].GPOS[0]=  5344.000;
    CSIP[ 38].GPOS[1]=  4512.350;
    CSIP[ 38].GPOS[2]=  0.000000;
    CSIP[ 39].GPOS[0]=- 7392.000;
    CSIP[ 39].GPOS[1]=- 8608.350;
    CSIP[ 39].GPOS[2]=  0.000000;
    CSIP[ 40].GPOS[0]=  7466.700;
    CSIP[ 40].GPOS[1]=  4512.350;
    CSIP[ 40].GPOS[2]=  0.000000;
    CSIP[ 41].GPOS[0]=- 9514.700;
    CSIP[ 41].GPOS[1]=- 8608.350;
    CSIP[ 41].GPOS[2]=  0.000000;
    CSIP[ 42].GPOS[0]=  9589.300;
    CSIP[ 42].GPOS[1]=  4512.350;
    CSIP[ 42].GPOS[2]=  0.000000;
    CSIP[ 43].GPOS[0]=-11637.300;
    CSIP[ 43].GPOS[1]=- 8608.350;
    CSIP[ 43].GPOS[2]=  0.000000;
    CSIP[ 44].GPOS[0]= 11712.000;
    CSIP[ 44].GPOS[1]=  4512.350;
    CSIP[ 44].GPOS[2]=  0.000000;
    CSIP[ 45].GPOS[0]=-13760.000;
    CSIP[ 45].GPOS[1]=- 8608.350;
    CSIP[ 45].GPOS[2]=  0.000000;
    CSIP[ 46].GPOS[0]= 13834.700;
    CSIP[ 46].GPOS[1]=  4512.350;
    CSIP[ 46].GPOS[2]=  0.000000;
    CSIP[ 47].GPOS[0]=-15882.700;
    CSIP[ 47].GPOS[1]=- 8608.350;
    CSIP[ 47].GPOS[2]=  0.000000;
    CSIP[ 48].GPOS[0]=- 9514.700;
    CSIP[ 48].GPOS[1]=  8987.350;
    CSIP[ 48].GPOS[2]=  0.000000;
    CSIP[ 49].GPOS[0]=  7466.700;
    CSIP[ 49].GPOS[1]=-13083.350;
    CSIP[ 49].GPOS[2]=  0.000000;
    CSIP[ 50].GPOS[0]=- 7392.000;
    CSIP[ 50].GPOS[1]=  8987.350;
    CSIP[ 50].GPOS[2]=  0.000000;
    CSIP[ 51].GPOS[0]=  5344.000;
    CSIP[ 51].GPOS[1]=-13083.350;
    CSIP[ 51].GPOS[2]=  0.000000;
    CSIP[ 52].GPOS[0]=- 5269.300;
    CSIP[ 52].GPOS[1]=  8987.350;
    CSIP[ 52].GPOS[2]=  0.000000;
    CSIP[ 53].GPOS[0]=  3221.300;
    CSIP[ 53].GPOS[1]=-13083.350;
    CSIP[ 53].GPOS[2]=  0.000000;
    CSIP[ 54].GPOS[0]=- 3146.700;
    CSIP[ 54].GPOS[1]=  8987.350;
    CSIP[ 54].GPOS[2]=  0.000000;
    CSIP[ 55].GPOS[0]=  1098.700;
    CSIP[ 55].GPOS[1]=-13083.350;
    CSIP[ 55].GPOS[2]=  0.000000;
    CSIP[ 56].GPOS[0]=- 1024.000;
    CSIP[ 56].GPOS[1]=  8987.350;
    CSIP[ 56].GPOS[2]=  0.000000;
    CSIP[ 57].GPOS[0]=- 1024.000;
    CSIP[ 57].GPOS[1]=-13083.350;
    CSIP[ 57].GPOS[2]=  0.000000;
    CSIP[ 58].GPOS[0]=  1098.700;
    CSIP[ 58].GPOS[1]=  8987.350;
    CSIP[ 58].GPOS[2]=  0.000000;
    CSIP[ 59].GPOS[0]=- 3146.700;
    CSIP[ 59].GPOS[1]=-13083.350;
    CSIP[ 59].GPOS[2]=  0.000000;
    CSIP[ 60].GPOS[0]=  3221.300;
    CSIP[ 60].GPOS[1]=  8987.350;
    CSIP[ 60].GPOS[2]=  0.000000;
    CSIP[ 61].GPOS[0]=- 5269.300;
    CSIP[ 61].GPOS[1]=-13083.350;
    CSIP[ 61].GPOS[2]=  0.000000;
    CSIP[ 62].GPOS[0]=  5344.000;
    CSIP[ 62].GPOS[1]=  8987.350;
    CSIP[ 62].GPOS[2]=  0.000000;
    CSIP[ 63].GPOS[0]=- 7392.000;
    CSIP[ 63].GPOS[1]=-13083.350;
    CSIP[ 63].GPOS[2]=  0.000000;
    CSIP[ 64].GPOS[0]=  7466.700;
    CSIP[ 64].GPOS[1]=  8987.350;
    CSIP[ 64].GPOS[2]=  0.000000;
    CSIP[ 65].GPOS[0]=- 9514.700;
    CSIP[ 65].GPOS[1]=-13083.350;
    CSIP[ 65].GPOS[2]=  0.000000;
    CSIP[ 66].GPOS[0]=  9589.300;
    CSIP[ 66].GPOS[1]=  8987.350;
    CSIP[ 66].GPOS[2]=  0.000000;
    CSIP[ 67].GPOS[0]=-11637.300;
    CSIP[ 67].GPOS[1]=-13083.350;
    CSIP[ 67].GPOS[2]=  0.000000;
    CSIP[ 68].GPOS[0]= 11712.000;
    CSIP[ 68].GPOS[1]=  8987.350;
    CSIP[ 68].GPOS[2]=  0.000000;
    CSIP[ 69].GPOS[0]=-13760.000;
    CSIP[ 69].GPOS[1]=-13083.350;
    CSIP[ 69].GPOS[2]=  0.000000;
    CSIP[ 70].GPOS[0]=- 7392.000;
    CSIP[ 70].GPOS[1]= 13462.350;
    CSIP[ 70].GPOS[2]=  0.000000;
    CSIP[ 71].GPOS[0]=  5344.000;
    CSIP[ 71].GPOS[1]=-17558.350;
    CSIP[ 71].GPOS[2]=  0.000000;
    CSIP[ 72].GPOS[0]=- 5269.300;
    CSIP[ 72].GPOS[1]= 13462.350;
    CSIP[ 72].GPOS[2]=  0.000000;
    CSIP[ 73].GPOS[0]=  3221.300;
    CSIP[ 73].GPOS[1]=-17558.350;
    CSIP[ 73].GPOS[2]=  0.000000;
    CSIP[ 74].GPOS[0]=- 3146.700;
    CSIP[ 74].GPOS[1]= 13462.350;
    CSIP[ 74].GPOS[2]=  0.000000;
    CSIP[ 75].GPOS[0]=  1098.700;
    CSIP[ 75].GPOS[1]=-17558.350;
    CSIP[ 75].GPOS[2]=  0.000000;
    CSIP[ 76].GPOS[0]=- 1024.000;
    CSIP[ 76].GPOS[1]= 13462.350;
    CSIP[ 76].GPOS[2]=  0.000000;
    CSIP[ 77].GPOS[0]=- 1024.000;
    CSIP[ 77].GPOS[1]=-17558.350;
    CSIP[ 77].GPOS[2]=  0.000000;
    CSIP[ 78].GPOS[0]=  1098.700;
    CSIP[ 78].GPOS[1]= 13462.350;
    CSIP[ 78].GPOS[2]=  0.000000;
    CSIP[ 79].GPOS[0]=- 3146.700;
    CSIP[ 79].GPOS[1]=-17558.350;
    CSIP[ 79].GPOS[2]=  0.000000;
    CSIP[ 80].GPOS[0]=  3221.300;
    CSIP[ 80].GPOS[1]= 13462.350;
    CSIP[ 80].GPOS[2]=  0.000000;
    CSIP[ 81].GPOS[0]=- 5269.300;
    CSIP[ 81].GPOS[1]=-17558.350;
    CSIP[ 81].GPOS[2]=  0.000000;
    CSIP[ 82].GPOS[0]=  5344.000;
    CSIP[ 82].GPOS[1]= 13462.350;
    CSIP[ 82].GPOS[2]=  0.000000;
    CSIP[ 83].GPOS[0]=- 7392.000;
    CSIP[ 83].GPOS[1]=-17558.350;
    CSIP[ 83].GPOS[2]=  0.000000;
    CSIP[ 84].GPOS[0]=  9589.300;
    CSIP[ 84].GPOS[1]=- 4437.650;
    CSIP[ 84].GPOS[2]=  0.000000;
    CSIP[ 85].GPOS[0]=-11637.300;
    CSIP[ 85].GPOS[1]=   341.650;
    CSIP[ 85].GPOS[2]=  0.000000;
    CSIP[ 86].GPOS[0]= 11712.000;
    CSIP[ 86].GPOS[1]=- 4437.650;
    CSIP[ 86].GPOS[2]=  0.000000;
    CSIP[ 87].GPOS[0]=-13760.000;
    CSIP[ 87].GPOS[1]=   341.650;
    CSIP[ 87].GPOS[2]=  0.000000;
    CSIP[ 88].GPOS[0]= 13834.700;
    CSIP[ 88].GPOS[1]=- 4437.650;
    CSIP[ 88].GPOS[2]=  0.000000;
    CSIP[ 89].GPOS[0]=-15882.700;
    CSIP[ 89].GPOS[1]=   341.650;
    CSIP[ 89].GPOS[2]=  0.000000;
    CSIP[ 90].GPOS[0]=  9589.300;
    CSIP[ 90].GPOS[1]=- 8912.650;
    CSIP[ 90].GPOS[2]=  0.000000;
    CSIP[ 91].GPOS[0]=-11637.300;
    CSIP[ 91].GPOS[1]=  4816.650;
    CSIP[ 91].GPOS[2]=  0.000000;
    CSIP[ 92].GPOS[0]= 11712.000;
    CSIP[ 92].GPOS[1]=- 8912.650;
    CSIP[ 92].GPOS[2]=  0.000000;
    CSIP[ 93].GPOS[0]=-13760.000;
    CSIP[ 93].GPOS[1]=  4816.650;
    CSIP[ 93].GPOS[2]=  0.000000;
    CSIP[ 94].GPOS[0]= 13834.700;
    CSIP[ 94].GPOS[1]=- 8912.650;
    CSIP[ 94].GPOS[2]=  0.000000;
    CSIP[ 95].GPOS[0]=-15882.700;
    CSIP[ 95].GPOS[1]=  4816.650;
    CSIP[ 95].GPOS[2]=  0.000000;
    CSIP[ 96].GPOS[0]=  9589.300;
    CSIP[ 96].GPOS[1]=-13387.650;
    CSIP[ 96].GPOS[2]=  0.000000;
    CSIP[ 97].GPOS[0]=-11637.300;
    CSIP[ 97].GPOS[1]=  9291.650;
    CSIP[ 97].GPOS[2]=  0.000000;
    CSIP[ 98].GPOS[0]= 11712.000;
    CSIP[ 98].GPOS[1]=-13387.650;
    CSIP[ 98].GPOS[2]=  0.000000;
    CSIP[ 99].GPOS[0]=-13760.000;
    CSIP[ 99].GPOS[1]=  9291.650;
    CSIP[ 99].GPOS[2]=  0.000000;

    CSIP[100].GPOS[0]=- 7467.700;
    CSIP[100].GPOS[1]= 13543.650;
    CSIP[100].GPOS[2]=  0.785398;
    CSIP[101].GPOS[0]= 11643.000;
    CSIP[101].GPOS[1]= 13543.650;
    CSIP[101].GPOS[2]=  0.785398;
    CSIP[102].GPOS[0]= 11643.000;
    CSIP[102].GPOS[1]=-15341.350;
    CSIP[102].GPOS[2]=  0.785398;
    CSIP[103].GPOS[0]=- 7467.700;
    CSIP[103].GPOS[1]=-15341.350;
    CSIP[103].GPOS[2]=  0.785398;
}
void CL_GSIP::F_WCSA_GSIP_SETDEFAULTPOSITIONS_SCfromPAF(){
    int CID;
    for(CID=0;CID<10;CID++)
    CSIP[CID].ID=CID;
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
/*
    CSIP[  0].GPOS[0]=     4243.45;
    CSIP[  0].GPOS[1]=     1951.42;
    CSIP[  0].GPOS[2]= 9.42553e-05;
    CSIP[  1].GPOS[0]=     2121.68;
    CSIP[  1].GPOS[1]=     1951.15;
    CSIP[  1].GPOS[2]= 0.000213211;
    CSIP[  2].GPOS[0]=   -0.632341;
    CSIP[  2].GPOS[1]=     1952.32;
    CSIP[  2].GPOS[2]= 0.000308735;
    CSIP[  3].GPOS[0]=     4244.21;
    CSIP[  3].GPOS[1]=    -2300.46;
    CSIP[  3].GPOS[2]= 0.000100736;
    CSIP[  4].GPOS[0]=     2126.83;
    CSIP[  4].GPOS[1]=    -2299.38;
    CSIP[  4].GPOS[2]= 0.000100736;
    CSIP[  5].GPOS[0]=    -2.09345;
    CSIP[  5].GPOS[1]=    -2305.18;
    CSIP[  5].GPOS[2]= -6.8067e-05;
    CSIP[  6].GPOS[0]=    -4246.74;
    CSIP[  6].GPOS[1]=     1950.66;
    CSIP[  6].GPOS[2]= 0.000425587;
    CSIP[  7].GPOS[0]=    -2123.46;
    CSIP[  7].GPOS[1]=     1952.01;
    CSIP[  7].GPOS[2]= 0.000272656;
    CSIP[  8].GPOS[0]=    -4244.22;
    CSIP[  8].GPOS[1]=    -2299.95;
    CSIP[  8].GPOS[2]=-2.88434e-05;
    CSIP[  9].GPOS[0]=    -2122.81;
    CSIP[  9].GPOS[1]=    -2299.69;
    CSIP[  9].GPOS[2]=  0.00026042;*/
}
void CL_GSIP::F_WCSA_GSIP_SETDEFAULTPOSITIONS_HSCfromPAF(){
    int CID;
    for(CID=0;CID<CCDNUM;CID++)
    CSIP[CID].ID=CID;
    CSIP[  0].GPOS[0]=- 9514.700;
    CSIP[  0].GPOS[1]=    37.350;
    CSIP[  0].GPOS[2]=  0.000000;
    CSIP[  1].GPOS[0]=  7466.700;
    CSIP[  1].GPOS[1]=- 4133.350;
    CSIP[  1].GPOS[2]=  0.000000;
    CSIP[  2].GPOS[0]=- 7392.000;
    CSIP[  2].GPOS[1]=    37.350;
    CSIP[  2].GPOS[2]=  0.000000;
    CSIP[  3].GPOS[0]=  5344.000;
    CSIP[  3].GPOS[1]=- 4133.350;
    CSIP[  3].GPOS[2]=  0.000000;
    CSIP[  4].GPOS[0]=- 5269.300;
    CSIP[  4].GPOS[1]=    37.350;
    CSIP[  4].GPOS[2]=  0.000000;
    CSIP[  5].GPOS[0]=  3221.300;
    CSIP[  5].GPOS[1]=- 4133.350;
    CSIP[  5].GPOS[2]=  0.000000;
    CSIP[  6].GPOS[0]=- 3146.700;
    CSIP[  6].GPOS[1]=    37.350;
    CSIP[  6].GPOS[2]=  0.000000;
    CSIP[  7].GPOS[0]=  1098.700;
    CSIP[  7].GPOS[1]=- 4133.350;
    CSIP[  7].GPOS[2]=  0.000000;
    CSIP[  8].GPOS[0]=- 1024.000;
    CSIP[  8].GPOS[1]=    37.350;
    CSIP[  8].GPOS[2]=  0.000000;
    CSIP[  9].GPOS[0]=- 1024.000;
    CSIP[  9].GPOS[1]=- 4133.350;
    CSIP[  9].GPOS[2]=  0.000000;
    CSIP[ 10].GPOS[0]=  1098.700;
    CSIP[ 10].GPOS[1]=    37.350;
    CSIP[ 10].GPOS[2]=  0.000000;
    CSIP[ 11].GPOS[0]=- 3146.700;
    CSIP[ 11].GPOS[1]=- 4133.350;
    CSIP[ 11].GPOS[2]=  0.000000;
    CSIP[ 12].GPOS[0]=  3221.300;
    CSIP[ 12].GPOS[1]=    37.350;
    CSIP[ 12].GPOS[2]=  0.000000;
    CSIP[ 13].GPOS[0]=- 5269.300;
    CSIP[ 13].GPOS[1]=- 4133.350;
    CSIP[ 13].GPOS[2]=  0.000000;
    CSIP[ 14].GPOS[0]=  5344.000;
    CSIP[ 14].GPOS[1]=    37.350;
    CSIP[ 14].GPOS[2]=  0.000000;
    CSIP[ 15].GPOS[0]=- 7392.000;
    CSIP[ 15].GPOS[1]=- 4133.350;
    CSIP[ 15].GPOS[2]=  0.000000;
    CSIP[ 16].GPOS[0]=  7466.700;
    CSIP[ 16].GPOS[1]=    37.350;
    CSIP[ 16].GPOS[2]=  0.000000;
    CSIP[ 17].GPOS[0]=- 9514.700;
    CSIP[ 17].GPOS[1]=- 4133.350;
    CSIP[ 17].GPOS[2]=  0.000000;
    CSIP[ 18].GPOS[0]=  9589.300;
    CSIP[ 18].GPOS[1]=    37.350;
    CSIP[ 18].GPOS[2]=  0.000000;
    CSIP[ 19].GPOS[0]=-11637.300;
    CSIP[ 19].GPOS[1]=- 4133.350;
    CSIP[ 19].GPOS[2]=  0.000000;
    CSIP[ 20].GPOS[0]= 11712.000;
    CSIP[ 20].GPOS[1]=    37.350;
    CSIP[ 20].GPOS[2]=  0.000000;
    CSIP[ 21].GPOS[0]=-13760.000;
    CSIP[ 21].GPOS[1]=- 4133.350;
    CSIP[ 21].GPOS[2]=  0.000000;
    CSIP[ 22].GPOS[0]= 13834.700;
    CSIP[ 22].GPOS[1]=    37.350;
    CSIP[ 22].GPOS[2]=  0.000000;
    CSIP[ 23].GPOS[0]=-15882.700;
    CSIP[ 23].GPOS[1]=- 4133.350;
    CSIP[ 23].GPOS[2]=  0.000000;
    CSIP[ 24].GPOS[0]=- 9514.700;
    CSIP[ 24].GPOS[1]=  4512.350;
    CSIP[ 24].GPOS[2]=  0.000000;
    CSIP[ 25].GPOS[0]=  7466.700;
    CSIP[ 25].GPOS[1]=- 8608.350;
    CSIP[ 25].GPOS[2]=  0.000000;
    CSIP[ 26].GPOS[0]=- 7392.000;
    CSIP[ 26].GPOS[1]=  4512.350;
    CSIP[ 26].GPOS[2]=  0.000000;
    CSIP[ 27].GPOS[0]=  5344.000;
    CSIP[ 27].GPOS[1]=- 8608.350;
    CSIP[ 27].GPOS[2]=  0.000000;
    CSIP[ 28].GPOS[0]=- 5269.300;
    CSIP[ 28].GPOS[1]=  4512.350;
    CSIP[ 28].GPOS[2]=  0.000000;
    CSIP[ 29].GPOS[0]=  3221.300;
    CSIP[ 29].GPOS[1]=- 8608.350;
    CSIP[ 29].GPOS[2]=  0.000000;
    CSIP[ 30].GPOS[0]=- 3146.700;
    CSIP[ 30].GPOS[1]=  4512.350;
    CSIP[ 30].GPOS[2]=  0.000000;
    CSIP[ 31].GPOS[0]=  1098.700;
    CSIP[ 31].GPOS[1]=- 8608.350;
    CSIP[ 31].GPOS[2]=  0.000000;
    CSIP[ 32].GPOS[0]=- 1024.000;
    CSIP[ 32].GPOS[1]=  4512.350;
    CSIP[ 32].GPOS[2]=  0.000000;
    CSIP[ 33].GPOS[0]=- 1024.000;
    CSIP[ 33].GPOS[1]=- 8608.350;
    CSIP[ 33].GPOS[2]=  0.000000;
    CSIP[ 34].GPOS[0]=  1098.700;
    CSIP[ 34].GPOS[1]=  4512.350;
    CSIP[ 34].GPOS[2]=  0.000000;
    CSIP[ 35].GPOS[0]=- 3146.700;
    CSIP[ 35].GPOS[1]=- 8608.350;
    CSIP[ 35].GPOS[2]=  0.000000;
    CSIP[ 36].GPOS[0]=  3221.300;
    CSIP[ 36].GPOS[1]=  4512.350;
    CSIP[ 36].GPOS[2]=  0.000000;
    CSIP[ 37].GPOS[0]=- 5269.300;
    CSIP[ 37].GPOS[1]=- 8608.350;
    CSIP[ 37].GPOS[2]=  0.000000;
    CSIP[ 38].GPOS[0]=  5344.000;
    CSIP[ 38].GPOS[1]=  4512.350;
    CSIP[ 38].GPOS[2]=  0.000000;
    CSIP[ 39].GPOS[0]=- 7392.000;
    CSIP[ 39].GPOS[1]=- 8608.350;
    CSIP[ 39].GPOS[2]=  0.000000;
    CSIP[ 40].GPOS[0]=  7466.700;
    CSIP[ 40].GPOS[1]=  4512.350;
    CSIP[ 40].GPOS[2]=  0.000000;
    CSIP[ 41].GPOS[0]=- 9514.700;
    CSIP[ 41].GPOS[1]=- 8608.350;
    CSIP[ 41].GPOS[2]=  0.000000;
    CSIP[ 42].GPOS[0]=  9589.300;
    CSIP[ 42].GPOS[1]=  4512.350;
    CSIP[ 42].GPOS[2]=  0.000000;
    CSIP[ 43].GPOS[0]=-11637.300;
    CSIP[ 43].GPOS[1]=- 8608.350;
    CSIP[ 43].GPOS[2]=  0.000000;
    CSIP[ 44].GPOS[0]= 11712.000;
    CSIP[ 44].GPOS[1]=  4512.350;
    CSIP[ 44].GPOS[2]=  0.000000;
    CSIP[ 45].GPOS[0]=-13760.000;
    CSIP[ 45].GPOS[1]=- 8608.350;
    CSIP[ 45].GPOS[2]=  0.000000;
    CSIP[ 46].GPOS[0]= 13834.700;
    CSIP[ 46].GPOS[1]=  4512.350;
    CSIP[ 46].GPOS[2]=  0.000000;
    CSIP[ 47].GPOS[0]=-15882.700;
    CSIP[ 47].GPOS[1]=- 8608.350;
    CSIP[ 47].GPOS[2]=  0.000000;
    CSIP[ 48].GPOS[0]=- 9514.700;
    CSIP[ 48].GPOS[1]=  8987.350;
    CSIP[ 48].GPOS[2]=  0.000000;
    CSIP[ 49].GPOS[0]=  7466.700;
    CSIP[ 49].GPOS[1]=-13083.350;
    CSIP[ 49].GPOS[2]=  0.000000;
    CSIP[ 50].GPOS[0]=- 7392.000;
    CSIP[ 50].GPOS[1]=  8987.350;
    CSIP[ 50].GPOS[2]=  0.000000;
    CSIP[ 51].GPOS[0]=  5344.000;
    CSIP[ 51].GPOS[1]=-13083.350;
    CSIP[ 51].GPOS[2]=  0.000000;
    CSIP[ 52].GPOS[0]=- 5269.300;
    CSIP[ 52].GPOS[1]=  8987.350;
    CSIP[ 52].GPOS[2]=  0.000000;
    CSIP[ 53].GPOS[0]=  3221.300;
    CSIP[ 53].GPOS[1]=-13083.350;
    CSIP[ 53].GPOS[2]=  0.000000;
    CSIP[ 54].GPOS[0]=- 3146.700;
    CSIP[ 54].GPOS[1]=  8987.350;
    CSIP[ 54].GPOS[2]=  0.000000;
    CSIP[ 55].GPOS[0]=  1098.700;
    CSIP[ 55].GPOS[1]=-13083.350;
    CSIP[ 55].GPOS[2]=  0.000000;
    CSIP[ 56].GPOS[0]=- 1024.000;
    CSIP[ 56].GPOS[1]=  8987.350;
    CSIP[ 56].GPOS[2]=  0.000000;
    CSIP[ 57].GPOS[0]=- 1024.000;
    CSIP[ 57].GPOS[1]=-13083.350;
    CSIP[ 57].GPOS[2]=  0.000000;
    CSIP[ 58].GPOS[0]=  1098.700;
    CSIP[ 58].GPOS[1]=  8987.350;
    CSIP[ 58].GPOS[2]=  0.000000;
    CSIP[ 59].GPOS[0]=- 3146.700;
    CSIP[ 59].GPOS[1]=-13083.350;
    CSIP[ 59].GPOS[2]=  0.000000;
    CSIP[ 60].GPOS[0]=  3221.300;
    CSIP[ 60].GPOS[1]=  8987.350;
    CSIP[ 60].GPOS[2]=  0.000000;
    CSIP[ 61].GPOS[0]=- 5269.300;
    CSIP[ 61].GPOS[1]=-13083.350;
    CSIP[ 61].GPOS[2]=  0.000000;
    CSIP[ 62].GPOS[0]=  5344.000;
    CSIP[ 62].GPOS[1]=  8987.350;
    CSIP[ 62].GPOS[2]=  0.000000;
    CSIP[ 63].GPOS[0]=- 7392.000;
    CSIP[ 63].GPOS[1]=-13083.350;
    CSIP[ 63].GPOS[2]=  0.000000;
    CSIP[ 64].GPOS[0]=  7466.700;
    CSIP[ 64].GPOS[1]=  8987.350;
    CSIP[ 64].GPOS[2]=  0.000000;
    CSIP[ 65].GPOS[0]=- 9514.700;
    CSIP[ 65].GPOS[1]=-13083.350;
    CSIP[ 65].GPOS[2]=  0.000000;
    CSIP[ 66].GPOS[0]=  9589.300;
    CSIP[ 66].GPOS[1]=  8987.350;
    CSIP[ 66].GPOS[2]=  0.000000;
    CSIP[ 67].GPOS[0]=-11637.300;
    CSIP[ 67].GPOS[1]=-13083.350;
    CSIP[ 67].GPOS[2]=  0.000000;
    CSIP[ 68].GPOS[0]= 11712.000;
    CSIP[ 68].GPOS[1]=  8987.350;
    CSIP[ 68].GPOS[2]=  0.000000;
    CSIP[ 69].GPOS[0]=-13760.000;
    CSIP[ 69].GPOS[1]=-13083.350;
    CSIP[ 69].GPOS[2]=  0.000000;
    CSIP[ 70].GPOS[0]=- 7392.000;
    CSIP[ 70].GPOS[1]= 13462.350;
    CSIP[ 70].GPOS[2]=  0.000000;
    CSIP[ 71].GPOS[0]=  5344.000;
    CSIP[ 71].GPOS[1]=-17558.350;
    CSIP[ 71].GPOS[2]=  0.000000;
    CSIP[ 72].GPOS[0]=- 5269.300;
    CSIP[ 72].GPOS[1]= 13462.350;
    CSIP[ 72].GPOS[2]=  0.000000;
    CSIP[ 73].GPOS[0]=  3221.300;
    CSIP[ 73].GPOS[1]=-17558.350;
    CSIP[ 73].GPOS[2]=  0.000000;
    CSIP[ 74].GPOS[0]=- 3146.700;
    CSIP[ 74].GPOS[1]= 13462.350;
    CSIP[ 74].GPOS[2]=  0.000000;
    CSIP[ 75].GPOS[0]=  1098.700;
    CSIP[ 75].GPOS[1]=-17558.350;
    CSIP[ 75].GPOS[2]=  0.000000;
    CSIP[ 76].GPOS[0]=- 1024.000;
    CSIP[ 76].GPOS[1]= 13462.350;
    CSIP[ 76].GPOS[2]=  0.000000;
    CSIP[ 77].GPOS[0]=- 1024.000;
    CSIP[ 77].GPOS[1]=-17558.350;
    CSIP[ 77].GPOS[2]=  0.000000;
    CSIP[ 78].GPOS[0]=  1098.700;
    CSIP[ 78].GPOS[1]= 13462.350;
    CSIP[ 78].GPOS[2]=  0.000000;
    CSIP[ 79].GPOS[0]=- 3146.700;
    CSIP[ 79].GPOS[1]=-17558.350;
    CSIP[ 79].GPOS[2]=  0.000000;
    CSIP[ 80].GPOS[0]=  3221.300;
    CSIP[ 80].GPOS[1]= 13462.350;
    CSIP[ 80].GPOS[2]=  0.000000;
    CSIP[ 81].GPOS[0]=- 5269.300;
    CSIP[ 81].GPOS[1]=-17558.350;
    CSIP[ 81].GPOS[2]=  0.000000;
    CSIP[ 82].GPOS[0]=  5344.000;
    CSIP[ 82].GPOS[1]= 13462.350;
    CSIP[ 82].GPOS[2]=  0.000000;
    CSIP[ 83].GPOS[0]=- 7392.000;
    CSIP[ 83].GPOS[1]=-17558.350;
    CSIP[ 83].GPOS[2]=  0.000000;
    CSIP[ 84].GPOS[0]=  9589.300;
    CSIP[ 84].GPOS[1]=- 4437.650;
    CSIP[ 84].GPOS[2]=  0.000000;
    CSIP[ 85].GPOS[0]=-11637.300;
    CSIP[ 85].GPOS[1]=   341.650;
    CSIP[ 85].GPOS[2]=  0.000000;
    CSIP[ 86].GPOS[0]= 11712.000;
    CSIP[ 86].GPOS[1]=- 4437.650;
    CSIP[ 86].GPOS[2]=  0.000000;
    CSIP[ 87].GPOS[0]=-13760.000;
    CSIP[ 87].GPOS[1]=   341.650;
    CSIP[ 87].GPOS[2]=  0.000000;
    CSIP[ 88].GPOS[0]= 13834.700;
    CSIP[ 88].GPOS[1]=- 4437.650;
    CSIP[ 88].GPOS[2]=  0.000000;
    CSIP[ 89].GPOS[0]=-15882.700;
    CSIP[ 89].GPOS[1]=   341.650;
    CSIP[ 89].GPOS[2]=  0.000000;
    CSIP[ 90].GPOS[0]=  9589.300;
    CSIP[ 90].GPOS[1]=- 8912.650;
    CSIP[ 90].GPOS[2]=  0.000000;
    CSIP[ 91].GPOS[0]=-11637.300;
    CSIP[ 91].GPOS[1]=  4816.650;
    CSIP[ 91].GPOS[2]=  0.000000;
    CSIP[ 92].GPOS[0]= 11712.000;
    CSIP[ 92].GPOS[1]=- 8912.650;
    CSIP[ 92].GPOS[2]=  0.000000;
    CSIP[ 93].GPOS[0]=-13760.000;
    CSIP[ 93].GPOS[1]=  4816.650;
    CSIP[ 93].GPOS[2]=  0.000000;
    CSIP[ 94].GPOS[0]= 13834.700;
    CSIP[ 94].GPOS[1]=- 8912.650;
    CSIP[ 94].GPOS[2]=  0.000000;
    CSIP[ 95].GPOS[0]=-15882.700;
    CSIP[ 95].GPOS[1]=  4816.650;
    CSIP[ 95].GPOS[2]=  0.000000;
    CSIP[ 96].GPOS[0]=  9589.300;
    CSIP[ 96].GPOS[1]=-13387.650;
    CSIP[ 96].GPOS[2]=  0.000000;
    CSIP[ 97].GPOS[0]=-11637.300;
    CSIP[ 97].GPOS[1]=  9291.650;
    CSIP[ 97].GPOS[2]=  0.000000;
    CSIP[ 98].GPOS[0]= 11712.000;
    CSIP[ 98].GPOS[1]=-13387.650;
    CSIP[ 98].GPOS[2]=  0.000000;
    CSIP[ 99].GPOS[0]=-13760.000;
    CSIP[ 99].GPOS[1]=  9291.650;
    CSIP[ 99].GPOS[2]=  0.000000;

    CSIP[100].GPOS[0]=- 7467.700;
    CSIP[100].GPOS[1]= 13543.650;
    CSIP[100].GPOS[2]=  0.785398;
    CSIP[101].GPOS[0]= 11643.000;
    CSIP[101].GPOS[1]= 13543.650;
    CSIP[101].GPOS[2]=  0.785398;
    CSIP[102].GPOS[0]= 11643.000;
    CSIP[102].GPOS[1]=-15341.350;
    CSIP[102].GPOS[2]=  0.785398;
    CSIP[103].GPOS[0]=- 7467.700;
    CSIP[103].GPOS[1]=-15341.350;
    CSIP[103].GPOS[2]=  0.785398;
}
