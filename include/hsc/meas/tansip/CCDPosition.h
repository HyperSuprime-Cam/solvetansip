#ifndef  g9a772de6_7a99_4ce0_b588_20befff300cd
#define  g9a772de6_7a99_4ce0_b588_20befff300cd

namespace hsc { namespace meas {
namespace tansip {

/** CCDPosition describes the disposition of a CCD in the focal plane.
    A vector of this structure is employed as a container of user input.
*/
struct CCDPosition
{
    double centerX; ///< The position of the center of this CCD
    double centerY; ///<     in the global pixel coord
    double angle  ; ///< The position angle in radians
    int    width  ; ///< The size of this CCD, in pixels
    int    height ; ///< The size of this CCD, in pixels
};

} // tansip
}} // hsc::meas
#endif //g9a772de6_7a99_4ce0_b588_20befff300cd
