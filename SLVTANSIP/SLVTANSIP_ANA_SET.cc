//--------------------------------------------------
//SLVTANSIP_ANA_SET.cc
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
#include"SLVTANSIP_SUB.h"

using namespace std;
void CL_ANA::SET_DATA(char* prmfile,char* objfile){
	sprintf(NAME_PRM,prmfile);
	sprintf(NAME_OBJ,objfile);

	SET_PRM1st();
	if(STDOUT==1||STDOUT==2)cout << "--- SET DATA : START ---" <<endl;
	if(STDOUT==2)cout << "paramfile  : " <<NAME_PRM<<endl;
	if(STDOUT==2)cout << "objectfile : " <<NAME_OBJ<<endl;
	CHECK_PRM1st();
	if(FLAG_ANA==0)return;

	NEW_MEMORY();
	SET_PRM2nd();
	CHECK_PRM2nd();
	
	if(STDOUT==2)SHOW_ANA();
	if(STDOUT==2)SHOW_CCD(0);
	if(STDOUT==2)SHOW_CCD(NUM_CCD);
	if(STDOUT==2)SHOW_OBJ(0);
	if(STDOUT==2)SHOW_OBJ(NUM_OBJ-1);
	if(STDOUT==1||STDOUT==2)cout << "--- SET DATA : END ---" <<endl;
}
void CL_ANA::SET_PRM1st(){
	ifstream pin,oin;
	char fin[6][100];

	sprintf(INSTR,"HSC");
	FLAG_ANA=1;
	NUM_CCD=104;
	NUM_OBJ=0;
	ORDER_ASIP=9;
	ORDER_PSIP=9;
	ORDER_LSIP=4;
	STDOUT=2;

	pin.open(NAME_PRM);
	oin.open(NAME_OBJ);
	while((pin>>fin[0]>>fin[1]>>fin[2])!=0){
		if(strcmp("INSTR:",fin[0])==0)
		sprintf(INSTR,fin[1]);
		if(strcmp("NCCD:",fin[0])==0)
		NUM_CCD=atoi(fin[1]);
		if(strcmp("ASIPORDER:",fin[0])==0)
		ORDER_ASIP=atof(fin[1]);
		if(strcmp("PSIPORDER:",fin[0])==0)
		ORDER_PSIP=atof(fin[1]);
		if(strcmp("LSIPORDER:",fin[0])==0)
		ORDER_LSIP=atoi(fin[1]);
		if(strcmp("STDOUT:",fin[0])==0)
		STDOUT=atoi(fin[1]);
	}

	pin.close();
	while((oin>>fin[0]>>fin[1]>>fin[2]>>fin[3]>>fin[4]>>fin[5])!=0)
	NUM_OBJ++;
	NUM_FIT=NUM_OBJ;
	oin.close();
}
void CL_ANA::SET_PRM2nd(){
	if(strcmp(INSTR,"SC")==0){
		SET_INITCCD_SC();
	}else{
		SET_INITCCD_HSC();
	}

	ifstream pin,oin;
	char fin[6][100],fccd[100];

	sprintf(MODE_CR,"PIX");
	sprintf(MODE_OA,"REV");
	MODE_CCDPOS=0;
	MODE_CCDPOSH=0;
	MODE_REJ=0;
	CRPIX[0]=0.0;
	CRPIX[1]=0.0;
	CRVAL[0]=0.0;
	CRVAL[1]=0.0;
	CLIP_SIGMA=2.0;
	GPOS_BASIS[0]=0.0;
	GPOS_BASIS[1]=0.0;
	GPOS_BASIS[2]=0.0;
	EXTRACALC=0;
	FILEOUT=0;
	sprintf(DIR_CCD,"./");
	sprintf(DIR_OBJ,"./");

	pin.open(NAME_PRM);
	oin.open(NAME_OBJ);
	while((pin>>fin[0]>>fin[1]>>fin[2])!=0){
		if(strcmp("CRMODE:",fin[0])==0)
		sprintf(MODE_CR,fin[1]);
		if(strcmp("OAMODE:",fin[0])==0)
		sprintf(MODE_OA,fin[1]);
		if(strcmp("CCDPMODE:",fin[0])==0)
		MODE_CCDPOS=atoi(fin[1]);
		if(strcmp("CCDPHMODE:",fin[0])==0)
		MODE_CCDPOSH=atoi(fin[1]);
		if(strcmp("REJMODE:",fin[0])==0)
		MODE_REJ=atoi(fin[1]);
		if(strcmp("CRPIX1:",fin[0])==0)
		CRPIX[0]=atof(fin[1]);
		if(strcmp("CRPIX2:",fin[0])==0)
		CRPIX[1]=atof(fin[1]);
		if(strcmp("CRVAL1:",fin[0])==0)
		CRVAL[0]=atof(fin[1]);
		if(strcmp("CRVAL2:",fin[0])==0)
		CRVAL[1]=atof(fin[1]);
		if(strcmp("CLIPSIGMA:",fin[0])==0)
		CLIP_SIGMA=atof(fin[1]);
		if(strcmp("BASISPOSX:",fin[0])==0)
		GPOS_BASIS[0]=atof(fin[1]);
		if(strcmp("BASISPOSY:",fin[0])==0)
		GPOS_BASIS[1]=atof(fin[1]);
		if(strcmp("BASISPOST:",fin[0])==0)
		GPOS_BASIS[2]=atof(fin[1]);
		if(strcmp("EXTRACALC:",fin[0])==0)
		EXTRACALC=atoi(fin[1]);
		if(strcmp("PVCALC:",fin[0])==0)
		PVCALC=atoi(fin[1]);
		if(strcmp("FILEOUT:",fin[0])==0)
		FILEOUT=atoi(fin[1]);
		if(strcmp("PAFOUT:",fin[0])==0)
		PAFOUT=atoi(fin[1]);
		if(strcmp("PVOUT:",fin[0])==0)
		PVOUT=atoi(fin[1]);
		if(strcmp("CCDFILEDIR:",fin[0])==0)
		sprintf(DIR_CCD,fin[1]);
		if(strcmp("OBJFILEDIR:",fin[0])==0)
		sprintf(DIR_OBJ,fin[1]);
		for(CID=0;CID<NUM_CCD;CID++){
			sprintf(fccd,"HSCIGPOS%03d_X:",CID);
			if(strcmp(fccd,fin[0])==0)
			CCD[CID].GPOS[0]=atof(fin[1]);
			sprintf(fccd,"HSCIGPOS%03d_Y:",CID);
			if(strcmp(fccd,fin[0])==0)
			CCD[CID].GPOS[1]=atof(fin[1]);
			sprintf(fccd,"HSCIGPOS%03d_T:",CID);
			if(strcmp(fccd,fin[0])==0)
			CCD[CID].GPOS[2]=atof(fin[1]);
		}
	}

	int i,DIRLEN;
	char DOT[2],DIR[100];
	if(strcmp(DIR_CCD,"AUTO")==0){
		sprintf(DOT,".");
		for(i=strlen(NAME_OBJ)-1;i>-0.5;i--)
		if(NAME_OBJ[i]==DOT[0]){
			DIRLEN=i;
			break;
		}
		for(i=0;i<DIRLEN;i++)
		DIR[i]=NAME_OBJ[i];
		DIR[i]='\0';
		sprintf(DIR_CCD,DIR);
	}
	
	if(strcmp(DIR_OBJ,"AUTO")==0){
		sprintf(DOT,".");
		for(i=strlen(NAME_OBJ)-1;i>-0.5;i--)
		if(NAME_OBJ[i]==DOT[0]){
			DIRLEN=i;
			break;
		}
		for(i=0;i<DIRLEN;i++)
		DIR[i]=NAME_OBJ[i];
		DIR[i]='\0';
		sprintf(DIR_OBJ,DIR);
	}

	pin.close();
	OID=0;
	while((oin>>fin[0]>>fin[1]>>fin[2]>>fin[3]>>fin[4]>>fin[5])!=0){
		OBJ[OID].ID_OBJ    = atoll(fin[0]);
		OBJ[OID].ID_CHIP   = atoi(fin[1]);
		OBJ[OID].X_LOCAL[0]= atof(fin[2]);
		OBJ[OID].X_LOCAL[1]= atof(fin[3]);
		OBJ[OID].X_RADEC[0]= atof(fin[4]);
		OBJ[OID].X_RADEC[1]= atof(fin[5]);
		if(isfinite(OBJ[OID].ID_OBJ)&&
		   isfinite(OBJ[OID].ID_CHIP)&&
		   isfinite(OBJ[OID].X_LOCAL[0])&&
		   isfinite(OBJ[OID].X_LOCAL[1])&&
		   isfinite(OBJ[OID].X_RADEC[0])&&
		   isfinite(OBJ[OID].X_RADEC[1])&&
		   OBJ[OID].ID_CHIP<NUM_CCD-0.5){
		OBJ[OID].FLAG_OBJ  = 1;
		}else{
		OBJ[OID].FLAG_OBJ  = 0;
		}
		CCD[OBJ[OID].ID_CHIP].NUM_OBJ+=1;
		CCD[NUM_CCD].NUM_OBJ+=1;
		for(i=0;i<2;i++){
			OBJ[OID].X_GLOBL[i]=0;
			OBJ[OID].X_CRPIXGLOBL[i]=0;
			OBJ[OID].X_CRPIXLOCAL[i]=0;
			OBJ[OID].X_IMPXLGLOBL[i]=0;
			OBJ[OID].X_IMPXLLOCAL[i]=0;
			OBJ[OID].X_IMWLD[i]=0;
			OBJ[OID].X_LOCAL_TANfromRADEC[i]=0;
			OBJ[OID].X_GLOBL_TANfromRADEC[i]=0;
			OBJ[OID].X_CRPIXLOCAL_TANfromRADEC[i]=0;
			OBJ[OID].X_CRPIXGLOBL_TANfromRADEC[i]=0;
			OBJ[OID].X_IMPXLLOCAL_TANfromLOCAL[i]=0;
			OBJ[OID].X_IMPXLGLOBL_TANfromGLOBL[i]=0;
			OBJ[OID].X_IMWLD_TANfromLOCAL[i]=0;
			OBJ[OID].X_IMWLD_TANfromGLOBL[i]=0;
			OBJ[OID].X_RADEC_TANfromLOCAL[i]=0;
			OBJ[OID].X_RADEC_TANfromGLOBL[i]=0;
			OBJ[OID].X_LOCAL_SIPfromRADEC[i]=0;
			OBJ[OID].X_GLOBL_SIPfromRADEC[i]=0;
			OBJ[OID].X_CRPIXLOCAL_SIPfromRADEC[i]=0;
			OBJ[OID].X_CRPIXGLOBL_SIPfromRADEC[i]=0;
			OBJ[OID].X_IMPXLLOCAL_SIPfromLOCAL[i]=0;
			OBJ[OID].X_IMPXLGLOBL_SIPfromGLOBL[i]=0;
			OBJ[OID].X_IMWLD_SIPfromLOCAL[i]=0;
			OBJ[OID].X_IMWLD_SIPfromGLOBL[i]=0;
			OBJ[OID].X_RADEC_SIPfromLOCAL[i]=0;
			OBJ[OID].X_RADEC_SIPfromGLOBL[i]=0;
		}

		OID++;
	}

	for(CID=0;CID<NUM_CCD+1;CID++){
		CCD[CID].NUM_FIT=CCD[CID].NUM_OBJ;
		CCD[CID].GPOS_INIT[0]=CCD[CID].GPOS[0];
		CCD[CID].GPOS_INIT[1]=CCD[CID].GPOS[1];
		CCD[CID].GPOS_INIT[2]=CCD[CID].GPOS[2];
		CCD[CID].AVE_DIF_LOCAL[0]=0.0;
		CCD[CID].AVE_DIF_LOCAL[1]=0.0;
		CCD[CID].AVE_DIF_RADEC[0]=0.0;
		CCD[CID].AVE_DIF_RADEC[1]=0.0;
		CCD[CID].AVE_DIF_CRPIX[0]=0.0;
		CCD[CID].AVE_DIF_CRPIX[1]=0.0;
		CCD[CID].AVE_DIF_IMPXL[0]=0.0;
		CCD[CID].AVE_DIF_IMPXL[1]=0.0;
		CCD[CID].RMS_DIF_LOCAL[0]=0.0;
		CCD[CID].RMS_DIF_LOCAL[1]=0.0;
		CCD[CID].RMS_DIF_RADEC[0]=0.0;
		CCD[CID].RMS_DIF_RADEC[1]=0.0;
		CCD[CID].RMS_DIF_CRPIX[0]=0.0;
		CCD[CID].RMS_DIF_CRPIX[1]=0.0;
		CCD[CID].RMS_DIF_IMPXL[0]=0.0;
		CCD[CID].RMS_DIF_IMPXL[1]=0.0;
		CCD[CID].MAX_DIF_LOCAL[0]=0.0;
		CCD[CID].MAX_DIF_LOCAL[1]=0.0;
		CCD[CID].MAX_DIF_RADEC[0]=0.0;
		CCD[CID].MAX_DIF_RADEC[1]=0.0;
		CCD[CID].MAX_DIF_CRPIX[0]=0.0;
		CCD[CID].MAX_DIF_CRPIX[1]=0.0;
		CCD[CID].MAX_DIF_IMPXL[0]=0.0;
		CCD[CID].MAX_DIF_IMPXL[1]=0.0;
	}
	CCD[NUM_CCD].CRPIX[0]=CRPIX[0];
	CCD[NUM_CCD].CRPIX[1]=CRPIX[1];
	CCD[NUM_CCD].CRVAL[0]=CRVAL[0];
	CCD[NUM_CCD].CRVAL[1]=CRVAL[1];
	oin.close();
}
void CL_ANA::CHECK_PRM1st(){
	if(STDOUT==2)cout<<"-- PARAMETER CHECK 1st --"<<endl;
	if(strcmp(INSTR,"SC")||strcmp(INSTR,"HSC")){
		if(STDOUT==2)cout<<"OK:INSTR"<<endl;
	}else{
		cout << "WARNING : INSTR = " << INSTR << " is not SC nor HSC : " 
		     << "CHANGE INSTR to HSC" <<endl;
		sprintf(INSTR,"HSC");
	}
	if(NUM_CCD<1){
		cout << "WARNING : NUM_CCD = " << NUM_CCD << " < 1 : "
		     << "CHANGE NUM_CCD to 104" <<endl;
		NUM_CCD=104;
	}else{
		if(STDOUT==2)cout<<"OK:CCDNUM"<<endl;
	}
	if(ORDER_ASIP<2||ORDER_ASIP>9.5){
		cout << "WARNING : ASIPORDER = " << ORDER_ASIP << " < 2 or > 10: " 
		     << "CHANGE ORDER_ASIP to 9" <<endl;
		ORDER_ASIP=9;
	}else{
		if(STDOUT==2)cout<<"OK:ASIP_ORDER"<<endl;
	}
	if(ORDER_PSIP<2||ORDER_PSIP>9.5){
		cout << "WARNING : PSIPORDER = " << ORDER_PSIP << " < 2 or > 10: " 
		     << "CHANGE ORDER_PSIP to 9" <<endl;
		ORDER_PSIP=9;
	}else{
		if(STDOUT==2)cout<<"OK:PSIP_ORDER"<<endl;
	}
	if(NUM_FIT<0.5){
		cout << "ERROR : OBJECT NUMBER = " << NUM_FIT << " < 1 : " 
		     << "TERMINATE ANALYSIS" <<endl;
		FLAG_ANA=0;
	}else{
		if(STDOUT==2)cout<<"OK:OBJNUM"<<endl;
	}
}
void CL_ANA::CHECK_PRM2nd(){
	if(STDOUT==2)cout<<"-- PARAMETER CHECK 2nd --"<<endl;
	int FLAG_CID;
	FLAG_CID=1;
	for(CID=0;CID<NUM_CCD;CID++)
	if(CCD[CID].NUM_FIT<1.5){
		FLAG_CID=0;
		cout << "ERROR : OBJECT NUMBER of CHIPID "<<CID<<" = " << CCD[CID].NUM_FIT << " < 2 : " 
		     << "CHANGE CCDPOSMODE to 0" <<endl;
		MODE_CCDPOS=0;
		MODE_CCDPOSH=0;
	}
	if(STDOUT==2&&FLAG_CID==1)cout<<"OK:OBJNUM in each CCD"<<endl;

	if(strcmp(MODE_CR,"AUTO")==0||strcmp(MODE_CR,"PIX")==0||strcmp(MODE_CR,"VAL")==0||strcmp(MODE_CR,"OAXIS")==0){
		if(STDOUT==2)cout<<"OK:CRMODE"<<endl;
	}else{
		cout << "WARNING : CRMODE = " << MODE_CR << " is not 'AUTO' nor 'PIX' nor 'VAL' nor 'OAXIS' : " 
		     << "CHANGE CRMODE to 'AUTO'" <<endl;
		sprintf(MODE_CR,"AUTO");
	}
	if(MODE_CCDPOS==0||MODE_CCDPOS==1){
		if(STDOUT==2)cout<<"OK:CCDPOSMODE"<<endl;
	}else{
		cout << "WARNING : CCDPOSMODE = " << MODE_CCDPOS << " is not 0 nor 1 : " 
		     << "CHANGE CCDPOSMODE to 0" <<endl;
		MODE_CCDPOS=0;
	}
	if(NUM_FIT>0.5*(ORDER_ASIP+1)*(ORDER_ASIP+2)+1){
		if(STDOUT==2)cout<<"OK:ASIP_ORDER"<<endl;
	}else{
		cout << "WARNING : ASIP_ORDER = " << ORDER_ASIP << " is too large : ";
		int PORDER;
		for(PORDER=ORDER_ASIP+1;PORDER>1;PORDER--)
		if(NUM_FIT>0.5*(PORDER+1)*(PORDER+2)+1){
		ORDER_ASIP=PORDER;
		break;
		}
		cout << "CHANGE ASIP_ORDER to "<< ORDER_ASIP <<endl;
	}
	if(NUM_FIT>0.5*(ORDER_PSIP+1)*(ORDER_PSIP+2)+1){
		if(STDOUT==2)cout<<"OK:PSIP_ORDER"<<endl;
	}else{
		cout << "WARNING : PSIP_ORDER = " << ORDER_PSIP << " is too large : ";
		int PORDER;
		for(PORDER=ORDER_PSIP+1;PORDER>1;PORDER--)
		if(NUM_FIT>0.5*(PORDER+1)*(PORDER+2)+1){
		ORDER_PSIP=PORDER;
		break;
		}
		cout << "CHANGE PSIP_ORDER to "<< ORDER_PSIP <<endl;
	}
	FLAG_CID=1;
	for(CID=0;CID<NUM_CCD;CID++)
	if(CCD[CID].NUM_FIT>0.5*(ORDER_LSIP+1)*(ORDER_LSIP+2)+1){
	}else{
		FLAG_CID=0;
		cout << "WARNING : LSIP_ORDER of CCD "<<CID<<" = " << ORDER_LSIP << " is too large : ";
		int PORDER;
		for(PORDER=ORDER_PSIP+1;PORDER>1;PORDER--)
		if(CCD[CID].NUM_FIT>0.5*(PORDER+1)*(PORDER+2)+1){
		ORDER_LSIP=PORDER;
		break;
		}
		cout << "CHANGE LSIP_ORDER to "<< ORDER_LSIP <<endl;
	}
	if(STDOUT==2&&FLAG_CID==1)cout<<"OK:LSIP_ORDER"<<endl;
}
void CL_ANA::NEW_MEMORY(){
	int i;

	CCD = new CL_CCD[NUM_CCD+1];
	for(CID=0;CID<NUM_CCD+1;CID++){
		for(i=0;i<2;i++){
			CCD[CID].ASIP[i]       = F_NEWdouble1((ORDER_ASIP+1)*(ORDER_ASIP+2));
			CCD[CID].PSIP[i]       = F_NEWdouble1((ORDER_PSIP+1)*(ORDER_PSIP+2));
			CCD[CID].LCoef[i]      = F_NEWdouble1((ORDER_LSIP+1)*(ORDER_LSIP+2));
			CCD[CID].LCDSIP[i]     = F_NEWdouble1((ORDER_LSIP+1)*(ORDER_LSIP+2));
			CCD[CID].dLCDSIP[i][0] = F_NEWdouble1((ORDER_LSIP+1)*(ORDER_LSIP+2));
			CCD[CID].dLCDSIP[i][1] = F_NEWdouble1((ORDER_LSIP+1)*(ORDER_LSIP+2));
			CCD[CID].CDASIP[i]     = F_NEWdouble1((ORDER_ASIP+1)*(ORDER_ASIP+2));
			CCD[CID].CDPSIP[i]     = F_NEWdouble1((ORDER_PSIP+1)*(ORDER_PSIP+2));
			CCD[CID].dCDPSIP[i][0] = F_NEWdouble1((ORDER_PSIP+1)*(ORDER_PSIP+2));
			CCD[CID].dCDPSIP[i][1] = F_NEWdouble1((ORDER_PSIP+1)*(ORDER_PSIP+2));
			CCD[CID].dPSIP[i][0]   = F_NEWdouble1((ORDER_PSIP+1)*(ORDER_PSIP+2));
			CCD[CID].dPSIP[i][1]   = F_NEWdouble1((ORDER_PSIP+1)*(ORDER_PSIP+2));
		}
	}
	OBJ = new CL_OBJ[NUM_OBJ  ];
}
void CL_ANA::DEL_MEMORY(){
	int i;

	for(CID=0;CID<NUM_CCD+1;CID++){
		for(i=0;i<2;i++){
			delete [] CCD[CID].ASIP[i];
			delete [] CCD[CID].PSIP[i];
			delete [] CCD[CID].LCoef[i];
			delete [] CCD[CID].LCDSIP[i];
			delete [] CCD[CID].dLCDSIP[i][0];
			delete [] CCD[CID].dLCDSIP[i][1];
			delete [] CCD[CID].CDASIP[i];
			delete [] CCD[CID].CDPSIP[i];
			delete [] CCD[CID].dCDPSIP[i][0];
			delete [] CCD[CID].dCDPSIP[i][1];
			delete [] CCD[CID].dPSIP[i][0];
			delete [] CCD[CID].dPSIP[i][1];
			if(EXTRACALC==1&&PVCALC==1)
			delete [] CCD[CID].PV[i];
		}
	}
	delete [] CCD;
	delete [] OBJ;
}
void CL_ANA::SHOW_ANA(){
	cout <<"--- ANALYSIS INFO ---"<<endl;
	cout <<"INSTR		: "<<INSTR<<endl;
	cout <<"NUM_CCD		: "<<NUM_CCD<<endl;
	cout <<"NUM_OBJ		: "<<NUM_OBJ<<endl;
	cout <<"CRMODE		: "<<MODE_CR<<endl;
//	cout <<"OAMODE		: "<<MODE_OA<<endl;
	cout <<"CCDPOSMODE	: "<<MODE_CCDPOS<<endl;
	cout <<"CCDPOSHMODE	: "<<MODE_CCDPOSH<<endl;
	cout <<"REJMODE		: "<<MODE_REJ<<endl;
	cout <<"CRPIX1		: "<<CRPIX[0]<<endl;
	cout <<"CRPIX2		: "<<CRPIX[1]<<endl;
	cout <<"CRVAL1		: "<<CRVAL[0]<<endl;
	cout <<"CRVAL2		: "<<CRVAL[1]<<endl;
	cout <<"ASIPORDER	: "<<ORDER_ASIP<<endl;
	cout <<"PSIPORDER	: "<<ORDER_PSIP<<endl;
	cout <<"LSIPORDER	: "<<ORDER_PSIP<<endl;
	cout <<"CLIP_SIGMA	: "<<CLIP_SIGMA<<endl;
	cout <<"BASISPOS_X	: "<<GPOS_BASIS[0]<<endl;
	cout <<"BASISPOS_Y	: "<<GPOS_BASIS[1]<<endl;
	cout <<"BASISPOS_T	: "<<GPOS_BASIS[2]<<endl;
	cout <<"EXTRACALC	: "<<EXTRACALC<<endl;
	cout <<"STDOUT		: "<<STDOUT<<endl;
	cout <<"FILEOUT		: "<<FILEOUT<<endl;
	if(FILEOUT==1)
	cout <<"CCDFILE_DIR	: "<<DIR_CCD<<endl;
	if(FILEOUT==1)
	cout <<"OBJFILE_DIR	: "<<DIR_OBJ<<endl;
	cout <<"PAFOUT		: "<<PAFOUT<<endl;
	cout <<"PVOUT		: "<<PVOUT<<endl;
}
void CL_ANA::SET_CENTERCR(){
	CRPIX[0]=CENTER_PIXEL[0];
	CRPIX[1]=CENTER_PIXEL[1];
}

