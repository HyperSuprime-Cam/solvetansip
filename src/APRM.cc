//-----------------------------------------------------------
//APRM.cc
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include"hsc/meas/tansip/APRM.h"

using namespace std;
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
	FLAG_OUT      = 2;
	DIR_OUT       = "./";

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
		if(KEY=="FLAG_OUT")
		FLAG_OUT      = atoi(VAL.c_str());
		if(KEY=="DIR_OUT")
		DIR_OUT       = VAL;
		if(KEY=="NUM_CCD")
		NUM_CCD       = atoi(VAL.c_str());
		if(KEY=="NUM_REF")
		NUM_REF       = atoi(VAL.c_str());
		NUM_FIT       = NUM_REF;
	}
	if(FLAG_STD>0.5)cout<<"-- SET APRM --"<<endl;

}
int  CL_APRM::CHECK(){
	if(CHECK_MODECR()==1)return 1;
	if(CHECK_ORDERASIP()==1)return 1;
	if(CHECK_ORDERPSIP()==1)return 1;
	return 0;
}
int  CL_APRM::CHECK_MODECR(){
	if(MODE_CR=="PIX"||MODE_CR=="VAL"||MODE_CR=="AUTO"){
		if(FLAG_STD>1.5)cout << "OK : MODE_CR   : " << MODE_CR << endl;
		return 0;
	}else{
		cout << "---------------------------------------------" << endl;
		cout <<	"Input 'MODE_CR' is '" << MODE_CR << "'"<< endl;
		cout << "Warning : MODE_CR must be 'AUTO' or 'VAL' or 'PIX'" << endl;
		MODE_CR="AUTO";
		cout << "Warning : SET MODE_CR to " << MODE_CR << endl;
		cout << "---------------------------------------------" << endl;
		return 0;
	}
}
int  CL_APRM::CHECK_ORDERASIP(){
	if(ORDER_ASIP>0.5&&ORDER_ASIP<9.5){
		if(FLAG_STD>1.5)cout << "OK : ORDER_ASIP : " << ORDER_ASIP << endl;
		return 0;
	}else{
		cout << "---------------------------------------------" << endl;
		cout << "Input 'ORDER_ASIP' is '" << ORDER_ASIP << "'"<< endl;
		cout << "Warning : ORDER_ASIP must be between 0 and 9" << endl;
		ORDER_ASIP=9;
		cout << "Warning : SET ORDER_ASIP to " << ORDER_ASIP << endl;
		cout << "---------------------------------------------" << endl;
		return 0;
	}
}
int  CL_APRM::CHECK_ORDERPSIP(){
	if(ORDER_PSIP>0.5&&ORDER_PSIP<9.5){
		if(FLAG_STD>1.5)cout << "OK : ORDER_PSIP : " << ORDER_PSIP << endl;
		return 0;
	}else{
		cout << "---------------------------------------------" << endl;
		cout << "Input 'ORDER_PSIP' is '" << ORDER_PSIP << "'"<< endl;
		cout << "Warning : ORDER_PSIP must be between 0 and 9" << endl;
		ORDER_PSIP=9;
		cout << "Warning : SET ORDER_PSIP to " << ORDER_PSIP << endl;
		cout << "---------------------------------------------" << endl;
		return 0;
	}
}
void CL_APRM::SHOW(){
	cout << "-- SHOW APROP --" << endl;
	cout << "INSTRUMENT  : " << INSTR        << endl;
	cout << "MODE_CR     : " << MODE_CR      << endl;
	cout << "MODE_CCDPOS : " << MODE_CCDPOS  << endl;
	cout << "MODE_REJ    : " << MODE_REJ     << endl;
	cout << "NUM_CCD     : " << NUM_CCD      << endl;
	cout << "NUM_REF     : " << NUM_REF      << endl;
	cout << "NUM_FIT     : " << NUM_FIT      << endl;
	cout << "CRPIX1      : " << CRPIX[0]     << endl;
	cout << "CRPIX2      : " << CRPIX[1]     << endl;
	cout << "CRVAL1      : " << CRVAL[0]     << endl;
	cout << "CRVAL2      : " << CRVAL[1]     << endl;
	cout << "SIPORDER    : " << ORDER_ASIP   << endl;
	cout << "SIPPORDER   : " << ORDER_PSIP   << endl;
	cout << "CRIP_SIGMA  : " << SIGMA_CLIP   << endl;
	cout << "PRECISIONPOS: " << PRECISION_CCD<< endl;
	cout << "STDOUT      : " << FLAG_STD     << endl;
	cout << "OUTFLAG     : " << FLAG_OUT     << endl;
	cout << "OUTDIR      : " << DIR_OUT      << endl;
	cout <<endl;
}
void CL_APRM::SET_END(){

}
