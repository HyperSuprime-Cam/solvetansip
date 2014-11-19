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
CL_REFs::CL_REFs(
	std::vector<ReferenceMatch> const& matchList,
	CL_APRM                          * APRM_IN,
	CL_CCDs                          * CCDs_IN
){
	APRM = APRM_IN;
	CCDs = CCDs_IN;

	REF.reserve(matchList.size());

	if(APRM->FLAG_STD >= 1)cout<<"-- SET REFs --"<<endl;

	for(std::vector<ReferenceMatch>::const_iterator match = matchList.begin();
		match != matchList.end(); ++match
	){
		REF.resize(REF.size() + 1);
		CL_REF& r = REF.back();
		r.APRM = APRM;
		r.REFs = this;
		r.CCD  = &CCDs->CCD[match->ccdId];
		r.GCD  = &CCDs->GCD;

		r.ID_CCD = match->ccdId;

		if(std::isfinite(match->x + match->y + match->ra + match->dec)){
			r.FLAG_OBJ = 1;
		}
		else{
			r.FLAG_OBJ = 0;
		}

		r.POS_DETECTED_LOCAL_L[0] = match->x  ;
		r.POS_DETECTED_LOCAL_L[1] = match->y  ;
		r.POS_CELESTIAL_RADEC [0] = match->ra ;
		r.POS_CELESTIAL_RADEC [1] = match->dec;
	}
	SET_NUM();

	SET_POS_DETECTED_LOCAL_GfromLOCAL_L();
	SET_MAXMIN_LOCAL_G();

}


void CL_REFs::SET_NUM() const
{
	CL_GCD& GCD = CCDs->GCD;

	for(std::vector<CL_CCD>::iterator ccd = CCDs->CCD.begin();
		ccd != CCDs->CCD.end(); ++ccd
	){
		ccd->NUM_REF = 0;
		ccd->NUM_FIT = 0;
		ccd->NUM_REJ = 0;
	}
	GCD.NUM_REF = 0;
	GCD.NUM_FIT = 0;
	GCD.NUM_REJ = 0;

	for(std::vector<CL_REF>::const_iterator r = REF.begin();
		r != REF.end(); ++r
	){
		CL_CCD& CCD = *(r->CCD);

		CCD.NUM_REF += 1;
		GCD.NUM_REF += 1;

		if(r->FLAG_OBJ == 1){
			CCD.NUM_FIT += 1;
			GCD.NUM_FIT += 1;
		}
		else{
			CCD.NUM_REJ += 1;
			GCD.NUM_REJ += 1;
		}
	}
}


void CL_REFs::SHOW(){
	cout << "-- SHOW REFs --" << endl;
	cout << "MODE_CR        : " << APRM->MODE_CR << endl;
	cout << "NUM_REF        : " << REF.size()    << endl;
	cout << "NUM_FIT        : " << CCDs->GCD.NUM_FIT << endl;
	cout << "AVE LOCAL_G X  : " ;cout.width(10);cout<< AVE_LOCAL_G[0] <<endl;
	cout << "AVE LOCAL_G Y  : " ;cout.width(10);cout<< AVE_LOCAL_G[1] <<endl;
	cout << "MAX LOCAL_G X  : " ;cout.width(10);cout<< MAX_LOCAL_G[0] <<endl;
	cout << "MAX LOCAL_G Y  : " ;cout.width(10);cout<< MAX_LOCAL_G[1] <<endl;
	cout << "MIN LOCAL_G X  : " ;cout.width(10);cout<< MIN_LOCAL_G[0] <<endl;
	cout << "MIN LOCAL_G Y  : " ;cout.width(10);cout<< MIN_LOCAL_G[1] <<endl;
}
//REFs::POS
void CL_REFs::SET_POS_DETECTED_LOCAL_GfromLOCAL_L(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_LOCAL_GfromLOCAL_L);
}
void CL_REFs::SET_POS_DETECTED_CRPIX_LfromLOCAL_L(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_CRPIX_LfromLOCAL_L);
}
void CL_REFs::SET_POS_DETECTED_CRPIX_GfromLOCAL_G(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_CRPIX_GfromLOCAL_G);
}
void CL_REFs::SET_POS_DETECTED_IMPIX_LfromCRPIX_L(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_IMPIX_LfromCRPIX_L);
}
void CL_REFs::SET_POS_DETECTED_IMPIX_GfromCRPIX_G(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_IMPIX_GfromCRPIX_G);
}
void CL_REFs::SET_POS_DETECTED_IMWLD_LfromIMPIX_L(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_IMWLD_LfromIMPIX_L);
}
void CL_REFs::SET_POS_DETECTED_IMWLD_GfromIMPIX_G(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_IMWLD_GfromIMPIX_G);
}
void CL_REFs::SET_POS_DETECTED_RADEC_LfromIMWLD_L(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_RADEC_LfromIMWLD_L);
}
void CL_REFs::SET_POS_DETECTED_RADEC_GfromIMWLD_G(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_RADEC_GfromIMWLD_G);
}
void CL_REFs::SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L);
}
void CL_REFs::SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G);
}
void CL_REFs::SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L);
}
void CL_REFs::SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G);
}
void CL_REFs::SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L);
}
void CL_REFs::SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G(){
	this->forAllRef(&CL_REF::SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G);
}
void CL_REFs::SET_POS_DETECTED_ALL(){
	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		r->SET_POS_DETECTED_LOCAL_GfromLOCAL_L();
		r->SET_POS_DETECTED_CRPIX_LfromLOCAL_L();
		r->SET_POS_DETECTED_CRPIX_GfromLOCAL_G();
		r->SET_POS_DETECTED_IMPIX_LfromCRPIX_L();
		r->SET_POS_DETECTED_IMPIX_GfromCRPIX_G();
		r->SET_POS_DETECTED_IMWLD_LfromIMPIX_L();
		r->SET_POS_DETECTED_IMWLD_GfromIMPIX_G();
		r->SET_POS_DETECTED_RADEC_LfromIMWLD_L();
		r->SET_POS_DETECTED_RADEC_GfromIMWLD_G();
		r->SET_POS_DETECTED_ASIP_IMPIX_LfromCRPIX_L();
		r->SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();
		r->SET_POS_DETECTED_ASIP_IMWLD_LfromASIP_IMPIX_L();
		r->SET_POS_DETECTED_ASIP_IMWLD_GfromASIP_IMPIX_G();
		r->SET_POS_DETECTED_ASIP_RADEC_LfromASIP_IMWLD_L();
		r->SET_POS_DETECTED_ASIP_RADEC_GfromASIP_IMWLD_G();
	}
}
void CL_REFs::SET_POS_CELESTIAL_IMWLDfromRADEC(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_IMWLDfromRADEC);
}
void CL_REFs::SET_POS_CELESTIAL_IMPIX_GfromIMWLD(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_IMPIX_GfromIMWLD);
}
void CL_REFs::SET_POS_CELESTIAL_IMPIX_LfromIMWLD(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_IMPIX_LfromIMWLD);
}
void CL_REFs::SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G);
}
void CL_REFs::SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L);
}
void CL_REFs::SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G);
}
void CL_REFs::SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L);
}
void CL_REFs::SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD);
}
void CL_REFs::SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G);
}
void CL_REFs::SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L);
}
void CL_REFs::SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G);
}
void CL_REFs::SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L(){
	this->forAllRef(&CL_REF::SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L);
}
void CL_REFs::SET_POS_CELESTIAL_ALL(){
	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		r->SET_POS_CELESTIAL_IMWLDfromRADEC();
		r->SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
		r->SET_POS_CELESTIAL_IMPIX_LfromIMWLD();
		r->SET_POS_CELESTIAL_CRPIX_GfromIMPIX_G();
		r->SET_POS_CELESTIAL_CRPIX_LfromIMPIX_L();
		r->SET_POS_CELESTIAL_LOCAL_GfromCRPIX_G();
		r->SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L();
		r->SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();
		r->SET_POS_CELESTIAL_PSIP_CRPIX_LfromIMPIX_L();
		r->SET_POS_CELESTIAL_PSIP_LOCAL_GfromPSIP_CRPIX_G();
		r->SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L();
	}
}
void CL_REFs::SET_DIFF(){
	this->forAllRef(&CL_REF::SET_DIFF);
}
void CL_REFs::SET_OPTICAL_DISTORTIONbyPSIP(){
	this->forAllRef(&CL_REF::SET_OPTICAL_DISTORTIONbyPSIP);
}


