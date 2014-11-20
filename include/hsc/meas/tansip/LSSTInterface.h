#ifndef  g756b9590_676d_43ae_8c81_f578a39c2f87
#define  g756b9590_676d_43ae_8c81_f578a39c2f87

#include "lsst/pex/policy.h"
#include "lsst/afw/coord/Coord.h"
#include "lsst/afw/geom/Point.h"
#include "lsst/afw/table/Match.h"

#include "APRM.h"
#include "ReferenceMatch.h"

#include <iostream>

namespace hsc { namespace meas {
namespace tansip {

//
// AnaParam converters
//

inline AnaParam
toAnaParam(
    lsst::pex::policy::Policy const& policy
){
    AnaParam param;

    lsst::pex::policy::Policy::StringArray names = policy.paramNames(true);
    for(lsst::pex::policy::Policy::StringArray::iterator it = names.begin();
        it != names.end(); ++it
    ){
        #define CONDITIONAL_COPY(type, internal, external) \
            if(*it == external){ \
                param.internal = policy.get##type(external); \
                continue; \
            }
        CONDITIONAL_COPY(String, INSTR        , "INSTR"        );
        CONDITIONAL_COPY(String, MODE_CR      , "MODE_CR"      );
        CONDITIONAL_COPY(Bool  , MODE_CCDPOS  , "MODE_CCDPOS"  );
        CONDITIONAL_COPY(Double, PRECISION_CCD, "PRECISION_POS");
        CONDITIONAL_COPY(Double, CRPIX[0]     , "CRPIX1"       );
        CONDITIONAL_COPY(Double, CRPIX[1]     , "CRPIX2"       );
        CONDITIONAL_COPY(Double, CRVAL[0]     , "CRVAL1"       );
        CONDITIONAL_COPY(Double, CRVAL[1]     , "CRVAL2"       );
        CONDITIONAL_COPY(Int   , ORDER_ASIP   , "ORDER_ASIP"   );
        CONDITIONAL_COPY(Int   , ORDER_PSIP   , "ORDER_PSIP"   );
        CONDITIONAL_COPY(Bool  , MODE_REJ     , "MODE_REJ"     );
        CONDITIONAL_COPY(Double, SIGMA_CLIP   , "CLIPSIGMA"    );
        CONDITIONAL_COPY(Int   , VERBOSITY    ,  "FLAG_STD"    );
        #undef CONDITIONAL_COPY

        std::cout
            << "Warning: toAnaParam: Invalid parameter ignored: "
            << *it << std::endl
        ;
    }

    return param;
}

//
// ReferenceMatch converters
//

inline ReferenceMatch
toReferenceMatch(
    lsst::afw::coord::Coord  const& sky,
    lsst::afw::geom::Point2D const& pixels,
    int                             ccdId
){
    lsst::afw::coord::IcrsCoord icrs = sky.toIcrs();

    ReferenceMatch match;
    match.ccdId = ccdId;
    match.x     = pixels.getX();
    match.y     = pixels.getY();
    match.ra    = icrs.getRa ().asDegrees();
    match.dec   = icrs.getDec().asDegrees();

    return match;
}


inline ReferenceMatch
toReferenceMatch(
    lsst::afw::table::ReferenceMatch const& match,
    int                                     ccdId
){
    return toReferenceMatch(match.first->getCoord(), match.second->getCentroid(), ccdId);
}

} // namespace tansip
}} // namespace hsc::meas
#endif //g756b9590_676d_43ae_8c81_f578a39c2f87
