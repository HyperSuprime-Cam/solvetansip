//------------------------------------------------------------
//WCS_TANSIP.h
//
//Last modification : 2011/02/22
//------------------------------------------------------------

#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_CPROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"

void    F_WCS_TANSIP(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_WCSCCD(CL_APROP, CL_CPROP *,CL_PAIR *,CL_CSIP *);
void    F_PROJECTIONPOINT(CL_APROP,CL_CPROP,CL_PAIR*,CL_CSIP*);
void    F_PROJECTION(CL_APROP,CL_CPROP,CL_PAIR*,CL_CSIP*);
void    F_LPFITTING_DIFFPAIR(CL_APROP,CL_CPROP,CL_PAIR*,CL_CSIP*);
void    F_CHANGEdxLtodxG(CL_APROP,CL_CPROP*,CL_PAIR*,CL_CSIP*);
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

