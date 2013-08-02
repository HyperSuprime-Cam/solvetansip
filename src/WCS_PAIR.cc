//------------------------------------------------------------
//WCS_APAIR.cc
//
//Last modification : 2011/12/20
//------------------------------------------------------------
#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<cmath>
#include<string.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"
//#include "hsc/meas/tansip/WCS_SUB.h"
//#include "hsc/meas/tansip/LeastSquares.h"

using namespace std;
void F_SET_SIMCCDPOS(double **GPOS);
//--------------------------------------------------
//MAIN
//--------------------------------------------------
void CL_APAIR::F_WCSA_APAIR_NEWAPAIR(){
//1
    PAIR = new CL_PAIR[ALLREFNUM];
    GPOS = F_NEWdouble2(CCDNUM,3);
//2
    REJNUM              =F_NEWint1(CCDNUM+1);
    SIP_AB[0]           =F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
    SIP_AB[1]           =F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
    SIP_ABP[0]          =F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    SIP_ABP[1]          =F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    CDSIP_AB[0]         =F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
    CDSIP_AB[1]         =F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
    CDSIP_ABP[0]        =F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    CDSIP_ABP[1]        =F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TCoef[0]            =F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
    TCoef[1]            =F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
    TdCoef[0][0]        =F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
    TdCoef[0][1]        =F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
    TdCoef[1][0]        =F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
    TdCoef[1][1]        =F_NEWdouble1((SIP_ORDER  +1)*(SIP_ORDER  +2));
    TPCoef[0]           =F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TPCoef[1]           =F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TdPCoef[0][0]       =F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TdPCoef[0][1]       =F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TdPCoef[1][0]       =F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TdPCoef[1][1]       =F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TLCoef[0]           =F_NEWdouble2(CCDNUM,(SIP_L_ORDER+1)*(SIP_L_ORDER+2));
    TLCoef[1]           =F_NEWdouble2(CCDNUM,(SIP_L_ORDER+1)*(SIP_L_ORDER+2));
    TdLCoef[0][0]       =F_NEWdouble2(CCDNUM,(SIP_L_ORDER+1)*(SIP_L_ORDER+2));
    TdLCoef[0][1]       =F_NEWdouble2(CCDNUM,(SIP_L_ORDER+1)*(SIP_L_ORDER+2));
    TdLCoef[1][0]       =F_NEWdouble2(CCDNUM,(SIP_L_ORDER+1)*(SIP_L_ORDER+2));
    TdLCoef[1][1]       =F_NEWdouble2(CCDNUM,(SIP_L_ORDER+1)*(SIP_L_ORDER+2));

}
void CL_APAIR::F_WCSA_APAIR_DELAPAIR(){
//2
    F_DELint1   (REJNUM);
    F_DELdouble1(SIP_AB[0]           );
    F_DELdouble1(SIP_AB[1]           );
    F_DELdouble1(SIP_ABP[0]          );
    F_DELdouble1(SIP_ABP[1]          );
    F_DELdouble1(CDSIP_AB[0]         );
    F_DELdouble1(CDSIP_AB[1]         );
    F_DELdouble1(CDSIP_ABP[0]        );
    F_DELdouble1(CDSIP_ABP[1]        );
    F_DELdouble1(TCoef[0]            );
    F_DELdouble1(TCoef[1]            );
    F_DELdouble1(TdCoef[0][0]        );
    F_DELdouble1(TdCoef[0][1]        );
    F_DELdouble1(TdCoef[1][0]        );
    F_DELdouble1(TdCoef[1][1]        );
    F_DELdouble1(TPCoef[0]           );
    F_DELdouble1(TPCoef[1]           );
    F_DELdouble1(TdPCoef[0][0]       );
    F_DELdouble1(TdPCoef[0][1]       );
    F_DELdouble1(TdPCoef[1][0]       );
    F_DELdouble1(TdPCoef[1][1]       );
    F_DELdouble2(CCDNUM,TLCoef[0]    );
    F_DELdouble2(CCDNUM,TLCoef[1]    );
    F_DELdouble2(CCDNUM,TdLCoef[0][0]);
    F_DELdouble2(CCDNUM,TdLCoef[0][1]);
    F_DELdouble2(CCDNUM,TdLCoef[1][0]);
    F_DELdouble2(CCDNUM,TdLCoef[1][1]);
//1
    delete [] PAIR;
    F_DELdouble2(CCDNUM,GPOS);
}
void CL_APAIR::F_WCSA_APAIR_SET0(){
    CCDPOSMODE =0;
//    CCDNUM     =0;
//    ALLREFNUM  =0;
//    ALLFITNUM  =0;
//    SIP_ORDER  =0;
//    SIP_P_ORDER=0;
//    SIP_L_ORDER=0;
    CLIP_SIGMA =0;
    ANGLE      =0;
    OAVAL[0]=OAVAL[1]=0;
    OAPIX[0]=OAPIX[1]=0;
    CRVAL[0]=CRVAL[1]=0;
    CRPIX[0]=CRPIX[1]=0;
    CENTER_PIXEL[0]=CENTER_PIXEL[1]=0;
    CENTER_RADEC[0]=CENTER_RADEC[1]=0;
    CD[0][0]=CD[0][1]=CD[1][0]=CD[1][1]=0;
    InvCD[0][0]=InvCD[0][1]=InvCD[1][0]=InvCD[1][1]=0;
}
void CL_APAIR::F_WCSA_APAIR_REJECTION(){
    int NUM,CID;

//    if(STDOUT==2)for(CID=0;CID<CCDNUM;CID++)cout << "X : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][0] <<endl<< "Y : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][1] << endl;
//    F_WCSA_APAIR_CALCRMS(SIP_P_ORDER,0,10);   
    F_WCSA_APAIR_CALCRMS(SIP_ORDER,10,0);   

//cout << "-- REJECTION VALUE --" << endl;
//for(NUM=0;NUM<ALLREFNUM;NUM++)
//if(PAIR[NUM].FLAG == 1)
//cout << NUM << "	" << PAIR[NUM].CHIPID << "	" << PAIR[NUM].X_RADEC[0] << "	" << PAIR[NUM].X_RADEC[1] << "	" << PAIR[NUM].X_CENTER_GLOBAL[0] << "	" << PAIR[NUM].X_CENTER_GLOBAL[1] << "	" << F_CALCVALUE(SIP_P_ORDER,TCoef[0],PAIR[NUM].X_RADEC) << "	" << F_CALCVALUE(SIP_P_ORDER,TCoef[1],PAIR[NUM].X_RADEC) << "	" <<  fabs(PAIR[NUM].X_CENTER_GLOBAL[0]-F_CALCVALUE(SIP_P_ORDER,TCoef[0],PAIR[NUM].X_RADEC)) << "	" << CLIP_SIGMA*AVERMS[0][1] << "	" << fabs(PAIR[NUM].X_CENTER_GLOBAL[1]-F_CALCVALUE(SIP_P_ORDER,TCoef[1],PAIR[NUM].X_RADEC)) << "	" << CLIP_SIGMA*AVERMS[1][1] << endl;
//for(NUM=0;NUM<ALLREFNUM;NUM++)
//if(PAIR[NUM].FLAG == 1)
//if(fabs(PAIR[NUM].X_RADEC[0]-F_CALCVALUE(SIP_ORDER,TCoef[0],PAIR[NUM].X_CENTER_GLOBAL)) > CLIP_SIGMA*AVERMS[0][1] || fabs(PAIR[NUM].X_RADEC[1]-F_CALCVALUE(SIP_ORDER,TCoef[1],PAIR[NUM].X_CENTER_GLOBAL)) > CLIP_SIGMA*AVERMS[1][1])
//cout << NUM << "	" << PAIR[NUM].CHIPID << "	" << PAIR[NUM].X_RADEC[0] << "	" << PAIR[NUM].X_RADEC[1] << "	" << PAIR[NUM].X_CENTER_GLOBAL[0] << "	" << PAIR[NUM].X_CENTER_GLOBAL[1] << "	" << F_CALCVALUE(SIP_ORDER,TCoef[0],PAIR[NUM].X_CENTER_GLOBAL) << "	" << F_CALCVALUE(SIP_ORDER,TCoef[1],PAIR[NUM].X_CENTER_GLOBAL) << "	" <<  fabs(PAIR[NUM].X_RADEC[0]-F_CALCVALUE(SIP_ORDER,TCoef[0],PAIR[NUM].X_CENTER_GLOBAL)) << "	" << CLIP_SIGMA*AVERMS[0][1] << "	" << fabs(PAIR[NUM].X_RADEC[1]-F_CALCVALUE(SIP_ORDER,TCoef[1],PAIR[NUM].X_CENTER_GLOBAL)) << "	" << CLIP_SIGMA*AVERMS[1][1] << endl;

    for(NUM=0;NUM<ALLREFNUM;NUM++)
//    if(fabs(PAIR[NUM].X_CENTER_GLOBAL[0]-F_CALCVALUE(SIP_P_ORDER,TCoef[0],PAIR[NUM].X_RADEC)) > CLIP_SIGMA*AVERMS[0][1] || fabs(PAIR[NUM].X_CENTER_GLOBAL[1]-F_CALCVALUE(SIP_P_ORDER,TCoef[1],PAIR[NUM].X_RADEC)) > CLIP_SIGMA*AVERMS[1][1]){
    if(fabs(PAIR[NUM].X_RADEC[0]-F_CALCVALUE(SIP_ORDER,TCoef[0],PAIR[NUM].X_CENTER_GLOBAL)) > CLIP_SIGMA*AVERMS[0][1] || fabs(PAIR[NUM].X_RADEC[1]-F_CALCVALUE(SIP_ORDER,TCoef[1],PAIR[NUM].X_CENTER_GLOBAL)) > CLIP_SIGMA*AVERMS[1][1]||PAIR[NUM].FLAG==0){
    PAIR[NUM].FLAG=0;
    REJNUM[PAIR[NUM].CHIPID]++;
    REJNUM[CCDNUM]++;
    }
    F_WCSA_APAIR_CENTERofOBJECTS();
    if(STDOUT==2)cout << "CENTER_PIXEL : " << CENTER_PIXEL[0] << " , " << CENTER_PIXEL[1] << endl;
    if(STDOUT==2)cout << "CENTER_RADEC : " << CENTER_RADEC[0] << " , " << CENTER_RADEC[1] << endl;
    if(STDOUT==2)cout << "BEFORE REJECTION" << endl;
    if(STDOUT==2)cout << "RMS X(degree): " << AVERMS[0][1] << endl;
    if(STDOUT==2)cout << "RMS Y(degree): " << AVERMS[1][1] << endl;
    if(STDOUT==2)cout << "RMS X(pix)   : " << AVERMS[0][1]/4.7e-5 << endl;
    if(STDOUT==2)cout << "RMS Y(pix)   : " << AVERMS[1][1]/4.7e-5 << endl;
    F_WCSA_APAIR_CALCRMS(SIP_ORDER,10,0);   
//for(NUM=0;NUM<ALLREFNUM;NUM++)
//if(PAIR[NUM].FLAG == 1)
//if(fabs(PAIR[NUM].X_RADEC[0]-F_CALCVALUE(SIP_ORDER,TCoef[0],PAIR[NUM].X_CENTER_GLOBAL)) > CLIP_SIGMA*AVERMS[0][1] || fabs(PAIR[NUM].X_RADEC[1]-F_CALCVALUE(SIP_ORDER,TCoef[1],PAIR[NUM].X_CENTER_GLOBAL)) > CLIP_SIGMA*AVERMS[1][1])
//cout << NUM << "	" << PAIR[NUM].CHIPID << "	" << PAIR[NUM].X_RADEC[0] << "	" << PAIR[NUM].X_RADEC[1] << "	" << PAIR[NUM].X_CENTER_GLOBAL[0] << "	" << PAIR[NUM].X_CENTER_GLOBAL[1] << "	" << F_CALCVALUE(SIP_ORDER,TCoef[0],PAIR[NUM].X_CENTER_GLOBAL) << "	" << F_CALCVALUE(SIP_ORDER,TCoef[1],PAIR[NUM].X_CENTER_GLOBAL) << "	" <<  fabs(PAIR[NUM].X_RADEC[0]-F_CALCVALUE(SIP_ORDER,TCoef[0],PAIR[NUM].X_CENTER_GLOBAL)) << "	" << CLIP_SIGMA*AVERMS[0][1] << "	" << fabs(PAIR[NUM].X_RADEC[1]-F_CALCVALUE(SIP_ORDER,TCoef[1],PAIR[NUM].X_CENTER_GLOBAL)) << "	" << CLIP_SIGMA*AVERMS[1][1] << endl;
    if(STDOUT==2)cout << "AFTER REJECTION" << endl;
    if(STDOUT==2)cout << "RMS X(degree): " << AVERMS[0][1] << endl;
    if(STDOUT==2)cout << "RMS Y(degree): " << AVERMS[1][1] << endl;
    if(STDOUT==2)cout << "RMS X(pix)   : " << AVERMS[0][1]/4.7e-5 << endl;
    if(STDOUT==2)cout << "RMS Y(pix)   : " << AVERMS[1][1]/4.7e-5 << endl;
    for(CID=0;CID<CCDNUM;CID++)
    if(STDOUT==2)cout << "REJECTED NUM CHIP : " << CID << " : " << REJNUM[CID] << endl;
    if(STDOUT==2)cout << "REJECTED NUM TOTAL: " << REJNUM[CCDNUM] << endl;

}
void CL_APAIR::F_WCSA_APAIR_GPOS(){
    int CID;

    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : PROJECTION ---" << endl;

    F_WCSA_APAIR_CENTERPROJECTION();
    F_WCSA_APAIR_LDIFFVALUES();

    if(CCDPOSMODE==1){
    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : CALCULATING THETA of CCD ---" << endl;
    F_WCSA_APAIR_CCDPOSITIONS_T();
    if(STDOUT==2)cout << "T  iteration times : " << IterNUM_T  << " (MAX=10)" << endl;
    if(STDOUT==2)for(CID=0;CID<CCDNUM;CID++)cout << "T : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][2] << endl;
    if(STDOUT==2)cout << "T : AVE : " << GPOS_AVE[2] << endl;
    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : SET AVERAGE of THETAs = 0 ---" << endl;
    F_WCSA_APAIR_CCDPOSITIONS_T_SETAVERAGE();
//add : ROTATE CCD
    if(STDOUT==2)for(CID=0;CID<CCDNUM;CID++)cout << "T : " << setfill ('0') << setw (3) <<CID << fixed<< " : " <<scientific << GPOS[CID][2] <<fixed<< endl;
    
    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : CALCULATING XY of CCD ---" << endl;
    F_WCSA_APAIR_CCDPOSITIONS_XY();
//add : SHIFT CCD
    F_WCSA_APAIR_CCDPOSITIONS_XY_SETAVERAGE();//CENTER = (1024, 2048)
//HIGH ORDER CORRECTION 
    if(STDOUT==2)for(CID=0;CID<CCDNUM;CID++)cout << "X : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][0] <<endl<< "Y : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][1] << endl;
//    F_WCSA_APAIR_CCDPOSITIONS_XY_CORRECTION();
    }

    if(CCDPOSHMODE==1){
    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : HIGH PRESICION CORRECTION ---" << endl;
    F_WCSA_APAIR_CCDPOSITIONS_XYT_CORRECTION();
//    if(STDOUT==2)for(CID=0;CID<CCDNUM;CID++)cout << "X : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][0] <<endl<< "Y : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][1] << endl;
 //   if(STDOUT==2)cout << "X : AVE : " << GPOS_AVE[0] << endl << "Y : AVE : " << GPOS_AVE[1] << endl;
    if(STDOUT==2)for(CID=0;CID<CCDNUM;CID++)cout << "CID : " << setfill ('0') << setw (3) <<CID << fixed<< " : X : " << GPOS[CID][0] << " : Y : " << GPOS[CID][1] << " : T : " <<scientific<< GPOS[CID][2] << endl;
//for(CID=0;CID<CCDNUM;CID++)cout << "CID : " << setfill ('0') << setw (3) <<CID << fixed<< " : X : " << GPOS[CID][0]+1024 << " : Y : " << GPOS[CID][1]+2088 << " : T : " <<scientific<< GPOS[CID][2] << endl;

	}
}

