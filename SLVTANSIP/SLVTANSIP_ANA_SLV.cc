//--------------------------------------------------
//SLVTANSIP_ANA_SLV.cc
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#include<iostream>
#include<cstring>
#include<cmath>
#include"SLVTANSIP_ANA.h"

using namespace std;
void CL_ANA::SLV_DATA(){
	if(STDOUT==1||STDOUT==2)cout << "--- SOLVE DATA : START ---" <<endl;
//REJECTION
	if(MODE_REJ==1){
	if(STDOUT==1||STDOUT==2)cout << "--- SOLVE DATA : REJECT BAD OBJECTS ---" <<endl;
	REJ_BAD();
	CHECK_PRM2nd();
	}
//CCD POSITIONS
	MEAS_CR();
	if(MODE_CCDPOS==1||MODE_CCDPOSH==1){
	if(STDOUT==1||STDOUT==2)cout << "--- SOLVE DATA : DETERMINE CCD POSITIONS ---" <<endl;
	MEAS_CCDPOS();
	}
//POSITIONS
	if(STDOUT==1||STDOUT==2)cout << "--- SOLVE DATA : CALCULATE POSITIONS ---" <<endl;
	CALC_POSITIONS();
//CDSIP
	if(STDOUT==1||STDOUT==2)cout << "--- SOLVE DATA : CALCULATE CD and SIP ---" <<endl;
	CALC_DISTROTION();
	if(STDOUT==1||STDOUT==2)cout << "--- SOLVE DATA : SET LOCAL CCD ---" <<endl;
	SET_LOCAL();

	if(STDOUT==1||STDOUT==2)cout << "--- SOLVE DATA : END ---" <<endl;
}
void CL_ANA::REJ_BAD(){
	double DIF[2];
	CALC_X_GLOBL();
	if(strcmp(MODE_CR,"VAL")==0){
		CALC_X_IMWLD();
		FIT_GLOBL(1,1,6,CCD[NUM_CCD].CDPSIP);
		CALC_X_GLOBLfromIMWLD();
		CALC_DIFF(6,16,DIFF);
		if(STDOUT==2)cout<<"RMS : "<<hypot(DIFF[0][1],DIFF[1][1])<<" (pixel)"<<endl;
		for(OID=0;OID<NUM_OBJ;OID++){
			DIF[0]=OBJ[OID].X_GLOBL[0]-OBJ[OID].X_GLOBL_SIPfromRADEC[0];
			DIF[1]=OBJ[OID].X_GLOBL[1]-OBJ[OID].X_GLOBL_SIPfromRADEC[1];
			if(hypot(DIF[0],DIF[1])>CLIP_SIGMA*hypot(DIFF[0][1],DIFF[1][1]))
			OBJ[OID].FLAG_OBJ=0;
		}
	}else{
		if(strcmp(MODE_CR,"AUTO")==0||strcmp(MODE_CR,"OAXIS")==0){
			CALC_X_CENTER();
			SET_CENTERCR();
		}
		CALC_X_CRPIXGLOBL();
		FIT_GLOBL(0,4,0,CCD[NUM_CCD].CDASIP);
		CALC_X_RADECfromCRPIXGLOBL();
		CALC_DIFF(0, 8,DIFF);
		if(STDOUT==2)cout<<"RMS : "<<hypot(DIFF[0][1],DIFF[1][1])<<" (degree)"<<endl;
		for(OID=0;OID<NUM_OBJ;OID++){
			DIF[0]=OBJ[OID].X_RADEC[0]-OBJ[OID].X_RADEC_SIPfromLOCAL[0];
			DIF[1]=OBJ[OID].X_RADEC[1]-OBJ[OID].X_RADEC_SIPfromLOCAL[1];
			if(hypot(DIF[0],DIF[1])>CLIP_SIGMA*hypot(DIFF[0][1],DIFF[1][1]))
			OBJ[OID].FLAG_OBJ=0;
		}
	}
	for(CID=0;CID<NUM_CCD+1;CID++)
	CCD[CID].NUM_FIT=0;
	NUM_FIT=0;
	NUM_REJ=0;
	for(OID=0;OID<NUM_OBJ;OID++)
	if(OBJ[OID].FLAG_OBJ==1){
		CID=OBJ[OID].ID_CHIP;
		CCD[CID].NUM_FIT++;
		CCD[NUM_CCD].NUM_FIT++;
		NUM_FIT++;
	}else{
		NUM_REJ++;
	}
	if(STDOUT==2)
	for(CID=0;CID<NUM_CCD+1;CID++)
	cout<<"FITNUM"<<CID<<" : "<<CCD[CID].NUM_FIT<<endl;
	if(STDOUT==2)cout<<"ALLFITNUM : "<<NUM_FIT<<endl;
	if(STDOUT==2)cout<<"ALLREJNUM : "<<NUM_REJ<<endl;

	if(strcmp(MODE_CR,"VAL")==0){
		CALC_X_GLOBLfromIMWLD();
		CALC_DIFF(6,16,DIFF);
		if(STDOUT==2)cout<<"RMS : "<<hypot(DIFF[0][1],DIFF[1][1])<<" (pixel)"<<endl;
	}else{
		CALC_X_RADECfromCRPIXGLOBL();
		CALC_DIFF(0, 8,DIFF);
		if(STDOUT==2)cout<<"RMS : "<<hypot(DIFF[0][1],DIFF[1][1])<<" (degree)"<<endl;
	}
}
void CL_ANA::MEAS_CR(){
	CALC_X_GLOBL();
	if(strcmp(MODE_CR,"VAL")==0){
		CALC_X_IMWLD();
		CALC_CRPIX();
		CALC_X_CRPIXGLOBL();
	}else{
		if(strcmp(MODE_CR,"AUTO")==0||strcmp(MODE_CR,"OAXIS")==0){
			CALC_X_CENTER();
			SET_CENTERCR();
		}
		CALC_X_CRPIXGLOBL();
		CALC_CRVAL();
		CALC_X_IMWLD();
	}
	if(STDOUT==2)cout<<"CRPIX : ( " << CRPIX[0] << " , " << CRPIX[1] << " )"<<endl;
	if(STDOUT==2)cout<<"CRVAL : ( " << CRVAL[0] << " , " << CRVAL[1] << " )"<<endl;
	CCD[NUM_CCD].CRPIX[0]=CRPIX[0];
	CCD[NUM_CCD].CRPIX[1]=CRPIX[1];
	CCD[NUM_CCD].CRVAL[0]=CRVAL[0];
	CCD[NUM_CCD].CRVAL[1]=CRVAL[1];
}
void CL_ANA::MEAS_CCDPOS(){
	if(MODE_CCDPOS==1){
	MEAS_CCDPOS_T();
	MEAS_CCDPOS_XY();
	}
	if(MODE_CCDPOSH==1)
	MEAS_CCDPOS_XYT();
	if(STDOUT==2)for(CID=0;CID<NUM_CCD;CID++)cout<<"CHIPID : "<<CID<<"	: X : "<<CCD[CID].GPOS[0]<<"	: Y : "<<CCD[CID].GPOS[1]<<"	: T : "<<CCD[CID].GPOS[2]<<endl;
	MEAS_CR();
}
void CL_ANA::CALC_POSITIONS(){
	CALC_X_GLOBL();
	CALC_X_CRPIXGLOBL();
	CALC_X_IMWLD();
}
void CL_ANA::CALC_POSITIONS_LOCAL(){
	CALC_X_CRPIXLOCAL();
	CALC_X_IMPXLLOCAL();
}
void CL_ANA::CALC_DISTROTION(){
	FIT_GLOBL(0,4,1,CCD[NUM_CCD].CDASIP);
	DIV_ASIP();
//	FIT_GLOBL(1,1,3,CCD[NUM_CCD].CDPSIP);
//	DIV_PSIP();
	CALC_X_IMPXLGLOBL();
	FIT_GLOBL(1,2,4,CCD[NUM_CCD].PSIP);
	SET_PSIP();
}
void CL_ANA::SET_LOCAL(){
	ROT_CRCDSIP();
}

