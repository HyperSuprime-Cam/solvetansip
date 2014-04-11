//-----------------------------------------------------------
//REF.h
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef REF_H
#define REF_H

#include<vector>
#include<string>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include"hsc/meas/tansip/APRM.h"
#include"hsc/meas/tansip/CCD.h"
#include"hsc/meas/tansip/CPP.h"
#include"hsc/meas/tansip/CALC.h"

#define PI (4*atan(1.0))


class CL_REF{
private:
public:
	CL_APRM *APRM;
	CL_CCD  *CCD;
	CL_CCD  *GCD;
	double  *GPOS_L[4];
	int     *LENGTH_CCD[2];
	int	*ORDER_ASIP;
	int	*ORDER_PSIP;
	double	*CRVAL[2];
	double	*CRPIX_G[2];
	double	*CRPIX_L[2];
	double  *CD[2][2];
	double  *InvCD[2][2];
	double  *ASIP_DX[2];
	double  *ASIP_DY[2];
	double  *PSIP_DX[2];
	double  *PSIP_DY[2];

	long long int ID_OBJ;
	int	ID_CCD;
	int	FLAG_OBJ;
//POS_CELESTIC
	double	POS_CELESTIAL_RADEC[2];//degree
	double	POS_CELESTIAL_IMWLD[2];//degree
	double 	POS_CELESTIAL_IMPIX_L[2];
	double 	POS_CELESTIAL_IMPIX_G[2];
	double	POS_CELESTIAL_CRPIX_L[2];
	double 	POS_CELESTIAL_CRPIX_G[2];
	double 	POS_CELESTIAL_LOCAL_G[2];
	double	POS_CELESTIAL_LOCAL_L[2];
	double	POS_CELESTIAL_LOCAL_C[2];
	double	POS_CELESTIAL_PSIP_CRPIX_L[2];
	double 	POS_CELESTIAL_PSIP_CRPIX_G[2];
	double 	POS_CELESTIAL_PSIP_LOCAL_G[2];
	double	POS_CELESTIAL_PSIP_LOCAL_L[2];
	double	POS_CELESTIAL_PSIP_LOCAL_C[2];

//POS_DETECTED
	double	POS_DETECTED_LOCAL_L[2];
	double	POS_DETECTED_LOCAL_C[2];
	double	POS_DETECTED_LOCAL_G[2];
	double	POS_DETECTED_CRPIX_L[2];
	double 	POS_DETECTED_CRPIX_G[2];
	double	POS_DETECTED_IMPIX_L[2];
	double 	POS_DETECTED_IMPIX_G[2];
	double 	POS_DETECTED_IMWLD_L[2];
	double 	POS_DETECTED_IMWLD_G[2];
	double 	POS_DETECTED_RADEC_L[2];
	double 	POS_DETECTED_RADEC_G[2];
	double	POS_DETECTED_ASIP_CRPIX_L[2];
	double 	POS_DETECTED_ASIP_CRPIX_G[2];
	double	POS_DETECTED_ASIP_IMPIX_L[2];
	double 	POS_DETECTED_ASIP_IMPIX_G[2];
	double 	POS_DETECTED_ASIP_IMWLD_L[2];
	double 	POS_DETECTED_ASIP_IMWLD_G[2];
	double 	POS_DETECTED_ASIP_RADEC_L[2];
	double 	POS_DETECTED_ASIP_RADEC_G[2];
//DIFF
	double  DIFF_ASIP[2];
	double  DIFF_PSIP[2];
//DIST
	double	CAMERA_JACO;
	double	CAMERA_MAG;
	double	CAMERA_CONV;
	double	CAMERA_SHEAR[2];
	double	CAMERA_ROT;
	
//FUNCTIONS
	void SET_INIT(CL_CCD*  CCD,CL_CCD*  GCD);
//FUNCTIONS::POS
	void SET_POS_DETECTED_LOCAL_CfromLOCAL_L();
	void SET_POS_DETECTED_LOCAL_GfromLOCAL_L();
	void SET_POS_DETECTED_CRPIX_LfromLOCAL_L();
	void SET_POS_DETECTED_CRPIX_GfromLOCAL_G();
	void SET_POS_DETECTED_IMPIX_LfromCRPIX_L();
	void SET_POS_DETECTED_IMPIX_GfromCRPIX_G();
	void SET_POS_DETECTED_IMWLD_LfromIMPIX_L();
	void SET_POS_DETECTED_IMWLD_GfromIMPIX_G();
	void SET_POS_DETECTED_RADEC_LfromIMWLD_L();
	void SET_POS_DETECTED_RADEC_GfromIMWLD_G();
	void SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L();
	void SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();
	void SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L();
	void SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G();
	void SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L();
	void SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G();
	void SET_POS_CELESTIAL_IMWLDfromRADEC();
	void SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
	void SET_POS_CELESTIAL_IMPIX_LfromIMWLD();
	void SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G();
	void SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L();
	void SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G();
	void SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L();
	void SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD();
	void SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();
	void SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L();
	void SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G();
	void SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L();
	void SET_DIFF();
	void SET_OPTICAL_DISTORTIONbyPSIP();
};
class CL_REFs{
private:
public:
	CL_APRM *APRM;
	CL_CCDs *CCDs;
	CL_REF  *REF;
	string  *MODE_CR;
	int     *MODE_CCDPOS;
	int     *MODE_REJ;
	int	*ORDER_ASIP;
	int	*ORDER_PSIP;
	double	*CRVAL[2];
	double	*CRPIX[2];
	double  *OAPIX[2];
	int	*FLAG_STD;
	int     *NUM_CCD;
	int     *NUM_REF;
	int     *NUM_FIT;
	int     *NUM_REJ;
	double  *GPOS_C_BASIS[3];
	double  *SIGMA_CLIP;
	double  *PRECISION_CCD;
	double	*ASIP[2];
	double	*PSIP[2];
	double  *CD[2][2];
	double  *InvCD[2][2];
	double	*DIF_AVE_ASIP[2];
	double	*DIF_RMS_ASIP[2];
	double	*DIF_MAX_ASIP[2];
	double	*DIF_AVE_PSIP[2];
	double	*DIF_RMS_PSIP[2];
	double	*DIF_MAX_PSIP[2];
	double  *ASIP_DX[2];
	double  *ASIP_DY[2];
	double  *PSIP_DX[2];
	double  *PSIP_DY[2];
	double	*PSIP_CONV;
	double	*PSIP_ROT;
	double	*PSIP_SHEAR[2];
	double	*PSIP_MAG;
	double	*PSIP_JACO;
	double   MAX_LOCAL_G_R;
	double   MAX_LOCAL_G[2];
	double   MIN_LOCAL_G[2];
	double   AVE_LOCAL_G[2];
	double  *MAX_CRPIX_G_R;
	double  *MAX_CRPIX_G[2];
	double  *MIN_CRPIX_G[2];
	double  *AVE_CRPIX_G[2];
	
//FUNCTIONS
	void SET_INIT(CL_APRM *APRM,CL_CCDs* CCDs);
	void SET_INPUT(std::vector< std::vector< std::string > > REF_Argvs,CL_APRM* APRM,CL_CCDs* CCDs);
	void SET_NUM();
	void SET_END();
	int  CHECK();
	void SET_CCD(CL_CCDs*  CCDs);
//FUNCTIONS::POS
	void SET_POS_DETECTED_LOCAL_CfromLOCAL_L();
	void SET_POS_DETECTED_LOCAL_GfromLOCAL_L();
	void SET_POS_DETECTED_CRPIX_LfromLOCAL_L();
	void SET_POS_DETECTED_CRPIX_GfromLOCAL_G();
	void SET_POS_DETECTED_IMPIX_LfromCRPIX_L();
	void SET_POS_DETECTED_IMPIX_GfromCRPIX_G();
	void SET_POS_DETECTED_IMWLD_LfromIMPIX_L();
	void SET_POS_DETECTED_IMWLD_GfromIMPIX_G();
	void SET_POS_DETECTED_RADEC_LfromIMWLD_L();
	void SET_POS_DETECTED_RADEC_GfromIMWLD_G();
	void SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L();
	void SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();
	void SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L();
	void SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G();
	void SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L();
	void SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G();
	void SET_POS_DETECTED_ALL();
	void SET_POS_CELESTIAL_IMWLDfromRADEC();
	void SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
	void SET_POS_CELESTIAL_IMPIX_LfromIMWLD();
	void SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G();
	void SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L();
	void SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G();
	void SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L();
	void SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD();
	void SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();
	void SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L();
	void SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G();
	void SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L();
	void SET_POS_CELESTIAL_ALL();
	void SET_DIFF();
	void SET_OPTICAL_DISTORTIONbyPSIP();
	void SET_MAXMIN_LOCAL_G();
	void SET_MAXMIN_CRPIX_G();
	int  GET_ID_NEAR_CRVAL();
	int  GET_ID_NEAR_CRPIX();
//FUNCTIONS::FIT
	void FIT_CbyD(int ID_C,int ID_D);
	void FIT_DbyC(int ID_D,int ID_C);
	void CALC_STAT_ASIP();
	void CALC_STAT_PSIP();
	void CALC_STAT_SIP_LOCAL();
	void CALC_CRPIXatCRVAL();
	void CALC_CRVALatCRPIX();
	void CALC_CENTERPIXEL();
	void SET_CRPIXatCENTER();
//REJECTION
	void REJECT_BADREF();
	void REJECT_BADREF_ASIP();
	void REJECT_BADREF_PSIP();
//CCD POSITION
	void DETERMINE_CCDPOSITION();
	void SET_CCDAVE();
//TANSIP
	void DETERMINE_TANSIP();
	void CALC_TANSIP();
//DISTORTION
	void CALC_OPTICAL_DISTORTION();
	void DEVIATION_SIP(int ORDER,double *Coef,double *dxCoef,double *dyCoef);
	void FIT_DIST();
	void CALC_OPTICAL_AXIS();
	
	void SHOW();

};
#endif
