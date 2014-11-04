//-----------------------------------------------------------
//SLVTS.cc
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <boost/make_shared.hpp>
#include "hsc/meas/tansip/SLVTS.h"
#include "HIRES_CLOCK.h"

namespace hsc { namespace meas {
namespace tansip {

boost::shared_ptr<CL_SLVTS> SOLVETANSIP(std::vector< std::vector< std::vector<std::string> > > SLVTS_Argvs){
	my::clock_t TS,TE;
	my::clock_t T1,T2;
	TS=my::clock();
	boost::shared_ptr<CL_SLVTS> SLVTS = boost::make_shared<CL_SLVTS>();

	T1=my::clock();
	SLVTS->SET_INIT();
	SLVTS->SET_INPUT(SLVTS_Argvs);
	if(!SLVTS->CHECK_INPUT()){
		std::cout << "Error : in checking Input Values" << std::endl;
		return boost::shared_ptr<CL_SLVTS>();
	}
	T2=my::clock();
	if(SLVTS->APRM->FLAG_STD >= 1) std::cout << "TIME SET INPUT         : "<<(T2-T1) << " (sec)" << std::endl;

	SLVTS->CALC_WCS();

//	SLVTS->END()

	TE=my::clock();
	if(SLVTS->APRM->FLAG_STD >= 1) std::cout << "TIME SOLVETANSIP TOTAL : "<<(TE-TS) << " (sec)" << std::endl;

	return SLVTS;
}
void CL_SLVTS::SET_END(){
	APRM->SET_END();
	CCDs->SET_END();
	REFs->SET_END();
}
void CL_SLVTS::SET_INIT(){
	APRM = boost::make_shared<CL_APRM>();
	CCDs = boost::make_shared<CL_CCDs>();
	REFs = boost::make_shared<CL_REFs>();
}
void CL_SLVTS::SET_INPUT(std::vector< std::vector< std::vector< std::string > > > SLVTS_Argvs){

	APRM->SET_INPUT(SLVTS_Argvs[0]);
	CCDs->SET_INPUT(SLVTS_Argvs[1], APRM.get());
	REFs->SET_INPUT(SLVTS_Argvs[2], APRM.get(), CCDs.get());
	if(APRM->FLAG_STD >= 2)APRM->SHOW();
	if(APRM->FLAG_STD >= 2)CCDs->SHOW();
	if(APRM->FLAG_STD >= 2)REFs->SHOW();

}
bool CL_SLVTS::CHECK_INPUT(){
	if(APRM->FLAG_STD >= 1) std::cout << "-- CHECK INPUT --" << std::endl;
	return APRM->CHECK()
		&& CCDs->CHECK()
		&& REFs->CHECK()
	;
}
void CL_SLVTS::CALC_WCS(){
	my::clock_t T1,T2;

	T1=my::clock();
	if(APRM->MODE_REJ==1)
	REFs->REJECT_BADREF();
	T2=my::clock();
	if(APRM->FLAG_STD >= 1) std::cout << "TIME REJECTION         : "<<(T2-T1) << " (sec)" << std::endl;

	T1=my::clock();
	if(APRM->MODE_CCDPOS==1)
	REFs->DETERMINE_CCDPOSITION();
	T2=my::clock();
	if(APRM->FLAG_STD >= 1) std::cout << "TIME CCDPOSITION       : "<<(T2-T1) << " (sec)" << std::endl;

	T1=my::clock();
	REFs->DETERMINE_TANSIP();
	T2=my::clock();
	if(APRM->FLAG_STD >= 1) std::cout <<"TIME TANSIP            : "<<(T2-T1) << " (sec)" << std::endl;

}

} // namespace tansip
}} // namespace hsc::meas
