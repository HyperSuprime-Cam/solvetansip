//-----------------------------------------------------------
//CCD.cc
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#include"hsc/meas/tansip/CCD.h"

using namespace std;
//CCDs
void CL_CCDs::SET_INIT(CL_APRM *APRM_IN){
	APRM=APRM_IN;
	MODE_CCDPOS=&APRM_IN->MODE_CCDPOS;
	NUM_CCD    =&APRM_IN->NUM_CCD;
	FLAG_STD   =&APRM_IN->FLAG_STD;
	CCD = new CL_CCD[*NUM_CCD+1];
	
	ORDER_ASIP     =&APRM->ORDER_ASIP;
	ORDER_PSIP     =&APRM->ORDER_PSIP;
	CRPIX[0]       =&APRM->CRPIX[0];
	CRPIX[1]       =&APRM->CRPIX[1];
	CRVAL[0]       =&APRM->CRVAL[0];
	CRVAL[1]       =&APRM->CRVAL[1];
	
	int i;
	for(i=0;i<*NUM_CCD;i++){
		CCD[i].CRPIX[0]=new double[1];
		CCD[i].CRPIX[1]=new double[1];
	}
	for(i=0;i<*NUM_CCD+1;i++){
		CCD[i].SET_INIT();
		CCD[i].ORDER_ASIP	=ORDER_ASIP;
		CCD[i].ORDER_PSIP	=ORDER_PSIP;
		CCD[i].NUM_REF		=0;
		CCD[i].NUM_FIT		=0;
		CCD[i].NUM_REJ		=0;
		CCD[i].CRVAL[0]		=CRVAL[0];
		CCD[i].CRVAL[1]		=CRVAL[1];
		CCD[i].ASIP[0]		=new double[(*ORDER_ASIP+1)*(*ORDER_ASIP+2)];
		CCD[i].ASIP[1]		=new double[(*ORDER_ASIP+1)*(*ORDER_ASIP+2)];
		CCD[i].PSIP[0]		=new double[(*ORDER_PSIP+1)*(*ORDER_PSIP+2)];
		CCD[i].PSIP[1]		=new double[(*ORDER_PSIP+1)*(*ORDER_PSIP+2)];
		CCD[i].PSIP_CONV	=new double[(*ORDER_PSIP+1)*(*ORDER_PSIP+2)];
		CCD[i].PSIP_ROT		=new double[(*ORDER_PSIP+1)*(*ORDER_PSIP+2)];
		CCD[i].PSIP_SHEAR[0]	=new double[(*ORDER_PSIP+1)*(*ORDER_PSIP+2)];
		CCD[i].PSIP_SHEAR[1]	=new double[(*ORDER_PSIP+1)*(*ORDER_PSIP+2)];
		CCD[i].PSIP_MAG		=new double[(*ORDER_PSIP+1)*(*ORDER_PSIP+2)];
		CCD[i].PSIP_JACO	=new double[(*ORDER_PSIP+1)*(*ORDER_PSIP+2)];
	}
	CCD[*NUM_CCD].CRPIX[0]=CRPIX[0];
	CCD[*NUM_CCD].CRPIX[1]=CRPIX[1];
	SET_CRPIX();
}
void CL_CCDs::SET_INPUT(std::vector< std::vector< std::string > > CCD_Argvs,CL_APRM *APRM){
	int i;
	
	SET_INIT(APRM);
	MAX_CRPIX_G_R =0;
	MAX_CRPIX_G[0]=0;
	MAX_CRPIX_G[1]=0;
	MIN_CRPIX_G[0]=0;
	MIN_CRPIX_G[1]=0;
	AVE_CRPIX_G[0]=0;
	AVE_CRPIX_G[1]=0;
	GPOS_C_BASIS[0]=0;
	GPOS_C_BASIS[1]=0;
	GPOS_C_BASIS[2]=0;
	if(*FLAG_STD>0.5)cout<<"-- SET CCDs --"<<endl;
	for(i=0;i<(*NUM_CCD);i++){
		CCD[i].ID       =atoi(CCD_Argvs[i][0].c_str());
		CCD[i].GPOS_C[0]=atof(CCD_Argvs[i][1].c_str());
		CCD[i].GPOS_C[1]=atof(CCD_Argvs[i][2].c_str());
		CCD[i].GPOS_C[2]=atof(CCD_Argvs[i][3].c_str());
		CCD[i].GPOS_C[3]=atof(CCD_Argvs[i][3].c_str())*180.0/3.14159265;
		CCD[i].LENGTH[0]=atoi(CCD_Argvs[i][4].c_str());
		CCD[i].LENGTH[1]=atoi(CCD_Argvs[i][5].c_str());
		GPOS_C_BASIS[0]+=CCD[i].GPOS_C[0];
		GPOS_C_BASIS[1]+=CCD[i].GPOS_C[1];
		GPOS_C_BASIS[2]+=CCD[i].GPOS_C[2];
	}
	GPOS_C_BASIS[0]/=(*NUM_CCD);
	GPOS_C_BASIS[1]/=(*NUM_CCD);
	GPOS_C_BASIS[2]/=(*NUM_CCD);
	GPOS_C_BASIS[3]=GPOS_C_BASIS[2]*180/3.14159265;
	CCD[*NUM_CCD].ID       =999;
	CCD[*NUM_CCD].GPOS_C[0]=0;
	CCD[*NUM_CCD].GPOS_C[1]=0;
	CCD[*NUM_CCD].GPOS_C[2]=0;
	CCD[*NUM_CCD].GPOS_C[3]=0;
	CCD[*NUM_CCD].LENGTH[0]=0;
	CCD[*NUM_CCD].LENGTH[1]=0;
	
	GET_GPOS_LfromGPOS_C();
}
void CL_CCDs::SET_END(){
	delete [] CCD;
	int i;
	for(i=0;i<*NUM_CCD;i++){
		delete [] CCD[i].CRPIX[0];
		delete [] CCD[i].CRPIX[1];
	}
	for(i=0;i<*NUM_CCD+1;i++){
		delete [] CCD[i].ASIP[0];
		delete [] CCD[i].ASIP[1];
		delete [] CCD[i].PSIP[0];
		delete [] CCD[i].PSIP[1];
		delete [] CCD[i].PSIP_CONV;
		delete [] CCD[i].PSIP_ROT;
		delete [] CCD[i].PSIP_SHEAR[0];
		delete [] CCD[i].PSIP_SHEAR[1];
		delete [] CCD[i].PSIP_MAG;
		delete [] CCD[i].PSIP_JACO;
	}
}
int  CL_CCDs::CHECK(){
	if(CHECK_NUMCCD()==1)return 1;
	if(CHECK_NUMFIT()==1)return 1;
	if(CHECK_NUMFITALL()==1)return 1;
	return 0;
}
int  CL_CCDs::CHECK_NUMCCD(){
	if(*NUM_CCD>0.5){
		if(*FLAG_STD>1.5)cout << "OK : NUM_CCD : " << *NUM_CCD << endl;
		return 0;
	}else{
		cout << "---------------------------------------------" << endl;
		cout << "Input 'NUM_CCD' is '" << NUM_CCD << "'"<< endl;
		cout << "Error : NUM_CCD(Number of CCDs) must be larger than 0" << endl;
		cout << "---------------------------------------------" << endl;
		return 1;
	}
}
int  CL_CCDs::CHECK_NUMFIT(){
	int i;
	for(i=0;i<*NUM_CCD;i++){
		if(CCD[i].NUM_FIT>2.5){
			if(*FLAG_STD>1.5){
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
			*MODE_CCDPOS=0;
			cout << "Warning : SET MODE_CCDPOS to " << *MODE_CCDPOS << endl;
			cout << "---------------------------------------------" << endl;
		}
	}
	return 0;

}
int  CL_CCDs::CHECK_NUMFITALL(){
	if(CCD[*NUM_CCD].NUM_FIT<0.5){
		cout << "---------------------------------------------" << endl;
		cout << "Input 'NUM_FIT' is '" << CCD[*NUM_CCD].NUM_FIT << "'"<< endl;
		cout << "Error : NUM_FIT(Number of references for fitting) must be larger than 0" << endl;
		cout << "---------------------------------------------" << endl;
		return 1;
	}else if(CCD[*NUM_CCD].NUM_FIT<(0.5*(*ORDER_ASIP+1)*(*ORDER_ASIP+2)+1)||
		 CCD[*NUM_CCD].NUM_FIT<(0.5*(*ORDER_PSIP+1)*(*ORDER_PSIP+2)+1)){
			cout << "---------------------------------------------" << endl;
			cout << "Warning : NUM_FIT : CCD : ALL : ";
			cout.width(5);
			cout << CCD[*NUM_CCD].NUM_FIT << endl;
			for(*ORDER_ASIP=0;*ORDER_ASIP<10;*ORDER_ASIP+=1)
			if(0.5*(*ORDER_ASIP+1+1)*(*ORDER_ASIP+2+1)>CCD[*NUM_CCD].NUM_FIT)
			break;
			*ORDER_PSIP=*ORDER_ASIP;
			cout << "Warning : SET ORDER_ASIP to " << *ORDER_ASIP << endl;
			cout << "Warning : SET ORDER_PSIP to " << *ORDER_PSIP << endl;
			cout << "---------------------------------------------" << endl;
		return 0;
	}else{
		if(*FLAG_STD>1.5){
			cout << "OK : NUM_FIT : CCD : ALL : " ;
			cout.width(5);
			cout << CCD[*NUM_CCD].NUM_FIT << endl;
		}
		return 0;
	}
}
void CL_CCDs::GET_GPOS_LfromGPOS_C(){
	int i;
	for(i=0;i<*NUM_CCD+1;i++)
	CCD[i].GET_GPOS_LfromGPOS_C();
}
void CL_CCDs::GET_GPOS_CfromGPOS_L(){
	int i;
	for(i=0;i<*NUM_CCD;i++)
	CCD[i].GET_GPOS_CfromGPOS_L();
}
void CL_CCDs::SET_CRVAL(){
	int i;
	for(i=0;i<*NUM_CCD;i++){
		*CCD[i].CRVAL[0]=*CCD[*NUM_CCD].CRVAL[0];
		*CCD[i].CRVAL[1]=*CCD[*NUM_CCD].CRVAL[1];
	}
}
void CL_CCDs::SET_CRPIX(){
	int i;
	for(i=0;i<*NUM_CCD;i++){
		*CCD[i].CRPIX[0]=-(CCD[i].GPOS_L[0]-*CCD[*NUM_CCD].CRPIX[0])*cos(CCD[i].GPOS_L[2])
				 -(CCD[i].GPOS_L[1]-*CCD[*NUM_CCD].CRPIX[1])*sin(CCD[i].GPOS_L[2]);
		*CCD[i].CRPIX[1]=-(CCD[i].GPOS_L[1]-*CCD[*NUM_CCD].CRPIX[1])*cos(CCD[i].GPOS_L[2])
			         +(CCD[i].GPOS_L[0]-*CCD[*NUM_CCD].CRPIX[0])*sin(CCD[i].GPOS_L[2]);
	}
}
void CL_CCDs::SET_OAPIX(){
	int i;
	for(i=0;i<*NUM_CCD;i++){
		 CCD[i].OAPIX[0]=-(CCD[i].GPOS_L[0]-CCD[*NUM_CCD].OAPIX[0])*cos(CCD[i].GPOS_L[2])
				 -(CCD[i].GPOS_L[1]-CCD[*NUM_CCD].OAPIX[1])*sin(CCD[i].GPOS_L[2]);
		 CCD[i].OAPIX[1]=-(CCD[i].GPOS_L[1]-CCD[*NUM_CCD].OAPIX[1])*cos(CCD[i].GPOS_L[2])
			         +(CCD[i].GPOS_L[0]-CCD[*NUM_CCD].OAPIX[0])*sin(CCD[i].GPOS_L[2]);
	}
}
void CL_CCDs::SET_CCDs(){
//CR
	SET_CRVAL();
	SET_CRPIX();
	SET_OAPIX();

//CD SIP DIST FUNCTIONS
	double *G_ASIP[2],*G_PSIP[2];
	G_ASIP[0]=CPP_MEMORY_NEWdouble1((*ORDER_ASIP+1)*(*ORDER_ASIP+2));
	G_ASIP[1]=CPP_MEMORY_NEWdouble1((*ORDER_ASIP+1)*(*ORDER_ASIP+2));
	G_PSIP[0]=CPP_MEMORY_NEWdouble1((*ORDER_PSIP+1)*(*ORDER_PSIP+2));
	G_PSIP[1]=CPP_MEMORY_NEWdouble1((*ORDER_PSIP+1)*(*ORDER_PSIP+2));
	
	int i,j,ij,CID;
	ij=0;
	for(i=0;i<*ORDER_ASIP+1  ;i++)
	for(j=0;j<*ORDER_ASIP+1-i;j++){
		G_ASIP[0][ij]=CCD[(*NUM_CCD)].CD[0][0]*CCD[(*NUM_CCD)].ASIP[0][ij]+CCD[(*NUM_CCD)].CD[0][1]*CCD[(*NUM_CCD)].ASIP[1][ij];
		G_ASIP[1][ij]=CCD[(*NUM_CCD)].CD[1][0]*CCD[(*NUM_CCD)].ASIP[0][ij]+CCD[(*NUM_CCD)].CD[1][1]*CCD[(*NUM_CCD)].ASIP[1][ij];
		ij++;
	}
	ij=0;
	for(i=0;i<*ORDER_PSIP+1  ;i++)
	for(j=0;j<*ORDER_PSIP+1-i;j++){
		G_PSIP[0][ij]=CCD[(*NUM_CCD)].PSIP[0][ij];
		G_PSIP[1][ij]=CCD[(*NUM_CCD)].PSIP[1][ij];
		ij++;
	}

	G_ASIP[0][1*(*ORDER_ASIP)+1]+=CCD[(*NUM_CCD)].CD[0][0];
	G_ASIP[0][0*(*ORDER_ASIP)+1]+=CCD[(*NUM_CCD)].CD[0][1];
	G_ASIP[1][1*(*ORDER_ASIP)+1]+=CCD[(*NUM_CCD)].CD[1][0];
	G_ASIP[1][0*(*ORDER_ASIP)+1]+=CCD[(*NUM_CCD)].CD[1][1];
	G_PSIP[0][1*(*ORDER_PSIP)+1]+=1.0;
	G_PSIP[0][0*(*ORDER_PSIP)+1]+=0.0;
	G_PSIP[1][1*(*ORDER_PSIP)+1]+=0.0;
	G_PSIP[1][0*(*ORDER_PSIP)+1]+=1.0;
	
	double IABP[2];
	for(CID=0;CID<*NUM_CCD;CID++){
		CCD[CID].SET_SIPROT(*ORDER_ASIP,G_ASIP[0],CCD[CID].ASIP[0]);
		CCD[CID].SET_SIPROT(*ORDER_ASIP,G_ASIP[1],CCD[CID].ASIP[1]);
		CCD[CID].SET_SIPROT(*ORDER_PSIP,G_PSIP[0],CCD[CID].PSIP[0]);
		CCD[CID].SET_SIPROT(*ORDER_PSIP,G_PSIP[1],CCD[CID].PSIP[1]);
		CCD[CID].SET_CDASIP();
		ij=0;
		for(i=0;i<*ORDER_PSIP+1  ;i++)
		for(j=0;j<*ORDER_PSIP+1-i;j++){
			IABP[0]=CCD[(*NUM_CCD)].CD[0][0]*CCD[CID].PSIP[0][ij]+CCD[(*NUM_CCD)].CD[0][1]*CCD[CID].PSIP[1][ij];
			IABP[1]=CCD[(*NUM_CCD)].CD[1][0]*CCD[CID].PSIP[0][ij]+CCD[(*NUM_CCD)].CD[1][1]*CCD[CID].PSIP[1][ij];
			CCD[CID].PSIP[0][ij]=CCD[CID].InvCD[0][0]*IABP[0]+CCD[CID].InvCD[0][1]*IABP[1];
			CCD[CID].PSIP[1][ij]=CCD[CID].InvCD[1][0]*IABP[0]+CCD[CID].InvCD[1][1]*IABP[1];
			ij++;
		}
		CCD[CID].SET_CDPSIP();

		CCD[CID].SET_SIPROT(*ORDER_PSIP-1,CCD[(*NUM_CCD)].PSIP_CONV    ,CCD[CID].PSIP_CONV    );
		CCD[CID].SET_SIPROT(*ORDER_PSIP-1,CCD[(*NUM_CCD)].PSIP_ROT     ,CCD[CID].PSIP_ROT     );
		CCD[CID].SET_SIPROT(*ORDER_PSIP-1,CCD[(*NUM_CCD)].PSIP_SHEAR[0],CCD[CID].PSIP_SHEAR[0]);
		CCD[CID].SET_SIPROT(*ORDER_PSIP-1,CCD[(*NUM_CCD)].PSIP_SHEAR[1],CCD[CID].PSIP_SHEAR[1]);
		CCD[CID].SET_SIPROT(*ORDER_PSIP-1,CCD[(*NUM_CCD)].PSIP_MAG     ,CCD[CID].PSIP_MAG     );
		CCD[CID].SET_SIPROT(*ORDER_PSIP-1,CCD[(*NUM_CCD)].PSIP_JACO    ,CCD[CID].PSIP_JACO    );
	}
	
	CPP_MEMORY_DELdouble1((*ORDER_ASIP+1)*(*ORDER_ASIP+2),G_ASIP[0]);
	CPP_MEMORY_DELdouble1((*ORDER_ASIP+1)*(*ORDER_ASIP+2),G_ASIP[1]);
	CPP_MEMORY_DELdouble1((*ORDER_PSIP+1)*(*ORDER_PSIP+2),G_PSIP[0]);
	CPP_MEMORY_DELdouble1((*ORDER_PSIP+1)*(*ORDER_PSIP+2),G_PSIP[1]);
}
void CL_CCDs::SHOW(){
	int i;

	cout << "-- SHOW CCDs --" << endl;
	cout << "NUM_CCD             : " << *NUM_CCD        << endl;
	cout << "BASISPOSX   (Center): " ;cout.width(10);cout<< GPOS_C_BASIS[0]<< endl;
	cout << "BASISPOSY   (Center): " ;cout.width(10);cout<< GPOS_C_BASIS[1]<< endl;
	cout << "BASISPOSTrad(Center): " ;cout.width(10);cout<< GPOS_C_BASIS[2]<< endl;
	cout << "BASISPOSTdeg(Center): " ;cout.width(10);cout<< GPOS_C_BASIS[3]<< endl;
	cout << "MAX_CRPIX_G_R       : " ;cout.width(10);cout<< MAX_CRPIX_G_R    << endl;
	cout << "MAX_CRPIX_G_X       : " ;cout.width(10);cout<< MAX_CRPIX_G[0]   << endl;
	cout << "MAX_CRPIX_G_Y       : " ;cout.width(10);cout<< MAX_CRPIX_G[1]   << endl;
	cout << "MIN_CRPIX_G_X       : " ;cout.width(10);cout<< MIN_CRPIX_G[0]   << endl;
	cout << "MIN_CRPIX_G_Y       : " ;cout.width(10);cout<< MIN_CRPIX_G[1]   << endl;
	cout << "AVE_CRPIX_G_X       : " ;cout.width(10);cout<< AVE_CRPIX_G[0]   << endl;
	cout << "AVE_CRPIX_G_Y       : " ;cout.width(10);cout<< AVE_CRPIX_G[1]   << endl;
	cout << "-- SHOW CCD --" << endl;
	cout << " ID :        X_C        Y_C        T_C       L1       L2 NUM_REF NUM_FIT NUM_REJ" << endl;
	for(i=0;i<*NUM_CCD+1;i++){
		cout.width( 3);
		cout<<CCD[i].ID <<" : ";
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

}
//CCD
void CL_CCD::SET_INIT(){
}
void CL_CCD::SET_END(){
}
void CL_CCD::GET_GPOS_LfromGPOS_C(){
	GPOS_L[0]=GPOS_C[0]-0.5*(LENGTH[0]*cos(GPOS_C[2])-LENGTH[1]*sin(GPOS_C[2]));
	GPOS_L[1]=GPOS_C[1]-0.5*(LENGTH[1]*cos(GPOS_C[2])+LENGTH[0]*sin(GPOS_C[2]));
	GPOS_L[2]=GPOS_C[2];
	GPOS_L[3]=GPOS_C[3];
}
void CL_CCD::GET_GPOS_CfromGPOS_L(){
	GPOS_C[0]=GPOS_L[0]+0.5*(LENGTH[0]*cos(GPOS_L[2])-LENGTH[1]*sin(GPOS_L[2]));
	GPOS_C[1]=GPOS_L[1]+0.5*(LENGTH[1]*cos(GPOS_L[2])+LENGTH[0]*sin(GPOS_L[2]));
	GPOS_C[2]=GPOS_L[2];
	GPOS_C[3]=GPOS_L[3];
}
void CL_CCD::SET_CDASIP(){
	int i;
	double *TSIP[2];
	TSIP[0] = new double[(*ORDER_ASIP+1)*(*ORDER_ASIP+2)];
	TSIP[1] = new double[(*ORDER_ASIP+1)*(*ORDER_ASIP+2)];
	
	CD[0][0]=ASIP[0][1*(*ORDER_ASIP)+1];
	CD[0][1]=ASIP[0][0*(*ORDER_ASIP)+1];
	CD[1][0]=ASIP[1][1*(*ORDER_ASIP)+1];
	CD[1][1]=ASIP[1][0*(*ORDER_ASIP)+1];
	InvCD[0][0]= CD[1][1]/(CD[0][0]*CD[1][1]-CD[0][1]*CD[1][0]);
	InvCD[0][1]=-CD[0][1]/(CD[0][0]*CD[1][1]-CD[0][1]*CD[1][0]);
	InvCD[1][0]=-CD[1][0]/(CD[0][0]*CD[1][1]-CD[0][1]*CD[1][0]);
	InvCD[1][1]= CD[0][0]/(CD[0][0]*CD[1][1]-CD[0][1]*CD[1][0]);
	for(i=0;i<int(0.5*(*ORDER_ASIP+1)*(*ORDER_ASIP+2)+0.1);i++){
		TSIP[0][i]=ASIP[0][i];
		TSIP[1][i]=ASIP[1][i];
		ASIP[0][i]=InvCD[0][0]*TSIP[0][i]+InvCD[0][1]*TSIP[1][i];
		ASIP[1][i]=InvCD[1][0]*TSIP[0][i]+InvCD[1][1]*TSIP[1][i];
	}
	ASIP[0][1*(*ORDER_ASIP)+1]-=1;
	ASIP[1][0*(*ORDER_ASIP)+1]-=1;

        ANGLE=atan2(CD[0][0]-CD[1][1],-CD[1][0]-CD[0][1]);

	delete [] TSIP[0];
	delete [] TSIP[1];
}
void CL_CCD::SET_CDPSIP(){
	PSIP[0][1*(*ORDER_PSIP)+1]-=1;
	PSIP[1][0*(*ORDER_PSIP)+1]-=1;
}
void CL_CCD::SET_SIPROT(int ORDER,double *COEF_IN, double *COEF){
	int i,j,ij;
	double ***Coef;

	double THETA;
	THETA=GPOS_L[2];

	Coef = CPP_MEMORY_NEWdouble3(2,ORDER+1,ORDER+1);
//--------------------------------------------------
	double ABS[10],PHI[10],Z[10][2];

	ij=0;
	for(i=0;i<ORDER+1  ;i++)
	for(j=0;j<ORDER+1-i;j++)
	Coef[0][i][j]=COEF_IN[ij++];

// 0 -----
        if(ORDER > -0.5)
        Coef[1][0][0] =Coef[0][0][0];

// 1 -----
        if(ORDER >  0.5){
            ABS[1]=hypot(Coef[0][0][1],Coef[0][1][0]);
            PHI[1]=atan2(Coef[0][0][1],Coef[0][1][0]);
            Coef[1][1][0]=ABS[1]*cos(PHI[1]-1*THETA);
            Coef[1][0][1]=ABS[1]*sin(PHI[1]-1*THETA);
        }

// 2 -----
        if(ORDER >  1.5){
            Z[2][0]=0.5*(Coef[0][2][0]-Coef[0][0][2]);
            Z[2][1]=0.5*(Coef[0][1][1]);
            ABS[0]=0.5*(Coef[0][2][0]+Coef[0][0][2]);
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            Coef[1][2][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA);
            Coef[1][1][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA);
            Coef[1][0][2]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA);
        }

// 3 -----
        if(ORDER >  2.5){
            Z[1][0]=0.25*(3*Coef[0][3][0]+  Coef[0][1][2]);
            Z[1][1]=0.25*(  Coef[0][2][1]+3*Coef[0][0][3]);
            Z[3][0]=0.25*(  Coef[0][3][0]-  Coef[0][1][2]);
            Z[3][1]=0.25*(  Coef[0][2][1]-  Coef[0][0][3]);
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            Coef[1][3][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA);
            Coef[1][2][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA);
            Coef[1][1][2]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA);
            Coef[1][0][3]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA);
        }

