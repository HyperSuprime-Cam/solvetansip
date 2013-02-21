//--------------------------------------------------
//SLVTANSIP_ANA_OUT.cc
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#include<iostream>
#include<fstream>
#include<iomanip>
#include<fitsio.h>
#include"SLVTANSIP_ANA.h"

using namespace std;
void CL_ANA::OUT_DATA(){
	if(STDOUT==1||STDOUT==2)cout << "--- OUTPUT FILE : START ---" <<endl;
	OUT_CCD();
	OUT_CCD_ALL();
	if(PAFOUT==1)
	OUT_PAF();
	if(PVCALC==1&&PVOUT==1)
	OUT_CCD_PV();
	OUT_OBJ();
	if(STDOUT==1||STDOUT==2)cout << "--- OUTPUT FILE : END ---" <<endl;
}
void CL_ANA::OUT_CCD(){
	if(STDOUT==1||STDOUT==2)cout << "--- OUTPUT FILE : CCD ---" <<endl;
	int status,IVALUE;
	int i,j,ij;
	char outname[100],KEYNAME[100],COMMENT[100],CVALUE[100];
	fitsfile *fptr;

	for(CID=0;CID<NUM_CCD+1;CID++){
		sprintf(outname,"!%s/SLVTANSIP_CCD%03d.fits",DIR_CCD,CID);
		if(CID==NUM_CCD)
		sprintf(outname,"!%s/SLVTANSIP_GLOBAL.fits",DIR_CCD);

		status=0;
		fits_create_file(&fptr,outname,&status);
		fits_report_error(stderr,status);

		sprintf(KEYNAME,"SIMPLE");
		sprintf(COMMENT,"Fits standard");
		sprintf(CVALUE,"true");
		fits_write_key(fptr,TLOGICAL,KEYNAME,CVALUE,COMMENT,&status);
		sprintf(KEYNAME,"BITPIX");
		sprintf(COMMENT,"Bits per pixel");
		IVALUE=-32;
		fits_write_key(fptr,TINT,KEYNAME,&IVALUE,COMMENT,&status);
		sprintf(KEYNAME,"NAXIS");
		sprintf(COMMENT,"Number of axis");
		IVALUE=0;
		fits_write_key(fptr,TINT,KEYNAME,&IVALUE,COMMENT,&status);
		sprintf(KEYNAME,"DET-ID");
		sprintf(COMMENT,"CCD CHIP ID");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"GLOBAL coordinate");
		fits_write_key(fptr,TINT,KEYNAME,&CCD[CID].ID_CHIP,COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"NUM_OBJ");
		sprintf(COMMENT,"NUMBER of REFERENCE OBJECTS");
		fits_write_key(fptr,TINT,KEYNAME,&CCD[CID].NUM_OBJ,COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"NUM_FIT");
		sprintf(COMMENT,"NUMBER of REFERENCE OBJECTS for SIP FITTING");
		fits_write_key(fptr,TINT,KEYNAME,&CCD[CID].NUM_FIT,COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"GPOS_X");
		sprintf(COMMENT,"GLOBAL POSITION X");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].GPOS[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"GPOS_Y");
		sprintf(COMMENT,"GLOBAL POSITION Y");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].GPOS[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"GPOS_T");
		sprintf(COMMENT,"GLOBAL POSITION THETA");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].GPOS[2],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CRPIX1");
		sprintf(COMMENT,"CRPIX X");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CRPIX[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CRPIX2");
		sprintf(COMMENT,"CRPIX Y");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CRPIX[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CRVAL1");
		sprintf(COMMENT,"CRVAL X");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CRVAL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CRVAL2");
		sprintf(COMMENT,"CRVAL Y");
//		fits_write_key_dbl(fptr,KEYNAME,CCD[CID].CRVAL[1],9,COMMENT,&status);
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CRVAL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CD1_1");
		sprintf(COMMENT,"CD MATRIX[1,1]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CD[0][0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CD1_2");
		sprintf(COMMENT,"CD MATRIX[1,2]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CD[0][1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CD2_1");
		sprintf(COMMENT,"CD MATRIX[2,1]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CD[1][0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CD2_2");
		sprintf(COMMENT,"CD MATRIX[2,2]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CD[1][1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"InvCD1_1");
		sprintf(COMMENT,"Inverse CD MATRIX[1,1]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].InvCD[0][0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"InvCD1_2");
		sprintf(COMMENT,"Inverse CD MATRIX[1,2]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].InvCD[0][1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"InvCD2_1");
		sprintf(COMMENT,"Inverse CD MATRIX[2,1]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].InvCD[1][0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"InvCD2_2");
		sprintf(COMMENT,"Inverse CD MATRIX[2,2]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].InvCD[1][1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"ANGLE");
		sprintf(COMMENT,"ANGLE(rad)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].ANGLE,COMMENT,&status);
		fits_report_error(stderr,status);

		sprintf(KEYNAME,"A_ORDER");
		sprintf(COMMENT,"POLYNOMINAL ORDER of SIP_X");
		fits_write_key(fptr,TINT,KEYNAME,&ORDER_ASIP,COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(COMMENT,"POLYNOMINAL COEFFICIENT of SIP_X");
		ij=0;
		for(i=0;i<ORDER_ASIP+1;i++)
		for(j=0;j<ORDER_ASIP+1;j++)
		if(i+j<ORDER_PSIP+1){
			sprintf(KEYNAME,"A_%d_%d",i,j);
			fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].ASIP[0][ij],COMMENT,&status);
			fits_report_error(stderr,status);
			ij++;
		}
		sprintf(KEYNAME,"B_ORDER");
		sprintf(COMMENT,"POLYNOMINAL ORDER of SIP_Y");
		fits_write_key(fptr,TINT,KEYNAME,&ORDER_ASIP,COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(COMMENT,"POLYNOMINAL COEFFICIENT of SIP_Y");
		ij=0;
		for(i=0;i<ORDER_ASIP+1;i++)
		for(j=0;j<ORDER_ASIP+1;j++)
		if(i+j<ORDER_PSIP+1){
			sprintf(KEYNAME,"B_%d_%d",i,j);
			fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].ASIP[1][ij],COMMENT,&status);
			fits_report_error(stderr,status);
			ij++;
		}
		sprintf(KEYNAME,"AP_ORDER");
		sprintf(COMMENT,"POLYNOMINAL ORDER of PSIP_X");
		fits_write_key(fptr,TINT,KEYNAME,&ORDER_PSIP,COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(COMMENT,"POLYNOMINAL COEFFICIENT of PSIP_X");
		ij=0;
		for(i=0;i<ORDER_PSIP+1;i++)
		for(j=0;j<ORDER_PSIP+1;j++)
		if(i+j<ORDER_PSIP+1){
			sprintf(KEYNAME,"AP_%d_%d",i,j);
			fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].PSIP[0][ij],COMMENT,&status);
			fits_report_error(stderr,status);
			ij++;
		}
		sprintf(KEYNAME,"BP_ORDER");
		sprintf(COMMENT,"POLYNOMINAL ORDER of PSIP_Y");
		fits_write_key(fptr,TINT,KEYNAME,&ORDER_PSIP,COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(COMMENT,"POLYNOMINAL COEFFICIENT of PSIP_Y");
		ij=0;
		for(i=0;i<ORDER_PSIP+1;i++)
		for(j=0;j<ORDER_PSIP+1;j++)
		if(i+j<ORDER_PSIP+1){
			sprintf(KEYNAME,"BP_%d_%d",i,j);
			fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].PSIP[1][ij],COMMENT,&status);
			fits_report_error(stderr,status);
			ij++;
		}

		sprintf(KEYNAME,"MAX_R");
		sprintf(COMMENT,"MAXIMUM RADIUS of OBJECT from CRPIX(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&MAX_R,COMMENT,&status);
		fits_report_error(stderr,status);

		sprintf(KEYNAME,"AVE_IMPX");
		sprintf(COMMENT,"AVE of SIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_IMPXL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_IMPY");
		sprintf(COMMENT,"AVE of SIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_IMPXL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_CRX");
		sprintf(COMMENT,"AVE of PSIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_CRPIX[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_CRY");
		sprintf(COMMENT,"AVE of PSIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_CRPIX[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_LOX");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"AVE_GLX");
		sprintf(COMMENT,"AVE of CALCULATED LOCAL from RADEC X(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"AVE of CALCULATED GLOBAL from RADEC X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_LOCAL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_LOY");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"AVE_GLY");
		sprintf(COMMENT,"AVE of CALCULATED LOCAL from RADEC Y(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"AVE of CALCULATED GLOBAL from RADEC Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_LOCAL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_RA");
		sprintf(COMMENT,"AVE of CALCULATED RADEC from LOCAL X(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"AVE of CALCULATED RADEC from GLOBAL X(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_RADEC[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_DEC");
		sprintf(COMMENT,"AVE of CALCULATED RADEC from LOCAL Y(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"AVE of CALCULATED RADEC from GLOBAL Y(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_RADEC[1],COMMENT,&status);
		fits_report_error(stderr,status);

		sprintf(KEYNAME,"RMS_IMPX");
		sprintf(COMMENT,"RMS of SIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_IMPXL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_IMPY");
		sprintf(COMMENT,"RMS of SIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_IMPXL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_CRX");
		sprintf(COMMENT,"RMS of PSIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_CRPIX[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_CRY");
		sprintf(COMMENT,"RMS of PSIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_CRPIX[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_LOX");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"RMS_GLX");
		sprintf(COMMENT,"RMS of CALCULATED LOCAL from RADEC X(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"RMS of CALCULATED GLOBAL from RADEC X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_LOCAL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_LOY");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"RMS_GLY");
		sprintf(COMMENT,"RMS of CALCULATED LOCAL from RADEC Y(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"RMS of CALCULATED GLOBAL from RADEC Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_LOCAL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_RA");
		sprintf(COMMENT,"RMS of CALCULATED RADEC from LOCAL X(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"RMS of CALCULATED RADEC from GLOBAL X(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_RADEC[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_DEC");
		sprintf(COMMENT,"RMS of CALCULATED RADEC from LOCAL Y(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"RMS of CALCULATED RADEC from GLOBAL Y(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_RADEC[1],COMMENT,&status);
		fits_report_error(stderr,status);

		sprintf(KEYNAME,"MAX_IMPX");
		sprintf(COMMENT,"MAX of SIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_IMPXL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_IMPY");
		sprintf(COMMENT,"MAX of SIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_IMPXL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_CRX");
		sprintf(COMMENT,"MAX of PSIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_CRPIX[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_CRY");
		sprintf(COMMENT,"MAX of PSIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_CRPIX[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_LOX");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"MAX_GLX");
		sprintf(COMMENT,"MAX of CALCULATED LOCAL from RADEC X(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"MAX of CALCULATED GLOBAL from RADEC X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_LOCAL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_LOY");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"MAX_GLY");
		sprintf(COMMENT,"MAX of CALCULATED LOCAL from RADEC Y(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"MAX of CALCULATED GLOBAL from RADEC Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_LOCAL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_RA");
		sprintf(COMMENT,"MAX of CALCULATED RADEC from LOCAL X(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"MAX of CALCULATED RADEC from GLOBAL X(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_RADEC[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_DEC");
		sprintf(COMMENT,"MAX of CALCULATED RADEC from LOCAL Y(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"MAX of CALCULATED RADEC from GLOBAL Y(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_RADEC[1],COMMENT,&status);
		fits_report_error(stderr,status);


		fits_close_file(fptr,&status);
		fits_report_error(stderr,status);
	}
}
void CL_ANA::OUT_PAF(){
	int i,j,ij;
	char fpout[100];
	ofstream pout;
	sprintf(fpout,"%s/SLVTANSIP_RESULT.paf",DIR_CCD);
	pout.open(fpout);
	
	pout<<"#AnalysisProperty	"<<"#"<<"	#"<<endl;
	pout<<"INSTR:		"<<INSTR<<"	#INSTRUMENT_HSC_or_SC"<<endl;
	pout<<"CRMODE:		"<<MODE_CR<<"	#AUTO_for_AUTO_MODE,PIX_and_VAL_for_MANUAL_MODE"<<endl;
	pout<<"OAMODE:		"<<MODE_OA<<"	#"<<endl;
	pout<<"REJMODE:	"<<MODE_REJ<<"	#1=REJECT_BAD_REFERENCES"<<endl;
	pout<<"CCDPMODE:	"<<MODE_CCDPOS<<"	#1=DETERMINING_CCD_POSITION"<<endl;
	pout<<"CCDPHMODE:	"<<MODE_CCDPOSH<<"	#1=DETERMINING_CCD_POSITION_WITH_HIGH_PRESITION"<<endl;
	pout<<"NCCD:		"<<NUM_CCD<<"	#NUMBER_of_CCD_for_analysis"<<endl;
	pout<<"LSIPORDER:	"<<ORDER_LSIP<<"	#SIP_ORDER_of_AL_and_BL "<<endl;
	pout<<"ASIPORDER:	"<<ORDER_ASIP<<"	#SIP_ORDER_of_A_and_B "<<endl;
	pout<<"PSIPORDER:	"<<ORDER_PSIP<<"	#SIP_ORDER_of_AP_and_BP "<<endl;
	pout<<"CLIPSIGMA:	"<<CLIP_SIGMA<<"	#CONTROLE_STRENGTH_OF_REJECTION"<<endl;
	pout<<"CRPIX1:		"<<CRPIX[0]<<"	#CRPIX_VALUE_OF_AXIS_1(MANUAL_MODE)"<<endl;
	pout<<"CRPIX2:		"<<CRPIX[1]<<"	#CRPIX_VALUE_OF_AXIS_2(MANUAL_MODE)"<<endl;
	pout<<"CRVAL1:		"<<CRVAL[0]<<"	#CRVAL_VALUE_OF_AXIS_1(MANUAL_MODE)"<<endl;
	pout<<"CRVAL2:		"<<CRVAL[1]<<"	#CRVAL_VALUE_OF_AXIS_2(MANUAL_MODE)"<<endl;
	pout<<"BASISPOSX:	"<<GPOS_BASIS[0]<<"	#X_BASIS_OF_GLOBAL_POSITION"<<endl;
	pout<<"BASISPOSY:	"<<GPOS_BASIS[1]<<"	#Y_BASIS_OF_GLOBAL_POSITION"<<endl;
	pout<<"BASISPOST:	"<<GPOS_BASIS[2]<<"	#T_BASIS_OF_GLOBAL_POSITION"<<endl;
	pout<<"EXTRACALC:	"<<EXTRACALC<<"	#0=only_standard_calcultion,1=with_extra_calculation"<<endl;
	pout<<"PVCALC:		"<<PVCALC<<"	#1=calculate_PV_Coef"<<endl;
	pout<<"STDOUT:		"<<STDOUT<<"	#0=non_output,1=STEP_output,2=detail_output"<<endl;
	pout<<"FILEOUT:	"<<FILEOUT<<"	#0=non_output,1=output_file"<<endl;
	pout<<"PAFOUT:		"<<PAFOUT<<"	#1=output_new_paffile"<<endl;
	pout<<"PVOUT:		"<<PVOUT<<"	#1=OUTPUT_PV_Coef"<<endl;
	pout<<"CCDFILEDIR:	"<<"AUTO"<<"	#output_directory_of_CCD_fitsheader"<<endl;
	pout<<"OBJFILEDIR:	"<<"AUTO"<<"	#output_directory_of_OBJ_fitsheader"<<endl;
	pout<<"# CCDPOSITIONS INITIAL"<<endl;
	pout<<"# HSC #"<<endl;
	for(CID=0;CID<NUM_CCD;CID++){
		pout<<"HSCIGPOS"<< setw(3) << setfill('0') <<CID<<"_X:	"<<CCD[CID].GPOS[0]<<"	#"<<endl;
		pout<<"HSCIGPOS"<< setw(3) << setfill('0') <<CID<<"_Y:	"<<CCD[CID].GPOS[1]<<"	#"<<endl;
		pout<<"HSCIGPOS"<< setw(3) << setfill('0') <<CID<<"_T:	"<<CCD[CID].GPOS[2]<<"	#"<<endl;
	}
	pout<<"# DISTORTION INITIAL"<<endl;
	pout<<"IASIPORDER:	"<<ORDER_ASIP<<"	#SIP_ORDER_of_A_and_B"<<endl;
	pout<<"IPSIPORDER:	"<<ORDER_PSIP<<"	#SIP_ORDER_of_AP_and_BP"<<endl;
	pout<<"ICD_1_1:		"<<CCD[NUM_CCD].CD[0][0]<<"	#"<<endl;
	pout<<"ICD_1_2:		"<<CCD[NUM_CCD].CD[0][1]<<"	#"<<endl;
	pout<<"ICD_2_1:		"<<CCD[NUM_CCD].CD[1][0]<<"	#"<<endl;
	pout<<"ICD_2_2:		"<<CCD[NUM_CCD].CD[1][1]<<"	#"<<endl;
	pout<<"IMAXFRAD:	"<<MAX_R<<"	#"<<endl;
	ij=0;
	for(i=0;i<ORDER_ASIP+1;i++)
	for(j=0;j<ORDER_ASIP+1;j++)
	if(i+j<ORDER_ASIP+1){
		pout<<"IA_"<<i<<"_"<<j<<":	"<<CCD[NUM_CCD].ASIP[0][ij]<<"	#"<<endl;
		ij++;
	}
	ij=0;
	for(i=0;i<ORDER_ASIP+1;i++)
	for(j=0;j<ORDER_ASIP+1;j++)
	if(i+j<ORDER_ASIP+1){
		pout<<"IB_"<<i<<"_"<<j<<":	"<<CCD[NUM_CCD].ASIP[1][ij]<<"	#"<<endl;
		ij++;
	}
	ij=0;
	for(i=0;i<ORDER_PSIP+1;i++)
	for(j=0;j<ORDER_PSIP+1;j++)
	if(i+j<ORDER_PSIP+1){
		pout<<"IAP_"<<i<<"_"<<j<<":	"<<CCD[NUM_CCD].PSIP[0][ij]<<"	#"<<endl;
		ij++;
	}
	ij=0;
	for(i=0;i<ORDER_PSIP+1;i++)
	for(j=0;j<ORDER_PSIP+1;j++)
	if(i+j<ORDER_PSIP+1){
		pout<<"IBP_"<<i<<"_"<<j<<":	"<<CCD[NUM_CCD].PSIP[1][ij]<<"	#"<<endl;
		ij++;
	}
}
void CL_ANA::OUT_CCD_PV(){
	if(STDOUT==1||STDOUT==2)cout << "--- OUTPUT FILE : CCD_PV ---" <<endl;
	int status,IVALUE;
	int i,j,ij;
	char outname[100],KEYNAME[100],COMMENT[100],CVALUE[100];
	fitsfile *fptr;

	for(CID=0;CID<NUM_CCD+1;CID++){
		sprintf(outname,"!%s/SLVTANSIP_CCD%03d_PV.fits",DIR_CCD,CID);
		if(CID==NUM_CCD)
		sprintf(outname,"!%s/SLVTANSIP_GLOBAL_PV.fits",DIR_CCD);

		status=0;
		fits_create_file(&fptr,outname,&status);
		fits_report_error(stderr,status);

		sprintf(KEYNAME,"SIMPLE");
		sprintf(COMMENT,"Fits standard");
		sprintf(CVALUE,"true");
		fits_write_key(fptr,TLOGICAL,KEYNAME,CVALUE,COMMENT,&status);
		sprintf(KEYNAME,"BITPIX");
		sprintf(COMMENT,"Bits per pixel");
		IVALUE=-32;
		fits_write_key(fptr,TINT,KEYNAME,&IVALUE,COMMENT,&status);
		sprintf(KEYNAME,"NAXIS");
		sprintf(COMMENT,"Number of axis");
		IVALUE=0;
		fits_write_key(fptr,TINT,KEYNAME,&IVALUE,COMMENT,&status);
		sprintf(KEYNAME,"DET-ID");
		sprintf(COMMENT,"CCD CHIP ID");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"GLOBAL coordinate");
		fits_write_key(fptr,TINT,KEYNAME,&CCD[CID].ID_CHIP,COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"NUM_OBJ");
		sprintf(COMMENT,"NUMBER of REFERENCE OBJECTS");
		fits_write_key(fptr,TINT,KEYNAME,&CCD[CID].NUM_OBJ,COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"NUM_FIT");
		sprintf(COMMENT,"NUMBER of REFERENCE OBJECTS for SIP FITTING");
		fits_write_key(fptr,TINT,KEYNAME,&CCD[CID].NUM_FIT,COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"GPOS_X");
		sprintf(COMMENT,"GLOBAL POSITION X");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].GPOS[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"GPOS_X");
		sprintf(COMMENT,"GLOBAL POSITION Y");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].GPOS[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"GPOS_T");
		sprintf(COMMENT,"GLOBAL POSITION THETA");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].GPOS[2],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CRPIX1");
		sprintf(COMMENT,"CRPIX X");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CRPIX[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CRPIX2");
		sprintf(COMMENT,"CRPIX Y");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CRPIX[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CRVAL1");
		sprintf(COMMENT,"CRVAL X");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CRVAL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CRVAL2");
		sprintf(COMMENT,"CRVAL Y");
//		fits_write_key_dbl(fptr,KEYNAME,CCD[CID].CRVAL[1],9,COMMENT,&status);
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CRVAL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CD1_1");
		sprintf(COMMENT,"CD MATRIX[1,1]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CD[0][0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CD1_2");
		sprintf(COMMENT,"CD MATRIX[1,2]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CD[0][1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CD2_1");
		sprintf(COMMENT,"CD MATRIX[2,1]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CD[1][0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"CD2_2");
		sprintf(COMMENT,"CD MATRIX[2,2]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].CD[1][1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"InvCD1_1");
		sprintf(COMMENT,"Inverse CD MATRIX[1,1]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].InvCD[0][0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"InvCD1_2");
		sprintf(COMMENT,"Inverse CD MATRIX[1,2]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].InvCD[0][1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"InvCD2_1");
		sprintf(COMMENT,"Inverse CD MATRIX[2,1]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].InvCD[1][0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"InvCD2_2");
		sprintf(COMMENT,"Inverse CD MATRIX[2,2]");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].InvCD[1][1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"ANGLE");
		sprintf(COMMENT,"ANGLE(rad)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].ANGLE,COMMENT,&status);
		fits_report_error(stderr,status);

		sprintf(KEYNAME,"PV_ORDER");
		sprintf(COMMENT,"POLYNOMINAL ORDER of PV");
		i =7;
		fits_write_key(fptr,TINT,KEYNAME,&i,COMMENT,&status);
		fits_report_error(stderr,status);

		sprintf(COMMENT,"COEFFICIENT of PV1");
		ij=0;
		for(ij=0;ij<40;ij++){
			sprintf(KEYNAME,"PV1_%d",ij);
			fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[NUM_CCD].PV[0][ij],COMMENT,&status);
			fits_report_error(stderr,status);
		}
		sprintf(COMMENT,"COEFFICIENT of PV2");
		ij=0;
		for(ij=0;ij<40;ij++){
			sprintf(KEYNAME,"PV2_%d",ij);
			fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[NUM_CCD].PV[1][ij],COMMENT,&status);
			fits_report_error(stderr,status);
		}

		sprintf(KEYNAME,"MAX_R");
		sprintf(COMMENT,"MAXIMUM RADIUS of OBJECT from CRPIX(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&MAX_R,COMMENT,&status);
		fits_report_error(stderr,status);

		sprintf(KEYNAME,"AVE_IMPX");
		sprintf(COMMENT,"AVE of SIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_IMPXL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_IMPY");
		sprintf(COMMENT,"AVE of SIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_IMPXL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_CRX");
		sprintf(COMMENT,"AVE of PSIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_CRPIX[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_CRY");
		sprintf(COMMENT,"AVE of PSIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_CRPIX[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_LOX");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"AVE_GLX");
		sprintf(COMMENT,"AVE of CALCULATED LOCAL from RADEC X(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"AVE of CALCULATED GLOBAL from RADEC X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_LOCAL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_LOY");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"AVE_GLY");
		sprintf(COMMENT,"AVE of CALCULATED LOCAL from RADEC Y(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"AVE of CALCULATED GLOBAL from RADEC Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_LOCAL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_RA");
		sprintf(COMMENT,"AVE of CALCULATED RADEC from LOCAL X(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"AVE of CALCULATED RADEC from GLOBAL X(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_RADEC[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"AVE_DEC");
		sprintf(COMMENT,"AVE of CALCULATED RADEC from LOCAL Y(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"AVE of CALCULATED RADEC from GLOBAL Y(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].AVE_DIF_RADEC[1],COMMENT,&status);
		fits_report_error(stderr,status);

		sprintf(KEYNAME,"RMS_IMPX");
		sprintf(COMMENT,"RMS of SIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_IMPXL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_IMPY");
		sprintf(COMMENT,"RMS of SIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_IMPXL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_CRX");
		sprintf(COMMENT,"RMS of PSIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_CRPIX[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_CRY");
		sprintf(COMMENT,"RMS of PSIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_CRPIX[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_LOX");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"RMS_GLX");
		sprintf(COMMENT,"RMS of CALCULATED LOCAL from RADEC X(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"RMS of CALCULATED GLOBAL from RADEC X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_LOCAL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_LOY");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"RMS_GLY");
		sprintf(COMMENT,"RMS of CALCULATED LOCAL from RADEC Y(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"RMS of CALCULATED GLOBAL from RADEC Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_LOCAL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_RA");
		sprintf(COMMENT,"RMS of CALCULATED RADEC from LOCAL X(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"RMS of CALCULATED RADEC from GLOBAL X(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_RADEC[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"RMS_DEC");
		sprintf(COMMENT,"RMS of CALCULATED RADEC from LOCAL Y(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"RMS of CALCULATED RADEC from GLOBAL Y(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].RMS_DIF_RADEC[1],COMMENT,&status);
		fits_report_error(stderr,status);

		sprintf(KEYNAME,"MAX_IMPX");
		sprintf(COMMENT,"MAX of SIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_IMPXL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_IMPY");
		sprintf(COMMENT,"MAX of SIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_IMPXL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_CRX");
		sprintf(COMMENT,"MAX of PSIP FITTING X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_CRPIX[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_CRY");
		sprintf(COMMENT,"MAX of PSIP FITTING Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_CRPIX[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_LOX");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"MAX_GLX");
		sprintf(COMMENT,"MAX of CALCULATED LOCAL from RADEC X(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"MAX of CALCULATED GLOBAL from RADEC X(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_LOCAL[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_LOY");
		if(CID==NUM_CCD)
		sprintf(KEYNAME,"MAX_GLY");
		sprintf(COMMENT,"MAX of CALCULATED LOCAL from RADEC Y(pix)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"MAX of CALCULATED GLOBAL from RADEC Y(pix)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_LOCAL[1],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_RA");
		sprintf(COMMENT,"MAX of CALCULATED RADEC from LOCAL X(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"MAX of CALCULATED RADEC from GLOBAL X(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_RADEC[0],COMMENT,&status);
		fits_report_error(stderr,status);
		sprintf(KEYNAME,"MAX_DEC");
		sprintf(COMMENT,"MAX of CALCULATED RADEC from LOCAL Y(degree)");
		if(CID==NUM_CCD)
		sprintf(COMMENT,"MAX of CALCULATED RADEC from GLOBAL Y(degree)");
		fits_write_key(fptr,TDOUBLE,KEYNAME,&CCD[CID].MAX_DIF_RADEC[1],COMMENT,&status);
		fits_report_error(stderr,status);


		fits_close_file(fptr,&status);
		fits_report_error(stderr,status);
	}
}
void CL_ANA::OUT_CCD_ALL(){
	if(STDOUT==1||STDOUT==2)cout << "--- OUTPUT FILE : CCD ALL ---" <<endl;
	int i,j,ij,k,status;
	int NUM_COL;
	long NUM_ROW;
	char **ttype,**tform,**tunit,extname[100],outname[100];
	fitsfile *fptr;

	sprintf(outname,"!%s/SLVTANSIP_CCDALL.fits",DIR_OBJ);

	NUM_ROW=0;
	for(CID=0;CID<NUM_CCD+1;CID++)
	NUM_ROW++;
	NUM_COL=300;

	status=0;
	fits_create_file(&fptr,outname,&status);
	fits_report_error(stderr,status);

	ttype = new char*[NUM_COL];
	tform = new char*[NUM_COL];
	tunit = new char*[NUM_COL];
	for(i=0;i<NUM_COL;i++){
		ttype[i]=new char[100];
		tform[i]=new char[100];
		tunit[i]=new char[100];
	}

	sprintf(extname,"CCD INFORMATION");
	sprintf(ttype[ 0],"DET-ID");
	sprintf(tform[ 0],"K");
	sprintf(tunit[ 0],"");
	sprintf(ttype[ 1],"NUM_OBJ");
	sprintf(tform[ 1],"K");
	sprintf(tunit[ 1],"");
	sprintf(ttype[ 2],"NUM_FIT");
	sprintf(tform[ 2],"K");
	sprintf(tunit[ 2],"");
	sprintf(ttype[ 3],"GPOS_X");
	sprintf(tform[ 3],"D");
	sprintf(tunit[ 3],"pixel");
	sprintf(ttype[ 4],"GPOS_Y");
	sprintf(tform[ 4],"D");
	sprintf(tunit[ 4],"pixel");
	sprintf(ttype[ 5],"GPOS_T");
	sprintf(tform[ 5],"D");
	sprintf(tunit[ 5],"degree");
	sprintf(ttype[ 6],"CRPIX1");
	sprintf(tform[ 6],"D");
	sprintf(tunit[ 6],"pixel");
	sprintf(ttype[ 7],"CRPIX2");
	sprintf(tform[ 7],"D");
	sprintf(tunit[ 7],"pixel");
	sprintf(ttype[ 8],"CRVAL1");
	sprintf(tform[ 8],"D");
	sprintf(tunit[ 8],"degree");
	sprintf(ttype[ 9],"CRVAL2");
	sprintf(tform[ 9],"D");
	sprintf(tunit[ 9],"degree");
	sprintf(ttype[10],"CD1_1");
	sprintf(tform[10],"D");
	sprintf(tunit[10],"degree/pixel");
	sprintf(ttype[11],"CD1_2");
	sprintf(tform[11],"D");
	sprintf(tunit[11],"degree/pixel");
	sprintf(ttype[12],"CD2_1");
	sprintf(tform[12],"D");
	sprintf(tunit[12],"degree/pixel");
	sprintf(ttype[13],"CD2_2");
	sprintf(tform[13],"D");
	sprintf(tunit[13],"degree/pixel");
	sprintf(ttype[14],"InvCD1_1");
	sprintf(tform[14],"D");
	sprintf(tunit[14],"pixel/degree");
	sprintf(ttype[15],"InvCD1_2");
	sprintf(tform[15],"D");
	sprintf(tunit[15],"pixel/degree");
	sprintf(ttype[16],"InvCD2_1");
	sprintf(tform[16],"D");
	sprintf(tunit[16],"pixel/degree");
	sprintf(ttype[17],"InvCD2_2");
	sprintf(tform[17],"D");
	sprintf(tunit[17],"pixel/degree");
	sprintf(ttype[18],"ANGLE");
	sprintf(tform[18],"D");
	sprintf(tunit[18],"radian");
	sprintf(ttype[19],"A_ORDER");
	sprintf(tform[19],"K");
	sprintf(tunit[19],"");
	k=20;
	ij=0;
	for(i=0;i<ORDER_ASIP+1;i++)
	for(j=0;j<ORDER_ASIP+1;j++)
	if(i+j<ORDER_ASIP+1){
		sprintf(ttype[k],"A_%d_%d",i,j);
		sprintf(tform[k],"D");
		sprintf(tunit[k],"");
		k++;
		ij++;
	}
	sprintf(ttype[k],"B_ORDER");
	sprintf(tform[k],"K");
	sprintf(tunit[k],"");
	k++;
	ij=0;
	for(i=0;i<ORDER_ASIP+1;i++)
	for(j=0;j<ORDER_ASIP+1;j++)
	if(i+j<ORDER_ASIP+1){
		sprintf(ttype[k],"B_%d_%d",i,j);
		sprintf(tform[k],"D");
		sprintf(tunit[k],"");
		k++;
		ij++;
	}
	sprintf(ttype[k],"AP_ORDER");
	sprintf(tform[k],"K");
	sprintf(tunit[k],"");
	k++;
	ij=0;
	for(i=0;i<ORDER_PSIP+1;i++)
	for(j=0;j<ORDER_PSIP+1;j++)
	if(i+j<ORDER_PSIP+1){
		sprintf(ttype[k],"AP_%d_%d",i,j);
		sprintf(tform[k],"D");
		sprintf(tunit[k],"");
		k++;
		ij++;
	}
	sprintf(ttype[k],"BP_ORDER");
	sprintf(tform[k],"K");
	sprintf(tunit[k],"");
	k++;
	ij=0;
	for(i=0;i<ORDER_PSIP+1;i++)
	for(j=0;j<ORDER_PSIP+1;j++)
	if(i+j<ORDER_PSIP+1){
		sprintf(ttype[k],"BP_%d_%d",i,j);
		sprintf(tform[k],"D");
		sprintf(tunit[k],"");
		k++;
		ij++;
	}

	sprintf(ttype[k],"MAX_R");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"AVE_IMPIX_X");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"AVE_IMPIX_Y");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"AVE_CRPIX_X");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"AVE_CRPIX_Y");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"AVE_LOCAL_X");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"AVE_LOCAL_Y");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"AVE_RA");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"degree");
	k++;
	sprintf(ttype[k],"AVE_DEC");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"degree");
	k++;
	sprintf(ttype[k],"RMS_IMPIX_X");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"RMS_IMPIX_Y");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"RMS_CRPIX_X");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"RMS_CRPIX_Y");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"RMS_LOCAL_X");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"RMS_LOCAL_Y");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"RMS_RA");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"degree");
	k++;
	sprintf(ttype[k],"RMS_DEC");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"degree");
	k++;
	sprintf(ttype[k],"MAX_IMPIX_X");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"MAX_IMPIX_Y");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"MAX_CRPIX_X");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"MAX_CRPIX_Y");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"MAX_LOCAL_X");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"MAX_LOCAL_Y");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"pixel");
	k++;
	sprintf(ttype[k],"MAX_RA");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"degree");
	k++;
	sprintf(ttype[k],"MAX_DEC");
	sprintf(tform[k],"D");
	sprintf(tunit[k],"degree");
	k++;

	for(;k<300;k++){
	sprintf(ttype[k],"BLANK");
	sprintf(tform[k],"X");
	sprintf(tunit[k],"");
	}
	fits_create_tbl(fptr,BINARY_TBL,NUM_ROW,NUM_COL,ttype,tform,tunit,extname,&status);
	fits_report_error(stderr,status);

	long long int *FCID,*FNO,*FNF;
	double *FGPOS[3],*FCRPIX[2],*FCRVAL[2],*FCD[2][2],*FInvCD[2][2],*FANGLE,*FMAXR;
	long long int *FA_ORDER,*FB_ORDER,*FAP_ORDER,*FBP_ORDER;
	double *FA_SIP[100],*FB_SIP[100],*FAP_SIP[100],*FBP_SIP[100];
	double *FAVE_IMPIX[2],*FAVE_CRPIX[2],*FAVE_LOCAL[2],*FAVE_RADEC[2];
	double *FRMS_IMPIX[2],*FRMS_CRPIX[2],*FRMS_LOCAL[2],*FRMS_RADEC[2];
	double *FMAX_IMPIX[2],*FMAX_CRPIX[2],*FMAX_LOCAL[2],*FMAX_RADEC[2];

	FCID		= new long long int[NUM_ROW];
	FNO		= new long long int[NUM_ROW];
	FNF		= new long long int[NUM_ROW];
	FGPOS[0]	= new double[NUM_ROW];
	FGPOS[1]	= new double[NUM_ROW];
	FGPOS[2]	= new double[NUM_ROW];
	FCRPIX[0]	= new double[NUM_ROW];
	FCRPIX[1]	= new double[NUM_ROW];
	FCRVAL[0]	= new double[NUM_ROW];
	FCRVAL[1]	= new double[NUM_ROW];
	FCD[0][0]	= new double[NUM_ROW];
	FCD[0][1]	= new double[NUM_ROW];
	FCD[1][0]	= new double[NUM_ROW];
	FCD[1][1]	= new double[NUM_ROW];
	FInvCD[0][0]	= new double[NUM_ROW];
	FInvCD[0][1]	= new double[NUM_ROW];
	FInvCD[1][0]	= new double[NUM_ROW];
	FInvCD[1][1]	= new double[NUM_ROW];
	FANGLE		= new double[NUM_ROW];
	FA_ORDER	= new long long int[NUM_ROW];
	FB_ORDER	= new long long int[NUM_ROW];
	FAP_ORDER	= new long long int[NUM_ROW];
	FBP_ORDER	= new long long int[NUM_ROW];
	for(i=0;i<100;i++){
	FA_SIP[i]	= new double[NUM_ROW];
	FB_SIP[i]	= new double[NUM_ROW];
	FAP_SIP[i]	= new double[NUM_ROW];
	FBP_SIP[i]	= new double[NUM_ROW];
	}
	FMAXR		= new double[NUM_ROW];
	for(i=0;i<2;i++){
	FAVE_IMPIX[i]	= new double[NUM_ROW];
	FAVE_CRPIX[i]	= new double[NUM_ROW];
	FAVE_LOCAL[i]	= new double[NUM_ROW];
	FAVE_RADEC[i]	= new double[NUM_ROW];
	FRMS_IMPIX[i]	= new double[NUM_ROW];
	FRMS_CRPIX[i]	= new double[NUM_ROW];
	FRMS_LOCAL[i]	= new double[NUM_ROW];
	FRMS_RADEC[i]	= new double[NUM_ROW];
	FMAX_IMPIX[i]	= new double[NUM_ROW];
	FMAX_CRPIX[i]	= new double[NUM_ROW];
	FMAX_LOCAL[i]	= new double[NUM_ROW];
	FMAX_RADEC[i]	= new double[NUM_ROW];
	}

	for(CID=0;CID<NUM_CCD+1;CID++){
		FCID[CID]	= CCD[CID].ID_CHIP;
		FNO[CID]	= CCD[CID].NUM_OBJ;
		FNF[CID]	= CCD[CID].NUM_FIT;
		FGPOS[0][CID]	= CCD[CID].GPOS[0];
		FGPOS[1][CID]	= CCD[CID].GPOS[1];
		FGPOS[2][CID]	= CCD[CID].GPOS[2];
		FCRPIX[0][CID]	= CCD[CID].CRPIX[0];
		FCRPIX[1][CID]	= CCD[CID].CRPIX[1];
		FCRVAL[0][CID]	= CCD[CID].CRVAL[0];
		FCRVAL[1][CID]	= CCD[CID].CRVAL[1];
		FCD[0][0][CID]	= CCD[CID].CD[0][0];
		FCD[0][1][CID]	= CCD[CID].CD[0][1];
		FCD[1][0][CID]	= CCD[CID].CD[1][0];
		FCD[1][1][CID]	= CCD[CID].CD[1][1];
		FInvCD[0][0][CID]	= CCD[CID].InvCD[0][0];
		FInvCD[0][1][CID]	= CCD[CID].InvCD[0][1];
		FInvCD[1][0][CID]	= CCD[CID].InvCD[1][0];
		FInvCD[1][1][CID]	= CCD[CID].InvCD[1][1];
		FANGLE[CID]	= CCD[CID].ANGLE;
		FA_ORDER[CID]	= ORDER_ASIP;
		ij=0;
		for(i=0;i<ORDER_ASIP+1;i++)
		for(j=0;j<ORDER_ASIP+1;j++)
		if(i+j<ORDER_ASIP+1){
		FA_SIP[ij][CID]	= CCD[CID].ASIP[0][ij];
		ij++;
		}
		FB_ORDER[CID]	= ORDER_ASIP;
		ij=0;
		for(i=0;i<ORDER_ASIP+1;i++)
		for(j=0;j<ORDER_ASIP+1;j++)
		if(i+j<ORDER_ASIP+1){
		FB_SIP[ij][CID]	= CCD[CID].ASIP[1][ij];
		ij++;
		}
		FAP_ORDER[CID]	= ORDER_PSIP;
		ij=0;
		for(i=0;i<ORDER_PSIP+1;i++)
		for(j=0;j<ORDER_PSIP+1;j++)
		if(i+j<ORDER_PSIP+1){
		FAP_SIP[ij][CID]	= CCD[CID].PSIP[0][ij];
		ij++;
		}
		FBP_ORDER[CID]	= ORDER_PSIP;
		ij=0;
		for(i=0;i<ORDER_PSIP+1;i++)
		for(j=0;j<ORDER_PSIP+1;j++)
		if(i+j<ORDER_PSIP+1){
		FBP_SIP[ij][CID]	= CCD[CID].PSIP[1][ij];
		ij++;
		}
		FMAXR[CID]=MAX_R;

		for(i=0;i<2;i++){
		FAVE_IMPIX[i][CID]	= CCD[CID].AVE_DIF_IMPXL[i];
		FAVE_CRPIX[i][CID]	= CCD[CID].AVE_DIF_CRPIX[i];
		FAVE_LOCAL[i][CID]	= CCD[CID].AVE_DIF_LOCAL[i];
		FAVE_RADEC[i][CID]	= CCD[CID].AVE_DIF_RADEC[i];
		FRMS_IMPIX[i][CID]	= CCD[CID].RMS_DIF_IMPXL[i];
		FRMS_CRPIX[i][CID]	= CCD[CID].RMS_DIF_CRPIX[i];
		FRMS_LOCAL[i][CID]	= CCD[CID].RMS_DIF_LOCAL[i];
		FRMS_RADEC[i][CID]	= CCD[CID].RMS_DIF_RADEC[i];
		FMAX_IMPIX[i][CID]	= CCD[CID].MAX_DIF_IMPXL[i];
		FMAX_CRPIX[i][CID]	= CCD[CID].MAX_DIF_CRPIX[i];
		FMAX_LOCAL[i][CID]	= CCD[CID].MAX_DIF_LOCAL[i];
		FMAX_RADEC[i][CID]	= CCD[CID].MAX_DIF_RADEC[i];
		}
	}

	fits_write_col(fptr,TLONGLONG, 1,1,1,NUM_ROW,FCID,&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TLONGLONG, 2,1,1,NUM_ROW,FNO,&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TLONGLONG, 3,1,1,NUM_ROW,FNF,&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 4,1,1,NUM_ROW,FGPOS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 5,1,1,NUM_ROW,FGPOS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 6,1,1,NUM_ROW,FGPOS[2],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 7,1,1,NUM_ROW,FCRPIX[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 8,1,1,NUM_ROW,FCRPIX[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 9,1,1,NUM_ROW,FCRVAL[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,10,1,1,NUM_ROW,FCRVAL[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,11,1,1,NUM_ROW,FCD[0][0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,12,1,1,NUM_ROW,FCD[0][1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,13,1,1,NUM_ROW,FCD[1][0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,14,1,1,NUM_ROW,FCD[1][1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,15,1,1,NUM_ROW,FInvCD[0][0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,16,1,1,NUM_ROW,FInvCD[0][1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,17,1,1,NUM_ROW,FInvCD[1][0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,18,1,1,NUM_ROW,FInvCD[1][1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,19,1,1,NUM_ROW,FANGLE,&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TLONGLONG,20,1,1,NUM_ROW,FA_ORDER,&status);
	fits_report_error(stderr,status);
	k=21;
	ij=0;
	for(i=0;i<ORDER_ASIP+1;i++)
	for(j=0;j<ORDER_ASIP+1;j++)
	if(i+j<ORDER_ASIP+1){
		fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FA_SIP[ij],&status);
		fits_report_error(stderr,status);
		k++;
		ij++;
	}
	fits_write_col(fptr,TLONGLONG,k,1,1,NUM_ROW,FB_ORDER,&status);
	fits_report_error(stderr,status);
	k++;
	ij=0;
	for(i=0;i<ORDER_ASIP+1;i++)
	for(j=0;j<ORDER_ASIP+1;j++)
	if(i+j<ORDER_ASIP+1){
		fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FB_SIP[ij],&status);
		fits_report_error(stderr,status);
		k++;
		ij++;
	}
	fits_write_col(fptr,TLONGLONG,k,1,1,NUM_ROW,FAP_ORDER,&status);
	fits_report_error(stderr,status);
	k++;
	ij=0;
	for(i=0;i<ORDER_PSIP+1;i++)
	for(j=0;j<ORDER_PSIP+1;j++)
	if(i+j<ORDER_PSIP+1){
		fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FAP_SIP[ij],&status);
		fits_report_error(stderr,status);
		k++;
		ij++;
	}
	fits_write_col(fptr,TLONGLONG,k,1,1,NUM_ROW,FBP_ORDER,&status);
	fits_report_error(stderr,status);
	k++;
	ij=0;
	for(i=0;i<ORDER_PSIP+1;i++)
	for(j=0;j<ORDER_PSIP+1;j++)
	if(i+j<ORDER_PSIP+1){
		fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FBP_SIP[ij],&status);
		fits_report_error(stderr,status);
		k++;
		ij++;
	}

	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FMAXR,&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FAVE_IMPIX[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FAVE_IMPIX[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FAVE_CRPIX[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FAVE_CRPIX[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FAVE_LOCAL[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FAVE_LOCAL[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FAVE_RADEC[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FAVE_RADEC[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FRMS_IMPIX[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FRMS_IMPIX[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FRMS_CRPIX[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FRMS_CRPIX[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FRMS_LOCAL[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FRMS_LOCAL[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FRMS_RADEC[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FRMS_RADEC[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FMAX_IMPIX[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FMAX_IMPIX[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FMAX_CRPIX[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FMAX_CRPIX[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FMAX_LOCAL[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FMAX_LOCAL[1],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FMAX_RADEC[0],&status);
	fits_report_error(stderr,status);
	k++;
	fits_write_col(fptr,TDOUBLE  , k,1,1,NUM_ROW,FMAX_RADEC[1],&status);
	fits_report_error(stderr,status);
	k++;

	fits_close_file(fptr,&status);
	fits_report_error(stderr,status);

	for(i=0;i<NUM_COL;i++){
		delete [] ttype[i];
		delete [] tform[i];
		delete [] tunit[i];
	}
	delete [] ttype;
	delete [] tform;
	delete [] tunit;

	delete [] FCID;
	delete [] FNO;
	delete [] FNF;
	delete [] FGPOS[0];
	delete [] FGPOS[1];
	delete [] FGPOS[2];
	delete [] FCRPIX[0];
	delete [] FCRPIX[1];
	delete [] FCRVAL[0];
	delete [] FCRVAL[1];
	delete [] FCD[0][0];
	delete [] FCD[0][1];
	delete [] FCD[1][0];
	delete [] FCD[1][1];
	delete [] FInvCD[0][0];
	delete [] FInvCD[0][1];
	delete [] FInvCD[1][0];
	delete [] FInvCD[1][1];
	delete [] FANGLE;
	delete [] FMAXR;
	delete [] FA_ORDER;
	delete [] FB_ORDER;
	delete [] FAP_ORDER;
	delete [] FBP_ORDER;
	for(i=0;i<100;i++){
	delete [] FA_SIP[i];
	delete [] FB_SIP[i];
	delete [] FAP_SIP[i];
	delete [] FBP_SIP[i];
	}
	for(i=0;i<2;i++){
	delete [] FAVE_IMPIX[i];
	delete [] FAVE_CRPIX[i];
	delete [] FAVE_LOCAL[i];
	delete [] FAVE_RADEC[i];
	delete [] FRMS_IMPIX[i];
	delete [] FRMS_CRPIX[i];
	delete [] FRMS_LOCAL[i];
	delete [] FRMS_RADEC[i];
	delete [] FMAX_IMPIX[i];
	delete [] FMAX_CRPIX[i];
	delete [] FMAX_LOCAL[i];
	delete [] FMAX_RADEC[i];
	}
}
void CL_ANA::OUT_OBJ(){
	if(STDOUT==1||STDOUT==2)cout << "--- OUTPUT FILE : OBJ ---" <<endl;
	int i,j,status;
	int NUM_COL;
	long NUM_ROW;
	char **ttype,**tform,**tunit,extname[100],outname[100];
	fitsfile *fptr;

	sprintf(outname,"!%s/SLVTANSIP_OBJECTS.fits",DIR_OBJ);

	NUM_ROW=0;
	for(OID=0;OID<NUM_OBJ;OID++)
	NUM_ROW++;
	NUM_COL=64;

	status=0;
	fits_create_file(&fptr,outname,&status);
	fits_report_error(stderr,status);

	ttype = new char*[NUM_COL];
	tform = new char*[NUM_COL];
	tunit = new char*[NUM_COL];
	for(i=0;i<NUM_COL;i++){
		ttype[i]=new char[100];
		tform[i]=new char[100];
		tunit[i]=new char[100];
	}
	sprintf(extname,"MACHED OBJECTS");
	sprintf(ttype[ 0],"OBJID");
	sprintf(tform[ 0],"K");
	sprintf(tunit[ 0],"");
	sprintf(ttype[ 1],"DET-ID");
	sprintf(tform[ 1],"K");
	sprintf(tunit[ 1],"");
	sprintf(ttype[ 2],"OBJFLAG");
	sprintf(tform[ 2],"K");
	sprintf(tunit[ 2],"");
	sprintf(ttype[ 3],"X_LOCAL");
	sprintf(tform[ 3],"D");
	sprintf(tunit[ 3],"pixel");
	sprintf(ttype[ 4],"Y_LOCAL");
	sprintf(tform[ 4],"D");
	sprintf(tunit[ 4],"pixel");
	sprintf(ttype[ 5],"RA");
	sprintf(tform[ 5],"D");
	sprintf(tunit[ 5],"degree");
	sprintf(ttype[ 6],"DEC");
	sprintf(tform[ 6],"D");
	sprintf(tunit[ 6],"degree");
	sprintf(ttype[ 7],"X_GLOBAL");
	sprintf(tform[ 7],"D");
	sprintf(tunit[ 7],"pixel");
	sprintf(ttype[ 8],"Y_GLOBAL");
	sprintf(tform[ 8],"D");
	sprintf(tunit[ 8],"pixel");
	sprintf(ttype[ 9],"X_CRPIXLOCAL");
	sprintf(tform[ 9],"D");
	sprintf(tunit[ 9],"pixel");
	sprintf(ttype[10],"Y_CRPIXLOCAL");
	sprintf(tform[10],"D");
	sprintf(tunit[10],"pixel");
	sprintf(ttype[11],"X_CRPIXGLOBAL");
	sprintf(tform[11],"D");
	sprintf(tunit[11],"pixel");
	sprintf(ttype[12],"Y_CRPIXGLOBAL");
	sprintf(tform[12],"D");
	sprintf(tunit[12],"pixel");
	sprintf(ttype[13],"X_IMPIXELLOCAL");
	sprintf(tform[13],"D");
	sprintf(tunit[13],"pixel");
	sprintf(ttype[14],"Y_IMPIXELLOCAL");
	sprintf(tform[14],"D");
	sprintf(tunit[14],"pixel");
	sprintf(ttype[15],"X_IMPXLGLOBAL");
	sprintf(tform[15],"D");
	sprintf(tunit[15],"pixel");
	sprintf(ttype[16],"Y_IMPXLGLOBAL");
	sprintf(tform[16],"D");
	sprintf(tunit[16],"pixel");
	sprintf(ttype[17],"X_IMWORLD");
	sprintf(tform[17],"D");
	sprintf(tunit[17],"pixel");
	sprintf(ttype[18],"Y_IMWORLD");
	sprintf(tform[18],"D");
	sprintf(tunit[18],"degree");

	sprintf(ttype[19],"X_LOCAL_TANSIPfromRADEC");
	sprintf(tform[19],"D");
	sprintf(tunit[19],"pixel");
	sprintf(ttype[20],"Y_LOCAL_TANSIPfromRADEC");
	sprintf(tform[20],"D");
	sprintf(tunit[20],"pixel");
	sprintf(ttype[21],"RA_TANSIPfromLOCAL");
	sprintf(tform[21],"D");
	sprintf(tunit[21],"degree");
	sprintf(ttype[22],"DEC_TANSIPfromLOCAL");
	sprintf(tform[22],"D");
	sprintf(tunit[22],"degree");
	sprintf(ttype[23],"RA_TANSIPfromGLOBAL");
	sprintf(tform[23],"D");
	sprintf(tunit[23],"degree");
	sprintf(ttype[24],"DEC_TANSIPfromGLOBAL");
	sprintf(tform[24],"D");
	sprintf(tunit[24],"degree");
	sprintf(ttype[25],"X_GLOBAL_TANSIPfromRADEC");
	sprintf(tform[25],"D");
	sprintf(tunit[25],"pixel");
	sprintf(ttype[26],"Y_GLOBAL_TANSIPfromRADEC");
	sprintf(tform[26],"D");
	sprintf(tunit[26],"pixel");
	sprintf(ttype[27],"X_CRPIXLOCAL_TANSIPfromRADEC");
	sprintf(tform[27],"D");
	sprintf(tunit[27],"pixel");
	sprintf(ttype[28],"Y_CRPIXLOCAL_TANSIPfromRADEC");
	sprintf(tform[28],"D");
	sprintf(tunit[28],"pixel");
	sprintf(ttype[29],"X_CRPIXGLOBAL_TANSIPfromRADEC");
	sprintf(tform[29],"D");
	sprintf(tunit[29],"pixel");
	sprintf(ttype[30],"Y_CRPIXGLOBAL_TANSIPfromRADEC");
	sprintf(tform[30],"D");
	sprintf(tunit[30],"pixel");
	sprintf(ttype[31],"X_IMPIXELLOCAL_TANSIPfromLOCAL");
	sprintf(tform[31],"D");
	sprintf(tunit[31],"pixel");
	sprintf(ttype[32],"Y_IMPIXELLOCAL_TANSIPfromLOCAL");
	sprintf(tform[32],"D");
	sprintf(tunit[32],"pixel");
	sprintf(ttype[33],"X_IMPIXELGLOBAL_TANSIPfromGLOBAL");
	sprintf(tform[33],"D");
	sprintf(tunit[33],"pixel");
	sprintf(ttype[34],"Y_IMPIXELGLOBAL_TANSIPfromGLOBAL");
	sprintf(tform[34],"D");
	sprintf(tunit[34],"pixel");
	sprintf(ttype[35],"X_IMWORLD_TANSIPfromLOCAL");
	sprintf(tform[35],"D");
	sprintf(tunit[35],"degree");
	sprintf(ttype[36],"Y_IMWORLD_TANSIPfromLOCAL");
	sprintf(tform[36],"D");
	sprintf(tunit[36],"degree");
	sprintf(ttype[37],"X_IMWORLD_TANSIPfromGLOBAL");
	sprintf(tform[37],"D");
	sprintf(tunit[37],"degree");
	sprintf(ttype[38],"Y_IMWORLD_TANSIPfromGLOBAL");
	sprintf(tform[38],"D");
	sprintf(tunit[38],"degree");

	sprintf(ttype[39],"X_LOCAL_TANfromRADEC");
	sprintf(tform[39],"D");
	sprintf(tunit[39],"pixel");
	sprintf(ttype[40],"Y_LOCAL_TANfromRADEC");
	sprintf(tform[40],"D");
	sprintf(tunit[40],"pixel");
	sprintf(ttype[41],"RA_TANfromLOCAL");
	sprintf(tform[41],"D");
	sprintf(tunit[41],"degree");
	sprintf(ttype[42],"DEC_TANfromLOCAL");
	sprintf(tform[42],"D");
	sprintf(tunit[42],"degree");
	sprintf(ttype[43],"RA_TANfromGLOBAL");
	sprintf(tform[43],"D");
	sprintf(tunit[43],"degree");
	sprintf(ttype[44],"DEC_TANfromGLOBAL");
	sprintf(tform[44],"D");
	sprintf(tunit[44],"degree");
	sprintf(ttype[45],"X_GLOBAL_TANfromRADEC");
	sprintf(tform[45],"D");
	sprintf(tunit[45],"pixel");
	sprintf(ttype[46],"Y_GLOBAL_TANfromRADEC");
	sprintf(tform[46],"D");
	sprintf(tunit[46],"pixel");
	sprintf(ttype[47],"X_CRPIXLOCAL_TANfromRADEC");
	sprintf(tform[47],"D");
	sprintf(tunit[47],"pixel");
	sprintf(ttype[48],"Y_CRPIXLOCAL_TANfromRADEC");
	sprintf(tform[48],"D");
	sprintf(tunit[48],"pixel");
	sprintf(ttype[49],"X_CRPIXGLOBAL_TANfromRADEC");
	sprintf(tform[49],"D");
	sprintf(tunit[49],"pixel");
	sprintf(ttype[50],"Y_CRPIXGLOBAL_TANfromRADEC");
	sprintf(tform[50],"D");
	sprintf(tunit[50],"pixel");
	sprintf(ttype[51],"X_IMPIXELLOCAL_TANfromLOCAL");
	sprintf(tform[51],"D");
	sprintf(tunit[51],"pixel");
	sprintf(ttype[52],"Y_IMPIXELLOCAL_TANfromLOCAL");
	sprintf(tform[52],"D");
	sprintf(tunit[52],"pixel");
	sprintf(ttype[53],"X_IMPIXELGLOBAL_TANfromGLOBAL");
	sprintf(tform[53],"D");
	sprintf(tunit[53],"pixel");
	sprintf(ttype[54],"Y_IMPIXELGLOBAL_TANfromGLOBAL");
	sprintf(tform[54],"D");
	sprintf(tunit[54],"pixel");
	sprintf(ttype[55],"X_IMWORLD_TANfromRLOCAL");
	sprintf(tform[55],"D");
	sprintf(tunit[55],"degree");
	sprintf(ttype[56],"Y_IMWORLD_TANfromRLOCAL");
	sprintf(tform[56],"D");
	sprintf(tunit[56],"degree");
	sprintf(ttype[57],"X_IMWORLD_TANfromGLOBAL");
	sprintf(tform[57],"D");
	sprintf(tunit[57],"degree");
	sprintf(ttype[58],"Y_IMWORLD_TANfromGLOBAL");
	sprintf(tform[58],"D");
	sprintf(tunit[58],"degree");

	sprintf(ttype[59],"OPTIC_MAGNIFICATION");
	sprintf(tform[59],"D");
	sprintf(tunit[59],"");
	sprintf(ttype[60],"OPTIC_CONVERGENCE");
	sprintf(tform[60],"D");
	sprintf(tunit[60],"");
	sprintf(ttype[61],"OPTIC_SHEAR1");
	sprintf(tform[61],"D");
	sprintf(tunit[61],"");
	sprintf(ttype[62],"OPTIC_SHEAR2");
	sprintf(tform[62],"D");
	sprintf(tunit[62],"");
	sprintf(ttype[63],"OPTIC_ROTATION");
	sprintf(tform[63],"D");
	sprintf(tunit[63],"");

	fits_create_tbl(fptr,BINARY_TBL,NUM_ROW,NUM_COL,ttype,tform,tunit,extname,&status);
	fits_report_error(stderr,status);

	long long int *FID,*FCID,*FFLAG;
	double  *FL[2],  *FW[2],          *FG[2],* FCL[2], *FCG[2], *FIL[2], *FIG[2], *FIW[2];
	double *FLS[2],*FWLS[2],*FWGS[2],*FGS[2],*FCLS[2],*FCGS[2],*FILS[2],*FIGS[2],*FIWLS[2],*FIWGS[2];
	double *FLT[2],*FWLT[2],*FWGT[2],*FGT[2],*FCLT[2],*FCGT[2],*FILT[2],*FIGT[2],*FIWLT[2],*FIWGT[2];
	double *OPT_MAG,*OPT_CONV,*OPT_SHEAR[2],*OPT_ROT;

	FID     = new long long int[NUM_ROW];
	FCID     = new long long int[NUM_ROW];
	FFLAG   = new long long int[NUM_ROW];
	FL[0]   = new double[NUM_ROW];
	FL[1]   = new double[NUM_ROW];
	FW[0]   = new double[NUM_ROW];
	FW[1]   = new double[NUM_ROW];
	FG[0]   = new double[NUM_ROW];
	FG[1]   = new double[NUM_ROW];
	FCL[0]  = new double[NUM_ROW];
	FCL[1]  = new double[NUM_ROW];
	FCG[0]  = new double[NUM_ROW];
	FCG[1]  = new double[NUM_ROW];
	FIL[0]  = new double[NUM_ROW];
	FIL[1]  = new double[NUM_ROW];
	FIG[0]  = new double[NUM_ROW];
	FIG[1]  = new double[NUM_ROW];
	FIW[0]  = new double[NUM_ROW];
	FIW[1]  = new double[NUM_ROW];
	FLS[0]  = new double[NUM_ROW];
	FLS[1]  = new double[NUM_ROW];
	FWLS[0] = new double[NUM_ROW];
	FWLS[1] = new double[NUM_ROW];
	FWGS[0] = new double[NUM_ROW];
	FWGS[1] = new double[NUM_ROW];
	FGS[0]  = new double[NUM_ROW];
	FGS[1]  = new double[NUM_ROW];
	FCLS[0] = new double[NUM_ROW];
	FCLS[1] = new double[NUM_ROW];
	FCGS[0] = new double[NUM_ROW];
	FCGS[1] = new double[NUM_ROW];
	FILS[0] = new double[NUM_ROW];
	FILS[1] = new double[NUM_ROW];
	FIGS[0] = new double[NUM_ROW];
	FIGS[1] = new double[NUM_ROW];
	FIWLS[0]= new double[NUM_ROW];
	FIWLS[1]= new double[NUM_ROW];
	FIWGS[0]= new double[NUM_ROW];
	FIWGS[1]= new double[NUM_ROW];
	FLT[0]  = new double[NUM_ROW];
	FLT[1]  = new double[NUM_ROW];
	FWLT[0] = new double[NUM_ROW];
	FWLT[1] = new double[NUM_ROW];
	FWGT[0] = new double[NUM_ROW];
	FWGT[1] = new double[NUM_ROW];
	FGT[0]  = new double[NUM_ROW];
	FGT[1]  = new double[NUM_ROW];
	FCLT[0] = new double[NUM_ROW];
	FCLT[1] = new double[NUM_ROW];
	FCGT[0] = new double[NUM_ROW];
	FCGT[1] = new double[NUM_ROW];
	FILT[0] = new double[NUM_ROW];
	FILT[1] = new double[NUM_ROW];
	FIGT[0] = new double[NUM_ROW];
	FIGT[1] = new double[NUM_ROW];
	FIWLT[0]= new double[NUM_ROW];
	FIWLT[1]= new double[NUM_ROW];
	FIWGT[0]= new double[NUM_ROW];
	FIWGT[1]= new double[NUM_ROW];
	OPT_MAG      = new double[NUM_ROW];
	OPT_CONV     = new double[NUM_ROW];
	OPT_SHEAR[0] = new double[NUM_ROW];
	OPT_SHEAR[1] = new double[NUM_ROW];
	OPT_ROT      = new double[NUM_ROW];

	for(OID=0;OID<NUM_OBJ;OID++){
		FID[OID]     = OBJ[OID].ID_OBJ;
		FCID[OID]     = OBJ[OID].ID_CHIP;
		FFLAG[OID]   = OBJ[OID].FLAG_OBJ;
		FL[0][OID]   = OBJ[OID].X_LOCAL[0];
		FL[1][OID]   = OBJ[OID].X_LOCAL[1];
		FW[0][OID]   = OBJ[OID].X_RADEC[0];
		FW[1][OID]   = OBJ[OID].X_RADEC[1];
		FG[0][OID]   = OBJ[OID].X_GLOBL[0];
		FG[1][OID]   = OBJ[OID].X_GLOBL[1];
		FCL[0][OID]  = OBJ[OID].X_CRPIXLOCAL[0];
		FCL[1][OID]  = OBJ[OID].X_CRPIXLOCAL[1];
		FCG[0][OID]  = OBJ[OID].X_CRPIXGLOBL[0];
		FCG[1][OID]  = OBJ[OID].X_CRPIXGLOBL[1];
		FIL[0][OID]  = OBJ[OID].X_IMPXLLOCAL[0];
		FIL[1][OID]  = OBJ[OID].X_IMPXLLOCAL[1];
		FIG[0][OID]  = OBJ[OID].X_IMPXLGLOBL[0];
		FIG[1][OID]  = OBJ[OID].X_IMPXLGLOBL[1];
		FIW[0][OID]  = OBJ[OID].X_IMWLD[0];
		FIW[1][OID]  = OBJ[OID].X_IMWLD[1];
		FLS[0][OID]   = OBJ[OID].X_LOCAL_SIPfromRADEC[0];
		FLS[1][OID]   = OBJ[OID].X_LOCAL_SIPfromRADEC[1];
		FWLS[0][OID]  = OBJ[OID].X_RADEC_SIPfromLOCAL[0];
		FWLS[1][OID]  = OBJ[OID].X_RADEC_SIPfromLOCAL[1];
		FWGS[0][OID]  = OBJ[OID].X_RADEC_SIPfromGLOBL[0];
		FWGS[1][OID]  = OBJ[OID].X_RADEC_SIPfromGLOBL[1];
		FGS[0][OID]   = OBJ[OID].X_GLOBL_SIPfromRADEC[0];
		FGS[1][OID]   = OBJ[OID].X_GLOBL_SIPfromRADEC[1];
		FCLS[0][OID]  = OBJ[OID].X_CRPIXLOCAL_SIPfromRADEC[0];
		FCLS[1][OID]  = OBJ[OID].X_CRPIXLOCAL_SIPfromRADEC[1];
		FCGS[0][OID]  = OBJ[OID].X_CRPIXGLOBL_SIPfromRADEC[0];
		FCGS[1][OID]  = OBJ[OID].X_CRPIXGLOBL_SIPfromRADEC[1];
		FILS[0][OID]  = OBJ[OID].X_IMPXLLOCAL_SIPfromLOCAL[0];
		FILS[1][OID]  = OBJ[OID].X_IMPXLLOCAL_SIPfromLOCAL[1];
		FIGS[0][OID]  = OBJ[OID].X_IMPXLGLOBL_SIPfromGLOBL[0];
		FIGS[1][OID]  = OBJ[OID].X_IMPXLGLOBL_SIPfromGLOBL[1];
		FIWLS[0][OID] = OBJ[OID].X_IMWLD_SIPfromLOCAL[0];
		FIWLS[1][OID] = OBJ[OID].X_IMWLD_SIPfromLOCAL[1];
		FIWGS[0][OID] = OBJ[OID].X_IMWLD_SIPfromGLOBL[0];
		FIWGS[1][OID] = OBJ[OID].X_IMWLD_SIPfromGLOBL[1];
		FLT[0][OID]   = OBJ[OID].X_LOCAL_TANfromRADEC[0];
		FLT[1][OID]   = OBJ[OID].X_LOCAL_TANfromRADEC[1];
		FWLT[0][OID]  = OBJ[OID].X_RADEC_TANfromLOCAL[0];
		FWLT[1][OID]  = OBJ[OID].X_RADEC_TANfromLOCAL[1];
		FWGT[0][OID]  = OBJ[OID].X_RADEC_TANfromGLOBL[0];
		FWGT[1][OID]  = OBJ[OID].X_RADEC_TANfromGLOBL[1];
		FGT[0][OID]   = OBJ[OID].X_GLOBL_TANfromRADEC[0];
		FGT[1][OID]   = OBJ[OID].X_GLOBL_TANfromRADEC[1];
		FCLT[0][OID]  = OBJ[OID].X_CRPIXLOCAL_TANfromRADEC[0];
		FCLT[1][OID]  = OBJ[OID].X_CRPIXLOCAL_TANfromRADEC[1];
		FCGT[0][OID]  = OBJ[OID].X_CRPIXGLOBL_TANfromRADEC[0];
		FCGT[1][OID]  = OBJ[OID].X_CRPIXGLOBL_TANfromRADEC[1];
		FILT[0][OID]  = OBJ[OID].X_IMPXLLOCAL_TANfromLOCAL[0];
		FILT[1][OID]  = OBJ[OID].X_IMPXLLOCAL_TANfromLOCAL[1];
		FIGT[0][OID]  = OBJ[OID].X_IMPXLGLOBL_TANfromGLOBL[0];
		FIGT[1][OID]  = OBJ[OID].X_IMPXLGLOBL_TANfromGLOBL[1];
		FIWLT[0][OID] = OBJ[OID].X_IMWLD_TANfromLOCAL[0];
		FIWLT[1][OID] = OBJ[OID].X_IMWLD_TANfromLOCAL[1];
		FIWGT[0][OID] = OBJ[OID].X_IMWLD_TANfromGLOBL[0];
		FIWGT[1][OID] = OBJ[OID].X_IMWLD_TANfromGLOBL[1];
		OPT_MAG[OID]      = OBJ[OID].OPT_MAG;
		OPT_CONV[OID]     = OBJ[OID].OPT_CONV;
		OPT_SHEAR[0][OID] = OBJ[OID].OPT_SHEAR[0];
		OPT_SHEAR[1][OID] = OBJ[OID].OPT_SHEAR[1];
		OPT_ROT[OID]      = OBJ[OID].OPT_ROT;
	}

	fits_write_col(fptr,TLONGLONG, 1,1,1,NUM_ROW,FID,&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TLONGLONG, 2,1,1,NUM_ROW,FCID,&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TLONGLONG, 3,1,1,NUM_ROW,FFLAG,&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 4,1,1,NUM_ROW,FL[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 5,1,1,NUM_ROW,FL[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 6,1,1,NUM_ROW,FW[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 7,1,1,NUM_ROW,FW[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 8,1,1,NUM_ROW,FG[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  , 9,1,1,NUM_ROW,FG[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,10,1,1,NUM_ROW,FCL[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,11,1,1,NUM_ROW,FCL[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,12,1,1,NUM_ROW,FCG[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,13,1,1,NUM_ROW,FCG[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,14,1,1,NUM_ROW,FIL[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,15,1,1,NUM_ROW,FIL[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,16,1,1,NUM_ROW,FIG[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,17,1,1,NUM_ROW,FIG[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,18,1,1,NUM_ROW,FIW[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,19,1,1,NUM_ROW,FIW[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,20,1,1,NUM_ROW,FLS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,21,1,1,NUM_ROW,FLS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,22,1,1,NUM_ROW,FWLS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,23,1,1,NUM_ROW,FWLS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,24,1,1,NUM_ROW,FWGS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,25,1,1,NUM_ROW,FWGS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,26,1,1,NUM_ROW,FGS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,27,1,1,NUM_ROW,FGS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,28,1,1,NUM_ROW,FCLS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,29,1,1,NUM_ROW,FCLS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,30,1,1,NUM_ROW,FCGS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,31,1,1,NUM_ROW,FCGS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,32,1,1,NUM_ROW,FILS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,33,1,1,NUM_ROW,FILS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,34,1,1,NUM_ROW,FIGS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,35,1,1,NUM_ROW,FIGS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,36,1,1,NUM_ROW,FIWLS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,37,1,1,NUM_ROW,FIWLS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,38,1,1,NUM_ROW,FIWGS[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,39,1,1,NUM_ROW,FIWGS[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,40,1,1,NUM_ROW,FLT[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,41,1,1,NUM_ROW,FLT[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,42,1,1,NUM_ROW,FWLT[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,43,1,1,NUM_ROW,FWLT[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,44,1,1,NUM_ROW,FWGT[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,45,1,1,NUM_ROW,FWGT[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,46,1,1,NUM_ROW,FGT[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,47,1,1,NUM_ROW,FGT[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,48,1,1,NUM_ROW,FCLT[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,49,1,1,NUM_ROW,FCLT[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,50,1,1,NUM_ROW,FCGT[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,51,1,1,NUM_ROW,FCGT[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,52,1,1,NUM_ROW,FILT[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,53,1,1,NUM_ROW,FILT[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,54,1,1,NUM_ROW,FIGT[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,55,1,1,NUM_ROW,FIGT[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,56,1,1,NUM_ROW,FIWLT[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,57,1,1,NUM_ROW,FIWLT[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,58,1,1,NUM_ROW,FIWGT[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,59,1,1,NUM_ROW,FIWGT[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,60,1,1,NUM_ROW,OPT_MAG,&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,61,1,1,NUM_ROW,OPT_CONV,&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,62,1,1,NUM_ROW,OPT_SHEAR[0],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,63,1,1,NUM_ROW,OPT_SHEAR[1],&status);
	fits_report_error(stderr,status);
	fits_write_col(fptr,TDOUBLE  ,64,1,1,NUM_ROW,OPT_ROT,&status);
	fits_report_error(stderr,status);


	fits_close_file(fptr,&status);
	fits_report_error(stderr,status);
	for(i=0;i<NUM_COL;i++){
		delete [] ttype[i];
		delete [] tform[i];
		delete [] tunit[i];
	}
	delete [] ttype;
	delete [] tform;
	delete [] tunit;

	delete [] FID;
	delete [] FCID;
	delete [] FFLAG;
	delete [] FL[0];  
	delete [] FL[1];  
	delete [] FW[0];  
	delete [] FW[1];  
	delete [] FG[0];  
	delete [] FG[1];  
	delete [] FCL[0];  
	delete [] FCL[1]; 
	delete [] FCG[0]; 
	delete [] FCG[1]; 
	delete [] FIL[0]; 
	delete [] FIL[1]; 
	delete [] FIG[0]; 
	delete [] FIG[1]; 
	delete [] FIW[0]; 
	delete [] FIW[1]; 
	delete [] FLS[0]; 
	delete [] FLS[1]; 
	delete [] FWLS[0]; 
	delete [] FWLS[1]; 
	delete [] FWGS[0]; 
	delete [] FWGS[1]; 
	delete [] FGS[0]; 
	delete [] FGS[1]; 
	delete [] FCLS[0]; 
	delete [] FCLS[1];
	delete [] FCGS[0];
	delete [] FCGS[1];
	delete [] FILS[0];
	delete [] FILS[1];
	delete [] FIGS[0];
	delete [] FIGS[1];
	delete [] FIWLS[0];
	delete [] FIWLS[1];
	delete [] FIWGS[0];
	delete [] FIWGS[1];
	delete [] FLT[0];
	delete [] FLT[1];
	delete [] FWLT[0];
	delete [] FWLT[1];
	delete [] FWGT[0];
	delete [] FWGT[1];
	delete [] FGT[0];
	delete [] FGT[1];
	delete [] FCLT[0];
	delete [] FCLT[1];
	delete [] FCGT[0];
	delete [] FCGT[1];
	delete [] FILT[0];
	delete [] FILT[1];
	delete [] FIGT[0];
	delete [] FIGT[1];
	delete [] FIWLT[0];
	delete [] FIWLT[1];
	delete [] FIWGT[0];
	delete [] FIWGT[1];
	delete [] OPT_MAG;
	delete [] OPT_CONV;
	delete [] OPT_SHEAR[0];
	delete [] OPT_SHEAR[1];
	delete [] OPT_ROT;
}

