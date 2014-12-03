//-----------------------------------------------------------
//REF.h
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef  g34c2d15f_e6b5_475f_ba9f_16a88227c416
#define  g34c2d15f_e6b5_475f_ba9f_16a88227c416

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include <ndarray.h>

#include "hsc/meas/tansip/ReferenceMatch.h"
#include "hsc/meas/tansip/APRM.h"
#include "CCD.h"
#include "Polynomial.h"

namespace hsc { namespace meas {
namespace tansip {


enum EPosDetected
{
    DETECTED_LOCAL_G,
    DETECTED_CRPIX_G,
    DETECTED_IMPIX_G,
    DETECTED_IMWLD_G,
    DETECTED_RADEC_G,
};

enum EPosCelestial
{
    CELESTIAL_RADEC,
    CELESTIAL_IMWLD,
    CELESTIAL_IMPIX_G,
    CELESTIAL_CRPIX_G,
    CELESTIAL_LOCAL_G,
};

struct CL_REFs;

struct CL_REF
{
    AnaParam * APRM;//=SLVTS->APRM
    CL_REFs  * REFs;
    CL_CCD   * CCD;//=SLVTS->CCDs->CCD[ID_CCD]
    CL_GCD   * GCD;//=SLVTS->CCDs->CCD[NUMCCD]

    int ID_CCD;
    int FLAG_OBJ;
//POS_CELESTIC
    double  POS_CELESTIAL_RADEC[2];//degree
    double  POS_CELESTIAL_IMWLD[2];//degree
    double  POS_CELESTIAL_IMPIX_L[2];
    double  POS_CELESTIAL_IMPIX_G[2];
    double  POS_CELESTIAL_CRPIX_L[2];
    double  POS_CELESTIAL_CRPIX_G[2];
    double  POS_CELESTIAL_LOCAL_G[2];
    double  POS_CELESTIAL_LOCAL_L[2];
    double  POS_CELESTIAL_PSIP_CRPIX_L[2];
    double  POS_CELESTIAL_PSIP_CRPIX_G[2];
    double  POS_CELESTIAL_PSIP_LOCAL_G[2];
    double  POS_CELESTIAL_PSIP_LOCAL_L[2];

//POS_DETECTED
    double  POS_DETECTED_LOCAL_L[2];
    double  POS_DETECTED_LOCAL_G[2];
    double  POS_DETECTED_CRPIX_L[2];
    double  POS_DETECTED_CRPIX_G[2];
    double  POS_DETECTED_IMPIX_L[2];
    double  POS_DETECTED_IMPIX_G[2];
    double  POS_DETECTED_IMWLD_L[2];
    double  POS_DETECTED_IMWLD_G[2];
    double  POS_DETECTED_RADEC_L[2];
    double  POS_DETECTED_RADEC_G[2];
    double  POS_DETECTED_ASIP_CRPIX_L[2];
    double  POS_DETECTED_ASIP_CRPIX_G[2];
    double  POS_DETECTED_ASIP_IMPIX_L[2];
    double  POS_DETECTED_ASIP_IMPIX_G[2];
    double  POS_DETECTED_ASIP_IMWLD_L[2];
    double  POS_DETECTED_ASIP_IMWLD_G[2];
    double  POS_DETECTED_ASIP_RADEC_L[2];
    double  POS_DETECTED_ASIP_RADEC_G[2];
//DIFF
    double  DIFF_ASIP[2];
    double  DIFF_PSIP[2];
//DIST
    double  CAMERA_JACO;

//Run-time position selectors
    double const (&(POS(EPosDetected  d) const))[2];
    double const (&(POS(EPosCelestial c) const))[2];

