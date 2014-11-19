//------------------------------------------------------------
//SLVTS_GET.cc
//getting program for wcs in pipeline
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include "hsc/meas/tansip/SLVTS_GET.h"

namespace hsc { namespace meas {
namespace tansip {

using namespace std;
//-----------------------------------------------------------------
//Getting Functions : SUMMARY Info
//-----------------------------------------------------------------
std::string GET_SUM_MODECR(CL_SLVTS* SLVTS){
	return SLVTS->APRM->MODE_CR;
}
int GET_SUM_MODEREJ(CL_SLVTS* SLVTS){
	return SLVTS->APRM->MODE_REJ;
}
int GET_SUM_MODECCD(CL_SLVTS* SLVTS){
	return SLVTS->APRM->MODE_CCDPOS;
}
int GET_SUM_NUMCCD(CL_SLVTS* SLVTS){
	return SLVTS->CCDs->CCD.size();
}
int GET_SUM_NUMFIT(CL_SLVTS* SLVTS){
	return SLVTS->APRM->NUM_FIT;
}
std::vector< double > GET_SUM_CRPIX(CL_SLVTS* SLVTS){
	std::vector< double > CRPIX;
	CRPIX.push_back(SLVTS->CCDs->GCD.CRPIX[0]);
	CRPIX.push_back(SLVTS->CCDs->GCD.CRPIX[1]);
	return CRPIX;
}
std::vector< double > GET_SUM_CRVAL(CL_SLVTS* SLVTS){
	std::vector< double > CRVAL;
	CRVAL.push_back(SLVTS->APRM->CRVAL[0]);
	CRVAL.push_back(SLVTS->APRM->CRVAL[1]);
	return CRVAL;
}
std::vector< double > GET_SUM_OAPIX(CL_SLVTS* SLVTS){
	std::vector< double > OAPIX;
	OAPIX.push_back(SLVTS->CCDs->GCD.OAPIX[0]);
	OAPIX.push_back(SLVTS->CCDs->GCD.OAPIX[1]);
	return OAPIX;
}
std::vector< double > GET_SUM_CD(CL_SLVTS* SLVTS){
	std::vector< double > CD;
	CD.push_back(SLVTS->CCDs->GCD.CD[0][0]);
	CD.push_back(SLVTS->CCDs->GCD.CD[0][1]);
	CD.push_back(SLVTS->CCDs->GCD.CD[1][0]);
	CD.push_back(SLVTS->CCDs->GCD.CD[1][1]);
	return CD;
}
double GET_SUM_ANGLE(CL_SLVTS* SLVTS){
	return SLVTS->CCDs->GCD.ANGLE;
}
std::vector< double > GET_SUM_MAX_CRPIX_G(CL_SLVTS* SLVTS){
	std::vector< double > MAX_CRPIX_G;
	MAX_CRPIX_G.push_back(SLVTS->CCDs->MAX_CRPIX_G[0]);
	MAX_CRPIX_G.push_back(SLVTS->CCDs->MAX_CRPIX_G[1]);
	MAX_CRPIX_G.push_back(SLVTS->CCDs->MIN_CRPIX_G[0]);
	MAX_CRPIX_G.push_back(SLVTS->CCDs->MIN_CRPIX_G[1]);
	MAX_CRPIX_G.push_back(SLVTS->CCDs->AVE_CRPIX_G[0]);
	MAX_CRPIX_G.push_back(SLVTS->CCDs->AVE_CRPIX_G[1]);
	return MAX_CRPIX_G;
}
std::vector< double > GET_SUM_CD_CORANGLE(CL_SLVTS* SLVTS){
	double GCD[4],GANG;
	std::vector< double > CD_COR;
	GCD[0]=SLVTS->CCDs->GCD.CD[0][0];
	GCD[1]=SLVTS->CCDs->GCD.CD[0][1];
	GCD[2]=SLVTS->CCDs->GCD.CD[1][0];
	GCD[3]=SLVTS->CCDs->GCD.CD[1][1];
	GANG  =SLVTS->CCDs->GCD.ANGLE;

	CD_COR.push_back(cos(-GANG)*GCD[0]-sin(-GANG)*GCD[2]);
	CD_COR.push_back(cos(-GANG)*GCD[1]-sin(-GANG)*GCD[3]);
	CD_COR.push_back(sin(-GANG)*GCD[0]+cos(-GANG)*GCD[2]);
	CD_COR.push_back(sin(-GANG)*GCD[1]+cos(-GANG)*GCD[3]);
	return CD_COR;
}
std::vector< double > GET_SUM_RMSASIP(CL_SLVTS* SLVTS){
	std::vector< double > RMSASIP;
	RMSASIP.push_back(SLVTS->CCDs->GCD.DIF_RMS_ASIP[0]);
	RMSASIP.push_back(SLVTS->CCDs->GCD.DIF_RMS_ASIP[1]);
	return RMSASIP;
}
std::vector< double > GET_SUM_RMSPSIP(CL_SLVTS* SLVTS){
	std::vector< double > RMSPSIP;
	RMSPSIP.push_back(SLVTS->CCDs->GCD.DIF_RMS_PSIP[0]);
	RMSPSIP.push_back(SLVTS->CCDs->GCD.DIF_RMS_PSIP[1]);
	return RMSPSIP;
}
//-----------------------------------------------------------------
//Getting Functions : CCD Info
//-----------------------------------------------------------------

namespace {
    template <class Elem, class Member>
    std::vector<Elem> GetCCDField(
        CL_CCDs const& CCDs, Member const& member
    ){
        std::vector<Elem> slice;
        slice.reserve(CCDs.CCD.size() + 1);

        for(std::vector<CL_CCD>::const_iterator ccd = CCDs.CCD.begin();
            ccd != CCDs.CCD.end(); ++ccd
        ){
            slice.push_back((*ccd).*member);
        }
        slice.push_back(CCDs.GCD.*member);

        return slice;
    }