void CL_APAIR::F_WCSA_APAIR_WCS(){
    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : GET CR--" << endl;
    F_WCSA_APAIR_CALCCR();

    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET X--" << endl;
    F_WCSA_APAIR_SETX();

    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : FITTING--" << endl;
    F_WCSA_APAIR_FITTING();
    F_WCSA_APAIR_SETXSIP();

    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET RMS of SIPs--" << endl;
    F_WCSA_APAIR_CALCSIPRMS();
    F_WCSA_APAIR_CALCPSIPRMS();

    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : GET CRSM (Convergence, rotation, Shear, Magnification)--" << endl;
    F_WCSA_APAIR_CALCCONVROTSHEARMAG();
}

//--------------------------------------------------
//SET X
//--------------------------------------------------
void CL_APAIR::F_WCSA_APAIR_SETXG(){
    int NUM;
    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].X_GLOBAL[0]=GPOS[PAIR[NUM].CHIPID][0]+PAIR[NUM].X_LOCAL[0]*cos(GPOS[PAIR[NUM].CHIPID][2])-PAIR[NUM].X_LOCAL[1]*sin(GPOS[PAIR[NUM].CHIPID][2]);
        PAIR[NUM].X_GLOBAL[1]=GPOS[PAIR[NUM].CHIPID][1]+PAIR[NUM].X_LOCAL[1]*cos(GPOS[PAIR[NUM].CHIPID][2])+PAIR[NUM].X_LOCAL[0]*sin(GPOS[PAIR[NUM].CHIPID][2]);
    }
}
void CL_APAIR::F_WCSA_APAIR_SETXCRPIX(){
    int NUM;
    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].X_CRPIX[0]=PAIR[NUM].X_GLOBAL[0]-CRPIX[0];
        PAIR[NUM].X_CRPIX[1]=PAIR[NUM].X_GLOBAL[1]-CRPIX[1];
        PAIR[NUM].X_GLOBALCRPIX[0]=PAIR[NUM].X_GLOBAL[0]-CRPIX[0];
        PAIR[NUM].X_GLOBALCRPIX[1]=PAIR[NUM].X_GLOBAL[1]-CRPIX[1];
    }
}
void CL_APAIR::F_WCSA_APAIR_PROJECTION(){
    int NUM;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    F_PROJECTION(PAIR[NUM].X_RADEC,PAIR[NUM].X_IM_WORLD,CRVAL);
}
void CL_APAIR::F_WCSA_APAIR_SETXIM(){
    int NUM;
    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].X_IM_PIXEL[0]=InvCD[0][0]*PAIR[NUM].X_IM_WORLD[0]+InvCD[0][1]*PAIR[NUM].X_IM_WORLD[1];
        PAIR[NUM].X_IM_PIXEL[1]=InvCD[1][0]*PAIR[NUM].X_IM_WORLD[0]+InvCD[1][1]*PAIR[NUM].X_IM_WORLD[1];
    }
}
void CL_APAIR::F_WCSA_APAIR_SETXSIP(){
    int NUM;
    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].X_PSIP_GLOBALCRPIX[0]=F_CALCVALUE(SIP_P_ORDER,SIP_ABP[0],PAIR[NUM].X_IM_PIXEL)+PAIR[NUM].X_IM_PIXEL[0];
        PAIR[NUM].X_PSIP_GLOBALCRPIX[1]=F_CALCVALUE(SIP_P_ORDER,SIP_ABP[1],PAIR[NUM].X_IM_PIXEL)+PAIR[NUM].X_IM_PIXEL[1];
        PAIR[NUM].X_SIP_IM_PIXEL[0]    =F_CALCVALUE(SIP_ORDER,SIP_AB[0],PAIR[NUM].X_GLOBALCRPIX)+PAIR[NUM].X_GLOBALCRPIX[0];
        PAIR[NUM].X_SIP_IM_PIXEL[1]    =F_CALCVALUE(SIP_ORDER,SIP_AB[1],PAIR[NUM].X_GLOBALCRPIX)+PAIR[NUM].X_GLOBALCRPIX[1];
    }
}
void CL_APAIR::F_WCSA_APAIR_CALCMAXR(){
    int NUM,CID;
    double R;
    R=0;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG == 1)
    if(hypot(PAIR[NUM].X_CRPIX[0],PAIR[NUM].X_CRPIX[1])>R){
        R=hypot(PAIR[NUM].X_CRPIX[0],PAIR[NUM].X_CRPIX[1]);
    }
    MAXFRAD=R;
    
    R=0;
    for(CID=0;CID<CCDNUM;CID++){
        if(hypot(GPOS[CID][0]-CRPIX[0]+0000,GPOS[CID][1]-CRPIX[1]+0000)>R)
        R= hypot(GPOS[CID][0]-CRPIX[0]+0000,GPOS[CID][1]-CRPIX[1]+0000);
        if(hypot(GPOS[CID][0]-CRPIX[0]+2048,GPOS[CID][1]-CRPIX[1]+0000)>R)
        R= hypot(GPOS[CID][0]-CRPIX[0]+2048,GPOS[CID][1]-CRPIX[1]+0000);
        if(hypot(GPOS[CID][0]-CRPIX[0]+0000,GPOS[CID][1]-CRPIX[1]+4096)>R)
        R= hypot(GPOS[CID][0]-CRPIX[0]+0000,GPOS[CID][1]-CRPIX[1]+4096);
        if(hypot(GPOS[CID][0]-CRPIX[0]+2048,GPOS[CID][1]-CRPIX[1]+4096)>R)
        R= hypot(GPOS[CID][0]-CRPIX[0]+2048,GPOS[CID][1]-CRPIX[1]+4096);
    }
    MAXDRAD=R;
}
void CL_APAIR::F_WCSA_APAIR_SETX(){
    F_WCSA_APAIR_SETXG();
    F_WCSA_APAIR_SETXCRPIX();
    F_WCSA_APAIR_PROJECTION();
    F_WCSA_APAIR_SETXIM();
    F_WCSA_APAIR_CALCMAXR();
}
void CL_APAIR::F_WCSA_APAIR_CENTERPROJECTION(){
    int NUM;
/*    if(strcmp(CRPIXMODE,"VAL")==0){
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        F_PROJECTION(PAIR[NUM].X_RADEC,PAIR[NUM].X_CENTER_IM_WORLD,CRVAL);
    }else{
*/        for(NUM=0;NUM<ALLREFNUM;NUM++)
        F_PROJECTION(PAIR[NUM].X_RADEC,PAIR[NUM].X_CENTER_IM_WORLD,CENTER_RADEC);
//    }
}
void CL_APAIR::F_WCSA_APAIR_CENTERofOBJECTS(){
    int NUM,FNUM;

    CENTER_PIXEL[0]=CENTER_PIXEL[1]=CENTER_RADEC[0]=CENTER_RADEC[1]=FNUM=0;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG == 1){
        CENTER_PIXEL[0]+=PAIR[NUM].X_GLOBAL[0];
        CENTER_PIXEL[1]+=PAIR[NUM].X_GLOBAL[1];
        FNUM++;
    }
    ALLFITNUM=FNUM;
    CENTER_PIXEL[0]/=FNUM;
    CENTER_PIXEL[1]/=FNUM;
//cout << "CENTER : " << CENTER_PIXEL[0] << " : " << CENTER_PIXEL[1] << endl;
//CENTER_PIXEL[0]+=124;
//CENTER_PIXEL[1]+=248;
    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].X_CENTER_GLOBAL[0]=PAIR[NUM].X_GLOBAL[0]-CENTER_PIXEL[0];
        PAIR[NUM].X_CENTER_GLOBAL[1]=PAIR[NUM].X_GLOBAL[1]-CENTER_PIXEL[1];
   }

    F_WCSA_APAIR_GFITTING(SIP_ORDER,6,0,TCoef);
    CENTER_RADEC[0]=TCoef[0][0];
    CENTER_RADEC[1]=TCoef[1][0];


}
void CL_APAIR::F_WCSA_APAIR_CALCCR(){

          if(strcmp(CRPIXMODE,"OAXIS")==0){
F_WCSA_APAIR_SETXG();
F_WCSA_APAIR_CENTERofOBJECTS();
CRPIX[0]=CENTER_PIXEL[0];
CRPIX[1]=CENTER_PIXEL[1];
CRVAL[0]=CENTER_RADEC[0];
CRVAL[1]=CENTER_RADEC[1];
    }else if(strcmp(CRPIXMODE,"PIX")==0){
        F_WCSA_APAIR_CALCCRVAL();
    }else if(strcmp(CRPIXMODE,"VAL")==0){
        F_WCSA_APAIR_CALCCRPIX();
    }else                                 {
        F_WCSA_APAIR_SETXG();
        F_WCSA_APAIR_CENTERofOBJECTS();
        CRPIX[0]=CENTER_PIXEL[0];
        CRPIX[1]=CENTER_PIXEL[1];
        CRVAL[0]=CENTER_RADEC[0];
        CRVAL[1]=CENTER_RADEC[1];
    }
}
void CL_APAIR::F_WCSA_APAIR_CALCCRVAL(){
    F_WCSA_APAIR_SETXG();
    F_WCSA_APAIR_SETXCRPIX();
    F_WCSA_APAIR_GFITTING(SIP_ORDER,3,0,TCoef);
    CRVAL[0]=TCoef[0][0];
    CRVAL[1]=TCoef[1][0];
}
void CL_APAIR::F_WCSA_APAIR_CALCCRPIX(){
    F_WCSA_APAIR_PROJECTION();
    F_WCSA_APAIR_SETXG();
    F_WCSA_APAIR_GFITTING(SIP_P_ORDER,1,4,TPCoef);
    CRPIX[0]=TPCoef[0][0];
    CRPIX[1]=TPCoef[1][0];
}
//---------------------------------------------
//FITTING
//---------------------------------------------
void CL_APAIR::F_WCSA_APAIR_FITTING(){
F_WCSA_APAIR_GFITTING(SIP_ORDER  ,3,1,CDSIP_AB);
F_WCSA_APAIR_SETCDSIP();
F_WCSA_APAIR_SETXIM();
F_WCSA_APAIR_GFITTING(SIP_P_ORDER,1,3,CDSIP_ABP);
/*
cout << scientific << endl;
cout <<"00:"<< CDSIP_ABP[0][0] << "	" << CDSIP_ABP[1][0] << endl;
cout <<"01:"<< CDSIP_ABP[0][1] << "	" << CDSIP_ABP[1][1] << endl;
cout <<"02:"<< CDSIP_ABP[0][2] << "	" << CDSIP_ABP[1][2] << endl;
cout <<"03:"<< CDSIP_ABP[0][3] << "	" << CDSIP_ABP[1][3] << endl;
cout <<"04:"<< CDSIP_ABP[0][4] << "	" << CDSIP_ABP[1][4] << endl;
cout <<"05:"<< CDSIP_ABP[0][5] << "	" << CDSIP_ABP[1][5] << endl;
cout <<"06:"<< CDSIP_ABP[0][6] << "	" << CDSIP_ABP[1][6] << endl;
cout <<"07:"<< CDSIP_ABP[0][7] << "	" << CDSIP_ABP[1][7] << endl;
cout <<"08:"<< CDSIP_ABP[0][8] << "	" << CDSIP_ABP[1][8] << endl;
cout <<"09:"<< CDSIP_ABP[0][9] << "	" << CDSIP_ABP[1][9] << endl;
cout <<"10:"<< CDSIP_ABP[0][10] << "	" << CDSIP_ABP[1][10] << endl;
cout <<"11:"<< CDSIP_ABP[0][11] << "	" << CDSIP_ABP[1][11] << endl;
cout << endl;
F_WCSA_APAIR_GFITTING(SIP_P_ORDER,2,3,SIP_ABP);
cout <<"00:"<< SIP_ABP[0][0] << "	" << SIP_ABP[1][0] << endl;
cout <<"01:"<< SIP_ABP[0][1] << "	" << SIP_ABP[1][1] << endl;
cout <<"02:"<< SIP_ABP[0][2] << "	" << SIP_ABP[1][2] << endl;
cout <<"03:"<< SIP_ABP[0][3] << "	" << SIP_ABP[1][3] << endl;
cout <<"04:"<< SIP_ABP[0][4] << "	" << SIP_ABP[1][4] << endl;
cout <<"05:"<< SIP_ABP[0][5] << "	" << SIP_ABP[1][5] << endl;
cout <<"06:"<< SIP_ABP[0][6] << "	" << SIP_ABP[1][6] << endl;
cout <<"07:"<< SIP_ABP[0][7] << "	" << SIP_ABP[1][7] << endl;
cout <<"08:"<< SIP_ABP[0][8] << "	" << SIP_ABP[1][8] << endl;
cout <<"09:"<< SIP_ABP[0][9] << "	" << SIP_ABP[1][9] << endl;
cout <<"10:"<< SIP_ABP[0][10] << "	" << SIP_ABP[1][10] << endl;
cout <<"11:"<< SIP_ABP[0][11] << "	" << SIP_ABP[1][11] << endl;
F_WCSA_APAIR_CHANGEVARIABLE(SIP_P_ORDER,CD,CDSIP_ABP[0],SIP_ABP[0]);
F_WCSA_APAIR_CHANGEVARIABLE(SIP_P_ORDER,CD,CDSIP_ABP[1],SIP_ABP[1]);
cout <<"00:"<< SIP_ABP[0][0] << "	" << SIP_ABP[1][0] << endl;
cout <<"01:"<< SIP_ABP[0][1] << "	" << SIP_ABP[1][1] << endl;
cout <<"02:"<< SIP_ABP[0][2] << "	" << SIP_ABP[1][2] << endl;
cout <<"03:"<< SIP_ABP[0][3] << "	" << SIP_ABP[1][3] << endl;
cout <<"04:"<< SIP_ABP[0][4] << "	" << SIP_ABP[1][4] << endl;
cout <<"05:"<< SIP_ABP[0][5] << "	" << SIP_ABP[1][5] << endl;
cout <<"06:"<< SIP_ABP[0][6] << "	" << SIP_ABP[1][6] << endl;
cout <<"07:"<< SIP_ABP[0][7] << "	" << SIP_ABP[1][7] << endl;
cout <<"08:"<< SIP_ABP[0][8] << "	" << SIP_ABP[1][8] << endl;
cout <<"09:"<< SIP_ABP[0][9] << "	" << SIP_ABP[1][9] << endl;
cout <<"10:"<< SIP_ABP[0][10] << "	" << SIP_ABP[1][10] << endl;
cout <<"11:"<< SIP_ABP[0][11] << "	" << SIP_ABP[1][11] << endl;
cout << endl;
*/
//F_WCSA_APAIR_CHANGEVARIABLE(SIP_P_ORDER,InvCD,SIP_ABP[0],CDSIP_ABP[0]);
//F_WCSA_APAIR_CHANGEVARIABLE(SIP_P_ORDER,InvCD,SIP_ABP[1],CDSIP_ABP[1]);
//F_WCSA_APAIR_SETCDPSIP();
F_WCSA_APAIR_GFITTING(SIP_P_ORDER,2,3,SIP_ABP);
F_WCSA_APAIR_SETCDPSIP();
}
void CL_APAIR::F_WCSA_APAIR_GFITTING(int ORDER,int VARIABLE,int FUNCTION, double **Coef){
    int i,NUM,FNUM=0;
    double ***dx;

//--------------------------------------------------
    dx = F_NEWdouble3(2,ALLREFNUM,3);

    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG == 1){
            for(i=0;i<2;i++)
	      if(VARIABLE==0){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_RADEC[i];
        }else if(VARIABLE==1){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_IM_WORLD[i];
        }else if(VARIABLE==2){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_IM_PIXEL[i];
        }else if(VARIABLE==3){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_CRPIX[i];
        }else if(VARIABLE==4){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_GLOBAL[i];
        }else if(VARIABLE==5){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_LOCAL[i];
        }else if(VARIABLE==6){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_CENTER_GLOBAL[i];
        }else if(VARIABLE==7){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_CENTER_IM_WORLD[i];
        }else if(VARIABLE==10){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_CENTER_GLOBAL[i];
        }else if(VARIABLE==11){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_CENTER_RADEC[i];
        }
            for(i=0;i<2;i++)
	      if(FUNCTION==0){
            dx[i][FNUM][2]=PAIR[NUM].X_RADEC[i];
        }else if(FUNCTION==1){
            dx[i][FNUM][2]=PAIR[NUM].X_IM_WORLD[i];
        }else if(FUNCTION==2){
            dx[i][FNUM][2]=PAIR[NUM].X_IM_PIXEL[i];
        }else if(FUNCTION==3){
            dx[i][FNUM][2]=PAIR[NUM].X_CRPIX[i];
        }else if(FUNCTION==4){
            dx[i][FNUM][2]=PAIR[NUM].X_GLOBAL[i];
        }else if(FUNCTION==5){
            dx[i][FNUM][2]=PAIR[NUM].X_LOCAL[i];
        }else if(FUNCTION==6){
            dx[i][FNUM][2]=PAIR[NUM].CAMERA_CONVROT[i];
        }else if(FUNCTION==7){
            dx[i][FNUM][2]=PAIR[NUM].CAMERA_SHEAR[i];
        }else if(FUNCTION==8){
            dx[i][FNUM][2]=PAIR[NUM].CAMERA_MAGNIFICATION;
        }else if(FUNCTION==9){
            dx[i][FNUM][2]=PAIR[NUM].CAMERA_PMAGNIFICATION;
        }else if(FUNCTION==10){
            dx[i][FNUM][2]=PAIR[NUM].X_CENTER_GLOBAL[i];
        }else if(FUNCTION==11){
            dx[i][FNUM][2]=PAIR[NUM].X_CENTER_RADEC[i];
        }
        FNUM++;
    }
    ALLFITNUM=FNUM;

    for(NUM=FNUM;NUM<ALLREFNUM;NUM++)
    dx[0][NUM][0]=dx[0][NUM][1]=dx[0][NUM][2]=dx[1][NUM][0]=dx[1][NUM][1]=dx[1][NUM][2]=0;

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
//--------------------------------------------------
    F_DELdouble3(2,ALLREFNUM,dx);
}

