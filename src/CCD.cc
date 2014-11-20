//-----------------------------------------------------------
//CCD.cc
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include "CCD.h"

namespace hsc { namespace meas {
namespace tansip {

using namespace std;
//CCDs
CL_CCDs::CL_CCDs(
	std::vector<CCDPosition> const& ccdPosition,
	AnaParam                      * APRM_IN
){
	APRM        = APRM_IN;

	int const NUM_CCD = ccdPosition.size();
	CCD.resize(NUM_CCD);

	for(int i = 0; i < NUM_CCD; ++i){
		CCD[i].CCDs          = this;
		CCD[i].ID            = i;
		CCD[i].NUM_REF		 = 0;
		CCD[i].NUM_FIT		 = 0;
		CCD[i].NUM_REJ		 = 0;
		CCD[i].CRPIX[0]      = 0;
		CCD[i].CRPIX[1]      = 0;
		CCD[i].ASIP[0]		 = Polynomial2D(APRM->ORDER_ASIP);
		CCD[i].ASIP[1]		 = Polynomial2D(APRM->ORDER_ASIP);
		CCD[i].PSIP[0]		 = Polynomial2D(APRM->ORDER_PSIP);
		CCD[i].PSIP[1]		 = Polynomial2D(APRM->ORDER_PSIP);
	}

	GCD.CCDs         = this;
	GCD.ID           = 999;
	GCD.NUM_REF		 = 0;
	GCD.NUM_FIT		 = 0;
	GCD.NUM_REJ		 = 0;
	GCD.CRPIX[0]     = APRM->CRPIX[0];
	GCD.CRPIX[1]     = APRM->CRPIX[1];
	GCD.ASIP[0]		 = Polynomial2D(APRM->ORDER_ASIP);
	GCD.ASIP[1]		 = Polynomial2D(APRM->ORDER_ASIP);
	GCD.PSIP[0]		 = Polynomial2D(APRM->ORDER_PSIP);
	GCD.PSIP[1]		 = Polynomial2D(APRM->ORDER_PSIP);
	GCD.CRVAL[0]     = APRM->CRVAL[0];
	GCD.CRVAL[1]     = APRM->CRVAL[1];

	SET_CRPIX();


	MAX_CRPIX_G[0]=0;
	MAX_CRPIX_G[1]=0;
	MIN_CRPIX_G[0]=0;
	MIN_CRPIX_G[1]=0;
	AVE_CRPIX_G[0]=0;
	AVE_CRPIX_G[1]=0;
	GPOS_C_BASIS[0]=0;
	GPOS_C_BASIS[1]=0;
	GPOS_C_BASIS[2]=0;
	if(APRM->VERBOSITY >= 1)cout<<"-- SET CCDs --"<<endl;
	for(int i = 0; i < NUM_CCD; ++i){
		CCD[i].GPOS_C[0] = ccdPosition[i].centerX;
		CCD[i].GPOS_C[1] = ccdPosition[i].centerY;
		CCD[i].GPOS_C[2] = ccdPosition[i].angle;
		CCD[i].GPOS_C[3] = ccdPosition[i].angle*(180.0/M_PI);
		CCD[i].LENGTH[0] = ccdPosition[i].width;
		CCD[i].LENGTH[1] = ccdPosition[i].height;
		GPOS_C_BASIS[0] += CCD[i].GPOS_C[0];
		GPOS_C_BASIS[1] += CCD[i].GPOS_C[1];
		GPOS_C_BASIS[2] += CCD[i].GPOS_C[2];
	}
	GPOS_C_BASIS[0] /= NUM_CCD;
	GPOS_C_BASIS[1] /= NUM_CCD;
	GPOS_C_BASIS[2] /= NUM_CCD;
	GPOS_C_BASIS[3]=GPOS_C_BASIS[2]*(180.0/M_PI);

	GCD.GPOS_C[0]=0;
	GCD.GPOS_C[1]=0;
	GCD.GPOS_C[2]=0;
	GCD.GPOS_C[3]=0;
	GCD.LENGTH[0]=0;
	GCD.LENGTH[1]=0;

	GET_GPOS_LfromGPOS_C();
}


bool CL_CCDs::CHECK(){
	return CHECK_NUMCCD   ()
		&& CHECK_NUMFIT   ()
		&& CHECK_NUMFITALL()
	;
}
bool CL_CCDs::CHECK_NUMCCD(){
	if(!CCD.empty()){
		if(APRM->VERBOSITY >= 2)cout << "OK : NUM_CCD : " << CCD.size() << endl;
		return true;
	}else{
		cout << "---------------------------------------------" << endl;
		cout << "Input 'NUM_CCD' is '" << CCD.size() << "'"<< endl;
		cout << "Error : NUM_CCD(Number of CCDs) must be larger than 0" << endl;
		cout << "---------------------------------------------" << endl;
		return false;
	}
}
bool CL_CCDs::CHECK_NUMFIT(){
	for(std::size_t i = 0; i < CCD.size(); ++i){
		if(CCD[i].areReferencesSufficient()){
			if(APRM->VERBOSITY >= 2){
				cout << "OK : NUM_FIT : CCD : ";
				cout.width(3);
				cout << i << " : " ;
				cout.width(5);
				cout << CCD[i].NUM_FIT << endl;
			}
		}else{
			cout << "---------------------------------------------" << endl;
			cout << "Warning : NUM_FIT : CCD : ";
			cout.width(3);
			cout << i << " : ";
			cout.width(5);
			cout << CCD[i].NUM_FIT << endl;
			cout << "This ccd will be omitted when determining CCD positions." << endl;
		}
	}
	return true;
}
bool CL_CCDs::CHECK_NUMFITALL(){
	int       ORDER_ASIP = APRM->ORDER_ASIP;
	int const ORDER_PSIP = APRM->ORDER_PSIP;

	if(GCD.NUM_FIT <= 0){
		cout << "---------------------------------------------" << endl;
		cout << "Input 'NUM_FIT' is '" << GCD.NUM_FIT << "'"<< endl;
		cout << "Error : NUM_FIT(Number of references for fitting) must be larger than 0" << endl;
		cout << "---------------------------------------------" << endl;
		return false;
	}else if(GCD.NUM_FIT <= (ORDER_ASIP+1)*(ORDER_ASIP+2)/2 ||
		GCD.NUM_FIT <= (ORDER_PSIP+1)*(ORDER_PSIP+2)/2 ){
			cout << "---------------------------------------------" << endl;
			cout << "Warning : NUM_FIT : CCD : ALL : ";
			cout.width(5);
			cout << GCD.NUM_FIT << endl;
			for(ORDER_ASIP = 0; ORDER_ASIP < 10; ++ORDER_ASIP){
				if((ORDER_ASIP+1+1)*(ORDER_ASIP+2+1)/2 > GCD.NUM_FIT){
					break;
				}
			}
			APRM->ORDER_ASIP = ORDER_ASIP;
			APRM->ORDER_PSIP = ORDER_ASIP;
			cout << "Warning : SET ORDER_ASIP to " << APRM->ORDER_ASIP << endl;
			cout << "Warning : SET ORDER_PSIP to " << APRM->ORDER_PSIP << endl;
			cout << "---------------------------------------------" << endl;
		return true;
	}else{
		if(APRM->VERBOSITY >= 2){
			cout << "OK : NUM_FIT : CCD : ALL : " ;
			cout.width(5);
			cout << GCD.NUM_FIT << endl;
		}
		return true;
	}
}
void CL_CCDs::GET_GPOS_LfromGPOS_C(){
	for(std::vector<CL_CCD>::iterator ccd = CCD.begin();
		ccd != CCD.end(); ++ccd
	){
		ccd->GET_GPOS_LfromGPOS_C();
	}
	GCD.GET_GPOS_LfromGPOS_C();
}
void CL_CCDs::GET_GPOS_CfromGPOS_L(){
	for(std::vector<CL_CCD>::iterator ccd = CCD.begin();
		ccd != CCD.end(); ++ccd
	){
		ccd->GET_GPOS_CfromGPOS_L();
	}

	// mineo: Is this not necessary??
	// GCD.GET_GPOS_CfromGPOS_L();
}
void CL_CCDs::SET_CRPIX(){
	for(std::vector<CL_CCD>::iterator ccd = CCD.begin();
		ccd != CCD.end(); ++ccd
	){
		ccd->CRPIX[0] =
			-(ccd->GPOS_L[0] - GCD.CRPIX[0])*cos(ccd->GPOS_L[2])
			-(ccd->GPOS_L[1] - GCD.CRPIX[1])*sin(ccd->GPOS_L[2]);
		ccd->CRPIX[1] =
			-(ccd->GPOS_L[1] - GCD.CRPIX[1])*cos(ccd->GPOS_L[2])
			+(ccd->GPOS_L[0] - GCD.CRPIX[0])*sin(ccd->GPOS_L[2]);
	}
}
void CL_CCDs::SET_OAPIX(){
	for(std::vector<CL_CCD>::iterator ccd = CCD.begin();
		ccd != CCD.end(); ++ccd
	){
		 ccd->OAPIX[0] =
			-(ccd->GPOS_L[0] - GCD.OAPIX[0])*cos(ccd->GPOS_L[2])
			-(ccd->GPOS_L[1] - GCD.OAPIX[1])*sin(ccd->GPOS_L[2]);
		 ccd->OAPIX[1] =
			-(ccd->GPOS_L[1] - GCD.OAPIX[1])*cos(ccd->GPOS_L[2])
			+(ccd->GPOS_L[0] - GCD.OAPIX[0])*sin(ccd->GPOS_L[2]);
	}
}
void CL_CCDs::SET_CCDs(){
//CR
	SET_CRPIX();
	SET_OAPIX();

//CD SIP DIST FUNCTIONS
	Polynomial2D G_ASIP_0 = GCD.ASIP[0]; // deep copy
	Polynomial2D G_ASIP_1 = GCD.ASIP[1]; // deep copy
	Polynomial2D G_PSIP_0 = GCD.PSIP[0]; // deep copy
	Polynomial2D G_PSIP_1 = GCD.PSIP[1]; // deep copy

	Polynomial2D::CoeffVector coeff_0 = G_ASIP_0.getCoeffVector();
	Polynomial2D::CoeffVector coeff_1 = G_ASIP_1.getCoeffVector();
	for(unsigned ij = 0; ij < coeff_0.size(); ++ij){
		double x = GCD.CD[0][0]*coeff_0[ij] + GCD.CD[0][1]*coeff_1[ij];
		double y = GCD.CD[1][0]*coeff_0[ij] + GCD.CD[1][1]*coeff_1[ij];
		coeff_0[ij] = x;
		coeff_1[ij] = y;
	}
	G_ASIP_0.setCoeffVector(coeff_0);
	G_ASIP_1.setCoeffVector(coeff_1);

	G_ASIP_0.coeff(1,0) += GCD.CD[0][0];
	G_ASIP_0.coeff(0,1) += GCD.CD[0][1];
	G_ASIP_1.coeff(1,0) += GCD.CD[1][0];
	G_ASIP_1.coeff(0,1) += GCD.CD[1][1];
	G_PSIP_0.coeff(1,0) += 1.0;
	G_PSIP_0.coeff(0,1) += 0.0;
	G_PSIP_1.coeff(1,0) += 0.0;
	G_PSIP_1.coeff(0,1) += 1.0;

	for(std::vector<CL_CCD>::iterator ccd = CCD.begin();
		ccd != CCD.end(); ++ccd
	){
		ccd->ASIP[0] = ccd->SET_SIPROT(G_ASIP_0);
		ccd->ASIP[1] = ccd->SET_SIPROT(G_ASIP_1);
		ccd->PSIP[0] = ccd->SET_SIPROT(G_PSIP_0);
		ccd->PSIP[1] = ccd->SET_SIPROT(G_PSIP_1);
		ccd->SET_CDASIP();

		coeff_0 = ccd->PSIP[0].getCoeffVector();
		coeff_1 = ccd->PSIP[1].getCoeffVector();
		for(unsigned ij = 0; ij < coeff_0.size(); ++ij){
			double x = GCD.CD[0][0]*coeff_0[ij]+GCD.CD[0][1]*coeff_1[ij];
			double y = GCD.CD[1][0]*coeff_0[ij]+GCD.CD[1][1]*coeff_1[ij];
			coeff_0[ij]=ccd->InvCD[0][0]*x+ccd->InvCD[0][1]*y;
			coeff_1[ij]=ccd->InvCD[1][0]*x+ccd->InvCD[1][1]*y;
		}
		ccd->PSIP[0].setCoeffVector(coeff_0);
		ccd->PSIP[1].setCoeffVector(coeff_1);

		ccd->SET_CDPSIP();
	}
}
void CL_CCDs::SHOW(){
	int const NUM_CCD    = CCD.size();

	cout << setprecision(3);
	cout << scientific;
	cout << "-- SHOW CCDs --" << endl;
	cout << "NUM_CCD             : " << NUM_CCD        << endl;
	cout << "BASISPOSX   (Center): " ;cout.width(10);cout<< GPOS_C_BASIS[0]<< endl;
	cout << "BASISPOSY   (Center): " ;cout.width(10);cout<< GPOS_C_BASIS[1]<< endl;
	cout << "BASISPOSTrad(Center): " ;cout.width(10);cout<< GPOS_C_BASIS[2]<< endl;
	cout << "BASISPOSTdeg(Center): " ;cout.width(10);cout<< GPOS_C_BASIS[3]<< endl;
	cout << "MAX_CRPIX_G_X       : " ;cout.width(10);cout<< MAX_CRPIX_G[0]   << endl;
	cout << "MAX_CRPIX_G_Y       : " ;cout.width(10);cout<< MAX_CRPIX_G[1]   << endl;
	cout << "MIN_CRPIX_G_X       : " ;cout.width(10);cout<< MIN_CRPIX_G[0]   << endl;
	cout << "MIN_CRPIX_G_Y       : " ;cout.width(10);cout<< MIN_CRPIX_G[1]   << endl;
	cout << "AVE_CRPIX_G_X       : " ;cout.width(10);cout<< AVE_CRPIX_G[0]   << endl;
	cout << "AVE_CRPIX_G_Y       : " ;cout.width(10);cout<< AVE_CRPIX_G[1]   << endl;
	cout << "-- SHOW CCD --" << endl;
	cout << " ID :        X_C        Y_C        T_C       L1       L2 NUM_REF NUM_FIT NUM_REJ" << endl;
	for(int i = 0; i < NUM_CCD; ++i){
		cout.width( 3);
		cout<< i <<" : ";
		cout.width(10);
		cout<<fixed<<setprecision(3)<<CCD[i].GPOS_C[0] <<" ";
		cout.width(10);
		cout<<fixed<<setprecision(3)<<CCD[i].GPOS_C[1] <<" ";
		cout.width(10);
		cout<<fixed<<setprecision(3)<<scientific<<CCD[i].GPOS_C[2] <<" ";
		cout.width(8);
		cout<<fixed<<setprecision(3)<<CCD[i].LENGTH[0] <<" ";
		cout.width(8);
		cout<<fixed<<setprecision(3)<<CCD[i].LENGTH[1] <<" ";
		cout.width(7);
		cout<<CCD[i].NUM_REF << " ";
		cout.width(7);
		cout<<CCD[i].NUM_FIT << " ";
		cout.width(7);
		cout<<CCD[i].NUM_REJ << endl;
	}

	cout.width( 3);
	cout<< "GCD" <<" : ";
	cout.width(10);
	cout<<fixed<<setprecision(3)<<GCD.GPOS_C[0] <<" ";
	cout.width(10);
	cout<<fixed<<setprecision(3)<<GCD.GPOS_C[1] <<" ";
	cout.width(10);
	cout<<fixed<<setprecision(3)<<scientific<<GCD.GPOS_C[2] <<" ";
	cout.width(8);
	cout<<fixed<<setprecision(3)<<GCD.LENGTH[0] <<" ";
	cout.width(8);
	cout<<fixed<<setprecision(3)<<GCD.LENGTH[1] <<" ";
	cout.width(7);
	cout<<GCD.NUM_REF << " ";
	cout.width(7);
	cout<<GCD.NUM_FIT << " ";
	cout.width(7);
	cout<<GCD.NUM_REJ << endl;
}


//CCD
void CCDBase::GET_GPOS_LfromGPOS_C(){
	GPOS_L[0]=GPOS_C[0]-0.5*(LENGTH[0]*cos(GPOS_C[2])-LENGTH[1]*sin(GPOS_C[2]));
	GPOS_L[1]=GPOS_C[1]-0.5*(LENGTH[1]*cos(GPOS_C[2])+LENGTH[0]*sin(GPOS_C[2]));
	GPOS_L[2]=GPOS_C[2];
	GPOS_L[3]=GPOS_C[3];
}
void CCDBase::GET_GPOS_CfromGPOS_L(){
	GPOS_C[0]=GPOS_L[0]+0.5*(LENGTH[0]*cos(GPOS_L[2])-LENGTH[1]*sin(GPOS_L[2]));
	GPOS_C[1]=GPOS_L[1]+0.5*(LENGTH[1]*cos(GPOS_L[2])+LENGTH[0]*sin(GPOS_L[2]));
	GPOS_C[2]=GPOS_L[2];
	GPOS_C[3]=GPOS_L[3];
}
void CCDBase::SET_CDASIP(){
	CD[0][0]=ASIP[0].coeff(1,0);
	CD[0][1]=ASIP[0].coeff(0,1);
	CD[1][0]=ASIP[1].coeff(1,0);
	CD[1][1]=ASIP[1].coeff(0,1);
	InvCD[0][0]= CD[1][1]/(CD[0][0]*CD[1][1]-CD[0][1]*CD[1][0]);
	InvCD[0][1]=-CD[0][1]/(CD[0][0]*CD[1][1]-CD[0][1]*CD[1][0]);
	InvCD[1][0]=-CD[1][0]/(CD[0][0]*CD[1][1]-CD[0][1]*CD[1][0]);
	InvCD[1][1]= CD[0][0]/(CD[0][0]*CD[1][1]-CD[0][1]*CD[1][0]);

	Polynomial2D::CoeffVector coeff_0 = ASIP[0].getCoeffVector();
	Polynomial2D::CoeffVector coeff_1 = ASIP[1].getCoeffVector();
	for(unsigned ij = 0; ij < coeff_0.size(); ++ij){
		double TSIP[2];
		TSIP[0] = coeff_0[ij];
		TSIP[1] = coeff_1[ij];
		coeff_0[ij] = InvCD[0][0]*TSIP[0]+InvCD[0][1]*TSIP[1];
		coeff_1[ij] = InvCD[1][0]*TSIP[0]+InvCD[1][1]*TSIP[1];
	}
	ASIP[0].setCoeffVector(coeff_0);
	ASIP[1].setCoeffVector(coeff_1);

	ASIP[0].coeff(1,0) -= 1;
	ASIP[1].coeff(0,1) -= 1;

	ANGLE=atan2(CD[0][0]-CD[1][1],-CD[1][0]-CD[0][1]);
}
void CCDBase::SET_CDPSIP(){
	PSIP[0].coeff(1,0) -= 1;
	PSIP[1].coeff(0,1) -= 1;
}
Polynomial2D CCDBase::SET_SIPROT(Polynomial2D const& POLY){
	double const THETA = GPOS_L[2];

	Polynomial2D POLY_OUT(POLY.getDegree());
//--------------------------------------------------
	double ABS[10],PHI[10],Z[10][2];

// 0 -----
	if(POLY.getDegree() >= 0)
	POLY_OUT.coeff(0,0) =POLY.coeff(0,0);

// 1 -----
	if(POLY.getDegree() >= 1){
		ABS[1]=hypot(POLY.coeff(0,1),POLY.coeff(1,0));
		PHI[1]=atan2(POLY.coeff(0,1),POLY.coeff(1,0));
		POLY_OUT.coeff(1,0)=ABS[1]*cos(PHI[1]-1*THETA);
		POLY_OUT.coeff(0,1)=ABS[1]*sin(PHI[1]-1*THETA);
	}

// 2 -----
	if(POLY.getDegree() >= 2){
		Z[2][0]=0.5*(POLY.coeff(2,0)-POLY.coeff(0,2));
		Z[2][1]=0.5*(POLY.coeff(1,1));
		ABS[0]=0.5*(POLY.coeff(2,0)+POLY.coeff(0,2));
		ABS[2]=hypot(Z[2][1],Z[2][0]);
		PHI[2]=atan2(Z[2][1],Z[2][0]);
		POLY_OUT.coeff(2,0)=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA);
		POLY_OUT.coeff(1,1)=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA);
		POLY_OUT.coeff(0,2)=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA);
	}

// 3 -----
	if(POLY.getDegree() >= 3){
		Z[1][0]=0.25*(3*POLY.coeff(3,0)+  POLY.coeff(1,2));
		Z[1][1]=0.25*(  POLY.coeff(2,1)+3*POLY.coeff(0,3));
		Z[3][0]=0.25*(  POLY.coeff(3,0)-  POLY.coeff(1,2));
		Z[3][1]=0.25*(  POLY.coeff(2,1)-  POLY.coeff(0,3));
		ABS[1]=hypot(Z[1][1],Z[1][0]);
		ABS[3]=hypot(Z[3][1],Z[3][0]);
		PHI[1]=atan2(Z[1][1],Z[1][0]);
		PHI[3]=atan2(Z[3][1],Z[3][0]);
		POLY_OUT.coeff(3,0)=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA);
		POLY_OUT.coeff(2,1)=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA);
		POLY_OUT.coeff(1,2)=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA);
		POLY_OUT.coeff(0,3)=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA);
	}

