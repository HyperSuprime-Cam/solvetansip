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
	return SLVTS->APRM->NUM_CCD;
}
int GET_SUM_NUMFIT(CL_SLVTS* SLVTS){
	return SLVTS->APRM->NUM_FIT;
}
std::vector< double > GET_SUM_CRPIX(CL_SLVTS* SLVTS){
	std::vector< double > CRPIX;
	CRPIX.push_back(SLVTS->APRM->CRPIX[0]);
	CRPIX.push_back(SLVTS->APRM->CRPIX[1]);
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
	OAPIX.push_back(SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].OAPIX[0]);
	OAPIX.push_back(SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].OAPIX[1]);
	return OAPIX;
}
std::vector< double > GET_SUM_CD(CL_SLVTS* SLVTS){
	std::vector< double > CD;
	CD.push_back(SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].CD[0][0]);
	CD.push_back(SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].CD[0][1]);
	CD.push_back(SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].CD[1][0]);
	CD.push_back(SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].CD[1][1]);
	return CD;
}
double GET_SUM_ANGLE(CL_SLVTS* SLVTS){
	return SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].ANGLE;
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
	GCD[0]=SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].CD[0][0];
	GCD[1]=SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].CD[0][1];
	GCD[2]=SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].CD[1][0];
	GCD[3]=SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].CD[1][1];
	GANG  =SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].ANGLE;

	CD_COR.push_back(cos(-GANG)*GCD[0]-sin(-GANG)*GCD[2]);
	CD_COR.push_back(cos(-GANG)*GCD[1]-sin(-GANG)*GCD[3]);
	CD_COR.push_back(sin(-GANG)*GCD[0]+cos(-GANG)*GCD[2]);
	CD_COR.push_back(sin(-GANG)*GCD[1]+cos(-GANG)*GCD[3]);
	return CD_COR;
}
std::vector< double > GET_SUM_RMSASIP(CL_SLVTS* SLVTS){
	std::vector< double > RMSASIP;
	RMSASIP.push_back(SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_RMS_ASIP[0]);
	RMSASIP.push_back(SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_RMS_ASIP[1]);
	return RMSASIP;
}
std::vector< double > GET_SUM_RMSPSIP(CL_SLVTS* SLVTS){
	std::vector< double > RMSPSIP;
	RMSPSIP.push_back(SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_RMS_PSIP[0]);
	RMSPSIP.push_back(SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_RMS_PSIP[1]);
	return RMSPSIP;
}
//-----------------------------------------------------------------
//Getting Functions : CCD Info
//-----------------------------------------------------------------
std::vector< int > GET_CCD_ID(CL_SLVTS* SLVTS){
    int ID;
    std::vector< int > CID;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++)
    CID.push_back(SLVTS->CCDs->CCD[ID].ID);

    return CID;
}
std::vector< int > GET_CCD_NUMREF(CL_SLVTS* SLVTS){
    int ID;
    std::vector< int > RNUM;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++)
    RNUM.push_back(SLVTS->CCDs->CCD[ID].NUM_REF);

    return RNUM;
}
std::vector< int > GET_CCD_NUMFIT(CL_SLVTS* SLVTS){
    int ID;
    std::vector< int > FNUM;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++)
    FNUM.push_back(SLVTS->CCDs->CCD[ID].NUM_FIT);

    return FNUM;
}
std::vector< std::vector< double > > GET_CCD_GPOS_L(CL_SLVTS* SLVTS){
    int ID;
    std::vector< double > POSX,POSY,POST,POSD;
    std::vector< std::vector< double > > CCDPOS;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++){
	POSX.push_back(SLVTS->CCDs->CCD[ID].GPOS_L[0]);
	POSY.push_back(SLVTS->CCDs->CCD[ID].GPOS_L[1]);
	POST.push_back(SLVTS->CCDs->CCD[ID].GPOS_L[2]);
	POSD.push_back(SLVTS->CCDs->CCD[ID].GPOS_L[3]);
    }
    CCDPOS.push_back(POSX);
    CCDPOS.push_back(POSY);
    CCDPOS.push_back(POST);
    CCDPOS.push_back(POSD);

    return CCDPOS;
}
std::vector< std::vector< double > > GET_CCD_GPOS_C(CL_SLVTS* SLVTS){
    int ID;
    std::vector< double > POSX,POSY,POST,POSD;
    std::vector< std::vector< double > > CCDPOS;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++){
	POSX.push_back(SLVTS->CCDs->CCD[ID].GPOS_C[0]);
	POSY.push_back(SLVTS->CCDs->CCD[ID].GPOS_C[1]);
	POST.push_back(SLVTS->CCDs->CCD[ID].GPOS_C[2]);
	POSD.push_back(SLVTS->CCDs->CCD[ID].GPOS_C[3]);
    }
    CCDPOS.push_back(POSX);
    CCDPOS.push_back(POSY);
    CCDPOS.push_back(POST);
    CCDPOS.push_back(POSD);

    return CCDPOS;
}
std::vector< std::vector< double > > GET_CCD_CR(CL_SLVTS* SLVTS){
    int ID;
    std::vector< double > CRP1,CRP2,CRV1,CRV2;
    std::vector< std::vector< double > > CCDCR;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++){
	CRP1.push_back(*SLVTS->CCDs->CCD[ID].CRPIX[0]);
	CRP2.push_back(*SLVTS->CCDs->CCD[ID].CRPIX[1]);
	CRV1.push_back(SLVTS->APRM->CRVAL[0]);
	CRV2.push_back(SLVTS->APRM->CRVAL[1]);
    }
	CCDCR.push_back(CRP1);
	CCDCR.push_back(CRP2);
	CCDCR.push_back(CRV1);
	CCDCR.push_back(CRV2);

    return CCDCR;
}
std::vector< std::vector< double > > GET_CCD_OA(CL_SLVTS* SLVTS){
    int ID;
    std::vector< double > OAP1,OAP2;
    std::vector< std::vector< double > > CCDOA;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++){
	OAP1.push_back(SLVTS->CCDs->CCD[ID].OAPIX[0]);
	OAP2.push_back(SLVTS->CCDs->CCD[ID].OAPIX[1]);
    }
	CCDOA.push_back(OAP1);
	CCDOA.push_back(OAP2);

    return CCDOA;
}
std::vector< std::vector< double > > GET_CCD_CD(CL_SLVTS* SLVTS){
    int ID;
    std::vector< double > CD11,CD12,CD21,CD22;
    std::vector< std::vector< double > > CCDCD;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++){
	CD11.push_back(SLVTS->CCDs->CCD[ID].CD[0][0]);
	CD12.push_back(SLVTS->CCDs->CCD[ID].CD[0][1]);
	CD21.push_back(SLVTS->CCDs->CCD[ID].CD[1][0]);
	CD22.push_back(SLVTS->CCDs->CCD[ID].CD[1][1]);
    }
	CCDCD.push_back(CD11);
	CCDCD.push_back(CD12);
	CCDCD.push_back(CD21);
	CCDCD.push_back(CD22);

    return CCDCD;
}
std::vector< std::vector< double > > GET_CCD_ERRSIP(CL_SLVTS* SLVTS){
    int ID;
    std::vector< double > ERRXA,ERRXB,ERRXC,ERRYA,ERRYB,ERRYC;
    std::vector< std::vector< double > >  CCDERR;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++){
	ERRXA.push_back(SLVTS->CCDs->CCD[ID].DIF_AVE_ASIP[0]);
	ERRXB.push_back(SLVTS->CCDs->CCD[ID].DIF_RMS_ASIP[0]);
	ERRXC.push_back(SLVTS->CCDs->CCD[ID].DIF_MAX_ASIP[0]);
	ERRYA.push_back(SLVTS->CCDs->CCD[ID].DIF_AVE_ASIP[1]);
	ERRYB.push_back(SLVTS->CCDs->CCD[ID].DIF_RMS_ASIP[1]);
	ERRYC.push_back(SLVTS->CCDs->CCD[ID].DIF_MAX_ASIP[1]);
    }
	CCDERR.push_back(ERRXA);
	CCDERR.push_back(ERRXB);
	CCDERR.push_back(ERRXC);
	CCDERR.push_back(ERRYA);
	CCDERR.push_back(ERRYB);
	CCDERR.push_back(ERRYC);

    return CCDERR;
}
std::vector< std::vector< double > > GET_CCD_ERRPSIP(CL_SLVTS* SLVTS){
    int ID;
    std::vector< double > ERRXA,ERRXB,ERRXC,ERRYA,ERRYB,ERRYC;
    std::vector< std::vector< double > >  CCDERR;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++){
	ERRXA.push_back(SLVTS->CCDs->CCD[ID].DIF_AVE_PSIP[0]);
	ERRXB.push_back(SLVTS->CCDs->CCD[ID].DIF_RMS_PSIP[0]);
	ERRXC.push_back(SLVTS->CCDs->CCD[ID].DIF_MAX_PSIP[0]);
	ERRYA.push_back(SLVTS->CCDs->CCD[ID].DIF_AVE_PSIP[1]);
	ERRYB.push_back(SLVTS->CCDs->CCD[ID].DIF_RMS_PSIP[1]);
	ERRYC.push_back(SLVTS->CCDs->CCD[ID].DIF_MAX_PSIP[1]);
    }
	CCDERR.push_back(ERRXA);
	CCDERR.push_back(ERRXB);
	CCDERR.push_back(ERRXC);
	CCDERR.push_back(ERRYA);
	CCDERR.push_back(ERRYB);
	CCDERR.push_back(ERRYC);

    return CCDERR;
}
std::vector< int > GET_CCD_ORDERSIP(CL_SLVTS* SLVTS){
    int ID;
    std::vector< int > SORD;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++)
    SORD.push_back(SLVTS->APRM->ORDER_ASIP);

    return SORD;
}
std::vector< int > GET_CCD_ORDERPSIP(CL_SLVTS* SLVTS){
    int ID;
    std::vector< int > PORD;
    for(ID=0;ID<SLVTS->APRM->NUM_CCD+1;ID++)
    PORD.push_back(SLVTS->APRM->ORDER_PSIP);

    return PORD;
}
std::vector< std::vector< double > > GET_CCD_COEFSIPA(CL_SLVTS* SLVTS){
    std::vector< Polynomial2D::CoeffVector > coeffs(SLVTS->APRM->NUM_CCD + 1);
    for(std::size_t ID = 0; ID < coeffs.size(); ++ID){
        coeffs[ID] = SLVTS->CCDs->CCD[ID].ASIP[0].getCoeffVector();
    }

    // transpose coeffs => CCDCOEF

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
    std::vector< Polynomial2D::CoeffVector > coeffs(SLVTS->APRM->NUM_CCD + 1);
    for(std::size_t ID = 0; ID < coeffs.size(); ++ID){
        coeffs[ID] = SLVTS->CCDs->CCD[ID].ASIP[1].getCoeffVector();
    }

    // transpose coeffs => CCDCOEF

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
    std::vector< Polynomial2D::CoeffVector > coeffs(SLVTS->APRM->NUM_CCD + 1);
    for(std::size_t ID = 0; ID < coeffs.size(); ++ID){
        coeffs[ID] = SLVTS->CCDs->CCD[ID].PSIP[0].getCoeffVector();
    }

    // transpose coeffs => CCDCOEF

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
    std::vector< Polynomial2D::CoeffVector > coeffs(SLVTS->APRM->NUM_CCD + 1);
    for(std::size_t ID = 0; ID < coeffs.size(); ++ID){
        coeffs[ID] = SLVTS->CCDs->CCD[ID].PSIP[1].getCoeffVector();
    }

    // transpose coeffs => CCDCOEF

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
