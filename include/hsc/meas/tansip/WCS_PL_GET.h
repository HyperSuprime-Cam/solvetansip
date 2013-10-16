//-----------------------------------------------------------
//WCS_PL_GET.h
//
//Last modification : 2011/06/15
//------------------------------------------------------------
#include "hsc/meas/tansip/WCS_PL_MAIN.h"
#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"
#ifndef WCS_PL_GET_H
#define WCS_PL_GET_H
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP Values
//-----------------------------------------------------------------
int F_WCSA_PLGET_CCDNUM(CL_WCSA_ASP* WCSA_ASP);
int F_WCSA_PLGET_ALLREFNUM(CL_WCSA_ASP* WCSA_ASP);
int F_WCSA_PLGET_ALLFITNUM(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLGET_CRPIX(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLGET_CRVAL(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLGET_REFNUM(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLGET_FITNUM(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLGET_SIPRMSX(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLGET_SIPRMSY(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLGET_PSIPRMSX(CL_WCSA_ASP* WCSA_ASP);
std::vector< double > F_WCSA_PLGET_PSIPRMSY(CL_WCSA_ASP* WCSA_ASP);
//-----------------------------------------------------------------
//Getting Functions : CCD Info
//-----------------------------------------------------------------
std::vector< int > F_WCSA_PLGET_CCD_ID(CL_WCSA_ASP* WCSA_ASP);
std::vector< int > F_WCSA_PLGET_CCD_NUMREF(CL_WCSA_ASP* WCSA_ASP);
std::vector< int > F_WCSA_PLGET_CCD_NUMFIT(CL_WCSA_ASP* WCSA_ASP);
std::vector< int > F_WCSA_PLGET_CCD_ORDERSIP(CL_WCSA_ASP* WCSA_ASP);
std::vector< int > F_WCSA_PLGET_CCD_ORDERPSIP(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_GPOS(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_CR(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_CD(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_ERRSIP(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_ERRPSIP(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_COEFSIPA(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_COEFSIPB(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_COEFPSIPA(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_COEFPSIPB(CL_WCSA_ASP* WCSA_ASP);
//-----------------------------------------------------------------
//Getting Functions : REF Info
//-----------------------------------------------------------------
std::vector< long long int > F_WCSA_PLGET_REF_ID(CL_WCSA_ASP* WCSA_ASP);
std::vector< int > F_WCSA_PLGET_REF_CID(CL_WCSA_ASP* WCSA_ASP);
std::vector< int > F_WCSA_PLGET_REF_FLAG(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_POSLOCAL(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_POSGLOBAL(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_POSRADEC(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_POSLCRPIX(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_POSGCRPIX(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_DIFFSIP(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_DIFFPSIP(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_CAMERADISTSIP(CL_WCSA_ASP* WCSA_ASP);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_CAMERADISTPSIP(CL_WCSA_ASP* WCSA_ASP);
//-----------------------------------------------------------------
//Getting Functions : CCD Regions
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLGET_CORNAR(CL_WCSA_ASP* WCSA_ASP,int CID);
std::vector< double > F_WCSA_PLGET_DISTCORRCORNAR(CL_WCSA_ASP* WCSA_ASP,int CID);
std::vector< double > F_WCSA_PLGET_DISTCORRCORNAR_N(CL_WCSA_ASP* WCSA_ASP,int CID,int N);
std::vector< double > F_WCSA_PLGET_RADECCORNAR(CL_WCSA_ASP* WCSA_ASP,int CID);
std::vector< int >    F_WCSA_PLGET_INDEX(CL_WCSA_ASP *WCSA_ASP);
//-----------------------------------------------------------------
//Getting Functions : POSITIONs
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLGET_POSITION_RADECfromLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLGET_POSITION_RADECfromCRPIX(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLGET_POSITION_LOCALfromRADEC(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLGET_POSITION_CRPIXfromRADEC(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLGET_POSITION_CCDIDLOCALfromGLOBAL(CL_WCSA_ASP* WCSA_ASP,std::vector< double > XY);
std::vector< double > F_WCSA_PLGET_POSITION_GLOBALfromCCDIDLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLGET_POSITION_IMPIXELfromLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
std::vector< double > F_WCSA_PLGET_POSITION_LOCALfromIMPIXEL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY);
//-----------------------------------------------------------------
//Getting Functions : GRID POSITIONs
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLGET_POSITION_RADECfromLOCALGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLGET_POSITION_RADECfromCRPIXGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLGET_POSITION_LOCALfromRADECGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLGET_POSITION_CRPIXfromRADECGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : JACOBIAN GRID
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLGET_CRSMA_atLOCALGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLGET_CRSMA_atCRPIXGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLGET_CRSMA_atRADECGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLGET_CRSM_atLOCALGRID(CL_WCSA_ASP* WCSA_ASP,int CID,int CRSMID,std::vector< double > X,std::vector< double > Y);
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : DSITORTION GRID
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLGET_DISTORTION_atCRPIXGRID(CL_WCSA_ASP* WCSA_ASP,std::vector< double > GRID);
std::vector< std::vector< double > > F_WCSA_PLGET_DISTORTION_atRADECGRID(CL_WCSA_ASP* WCSA_ASP,std::vector< double > GRID);
//-----------------------------------------------------------------
//Getting Functions : REFERENCE values
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLGET_REF_ID(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CHIPID(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_FLAG(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYLOCAL(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYRADEC(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYGLOBAL(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYGLOBALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYLOCALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYIMPIXEL(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYIMWORLD(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CAMERACONV(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CAMERAROT(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CAMERASHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CAMERASHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CAMERAMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CAMERAPCONV(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CAMERAPROT(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CAMERAPSHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CAMERAPSHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID);
std::vector< double > F_WCSA_PLGET_REF_CAMERAPMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID);

std::vector< double > F_WCSA_PLGET_REF(CL_WCSA_ASP* WCSA_ASP, boost::int64_t REFID);
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : CCD
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLGET_CCDPOSITIONS(CL_WCSA_ASP* WCSA_ASP, int CID);

#endif
