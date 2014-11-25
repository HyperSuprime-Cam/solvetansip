//-----------------------------------------------------------
//SLVTS.h
//class solvetansip
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef  g99cf6978_db6c_4a74_9c0b_2cf5231f0aab
#define  g99cf6978_db6c_4a74_9c0b_2cf5231f0aab

#include <vector>
#include <boost/shared_ptr.hpp>

#include "hsc/meas/tansip/APRM.h"
#include "hsc/meas/tansip/CCDPosition.h"
#include "hsc/meas/tansip/ReferenceMatch.h"

namespace hsc { namespace meas {
namespace tansip {

/** The handle of solved data
	To read from it, use SLVTS_GET.h and SLVTS_LSST.h
*/
struct SLVTSState
{
#ifdef SWIG
private: // SWIG should not see the members
#endif
	boost::shared_ptr<void> APRM; /// pointer to AnaParam
	boost::shared_ptr<void> CCDs; /// pointer to CL_CCDs
	boost::shared_ptr<void> REFs; /// pointer to CL_REFs
};

/** Solve TANSIP (The main routine)
*/
SLVTSState SOLVETANSIP(
	AnaParam                    const& param,
	std::vector<CCDPosition   > const& ccdPosition,
	std::vector<ReferenceMatch> const& matchList
);

} // namespace tansip
}} // namespace hsc::meas
#endif //g99cf6978_db6c_4a74_9c0b_2cf5231f0aab