// 4 -----
	if(POLY.getDegree() >= 4){
		Z[2][0]=  0.5*(POLY.coeff(4,0)-POLY.coeff(0,4));
		Z[2][1]= 0.25*(POLY.coeff(3,1)+POLY.coeff(1,3));
		Z[4][0]=0.125*(POLY.coeff(4,0)-POLY.coeff(2,2)+POLY.coeff(0,4));
		Z[4][1]=0.125*(POLY.coeff(3,1)-POLY.coeff(1,3));
		ABS[0]=0.125*(3*POLY.coeff(4,0)+POLY.coeff(2,2)+3*POLY.coeff(0,4));
		ABS[2]=hypot(Z[2][1],Z[2][0]);
		ABS[4]=hypot(Z[4][1],Z[4][0]);
		PHI[2]=atan2(Z[2][1],Z[2][0]);
		PHI[4]=atan2(Z[4][1],Z[4][0]);
		POLY_OUT.coeff(4,0)=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA);
		POLY_OUT.coeff(3,1)=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+4*ABS[4]*sin(PHI[4]-4*THETA);
		POLY_OUT.coeff(2,2)=2*ABS[0]+0*ABS[2]*cos(PHI[2]-2*THETA)-6*ABS[4]*cos(PHI[4]-4*THETA);
		POLY_OUT.coeff(1,3)=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)-4*ABS[4]*sin(PHI[4]-4*THETA);
		POLY_OUT.coeff(0,4)=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA);
	}

