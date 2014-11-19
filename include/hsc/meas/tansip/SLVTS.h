//-----------------------------------------------------------
//SLVTS.h
//class solvetansip
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef  g99cf6978_db6c_4a74_9c0b_2cf5231f0aab
#define  g99cf6978_db6c_4a74_9c0b_2cf5231f0aab

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include "hsc/meas/tansip/APRM.h"
#include "hsc/meas/tansip/CCD.h"
#include "hsc/meas/tansip/REF.h"

namespace hsc { namespace meas {
namespace tansip {

class CL_SLVTS{
private:
public:
	boost::shared_ptr<CL_APRM> APRM;//class anaysis parameters
	boost::shared_ptr<CL_CCDs> CCDs;//class CCDs
	boost::shared_ptr<CL_REFs> REFs;//class references

//FUNCTIONs
	void SET_INPUT(
		std::vector< std::vector< std::string > > const& APRM,
		std::vector<CCDPosition   >               const& ccdPosition,
		std::vector<ReferenceMatch>               const& matchList
	);//setting input information
	bool CHECK_INPUT();//checking input values
	void CALC_WCS();//main calculation of solvetansip
};

boost::shared_ptr<CL_SLVTS> SOLVETANSIP(
	std::vector< std::vector< std::string > > const& APRM,
	std::vector<CCDPosition   >               const& ccdPosition,
	std::vector<ReferenceMatch>               const& matchList
);//called by lsst for calculating solvetansip

} // namespace tansip
}} // namespace hsc::meas
#endif //g99cf6978_db6c_4a74_9c0b_2cf5231f0aab
