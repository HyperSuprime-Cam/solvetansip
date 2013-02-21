//--------------------------------------------------
//SLVTANSIP_OBJ.h
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#ifndef SLVTANSIP_OBJ_H
#define SLVTANSIP_OBJ_H

#include<iostream>

using namespace std;
class CL_OBJ{
private:
public:
	long long int ID_OBJ;
	int ID_CHIP;
	int FLAG_OBJ;
	double X_LOCAL[2];
	double X_GLOBL[2];
	double X_CRPIXLOCAL[2];
	double X_CRPIXGLOBL[2];
	double X_IMPXLLOCAL[2];
	double X_IMPXLGLOBL[2];
	double X_IMWLD[2];
	double X_RADEC[2];
//double X_CENTER[2];
	double X_LOCAL_TANfromRADEC[2];
	double X_GLOBL_TANfromRADEC[2];
	double X_CRPIXLOCAL_TANfromRADEC[2];
	double X_CRPIXGLOBL_TANfromRADEC[2];
	double X_IMPXLLOCAL_TANfromLOCAL[2];
	double X_IMPXLGLOBL_TANfromGLOBL[2];
	double X_IMWLD_TANfromLOCAL[2];
	double X_IMWLD_TANfromGLOBL[2];
	double X_RADEC_TANfromLOCAL[2];
	double X_RADEC_TANfromGLOBL[2];
	double X_LOCAL_SIPfromRADEC[2];
	double X_GLOBL_SIPfromRADEC[2];
	double X_CRPIXLOCAL_SIPfromRADEC[2];
	double X_CRPIXGLOBL_SIPfromRADEC[2];
	double X_IMPXLLOCAL_SIPfromLOCAL[2];
	double X_IMPXLGLOBL_SIPfromGLOBL[2];
	double X_IMWLD_SIPfromLOCAL[2];
	double X_IMWLD_SIPfromGLOBL[2];
	double X_RADEC_SIPfromLOCAL[2];
	double X_RADEC_SIPfromGLOBL[2];
	
	double dX_LOCAL_IMWLD_FIT[2][2];
	double dX_GLOBL_IMWLD[2][2];
	double dX_GLOBL_IMWLD_FIT[2][2];
	double X_GLOBL_FIT[2];

	double OPT_MAG;
	double OPT_CONV;
	double OPT_SHEAR[2];
	double OPT_ROT;
};
#endif
