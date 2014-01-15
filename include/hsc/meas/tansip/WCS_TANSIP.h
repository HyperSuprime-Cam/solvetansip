//------------------------------------------------------------
//WCS_TANSIP.h
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#ifndef WCS_TANSIP_H
#define WCS_TANSIP_H

//#include "hsc/meas/tansip/WCS_PL_MAIN.h"
#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"
#include "hsc/meas/tansip/WCS_SUB.h"
#include "hsc/meas/tansip/LeastSquares.h"

void    F_WCSA_TANSIP             (CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP);
void    F_WCSA_TANSIP_SET_APROP   (CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP);
void    F_WCSA_TANSIP_SET_GSIP    (CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP);
void    F_WCSA_TANSIP_SET_APAIR   (CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP);
void    F_WCSA_TANSIP_SET_GETREJECTIONRESULT(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP);
void    F_WCSA_TANSIP_SET_GETWCS  (CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP);
void    F_WCSA_TANSIP_SET_CALCREFPARAMLOCAL(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP);

#endif
