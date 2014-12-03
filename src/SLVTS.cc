//-----------------------------------------------------------
//SLVTS.cc
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include "hsc/meas/tansip/SLVTS.h"
#include "CCD.h"
#include "REF.h"
#include "HIRES_CLOCK.h"

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/make_shared.hpp>


namespace hsc { namespace meas {
namespace tansip {

SLVTSState
SOLVETANSIP(
    AnaParam                    const& param,
    std::vector<CCDPosition   > const& ccdPosition,
    std::vector<ReferenceMatch> const& matchList
){
    //
    // Devour input objects
    //

    my::clock_t TS = my::clock();
    my::clock_t T1 = TS;

    boost::shared_ptr<AnaParam> APRM = boost::make_shared<AnaParam>(param); // just clone
    boost::shared_ptr<CL_CCDs > CCDs = boost::make_shared<CL_CCDs >(ccdPosition, APRM.get());
    boost::shared_ptr<CL_REFs > REFs = boost::make_shared<CL_REFs >(matchList, APRM.get(), CCDs.get());

    if(APRM->VERBOSITY >= 2) APRM->SHOW();
    if(APRM->VERBOSITY >= 2) CCDs->SHOW();
    if(APRM->VERBOSITY >= 2) REFs->SHOW();

    //
    // Check whether the input is acceptable
    //

    if(APRM->VERBOSITY >= 1) std::cout << "-- CHECK INPUT --" << std::endl;
    if(!APRM->CHECK()
    || !CCDs->CHECK()
    || !REFs->CHECK()
    ){
        throw std::runtime_error("Error : in checking Input Values");
    }

    my::clock_t T2 = my::clock();
    if(APRM->VERBOSITY >= 1) std::cout << "TIME SET INPUT         : "<<(T2-T1) << " (sec)" << std::endl;

    //
    // Solve tansip
    //

    if(APRM->MODE_REJ){
        T1=my::clock();
        REFs->REJECT_BADREF();
        T2=my::clock();
        if(APRM->VERBOSITY >= 1) std::cout << "TIME REJECTION         : "<<(T2-T1) << " (sec)" << std::endl;
    }

    if(APRM->MODE_CCDPOS){
        T1=my::clock();
        REFs->DETERMINE_CCDPOSITION();
        T2=my::clock();
        if(APRM->VERBOSITY >= 1) std::cout << "TIME CCDPOSITION       : "<<(T2-T1) << " (sec)" << std::endl;
    }

    T1=my::clock();
    REFs->DETERMINE_TANSIP();
    T2=my::clock();
    if(APRM->VERBOSITY >= 1) std::cout <<"TIME TANSIP            : "<<(T2-T1) << " (sec)" << std::endl;

    //
    // Create an output object
    //

    SLVTSState SLVTS;
    SLVTS.APRM = APRM;
    SLVTS.CCDs = CCDs;
    SLVTS.REFs = REFs;

    my::clock_t TE = my::clock();
    if(APRM->VERBOSITY >= 1) std::cout << "TIME SOLVETANSIP TOTAL : "<<(TE-TS) << " (sec)" << std::endl;

    return SLVTS;
}

} // namespace tansip
}} // namespace hsc::meas