void CL_REFs::SET_MAXMIN_LOCAL_G(){
	AVE_LOCAL_G[0] = 0;
	AVE_LOCAL_G[1] = 0;
	int nRef = 0;

	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		AVE_LOCAL_G[0] += r->POS_DETECTED_LOCAL_G[0];
		AVE_LOCAL_G[1] += r->POS_DETECTED_LOCAL_G[1];
		nRef += 1;
	}

	AVE_LOCAL_G[0]/=nRef;
	AVE_LOCAL_G[1]/=nRef;

	MAX_LOCAL_G[0]=MIN_LOCAL_G[0]=AVE_LOCAL_G[0];
	MAX_LOCAL_G[1]=MIN_LOCAL_G[1]=AVE_LOCAL_G[1];

	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		if(r->POS_DETECTED_LOCAL_G[0] > MAX_LOCAL_G[0]){
			MAX_LOCAL_G[0] = r->POS_DETECTED_LOCAL_G[0];
		}
		else if(r->POS_DETECTED_LOCAL_G[0] < MIN_LOCAL_G[0]){
			MIN_LOCAL_G[0] = r->POS_DETECTED_LOCAL_G[0];
		}

		if(r->POS_DETECTED_LOCAL_G[1] > MAX_LOCAL_G[1]){
			MAX_LOCAL_G[1] = r->POS_DETECTED_LOCAL_G[1];
		}
		else if(r->POS_DETECTED_LOCAL_G[1] < MIN_LOCAL_G[1]){
			MIN_LOCAL_G[1] = r->POS_DETECTED_LOCAL_G[1];
		}
	}
}


void CL_REFs::SET_MAXMIN_CRPIX_G(){
	double (&MAX_CRPIX_G)[2] = CCDs->MAX_CRPIX_G;
	double (&MIN_CRPIX_G)[2] = CCDs->MIN_CRPIX_G;
	double (&AVE_CRPIX_G)[2] = CCDs->AVE_CRPIX_G;

	AVE_CRPIX_G[0]=AVE_CRPIX_G[1]=0;
	int nRef = 0;
	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		AVE_CRPIX_G[0] += r->POS_DETECTED_CRPIX_G[0];
		AVE_CRPIX_G[1] += r->POS_DETECTED_CRPIX_G[1];
		nRef += 1;
	}
	AVE_CRPIX_G[0]/=nRef;
	AVE_CRPIX_G[1]/=nRef;

	MAX_CRPIX_G[0]=MIN_CRPIX_G[0]=AVE_CRPIX_G[0];
	MAX_CRPIX_G[1]=MIN_CRPIX_G[1]=AVE_CRPIX_G[1];

	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		if(r->POS_DETECTED_CRPIX_G[0] > MAX_CRPIX_G[0]){
			MAX_CRPIX_G[0] = r->POS_DETECTED_CRPIX_G[0];
		}
		else if(r->POS_DETECTED_CRPIX_G[0] < MIN_CRPIX_G[0]){
			MIN_CRPIX_G[0] = r->POS_DETECTED_CRPIX_G[0];
		}

		if(r->POS_DETECTED_CRPIX_G[1] > MAX_CRPIX_G[1]){
			MAX_CRPIX_G[1] = r->POS_DETECTED_CRPIX_G[1];
		}
		else if(r->POS_DETECTED_CRPIX_G[1] < MIN_CRPIX_G[1]){
			MIN_CRPIX_G[1] = r->POS_DETECTED_CRPIX_G[1];
		}
	}
}


