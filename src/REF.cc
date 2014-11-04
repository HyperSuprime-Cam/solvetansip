//-----------------------------------------------------------
//REF.cc
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include "hsc/meas/tansip/REF.h"

#include <stdexcept>

namespace hsc { namespace meas {
namespace tansip {

using namespace std;
//REFs
void CL_REFs::SET_INIT(CL_APRM *APRM_IN,CL_CCDs* CCDs_IN){
	APRM=APRM_IN;
	CCDs=CCDs_IN;

	int const NUM_REF    = APRM->NUM_REF;
	REF.resize(NUM_REF);

	for(int i = 0; i < NUM_REF; ++i){
		REF[i].APRM = APRM;
		REF[i].REFs = this;
	}
}
void CL_REFs::SET_INPUT(std::vector< std::vector< std::string > > REF_Argvs,CL_APRM* APRM,CL_CCDs* CCDs){
	SET_INIT(APRM,CCDs);

	int const NUM_REF    = APRM->NUM_REF;

	if(APRM->FLAG_STD >= 1)cout<<"-- SET REFs --"<<endl;
	for(int i = 0; i < NUM_REF; ++i){
		long long IDOBJ = atoll(REF_Argvs[i][0].c_str());
		int       IDCCD = atoi (REF_Argvs[i][1].c_str());

		double POS_L[2],RADEC[2];
		POS_L[0]=atof(REF_Argvs[i][2].c_str());
		POS_L[1]=atof(REF_Argvs[i][3].c_str());
		RADEC[0]=atof(REF_Argvs[i][4].c_str());
		RADEC[1]=atof(REF_Argvs[i][5].c_str());
//cout << i << "	" << IDOBJ << "  " << IDCCD << "  " << POS_L[0] << "  " << POS_L[1] << "  " << RADEC[0] << "  " << RADEC[1]<<endl;
		if(isfinite(IDOBJ)   &&isfinite(IDCCD)   &&
		   isfinite(POS_L[0])&&isfinite(POS_L[1])&&
		   isfinite(RADEC[0])&&isfinite(RADEC[1])){
			REF[i].ID_OBJ        =IDOBJ;
			REF[i].ID_CCD        =IDCCD;
			REF[i].POS_DETECTED_LOCAL_L[0]=POS_L[0];
			REF[i].POS_DETECTED_LOCAL_L[1]=POS_L[1];
			REF[i].POS_CELESTIAL_RADEC[0] =RADEC[0];
			REF[i].POS_CELESTIAL_RADEC[1] =RADEC[1];
			REF[i].FLAG_OBJ	     =1;
		}else{
			REF[i].FLAG_OBJ	     =0;
		}
	}
	SET_NUM();
	SET_CCD(CCDs);
	SET_POS_DETECTED_LOCAL_CfromLOCAL_L();
	SET_POS_DETECTED_LOCAL_GfromLOCAL_L();
	SET_MAXMIN_LOCAL_G();

}
void CL_REFs::SET_NUM(){
	int const NUM_REF    = APRM->NUM_REF;
	int const NUM_CCD    = APRM->NUM_CCD;

	for(int i = 0; i < NUM_CCD+1; ++i){
		CCDs->CCD[i].NUM_REF=0;
		CCDs->CCD[i].NUM_FIT=0;
		CCDs->CCD[i].NUM_REJ=0;
	}

	for(int i = 0; i < NUM_REF; ++i){
		CCDs->CCD[REF[i].ID_CCD].NUM_REF+=1;
		CCDs->CCD[      NUM_CCD].NUM_REF+=1;
		if(REF[i].FLAG_OBJ==1){
			CCDs->CCD[REF[i].ID_CCD].NUM_FIT+=1;
			CCDs->CCD[      NUM_CCD].NUM_FIT+=1;
		}else{
			CCDs->CCD[REF[i].ID_CCD].NUM_REJ+=1;
			CCDs->CCD[      NUM_CCD].NUM_REJ+=1;
		}
	}
}
void CL_REFs::SET_END(){
}
void CL_REFs::SET_CCD(CL_CCDs*  CCDs){
	int const NUM_REF    = APRM->NUM_REF;
	int const NUM_CCD    = APRM->NUM_CCD;

	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_INIT(&CCDs->CCD[REF[i].ID_CCD],&CCDs->CCD[NUM_CCD]);
}
void CL_REFs::SHOW(){
	cout << "-- SHOW REFs --" << endl;
	cout << "MODE_CR        : " << APRM->MODE_CR << endl;
	cout << "NUM_REF        : " << APRM->NUM_REF << endl;
	cout << "NUM_FIT        : " << APRM->NUM_FIT << endl;
	cout << "AVE LOCAL_G X  : " ;cout.width(10);cout<< AVE_LOCAL_G[0] <<endl;
	cout << "AVE LOCAL_G Y  : " ;cout.width(10);cout<< AVE_LOCAL_G[1] <<endl;
	cout << "MAX LOCAL_G X  : " ;cout.width(10);cout<< MAX_LOCAL_G[0] <<endl;
	cout << "MAX LOCAL_G Y  : " ;cout.width(10);cout<< MAX_LOCAL_G[1] <<endl;
	cout << "MIN LOCAL_G X  : " ;cout.width(10);cout<< MIN_LOCAL_G[0] <<endl;
	cout << "MIN LOCAL_G Y  : " ;cout.width(10);cout<< MIN_LOCAL_G[1] <<endl;
	cout << "MAX LOCAL_G R  : " ;cout.width(10);cout<< MAX_LOCAL_G_R  <<endl;
}
//REFs::POS
void CL_REFs::SET_POS_DETECTED_LOCAL_CfromLOCAL_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_LOCAL_CfromLOCAL_L();
}
void CL_REFs::SET_POS_DETECTED_LOCAL_GfromLOCAL_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_LOCAL_GfromLOCAL_L();
}
void CL_REFs::SET_POS_DETECTED_CRPIX_LfromLOCAL_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_CRPIX_LfromLOCAL_L();
}
void CL_REFs::SET_POS_DETECTED_CRPIX_GfromLOCAL_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_CRPIX_GfromLOCAL_G();
}
void CL_REFs::SET_POS_DETECTED_IMPIX_LfromCRPIX_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_IMPIX_LfromCRPIX_L();
}
void CL_REFs::SET_POS_DETECTED_IMPIX_GfromCRPIX_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_IMPIX_GfromCRPIX_G();
}
void CL_REFs::SET_POS_DETECTED_IMWLD_LfromIMPIX_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_IMWLD_LfromIMPIX_L();
}
void CL_REFs::SET_POS_DETECTED_IMWLD_GfromIMPIX_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_IMWLD_GfromIMPIX_G();
}
void CL_REFs::SET_POS_DETECTED_RADEC_LfromIMWLD_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_RADEC_LfromIMWLD_L();
}
void CL_REFs::SET_POS_DETECTED_RADEC_GfromIMWLD_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_RADEC_GfromIMWLD_G();
}
void CL_REFs::SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L();
}
void CL_REFs::SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();
}
void CL_REFs::SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L();
}
void CL_REFs::SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G();
}
void CL_REFs::SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L();
}
void CL_REFs::SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G();
}
void CL_REFs::SET_POS_DETECTED_ALL(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i){
		REF[i].SET_POS_DETECTED_LOCAL_GfromLOCAL_L();
		REF[i].SET_POS_DETECTED_CRPIX_LfromLOCAL_L();
		REF[i].SET_POS_DETECTED_CRPIX_GfromLOCAL_G();
		REF[i].SET_POS_DETECTED_IMPIX_LfromCRPIX_L();
		REF[i].SET_POS_DETECTED_IMPIX_GfromCRPIX_G();
		REF[i].SET_POS_DETECTED_IMWLD_LfromIMPIX_L();
		REF[i].SET_POS_DETECTED_IMWLD_GfromIMPIX_G();
		REF[i].SET_POS_DETECTED_RADEC_LfromIMWLD_L();
		REF[i].SET_POS_DETECTED_RADEC_GfromIMWLD_G();
		REF[i].SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L();
		REF[i].SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();
		REF[i].SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L();
		REF[i].SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G();
		REF[i].SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L();
		REF[i].SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G();
	}
}
void CL_REFs::SET_POS_CELESTIAL_IMWLDfromRADEC(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_IMWLDfromRADEC();
}
void CL_REFs::SET_POS_CELESTIAL_IMPIX_GfromIMWLD(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
}
void CL_REFs::SET_POS_CELESTIAL_IMPIX_LfromIMWLD(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_IMPIX_LfromIMWLD();
}
void CL_REFs::SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G();
}
void CL_REFs::SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L();
}
void CL_REFs::SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G();
}
void CL_REFs::SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L();
}
void CL_REFs::SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD();
}
void CL_REFs::SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();
}
void CL_REFs::SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L();
}
void CL_REFs::SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G();
}
void CL_REFs::SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L();
}
void CL_REFs::SET_POS_CELESTIAL_ALL(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i){
		REF[i].SET_POS_CELESTIAL_IMWLDfromRADEC();
		REF[i].SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
		REF[i].SET_POS_CELESTIAL_IMPIX_LfromIMWLD();
		REF[i].SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G();
		REF[i].SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L();
		REF[i].SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G();
		REF[i].SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L();
		REF[i].SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();
		REF[i].SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L();
		REF[i].SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G();
		REF[i].SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L();
	}
}
void CL_REFs::SET_DIFF(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_DIFF();
}
void CL_REFs::SET_OPTICAL_DISTORTIONbyPSIP(){
	int const NUM_REF    = APRM->NUM_REF;
	for(int i = 0; i < NUM_REF; ++i)
	REF[i].SET_OPTICAL_DISTORTIONbyPSIP();
}
void CL_REFs::SET_MAXMIN_LOCAL_G(){
	int const NUM_REF    = APRM->NUM_REF;

	AVE_LOCAL_G[0]=AVE_LOCAL_G[1]=0;
	APRM->NUM_FIT=0;
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		AVE_LOCAL_G[0]+=REF[i].POS_DETECTED_LOCAL_G[0];
		AVE_LOCAL_G[1]+=REF[i].POS_DETECTED_LOCAL_G[1];
		APRM->NUM_FIT+=1;
	}
	AVE_LOCAL_G[0]/=APRM->NUM_FIT;
	AVE_LOCAL_G[1]/=APRM->NUM_FIT;

	MAX_LOCAL_G_R =0;
	MAX_LOCAL_G[0]=MIN_LOCAL_G[0]=AVE_LOCAL_G[0];
	MAX_LOCAL_G[1]=MIN_LOCAL_G[1]=AVE_LOCAL_G[1];
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		if(REF[i].POS_DETECTED_LOCAL_G[0]>MAX_LOCAL_G[0])
		MAX_LOCAL_G[0]=REF[i].POS_DETECTED_LOCAL_G[0];
		if(REF[i].POS_DETECTED_LOCAL_G[0]<MIN_LOCAL_G[0])
		MIN_LOCAL_G[0]=REF[i].POS_DETECTED_LOCAL_G[0];
		if(REF[i].POS_DETECTED_LOCAL_G[1]>MAX_LOCAL_G[1])
		MAX_LOCAL_G[1]=REF[i].POS_DETECTED_LOCAL_G[1];
		if(REF[i].POS_DETECTED_LOCAL_G[1]<MIN_LOCAL_G[1])
		MIN_LOCAL_G[1]=REF[i].POS_DETECTED_LOCAL_G[1];
		double R=hypot(REF[i].POS_DETECTED_LOCAL_G[0],REF[i].POS_DETECTED_LOCAL_G[1]);
		if(R>MAX_LOCAL_G_R)
		MAX_LOCAL_G_R=R;
	}
}
void CL_REFs::SET_MAXMIN_CRPIX_G(){
	int const NUM_REF    = APRM->NUM_REF;

	double  &MAX_CRPIX_G_R   = CCDs->MAX_CRPIX_G_R;
	double (&MAX_CRPIX_G)[2] = CCDs->MAX_CRPIX_G;
	double (&MIN_CRPIX_G)[2] = CCDs->MIN_CRPIX_G;
	double (&AVE_CRPIX_G)[2] = CCDs->AVE_CRPIX_G;

	AVE_CRPIX_G[0]=AVE_CRPIX_G[1]=0;
	APRM->NUM_FIT=0;
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		AVE_CRPIX_G[0]+=REF[i].POS_DETECTED_CRPIX_G[0];
		AVE_CRPIX_G[1]+=REF[i].POS_DETECTED_CRPIX_G[1];
		APRM->NUM_FIT+=1;
	}
	AVE_CRPIX_G[0]/=APRM->NUM_FIT;
	AVE_CRPIX_G[1]/=APRM->NUM_FIT;

	MAX_CRPIX_G_R =0;
	MAX_CRPIX_G[0]=MIN_CRPIX_G[0]=AVE_CRPIX_G[0];
	MAX_CRPIX_G[1]=MIN_CRPIX_G[1]=AVE_CRPIX_G[1];
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		if(REF[i].POS_DETECTED_CRPIX_G[0]>MAX_CRPIX_G[0])
		MAX_CRPIX_G[0]=REF[i].POS_DETECTED_CRPIX_G[0];
		if(REF[i].POS_DETECTED_CRPIX_G[0]<MIN_CRPIX_G[0])
		MIN_CRPIX_G[0]=REF[i].POS_DETECTED_CRPIX_G[0];
		if(REF[i].POS_DETECTED_CRPIX_G[1]>MAX_CRPIX_G[1])
		MAX_CRPIX_G[1]=REF[i].POS_DETECTED_CRPIX_G[1];
		if(REF[i].POS_DETECTED_CRPIX_G[1]<MIN_CRPIX_G[1])
		MIN_CRPIX_G[1]=REF[i].POS_DETECTED_CRPIX_G[1];
		double R=hypot(REF[i].POS_DETECTED_CRPIX_G[0],REF[i].POS_DETECTED_CRPIX_G[1]);
		if(R>MAX_CRPIX_G_R)
		MAX_CRPIX_G_R=R;
	}
}
int  CL_REFs::GET_ID_NEAR_CRVAL(){
	int const NUM_REF    = APRM->NUM_REF;

	int ID_MIN=0;
	double MIN_CRVAL=INFINITY;
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		double R_CRVAL=hypot(REF[i].POS_CELESTIAL_RADEC[0]-APRM->CRVAL[0],REF[i].POS_CELESTIAL_RADEC[1]-APRM->CRVAL[1]);
		if(R_CRVAL<MIN_CRVAL){
			MIN_CRVAL=R_CRVAL;
			ID_MIN=i;
		}
	}

	return ID_MIN;
}
int  CL_REFs::GET_ID_NEAR_CRPIX(){
	int const NUM_REF    = APRM->NUM_REF;

	int ID_MIN=0;
	double MIN_CRPIX=INFINITY;
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		double R_CRPIX=hypot(REF[i].POS_DETECTED_LOCAL_G[0]-APRM->CRPIX[0],REF[i].POS_DETECTED_LOCAL_G[1]-APRM->CRPIX[1]);
		if(R_CRPIX<MIN_CRPIX){
			MIN_CRPIX=R_CRPIX;
			ID_MIN=i;
		}
	}

	return ID_MIN;
}

