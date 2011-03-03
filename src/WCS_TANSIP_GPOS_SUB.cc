//------------------------------------------------------------
//WCS_TANSIP_SUB.cc
//
//Last modification : 2011/02/22
//------------------------------------------------------------
#include<iostream>
#include<cmath>
#include "hsc/meas/tansip/WCS_PL_MAIN.h"
#include "hsc/meas/tansip/WCS_TANSIP.h"

#define PI (4*atan(1.0))
#define INFMIN pow(10,-10)
using namespace std;
void    F_MINT(int ,int ,CL_APROP,CL_CPROP *,CL_PAIR *,double **);
void    F_PROJECTIONPOINT(CL_APROP APROP,CL_CPROP CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
	int i,NUM=0;
	double RA=0,DEC=0;

	cout << endl << "--- F_WCS_TANSIP : GLOBAL POSITION : SET PROJECTIONPOINT ---\n";
	CSIP->CRPIX[0]=0;
	CSIP->CRPIX[1]=0;
	for(i=0;i<APROP.NUMREFALL;i++){
		RA +=PAIR[i].RA;
		DEC+=PAIR[i].DEC;
		NUM+=1;
	}
	CSIP->CRVAL[0]= RA/NUM;
	CSIP->CRVAL[1]=DEC/NUM;

	cout << "PROJECTION POINT : ( " << CSIP->CRPIX[0] << " , " << CSIP->CRPIX[1] << " )(pix) : ( " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1] << " )(deg)\n";
}
void    F_PROJECTION(CL_APROP APROP,CL_CPROP CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i;
    double CR[4],RADEC[4];
	
    cout << endl << "--- F_WCS_TANSIP : GLOBAL POSITION : PROJECTION ---\n";
    CR[0]=CSIP->CRPIX[0];
    CR[1]=CSIP->CRPIX[1];
    CR[2]=CSIP->CRVAL[0];
    CR[3]=CSIP->CRVAL[1];
    CSIP->CD[0][0]=1;
    CSIP->CD[0][1]=0;
    CSIP->CD[1][0]=0;
    CSIP->CD[1][1]=1;
    for(i=0;i<APROP.NUMREFALL;i++){
        RADEC[0]=0;
        RADEC[1]=0;
        RADEC[2]=PAIR[i].RA;
        RADEC[3]=PAIR[i].DEC;
        F_WCSPIX_TAN(RADEC,CR,CSIP->CD);
        PAIR[i].xI=RADEC[0];
        PAIR[i].yI=RADEC[1];
    }
}
void    F_LPFITTING_DIFFPAIR(CL_APROP APROP,CL_CPROP CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,j,ij,CID,NUM;
    double ***dx[3];
    double ***PSIP;
    double **PSIPXY;
    double ***DIFFPSIP[4];

    cout << endl << "--- F_WCS_TANSIP : GLOBAL POSITION : LOCAL ABP SIP FITTING ---\n";

    for(i=0;i<3;i++){
    dx[i] = new double**[APROP.CCDNUM];
    for(CID=0;CID<APROP.CCDNUM;CID++){
    dx[i][CID]=new double*[APROP.NUMREFALL];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    dx[i][CID][NUM]=new double[3];
    for(j=0;j<3;j++)
    dx[i][CID][NUM][j]=0;
    }}}
    
    PSIP=new double**[APROP.CCDNUM];
    for(CID=0;CID<APROP.CCDNUM;CID++){	
    PSIP[CID]=new double*[2];
    for(i=0;i<2;i++){
    PSIP[CID][i] = new double[(APROP.SIP_L_ORDER+1)*(APROP.SIP_L_ORDER+1)];
    for(j=0;j<(APROP.SIP_L_ORDER+1)*(APROP.SIP_L_ORDER+1);j++)
    PSIP[CID][i][j]=0;
    }}

    PSIPXY=new double*[(APROP.SIP_L_ORDER+1)];
    for(i=0;i<(APROP.SIP_L_ORDER+1);i++){
    PSIPXY[i]=new double[(APROP.SIP_L_ORDER+1)];
    for(j=0;j<(APROP.SIP_L_ORDER+1);j++)
    PSIPXY[i][j]=0;
    }

    for(ij=0;ij<4;ij++){
    DIFFPSIP[ij] = new double**[APROP.CCDNUM];
    for(CID=0;CID<APROP.CCDNUM;CID++){
    DIFFPSIP[ij][CID] = new double*[(APROP.SIP_L_ORDER+1)];
    for(i=0;i<(APROP.SIP_L_ORDER+1);i++){
    DIFFPSIP[ij][CID][i] = new double[(APROP.SIP_L_ORDER+1)];
    for(j=0;j<(APROP.SIP_L_ORDER+1);j++)
    DIFFPSIP[ij][CID][i][j]=0;
    }}}
