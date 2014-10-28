#ifndef  g35236865_3fc2_4f50_94c7_2537fbd63cc7
#define  g35236865_3fc2_4f50_94c7_2537fbd63cc7

//-----------------------------------------------------------
//SLVTS_GET.h
//getting information from class solvetansip
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include "hsc/meas/tansip/SLVTS.h"

namespace hsc { namespace meas {
namespace tansip {

//-----------------------------------------------------------------
//Getting Functions : SUMMARY Info
//-----------------------------------------------------------------
std::string GET_SUM_MODECR(CL_SLVTS* SLVTS);//getting MODECR from APROP
int GET_SUM_MODEREJ(CL_SLVTS* SLVTS);//getting MODEREJ from APROP
int GET_SUM_MODECCD(CL_SLVTS* SLVTS);//getting MODECCDPOS from APROP
int GET_SUM_NUMCCD(CL_SLVTS* SLVTS);//getting number of CCD
int GET_SUM_NUMREF(CL_SLVTS* SLVTS);//getting number of references of input
int GET_SUM_NUMFIT(CL_SLVTS* SLVTS);//getting number of references for fitting
std::vector< double > GET_SUM_CRPIX(CL_SLVTS* SLVTS);//getting CRPIX in global coordinate
std::vector< double > GET_SUM_CRVAL(CL_SLVTS* SLVTS);//getting CRVAL
std::vector< double > GET_SUM_OAPIX(CL_SLVTS* SLVTS);//getting OAPIX in global coordinate
std::vector< double > GET_SUM_CD(CL_SLVTS* SLVTS);//getting CDMATRIX in global coordinate
double GET_SUM_ANGLE(CL_SLVTS* SLVTS);//getting ANGLE in global coordinate
std::vector< double > GET_SUM_MAX_CRPIX_G(CL_SLVTS* SLVTS);//getting MAXIMUM RADIUS in global coordinate
std::vector< double > GET_SUM_CD_CORANGLE(CL_SLVTS* SLVTS);//getting ANGLE corrected CD matrix in global coordinate
std::vector< double > GET_SUM_RMSASIP(CL_SLVTS* SLVTS);//getting RMS of SIP fitting in global coordinate
std::vector< double > GET_SUM_RMSPSIP(CL_SLVTS* SLVTS);//getting RMS of PSIP in global coordinate
//-----------------------------------------------------------------
//Getting Functions : CCD Info
//-----------------------------------------------------------------
std::vector< int > GET_CCD_ID(CL_SLVTS* SLVTS);//getting ID of all CCD
std::vector< int > GET_CCD_NUMREF(CL_SLVTS* SLVTS);//getting number of reference of input all CCD having
std::vector< int > GET_CCD_NUMFIT(CL_SLVTS* SLVTS);//getting number of reference for fitting all CCD having
std::vector< int > GET_CCD_ORDERSIP(CL_SLVTS* SLVTS);//getting oreder of SIP fitting all CCD having
std::vector< int > GET_CCD_ORDERPSIP(CL_SLVTS* SLVTS);//getting oreder of PSIP fitting all CCD having
std::vector< std::vector< double > > GET_CCD_GPOS_L(CL_SLVTS* SLVTS);//getting lower left corner CCD position of each CCD
std::vector< std::vector< double > > GET_CCD_GPOS_C(CL_SLVTS* SLVTS);//getting center CCD position of each CCD
std::vector< std::vector< double > > GET_CCD_CR(CL_SLVTS* SLVTS);//getting CRPIX of all CCD
std::vector< std::vector< double > > GET_CCD_OA(CL_SLVTS* SLVTS);//getting OAPIX of all CCD
std::vector< std::vector< double > > GET_CCD_CD(CL_SLVTS* SLVTS);//getting CD MATRIX of all CCD
std::vector< std::vector< double > > GET_CCD_ERRSIP(CL_SLVTS* SLVTS);//getting statistics of SIP fitting of all CCD
std::vector< std::vector< double > > GET_CCD_ERRPSIP(CL_SLVTS* SLVTS);//getting statistics of SIP fitting of all CCD
std::vector< std::vector< double > > GET_CCD_COEFSIPA(CL_SLVTS* SLVTS);//getting coefficients of SIPA fitting of all CCD
std::vector< std::vector< double > > GET_CCD_COEFSIPB(CL_SLVTS* SLVTS);//getting coefficients of SIPB fitting of all CCD
std::vector< std::vector< double > > GET_CCD_COEFPSIPA(CL_SLVTS* SLVTS);//getting coefficients of PSIPA fitting of all CCD
std::vector< std::vector< double > > GET_CCD_COEFPSIPB(CL_SLVTS* SLVTS);//getting coefficients of PSIPB fitting of all CCD
//-----------------------------------------------------------------
//Getting Functions : REF Info
//-----------------------------------------------------------------
std::vector< long long int > GET_REF_ID(CL_SLVTS* SLVTS);//getting ID of all references
std::vector< int > GET_REF_CID(CL_SLVTS* SLVTS);//getting CCD ID of all references
std::vector< int > GET_REF_FLAG(CL_SLVTS* SLVTS);//getting FLAG of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_RADEC(CL_SLVTS* SLVTS);//getting RADEC from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMWLD(CL_SLVTS* SLVTS);//getting IMWLD from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMPIX_L(CL_SLVTS* SLVTS);//getting IMPIX_L from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMPIX_G(CL_SLVTS* SLVTS);//getting IMPIX_G from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_CRPIX_L(CL_SLVTS* SLVTS);//getting CRPIX_L from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_CRPIX_G(CL_SLVTS* SLVTS);//getting CRPIX_G from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_LOCAL_L(CL_SLVTS* SLVTS);//getting LOCAL_L from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_LOCAL_G(CL_SLVTS* SLVTS);//getting LOCAL_G from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_LOCAL_C(CL_SLVTS* SLVTS);//getting LOCAL_C from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_CRPIX_L(CL_SLVTS* SLVTS);//getting CRPIX_L from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_CRPIX_G(CL_SLVTS* SLVTS);//getting CRPIX_G from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_LOCAL_L(CL_SLVTS* SLVTS);//getting LOCAL_L from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_LOCAL_G(CL_SLVTS* SLVTS);//getting LOCAL_G from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_LOCAL_C(CL_SLVTS* SLVTS);//getting LOCAL_C from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_LOCAL_L(CL_SLVTS* SLVTS);//getting LOCAL_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_LOCAL_G(CL_SLVTS* SLVTS);//getting LOCAL_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_LOCAL_C(CL_SLVTS* SLVTS);//getting LOCAL_C from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_CRPIX_L(CL_SLVTS* SLVTS);//getting CRPIX_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_CRPIX_G(CL_SLVTS* SLVTS);//getting CRPIX_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMPIX_L(CL_SLVTS* SLVTS);//getting IMPIX_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMPIX_G(CL_SLVTS* SLVTS);//getting IMPIX_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMWLD_L(CL_SLVTS* SLVTS);//getting IMWLD_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMWLD_G(CL_SLVTS* SLVTS);//getting IMWLD_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_RADEC_L(CL_SLVTS* SLVTS);//getting RADEC_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_RADEC_G(CL_SLVTS* SLVTS);//getting RADEC_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_CRPIX_L(CL_SLVTS* SLVTS);//getting CRPIX_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_CRPIX_G(CL_SLVTS* SLVTS);//getting CRPIX_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMPIX_L(CL_SLVTS* SLVTS);//getting IMPIX_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMPIX_G(CL_SLVTS* SLVTS);//getting IMPIX_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMWLD_L(CL_SLVTS* SLVTS);//getting IMWLD_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMWLD_G(CL_SLVTS* SLVTS);//getting IMWLD_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_RADEC_L(CL_SLVTS* SLVTS);//getting RADEC from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_RADEC_G(CL_SLVTS* SLVTS);//getting RADEC from DETECTED of all references
std::vector< std::vector< double > > GET_REF_DIFF(CL_SLVTS* SLVTS);//getting DIFF from SIP and PSIP fitting of all references
std::vector< std::vector< double > > GET_REF_CAMERADISTPSIP(CL_SLVTS* SLVTS);//getting DISTORTION from PSIP fitting of all references

} // namespace tansip
}} // namespace hsc::meas
#endif //g35236865_3fc2_4f50_94c7_2537fbd63cc7

