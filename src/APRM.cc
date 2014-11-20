//-----------------------------------------------------------
//APRM.cc
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include"hsc/meas/tansip/APRM.h"

namespace hsc { namespace meas {
namespace tansip {

AnaParam::AnaParam()
	: INSTR         ( "HSC" )
	, MODE_CR       ( "PIX" )

	, MODE_CCDPOS   ( false )
	, PRECISION_CCD ( 0.1   )

	, ORDER_ASIP    ( 0     )
	, ORDER_PSIP    ( 0     )
	, MODE_REJ      ( false )
	, SIGMA_CLIP    ( 10.0  )

	, VERBOSITY     ( 1     )
{
	CRPIX[0]   = 0.0;
	CRPIX[1]   = 0.0;
	CRVAL[0]   = 0.0;
	CRVAL[1]   = 0.0;
}


bool  AnaParam::CHECK(){
	return CHECK_MODECR   ()
		&& CHECK_ORDERASIP()
		&& CHECK_ORDERPSIP()
	;
}


bool  AnaParam::CHECK_MODECR(){
	if(MODE_CR=="PIX"||MODE_CR=="VAL"||MODE_CR=="AUTO"){
		if(VERBOSITY >= 2) std::cout << "OK : MODE_CR   : " << MODE_CR << std::endl;
		return true;
	}else{
		std::cout << "---------------------------------------------" << std::endl;
		std::cout <<	"Input 'MODE_CR' is '" << MODE_CR << "'"<< std::endl;
		std::cout << "Warning : MODE_CR must be 'AUTO' or 'VAL' or 'PIX'" << std::endl;
		MODE_CR="AUTO";
		std::cout << "Warning : SET MODE_CR to " << MODE_CR << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
		// return true in any case
		return true;
	}
}


bool  AnaParam::CHECK_ORDERASIP(){
	if(ORDER_ASIP >=1 && ORDER_ASIP <= 9){
		if(VERBOSITY >= 2) std::cout << "OK : ORDER_ASIP : " << ORDER_ASIP << std::endl;
		return true;
	}else{
		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "Input 'ORDER_ASIP' is '" << ORDER_ASIP << "'"<< std::endl;
		std::cout << "Warning : ORDER_ASIP must be between 0 and 9" << std::endl;
		ORDER_ASIP=9;
		std::cout << "Warning : SET ORDER_ASIP to " << ORDER_ASIP << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
		// return true in any case
		return true;
	}
}
bool  AnaParam::CHECK_ORDERPSIP(){
	if(ORDER_PSIP >= 1 && ORDER_PSIP <= 9){
		if(VERBOSITY >= 2) std::cout << "OK : ORDER_PSIP : " << ORDER_PSIP << std::endl;
		return true;
	}else{
		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "Input 'ORDER_PSIP' is '" << ORDER_PSIP << "'"<< std::endl;
		std::cout << "Warning : ORDER_PSIP must be between 0 and 9" << std::endl;
		ORDER_PSIP=9;
		std::cout << "Warning : SET ORDER_PSIP to " << ORDER_PSIP << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
		// return true in any case
		return true;
	}
}
void AnaParam::SHOW(){
	std::cout << "-- SHOW APROP --"               << std::endl;
	std::cout << "INSTRUMENT  : " << INSTR        << std::endl;
	std::cout << "MODE_CR     : " << MODE_CR      << std::endl;
	std::cout << "MODE_CCDPOS : " << MODE_CCDPOS  << std::endl;
	std::cout << "MODE_REJ    : " << MODE_REJ     << std::endl;
	std::cout << "CRPIX1      : " << CRPIX[0]     << std::endl;
	std::cout << "CRPIX2      : " << CRPIX[1]     << std::endl;
	std::cout << "CRVAL1      : " << CRVAL[0]     << std::endl;
	std::cout << "CRVAL2      : " << CRVAL[1]     << std::endl;
	std::cout << "SIPORDER    : " << ORDER_ASIP   << std::endl;
	std::cout << "SIPPORDER   : " << ORDER_PSIP   << std::endl;
	std::cout << "CRIP_SIGMA  : " << SIGMA_CLIP   << std::endl;
	std::cout << "PRECISIONPOS: " << PRECISION_CCD<< std::endl;
	std::cout << "STDOUT      : " << VERBOSITY     << std::endl;
	std::cout << std::endl;
}


} // namespace tansip
}} // namespace hsc::meas
