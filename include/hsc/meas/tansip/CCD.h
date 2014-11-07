//-----------------------------------------------------------
//CCD.h
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef  gfe76caaa_f951_46d7_ae0f_d78e88e8cbe1
#define  gfe76caaa_f951_46d7_ae0f_d78e88e8cbe1

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

#include <ndarray.h>

#include "hsc/meas/tansip/APRM.h"
#include "hsc/meas/tansip/Polynomial.h"

namespace hsc { namespace meas {
namespace tansip {

class CL_CCD{
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
	double	*CRPIX[2];//=APRM->CRVAL if this is the last element in CL_CCDs or is unique.
	double	 OAPIX[2];
	double	 CD[2][2];
	double	 InvCD[2][2];
	Polynomial2D  ASIP[2];
	Polynomial2D  PSIP[2];
	Polynomial2D  PSIP_CONV;
	Polynomial2D  PSIP_ROT;
	Polynomial2D  PSIP_SHEAR[2];
	Polynomial2D  PSIP_MAG;
	Polynomial2D  PSIP_JACO;
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
	Polynomial2D SET_SIPROT(Polynomial2D const& POLY);//calculating SIP and PSIP coefficients with effect due to CCD rotation
	void SHOW();//showing CCD infomation

	bool areReferencesSufficient() const {
		return this->NUM_FIT >= 3;
	}
};
class CL_CCDs{
private:
public:
	CL_APRM *APRM;//=SLVTS->APRM
	std::vector<CL_CCD>  CCD;
	double	 GPOS_C_BASIS[4];//pixel,pixel,radian,degree
	double   MAX_CRPIX_G_R;
	double   MAX_CRPIX_G[2];
	double   MIN_CRPIX_G[2];
	double   AVE_CRPIX_G[2];

	ndarray::Array<double, 1, 1> HOLDER_OF_CRPIX_OF_CCDS;

	void SET_INIT(CL_APRM *APRM);//setting initial values
	void SET_INPUT(std::vector< std::vector< std::string > > CCD_Argvs,CL_APRM *APRM);//setting input values
	void SET_END();//destructor
	bool CHECK();//checking current values
	bool CHECK_NUMCCD();//checking number of CCDs
	bool CHECK_NUMFIT();//checking current number for fitting of each CCDs
	bool CHECK_NUMFITALL();//checking current number for fitting of all CCDs
	void GET_GPOS_LfromGPOS_C();//setting lower left corner position from center position in global coordinate for all CCDs
	void GET_GPOS_CfromGPOS_L();//setting center position from lower left corner position in global coordinate for all CCDs
	void SET_CRPIX();//setting CRPIX for all CCDs
	void SET_OAPIX();//setting OAXPI for all CCDs
	void SET_CCDs();//setting solvtansip information of local CCDs from global information
	void SHOW();//showing CCDs infomation
};

} // namespace tansip
}} // namespace hsc::meas
#endif //gfe76caaa_f951_46d7_ae0f_d78e88e8cbe1
