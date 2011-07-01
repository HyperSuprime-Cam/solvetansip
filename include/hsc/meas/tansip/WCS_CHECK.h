//-----------------------------------------------------------
//WCS_CHECK.h
//
//Last modification : 2011/06/20
//------------------------------------------------------------
#include<vector>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
void    F_WCS_CHECK_CCDPOSITION_SC(int,CL_APROP*,CL_CPROP*);
void    F_WCS_CHECK_OADISTORTION_SC(int,double,CL_APROP*,CL_CPROP*,CL_CSIP*);
void    F_WCS_CHECK_OAPOSITION_SC(int,CL_APROP*,CL_CPROP*,CL_CSIP*);
