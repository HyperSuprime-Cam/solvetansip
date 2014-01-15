//-----------------------------------------------------------
//CCD.h
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef CCD_H
#define CCD_H

#include<vector>
#include<string>
#include<cmath>
#include<iostream>
#include<iomanip>
#include"hsc/meas/tansip/APRM.h"
#include"hsc/meas/tansip/CPP.h"

class CL_CCD{
private:
public:
	CL_APRM *APRM;
	int	 ID;
	int	 NUM_REF;
	int	 NUM_FIT;
	int	 NUM_REJ;
	double	 GPOS_C[4];//pixel,pixel,radian,degree
	double	 GPOS_L[4];//pixel,pixel,radian,degree
	int      LENGTH[2];
	double   ANGLE;
	double	*CRVAL[2];
	double	*CRPIX[2];
	double	 OAPIX[2];
	double	 CD[2][2];
	double	 InvCD[2][2];
	int	*ORDER_ASIP;
	int	*ORDER_PSIP;
	double	*ASIP[2];
	double	*PSIP[2];
	double	*PSIP_CONV;
	double	*PSIP_ROT;
	double	*PSIP_SHEAR[2];
	double	*PSIP_MAG;
	double	*PSIP_JACO;
	double	 DIF_AVE_ASIP[2];
	double	 DIF_AVE_PSIP[2];
	double	 DIF_RMS_ASIP[2];
	double	 DIF_RMS_PSIP[2];
	double	 DIF_MAX_ASIP[2];
	double	 DIF_MAX_PSIP[2];

	void SET_INIT();
	void SET_END();
	void GET_GPOS_LfromGPOS_C();
	void GET_GPOS_CfromGPOS_L();
	void SET_CDASIP();
	void SET_CDPSIP();
	void SET_SIPROT(int ORDER,double *COEF_IN, double *COEF);
	void SHOW();
};
class CL_CCDs{
private:
public:
	CL_APRM *APRM;
	CL_CCD  *CCD;
	int     *MODE_CCDPOS;
	int     *NUM_CCD;
	double	 GPOS_C_BASIS[4];//pixel,pixel,radian,degree
	int	*ORDER_ASIP;
	int	*ORDER_PSIP;
	double	*CRVAL[2];
	double	*CRPIX[2];
	int	*FLAG_STD;
	double   MAX_CRPIX_G_R;
	double   MAX_CRPIX_G[2];
	double   MIN_CRPIX_G[2];
	double   AVE_CRPIX_G[2];

	
	void SET_INIT(CL_APRM *APRM);
	void SET_INPUT(std::vector< std::vector< std::string > > CCD_Argvs,CL_APRM *APRM);
	void SET_END();
	int  CHECK();
	int  CHECK_NUMCCD();
	int  CHECK_NUMFIT();
	int  CHECK_NUMFITALL();
	void GET_GPOS_LfromGPOS_C();
	void GET_GPOS_CfromGPOS_L();
	void SET_CRVAL();
	void SET_CRPIX();
	void SET_OAPIX();
	void SET_CCDs();
	void SHOW();
};
#endif
