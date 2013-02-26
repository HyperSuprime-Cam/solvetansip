//--------------------------------------------------
//SLVTANSIP_ANA_FIT.cc
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#include<iostream>
#include<cmath>
#include"SLVTANSIP_ANA.h"

#define MAXTLOOP 1
#define MAXXYLOOP 10

using namespace std;
void CL_ANA::MEAS_CCDPOS_T(){
	int i,j,ORDER;

	ORDER=(int)(0.5*(ORDER_LSIP+1)*(ORDER_LSIP+2)+0.5);
	FIT_LOCAL(2,1,7);
	for(CID=0;CID<NUM_CCD;CID++)
	for(i=0;i<2;i++){
		for(j=0;j<ORDER;j++){
		CCD[CID].LCDSIP[i][j]=CCD[CID].LCoef[i][j];
		}
	        F_DIFFSIP(ORDER_LSIP,CCD[CID].LCDSIP[i],CCD[CID].dLCDSIP[i][0],CCD[CID].dLCDSIP[i][1]);
	}
	for(OID=0;OID<NUM_OBJ;OID++){
	        CID=OBJ[OID].ID_CHIP;
		for(i=0;i<2;i++)
		for(j=0;j<2;j++)
	        OBJ[OID].dX_LOCAL_IMWLD_FIT[i][j]=F_CALCVALUE(ORDER_LSIP,CCD[CID].dLCDSIP[i][j],OBJ[OID].X_IMWLD);
	}

//--------------------------------------------------
	int IterNUM_T,TCHECK,FNUM;
	double *Tcheck;
	double ****dGdI;
	dGdI  = F_NEWdouble4(2,2,NUM_OBJ,3);
    
	Tcheck = F_NEWdouble1(NUM_CCD);
	for(IterNUM_T=0;IterNUM_T<MAXTLOOP;IterNUM_T++){
		for(CID=0;CID<NUM_CCD;CID++)
	        Tcheck[CID]=CCD[CID].GPOS[2];

		FNUM=0;
		for(OID=0;OID<NUM_OBJ;OID++){
		        CID=OBJ[OID].ID_CHIP;
		        OBJ[OID].dX_GLOBL_IMWLD[0][0]=OBJ[OID].dX_LOCAL_IMWLD_FIT[0][0]*cos(CCD[CID].GPOS[2])-OBJ[OID].dX_LOCAL_IMWLD_FIT[1][0]*sin(CCD[CID].GPOS[2]);
		        OBJ[OID].dX_GLOBL_IMWLD[1][0]=OBJ[OID].dX_LOCAL_IMWLD_FIT[1][0]*cos(CCD[CID].GPOS[2])+OBJ[OID].dX_LOCAL_IMWLD_FIT[0][0]*sin(CCD[CID].GPOS[2]);
		        OBJ[OID].dX_GLOBL_IMWLD[0][1]=OBJ[OID].dX_LOCAL_IMWLD_FIT[0][1]*cos(CCD[CID].GPOS[2])-OBJ[OID].dX_LOCAL_IMWLD_FIT[1][1]*sin(CCD[CID].GPOS[2]);
		        OBJ[OID].dX_GLOBL_IMWLD[1][1]=OBJ[OID].dX_LOCAL_IMWLD_FIT[1][1]*cos(CCD[CID].GPOS[2])+OBJ[OID].dX_LOCAL_IMWLD_FIT[0][1]*sin(CCD[CID].GPOS[2]);
			if(OBJ[OID].FLAG_OBJ==1){
			for(i=0;i<2;i++)
			for(j=0;j<2;j++){
			        dGdI[i][j][FNUM][0]=OBJ[OID].X_IMWLD[0];
			        dGdI[i][j][FNUM][1]=OBJ[OID].X_IMWLD[1];
			        dGdI[i][j][FNUM][2]=OBJ[OID].dX_GLOBL_IMWLD[i][j];
			}
		        FNUM++;
			}
		}

		#pragma omp parallel num_threads(4)
		#pragma omp sections
		{
		        #pragma omp section
		        {
			        F_LS2(FNUM,ORDER_PSIP-1,dGdI[0][0],CCD[NUM_CCD].dCDPSIP[0][0]);
		        }
		        #pragma omp section
		        {
			        F_LS2(FNUM,ORDER_PSIP-1,dGdI[0][1],CCD[NUM_CCD].dCDPSIP[0][1]);
		        }
		        #pragma omp section
		        {
			        F_LS2(FNUM,ORDER_PSIP-1,dGdI[1][0],CCD[NUM_CCD].dCDPSIP[1][0]);
		        }
		        #pragma omp section
		        {
			        F_LS2(FNUM,ORDER_PSIP-1,dGdI[1][1],CCD[NUM_CCD].dCDPSIP[1][1]);
		        }
		}
		for(OID=0;OID<NUM_OBJ;OID++)
		for(i=0;i<2;i++)
		for(j=0;j<2;j++)
	        OBJ[OID].dX_GLOBL_IMWLD_FIT[i][j]=F_CALCVALUE(ORDER_PSIP-1,CCD[NUM_CCD].dCDPSIP[i][j],OBJ[OID].X_IMWLD);
	
		CCDPOSITIONS_T_MAT();
	
	        TCHECK=0;
	        for(CID=0;CID<NUM_CCD;CID++)
	        if(fabs(Tcheck[CID]-CCD[CID].GPOS[2])>1e-5)
	        TCHECK++;

	        if(TCHECK==0)
	        break;
	}

	double GPOS_AVE[3];
	GPOS_AVE[2]=0;
	int AVENUM=0;
	for(CID=0;CID<NUM_CCD;CID++)
	if(CID<100){
	        GPOS_AVE[2]+=CCD[CID].GPOS[2];
		AVENUM++;
	}
	GPOS_AVE[2]/=AVENUM;

	for(CID=0;CID<NUM_CCD;CID++)
	CCD[CID].GPOS[2]-=GPOS_AVE[2]-GPOS_BASIS[2];

//for(CID=0;CID<NUM_CCD;CID++)
//CCD[CID].GPOS[2]=0;
//for(CID=0;CID<NUM_CCD;CID++)
//cout<<CCD[CID].GPOS[2]<<endl;
//--------------------------------------------------
	F_DELdouble4(2,2,NUM_OBJ,dGdI);
	F_DELdouble1(Tcheck);
}
void CL_ANA::CCDPOSITIONS_T_MAT(){
    int i,j,ij,k,l,kl,dCoefNUM;
    double *MA,**MB,**InvMB,*MC,***XY;

    dCoefNUM=(int)(0.5*(ORDER_PSIP+1-1)*(ORDER_PSIP+2-1)+0.5);

       MA = F_NEWdouble1(NUM_CCD+4*dCoefNUM);
       MB = F_NEWdouble2(NUM_CCD+4*dCoefNUM,NUM_CCD+4*dCoefNUM);
    InvMB = F_NEWdouble2(NUM_CCD+4*dCoefNUM,NUM_CCD+4*dCoefNUM);
       MC = F_NEWdouble1(NUM_CCD+4*dCoefNUM);
       XY = F_NEWdouble3(NUM_OBJ,2*dCoefNUM+1,2*dCoefNUM+1);
//--------------------------------------------------
//XY
    for(OID=0;OID<NUM_OBJ;OID++)
    for(i=0;i<ORDER_PSIP+1-1;i++)
    for(j=0;j<ORDER_PSIP+1-1;j++)
    if(i+j<ORDER_PSIP+1-1)
    XY[OID][i][j] = pow(OBJ[OID].X_IMWLD[0],i)*pow(OBJ[OID].X_IMWLD[1],j);


//--------------------------------------------------
//dA1
    for(OID=0;OID<NUM_OBJ;OID++)
    if(OBJ[OID].FLAG_OBJ==1){
        MA[OBJ[OID].ID_CHIP]-= OBJ[OID].dX_GLOBL_IMWLD[1][0]*OBJ[OID].dX_GLOBL_IMWLD_FIT[0][0];
        MA[OBJ[OID].ID_CHIP]-=-OBJ[OID].dX_GLOBL_IMWLD[0][0]*OBJ[OID].dX_GLOBL_IMWLD_FIT[1][0];
        MA[OBJ[OID].ID_CHIP]-= OBJ[OID].dX_GLOBL_IMWLD[1][1]*OBJ[OID].dX_GLOBL_IMWLD_FIT[0][1];
        MA[OBJ[OID].ID_CHIP]-=-OBJ[OID].dX_GLOBL_IMWLD[0][1]*OBJ[OID].dX_GLOBL_IMWLD_FIT[1][1];
    }
//--------------------------------------------------
//dA2
    ij=0;
    for(i=0;i<ORDER_PSIP+1-1;i++)
    for(j=0;j<ORDER_PSIP+1-1;j++)
    if(i+j<ORDER_PSIP+1-1){
        for(OID=0;OID<NUM_OBJ;OID++)
        if(OBJ[OID].FLAG_OBJ==1){
            MA[NUM_CCD+0*dCoefNUM+ij]+=(OBJ[OID].dX_GLOBL_IMWLD[0][0]-OBJ[OID].dX_GLOBL_IMWLD_FIT[0][0])*XY[OID][i][j];
            MA[NUM_CCD+1*dCoefNUM+ij]+=(OBJ[OID].dX_GLOBL_IMWLD[1][0]-OBJ[OID].dX_GLOBL_IMWLD_FIT[1][0])*XY[OID][i][j];
            MA[NUM_CCD+2*dCoefNUM+ij]+=(OBJ[OID].dX_GLOBL_IMWLD[0][1]-OBJ[OID].dX_GLOBL_IMWLD_FIT[0][1])*XY[OID][i][j];
            MA[NUM_CCD+3*dCoefNUM+ij]+=(OBJ[OID].dX_GLOBL_IMWLD[1][1]-OBJ[OID].dX_GLOBL_IMWLD_FIT[1][1])*XY[OID][i][j];
        }
    ij++;
    }
//--------------------------------------------------
//dB11
    for(OID=0;OID<NUM_OBJ;OID++)
    if(OBJ[OID].FLAG_OBJ==1){
        MB[OBJ[OID].ID_CHIP][OBJ[OID].ID_CHIP]+=OBJ[OID].dX_GLOBL_IMWLD[0][0]*OBJ[OID].dX_GLOBL_IMWLD[0][0];
        MB[OBJ[OID].ID_CHIP][OBJ[OID].ID_CHIP]+=OBJ[OID].dX_GLOBL_IMWLD[1][0]*OBJ[OID].dX_GLOBL_IMWLD[1][0];
        MB[OBJ[OID].ID_CHIP][OBJ[OID].ID_CHIP]+=OBJ[OID].dX_GLOBL_IMWLD[0][1]*OBJ[OID].dX_GLOBL_IMWLD[0][1];
        MB[OBJ[OID].ID_CHIP][OBJ[OID].ID_CHIP]+=OBJ[OID].dX_GLOBL_IMWLD[1][1]*OBJ[OID].dX_GLOBL_IMWLD[1][1];
    }
    
//--------------------------------------------------
//dB12
    ij=0;
    for(i=0;i<ORDER_PSIP+1-1;i++)
    for(j=0;j<ORDER_PSIP+1-1;j++)
    if(i+j<ORDER_PSIP+1-1){
        for(OID=0;OID<NUM_OBJ;OID++)
        if(OBJ[OID].FLAG_OBJ==1){
            MB[OBJ[OID].ID_CHIP][NUM_CCD+0*dCoefNUM+ij]+= OBJ[OID].dX_GLOBL_IMWLD[1][0]*XY[OID][i][j];
            MB[OBJ[OID].ID_CHIP][NUM_CCD+1*dCoefNUM+ij]+=-OBJ[OID].dX_GLOBL_IMWLD[0][0]*XY[OID][i][j];
            MB[OBJ[OID].ID_CHIP][NUM_CCD+2*dCoefNUM+ij]+= OBJ[OID].dX_GLOBL_IMWLD[1][1]*XY[OID][i][j];
            MB[OBJ[OID].ID_CHIP][NUM_CCD+3*dCoefNUM+ij]+=-OBJ[OID].dX_GLOBL_IMWLD[0][1]*XY[OID][i][j];
        }
    ij++;
    }
//--------------------------------------------------
//dB21
    ij=0;
    for(i=0;i<ORDER_PSIP+1-1;i++)
    for(j=0;j<ORDER_PSIP+1-1;j++)
    if(i+j<ORDER_PSIP+1-1){
        for(OID=0;OID<NUM_OBJ;OID++)
        if(OBJ[OID].FLAG_OBJ==1){
            MB[NUM_CCD+0*dCoefNUM+ij][OBJ[OID].ID_CHIP]+= OBJ[OID].dX_GLOBL_IMWLD[1][0]*XY[OID][i][j];
            MB[NUM_CCD+1*dCoefNUM+ij][OBJ[OID].ID_CHIP]+=-OBJ[OID].dX_GLOBL_IMWLD[0][0]*XY[OID][i][j];
            MB[NUM_CCD+2*dCoefNUM+ij][OBJ[OID].ID_CHIP]+= OBJ[OID].dX_GLOBL_IMWLD[1][1]*XY[OID][i][j];
            MB[NUM_CCD+3*dCoefNUM+ij][OBJ[OID].ID_CHIP]+=-OBJ[OID].dX_GLOBL_IMWLD[0][1]*XY[OID][i][j];
        }
    ij++;
    }

//--------------------------------------------------
//dB22
    ij=0;
    for(i=0;i<ORDER_PSIP+1-1;i++)
    for(j=0;j<ORDER_PSIP+1-1;j++)
    if(i+j<ORDER_PSIP+1-1){
    kl=0;
    for(k=0;k<ORDER_PSIP+1-1;k++)
    for(l=0;l<ORDER_PSIP+1-1;l++)
    if(k+l<ORDER_PSIP+1-1){
        for(OID=0;OID<NUM_OBJ;OID++)
        if(OBJ[OID].FLAG_OBJ==1){
            MB[NUM_CCD+0*dCoefNUM+ij][NUM_CCD+0*dCoefNUM+kl]+=pow(OBJ[OID].X_IMWLD[0],i+k)*pow(OBJ[OID].X_IMWLD[1],j+l);
            MB[NUM_CCD+1*dCoefNUM+ij][NUM_CCD+1*dCoefNUM+kl]+=pow(OBJ[OID].X_IMWLD[0],i+k)*pow(OBJ[OID].X_IMWLD[1],j+l);
            MB[NUM_CCD+2*dCoefNUM+ij][NUM_CCD+2*dCoefNUM+kl]+=pow(OBJ[OID].X_IMWLD[0],i+k)*pow(OBJ[OID].X_IMWLD[1],j+l);
            MB[NUM_CCD+3*dCoefNUM+ij][NUM_CCD+3*dCoefNUM+kl]+=pow(OBJ[OID].X_IMWLD[0],i+k)*pow(OBJ[OID].X_IMWLD[1],j+l);
        }
    kl++;
    }
    ij++;
    }

//--------------------------------------------------
    F_InvM(NUM_CCD+4*dCoefNUM,MB,InvMB);

    for(CID =0;CID <NUM_CCD+4*dCoefNUM;CID ++)
    for(CID2=0;CID2<NUM_CCD+4*dCoefNUM;CID2++)
    MC[CID]+=InvMB[CID][CID2]*MA[CID2];

    for(CID=0;CID<NUM_CCD;CID++){
	CCD[CID].GPOS[2]+=MC[CID];
	if(CCD[CID].GPOS[2]> 3.14159265)
	CCD[CID].GPOS[2]-= 2*3.14159265;
	if(CCD[CID].GPOS[2]<-3.14159265)
	CCD[CID].GPOS[2]+= 2*3.14159265;
    }

//--------------------------------------------------
    F_DELdouble1(MA);
    F_DELdouble2(NUM_CCD+4*dCoefNUM,   MB);
    F_DELdouble2(NUM_CCD+4*dCoefNUM,InvMB);
    F_DELdouble1(MC);
    F_DELdouble3(NUM_OBJ,2*dCoefNUM+1,XY);

}
void CL_ANA::MEAS_CCDPOS_XY(){
	int i;

	for(i=0;i<(ORDER_PSIP+1)*(ORDER_PSIP+2);i++)
	CCD[NUM_CCD].CDPSIP[0][i]=CCD[NUM_CCD].CDPSIP[1][i]=0;

	F_INTSIP(ORDER_PSIP,CCD[NUM_CCD].dCDPSIP[0][0],CCD[NUM_CCD].dCDPSIP[0][1],CCD[NUM_CCD].CDPSIP[0]);
	F_INTSIP(ORDER_PSIP,CCD[NUM_CCD].dCDPSIP[1][0],CCD[NUM_CCD].dCDPSIP[1][1],CCD[NUM_CCD].CDPSIP[1]);
//--------------------------------------------------
	for(OID=0;OID<NUM_OBJ;OID++){
	        OBJ[OID].X_GLOBL[0]=F_CALCVALUE(ORDER_PSIP,CCD[NUM_CCD].CDPSIP[0],OBJ[OID].X_IMWLD);
	        OBJ[OID].X_GLOBL[1]=F_CALCVALUE(ORDER_PSIP,CCD[NUM_CCD].CDPSIP[1],OBJ[OID].X_IMWLD);
	}
//--------------------------------------------------
	double **dX;
	dX = F_NEWdouble2(NUM_CCD,3);

	for(OID=0;OID<NUM_OBJ;OID++)
	if(OBJ[OID].FLAG_OBJ==1){
		CID=OBJ[OID].ID_CHIP;
	        dX[CID][0]+=1;
	        dX[CID][1]+=OBJ[OID].X_GLOBL[0]-(OBJ[OID].X_LOCAL[0]*cos(CCD[CID].GPOS[2])-OBJ[OID].X_LOCAL[1]*sin(CCD[CID].GPOS[2]));
	        dX[CID][2]+=OBJ[OID].X_GLOBL[1]-(OBJ[OID].X_LOCAL[1]*cos(CCD[CID].GPOS[2])+OBJ[OID].X_LOCAL[0]*sin(CCD[CID].GPOS[2]));
	}

	for(CID=0;CID<NUM_CCD;CID++){
	        CCD[CID].GPOS[0]=dX[CID][1]/dX[CID][0];
	        CCD[CID].GPOS[1]=dX[CID][2]/dX[CID][0];
	}

	double GPOS_AVE[3];
	GPOS_AVE[0]=GPOS_AVE[1]=0;
	int AVENUM=0;
	for(CID=0;CID<NUM_CCD;CID++)
	if(CID<100){
	        GPOS_AVE[0]+=CCD[CID].GPOS[0];
	        GPOS_AVE[1]+=CCD[CID].GPOS[1];
		AVENUM++;
	}
	GPOS_AVE[0]/=AVENUM;
	GPOS_AVE[1]/=AVENUM;

	for(CID=0;CID<NUM_CCD;CID++){
		CCD[CID].GPOS[0]-=GPOS_AVE[0]-GPOS_BASIS[0];
		CCD[CID].GPOS[1]-=GPOS_AVE[1]-GPOS_BASIS[1];
	}

	CALC_X_GLOBL();
}
void CL_ANA::MEAS_CCDPOS_XYT(){
	int i,j,ij,k,l,kl,CID2,NUM,CoefNUM;
       	int AVENUM=0;
	double *MAXYT,**MBXYT,**InvMBXYT,*MCXYT;
	double ***XY,*XLsYLc,*YLsXLc;
	double GPOS_AVE[3],dXYT[3];

	CoefNUM=(int)(0.5*(ORDER_PSIP+1)*(ORDER_PSIP+2)+0.5);

	   MAXYT = F_NEWdouble1(3*NUM_CCD+2*(CoefNUM-1));
	   MBXYT = F_NEWdouble2(3*NUM_CCD+2*(CoefNUM-1),3*NUM_CCD+2*(CoefNUM-1));
	InvMBXYT = F_NEWdouble2(3*NUM_CCD+2*(CoefNUM-1),3*NUM_CCD+2*(CoefNUM-1));
	   MCXYT = F_NEWdouble1(3*NUM_CCD+2*(CoefNUM-1));
	      XY = F_NEWdouble3(NUM_OBJ,ORDER_PSIP+1,ORDER_PSIP+1);
	  XLsYLc = F_NEWdouble1(NUM_OBJ);
	  YLsXLc = F_NEWdouble1(NUM_OBJ);

	int XYLOOP,ENDFLAG;
	double **XYINIT,chi2;
	XYINIT=F_NEWdouble2(NUM_CCD,3);

	for(CID =0;CID <NUM_CCD;CID ++){
	        XYINIT[CID][0]=CCD[CID].GPOS[0];
	        XYINIT[CID][1]=CCD[CID].GPOS[1];
	        XYINIT[CID][2]=CCD[CID].GPOS[2];
	}

	for(XYLOOP=0;XYLOOP<MAXXYLOOP;XYLOOP++){
	        CALC_X_GLOBL();
	
		FIT_GLOBL(1,1,6,CCD[NUM_CCD].CDPSIP);
//--------------------------------------------------
	        for(OID=0;OID<NUM_OBJ;OID++){
	        	OBJ[OID].X_GLOBL_FIT[0]=F_CALCVALUE(ORDER_PSIP,CCD[NUM_CCD].CDPSIP[0],OBJ[OID].X_IMWLD);
	        	OBJ[OID].X_GLOBL_FIT[1]=F_CALCVALUE(ORDER_PSIP,CCD[NUM_CCD].CDPSIP[1],OBJ[OID].X_IMWLD);
	        }
//--------------------------------------------------
//XY
	        for(OID=0;OID<NUM_OBJ;OID++)
	        for(i=0;i<ORDER_PSIP+1;i++)
	        for(j=0;j<ORDER_PSIP+1;j++)
	        if(i+j<ORDER_PSIP+1)
	        XY[OID][i][j] = pow(OBJ[OID].X_IMWLD[0],i)*pow(OBJ[OID].X_IMWLD[1],j);
	
	        for(OID=0;OID<NUM_OBJ;OID++){
			CID=OBJ[OID].ID_CHIP;
	        	XLsYLc[OID]=OBJ[OID].X_LOCAL[0]*sin(CCD[CID].GPOS[2])+OBJ[OID].X_LOCAL[1]*cos(CCD[CID].GPOS[2]);
	        	YLsXLc[OID]=OBJ[OID].X_LOCAL[1]*sin(CCD[CID].GPOS[2])-OBJ[OID].X_LOCAL[0]*cos(CCD[CID].GPOS[2]);
	        }
//--------------------------------------------------
	        for(CID =0;CID <3*NUM_CCD+2*(CoefNUM-1);CID ++){
	        MAXYT[CID]=MCXYT[CID]=0;
	        for(CID2=0;CID2<3*NUM_CCD+2*(CoefNUM-1);CID2++){
	        MBXYT[CID][CID2]=InvMBXYT[CID][CID2]=0;
	        }}
//--------------------------------------------------
//dAXYT
	        for(OID=0;OID<NUM_OBJ;OID++)
	        if(OBJ[OID].FLAG_OBJ==1){
			CID=OBJ[OID].ID_CHIP;
	        	MAXYT[0*NUM_CCD+CID]-=(OBJ[OID].X_GLOBL[0]-OBJ[OID].X_GLOBL_FIT[0]);
	        	MAXYT[1*NUM_CCD+CID]-=(OBJ[OID].X_GLOBL[1]-OBJ[OID].X_GLOBL_FIT[1]);
	        	MAXYT[2*NUM_CCD+CID]-=-XLsYLc[OID]*(OBJ[OID].X_GLOBL[0]-OBJ[OID].X_GLOBL_FIT[0])-YLsXLc[OID]*(OBJ[OID].X_GLOBL[1]-OBJ[OID].X_GLOBL_FIT[1]);
	        }
//--------------------------------------------------
//dAA
	        ij=0;
	        for(i=0;i<ORDER_PSIP+1;i++)
	        for(j=0;j<ORDER_PSIP+1;j++)
	        if(i+j<ORDER_PSIP+1&&i+j!=0){
		        for(OID=0;OID<NUM_OBJ;OID++)
	        	if(OBJ[OID].FLAG_OBJ==1){
	        	MAXYT[3*NUM_CCD+0*(CoefNUM-1)+ij]-=-(OBJ[OID].X_GLOBL[0]-OBJ[OID].X_GLOBL_FIT[0])*XY[OID][i][j];
	        	MAXYT[3*NUM_CCD+1*(CoefNUM-1)+ij]-=-(OBJ[OID].X_GLOBL[1]-OBJ[OID].X_GLOBL_FIT[1])*XY[OID][i][j];
	        	}
	        ij++;
	        }
//--------------------------------------------------
//dBXYTXYT
        	for(OID=0;OID<NUM_OBJ;OID++)
        	if(OBJ[OID].FLAG_OBJ==1&&i+j!=0){
			CID=OBJ[OID].ID_CHIP;
        		MBXYT[0*NUM_CCD+CID][0*NUM_CCD+CID]+=1;
//      		MBXYT[0*NUM_CCD+CID][1*NUM_CCD+CID]+=0;
        		MBXYT[0*NUM_CCD+CID][2*NUM_CCD+CID]+=-XLsYLc[OID];
//      		MBXYT[1*NUM_CCD+CID][0*NUM_CCD+CID]+=0;
        		MBXYT[1*NUM_CCD+CID][1*NUM_CCD+CID]+=1;
        		MBXYT[1*NUM_CCD+CID][2*NUM_CCD+CID]+=-YLsXLc[OID];
        		MBXYT[2*NUM_CCD+CID][0*NUM_CCD+CID]+=-XLsYLc[OID];
        		MBXYT[2*NUM_CCD+CID][1*NUM_CCD+CID]+=-YLsXLc[OID];
        		MBXYT[2*NUM_CCD+CID][2*NUM_CCD+CID]+= XLsYLc[OID]*XLsYLc[OID]+YLsXLc[OID]*YLsXLc[OID];
        	}
    
//--------------------------------------------------
//dBXYTA
        	ij=0;
        	for(i=0;i<ORDER_PSIP+1;i++)
        	for(j=0;j<ORDER_PSIP+1;j++)
        	if(i+j<ORDER_PSIP+1&&i+j!=0){
		        for(OID=0;OID<NUM_OBJ;OID++)
		        if(OBJ[OID].FLAG_OBJ==1){
				CID=OBJ[OID].ID_CHIP;
		                MBXYT[0*NUM_CCD+CID][3*NUM_CCD+0*(CoefNUM-1)+ij]+=-XY[OID][i][j];
		                MBXYT[1*NUM_CCD+CID][3*NUM_CCD+1*(CoefNUM-1)+ij]+=-XY[OID][i][j];
		                MBXYT[2*NUM_CCD+CID][3*NUM_CCD+0*(CoefNUM-1)+ij]+=-XY[OID][i][j]*(-XLsYLc[OID]);
		                MBXYT[2*NUM_CCD+CID][3*NUM_CCD+1*(CoefNUM-1)+ij]+=-XY[OID][i][j]*(-YLsXLc[OID]);
		        }
		        ij++;
        	}
//--------------------------------------------------
//dBAXYT
        	ij=0;
        	for(i=0;i<ORDER_PSIP+1;i++)
        	for(j=0;j<ORDER_PSIP+1;j++)
        	if(i+j<ORDER_PSIP+1&&i+j!=0){
		        for(OID=0;OID<NUM_OBJ;OID++)
		        if(OBJ[OID].FLAG_OBJ==1){
				CID=OBJ[OID].ID_CHIP;
		                MBXYT[3*NUM_CCD+0*(CoefNUM-1)+ij][0*NUM_CCD+CID]+=-XY[OID][i][j];
		                MBXYT[3*NUM_CCD+1*(CoefNUM-1)+ij][1*NUM_CCD+CID]+=-XY[OID][i][j];
		                MBXYT[3*NUM_CCD+0*(CoefNUM-1)+ij][2*NUM_CCD+CID]+=-XY[OID][i][j]*(-XLsYLc[OID]);
		                MBXYT[3*NUM_CCD+1*(CoefNUM-1)+ij][2*NUM_CCD+CID]+=-XY[OID][i][j]*(-YLsXLc[OID]);
		        }
		        ij++;
        	}
//--------------------------------------------------
//dBAA
        	ij=0;
        	for(i=0;i<ORDER_PSIP+1;i++)
        	for(j=0;j<ORDER_PSIP+1;j++)
        	if(i+j<ORDER_PSIP+1&&i+j!=0){
        	kl=0;
        	for(k=0;k<ORDER_PSIP+1;k++)
        	for(l=0;l<ORDER_PSIP+1;l++)
        	if(k+l<ORDER_PSIP+1&&k+l!=0){
		        for(OID=0;OID<NUM_OBJ;OID++)
		        if(OBJ[OID].FLAG_OBJ==1){
		                MBXYT[3*NUM_CCD+0*(CoefNUM-1)+ij][3*NUM_CCD+0*(CoefNUM-1)+kl]+=pow(OBJ[OID].X_IMWLD[0],i+k)*pow(OBJ[OID].X_IMWLD[1],j+l);
//		                MBXYT[3*NUM_CCD+0*(CoefNUM-1)+ij][3*NUM_CCD+1*(CoefNUM-1)+kl]+=0;
//      		        MBXYT[3*NUM_CCD+1*(CoefNUM-1)+ij][3*NUM_CCD+0*(CoefNUM-1)+kl]+=0;
        		        MBXYT[3*NUM_CCD+1*(CoefNUM-1)+ij][3*NUM_CCD+1*(CoefNUM-1)+kl]+=pow(OBJ[OID].X_IMWLD[0],i+k)*pow(OBJ[OID].X_IMWLD[1],j+l);
        		}
        		kl++;
        	}
        	ij++;
        	}
//--------------------------------------------------
        	F_InvM(3*NUM_CCD+2*(CoefNUM-1),MBXYT,InvMBXYT);

        	for(CID =0;CID <3*NUM_CCD+2*(CoefNUM-1);CID ++)
        	for(CID2=0;CID2<3*NUM_CCD+2*(CoefNUM-1);CID2++)
        	MCXYT[CID]+=InvMBXYT[CID][CID2]*MAXYT[CID2];
	
        	for(CID=0;CID<NUM_CCD;CID++){
        		CCD[CID].GPOS[0]+=MCXYT[0*NUM_CCD+CID];
        		CCD[CID].GPOS[1]+=MCXYT[1*NUM_CCD+CID];
        		CCD[CID].GPOS[2]+=MCXYT[2*NUM_CCD+CID];
			if(CCD[CID].GPOS[2]> 3.14159265)
			CCD[CID].GPOS[2]-= 2*3.14159265;
			if(CCD[CID].GPOS[2]<-3.14159265)
			CCD[CID].GPOS[2]+= 2*3.14159265;
        	}
//--------------------------------------------------
        	GPOS_AVE[2]=0;
        	AVENUM=0;
        	for(CID=0;CID<NUM_CCD;CID++)
        	if(CID<100){
        		GPOS_AVE[2]+=CCD[CID].GPOS[2];
        		AVENUM++;
        	}
        	GPOS_AVE[2]/=AVENUM;

		dXYT[2]=GPOS_AVE[2]-GPOS_BASIS[2];
		for(CID=0;CID<NUM_CCD;CID++){
			CCD[CID].GPOS[2]-=dXYT[2];
			dXYT[0]=CCD[CID].GPOS[0]*cos(-dXYT[2])-CCD[CID].GPOS[1]*sin(-dXYT[2]);
			dXYT[1]=CCD[CID].GPOS[1]*cos(-dXYT[2])+CCD[CID].GPOS[0]*sin(-dXYT[2]);
			CCD[CID].GPOS[0]=dXYT[0];
			CCD[CID].GPOS[1]=dXYT[1];			
		}
//--------------------------------------------------

        	GPOS_AVE[0]=GPOS_AVE[1]=0;
        	AVENUM=0;
        	for(CID=0;CID<NUM_CCD;CID++)
        	if(CID<100){
        		GPOS_AVE[0]+=CCD[CID].GPOS[0];
        		GPOS_AVE[1]+=CCD[CID].GPOS[1];
        		AVENUM++;
        	}
        	GPOS_AVE[0]/=AVENUM;
        	GPOS_AVE[1]/=AVENUM;

		dXYT[0]=GPOS_AVE[0]-GPOS_BASIS[0];
		dXYT[1]=GPOS_AVE[1]-GPOS_BASIS[1];
		for(CID=0;CID<NUM_CCD;CID++){
			CCD[CID].GPOS[0]-=dXYT[0];
			CCD[CID].GPOS[1]-=dXYT[1];
		}

//--------------------------------------------------
	        ENDFLAG=1;
	        for(CID =0;CID <NUM_CCD;CID ++)
	        if(hypot(XYINIT[CID][0]-CCD[CID].GPOS[0],XYINIT[CID][1]-CCD[CID].GPOS[1])>pow(10.0,-2.0)||fabs(XYINIT[CID][2]-CCD[CID].GPOS[2])>pow(10.0,-5.0))
	        ENDFLAG=0;

	        if(ENDFLAG==1){
	        	break;
	        }else{
	        	if(STDOUT==2)cout << "XYLOOP = " << XYLOOP+1 << endl;
	        	for(CID =0;CID <NUM_CCD;CID ++){
	        	        XYINIT[CID][0]=CCD[CID].GPOS[0];
	        	        XYINIT[CID][1]=CCD[CID].GPOS[1];
	        	        XYINIT[CID][2]=CCD[CID].GPOS[2];
	        	}
	        }
	}

	F_DELdouble1(MAXYT);
	F_DELdouble2(3*NUM_CCD+2*(CoefNUM-1),MBXYT);
	F_DELdouble2(3*NUM_CCD+2*(CoefNUM-1),InvMBXYT);
	F_DELdouble1(MCXYT);
	F_DELdouble3(NUM_OBJ,ORDER_PSIP+1,XY);
	F_DELdouble2(NUM_CCD,XYINIT);
	F_DELdouble1(XLsYLc);
	F_DELdouble1(YLsXLc);
}
void CL_ANA::ROT_CRCDSIP(){
	int i,j,ij;
	double IABP[2],detCD;

	CCD[NUM_CCD].PSIP[0][1*(ORDER_PSIP+1)+0]+=1.0;
	CCD[NUM_CCD].PSIP[1][0*(ORDER_PSIP+1)+1]+=1.0;
	for(CID=0;CID<NUM_CCD;CID++){
	        F_SIPROT(ORDER_ASIP,CCD[CID].GPOS[2],CCD[NUM_CCD].CDASIP[0],CCD[CID].CDASIP[0]);
	        F_SIPROT(ORDER_ASIP,CCD[CID].GPOS[2],CCD[NUM_CCD].CDASIP[1],CCD[CID].CDASIP[1]);
	        F_SIPROT(ORDER_PSIP,CCD[CID].GPOS[2],CCD[NUM_CCD].PSIP[0]  ,CCD[CID].PSIP[0]  );
	        F_SIPROT(ORDER_PSIP,CCD[CID].GPOS[2],CCD[NUM_CCD].PSIP[1]  ,CCD[CID].PSIP[1]  );

	        CCD[CID].CD[0][0]=CCD[CID].CDASIP[0][1*(ORDER_PSIP+1)+0];
	        CCD[CID].CD[0][1]=CCD[CID].CDASIP[0][0*(ORDER_PSIP+1)+1];
	        CCD[CID].CD[1][0]=CCD[CID].CDASIP[1][1*(ORDER_PSIP+1)+0];
	        CCD[CID].CD[1][1]=CCD[CID].CDASIP[1][0*(ORDER_PSIP+1)+1]; 
	        CCD[CID].ANGLE=atan2(CCD[CID].CD[1][0]-(-1)*CCD[CID].CD[0][1],(-1)*CCD[CID].CD[0][0]+CCD[CID].CD[1][1]);

		detCD=CCD[CID].CD[0][0]*CCD[CID].CD[1][1]-CCD[CID].CD[1][0]*CCD[CID].CD[0][1];
	        CCD[CID].InvCD[0][0]= CCD[CID].CD[1][1]/detCD;
	        CCD[CID].InvCD[0][1]=-CCD[CID].CD[0][1]/detCD;
	        CCD[CID].InvCD[1][0]=-CCD[CID].CD[1][0]/detCD;
	        CCD[CID].InvCD[1][1]= CCD[CID].CD[0][0]/detCD;

	        ij=0;
	        for(i=0;i<ORDER_ASIP+1;i++)
	        for(j=0;j<ORDER_ASIP+1;j++)
	        if(i+j<ORDER_ASIP+1){
	        	CCD[CID].ASIP[0][ij]=CCD[CID].InvCD[0][0]*CCD[CID].CDASIP[0][ij]+CCD[CID].InvCD[0][1]*CCD[CID].CDASIP[1][ij];
	        	CCD[CID].ASIP[1][ij]=CCD[CID].InvCD[1][0]*CCD[CID].CDASIP[0][ij]+CCD[CID].InvCD[1][1]*CCD[CID].CDASIP[1][ij];
	        	ij++;	
	        }
	        CCD[CID].ASIP[0][1*(ORDER_ASIP+1)+0]-=1.0;
	        CCD[CID].ASIP[1][0*(ORDER_ASIP+1)+1]-=1.0;
	        ij=0;
	        for(i=0;i<ORDER_PSIP+1;i++)
	        for(j=0;j<ORDER_PSIP+1;j++)
	        if(i+j<ORDER_PSIP+1){
		        IABP[0]=CCD[NUM_CCD].CD[0][0]*CCD[CID].PSIP[0][ij]+CCD[NUM_CCD].CD[0][1]*CCD[CID].PSIP[1][ij];
		        IABP[1]=CCD[NUM_CCD].CD[1][0]*CCD[CID].PSIP[0][ij]+CCD[NUM_CCD].CD[1][1]*CCD[CID].PSIP[1][ij];
		        CCD[CID].PSIP[0][ij]=CCD[CID].InvCD[0][0]*IABP[0]+CCD[CID].InvCD[0][1]*IABP[1];
		        CCD[CID].PSIP[1][ij]=CCD[CID].InvCD[1][0]*IABP[0]+CCD[CID].InvCD[1][1]*IABP[1];
		        ij++;
        	}
		CCD[CID].PSIP[0][1*(ORDER_PSIP+1)+0]-=1.0;
		CCD[CID].PSIP[1][0*(ORDER_PSIP+1)+1]-=1.0;

/*
F_SIPROT(ORDER_ASIP,CCD[CID].GPOS[2],CCD[NUM_CCD].ASIP_MAG   ,CCD[CID].ASIP_MAG   );
F_SIPROT(ORDER_ASIP,CCD[CID].GPOS[2],CCD[NUM_CCD].ASIP_CRS[0],CCD[CID].ASIP_CRS[0]);
F_SIPROT(ORDER_ASIP,CCD[CID].GPOS[2],CCD[NUM_CCD].ASIP_CRS[1],CCD[CID].ASIP_CRS[1]);
F_SIPROT(ORDER_ASIP,CCD[CID].GPOS[2],CCD[NUM_CCD].ASIP_CRS[2],CCD[CID].ASIP_CRS[2]);
F_SIPROT(ORDER_ASIP,CCD[CID].GPOS[2],CCD[NUM_CCD].ASIP_CRS[3],CCD[CID].ASIP_CRS[3]);
F_SIPROT(ORDER_PSIP,CCD[CID].GPOS[2],CCD[NUM_CCD].PSIP_MAG   ,CCD[CID].PSIP_MAG   );
F_SIPROT(ORDER_PSIP,CCD[CID].GPOS[2],CCD[NUM_CCD].PSIP_CRS[0],CCD[CID].PSIP_CRS[0]);
F_SIPROT(ORDER_PSIP,CCD[CID].GPOS[2],CCD[NUM_CCD].PSIP_CRS[1],CCD[CID].PSIP_CRS[1]);
F_SIPROT(ORDER_PSIP,CCD[CID].GPOS[2],CCD[NUM_CCD].PSIP_CRS[2],CCD[CID].PSIP_CRS[2]);
F_SIPROT(ORDER_PSIP,CCD[CID].GPOS[2],CCD[NUM_CCD].PSIP_CRS[3],CCD[CID].PSIP_CRS[3]);
*/
//CCD[CID].MAXFRAD =CCD[NUM_CCD].MAXFRAD;
//CCD[CID].MAXDRAD =CCD[NUM_CCD].MAXDRAD;
	        CCD[CID].CRVAL[0]=CCD[NUM_CCD].CRVAL[0];
	        CCD[CID].CRVAL[1]=CCD[NUM_CCD].CRVAL[1];
//		CCD[CID].OAVAL[0]=CCD[NUM_CCD].OAVAL[0];
//		CCD[CID].OAVAL[1]=CCD[NUM_CCD].OAVAL[1];
	        CCD[CID].CRPIX[0]=-(CCD[CID].GPOS[0]-CCD[NUM_CCD].CRPIX[0])*cos(CCD[CID].GPOS[2])-(CCD[CID].GPOS[1]-CCD[NUM_CCD].CRPIX[1])*sin(CCD[CID].GPOS[2]);
	        CCD[CID].CRPIX[1]=-(CCD[CID].GPOS[1]-CCD[NUM_CCD].CRPIX[1])*cos(CCD[CID].GPOS[2])+(CCD[CID].GPOS[0]-CCD[NUM_CCD].CRPIX[0])*sin(CCD[CID].GPOS[2]);
//		CCD[CID].OAPIX[0]=-(CCD[CID].GPOS[0]-CCD[NUM_CCD].OAPIX[0])*cos(CCD[CID].GPOS[2])-(CCD[CID].GPOS[1]-CCD[NUM_CCD].OAPIX[1])*sin(CCD[CID].GPOS[2]);
//		CCD[CID].OAPIX[1]=-(CCD[CID].GPOS[1]-CCD[NUM_CCD].OAPIX[1])*cos(CCD[CID].GPOS[2])+(CCD[CID].GPOS[0]-CCD[NUM_CCD].OAPIX[0])*sin(CCD[CID].GPOS[2]);
	}
	CCD[NUM_CCD].PSIP[0][1*(ORDER_PSIP+1)+0]-=1.0;
	CCD[NUM_CCD].PSIP[1][0*(ORDER_PSIP+1)+1]-=1.0;
}