// 4 -----
        if(ORDER >  3.5){
            Z[2][0]=  0.5*(Coef[0][4][0]-Coef[0][0][4]);
            Z[2][1]= 0.25*(Coef[0][3][1]+Coef[0][1][3]);
            Z[4][0]=0.125*(Coef[0][4][0]-Coef[0][2][2]+Coef[0][0][4]);
            Z[4][1]=0.125*(Coef[0][3][1]-Coef[0][1][3]);
            ABS[0]=0.125*(3*Coef[0][4][0]+Coef[0][2][2]+3*Coef[0][0][4]);
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            Coef[1][4][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA);
            Coef[1][3][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+4*ABS[4]*sin(PHI[4]-4*THETA);
            Coef[1][2][2]=2*ABS[0]+0*ABS[2]*cos(PHI[2]-2*THETA)-6*ABS[4]*cos(PHI[4]-4*THETA);
            Coef[1][1][3]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)-4*ABS[4]*sin(PHI[4]-4*THETA);
            Coef[1][0][4]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA);
        }

// 5 -----
        if(ORDER >  4.5){
            Z[1][0]=(5*Coef[0][5][0]+  Coef[0][3][2]+  Coef[0][1][4])/16.0*2.0;
            Z[1][1]=(  Coef[0][4][1]+  Coef[0][2][3]+5*Coef[0][0][5])/16.0*2.0;
            Z[3][0]=(5*Coef[0][5][0]-  Coef[0][3][2]-3*Coef[0][1][4])/16.0;
            Z[3][1]=(3*Coef[0][4][1]+  Coef[0][2][3]-5*Coef[0][0][5])/16.0;
            Z[5][0]=(  Coef[0][5][0]-  Coef[0][3][2]+  Coef[0][1][4])/16.0;
            Z[5][1]=(  Coef[0][4][1]-  Coef[0][2][3]+  Coef[0][0][5])/16.0;
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            ABS[5]=hypot(Z[5][1],Z[5][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            PHI[5]=atan2(Z[5][1],Z[5][0]);
            Coef[1][5][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA);
            Coef[1][4][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA);
            Coef[1][3][2]=2*ABS[1]*cos(PHI[1]-1*THETA)-2*ABS[3]*cos(PHI[3]-3*THETA)-10*ABS[5]*cos(PHI[5]-5*THETA);
            Coef[1][2][3]=2*ABS[1]*sin(PHI[1]-1*THETA)+2*ABS[3]*sin(PHI[3]-3*THETA)-10*ABS[5]*sin(PHI[5]-5*THETA);
            Coef[1][1][4]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA);
            Coef[1][0][5]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA);
        }