// 5 -----
	if(POLY.getDegree() >= 5){
		Z[1][0]=(5*POLY.coeff(5,0)+  POLY.coeff(3,2)+  POLY.coeff(1,4))/16.0*2.0;
		Z[1][1]=(  POLY.coeff(4,1)+  POLY.coeff(2,3)+5*POLY.coeff(0,5))/16.0*2.0;
		Z[3][0]=(5*POLY.coeff(5,0)-  POLY.coeff(3,2)-3*POLY.coeff(1,4))/16.0;
		Z[3][1]=(3*POLY.coeff(4,1)+  POLY.coeff(2,3)-5*POLY.coeff(0,5))/16.0;
		Z[5][0]=(  POLY.coeff(5,0)-  POLY.coeff(3,2)+  POLY.coeff(1,4))/16.0;
		Z[5][1]=(  POLY.coeff(4,1)-  POLY.coeff(2,3)+  POLY.coeff(0,5))/16.0;
		ABS[1]=hypot(Z[1][1],Z[1][0]);
		ABS[3]=hypot(Z[3][1],Z[3][0]);
		ABS[5]=hypot(Z[5][1],Z[5][0]);
		PHI[1]=atan2(Z[1][1],Z[1][0]);
		PHI[3]=atan2(Z[3][1],Z[3][0]);
		PHI[5]=atan2(Z[5][1],Z[5][0]);
		POLY_OUT.coeff(5,0)=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA);
		POLY_OUT.coeff(4,1)=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA);
		POLY_OUT.coeff(3,2)=2*ABS[1]*cos(PHI[1]-1*THETA)-2*ABS[3]*cos(PHI[3]-3*THETA)-10*ABS[5]*cos(PHI[5]-5*THETA);
		POLY_OUT.coeff(2,3)=2*ABS[1]*sin(PHI[1]-1*THETA)+2*ABS[3]*sin(PHI[3]-3*THETA)-10*ABS[5]*sin(PHI[5]-5*THETA);
		POLY_OUT.coeff(1,4)=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA);
		POLY_OUT.coeff(0,5)=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA);
	}