//LOCAL FITTING
    for(i=0;i<APROP.NUMREFALL;i++){
        CID=PAIR[i].CHIPID;
        NUM=dx[0][CID][0][0];
        dx[1][CID][NUM][0]=dx[2][CID][NUM][0]=PAIR[i].xI;
        dx[1][CID][NUM][1]=dx[2][CID][NUM][1]=PAIR[i].yI;
        dx[1][CID][NUM][2]=PAIR[i].xL;        
        dx[2][CID][NUM][2]=PAIR[i].yL;        
        dx[0][CID][0][0]+=1;
    }

    for(CID=0;CID<APROP.CCDNUM;CID++){
        F_LS2(dx[0][CID][0][0],APROP.SIP_L_ORDER,dx[1][CID],PSIP[CID][0]);
        F_LS2(dx[0][CID][0][0],APROP.SIP_L_ORDER,dx[2][CID],PSIP[CID][1]);
    }

//DIFFERENTIAL OF PAIR
    for(CID=0;CID<APROP.CCDNUM;CID++){
        ij=0;
        for(i=0;i<(APROP.SIP_L_ORDER+1);i++)
        for(j=0;j<(APROP.SIP_L_ORDER+1);j++)
        if(i+j<(APROP.SIP_L_ORDER+1)){
        PSIPXY[i][j]=PSIP[CID][0][ij];
        ij++;
        }
        for(i=0;i<(APROP.SIP_L_ORDER+1);i++)
        for(j=0;j<(APROP.SIP_L_ORDER+1);j++){
        if(i<(APROP.SIP_L_ORDER+1)-1)
        DIFFPSIP[0][CID][i][j]=(i+1)*PSIPXY[i+1][j];
        if(j<(APROP.SIP_L_ORDER+1)-1)
        DIFFPSIP[1][CID][i][j]=(j+1)*PSIPXY[i][j+1];
        }

        ij=0;
        for(i=0;i<(APROP.SIP_L_ORDER+1);i++)
        for(j=0;j<(APROP.SIP_L_ORDER+1);j++)
        if(i+j<(APROP.SIP_L_ORDER+1)){
        PSIPXY[i][j]=PSIP[CID][1][ij];
        ij++;
        }
        for(i=0;i<(APROP.SIP_L_ORDER+1);i++)
        for(j=0;j<(APROP.SIP_L_ORDER+1);j++){
        if(i<(APROP.SIP_L_ORDER+1)-1)
        DIFFPSIP[2][CID][i][j]=(i+1)*PSIPXY[i+1][j];
        if(j<(APROP.SIP_L_ORDER+1)-1)
        DIFFPSIP[3][CID][i][j]=(j+1)*PSIPXY[i][j+1];
        }
    }

    for(ij=0;ij<APROP.NUMREFALL;ij++){
//cout << PAIR[ij].ID << "	" << PAIR[ij].CHIPID << "	" << PAIR[ij].xL << "	" << PAIR[ij].yL << endl;
        CID=PAIR[ij].CHIPID;
        PAIR[ij].dxLdxI=PAIR[ij].dxLdyI=PAIR[ij].dyLdxI=PAIR[ij].dyLdyI=0;
        for(i=0;i<(APROP.SIP_L_ORDER+1);i++)
        for(j=0;j<(APROP.SIP_L_ORDER+1);j++){
            PAIR[ij].dxLdxI+=DIFFPSIP[0][CID][i][j]*pow(PAIR[ij].xI,i)*pow(PAIR[ij].yI,j);
            PAIR[ij].dxLdyI+=DIFFPSIP[1][CID][i][j]*pow(PAIR[ij].xI,i)*pow(PAIR[ij].yI,j);
            PAIR[ij].dyLdxI+=DIFFPSIP[2][CID][i][j]*pow(PAIR[ij].xI,i)*pow(PAIR[ij].yI,j);
            PAIR[ij].dyLdyI+=DIFFPSIP[3][CID][i][j]*pow(PAIR[ij].xI,i)*pow(PAIR[ij].yI,j);
        }
    }