// 6 -----
        if(ORDER >  5.5){
            Z[2][0]=(15*Coef[0][6][0]+  Coef[0][4][2]-  Coef[0][2][4]-15*Coef[0][0][6])/32.0;
            Z[2][1]=( 5*Coef[0][5][1]+3*Coef[0][3][3]+5*Coef[0][1][5])/32.0;
            Z[4][0]=( 3*Coef[0][6][0]-  Coef[0][4][2]-  Coef[0][2][4]+ 3*Coef[0][0][6])/32.0*2.0;
            Z[4][1]=( 4*Coef[0][5][1]+0*Coef[0][3][3]-4*Coef[0][1][5])/32.0;
            Z[6][0]=( 1*Coef[0][6][0]-  Coef[0][4][2]+  Coef[0][2][4]-   Coef[0][0][6])/32.0;
            Z[6][1]=( 1*Coef[0][5][1]-1*Coef[0][3][3]+1*Coef[0][1][5])/32.0;
            ABS[0]= ( 5*Coef[0][6][0]+  Coef[0][4][2]+  Coef[0][2][4]+ 5*Coef[0][0][6])/32.0*2.0;
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            ABS[6]=hypot(Z[6][1],Z[6][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            PHI[6]=atan2(Z[6][1],Z[6][0]);
            Coef[1][6][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA)+ 1*ABS[6]*cos(PHI[6]-6*THETA);
            Coef[1][5][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA);
            Coef[1][4][2]=3*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)-5*ABS[4]*cos(PHI[4]-4*THETA)-15*ABS[6]*cos(PHI[6]-6*THETA);
            Coef[1][3][3]=0*ABS[0]+4*ABS[2]*sin(PHI[2]-2*THETA)+0*ABS[4]*sin(PHI[4]-4*THETA)-20*ABS[6]*sin(PHI[6]-6*THETA);
            Coef[1][2][4]=3*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)-5*ABS[4]*cos(PHI[4]-4*THETA)+15*ABS[6]*cos(PHI[6]-6*THETA);
            Coef[1][1][5]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)-4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA);
            Coef[1][0][6]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+1*ABS[4]*cos(PHI[4]-4*THETA)- 1*ABS[6]*cos(PHI[6]-6*THETA);
        }

