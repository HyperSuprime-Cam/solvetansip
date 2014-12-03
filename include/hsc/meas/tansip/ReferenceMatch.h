#ifndef  ga213c8b2_84d9_443b_ba7d_a14c3be178e9
#define  ga213c8b2_84d9_443b_ba7d_a14c3be178e9

namespace hsc { namespace meas {
namespace tansip {

/** Match of a source on a detector and a celestial object.
    A vector of this structure is employed as a container of user input.
*/
struct ReferenceMatch
{
    int    ccdId; ///< on which CCD this object is
    double x    ; ///< LOCAL_L coord
    double y    ; ///< LOCAL_L coord
    double ra   ; ///< in degrees
    double dec  ; ///< in degrees
};

} // namespace tansip
}} // namespace hsc::meas
#endif //ga213c8b2_84d9_443b_ba7d_a14c3be178e9
