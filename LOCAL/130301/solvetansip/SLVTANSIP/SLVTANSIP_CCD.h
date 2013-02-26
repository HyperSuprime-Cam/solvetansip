//--------------------------------------------------
//SLVTANSIP_CCD.h
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#ifndef SLVTANSIP_CCD_H
#define SLVTANSIP_CCD_H

#include<iostream>

using namespace std;
class CL_CCD{
private:
public:
	int ID_CHIP;
	int NUM_OBJ;
	int NUM_FIT;
	double GPOS[3];
	double GPOS_INIT[3];
	double CRVAL[2];
	double CRPIX[2];
	double CD[2][2];
	double InvCD[2][2];
	double CDP[2][2];
	double InvCDP[2][2];
	double ANGLE;
	double *CDASIP[2];
	double *CDPSIP[2];
	double *ASIP[2];
	double *PSIP[2];
	double *dCDPSIP[2][2];
	double *dPSIP[2][2];
	double *LCDSIP[2];
	double *dLCDSIP[2][2];
	double *LCoef[2];	
	double *PV[2];
	double AVE_DIF_CRPIX[2];
	double AVE_DIF_IMPXL[2];
	double AVE_DIF_LOCAL[2];
	double AVE_DIF_RADEC[2];
	double RMS_DIF_CRPIX[2];
	double RMS_DIF_IMPXL[2];
	double RMS_DIF_LOCAL[2];
	double RMS_DIF_RADEC[2];
	double MAX_DIF_CRPIX[2];
	double MAX_DIF_IMPXL[2];
	double MAX_DIF_LOCAL[2];
	double MAX_DIF_RADEC[2];
};
#endif