void CL_APAIR::F_WCSA_APAIR_LFITTING(int VARIABLE,int FUNCTION){
    int i,CID,NUM,*CNUM;
    double ****dx;

//--------------------------------------------------
    CNUM = F_NEWint1(CCDNUM);
    dx = F_NEWdouble4(2,CCDNUM,ALLREFNUM,3);
//--------------------------------------------------

    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG == 1){
        CID=PAIR[NUM].CHIPID;
        for(i=0;i<2;i++)
	      if(VARIABLE==0){
            dx[0][CID][CNUM[CID]][i]=dx[1][CID][CNUM[CID]][i]=PAIR[NUM].X_RADEC[i];
        }else if(VARIABLE==1){
            dx[0][CID][CNUM[CID]][i]=dx[1][CID][CNUM[CID]][i]=PAIR[NUM].X_IM_WORLD[i];
        }else if(VARIABLE==2){
            dx[0][CID][CNUM[CID]][i]=dx[1][CID][CNUM[CID]][i]=PAIR[NUM].X_IM_PIXEL[i];
        }else if(VARIABLE==3){
            dx[0][CID][CNUM[CID]][i]=dx[1][CID][CNUM[CID]][i]=PAIR[NUM].X_CRPIX[i];
        }else if(VARIABLE==4){
            dx[0][CID][CNUM[CID]][i]=dx[1][CID][CNUM[CID]][i]=PAIR[NUM].X_GLOBAL[i];
        }else if(VARIABLE==5){
            dx[0][CID][CNUM[CID]][i]=dx[1][CID][CNUM[CID]][i]=PAIR[NUM].X_LOCAL[i];
        }else if(VARIABLE==6){
            dx[0][CID][CNUM[CID]][i]=dx[1][CID][CNUM[CID]][i]=PAIR[NUM].X_CENTER_GLOBAL[i];
        }else if(VARIABLE==7){
            dx[0][CID][CNUM[CID]][i]=dx[1][CID][CNUM[CID]][i]=PAIR[NUM].X_CENTER_IM_WORLD[i];
        }

        for(i=0;i<2;i++)
	      if(FUNCTION==0){
            dx[i][CID][CNUM[CID]][2]=PAIR[NUM].X_RADEC[i];
        }else if(FUNCTION==1){
            dx[i][CID][CNUM[CID]][2]=PAIR[NUM].X_IM_WORLD[i];
        }else if(FUNCTION==2){
            dx[i][CID][CNUM[CID]][2]=PAIR[NUM].X_IM_PIXEL[i];
        }else if(FUNCTION==3){
            dx[i][CID][CNUM[CID]][2]=PAIR[NUM].X_CRPIX[i];
        }else if(FUNCTION==4){
            dx[i][CID][CNUM[CID]][2]=PAIR[NUM].X_GLOBAL[i];
        }else if(FUNCTION==5){
            dx[i][CID][CNUM[CID]][2]=PAIR[NUM].X_LOCAL[i];
        }else if(FUNCTION==6){
            dx[i][CID][CNUM[CID]][2]=PAIR[NUM].CAMERA_CONVROT[i];
        }else if(FUNCTION==7){
            dx[i][CID][CNUM[CID]][2]=PAIR[NUM].CAMERA_SHEAR[i];
        }
        CNUM[CID]++;
    }
    for(CID=0;CID<CCDNUM;CID++)
    for(i=0;i<2;i++)
    F_LS2(CNUM[CID],SIP_L_ORDER,dx[i][CID],TLCoef[i][CID]);

//--------------------------------------------------*/
    F_DELint1(CNUM);
    F_DELdouble4(2,CCDNUM,ALLREFNUM,dx);
}
void CL_APAIR::F_WCSA_APAIR_CALCRMS(int ORDER,int VARIABLE,int FUNCTION){
    int i,NUM,FNUM=0;
    double ***dx,**data;

//--------------------------------------------------
    dx = F_NEWdouble3(2,ALLREFNUM,3);
    data = F_NEWdouble2(2,ALLREFNUM);
//--------------------------------------------------

    F_WCSA_APAIR_GFITTING(ORDER,VARIABLE,FUNCTION,TCoef);

    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG == 1){
            for(i=0;i<2;i++)
	      if(VARIABLE==0){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_RADEC[i];
        }else if(VARIABLE==1){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_IM_WORLD[i];
        }else if(VARIABLE==2){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_IM_PIXEL[i];
        }else if(VARIABLE==3){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_CRPIX[i];
        }else if(VARIABLE==4){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_GLOBAL[i];
        }else if(VARIABLE==5){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_LOCAL[i];
        }else if(VARIABLE==6){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_CENTER_GLOBAL[i];
        }else if(VARIABLE==7){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_CENTER_IM_WORLD[i];
        }else if(VARIABLE==10){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_CENTER_GLOBAL[i];
        }else if(VARIABLE==11){
            dx[0][FNUM][i]=dx[1][FNUM][i]=PAIR[NUM].X_CENTER_RADEC[i];
        }
            for(i=0;i<2;i++)
	      if(FUNCTION==0){
            dx[i][FNUM][2]=PAIR[NUM].X_RADEC[i];
        }else if(FUNCTION==1){
            dx[i][FNUM][2]=PAIR[NUM].X_IM_WORLD[i];
        }else if(FUNCTION==2){
            dx[i][FNUM][2]=PAIR[NUM].X_IM_PIXEL[i];
        }else if(FUNCTION==3){
            dx[i][FNUM][2]=PAIR[NUM].X_CRPIX[i];
        }else if(FUNCTION==4){
            dx[i][FNUM][2]=PAIR[NUM].X_GLOBAL[i];
        }else if(FUNCTION==5){
            dx[i][FNUM][2]=PAIR[NUM].X_LOCAL[i];
        }else if(FUNCTION==6){
            dx[i][FNUM][2]=PAIR[NUM].CAMERA_CONVROT[i];
        }else if(FUNCTION==7){
            dx[i][FNUM][2]=PAIR[NUM].CAMERA_SHEAR[i];
        }else if(FUNCTION==10){
            dx[i][FNUM][2]=PAIR[NUM].X_CENTER_GLOBAL[i];
        }else if(FUNCTION==11){
            dx[i][FNUM][2]=PAIR[NUM].X_CENTER_RADEC[i];
        }
        FNUM++;
    }

//--------------------------------------------------
    for(NUM=0;NUM<FNUM;NUM++){
        data[0][NUM]=dx[0][NUM][2]-F_CALCVALUE(ORDER,TCoef[0],dx[0][NUM]);
        data[1][NUM]=dx[1][NUM][2]-F_CALCVALUE(ORDER,TCoef[1],dx[1][NUM]);
    }
    F_RMS(FNUM,data[0],AVERMS[0]);
    F_RMS(FNUM,data[1],AVERMS[1]);
