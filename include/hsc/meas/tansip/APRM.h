//-----------------------------------------------------------
//APRM.h
//------------------------------------------------------------
#ifndef  gd3b2467b_f431_4fa4_94cb_a1f35bb9e186
#define  gd3b2467b_f431_4fa4_94cb_a1f35bb9e186

#include<vector>
#include<string>
#include<iostream>
#include<stdlib.h>

namespace hsc { namespace meas {
namespace tansip {

/** Analysis parameter
*/
struct AnaParam
{
    /** Mode of CRPIX/VAL.
        -- "AUTO":
            CRPIX is set automatically at the center of all detected objects,
            and CRVAL is determined with reference to this CRPIX.
        -- "PIX:
            CRPIX is given by the user,
            and CRVAL is determined with reference to this CRPIX.
        -- "VAL":
            CRVAL is given by the user,
            and CRPIX is determined with reference to this CRVAL.
    */
    std::string  MODE_CR;

//CCD
    bool    MODE_CCDPOS;   ///< Whether to compute CCDs' positions.
    double  PRECISION_CCD; ///< Precision, in pixels, of computed CCDs' positions.

//REF
    double  CRPIX1;  ///< User-given CRPIX (valid only if MODE_CR == PIX)
    double  CRPIX2;  ///< User-given CRPIX (valid only if MODE_CR == PIX)
    double  CRVAL1;  ///< User-given CRVAL (valid only if MODE_CR == VAL)
    double  CRVAL2;  ///< User-given CRVAL (valid only if MODE_CR == VAL)
    // Internal NOTE: CRPIX/VAL of AnaParam is used for input only.
    // *DO*NOT* use them in program codes: they're probably out of date.
    // Use CL_GCD::CRPIX/VAL instead.

    int     ORDER_ASIP; ///< The degree of SIP
    int     ORDER_PSIP; ///< The degree of PSIP
    bool    MODE_REJ  ; ///< Whether to reject bad references
    double  SIGMA_CLIP; ///< Reference are rejected when |dx| > SIGMA_CLIP * sigma

//OUTPUT
    int  VERBOSITY; ///< Verbosity: 0, 1, or 2

//FUNCTIONs
    AnaParam();

    void SHOW();            ///< showing curret values
    bool CHECK();           ///< checking current values
    bool CHECK_MODECR();    ///< checking current MODECR
    bool CHECK_ORDERASIP(); ///< checking current SIP oreder
    bool CHECK_ORDERPSIP(); ///< checking current PSIP order
};

} // namespace tansip
}} // namespace hsc::meas
#endif //gd3b2467b_f431_4fa4_94cb_a1f35bb9e186