    template <class Elem, class Member>
    std::vector<Elem> GetCCDField(
        CL_CCDs const& CCDs, Member const& member, std::size_t i
    ){
        std::vector<Elem> slice;
        slice.reserve(CCDs.CCD.size() + 1);

        for(std::vector<CL_CCD>::const_iterator ccd = CCDs.CCD.begin();
            ccd != CCDs.CCD.end(); ++ccd
        ){
            slice.push_back(((*ccd).*member)[i]);
        }
        slice.push_back((CCDs.GCD.*member)[i]);

        return slice;
    }

    template <class Elem, class Member>
    std::vector<Elem> GetCCDField(
        CL_CCDs const& CCDs, Member const& member, std::size_t i, std::size_t j
    ){
        std::vector<Elem> slice;
        slice.reserve(CCDs.CCD.size() + 1);

        for(std::vector<CL_CCD>::const_iterator ccd = CCDs.CCD.begin();
            ccd != CCDs.CCD.end(); ++ccd
        ){
            slice.push_back(((*ccd).*member)[i][j]);
        }
        slice.push_back((CCDs.GCD.*member)[i][j]);

        return slice;
    }
}

std::vector< int > GET_CCD_NUMREF(CL_SLVTS* SLVTS){
	return GetCCDField<int>(*SLVTS->CCDs, &CCDBase::NUM_REF);
}
std::vector< int > GET_CCD_NUMFIT(CL_SLVTS* SLVTS){
    return GetCCDField<int>(*SLVTS->CCDs, &CCDBase::NUM_FIT);
}
std::vector< std::vector< double > > GET_CCD_GPOS_L(CL_SLVTS* SLVTS){
    std::vector< std::vector< double > > CCDPOS(4);
    CCDPOS[0] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::GPOS_L, 0);
    CCDPOS[1] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::GPOS_L, 1);
    CCDPOS[2] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::GPOS_L, 2);
    CCDPOS[3] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::GPOS_L, 3);

    return CCDPOS;
}
std::vector< std::vector< double > > GET_CCD_GPOS_C(CL_SLVTS* SLVTS){
    std::vector< std::vector< double > > CCDPOS(4);
    CCDPOS[0] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::GPOS_C, 0);
    CCDPOS[1] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::GPOS_C, 1);
    CCDPOS[2] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::GPOS_C, 2);
    CCDPOS[3] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::GPOS_C, 3);

    return CCDPOS;
}
std::vector< std::vector< double > > GET_CCD_CR(CL_SLVTS* SLVTS){
    std::vector< std::vector< double > > CCDCR(4);
    CCDCR[0] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::CRPIX, 0);
    CCDCR[1] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::CRPIX, 1);
    CCDCR[2].assign(CCDCR[0].size(), SLVTS->APRM->CRVAL[0]);
    CCDCR[3].assign(CCDCR[0].size(), SLVTS->APRM->CRVAL[1]);

    return CCDCR;
}
std::vector< std::vector< double > > GET_CCD_OA(CL_SLVTS* SLVTS){
    std::vector< std::vector< double > > CCDOA(2);
    CCDOA[0] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::OAPIX, 0);
    CCDOA[1] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::OAPIX, 1);

    return CCDOA;
}
std::vector< std::vector< double > > GET_CCD_CD(CL_SLVTS* SLVTS){
    std::vector< std::vector< double > > CCDCD(4);
    CCDCD[0] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::CD, 0, 0);
    CCDCD[1] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::CD, 0, 1);
    CCDCD[2] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::CD, 1, 0);
    CCDCD[3] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::CD, 1, 1);

    return CCDCD;
}
std::vector< std::vector< double > > GET_CCD_ERRSIP(CL_SLVTS* SLVTS){
    std::vector< std::vector< double > >  CCDERR(6);
    CCDERR[0] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_AVE_ASIP, 0);
    CCDERR[1] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_RMS_ASIP, 0);
    CCDERR[2] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_MAX_ASIP, 0);
    CCDERR[3] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_AVE_ASIP, 1);
    CCDERR[4] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_RMS_ASIP, 1);
    CCDERR[5] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_MAX_ASIP, 1);

    return CCDERR;
}
std::vector< std::vector< double > > GET_CCD_ERRPSIP(CL_SLVTS* SLVTS){
    std::vector< std::vector< double > >  CCDERR(6);
	CCDERR[0] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_AVE_PSIP, 0);
	CCDERR[1] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_RMS_PSIP, 0);
	CCDERR[2] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_MAX_PSIP, 0);
	CCDERR[3] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_AVE_PSIP, 1);
	CCDERR[4] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_RMS_PSIP, 1);
	CCDERR[5] = GetCCDField<double>(*SLVTS->CCDs, &CCDBase::DIF_MAX_PSIP, 1);

    return CCDERR;
}
std::vector< int > GET_CCD_ORDERSIP(CL_SLVTS* SLVTS){
    return std::vector<int>(SLVTS->CCDs->CCD.size() + 1, SLVTS->APRM->ORDER_ASIP);
}
std::vector< int > GET_CCD_ORDERPSIP(CL_SLVTS* SLVTS){
    return std::vector<int>(SLVTS->CCDs->CCD.size() + 1, SLVTS->APRM->ORDER_PSIP);
}
std::vector< std::vector< double > > GET_CCD_COEFSIPA(CL_SLVTS* SLVTS){
    std::vector< Polynomial2D::CoeffVector > coeffs;
    for(std::vector<CL_CCD>::iterator ccd = SLVTS->CCDs->CCD.begin();
        ccd != SLVTS->CCDs->CCD.end(); ++ccd
    ){
        coeffs.push_back(ccd->ASIP[0].getCoeffVector());
    }
    coeffs.push_back(SLVTS->CCDs->GCD.ASIP[0].getCoeffVector());

    // transpose coeffs to make CCDCOEF

    std::vector< std::vector< double > >  CCDCOEF(coeffs.front().length);
    for(std::size_t ORDER = 0; ORDER < CCDCOEF.size(); ++ORDER){
        std::vector< double >& COEF = CCDCOEF[ORDER];
        for(std::size_t ID = 0; ID < coeffs.size(); ++ID){
            COEF.push_back(coeffs[ID][ORDER]);
        }
    }
    return CCDCOEF;
}
std::vector< std::vector< double > > GET_CCD_COEFSIPB(CL_SLVTS* SLVTS){
    std::vector< Polynomial2D::CoeffVector > coeffs;
    for(std::vector<CL_CCD>::iterator ccd = SLVTS->CCDs->CCD.begin();
        ccd != SLVTS->CCDs->CCD.end(); ++ccd
    ){
        coeffs.push_back(ccd->ASIP[1].getCoeffVector());
    }
    coeffs.push_back(SLVTS->CCDs->GCD.ASIP[1].getCoeffVector());

    // transpose coeffs to make CCDCOEF

    std::vector< std::vector< double > >  CCDCOEF(coeffs.front().length);
    for(std::size_t ORDER = 0; ORDER < CCDCOEF.size(); ++ORDER){
        std::vector< double >& COEF = CCDCOEF[ORDER];
        for(std::size_t ID = 0; ID < coeffs.size(); ++ID){
            COEF.push_back(coeffs[ID][ORDER]);
        }
    }
    return CCDCOEF;
}
std::vector< std::vector< double > > GET_CCD_COEFPSIPA(CL_SLVTS* SLVTS){
    std::vector< Polynomial2D::CoeffVector > coeffs;
    for(std::vector<CL_CCD>::iterator ccd = SLVTS->CCDs->CCD.begin();
        ccd != SLVTS->CCDs->CCD.end(); ++ccd
    ){
        coeffs.push_back(ccd->PSIP[0].getCoeffVector());
    }
    coeffs.push_back(SLVTS->CCDs->GCD.PSIP[0].getCoeffVector());

    // transpose coeffs to make CCDCOEF

    std::vector< std::vector< double > >  CCDCOEF(coeffs.front().length);
    for(std::size_t ORDER = 0; ORDER < CCDCOEF.size(); ++ORDER){
        std::vector< double >& COEF = CCDCOEF[ORDER];
        for(std::size_t ID = 0; ID < coeffs.size(); ++ID){
            COEF.push_back(coeffs[ID][ORDER]);
        }
    }
    return CCDCOEF;
}
std::vector< std::vector< double > > GET_CCD_COEFPSIPB(CL_SLVTS* SLVTS){
    std::vector< Polynomial2D::CoeffVector > coeffs;
    for(std::vector<CL_CCD>::iterator ccd = SLVTS->CCDs->CCD.begin();
        ccd != SLVTS->CCDs->CCD.end(); ++ccd
    ){
        coeffs.push_back(ccd->PSIP[1].getCoeffVector());
    }
    coeffs.push_back(SLVTS->CCDs->GCD.PSIP[1].getCoeffVector());

    // transpose coeffs to make CCDCOEF

    std::vector< std::vector< double > >  CCDCOEF(coeffs.front().length);
    for(std::size_t ORDER = 0; ORDER < CCDCOEF.size(); ++ORDER){
        std::vector< double >& COEF = CCDCOEF[ORDER];
        for(std::size_t ID = 0; ID < coeffs.size(); ++ID){
            COEF.push_back(coeffs[ID][ORDER]);
        }
    }
    return CCDCOEF;
}