int  CL_REFs::GET_ID_NEAR_CRVAL()
{
	double (&CRVAL)[2] = CCDs->GCD.CRVAL;

	std::vector<CL_REF>::iterator pMin = REF.end();
	double MIN_CRVAL = INFINITY;

	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		double R_CRVAL=hypot(r->POS_CELESTIAL_RADEC[0]-CRVAL[0],r->POS_CELESTIAL_RADEC[1]-CRVAL[1]);
		if(R_CRVAL < MIN_CRVAL){
			MIN_CRVAL = R_CRVAL;
			pMin = r;
		}
	}

	return pMin - REF.begin();
}


int  CL_REFs::GET_ID_NEAR_CRPIX()
{
	const double (&CRPIX)[2] = CCDs->GCD.CRPIX;

	std::vector<CL_REF>::iterator pMin = REF.end();
	double MIN_CRPIX = INFINITY;

	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		double R_CRPIX=hypot(r->POS_DETECTED_LOCAL_G[0]-CRPIX[0],r->POS_DETECTED_LOCAL_G[1]-CRPIX[1]);
		if(R_CRPIX < MIN_CRPIX){
			MIN_CRPIX = R_CRPIX;
			pMin = r;
		}
	}

	return pMin - REF.begin();
}

//REFS::FIT
void CL_REFs::FIT_CbyD(EPosCelestial ID_C, EPosDetected ID_D){
	ndarray::Array<double, 2, 2> dx = ndarray::allocate(REF.size(),3);
	ndarray::Array<double, 2, 2> dy = ndarray::allocate(REF.size(),3);

	int nRef = 0;
	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		double (&D)[2] = r->POS(ID_D);
		double (&C)[2] = r->POS(ID_C);

		if(isfinite(D[0]) && isfinite(D[1])
		&& isfinite(C[0]) && isfinite(C[1])
		){
			dx[nRef][0]=dy[nRef][0]=D[0];
			dx[nRef][1]=dy[nRef][1]=D[1];
			dx[nRef][2]=C[0];
			dy[nRef][2]=C[1];
			nRef+=1;
		}
	}

	Polynomial2D (&ASIP)[2] = CCDs->GCD.ASIP;
	ASIP[0] = CALC_FIT_LS2(nRef,APRM->ORDER_ASIP,dx);
	ASIP[1] = CALC_FIT_LS2(nRef,APRM->ORDER_ASIP,dy);
}


void CL_REFs::FIT_DbyC(EPosDetected ID_D, EPosCelestial ID_C)
{
	ndarray::Array<double, 2, 2> dx = ndarray::allocate(REF.size(), 3);
	ndarray::Array<double, 2, 2> dy = ndarray::allocate(REF.size(), 3);

	int nRef = 0;
	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		double (&D)[2] = r->POS(ID_D);
		double (&C)[2] = r->POS(ID_C);

		if(isfinite(D[0]) && isfinite(D[1])
		&& isfinite(C[0]) && isfinite(C[1])
		){
			dx[nRef][0]=dy[nRef][0]=C[0];
			dx[nRef][1]=dy[nRef][1]=C[1];
			dx[nRef][2]=D[0];
			dy[nRef][2]=D[1];
			nRef+=1;
		}
	}

	Polynomial2D (&PSIP)[2] = CCDs->GCD.PSIP;
	PSIP[0] = CALC_FIT_LS2(nRef,APRM->ORDER_PSIP,dx);
	PSIP[1] = CALC_FIT_LS2(nRef,APRM->ORDER_PSIP,dy);
}