//--------------------------------------------------
    F_DELdouble3(2,ALLREFNUM,dx);
    F_DELdouble2(2,data);
}
void CL_APAIR::F_WCSA_APAIR_SETCDSIP(){
    CD[0][0]=CDSIP_AB[0][1*(SIP_ORDER+1)+0];
    CD[0][1]=CDSIP_AB[0][0*(SIP_ORDER+1)+1];
    CD[1][0]=CDSIP_AB[1][1*(SIP_ORDER+1)+0];
    CD[1][1]=CDSIP_AB[1][0*(SIP_ORDER+1)+1]; 
    ANGLE=atan2(CD[1][0]-(-1)*CD[0][1],(-1)*CD[0][0]+CD[1][1]);

    InvCD[0][0]= CD[1][1]/(CD[0][0]*CD[1][1]-CD[1][0]*CD[0][1]);
    InvCD[0][1]=-CD[0][1]/(CD[0][0]*CD[1][1]-CD[1][0]*CD[0][1]);
    InvCD[1][0]=-CD[1][0]/(CD[0][0]*CD[1][1]-CD[1][0]*CD[0][1]);
    InvCD[1][1]= CD[0][0]/(CD[0][0]*CD[1][1]-CD[1][0]*CD[0][1]);

    int i,j,ij;
    ij=0;
    for(i=0;i<SIP_ORDER+1;i++)
    for(j=0;j<SIP_ORDER+1;j++)
    if(i+j<SIP_ORDER+1){
        SIP_AB[0][ij]=InvCD[0][0]*CDSIP_AB[0][ij]+InvCD[0][1]*CDSIP_AB[1][ij];
        SIP_AB[1][ij]=InvCD[1][0]*CDSIP_AB[0][ij]+InvCD[1][1]*CDSIP_AB[1][ij];
        ij++;	
    }
    SIP_AB[0][1*(SIP_ORDER+1)+0]-=1.0;
    SIP_AB[1][0*(SIP_ORDER+1)+1]-=1.0;
}
void CL_APAIR::F_WCSA_APAIR_SETCDPSIP(){
/*    int i,j,ij;
    ij=0;
    for(i=0;i<SIP_P_ORDER+1;i++)
    for(j=0;j<SIP_P_ORDER+1;j++)
    if(i+j<SIP_P_ORDER+1){
        SIP_ABP[0][ij]=CDSIP_ABP[0][ij];
        SIP_ABP[1][ij]=CDSIP_ABP[1][ij];
        ij++;	
    }*/
    SIP_ABP[0][1*(SIP_P_ORDER+1)+0]-=1.0;
    SIP_ABP[1][0*(SIP_P_ORDER+1)+1]-=1.0;
}
void CL_APAIR::F_WCSA_APAIR_CALCCONVROTSHEARMAG(){
    int NUM;
    double dGdI[2][2],InvdGdI[2][2],dIdG[2][2],InvdIdG[2][2];

    F_DIFFSIP(SIP_ORDER,SIP_AB[0],TdCoef[0][0],TdCoef[0][1]);
    F_DIFFSIP(SIP_ORDER,SIP_AB[1],TdCoef[1][0],TdCoef[1][1]);
    F_DIFFSIP(SIP_P_ORDER,SIP_ABP[0],TdPCoef[0][0],TdPCoef[0][1]);
    F_DIFFSIP(SIP_P_ORDER,SIP_ABP[1],TdPCoef[1][0],TdPCoef[1][1]);

    for(NUM=0;NUM<ALLREFNUM;NUM++){
        dGdI[0][0]=F_CALCVALUE(SIP_ORDER,TdCoef[0][0],PAIR[NUM].X_CRPIX);
        dGdI[0][1]=F_CALCVALUE(SIP_ORDER,TdCoef[0][1],PAIR[NUM].X_CRPIX);
        dGdI[1][0]=F_CALCVALUE(SIP_ORDER,TdCoef[1][0],PAIR[NUM].X_CRPIX);
        dGdI[1][1]=F_CALCVALUE(SIP_ORDER,TdCoef[1][1],PAIR[NUM].X_CRPIX);
        InvdGdI[0][0]=(1+dGdI[1][1])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0])-1;
        InvdGdI[0][1]=( -dGdI[0][1])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0]);
        InvdGdI[1][0]=( -dGdI[1][0])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0]);
        InvdGdI[1][1]=(1+dGdI[0][0])/((1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0])-1;
        dIdG[0][0]=F_CALCVALUE(SIP_P_ORDER,TdPCoef[0][0],PAIR[NUM].X_IM_PIXEL);
        dIdG[0][1]=F_CALCVALUE(SIP_P_ORDER,TdPCoef[0][1],PAIR[NUM].X_IM_PIXEL);
        dIdG[1][0]=F_CALCVALUE(SIP_P_ORDER,TdPCoef[1][0],PAIR[NUM].X_IM_PIXEL);
        dIdG[1][1]=F_CALCVALUE(SIP_P_ORDER,TdPCoef[1][1],PAIR[NUM].X_IM_PIXEL);
        InvdIdG[0][0]=(1+dIdG[1][1])/((1+dIdG[0][0])*(1+dIdG[1][1])-dIdG[0][1]*dIdG[1][0])-1;
        InvdIdG[0][1]=( -dIdG[0][1])/((1+dIdG[0][0])*(1+dIdG[1][1])-dIdG[0][1]*dIdG[1][0]);
        InvdIdG[1][0]=( -dIdG[1][0])/((1+dIdG[0][0])*(1+dIdG[1][1])-dIdG[0][1]*dIdG[1][0]);
        InvdIdG[1][1]=(1+dIdG[0][0])/((1+dIdG[0][0])*(1+dIdG[1][1])-dIdG[0][1]*dIdG[1][0])-1;

        PAIR[NUM].CAMERA_PCONVROT[0]   =0.5*(1+dIdG[0][0]+1+dIdG[1][1]);
        PAIR[NUM].CAMERA_PCONVROT[1]   =0.5*(  dIdG[0][1]-  dIdG[1][0]);
        PAIR[NUM].CAMERA_PSHEAR[0]     =0.5*(  dIdG[0][0]-  dIdG[1][1]);
        PAIR[NUM].CAMERA_PSHEAR[1]     =0.5*(  dIdG[0][1]+  dIdG[1][0]);
        PAIR[NUM].CAMERA_PMAGNIFICATION=(PAIR[NUM].CAMERA_PCONVROT[0]*PAIR[NUM].CAMERA_PCONVROT[0]-(PAIR[NUM].CAMERA_PSHEAR[0]*PAIR[NUM].CAMERA_PSHEAR[0]+PAIR[NUM].CAMERA_PSHEAR[1]*PAIR[NUM].CAMERA_PSHEAR[1]));
        PAIR[NUM].CAMERA_PJACOBIAN     =(1+dIdG[0][0])*(1+dIdG[1][1])-dIdG[0][1]*dIdG[1][0];
        PAIR[NUM].CAMERA_PPIXELAREA    =(1+InvdIdG[0][0])*(1+InvdIdG[1][1])-InvdIdG[0][1]*InvdIdG[1][0];

        PAIR[NUM].CAMERA_CONVROT[0]    =0.5*(1+InvdGdI[0][0]+1+InvdGdI[1][1]);
        PAIR[NUM].CAMERA_CONVROT[1]    =0.5*(  InvdGdI[0][1]-  InvdGdI[1][0]);
        PAIR[NUM].CAMERA_SHEAR[0]      =0.5*(  InvdGdI[0][0]-  InvdGdI[1][1]);
        PAIR[NUM].CAMERA_SHEAR[1]      =0.5*(  InvdGdI[0][1]+  InvdGdI[1][0]);
        PAIR[NUM].CAMERA_MAGNIFICATION =PAIR[NUM].CAMERA_CONVROT[0]*PAIR[NUM].CAMERA_CONVROT[0]-(PAIR[NUM].CAMERA_SHEAR[0]*PAIR[NUM].CAMERA_SHEAR[0]+PAIR[NUM].CAMERA_SHEAR[1]*PAIR[NUM].CAMERA_SHEAR[1]);
        PAIR[NUM].CAMERA_JACOBIAN      =(1+InvdGdI[0][0])*(1+InvdGdI[1][1])-InvdGdI[0][1]*InvdGdI[1][0];
        PAIR[NUM].CAMERA_PIXELAREA     =(1+dGdI[0][0])*(1+dGdI[1][1])-dGdI[0][1]*dGdI[1][0];
    }

}
void CL_APAIR::F_WCSA_APAIR_CHANGEVARIABLE(int ORDER, double SR[2][2], double* F, double* G){
	int i,j,k,l,m;
	double ***M;//X'=M*X
	double ***N;
	double **TF,**TG;

	TF=F_NEWdouble2(ORDER+1,ORDER+1);
	TG=F_NEWdouble2(ORDER+1,ORDER+1);
	M = new double**[ORDER+1];
	for(i=0;i<ORDER+1;i++)
	M[i]=F_NEWdouble2(i+1,i+1);
	N = new double**[ORDER+1];
	for(i=0;i<ORDER+1;i++)
	N[i]=F_NEWdouble2(i+1,i+1);
//--------------------------------------------------
	k=0;
        for(i=0;i<ORDER+1;i++)
        for(j=0;j<ORDER+1;j++)
	if(i+j<ORDER+1){
		TF[i][j]=F[k];
		k++;
	}

//--------------------------------------------------
	M[0][0][0]=1;
	N[0][0][0]=1;
	for(i=1;i<ORDER+1;i++)
	for(j=0;j<i;j++)
	for(k=0;k<i;k++)
	for(l=0;l<2;l++)
	for(m=0;m<2;m++)
	M[i][j+l][k+m]+=M[i-1][j][k]*SR[l][m];

	for(i=1;i<ORDER+1;i++)
	for(j=0;j<i;j++)
	for(l=0;l<2;l++)
	N[i][j+l][0]+=N[i-1][j][0];
	
	for(i=1;i<ORDER+1;i++)
	for(j=0;j<i+1;j++)
	for(k=0;k<i+1;k++)
	M[i][j][k]/=N[i][j][0];

	for(i=0;i<ORDER+1;i++)
	for(j=0;j<i+1;j++)
	for(k=0;k<i+1;k++)
	TG[i-j][j]+=M[i][j][k]*TF[i-k][k];

//--------------------------------------------------
	k=0;
        for(i=0;i<ORDER+1;i++)
        for(j=0;j<ORDER+1;j++)
	if(i+j<ORDER+1){
		G[k]=TG[i][j];
		k++;
	}

//--------------------------------------------------
	F_DELdouble2(ORDER+1,TF);
	F_DELdouble2(ORDER+1,TG);
	for(i=0;i<ORDER+1;i++){
	F_DELdouble2(i+1,M[i]);
	F_DELdouble2(i+1,N[i]);
	}
	delete [] M;
	delete [] N;
}
void CL_APAIR::F_WCSA_APAIR_CALCSIPRMS(){
    int NUM,FNUM=0;
    double **data,MAXDIFF[2];

//--------------------------------------------------
    data = F_NEWdouble2(2,ALLREFNUM);
//--------------------------------------------------
    FNUM=0;
    MAXDIFF[0]=MAXDIFF[1]=0;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG == 1){
        data[0][FNUM]=PAIR[NUM].X_IM_PIXEL[0]-PAIR[NUM].X_SIP_IM_PIXEL[0];
        data[1][FNUM]=PAIR[NUM].X_IM_PIXEL[1]-PAIR[NUM].X_SIP_IM_PIXEL[1];
        if(fabs(MAXDIFF[0])<fabs(data[0][FNUM]))
	MAXDIFF[0]=data[0][FNUM];
        if(fabs(MAXDIFF[1])<fabs(data[1][FNUM]))
	MAXDIFF[1]=data[1][FNUM];
        FNUM++;
    }
    F_RMS(FNUM,data[0],SIPRMS[0]);
    F_RMS(FNUM,data[1],SIPRMS[1]);
    SIPRMS[0][2]=MAXDIFF[0];
    SIPRMS[1][2]=MAXDIFF[1];
//--------------------------------------------------
    F_DELdouble2(2,data);
}
void CL_APAIR::F_WCSA_APAIR_CALCPSIPRMS(){
    int NUM,FNUM=0;
    double **data,MAXDIFF[2];

//--------------------------------------------------
    data = F_NEWdouble2(2,ALLREFNUM);
//--------------------------------------------------
    FNUM=0;
    MAXDIFF[0]=MAXDIFF[1]=0;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG == 1){
        data[0][FNUM]=PAIR[NUM].X_GLOBALCRPIX[0]-PAIR[NUM].X_PSIP_GLOBALCRPIX[0];
        data[1][FNUM]=PAIR[NUM].X_GLOBALCRPIX[1]-PAIR[NUM].X_PSIP_GLOBALCRPIX[1];
        if(fabs(MAXDIFF[0])<fabs(data[0][FNUM]))
	MAXDIFF[0]=data[0][FNUM];
        if(fabs(MAXDIFF[1])<fabs(data[1][FNUM]))
	MAXDIFF[1]=data[1][FNUM];
        FNUM++;
    }
    F_RMS(FNUM,data[0],PSIPRMS[0]);
    F_RMS(FNUM,data[1],PSIPRMS[1]);
    PSIPRMS[0][2]=MAXDIFF[0];
    PSIPRMS[1][2]=MAXDIFF[1];
//--------------------------------------------------
    F_DELdouble2(2,data);
}
void CL_APAIR::F_WCSA_APAIR_LDIFFVALUES(){
    int CID,NUM;

    F_WCSA_APAIR_LFITTING(7,5);//InvCD=unit
    for(CID=0;CID<CCDNUM;CID++){
        F_DIFFSIP(SIP_L_ORDER,TLCoef[0][CID],TdLCoef[0][0][CID],TdLCoef[0][1][CID]);
        F_DIFFSIP(SIP_L_ORDER,TLCoef[1][CID],TdLCoef[1][0][CID],TdLCoef[1][1][CID]);
    }

    for(NUM=0;NUM<ALLREFNUM;NUM++){
        CID=PAIR[NUM].CHIPID;
        PAIR[NUM].dxLdxI=F_CALCVALUE(SIP_L_ORDER,TdLCoef[0][0][CID],PAIR[NUM].X_CENTER_IM_WORLD);
        PAIR[NUM].dxLdyI=F_CALCVALUE(SIP_L_ORDER,TdLCoef[0][1][CID],PAIR[NUM].X_CENTER_IM_WORLD);
        PAIR[NUM].dyLdxI=F_CALCVALUE(SIP_L_ORDER,TdLCoef[1][0][CID],PAIR[NUM].X_CENTER_IM_WORLD);
        PAIR[NUM].dyLdyI=F_CALCVALUE(SIP_L_ORDER,TdLCoef[1][1][CID],PAIR[NUM].X_CENTER_IM_WORLD);
    }
}
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_T(){
    int CID,TCHECK;
    double *Tcheck;
    
    Tcheck = F_NEWdouble1(CCDNUM);
//--------------------------------------------------

    for(IterNUM_T=0;IterNUM_T<20;IterNUM_T++){
        for(CID=0;CID<CCDNUM;CID++)
        Tcheck[CID]=GPOS[CID][2];

        F_WCSA_APAIR_GDIFFVALUES();
//        F_WCSA_APAIR_CCDPOSITIONS_T_MAT();
F_WCSA_APAIR_CCDPOSITIONS_T_MAT2();


        TCHECK=0;
        for(CID=0;CID<CCDNUM;CID++)
        if(fabs(Tcheck[CID]-GPOS[CID][2])>1e-5)
        TCHECK++;

        if(TCHECK==0)
        break;

/*for(CID=0;CID<CCDNUM;CID++)
GPOS[CID][2]=0;
GPOS_AVE[2]=0;
break;
*/    }
    GPOS_AVE[2]=0;
    int AVENUM=0;
    for(CID=0;CID<CCDNUM;CID++)
    if(CID<100){
        GPOS_AVE[2]+=GPOS[CID][2];
        AVENUM++;
    }
    GPOS_AVE[2]/=AVENUM;
//--------------------------------------------------
    F_DELdouble1(Tcheck);
}

