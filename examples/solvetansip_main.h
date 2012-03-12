#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"

class CL_WCSA_ASP{//Chip property
private:
public:
    CL_APROP* APROP;
    CL_GSIP*  GSIP;
    CL_APAIR* APAIR;

    void F_WCS_PLMAIN_NEWWCSA_ASP();
    void F_WCS_PLMAIN_DELWCSA_ASP();
};
void CL_WCSA_ASP::F_WCS_PLMAIN_NEWWCSA_ASP(){
    APROP= new CL_APROP[1];
    GSIP = new CL_GSIP[1];
    APAIR= new CL_APAIR[1];
}
void CL_WCSA_ASP::F_WCS_PLMAIN_DELWCSA_ASP(){
    delete [] APROP;
    delete [] GSIP ;
    delete [] APAIR;
}
