//-----------------------------------------------------------
//SLVTS_LSST.h
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef SLVTS_LSST_H
#define SLVTS_LSST_H

#include "lsst/daf/base/PropertySet.h"
#include"hsc/meas/tansip/SLVTS.h"
namespace dafbase = lsst::daf::base;

dafbase::PropertySet::Ptr SET_EMPTYMETADATA();
void SET_METADATA(std::vector< CL_SLVTS* > SLVTS, dafbase::PropertySet::Ptr &meta);

#endif