void CL_APAIR::F_WCSA_APAIR_GDIFFVALUES(){
//Calculating dxG/dxI and Zxx
    int NUM,FNUM;
    double ****dGdI;
    dGdI  = F_NEWdouble4(2,2,ALLREFNUM,3);

    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].dxGdxI=PAIR[NUM].dxLdxI*cos(GPOS[PAIR[NUM].CHIPID][2])-PAIR[NUM].dyLdxI*sin(GPOS[PAIR[NUM].CHIPID][2]);
        PAIR[NUM].dyGdxI=PAIR[NUM].dyLdxI*cos(GPOS[PAIR[NUM].CHIPID][2])+PAIR[NUM].dxLdxI*sin(GPOS[PAIR[NUM].CHIPID][2]);
        PAIR[NUM].dxGdyI=PAIR[NUM].dxLdyI*cos(GPOS[PAIR[NUM].CHIPID][2])-PAIR[NUM].dyLdyI*sin(GPOS[PAIR[NUM].CHIPID][2]);
        PAIR[NUM].dyGdyI=PAIR[NUM].dyLdyI*cos(GPOS[PAIR[NUM].CHIPID][2])+PAIR[NUM].dxLdyI*sin(GPOS[PAIR[NUM].CHIPID][2]);
    }
    FNUM=0;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG==1){
        dGdI[0][0][FNUM][0]=dGdI[0][1][FNUM][0]=dGdI[1][0][FNUM][0]=dGdI[1][1][FNUM][0]=PAIR[NUM].X_CENTER_IM_WORLD[0];
        dGdI[0][0][FNUM][1]=dGdI[0][1][FNUM][1]=dGdI[1][0][FNUM][1]=dGdI[1][1][FNUM][1]=PAIR[NUM].X_CENTER_IM_WORLD[1];
        dGdI[0][0][FNUM][2]=PAIR[NUM].dxGdxI;
        dGdI[1][0][FNUM][2]=PAIR[NUM].dyGdxI;
        dGdI[0][1][FNUM][2]=PAIR[NUM].dxGdyI;
        dGdI[1][1][FNUM][2]=PAIR[NUM].dyGdyI;
        FNUM++;
    }

    #pragma omp parallel num_threads(4)
    #pragma omp sections
    {
        #pragma omp section
        {
            F_LS2(FNUM,SIP_P_ORDER-1,dGdI[0][0],TdPCoef[0][0]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,SIP_P_ORDER-1,dGdI[0][1],TdPCoef[0][1]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,SIP_P_ORDER-1,dGdI[1][0],TdPCoef[1][0]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,SIP_P_ORDER-1,dGdI[1][1],TdPCoef[1][1]);
        }
    }

    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].Zxx=PAIR[NUM].Zxy=PAIR[NUM].Zyx=PAIR[NUM].Zyy=0;
        PAIR[NUM].Zxx=F_CALCVALUE(SIP_P_ORDER-1,TdPCoef[0][0],PAIR[NUM].X_CENTER_IM_WORLD);
        PAIR[NUM].Zxy=F_CALCVALUE(SIP_P_ORDER-1,TdPCoef[0][1],PAIR[NUM].X_CENTER_IM_WORLD);
        PAIR[NUM].Zyx=F_CALCVALUE(SIP_P_ORDER-1,TdPCoef[1][0],PAIR[NUM].X_CENTER_IM_WORLD);
        PAIR[NUM].Zyy=F_CALCVALUE(SIP_P_ORDER-1,TdPCoef[1][1],PAIR[NUM].X_CENTER_IM_WORLD);
//if(NUM<100)
//cout <<fixed<< PAIR[NUM].X_CENTER_IM_WORLD[0] << "	" << PAIR[NUM].dxGdxI << "	" <<PAIR[NUM].Zxx << endl;
//cout.unsetf(ios::fixed);
    }

//--------------------------------------------------
    F_DELdouble4(2,2,ALLREFNUM,dGdI);
}
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_T_MAT(){
    int i,j,ij,k,l,kl,CID,CID2,NUM,dCoefNUM;
    double *MA,**MB,**InvMB,*MC;

    dCoefNUM=(int)(0.5*(SIP_P_ORDER+1-1)*(SIP_P_ORDER+2-1)+0.5);

       MA = F_NEWdouble1(CCDNUM+4*dCoefNUM);
       MB = F_NEWdouble2(CCDNUM+4*dCoefNUM,CCDNUM+4*dCoefNUM);
    InvMB = F_NEWdouble2(CCDNUM+4*dCoefNUM,CCDNUM+4*dCoefNUM);
       MC = F_NEWdouble1(CCDNUM+4*dCoefNUM);
//--------------------------------------------------
//dA1
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG==1){
        MA[PAIR[NUM].CHIPID]-= PAIR[NUM].dyGdxI*PAIR[NUM].Zxx;
        MA[PAIR[NUM].CHIPID]-=-PAIR[NUM].dxGdxI*PAIR[NUM].Zyx;
        MA[PAIR[NUM].CHIPID]-= PAIR[NUM].dyGdyI*PAIR[NUM].Zxy;
        MA[PAIR[NUM].CHIPID]-=-PAIR[NUM].dxGdyI*PAIR[NUM].Zyy;
    }
//--------------------------------------------------
//dA2
    ij=0;
    for(i=0;i<SIP_P_ORDER+1-1;i++)
    for(j=0;j<SIP_P_ORDER+1-1;j++)
    if(i+j<SIP_P_ORDER+1-1){
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1){
            MA[CCDNUM+0*dCoefNUM+ij]+=(PAIR[NUM].dxGdxI-PAIR[NUM].Zxx)*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MA[CCDNUM+1*dCoefNUM+ij]+=(PAIR[NUM].dyGdxI-PAIR[NUM].Zyx)*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MA[CCDNUM+2*dCoefNUM+ij]+=(PAIR[NUM].dxGdyI-PAIR[NUM].Zxy)*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MA[CCDNUM+3*dCoefNUM+ij]+=(PAIR[NUM].dyGdyI-PAIR[NUM].Zyy)*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
        }
    ij++;
    }
//--------------------------------------------------
//dB11
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG==1){
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dxGdxI*PAIR[NUM].dxGdxI;
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dyGdxI*PAIR[NUM].dyGdxI;
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dxGdyI*PAIR[NUM].dxGdyI;
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dyGdyI*PAIR[NUM].dyGdyI;
    }
    
//--------------------------------------------------
//dB12
    ij=0;
    for(i=0;i<SIP_P_ORDER+1-1;i++)
    for(j=0;j<SIP_P_ORDER+1-1;j++)
    if(i+j<SIP_P_ORDER+1-1){
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1){
            MB[PAIR[NUM].CHIPID][CCDNUM+0*dCoefNUM+ij]+= PAIR[NUM].dyGdxI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[PAIR[NUM].CHIPID][CCDNUM+1*dCoefNUM+ij]+=-PAIR[NUM].dxGdxI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[PAIR[NUM].CHIPID][CCDNUM+2*dCoefNUM+ij]+= PAIR[NUM].dyGdyI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[PAIR[NUM].CHIPID][CCDNUM+3*dCoefNUM+ij]+=-PAIR[NUM].dxGdyI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
        }
    ij++;
    }
//--------------------------------------------------
//dB21
    ij=0;
    for(i=0;i<SIP_P_ORDER+1-1;i++)
    for(j=0;j<SIP_P_ORDER+1-1;j++)
    if(i+j<SIP_P_ORDER+1-1){
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1){
            MB[CCDNUM+0*dCoefNUM+ij][PAIR[NUM].CHIPID]+= PAIR[NUM].dyGdxI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[CCDNUM+1*dCoefNUM+ij][PAIR[NUM].CHIPID]+=-PAIR[NUM].dxGdxI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[CCDNUM+2*dCoefNUM+ij][PAIR[NUM].CHIPID]+= PAIR[NUM].dyGdyI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[CCDNUM+3*dCoefNUM+ij][PAIR[NUM].CHIPID]+=-PAIR[NUM].dxGdyI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
        }
    ij++;
    }

//--------------------------------------------------
//dB22
    ij=0;
    for(i=0;i<SIP_P_ORDER+1-1;i++)
    for(j=0;j<SIP_P_ORDER+1-1;j++)
    if(i+j<SIP_P_ORDER+1-1){
    kl=0;
    for(k=0;k<SIP_P_ORDER+1-1;k++)
    for(l=0;l<SIP_P_ORDER+1-1;l++)
    if(k+l<SIP_P_ORDER+1-1){
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1){
            MB[CCDNUM+0*dCoefNUM+ij][CCDNUM+0*dCoefNUM+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
            MB[CCDNUM+1*dCoefNUM+ij][CCDNUM+1*dCoefNUM+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
            MB[CCDNUM+2*dCoefNUM+ij][CCDNUM+2*dCoefNUM+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
            MB[CCDNUM+3*dCoefNUM+ij][CCDNUM+3*dCoefNUM+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
        }
    kl++;
    }
    ij++;
    }

//--------------------------------------------------
    F_InvM(CCDNUM+4*dCoefNUM,MB,InvMB);

    for(CID =0;CID <CCDNUM+4*dCoefNUM;CID ++)
    for(CID2=0;CID2<CCDNUM+4*dCoefNUM;CID2++)
    MC[CID]+=InvMB[CID][CID2]*MA[CID2];

    for(CID=0;CID<CCDNUM;CID++)
    GPOS[CID][2]+=MC[CID];

//--------------------------------------------------
    F_DELdouble1(MA);
    F_DELdouble2(CCDNUM+4*dCoefNUM,   MB);
    F_DELdouble2(CCDNUM+4*dCoefNUM,InvMB);
    F_DELdouble1(MC);

}
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_T_MAT2(){
    int i,j,ij,k,l,kl,CID,CID2,NUM,dCoefNUM;
    double *MA,**MB,**InvMB,*MC,***XY;

    dCoefNUM=(int)(0.5*(SIP_P_ORDER+1-1)*(SIP_P_ORDER+2-1)+0.5);

       MA = F_NEWdouble1(CCDNUM+4*dCoefNUM);
       MB = F_NEWdouble2(CCDNUM+4*dCoefNUM,CCDNUM+4*dCoefNUM);
    InvMB = F_NEWdouble2(CCDNUM+4*dCoefNUM,CCDNUM+4*dCoefNUM);
       MC = F_NEWdouble1(CCDNUM+4*dCoefNUM);
       XY = F_NEWdouble3(ALLREFNUM,dCoefNUM+1,dCoefNUM+1);
//--------------------------------------------------
//XY
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    for(i=0;i<SIP_P_ORDER+1-1;i++)
    for(j=0;j<SIP_P_ORDER+1-1;j++)
    if(i+j<SIP_P_ORDER+1-1)
    XY[NUM][i][j] = pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);


//--------------------------------------------------
//dA1
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG==1){
        MA[PAIR[NUM].CHIPID]-= PAIR[NUM].dyGdxI*PAIR[NUM].Zxx;
        MA[PAIR[NUM].CHIPID]-=-PAIR[NUM].dxGdxI*PAIR[NUM].Zyx;
        MA[PAIR[NUM].CHIPID]-= PAIR[NUM].dyGdyI*PAIR[NUM].Zxy;
        MA[PAIR[NUM].CHIPID]-=-PAIR[NUM].dxGdyI*PAIR[NUM].Zyy;
    }
//--------------------------------------------------
//dA2
    ij=0;
    for(i=0;i<SIP_P_ORDER+1-1;i++)
    for(j=0;j<SIP_P_ORDER+1-1;j++)
    if(i+j<SIP_P_ORDER+1-1){
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1){
            MA[CCDNUM+0*dCoefNUM+ij]+=(PAIR[NUM].dxGdxI-PAIR[NUM].Zxx)*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MA[CCDNUM+1*dCoefNUM+ij]+=(PAIR[NUM].dyGdxI-PAIR[NUM].Zyx)*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MA[CCDNUM+2*dCoefNUM+ij]+=(PAIR[NUM].dxGdyI-PAIR[NUM].Zxy)*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MA[CCDNUM+3*dCoefNUM+ij]+=(PAIR[NUM].dyGdyI-PAIR[NUM].Zyy)*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
        }
    ij++;
    }
//--------------------------------------------------
//dB11
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG==1){
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dxGdxI*PAIR[NUM].dxGdxI;
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dyGdxI*PAIR[NUM].dyGdxI;
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dxGdyI*PAIR[NUM].dxGdyI;
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dyGdyI*PAIR[NUM].dyGdyI;
    }
    
//--------------------------------------------------
//dB12
    ij=0;
    for(i=0;i<SIP_P_ORDER+1-1;i++)
    for(j=0;j<SIP_P_ORDER+1-1;j++)
    if(i+j<SIP_P_ORDER+1-1){
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1){
            MB[PAIR[NUM].CHIPID][CCDNUM+0*dCoefNUM+ij]+= PAIR[NUM].dyGdxI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[PAIR[NUM].CHIPID][CCDNUM+1*dCoefNUM+ij]+=-PAIR[NUM].dxGdxI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[PAIR[NUM].CHIPID][CCDNUM+2*dCoefNUM+ij]+= PAIR[NUM].dyGdyI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[PAIR[NUM].CHIPID][CCDNUM+3*dCoefNUM+ij]+=-PAIR[NUM].dxGdyI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
        }
    ij++;
    }
//--------------------------------------------------
//dB21
    ij=0;
    for(i=0;i<SIP_P_ORDER+1-1;i++)
    for(j=0;j<SIP_P_ORDER+1-1;j++)
    if(i+j<SIP_P_ORDER+1-1){
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1){
            MB[CCDNUM+0*dCoefNUM+ij][PAIR[NUM].CHIPID]+= PAIR[NUM].dyGdxI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[CCDNUM+1*dCoefNUM+ij][PAIR[NUM].CHIPID]+=-PAIR[NUM].dxGdxI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[CCDNUM+2*dCoefNUM+ij][PAIR[NUM].CHIPID]+= PAIR[NUM].dyGdyI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
            MB[CCDNUM+3*dCoefNUM+ij][PAIR[NUM].CHIPID]+=-PAIR[NUM].dxGdyI*pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);
        }
    ij++;
    }