void CL_REFs::CALC_STAT_ASIP()
{
	ndarray::Array<double, 1, 1> DIFF[2];
	DIFF[0] = ndarray::allocate(REF.size());
	DIFF[1] = ndarray::allocate(REF.size());

	int nRef = 0;
	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		DIFF[0][nRef] = r->POS_DETECTED_ASIP_IMPIX_G[0] - r->POS_CELESTIAL_IMPIX_G[0];
		DIFF[1][nRef] = r->POS_DETECTED_ASIP_IMPIX_G[1] - r->POS_CELESTIAL_IMPIX_G[1];
		nRef += 1;
	}

	double STAT[2][4];
	CALC_STAT_RMSMAX(nRef,DIFF[0].getData(), STAT[0]);
	CALC_STAT_RMSMAX(nRef,DIFF[1].getData(), STAT[1]);

	double (&DIF_AVE_ASIP)[2] = CCDs->GCD.DIF_AVE_ASIP;
	double (&DIF_RMS_ASIP)[2] = CCDs->GCD.DIF_RMS_ASIP;
	double (&DIF_MAX_ASIP)[2] = CCDs->GCD.DIF_MAX_ASIP;

	DIF_AVE_ASIP[0] = STAT[0][1];
	DIF_AVE_ASIP[1] = STAT[1][1];
	DIF_RMS_ASIP[0] = STAT[0][2];
	DIF_RMS_ASIP[1] = STAT[1][2];
	DIF_MAX_ASIP[0] = STAT[0][3];
	DIF_MAX_ASIP[1] = STAT[1][3];

	if(APRM->FLAG_STD >= 2){
		cout<<"-- STAT ASIP DIFF --"<<endl;
		cout<<"NUM    : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<nRef<<endl;
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
	ndarray::Array<double, 1, 1> DIFF[2];
	DIFF[0] = ndarray::allocate(REF.size());
	DIFF[1] = ndarray::allocate(REF.size());

	int nRef = 0;
	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		DIFF[0][nRef] = r->POS_CELESTIAL_PSIP_CRPIX_G[0] - r->POS_DETECTED_CRPIX_G[0];
		DIFF[1][nRef] = r->POS_CELESTIAL_PSIP_CRPIX_G[1] - r->POS_DETECTED_CRPIX_G[1];
		nRef+=1;
	}

	double STAT[2][4];
	CALC_STAT_RMSMAX(nRef,DIFF[0].getData(),STAT[0]);
	CALC_STAT_RMSMAX(nRef,DIFF[1].getData(),STAT[1]);

	double (&DIF_AVE_PSIP)[2] = CCDs->GCD.DIF_AVE_PSIP;
	double (&DIF_RMS_PSIP)[2] = CCDs->GCD.DIF_RMS_PSIP;
	double (&DIF_MAX_PSIP)[2] = CCDs->GCD.DIF_MAX_PSIP;

	DIF_AVE_PSIP[0] = STAT[0][1];
	DIF_AVE_PSIP[1] = STAT[1][1];
	DIF_RMS_PSIP[0] = STAT[0][2];
	DIF_RMS_PSIP[1] = STAT[1][2];
	DIF_MAX_PSIP[0] = STAT[0][3];
	DIF_MAX_PSIP[1] = STAT[1][3];

	if(APRM->FLAG_STD >= 2){
		cout<<"-- STAT PSIP DIFF --"<<endl;
		cout<<"NUM    : ";
		cout.width(10);
		cout<<scientific<<setprecision(3)<<nRef<<endl;
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


void CL_REFs::CALC_STAT_SIP_LOCAL()
{
	int const NUM_CCD = CCDs->CCD.size();

	ndarray::Array<int   , 1, 1> NUM = ndarray::allocate(NUM_CCD);
	ndarray::Array<double, 3, 3> DIFF= ndarray::allocate(NUM_CCD, 4, REF.size());

	NUM.deep() = 0;

	int nRef = 0;
	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		DIFF[r->ID_CCD][0][NUM[r->ID_CCD]] = r->POS_DETECTED_ASIP_IMPIX_L [0] - r->POS_CELESTIAL_IMPIX_L[0];
		DIFF[r->ID_CCD][1][NUM[r->ID_CCD]] = r->POS_DETECTED_ASIP_IMPIX_L [1] - r->POS_CELESTIAL_IMPIX_L[1];
		DIFF[r->ID_CCD][2][NUM[r->ID_CCD]] = r->POS_CELESTIAL_PSIP_CRPIX_L[0] - r->POS_DETECTED_CRPIX_L [0];
		DIFF[r->ID_CCD][3][NUM[r->ID_CCD]] = r->POS_CELESTIAL_PSIP_CRPIX_L[1] - r->POS_DETECTED_CRPIX_L [1];
		NUM [r->ID_CCD] += 1;
		nRef+=1;
	}

	for(int i = 0; i < NUM_CCD; ++i){
		double STAT[4][4];

		CALC_STAT_RMSMAX(NUM[i],DIFF[i][0].getData(),STAT[0]);
		CALC_STAT_RMSMAX(NUM[i],DIFF[i][1].getData(),STAT[1]);
		CALC_STAT_RMSMAX(NUM[i],DIFF[i][2].getData(),STAT[2]);
		CALC_STAT_RMSMAX(NUM[i],DIFF[i][3].getData(),STAT[3]);
		CCDs->CCD[i].DIF_AVE_ASIP[0] = STAT[0][1];
		CCDs->CCD[i].DIF_AVE_ASIP[1] = STAT[1][1];
		CCDs->CCD[i].DIF_AVE_PSIP[0] = STAT[2][1];
		CCDs->CCD[i].DIF_AVE_PSIP[1] = STAT[3][1];
		CCDs->CCD[i].DIF_RMS_ASIP[0] = STAT[0][2];
		CCDs->CCD[i].DIF_RMS_ASIP[1] = STAT[1][2];
		CCDs->CCD[i].DIF_RMS_PSIP[0] = STAT[2][2];
		CCDs->CCD[i].DIF_RMS_PSIP[1] = STAT[3][2];
		CCDs->CCD[i].DIF_MAX_ASIP[0] = STAT[0][3];
		CCDs->CCD[i].DIF_MAX_ASIP[1] = STAT[1][3];
		CCDs->CCD[i].DIF_MAX_PSIP[0] = STAT[2][3];
		CCDs->CCD[i].DIF_MAX_PSIP[1] = STAT[3][3];
	}
}


