//--------------------------------------------------
//SLVTANSIP_SWIG.h
//
//Last Update 2013/03/01
//--------------------------------------------------
#ifndef SLVTANSIP_SWIG_H
#define SLVTANSIP_SWIG_H
#include"SLVTANSIP_ANA.h"

CL_ANA* SLVTANSIP_SWIG_SET(std::string,std::string);
void SLVTANSIP_SWIG_SLV(CL_ANA*);
void SLVTANSIP_SWIG_EXT(CL_ANA*);
void SLVTANSIP_SWIG_OUT(CL_ANA*);
void SLVTANSIP_SWIG_DEL(CL_ANA*);
CL_ANA* SLVTANSIP_SWIG_MAKE_ANAfromfits(std::string CCDDIR);
void    SLVTANSIP_SWIG_DEL_ANAfromfits(CL_ANA*);

int  SLVTANSIP_SWIG_GET_OUTFLAG(CL_ANA*);
int  SLVTANSIP_SWIG_GET_CCDNUM (CL_ANA*);
std::string SLVTANSIP_SWIG_GET_OUTDIRCCD(CL_ANA*);
std::string SLVTANSIP_SWIG_GET_OUTDIROBJ(CL_ANA*);
double  SLVTANSIP_SWIG_GET_MAXR(CL_ANA*);
std::vector< double > SLVTANSIP_SWIG_GET_CRPIX (CL_ANA*,int CID);
std::vector< double > SLVTANSIP_SWIG_GET_CRVAL (CL_ANA*,int CID);
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_CORNAR_GLOBAL(CL_ANA*);
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_GPOS_GLOBAL(CL_ANA*);
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_TANPOSITION_LOCAL(CL_ANA*,int CID,std::vector< std::vector< double > >);
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_TANPOSITION_RADEC(CL_ANA*,int CID,std::vector< std::vector< double > >);
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_SIPPOSITION_LOCAL(CL_ANA*,int CID,std::vector< std::vector< double > >);
std::vector< std::vector< double > > SLVTANSIP_SWIG_GET_SIPPOSITION_RADEC(CL_ANA*,int CID,std::vector< std::vector< double > >);

#endif
