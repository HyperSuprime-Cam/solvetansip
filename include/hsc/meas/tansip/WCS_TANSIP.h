//------------------------------------------------------------
//WCS_TANSIP.h
//
//Last modification : 2011/04/01
//------------------------------------------------------------

#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_CPROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"

void    F_WCS_TANSIP(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
//MAIN
void    F_WCS_TANSIP_SET (CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_CCD (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
//SUB
double  F_CALCVALUE(int ORDER,double *Coef,double *X);
void    F_PROJECTION(double *Cdeg,double *Pdeg,double *PPOINT);
void    F_InvPROJECTION(double *Pdeg,double *Cdeg,double *PPOINT);
void    F_DIFFSIP(int ORDER,double *Coef,double *dxCoef,double *dyCoef);  
void    F_INTSIP(int ORDER,double *dxCoef,double *dyCoef,double *Coef);
//etc
void    F_LS2(int dataNUM,int Order,double **data,double *Coef);
void    F_LS1(int dataNUM,int Order,double **data,double *Coef);
void	F_RMS(int NUM,double *data,double *STAT);
void    F_InvM(int MNUM,double **Min,double **Mout);
/*
void    F_WCS_TANSIP_GPOS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_WCSCCD(CL_APROP, CL_CPROP *,CL_PAIR *,CL_CSIP *);
void    F_PROJECTIONPOINT(CL_APROP,CL_CPROP,CL_PAIR*,CL_CSIP*);
void    F_PROJECTION(CL_APROP,CL_CPROP,CL_PAIR*,CL_CSIP*);
void    F_LPFITTING_DIFFPAIR(CL_APROP,CL_CPROP,CL_PAIR*,CL_CSIP*);
void    F_CHANGEdxLtodxG(CL_APROP,CL_CPROP*,CL_PAIR*,CL_CSIP*);
void    F_CHANGEdxLtodxG_Linear(CL_APROP,CL_CPROP*,CL_PAIR*,CL_CSIP*);
void    F_CHANGEdxLtodxGNOROT(CL_APROP,CL_CPROP,CL_PAIR*,CL_CSIP*);
void    F_FITINTdxGdxI(CL_APROP,CL_CPROP,CL_PAIR*,CL_CSIP*);
void    F_FITGPOS(CL_APROP,CL_CPROP*,CL_PAIR*,CL_CSIP*);
void    F_CDSIP(CL_APROP,CL_CPROP*,CL_PAIR*,CL_CSIP*);
void    F_WCSPIX_TAN(double x[],double CR[],double CD[][2]);
void    F_PIXWCS_TAN(double x[],double CR[],double CD[][2]);
void    F_SIP(int FR,int Order,double x[],double xSIP[],double CR[],double *SIP[2]);
void    F_FLAG(CL_APROP,CL_PAIR*,CL_CSIP*);
void    F_InvM(int MNUM,double **Min,double **Mout);
void    F_LS2(int dataNUM,int Order,double **data,double *Coef);
*/