//--------------------------------------------------
    for(i=0;i<3;i++){
    for(CID=0;CID<APROP.CCDNUM;CID++){
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    delete [] dx[i][CID][NUM];
    delete [] dx[i][CID];
    }
    delete [] dx[i];
    }

    for(CID=0;CID<APROP.CCDNUM;CID++){	
    for(i=0;i<2;i++)
    delete [] PSIP[CID][i];
    delete [] PSIP[CID];
    }
    delete [] PSIP;

    for(i=0;i<(APROP.SIP_L_ORDER+1);i++)
    delete [] PSIPXY[i];
    delete [] PSIPXY;

    for(i=0;i<4;i++){
    for(CID=0;CID<APROP.CCDNUM;CID++){
    for(j=0;j<(APROP.SIP_L_ORDER+1);j++)
    delete [] DIFFPSIP[i][CID][j];    
    delete [] DIFFPSIP[i][CID];    
    }
    delete [] DIFFPSIP[i];    
    }
}
void    F_CHANGEdxLtodxG(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,j,CID,NUM,PHASE;
    double **dGdI[4],*dPSIP[4];
    cout << endl << "--- F_WCS_TANSIP : GLOBAL POSITION : DETERMINING dxG FROM dxL ---\n";

    for(i=0;i<4;i++){
    dGdI[i] = new double*[APROP.NUMREFALL];
    for(j=0;j<APROP.NUMREFALL;j++)
    dGdI[i][j] = new double[3];
    dPSIP[i] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+1)];
    for(j=0;j<(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+1);j++)
    dPSIP[i][j]=0;
    }

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].dxGdxI=PAIR[NUM].dxLdxI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].dyLdxI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].dxGdyI=PAIR[NUM].dxLdyI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].dyLdyI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].dyGdxI=PAIR[NUM].dyLdxI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].dxLdxI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].dyGdyI=PAIR[NUM].dyLdyI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].dxLdyI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
    }

//    for(PHASE=0;PHASE<APROP.CCDNUM;PHASE++)
//    for(CID=0;CID<APROP.CCDNUM;CID++){
//    if(CPROP[CID].PHASE==PHASE){
//fitting
        for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
            dGdI[0][NUM][0]=dGdI[1][NUM][0]=dGdI[2][NUM][0]=dGdI[3][NUM][0]=PAIR[NUM].xI;
            dGdI[0][NUM][1]=dGdI[1][NUM][1]=dGdI[2][NUM][1]=dGdI[3][NUM][1]=PAIR[NUM].yI;
            dGdI[0][NUM][2]=PAIR[NUM].dxGdxI;
            dGdI[1][NUM][2]=PAIR[NUM].dxGdyI;
            dGdI[2][NUM][2]=PAIR[NUM].dyGdxI;
            dGdI[3][NUM][2]=PAIR[NUM].dyGdyI;
        }
        for(i=0;i<4;i++)
        F_LS2(APROP.NUMREFALL,APROP.SIP_P_ORDER-1,dGdI[i],dPSIP[i]);
//minimum RMS
        for(CID=0;CID<APROP.CCDNUM;CID++){
        F_MINT(-1,CID,APROP,CPROP,PAIR,dPSIP);
        F_MINT(-2,CID,APROP,CPROP,PAIR,dPSIP);
        F_MINT(-3,CID,APROP,CPROP,PAIR,dPSIP);
        F_MINT(-4,CID,APROP,CPROP,PAIR,dPSIP);
        F_MINT(-5,CID,APROP,CPROP,PAIR,dPSIP);
        F_MINT(-6,CID,APROP,CPROP,PAIR,dPSIP);
        }

