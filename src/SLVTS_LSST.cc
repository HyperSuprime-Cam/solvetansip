//------------------------------------------------------------
//SLVTS_LSST.cc
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

#include"hsc/meas/tansip/SLVTS_LSST.h"
using namespace std;
namespace dafbase  = lsst::daf::base;
namespace afwGeom  = lsst::afw::geom;
namespace afwImage = lsst::afw::image;

dafbase::PropertySet::Ptr SET_EMPTYMETADATA(){
	dafbase::PropertySet::Ptr meta(new dafbase::PropertySet);
	return meta;
}
void SET_METADATA(std::vector< CL_SLVTS* > VSLVTS, dafbase::PropertySet::Ptr &meta){
	CL_SLVTS* SLVTS;
	SLVTS=VSLVTS[0];

	meta->add("ST_A_MODE_CR"    ,SLVTS->APRM->MODE_CR);
	meta->add("ST_A_MODE_REJ"   ,SLVTS->APRM->MODE_REJ);
	meta->add("ST_A_MODE_CCDPOS",SLVTS->APRM->MODE_CCDPOS);
	meta->add("ST_A_NUM_CCD"    ,SLVTS->APRM->NUM_CCD);
	meta->add("ST_A_NUM_REF"    ,SLVTS->APRM->NUM_REF);
	meta->add("ST_A_NUM_FIT"    ,SLVTS->APRM->NUM_FIT);
        meta->add("ST_A_NUM_REJ"    ,SLVTS->APRM->NUM_REJ);
        meta->add("ST_A_CRPIX1"     ,SLVTS->APRM->CRPIX[0]);
	meta->add("ST_A_CRPIX2"     ,SLVTS->APRM->CRPIX[1]);
	meta->add("ST_A_CRVAL1"     ,SLVTS->APRM->CRVAL[0]);
	meta->add("ST_A_CRVAL2"     ,SLVTS->APRM->CRVAL[1]);
        meta->add("ST_A_SIGMA_CLIP" ,SLVTS->APRM->SIGMA_CLIP);
 	meta->add("ST_G_MAX_CRPIX_G_R",SLVTS->CCDs->MAX_CRPIX_G_R);

	int CID,i,j,ij;
	char KEY[100];
/*
double VALUE;
VALUE=meta->getAsDouble("ST_G_MAX_CRPIX_G_R");
cout<<scientific<<setprecision(6)<<"R : "<<SLVTS->CCDs->MAX_CRPIX_G_R<<"	"<<VALUE<<endl;
*/
	for(CID=0;CID<SLVTS->APRM->NUM_CCD+1;CID++){
		sprintf(KEY,"ST_C%03d_ID"      ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].ID);
                sprintf(KEY,"ST_C%03d_NUM_REF" ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].NUM_REF);
                sprintf(KEY,"ST_C%03d_NUM_FIT" ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].NUM_FIT);
                sprintf(KEY,"ST_C%03d_NUM_REJ" ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].NUM_REJ);
                sprintf(KEY,"ST_C%03d_GPOS_LX" ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].GPOS_L[0]);
                sprintf(KEY,"ST_C%03d_GPOS_LY" ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].GPOS_L[1]);
                sprintf(KEY,"ST_C%03d_GPOS_LT" ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].GPOS_L[2]);
                sprintf(KEY,"ST_C%03d_GPOS_LTD",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].GPOS_L[3]);
                sprintf(KEY,"ST_C%03d_GPOS_CX" ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].GPOS_C[0]);
                sprintf(KEY,"ST_C%03d_GPOS_CY" ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].GPOS_C[1]);
                sprintf(KEY,"ST_C%03d_GPOS_CT" ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].GPOS_C[2]);
                sprintf(KEY,"ST_C%03d_GPOS_CTD",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].GPOS_C[3]);
                sprintf(KEY,"ST_C%03d_CRPIX1"  ,CID);
	        meta->add(KEY,*SLVTS->CCDs->CCD[CID].CRPIX[0]);
                sprintf(KEY,"ST_C%03d_CRPIX2"  ,CID);
	        meta->add(KEY,*SLVTS->CCDs->CCD[CID].CRPIX[1]);
                sprintf(KEY,"ST_C%03d_CRVAL1"  ,CID);
	        meta->add(KEY,*SLVTS->CCDs->CCD[CID].CRVAL[2]);
                sprintf(KEY,"ST_C%03d_CRVAL2"  ,CID);
	        meta->add(KEY,*SLVTS->CCDs->CCD[CID].CRVAL[3]);
                sprintf(KEY,"ST_C%03d_CD1_1"  ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].CD[0][0]);
                sprintf(KEY,"ST_C%03d_CD1_2"  ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].CD[0][1]);
                sprintf(KEY,"ST_C%03d_CD2_1"  ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].CD[1][0]);
                sprintf(KEY,"ST_C%03d_CD2_2"  ,CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].CD[1][1]);
                sprintf(KEY,"ST_C%03d_InvCD1_1",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].InvCD[0][0]);
                sprintf(KEY,"ST_C%03d_InvCD1_2",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].InvCD[0][1]);
                sprintf(KEY,"ST_C%03d_InvCD2_1",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].InvCD[1][0]);
                sprintf(KEY,"ST_C%03d_InvCD2_2",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].InvCD[1][1]);
                sprintf(KEY,"ST_C%03d_OREDER_ASIP",CID);
	        meta->add(KEY,*SLVTS->CCDs->CCD[CID].ORDER_ASIP);
		ij=0;
		for(i=0;i<SLVTS->APRM->ORDER_ASIP+1  ;i++)
                for(j=0;j<SLVTS->APRM->ORDER_ASIP+1-i;j++){
        	        sprintf(KEY,"ST_C%03d_ASIP_X_%d_%d" ,CID,i,j);
	        	meta->add(KEY,SLVTS->CCDs->CCD[CID].ASIP[0][ij]);
			ij++;
		}
                ij=0;
                for(i=0;i<SLVTS->APRM->ORDER_ASIP+1  ;i++)
                for(j=0;j<SLVTS->APRM->ORDER_ASIP+1-i;j++){
                        sprintf(KEY,"ST_C%03d_ASIP_Y_%d_%d" ,CID,i,j);
	        	meta->add(KEY,SLVTS->CCDs->CCD[CID].ASIP[1][ij]);
                        ij++;
                }
                sprintf(KEY,"ST_C%03d_ASIP_DIF_AVE_X",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_AVE_ASIP[0]);
                sprintf(KEY,"ST_C%03d_ASIP_DIF_AVE_Y",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_AVE_ASIP[1]);
                sprintf(KEY,"ST_C%03d_ASIP_DIF_RMS_X",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_RMS_ASIP[0]);
                sprintf(KEY,"ST_C%03d_ASIP_DIF_RMS_Y",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_RMS_ASIP[1]);
                sprintf(KEY,"ST_C%03d_ASIP_DIF_MAX_X",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_MAX_ASIP[0]);
                sprintf(KEY,"ST_C%03d_ASIP_DIF_MAX_Y",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_MAX_ASIP[1]);

                sprintf(KEY,"ST_C%03d_ORDER_PSIP" ,CID);
	        meta->add(KEY,*SLVTS->CCDs->CCD[CID].ORDER_PSIP);
                ij=0;
                for(i=0;i<SLVTS->APRM->ORDER_PSIP+1  ;i++)
                for(j=0;j<SLVTS->APRM->ORDER_PSIP+1-i;j++){
                        sprintf(KEY,"ST_C%03d_PSIP_X_%d_%d" ,CID,i,j);
	    		meta->add(KEY,SLVTS->CCDs->CCD[CID].PSIP[0][ij]);
                        ij++;
                }
                ij=0;
                for(i=0;i<SLVTS->APRM->ORDER_PSIP+1  ;i++)
                for(j=0;j<SLVTS->APRM->ORDER_PSIP+1-i;j++){
                        sprintf(KEY,"ST_C%03d_PSIP_Y_%d_%d" ,CID,i,j);
	 	   	meta->add(KEY,SLVTS->CCDs->CCD[CID].PSIP[1][ij]);
                        ij++;
                }
                sprintf(KEY,"ST_C%03d_PSIP_DIF_AVE_X",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_AVE_PSIP[0]);
                sprintf(KEY,"ST_C%03d_PSIP_DIF_AVE_Y",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_AVE_PSIP[1]);
                sprintf(KEY,"ST_C%03d_PSIP_DIF_RMS_X",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_RMS_PSIP[0]);
                sprintf(KEY,"ST_C%03d_PSIP_DIF_RMS_Y",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_RMS_PSIP[1]);
                sprintf(KEY,"ST_C%03d_PSIP_DIF_MAX_X",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_MAX_PSIP[0]);
                sprintf(KEY,"ST_C%03d_PSIP_DIF_MAX_Y",CID);
	        meta->add(KEY,SLVTS->CCDs->CCD[CID].DIF_MAX_PSIP[1]);
	}


