//------------------------------------------------------------
//WCS_APROP.cc
//
//Last modification : 2010/08/03
//------------------------------------------------------------
#include "lsst/pex/policy/Policy.h"
#include "hsc/meas/tansip/WCS_APROP.h"

using namespace std;
void    F_MAKEAPROP(lsst::pex::policy::Policy::Ptr &APROPPolicy,CL_APROP *APROP){
    APROP->CRPIXMODE  =APROPPolicy->getString("CRPIXMODE");
    APROP->CCDNUM     =APROPPolicy->getInt("NCCD");
    APROP->CRPIX[0]   =APROPPolicy->getDouble("CRPIX1");
    APROP->CRPIX[1]   =APROPPolicy->getDouble("CRPIX2");
    APROP->SIP_ORDER  =APROPPolicy->getInt("SIPORDER");
    APROP->SIP_P_ORDER=APROPPolicy->getInt("PSIPORDER");
    APROP->CLIP_SIGMA =APROPPolicy->getDouble("CLIPSIGMA");	
    APROP->CHECKFILE  =APROPPolicy->getInt("CHECKFILE");	
}
