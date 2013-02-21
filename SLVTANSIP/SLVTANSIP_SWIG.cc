//--------------------------------------------------
//SLVTANSIP_SWIG.cc
//
//Last Update 2013/03/01
//--------------------------------------------------

#include<iostream>
#include<stdio.h>
#include<fitsio.h>
#include"SLVTANSIP_ANA.h"

#define LEN_CCDX 2048
#define LEN_CCDY 4176

using namespace std;
CL_ANA* SLVTANSIP_SWIG_SET(std::string pafname,std::string objname){
	cout<<"--- SLVTANSIP SET SWIG START ---"<<endl;
	CL_ANA *ANA;
	char FPRM[100],FOBJ[100];
	ANA = new CL_ANA[1];
	sprintf(FPRM,pafname.c_str());
	sprintf(FOBJ,objname.c_str());
	ANA->SET_DATA(FPRM,FOBJ);

	return ANA;
	cout<<"--- SLVTANSIP SET SWIG END ---"<<endl;
}
void SLVTANSIP_SWIG_SLV(CL_ANA* ANA){
	cout<<"--- SLVTANSIP SLV SWIG START ---"<<endl;
	if(ANA->FLAG_ANA!=0)
	ANA->SLV_DATA();
	cout<<"--- SLVTANSIP SLV SWIG END ---"<<endl;
}
void SLVTANSIP_SWIG_EXT(CL_ANA* ANA){
	cout<<"--- SLVTANSIP EXT SWIG START ---"<<endl;
	if(ANA->FLAG_ANA!=0)
	if(ANA->EXTRACALC==1)
	ANA->EXT_DATA();
	cout<<"--- SLVTANSIP EXT SWIG END ---"<<endl;
}
void SLVTANSIP_SWIG_OUT(CL_ANA* ANA){
	cout<<"--- SLVTANSIP OUT SWIG START ---"<<endl;
	if(ANA->FLAG_ANA!=0)
	if(ANA->FILEOUT==1)
	ANA->OUT_DATA();
	cout<<"--- SLVTANSIP OUT SWIG END ---"<<endl;
}
void SLVTANSIP_SWIG_DEL(CL_ANA* ANA){
	cout<<"--- SLVTANSIP DEL SWIG START ---"<<endl;
	ANA->DEL_MEMORY();
	delete [] ANA;
	cout<<"--- SLVTANSIP DEL SWIG END ---"<<endl;
}
int  SLVTANSIP_SWIG_GET_OUTFLAG(CL_ANA *ANA){
	return ANA->FILEOUT;
}
string SLVTANSIP_SWIG_GET_OUTDIRCCD(CL_ANA *ANA){
	string DIR_CCD(ANA->DIR_CCD);
	return DIR_CCD;
}
string SLVTANSIP_SWIG_GET_OUTDIROBJ(CL_ANA *ANA){
	string DIR_OBJ(ANA->DIR_OBJ);
	return DIR_OBJ;
}
int  SLVTANSIP_SWIG_GET_CCDNUM(CL_ANA *ANA){
	return ANA->NUM_CCD;
}
double  SLVTANSIP_SWIG_GET_MAXR(CL_ANA *ANA){
	return ANA->MAX_R;
}
//TOOL