//REFS::FIT
void CL_REFs::FIT_CbyD(int ID_C,int ID_D){
	int const NUM_REF    = APRM->NUM_REF;

	ndarray::Array<double, 2, 2> dx = ndarray::allocate(NUM_REF,3);
	ndarray::Array<double, 2, 2> dy = ndarray::allocate(NUM_REF,3);

	APRM->NUM_FIT=0;
	for(int i = 0 ; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		double D[2] = {}, C[2] = {};

		      if(ID_D== 0){
			D[0]=REF[i].POS_DETECTED_LOCAL_G[0];
			D[1]=REF[i].POS_DETECTED_LOCAL_G[1];
		}else if(ID_D== 1){
			D[0]=REF[i].POS_DETECTED_CRPIX_G[0];
			D[1]=REF[i].POS_DETECTED_CRPIX_G[1];
		}else if(ID_D== 2){
			D[0]=REF[i].POS_DETECTED_IMPIX_G[0];
			D[1]=REF[i].POS_DETECTED_IMPIX_G[1];
		}else if(ID_D== 3){
			D[0]=REF[i].POS_DETECTED_IMWLD_G[0];
			D[1]=REF[i].POS_DETECTED_IMWLD_G[1];
		}else if(ID_D== 4){
			D[0]=REF[i].POS_DETECTED_RADEC_G[0];
			D[1]=REF[i].POS_DETECTED_RADEC_G[1];
		}
		      if(ID_C== 0){
			C[0]=REF[i].POS_CELESTIAL_RADEC[0];
			C[1]=REF[i].POS_CELESTIAL_RADEC[1];
		}else if(ID_C== 1){
			C[0]=REF[i].POS_CELESTIAL_IMWLD[0];
			C[1]=REF[i].POS_CELESTIAL_IMWLD[1];
		}else if(ID_C== 2){
			C[0]=REF[i].POS_CELESTIAL_IMPIX_G[0];
			C[1]=REF[i].POS_CELESTIAL_IMPIX_G[1];
		}else if(ID_C== 3){
			C[0]=REF[i].POS_CELESTIAL_CRPIX_G[0];
			C[1]=REF[i].POS_CELESTIAL_CRPIX_G[1];
		}else if(ID_C== 4){
			C[0]=REF[i].POS_CELESTIAL_LOCAL_G[0];
			C[1]=REF[i].POS_CELESTIAL_LOCAL_G[1];
		}

		if(isfinite(D[0])&&isfinite(D[1])&&
		   isfinite(C[0])&&isfinite(C[1])){
			dx[APRM->NUM_FIT][0]=dy[APRM->NUM_FIT][0]=D[0];
			dx[APRM->NUM_FIT][1]=dy[APRM->NUM_FIT][1]=D[1];
			dx[APRM->NUM_FIT][2]=C[0];
			dy[APRM->NUM_FIT][2]=C[1];
			APRM->NUM_FIT+=1;
		}
	}

	Polynomial2D (&ASIP)[2] = CCDs->CCD[APRM->NUM_CCD].ASIP;
	ASIP[0] = CALC_FIT_LS2(APRM->NUM_FIT,APRM->ORDER_ASIP,dx);
	ASIP[1] = CALC_FIT_LS2(APRM->NUM_FIT,APRM->ORDER_ASIP,dy);
}
void CL_REFs::FIT_DbyC(int ID_D,int ID_C){
	int const NUM_REF    = APRM->NUM_REF;

	ndarray::Array<double, 2, 2> dx = ndarray::allocate(NUM_REF,3);
	ndarray::Array<double, 2, 2> dy = ndarray::allocate(NUM_REF,3);

	APRM->NUM_FIT=0;
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		double D[2] = {},C[2] = {};

		      if(ID_D== 0){
			D[0]=REF[i].POS_DETECTED_LOCAL_G[0];
			D[1]=REF[i].POS_DETECTED_LOCAL_G[1];
		}else if(ID_D== 1){
			D[0]=REF[i].POS_DETECTED_CRPIX_G[0];
			D[1]=REF[i].POS_DETECTED_CRPIX_G[1];
		}else if(ID_D== 2){
			D[0]=REF[i].POS_DETECTED_IMPIX_G[0];
			D[1]=REF[i].POS_DETECTED_IMPIX_G[1];
		}else if(ID_D== 3){
			D[0]=REF[i].POS_DETECTED_IMWLD_G[0];
			D[1]=REF[i].POS_DETECTED_IMWLD_G[1];
		}else if(ID_D== 4){
			D[0]=REF[i].POS_DETECTED_RADEC_G[0];
			D[1]=REF[i].POS_DETECTED_RADEC_G[1];
		}
		      if(ID_C== 0){
			C[0]=REF[i].POS_CELESTIAL_RADEC[0];
			C[1]=REF[i].POS_CELESTIAL_RADEC[1];
		}else if(ID_C== 1){
			C[0]=REF[i].POS_CELESTIAL_IMWLD[0];
			C[1]=REF[i].POS_CELESTIAL_IMWLD[1];
		}else if(ID_C== 2){
			C[0]=REF[i].POS_CELESTIAL_IMPIX_G[0];
			C[1]=REF[i].POS_CELESTIAL_IMPIX_G[1];
		}else if(ID_C== 3){
			C[0]=REF[i].POS_CELESTIAL_CRPIX_G[0];
			C[1]=REF[i].POS_CELESTIAL_CRPIX_G[1];
		}else if(ID_C== 4){
			C[0]=REF[i].POS_CELESTIAL_LOCAL_G[0];
			C[1]=REF[i].POS_CELESTIAL_LOCAL_G[1];
		}
                if(isfinite(D[0])&&isfinite(D[1])&&
                   isfinite(C[0])&&isfinite(C[1])){
			dx[APRM->NUM_FIT][0]=dy[APRM->NUM_FIT][0]=C[0];
			dx[APRM->NUM_FIT][1]=dy[APRM->NUM_FIT][1]=C[1];
			dx[APRM->NUM_FIT][2]=D[0];
			dy[APRM->NUM_FIT][2]=D[1];
			APRM->NUM_FIT+=1;
		}
	}

	Polynomial2D (&PSIP)[2] = CCDs->CCD[APRM->NUM_CCD].PSIP;
	PSIP[0] = CALC_FIT_LS2(APRM->NUM_FIT,APRM->ORDER_PSIP,dx);
	PSIP[1] = CALC_FIT_LS2(APRM->NUM_FIT,APRM->ORDER_PSIP,dy);
}
void CL_REFs::CALC_STAT_ASIP(){
	int const NUM_REF    = APRM->NUM_REF;
	int const NUM_CCD    = APRM->NUM_CCD;

	ndarray::Array<double, 1, 1> DIFF[2];
	DIFF[0]= ndarray::allocate(NUM_REF);
	DIFF[1]= ndarray::allocate(NUM_REF);

	APRM->NUM_FIT=0;
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		DIFF[0][APRM->NUM_FIT]=REF[i].POS_DETECTED_ASIP_IMPIX_G[0]-REF[i].POS_CELESTIAL_IMPIX_G[0];
		DIFF[1][APRM->NUM_FIT]=REF[i].POS_DETECTED_ASIP_IMPIX_G[1]-REF[i].POS_CELESTIAL_IMPIX_G[1];
		APRM->NUM_FIT+=1;
	}

	double STAT[2][4];
	CALC_STAT_RMSMAX(APRM->NUM_FIT,DIFF[0].getData(),STAT[0]);
	CALC_STAT_RMSMAX(APRM->NUM_FIT,DIFF[1].getData(),STAT[1]);

	double (&DIF_AVE_ASIP)[2] = CCDs->CCD[NUM_CCD].DIF_AVE_ASIP;
	double (&DIF_RMS_ASIP)[2] = CCDs->CCD[NUM_CCD].DIF_RMS_ASIP;
	double (&DIF_MAX_ASIP)[2] = CCDs->CCD[NUM_CCD].DIF_MAX_ASIP;

	DIF_AVE_ASIP[0]=STAT[0][1];
	DIF_AVE_ASIP[1]=STAT[1][1];
	DIF_RMS_ASIP[0]=STAT[0][2];
	DIF_RMS_ASIP[1]=STAT[1][2];
	DIF_MAX_ASIP[0]=STAT[0][3];
	DIF_MAX_ASIP[1]=STAT[1][3];

	if(APRM->FLAG_STD >= 2){
		cout<<"-- STAT ASIP DIFF --"<<endl;
		cout<<"NUM    : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<APRM->NUM_FIT<<endl;
		cout<<"AVE X  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_AVE_ASIP[0]<<endl;
		cout<<"RMS X  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_RMS_ASIP[0]<<endl;
		cout<<"MAX X  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_MAX_ASIP[0]<<endl;
		cout<<"AVE Y  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_AVE_ASIP[1]<<endl;
		cout<<"RMS Y  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_RMS_ASIP[1]<<endl;
		cout<<"MAX Y  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_MAX_ASIP[1]<<endl;
	}
}
void CL_REFs::CALC_STAT_PSIP(){
	int const NUM_REF    = APRM->NUM_REF;
	int const NUM_CCD    = APRM->NUM_CCD;

	ndarray::Array<double, 1, 1> DIFF[2];
	DIFF[0]= ndarray::allocate(NUM_REF);
	DIFF[1]= ndarray::allocate(NUM_REF);

	APRM->NUM_FIT=0;
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		DIFF[0][APRM->NUM_FIT]=REF[i].POS_CELESTIAL_PSIP_CRPIX_G[0]-REF[i].POS_DETECTED_CRPIX_G[0];
		DIFF[1][APRM->NUM_FIT]=REF[i].POS_CELESTIAL_PSIP_CRPIX_G[1]-REF[i].POS_DETECTED_CRPIX_G[1];
		APRM->NUM_FIT+=1;
	}

	double STAT[2][4];
	CALC_STAT_RMSMAX(APRM->NUM_FIT,DIFF[0].getData(),STAT[0]);
	CALC_STAT_RMSMAX(APRM->NUM_FIT,DIFF[1].getData(),STAT[1]);

	double (&DIF_AVE_PSIP)[2] = CCDs->CCD[NUM_CCD].DIF_AVE_PSIP;
	double (&DIF_RMS_PSIP)[2] = CCDs->CCD[NUM_CCD].DIF_RMS_PSIP;
	double (&DIF_MAX_PSIP)[2] = CCDs->CCD[NUM_CCD].DIF_MAX_PSIP;

	DIF_AVE_PSIP[0]=STAT[0][1];
	DIF_AVE_PSIP[1]=STAT[1][1];
	DIF_RMS_PSIP[0]=STAT[0][2];
	DIF_RMS_PSIP[1]=STAT[1][2];
	DIF_MAX_PSIP[0]=STAT[0][3];
	DIF_MAX_PSIP[1]=STAT[1][3];

	if(APRM->FLAG_STD >= 2){
		cout<<"-- STAT PSIP DIFF --"<<endl;
		cout<<"NUM    : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<APRM->NUM_FIT<<endl;
		cout<<"AVE X  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_AVE_PSIP[0]<<endl;
		cout<<"RMS X  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_RMS_PSIP[0]<<endl;
		cout<<"MAX X  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_MAX_PSIP[0]<<endl;
		cout<<"AVE Y  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_AVE_PSIP[1]<<endl;
		cout<<"RMS Y  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_RMS_PSIP[1]<<endl;
		cout<<"MAX Y  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<DIF_MAX_PSIP[1]<<endl;
	}
}
void CL_REFs::CALC_STAT_SIP_LOCAL(){
	int const NUM_REF    = APRM->NUM_REF;
	int const NUM_CCD    = APRM->NUM_CCD;

	ndarray::Array<int   , 1, 1> NUM = ndarray::allocate(NUM_CCD);
	ndarray::Array<double, 3, 3> DIFF= ndarray::allocate(NUM_CCD,4,NUM_REF);
	ndarray::Array<double, 3, 3> STAT= ndarray::allocate(NUM_CCD,4,4);

	NUM.deep() = 0;

	APRM->NUM_FIT=0;
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		DIFF[REF[i].ID_CCD][0][NUM[REF[i].ID_CCD]]=REF[i].POS_DETECTED_ASIP_IMPIX_L[0]-REF[i].POS_CELESTIAL_IMPIX_L[0];
		DIFF[REF[i].ID_CCD][1][NUM[REF[i].ID_CCD]]=REF[i].POS_DETECTED_ASIP_IMPIX_L[1]-REF[i].POS_CELESTIAL_IMPIX_L[1];
		DIFF[REF[i].ID_CCD][2][NUM[REF[i].ID_CCD]]=REF[i].POS_CELESTIAL_PSIP_CRPIX_L[0]-REF[i].POS_DETECTED_CRPIX_L[0];
		DIFF[REF[i].ID_CCD][3][NUM[REF[i].ID_CCD]]=REF[i].POS_CELESTIAL_PSIP_CRPIX_L[1]-REF[i].POS_DETECTED_CRPIX_L[1];
		 NUM[REF[i].ID_CCD]+=1;
		APRM->NUM_FIT+=1;
	}
	for(int i = 0; i < NUM_CCD; ++i){
		CALC_STAT_RMSMAX(NUM[i],DIFF[i][0].getData(),STAT[i][0].getData());
		CALC_STAT_RMSMAX(NUM[i],DIFF[i][1].getData(),STAT[i][1].getData());
		CALC_STAT_RMSMAX(NUM[i],DIFF[i][2].getData(),STAT[i][2].getData());
		CALC_STAT_RMSMAX(NUM[i],DIFF[i][3].getData(),STAT[i][3].getData());
		CCDs->CCD[i].DIF_AVE_ASIP[0]=STAT[i][0][1];
		CCDs->CCD[i].DIF_AVE_ASIP[1]=STAT[i][1][1];
		CCDs->CCD[i].DIF_AVE_PSIP[0]=STAT[i][2][1];
		CCDs->CCD[i].DIF_AVE_PSIP[1]=STAT[i][3][1];
		CCDs->CCD[i].DIF_RMS_ASIP[0]=STAT[i][0][2];
		CCDs->CCD[i].DIF_RMS_ASIP[1]=STAT[i][1][2];
		CCDs->CCD[i].DIF_RMS_PSIP[0]=STAT[i][2][2];
		CCDs->CCD[i].DIF_RMS_PSIP[1]=STAT[i][3][2];
		CCDs->CCD[i].DIF_MAX_ASIP[0]=STAT[i][0][3];
		CCDs->CCD[i].DIF_MAX_ASIP[1]=STAT[i][1][3];
		CCDs->CCD[i].DIF_MAX_PSIP[0]=STAT[i][2][3];
		CCDs->CCD[i].DIF_MAX_PSIP[1]=STAT[i][3][3];
	}
}
void CL_REFs::CALC_CRPIXatCRVAL(){
	int const NUM_CCD    = APRM->NUM_CCD;
	Polynomial2D (&PSIP)[2] = CCDs->CCD[NUM_CCD].PSIP;

	SET_POS_CELESTIAL_IMWLDfromRADEC();
	FIT_DbyC(0,1);
	APRM->CRPIX[0]=PSIP[0].coeff(0,0);
	APRM->CRPIX[1]=PSIP[1].coeff(0,0);
	SET_POS_DETECTED_CRPIX_GfromLOCAL_G();
	FIT_CbyD(1,1);
	CCDs->CCD[NUM_CCD].SET_CDASIP();
	SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
	FIT_DbyC(1,2);
	CCDs->CCD[NUM_CCD].SET_CDPSIP();
	if(APRM->FLAG_STD >= 2){
		double (&CD)[2][2] = CCDs->CCD[NUM_CCD].CD;
		cout<<"-- CRPIX at CRVAL --"<<endl;
		cout<<"CRVAL1 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<APRM->CRVAL[0]<<endl;
		cout<<"CRVAL2 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<APRM->CRVAL[1]<<endl;
		cout<<"CRPIX1 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<APRM->CRPIX[0]<<endl;
		cout<<"CRPIX2 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<APRM->CRPIX[1]<<endl;
		cout<<"-- CD MATRIX --"<<endl;
		cout<<"CD1_1  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<CD[0][0]<<endl;
		cout<<"CD1_2  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<CD[0][1]<<endl;
		cout<<"CD2_1  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<CD[1][0]<<endl;
		cout<<"CD2_2  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<CD[1][1]<<endl;

	}
}
void CL_REFs::CALC_CRVALatCRPIX(){
	int const NUM_CCD    = APRM->NUM_CCD;
	Polynomial2D (&ASIP)[2] = CCDs->CCD[NUM_CCD].ASIP;

	int ID;
	SET_POS_DETECTED_CRPIX_GfromLOCAL_G();
	ID=GET_ID_NEAR_CRPIX();
	APRM->CRVAL[0]=REF[ID].POS_CELESTIAL_RADEC[0];
	APRM->CRVAL[1]=REF[ID].POS_CELESTIAL_RADEC[1];

	for(int LOOP = 0; LOOP < 10; ++LOOP){
		SET_POS_CELESTIAL_IMWLDfromRADEC();
		FIT_CbyD(1,1);
		double SCALE=sqrt(-ASIP[0].coeff(1,0)*ASIP[1].coeff(0,1)+ASIP[0].coeff(0,1)*ASIP[1].coeff(1,0));
		if(hypot(ASIP[0].coeff(0,0),ASIP[1].coeff(0,0))/SCALE<0.001){
			break;
		}else{
			APRM->CRVAL[0]+=ASIP[0].coeff(0,0)/cos(APRM->CRVAL[1]*(M_PI/180));
			APRM->CRVAL[1]+=ASIP[1].coeff(0,0);
		}
	}
	CCDs->CCD[NUM_CCD].SET_CDASIP();
	if(APRM->FLAG_STD >= 2){
		double (&CD)[2][2] = CCDs->CCD[NUM_CCD].CD;
		cout<<"-- CRVAL at CRPIX --"<<endl;
		cout<<"CRPIX1 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<APRM->CRPIX[0]<<endl;
		cout<<"CRPIX2 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<APRM->CRPIX[1]<<endl;
		cout<<"CRVAL1 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<APRM->CRVAL[0]<<endl;
		cout<<"CRVAL2 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<APRM->CRVAL[1]<<endl;
		cout<<"-- CD MATRIX --"<<endl;
		cout<<"CD1_1  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<CD[0][0]<<endl;
		cout<<"CD1_2  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<CD[0][1]<<endl;
		cout<<"CD2_1  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<CD[1][0]<<endl;
		cout<<"CD2_2  : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<CD[1][1]<<endl;
	}
}
void CL_REFs::SET_CRPIXatCENTER(){
	APRM->CRPIX[0]=AVE_LOCAL_G[0];
	APRM->CRPIX[1]=AVE_LOCAL_G[1];
}

