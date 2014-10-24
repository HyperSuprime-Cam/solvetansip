//-----------------------------------------------------------
//REF.h
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef REF_H
#define REF_H

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include <ndarray.h>

#include "hsc/meas/tansip/APRM.h"
#include "hsc/meas/tansip/CCD.h"
#include "hsc/meas/tansip/CALC.h"


class CL_REF{
private:
public:
	CL_APRM *APRM;//=SLVTS->APRM
	CL_CCD  *CCD;//=SLVTS->CCDs->CCD[ID_CCD]
	CL_CCD  *GCD;//=SLVTS->CCDs->CCD[NUMCCD]
	double  *GPOS_L[4];//=CCD->GPOS_L
	int     *LENGTH_CCD[2];//=CCD->LENGTH
	double	*CRPIX_L[2];//=CCD->CRPIX
	double  *CD[2][2];//=GCD->CD
	double  *InvCD[2][2];//=GCD->InvCD
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
	void SET_INIT(CL_CCD*  CCD,CL_CCD*  GCD);//setting initial values
//FUNCTIONS::POS
	void SET_POS_DETECTED_LOCAL_CfromLOCAL_L();//setting detected position of LOCAL_C from LOCAL_L
	void SET_POS_DETECTED_LOCAL_GfromLOCAL_L();//setting detected position of LOCAL_G from LOCAL_L
	void SET_POS_DETECTED_CRPIX_LfromLOCAL_L();//setting detected position of CRPIX_L from LOCAL_L
	void SET_POS_DETECTED_CRPIX_GfromLOCAL_G();//setting detected position of CRPIX_G from LOCAL_G
	void SET_POS_DETECTED_IMPIX_LfromCRPIX_L();//setting detected position of IMPIX_L from CRPIX_L
	void SET_POS_DETECTED_IMPIX_GfromCRPIX_G();//setting detected position of IMPIX_G from CRPIX_G
	void SET_POS_DETECTED_IMWLD_LfromIMPIX_L();//setting detected position of IMWLD_L from IMPIX_L
	void SET_POS_DETECTED_IMWLD_GfromIMPIX_G();//setting detected position of IMWLD_G from IMPIX_G
	void SET_POS_DETECTED_RADEC_LfromIMWLD_L();//setting detected position of RADEC_L from IMWLD_L
	void SET_POS_DETECTED_RADEC_GfromIMWLD_G();//setting detected position of RADEC_G from IMWLD_G
	void SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L();//setting detected position of IMPIX_L from CRPIX_L with SIP
	void SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();//setting detected position of IMPIX_G from CRPIX_G with SIP
	void SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L();//setting detected position of IMWLD_L from IMPIX_L with SIP
	void SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G();//setting detected position of IMWLD_G from IMPIX_G with SIP
	void SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L();//setting detected position of RADEC_L from IMWLD_L with SIP
	void SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G();//setting detected position of RADEC_G from IMWLD_G with SIP
	void SET_POS_CELESTIAL_IMWLDfromRADEC();//setting celestial position of IMWLD from RADEC
	void SET_POS_CELESTIAL_IMPIX_GfromIMWLD();//setting celestial position of IMPIX_G from IMWLD
	void SET_POS_CELESTIAL_IMPIX_LfromIMWLD();//setting celestial position of IMPIX_L from IMWLD
	void SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G();//setting celestial position of CRPIX_G from IMPIX_G
	void SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L();//setting celestial position of CRPIX_L from IMPIX_L
	void SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G();//setting celestial position of LOCAL_G from CRPIX_G
	void SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L();//setting celestial position of LOCAL_L from CRPIX_L
	void SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD();//setting celestial position of LOCAL_G from IMWLD with PSIP
	void SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();//setting celestial position of CRPIX_G from IMPIX_G with PSIP
	void SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L();//setting celestial position of CRPIX_L from IMPIX_L with PSIP
	void SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G();//setting celestial position of LOCAL_G from CRPIX_G with PSIP
	void SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L();//setting celestial position of LOCAL_L from CRPIX_L with PSIP
	void SET_DIFF();//calculating differences from SIP and PSIP fitting
	void SET_OPTICAL_DISTORTIONbyPSIP();//calculating distortion from PSIP
};
class CL_REFs{
private:
public:
	CL_APRM *APRM;//SLVTS->APRM
	CL_CCDs *CCDs;//SLVTS->CCDs
	std::vector<CL_REF>  REF;
	double  *OAPIX[2];//CCDs->CCD[NUM_CCD]->OAPIX
	double  *GPOS_C_BASIS[3];//CCDs->GPOS_C_BASIS
	ndarray::Array<double, 1, 1> ASIP[2];//CCDs->ASIP
	ndarray::Array<double, 1, 1> PSIP[2];//CCDs->PSIP
	double  *CD[2][2];//CCDs->CD
	double  *InvCD[2][2];//CCDs->InvCD
	double	*DIF_AVE_ASIP[2];//CCDs->DIF_AVE_ASIP
	double	*DIF_RMS_ASIP[2];//CCDs->DIF_RMS_ASIP
	double	*DIF_MAX_ASIP[2];//CCDs->DIF_MAX_ASIP
	double	*DIF_AVE_PSIP[2];//CCDs->DIF_AVE_PSIP
	double	*DIF_RMS_PSIP[2];//CCDs->DIF_RMS_PSIP
	double	*DIF_MAX_PSIP[2];//CCDs->DIF_MAX_PSIP
	ndarray::Array<double, 1, 1> ASIP_DX[2];
	ndarray::Array<double, 1, 1> ASIP_DY[2];
	ndarray::Array<double, 1, 1> PSIP_DX[2];
	ndarray::Array<double, 1, 1> PSIP_DY[2];
	ndarray::Array<double, 1, 1> PSIP_CONV;    //CCDs->PSIP_CONV
	ndarray::Array<double, 1, 1> PSIP_ROT;     //CCDs->PSIP_ROT
	ndarray::Array<double, 1, 1> PSIP_SHEAR[2];//CCDs->PSIP_SHEAR
	ndarray::Array<double, 1, 1> PSIP_MAG;     //CCDs->PSIP_MAG
	ndarray::Array<double, 1, 1> PSIP_JACO;    //CCDs->PSIP_JACO
	double   MAX_LOCAL_G_R;
	double   MAX_LOCAL_G[2];
	double   MIN_LOCAL_G[2];
	double   AVE_LOCAL_G[2];
	double  *MAX_CRPIX_G_R;//CCDs->MAX_CRPIX_G_R
	double  *MAX_CRPIX_G[2];//CCDs->MAX_CRPIX_G
	double  *MIN_CRPIX_G[2];//CCDs->MIN_CRPIX_G
	double  *AVE_CRPIX_G[2];//CCDs->AVE_CRPIX_G

//FUNCTIONS
	void SET_INIT(CL_APRM *APRM,CL_CCDs* CCDs);//setting inital values
	void SET_INPUT(std::vector< std::vector< std::string > > REF_Argvs,CL_APRM* APRM,CL_CCDs* CCDs);//setting input values
	void SET_NUM();//setting NUM_REF, NUM_FIT, NUM_REJ
	void SET_END();//destructor
	int  CHECK();//checking current values
	void SET_CCD(CL_CCDs*  CCDs);//setting initial values of all CCDs
//FUNCTIONS::POS