void CL_REFs::CALC_CRPIXatCRVAL()
{
	Polynomial2D (&PSIP)[2] = CCDs->GCD.PSIP;

	SET_POS_CELESTIAL_IMWLDfromRADEC();
	FIT_DbyC(DETECTED_LOCAL_G, CELESTIAL_IMWLD);
	CCDs->GCD.CRPIX[0]=PSIP[0].coeff(0,0);
	CCDs->GCD.CRPIX[1]=PSIP[1].coeff(0,0);
	SET_POS_DETECTED_CRPIX_GfromLOCAL_G();
	FIT_CbyD(CELESTIAL_IMWLD, DETECTED_CRPIX_G);
	CCDs->GCD.SET_CDASIP();
	SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
	FIT_DbyC(DETECTED_CRPIX_G, CELESTIAL_IMPIX_G);
	CCDs->GCD.SET_CDPSIP();
	if(APRM->FLAG_STD >= 2){
		double (&CD)[2][2] = CCDs->GCD.CD;
		cout<<"-- CRPIX at CRVAL --"<<endl;
		cout<<"CRVAL1 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<CCDs->GCD.CRVAL[0]<<endl;
		cout<<"CRVAL2 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<CCDs->GCD.CRVAL[1]<<endl;
		cout<<"CRPIX1 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<CCDs->GCD.CRPIX[0]<<endl;
		cout<<"CRPIX2 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<CCDs->GCD.CRPIX[1]<<endl;
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
	Polynomial2D (&ASIP)[2] = CCDs->GCD.ASIP;

	SET_POS_DETECTED_CRPIX_GfromLOCAL_G();
	int ID = GET_ID_NEAR_CRPIX();

	double (&CRVAL)[2] = CCDs->GCD.CRVAL;

	CRVAL[0]=REF[ID].POS_CELESTIAL_RADEC[0];
	CRVAL[1]=REF[ID].POS_CELESTIAL_RADEC[1];

	for(int LOOP = 0; LOOP < 10; ++LOOP){
		SET_POS_CELESTIAL_IMWLDfromRADEC();
		FIT_CbyD(CELESTIAL_IMWLD, DETECTED_CRPIX_G);
		double SCALE=sqrt(-ASIP[0].coeff(1,0)*ASIP[1].coeff(0,1)+ASIP[0].coeff(0,1)*ASIP[1].coeff(1,0));
		if(hypot(ASIP[0].coeff(0,0),ASIP[1].coeff(0,0))/SCALE<0.001){
			break;
		}else{
			CRVAL[0]+=ASIP[0].coeff(0,0)/cos(CRVAL[1]*(M_PI/180));
			CRVAL[1]+=ASIP[1].coeff(0,0);
		}
	}
	CCDs->GCD.SET_CDASIP();
	if(APRM->FLAG_STD >= 2){
		double (&CD)[2][2] = CCDs->GCD.CD;
		cout<<"-- CRVAL at CRPIX --"<<endl;
		cout<<"CRPIX1 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<CCDs->GCD.CRPIX[0]<<endl;
		cout<<"CRPIX2 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<CCDs->GCD.CRPIX[1]<<endl;
		cout<<"CRVAL1 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<CCDs->GCD.CRVAL[0]<<endl;
		cout<<"CRVAL2 : ";
		cout.width(10);
		cout<<fixed<<setprecision(6)<<CCDs->GCD.CRVAL[1]<<endl;
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
	CCDs->GCD.CRPIX[0]=AVE_LOCAL_G[0];
	CCDs->GCD.CRPIX[1]=AVE_LOCAL_G[1];
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
	double const SIGMA_CLIP = APRM->SIGMA_CLIP;
	double (&DIF_RMS_ASIP)[2] = CCDs->GCD.DIF_RMS_ASIP;

	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		double DIFF[2];
		DIFF[0] = r->POS_DETECTED_ASIP_IMPIX_G[0] - r->POS_CELESTIAL_IMPIX_G[0];
		DIFF[1] = r->POS_DETECTED_ASIP_IMPIX_G[1] - r->POS_CELESTIAL_IMPIX_G[1];

		if(fabs(DIFF[0]) > SIGMA_CLIP*DIF_RMS_ASIP[0]
		|| fabs(DIFF[1]) > SIGMA_CLIP*DIF_RMS_ASIP[1]
		){
			r->FLAG_OBJ = 0;
		}
		else{
			r->FLAG_OBJ = 1;
		}
	}

}


void CL_REFs::REJECT_BADREF_PSIP(){
	double const SIGMA_CLIP = APRM->SIGMA_CLIP;
	double (&DIF_RMS_PSIP)[2] = CCDs->GCD.DIF_RMS_PSIP;

	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		double DIFF[2];
		DIFF[0] = r->POS_CELESTIAL_PSIP_CRPIX_G[0] - r->POS_DETECTED_CRPIX_G[0];
		DIFF[1] = r->POS_CELESTIAL_PSIP_CRPIX_G[1] - r->POS_DETECTED_CRPIX_G[1];
		if(fabs(DIFF[0]) > SIGMA_CLIP*DIF_RMS_PSIP[0]
		|| fabs(DIFF[1]) > SIGMA_CLIP*DIF_RMS_PSIP[1]
		){
			r->FLAG_OBJ = 0;
		}
		else{
			r->FLAG_OBJ = 1;
		}
	}
}