//--------------------------------------------------
//dB22
    ij=0;
    for(i=0;i<SIP_P_ORDER+1-1;i++)
    for(j=0;j<SIP_P_ORDER+1-1;j++)
    if(i+j<SIP_P_ORDER+1-1){
    kl=0;
    for(k=0;k<SIP_P_ORDER+1-1;k++)
    for(l=0;l<SIP_P_ORDER+1-1;l++)
    if(k+l<SIP_P_ORDER+1-1){
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1){
            MB[CCDNUM+0*dCoefNUM+ij][CCDNUM+0*dCoefNUM+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
            MB[CCDNUM+1*dCoefNUM+ij][CCDNUM+1*dCoefNUM+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
            MB[CCDNUM+2*dCoefNUM+ij][CCDNUM+2*dCoefNUM+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
            MB[CCDNUM+3*dCoefNUM+ij][CCDNUM+3*dCoefNUM+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
        }
    kl++;
    }
    ij++;
    }

//--------------------------------------------------
    F_InvM(CCDNUM+4*dCoefNUM,MB,InvMB);

    for(CID =0;CID <CCDNUM+4*dCoefNUM;CID ++)
    for(CID2=0;CID2<CCDNUM+4*dCoefNUM;CID2++)
    MC[CID]+=InvMB[CID][CID2]*MA[CID2];

    for(CID=0;CID<CCDNUM;CID++)
    GPOS[CID][2]+=MC[CID];

//--------------------------------------------------
    F_DELdouble1(MA);
    F_DELdouble2(CCDNUM+4*dCoefNUM,   MB);
    F_DELdouble2(CCDNUM+4*dCoefNUM,InvMB);
    F_DELdouble1(MC);
    F_DELdouble3(ALLREFNUM,dCoefNUM+1,XY);

}
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_T_SETAVERAGE(){
    int CID;
    for(CID=0;CID<CCDNUM;CID++)
    GPOS[CID][2]-=GPOS_AVE[2]-BASISPOS[2];
}
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_T_SETAVERAGE_XY(){
    int CID;
    double DX,DY,DT;
    DT=-(GPOS_AVE[2]-BASISPOS[2]);
    for(CID=0;CID<CCDNUM;CID++){
    DX=GPOS[CID][0]*cos(DT)-GPOS[CID][1]*sin(DT);
    DY=GPOS[CID][1]*cos(DT)+GPOS[CID][0]*sin(DT);
    GPOS[CID][0]=DX;
    GPOS[CID][1]=DY;
    GPOS[CID][2]+=DT;
    }
}
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_XY(){
    int i,NUM,FNUM,CID,CoefNUM,dCoefNUM;
    double ****dGdI;

     CoefNUM=(int)(0.5*(SIP_P_ORDER+1  )*(SIP_P_ORDER+2  )+0.5);
    dCoefNUM=(int)(0.5*(SIP_P_ORDER+1-1)*(SIP_P_ORDER+2-1)+0.5);

    dGdI  = F_NEWdouble4(2,2,ALLREFNUM,3);
//--------------------------------------------------

    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].dxGdxI=PAIR[NUM].dxLdxI*cos(GPOS[PAIR[NUM].CHIPID][2])-PAIR[NUM].dyLdxI*sin(GPOS[PAIR[NUM].CHIPID][2]);
        PAIR[NUM].dyGdxI=PAIR[NUM].dyLdxI*cos(GPOS[PAIR[NUM].CHIPID][2])+PAIR[NUM].dxLdxI*sin(GPOS[PAIR[NUM].CHIPID][2]);
        PAIR[NUM].dxGdyI=PAIR[NUM].dxLdyI*cos(GPOS[PAIR[NUM].CHIPID][2])-PAIR[NUM].dyLdyI*sin(GPOS[PAIR[NUM].CHIPID][2]);
        PAIR[NUM].dyGdyI=PAIR[NUM].dyLdyI*cos(GPOS[PAIR[NUM].CHIPID][2])+PAIR[NUM].dxLdyI*sin(GPOS[PAIR[NUM].CHIPID][2]);
    }
    FNUM=0;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG==1){
        dGdI[0][0][FNUM][0]=dGdI[0][1][FNUM][0]=dGdI[1][0][FNUM][0]=dGdI[1][1][FNUM][0]=PAIR[NUM].X_CENTER_IM_WORLD[0];
        dGdI[0][0][FNUM][1]=dGdI[0][1][FNUM][1]=dGdI[1][0][FNUM][1]=dGdI[1][1][FNUM][1]=PAIR[NUM].X_CENTER_IM_WORLD[1];
        dGdI[0][0][FNUM][2]=PAIR[NUM].dxGdxI;
        dGdI[1][0][FNUM][2]=PAIR[NUM].dyGdxI;
        dGdI[0][1][FNUM][2]=PAIR[NUM].dxGdyI;
        dGdI[1][1][FNUM][2]=PAIR[NUM].dyGdyI;
        FNUM++;
    }
    #pragma omp parallel num_threads(4)
    #pragma omp sections
    {
    #pragma omp section
        {
            F_LS2(FNUM,SIP_P_ORDER-1,dGdI[0][0],TdPCoef[0][0]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,SIP_P_ORDER-1,dGdI[0][1],TdPCoef[0][1]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,SIP_P_ORDER-1,dGdI[1][0],TdPCoef[1][0]);
        }
        #pragma omp section
        {
            F_LS2(FNUM,SIP_P_ORDER-1,dGdI[1][1],TdPCoef[1][1]);
        }
    }

//--------------------------------------------------
    for(i=0;i<CoefNUM;i++)
    TPCoef[0][i]=TPCoef[1][i]=0;

    F_INTSIP(SIP_P_ORDER,TdPCoef[0][0],TdPCoef[0][1],TPCoef[0]);
    F_INTSIP(SIP_P_ORDER,TdPCoef[1][0],TdPCoef[1][1],TPCoef[1]);
//--------------------------------------------------
    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].X_CENTER_GLOBAL[0]=F_CALCVALUE(SIP_P_ORDER,TPCoef[0],PAIR[NUM].X_CENTER_IM_WORLD);
        PAIR[NUM].X_CENTER_GLOBAL[1]=F_CALCVALUE(SIP_P_ORDER,TPCoef[1],PAIR[NUM].X_CENTER_IM_WORLD);
    }
//--------------------------------------------------
    double **dX;
    dX = F_NEWdouble2(CCDNUM,3);

    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG==1){
        dX[PAIR[NUM].CHIPID][0]+=1;
        dX[PAIR[NUM].CHIPID][1]+=PAIR[NUM].X_CENTER_GLOBAL[0]-(PAIR[NUM].X_LOCAL[0]*cos(GPOS[PAIR[NUM].CHIPID][2])-PAIR[NUM].X_LOCAL[1]*sin(GPOS[PAIR[NUM].CHIPID][2]));
        dX[PAIR[NUM].CHIPID][2]+=PAIR[NUM].X_CENTER_GLOBAL[1]-(PAIR[NUM].X_LOCAL[1]*cos(GPOS[PAIR[NUM].CHIPID][2])+PAIR[NUM].X_LOCAL[0]*sin(GPOS[PAIR[NUM].CHIPID][2]));
    }

    for(CID=0;CID<CCDNUM;CID++){
        GPOS[CID][0]=dX[CID][1]/dX[CID][0];
        GPOS[CID][1]=dX[CID][2]/dX[CID][0];
    }


//AVERAGE
    GPOS_AVE[0]=GPOS_AVE[1]=0;
    int AVENUM=0;
    for(CID=0;CID<CCDNUM;CID++)
    if(CID<100){
        GPOS_AVE[0]+=GPOS[CID][0];
        GPOS_AVE[1]+=GPOS[CID][1];
        AVENUM++;
    }
    GPOS_AVE[0]/=AVENUM;
    GPOS_AVE[1]/=AVENUM;
//--------------------------------------------------
    F_DELdouble4(2,2,ALLREFNUM,dGdI);
    F_DELdouble2(CCDNUM,dX);
}
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_XY_CORRECTION(){
    int i,j,ij,k,l,kl,CID,CID2,NUM,CoefNUM;
    double *MAX,**MBX,**InvMBX,*MCX;
    double *MAY,**MBY,**InvMBY,*MCY;
    double **Coef,***XY;



    CoefNUM=(int)(0.5*(SIP_P_ORDER+1)*(SIP_P_ORDER+2)+0.5);
      Coef = F_NEWdouble2(2,CoefNUM);
       MAX = F_NEWdouble1(CCDNUM+CoefNUM-1);
       MBX = F_NEWdouble2(CCDNUM+CoefNUM-1,CCDNUM+CoefNUM-1);
    InvMBX = F_NEWdouble2(CCDNUM+CoefNUM-1,CCDNUM+CoefNUM-1);
       MCX = F_NEWdouble1(CCDNUM+CoefNUM-1);
       MAY = F_NEWdouble1(CCDNUM+CoefNUM-1);
       MBY = F_NEWdouble2(CCDNUM+CoefNUM-1,CCDNUM+CoefNUM-1);
    InvMBY = F_NEWdouble2(CCDNUM+CoefNUM-1,CCDNUM+CoefNUM-1);
       MCY = F_NEWdouble1(CCDNUM+CoefNUM-1);
        XY = F_NEWdouble3(ALLREFNUM,CoefNUM+1,CoefNUM+1);

    int XYLOOP,ENDFLAG;
    double **XYINIT,chi2;
    XYINIT=F_NEWdouble2(CCDNUM,2);

    for(CID =0;CID <CCDNUM;CID ++){
        XYINIT[CID][0]=GPOS[CID][0];
        XYINIT[CID][1]=GPOS[CID][1];
    }
    
    for(XYLOOP=0;XYLOOP<10;XYLOOP++){
        F_WCSA_APAIR_SETXG();    
        F_WCSA_APAIR_CENTERofOBJECTS();
        F_WCSA_APAIR_CENTERPROJECTION();
//--------------------------------------------------
        F_WCSA_APAIR_GFITTING(SIP_P_ORDER,7,10,Coef);
        for(NUM=0;NUM<ALLREFNUM;NUM++){
            PAIR[NUM].XYGx=F_CALCVALUE(SIP_P_ORDER,Coef[0],PAIR[NUM].X_CENTER_IM_WORLD);
            PAIR[NUM].XYGy=F_CALCVALUE(SIP_P_ORDER,Coef[1],PAIR[NUM].X_CENTER_IM_WORLD);
//cout <<scientific<<GPOS[PAIR[NUM].CHIPID][0]<<"	"<<GPOS[PAIR[NUM].CHIPID][1]<<"	"<<GPOS[PAIR[NUM].CHIPID][2]<<"	"<< PAIR[NUM].X_CENTER_GLOBAL[0] << "	" << PAIR[NUM].X_CENTER_GLOBAL[1] << "	" <<PAIR[NUM].XYGx << "	" << PAIR[NUM].XYGy << endl;
        }
//--------------------------------------------------
//XY
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1)
        XY[NUM][i][j] = pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);

//--------------------------------------------------
        for(CID =0;CID <CCDNUM+CoefNUM-1;CID ++){
        MAX[CID]=MAY[CID]=MCX[CID]=MCY[CID]=0;
        for(CID2=0;CID2<CCDNUM+CoefNUM-1;CID2++){
        MBX[CID][CID2]=MBY[CID][CID2]=InvMBX[CID][CID2]=InvMBY[CID][CID2]=0;
        }}
//--------------------------------------------------
//dA1
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1){
            MAX[PAIR[NUM].CHIPID]-=(PAIR[NUM].X_CENTER_GLOBAL[0]-PAIR[NUM].XYGx);
            MAY[PAIR[NUM].CHIPID]-=(PAIR[NUM].X_CENTER_GLOBAL[1]-PAIR[NUM].XYGy);
        }
//--------------------------------------------------
//dA2
        ij=0;
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1&&i+j!=0){
            for(NUM=0;NUM<ALLREFNUM;NUM++)
            if(PAIR[NUM].FLAG==1){
            MAX[CCDNUM+ij]+=(PAIR[NUM].X_CENTER_GLOBAL[0]-PAIR[NUM].XYGx)*XY[NUM][i][j];
            MAY[CCDNUM+ij]+=(PAIR[NUM].X_CENTER_GLOBAL[1]-PAIR[NUM].XYGy)*XY[NUM][i][j];
            }
        ij++;
        }
//--------------------------------------------------
//dB11
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1&&i+j!=0){
            MBX[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=1;
            MBY[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=1;
        }
    
//--------------------------------------------------
//dB12
        ij=0;
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1&&i+j!=0){
            for(NUM=0;NUM<ALLREFNUM;NUM++)
            if(PAIR[NUM].FLAG==1){
                MBX[PAIR[NUM].CHIPID][CCDNUM+ij]-=XY[NUM][i][j];
                MBY[PAIR[NUM].CHIPID][CCDNUM+ij]-=XY[NUM][i][j];
            }
        ij++;
        }
//--------------------------------------------------
//dB21
        ij=0;
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1&&i+j!=0){
            for(NUM=0;NUM<ALLREFNUM;NUM++)
            if(PAIR[NUM].FLAG==1){
                MBX[CCDNUM+ij][PAIR[NUM].CHIPID]-=XY[NUM][i][j];
                MBY[CCDNUM+ij][PAIR[NUM].CHIPID]-=XY[NUM][i][j];
            }
        ij++;
        }