// 6 -----
	if(POLY.getDegree() >= 6){
		Z[2][0]=(15*POLY.coeff(6,0)+  POLY.coeff(4,2)-  POLY.coeff(2,4)-15*POLY.coeff(0,6))/32.0;
		Z[2][1]=( 5*POLY.coeff(5,1)+3*POLY.coeff(3,3)+5*POLY.coeff(1,5))/32.0;
		Z[4][0]=( 3*POLY.coeff(6,0)-  POLY.coeff(4,2)-  POLY.coeff(2,4)+ 3*POLY.coeff(0,6))/32.0*2.0;
		Z[4][1]=( 4*POLY.coeff(5,1)+0*POLY.coeff(3,3)-4*POLY.coeff(1,5))/32.0;
		Z[6][0]=( 1*POLY.coeff(6,0)-  POLY.coeff(4,2)+  POLY.coeff(2,4)-   POLY.coeff(0,6))/32.0;
		Z[6][1]=( 1*POLY.coeff(5,1)-1*POLY.coeff(3,3)+1*POLY.coeff(1,5))/32.0;
		ABS[0]= ( 5*POLY.coeff(6,0)+  POLY.coeff(4,2)+  POLY.coeff(2,4)+ 5*POLY.coeff(0,6))/32.0*2.0;
		ABS[2]=hypot(Z[2][1],Z[2][0]);
		ABS[4]=hypot(Z[4][1],Z[4][0]);
		ABS[6]=hypot(Z[6][1],Z[6][0]);
		PHI[2]=atan2(Z[2][1],Z[2][0]);
		PHI[4]=atan2(Z[4][1],Z[4][0]);
		PHI[6]=atan2(Z[6][1],Z[6][0]);
		POLY_OUT.coeff(6,0)=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA)+ 1*ABS[6]*cos(PHI[6]-6*THETA);
		POLY_OUT.coeff(5,1)=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA);
		POLY_OUT.coeff(4,2)=3*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)-5*ABS[4]*cos(PHI[4]-4*THETA)-15*ABS[6]*cos(PHI[6]-6*THETA);
		POLY_OUT.coeff(3,3)=0*ABS[0]+4*ABS[2]*sin(PHI[2]-2*THETA)+0*ABS[4]*sin(PHI[4]-4*THETA)-20*ABS[6]*sin(PHI[6]-6*THETA);
		POLY_OUT.coeff(2,4)=3*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)-5*ABS[4]*cos(PHI[4]-4*THETA)+15*ABS[6]*cos(PHI[6]-6*THETA);
		POLY_OUT.coeff(1,5)=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)-4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA);
		POLY_OUT.coeff(0,6)=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA)- 1*ABS[6]*cos(PHI[6]-6*THETA);
	}

