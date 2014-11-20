#include "hsc/meas/tansip/LSSTInterface.h"
#include "Utility.h"
#include <iostream>
#include <stdexcept>

namespace hsc { namespace meas {
namespace tansip {

/** Create AnaParam by reading Policy
*/
AnaParam
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
        CONDITIONAL_COPY(Int   , VERBOSITY    , "FLAG_STD"     );
        #undef CONDITIONAL_COPY

        std::cout
            << "Warning: toAnaParam: Invalid parameter ignored: "
            << *it << std::endl
        ;
    }

    return param;
}


namespace {
    lsst::afw::cameraGeom::Detector const* findCcd(
        lsst::afw::cameraGeom::Detector const* detector,
        lsst::afw::cameraGeom::Id       const& id
    ){
        if(lsst::afw::cameraGeom::DetectorMosaic const* mosaic
            = dynamic_cast<lsst::afw::cameraGeom::DetectorMosaic const*>(detector)
        ){
            for(lsst::afw::cameraGeom::DetectorMosaic::const_iterator it = mosaic->begin();
                it != mosaic->end(); ++it
            ){
                if(lsst::afw::cameraGeom::Detector const* found = findCcd(it->get(), id)){
                    return found;
                }
            }
            return NULL;
        }
        else{
            if(detector->getId() == id) return detector;
            return NULL;
        }
    }
}

/** Get CCDPosition of a specific CCD
*/
CCDPosition
getCCDPosition(
    lsst::afw::cameraGeom::DetectorMosaic const& camera,
    int                                          ccdId
){
    lsst::afw::cameraGeom::Detector const* ccd = findCcd(&camera, ccdId);
    if(!ccd){
        throw std::runtime_error(fmt("CCD not found: ccdId = %d", ccdId));
    }
    double pixelSize = ccd->getPixelSize();

    lsst::afw::geom::Point2D  center = ccd->getCenter().getPixels(pixelSize);
    lsst::afw::geom::Extent2D size   = ccd->getSize().getPixels(pixelSize);

    CCDPosition pos;
    pos.centerX = center.getX();
    pos.centerY = center.getY();
    pos.angle   = ccd->getOrientation().getYaw().asRadians();
    pos.width   = (int)(size.getX() + 0.5);
    pos.height  = (int)(size.getY() + 0.5);

    return pos;
}


/** Get CCDPositions of all CCDs whose ccdId is in [0, numCcd)
*/
std::vector<CCDPosition>
getCCDPositionList(
    lsst::afw::cameraGeom::DetectorMosaic const& camera,
    int                                          numCcd
){
    std::vector<CCDPosition> posList(numCcd);

    for(int i = 0; i < numCcd; ++i){
        posList[i] = getCCDPosition(camera, i);
    }

    return posList;
}

} // namespace tansip
}} // namespace hsc::meas
