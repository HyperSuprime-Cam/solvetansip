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
std::string GET_SUM_MODECR(SLVTSState const& handle);//getting MODECR from APROP
int GET_SUM_MODEREJ(SLVTSState const& handle);//getting MODEREJ from APROP
int GET_SUM_MODECCD(SLVTSState const& handle);//getting MODECCDPOS from APROP
int GET_SUM_NUMCCD(SLVTSState const& handle);//getting number of CCD
int GET_SUM_NUMREF(SLVTSState const& handle);//getting number of references of input
int GET_SUM_NUMFIT(SLVTSState const& handle);//getting number of references for fitting
std::vector< double > GET_SUM_CRPIX(SLVTSState const& handle);//getting CRPIX in global coordinate
std::vector< double > GET_SUM_CRVAL(SLVTSState const& handle);//getting CRVAL
std::vector< double > GET_SUM_OAPIX(SLVTSState const& handle);//getting OAPIX in global coordinate
std::vector< double > GET_SUM_CD(SLVTSState const& handle);//getting CDMATRIX in global coordinate
double GET_SUM_ANGLE(SLVTSState const& handle);//getting ANGLE in global coordinate
std::vector< double > GET_SUM_MAX_CRPIX_G(SLVTSState const& handle);//getting MAXIMUM RADIUS in global coordinate
std::vector< double > GET_SUM_CD_CORANGLE(SLVTSState const& handle);//getting ANGLE corrected CD matrix in global coordinate
std::vector< double > GET_SUM_RMSASIP(SLVTSState const& handle);//getting RMS of SIP fitting in global coordinate
std::vector< double > GET_SUM_RMSPSIP(SLVTSState const& handle);//getting RMS of PSIP in global coordinate
//-----------------------------------------------------------------
//Getting Functions : CCD Info
//-----------------------------------------------------------------
std::vector< int > GET_CCD_NUMREF(SLVTSState const& handle);//getting number of reference of input all CCD having
std::vector< int > GET_CCD_NUMFIT(SLVTSState const& handle);//getting number of reference for fitting all CCD having
std::vector< int > GET_CCD_ORDERSIP(SLVTSState const& handle);//getting oreder of SIP fitting all CCD having
std::vector< int > GET_CCD_ORDERPSIP(SLVTSState const& handle);//getting oreder of PSIP fitting all CCD having
std::vector< std::vector< double > > GET_CCD_GPOS_L(SLVTSState const& handle);//getting lower left corner CCD position of each CCD
std::vector< std::vector< double > > GET_CCD_GPOS_C(SLVTSState const& handle);//getting center CCD position of each CCD
std::vector< std::vector< double > > GET_CCD_CR(SLVTSState const& handle);//getting CRPIX of all CCD
std::vector< std::vector< double > > GET_CCD_OA(SLVTSState const& handle);//getting OAPIX of all CCD
std::vector< std::vector< double > > GET_CCD_CD(SLVTSState const& handle);//getting CD MATRIX of all CCD
std::vector< std::vector< double > > GET_CCD_ERRSIP(SLVTSState const& handle);//getting statistics of SIP fitting of all CCD
std::vector< std::vector< double > > GET_CCD_ERRPSIP(SLVTSState const& handle);//getting statistics of SIP fitting of all CCD
std::vector< std::vector< double > > GET_CCD_COEFSIPA(SLVTSState const& handle);//getting coefficients of SIPA fitting of all CCD
std::vector< std::vector< double > > GET_CCD_COEFSIPB(SLVTSState const& handle);//getting coefficients of SIPB fitting of all CCD
std::vector< std::vector< double > > GET_CCD_COEFPSIPA(SLVTSState const& handle);//getting coefficients of PSIPA fitting of all CCD
std::vector< std::vector< double > > GET_CCD_COEFPSIPB(SLVTSState const& handle);//getting coefficients of PSIPB fitting of all CCD

/** Get a CCDPosition list that's been resulted from a fit */
std::vector<CCDPosition> getCCDPositionList(SLVTSState const& handle);

//-----------------------------------------------------------------
//Getting Functions : REF Info
//-----------------------------------------------------------------
std::vector< int > GET_REF_CID(SLVTSState const& handle);//getting CCD ID of all references
std::vector< int > GET_REF_FLAG(SLVTSState const& handle);//getting FLAG of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_RADEC(SLVTSState const& handle);//getting RADEC from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMWLD(SLVTSState const& handle);//getting IMWLD from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMPIX_L(SLVTSState const& handle);//getting IMPIX_L from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMPIX_G(SLVTSState const& handle);//getting IMPIX_G from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_CRPIX_L(SLVTSState const& handle);//getting CRPIX_L from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_CRPIX_G(SLVTSState const& handle);//getting CRPIX_G from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_LOCAL_L(SLVTSState const& handle);//getting LOCAL_L from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_LOCAL_G(SLVTSState const& handle);//getting LOCAL_G from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_CRPIX_L(SLVTSState const& handle);//getting CRPIX_L from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_CRPIX_G(SLVTSState const& handle);//getting CRPIX_G from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_LOCAL_L(SLVTSState const& handle);//getting LOCAL_L from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_LOCAL_G(SLVTSState const& handle);//getting LOCAL_G from CELESTIAL of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_LOCAL_L(SLVTSState const& handle);//getting LOCAL_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_LOCAL_G(SLVTSState const& handle);//getting LOCAL_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_CRPIX_L(SLVTSState const& handle);//getting CRPIX_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_CRPIX_G(SLVTSState const& handle);//getting CRPIX_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMPIX_L(SLVTSState const& handle);//getting IMPIX_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMPIX_G(SLVTSState const& handle);//getting IMPIX_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMWLD_L(SLVTSState const& handle);//getting IMWLD_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMWLD_G(SLVTSState const& handle);//getting IMWLD_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_RADEC_L(SLVTSState const& handle);//getting RADEC_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_RADEC_G(SLVTSState const& handle);//getting RADEC_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_CRPIX_L(SLVTSState const& handle);//getting CRPIX_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_CRPIX_G(SLVTSState const& handle);//getting CRPIX_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMPIX_L(SLVTSState const& handle);//getting IMPIX_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMPIX_G(SLVTSState const& handle);//getting IMPIX_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMWLD_L(SLVTSState const& handle);//getting IMWLD_L from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMWLD_G(SLVTSState const& handle);//getting IMWLD_G from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_RADEC_L(SLVTSState const& handle);//getting RADEC from DETECTED of all references
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_RADEC_G(SLVTSState const& handle);//getting RADEC from DETECTED of all references
std::vector< std::vector< double > > GET_REF_DIFF(SLVTSState const& handle);//getting DIFF from SIP and PSIP fitting of all references
std::vector< double > GET_REF_CAMERAJACOPSIP(SLVTSState const& handle);//getting DISTORTION from PSIP fitting of all references

} // namespace tansip
}} // namespace hsc::meas
#endif //g35236865_3fc2_4f50_94c7_2537fbd63cc7