// 7 -----
	if(POLY.getDegree() >= 7){
		Z[1][0]=(35*POLY.coeff(7,0)+5*POLY.coeff(5,2)+3*POLY.coeff(3,4)+ 5*POLY.coeff(1,6))/64.0;
		Z[1][1]=( 5*POLY.coeff(6,1)+3*POLY.coeff(4,3)+5*POLY.coeff(2,5)+35*POLY.coeff(0,7))/64.0;
		Z[3][0]=(21*POLY.coeff(7,0)-1*POLY.coeff(5,2)-3*POLY.coeff(3,4)- 9*POLY.coeff(1,6))/64.0;
		Z[3][1]=( 9*POLY.coeff(6,1)+3*POLY.coeff(4,3)+1*POLY.coeff(2,5)-21*POLY.coeff(0,7))/64.0;
		Z[5][0]=( 7*POLY.coeff(7,0)-3*POLY.coeff(5,2)-1*POLY.coeff(3,4)+ 5*POLY.coeff(1,6))/64.0;
		Z[5][1]=( 5*POLY.coeff(6,1)-1*POLY.coeff(4,3)-3*POLY.coeff(2,5)+ 7*POLY.coeff(0,7))/64.0;
		Z[7][0]=( 1*POLY.coeff(7,0)-1*POLY.coeff(5,2)+1*POLY.coeff(3,4)- 1*POLY.coeff(1,6))/64.0;
		Z[7][1]=( 1*POLY.coeff(6,1)-1*POLY.coeff(4,3)+1*POLY.coeff(2,5)- 1*POLY.coeff(0,7))/64.0;
		ABS[1]=hypot(Z[1][1],Z[1][0]);
		ABS[3]=hypot(Z[3][1],Z[3][0]);
		ABS[5]=hypot(Z[5][1],Z[5][0]);
		ABS[7]=hypot(Z[7][1],Z[7][0]);
		PHI[1]=atan2(Z[1][1],Z[1][0]);
		PHI[3]=atan2(Z[3][1],Z[3][0]);
		PHI[5]=atan2(Z[5][1],Z[5][0]);
		PHI[7]=atan2(Z[7][1],Z[7][0]);
		POLY_OUT.coeff(7,0)=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA)+ 1*ABS[7]*cos(PHI[7]-7*THETA);
		POLY_OUT.coeff(6,1)=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA)+ 7*ABS[7]*sin(PHI[7]-7*THETA);
		POLY_OUT.coeff(5,2)=3*ABS[1]*cos(PHI[1]-1*THETA)-1*ABS[3]*cos(PHI[3]-3*THETA)- 9*ABS[5]*cos(PHI[5]-5*THETA)-21*ABS[7]*cos(PHI[7]-7*THETA);
		POLY_OUT.coeff(4,3)=3*ABS[1]*sin(PHI[1]-1*THETA)+5*ABS[3]*sin(PHI[3]-3*THETA)- 5*ABS[5]*sin(PHI[5]-5*THETA)-35*ABS[7]*sin(PHI[7]-7*THETA);
		POLY_OUT.coeff(3,4)=3*ABS[1]*cos(PHI[1]-1*THETA)-5*ABS[3]*cos(PHI[3]-3*THETA)- 5*ABS[5]*cos(PHI[5]-5*THETA)+35*ABS[7]*cos(PHI[7]-7*THETA);
		POLY_OUT.coeff(2,5)=3*ABS[1]*sin(PHI[1]-1*THETA)+1*ABS[3]*sin(PHI[3]-3*THETA)- 9*ABS[5]*sin(PHI[5]-5*THETA)+21*ABS[7]*sin(PHI[7]-7*THETA);
		POLY_OUT.coeff(1,6)=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA)- 7*ABS[7]*cos(PHI[7]-7*THETA);
		POLY_OUT.coeff(0,7)=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA)- 1*ABS[7]*sin(PHI[7]-7*THETA);
	}

