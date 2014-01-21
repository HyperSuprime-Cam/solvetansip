//-----------------------------------------------------------
//SLVTS_GET.h
//
//Last modification : 2014/01/01
//------------------------------------------------------------

#include "hsc/meas/tansip/SLVTS.h"
#ifndef SLVTS_GET_H
#define SLVTS_GET_H
//-----------------------------------------------------------------
//Getting Functions : SUMMARY Info
//-----------------------------------------------------------------
int GET_SUM_NUMCCD(CL_SLVTS* SLVTS);
int GET_SUM_NUMREF(CL_SLVTS* SLVTS);
int GET_SUM_NUMFIT(CL_SLVTS* SLVTS);
std::vector< double > GET_SUM_CRPIX(CL_SLVTS* SLVTS);
std::vector< double > GET_SUM_CRVAL(CL_SLVTS* SLVTS);
std::vector< double > GET_SUM_OAPIX(CL_SLVTS* SLVTS);
std::vector< double > GET_SUM_CD(CL_SLVTS* SLVTS);
double GET_SUM_ANGLE(CL_SLVTS* SLVTS);
std::vector< double > GET_SUM_RMSASIP(CL_SLVTS* SLVTS);
std::vector< double > GET_SUM_RMSPSIP(CL_SLVTS* SLVTS);
//-----------------------------------------------------------------
//Getting Functions : CCD Info
//-----------------------------------------------------------------
std::vector< int > GET_CCD_ID(CL_SLVTS* SLVTS);
std::vector< int > GET_CCD_NUMREF(CL_SLVTS* SLVTS);
std::vector< int > GET_CCD_NUMFIT(CL_SLVTS* SLVTS);
std::vector< int > GET_CCD_ORDERSIP(CL_SLVTS* SLVTS);
std::vector< int > GET_CCD_ORDERPSIP(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_GPOS_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_GPOS_C(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_CR(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_OA(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_CD(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_ERRSIP(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_ERRPSIP(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_COEFSIPA(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_COEFSIPB(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_COEFPSIPA(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_CCD_COEFPSIPB(CL_SLVTS* SLVTS);
//-----------------------------------------------------------------
//Getting Functions : REF Info
//-----------------------------------------------------------------
std::vector< long long int > GET_REF_ID(CL_SLVTS* SLVTS);
std::vector< int > GET_REF_CID(CL_SLVTS* SLVTS);
std::vector< int > GET_REF_FLAG(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_RADEC(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMWLD(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMPIX_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMPIX_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_CRPIX_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_CRPIX_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_LOCAL_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_LOCAL_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_LOCAL_C(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_CRPIX_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_CRPIX_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_LOCAL_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_LOCAL_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_LOCAL_C(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_LOCAL_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_LOCAL_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_LOCAL_C(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_CRPIX_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_CRPIX_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMPIX_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMPIX_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMWLD_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMWLD_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_RADEC_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_RADEC_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_CRPIX_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_CRPIX_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMPIX_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMPIX_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMWLD_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMWLD_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_RADEC_L(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_RADEC_G(CL_SLVTS* SLVTS);
std::vector< std::vector< double > > GET_REF_CAMERADISTPSIP(CL_SLVTS* SLVTS);

#endif