// 7 -----
        if(ORDER >  6.5){
            Z[1][0]=(35*Coef[0][7][0]+5*Coef[0][5][2]+3*Coef[0][3][4]+ 5*Coef[0][1][6])/64.0;
            Z[1][1]=( 5*Coef[0][6][1]+3*Coef[0][4][3]+5*Coef[0][2][5]+35*Coef[0][0][7])/64.0;
            Z[3][0]=(21*Coef[0][7][0]-1*Coef[0][5][2]-3*Coef[0][3][4]- 9*Coef[0][1][6])/64.0;
            Z[3][1]=( 9*Coef[0][6][1]+3*Coef[0][4][3]+1*Coef[0][2][5]-21*Coef[0][0][7])/64.0;
            Z[5][0]=( 7*Coef[0][7][0]-3*Coef[0][5][2]-1*Coef[0][3][4]+ 5*Coef[0][1][6])/64.0;
            Z[5][1]=( 5*Coef[0][6][1]-1*Coef[0][4][3]-3*Coef[0][2][5]+ 7*Coef[0][0][7])/64.0;
            Z[7][0]=( 1*Coef[0][7][0]-1*Coef[0][5][2]+1*Coef[0][3][4]- 1*Coef[0][1][6])/64.0;
            Z[7][1]=( 1*Coef[0][6][1]-1*Coef[0][4][3]+1*Coef[0][2][5]- 1*Coef[0][0][7])/64.0;
            ABS[1]=hypot(Z[1][1],Z[1][0]);
            ABS[3]=hypot(Z[3][1],Z[3][0]);
            ABS[5]=hypot(Z[5][1],Z[5][0]);
            ABS[7]=hypot(Z[7][1],Z[7][0]);
            PHI[1]=atan2(Z[1][1],Z[1][0]);
            PHI[3]=atan2(Z[3][1],Z[3][0]);
            PHI[5]=atan2(Z[5][1],Z[5][0]);
            PHI[7]=atan2(Z[7][1],Z[7][0]);
            Coef[1][7][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA)+ 1*ABS[7]*cos(PHI[7]-7*THETA);
            Coef[1][6][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA)+ 7*ABS[7]*sin(PHI[7]-7*THETA);
            Coef[1][5][2]=3*ABS[1]*cos(PHI[1]-1*THETA)-1*ABS[3]*cos(PHI[3]-3*THETA)- 9*ABS[5]*cos(PHI[5]-5*THETA)-21*ABS[7]*cos(PHI[7]-7*THETA);
            Coef[1][4][3]=3*ABS[1]*sin(PHI[1]-1*THETA)+5*ABS[3]*sin(PHI[3]-3*THETA)- 5*ABS[5]*sin(PHI[5]-5*THETA)-35*ABS[7]*sin(PHI[7]-7*THETA);
            Coef[1][3][4]=3*ABS[1]*cos(PHI[1]-1*THETA)-5*ABS[3]*cos(PHI[3]-3*THETA)- 5*ABS[5]*cos(PHI[5]-5*THETA)+35*ABS[7]*cos(PHI[7]-7*THETA);
            Coef[1][2][5]=3*ABS[1]*sin(PHI[1]-1*THETA)+1*ABS[3]*sin(PHI[3]-3*THETA)- 9*ABS[5]*sin(PHI[5]-5*THETA)+21*ABS[7]*sin(PHI[7]-7*THETA);
            Coef[1][1][6]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA)- 7*ABS[7]*cos(PHI[7]-7*THETA);
            Coef[1][0][7]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA)- 1*ABS[7]*sin(PHI[7]-7*THETA);
        }

