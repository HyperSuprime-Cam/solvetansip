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

using namespace std;
boost::shared_ptr<CL_SLVTS> SOLVETANSIP(std::vector< std::vector< std::vector<std::string> > > SLVTS_Argvs){
	my::clock_t TS,TE;
	my::clock_t T1,T2;
	TS=my::clock();
	boost::shared_ptr<CL_SLVTS> SLVTS = boost::make_shared<CL_SLVTS>();

	T1=my::clock();
	SLVTS->SET_INIT();
	SLVTS->SET_INPUT(SLVTS_Argvs);
	if(SLVTS->CHECK_INPUT()==1){
		cout << "Error : in checking Input Values" <<endl;
		return boost::shared_ptr<CL_SLVTS>();
	}
	T2=my::clock();
	if(SLVTS->APRM->FLAG_STD>0.5)cout<<"TIME SET INPUT         : "<<(T2-T1) << " (sec)"<<endl;

	SLVTS->CALC_WCS();

//	SLVTS->END()

	TE=my::clock();
	if(SLVTS->APRM->FLAG_STD>0.5)cout<<"TIME SOLVETANSIP TOTAL : "<<(TE-TS) << " (sec)"<<endl;

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
	if(APRM->FLAG_STD>1.5)APRM->SHOW();
	if(APRM->FLAG_STD>1.5)CCDs->SHOW();
	if(APRM->FLAG_STD>1.5)REFs->SHOW();

}
int CL_SLVTS::CHECK_INPUT(){
	if(APRM->FLAG_STD>0.5)cout<<"-- CHECK INPUT --"<<endl;
	if(APRM->CHECK()==1)return 1;
	if(CCDs->CHECK()==1)return 1;
	if(REFs->CHECK()==1)return 1;
	return 0;
}
void CL_SLVTS::CALC_WCS(){
	my::clock_t T1,T2;

	T1=my::clock();
	if(APRM->MODE_REJ==1)
	REFs->REJECT_BADREF();
	T2=my::clock();
	if(APRM->FLAG_STD>0.5)cout<<"TIME REJECTION         : "<<(T2-T1) << " (sec)"<<endl;

	T1=my::clock();
	if(APRM->MODE_CCDPOS==1)
	REFs->DETERMINE_CCDPOSITION();
	T2=my::clock();
	if(APRM->FLAG_STD>0.5)cout<<"TIME CCDPOSITION       : "<<(T2-T1) << " (sec)"<<endl;

	T1=my::clock();
	REFs->DETERMINE_TANSIP();
	T2=my::clock();
	if(APRM->FLAG_STD>0.5)cout<<"TIME TANSIP            : "<<(T2-T1) << " (sec)"<<endl;

}

} // namespace tansip
}} // namespace hsc::meas