//CCD POSITION
void CL_REFs::DETERMINE_CCDPOSITION(){
	if(APRM->FLAG_STD >= 1)cout<<"-- DETERMINE CCD POSITIONS --"<<endl;

	// See doc/determine_ccdposition.tex for a mathematical description
	// of this function

	int const NUM_CCD    = CCDs->CCD.size();
	int const ORDER_PSIP = APRM->ORDER_PSIP;

	// Find CCDs that have sufficient references on them
	std::vector<CL_CCD*> validCcd;
	validCcd.reserve(NUM_CCD);

	std::vector<int> ccdIdToValidId(NUM_CCD, -1);

	for(int i = 0; i < NUM_CCD; ++i){
		if(CCDs->CCD[i].areReferencesSufficient()){
			ccdIdToValidId[i] = validCcd.size();
			validCcd.push_back(&CCDs->CCD[i]);
		}
	}

	int const nValidCcd = validCcd.size();
	if(nValidCcd <= 0){
		cout << "Warning: No ccd has sufficient number of references on it." << endl;
		cout << "    DETERMINE_CCDPOSITION() did nothing." << endl;
		return;
	}

	int const                    NUM_COEF = (ORDER_PSIP+1)*(ORDER_PSIP+2)/2;
	ndarray::Array<double, 2, 2> COEF     = ndarray::allocate(2, NUM_COEF);
	ndarray::Array<double, 1, 1> MAXYT    = ndarray::allocate(3*nValidCcd+2*(NUM_COEF-1)+1);
	ndarray::Array<double, 2, 2> MBXYT    = ndarray::allocate(3*nValidCcd+2*(NUM_COEF-1)+1, 3*nValidCcd+2*(NUM_COEF-1)+1);
	ndarray::Array<double, 3, 3> XY       = ndarray::allocate(REF.size(), 2*ORDER_PSIP+1, 2*ORDER_PSIP+1);
	ndarray::Array<double, 1, 1> XLsYLc   = ndarray::allocate(REF.size());
	ndarray::Array<double, 1, 1> YLsXLc   = ndarray::allocate(REF.size());
	ndarray::Array<double, 2, 2> XYINIT   = ndarray::allocate(nValidCcd, 3);
	ndarray::Array<double, 1, 1> XN       = ndarray::allocate(2*ORDER_PSIP+1);
	ndarray::Array<double, 1, 1> YN       = ndarray::allocate(2*ORDER_PSIP+1);

	for(int i = 0; i < nValidCcd; ++i){
		XYINIT[i][0] = validCcd[i]->GPOS_L[0];
		XYINIT[i][1] = validCcd[i]->GPOS_L[1];
		XYINIT[i][2] = validCcd[i]->GPOS_L[2];
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
		FIT_DbyC(DETECTED_LOCAL_G, CELESTIAL_IMWLD);
		SET_POS_CELESTIAL_PSIP_LOCAL_GfromIMWLD();
//--------------------------------------------------
//XY
		for(std::size_t NUM = 0; NUM < REF.size(); ++NUM){
			if(REF[NUM].FLAG_OBJ != 1) continue;

			XN[0]=1;
			YN[0]=1;
			for(int i = 1; i <= 2*ORDER_PSIP; ++i){
				XN[i] = XN[i-1]*REF[NUM].POS_CELESTIAL_IMWLD[0];
				YN[i] = YN[i-1]*REF[NUM].POS_CELESTIAL_IMWLD[1];
			}
			for(int i = 0; i <= 2*ORDER_PSIP; ++i)
			for(int j = 0; j <= 2*ORDER_PSIP; ++j)
				XY[NUM][i][j] = XN[i]*YN[j];
		}
		for(std::size_t NUM = 0; NUM < REF.size(); ++NUM){
			if(REF[NUM].FLAG_OBJ != 1) continue;

			int ID_CCD = REF[NUM].ID_CCD;
			if(ccdIdToValidId[ID_CCD] < 0) continue;

			XLsYLc[NUM]=REF[NUM].POS_DETECTED_LOCAL_L[0]*sin(REF[NUM].CCD->GPOS_L[2])+
				    REF[NUM].POS_DETECTED_LOCAL_L[1]*cos(REF[NUM].CCD->GPOS_L[2]);
			YLsXLc[NUM]=REF[NUM].POS_DETECTED_LOCAL_L[1]*sin(REF[NUM].CCD->GPOS_L[2])-
				    REF[NUM].POS_DETECTED_LOCAL_L[0]*cos(REF[NUM].CCD->GPOS_L[2]);
		}

//--------------------------------------------------
//INIT a & B: we are solving B*c = a
		MAXYT.deep() = 0;
		MBXYT.deep() = 0;

//--------------------------------------------------
// CCD positions (\delta X, \delta Y, \delta \Theta)
		for(std::size_t NUM = 0; NUM < REF.size(); ++NUM){
			if(REF[NUM].FLAG_OBJ != 1) continue;

			int validCcdId = ccdIdToValidId[REF[NUM].ID_CCD];
			if(validCcdId < 0) continue;

			MAXYT[0*nValidCcd+validCcdId]-=(REF[NUM].POS_DETECTED_LOCAL_G[0]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[0]);
			MAXYT[1*nValidCcd+validCcdId]-=(REF[NUM].POS_DETECTED_LOCAL_G[1]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[1]);
			MAXYT[2*nValidCcd+validCcdId]-=-XLsYLc[NUM]*(REF[NUM].POS_DETECTED_LOCAL_G[0]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[0])
							     -YLsXLc[NUM]*(REF[NUM].POS_DETECTED_LOCAL_G[1]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[1]);
		}
// Polynomial coefficients (\delta a_{mn}, \delta b_{mn})
		int ij=0;
		for(int i=0;i<ORDER_PSIP+1  ;i++)
		for(int j=0;j<ORDER_PSIP+1-i;j++)
		if(i+j!=0){
			for(std::size_t NUM = 0; NUM < REF.size(); ++NUM){
				if(REF[NUM].FLAG_OBJ != 1) continue;
				MAXYT[3*nValidCcd+0*(NUM_COEF-1)+ij]-=-(REF[NUM].POS_DETECTED_LOCAL_G[0]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[0])*XY[NUM][i][j];
				MAXYT[3*nValidCcd+1*(NUM_COEF-1)+ij]-=-(REF[NUM].POS_DETECTED_LOCAL_G[1]-REF[NUM].POS_CELESTIAL_PSIP_LOCAL_G[1])*XY[NUM][i][j];
			}
			ij++;
		}
//--------------------------------------------------
// CCD positions \times CCD positions
		for(std::size_t NUM = 0; NUM < REF.size(); ++NUM){
			if(REF[NUM].FLAG_OBJ != 1) continue;

			int validCcdId = ccdIdToValidId[REF[NUM].ID_CCD];
			if(validCcdId < 0) continue;

			MBXYT[0*nValidCcd+validCcdId][0*nValidCcd+validCcdId]+=1;
//			MBXYT[0*nValidCcd+validCcdId][1*nValidCcd+validCcdId]+=0;
			MBXYT[0*nValidCcd+validCcdId][2*nValidCcd+validCcdId]+=-XLsYLc[NUM];
//			MBXYT[1*nValidCcd+validCcdId][0*nValidCcd+validCcdId]+=0;
			MBXYT[1*nValidCcd+validCcdId][1*nValidCcd+validCcdId]+=1;
			MBXYT[1*nValidCcd+validCcdId][2*nValidCcd+validCcdId]+=-YLsXLc[NUM];
			MBXYT[2*nValidCcd+validCcdId][0*nValidCcd+validCcdId]+=-XLsYLc[NUM];
			MBXYT[2*nValidCcd+validCcdId][1*nValidCcd+validCcdId]+=-YLsXLc[NUM];
			MBXYT[2*nValidCcd+validCcdId][2*nValidCcd+validCcdId]+= XLsYLc[NUM]*XLsYLc[NUM]+YLsXLc[NUM]*YLsXLc[NUM];
		}

// CCD positions \times Polynomial coefficients
		ij=0;
		for(int i=0;i<ORDER_PSIP+1  ;i++)
		for(int j=0;j<ORDER_PSIP+1-i;j++)
		if(i+j!=0){
			for(std::size_t NUM = 0; NUM < REF.size(); ++NUM){
				if(REF[NUM].FLAG_OBJ != 1) continue;

				int validCcdId = ccdIdToValidId[REF[NUM].ID_CCD];
				if(validCcdId < 0) continue;

				MBXYT[0*nValidCcd+validCcdId][3*nValidCcd+0*(NUM_COEF-1)+ij]+=-XY[NUM][i][j];
				MBXYT[1*nValidCcd+validCcdId][3*nValidCcd+1*(NUM_COEF-1)+ij]+=-XY[NUM][i][j];
				MBXYT[2*nValidCcd+validCcdId][3*nValidCcd+0*(NUM_COEF-1)+ij]+=-XY[NUM][i][j]*(-XLsYLc[NUM]);
				MBXYT[2*nValidCcd+validCcdId][3*nValidCcd+1*(NUM_COEF-1)+ij]+=-XY[NUM][i][j]*(-YLsXLc[NUM]);
			}
			ij++;
		}

// Polynomial coefficients \times CCD positions
		ij=0;
		for(int i=0;i<ORDER_PSIP+1  ;i++)
		for(int j=0;j<ORDER_PSIP+1-i;j++)
		if(i+j!=0){
			for(std::size_t NUM = 0; NUM < REF.size(); ++NUM){
				if(REF[NUM].FLAG_OBJ != 1) continue;

				int validCcdId = ccdIdToValidId[REF[NUM].ID_CCD];
				if(validCcdId < 0) continue;

				MBXYT[3*nValidCcd+0*(NUM_COEF-1)+ij][0*nValidCcd+validCcdId]+=-XY[NUM][i][j];
				MBXYT[3*nValidCcd+1*(NUM_COEF-1)+ij][1*nValidCcd+validCcdId]+=-XY[NUM][i][j];
				MBXYT[3*nValidCcd+0*(NUM_COEF-1)+ij][2*nValidCcd+validCcdId]+=-XY[NUM][i][j]*(-XLsYLc[NUM]);
				MBXYT[3*nValidCcd+1*(NUM_COEF-1)+ij][2*nValidCcd+validCcdId]+=-XY[NUM][i][j]*(-YLsXLc[NUM]);
			}
			ij++;
		}

// Polynomial coefficients \times Polynomial coefficients
		ij=0;
		for(int i=0;i<ORDER_PSIP+1  ;i++)
		for(int j=0;j<ORDER_PSIP+1-i;j++)
		if(i+j!=0){
			int kl=0;
			for(int k=0;k<ORDER_PSIP+1  ;k++)
			for(int l=0;l<ORDER_PSIP+1-k;l++)
			if(k+l!=0){
				for(std::size_t NUM = 0; NUM < REF.size(); ++NUM){
					if(REF[NUM].FLAG_OBJ != 1) continue;
					MBXYT[3*nValidCcd+0*(NUM_COEF-1)+ij][3*nValidCcd+0*(NUM_COEF-1)+kl]+=XY[NUM][i+k][j+l];

//					MBXYT[3*nValidCcd+0*(NUM_COEF-1)+ij][3*nValidCcd+1*(NUM_COEF-1)+kl]+=0;
//					MBXYT[3*nValidCcd+1*(NUM_COEF-1)+ij][3*nValidCcd+0*(NUM_COEF-1)+kl]+=0;
					MBXYT[3*nValidCcd+1*(NUM_COEF-1)+ij][3*nValidCcd+1*(NUM_COEF-1)+kl]+=XY[NUM][i+k][j+l];
				}
				kl++;
			}
			ij++;
		}

// restraint conditions: \sum_c \delta \Theta_c = 0
		for(int validCcdId = 0; validCcdId < nValidCcd; ++validCcdId){
			MBXYT[2*nValidCcd+validCcdId][3*nValidCcd+2*(NUM_COEF-1) + 0] = 1;
			MBXYT[3*nValidCcd+2*(NUM_COEF-1) + 0][2*nValidCcd+validCcdId] = 1;
		}
//--------------------------------------------------
		// C = B^{-1} A
		ndarray::Array<double, 1, 1> MCXYT = SOLVE_LINEAR_EQUATION(MBXYT, MAXYT);

		for(int CID = 0; CID < nValidCcd; ++CID){
			validCcd[CID]->GPOS_L[0] += MCXYT[0*nValidCcd+CID];
			validCcd[CID]->GPOS_L[1] += MCXYT[1*nValidCcd+CID];
			validCcd[CID]->GPOS_L[2] += MCXYT[2*nValidCcd+CID];
			validCcd[CID]->GPOS_L[3] = validCcd[CID]->GPOS_L[2]*(180/M_PI);
		}
		SET_CCDAVE();

//--------------------------------------------------

		double const PRECISION_CCD = APRM->PRECISION_CCD;
		int ENDFLAG=1;
		for(int CID = 0; CID < nValidCcd; ++CID)
		if(hypot(XYINIT[CID][0] - validCcd[CID]->GPOS_L[0],
			 XYINIT[CID][1] - validCcd[CID]->GPOS_L[1]) > PRECISION_CCD ||
		    fabs(XYINIT[CID][2] - validCcd[CID]->GPOS_L[2]) > PRECISION_CCD/5000)
		ENDFLAG=0;

		if(ENDFLAG==1){
			break;
		}else{
			if(APRM->FLAG_STD >= 2)cout << "CCD GPOS LOOP : " << XYLOOP+1 << endl;
			for(int CID = 0; CID < nValidCcd; ++CID){
				XYINIT[CID][0] = validCcd[CID]->GPOS_L[0];
				XYINIT[CID][1] = validCcd[CID]->GPOS_L[1];
				XYINIT[CID][2] = validCcd[CID]->GPOS_L[2];
			}
		}

	}

	if(APRM->FLAG_STD >= 2)CCDs->SHOW();
}
void CL_REFs::SET_CCDAVE(){
	int const NUM_CCD    = CCDs->CCD.size();

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

	if(APRM->FLAG_STD >= 2)CCDs->GCD.SHOW();
//	if(APRM->FLAG_STD >= 2)CCDs->CCD[0].SHOW();
	if(CCDs->CCD.size() >= 49) { // assumes HSC, and show DET-ID=50
	  if(APRM->FLAG_STD >= 2)CCDs->CCD[49].SHOW();
	}
	else { // assumes SC, and show DET-ID=5
	  if(APRM->FLAG_STD >= 2)CCDs->CCD[4].SHOW();
	}
//	if(APRM->NUM_CCD>103)
//	if(APRM->FLAG_STD >= 2)CCDs->CCD[100].SHOW();

}
void CL_REFs::CALC_TANSIP(){
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
	FIT_CbyD(CELESTIAL_IMWLD, DETECTED_CRPIX_G);
	CCDs->GCD.SET_CDASIP();
	SET_POS_DETECTED_ASIP_IMPIX_GfromCRPIX_G();
	SET_POS_CELESTIAL_IMPIX_GfromIMWLD();
	CALC_STAT_ASIP();

	FIT_DbyC(DETECTED_CRPIX_G, CELESTIAL_IMPIX_G);
	CCDs->GCD.SET_CDPSIP();
	SET_POS_CELESTIAL_PSIP_CRPIX_GfromIMPIX_G();
	CALC_STAT_PSIP();

	SET_DIFF();
	SET_MAXMIN_CRPIX_G();
}
//DISTORTION
void CL_REFs::CALC_OPTICAL_DISTORTION(){
	Polynomial2D (&PSIP)[2] = CCDs->GCD.PSIP;
	PSIP_DX[0] = PSIP[0].dx();
	PSIP_DY[0] = PSIP[0].dy();
	PSIP_DX[1] = PSIP[1].dx();
	PSIP_DY[1] = PSIP[1].dy();

	SET_OPTICAL_DISTORTIONbyPSIP();
	CALC_OPTICAL_AXIS();
}
Polynomial2D CL_REFs::FIT_PSIP_JACO(){
	int const ORDER_PSIP = APRM->ORDER_PSIP;

	ndarray::Array<double, 2, 2> dJ = ndarray::allocate(REF.size(),3);

	int nRef = 0;
	for(std::vector<CL_REF>::iterator r = REF.begin();
		r != REF.end(); ++r
	){
		if(r->FLAG_OBJ != 1) continue;
		dJ[nRef][0] = r->POS_CELESTIAL_IMPIX_G[0];
		dJ[nRef][1] = r->POS_CELESTIAL_IMPIX_G[1];
		dJ[nRef][2] = r->CAMERA_JACO;
		nRef += 1;
	}

	return CALC_FIT_LS2(nRef,ORDER_PSIP-1,dJ );
}
void CL_REFs::CALC_OPTICAL_AXIS(){
	Polynomial2D PSIP_JACO = FIT_PSIP_JACO();

	Polynomial2D JDX = PSIP_JACO.dx();
	Polynomial2D JDY = PSIP_JACO.dy();

	Polynomial2D JDXDX = JDX.dx();
	Polynomial2D JDXDY = JDX.dy();
	Polynomial2D JDYDX = JDY.dx();
	Polynomial2D JDYDY = JDY.dy();

	double PX=CCDs->GCD.CRPIX[0];
	double PY=CCDs->GCD.CRPIX[1];

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
	CCDs->GCD.OAPIX[0]=PX;
	CCDs->GCD.OAPIX[1]=PY;
}

