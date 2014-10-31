//-----------------------------------------------------------
//APRM.h
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef  gd3b2467b_f431_4fa4_94cb_a1f35bb9e186
#define  gd3b2467b_f431_4fa4_94cb_a1f35bb9e186

#include<vector>
#include<string>
#include<iostream>
#include<stdlib.h>

namespace hsc { namespace meas {
namespace tansip {

class CL_APRM{
private:
public:
	std::string  INSTR;//HSC or SC
	std::string	 MODE_CR;
//CCD
	int	NUM_CCD;
	int	MODE_CCDPOS;
	double  PRECISION_CCD;//pixel
//REF
	int	NUM_REF;
	int	NUM_FIT;
	int	NUM_REJ;
	double	CRPIX[2];
	double	CRVAL[2];
	int	ORDER_ASIP;
	int	ORDER_PSIP;
	int	MODE_REJ;
	double	SIGMA_CLIP;

//OUTPUT
	int	FLAG_STD;

//FUNCTIONs
	void SET_INIT();//setting initial values
	void SET_INPUT(std::vector< std::vector< std::string > > APRM_Argvs);//setting input values
	void SHOW();//showing curret values
	int  CHECK();//checking current values
	int  CHECK_MODECR();//checking current MODECR
	int  CHECK_ORDERASIP();//checking current SIP oreder
	int  CHECK_ORDERPSIP();//checking current PSIP order
	void SET_END();//destructor
};

} // namespace tansip
}} // namespace hsc::meas
#endif //gd3b2467b_f431_4fa4_94cb_a1f35bb9e186
