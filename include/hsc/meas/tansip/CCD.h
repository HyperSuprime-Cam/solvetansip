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
	CL_APRM *APRM;//=SLVTS->APRM
	int	 ID;
	int	 NUM_REF;
	int	 NUM_FIT;
	int	 NUM_REJ;
	double	 GPOS_C[4];//pixel,pixel,radian,degree
	double	 GPOS_L[4];//pixel,pixel,radian,degree
	int      LENGTH[2];
	double   ANGLE;
	double	*CRVAL[2];//=APRM->CRVAL
	double	*CRPIX[2];//=APRM->CRPIX
	double	 OAPIX[2];
	double	 CD[2][2];
	double	 InvCD[2][2];
	int	*ORDER_ASIP;//=APRM->ORDER_ASIP
	int	*ORDER_PSIP;//=APRM->ORDER_PSIP
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

	void SET_INIT();//setting initial values
	void SET_END();//destructor
	void GET_GPOS_LfromGPOS_C();//setting lower left corner position from center position in global coordinate
	void GET_GPOS_CfromGPOS_L();//setting center position from lower left corner position in global coordinate
	void SET_CDASIP();//divide fitting coefficients into CD matrix and others and setting SIP coefficients
	void SET_CDPSIP();//setting PSF coefficients
	void SET_SIPROT(int ORDER,double *COEF_IN, double *COEF);//calculating SIP and PSIP coefficients with effect due to CCD rotation
	void SHOW();//showing CCD infomation
};
class CL_CCDs{
private:
public:
	CL_APRM *APRM;//=SLVTS->APRM
	CL_CCD  *CCD;
	int     *MODE_CCDPOS;//=APRM->MODE_CCDPOS
	int     *NUM_CCD;
	double	 GPOS_C_BASIS[4];//pixel,pixel,radian,degree
	int	*ORDER_ASIP;
	int	*ORDER_PSIP;
	double	*CRVAL[2];
	double	*CRPIX[2];
	int	*FLAG_STD;//=APRM->FLAG_STD
	double   MAX_CRPIX_G_R;
	double   MAX_CRPIX_G[2];
	double   MIN_CRPIX_G[2];
	double   AVE_CRPIX_G[2];

	
	void SET_INIT(CL_APRM *APRM);//setting initial values
	void SET_INPUT(std::vector< std::vector< std::string > > CCD_Argvs,CL_APRM *APRM);//setting input values
	void SET_END();//destructor
	int  CHECK();//checking current values
	int  CHECK_NUMCCD();//checking number of CCDs
	int  CHECK_NUMFIT();//checking current number for fitting of each CCDs
	int  CHECK_NUMFITALL();//checking current number for fitting of all CCDs
	void GET_GPOS_LfromGPOS_C();//setting lower left corner position from center position in global coordinate for all CCDs
	void GET_GPOS_CfromGPOS_L();//setting center position from lower left corner position in global coordinate for all CCDs
	void SET_CRVAL();//setting CRVAL for all CCDs
	void SET_CRPIX();//setting CRPIX for all CCDs
	void SET_OAPIX();//setting OAXPI for all CCDs
	void SET_CCDs();//setting solvtansip information of local CCDs from global information
	void SHOW();//showing CCDs infomation
};
#endif