//REF::POS
void CL_REF::SET_POS_DETECTED_LOCAL_GfromLOCAL_L(){
	POS_DETECTED_LOCAL_G[0]=POS_DETECTED_LOCAL_L[0]*cos(CCD->GPOS_L[2])-POS_DETECTED_LOCAL_L[1]*sin(CCD->GPOS_L[2])+CCD->GPOS_L[0];
	POS_DETECTED_LOCAL_G[1]=POS_DETECTED_LOCAL_L[1]*cos(CCD->GPOS_L[2])+POS_DETECTED_LOCAL_L[0]*sin(CCD->GPOS_L[2])+CCD->GPOS_L[1];
}
void CL_REF::SET_POS_DETECTED_CRPIX_GfromLOCAL_G(){
	POS_DETECTED_CRPIX_G[0]=POS_DETECTED_LOCAL_G[0]-GCD->CRPIX[0];
	POS_DETECTED_CRPIX_G[1]=POS_DETECTED_LOCAL_G[1]-GCD->CRPIX[1];
}
void CL_REF::SET_POS_DETECTED_CRPIX_LfromLOCAL_L(){
	POS_DETECTED_CRPIX_L[0]=POS_DETECTED_LOCAL_L[0]-CCD->CRPIX[0];
	POS_DETECTED_CRPIX_L[1]=POS_DETECTED_LOCAL_L[1]-CCD->CRPIX[1];
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
	CRVALrad[0]=GCD->CRVAL[0]*(M_PI/180);
	CRVALrad[1]=GCD->CRVAL[1]*(M_PI/180);
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
	CRVALrad[0]=GCD->CRVAL[0]*(M_PI/180);
	CRVALrad[1]=GCD->CRVAL[1]*(M_PI/180);
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
	CRVALrad[0]=GCD->CRVAL[0]*(M_PI/180);
	CRVALrad[1]=GCD->CRVAL[1]*(M_PI/180);
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
	CRVALrad[0]=GCD->CRVAL[0]*(M_PI/180);
	CRVALrad[1]=GCD->CRVAL[1]*(M_PI/180);
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
	CRVALrad[0]=GCD->CRVAL[0]*(M_PI/180);
	CRVALrad[1]=GCD->CRVAL[1]*(M_PI/180);

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
	POS_CELESTIAL_LOCAL_G[0]=POS_CELESTIAL_CRPIX_G[0]+GCD->CRPIX[0];
	POS_CELESTIAL_LOCAL_G[1]=POS_CELESTIAL_CRPIX_G[1]+GCD->CRPIX[1];
}
void CL_REF::SET_POS_CELESTIAL_LOCAL_LfromCRPIX_L(){
	POS_CELESTIAL_LOCAL_L[0]=POS_CELESTIAL_CRPIX_L[0]+CCD->CRPIX[0];
	POS_CELESTIAL_LOCAL_L[1]=POS_CELESTIAL_CRPIX_L[1]+CCD->CRPIX[1];
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
	POS_CELESTIAL_PSIP_LOCAL_G[0]=POS_CELESTIAL_PSIP_CRPIX_G[0]+GCD->CRPIX[0];
	POS_CELESTIAL_PSIP_LOCAL_G[1]=POS_CELESTIAL_PSIP_CRPIX_G[1]+GCD->CRPIX[1];
}
void CL_REF::SET_POS_CELESTIAL_PSIP_LOCAL_LfromPSIP_CRPIX_L(){
	POS_CELESTIAL_PSIP_LOCAL_L[0]=POS_CELESTIAL_PSIP_CRPIX_L[0]+CCD->CRPIX[0];
	POS_CELESTIAL_PSIP_LOCAL_L[1]=POS_CELESTIAL_PSIP_CRPIX_L[1]+CCD->CRPIX[1];
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

	CAMERA_JACO     =(1+dCdI[0][0])*(1+dCdI[1][1])-dCdI[0][1]*dCdI[1][0];
}

} // namespace tansip
}} // namespace hsc::meas
