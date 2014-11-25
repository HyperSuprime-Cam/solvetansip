#ifndef  g756b9590_676d_43ae_8c81_f578a39c2f87
#define  g756b9590_676d_43ae_8c81_f578a39c2f87

#include "lsst/pex/policy.h"

#include "lsst/afw/coord.h"
#include "lsst/afw/geom.h"
#include "lsst/afw/table.h"

#include "lsst/afw/cameraGeom.h"

#include "APRM.h"
#include "CCDPosition.h"
#include "ReferenceMatch.h"


namespace hsc { namespace meas {
namespace tansip {

//
// AnaParam converters
//

/** Create AnaParam by reading Policy
*/
AnaParam
toAnaParam(
    lsst::pex::policy::Policy const& policy
);


//
// CCDPosition converters
//

/** Get CCDPosition of a specific CCD
*/
CCDPosition
getCCDPosition(
    lsst::afw::cameraGeom::DetectorMosaic const& camera,
    int                                          ccdId
);

/** Get CCDPositions of all CCDs whose ccdId is in [0, numCcd)
*/
std::vector<CCDPosition>
getCCDPositionList(
    lsst::afw::cameraGeom::DetectorMosaic const& camera,
    int                                          numCcd
);

//
// ReferenceMatch converters
//

/** Create a single ReferenceMatch from afw coord objects.
    @param sky    The position of a reference object
    @param pixels The position of a detected object
    @param ccdId  The ID of the CCD on which the object is detected
*/
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


/**  Create a single ReferenceMatch from afw::ReferenceMatch.
    @param match  Match.
    @param ccdId  The ID of the CCD on which the object is detected
*/
inline ReferenceMatch
toReferenceMatch(
    lsst::afw::table::ReferenceMatch const& match,
    int                                     ccdId
){
    return toReferenceMatch(match.first->getCoord(), match.second->getCentroid(), ccdId);
}


/** toReferenceMatchList(matchLists) is not defined here
    but in the python wrapper layer.
*/

} // namespace tansip
}} // namespace hsc::meas
#endif //g756b9590_676d_43ae_8c81_f578a39c2f87