	void SET_POS_DETECTED_LOCAL_CfromLOCAL_L();//setting detected position of LOCAL_C from LOCAL_L for all references
	void SET_POS_DETECTED_LOCAL_GfromLOCAL_L();//setting detected position of LOCAL_G from LOCAL_L for all references
	void SET_POS_DETECTED_CRPIX_LfromLOCAL_L();//setting detected position of CRPIX_L from LOCAL_L for all references
	void SET_POS_DETECTED_CRPIX_GfromLOCAL_G();//setting detected position of CRPIX_G from LOCAL_G for all references
	void SET_POS_DETECTED_IMPIX_LfromCRPIX_L();//setting detected position of IMPIX_L from CRPIX_L for all references
	void SET_POS_DETECTED_IMPIX_GfromCRPIX_G();//setting detected position of IMPIX_G from CRPIX_G for all references
	void SET_POS_DETECTED_IMWLD_LfromIMPIX_L();//setting detected position of IMWLD_L from IMPIX_L for all references
	void SET_POS_DETECTED_IMWLD_GfromIMPIX_G();//setting detected position of IMWLD_G from IMPIX_G for all references
	void SET_POS_DETECTED_RADEC_LfromIMWLD_L();//setting detected position of RADEC_L from IMWLD_L for all references
	void SET_POS_DETECTED_RADEC_GfromIMWLD_G();//setting detected position of RADEC_G from IMWLD_G for all references
	void SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L();//setting detected position of IMPIX_L from CRPIX_L with SIP for all references
	void SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();//setting detected position of IMPIX_G from CRPIX_G with SIP for all references
	void SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L();//setting detected position of IMWLD_L from IMPIX_L with SIP for all references
	void SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G();//setting detected position of IMWLD_G from IMPIX_G with SIP for all references
	void SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L();//setting detected position of RADEC_L from IMWLD_L with SIP for all references
	void SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G();//setting detected position of RADEC_G from IMWLD_G with SIP for all references
	void SET_POS_DETECTED_ALL();//setting all detected positions for all references
	void SET_POS_CELESTIAL_IMWLDfromRADEC();//setting celestial position of IMWLD from RADEC for all references
	void SET_POS_CELESTIAL_IMPIX_GfromIMWLD();//setting celestial position of IMPIX_G from IMWLD for all references
	void SET_POS_CELESTIAL_IMPIX_LfromIMWLD();//setting celestial position of IMPIX_L from IMWLD for all references
	void SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G();//setting celestial position of CRPIX_G from IMPIX_G for all references
	void SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L();//setting celestial position of CRPIX_L from IMPIX_L for all references
	void SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G();//setting celestial position of LOCAL_G from CRPIX_G for all references
	void SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L();//setting celestial position of LOCAL_L from CRPIX_L for all references
	void SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD();//setting celestial position of LOCAL_G from IMWLD with PSIP for all references
	void SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();//setting celestial position of CRPIX_G from IMPIX_G with PSIP for all references
	void SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L();//setting celestial position of CRPIX_L from IMPIX_L with PSIP for all references
	void SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G();//setting celestial position of LOCAL_G from CRPIX_G with PSIP for all references
	void SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L();//setting celestial position of LOCAL_L from CRPIX_L with PSIP for all references
	void SET_POS_CELESTIAL_ALL();//setting all celestial positions for all references
	void SET_DIFF();//calculating differences from SIP and PSIP fitting for all references
	void SET_OPTICAL_DISTORTIONbyPSIP();//calculating distortion from PSIP all references
	void SET_MAXMIN_LOCAL_G();//setting maximun position in global coordinate
	void SET_MAXMIN_CRPIX_G();//setting maximun position in global CRPIX coordinate
	int  GET_ID_NEAR_CRVAL();//getting ID of reference which is nearest to CRVAL
	int  GET_ID_NEAR_CRPIX();//getting ID of reference which is nearest to CRPIX
//FUNCTIONS::FIT
	void FIT_CbyD(int ID_C,int ID_D);//fitting Celestial position by Detected position and getting coefficients of polynomial fitting. coordinates are assined by ID_C and ID_D
	void FIT_DbyC(int ID_D,int ID_C);//fitting Detected position by Celestial position and getting coefficients of polynomial fitting. coordinates are assined by ID_C and ID_D
	void CALC_STAT_ASIP();//getting statistics of SIP fitting for global fitting
	void CALC_STAT_PSIP();//getting statistics of PSIP fitting for global fitting
	void CALC_STAT_SIP_LOCAL();//getting statistics of SIP and PSIP fitting for each CCD fitting
	void CALC_CRPIXatCRVAL();//calculating CRPIX as CRVAL
	void CALC_CRVALatCRPIX();//calculating CRVAL as CRPIX
	void CALC_CENTERPIXEL();//calculating average position of references
	void SET_CRPIXatCENTER();//setting average position as CRPIX
//REJECTION
	void REJECT_BADREF();//rejecting references which have position far from fitting position
	void REJECT_BADREF_ASIP();//rejecting references which have position far from  SIP fitting position
	void REJECT_BADREF_PSIP();//rejecting references which have position far from PSIP fitting position
//CCD POSITION
	void DETERMINE_CCDPOSITION();//determining CCD positions
	void SET_CCDAVE();//shifting CCD positions to fit CCDBASIS
//TANSIP
	void DETERMINE_TANSIP();//determining SIP, Distortion, statistics of fitting and references positions
	void CALC_TANSIP();//calculating CD, SIP and PSIP coefficients
//DISTORTION
	void CALC_OPTICAL_DISTORTION();//CALC Distortion from PSIP
	void DEVIATION_SIP(int ORDER,double *Coef,double *dxCoef,double *dyCoef);//calculating deviation of SIP and PSIP
	void FIT_DIST();//fitting optical distortion
	void CALC_OPTICAL_AXIS();//caluclationg optical axis

	void SHOW();//show information of references

};
#endif
