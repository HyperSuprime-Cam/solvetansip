//-----------------------------------------------------------
//SLVTS_LSST.h
//Calling solvetansip codes in lsst pipeline
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef  g30d4848d_dc4e_424e_910e_12f1855fb834
#define  g30d4848d_dc4e_424e_910e_12f1855fb834

#include "lsst/daf/base/PropertySet.h"
#include "lsst/afw/image/TanWcs.h"
#include"hsc/meas/tansip/SLVTS.h"

namespace hsc { namespace meas {
namespace tansip {

/** Add solvetansip result to metadata
    @param meta
        A PropertySet to which to add new properties.
        If this parameter is nullptr, a new PropertySet is created.

    @return meta if present, otherwise a new PropertySet.
*/
lsst::daf::base::PropertySet::Ptr
GET_METADATA(SLVTSState const& handle, lsst::daf::base::PropertySet::Ptr const& meta = lsst::daf::base::PropertySet::Ptr());

/** Show (a summary of) metadata that's been added by GET_METADATA()
*/
void SHOW_METADATA(SLVTSState const& handle, lsst::daf::base::PropertySet::Ptr const& meta);

/** Create TanWcs objects for all CCDs
*/
std::vector <lsst::afw::image::TanWcs::Ptr> GET_TANWCS(SLVTSState const& handle);

} // namespace tansip
}} // namespace hsc::meas
#endif //g30d4848d_dc4e_424e_910e_12f1855fb834
