//-----------------------------------------------------------
//APRM.cc
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include"hsc/meas/tansip/APRM.h"

namespace hsc { namespace meas {
namespace tansip {

void CL_APRM::SET_INIT(){
	INSTR         = "HSC";
	MODE_CR       = "PIX";
	NUM_CCD       = 0;
	MODE_CCDPOS   = 0;
	NUM_REF       = 0;
	NUM_FIT       = 0;
	NUM_REJ       = 0;
	CRPIX[0]      = 0.0;
	CRPIX[1]      = 0.0;
	CRVAL[0]      = 0.0;
	CRVAL[1]      = 0.0;
	ORDER_ASIP    = 0;
	ORDER_PSIP    = 0;
	MODE_REJ      = 0;
	SIGMA_CLIP    = 10.0;
	PRECISION_CCD = 0.1;
	FLAG_STD      = 1;
}
void CL_APRM::SET_INPUT(std::vector< std::vector< std::string > > APRM_Argvs){
	SET_INIT();
	for(std::size_t i = 0; i < APRM_Argvs.size(); ++i){
		std::string const& KEY=APRM_Argvs[i][0];
		std::string const& VAL=APRM_Argvs[i][1];
		if(KEY=="INSTR")
		INSTR         = VAL;
		if(KEY=="MODE_CR")
		MODE_CR       = VAL;
		if(KEY=="MODE_CCDPOS")
		MODE_CCDPOS   = atoi(VAL.c_str());
		if(KEY=="ORDER_ASIP")
		ORDER_ASIP    = atoi(VAL.c_str());
		if(KEY=="ORDER_PSIP")
		ORDER_PSIP    = atoi(VAL.c_str());
		if(KEY=="MODE_REJ")
		MODE_REJ      = atoi(VAL.c_str());
		if(KEY=="PRECISION_POS")
		PRECISION_CCD = atof(VAL.c_str());
		if(KEY=="CLIPSIGMA")
		SIGMA_CLIP    = atof(VAL.c_str());
		if(KEY=="CRPIX1")
		CRPIX[0]      = atof(VAL.c_str());
		if(KEY=="CRPIX2")
		CRPIX[1]      = atof(VAL.c_str());
		if(KEY=="CRVAL1")
		CRVAL[0]      = atof(VAL.c_str());
		if(KEY=="CRVAL2")
		CRVAL[1]      = atof(VAL.c_str());
		if(KEY=="FLAG_STD")
		FLAG_STD      = atoi(VAL.c_str());
		if(KEY=="NUM_CCD")
		NUM_CCD       = atoi(VAL.c_str());
		if(KEY=="NUM_REF")
		NUM_REF       = atoi(VAL.c_str());
		NUM_FIT       = NUM_REF;
	}
	if(FLAG_STD >= 1) std::cout <<"-- SET APRM --"<< std::endl;

}
bool  CL_APRM::CHECK(){
	return CHECK_MODECR   ()
		&& CHECK_ORDERASIP()
		&& CHECK_ORDERPSIP()
	;
}
bool  CL_APRM::CHECK_MODECR(){
	if(MODE_CR=="PIX"||MODE_CR=="VAL"||MODE_CR=="AUTO"){
		if(FLAG_STD >= 2) std::cout << "OK : MODE_CR   : " << MODE_CR << std::endl;
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
bool  CL_APRM::CHECK_ORDERASIP(){
	if(ORDER_ASIP >=1 && ORDER_ASIP <= 9){
		if(FLAG_STD >= 2) std::cout << "OK : ORDER_ASIP : " << ORDER_ASIP << std::endl;
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
bool  CL_APRM::CHECK_ORDERPSIP(){
	if(ORDER_PSIP >= 1 && ORDER_PSIP <= 9){
		if(FLAG_STD >= 2) std::cout << "OK : ORDER_PSIP : " << ORDER_PSIP << std::endl;
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
void CL_APRM::SHOW(){
	std::cout << "-- SHOW APROP --"               << std::endl;
	std::cout << "INSTRUMENT  : " << INSTR        << std::endl;
	std::cout << "MODE_CR     : " << MODE_CR      << std::endl;
	std::cout << "MODE_CCDPOS : " << MODE_CCDPOS  << std::endl;
	std::cout << "MODE_REJ    : " << MODE_REJ     << std::endl;
	std::cout << "NUM_CCD     : " << NUM_CCD      << std::endl;
	std::cout << "NUM_REF     : " << NUM_REF      << std::endl;
	std::cout << "NUM_FIT     : " << NUM_FIT      << std::endl;
	std::cout << "CRPIX1      : " << CRPIX[0]     << std::endl;
	std::cout << "CRPIX2      : " << CRPIX[1]     << std::endl;
	std::cout << "CRVAL1      : " << CRVAL[0]     << std::endl;
	std::cout << "CRVAL2      : " << CRVAL[1]     << std::endl;
	std::cout << "SIPORDER    : " << ORDER_ASIP   << std::endl;
	std::cout << "SIPPORDER   : " << ORDER_PSIP   << std::endl;
	std::cout << "CRIP_SIGMA  : " << SIGMA_CLIP   << std::endl;
	std::cout << "PRECISIONPOS: " << PRECISION_CCD<< std::endl;
	std::cout << "STDOUT      : " << FLAG_STD     << std::endl;
	std::cout << std::endl;
}
void CL_APRM::SET_END(){

}

} // namespace tansip
}} // namespace hsc::meas