//REJECTION
void CL_REFs::REJECT_BADREF(){
	if(APRM->FLAG_STD >= 1)cout<<"-- REJECT BAD REFERENCES --"<<endl;

	      if(APRM->MODE_CR=="PIX"||APRM->MODE_CR=="AUTO"){
		if(APRM->MODE_CR=="AUTO"){
			SET_MAXMIN_LOCAL_G();
			SET_CRPIXatCENTER();
		}
		CALC_CRVALatCRPIX();
		SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
		SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();
		CALC_STAT_ASIP();
		if(APRM->FLAG_STD >= 2)cout<<"-- REJECTION by ASIP --"<<endl;
		REJECT_BADREF_ASIP();
		if(APRM->MODE_CR=="AUTO"){
			SET_MAXMIN_LOCAL_G();
			SET_CRPIXatCENTER();
		}
		CALC_CRVALatCRPIX();
		SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
		SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();
		CALC_STAT_ASIP();
	}else if(APRM->MODE_CR=="VAL"){
		CALC_CRPIXatCRVAL();
		SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();
		CALC_STAT_PSIP();
		if(APRM->FLAG_STD >= 2)cout<<"-- REJECTION by PSIP --"<<endl;
		REJECT_BADREF_PSIP();
		CALC_CRPIXatCRVAL();
		SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();
		CALC_STAT_PSIP();
	}
	SET_NUM();
	if(APRM->FLAG_STD >= 2)CCDs->SHOW();
	CCDs->CHECK_NUMFIT();
	CCDs->CHECK_NUMFITALL();

}
void CL_REFs::REJECT_BADREF_ASIP(){
	int    const NUM_REF    = APRM->NUM_REF;
	double const SIGMA_CLIP = APRM->SIGMA_CLIP;
	double (&DIF_RMS_ASIP)[2] = CCDs->CCD[APRM->NUM_CCD].DIF_RMS_ASIP;

	for(int i = 0; i < NUM_REF; ++i){
		double DIFF[2];
		DIFF[0]=REF[i].POS_DETECTED_ASIP_IMPIX_G[0]-REF[i].POS_CELESTIAL_IMPIX_G[0];
		DIFF[1]=REF[i].POS_DETECTED_ASIP_IMPIX_G[1]-REF[i].POS_CELESTIAL_IMPIX_G[1];

		if(fabs(DIFF[0])>SIGMA_CLIP*DIF_RMS_ASIP[0]||fabs(DIFF[1])>SIGMA_CLIP*DIF_RMS_ASIP[1]){
			REF[i].FLAG_OBJ=0;
		}else{
			REF[i].FLAG_OBJ=1;
		}
	}

}
void CL_REFs::REJECT_BADREF_PSIP(){
	int    const NUM_REF    = APRM->NUM_REF;
	double const SIGMA_CLIP = APRM->SIGMA_CLIP;
	double (&DIF_RMS_PSIP)[2] = CCDs->CCD[APRM->NUM_CCD].DIF_RMS_PSIP;

	for(int i = 0; i < NUM_REF; ++i){
		double DIFF[2];
		DIFF[0]=REF[i].POS_CELESTIAL_PSIP_CRPIX_G[0]-REF[i].POS_DETECTED_CRPIX_G[0];
		DIFF[1]=REF[i].POS_CELESTIAL_PSIP_CRPIX_G[1]-REF[i].POS_DETECTED_CRPIX_G[1];
		if(fabs(DIFF[0])>SIGMA_CLIP*DIF_RMS_PSIP[0]||fabs(DIFF[1])>SIGMA_CLIP*DIF_RMS_PSIP[1]){
			REF[i].FLAG_OBJ=0;
		}else{
			REF[i].FLAG_OBJ=1;
		}
	}
}
//CCD POSITION
void CL_REFs::DETERMINE_CCDPOSITION(){
	if(APRM->FLAG_STD >= 1)cout<<"-- DETERMINE CCD POSITIONS --"<<endl;

	int const NUM_REF    = APRM->NUM_REF;
	int const NUM_CCD    = APRM->NUM_CCD;
	int const ORDER_PSIP = APRM->ORDER_PSIP;

	int const                    NUM_COEF = (ORDER_PSIP+1)*(ORDER_PSIP+2)/2;
	ndarray::Array<double, 2, 2> COEF     = ndarray::allocate(2, NUM_COEF);
	ndarray::Array<double, 1, 1> MAXYT    = ndarray::allocate(3*NUM_CCD+2*(NUM_COEF-1));
	ndarray::Array<double, 2, 2> MBXYT    = ndarray::allocate(3*NUM_CCD+2*(NUM_COEF-1), 3*NUM_CCD+2*(NUM_COEF-1));
	ndarray::Array<double, 3, 3> XY       = ndarray::allocate(NUM_REF, (ORDER_PSIP+1)*(ORDER_PSIP+1), (ORDER_PSIP+1)*(ORDER_PSIP+1));
	ndarray::Array<double, 1, 1> XLsYLc   = ndarray::allocate(NUM_REF);
	ndarray::Array<double, 1, 1> YLsXLc   = ndarray::allocate(NUM_REF);
	ndarray::Array<double, 2, 2> XYINIT   = ndarray::allocate(NUM_CCD, 3);
	ndarray::Array<double, 1, 1> XN       = ndarray::allocate((ORDER_PSIP+1)*(ORDER_PSIP+1));
	ndarray::Array<double, 1, 1> YN       = ndarray::allocate((ORDER_PSIP+1)*(ORDER_PSIP+1));

	for(int CID = 0; CID < NUM_CCD; ++CID){
		XYINIT[CID][0]=CCDs->CCD[CID].GPOS_L[0];
		XYINIT[CID][1]=CCDs->CCD[CID].GPOS_L[1];
		XYINIT[CID][2]=CCDs->CCD[CID].GPOS_L[2];
	}


	for(int XYLOOP = 0; XYLOOP < 10; ++XYLOOP){
		SET_POS_DETECTED_LOCAL_GfromLOCAL_L();
		if(APRM->MODE_CR=="PIX"||APRM->MODE_CR=="AUTO"){
			if(APRM->MODE_CR=="AUTO"){
				SET_MAXMIN_LOCAL_G();
				SET_CRPIXatCENTER();
			}
			CALC_CRVALatCRPIX();
		}else if(APRM->MODE_CR=="VAL"){
			CALC_CRPIXatCRVAL();
		}
		SET_POS_CELESTIAL_IMWLDfromRADEC();
		FIT_DbyC(0,1);
		SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD();
//--------------------------------------------------
//XY
		for(int NUM = 0; NUM < NUM_REF; ++NUM){
			XN[0]=1;
			YN[0]=1;
			for(int i=1;i<(ORDER_PSIP+1)*(ORDER_PSIP+1);i++){
				XN[i]=XN[i-1]*REF[NUM].POS_CELESTIAL_IMWLD[0];
				YN[i]=YN[i-1]*REF[NUM].POS_CELESTIAL_IMWLD[1];
			}
			for(int i=0;i<(ORDER_PSIP+1)*(ORDER_PSIP+1);i++)
			for(int j=0;j<(ORDER_PSIP+1)*(ORDER_PSIP+1);j++)
			XY[NUM][i][j] = XN[i]*YN[j];
		}
		for(int NUM = 0; NUM < NUM_REF; ++NUM){
			XLsYLc[NUM]=REF[NUM].POS_DETECTED_LOCAL_L[0]*sin(CCDs->CCD[REF[NUM].ID_CCD].GPOS_L[2])+
				    REF[NUM].POS_DETECTED_LOCAL_L[1]*cos(CCDs->CCD[REF[NUM].ID_CCD].GPOS_L[2]);
			YLsXLc[NUM]=REF[NUM].POS_DETECTED_LOCAL_L[1]*sin(CCDs->CCD[REF[NUM].ID_CCD].GPOS_L[2])-
				    REF[NUM].POS_DETECTED_LOCAL_L[0]*cos(CCDs->CCD[REF[NUM].ID_CCD].GPOS_L[2]);
		}

//--------------------------------------------------
//INIT
		MAXYT.deep() = 0;
		MBXYT.deep() = 0;

//--------------------------------------------------
//dA
//dAXYT
		for(int NUM = 0; NUM < NUM_REF; ++NUM)
		if(REF[NUM].FLAG_OBJ==1){
			MAXYT[0*NUM_CCD+REF[NUM].ID_CCD]-=(REF[NUM].POS_DETECTED_LOCAL_G[0]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[0]);
			MAXYT[1*NUM_CCD+REF[NUM].ID_CCD]-=(REF[NUM].POS_DETECTED_LOCAL_G[1]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[1]);
			MAXYT[2*NUM_CCD+REF[NUM].ID_CCD]-=-XLsYLc[NUM]*(REF[NUM].POS_DETECTED_LOCAL_G[0]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[0])
							     -YLsXLc[NUM]*(REF[NUM].POS_DETECTED_LOCAL_G[1]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[1]);
		}
//dAA
		int ij=0;
		for(int i=0;i<ORDER_PSIP+1  ;i++)
		for(int j=0;j<ORDER_PSIP+1-i;j++)
		if(i+j!=0){
			for(int NUM = 0; NUM < NUM_REF; ++NUM)
			if(REF[NUM].FLAG_OBJ==1){
				MAXYT[3*NUM_CCD+0*(NUM_COEF-1)+ij]-=-(REF[NUM].POS_DETECTED_LOCAL_G[0]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[0])*XY[NUM][i][j];
				MAXYT[3*NUM_CCD+1*(NUM_COEF-1)+ij]-=-(REF[NUM].POS_DETECTED_LOCAL_G[1]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[1])*XY[NUM][i][j];
			}
			ij++;
		}
//--------------------------------------------------
//dB
//dBXYTXYT
		for(int NUM = 0; NUM < NUM_REF; ++NUM)
		if(REF[NUM].FLAG_OBJ==1){
			MBXYT[0*NUM_CCD+REF[NUM].ID_CCD][0*NUM_CCD+REF[NUM].ID_CCD]+=1;
//			MBXYT[0*NUM_CCD+REF[NUM].ID_CCD][1*NUM_CCD+REF[NUM].ID_CCD]+=0;
			MBXYT[0*NUM_CCD+REF[NUM].ID_CCD][2*NUM_CCD+REF[NUM].ID_CCD]+=-XLsYLc[NUM];
//			MBXYT[1*NUM_CCD+REF[NUM].ID_CCD][0*NUM_CCD+REF[NUM].ID_CCD]+=0;
			MBXYT[1*NUM_CCD+REF[NUM].ID_CCD][1*NUM_CCD+REF[NUM].ID_CCD]+=1;
			MBXYT[1*NUM_CCD+REF[NUM].ID_CCD][2*NUM_CCD+REF[NUM].ID_CCD]+=-YLsXLc[NUM];
			MBXYT[2*NUM_CCD+REF[NUM].ID_CCD][0*NUM_CCD+REF[NUM].ID_CCD]+=-XLsYLc[NUM];
			MBXYT[2*NUM_CCD+REF[NUM].ID_CCD][1*NUM_CCD+REF[NUM].ID_CCD]+=-YLsXLc[NUM];
			MBXYT[2*NUM_CCD+REF[NUM].ID_CCD][2*NUM_CCD+REF[NUM].ID_CCD]+= XLsYLc[NUM]*XLsYLc[NUM]+YLsXLc[NUM]*YLsXLc[NUM];
		}
//dBXYTA

		ij=0;
		for(int i=0;i<ORDER_PSIP+1  ;i++)
		for(int j=0;j<ORDER_PSIP+1-i;j++)
		if(i+j!=0){
			for(int NUM = 0; NUM < NUM_REF; ++NUM)
			if(REF[NUM].FLAG_OBJ==1){
				MBXYT[0*NUM_CCD+REF[NUM].ID_CCD][3*NUM_CCD+0*(NUM_COEF-1)+ij]+=-XY[NUM][i][j];
				MBXYT[1*NUM_CCD+REF[NUM].ID_CCD][3*NUM_CCD+1*(NUM_COEF-1)+ij]+=-XY[NUM][i][j];
				MBXYT[2*NUM_CCD+REF[NUM].ID_CCD][3*NUM_CCD+0*(NUM_COEF-1)+ij]+=-XY[NUM][i][j]*(-XLsYLc[NUM]);
				MBXYT[2*NUM_CCD+REF[NUM].ID_CCD][3*NUM_CCD+1*(NUM_COEF-1)+ij]+=-XY[NUM][i][j]*(-YLsXLc[NUM]);
			}
			ij++;
		}
//dBAXYT

		ij=0;
		for(int i=0;i<ORDER_PSIP+1  ;i++)
		for(int j=0;j<ORDER_PSIP+1-i;j++)
		if(i+j!=0){
			for(int NUM = 0; NUM < NUM_REF; ++NUM)
			if(REF[NUM].FLAG_OBJ==1){
				MBXYT[3*NUM_CCD+0*(NUM_COEF-1)+ij][0*NUM_CCD+REF[NUM].ID_CCD]+=-XY[NUM][i][j];
				MBXYT[3*NUM_CCD+1*(NUM_COEF-1)+ij][1*NUM_CCD+REF[NUM].ID_CCD]+=-XY[NUM][i][j];
				MBXYT[3*NUM_CCD+0*(NUM_COEF-1)+ij][2*NUM_CCD+REF[NUM].ID_CCD]+=-XY[NUM][i][j]*(-XLsYLc[NUM]);
				MBXYT[3*NUM_CCD+1*(NUM_COEF-1)+ij][2*NUM_CCD+REF[NUM].ID_CCD]+=-XY[NUM][i][j]*(-YLsXLc[NUM]);
			}
			ij++;
		}
//dBAA

		ij=0;
		for(int i=0;i<ORDER_PSIP+1  ;i++)
		for(int j=0;j<ORDER_PSIP+1-i;j++)
		if(i+j!=0){
			int kl=0;
			for(int k=0;k<ORDER_PSIP+1  ;k++)
			for(int l=0;l<ORDER_PSIP+1-k;l++)
			if(k+l!=0){
				for(int NUM = 0; NUM < NUM_REF; ++NUM)
				if(REF[NUM].FLAG_OBJ==1){
					MBXYT[3*NUM_CCD+0*(NUM_COEF-1)+ij][3*NUM_CCD+0*(NUM_COEF-1)+kl]+=XY[NUM][i+k][j+l];

//					MBXYT[3*NUM_CCD+0*(NUM_COEF-1)+ij][3*NUM_CCD+1*(NUM_COEF-1)+kl]+=0;
//					MBXYT[3*NUM_CCD+1*(NUM_COEF-1)+ij][3*NUM_CCD+0*(NUM_COEF-1)+kl]+=0;
					MBXYT[3*NUM_CCD+1*(NUM_COEF-1)+ij][3*NUM_CCD+1*(NUM_COEF-1)+kl]+=XY[NUM][i+k][j+l];
				}
				kl++;
			}
			ij++;
		}
//--------------------------------------------------
		// C = B^{-1} A
		ndarray::Array<double, 1, 1> MCXYT = SOLVE_LINEAR_EQUATION(MBXYT, MAXYT);

		for(int CID = 0; CID < NUM_CCD; ++CID){
			CCDs->CCD[CID].GPOS_L[0]+=MCXYT[0*NUM_CCD+CID];
			CCDs->CCD[CID].GPOS_L[1]+=MCXYT[1*NUM_CCD+CID];
			CCDs->CCD[CID].GPOS_L[2]+=MCXYT[2*NUM_CCD+CID];
			CCDs->CCD[CID].GPOS_L[3]=CCDs->CCD[CID].GPOS_L[2]*(180/M_PI);
		}
		SET_CCDAVE();

//--------------------------------------------------

		double const PRECISION_CCD = APRM->PRECISION_CCD;
		int ENDFLAG=1;
		for(int CID = 0; CID < NUM_CCD; ++CID)
		if(hypot(XYINIT[CID][0]-CCDs->CCD[CID].GPOS_L[0],
			 XYINIT[CID][1]-CCDs->CCD[CID].GPOS_L[1])>PRECISION_CCD||
		    fabs(XYINIT[CID][2]-CCDs->CCD[CID].GPOS_L[2])>PRECISION_CCD/5000)
		ENDFLAG=0;

		if(ENDFLAG==1){
			break;
		}else{
			if(APRM->FLAG_STD >= 2)cout << "CCD GPOS LOOP : " << XYLOOP+1 << endl;
			for(int CID = 0; CID < NUM_CCD; ++CID){
				XYINIT[CID][0]=CCDs->CCD[CID].GPOS_L[0];
				XYINIT[CID][1]=CCDs->CCD[CID].GPOS_L[1];
				XYINIT[CID][2]=CCDs->CCD[CID].GPOS_L[2];
			}
		}

	}

	if(APRM->FLAG_STD >= 2)CCDs->SHOW();
}
void CL_REFs::SET_CCDAVE(){
	int const NUM_CCD    = APRM->NUM_CCD;

	double GPOS[3];

	GPOS[2]=0;
	int AVENUM=0;
	for(int CID = 0; CID < NUM_CCD; ++CID)
	if(CID<100){
		GPOS[2]+=CCDs->CCD[CID].GPOS_L[2];
		AVENUM++;
	}
	GPOS[2]/=AVENUM;

	double DX,DY,DT;
	DT=-(GPOS[2]-CCDs->GPOS_C_BASIS[2]);
	for(int CID = 0; CID < NUM_CCD; ++CID){
		DX=CCDs->CCD[CID].GPOS_L[0]*cos(DT)-CCDs->CCD[CID].GPOS_L[1]*sin(DT);
		DY=CCDs->CCD[CID].GPOS_L[1]*cos(DT)+CCDs->CCD[CID].GPOS_L[0]*sin(DT);
		CCDs->CCD[CID].GPOS_L[0] =DX;
		CCDs->CCD[CID].GPOS_L[1] =DY;
		CCDs->CCD[CID].GPOS_L[2]+=DT;
		CCDs->CCD[CID].GPOS_L[3] =CCDs->CCD[CID].GPOS_L[2]*(180/M_PI);
	}
//---------------------------------------------
	CCDs->GET_GPOS_CfromGPOS_L();

	AVENUM=0;
	GPOS[0]=GPOS[1]=0;
	for(int CID = 0; CID < NUM_CCD; ++CID)
	if(CID<100){
		GPOS[0]+=CCDs->CCD[CID].GPOS_C[0];
		GPOS[1]+=CCDs->CCD[CID].GPOS_C[1];
		AVENUM++;
	}
	GPOS[0]/=AVENUM;
	GPOS[1]/=AVENUM;

	double BASIS[2];
	BASIS[0]=CCDs->GPOS_C_BASIS[0]*cos(CCDs->GPOS_C_BASIS[2])-CCDs->GPOS_C_BASIS[1]*sin(CCDs->GPOS_C_BASIS[2]);
	BASIS[1]=CCDs->GPOS_C_BASIS[1]*cos(CCDs->GPOS_C_BASIS[2])+CCDs->GPOS_C_BASIS[0]*sin(CCDs->GPOS_C_BASIS[2]);
	for(int CID = 0; CID < NUM_CCD; ++CID){
		CCDs->CCD[CID].GPOS_C[0]-=GPOS[0]-BASIS[0];
		CCDs->CCD[CID].GPOS_C[1]-=GPOS[1]-BASIS[1];
	}

	CCDs->GET_GPOS_LfromGPOS_C();
}
bool  CL_REFs::CHECK(){
	return true;
}
//SIP,PSIP
void CL_REFs::DETERMINE_TANSIP(){
//CALC TANSIP
	if(APRM->FLAG_STD >= 1)cout<<"-- CALC TANSIP --"<<endl;
	CALC_TANSIP();
//CALC OPTICAL DISTORTION
	if(APRM->FLAG_STD >= 1)cout<<"-- CALC OPTICAL DISTORTION --"<<endl;
	CALC_OPTICAL_DISTORTION();

//SET CCD (CRPIX CD SIP DIST OA)
	if(APRM->FLAG_STD >= 1)cout<<"-- SET CCD --"<<endl;
	CCDs->SET_CCDs();

//SET POS REFERENCES();
	if(APRM->FLAG_STD >= 1)cout<<"-- SET REFERENCES --"<<endl;
	SET_POS_DETECTED_ALL();
	SET_POS_CELESTIAL_ALL();

//CALC LOCAL RMS
	CALC_STAT_SIP_LOCAL();

	if(APRM->FLAG_STD >= 2)CCDs->CCD[APRM->NUM_CCD].SHOW();
//	if(APRM->FLAG_STD >= 2)CCDs->CCD[0].SHOW();
	if(APRM->NUM_CCD>=49) { // assumes HSC, and show DET-ID=50
	  if(APRM->FLAG_STD >= 2)CCDs->CCD[49].SHOW();
	}
	else { // assumes SC, and show DET-ID=5
	  if(APRM->FLAG_STD >= 2)CCDs->CCD[4].SHOW();
	}
//	if(APRM->NUM_CCD>103)
//	if(APRM->FLAG_STD >= 2)CCDs->CCD[100].SHOW();

}
void CL_REFs::CALC_TANSIP(){
	int const NUM_CCD    = APRM->NUM_CCD;
//SET CR
	SET_POS_DETECTED_LOCAL_GfromLOCAL_L();
	if(APRM->MODE_CR=="PIX"||APRM->MODE_CR=="AUTO"){
		if(APRM->MODE_CR=="AUTO"){
			SET_MAXMIN_LOCAL_G();
			SET_CRPIXatCENTER();
		}
		CALC_CRVALatCRPIX();
	}else if(APRM->MODE_CR=="VAL"){
		CALC_CRPIXatCRVAL();
	}

//CALC CD AND SIP GLOBAL
	SET_POS_CELESTIAL_IMWLDfromRADEC();
	SET_POS_DETECTED_CRPIX_GfromLOCAL_G();
	FIT_CbyD(1,1);
	CCDs->CCD[NUM_CCD].SET_CDASIP();
	SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();
	SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
	CALC_STAT_ASIP();

	FIT_DbyC(1,2);
	CCDs->CCD[NUM_CCD].SET_CDPSIP();
	SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();
	CALC_STAT_PSIP();

	SET_DIFF();
	SET_MAXMIN_CRPIX_G();
}
//DISTORTION
void CL_REFs::CALC_OPTICAL_DISTORTION(){
	Polynomial2D (&PSIP)[2] = CCDs->CCD[APRM->NUM_CCD].PSIP;
	PSIP_DX[0] = PSIP[0].dx();
	PSIP_DY[0] = PSIP[0].dy();
	PSIP_DX[1] = PSIP[1].dx();
	PSIP_DY[1] = PSIP[1].dy();

	SET_OPTICAL_DISTORTIONbyPSIP();
	FIT_DIST();
	CALC_OPTICAL_AXIS();
}
void CL_REFs::FIT_DIST(){
	int const NUM_REF    = APRM->NUM_REF;
	int const ORDER_PSIP = APRM->ORDER_PSIP;

	ndarray::Array<double, 2, 2> dC = ndarray::allocate(NUM_REF,3);
	ndarray::Array<double, 2, 2> dR = ndarray::allocate(NUM_REF,3);
	ndarray::Array<double, 2, 2> dS1= ndarray::allocate(NUM_REF,3);
	ndarray::Array<double, 2, 2> dS2= ndarray::allocate(NUM_REF,3);
	ndarray::Array<double, 2, 2> dM = ndarray::allocate(NUM_REF,3);
	ndarray::Array<double, 2, 2> dJ = ndarray::allocate(NUM_REF,3);

	APRM->NUM_FIT=0;
	for(int i = 0; i < NUM_REF; ++i)
	if(REF[i].FLAG_OBJ==1){
		double C[2],D[6];

		C[0]=REF[i].POS_CELESTIAL_IMPIX_G[0];
		C[1]=REF[i].POS_CELESTIAL_IMPIX_G[1];
		D[0]=REF[i].CAMERA_CONV;
		D[1]=REF[i].CAMERA_ROT;
		D[2]=REF[i].CAMERA_SHEAR[0];
		D[3]=REF[i].CAMERA_SHEAR[1];
		D[4]=REF[i].CAMERA_MAG;
		D[5]=REF[i].CAMERA_JACO;

		 dC[APRM->NUM_FIT][0]=dR[APRM->NUM_FIT][0]=dS1[APRM->NUM_FIT][0]=dS2[APRM->NUM_FIT][0]=dM[APRM->NUM_FIT][0]=dJ[APRM->NUM_FIT][0]=C[0];
		 dC[APRM->NUM_FIT][1]=dR[APRM->NUM_FIT][1]=dS1[APRM->NUM_FIT][1]=dS2[APRM->NUM_FIT][1]=dM[APRM->NUM_FIT][1]=dJ[APRM->NUM_FIT][1]=C[1];
		 dC[APRM->NUM_FIT][2]=D[0];
		 dR[APRM->NUM_FIT][2]=D[1];
		dS1[APRM->NUM_FIT][2]=D[2];
		dS2[APRM->NUM_FIT][2]=D[3];
		 dM[APRM->NUM_FIT][2]=D[4];
		 dJ[APRM->NUM_FIT][2]=D[5];
		APRM->NUM_FIT+=1;
	}

	CCDs->CCD[APRM->NUM_CCD].PSIP_CONV     = CALC_FIT_LS2(APRM->NUM_FIT,ORDER_PSIP-1,dC );
	CCDs->CCD[APRM->NUM_CCD].PSIP_ROT      = CALC_FIT_LS2(APRM->NUM_FIT,ORDER_PSIP-1,dR );
	CCDs->CCD[APRM->NUM_CCD].PSIP_SHEAR[0] = CALC_FIT_LS2(APRM->NUM_FIT,ORDER_PSIP-1,dS1);
	CCDs->CCD[APRM->NUM_CCD].PSIP_SHEAR[1] = CALC_FIT_LS2(APRM->NUM_FIT,ORDER_PSIP-1,dS2);
	CCDs->CCD[APRM->NUM_CCD].PSIP_MAG      = CALC_FIT_LS2(APRM->NUM_FIT,ORDER_PSIP-1,dM );
	CCDs->CCD[APRM->NUM_CCD].PSIP_JACO     = CALC_FIT_LS2(APRM->NUM_FIT,ORDER_PSIP-1,dJ );
}
void CL_REFs::CALC_OPTICAL_AXIS(){
	Polynomial2D& PSIP_JACO = CCDs->CCD[APRM->NUM_CCD].PSIP_JACO;

	Polynomial2D JDX = PSIP_JACO.dx();
	Polynomial2D JDY = PSIP_JACO.dy();

	Polynomial2D JDXDX = JDX.dx();
	Polynomial2D JDXDY = JDX.dy();
	Polynomial2D JDYDX = JDY.dx();
	Polynomial2D JDYDY = JDY.dy();

	double PX=APRM->CRPIX[0];
	double PY=APRM->CRPIX[1];

	for(int LOOP=0;LOOP<10;LOOP++){
		double V_JDX   = JDX  (PX, PY);
		double V_JDY   = JDY  (PX, PY);
		double V_JDXDX = JDXDX(PX, PY);
		double V_JDXDY = JDXDY(PX, PY);
		double V_JDYDX = JDYDX(PX, PY);
		double V_JDYDY = JDYDY(PX, PY);

		if(hypot((V_JDX/V_JDXDX),(V_JDY/V_JDYDY)) > 0.01){
			// P -= H^{-1} \nabla f
			double Idet = 1.0 / (V_JDXDX*V_JDYDY - V_JDXDY*V_JDYDX);
			PX -= Idet * (V_JDYDY*V_JDX - V_JDXDY*V_JDY);
			PY -= Idet * (V_JDXDX*V_JDY - V_JDYDX*V_JDX);
		}else{
			break;
		}
	}
	CCDs->CCD[APRM->NUM_CCD].OAPIX[0]=PX;
	CCDs->CCD[APRM->NUM_CCD].OAPIX[1]=PY;
}

