//------------------------------------------------------------
//SLVTS_LSST.cc
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include "hsc/meas/tansip/SLVTS_LSST.h"
#include "SLVTSStateImpl.h"
#include "Utility.h"

#include <vector>
#include <iostream>

#include <boost/make_shared.hpp>


namespace hsc { namespace meas {
namespace tansip {

namespace dafbase  = lsst::daf::base;
namespace afwGeom  = lsst::afw::geom;
namespace afwImage = lsst::afw::image;

namespace {
    void SetMetadataOfCCD(
        dafbase::PropertySet::Ptr const& meta,
        AnaParam                  const* APRM,
        CL_GCD                    const& global,
        CCDBase                   const& CCD,
        int                              cid)
    {
        meta->add(fmt("ST_C%03d_NUM_REF"    , cid), CCD.NUM_REF);
        meta->add(fmt("ST_C%03d_NUM_FIT"    , cid), CCD.NUM_FIT);
        meta->add(fmt("ST_C%03d_NUM_REJ"    , cid), CCD.NUM_REJ);
        meta->add(fmt("ST_C%03d_GPOS_LX"    , cid), CCD.GPOS_L[0]);
        meta->add(fmt("ST_C%03d_GPOS_LY"    , cid), CCD.GPOS_L[1]);
        meta->add(fmt("ST_C%03d_GPOS_LT"    , cid), CCD.GPOS_L[2]);
        meta->add(fmt("ST_C%03d_GPOS_LTD"   , cid), CCD.GPOS_L[3]);
        meta->add(fmt("ST_C%03d_GPOS_CX"    , cid), CCD.GPOS_C[0]);
        meta->add(fmt("ST_C%03d_GPOS_CY"    , cid), CCD.GPOS_C[1]);
        meta->add(fmt("ST_C%03d_GPOS_CT"    , cid), CCD.GPOS_C[2]);
        meta->add(fmt("ST_C%03d_GPOS_CTD"   , cid), CCD.GPOS_C[3]);
        meta->add(fmt("ST_C%03d_CRPIX1"     , cid), CCD.CRPIX[0]);
        meta->add(fmt("ST_C%03d_CRPIX2"     , cid), CCD.CRPIX[1]);
        meta->add(fmt("ST_C%03d_CRVAL1"     , cid), global.CRVAL[0]);
        meta->add(fmt("ST_C%03d_CRVAL2"     , cid), global.CRVAL[1]);
        meta->add(fmt("ST_C%03d_CD1_1"      , cid), CCD.CD[0][0]);
        meta->add(fmt("ST_C%03d_CD1_2"      , cid), CCD.CD[0][1]);
        meta->add(fmt("ST_C%03d_CD2_1"      , cid), CCD.CD[1][0]);
        meta->add(fmt("ST_C%03d_CD2_2"      , cid), CCD.CD[1][1]);
        meta->add(fmt("ST_C%03d_InvCD1_1"   , cid), CCD.InvCD[0][0]);
        meta->add(fmt("ST_C%03d_InvCD1_2"   , cid), CCD.InvCD[0][1]);
        meta->add(fmt("ST_C%03d_InvCD2_1"   , cid), CCD.InvCD[1][0]);
        meta->add(fmt("ST_C%03d_InvCD2_2"   , cid), CCD.InvCD[1][1]);
        meta->add(fmt("ST_C%03d_OREDER_ASIP", cid), APRM->ORDER_ASIP);

        for(int i = 0; i < APRM->ORDER_ASIP+1; ++i){
            for(int j = 0; j < APRM->ORDER_ASIP+1-i; ++j){
                meta->add(fmt("ST_C%03d_ASIP_X_%d_%d" ,cid,i,j),
                    CCD.ASIP[0].coeff(i,j));
            }
        }

        for(int i = 0; i < APRM->ORDER_ASIP+1; ++i){
            for(int j = 0; j < APRM->ORDER_ASIP+1-i; ++j){
                meta->add(fmt("ST_C%03d_ASIP_Y_%d_%d" ,cid,i,j),
                    CCD.ASIP[1].coeff(i,j));
            }
        }
        meta->add(fmt("ST_C%03d_ASIP_DIF_AVE_X", cid), CCD.DIF_AVE_ASIP[0]);
        meta->add(fmt("ST_C%03d_ASIP_DIF_AVE_Y", cid), CCD.DIF_AVE_ASIP[1]);
        meta->add(fmt("ST_C%03d_ASIP_DIF_RMS_X", cid), CCD.DIF_RMS_ASIP[0]);
        meta->add(fmt("ST_C%03d_ASIP_DIF_RMS_Y", cid), CCD.DIF_RMS_ASIP[1]);
        meta->add(fmt("ST_C%03d_ASIP_DIF_MAX_X", cid), CCD.DIF_MAX_ASIP[0]);
        meta->add(fmt("ST_C%03d_ASIP_DIF_MAX_Y", cid), CCD.DIF_MAX_ASIP[1]);

        meta->add(fmt("ST_C%03d_ORDER_PSIP" , cid), APRM->ORDER_PSIP);
        for(int i = 0; i < APRM->ORDER_PSIP+1; ++i){
            for(int j = 0; j < APRM->ORDER_PSIP+1-i; ++j){
                meta->add(fmt("ST_C%03d_PSIP_X_%d_%d" ,cid,i,j),
                    CCD.PSIP[0].coeff(i,j));
            }
        }
        for(int i = 0; i < APRM->ORDER_PSIP+1; ++i){
            for(int j = 0; j < APRM->ORDER_PSIP+1-i; ++j){
                meta->add(fmt("ST_C%03d_PSIP_Y_%d_%d" ,cid,i,j),
                    CCD.PSIP[1].coeff(i,j));
            }
        }
        meta->add(fmt("ST_C%03d_PSIP_DIF_AVE_X", cid), CCD.DIF_AVE_PSIP[0]);
        meta->add(fmt("ST_C%03d_PSIP_DIF_AVE_Y", cid), CCD.DIF_AVE_PSIP[1]);
        meta->add(fmt("ST_C%03d_PSIP_DIF_RMS_X", cid), CCD.DIF_RMS_PSIP[0]);
        meta->add(fmt("ST_C%03d_PSIP_DIF_RMS_Y", cid), CCD.DIF_RMS_PSIP[1]);
        meta->add(fmt("ST_C%03d_PSIP_DIF_MAX_X", cid), CCD.DIF_MAX_PSIP[0]);
        meta->add(fmt("ST_C%03d_PSIP_DIF_MAX_Y", cid), CCD.DIF_MAX_PSIP[1]);
    }
}


lsst::daf::base::PropertySet::Ptr
GET_METADATA(SLVTSState const& handle, dafbase::PropertySet::Ptr const& meta_in)
{
    SLVTSStateImpl SLVTS(handle);

    dafbase::PropertySet::Ptr meta = meta_in;
    if(!meta){
        meta = boost::make_shared<dafbase::PropertySet>();
    }

    meta->add("ST_A_MODE_CR"    , SLVTS.APRM->MODE_CR);
    meta->add("ST_A_MODE_REJ"   , SLVTS.APRM->MODE_REJ);
    meta->add("ST_A_MODE_CCDPOS", SLVTS.APRM->MODE_CCDPOS);
    meta->add("ST_A_NUM_CCD"    , (int)SLVTS.CCDs->CCD.size());
    meta->add("ST_A_NUM_FIT"    , SLVTS.CCDs->GCD.NUM_FIT);
    meta->add("ST_A_NUM_REJ"    , SLVTS.CCDs->GCD.NUM_REJ);
    meta->add("ST_A_CRPIX1"     , SLVTS.CCDs->GCD.CRPIX[0]);
    meta->add("ST_A_CRPIX2"     , SLVTS.CCDs->GCD.CRPIX[1]);
    meta->add("ST_A_CRVAL1"     , SLVTS.CCDs->GCD.CRVAL[0]);
    meta->add("ST_A_CRVAL2"     , SLVTS.CCDs->GCD.CRVAL[1]);
    meta->add("ST_A_SIGMA_CLIP" , SLVTS.APRM->SIGMA_CLIP);

/*
double VALUE;
VALUE=meta->getAsDouble("ST_G_MAX_CRPIX_G_R");
cout<<scientific<<setprecision(6)<<"R : "<<SLVTS.CCDs->MAX_CRPIX_G_R<<" "<<VALUE<<endl;
*/
    for(int CID = 0; CID < (int)SLVTS.CCDs->CCD.size(); ++CID){
        SetMetadataOfCCD(
            meta, SLVTS.APRM, SLVTS.CCDs->GCD, SLVTS.CCDs->CCD[CID], CID
        );
    }
    SetMetadataOfCCD(
        meta, SLVTS.APRM, SLVTS.CCDs->GCD, SLVTS.CCDs->GCD, SLVTS.CCDs->CCD.size()
    );

//Summary
    meta->add("sip_residuals_ave_x" , SLVTS.CCDs->GCD.DIF_AVE_ASIP[0]);
    meta->add("sip_residuals_ave_y" , SLVTS.CCDs->GCD.DIF_AVE_ASIP[1]);
    meta->add("sip_residuals_rms_x" , SLVTS.CCDs->GCD.DIF_RMS_ASIP[0]);
    meta->add("sip_residuals_rms_y" , SLVTS.CCDs->GCD.DIF_RMS_ASIP[1]);
    meta->add("psip_residuals_ave_x", SLVTS.CCDs->GCD.DIF_AVE_PSIP[0]);
    meta->add("psip_residuals_ave_y", SLVTS.CCDs->GCD.DIF_AVE_PSIP[1]);
    meta->add("psip_residuals_rms_x", SLVTS.CCDs->GCD.DIF_RMS_PSIP[0]);
    meta->add("psip_residuals_rms_y", SLVTS.CCDs->GCD.DIF_RMS_PSIP[1]);

    return meta;
}


void SHOW_METADATA(SLVTSState const& handle, dafbase::PropertySet::Ptr const& meta){
    SLVTSStateImpl SLVTS(handle);
    int const GL = (int)SLVTS.CCDs->CCD.size();

    if(SLVTS.APRM->VERBOSITY >= 1){
        #define SHOW(Type, key) \
            std::cout << key << " : " << meta->getAs##Type(key) << std::endl
        std::cout << "--- SHOW metadata ---" << std::endl;
        SHOW(String, "ST_A_MODE_CR"                    );
        SHOW(Int   , "ST_A_NUM_CCD"                    );
        SHOW(Double, fmt("ST_C%03d_PSIP_DIF_AVE_X", GL));
        SHOW(Double, fmt("ST_C%03d_PSIP_DIF_AVE_Y", GL));
        SHOW(Double, fmt("ST_C%03d_PSIP_DIF_RMS_X", GL));
        SHOW(Double, fmt("ST_C%03d_PSIP_DIF_RMS_Y", GL));
        SHOW(Double, fmt("ST_C%03d_PSIP_DIF_MAX_X", GL));
        SHOW(Double, fmt("ST_C%03d_PSIP_DIF_MAX_Y", GL));
        SHOW(Double, "sip_residuals_ave_x"             );
        SHOW(Double, "sip_residuals_ave_y"             );
        SHOW(Double, "sip_residuals_rms_x"             );
        SHOW(Double, "sip_residuals_rms_y"             );
        SHOW(Double, "psip_residuals_ave_x"            );
        SHOW(Double, "psip_residuals_ave_y"            );
        SHOW(Double, "psip_residuals_rms_x"            );
        SHOW(Double, "psip_residuals_rms_y"            );
        #undef SHOW
    }
}


namespace {
    lsst::afw::image::TanWcs::Ptr toTanWcs(
        CCDBase             const& CCD,
        CL_GCD              const& global
    ){
        afwGeom::PointD crpix = afwGeom::PointD(CCD   .CRPIX[0], CCD   .CRPIX[1]);
        afwGeom::PointD crval = afwGeom::PointD(global.CRVAL[0], global.CRVAL[1]);

        Eigen::Matrix2d cdMatrix;
        cdMatrix << CCD.CD[0][0],CCD.CD[0][1],CCD.CD[1][0],CCD.CD[1][1];

        int const OAS = CCD.ASIP[0].getDegree();
        int const OPS = CCD.PSIP[0].getDegree();
        Eigen::MatrixXd sipA  = Eigen::MatrixXd::Zero(OAS+1,OAS+1);
        Eigen::MatrixXd sipB  = Eigen::MatrixXd::Zero(OAS+1,OAS+1);
        Eigen::MatrixXd sipAp = Eigen::MatrixXd::Zero(OPS+1,OPS+1);
        Eigen::MatrixXd sipBp = Eigen::MatrixXd::Zero(OPS+1,OPS+1);

        for(int i = 0; i < OAS+1; ++i)
        for(int j = 0; j < OAS+1; ++j)
        if(i+j < OAS+1){
            sipA(i,j)=CCD.ASIP[0].coeff(i,j);
            sipB(i,j)=CCD.ASIP[1].coeff(i,j);
        }else{
            sipA(i,j)=0.0;
            sipB(i,j)=0.0;
        }
        for(int i = 0; i < OPS+1; ++i)
        for(int j = 0; j < OPS+1; ++j)
        if(i+j<OPS+1){
            sipAp(i,j)=CCD.PSIP[0].coeff(i,j);
            sipBp(i,j)=CCD.PSIP[1].coeff(i,j);
        }else{
            sipAp(i,j)=0.0;
            sipBp(i,j)=0.0;
        }

        return boost::make_shared<afwImage::TanWcs>(crval,crpix,cdMatrix,sipA,sipB,sipAp,sipBp);
    }
}


std::vector <lsst::afw::image::TanWcs::Ptr> GET_TANWCS(SLVTSState const& handle)
{
    SLVTSStateImpl SLVTS(handle);
    std::vector <lsst::afw::image::TanWcs::Ptr> V_TanWcs;

    for(std::vector<CL_CCD>::iterator ccd = SLVTS.CCDs->CCD.begin();
        ccd != SLVTS.CCDs->CCD.end(); ++ccd
    ){
        V_TanWcs.push_back(toTanWcs(*ccd, SLVTS.CCDs->GCD));
    }
    V_TanWcs.push_back(toTanWcs(SLVTS.CCDs->GCD, SLVTS.CCDs->GCD));

    return V_TanWcs;
}

} // namespace tansip
}} // namespace hsc::meas