//-----------------------------------------------------------------
//Getting Functions : REF Info
//-----------------------------------------------------------------
std::vector< int > GET_REF_CID(CL_SLVTS* SLVTS){
    std::vector< int > CID;
    for(std::vector<CL_REF>::const_iterator r = SLVTS->REFs->REF.begin();
        r != SLVTS->REFs->REF.end(); ++r
    ){
        CID.push_back(r->ID_CCD);
    }
    return CID;
}
std::vector< int > GET_REF_FLAG(CL_SLVTS* SLVTS){
    std::vector< int > FLAG;
    for(std::vector<CL_REF>::const_iterator r = SLVTS->REFs->REF.begin();
        r != SLVTS->REFs->REF.end(); ++r
    ){
        FLAG.push_back(r->FLAG_OBJ);
    }
    return FLAG;
}


namespace {
    template <class CL_REFMember>
    std::vector< std::vector< double > >
    GetRefPos(CL_SLVTS* SLVTS, CL_REFMember const& member)
    {
        std::vector< double > X,Y;
        std::vector< std::vector< double > > XY;
        for(std::vector<CL_REF>::const_iterator r = SLVTS->REFs->REF.begin();
            r != SLVTS->REFs->REF.end(); ++r
        ){
            X.push_back(((*r).*member)[0]);
            Y.push_back(((*r).*member)[1]);
        }
        XY.push_back(X);
        XY.push_back(Y);

        return XY;
    }
}


