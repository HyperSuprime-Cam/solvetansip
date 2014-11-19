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

struct CL_APRM
{
	std::string  INSTR;//HSC or SC
	std::string	 MODE_CR;
//CCD
	int	MODE_CCDPOS;
	double  PRECISION_CCD;//pixel
//REF
	double	CRPIX_IN[2];
	double	CRVAL_IN[2];
	int	ORDER_ASIP;
	int	ORDER_PSIP;
	int	MODE_REJ;
	double	SIGMA_CLIP;

//OUTPUT
	int	FLAG_STD;

//FUNCTIONs
	CL_APRM();

	void SET_INPUT(std::vector< std::vector< std::string > > APRM_Argvs);//setting input values
	void SHOW();//showing curret values
	bool CHECK();//checking current values
	bool CHECK_MODECR();//checking current MODECR
	bool CHECK_ORDERASIP();//checking current SIP oreder
	bool CHECK_ORDERPSIP();//checking current PSIP order
};

} // namespace tansip
}} // namespace hsc::meas
#endif //gd3b2467b_f431_4fa4_94cb_a1f35bb9e186