    double (&POS(EPosDetected  d))[2];
    double (&POS(EPosCelestial c))[2];

// Position converters
    void SET_POS_DETECTED_LOCAL_GfromLOCAL_L();//setting detected position of LOCAL_G from LOCAL_L
    void SET_POS_DETECTED_CRPIX_LfromLOCAL_L();//setting detected position of CRPIX_L from LOCAL_L
    void SET_POS_DETECTED_CRPIX_GfromLOCAL_G();//setting detected position of CRPIX_G from LOCAL_G
    void SET_POS_DETECTED_IMPIX_LfromCRPIX_L();//setting detected position of IMPIX_L from CRPIX_L
    void SET_POS_DETECTED_IMPIX_GfromCRPIX_G();//setting detected position of IMPIX_G from CRPIX_G
    void SET_POS_DETECTED_IMWLD_LfromIMPIX_L();//setting detected position of IMWLD_L from IMPIX_L
    void SET_POS_DETECTED_IMWLD_GfromIMPIX_G();//setting detected position of IMWLD_G from IMPIX_G
    void SET_POS_DETECTED_RADEC_LfromIMWLD_L();//setting detected position of RADEC_L from IMWLD_L
    void SET_POS_DETECTED_RADEC_GfromIMWLD_G();//setting detected position of RADEC_G from IMWLD_G
    void SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L();//setting detected position of IMPIX_L from CRPIX_L with SIP
    void SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();//setting detected position of IMPIX_G from CRPIX_G with SIP
    void SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L();//setting detected position of IMWLD_L from IMPIX_L with SIP
    void SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G();//setting detected position of IMWLD_G from IMPIX_G with SIP
    void SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L();//setting detected position of RADEC_L from IMWLD_L with SIP
    void SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G();//setting detected position of RADEC_G from IMWLD_G with SIP
    void SET_POS_CELESTIAL_IMWLDfromRADEC();//setting celestial position of IMWLD from RADEC
    void SET_POS_CELESTIAL_IMPIX_GfromIMWLD();//setting celestial position of IMPIX_G from IMWLD
    void SET_POS_CELESTIAL_IMPIX_LfromIMWLD();//setting celestial position of IMPIX_L from IMWLD
    void SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G();//setting celestial position of CRPIX_G from IMPIX_G
    void SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L();//setting celestial position of CRPIX_L from IMPIX_L
    void SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G();//setting celestial position of LOCAL_G from CRPIX_G
    void SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L();//setting celestial position of LOCAL_L from CRPIX_L
    void SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD();//setting celestial position of LOCAL_G from IMWLD with PSIP
    void SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();//setting celestial position of CRPIX_G from IMPIX_G with PSIP
    void SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L();//setting celestial position of CRPIX_L from IMPIX_L with PSIP
    void SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G();//setting celestial position of LOCAL_G from CRPIX_G with PSIP
    void SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L();//setting celestial position of LOCAL_L from CRPIX_L with PSIP
    void SET_DIFF();//calculating differences from SIP and PSIP fitting
    void SET_OPTICAL_DISTORTIONbyPSIP();//calculating distortion from PSIP
};


inline double const (&(CL_REF::POS(EPosDetected  d) const))[2]
{
    switch(d){
    case DETECTED_LOCAL_G:
        return POS_DETECTED_LOCAL_G;
    case DETECTED_CRPIX_G:
        return POS_DETECTED_CRPIX_G;
    case DETECTED_IMPIX_G:
        return POS_DETECTED_IMPIX_G;
    case DETECTED_IMWLD_G:
        return POS_DETECTED_IMWLD_G;
    case DETECTED_RADEC_G:
    default:
        return POS_DETECTED_RADEC_G;
    }
}


inline double (&CL_REF::POS(EPosDetected  d))[2]
{
    switch(d){
    case DETECTED_LOCAL_G:
        return POS_DETECTED_LOCAL_G;
    case DETECTED_CRPIX_G:
        return POS_DETECTED_CRPIX_G;
    case DETECTED_IMPIX_G:
        return POS_DETECTED_IMPIX_G;
    case DETECTED_IMWLD_G:
        return POS_DETECTED_IMWLD_G;
    case DETECTED_RADEC_G:
    default:
        return POS_DETECTED_RADEC_G;
    }
}


inline double const (&(CL_REF::POS(EPosCelestial c) const))[2]
{
    switch(c){
    case CELESTIAL_RADEC:
        return POS_CELESTIAL_RADEC;
    case CELESTIAL_IMWLD:
        return POS_CELESTIAL_IMWLD;
    case CELESTIAL_IMPIX_G:
        return POS_CELESTIAL_IMPIX_G;
    case CELESTIAL_CRPIX_G:
        return POS_CELESTIAL_CRPIX_G;
    case CELESTIAL_LOCAL_G:
    default:
        return POS_CELESTIAL_LOCAL_G;
    }
}


inline double (&CL_REF::POS(EPosCelestial c))[2]
{
    switch(c){
    case CELESTIAL_RADEC:
        return POS_CELESTIAL_RADEC;
    case CELESTIAL_IMWLD:
        return POS_CELESTIAL_IMWLD;
    case CELESTIAL_IMPIX_G:
        return POS_CELESTIAL_IMPIX_G;
    case CELESTIAL_CRPIX_G:
        return POS_CELESTIAL_CRPIX_G;
    case CELESTIAL_LOCAL_G:
    default:
        return POS_CELESTIAL_LOCAL_G;
    }
}


struct CL_REFs{
public:
    AnaParam * APRM;//SLVTS->APRM
    CL_CCDs  * CCDs;//SLVTS->CCDs
    std::vector<CL_REF>  REF;
    Polynomial2D PSIP_DX[2];
    Polynomial2D PSIP_DY[2];
    double   MAX_LOCAL_G[2];
    double   MIN_LOCAL_G[2];
    double   AVE_LOCAL_G[2];

//FUNCTIONS
    CL_REFs(
        std::vector<ReferenceMatch> const& matchList,
        AnaParam                         * APRM_IN,
        CL_CCDs                          * CCDs_IN
    );