// 8 -----
	if(POLY.getDegree() >= 8){
		Z[2][0]=(56*POLY.coeff(8,0)+4*POLY.coeff(6,2)+0*POLY.coeff(4,4)- 4*POLY.coeff(2,6)-56*POLY.coeff(0,8))/128.0;
		Z[2][1]=(14*POLY.coeff(7,1)+6*POLY.coeff(5,3)+6*POLY.coeff(3,5)+14*POLY.coeff(1,7))/128.0;
		Z[4][0]=(28*POLY.coeff(8,0)-4*POLY.coeff(6,2)-4*POLY.coeff(4,4)- 4*POLY.coeff(2,6)+28*POLY.coeff(0,8))/128.0;
		Z[4][1]=(14*POLY.coeff(7,1)+2*POLY.coeff(5,3)-2*POLY.coeff(3,5)-14*POLY.coeff(1,7))/128.0;
		Z[6][0]=( 8*POLY.coeff(8,0)-4*POLY.coeff(6,2)+0*POLY.coeff(4,4)+ 4*POLY.coeff(2,6)- 8*POLY.coeff(0,8))/128.0;
		Z[6][1]=( 6*POLY.coeff(7,1)-2*POLY.coeff(5,3)-2*POLY.coeff(3,5)+ 6*POLY.coeff(1,7))/128.0;
		Z[8][0]=( 1*POLY.coeff(8,0)-1*POLY.coeff(6,2)+1*POLY.coeff(4,4)- 1*POLY.coeff(2,6)+ 1*POLY.coeff(0,8))/128.0;
		Z[8][1]=( 1*POLY.coeff(7,1)-1*POLY.coeff(5,3)+1*POLY.coeff(3,5)- 1*POLY.coeff(1,7))/128.0;
		ABS[0]= (35*POLY.coeff(8,0)+5*POLY.coeff(6,2)+3*POLY.coeff(4,4)+ 5*POLY.coeff(2,6)+35*POLY.coeff(0,8))/128.0;
		ABS[2]=hypot(Z[2][1],Z[2][0]);
		ABS[4]=hypot(Z[4][1],Z[4][0]);
		ABS[6]=hypot(Z[6][1],Z[6][0]);
		ABS[8]=hypot(Z[8][1],Z[8][0]);
		PHI[2]=atan2(Z[2][1],Z[2][0]);
		PHI[4]=atan2(Z[4][1],Z[4][0]);
		PHI[6]=atan2(Z[6][1],Z[6][0]);
		PHI[8]=atan2(Z[8][1],Z[8][0]);
		POLY_OUT.coeff(8,0)=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+ 1*ABS[4]*cos(PHI[4]-4*THETA)+ 1*ABS[6]*cos(PHI[6]-6*THETA)+ 1*ABS[8]*cos(PHI[8]-8*THETA);
		POLY_OUT.coeff(7,1)=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+ 4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA)+ 8*ABS[8]*sin(PHI[8]-8*THETA);
		POLY_OUT.coeff(6,2)=4*ABS[0]+2*ABS[2]*cos(PHI[2]-2*THETA)- 4*ABS[4]*cos(PHI[4]-4*THETA)-14*ABS[6]*cos(PHI[6]-6*THETA)-28*ABS[8]*cos(PHI[8]-8*THETA);
		POLY_OUT.coeff(5,3)=0*ABS[0]+6*ABS[2]*sin(PHI[2]-2*THETA)+ 4*ABS[4]*sin(PHI[4]-4*THETA)-14*ABS[6]*sin(PHI[6]-6*THETA)-56*ABS[8]*sin(PHI[8]-8*THETA);
		POLY_OUT.coeff(4,4)=6*ABS[0]+0*ABS[2]*cos(PHI[2]-2*THETA)-10*ABS[4]*cos(PHI[4]-4*THETA)+ 0*ABS[6]*cos(PHI[6]-6*THETA)+70*ABS[8]*cos(PHI[8]-8*THETA);
		POLY_OUT.coeff(3,5)=0*ABS[0]+6*ABS[2]*sin(PHI[2]-2*THETA)- 4*ABS[4]*sin(PHI[4]-4*THETA)-14*ABS[6]*sin(PHI[6]-6*THETA)+56*ABS[8]*sin(PHI[8]-8*THETA);
		POLY_OUT.coeff(2,6)=4*ABS[0]-2*ABS[2]*cos(PHI[2]-2*THETA)- 4*ABS[4]*cos(PHI[4]-4*THETA)+14*ABS[6]*cos(PHI[6]-6*THETA)-28*ABS[8]*cos(PHI[8]-8*THETA);
		POLY_OUT.coeff(1,7)=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)- 4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA)- 8*ABS[8]*sin(PHI[8]-8*THETA);
		POLY_OUT.coeff(0,8)=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+ 1*ABS[4]*cos(PHI[4]-4*THETA)- 1*ABS[6]*cos(PHI[6]-6*THETA)+ 1*ABS[8]*cos(PHI[8]-8*THETA);
	}

