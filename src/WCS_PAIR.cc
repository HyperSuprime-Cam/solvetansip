//------------------------------------------------------------
//WCS_APAIR.cc
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<cmath>
#include<string.h>
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_SUB.h"
#include "hsc/meas/tansip/LeastSquares.h"

using namespace std;
//--------------------------------------------------
//MAIN
//--------------------------------------------------
void CL_APAIR::F_WCSA_APAIR_REJECTION(){
    int NUM;
    F_WCSA_APAIR_CENTERofOBJECTS();

    F_WCSA_APAIR_CALCRMS(0,6,0);   

    REJNUM=0;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(fabs(PAIR[NUM].X_RADEC[0]-F_CALCVALUE(SIP_ORDER,TCoef[0],PAIR[NUM].X_CENTER_GLOBAL)) > CLIP_SIGMA*AVERMS[0][1] || fabs(PAIR[NUM].X_RADEC[1]-F_CALCVALUE(SIP_ORDER,TCoef[1],PAIR[NUM].X_CENTER_GLOBAL)) > CLIP_SIGMA*AVERMS[1][1]){
    PAIR[NUM].FLAG=0;
    REJNUM++;
    }

    F_WCSA_APAIR_CENTERofOBJECTS();
    if(STDOUT==2)cout << "CENTER_PIXEL : " << CENTER_PIXEL[0] << " , " << CENTER_PIXEL[1] << endl;
    if(STDOUT==2)cout << "CENTER_RADEC : " << CENTER_RADEC[0] << " , " << CENTER_RADEC[1] << endl;
    if(STDOUT==2)cout << "RMS RA(deg)  : " << AVERMS[0][1] << endl;
    if(STDOUT==2)cout << "RMS DEC(deg) : " << AVERMS[1][1] << endl;
    if(STDOUT==2)cout << "REJECTED NUM : " << REJNUM << endl;

}
void CL_APAIR::F_WCSA_APAIR_GPOS(){
    int CID;

    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : PROJECTION ---" << endl;

    F_WCSA_APAIR_CENTERPROJECTION();
    F_WCSA_APAIR_LDIFFVALUES();

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
    if(STDOUT==2)for(CID=0;CID<CCDNUM;CID++)cout << "X : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][0] <<endl<< "Y : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][1] << endl;
    if(STDOUT==2)cout << "X : AVE : " << GPOS_AVE[0] << endl << "Y : AVE : " << GPOS_AVE[1] << endl;
    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : SET AVERAGE of XYs = 0 ---" << endl;
    F_WCSA_APAIR_CCDPOSITIONS_XY_SETAVERAGE();//CENTER = (1024, 2048)
    if(STDOUT==2)for(CID=0;CID<CCDNUM;CID++)cout << "X : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][0] <<endl<< "Y : " << setfill ('0') << setw (3) <<CID << fixed<< " : " << GPOS[CID][1] << endl;
}
void CL_APAIR::F_WCSA_APAIR_WCS(){
    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : GET CR--" << endl;
    F_WCSA_APAIR_CALCCR();

    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET X--" << endl;
    F_WCSA_APAIR_SETX();

    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : FITTING--" << endl;
    F_WCSA_APAIR_FITTING();

/*    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : FIT  SIP--" << endl;
    F_WCSA_APAIR_FITSIP();
    F_WCSA_APAIR_SETIM();

    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : FIT PSIP--" << endl;
    F_WCSA_APAIR_FITPSIP();
*/
    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : SET RMS of SIPs--" << endl;
    F_WCSA_APAIR_CALCSIPRMS();
    F_WCSA_APAIR_CALCPSIPRMS();

    if(STDOUT==1||STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS : GET CRSM (Convergence, rotation, Shear, Magnification)--" << endl;
    F_WCSA_APAIR_CALCCONVROTSHEARMAG();
//    F_WCSA_APAIR_CALCMAGROTSHEARfromTCoef();
//    F_WCSA_APAIR_CALCCRSfromTCoef();
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
void CL_APAIR::F_WCSA_APAIR_SETCRPIX(){
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
void CL_APAIR::F_WCSA_APAIR_SETIM(){
    int NUM;
    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].X_IM_PIXEL[0]=InvCD[0][0]*PAIR[NUM].X_IM_WORLD[0]+InvCD[0][1]*PAIR[NUM].X_IM_WORLD[1];
        PAIR[NUM].X_IM_PIXEL[1]=InvCD[1][0]*PAIR[NUM].X_IM_WORLD[0]+InvCD[1][1]*PAIR[NUM].X_IM_WORLD[1];
    }
}
void CL_APAIR::F_WCSA_APAIR_SETX(){
    F_WCSA_APAIR_SETXG();
    F_WCSA_APAIR_SETCRPIX();
    F_WCSA_APAIR_PROJECTION();
    F_WCSA_APAIR_SETIM();
}
void CL_APAIR::F_WCSA_APAIR_CENTERPROJECTION(){
    int NUM;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    F_PROJECTION(PAIR[NUM].X_RADEC,PAIR[NUM].X_CENTER_IM_WORLD,CENTER_RADEC);
}
void CL_APAIR::F_WCSA_APAIR_CENTERofOBJECTS(){
    int NUM,FNUM;

    CENTER_PIXEL[0]=CENTER_PIXEL[1]=FNUM=0;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG == 1){
        CENTER_PIXEL[0]+=PAIR[NUM].X_GLOBAL[0];
        CENTER_PIXEL[1]+=PAIR[NUM].X_GLOBAL[1];
        FNUM++;
    }
    ALLFITNUM=FNUM;
    CENTER_PIXEL[0]/=FNUM;
    CENTER_PIXEL[1]/=FNUM;
    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].X_CENTER_GLOBAL[0]=PAIR[NUM].X_GLOBAL[0]-CENTER_PIXEL[0];
        PAIR[NUM].X_CENTER_GLOBAL[1]=PAIR[NUM].X_GLOBAL[1]-CENTER_PIXEL[1];
    }

    F_WCSA_APAIR_GFITTING(0,6,0);

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
    F_WCSA_APAIR_SETCRPIX();
    F_WCSA_APAIR_GFITTING(0,3,0);
    CRVAL[0]=TCoef[0][0];
    CRVAL[1]=TCoef[1][0];
}
void CL_APAIR::F_WCSA_APAIR_CALCCRPIX(){
    F_WCSA_APAIR_PROJECTION();
    F_WCSA_APAIR_GFITTING(1,1,4);
    CRPIX[0]=TPCoef[0][0];
    CRPIX[1]=TPCoef[1][0];
}
//---------------------------------------------
//FITTING
//---------------------------------------------
void CL_APAIR::F_WCSA_APAIR_FITTING(){
F_WCSA_APAIR_GFITTING(SIP_ORDER  ,3,1,CDSIP_AB);
F_WCSA_APAIR_SETCDSIP();
F_WCSA_APAIR_SETIM();
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
        }
        FNUM++;
    }
    ALLFITNUM=FNUM;
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