// 8 -----
        if(ORDER >  7.5){
            Z[2][0]=(56*Coef[0][8][0]+4*Coef[0][6][2]+0*Coef[0][4][4]- 4*Coef[0][2][6]-56*Coef[0][0][8])/128.0;
            Z[2][1]=(14*Coef[0][7][1]+6*Coef[0][5][3]+6*Coef[0][3][5]+14*Coef[0][1][7])/128.0;
            Z[4][0]=(28*Coef[0][8][0]-4*Coef[0][6][2]-4*Coef[0][4][4]- 4*Coef[0][2][6]+28*Coef[0][0][8])/128.0;
            Z[4][1]=(14*Coef[0][7][1]+2*Coef[0][5][3]-2*Coef[0][3][5]-14*Coef[0][1][7])/128.0;
            Z[6][0]=( 8*Coef[0][8][0]-4*Coef[0][6][2]+0*Coef[0][4][4]+ 4*Coef[0][2][6]- 8*Coef[0][0][8])/128.0;
            Z[6][1]=( 6*Coef[0][7][1]-2*Coef[0][5][3]-2*Coef[0][3][5]+ 6*Coef[0][1][7])/128.0;
            Z[8][0]=( 1*Coef[0][8][0]-1*Coef[0][6][2]+1*Coef[0][4][4]- 1*Coef[0][2][6]+ 1*Coef[0][0][8])/128.0;
            Z[8][1]=( 1*Coef[0][7][1]-1*Coef[0][5][3]+1*Coef[0][3][5]- 1*Coef[0][1][7])/128.0;
            ABS[0]= (35*Coef[0][8][0]+5*Coef[0][6][2]+3*Coef[0][4][4]+ 5*Coef[0][2][6]+35*Coef[0][0][8])/128.0;
            ABS[2]=hypot(Z[2][1],Z[2][0]);
            ABS[4]=hypot(Z[4][1],Z[4][0]);
            ABS[6]=hypot(Z[6][1],Z[6][0]);
            ABS[8]=hypot(Z[8][1],Z[8][0]);
            PHI[2]=atan2(Z[2][1],Z[2][0]);
            PHI[4]=atan2(Z[4][1],Z[4][0]);
            PHI[6]=atan2(Z[6][1],Z[6][0]);
            PHI[8]=atan2(Z[8][1],Z[8][0]);
            Coef[1][8][0]=1*ABS[0]+1*ABS[2]*cos(PHI[2]-2*THETA)+ 1*ABS[4]*cos(PHI[4]-4*THETA)+ 1*ABS[6]*cos(PHI[6]-6*THETA)+ 1*ABS[8]*cos(PHI[8]-8*THETA);
            Coef[1][7][1]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)+ 4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA)+ 8*ABS[8]*sin(PHI[8]-8*THETA);
            Coef[1][6][2]=4*ABS[0]+2*ABS[2]*cos(PHI[2]-2*THETA)- 4*ABS[4]*cos(PHI[4]-4*THETA)-14*ABS[6]*cos(PHI[6]-6*THETA)-28*ABS[8]*cos(PHI[8]-8*THETA);
            Coef[1][5][3]=0*ABS[0]+6*ABS[2]*sin(PHI[2]-2*THETA)+ 4*ABS[4]*sin(PHI[4]-4*THETA)-14*ABS[6]*sin(PHI[6]-6*THETA)-56*ABS[8]*sin(PHI[8]-8*THETA);
            Coef[1][4][4]=6*ABS[0]+0*ABS[2]*cos(PHI[2]-2*THETA)-10*ABS[4]*cos(PHI[4]-4*THETA)+ 0*ABS[6]*cos(PHI[6]-6*THETA)+70*ABS[8]*cos(PHI[8]-8*THETA);
            Coef[1][3][5]=0*ABS[0]+6*ABS[2]*sin(PHI[2]-2*THETA)- 4*ABS[4]*sin(PHI[4]-4*THETA)-14*ABS[6]*sin(PHI[6]-6*THETA)+56*ABS[8]*sin(PHI[8]-8*THETA);
            Coef[1][2][6]=4*ABS[0]-2*ABS[2]*cos(PHI[2]-2*THETA)- 4*ABS[4]*cos(PHI[4]-4*THETA)+14*ABS[6]*cos(PHI[6]-6*THETA)-28*ABS[8]*cos(PHI[8]-8*THETA);
            Coef[1][1][7]=0*ABS[0]+2*ABS[2]*sin(PHI[2]-2*THETA)- 4*ABS[4]*sin(PHI[4]-4*THETA)+ 6*ABS[6]*sin(PHI[6]-6*THETA)- 8*ABS[8]*sin(PHI[8]-8*THETA);
            Coef[1][0][8]=1*ABS[0]-1*ABS[2]*cos(PHI[2]-2*THETA)+ 1*ABS[4]*cos(PHI[4]-4*THETA)- 1*ABS[6]*cos(PHI[6]-6*THETA)+ 1*ABS[8]*cos(PHI[8]-8*THETA);
        }