// 9 -----
	if(POLY.getDegree() >= 9){
		Z[1][0]=(126*POLY.coeff(9,0)+14*POLY.coeff(7,2)+6*POLY.coeff(5,4)+ 6*POLY.coeff(3,6)+ 14*POLY.coeff(1,8))/256.0;
		Z[1][1]=( 14*POLY.coeff(8,1)+ 6*POLY.coeff(6,3)+6*POLY.coeff(4,5)+14*POLY.coeff(2,7)+126*POLY.coeff(0,9))/256.0;
		Z[3][0]=( 84*POLY.coeff(9,0)+ 0*POLY.coeff(7,2)-4*POLY.coeff(5,4)- 8*POLY.coeff(3,6)- 28*POLY.coeff(1,8))/256.0;
		Z[3][1]=( 28*POLY.coeff(8,1)+ 8*POLY.coeff(6,3)+4*POLY.coeff(4,5)+ 0*POLY.coeff(2,7)- 84*POLY.coeff(0,9))/256.0;
		Z[5][0]=( 36*POLY.coeff(9,0)- 8*POLY.coeff(7,2)-4*POLY.coeff(5,4)+ 0*POLY.coeff(3,6)+ 20*POLY.coeff(1,8))/256.0;
		Z[5][1]=( 20*POLY.coeff(8,1)- 0*POLY.coeff(6,3)-4*POLY.coeff(4,5)- 8*POLY.coeff(2,7)+ 36*POLY.coeff(0,9))/256.0;
		Z[7][0]=(  9*POLY.coeff(9,0)- 5*POLY.coeff(7,2)+1*POLY.coeff(5,4)+ 3*POLY.coeff(3,6)-  7*POLY.coeff(1,8))/256.0;
		Z[7][1]=(  7*POLY.coeff(8,1)- 3*POLY.coeff(6,3)-1*POLY.coeff(4,5)+ 5*POLY.coeff(2,7)-  9*POLY.coeff(0,9))/256.0;
		Z[9][0]=(  1*POLY.coeff(9,0)- 1*POLY.coeff(7,2)+1*POLY.coeff(5,4)- 1*POLY.coeff(3,6)+  1*POLY.coeff(1,8))/256.0;
		Z[9][1]=(  1*POLY.coeff(8,1)- 1*POLY.coeff(6,3)+1*POLY.coeff(4,5)- 1*POLY.coeff(2,7)+  1*POLY.coeff(0,9))/256.0;
		ABS[1]=hypot(Z[1][1],Z[1][0]);
		ABS[3]=hypot(Z[3][1],Z[3][0]);
		ABS[5]=hypot(Z[5][1],Z[5][0]);
		ABS[7]=hypot(Z[7][1],Z[7][0]);
		ABS[9]=hypot(Z[9][1],Z[9][0]);
		PHI[1]=atan2(Z[1][1],Z[1][0]);
		PHI[3]=atan2(Z[3][1],Z[3][0]);
		PHI[5]=atan2(Z[5][1],Z[5][0]);
		PHI[7]=atan2(Z[7][1],Z[7][0]);
		PHI[9]=atan2(Z[9][1],Z[9][0]);
		POLY_OUT.coeff(9,0)=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA)+ 1*ABS[7]*cos(PHI[7]-7*THETA)+  1*ABS[9]*cos(PHI[9]-9*THETA);
		POLY_OUT.coeff(8,1)=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA)+ 7*ABS[7]*sin(PHI[7]-7*THETA)+  9*ABS[9]*sin(PHI[9]-9*THETA);
		POLY_OUT.coeff(7,2)=4*ABS[1]*cos(PHI[1]-1*THETA)+0*ABS[3]*cos(PHI[3]-3*THETA)- 8*ABS[5]*cos(PHI[5]-5*THETA)-20*ABS[7]*cos(PHI[7]-7*THETA)- 36*ABS[9]*cos(PHI[9]-9*THETA);
		POLY_OUT.coeff(6,3)=4*ABS[1]*sin(PHI[1]-1*THETA)+8*ABS[3]*sin(PHI[3]-3*THETA)+ 0*ABS[5]*sin(PHI[5]-5*THETA)-28*ABS[7]*sin(PHI[7]-7*THETA)- 84*ABS[9]*sin(PHI[9]-9*THETA);
		POLY_OUT.coeff(5,4)=6*ABS[1]*cos(PHI[1]-1*THETA)-6*ABS[3]*cos(PHI[3]-3*THETA)-14*ABS[5]*cos(PHI[5]-5*THETA)+14*ABS[7]*cos(PHI[7]-7*THETA)+126*ABS[9]*cos(PHI[9]-9*THETA);
		POLY_OUT.coeff(4,5)=6*ABS[1]*sin(PHI[1]-1*THETA)+6*ABS[3]*sin(PHI[3]-3*THETA)-14*ABS[5]*sin(PHI[5]-5*THETA)-14*ABS[7]*sin(PHI[7]-7*THETA)+126*ABS[9]*sin(PHI[9]-9*THETA);
		POLY_OUT.coeff(3,6)=4*ABS[1]*cos(PHI[1]-1*THETA)-8*ABS[3]*cos(PHI[3]-3*THETA)+ 0*ABS[5]*cos(PHI[5]-5*THETA)+28*ABS[7]*cos(PHI[7]-7*THETA)- 84*ABS[9]*cos(PHI[9]-9*THETA);
		POLY_OUT.coeff(2,7)=4*ABS[1]*sin(PHI[1]-1*THETA)+0*ABS[3]*sin(PHI[3]-3*THETA)- 8*ABS[5]*sin(PHI[5]-5*THETA)+20*ABS[7]*sin(PHI[7]-7*THETA)- 36*ABS[9]*sin(PHI[9]-9*THETA);
		POLY_OUT.coeff(1,8)=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA)- 7*ABS[7]*cos(PHI[7]-7*THETA)+  9*ABS[9]*cos(PHI[9]-9*THETA);
		POLY_OUT.coeff(0,9)=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA)- 1*ABS[7]*sin(PHI[7]-7*THETA)+  1*ABS[9]*sin(PHI[9]-9*THETA);
	}

	return POLY_OUT;
}

