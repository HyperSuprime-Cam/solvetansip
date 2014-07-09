//-----------------------------------------------------------
//SLVTS_LSST.h
//Calling solvetansip codes in lsst pipeline
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef SLVTS_LSST_H
#define SLVTS_LSST_H

#include "lsst/daf/base/PropertySet.h"
#include "lsst/afw/image/TanWcs.h"
#include"hsc/meas/tansip/SLVTS.h"
#include"hsc/meas/tansip/SLVTS_GET.h"
namespace dafbase = lsst::daf::base;

lsst::daf::base::PropertySet::Ptr SET_EMPTYMETADATA();//making empty metadata
void SET_METADATA(CL_SLVTS* SLVTS, lsst::daf::base::PropertySet::Ptr &meta);//setting solvetansip result to metadata
void CHECK_METADATA(CL_SLVTS* SLVTS, lsst::daf::base::PropertySet::Ptr &meta);//checking values in metadata
std::vector <lsst::afw::image::TanWcs::Ptr> SET_TANWCS(CL_SLVTS* SLVTS);//setting solvetansip result to lsst WCS type

#endif