//POS_CELESTIAL
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_RADEC(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_RADEC);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMWLD(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_IMWLD);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMPIX_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_IMPIX_L);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_IMPIX_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_IMPIX_G);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_CRPIX_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_CRPIX_L);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_CRPIX_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_CRPIX_G);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_LOCAL_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_LOCAL_L);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_LOCAL_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_LOCAL_G);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_CRPIX_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_PSIP_CRPIX_L);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_CRPIX_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_PSIP_CRPIX_G);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_LOCAL_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_PSIP_LOCAL_L);
}
std::vector< std::vector< double > > GET_REF_POS_CELESTIAL_PSIP_LOCAL_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_CELESTIAL_PSIP_LOCAL_G);
}
//POS_DETECTED
std::vector< std::vector< double > > GET_REF_POS_DETECTED_LOCAL_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_LOCAL_L);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_LOCAL_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_LOCAL_G);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_CRPIX_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_CRPIX_L);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_CRPIX_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_CRPIX_G);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMPIX_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_IMPIX_L);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMPIX_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_IMPIX_G);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMWLD_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_IMWLD_L);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_IMWLD_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_IMWLD_G);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_RADEC_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_RADEC_L);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_RADEC_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_RADEC_G);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_CRPIX_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_ASIP_CRPIX_L);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_CRPIX_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_ASIP_CRPIX_G);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMPIX_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_ASIP_IMPIX_L);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMPIX_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_ASIP_IMPIX_G);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMWLD_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_ASIP_IMWLD_L);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_IMWLD_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_ASIP_IMWLD_G);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_RADEC_L(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_ASIP_RADEC_L);
}
std::vector< std::vector< double > > GET_REF_POS_DETECTED_ASIP_RADEC_G(CL_SLVTS* SLVTS){
    return GetRefPos(SLVTS, &CL_REF::POS_DETECTED_ASIP_RADEC_G);
}
std::vector< std::vector< double > > GET_REF_DIFF(CL_SLVTS* SLVTS){
    std::vector< double > DIFFAX,DIFFAY,DIFFPX,DIFFPY;
    std::vector< std::vector< double > > DIFF;
    for(std::vector<CL_REF>::const_iterator r = SLVTS->REFs->REF.begin();
        r != SLVTS->REFs->REF.end(); ++r
    ){
        DIFFAX.push_back(r->DIFF_ASIP[0]);
        DIFFAY.push_back(r->DIFF_ASIP[1]);
        DIFFPX.push_back(r->DIFF_PSIP[0]);
        DIFFPY.push_back(r->DIFF_PSIP[1]);
    }
    DIFF.push_back(DIFFAX);
    DIFF.push_back(DIFFAY);
    DIFF.push_back(DIFFPX);
    DIFF.push_back(DIFFPY);

    return DIFF;
}
std::vector< double > GET_REF_CAMERAJACOPSIP(CL_SLVTS* SLVTS){
    std::vector< double > JACO;
    for(std::vector<CL_REF>::const_iterator r = SLVTS->REFs->REF.begin();
        r != SLVTS->REFs->REF.end(); ++r
    ){
         JACO.push_back(r->CAMERA_JACO);
    }

    return JACO;
}

} // namespace tansip
}} // namespace hsc::meas