void CCDBase::SHOW(){
	int const ORDER_ASIP = CCDs->APRM->ORDER_ASIP;
	int const ORDER_PSIP = CCDs->APRM->ORDER_PSIP;

	cout << setprecision(3);
	cout << scientific;
	cout << "-- SHOW CCD --" << endl;
	cout << "ID            : " << ID      << endl;
	cout << "NUM_REF       : " << NUM_REF << endl;
	cout << "NUM_FIT       : " << NUM_FIT << endl;
	cout << "NUM_REJ       : " << NUM_REJ << endl;
	cout << "POS_C X       : " ;cout.width(10);cout<< GPOS_C[0] << endl;
	cout << "POS_C Y       : " ;cout.width(10);cout<< GPOS_C[1] << endl;
	cout << "POS_C T       : " ;cout.width(10);cout<< GPOS_C[2] <<" (radian) "<< endl;
	cout << "POS_C T       : " ;cout.width(10);cout<< GPOS_C[3] <<" (degree) "<< endl;
	cout << "POS_L X       : " ;cout.width(10);cout<< GPOS_L[0] << endl;
	cout << "POS_L Y       : " ;cout.width(10);cout<< GPOS_L[1] << endl;
	cout << "POS_L T       : " ;cout.width(10);cout<< GPOS_L[2] <<" (radian) "<< endl;
	cout << "POS_L T       : " ;cout.width(10);cout<< GPOS_L[3] <<" (degree) "<< endl;
	cout << "LENGTH X      : " << LENGTH[0] << endl;
	cout << "LENGTH Y      : " << LENGTH[1] << endl;
	cout << "ANGLE         : " ;cout.width(10);cout<< ANGLE << endl;
	cout << "CRPIX 1       : " ;cout.width(10);cout<< CRPIX[0] << endl;
	cout << "CRPIX 2       : " ;cout.width(10);cout<< CRPIX[1] << endl;
	cout << "CRVAL Ra      : " ;cout.width(10);cout<< CCDs->GCD.CRVAL[0] <<" (degree) " << endl;
	cout << "CRVAL Dec     : " ;cout.width(10);cout<< CCDs->GCD.CRVAL[1] <<" (degree) " << endl;
	cout << "OAPIX 1       : " ;cout.width(10);cout<<  OAPIX[0] << endl;
	cout << "OAPIX 2       : " ;cout.width(10);cout<<  OAPIX[1] << endl;
	cout << "CD1_1         : " ;cout.width(10);cout<< CD[0][0] <<" (degree) " << endl;
	cout << "CD1_2         : " ;cout.width(10);cout<< CD[0][1] <<" (degree) " << endl;
	cout << "CD2_1         : " ;cout.width(10);cout<< CD[1][0] <<" (degree) " << endl;
	cout << "CD2_2         : " ;cout.width(10);cout<< CD[1][1] <<" (degree) " << endl;
	cout << "InvCD1_1      : " ;cout.width(10);cout<< InvCD[0][0] <<" (degree) " << endl;
	cout << "InvCD1_2      : " ;cout.width(10);cout<< InvCD[0][1] <<" (degree) " << endl;
	cout << "InvCD2_1      : " ;cout.width(10);cout<< InvCD[1][0] <<" (degree) " << endl;
	cout << "InvCD2_2      : " ;cout.width(10);cout<< InvCD[1][1] <<" (degree) " << endl;

	cout << "ORDER  SIP_A  : " << ORDER_ASIP<< endl;
	Polynomial2D::CoeffVector coeff = ASIP[0].getCoeffVector();
	for(unsigned i = 0; i < coeff.size(); ++i){
		cout<< " SIP_A ";cout.width(3);cout<<i<<"    : ";cout.width(10);cout<< coeff[i]<<endl;
	}

	cout << "ORDER  SIP_B  : " << ORDER_ASIP<< endl;
	coeff = ASIP[1].getCoeffVector();
	for(unsigned i = 0; i < coeff.size(); ++i){
		cout<< " SIP_B ";cout.width(3);cout<<i<<"    : ";cout.width(10);cout<< coeff[i]<<endl;
	}
	cout << "ORDER PSIP_A  : " << ORDER_PSIP<< endl;
	coeff = PSIP[0].getCoeffVector();
	for(unsigned i = 0; i < coeff.size(); ++i){
		cout<< "PSIP_A ";cout.width(3);cout<<i<<"    : ";cout.width(10);cout<< coeff[i]<<endl;
	}
	cout << "ORDER PSIP_B  : " << ORDER_PSIP<< endl;
	coeff = PSIP[1].getCoeffVector();
	for(unsigned i = 0; i < coeff.size(); ++i){
		cout<< "PSIP_B ";cout.width(3);cout<<i<<"    : ";cout.width(10);cout<< coeff[i]<<endl;
	}
	cout << "DIF AVE  SIPX : " ;cout.width(10);cout<< DIF_AVE_ASIP[0] <<" (pixel) " << endl;
	cout << "DIF AVE  SIPY : " ;cout.width(10);cout<< DIF_AVE_ASIP[1] <<" (pixel) " << endl;
	cout << "DIF RMS  SIPX : " ;cout.width(10);cout<< DIF_RMS_ASIP[0] <<" (pixel) " << endl;
	cout << "DIF RMS  SIPY : " ;cout.width(10);cout<< DIF_RMS_ASIP[1] <<" (pixel) " << endl;
	cout << "DIF MAX  SIPX : " ;cout.width(10);cout<< DIF_MAX_ASIP[0] <<" (pixel) " << endl;
	cout << "DIF MAX  SIPY : " ;cout.width(10);cout<< DIF_MAX_ASIP[1] <<" (pixel) " << endl;
	cout << "DIF AVE PSIPX : " ;cout.width(10);cout<< DIF_AVE_PSIP[0] <<" (pixel) " << endl;
	cout << "DIF AVE PSIPY : " ;cout.width(10);cout<< DIF_AVE_PSIP[1] <<" (pixel) " << endl;
	cout << "DIF RMS PSIPX : " ;cout.width(10);cout<< DIF_RMS_PSIP[0] <<" (pixel) " << endl;
	cout << "DIF RMS PSIPY : " ;cout.width(10);cout<< DIF_RMS_PSIP[1] <<" (pixel) " << endl;
	cout << "DIF MAX PSIPX : " ;cout.width(10);cout<< DIF_MAX_PSIP[0] <<" (pixel) " << endl;
	cout << "DIF MAX PSIPY : " ;cout.width(10);cout<< DIF_MAX_PSIP[1] <<" (pixel) " << endl;
}

} // namespace tansip
}} // namespace hsc::meas