//--------------------------------------------------
//dB22
        ij=0;
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1&&i+j!=0){
        kl=0;
        for(k=0;k<SIP_P_ORDER+1;k++)
        for(l=0;l<SIP_P_ORDER+1;l++)
        if(k+l<SIP_P_ORDER+1&&k+l!=0){
            for(NUM=0;NUM<ALLREFNUM;NUM++)
            if(PAIR[NUM].FLAG==1){
                MBX[CCDNUM+ij][CCDNUM+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
                MBY[CCDNUM+ij][CCDNUM+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
            }
        kl++;
        }
        ij++;
        }

//--------------------------------------------------
        F_InvM(CCDNUM+CoefNUM-1,MBX,InvMBX);
        F_InvM(CCDNUM+CoefNUM-1,MBY,InvMBY);

        for(CID =0;CID <CCDNUM+CoefNUM-1;CID ++)
        for(CID2=0;CID2<CCDNUM+CoefNUM-1;CID2++){
            MCX[CID]+=InvMBX[CID][CID2]*MAX[CID2];
            MCY[CID]+=InvMBY[CID][CID2]*MAY[CID2];
        }

        for(CID=0;CID<CCDNUM;CID++){
            GPOS[CID][0]+=MCX[CID];
            GPOS[CID][1]+=MCY[CID];
        }
        GPOS_AVE[0]=GPOS_AVE[1]=0;
        int AVENUM=0;
        for(CID=0;CID<CCDNUM;CID++)
        if(CID<100){
            GPOS_AVE[0]+=GPOS[CID][0];
            GPOS_AVE[1]+=GPOS[CID][1];
            AVENUM++;
        }
        GPOS_AVE[0]/=AVENUM;
        GPOS_AVE[1]/=AVENUM;
        F_WCSA_APAIR_CCDPOSITIONS_XY_SETAVERAGE();

//--------------------------------------------------
        ENDFLAG=1;
        for(CID =0;CID <CCDNUM;CID ++)
        if(hypot(XYINIT[CID][0]-GPOS[CID][0],XYINIT[CID][1]-GPOS[CID][1])>pow(10.0,-3.0))
        ENDFLAG=0;

        if(ENDFLAG==1){
            break;
        }else{
            if(STDOUT==1||STDOUT==2)
            cout << "XYLOOP = " << XYLOOP+1 << endl;
            for(CID =0;CID <CCDNUM;CID ++){
                XYINIT[CID][0]=GPOS[CID][0];
                XYINIT[CID][1]=GPOS[CID][1];
            }
        }

    }
    F_DELdouble2(2,Coef);
    F_DELdouble1(MAX);
    F_DELdouble2(CCDNUM+CoefNUM-1,   MBY);
    F_DELdouble2(CCDNUM+CoefNUM-1,InvMBY);
    F_DELdouble1(MCX);
    F_DELdouble1(MAY);
    F_DELdouble2(CCDNUM+CoefNUM-1,   MBX);
    F_DELdouble2(CCDNUM+CoefNUM-1,InvMBX);
    F_DELdouble1(MCY);
    F_DELdouble3(ALLREFNUM,CoefNUM+1,XY);
}
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_XYT_CORRECTION(){
    int i,j,ij,k,l,kl,CID,CID2,NUM,CoefNUM;
    double *MAXYT,**MBXYT,**InvMBXYT,*MCXYT;
    double **Coef,***XY,*XLsYLc,*YLsXLc;



    CoefNUM=(int)(0.5*(SIP_P_ORDER+1)*(SIP_P_ORDER+2)+0.5);
        Coef = F_NEWdouble2(2,CoefNUM);
       MAXYT = F_NEWdouble1(3*CCDNUM+2*(CoefNUM-1));
       MBXYT = F_NEWdouble2(3*CCDNUM+2*(CoefNUM-1),3*CCDNUM+2*(CoefNUM-1));
    InvMBXYT = F_NEWdouble2(3*CCDNUM+2*(CoefNUM-1),3*CCDNUM+2*(CoefNUM-1));
       MCXYT = F_NEWdouble1(3*CCDNUM+2*(CoefNUM-1));
          XY = F_NEWdouble3(ALLREFNUM,SIP_P_ORDER+1,SIP_P_ORDER+1);
      XLsYLc = F_NEWdouble1(ALLREFNUM);
      YLsXLc = F_NEWdouble1(ALLREFNUM);

    int XYLOOP,ENDFLAG;
    double **XYINIT,chi2;
    XYINIT=F_NEWdouble2(CCDNUM,3);

    for(CID =0;CID <CCDNUM;CID ++){
        XYINIT[CID][0]=GPOS[CID][0];
        XYINIT[CID][1]=GPOS[CID][1];
        XYINIT[CID][2]=GPOS[CID][2];
    }
    
    for(XYLOOP=0;XYLOOP<10;XYLOOP++){
        F_WCSA_APAIR_SETXG();    
        F_WCSA_APAIR_CENTERofOBJECTS();
        F_WCSA_APAIR_CENTERPROJECTION();
//--------------------------------------------------
        F_WCSA_APAIR_GFITTING(SIP_P_ORDER,7,10,Coef);
        for(NUM=0;NUM<ALLREFNUM;NUM++){
            PAIR[NUM].XYGx=F_CALCVALUE(SIP_P_ORDER,Coef[0],PAIR[NUM].X_CENTER_IM_WORLD);
            PAIR[NUM].XYGy=F_CALCVALUE(SIP_P_ORDER,Coef[1],PAIR[NUM].X_CENTER_IM_WORLD);
//cout <<scientific<<GPOS[PAIR[NUM].CHIPID][0]<<"	"<<GPOS[PAIR[NUM].CHIPID][1]<<"	"<<GPOS[PAIR[NUM].CHIPID][2]<<"	"<< PAIR[NUM].X_CENTER_GLOBAL[0] << "	" << PAIR[NUM].X_CENTER_GLOBAL[1] << "	" <<PAIR[NUM].XYGx << "	" << PAIR[NUM].XYGy << endl;
        }
//--------------------------------------------------
//XY
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1)
        XY[NUM][i][j] = pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j);

        for(NUM=0;NUM<ALLREFNUM;NUM++){
            XLsYLc[NUM]=PAIR[NUM].X_LOCAL[0]*sin(GPOS[PAIR[NUM].CHIPID][2])+PAIR[NUM].X_LOCAL[1]*cos(GPOS[PAIR[NUM].CHIPID][2]);
            YLsXLc[NUM]=PAIR[NUM].X_LOCAL[1]*sin(GPOS[PAIR[NUM].CHIPID][2])-PAIR[NUM].X_LOCAL[0]*cos(GPOS[PAIR[NUM].CHIPID][2]);
        }
//--------------------------------------------------
        for(CID =0;CID <3*CCDNUM+2*(CoefNUM-1);CID ++){
        MAXYT[CID]=MCXYT[CID]=0;
        for(CID2=0;CID2<3*CCDNUM+2*(CoefNUM-1);CID2++){
        MBXYT[CID][CID2]=InvMBXYT[CID][CID2]=0;
        }}
//--------------------------------------------------
//dAXYT
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1){
            MAXYT[0*CCDNUM+PAIR[NUM].CHIPID]-=(PAIR[NUM].X_CENTER_GLOBAL[0]-PAIR[NUM].XYGx);
            MAXYT[1*CCDNUM+PAIR[NUM].CHIPID]-=(PAIR[NUM].X_CENTER_GLOBAL[1]-PAIR[NUM].XYGy);
            MAXYT[2*CCDNUM+PAIR[NUM].CHIPID]-=-XLsYLc[NUM]*(PAIR[NUM].X_CENTER_GLOBAL[0]-PAIR[NUM].XYGx)-YLsXLc[NUM]*(PAIR[NUM].X_CENTER_GLOBAL[1]-PAIR[NUM].XYGy);
        }
//--------------------------------------------------
//dAA
        ij=0;
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1&&i+j!=0){
            for(NUM=0;NUM<ALLREFNUM;NUM++)
            if(PAIR[NUM].FLAG==1){
            MAXYT[3*CCDNUM+0*(CoefNUM-1)+ij]-=-(PAIR[NUM].X_CENTER_GLOBAL[0]-PAIR[NUM].XYGx)*XY[NUM][i][j];
            MAXYT[3*CCDNUM+1*(CoefNUM-1)+ij]-=-(PAIR[NUM].X_CENTER_GLOBAL[1]-PAIR[NUM].XYGy)*XY[NUM][i][j];
            }
        ij++;
        }
//--------------------------------------------------
//dBXYTXYT
        for(NUM=0;NUM<ALLREFNUM;NUM++)
        if(PAIR[NUM].FLAG==1&&i+j!=0){
            MBXYT[0*CCDNUM+PAIR[NUM].CHIPID][0*CCDNUM+PAIR[NUM].CHIPID]+=1;
//          MBXYT[0*CCDNUM+PAIR[NUM].CHIPID][1*CCDNUM+PAIR[NUM].CHIPID]+=0;
            MBXYT[0*CCDNUM+PAIR[NUM].CHIPID][2*CCDNUM+PAIR[NUM].CHIPID]+=-XLsYLc[NUM];
//          MBXYT[1*CCDNUM+PAIR[NUM].CHIPID][0*CCDNUM+PAIR[NUM].CHIPID]+=0;
            MBXYT[1*CCDNUM+PAIR[NUM].CHIPID][1*CCDNUM+PAIR[NUM].CHIPID]+=1;
            MBXYT[1*CCDNUM+PAIR[NUM].CHIPID][2*CCDNUM+PAIR[NUM].CHIPID]+=-YLsXLc[NUM];
            MBXYT[2*CCDNUM+PAIR[NUM].CHIPID][0*CCDNUM+PAIR[NUM].CHIPID]+=-XLsYLc[NUM];
            MBXYT[2*CCDNUM+PAIR[NUM].CHIPID][1*CCDNUM+PAIR[NUM].CHIPID]+=-YLsXLc[NUM];
            MBXYT[2*CCDNUM+PAIR[NUM].CHIPID][2*CCDNUM+PAIR[NUM].CHIPID]+=XLsYLc[NUM]*XLsYLc[NUM]+YLsXLc[NUM]*YLsXLc[NUM];
        }
    
//--------------------------------------------------
//dBXYTA
        ij=0;
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1&&i+j!=0){
            for(NUM=0;NUM<ALLREFNUM;NUM++)
            if(PAIR[NUM].FLAG==1){
                MBXYT[0*CCDNUM+PAIR[NUM].CHIPID][3*CCDNUM+0*(CoefNUM-1)+ij]+=-XY[NUM][i][j];
                MBXYT[1*CCDNUM+PAIR[NUM].CHIPID][3*CCDNUM+1*(CoefNUM-1)+ij]+=-XY[NUM][i][j];
                MBXYT[2*CCDNUM+PAIR[NUM].CHIPID][3*CCDNUM+0*(CoefNUM-1)+ij]+=-XY[NUM][i][j]*(-XLsYLc[NUM]);
                MBXYT[2*CCDNUM+PAIR[NUM].CHIPID][3*CCDNUM+1*(CoefNUM-1)+ij]+=-XY[NUM][i][j]*(-YLsXLc[NUM]);
            }
        ij++;
        }
//--------------------------------------------------
//dBAXYT
        ij=0;
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1&&i+j!=0){
            for(NUM=0;NUM<ALLREFNUM;NUM++)
            if(PAIR[NUM].FLAG==1){
                MBXYT[3*CCDNUM+0*(CoefNUM-1)+ij][0*CCDNUM+PAIR[NUM].CHIPID]+=-XY[NUM][i][j];
                MBXYT[3*CCDNUM+1*(CoefNUM-1)+ij][1*CCDNUM+PAIR[NUM].CHIPID]+=-XY[NUM][i][j];
                MBXYT[3*CCDNUM+0*(CoefNUM-1)+ij][2*CCDNUM+PAIR[NUM].CHIPID]+=-XY[NUM][i][j]*(-XLsYLc[NUM]);
                MBXYT[3*CCDNUM+1*(CoefNUM-1)+ij][2*CCDNUM+PAIR[NUM].CHIPID]+=-XY[NUM][i][j]*(-YLsXLc[NUM]);
            }
        ij++;
        }