//Summary
        meta->add("sip_residuals_ave_x" , SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_AVE_ASIP[0]);
        meta->add("sip_residuals_ave_y" , SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_AVE_ASIP[1]);
 	meta->add("sip_residuals_rms_x" , SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_RMS_ASIP[0]);
	meta->add("sip_residuals_rms_y" , SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_RMS_ASIP[1]);
        meta->add("psip_residuals_ave_x", SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_AVE_PSIP[0]);
        meta->add("psip_residuals_ave_y", SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_AVE_PSIP[1]);
        meta->add("psip_residuals_rms_x", SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_RMS_PSIP[0]);
        meta->add("psip_residuals_rms_y", SLVTS->CCDs->CCD[SLVTS->APRM->NUM_CCD].DIF_RMS_PSIP[1]);
	meta->add("nref_all"            , SLVTS->APRM->NUM_REF);
	meta->add("nref_fitting"        , SLVTS->APRM->NUM_FIT);

}
std::vector <lsst::afw::image::TanWcs::Ptr> SET_TANWCS(std::vector< CL_SLVTS* > VSLVTS){
	std::vector <lsst::afw::image::TanWcs::Ptr> V_TanWcs;
	int CID;
	CL_SLVTS* SLVTS;
	SLVTS=VSLVTS[0];
	
	int OAS,OPS;
	int i,j,ij;
	for(CID=0;CID<SLVTS->APRM->NUM_CCD+1;CID++){
		afwGeom::PointD crpix = afwGeom::PointD(*SLVTS->CCDs->CCD[CID].CRPIX[0],*SLVTS->CCDs->CCD[CID].CRPIX[1]);
		afwGeom::PointD crval = afwGeom::PointD(*SLVTS->CCDs->CCD[CID].CRVAL[0],*SLVTS->CCDs->CCD[CID].CRVAL[1]);
	
		Eigen::Matrix2d cdMatrix;
		cdMatrix << SLVTS->CCDs->CCD[CID].CD[0][0],SLVTS->CCDs->CCD[CID].CD[0][1],SLVTS->CCDs->CCD[CID].CD[1][0],SLVTS->CCDs->CCD[CID].CD[1][1];

		OAS=*SLVTS->CCDs->CCD[CID].ORDER_ASIP;
		OPS=*SLVTS->CCDs->CCD[CID].ORDER_PSIP;
		Eigen::MatrixXd sipA  = Eigen::MatrixXd::Zero(OAS+1,OAS+1);
		Eigen::MatrixXd sipB  = Eigen::MatrixXd::Zero(OAS+1,OAS+1);
		Eigen::MatrixXd sipAp = Eigen::MatrixXd::Zero(OPS+1,OPS+1);
		Eigen::MatrixXd sipBp = Eigen::MatrixXd::Zero(OPS+1,OPS+1);

		ij=0;
		for(i=0;i<OAS+1;i++)
		for(j=0;j<OAS+1;j++)
		if(i+j<OAS+1){
			sipA(i,j)=SLVTS->CCDs->CCD[CID].ASIP[0][ij];
			sipB(i,j)=SLVTS->CCDs->CCD[CID].ASIP[1][ij];
			ij++;
		}else{
			sipA(i,j)=0.0;
			sipB(i,j)=0.0;
		}
		ij=0;
		for(i=0;i<OAS+1;i++)
		for(j=0;j<OAS+1;j++)
		if(i+j<OAS+1){
			sipAp(i,j)=SLVTS->CCDs->CCD[CID].PSIP[0][ij];
			sipBp(i,j)=SLVTS->CCDs->CCD[CID].PSIP[1][ij];
			ij++;
		}else{
			sipAp(i,j)=0.0;
			sipBp(i,j)=0.0;
		}

		afwImage::TanWcs::Ptr resultTanWsc(new afwImage::TanWcs(crval,crpix,cdMatrix,sipA,sipB,sipAp,sipBp));
		V_TanWcs.push_back(resultTanWsc);
	}
	return V_TanWcs;
}
