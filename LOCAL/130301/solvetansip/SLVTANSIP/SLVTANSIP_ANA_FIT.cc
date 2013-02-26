//--------------------------------------------------
//SLVTANSIP_ANA_CCD.cc
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#include<iostream>
#include<cmath>
#include"SLVTANSIP_ANA.h"

using namespace std;
void CL_ANA::FIT_GLOBL(int APL,int VARIABLE,int FUNCTION, double **Coef){
	int i,j,FNUM;
	int ORDER;
	double ***dx;
	
		if(APL==0){
		ORDER=ORDER_ASIP;
	}else   if(APL==1){
		ORDER=ORDER_PSIP;
	}else   if(APL==2){
		ORDER=ORDER_LSIP;
	}else   if(APL==99){
		ORDER=7;
	}else{
		ORDER=ORDER_ASIP;
	}

	dx = F_NEWdouble3(2,NUM_OBJ,3);
	FNUM=0;
	for(OID=0;OID<NUM_OBJ;OID++)
	if(OBJ[OID].FLAG_OBJ == 1){
		for(i=0;i<2;i++)
			if(VARIABLE== 0){
			dx[0][FNUM][i]=dx[1][FNUM][i]=OBJ[OID].X_RADEC[i];
		}else   if(VARIABLE== 1){
			dx[0][FNUM][i]=dx[1][FNUM][i]=OBJ[OID].X_IMWLD[i];
		}else   if(VARIABLE== 2){
			dx[0][FNUM][i]=dx[1][FNUM][i]=OBJ[OID].X_IMPXLGLOBL[i];
		}else   if(VARIABLE== 3){
			dx[0][FNUM][i]=dx[1][FNUM][i]=OBJ[OID].X_IMPXLLOCAL[i];
		}else   if(VARIABLE== 4){
			dx[0][FNUM][i]=dx[1][FNUM][i]=OBJ[OID].X_CRPIXGLOBL[i];
		}else   if(VARIABLE== 5){
			dx[0][FNUM][i]=dx[1][FNUM][i]=OBJ[OID].X_CRPIXLOCAL[i];
		}else   if(VARIABLE== 6){
			dx[0][FNUM][i]=dx[1][FNUM][i]=OBJ[OID].X_GLOBL[i];
		}else   if(VARIABLE== 7){
			dx[0][FNUM][i]=dx[1][FNUM][i]=OBJ[OID].X_LOCAL[i];
		}else   if(VARIABLE==99){
			dx[0][FNUM][i]=dx[1][FNUM][i]=OBJ[OID].X_IMWLD_TANfromGLOBL[i];
		}else{
			dx[0][FNUM][i]=dx[1][FNUM][i]=OBJ[OID].X_RADEC[i];
		}

		for(i=0;i<2;i++)
			if(FUNCTION== 0){
			dx[i][FNUM][2]=OBJ[OID].X_RADEC[i];
		}else   if(FUNCTION== 1){
			dx[i][FNUM][2]=OBJ[OID].X_IMWLD[i];
		}else   if(FUNCTION== 2){
			dx[i][FNUM][2]=OBJ[OID].X_IMPXLGLOBL[i];
		}else   if(FUNCTION== 3){
			dx[i][FNUM][2]=OBJ[OID].X_IMPXLLOCAL[i];
		}else   if(FUNCTION== 4){
			dx[i][FNUM][2]=OBJ[OID].X_CRPIXGLOBL[i];
		}else   if(FUNCTION== 5){
			dx[i][FNUM][2]=OBJ[OID].X_CRPIXLOCAL[i];
		}else   if(FUNCTION== 6){
			dx[i][FNUM][2]=OBJ[OID].X_GLOBL[i];
		}else   if(FUNCTION== 7){
			dx[i][FNUM][2]=OBJ[OID].X_LOCAL[i];
		}else   if(FUNCTION==99){
			dx[i][FNUM][2]=OBJ[OID].X_IMWLD[i];
		}else{
			dx[i][FNUM][2]=OBJ[OID].X_GLOBL[i];
		}
		FNUM++;
	}
	NUM_FIT=FNUM;
	for(FNUM=NUM_FIT;FNUM<NUM_OBJ;FNUM++)
	for(i=0;i<2;i++)
	for(j=0;j<3;j++)
	dx[i][FNUM][j]=0;

	#pragma omp parallel num_threads(2)
	#pragma omp sections
	{
		#pragma omp section
		{
			F_LS2(NUM_FIT,ORDER,dx[0],Coef[0]);
		}
		#pragma omp section
		{
			F_LS2(NUM_FIT,ORDER,dx[1],Coef[1]);
		}
	}

	F_DELdouble3(2,NUM_OBJ,dx);
}
void CL_ANA::FIT_LOCAL (int APL,int VARIABLE,int FUNCTION){
	int i,*FNUM;
	int ORDER;
	double ****dx;

		if(APL==0){
		ORDER=ORDER_ASIP;
	}else   if(APL==1){
		ORDER=ORDER_PSIP;
	}else   if(APL==2){
		ORDER=ORDER_LSIP;
	}else{
		ORDER=ORDER_ASIP;
	}
//--------------------------------------------------
	FNUM = F_NEWint1(NUM_CCD);
	dx = F_NEWdouble4(2,NUM_CCD,NUM_OBJ,3);
//--------------------------------------------------
	for(OID=0;OID<NUM_OBJ;OID++)
	if(OBJ[OID].FLAG_OBJ == 1){
        	CID=OBJ[OID].ID_CHIP;
		for(i=0;i<2;i++)
			if(VARIABLE== 0){
			dx[0][CID][FNUM[CID]][i]=dx[1][CID][FNUM[CID]][i]=OBJ[OID].X_RADEC[i];
		}else   if(VARIABLE== 1){
			dx[0][CID][FNUM[CID]][i]=dx[1][CID][FNUM[CID]][i]=OBJ[OID].X_IMWLD[i];
		}else   if(VARIABLE== 2){
			dx[0][CID][FNUM[CID]][i]=dx[1][CID][FNUM[CID]][i]=OBJ[OID].X_IMPXLGLOBL[i];
		}else   if(VARIABLE== 3){
			dx[0][CID][FNUM[CID]][i]=dx[1][CID][FNUM[CID]][i]=OBJ[OID].X_IMPXLLOCAL[i];
		}else   if(VARIABLE== 4){
			dx[0][CID][FNUM[CID]][i]=dx[1][CID][FNUM[CID]][i]=OBJ[OID].X_CRPIXGLOBL[i];
		}else   if(VARIABLE== 5){
			dx[0][CID][FNUM[CID]][i]=dx[1][CID][FNUM[CID]][i]=OBJ[OID].X_CRPIXLOCAL[i];
		}else   if(VARIABLE== 6){
			dx[0][CID][FNUM[CID]][i]=dx[1][CID][FNUM[CID]][i]=OBJ[OID].X_GLOBL[i];
		}else   if(VARIABLE== 7){
			dx[0][CID][FNUM[CID]][i]=dx[1][CID][FNUM[CID]][i]=OBJ[OID].X_LOCAL[i];
		}else{
			dx[0][CID][FNUM[CID]][i]=dx[1][CID][FNUM[CID]][i]=OBJ[OID].X_RADEC[i];
		}

		for(i=0;i<2;i++)
			if(FUNCTION== 0){
			dx[i][CID][FNUM[CID]][2]=OBJ[OID].X_RADEC[i];
		}else   if(FUNCTION== 1){
			dx[i][CID][FNUM[CID]][2]=OBJ[OID].X_IMWLD[i];
		}else   if(FUNCTION== 2){
			dx[i][CID][FNUM[CID]][2]=OBJ[OID].X_IMPXLGLOBL[i];
		}else   if(FUNCTION== 3){
			dx[i][CID][FNUM[CID]][2]=OBJ[OID].X_IMPXLLOCAL[i];
		}else   if(FUNCTION== 4){
			dx[i][CID][FNUM[CID]][2]=OBJ[OID].X_CRPIXGLOBL[i];
		}else   if(FUNCTION== 5){
			dx[i][CID][FNUM[CID]][2]=OBJ[OID].X_CRPIXLOCAL[i];
		}else   if(FUNCTION== 6){
			dx[i][CID][FNUM[CID]][2]=OBJ[OID].X_GLOBL[i];
		}else   if(FUNCTION== 7){
			dx[i][CID][FNUM[CID]][2]=OBJ[OID].X_LOCAL[i];
		}else{
			dx[i][CID][FNUM[CID]][2]=OBJ[OID].X_GLOBL[i];
		}
		FNUM[CID]++;
	}

	for(CID=0;CID<NUM_CCD;CID++)
	for(i=0;i<2;i++)
	F_LS2(FNUM[CID],ORDER,dx[i][CID],CCD[CID].LCoef[i]);

//--------------------------------------------------
	F_DELint1(FNUM);
	F_DELdouble4(2,NUM_CCD,NUM_OBJ,dx);
}
void CL_ANA::CALC_DIFF(int V1,int V2, double DIF[2][2]){
	int FNUM,i;
	double **dV,A[2],B[2];
	dV = F_NEWdouble2(2,NUM_OBJ);
	FNUM=0;
	for(OID=0;OID<NUM_OBJ;OID++)
	if(OBJ[OID].FLAG_OBJ == 1){
		for(i=0;i<2;i++)
			if(V1==0 ){
			A[i]=OBJ[OID].X_RADEC[i];
		}else   if(V1==1 ){
			A[i]=OBJ[OID].X_IMWLD[i];
		}else   if(V1==2 ){
			A[i]=OBJ[OID].X_IMPXLGLOBL[i];
		}else   if(V1==3 ){
			A[i]=OBJ[OID].X_IMPXLLOCAL[i];
		}else   if(V1==4 ){
			A[i]=OBJ[OID].X_CRPIXGLOBL[i];
		}else   if(V1==5 ){
			A[i]=OBJ[OID].X_CRPIXLOCAL[i];
		}else   if(V1==6 ){
			A[i]=OBJ[OID].X_GLOBL[i];
		}else   if(V1==7 ){
			A[i]=OBJ[OID].X_LOCAL[i];
		}else   if(V1==8 ){
			A[i]=OBJ[OID].X_RADEC_SIPfromLOCAL[i];
		}else   if(V1==9 ){
			A[i]=OBJ[OID].X_RADEC_SIPfromGLOBL[i];
		}else   if(V1==10){
			A[i]=OBJ[OID].X_IMWLD_SIPfromLOCAL[i];
		}else   if(V1==11){
			A[i]=OBJ[OID].X_IMWLD_SIPfromGLOBL[i];
		}else   if(V1==12){
			A[i]=OBJ[OID].X_IMPXLGLOBL_SIPfromGLOBL[i];
		}else   if(V1==13){
			A[i]=OBJ[OID].X_IMPXLLOCAL_SIPfromLOCAL[i];
		}else   if(V1==14){
			A[i]=OBJ[OID].X_CRPIXGLOBL_SIPfromRADEC[i];
		}else   if(V1==15){
			A[i]=OBJ[OID].X_CRPIXLOCAL_SIPfromRADEC[i];
		}else   if(V1==16){
			A[i]=OBJ[OID].X_GLOBL_SIPfromRADEC[i];
		}else   if(V1==17){
			A[i]=OBJ[OID].X_LOCAL_SIPfromRADEC[i];
		}else   if(V1==18){
			A[i]=OBJ[OID].X_RADEC_TANfromLOCAL[i];
		}else   if(V1==19){
			A[i]=OBJ[OID].X_RADEC_TANfromGLOBL[i];
		}else   if(V1==20){
			A[i]=OBJ[OID].X_IMWLD_TANfromLOCAL[i];
		}else   if(V1==21){
			A[i]=OBJ[OID].X_IMWLD_TANfromGLOBL[i];
		}else   if(V1==22){
			A[i]=OBJ[OID].X_IMPXLGLOBL_TANfromGLOBL[i];
		}else   if(V1==23){
			A[i]=OBJ[OID].X_IMPXLLOCAL_TANfromLOCAL[i];
		}else   if(V1==24){
			A[i]=OBJ[OID].X_CRPIXGLOBL_TANfromRADEC[i];
		}else   if(V1==25){
			A[i]=OBJ[OID].X_CRPIXLOCAL_TANfromRADEC[i];
		}else   if(V1==26){
			A[i]=OBJ[OID].X_GLOBL_TANfromRADEC[i];
		}else   if(V1==27){
			A[i]=OBJ[OID].X_LOCAL_TANfromRADEC[i];
		}else{
			A[i]=OBJ[OID].X_RADEC[i];
		}

		for(i=0;i<2;i++)
			if(V2==0 ){
			B[i]=OBJ[OID].X_RADEC[i];
		}else   if(V2==1 ){
			B[i]=OBJ[OID].X_IMWLD[i];
		}else   if(V2==2 ){
			B[i]=OBJ[OID].X_IMPXLGLOBL[i];
		}else   if(V2==3 ){
			B[i]=OBJ[OID].X_IMPXLLOCAL[i];
		}else   if(V2==4 ){
			B[i]=OBJ[OID].X_CRPIXGLOBL[i];
		}else   if(V2==5 ){
			B[i]=OBJ[OID].X_CRPIXLOCAL[i];
		}else   if(V2==6 ){
			B[i]=OBJ[OID].X_GLOBL[i];
		}else   if(V2==7 ){
			B[i]=OBJ[OID].X_LOCAL[i];
		}else   if(V2==8 ){
			B[i]=OBJ[OID].X_RADEC_SIPfromLOCAL[i];
		}else   if(V2==9 ){
			B[i]=OBJ[OID].X_RADEC_SIPfromGLOBL[i];
		}else   if(V2==10){
			B[i]=OBJ[OID].X_IMWLD_SIPfromLOCAL[i];
		}else   if(V2==11){
			B[i]=OBJ[OID].X_IMWLD_SIPfromGLOBL[i];
		}else   if(V2==12){
			B[i]=OBJ[OID].X_IMPXLGLOBL_SIPfromGLOBL[i];
		}else   if(V2==13){
			B[i]=OBJ[OID].X_IMPXLLOCAL_SIPfromLOCAL[i];
		}else   if(V2==14){
			B[i]=OBJ[OID].X_CRPIXGLOBL_SIPfromRADEC[i];
		}else   if(V2==15){
			B[i]=OBJ[OID].X_CRPIXLOCAL_SIPfromRADEC[i];
		}else   if(V2==16){
			B[i]=OBJ[OID].X_GLOBL_SIPfromRADEC[i];
		}else   if(V2==17){
			B[i]=OBJ[OID].X_LOCAL_SIPfromRADEC[i];
		}else   if(V2==18){
			B[i]=OBJ[OID].X_RADEC_TANfromLOCAL[i];
		}else   if(V2==19){
			B[i]=OBJ[OID].X_RADEC_TANfromGLOBL[i];
		}else   if(V2==20){
			B[i]=OBJ[OID].X_IMWLD_TANfromLOCAL[i];
		}else   if(V2==21){
			B[i]=OBJ[OID].X_IMWLD_TANfromGLOBL[i];
		}else   if(V2==22){
			B[i]=OBJ[OID].X_IMPXLGLOBL_TANfromGLOBL[i];
		}else   if(V2==23){
			B[i]=OBJ[OID].X_IMPXLLOCAL_TANfromLOCAL[i];
		}else   if(V2==24){
			B[i]=OBJ[OID].X_CRPIXGLOBL_TANfromRADEC[i];
		}else   if(V2==25){
			B[i]=OBJ[OID].X_CRPIXLOCAL_TANfromRADEC[i];
		}else   if(V2==26){
			B[i]=OBJ[OID].X_GLOBL_TANfromRADEC[i];
		}else   if(V2==27){
			B[i]=OBJ[OID].X_LOCAL_TANfromRADEC[i];
		}else{
			B[i]=OBJ[OID].X_RADEC[i];
		}
		for(i=0;i<2;i++)
		dV[i][FNUM]=A[i]-B[i];
		FNUM++;
	}
	
	F_RMS(FNUM,dV[0],DIF[0]);
	F_RMS(FNUM,dV[1],DIF[1]);

	F_DELdouble2(2,dV);
}