//dtheta
//dxG
        for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
            PAIR[NUM].dxGdxI=PAIR[NUM].dxLdxI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].dyLdxI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
            PAIR[NUM].dxGdyI=PAIR[NUM].dxLdyI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].dyLdyI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
            PAIR[NUM].dyGdxI=PAIR[NUM].dyLdxI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].dxLdxI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
            PAIR[NUM].dyGdyI=PAIR[NUM].dyLdyI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].dxLdyI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        }
//        break;
//    }
//    }

    for(i=0;i<4;i++){
    delete [] dPSIP[i];
    for(j=0;j<APROP.NUMREFALL;j++)
    delete [] dGdI[i][j];
    delete [] dGdI[i];
    }

}
void    F_MINT(int order,int CID,CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,double **dPSIP){
    int i,ix,iy,ixy,NUM;
    double A;
    double RMS,RMSMIN;
    double dT,dTMIN;

    RMSMIN=pow(10,100);
    for(i=-10;i<10;i++){
        dT=CPROP[CID].GLOB_POS[2]+i*pow(10,order);
        RMS=0;
        for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
        if(PAIR[NUM].CHIPID==CID){
            A=0;
            ixy=0;
            for(ix=0;ix<APROP.SIP_P_ORDER+1-1;ix++)
            for(iy=0;iy<APROP.SIP_P_ORDER+1-1;iy++)
            if(ix+iy<APROP.SIP_P_ORDER+1-1){
            A+=dPSIP[0][ixy]*pow(PAIR[NUM].xI,ix)*pow(PAIR[NUM].yI,iy);
            ixy++;
            }
            RMS+=(A-(PAIR[NUM].dxLdxI*cos(dT)-PAIR[NUM].dyLdxI*sin(dT)))*(A-(PAIR[NUM].dxLdxI*cos(dT)-PAIR[NUM].dyLdxI*sin(dT)));

            A=0;
            ixy=0;
            for(ix=0;ix<APROP.SIP_P_ORDER+1-1;ix++)
            for(iy=0;iy<APROP.SIP_P_ORDER+1-1;iy++)
            if(ix+iy<APROP.SIP_P_ORDER+1-1){
            A+=dPSIP[1][ixy]*pow(PAIR[NUM].xI,ix)*pow(PAIR[NUM].yI,iy);
            ixy++;
            }
            RMS+=(A-(PAIR[NUM].dxLdyI*cos(dT)-PAIR[NUM].dyLdyI*sin(dT)))*(A-(PAIR[NUM].dxLdyI*cos(dT)-PAIR[NUM].dyLdyI*sin(dT)));

            A=0;
            ixy=0;
            for(ix=0;ix<APROP.SIP_P_ORDER+1-1;ix++)
            for(iy=0;iy<APROP.SIP_P_ORDER+1-1;iy++)
            if(ix+iy<APROP.SIP_P_ORDER+1-1){
            A+=dPSIP[2][ixy]*pow(PAIR[NUM].xI,ix)*pow(PAIR[NUM].yI,iy);
            ixy++;
            }
            RMS+=(A-(PAIR[NUM].dyLdxI*cos(dT)+PAIR[NUM].dxLdxI*sin(dT)))*(A-(PAIR[NUM].dyLdxI*cos(dT)+PAIR[NUM].dxLdxI*sin(dT)));

            A=0;
            ixy=0;
            for(ix=0;ix<APROP.SIP_P_ORDER+1-1;ix++)
            for(iy=0;iy<APROP.SIP_P_ORDER+1-1;iy++)
            if(ix+iy<APROP.SIP_P_ORDER+1-1){
            A+=dPSIP[3][ixy]*pow(PAIR[NUM].xI,ix)*pow(PAIR[NUM].yI,iy);
            ixy++;
            }
            RMS+=(A-(PAIR[NUM].dyLdyI*cos(dT)+PAIR[NUM].dxLdyI*sin(dT)))*(A-(PAIR[NUM].dyLdyI*cos(dT)+PAIR[NUM].dxLdyI*sin(dT)));
        }
        if(RMS<RMSMIN){
            RMSMIN=RMS;
            dTMIN=dT;
        }
    }
    CPROP[CID].GLOB_POS[2]=dTMIN;
}
void    F_CHANGEdxLtodxGNOROT(CL_APROP APROP,CL_CPROP CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM;
    cout << endl << "--- F_WCS_TANSIP : GLOBAL POSITION : DETERMINING dxG FROM dxL without rotation---\n";
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].dxGdxI=PAIR[NUM].dxLdxI;
        PAIR[NUM].dxGdyI=PAIR[NUM].dxLdyI;
        PAIR[NUM].dyGdxI=PAIR[NUM].dyLdxI;
        PAIR[NUM].dyGdyI=PAIR[NUM].dyLdyI;
    }

}
void    F_FITINTdxGdxI(CL_APROP APROP,CL_CPROP CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,j,k,ij,NUM;
    double **dx[4],*PSIP[4],**PSIPXY[4],**INTPSIPXY[4];

    cout << endl << "--- F_WCS_TANSIP : GLOBAL POSITION : FITTING AND INTEGRATING dxG ---\n";
    for(i=0;i<4;i++){
    dx[i]=new double*[APROP.NUMREFALL];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    dx[i][NUM]=new double[3];
    for(j=0;j<3;j++)
    dx[i][NUM][j]=0;
    }}

    for(i=0;i<4;i++){
    PSIP[i] = new double[(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+1)];
    for(j=0;j<(APROP.SIP_P_ORDER+1)*(APROP.SIP_P_ORDER+1);j++)
    PSIP[i][j]=0;
    }

    for(ij=0;ij<4;ij++){
    PSIPXY[ij] = new double*[(APROP.SIP_P_ORDER+1)];
    INTPSIPXY[ij] = new double*[(APROP.SIP_P_ORDER+1)];
    for(i=0;i<(APROP.SIP_P_ORDER+1);i++){
    PSIPXY[ij][i] = new double[(APROP.SIP_P_ORDER+1)];
    INTPSIPXY[ij][i] = new double[(APROP.SIP_P_ORDER+1)];
    for(j=0;j<(APROP.SIP_P_ORDER+1);j++){
    PSIPXY[ij][i][j]=0;
    INTPSIPXY[ij][i][j]=0;
    }}}