void CL_APAIR::F_WCSA_APAIR_GFITTING(int SELORDER,int VARIABLE,int FUNCTION){
//cout <<"F_WCS_TANSIP_GPOLYNOMIALFITTING"<<endl;
    int i,NUM,ORDER,FNUM=0;
    double ***dx;

//--------------------------------------------------
    dx = F_NEWdouble3(2,ALLREFNUM,3);
//--------------------------------------------------
          if(SELORDER==0){
        ORDER=SIP_ORDER;
    }else if(SELORDER==1){
        ORDER=SIP_P_ORDER;
    }else if(SELORDER==2){
        ORDER=SIP_ORDER-1;
    }else if(SELORDER==3){
        ORDER=SIP_L_ORDER;
    }else{
        ORDER=SIP_ORDER;
    }

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
        }
        FNUM++;
    }
    ALLFITNUM=FNUM;
    #pragma omp parallel num_threads(2)
    #pragma omp sections
    {
        #pragma omp section
        {
            if(SELORDER==1){
            F_LS2(FNUM,ORDER,dx[0],TPCoef[0]);
            }else{
            F_LS2(FNUM,ORDER,dx[0],TCoef[0]);
            }
        }
        #pragma omp section
        {
            if(SELORDER==1){
            F_LS2(FNUM,ORDER,dx[1],TPCoef[1]);
            }else{
            F_LS2(FNUM,ORDER,dx[1],TCoef[1]);
            }
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

    for(NUM=0;NUM<ALLREFNUM;NUM++){
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
void CL_APAIR::F_WCSA_APAIR_CALCRMS(int SELORDER,int VARIABLE,int FUNCTION){
    int i,NUM,ORDER,FNUM=0;
    double ***dx,**data;

//--------------------------------------------------
    dx = F_NEWdouble3(2,ALLREFNUM,3);
    data = F_NEWdouble2(2,ALLREFNUM);
//--------------------------------------------------
          if(SELORDER==0){
        ORDER=SIP_ORDER;
    }else if(SELORDER==1){
        ORDER=SIP_P_ORDER;
    }else if(SELORDER==2){
        ORDER=SIP_ORDER-1;
    }else if(SELORDER==3){
        ORDER=SIP_L_ORDER;
    }else{
        ORDER=SIP_ORDER;
    }

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
    int i,NUM;
    double *TdCoef[2][2],*TPdCoef[2][2];
    double dGdI[2][2],InvdGdI[2][2],dIdG[2][2];

    TdCoef[0][0]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
    TdCoef[0][1]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
    TdCoef[1][0]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
    TdCoef[1][1]=F_NEWdouble1((SIP_ORDER+1)*(SIP_ORDER+2));
    TdPCoef[0][0]=F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TdPCoef[0][1]=F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TdPCoef[1][0]=F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));
    TdPCoef[1][1]=F_NEWdouble1((SIP_P_ORDER+1)*(SIP_P_ORDER+2));

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

        PAIR[NUM].CAMERA_PCONVROT[0]   =0.5*(dIdG[0][0]+dIdG[1][1]);
        PAIR[NUM].CAMERA_PCONVROT[1]   =0.5*(dIdG[0][1]-dIdG[1][0]);
        PAIR[NUM].CAMERA_PSHEAR[0]     =0.5*(dIdG[0][0]-dIdG[1][1]);
        PAIR[NUM].CAMERA_PSHEAR[1]     =0.5*(dIdG[0][1]+dIdG[1][0]);
        PAIR[NUM].CAMERA_PMAGNIFICATION=((1+PAIR[NUM].CAMERA_PCONVROT[0])*(1+PAIR[NUM].CAMERA_PCONVROT[0])-(PAIR[NUM].CAMERA_PSHEAR[0]*PAIR[NUM].CAMERA_PSHEAR[0]+PAIR[NUM].CAMERA_PSHEAR[1]*PAIR[NUM].CAMERA_PSHEAR[1]));
        PAIR[NUM].CAMERA_CONVROT[0]    =0.5*(InvdGdI[0][0]+InvdGdI[1][1]);
        PAIR[NUM].CAMERA_CONVROT[1]    =0.5*(InvdGdI[0][1]-InvdGdI[1][0]);
        PAIR[NUM].CAMERA_SHEAR[0]      =0.5*(InvdGdI[0][0]-InvdGdI[1][1]);
        PAIR[NUM].CAMERA_SHEAR[1]      =0.5*(InvdGdI[0][1]+InvdGdI[1][0]);
        PAIR[NUM].CAMERA_MAGNIFICATION =((1+PAIR[NUM].CAMERA_CONVROT[0])*(1+PAIR[NUM].CAMERA_CONVROT[0])-(PAIR[NUM].CAMERA_SHEAR[0]*PAIR[NUM].CAMERA_SHEAR[0]+PAIR[NUM].CAMERA_SHEAR[1]*PAIR[NUM].CAMERA_SHEAR[1]));
    }

    F_DELdouble1(TdCoef[0][0]);
    F_DELdouble1(TdCoef[0][1]);
    F_DELdouble1(TdCoef[1][0]);
    F_DELdouble1(TdCoef[1][1]);
    F_DELdouble1(TdPCoef[0][0]);
    F_DELdouble1(TdPCoef[0][1]);
    F_DELdouble1(TdPCoef[1][0]);
    F_DELdouble1(TdPCoef[1][1]);
}
//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------
void CL_APAIR::F_WCSA_APAIR_SETSIP(){
    CD[0][0]=TCoef[0][1*(SIP_ORDER+1)+0];
    CD[0][1]=TCoef[0][0*(SIP_ORDER+1)+1];
    CD[1][0]=TCoef[1][1*(SIP_ORDER+1)+0];
    CD[1][1]=TCoef[1][0*(SIP_ORDER+1)+1]; 
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
        TSIP_AB[0][ij]=InvCD[0][0]*TCoef[0][ij]+InvCD[0][1]*TCoef[1][ij];
        TSIP_AB[1][ij]=InvCD[1][0]*TCoef[0][ij]+InvCD[1][1]*TCoef[1][ij];
        ij++;	
    }
    TSIP_AB[0][1*(SIP_ORDER+1)+0]-=1.0;
    TSIP_AB[1][0*(SIP_ORDER+1)+1]-=1.0;
}
void CL_APAIR::F_WCSA_APAIR_SETPSIP(){
    int i,j,ij;
    ij=0;
    for(i=0;i<SIP_P_ORDER+1;i++)
    for(j=0;j<SIP_P_ORDER+1;j++)
    if(i+j<SIP_P_ORDER+1){
        TSIP_ABP[0][ij]=TPCoef[0][ij];
        TSIP_ABP[1][ij]=TPCoef[1][ij];
        ij++;	
    }
    TSIP_ABP[0][1*(SIP_P_ORDER+1)+0]-=1.0;
    TSIP_ABP[1][0*(SIP_P_ORDER+1)+1]-=1.0;
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
void CL_APAIR::F_WCSA_APAIR_FITSIP(){
    F_WCSA_APAIR_GFITTING(0,3,1);
    F_WCSA_APAIR_SETSIP();
}
void CL_APAIR::F_WCSA_APAIR_FITPSIP(){
    F_WCSA_APAIR_GFITTING(1,2,3);
    F_WCSA_APAIR_SETPSIP();
}
void CL_APAIR::F_WCSA_APAIR_CALCMAGROTSHEAR(){
    F_WCSA_APAIR_GFITTING(0,3,1);
    F_WCSA_APAIR_CALCMAGROTSHEARfromTCoef();
}
void CL_APAIR::F_WCSA_APAIR_CALCCRS(){
//    F_WCSA_APAIR_GFITTING(0,3,1);
//    F_WCSA_APAIR_CALCMAGROTSHEARfromTCoef();
}
void CL_APAIR::F_WCSA_APAIR_CALCMAGROTSHEARfromTCoef(){
    int NUM;

/*??????????????????????????????????????????????????*/
    F_DIFFSIP(SIP_ORDER,TCoef[0],TdCoef[0][0],TdCoef[0][1]);
    F_DIFFSIP(SIP_ORDER,TCoef[1],TdCoef[1][0],TdCoef[1][1]);

    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].CAMERA_CONVROT[0] =PAIR[NUM].CAMERA_CONVROT[1] =PAIR[NUM].CAMERA_SHEAR[0] =PAIR[NUM].CAMERA_SHEAR[1] =PAIR[NUM].CAMERA_MAGNIFICATION =0;
        PAIR[NUM].CAMERA_PCONVROT[0]=PAIR[NUM].CAMERA_PCONVROT[1]=PAIR[NUM].CAMERA_PSHEAR[0]=PAIR[NUM].CAMERA_PSHEAR[1]=PAIR[NUM].CAMERA_PMAGNIFICATION=0;
    }

    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].dxGdxI=F_CALCVALUE(SIP_ORDER,TdCoef[0][0],PAIR[NUM].X_CRPIX);
        PAIR[NUM].dxGdyI=F_CALCVALUE(SIP_ORDER,TdCoef[0][1],PAIR[NUM].X_CRPIX);
        PAIR[NUM].dyGdxI=F_CALCVALUE(SIP_ORDER,TdCoef[1][0],PAIR[NUM].X_CRPIX);
        PAIR[NUM].dyGdyI=F_CALCVALUE(SIP_ORDER,TdCoef[1][1],PAIR[NUM].X_CRPIX);

        PAIR[NUM].CAMERA_MAGROT[0]=0.5*hypot((-1)*PAIR[NUM].dxGdxI+PAIR[NUM].dyGdyI,PAIR[NUM].dyGdxI-(-1)*PAIR[NUM].dxGdyI);
        PAIR[NUM].CAMERA_MAGROT[1]=atan2((PAIR[NUM].dyGdxI-(-1)*PAIR[NUM].dxGdyI),((-1)*PAIR[NUM].dxGdxI+PAIR[NUM].dyGdyI));
        PAIR[NUM].CAMERA_SHEAR[0] =0.5*((-1)*PAIR[NUM].dxGdxI-     PAIR[NUM].dyGdyI)/PAIR[NUM].CAMERA_MAGROT[0];
        PAIR[NUM].CAMERA_SHEAR[1] =0.5*(     PAIR[NUM].dyGdxI+(-1)*PAIR[NUM].dxGdyI)/PAIR[NUM].CAMERA_MAGROT[0];
    }
}
void CL_APAIR::F_WCSA_APAIR_CALCCRSfromTCoef(){
/*    int NUM;

    F_DIFFSIP(SIP_ORDER,TCoef[0],TdCoef[0][0],TdCoef[0][1]);
    F_DIFFSIP(SIP_ORDER,TCoef[1],TdCoef[1][0],TdCoef[1][1]);

    for(NUM=0;NUM<ALLREFNUM;NUM++){
        PAIR[NUM].dxGdxI=F_CALCVALUE(SIP_ORDER,TdCoef[0][0],PAIR[NUM].X_CRPIX);
        PAIR[NUM].dxGdyI=F_CALCVALUE(SIP_ORDER,TdCoef[0][1],PAIR[NUM].X_CRPIX);
        PAIR[NUM].dyGdxI=F_CALCVALUE(SIP_ORDER,TdCoef[1][0],PAIR[NUM].X_CRPIX);
        PAIR[NUM].dyGdyI=F_CALCVALUE(SIP_ORDER,TdCoef[1][1],PAIR[NUM].X_CRPIX);

        PAIR[NUM].CAMERA_MAGROT[0]=0.5*hypot((-1)*PAIR[NUM].dxGdxI+PAIR[NUM].dyGdyI,PAIR[NUM].dyGdxI-(-1)*PAIR[NUM].dxGdyI);
        PAIR[NUM].CAMERA_MAGROT[1]=atan2((PAIR[NUM].dyGdxI-(-1)*PAIR[NUM].dxGdyI),((-1)*PAIR[NUM].dxGdxI+PAIR[NUM].dyGdyI));
        PAIR[NUM].CAMERA_SHEAR[0] =0.5*((-1)*PAIR[NUM].dxGdxI-     PAIR[NUM].dyGdyI)/PAIR[NUM].CAMERA_MAGROT[0];
        PAIR[NUM].CAMERA_SHEAR[1] =0.5*(     PAIR[NUM].dyGdxI+(-1)*PAIR[NUM].dxGdyI)/PAIR[NUM].CAMERA_MAGROT[0];
    }*/
}
//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------
void CL_APAIR::F_WCSA_APAIR_CALCSIPRMS(){
    int NUM,FNUM=0;
    double **data;

//--------------------------------------------------
    data = F_NEWdouble2(2,ALLREFNUM);
//--------------------------------------------------
    FNUM=0;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG == 1){
        data[0][NUM]=PAIR[NUM].X_IM_PIXEL[0]-(F_CALCVALUE(SIP_ORDER,SIP_AB[0],PAIR[NUM].X_GLOBALCRPIX)+PAIR[NUM].X_GLOBALCRPIX[0]);
        data[1][NUM]=PAIR[NUM].X_IM_PIXEL[1]-(F_CALCVALUE(SIP_ORDER,SIP_AB[1],PAIR[NUM].X_GLOBALCRPIX)+PAIR[NUM].X_GLOBALCRPIX[1]);
        FNUM++;
    }
    F_RMS(FNUM,data[0],SIPRMS[0]);
    F_RMS(FNUM,data[1],SIPRMS[1]);