    void SET_NUM() const;//setting NUM_REF, NUM_FIT, NUM_REJ
    bool CHECK();//checking current values

    template <class CL_REF_MemberFunc>
    void forAllRef(CL_REF_MemberFunc const& memFunc){
        for(std::vector<CL_REF>::iterator r = REF.begin();
            r != REF.end(); ++r
        ){
            ((*r).*memFunc)();
        }
    }

//FUNCTIONS::POS
    void SET_POS_DETECTED_LOCAL_GfromLOCAL_L();//setting detected position of LOCAL_G from LOCAL_L for all references
    void SET_POS_DETECTED_CRPIX_LfromLOCAL_L();//setting detected position of CRPIX_L from LOCAL_L for all references
    void SET_POS_DETECTED_CRPIX_GfromLOCAL_G();//setting detected position of CRPIX_G from LOCAL_G for all references
    void SET_POS_DETECTED_IMPIX_LfromCRPIX_L();//setting detected position of IMPIX_L from CRPIX_L for all references
    void SET_POS_DETECTED_IMPIX_GfromCRPIX_G();//setting detected position of IMPIX_G from CRPIX_G for all references
    void SET_POS_DETECTED_IMWLD_LfromIMPIX_L();//setting detected position of IMWLD_L from IMPIX_L for all references
    void SET_POS_DETECTED_IMWLD_GfromIMPIX_G();//setting detected position of IMWLD_G from IMPIX_G for all references
    void SET_POS_DETECTED_RADEC_LfromIMWLD_L();//setting detected position of RADEC_L from IMWLD_L for all references
    void SET_POS_DETECTED_RADEC_GfromIMWLD_G();//setting detected position of RADEC_G from IMWLD_G for all references
    void SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L();//setting detected position of IMPIX_L from CRPIX_L with SIP for all references
    void SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();//setting detected position of IMPIX_G from CRPIX_G with SIP for all references
    void SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L();//setting detected position of IMWLD_L from IMPIX_L with SIP for all references
    void SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G();//setting detected position of IMWLD_G from IMPIX_G with SIP for all references
    void SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L();//setting detected position of RADEC_L from IMWLD_L with SIP for all references
    void SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G();//setting detected position of RADEC_G from IMWLD_G with SIP for all references
    void SET_POS_DETECTED_ALL();//setting all detected positions for all references
    void SET_POS_CELESTIAL_IMWLDfromRADEC();//setting celestial position of IMWLD from RADEC for all references
    void SET_POS_CELESTIAL_IMPIX_GfromIMWLD();//setting celestial position of IMPIX_G from IMWLD for all references
    void SET_POS_CELESTIAL_IMPIX_LfromIMWLD();//setting celestial position of IMPIX_L from IMWLD for all references
    void SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G();//setting celestial position of CRPIX_G from IMPIX_G for all references
    void SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L();//setting celestial position of CRPIX_L from IMPIX_L for all references
    void SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G();//setting celestial position of LOCAL_G from CRPIX_G for all references
    void SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L();//setting celestial position of LOCAL_L from CRPIX_L for all references
    void SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD();//setting celestial position of LOCAL_G from IMWLD with PSIP for all references
    void SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();//setting celestial position of CRPIX_G from IMPIX_G with PSIP for all references
    void SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L();//setting celestial position of CRPIX_L from IMPIX_L with PSIP for all references
    void SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G();//setting celestial position of LOCAL_G from CRPIX_G with PSIP for all references
    void SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L();//setting celestial position of LOCAL_L from CRPIX_L with PSIP for all references
    void SET_POS_CELESTIAL_ALL();//setting all celestial positions for all references
    void SET_DIFF();//calculating differences from SIP and PSIP fitting for all references
    void SET_OPTICAL_DISTORTIONbyPSIP();//calculating distortion from PSIP all references
    void SET_MAXMIN_LOCAL_G();//setting maximum position in global coordinate
    void SET_MAXMIN_CRPIX_G();//setting maximum position in global CRPIX coordinate
    int  GET_ID_NEAR_CRVAL();//getting ID of reference which is nearest to CRVAL
    int  GET_ID_NEAR_CRPIX();//getting ID of reference which is nearest to CRPIX
//FUNCTIONS::FIT
    void FIT_CbyD(EPosCelestial ID_C, EPosDetected ID_D);//fitting Celestial position by Detected position and getting coefficients of polynomial fitting. coordinates are assined by ID_C and ID_D
    void FIT_DbyC(EPosDetected ID_D, EPosCelestial ID_C);//fitting Detected position by Celestial position and getting coefficients of polynomial fitting. coordinates are assined by ID_C and ID_D
    void CALC_STAT_ASIP();//getting statistics of SIP fitting for global fitting
    void CALC_STAT_PSIP();//getting statistics of PSIP fitting for global fitting
    void CALC_STAT_SIP_LOCAL();//getting statistics of SIP and PSIP fitting for each CCD fitting
    void CALC_CRPIXatCRVAL();//calculating CRPIX as CRVAL
    void CALC_CRVALatCRPIX();//calculating CRVAL as CRPIX
    void CALC_CENTERPIXEL();//calculating average position of references
    void SET_CRPIXatCENTER();//setting average position as CRPIX
//REJECTION
    void REJECT_BADREF();//rejecting references which have position far from fitting position
    void REJECT_BADREF_ASIP();//rejecting references which have position far from  SIP fitting position
    void REJECT_BADREF_PSIP();//rejecting references which have position far from PSIP fitting position
//CCD POSITION
    void DETERMINE_CCDPOSITION();//determining CCD positions
    void SET_CCDAVE();//shifting CCD positions to fit CCDBASIS
//TANSIP
    void DETERMINE_TANSIP();//determining SIP, Distortion, statistics of fitting and references positions
    void CALC_TANSIP();//calculating CD, SIP and PSIP coefficients
//DISTORTION
    void CALC_OPTICAL_DISTORTION();//CALC Distortion from PSIP
    Polynomial2D FIT_PSIP_JACO(); //fitting CCDs' Jacobian with PSIP
    void CALC_OPTICAL_AXIS();//caluclationg optical axis

    void SHOW();//show information of references

};

} // namespace tansip
}} // namespace hsc::meas
#endif //g34c2d15f_e6b5_475f_ba9f_16a88227c416
