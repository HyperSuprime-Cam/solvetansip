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
#include"hsc/meas/tansip/SLVTS_GET.h"

namespace hsc { namespace meas {
namespace tansip {

lsst::daf::base::PropertySet::Ptr SET_EMPTYMETADATA();//making empty metadata
void SET_METADATA(CL_SLVTS* SLVTS, lsst::daf::base::PropertySet::Ptr &meta);//setting solvetansip result to metadata
void CHECK_METADATA(CL_SLVTS* SLVTS, lsst::daf::base::PropertySet::Ptr &meta);//checking values in metadata
std::vector <lsst::afw::image::TanWcs::Ptr> SET_TANWCS(CL_SLVTS* SLVTS);//setting solvetansip result to lsst WCS type

} // namespace tansip
}} // namespace hsc::meas
#endif //g30d4848d_dc4e_424e_910e_12f1855fb834