//FIT
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        for(i=0;i<4;i++){
            dx[i][NUM][0]=PAIR[NUM].xI;
            dx[i][NUM][1]=PAIR[NUM].yI;
        }
        dx[0][NUM][2]=PAIR[NUM].dxGdxI;
        dx[1][NUM][2]=PAIR[NUM].dxGdyI;
        dx[2][NUM][2]=PAIR[NUM].dyGdxI;
        dx[3][NUM][2]=PAIR[NUM].dyGdyI;
    }
    for(i=0;i<4;i++)
    F_LS2(APROP.NUMREFALL,APROP.SIP_P_ORDER-1,dx[i],PSIP[i]);
//INT
    ij=0;
    for(i=0;i<(APROP.SIP_P_ORDER+1)-1;i++)
    for(j=0;j<(APROP.SIP_P_ORDER+1)-1;j++)
    if(i+j<(APROP.SIP_P_ORDER+1)-1){
        for(k=0;k<4;k++)
        PSIPXY[k][i][j]=PSIP[k][ij];
        ij++;
    }
    for(k=0;k<4;k++)
    INTPSIPXY[k][0][0]=0;
    for(i=0;i<(APROP.SIP_P_ORDER+1);i++)
    for(j=0;j<(APROP.SIP_P_ORDER+1);j++){
        if(i>0){
        INTPSIPXY[0][i][j]=1.0/i*PSIPXY[0][i-1][j];
        INTPSIPXY[2][i][j]=1.0/i*PSIPXY[2][i-1][j];
        }
        if(j>0){
        INTPSIPXY[1][i][j]=1.0/j*PSIPXY[1][i][j-1];
        INTPSIPXY[3][i][j]=1.0/j*PSIPXY[3][i][j-1];
        }
    }
    for(k=0;k<4;k++)
    for(i=0;i<(APROP.SIP_P_ORDER+1);i++)
    for(j=0;j<(APROP.SIP_P_ORDER+1);j++)
    PSIPXY[k][i][j]=0;
    for(i=0;i<(APROP.SIP_P_ORDER+1);i++)
    for(j=0;j<(APROP.SIP_P_ORDER+1);j++){
              if(fabs(INTPSIPXY[0][i][j])>INFMIN&&fabs(INTPSIPXY[1][i][j])>INFMIN){
            PSIPXY[0][i][j]=0.5*(INTPSIPXY[0][i][j]+INTPSIPXY[1][i][j]);
        }else if(fabs(INTPSIPXY[0][i][j])<INFMIN){ 
            PSIPXY[0][i][j]=INTPSIPXY[1][i][j];
        }else if(fabs(INTPSIPXY[1][i][j])<INFMIN){ 
            PSIPXY[0][i][j]=INTPSIPXY[0][i][j];
        }else     {
            PSIPXY[0][i][j]=0;
        } 
              if(fabs(INTPSIPXY[2][i][j])>INFMIN&&fabs(INTPSIPXY[3][i][j])>INFMIN){
            PSIPXY[1][i][j]=0.5*(INTPSIPXY[2][i][j]+INTPSIPXY[3][i][j]);
        }else if(fabs(INTPSIPXY[2][i][j])<INFMIN){ 
            PSIPXY[1][i][j]=INTPSIPXY[3][i][j];
        }else if(fabs(INTPSIPXY[3][i][j])<INFMIN){ 
            PSIPXY[1][i][j]=INTPSIPXY[2][i][j];
        }else     {
            PSIPXY[1][i][j]=0;
        } 
    }
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
	PAIR[NUM].xG=PAIR[NUM].yG=0;
        for(i=0;i<(APROP.SIP_P_ORDER+1);i++)
        for(j=0;j<(APROP.SIP_P_ORDER+1);j++)
        if(i+j<(APROP.SIP_P_ORDER+1)){
        PAIR[NUM].xG+=PSIPXY[0][i][j]*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
        PAIR[NUM].yG+=PSIPXY[1][i][j]*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
        }
    }