CL_ANA* SLVTANSIP_SWIG_MAKE_ANAfromfits(std::string CCDDIR){
	CL_ANA *ANA;
	ANA = new CL_ANA[1];
	ANA->MAKE_ANAfromfits(CCDDIR);

	return ANA;
}
void SLVTANSIP_SWIG_DEL_ANAfromfits(CL_ANA* ANA){
	ANA->DEL_ANAfromfits();
	delete [] ANA;
}
void CL_ANA::MAKE_ANAfromfits(std::string CCDDIR){
	int status;
	char FGCCD[100],keyward[100];
	fitsfile *fptr;

	sprintf(DIR_CCD,CCDDIR.c_str());
	status=0;
	sprintf(FGCCD,"%s/SLVTANSIP_GLOBAL.fits",DIR_CCD);
	fits_open_file(&fptr,FGCCD,READONLY,&status);
	fits_report_error(stderr,status);
	fits_read_key(fptr,TINT,"DET-ID" ,&NUM_CCD,NULL,&status);
	fits_report_error(stderr,status);
	fits_read_key(fptr,TINT,"NUM_OBJ",&NUM_OBJ,NULL,&status);
	fits_report_error(stderr,status);
	fits_read_key(fptr,TINT,"A_ORDER",&ORDER_ASIP,NULL,&status);
	fits_report_error(stderr,status);
	fits_read_key(fptr,TINT,"AP_ORDER",&ORDER_PSIP,NULL,&status);
	fits_report_error(stderr,status);
	fits_read_key(fptr,TDOUBLE,"MAX_R",&MAX_R,NULL,&status);
	fits_report_error(stderr,status);

	fits_close_file(fptr,&status);

	int i,j,ij;
	CCD = new CL_CCD[NUM_CCD+1];
	for(CID=0;CID<NUM_CCD+1;CID++)
	for(i=0;i<2;i++){
		CCD[CID].ASIP[i]       = F_NEWdouble1((ORDER_ASIP+1)*(ORDER_ASIP+2));
		CCD[CID].PSIP[i]       = F_NEWdouble1((ORDER_PSIP+1)*(ORDER_PSIP+2));
	}

	for(CID=0;CID<NUM_CCD+1;CID++){
		sprintf(FGCCD,"%s/SLVTANSIP_CCD%03d.fits",DIR_CCD,CID);
		if(CID==NUM_CCD)
		sprintf(FGCCD,"%s/SLVTANSIP_GLOBAL.fits",DIR_CCD);
		fits_open_file(&fptr,FGCCD,READONLY,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TINT,"DET-ID" ,&CCD[CID].ID_CHIP,NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TINT,"NUM_OBJ",&CCD[CID].NUM_OBJ,NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TINT,"NUM_FIT",&CCD[CID].NUM_FIT,NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"GPOS_X",&CCD[CID].GPOS[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"GPOS_Y",&CCD[CID].GPOS[1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"GPOS_T",&CCD[CID].GPOS[2],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"CRPIX1",&CCD[CID].CRPIX[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"CRPIX2",&CCD[CID].CRPIX[1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"CRVAL1",&CCD[CID].CRVAL[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"CRVAL2",&CCD[CID].CRVAL[1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"CD1_1",&CCD[CID].CD[0][0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"CD1_2",&CCD[CID].CD[0][1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"CD2_1",&CCD[CID].CD[1][0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"CD2_2",&CCD[CID].CD[1][1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"InvCD1_1",&CCD[CID].InvCD[0][0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"InvCD1_2",&CCD[CID].InvCD[0][1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"InvCD2_1",&CCD[CID].InvCD[1][0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"InvCD2_2",&CCD[CID].InvCD[1][1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"ANGLE",&CCD[CID].ANGLE,NULL,&status);
		fits_report_error(stderr,status);
		ij=0;
		for(i=0;i<ORDER_ASIP+1;i++)
		for(j=0;j<ORDER_ASIP+1;j++)
		if(i+j<ORDER_ASIP+1){
			sprintf(keyward,"A_%d_%d",i,j);
			fits_read_key(fptr,TDOUBLE,keyward,&CCD[CID].ASIP[0][ij],NULL,&status);
			fits_report_error(stderr,status);
			ij++;
		}
		ij=0;
		for(i=0;i<ORDER_ASIP+1;i++)
		for(j=0;j<ORDER_ASIP+1;j++)
		if(i+j<ORDER_ASIP+1){
			sprintf(keyward,"B_%d_%d",i,j);
			fits_read_key(fptr,TDOUBLE,keyward,&CCD[CID].ASIP[1][ij],NULL,&status);
			fits_report_error(stderr,status);
			ij++;
		}
		ij=0;
		for(i=0;i<ORDER_ASIP+1;i++)
		for(j=0;j<ORDER_ASIP+1;j++)
		if(i+j<ORDER_ASIP+1){
			sprintf(keyward,"AP_%d_%d",i,j);
			fits_read_key(fptr,TDOUBLE,keyward,&CCD[CID].PSIP[0][ij],NULL,&status);
			fits_report_error(stderr,status);
			ij++;
		}
		ij=0;
		for(i=0;i<ORDER_ASIP+1;i++)
		for(j=0;j<ORDER_ASIP+1;j++)
		if(i+j<ORDER_ASIP+1){
			sprintf(keyward,"BP_%d_%d",i,j);
			fits_read_key(fptr,TDOUBLE,keyward,&CCD[CID].PSIP[1][ij],NULL,&status);
			fits_report_error(stderr,status);
			ij++;
		}

		fits_read_key(fptr,TDOUBLE,"AVE_IMPX",&CCD[CID].AVE_DIF_IMPXL[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"AVE_IMPY",&CCD[CID].AVE_DIF_IMPXL[1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"AVE_CRX" ,&CCD[CID].AVE_DIF_CRPIX[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"AVE_CRY" ,&CCD[CID].AVE_DIF_CRPIX[1],NULL,&status);
		fits_report_error(stderr,status);
		sprintf(keyward,"AVE_LOX");
		if(CID==NUM_CCD)
		sprintf(keyward,"AVE_GLX");
		fits_read_key(fptr,TDOUBLE,keyward   ,&CCD[CID].AVE_DIF_LOCAL[0],NULL,&status);
		fits_report_error(stderr,status);
		sprintf(keyward,"AVE_LOY");
		if(CID==NUM_CCD)
		sprintf(keyward,"AVE_GLY");
		fits_read_key(fptr,TDOUBLE,keyward   ,&CCD[CID].AVE_DIF_LOCAL[1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"AVE_RA"  ,&CCD[CID].AVE_DIF_RADEC[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"AVE_DEC" ,&CCD[CID].AVE_DIF_RADEC[1],NULL,&status);
		fits_report_error(stderr,status);

		fits_read_key(fptr,TDOUBLE,"RMS_IMPX",&CCD[CID].RMS_DIF_IMPXL[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"RMS_IMPY",&CCD[CID].RMS_DIF_IMPXL[1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"RMS_CRX" ,&CCD[CID].RMS_DIF_CRPIX[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"RMS_CRY" ,&CCD[CID].RMS_DIF_CRPIX[1],NULL,&status);
		fits_report_error(stderr,status);
		sprintf(keyward,"RMS_LOX");
		if(CID==NUM_CCD)
		sprintf(keyward,"RMS_GLX");
		fits_read_key(fptr,TDOUBLE,keyward   ,&CCD[CID].RMS_DIF_LOCAL[0],NULL,&status);
		fits_report_error(stderr,status);
		sprintf(keyward,"RMS_LOY");
		if(CID==NUM_CCD)
		sprintf(keyward,"RMS_GLY");
		fits_read_key(fptr,TDOUBLE,keyward   ,&CCD[CID].RMS_DIF_LOCAL[1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"RMS_RA"  ,&CCD[CID].RMS_DIF_RADEC[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"RMS_DEC" ,&CCD[CID].RMS_DIF_RADEC[1],NULL,&status);
		fits_report_error(stderr,status);

		fits_read_key(fptr,TDOUBLE,"MAX_IMPX",&CCD[CID].MAX_DIF_IMPXL[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"MAX_IMPY",&CCD[CID].MAX_DIF_IMPXL[1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"MAX_CRX" ,&CCD[CID].MAX_DIF_CRPIX[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"MAX_CRY" ,&CCD[CID].MAX_DIF_CRPIX[1],NULL,&status);
		fits_report_error(stderr,status);
		sprintf(keyward,"MAX_LOX");
		if(CID==NUM_CCD)
		sprintf(keyward,"MAX_GLX");
		fits_read_key(fptr,TDOUBLE,keyward   ,&CCD[CID].MAX_DIF_LOCAL[0],NULL,&status);
		fits_report_error(stderr,status);
		sprintf(keyward,"MAX_LOY");
		if(CID==NUM_CCD)
		sprintf(keyward,"MAX_GLY");
		fits_read_key(fptr,TDOUBLE,keyward   ,&CCD[CID].MAX_DIF_LOCAL[1],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"MAX_RA"  ,&CCD[CID].MAX_DIF_RADEC[0],NULL,&status);
		fits_report_error(stderr,status);
		fits_read_key(fptr,TDOUBLE,"MAX_DEC" ,&CCD[CID].MAX_DIF_RADEC[1],NULL,&status);
		fits_report_error(stderr,status);

		fits_close_file(fptr,&status);
	}		
	CRPIX[0]=CCD[NUM_CCD].CRPIX[0];
	CRPIX[1]=CCD[NUM_CCD].CRPIX[1];
	CRVAL[0]=CCD[NUM_CCD].CRVAL[0];
	CRVAL[1]=CCD[NUM_CCD].CRVAL[1];
}
void CL_ANA::DEL_ANAfromfits(){
	int i;
	for(CID=0;CID<NUM_CCD+1;CID++)
	for(i=0;i<2;i++){
		delete [] CCD[CID].ASIP[i];
		delete [] CCD[CID].PSIP[i];
	}
	delete [] CCD;
}
std::vector< double > SLVTANSIP_SWIG_GET_CRPIX (CL_ANA* ANA,int CID){
	std::vector< double > CRPIX(2);
	if(CID>-0.5&&CID<ANA->NUM_CCD-0.5){
		CRPIX[0]=ANA->CCD[CID].CRPIX[0];
		CRPIX[1]=ANA->CCD[CID].CRPIX[1];
	}else{
		CRPIX[0]=ANA->CCD[ANA->NUM_CCD].CRPIX[0];
		CRPIX[1]=ANA->CCD[ANA->NUM_CCD].CRPIX[1];
	}
	return CRPIX;
}
std::vector< double > SLVTANSIP_SWIG_GET_CRVAL (CL_ANA* ANA,int CID){
	std::vector< double > CRVAL(2);
	if(CID>-0.5&&CID<ANA->NUM_CCD-0.5){
		CRVAL[0]=ANA->CCD[CID].CRVAL[0];
		CRVAL[1]=ANA->CCD[CID].CRVAL[1];
	}else{
		CRVAL[0]=ANA->CCD[ANA->NUM_CCD].CRVAL[0];
		CRVAL[1]=ANA->CCD[ANA->NUM_CCD].CRVAL[1];
	}
	return CRVAL;
}
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_GPOS_GLOBAL(CL_ANA* ANA){
	std::vector< std::vector< double > > GPOS;
	std::vector< double > GPOSCHIP(3);
	for(ANA->CID=0;ANA->CID<ANA->NUM_CCD;ANA->CID++){
		GPOSCHIP[0]=ANA->CCD[ANA->CID].GPOS[0];
		GPOSCHIP[1]=ANA->CCD[ANA->CID].GPOS[1];
		GPOSCHIP[2]=ANA->CCD[ANA->CID].GPOS[2];
		GPOS.push_back(GPOSCHIP);
	}

	return GPOS;
}
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_CORNAR_GLOBAL(CL_ANA* ANA){
	std::vector< std::vector< double > > CORNAR;
	std::vector< double > CORNARCHIP(2);
	for(ANA->CID=0;ANA->CID<ANA->NUM_CCD;ANA->CID++)
	if(ANA->CID<99.5){
		CORNARCHIP[0]=ANA->CCD[ANA->CID].GPOS[0]+0*LEN_CCDX*cos(ANA->CCD[ANA->CID].GPOS[2])-0*LEN_CCDY*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNARCHIP[1]=ANA->CCD[ANA->CID].GPOS[1]+0*LEN_CCDY*cos(ANA->CCD[ANA->CID].GPOS[2])+0*LEN_CCDX*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNAR.push_back(CORNARCHIP);
		CORNARCHIP[0]=ANA->CCD[ANA->CID].GPOS[0]+1*LEN_CCDX*cos(ANA->CCD[ANA->CID].GPOS[2])-0*LEN_CCDY*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNARCHIP[1]=ANA->CCD[ANA->CID].GPOS[1]+0*LEN_CCDY*cos(ANA->CCD[ANA->CID].GPOS[2])+1*LEN_CCDX*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNAR.push_back(CORNARCHIP);
		CORNARCHIP[0]=ANA->CCD[ANA->CID].GPOS[0]+1*LEN_CCDX*cos(ANA->CCD[ANA->CID].GPOS[2])-1*LEN_CCDY*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNARCHIP[1]=ANA->CCD[ANA->CID].GPOS[1]+1*LEN_CCDY*cos(ANA->CCD[ANA->CID].GPOS[2])+1*LEN_CCDX*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNAR.push_back(CORNARCHIP);
		CORNARCHIP[0]=ANA->CCD[ANA->CID].GPOS[0]+0*LEN_CCDX*cos(ANA->CCD[ANA->CID].GPOS[2])-1*LEN_CCDY*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNARCHIP[1]=ANA->CCD[ANA->CID].GPOS[1]+1*LEN_CCDY*cos(ANA->CCD[ANA->CID].GPOS[2])+0*LEN_CCDX*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNAR.push_back(CORNARCHIP);
	}else if(ANA->CID>99.5&&ANA->CID<103.5){
		CORNARCHIP[0]=ANA->CCD[ANA->CID].GPOS[0]+0*LEN_CCDY*cos(ANA->CCD[ANA->CID].GPOS[2])-0*LEN_CCDX*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNARCHIP[1]=ANA->CCD[ANA->CID].GPOS[1]+0*LEN_CCDX*cos(ANA->CCD[ANA->CID].GPOS[2])+0*LEN_CCDY*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNAR.push_back(CORNARCHIP);
		CORNARCHIP[0]=ANA->CCD[ANA->CID].GPOS[0]+1*LEN_CCDY*cos(ANA->CCD[ANA->CID].GPOS[2])-0*LEN_CCDX*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNARCHIP[1]=ANA->CCD[ANA->CID].GPOS[1]+0*LEN_CCDX*cos(ANA->CCD[ANA->CID].GPOS[2])+1*LEN_CCDY*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNAR.push_back(CORNARCHIP);
		CORNARCHIP[0]=ANA->CCD[ANA->CID].GPOS[0]+1*LEN_CCDY*cos(ANA->CCD[ANA->CID].GPOS[2])-1*LEN_CCDX*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNARCHIP[1]=ANA->CCD[ANA->CID].GPOS[1]+1*LEN_CCDX*cos(ANA->CCD[ANA->CID].GPOS[2])+1*LEN_CCDY*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNAR.push_back(CORNARCHIP);
		CORNARCHIP[0]=ANA->CCD[ANA->CID].GPOS[0]+0*LEN_CCDY*cos(ANA->CCD[ANA->CID].GPOS[2])-1*LEN_CCDX*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNARCHIP[1]=ANA->CCD[ANA->CID].GPOS[1]+1*LEN_CCDX*cos(ANA->CCD[ANA->CID].GPOS[2])+0*LEN_CCDY*sin(ANA->CCD[ANA->CID].GPOS[2]);
		CORNAR.push_back(CORNARCHIP);
	}
	

	return CORNAR;
}
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_TANPOSITION_LOCAL(CL_ANA* ANA,int CID,std::vector< std::vector< double > > RADEC){
	std::vector< std::vector< double > > LOCAL_ALL;
	std::vector< double > LOCAL(2);
	int SIZE1;
	SIZE1=RADEC.size();
	
	ANA->OBJ = new CL_OBJ[SIZE1];
	ANA->NUM_OBJ=SIZE1;
	if(CID>-0.5&&CID<ANA->NUM_CCD-0.5){
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			ANA->OBJ[ANA->OID].X_RADEC[0]=RADEC[ANA->OID][0];
			ANA->OBJ[ANA->OID].X_RADEC[1]=RADEC[ANA->OID][1];
			ANA->OBJ[ANA->OID].X_LOCAL_TANfromRADEC[0]=0;
			ANA->OBJ[ANA->OID].X_LOCAL_TANfromRADEC[1]=0;
			ANA->OBJ[ANA->OID].ID_CHIP=CID;
		}
		ANA->CALC_X_IMWLD();
		ANA->CALC_X_IMPXLLOCAL();
		ANA->CALC_X_CRPIXLOCAL_TAN();
		ANA->CALC_X_LOCAL_TAN();
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			LOCAL[0]=ANA->OBJ[ANA->OID].X_LOCAL_TANfromRADEC[0];
			LOCAL[1]=ANA->OBJ[ANA->OID].X_LOCAL_TANfromRADEC[1];
			LOCAL_ALL.push_back(LOCAL);
		}
	}else if(CID==-1){
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			ANA->OBJ[ANA->OID].X_RADEC[0]=RADEC[ANA->OID][0];
			ANA->OBJ[ANA->OID].X_RADEC[1]=RADEC[ANA->OID][1];
			ANA->OBJ[ANA->OID].X_LOCAL_TANfromRADEC[0]=0;
			ANA->OBJ[ANA->OID].X_LOCAL_TANfromRADEC[1]=0;
			ANA->OBJ[ANA->OID].ID_CHIP=CID;
		}
		ANA->CALC_X_IMWLD();
		ANA->CALC_X_IMPXLLOCAL();
		ANA->CALC_X_CRPIXLOCAL_TAN();
		ANA->CALC_X_LOCAL_TAN();
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			LOCAL[0]=ANA->OBJ[ANA->OID].X_LOCAL_TANfromRADEC[0];
			LOCAL[1]=ANA->OBJ[ANA->OID].X_LOCAL_TANfromRADEC[1];
			LOCAL_ALL.push_back(LOCAL);
		}
	}else{
		LOCAL[0]=0.0;
		LOCAL[1]=0.0;
		LOCAL_ALL.push_back(LOCAL);
	}
	
	delete [] ANA->OBJ;
	return LOCAL_ALL;
}
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_TANPOSITION_RADEC(CL_ANA* ANA,int CID,std::vector< std::vector< double > > LOCAL){
	std::vector< std::vector< double > > RADEC_ALL;
	std::vector< double > RADEC(2);
	int SIZE1;
	SIZE1=LOCAL.size();
	
	ANA->OBJ = new CL_OBJ[SIZE1];
	ANA->NUM_OBJ=SIZE1;
	if(CID>-0.5&&CID<ANA->NUM_CCD-0.5){
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			ANA->OBJ[ANA->OID].X_LOCAL[0]=LOCAL[ANA->OID][0];
			ANA->OBJ[ANA->OID].X_LOCAL[1]=LOCAL[ANA->OID][1];
			ANA->OBJ[ANA->OID].X_RADEC_TANfromLOCAL[0]=0;
			ANA->OBJ[ANA->OID].X_RADEC_TANfromLOCAL[1]=0;
			ANA->OBJ[ANA->OID].ID_CHIP=CID;
		}
		ANA->CALC_X_CRPIXLOCAL();
		ANA->CALC_X_IMPXLLOCAL_TAN();
		ANA->CALC_X_IMWLDLOCAL_TAN();
		ANA->CALC_X_RADEC_TAN();
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			RADEC[0]=ANA->OBJ[ANA->OID].X_RADEC_TANfromLOCAL[0];
			RADEC[1]=ANA->OBJ[ANA->OID].X_RADEC_TANfromLOCAL[1];
			RADEC_ALL.push_back(RADEC);
		}
	}else if(CID==-1){
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			ANA->OBJ[ANA->OID].X_GLOBL[0]=LOCAL[ANA->OID][0];
			ANA->OBJ[ANA->OID].X_GLOBL[1]=LOCAL[ANA->OID][1];
			ANA->OBJ[ANA->OID].X_RADEC_TANfromGLOBL[0]=0;
			ANA->OBJ[ANA->OID].X_RADEC_TANfromGLOBL[1]=0;
		}
		ANA->CALC_X_CRPIXGLOBL();
		ANA->CALC_X_IMPXLGLOBL_TAN();
		ANA->CALC_X_IMWLDGLOBL_TAN();
		ANA->CALC_X_RADEC_TAN();
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			RADEC[0]=ANA->OBJ[ANA->OID].X_RADEC_TANfromGLOBL[0];
			RADEC[1]=ANA->OBJ[ANA->OID].X_RADEC_TANfromGLOBL[1];
			RADEC_ALL.push_back(RADEC);
		}
	}else{
		RADEC[0]=0.0;
		RADEC[1]=0.0;
		RADEC_ALL.push_back(RADEC);
	}
	delete [] ANA->OBJ;
	return RADEC_ALL;
}

std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_SIPPOSITION_LOCAL(CL_ANA* ANA,int CID,std::vector< std::vector< double > > RADEC){
	std::vector< std::vector< double > > LOCAL_ALL;
	std::vector< double > LOCAL(2);
	int SIZE1;
	SIZE1=RADEC.size();
	
	ANA->OBJ = new CL_OBJ[SIZE1];
	ANA->NUM_OBJ=SIZE1;
	if(CID>-0.5&&CID<ANA->NUM_CCD-0.5){
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			ANA->OBJ[ANA->OID].X_RADEC[0]=RADEC[ANA->OID][0];
			ANA->OBJ[ANA->OID].X_RADEC[1]=RADEC[ANA->OID][1];
			ANA->OBJ[ANA->OID].X_LOCAL_SIPfromRADEC[0]=0;
			ANA->OBJ[ANA->OID].X_LOCAL_SIPfromRADEC[1]=0;
			ANA->OBJ[ANA->OID].ID_CHIP=CID;
		}
		ANA->CALC_X_IMWLD();
		ANA->CALC_X_IMPXLLOCAL();
		ANA->CALC_X_CRPIXLOCAL_SIP();
		ANA->CALC_X_LOCAL_SIP();
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			LOCAL[0]=ANA->OBJ[ANA->OID].X_LOCAL_SIPfromRADEC[0];
			LOCAL[1]=ANA->OBJ[ANA->OID].X_LOCAL_SIPfromRADEC[1];
			LOCAL_ALL.push_back(LOCAL);
		}
	}else if(CID==-1){
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			ANA->OBJ[ANA->OID].X_RADEC[0]=RADEC[ANA->OID][0];
			ANA->OBJ[ANA->OID].X_RADEC[1]=RADEC[ANA->OID][1];
			ANA->OBJ[ANA->OID].X_LOCAL_SIPfromRADEC[0]=0;
			ANA->OBJ[ANA->OID].X_LOCAL_SIPfromRADEC[1]=0;
			ANA->OBJ[ANA->OID].ID_CHIP=CID;
		}
		ANA->CALC_X_IMWLD();
		ANA->CALC_X_IMPXLLOCAL();
		ANA->CALC_X_CRPIXLOCAL_SIP();
		ANA->CALC_X_LOCAL_SIP();
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			LOCAL[0]=ANA->OBJ[ANA->OID].X_LOCAL_SIPfromRADEC[0];
			LOCAL[1]=ANA->OBJ[ANA->OID].X_LOCAL_SIPfromRADEC[1];
			LOCAL_ALL.push_back(LOCAL);
		}
	}else{
		LOCAL[0]=0.0;
		LOCAL[1]=0.0;
		LOCAL_ALL.push_back(LOCAL);
	}
	
	delete [] ANA->OBJ;
	return LOCAL_ALL;
}
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_SIPPOSITION_RADEC(CL_ANA* ANA,int CID,std::vector< std::vector< double > > LOCAL){
	std::vector< std::vector< double > > RADEC_ALL;
	std::vector< double > RADEC(2);
	int SIZE1;
	SIZE1=LOCAL.size();
	
	ANA->OBJ = new CL_OBJ[SIZE1];
	ANA->NUM_OBJ=SIZE1;
	if(CID>-0.5&&CID<ANA->NUM_CCD-0.5){
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			ANA->OBJ[ANA->OID].X_LOCAL[0]=LOCAL[ANA->OID][0];
			ANA->OBJ[ANA->OID].X_LOCAL[1]=LOCAL[ANA->OID][1];
			ANA->OBJ[ANA->OID].X_RADEC_SIPfromLOCAL[0]=0;
			ANA->OBJ[ANA->OID].X_RADEC_SIPfromLOCAL[1]=0;
			ANA->OBJ[ANA->OID].ID_CHIP=CID;
		}
		ANA->CALC_X_CRPIXLOCAL();
		ANA->CALC_X_IMPXLLOCAL_SIP();
		ANA->CALC_X_IMWLDLOCAL_SIP();
		ANA->CALC_X_RADEC_SIP();
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			RADEC[0]=ANA->OBJ[ANA->OID].X_RADEC_SIPfromLOCAL[0];
			RADEC[1]=ANA->OBJ[ANA->OID].X_RADEC_SIPfromLOCAL[1];
			RADEC_ALL.push_back(RADEC);
		}
	}else if(CID==-1){
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			ANA->OBJ[ANA->OID].X_GLOBL[0]=LOCAL[ANA->OID][0];
			ANA->OBJ[ANA->OID].X_GLOBL[1]=LOCAL[ANA->OID][1];
			ANA->OBJ[ANA->OID].X_RADEC_SIPfromGLOBL[0]=0;
			ANA->OBJ[ANA->OID].X_RADEC_SIPfromGLOBL[1]=0;
		}
		ANA->CALC_X_CRPIXGLOBL();
		ANA->CALC_X_IMPXLGLOBL_SIP();
		ANA->CALC_X_IMWLDGLOBL_SIP();
		ANA->CALC_X_RADEC_SIP();
		for(ANA->OID=0;ANA->OID<SIZE1;ANA->OID++){
			RADEC[0]=ANA->OBJ[ANA->OID].X_RADEC_SIPfromGLOBL[0];
			RADEC[1]=ANA->OBJ[ANA->OID].X_RADEC_SIPfromGLOBL[1];
			RADEC_ALL.push_back(RADEC);
		}
	}else{
		RADEC[0]=0.0;
		RADEC[1]=0.0;
		RADEC_ALL.push_back(RADEC);
	}
	delete [] ANA->OBJ;
	return RADEC_ALL;
}