// 9 -----
        if(ORDER >  8.5){
            Z[1][0]=(126*Coef[0][9][0]+14*Coef[0][7][2]+6*Coef[0][5][4]+ 6*Coef[0][3][6]+ 14*Coef[0][1][8])/256.0;
            Z[1][1]=( 14*Coef[0][8][1]+ 6*Coef[0][6][3]+6*Coef[0][4][5]+14*Coef[0][2][7]+126*Coef[0][0][9])/256.0;
            Z[3][0]=( 84*Coef[0][9][0]+ 0*Coef[0][7][2]-4*Coef[0][5][4]- 8*Coef[0][3][6]- 28*Coef[0][1][8])/256.0;
            Z[3][1]=( 28*Coef[0][8][1]+ 8*Coef[0][6][3]+4*Coef[0][4][5]+ 0*Coef[0][2][7]- 84*Coef[0][0][9])/256.0;
            Z[5][0]=( 36*Coef[0][9][0]- 8*Coef[0][7][2]-4*Coef[0][5][4]+ 0*Coef[0][3][6]+ 20*Coef[0][1][8])/256.0;
            Z[5][1]=( 20*Coef[0][8][1]- 0*Coef[0][6][3]-4*Coef[0][4][5]- 8*Coef[0][2][7]+ 36*Coef[0][0][9])/256.0;
            Z[7][0]=(  9*Coef[0][9][0]- 5*Coef[0][7][2]+1*Coef[0][5][4]+ 3*Coef[0][3][6]-  7*Coef[0][1][8])/256.0;
            Z[7][1]=(  7*Coef[0][8][1]- 3*Coef[0][6][3]-1*Coef[0][4][5]+ 5*Coef[0][2][7]-  9*Coef[0][0][9])/256.0;
            Z[9][0]=(  1*Coef[0][9][0]- 1*Coef[0][7][2]+1*Coef[0][5][4]- 1*Coef[0][3][6]+  1*Coef[0][1][8])/256.0;
            Z[9][1]=(  1*Coef[0][8][1]- 1*Coef[0][6][3]+1*Coef[0][4][5]- 1*Coef[0][2][7]+  1*Coef[0][0][9])/256.0;
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
            Coef[1][9][0]=1*ABS[1]*cos(PHI[1]-1*THETA)+1*ABS[3]*cos(PHI[3]-3*THETA)+ 1*ABS[5]*cos(PHI[5]-5*THETA)+ 1*ABS[7]*cos(PHI[7]-7*THETA)+  1*ABS[9]*cos(PHI[9]-9*THETA);
            Coef[1][8][1]=1*ABS[1]*sin(PHI[1]-1*THETA)+3*ABS[3]*sin(PHI[3]-3*THETA)+ 5*ABS[5]*sin(PHI[5]-5*THETA)+ 7*ABS[7]*sin(PHI[7]-7*THETA)+  9*ABS[9]*sin(PHI[9]-9*THETA);
            Coef[1][7][2]=4*ABS[1]*cos(PHI[1]-1*THETA)+0*ABS[3]*cos(PHI[3]-3*THETA)- 8*ABS[5]*cos(PHI[5]-5*THETA)-20*ABS[7]*cos(PHI[7]-7*THETA)- 36*ABS[9]*cos(PHI[9]-9*THETA);
            Coef[1][6][3]=4*ABS[1]*sin(PHI[1]-1*THETA)+8*ABS[3]*sin(PHI[3]-3*THETA)+ 0*ABS[5]*sin(PHI[5]-5*THETA)-28*ABS[7]*sin(PHI[7]-7*THETA)- 84*ABS[9]*sin(PHI[9]-9*THETA);
            Coef[1][5][4]=6*ABS[1]*cos(PHI[1]-1*THETA)-6*ABS[3]*cos(PHI[3]-3*THETA)-14*ABS[5]*cos(PHI[5]-5*THETA)+14*ABS[7]*cos(PHI[7]-7*THETA)+126*ABS[9]*cos(PHI[9]-9*THETA);
            Coef[1][4][5]=6*ABS[1]*sin(PHI[1]-1*THETA)+6*ABS[3]*sin(PHI[3]-3*THETA)-14*ABS[5]*sin(PHI[5]-5*THETA)-14*ABS[7]*sin(PHI[7]-7*THETA)+126*ABS[9]*sin(PHI[9]-9*THETA);
            Coef[1][3][6]=4*ABS[1]*cos(PHI[1]-1*THETA)-8*ABS[3]*cos(PHI[3]-3*THETA)+ 0*ABS[5]*cos(PHI[5]-5*THETA)+28*ABS[7]*cos(PHI[7]-7*THETA)- 84*ABS[9]*cos(PHI[9]-9*THETA);
            Coef[1][2][7]=4*ABS[1]*sin(PHI[1]-1*THETA)+0*ABS[3]*sin(PHI[3]-3*THETA)- 8*ABS[5]*sin(PHI[5]-5*THETA)+20*ABS[7]*sin(PHI[7]-7*THETA)- 36*ABS[9]*sin(PHI[9]-9*THETA);
            Coef[1][1][8]=1*ABS[1]*cos(PHI[1]-1*THETA)-3*ABS[3]*cos(PHI[3]-3*THETA)+ 5*ABS[5]*cos(PHI[5]-5*THETA)- 7*ABS[7]*cos(PHI[7]-7*THETA)+  9*ABS[9]*cos(PHI[9]-9*THETA);
            Coef[1][0][9]=1*ABS[1]*sin(PHI[1]-1*THETA)-1*ABS[3]*sin(PHI[3]-3*THETA)+ 1*ABS[5]*sin(PHI[5]-5*THETA)- 1*ABS[7]*sin(PHI[7]-7*THETA)+  1*ABS[9]*sin(PHI[9]-9*THETA);
        }


	ij=0;
	for(i=0;i<ORDER+1  ;i++)
	for(j=0;j<ORDER+1-i;j++){
		COEF[ij]=Coef[1][i][j];
		ij++;
	}