//--------------------------------------------------
    for(i=0;i<4;i++){
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++)
    delete [] dx[i][NUM];
    delete [] dx[i];
    delete [] PSIP[i];
    for(j=0;j<(APROP.SIP_P_ORDER+1);j++){
    delete [] PSIPXY[i][j];
    delete [] INTPSIPXY[i][j];
    }
    delete [] PSIPXY[i];
    delete [] INTPSIPXY[i];
    }
}
void    F_FITGPOS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    cout << endl << "--- F_WCS_TANSIP : GLOBAL POSITION : FITTING GLOBAL POSITION ---\n";
    int i,CID,NUM;
    double **dX;

    dX = new double*[APROP.CCDNUM];
    for(CID=0;CID<APROP.CCDNUM;CID++){
    dX[CID] = new double[3];
    for(i=0;i<3;i++)
    dX[CID][i] = 0;
    }

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        dX[PAIR[NUM].CHIPID][0]+=1;
        dX[PAIR[NUM].CHIPID][1]+=PAIR[NUM].xG-(PAIR[NUM].xL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].yL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]));
        dX[PAIR[NUM].CHIPID][2]+=PAIR[NUM].yG-(PAIR[NUM].yL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].xL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]));
    }

    for(CID=0;CID<APROP.CCDNUM;CID++)
    cout <<fixed<< CID << " : " << dX[CID][1]/dX[CID][0] << "	"  << dX[CID][2]/dX[CID][0] << endl;

double BASE[2]={0};
/*
//BASE[0]=-1011.594-dX[5][1]/dX[5][0];
//BASE[1]=    9.080-dX[5][2]/dX[5][0];
BASE[0]= 0.0000-dX[5][1]/dX[5][0];
BASE[1]= 0.0000-dX[5][2]/dX[5][0];
for(CID=0;CID<APROP.CCDNUM;CID++)
cout <<fixed<< CID << " : " << dX[CID][1]/dX[CID][0]+BASE[0] << "	"  << dX[CID][2]/dX[CID][0]+BASE[1] << endl;
*/
    for(CID=0;CID<APROP.CCDNUM;CID++){
        CPROP[CID].GLOB_POS[0]=dX[CID][1]/dX[CID][0]+BASE[0];
        CPROP[CID].GLOB_POS[1]=dX[CID][2]/dX[CID][0]+BASE[1];
    }