//REF
void CL_REF::SET_INIT(CL_CCD*  CCD_IN,CL_CCD*  GCD_IN){
	CCD=CCD_IN;
	GCD=GCD_IN;
}
//REF::POS
void CL_REF::SET_POS_DETECTED_LOCAL_CfromLOCAL_L(){
	POS_DETECTED_LOCAL_C[0]=POS_DETECTED_LOCAL_L[0]-0.5*(CCD->LENGTH[0]);
	POS_DETECTED_LOCAL_C[1]=POS_DETECTED_LOCAL_L[1]-0.5*(CCD->LENGTH[1]);
}
void CL_REF::SET_POS_DETECTED_LOCAL_GfromLOCAL_L(){
	POS_DETECTED_LOCAL_G[0]=POS_DETECTED_LOCAL_L[0]*cos(CCD->GPOS_L[2])-POS_DETECTED_LOCAL_L[1]*sin(CCD->GPOS_L[2])+CCD->GPOS_L[0];
	POS_DETECTED_LOCAL_G[1]=POS_DETECTED_LOCAL_L[1]*cos(CCD->GPOS_L[2])+POS_DETECTED_LOCAL_L[0]*sin(CCD->GPOS_L[2])+CCD->GPOS_L[1];
}
void CL_REF::SET_POS_DETECTED_CRPIX_GfromLOCAL_G(){
	POS_DETECTED_CRPIX_G[0]=POS_DETECTED_LOCAL_G[0]-APRM->CRPIX[0];
	POS_DETECTED_CRPIX_G[1]=POS_DETECTED_LOCAL_G[1]-APRM->CRPIX[1];
}
void CL_REF::SET_POS_DETECTED_CRPIX_LfromLOCAL_L(){
	POS_DETECTED_CRPIX_L[0]=POS_DETECTED_LOCAL_L[0]-*CCD->CRPIX[0];
	POS_DETECTED_CRPIX_L[1]=POS_DETECTED_LOCAL_L[1]-*CCD->CRPIX[1];
}
void CL_REF::SET_POS_DETECTED_IMPIX_LfromCRPIX_L(){
	POS_DETECTED_IMPIX_L[0]=POS_DETECTED_CRPIX_L[0];
	POS_DETECTED_IMPIX_L[1]=POS_DETECTED_CRPIX_L[1];
}
void CL_REF::SET_POS_DETECTED_IMPIX_GfromCRPIX_G(){
	POS_DETECTED_IMPIX_G[0]=POS_DETECTED_CRPIX_G[0];
	POS_DETECTED_IMPIX_G[1]=POS_DETECTED_CRPIX_G[1];
}
void CL_REF::SET_POS_DETECTED_IMWLD_LfromIMPIX_L(){
	POS_DETECTED_IMWLD_L[0]=CCD->CD[0][0]*POS_DETECTED_IMPIX_L[0]+CCD->CD[0][1]*POS_DETECTED_IMPIX_L[1];
	POS_DETECTED_IMWLD_L[1]=CCD->CD[1][0]*POS_DETECTED_IMPIX_L[0]+CCD->CD[1][1]*POS_DETECTED_IMPIX_L[1];
}
void CL_REF::SET_POS_DETECTED_IMWLD_GfromIMPIX_G(){
	POS_DETECTED_IMWLD_G[0]=GCD->CD[0][0]*POS_DETECTED_IMPIX_G[0]+GCD->CD[0][1]*POS_DETECTED_IMPIX_G[1];
	POS_DETECTED_IMWLD_G[1]=GCD->CD[1][0]*POS_DETECTED_IMPIX_G[0]+GCD->CD[1][1]*POS_DETECTED_IMPIX_G[1];
}
void CL_REF::SET_POS_DETECTED_RADEC_LfromIMWLD_L(){
	double NRAD[2];//native psi,theta (RAD)
	double RADECrad[2],IMWLDrad[2],CRVALrad[2];
	CRVALrad[0]=APRM->CRVAL[0]*(M_PI/180);
	CRVALrad[1]=APRM->CRVAL[1]*(M_PI/180);
	IMWLDrad[0]=POS_DETECTED_IMWLD_L[0]*(M_PI/180);
	IMWLDrad[1]=POS_DETECTED_IMWLD_L[1]*(M_PI/180);

	NRAD[0]=atan2(IMWLDrad[0],-IMWLDrad[1]);
	NRAD[1]=atan(sqrt(IMWLDrad[0]*IMWLDrad[0]+IMWLDrad[1]*IMWLDrad[1]));
	if(NRAD[0]<0)
	NRAD[0]+=2*M_PI;
	if(NRAD[0]>2*M_PI)
	NRAD[0]-=2*M_PI;

	RADECrad[1]=asin(sin(NRAD[1])*sin(CRVALrad[1])+cos(NRAD[1])*cos(NRAD[0]-M_PI)*cos(CRVALrad[1]));
	RADECrad[0]=atan2(-cos(NRAD[1])*sin(NRAD[0]-M_PI),sin(NRAD[1])*cos(CRVALrad[1])-cos(NRAD[1])*cos(NRAD[0]-M_PI)*sin(CRVALrad[1]))+CRVALrad[0];
	POS_DETECTED_RADEC_L[0]=RADECrad[0]*(180/M_PI);
	POS_DETECTED_RADEC_L[1]=RADECrad[1]*(180/M_PI);
}
void CL_REF::SET_POS_DETECTED_RADEC_GfromIMWLD_G(){
	double NRAD[2];//native psi,theta (RAD)
	double RADECrad[2],IMWLDrad[2],CRVALrad[2];
	CRVALrad[0]=APRM->CRVAL[0]*(M_PI/180);
	CRVALrad[1]=APRM->CRVAL[1]*(M_PI/180);
	IMWLDrad[0]=POS_DETECTED_IMWLD_G[0]*(M_PI/180);
	IMWLDrad[1]=POS_DETECTED_IMWLD_G[1]*(M_PI/180);

	NRAD[0]=atan2(IMWLDrad[0],-IMWLDrad[1]);
	NRAD[1]=atan(sqrt(IMWLDrad[0]*IMWLDrad[0]+IMWLDrad[1]*IMWLDrad[1]));
	if(NRAD[0]<0)
	NRAD[0]+=2*M_PI;
	if(NRAD[0]>2*M_PI)
	NRAD[0]-=2*M_PI;

	RADECrad[1]=asin(sin(NRAD[1])*sin(CRVALrad[1])+cos(NRAD[1])*cos(NRAD[0]-M_PI)*cos(CRVALrad[1]));
	RADECrad[0]=atan2(-cos(NRAD[1])*sin(NRAD[0]-M_PI),sin(NRAD[1])*cos(CRVALrad[1])-cos(NRAD[1])*cos(NRAD[0]-M_PI)*sin(CRVALrad[1]))+CRVALrad[0];
	POS_DETECTED_RADEC_G[0]=RADECrad[0]*(180/M_PI);
	POS_DETECTED_RADEC_G[1]=RADECrad[1]*(180/M_PI);
}
void CL_REF::SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L(){
	POS_DETECTED_ASIP_IMPIX_L[0]=POS_DETECTED_CRPIX_L[0] + CCD->ASIP[0](POS_DETECTED_CRPIX_L[0], POS_DETECTED_CRPIX_L[1]);
	POS_DETECTED_ASIP_IMPIX_L[1]=POS_DETECTED_CRPIX_L[1] + CCD->ASIP[1](POS_DETECTED_CRPIX_L[0], POS_DETECTED_CRPIX_L[1]);
}
void CL_REF::SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G(){
	POS_DETECTED_ASIP_IMPIX_G[0]=POS_DETECTED_CRPIX_G[0] + GCD->ASIP[0](POS_DETECTED_CRPIX_G[0], POS_DETECTED_CRPIX_G[1]);
	POS_DETECTED_ASIP_IMPIX_G[1]=POS_DETECTED_CRPIX_G[1] + GCD->ASIP[1](POS_DETECTED_CRPIX_G[0], POS_DETECTED_CRPIX_G[1]);
}
void CL_REF::SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L(){
	POS_DETECTED_ASIP_IMWLD_L[0]=CCD->CD[0][0]*POS_DETECTED_ASIP_IMPIX_L[0]+CCD->CD[0][1]*POS_DETECTED_ASIP_IMPIX_L[1];
	POS_DETECTED_ASIP_IMWLD_L[1]=CCD->CD[1][0]*POS_DETECTED_ASIP_IMPIX_L[0]+CCD->CD[1][1]*POS_DETECTED_ASIP_IMPIX_L[1];
}
void CL_REF::SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G(){
	POS_DETECTED_ASIP_IMWLD_G[0]=GCD->CD[0][0]*POS_DETECTED_ASIP_IMPIX_G[0]+GCD->CD[0][1]*POS_DETECTED_ASIP_IMPIX_G[1];
	POS_DETECTED_ASIP_IMWLD_G[1]=GCD->CD[1][0]*POS_DETECTED_ASIP_IMPIX_G[0]+GCD->CD[1][1]*POS_DETECTED_ASIP_IMPIX_G[1];
}
void CL_REF::SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L(){
	double NRAD[2];//native psi,theta (RAD)
	double RADECrad[2],IMWLDrad[2],CRVALrad[2];
	CRVALrad[0]=APRM->CRVAL[0]*(M_PI/180);
	CRVALrad[1]=APRM->CRVAL[1]*(M_PI/180);
	IMWLDrad[0]=POS_DETECTED_ASIP_IMWLD_L[0]*(M_PI/180);
	IMWLDrad[1]=POS_DETECTED_ASIP_IMWLD_L[1]*(M_PI/180);

	NRAD[0]=atan2(IMWLDrad[0],-IMWLDrad[1]);
	NRAD[1]=atan(sqrt(IMWLDrad[0]*IMWLDrad[0]+IMWLDrad[1]*IMWLDrad[1]));
	if(NRAD[0]<0)
	NRAD[0]+=2*M_PI;
	if(NRAD[0]>2*M_PI)
	NRAD[0]-=2*M_PI;

	RADECrad[1]=asin(sin(NRAD[1])*sin(CRVALrad[1])+cos(NRAD[1])*cos(NRAD[0]-M_PI)*cos(CRVALrad[1]));
	RADECrad[0]=atan2(-cos(NRAD[1])*sin(NRAD[0]-M_PI),sin(NRAD[1])*cos(CRVALrad[1])-cos(NRAD[1])*cos(NRAD[0]-M_PI)*sin(CRVALrad[1]))+CRVALrad[0];
	POS_DETECTED_ASIP_RADEC_L[0]=RADECrad[0]*(180/M_PI);
	POS_DETECTED_ASIP_RADEC_L[1]=RADECrad[1]*(180/M_PI);
}
void CL_REF::SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G(){
	double NRAD[2];//native psi,theta (RAD)
	double RADECrad[2],IMWLDrad[2],CRVALrad[2];
	CRVALrad[0]=APRM->CRVAL[0]*(M_PI/180);
	CRVALrad[1]=APRM->CRVAL[1]*(M_PI/180);
	IMWLDrad[0]=POS_DETECTED_ASIP_IMWLD_G[0]*(M_PI/180);
	IMWLDrad[1]=POS_DETECTED_ASIP_IMWLD_G[1]*(M_PI/180);

	NRAD[0]=atan2(IMWLDrad[0],-IMWLDrad[1]);
	NRAD[1]=atan(sqrt(IMWLDrad[0]*IMWLDrad[0]+IMWLDrad[1]*IMWLDrad[1]));
	if(NRAD[0]<0)
	NRAD[0]+=2*M_PI;
	if(NRAD[0]>2*M_PI)
	NRAD[0]-=2*M_PI;

	RADECrad[1]=asin(sin(NRAD[1])*sin(CRVALrad[1])+cos(NRAD[1])*cos(NRAD[0]-M_PI)*cos(CRVALrad[1]));
	RADECrad[0]=atan2(-cos(NRAD[1])*sin(NRAD[0]-M_PI),sin(NRAD[1])*cos(CRVALrad[1])-cos(NRAD[1])*cos(NRAD[0]-M_PI)*sin(CRVALrad[1]))+CRVALrad[0];
	POS_DETECTED_ASIP_RADEC_G[0]=RADECrad[0]*(180/M_PI);
	POS_DETECTED_ASIP_RADEC_G[1]=RADECrad[1]*(180/M_PI);
}
void CL_REF::SET_POS_CELESTIAL_IMWLDfromRADEC(){
	double NRAD[2];//native psi,theta (RAD)
	double RADECrad[2],CRVALrad[2],IMWLDrad[2];
	RADECrad[0]=POS_CELESTIAL_RADEC[0]*(M_PI/180);
	RADECrad[1]=POS_CELESTIAL_RADEC[1]*(M_PI/180);
	CRVALrad[0]=APRM->CRVAL[0]*(M_PI/180);
	CRVALrad[1]=APRM->CRVAL[1]*(M_PI/180);

	if(hypot(RADECrad[0]-CRVALrad[0],RADECrad[1]-CRVALrad[1])<0.00000001){
		NRAD[0]=M_PI;
		NRAD[1]=M_PI*0.5;
	}else{
		NRAD[1]=asin(sin(RADECrad[1])*sin(CRVALrad[1])+cos(RADECrad[1])*cos(CRVALrad[1])*cos(RADECrad[0]-CRVALrad[0]));
		NRAD[0]=atan2( -cos(RADECrad[1])*sin(RADECrad[0]-CRVALrad[0]),
			sin(RADECrad[1])*cos(CRVALrad[1])
		-cos(RADECrad[1])*sin(CRVALrad[1])*cos(RADECrad[0]-CRVALrad[0]))+M_PI;
	}

	IMWLDrad[0]= 1.0/tan(NRAD[1])*sin(NRAD[0]);
	IMWLDrad[1]=-1.0/tan(NRAD[1])*cos(NRAD[0]);
	POS_CELESTIAL_IMWLD[0]=IMWLDrad[0]*(180/M_PI);
	POS_CELESTIAL_IMWLD[1]=IMWLDrad[1]*(180/M_PI);
}
void CL_REF::SET_POS_CELESTIAL_IMPIX_GfromIMWLD(){
	POS_CELESTIAL_IMPIX_G[0]=GCD->InvCD[0][0]*POS_CELESTIAL_IMWLD[0]+GCD->InvCD[0][1]*POS_CELESTIAL_IMWLD[1];
	POS_CELESTIAL_IMPIX_G[1]=GCD->InvCD[1][0]*POS_CELESTIAL_IMWLD[0]+GCD->InvCD[1][1]*POS_CELESTIAL_IMWLD[1];
}
void CL_REF::SET_POS_CELESTIAL_IMPIX_LfromIMWLD(){
	POS_CELESTIAL_IMPIX_L[0]=CCD->InvCD[0][0]*POS_CELESTIAL_IMWLD[0]+CCD->InvCD[0][1]*POS_CELESTIAL_IMWLD[1];
	POS_CELESTIAL_IMPIX_L[1]=CCD->InvCD[1][0]*POS_CELESTIAL_IMWLD[0]+CCD->InvCD[1][1]*POS_CELESTIAL_IMWLD[1];
}
void CL_REF::SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G(){
	POS_CELESTIAL_CRPIX_G[0]=POS_CELESTIAL_IMPIX_G[0];
	POS_CELESTIAL_CRPIX_G[1]=POS_CELESTIAL_IMPIX_G[1];
}
void CL_REF::SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L(){
	POS_CELESTIAL_CRPIX_L[0]=POS_CELESTIAL_IMPIX_L[0];
	POS_CELESTIAL_CRPIX_L[1]=POS_CELESTIAL_IMPIX_L[1];
}
void CL_REF::SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G(){
	POS_CELESTIAL_LOCAL_G[0]=POS_CELESTIAL_CRPIX_G[0]+APRM->CRPIX[0];
	POS_CELESTIAL_LOCAL_G[1]=POS_CELESTIAL_CRPIX_G[1]+APRM->CRPIX[1];
}
void CL_REF::SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L(){
	POS_CELESTIAL_LOCAL_L[0]=POS_CELESTIAL_CRPIX_L[0]+*CCD->CRPIX[0];
	POS_CELESTIAL_LOCAL_L[1]=POS_CELESTIAL_CRPIX_L[1]+*CCD->CRPIX[1];
}
void CL_REF::SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD(){
	POS_CELESTIAL_PSIP_LOCAL_G[0] = GCD->PSIP[0](POS_CELESTIAL_IMWLD[0], POS_CELESTIAL_IMWLD[1]);
	POS_CELESTIAL_PSIP_LOCAL_G[1] = GCD->PSIP[1](POS_CELESTIAL_IMWLD[0], POS_CELESTIAL_IMWLD[1]);
}
void CL_REF::SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G(){
	POS_CELESTIAL_PSIP_CRPIX_G[0]=POS_CELESTIAL_IMPIX_G[0] + GCD->PSIP[0](POS_CELESTIAL_IMPIX_G[0], POS_CELESTIAL_IMPIX_G[1]);
	POS_CELESTIAL_PSIP_CRPIX_G[1]=POS_CELESTIAL_IMPIX_G[1] + GCD->PSIP[1](POS_CELESTIAL_IMPIX_G[0], POS_CELESTIAL_IMPIX_G[1]);
}
void CL_REF::SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L(){
	POS_CELESTIAL_PSIP_CRPIX_L[0]=POS_CELESTIAL_IMPIX_L[0] + CCD->PSIP[0](POS_CELESTIAL_IMPIX_L[0], POS_CELESTIAL_IMPIX_L[1]);
	POS_CELESTIAL_PSIP_CRPIX_L[1]=POS_CELESTIAL_IMPIX_L[1] + CCD->PSIP[1](POS_CELESTIAL_IMPIX_L[0], POS_CELESTIAL_IMPIX_L[1]);
}
void CL_REF::SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G(){
	POS_CELESTIAL_PSIP_LOCAL_G[0]=POS_CELESTIAL_PSIP_CRPIX_G[0]+APRM->CRPIX[0];
	POS_CELESTIAL_PSIP_LOCAL_G[1]=POS_CELESTIAL_PSIP_CRPIX_G[1]+APRM->CRPIX[1];
}
void CL_REF::SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L(){
	POS_CELESTIAL_PSIP_LOCAL_L[0]=POS_CELESTIAL_PSIP_CRPIX_L[0]+*CCD->CRPIX[0];
	POS_CELESTIAL_PSIP_LOCAL_L[1]=POS_CELESTIAL_PSIP_CRPIX_L[1]+*CCD->CRPIX[1];
}
void CL_REF::SET_DIFF(){
	DIFF_ASIP[0]=POS_DETECTED_ASIP_IMPIX_G[0]-POS_CELESTIAL_IMPIX_G[0];
	DIFF_ASIP[1]=POS_DETECTED_ASIP_IMPIX_G[1]-POS_CELESTIAL_IMPIX_G[1];
	DIFF_PSIP[0]=POS_CELESTIAL_PSIP_CRPIX_G[0]-POS_DETECTED_CRPIX_G[0];
	DIFF_PSIP[1]=POS_CELESTIAL_PSIP_CRPIX_G[1]-POS_DETECTED_CRPIX_G[1];
}
void CL_REF::SET_OPTICAL_DISTORTIONbyPSIP(){
	double dCdI[2][2];

	dCdI[0][0] = REFs->PSIP_DX[0](POS_CELESTIAL_IMPIX_G[0], POS_CELESTIAL_IMPIX_G[1]);
	dCdI[0][1] = REFs->PSIP_DY[0](POS_CELESTIAL_IMPIX_G[0], POS_CELESTIAL_IMPIX_G[1]);
	dCdI[1][0] = REFs->PSIP_DX[1](POS_CELESTIAL_IMPIX_G[0], POS_CELESTIAL_IMPIX_G[1]);
	dCdI[1][1] = REFs->PSIP_DY[1](POS_CELESTIAL_IMPIX_G[0], POS_CELESTIAL_IMPIX_G[1]);

	CAMERA_CONV     =0.5*(1+dCdI[0][0]+1+dCdI[1][1]);
	CAMERA_ROT      =0.5*(  dCdI[0][1]-  dCdI[1][0]);
	CAMERA_SHEAR[0] =0.5*(  dCdI[0][0]-  dCdI[1][1]);
	CAMERA_SHEAR[1] =0.5*(  dCdI[0][1]+  dCdI[1][0]);
	CAMERA_MAG      =CAMERA_CONV*CAMERA_CONV-(CAMERA_SHEAR[0]*CAMERA_SHEAR[0]+CAMERA_SHEAR[1]*CAMERA_SHEAR[1]);
	CAMERA_JACO     =(1+dCdI[0][0])*(1+dCdI[1][1])-dCdI[0][1]*dCdI[1][0];

//cout<< POS_CELESTIAL_IMPIX_G[0]<<"	"<<POS_CELESTIAL_IMPIX_G[1]<<"	"<<CAMERA_CONV<<"	"<<CAMERA_ROT<<"	"<<CAMERA_SHEAR[0]<<"	"<<CAMERA_SHEAR[1]<<"	"<<CAMERA_MAG<<"	"<<CAMERA_JACO<<endl;
}

} // namespace tansip
}} // namespace hsc::meas
