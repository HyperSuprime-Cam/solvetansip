#ifndef  g756b9590_676d_43ae_8c81_f578a39c2f87
#define  g756b9590_676d_43ae_8c81_f578a39c2f87

#include "lsst/afw/coord/Coord.h"
#include "lsst/afw/geom/Point.h"
#include "lsst/afw/table/Match.h"

#include "ReferenceMatch.h"

// Declarations
namespace hsc { namespace meas {
namespace tansip {

/// Constructors
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
