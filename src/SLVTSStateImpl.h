#ifndef  g85e32086_90ba_4869_9f16_427234ca9a47
#define  g85e32086_90ba_4869_9f16_427234ca9a47

#include "hsc/meas/tansip/SLVTS.h"
#include "CCD.h"
#include "REF.h"

namespace hsc { namespace meas {
namespace tansip {

/** This is a helper class that down-casts
    the members of SLVTSState.
    In SLVTSState, the members are stored as void*,
    in order to hide their types from users.
*/
struct SLVTSStateImpl
{
    AnaParam* APRM;
    CL_CCDs * CCDs;
    CL_REFs * REFs;

    SLVTSStateImpl(SLVTSState const& handle)
        : APRM(static_cast<AnaParam*>(handle.APRM.get()))
        , CCDs(static_cast<CL_CCDs *>(handle.CCDs.get()))
        , REFs(static_cast<CL_REFs *>(handle.REFs.get()))
    {}
};

} // namespace tansip
}} // namespace hsc::meas
#endif //g85e32086_90ba_4869_9f16_427234ca9a47
