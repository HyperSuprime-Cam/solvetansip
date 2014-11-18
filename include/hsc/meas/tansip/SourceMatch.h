#ifndef  g756b9590_676d_43ae_8c81_f578a39c2f87
#define  g756b9590_676d_43ae_8c81_f578a39c2f87

#include "lsst/afw/coord/Coord.h"
#include "lsst/afw/geom/Point.h"
#include "lsst/afw/table/Match.h"


// Declarations
namespace hsc { namespace meas {
namespace tansip {

/// Interface between LSST measurement code and solvetansip
class SourceMatch {
public:
    typedef long SourceIdType;

    /// Constructors
    SourceMatch(
        SourceIdType id,                // Identifier
        lsst::afw::coord::Coord const& sky, // Sky coordinates
        lsst::afw::geom::Point2D const& pixels, // Pixel coordinates
        lsst::afw::geom::Point2D const& pixelErrors, // Pixel coordinate errors
        double flux                                  // Source flux
        );
    SourceMatch(lsst::afw::table::ReferenceMatch match);


    /// Accessors
    SourceIdType getId() const { return _id; }
    double getRa() const { return _ra; }
    double getDec() const { return _dec; }
    double getX() const { return _x; }
    double getY() const { return _y; }
    double getXErr() const { return _xErr; }
    double getYErr() const { return _yErr; }
    double getFlux() const { return _flux; }

private:
    SourceIdType _id;                   // Identifier
    double _ra, _dec;                   // Sky coordinates, degrees ICRS
    float _x, _y;                       // Pixel coordinates
    float _xErr, _yErr;                 // Error in pixel coordinates
    double _flux;                       // Flux of source
};


// Defintions

/// Constructors
inline SourceMatch::SourceMatch(SourceIdType id, lsst::afw::coord::Coord const& sky,
                                lsst::afw::geom::Point2D const& pixels,
                                lsst::afw::geom::Point2D const& pixelErrors,
                                double flux) :
    _id(id),
    _ra(sky.getLongitude().asDegrees()),
    _dec(sky.getLatitude().asDegrees()),
    _x(pixels.getX()),
    _y(pixels.getY()),
    _xErr(pixelErrors.getX()),
    _yErr(pixelErrors.getY()),
    _flux(flux)
{}

inline SourceMatch::SourceMatch(lsst::afw::table::ReferenceMatch match) :
    _id(match.first->getId()),
    _ra(match.first->getRa().asDegrees()),
    _dec(match.first->getDec().asDegrees()),
    _x(match.second->getX()),
    _y(match.second->getY()),
    _xErr(match.second->getTable()->getCentroidErrKey().getElement(*match.second, 0, 0)),
    _yErr(match.second->getTable()->getCentroidErrKey().getElement(*match.second, 1, 1)),
    _flux(match.second->getPsfFlux())
{}


} // namespace tansip
}} // namespace hsc::meas
#endif //g756b9590_676d_43ae_8c81_f578a39c2f87