/*
//YAGISAN
CPROP[0].GLOB_POS[0]= 3197;
CPROP[0].GLOB_POS[1]=   82;
CPROP[0].GLOB_POS[2]=    0;
CPROP[1].GLOB_POS[0]= 1075;
CPROP[1].GLOB_POS[1]=   82;
CPROP[1].GLOB_POS[2]=    0;
CPROP[2].GLOB_POS[0]=-1043;
CPROP[2].GLOB_POS[1]=   83;
CPROP[2].GLOB_POS[2]=    0;
CPROP[3].GLOB_POS[0]= 3197;
CPROP[3].GLOB_POS[1]=-4170;
CPROP[3].GLOB_POS[2]=    0;
CPROP[4].GLOB_POS[0]= 1081;
CPROP[4].GLOB_POS[1]=-4168;
CPROP[4].GLOB_POS[2]=    0;
CPROP[5].GLOB_POS[0]=-1045;
CPROP[5].GLOB_POS[1]=-4173;
CPROP[5].GLOB_POS[2]=    0;
CPROP[6].GLOB_POS[0]=-5285;
CPROP[6].GLOB_POS[1]=   83;
CPROP[6].GLOB_POS[2]=    0;
CPROP[7].GLOB_POS[0]=-3165;
CPROP[7].GLOB_POS[1]=   82;
CPROP[7].GLOB_POS[2]=    0;
CPROP[8].GLOB_POS[0]=-5283;
CPROP[8].GLOB_POS[1]=-4171;
CPROP[8].GLOB_POS[2]=    0;
CPROP[9].GLOB_POS[0]=-3163;
CPROP[9].GLOB_POS[1]=-4167;
CPROP[9].GLOB_POS[2]=    0;
*//*
//YOSHINOSAN
CPROP[0].GLOB_POS[0]=-5294.357+32.0;
CPROP[0].GLOB_POS[1]=    7.801;
CPROP[0].GLOB_POS[2]=    0.0002951;
CPROP[1].GLOB_POS[0]=-3169.207+32.0;
CPROP[1].GLOB_POS[1]=    9.680;
CPROP[1].GLOB_POS[2]=    0.0002563;
CPROP[2].GLOB_POS[0]=-1040.665+32.0;
CPROP[2].GLOB_POS[1]=-4107.447;
CPROP[2].GLOB_POS[2]=    0.0002663;
CPROP[3].GLOB_POS[0]= 1085.876+32.0;
CPROP[3].GLOB_POS[1]=-4170.447;
CPROP[3].GLOB_POS[2]=    0.0002072;
CPROP[4].GLOB_POS[0]= 1080.727+32.0;
CPROP[4].GLOB_POS[1]=   13.219;
CPROP[4].GLOB_POS[2]=    0.0002498;
CPROP[5].GLOB_POS[0]=-1011.594;
CPROP[5].GLOB_POS[1]=    9.080;
CPROP[5].GLOB_POS[2]=    0.0001967;
CPROP[6].GLOB_POS[0]=-5260.792;
CPROP[6].GLOB_POS[1]=-4110.721;
CPROP[6].GLOB_POS[2]=    0.0001673;
CPROP[7].GLOB_POS[0]=-3134.652;
CPROP[7].GLOB_POS[1]=-4110.798;
CPROP[7].GLOB_POS[2]=    0.0001967;
CPROP[8].GLOB_POS[0]= 3244.009;
CPROP[8].GLOB_POS[1]=-4103.241;
CPROP[8].GLOB_POS[2]=    0.0002740;
CPROP[9].GLOB_POS[0]= 3203.974+32.0;
CPROP[9].GLOB_POS[1]=   15.337;
CPROP[9].GLOB_POS[2]=    0.0002277;
*/
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].xG=CPROP[PAIR[NUM].CHIPID].GLOB_POS[0]+PAIR[NUM].xL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].yL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].yG=CPROP[PAIR[NUM].CHIPID].GLOB_POS[1]+PAIR[NUM].yL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].xL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
    }
    for(CID=0;CID<APROP.CCDNUM;CID++)
    delete [] dX[CID];
    delete [] dX;    
}
#undef PI