//--------------------------------------------------
//dBAA
        ij=0;
        for(i=0;i<SIP_P_ORDER+1;i++)
        for(j=0;j<SIP_P_ORDER+1;j++)
        if(i+j<SIP_P_ORDER+1&&i+j!=0){
        kl=0;
        for(k=0;k<SIP_P_ORDER+1;k++)
        for(l=0;l<SIP_P_ORDER+1;l++)
        if(k+l<SIP_P_ORDER+1&&k+l!=0){
            for(NUM=0;NUM<ALLREFNUM;NUM++)
            if(PAIR[NUM].FLAG==1){
                MBXYT[3*CCDNUM+0*(CoefNUM-1)+ij][3*CCDNUM+0*(CoefNUM-1)+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
//              MBXYT[3*CCDNUM+0*(CoefNUM-1)+ij][3*CCDNUM+1*(CoefNUM-1)+kl]+=0;
//              MBXYT[3*CCDNUM+1*(CoefNUM-1)+ij][3*CCDNUM+0*(CoefNUM-1)+kl]+=0;
                MBXYT[3*CCDNUM+1*(CoefNUM-1)+ij][3*CCDNUM+1*(CoefNUM-1)+kl]+=pow(PAIR[NUM].X_CENTER_IM_WORLD[0],i+k)*pow(PAIR[NUM].X_CENTER_IM_WORLD[1],j+l);
            }
        kl++;
        }
        ij++;
        }

//--------------------------------------------------
        F_InvM(3*CCDNUM+2*(CoefNUM-1),MBXYT,InvMBXYT);

        for(CID =0;CID <3*CCDNUM+2*(CoefNUM-1);CID ++)
        for(CID2=0;CID2<3*CCDNUM+2*(CoefNUM-1);CID2++)
            MCXYT[CID]+=InvMBXYT[CID][CID2]*MAXYT[CID2];

        for(CID=0;CID<CCDNUM;CID++){
            GPOS[CID][0]+=MCXYT[0*CCDNUM+CID];
            GPOS[CID][1]+=MCXYT[1*CCDNUM+CID];
            GPOS[CID][2]+=MCXYT[2*CCDNUM+CID];
        }

//--------------------------------------------------
        GPOS_AVE[0]=GPOS_AVE[1]=GPOS_AVE[2]=0;
        int AVENUM=0;
        for(CID=0;CID<CCDNUM;CID++)
        if(CID<100){
            GPOS_AVE[2]+=GPOS[CID][2];
            AVENUM++;
        }
        GPOS_AVE[2]/=AVENUM;
        F_WCSA_APAIR_CCDPOSITIONS_T_SETAVERAGE_XY();

        AVENUM=0;
        for(CID=0;CID<CCDNUM;CID++)
        if(CID<100){
            GPOS_AVE[0]+=GPOS[CID][0];
            GPOS_AVE[1]+=GPOS[CID][1];
            AVENUM++;
        }
        GPOS_AVE[0]/=AVENUM;
        GPOS_AVE[1]/=AVENUM;
        F_WCSA_APAIR_CCDPOSITIONS_XY_SETAVERAGE();
//--------------------------------------------------
        ENDFLAG=1;
        for(CID =0;CID <CCDNUM;CID ++)
        if(hypot(XYINIT[CID][0]-GPOS[CID][0],XYINIT[CID][1]-GPOS[CID][1])>pow(10.0,-2.0)||fabs(XYINIT[CID][2]-GPOS[CID][2])>pow(10.0,-5.0))
        ENDFLAG=0;

        if(ENDFLAG==1){
            break;
        }else{
            if(STDOUT==1||STDOUT==2)
            cout << "XYLOOP = " << XYLOOP+1 << endl;
            for(CID =0;CID <CCDNUM;CID ++){
                XYINIT[CID][0]=GPOS[CID][0];
                XYINIT[CID][1]=GPOS[CID][1];
                XYINIT[CID][2]=GPOS[CID][2];
            }
        }

    }
    F_DELdouble2(2,Coef);
    F_DELdouble1(MAXYT);
    F_DELdouble2(3*CCDNUM+2*(CoefNUM-1),MBXYT);
    F_DELdouble2(3*CCDNUM+2*(CoefNUM-1),InvMBXYT);
    F_DELdouble1(MCXYT);
    F_DELdouble3(ALLREFNUM,SIP_P_ORDER+1,XY);
    F_DELdouble2(CCDNUM,XYINIT);
    F_DELdouble1(XLsYLc);
    F_DELdouble1(YLsXLc);
}
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_XY_SETAVERAGE(){
    int CID;
    for(CID=0;CID<CCDNUM;CID++){
    GPOS[CID][0]-=GPOS_AVE[0]-(BASISPOS[0]*cos(BASISPOS[2])-BASISPOS[1]*sin(BASISPOS[2]));
    GPOS[CID][1]-=GPOS_AVE[1]-(BASISPOS[1]*cos(BASISPOS[2])+BASISPOS[0]*sin(BASISPOS[2]));
    }
}
//ETC
void CL_APAIR::F_WCSA_APAIR_SHOWAPAIR(){
    cout << "-- APAIR CHECK --" << endl;
    cout.unsetf(ios::fixed);
    cout << "CCDNUM    : " << CCDNUM << endl;
    cout << "CCDPOSMODE: " << CCDPOSMODE << endl;
    cout << "ALLREFNUM : " << ALLREFNUM << endl;
    cout << "ALLFITNUM : " << ALLFITNUM << endl;
    cout << "SIP_LORDER: " << SIP_L_ORDER << endl;
    cout << "SIP_ORDER : " << SIP_ORDER   << endl;
    cout << "SIP_PORDER: " << SIP_P_ORDER << endl;
    cout << "CLIP_SIGMA: " << CLIP_SIGMA << endl;
    cout << "CENTERPIX1: " << CENTER_PIXEL[0] << endl;
    cout << "CENTERPIX2: " << CENTER_PIXEL[1] << endl;
    cout << "CRPIX1    : " << CRPIX[0] << endl;
    cout << "CRPIX2    : " << CRPIX[1] << endl;
    cout << "CRVAL1    : " << CRVAL[0] << endl;
    cout << "CRVAL2    : " << CRVAL[1] << endl;
    cout << "OAPIX1    : " << OAPIX[0] << endl;
    cout << "OAPIX2    : " << OAPIX[1] << endl;
    cout << "OAVAL1    : " << OAVAL[0] << endl;
    cout << "OAVAL2    : " << OAVAL[1] << endl;
    cout << "CD11      : " << CD[0][0] << endl;
    cout << "CD12      : " << CD[0][1] << endl;
    cout << "CD21      : " << CD[1][0] << endl;
    cout << "CD22      : " << CD[1][1] << endl;
    cout << "InvCD11   : " << InvCD[0][0] << endl;
    cout << "InvCD12   : " << InvCD[0][1] << endl;
    cout << "InvCD21   : " << InvCD[1][0] << endl;
    cout << "InvCD22   : " << InvCD[1][1] << endl;
    cout << "ANGLE     : " << ANGLE<< endl;
    cout <<endl;
}
void  CL_APAIR::F_WCSA_APAIR_SHOWCCDPOS(){
    int CID;
        cout << "-- DEFAULT CCD POSITION --" << endl;
    for(CID=0;CID<CCDNUM;CID++){
        cout << GPOS[CID][0] << "	"
             << GPOS[CID][1] << "	"
             << GPOS[CID][2] << endl;
    }
}
void F_SET_SIMCCDPOS(double **GPOS){
//--------------------------------------------------

GPOS[0][0]=    -9514.700;
GPOS[0][1]=       78.000;
GPOS[0][2]=     0.000000;
GPOS[1][0]=     7466.700;
GPOS[1][1]=    -4174.000;
GPOS[1][2]=     0.000000;
GPOS[2][0]=    -7392.000;
GPOS[2][1]=       78.000;
GPOS[2][2]=     0.000000;
GPOS[3][0]=     5344.000;
GPOS[3][1]=    -4174.000;
GPOS[3][2]=     0.000000;
GPOS[4][0]=    -5269.300;
GPOS[4][1]=       78.000;
GPOS[4][2]=     0.000000;
GPOS[5][0]=     3221.300;
GPOS[5][1]=    -4174.000;
GPOS[5][2]=     0.000000;
GPOS[6][0]=    -3146.700;
GPOS[6][1]=       78.000;
GPOS[6][2]=     0.000000;
GPOS[7][0]=     1098.700;
GPOS[7][1]=    -4174.000;
GPOS[7][2]=     0.000000;
GPOS[8][0]=    -1024.000;
GPOS[8][1]=       78.000;
GPOS[8][2]=     0.000000;
GPOS[9][0]=    -1024.000;
GPOS[9][1]=    -4174.000;
GPOS[9][2]=     0.000000;
GPOS[10][0]=     1098.700;
GPOS[10][1]=       78.000;
GPOS[10][2]=     0.000000;
GPOS[11][0]=    -3146.700;
GPOS[11][1]=    -4174.000;
GPOS[11][2]=     0.000000;
GPOS[12][0]=     3221.300;
GPOS[12][1]=       78.000;
GPOS[12][2]=     0.000000;
GPOS[13][0]=    -5269.300;
GPOS[13][1]=    -4174.000;
GPOS[13][2]=     0.000000;
GPOS[14][0]=     5344.000;
GPOS[14][1]=       78.000;
GPOS[14][2]=     0.000000;
GPOS[15][0]=    -7392.000;
GPOS[15][1]=    -4174.000;
GPOS[15][2]=     0.000000;
GPOS[16][0]=     7466.700;
GPOS[16][1]=       78.000;
GPOS[16][2]=     0.000000;
GPOS[17][0]=    -9514.700;
GPOS[17][1]=    -4174.000;
GPOS[17][2]=     0.000000;
GPOS[18][0]=     9589.300;
GPOS[18][1]=       78.000;
GPOS[18][2]=     0.000000;
GPOS[19][0]=   -11637.300;
GPOS[19][1]=    -4174.000;
GPOS[19][2]=     0.000000;
GPOS[20][0]=    11712.000;
GPOS[20][1]=       78.000;
GPOS[20][2]=     0.000000;
GPOS[21][0]=   -13760.000;
GPOS[21][1]=    -4174.000;
GPOS[21][2]=     0.000000;
GPOS[22][0]=    13835.000;
GPOS[22][1]=       78.000;
GPOS[22][2]=     0.000000;
GPOS[23][0]=   -15883.000;
GPOS[23][1]=    -4174.000;
GPOS[23][2]=     0.000000;
GPOS[24][0]=    -9514.700;
GPOS[24][1]=     4546.000;
GPOS[24][2]=     0.000000;
GPOS[25][0]=     7466.700;
GPOS[25][1]=    -8642.000;
GPOS[25][2]=     0.000000;
GPOS[26][0]=    -7392.000;
GPOS[26][1]=     4546.000;
GPOS[26][2]=     0.000000;
GPOS[27][0]=     5344.000;
GPOS[27][1]=    -8642.000;
GPOS[27][2]=     0.000000;
GPOS[28][0]=    -5269.300;
GPOS[28][1]=     4546.000;
GPOS[28][2]=     0.000000;
GPOS[29][0]=     3221.300;
GPOS[29][1]=    -8642.000;
GPOS[29][2]=     0.000000;
GPOS[30][0]=    -3146.700;
GPOS[30][1]=     4546.000;
GPOS[30][2]=     0.000000;
GPOS[31][0]=     1098.700;
GPOS[31][1]=    -8642.000;
GPOS[31][2]=     0.000000;
GPOS[32][0]=    -1024.000;
GPOS[32][1]=     4546.000;
GPOS[32][2]=     0.000000;
GPOS[33][0]=    -1024.000;
GPOS[33][1]=    -8642.000;
GPOS[33][2]=     0.000000;
GPOS[34][0]=     1098.700;
GPOS[34][1]=     4546.000;
GPOS[34][2]=     0.000000;
GPOS[35][0]=    -3146.700;
GPOS[35][1]=    -8642.000;
GPOS[35][2]=     0.000000;
GPOS[36][0]=     3221.300;
GPOS[36][1]=     4546.000;
GPOS[36][2]=     0.000000;
GPOS[37][0]=    -5269.300;
GPOS[37][1]=    -8642.000;
GPOS[37][2]=     0.000000;
GPOS[38][0]=     5344.000;
GPOS[38][1]=     4546.000;
GPOS[38][2]=     0.000000;
GPOS[39][0]=    -7392.000;
GPOS[39][1]=    -8642.000;
GPOS[39][2]=     0.000000;
GPOS[40][0]=     7466.700;
GPOS[40][1]=     4546.000;
GPOS[40][2]=     0.000000;
GPOS[41][0]=    -9514.700;
GPOS[41][1]=    -8642.000;
GPOS[41][2]=     0.000000;
GPOS[42][0]=     9589.300;
GPOS[42][1]=     4546.000;
GPOS[42][2]=     0.000000;
GPOS[43][0]=   -11637.300;
GPOS[43][1]=    -8642.000;
GPOS[43][2]=     0.000000;
GPOS[44][0]=    11712.000;
GPOS[44][1]=     4546.000;
GPOS[44][2]=     0.000000;
GPOS[45][0]=   -13760.000;
GPOS[45][1]=    -8642.000;
GPOS[45][2]=     0.000000;
GPOS[46][0]=    13835.000;
GPOS[46][1]=     4546.000;
GPOS[46][2]=     0.000000;
GPOS[47][0]=   -15883.000;
GPOS[47][1]=    -8642.000;
GPOS[47][2]=     0.000000;
GPOS[48][0]=    -9514.700;
GPOS[48][1]=     9014.000;
GPOS[48][2]=     0.000000;
GPOS[49][0]=     7466.700;
GPOS[49][1]=   -13110.000;
GPOS[49][2]=     0.000000;
GPOS[50][0]=    -7392.000;
GPOS[50][1]=     9014.000;
GPOS[50][2]=     0.000000;
GPOS[51][0]=     5344.000;
GPOS[51][1]=   -13110.000;
GPOS[51][2]=     0.000000;
GPOS[52][0]=    -5269.300;
GPOS[52][1]=     9014.000;
GPOS[52][2]=     0.000000;
GPOS[53][0]=     3221.300;
GPOS[53][1]=   -13110.000;
GPOS[53][2]=     0.000000;
GPOS[54][0]=    -3146.700;
GPOS[54][1]=     9014.000;
GPOS[54][2]=     0.000000;
GPOS[55][0]=     1098.700;
GPOS[55][1]=   -13110.000;
GPOS[55][2]=     0.000000;
GPOS[56][0]=    -1024.000;
GPOS[56][1]=     9014.000;
GPOS[56][2]=     0.000000;
GPOS[57][0]=    -1024.000;
GPOS[57][1]=   -13110.000;
GPOS[57][2]=     0.000000;
GPOS[58][0]=     1098.700;
GPOS[58][1]=     9014.000;
GPOS[58][2]=     0.000000;
GPOS[59][0]=    -3146.700;
GPOS[59][1]=   -13110.000;
GPOS[59][2]=     0.000000;
GPOS[60][0]=     3221.300;
GPOS[60][1]=     9014.000;
GPOS[60][2]=     0.000000;
GPOS[61][0]=    -5269.300;
GPOS[61][1]=   -13110.000;
GPOS[61][2]=     0.000000;
GPOS[62][0]=     5344.000;
GPOS[62][1]=     9014.000;
GPOS[62][2]=     0.000000;
GPOS[63][0]=    -7392.000;
GPOS[63][1]=   -13110.000;
GPOS[63][2]=     0.000000;
GPOS[64][0]=     7466.700;
GPOS[64][1]=     9014.000;
GPOS[64][2]=     0.000000;
GPOS[65][0]=    -9514.700;
GPOS[65][1]=   -13110.000;
GPOS[65][2]=     0.000000;
GPOS[66][0]=     9589.300;
GPOS[66][1]=     9014.000;
GPOS[66][2]=     0.000000;
GPOS[67][0]=   -11637.300;
GPOS[67][1]=   -13110.000;
GPOS[67][2]=     0.000000;
GPOS[68][0]=    11712.000;
GPOS[68][1]=     9014.000;
GPOS[68][2]=     0.000000;
GPOS[69][0]=   -13760.000;
GPOS[69][1]=   -13110.000;
GPOS[69][2]=     0.000000;
GPOS[70][0]=    -7392.000;
GPOS[70][1]=    13483.000;
GPOS[70][2]=     0.000000;
GPOS[71][0]=     5344.000;
GPOS[71][1]=   -17579.000;
GPOS[71][2]=     0.000000;
GPOS[72][0]=    -5269.300;
GPOS[72][1]=    13483.000;
GPOS[72][2]=     0.000000;
GPOS[73][0]=     3221.300;
GPOS[73][1]=   -17579.000;
GPOS[73][2]=     0.000000;
GPOS[74][0]=    -3146.700;
GPOS[74][1]=    13483.000;
GPOS[74][2]=     0.000000;
GPOS[75][0]=     1098.700;
GPOS[75][1]=   -17579.000;
GPOS[75][2]=     0.000000;
GPOS[76][0]=    -1024.000;
GPOS[76][1]=    13483.000;
GPOS[76][2]=     0.000000;
GPOS[77][0]=    -1024.000;
GPOS[77][1]=   -17579.000;
GPOS[77][2]=     0.000000;
GPOS[78][0]=     1098.700;
GPOS[78][1]=    13483.000;
GPOS[78][2]=     0.000000;
GPOS[79][0]=    -3146.700;
GPOS[79][1]=   -17579.000;
GPOS[79][2]=     0.000000;
GPOS[80][0]=     3221.300;
GPOS[80][1]=    13483.000;
GPOS[80][2]=     0.000000;
GPOS[81][0]=    -5269.300;
GPOS[81][1]=   -17579.000;
GPOS[81][2]=     0.000000;
GPOS[82][0]=     5344.000;
GPOS[82][1]=    13483.000;
GPOS[82][2]=     0.000000;
GPOS[83][0]=    -7392.000;
GPOS[83][1]=   -17579.000;
GPOS[83][2]=     0.000000;
GPOS[84][0]=     9589.300;
GPOS[84][1]=    -4390.300;
GPOS[84][2]=     0.000000;
GPOS[85][0]=   -11637.300;
GPOS[85][1]=      294.300;
GPOS[85][2]=     0.000000;
GPOS[86][0]=    11712.000;
GPOS[86][1]=    -4390.300;
GPOS[86][2]=     0.000000;
GPOS[87][0]=   -13760.000;
GPOS[87][1]=      294.300;
GPOS[87][2]=     0.000000;
GPOS[88][0]=    13835.000;
GPOS[88][1]=    -4390.300;
GPOS[88][2]=     0.000000;
GPOS[89][0]=   -15883.000;
GPOS[89][1]=      294.300;
GPOS[89][2]=     0.000000;
GPOS[90][0]=     9589.300;
GPOS[90][1]=    -8859.000;
GPOS[90][2]=     0.000000;
GPOS[91][0]=   -11637.300;
GPOS[91][1]=     4763.000;
GPOS[91][2]=     0.000000;
GPOS[92][0]=    11712.000;
GPOS[92][1]=    -8859.000;
GPOS[92][2]=     0.000000;
GPOS[93][0]=   -13760.000;
GPOS[93][1]=     4763.000;
GPOS[93][2]=     0.000000;
GPOS[94][0]=    13835.000;
GPOS[94][1]=    -8859.000;
GPOS[94][2]=     0.000000;
GPOS[95][0]=   -15883.000;
GPOS[95][1]=     4763.000;
GPOS[95][2]=     0.000000;
GPOS[96][0]=     9589.300;
GPOS[96][1]=   -13327.000;
GPOS[96][2]=     0.000000;
GPOS[97][0]=   -11637.300;
GPOS[97][1]=     9231.000;
GPOS[97][2]=     0.000000;
GPOS[98][0]=    11712.000;
GPOS[98][1]=   -13327.000;
GPOS[98][2]=     0.000000;
GPOS[99][0]=   -13760.000;
GPOS[99][1]=     9231.000;
GPOS[99][2]=     0.000000;

//--------------------------------------------------
}