//--------------------------------------------------
	CPP_MEMORY_DELdouble3(2,ORDER+1,ORDER+1,Coef);

}

void CL_CCD::SHOW(){
	cout << setprecision(3);
	cout<<scientific;
	cout << "-- SHOW CCD --" << endl;
	cout << "ID            : " << ID      <<endl;
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
	cout << "CRPIX 1       : " ;cout.width(10);cout<< *CRPIX[0] << endl;
	cout << "CRPIX 2       : " ;cout.width(10);cout<< *CRPIX[1] << endl;
	cout << "CRVAL Ra      : " ;cout.width(10);cout<< *CRVAL[0] <<" (degree) " << endl;
	cout << "CRVAL Dec     : " ;cout.width(10);cout<< *CRVAL[1] <<" (degree) " << endl;
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
	cout << "ORDER  SIP_A  : " << *ORDER_ASIP<< endl;
	int i,j;
	j=int(0.5*(*ORDER_ASIP+1)*(*ORDER_ASIP+2)+0.1);
	for(i=0;i<j;i++){
		cout<< " SIP_A ";cout.width(3);cout<<i<<"    : ";cout.width(10);cout<< ASIP[0][i]<<endl;
	}
	
	cout << "ORDER  SIP_B  : " << *ORDER_ASIP<< endl;
	for(i=0;i<j;i++){
		cout<< " SIP_B ";cout.width(3);cout<<i<<"    : ";cout.width(10);cout<< ASIP[1][i]<<endl;
	}
	cout << "ORDER PSIP_A  : " << *ORDER_PSIP<< endl;
	for(i=0;i<j;i++){
		cout<< "PSIP_A ";cout.width(3);cout<<i<<"    : ";cout.width(10);cout<< PSIP[0][i]<<endl;
	}
	cout << "ORDER PSIP_B  : " << *ORDER_PSIP<< endl;
	for(i=0;i<j;i++){
		cout<< "PSIP_B ";cout.width(3);cout<<i<<"    : ";cout.width(10);cout<< PSIP[1][i]<<endl;
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

