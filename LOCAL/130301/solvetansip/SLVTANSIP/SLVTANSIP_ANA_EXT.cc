//--------------------------------------------------
//SLVTANSIP_ANA_EXT.cc
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<cmath>
#include"SLVTANSIP_ANA.h"

using namespace std;
void CL_ANA::EXT_DATA(){
	if(STDOUT==1||STDOUT==2)cout << "--- EXTRA CALCULATION : START---" <<endl;
	CALC_POSITIONS_LOCAL();
	CALC_TANSIPPOS();
	CALC_TANPOS();

	CALC_MAX_R();
	CALC_RMS();
	CALC_LOCALDISTORTION();

	if(PVCALC==1)
	CALC_PV();
	if(STDOUT==1||STDOUT==2)cout << "--- EXTRA CALCULATION : END ---" <<endl;
}
void CL_ANA::CALC_TANSIPPOS(){
	CALC_X_CRPIXGLOBL_SIP();
	CALC_X_CRPIXLOCAL_SIP();
	CALC_X_GLOBL_SIP();
	CALC_X_LOCAL_SIP();
	CALC_X_IMPXLGLOBL_SIP();
	CALC_X_IMPXLLOCAL_SIP();
	CALC_X_IMWLDGLOBL_SIP();
	CALC_X_IMWLDLOCAL_SIP();
	CALC_X_RADEC_SIP();
}
void CL_ANA::CALC_TANPOS(){
	CALC_X_CRPIXGLOBL_TAN();
	CALC_X_CRPIXLOCAL_TAN();
	CALC_X_GLOBL_TAN();
	CALC_X_LOCAL_TAN();
	CALC_X_IMPXLGLOBL_TAN();
	CALC_X_IMPXLLOCAL_TAN();
	CALC_X_IMWLDGLOBL_TAN();
	CALC_X_IMWLDLOCAL_TAN();
	CALC_X_RADEC_TAN();
}
void CL_ANA::CALC_RMS(){
	int i,*NUM;
	double ***DATA_RADEC,***DATA_CRPIX,***DATA_IMPXL,***DATA_LOCAL;
	double ***STAT_RADEC,***STAT_CRPIX,***STAT_IMPXL,***STAT_LOCAL;
	NUM       =F_NEWint1(NUM_CCD+1);
	DATA_RADEC=F_NEWdouble3(NUM_CCD+1,2,NUM_OBJ);
	DATA_CRPIX=F_NEWdouble3(NUM_CCD+1,2,NUM_OBJ);
	DATA_IMPXL=F_NEWdouble3(NUM_CCD+1,2,NUM_OBJ);
	DATA_LOCAL=F_NEWdouble3(NUM_CCD+1,2,NUM_OBJ);
	STAT_RADEC=F_NEWdouble3(NUM_CCD+1,2,3);
	STAT_CRPIX=F_NEWdouble3(NUM_CCD+1,2,3);
	STAT_IMPXL=F_NEWdouble3(NUM_CCD+1,2,3);
	STAT_LOCAL=F_NEWdouble3(NUM_CCD+1,2,3);

	for(OID=0;OID<NUM_OBJ;OID++)
	if(OBJ[OID].FLAG_OBJ==1){
		CID=OBJ[OID].ID_CHIP;
		for(i=0;i<2;i++){
			DATA_LOCAL[CID][i][NUM[CID]]=OBJ[OID].X_LOCAL_SIPfromRADEC[i]-OBJ[OID].X_LOCAL[i];
			DATA_CRPIX[CID][i][NUM[CID]]=OBJ[OID].X_CRPIXLOCAL_SIPfromRADEC[i]-OBJ[OID].X_CRPIXLOCAL[i];
			DATA_IMPXL[CID][i][NUM[CID]]=OBJ[OID].X_IMPXLLOCAL_SIPfromLOCAL[i]-OBJ[OID].X_IMPXLLOCAL[i];
			DATA_RADEC[CID][i][NUM[CID]]=OBJ[OID].X_RADEC_SIPfromLOCAL[i]-OBJ[OID].X_RADEC[i];
			DATA_LOCAL[NUM_CCD][i][NUM[NUM_CCD]]=OBJ[OID].X_GLOBL_SIPfromRADEC[i]-OBJ[OID].X_GLOBL[i];
			DATA_CRPIX[NUM_CCD][i][NUM[NUM_CCD]]=OBJ[OID].X_CRPIXGLOBL_SIPfromRADEC[i]-OBJ[OID].X_CRPIXGLOBL[i];
			DATA_IMPXL[NUM_CCD][i][NUM[NUM_CCD]]=OBJ[OID].X_IMPXLGLOBL_SIPfromGLOBL[i]-OBJ[OID].X_IMPXLGLOBL[i];
			DATA_RADEC[NUM_CCD][i][NUM[NUM_CCD]]=OBJ[OID].X_RADEC_SIPfromGLOBL[i]-OBJ[OID].X_RADEC[i];
		}
		NUM[CID]++;
		NUM[NUM_CCD]++;
	}

	for(CID=0;CID<NUM_CCD+1;CID++)
	if(NUM[CID]>0.5)
	for(i=0;i<2;i++){
		F_RMSMAX(NUM[CID],DATA_LOCAL[CID][i],STAT_LOCAL[CID][i]);
		F_RMSMAX(NUM[CID],DATA_CRPIX[CID][i],STAT_CRPIX[CID][i]);
		F_RMSMAX(NUM[CID],DATA_IMPXL[CID][i],STAT_IMPXL[CID][i]);
		F_RMSMAX(NUM[CID],DATA_RADEC[CID][i],STAT_RADEC[CID][i]);
		CCD[CID].AVE_DIF_LOCAL[i]=STAT_LOCAL[CID][i][0];
		CCD[CID].RMS_DIF_LOCAL[i]=STAT_LOCAL[CID][i][1];
		CCD[CID].MAX_DIF_LOCAL[i]=STAT_LOCAL[CID][i][2];
		CCD[CID].AVE_DIF_CRPIX[i]=STAT_CRPIX[CID][i][0];
		CCD[CID].RMS_DIF_CRPIX[i]=STAT_CRPIX[CID][i][1];
		CCD[CID].MAX_DIF_CRPIX[i]=STAT_CRPIX[CID][i][2];
		CCD[CID].AVE_DIF_IMPXL[i]=STAT_IMPXL[CID][i][0];
		CCD[CID].RMS_DIF_IMPXL[i]=STAT_IMPXL[CID][i][1];
		CCD[CID].MAX_DIF_IMPXL[i]=STAT_IMPXL[CID][i][2];
		CCD[CID].AVE_DIF_RADEC[i]=STAT_RADEC[CID][i][0];
		CCD[CID].RMS_DIF_RADEC[i]=STAT_RADEC[CID][i][1];
		CCD[CID].MAX_DIF_RADEC[i]=STAT_RADEC[CID][i][2];
	}
	
	F_DELint1(NUM);
	F_DELdouble3(NUM_CCD+1,2,DATA_RADEC);
	F_DELdouble3(NUM_CCD+1,2,DATA_CRPIX);
	F_DELdouble3(NUM_CCD+1,2,DATA_IMPXL);
	F_DELdouble3(NUM_CCD+1,2,DATA_LOCAL);
	F_DELdouble3(NUM_CCD+1,2,STAT_RADEC);
	F_DELdouble3(NUM_CCD+1,2,STAT_CRPIX);
	F_DELdouble3(NUM_CCD+1,2,STAT_IMPXL);
	F_DELdouble3(NUM_CCD+1,2,STAT_LOCAL);
}
void CL_ANA::CALC_LOCALDISTORTION(){
        F_DIFFSIP(ORDER_PSIP,CCD[NUM_CCD].PSIP[0],CCD[NUM_CCD].dPSIP[0][0],CCD[NUM_CCD].dPSIP[0][1]);
        F_DIFFSIP(ORDER_PSIP,CCD[NUM_CCD].PSIP[1],CCD[NUM_CCD].dPSIP[1][0],CCD[NUM_CCD].dPSIP[1][1]);
	CALC_DIST();	
}
void CL_ANA::CALC_PV(){
	for(OID=0;OID<NUM_CCD+1;OID++){
		CCD[OID].PV[0]=F_NEWdouble1(40);
		CCD[OID].PV[1]=F_NEWdouble1(40);
	}

	FIT_GLOBL(99,99,99,CCD[NUM_CCD].PV);

	int i,j,k,ij;
	double TPV[2][8][8];
	for(k=0;k< 2;k++){
	ij=0;
	for(i=0;i< 8;i++)
	for(j=0;j< 8;j++)
	if(i+j<8){
		TPV[k][i][j]=CCD[NUM_CCD].PV[k][ij];
		ij++;
	}else{
		TPV[k][i][j]=0;
	}}

	for(j=0;j< 2;j++){
		CCD[NUM_CCD].PV[j][ 0]=TPV[j][0][0];
		CCD[NUM_CCD].PV[j][ 1]=TPV[j][1][0];
		CCD[NUM_CCD].PV[j][ 2]=TPV[j][0][1];
		CCD[NUM_CCD].PV[j][ 3]=0;
		CCD[NUM_CCD].PV[j][ 4]=TPV[j][2][0];
		CCD[NUM_CCD].PV[j][ 5]=TPV[j][1][1];
		CCD[NUM_CCD].PV[j][ 6]=TPV[j][0][2];
		CCD[NUM_CCD].PV[j][ 7]=TPV[j][3][0];
		CCD[NUM_CCD].PV[j][ 8]=TPV[j][2][1];
		CCD[NUM_CCD].PV[j][ 9]=TPV[j][1][2];
		CCD[NUM_CCD].PV[j][10]=TPV[j][0][3];
		CCD[NUM_CCD].PV[j][11]=0;
		CCD[NUM_CCD].PV[j][12]=TPV[j][4][0];
		CCD[NUM_CCD].PV[j][13]=TPV[j][3][1];
		CCD[NUM_CCD].PV[j][14]=TPV[j][2][2];
		CCD[NUM_CCD].PV[j][15]=TPV[j][1][3];
		CCD[NUM_CCD].PV[j][16]=TPV[j][0][4];
		CCD[NUM_CCD].PV[j][17]=TPV[j][5][0];
		CCD[NUM_CCD].PV[j][18]=TPV[j][4][1];
		CCD[NUM_CCD].PV[j][19]=TPV[j][3][2];
		CCD[NUM_CCD].PV[j][20]=TPV[j][2][3];
		CCD[NUM_CCD].PV[j][21]=TPV[j][1][4];
		CCD[NUM_CCD].PV[j][22]=TPV[j][0][5];
		CCD[NUM_CCD].PV[j][23]=0;
		CCD[NUM_CCD].PV[j][24]=TPV[j][6][0];
		CCD[NUM_CCD].PV[j][25]=TPV[j][5][1];
		CCD[NUM_CCD].PV[j][26]=TPV[j][4][2];
		CCD[NUM_CCD].PV[j][27]=TPV[j][3][3];
		CCD[NUM_CCD].PV[j][28]=TPV[j][2][4];
		CCD[NUM_CCD].PV[j][29]=TPV[j][1][5];
		CCD[NUM_CCD].PV[j][30]=TPV[j][0][6];
		CCD[NUM_CCD].PV[j][31]=TPV[j][7][0];
		CCD[NUM_CCD].PV[j][32]=TPV[j][6][1];
		CCD[NUM_CCD].PV[j][33]=TPV[j][5][2];
		CCD[NUM_CCD].PV[j][34]=TPV[j][4][3];
		CCD[NUM_CCD].PV[j][35]=TPV[j][3][4];
		CCD[NUM_CCD].PV[j][36]=TPV[j][2][5];
		CCD[NUM_CCD].PV[j][37]=TPV[j][1][6];
		CCD[NUM_CCD].PV[j][38]=TPV[j][0][7];
		CCD[NUM_CCD].PV[j][39]=0;
	}
}