//--------------------------------------------------
    F_DELdouble2(2,data);
}
void CL_APAIR::F_WCSA_APAIR_CALCPSIPRMS(){
    int NUM,FNUM=0;
    double **data;

//--------------------------------------------------
    data = F_NEWdouble2(2,ALLREFNUM);
//--------------------------------------------------
    FNUM=0;
    for(NUM=0;NUM<ALLREFNUM;NUM++)
    if(PAIR[NUM].FLAG == 1){
        data[0][NUM]=PAIR[NUM].X_GLOBALCRPIX[0]-(F_CALCVALUE(SIP_P_ORDER,SIP_ABP[0],PAIR[NUM].X_IM_PIXEL)+PAIR[NUM].X_IM_PIXEL[0]);
        data[1][NUM]=PAIR[NUM].X_GLOBALCRPIX[1]-(F_CALCVALUE(SIP_P_ORDER,SIP_ABP[1],PAIR[NUM].X_IM_PIXEL)+PAIR[NUM].X_IM_PIXEL[1]);
        FNUM++;
    }
    F_RMS(FNUM,data[0],PSIPRMS[0]);
    F_RMS(FNUM,data[1],PSIPRMS[1]);
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

    for(IterNUM_T=0;IterNUM_T<10;IterNUM_T++){
        for(CID=0;CID<CCDNUM;CID++)
        Tcheck[CID]=GPOS[CID][2];

        F_WCSA_APAIR_GDIFFVALUES();
        F_WCSA_APAIR_CCDPOSITIONS_T_MAT();

        TCHECK=0;
        for(CID=0;CID<CCDNUM;CID++)
        if(fabs(Tcheck[CID]-GPOS[CID][2])>pow(10,-5.0))
        TCHECK++;

        if(TCHECK==0)
        break;
    }
    GPOS_AVE[2]=0;
    for(CID=0;CID<CCDNUM;CID++)
    GPOS_AVE[2]+=GPOS[CID][2]/CCDNUM;

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
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_T_SETAVERAGE(){
    int CID;
    for(CID=0;CID<CCDNUM;CID++)
    GPOS[CID][2]-=GPOS_AVE[2];
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

    GPOS_AVE[0]=GPOS_AVE[1]=0;
    for(CID=0;CID<CCDNUM;CID++){
        GPOS[CID][0]=dX[CID][1]/dX[CID][0];
        GPOS[CID][1]=dX[CID][2]/dX[CID][0];
        GPOS_AVE[0]+=GPOS[CID][0]/CCDNUM;
        GPOS_AVE[1]+=GPOS[CID][1]/CCDNUM;
    }

//--------------------------------------------------
    F_DELdouble4(2,2,ALLREFNUM,dGdI);
    F_DELdouble2(CCDNUM,dX);
}
void CL_APAIR::F_WCSA_APAIR_CCDPOSITIONS_XY_SETAVERAGE(){
    int CID;
    for(CID=0;CID<CCDNUM;CID++){
    GPOS[CID][0]-=GPOS_AVE[0]-1024;
    GPOS[CID][1]-=GPOS_AVE[1]-2048;
    }
}
//ETC
void CL_APAIR::F_WCSA_APAIR_SET0(){
    CCDPOSMODE =0;
    CCDNUM     =0;
    ALLREFNUM  =0;
    ALLFITNUM  =0;
    SIP_ORDER  =0;
    SIP_P_ORDER=0;
    SIP_L_ORDER=0;
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
