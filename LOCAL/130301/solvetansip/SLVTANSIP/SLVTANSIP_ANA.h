//--------------------------------------------------
//SLVTANSIP_ANA.h
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#ifndef SLVTANSIP_ANA_H
#define SLVTANSIP_ANA_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include"SLVTANSIP_CCD.h"
#include"SLVTANSIP_OBJ.h"
#include"SLVTANSIP_SUB.h"
#include"LeastSquares.h"

using namespace std;
class CL_ANA{
private:
public:
	CL_CCD* CCD;
	CL_OBJ* OBJ;
	int CID,CID2,OID;

	char NAME_PRM[100];
	char NAME_OBJ[100];
	char INSTR[10];
	char MODE_CR[10];//AUTO or PIX or VAL or OAXIS
	char MODE_OA[10];//MIN or REV
	int  MODE_CCDPOS;
	int  MODE_CCDPOSH;
	int  MODE_REJ;
	int  ORDER_ASIP;
	int  ORDER_PSIP;
	int  ORDER_LSIP;
	double CRVAL[2];
	double CRPIX[2];
	double CENTER_PIXEL[2];
	double CENTER_RADEC[2];
	int  NUM_CCD;
	int  NUM_OBJ;
	int  NUM_FIT;
	int  NUM_REJ;
	int  FLAG_ANA;
	double GPOS_BASIS[3];
	double CLIP_SIGMA;
	double MAX_R;
	double DIFF[2][2];
	int  EXTRACALC;
	int  PVCALC;
	int  STDOUT;
	int  FILEOUT;
	int  PVOUT;
	int  PAFOUT;
	char DIR_CCD[100];
	char DIR_OBJ[100];


//SLVTANSIP_ANA_SET
	void SET_DATA(char* prmfile,char* objfile);
	void SET_PRM1st();
	void SET_PRM2nd();
	void CHECK_PRM1st();
	void CHECK_PRM2nd();
	void SET_INITCCD_SC();
	void SET_INITCCD_HSC();
	void NEW_MEMORY();
	void DEL_MEMORY();
	void SHOW_ANA();
	void SHOW_CCD(int);
	void SHOW_OBJ(int);

//SLVTANSIP_ANA_SLV
	void SLV_DATA();
	void MEAS_CR();
	void SET_CENTERCR();
	void FIT_GLOBL(int APL,int VARIABLE,int FUNCTION, double **Coef);
	void FIT_LOCAL(int APL,int VARIABLE,int FUNCTION);
	void CALC_DIFF(int V1,int V2, double DIFF[2][2]);
	void REJ_BAD();
	void MEAS_CCDPOS();
	void CALC_POSITIONS();
	void CALC_POSITIONS_LOCAL();
	void CALC_DISTROTION();

//SLVTANSIP_ANA_EXT
	void EXT_DATA();
	void CALC_TANSIPPOS();
	void CALC_TANPOS();
	void CALC_MAX_R();
	void CALC_RMS();
	void CALC_LOCALDISTORTION();
	void CALC_PV();

//SLVTANSIP_ANA_OUT
	void OUT_DATA();
	void OUT_CCD();
	void OUT_CCD_ALL();
	void OUT_PAF();
	void OUT_CCD_PV();
	void OUT_OBJ();

//SLVTANSIP_ANA_CCD
	void MEAS_CCDPOS_T();
	void MEAS_CCDPOS_XY();
	void MEAS_CCDPOS_XYT();
	void CCDPOSITIONS_T_MAT();
	void ROT_CRCDSIP();

//SLVTANSIP_ANA_POS
	void CALC_CRPIX();
	void CALC_CRVAL();
	void CALC_X_GLOBL();
	void CALC_X_CRPIXLOCAL();
	void CALC_X_CRPIXGLOBL();
	void CALC_X_IMWLD();
	void CALC_X_IMPXLGLOBL();
	void CALC_X_IMPXLLOCAL();
	void CALC_X_CRPIXGLOBL_TAN();
	void CALC_X_CRPIXLOCAL_TAN();
	void CALC_X_GLOBL_TAN();
	void CALC_X_LOCAL_TAN();
	void CALC_X_IMPXLGLOBL_TAN();
	void CALC_X_IMPXLLOCAL_TAN();
	void CALC_X_IMWLDGLOBL_TAN();
	void CALC_X_IMWLDLOCAL_TAN();
	void CALC_X_RADEC_TAN();
	void CALC_X_CRPIXGLOBL_SIP();
	void CALC_X_CRPIXLOCAL_SIP();
	void CALC_X_GLOBL_SIP();
	void CALC_X_LOCAL_SIP();
	void CALC_X_IMPXLGLOBL_SIP();
	void CALC_X_IMPXLLOCAL_SIP();
	void CALC_X_IMWLDGLOBL_SIP();
	void CALC_X_IMWLDLOCAL_SIP();
	void CALC_X_RADEC_SIP();
	void CALC_X_CENTER();
	void CALC_X_GLOBLfromIMWLD();
	void CALC_X_RADECfromCRPIXGLOBL();
	void CALC_DIST();

//SLVTANSIP_ANA_DIST
	void DIV_ASIP();
	void DIV_PSIP();
	void SET_PSIP();
	void SET_LOCAL();



//SLVTANSIP_TOOL
	void MAKE_ANAfromfits(std::string CCDDIR);
	void DEL_ANAfromfits();

};
#endif
