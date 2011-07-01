//------------------------------------------------------------
//WCS_TANSIP_GPOS.cc
//Dtermining CCD positions
//
//Last modification : 2010/04/15
//------------------------------------------------------------
#include<iostream>
#include<iomanip>
#include<string.h>
#include<cmath>
#include<omp.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"
//#include<fstream>//temp

#define PI (4*atan(1.0))

using namespace std;
void    F_WCS_TANSIP_SETxG                (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_SETxCRVAL            (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_SETxCRPIX            (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_CENTERofOBJECTS      (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_CR           (int DIR,CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_PROJECTION           (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_PROJECTION      (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_CCDPOSITIONS_T  (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_LDIFFVALUES     (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_LPOLYNOMIALFITTING(int VARIABLE, int FUNCTION,CL_APROP APROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_A_GDIFFVALUES   (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_A_CCDPOSITIONS_T(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_CCDPOSITIONS_XY (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_ALIGN          (CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_SIPFIT           (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_PSIPFIT          (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_CAMERADIST       (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_SIPDIST          (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_WCS_OPTICAXIS        (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);

void    F_WCS_TANSIP_GPOS(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : PROJECTION ---" << endl;
        F_WCS_TANSIP_GPOS_PROJECTION(*APROP,CPROP,PAIR,&CSIP[APROP->CCDNUM]);
        F_WCS_TANSIP_GPOS_LDIFFVALUES(*APROP,CPROP,PAIR,CSIP);
        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : CALCULATING THETA of CCD ---" << endl;
        F_WCS_TANSIP_GPOS_CCDPOSITIONS_T(*APROP,CPROP,PAIR,CSIP);
        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : CALCULATING XY of CCD ---" << endl;
        F_WCS_TANSIP_GPOS_CCDPOSITIONS_XY(*APROP,CPROP,PAIR,CSIP);
        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : ALIGN ---" << endl;
        F_WCS_TANSIP_GPOS_ALIGN(APROP,CPROP,PAIR,CSIP);

}
void    F_WCS_TANSIP_GPOS_PROJECTION(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
//obtaining CRVAL

          if(strcmp(APROP.CRPIXMODE,"OAXIS")==0){
        F_WCS_TANSIP_SETxG(APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_CENTERofOBJECTS(APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_CR(0,APROP,CPROP,PAIR,CSIP);
        for(;;){
            F_WCS_TANSIP_PROJECTION(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_WCS_SIPFIT (APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_SETxCRVAL(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_WCS_PSIPFIT(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_WCS_CAMERADIST(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_WCS_SIPDIST(APROP,CPROP,PAIR,CSIP);
            F_WCS_TANSIP_WCS_OPTICAXIS(APROP,CPROP,PAIR,CSIP);
            if(hypot(CSIP->CRPIX[0]-CSIP->OAPIX[0],CSIP->CRPIX[1]-CSIP->OAPIX[1])<pow(10.0,-3))
            break;
            CSIP->CRVAL[0]=CSIP->OAVAL[0];
            CSIP->CRVAL[1]=CSIP->OAVAL[1];
            CSIP->CRPIX[0]=CSIP->OAPIX[0];
            CSIP->CRPIX[1]=CSIP->OAPIX[1];
            F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
        }
    }else if(strcmp(APROP.CRPIXMODE,"VAL")==0){
        CSIP->CRVAL[0]=APROP.CRVAL[0];
        CSIP->CRVAL[1]=APROP.CRVAL[1];
    }else if(strcmp(APROP.CRPIXMODE,"AUTO")==0){
        F_WCS_TANSIP_SETxG(APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_CENTERofOBJECTS(APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_CR(0,APROP,CPROP,PAIR,CSIP);
    }else if(strcmp(APROP.CRPIXMODE,"PIX")==0){
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_CR(0,APROP,CPROP,PAIR,CSIP);
    }

//projection
    if(APROP.STDOUT==2)cout << "PROJECTION POSITION ( " << CSIP->CRVAL[0] << " , " << CSIP->CRVAL[1] << " )"<< endl;
    F_WCS_TANSIP_PROJECTION(APROP,CPROP,PAIR,CSIP);
}
void    F_WCS_TANSIP_GPOS_LDIFFVALUES(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int CID,NUM,CoefNUM;
    double ****dLCoef;

    CoefNUM=(int)(0.5*(APROP.SIP_L_ORDER+1)*(APROP.SIP_L_ORDER+2)+0.1);
    dLCoef = F_NEWdouble4(2,2,APROP.CCDNUM,CoefNUM);

//--------------------------------------------------
//Calculating CRval of each CCD 
//CRpix is (0,0)

    F_WCS_TANSIP_GPOS_LPOLYNOMIALFITTING(5,1,APROP,PAIR,CSIP);
    for(CID=0;CID<APROP.CCDNUM;CID++){
        CSIP[CID].CRVAL[0]=CSIP[CID].TLCoef[0][0];
        CSIP[CID].CRVAL[1]=CSIP[CID].TLCoef[1][0];
    }

    F_WCS_TANSIP_GPOS_LPOLYNOMIALFITTING(1,5,APROP,PAIR,CSIP);//InvCD=unit

    for(CID=0;CID<APROP.CCDNUM;CID++){
        F_DIFFSIP(APROP.SIP_L_ORDER,CSIP[CID].TLCoef[0],dLCoef[0][0][CID],dLCoef[0][1][CID]);
        F_DIFFSIP(APROP.SIP_L_ORDER,CSIP[CID].TLCoef[1],dLCoef[1][0][CID],dLCoef[1][1][CID]);
    }

    double xI[2],**STdata,ST[2][2];
    STdata = F_NEWdouble2(2,APROP.NUMREFALL);
//ofstream out;
//out.open("dtemp.dat");
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        CID=PAIR[NUM].CHIPID;
        xI[0]=PAIR[NUM].xI;
        xI[1]=PAIR[NUM].yI;
        STdata[0][NUM]=F_CALCVALUE(APROP.SIP_L_ORDER,CSIP[CID].TLCoef[0],xI) - PAIR[NUM].xL;
        STdata[1][NUM]=F_CALCVALUE(APROP.SIP_L_ORDER,CSIP[CID].TLCoef[1],xI) - PAIR[NUM].yL;

        PAIR[NUM].dxLdxI=F_CALCVALUE(APROP.SIP_L_ORDER,dLCoef[0][0][CID],xI);
        PAIR[NUM].dxLdyI=F_CALCVALUE(APROP.SIP_L_ORDER,dLCoef[0][1][CID],xI);
        PAIR[NUM].dyLdxI=F_CALCVALUE(APROP.SIP_L_ORDER,dLCoef[1][0][CID],xI);
        PAIR[NUM].dyLdyI=F_CALCVALUE(APROP.SIP_L_ORDER,dLCoef[1][1][CID],xI);
//out << NUM << "	" << PAIR[NUM].xI << "	" << PAIR[NUM].yI << "	" << PAIR[NUM].dxLdxI << "	" << PAIR[NUM].dxLdyI << "	" << PAIR[NUM].dyLdxI << "	" << PAIR[NUM].dyLdyI << endl;
    }
    F_RMS(APROP.NUMREFALL,STdata[0],ST[0]);
    F_RMS(APROP.NUMREFALL,STdata[1],ST[1]);

    if(APROP.STDOUT==2)cout << "LOCAL PSIP FITTING : x : AVE : " << ST[0][0] << " : RMS : " << ST[0][1] << endl;
    if(APROP.STDOUT==2)cout << "LOCAL PSIP FITTING : y : AVE : " << ST[1][0] << " : RMS : " << ST[1][1] << endl;
    if(APROP.STDOUT==2)cout << endl;
    
//-------------------------------------------------
    F_DELdouble2(2,STdata);
    F_DELdouble4(2,2,APROP.CCDNUM,dLCoef);
}
void    F_WCS_TANSIP_GPOS_LPOLYNOMIALFITTING(int VARIABLE, int FUNCTION,CL_APROP APROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int CID,NUM,*CNUM;
    double ****dx;

//--------------------------------------------------
    CNUM = F_NEWint1(APROP.CCDNUM);
    dx = F_NEWdouble4(2,APROP.CCDNUM,APROP.NUMREFALL,3);

//--------------------------------------------------

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        CID=PAIR[NUM].CHIPID;
	      if(VARIABLE==0){
            dx[0][CID][CNUM[CID]][0]=dx[1][CID][CNUM[CID]][0]=PAIR[NUM].RA;
            dx[0][CID][CNUM[CID]][1]=dx[1][CID][CNUM[CID]][1]=PAIR[NUM].DEC;
        }else if(VARIABLE==1){
            dx[0][CID][CNUM[CID]][0]=dx[1][CID][CNUM[CID]][0]=PAIR[NUM].xI;
            dx[0][CID][CNUM[CID]][1]=dx[1][CID][CNUM[CID]][1]=PAIR[NUM].yI;
        }else if(VARIABLE==2){
            dx[0][CID][CNUM[CID]][0]=dx[1][CID][CNUM[CID]][0]=PAIR[NUM].xCRVAL;
            dx[0][CID][CNUM[CID]][1]=dx[1][CID][CNUM[CID]][1]=PAIR[NUM].yCRVAL;
        }else if(VARIABLE==3){
            dx[0][CID][CNUM[CID]][0]=dx[1][CID][CNUM[CID]][0]=PAIR[NUM].xCRPIX;
            dx[0][CID][CNUM[CID]][1]=dx[1][CID][CNUM[CID]][1]=PAIR[NUM].yCRPIX;
        }else if(VARIABLE==4){
            dx[0][CID][CNUM[CID]][0]=dx[1][CID][CNUM[CID]][0]=PAIR[NUM].xG;
            dx[0][CID][CNUM[CID]][1]=dx[1][CID][CNUM[CID]][1]=PAIR[NUM].yG;
        }else if(VARIABLE==5){
            dx[0][CID][CNUM[CID]][0]=dx[1][CID][CNUM[CID]][0]=PAIR[NUM].xL;
            dx[0][CID][CNUM[CID]][1]=dx[1][CID][CNUM[CID]][1]=PAIR[NUM].yL;
        }
	      if(FUNCTION==0){
            dx[0][CID][CNUM[CID]][2]=PAIR[NUM].RA;
            dx[1][CID][CNUM[CID]][2]=PAIR[NUM].DEC;
        }else if(FUNCTION==1){
            dx[0][CID][CNUM[CID]][2]=PAIR[NUM].xI;
            dx[1][CID][CNUM[CID]][2]=PAIR[NUM].yI;
        }else if(FUNCTION==2){
            dx[0][CID][CNUM[CID]][2]=PAIR[NUM].xCRVAL;
            dx[1][CID][CNUM[CID]][2]=PAIR[NUM].yCRVAL;
        }else if(FUNCTION==3){
            dx[0][CID][CNUM[CID]][2]=PAIR[NUM].xCRPIX;
            dx[1][CID][CNUM[CID]][2]=PAIR[NUM].yCRPIX;
        }else if(FUNCTION==4){
            dx[0][CID][CNUM[CID]][2]=PAIR[NUM].xG;
            dx[1][CID][CNUM[CID]][2]=PAIR[NUM].yG;
        }else if(FUNCTION==5){
            dx[0][CID][CNUM[CID]][2]=PAIR[NUM].xL;
            dx[1][CID][CNUM[CID]][2]=PAIR[NUM].yL;
        }
        CNUM[CID]++;
    }
    for(CID=0;CID<APROP.CCDNUM;CID++){
        F_LS2(CNUM[CID],APROP.SIP_L_ORDER,dx[0][CID],CSIP[CID].TLCoef[0]);
        F_LS2(CNUM[CID],APROP.SIP_L_ORDER,dx[1][CID],CSIP[CID].TLCoef[1]);
    }
//--------------------------------------------------*/
    F_DELint1(CNUM);
    F_DELdouble4(2,APROP.CCDNUM,APROP.NUMREFALL,dx);
}
void    F_WCS_TANSIP_GPOS_CCDPOSITIONS_T(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int Iter,ID,TCHECK;
    double *Tcheck;
    
    Tcheck = F_NEWdouble1(APROP.CCDNUM);
//--------------------------------------------------

    for(Iter=0;;Iter++){
        if(APROP.STDOUT==2)cout << "T iteration : " << Iter << endl;

        for(ID=0;ID<APROP.CCDNUM;ID++)
        Tcheck[ID]=CPROP[ID].GLOB_POS[2];

        F_WCS_TANSIP_GPOS_A_GDIFFVALUES(APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_GPOS_A_CCDPOSITIONS_T(APROP,CPROP,PAIR,CSIP);

        double MCBASE=CPROP[APROP.BASISCID].GLOB_POS[2]-APROP.BASIS_POS[2];
        for(ID=0;ID<APROP.CCDNUM;ID++)
        CPROP[ID].GLOB_POS[2]-=MCBASE;

        if(APROP.STDOUT==2)if(Iter==10){
            cout << "Theta iteration didn't converge" << endl;
            break;
        }

        TCHECK=0;
        for(ID=0;ID<APROP.CCDNUM;ID++)
        if(fabs(Tcheck[ID]-CPROP[ID].GLOB_POS[2])>pow(10,-5.0))
        TCHECK++;

        if(TCHECK==0){
            if(APROP.STDOUT==2)cout << "Theta iteration converged" << endl;
            if(APROP.STDOUT==2)for(ID=0;ID<APROP.CCDNUM;ID++)
            cout <<"CCD : " << ID << " : Theta : "<< CPROP[ID].GLOB_POS[2] << endl;
            if(APROP.STDOUT==2)cout << endl;
            break;
        }
    }
//--------------------------------------------------
    F_DELdouble1(Tcheck);
}
void    F_WCS_TANSIP_GPOS_A_GDIFFVALUES  (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,CoefNUM,dCoefNUM;
    double ****dGdI,***dPSIP;
    double xI[2];

     CoefNUM=(int)(0.5*(APROP.SIP_P_ORDER+1  )*(APROP.SIP_P_ORDER+2  )+0.5);
    dCoefNUM=(int)(0.5*(APROP.SIP_P_ORDER+1-1)*(APROP.SIP_P_ORDER+2-1)+0.5);

    dGdI  = F_NEWdouble4(2,2,APROP.NUMREFALL,3);
    dPSIP = F_NEWdouble3(2,2,dCoefNUM);

//Calculating dxG/dxI and Zxx
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].dxGdxI=PAIR[NUM].dxLdxI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].dyLdxI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].dyGdxI=PAIR[NUM].dyLdxI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].dxLdxI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].dxGdyI=PAIR[NUM].dxLdyI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].dyLdyI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].dyGdyI=PAIR[NUM].dyLdyI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].dxLdyI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
    }

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].xCRVAL=PAIR[NUM].xI;
        PAIR[NUM].yCRVAL=PAIR[NUM].yI;
        dGdI[0][0][NUM][0]=dGdI[0][1][NUM][0]=dGdI[1][0][NUM][0]=dGdI[1][1][NUM][0]=PAIR[NUM].xCRVAL;
        dGdI[0][0][NUM][1]=dGdI[0][1][NUM][1]=dGdI[1][0][NUM][1]=dGdI[1][1][NUM][1]=PAIR[NUM].yCRVAL;
        dGdI[0][0][NUM][2]=PAIR[NUM].dxGdxI;
        dGdI[1][0][NUM][2]=PAIR[NUM].dyGdxI;
        dGdI[0][1][NUM][2]=PAIR[NUM].dxGdyI;
        dGdI[1][1][NUM][2]=PAIR[NUM].dyGdyI;
    }
    #pragma omp parallel num_threads(4)
    #pragma omp sections
    {
        #pragma omp section
        {
            F_LS2(APROP.NUMREFALL,APROP.SIP_P_ORDER-1,dGdI[0][0],dPSIP[0][0]);
        }
        #pragma omp section
        {
            F_LS2(APROP.NUMREFALL,APROP.SIP_P_ORDER-1,dGdI[0][1],dPSIP[0][1]);
        }
        #pragma omp section
        {
            F_LS2(APROP.NUMREFALL,APROP.SIP_P_ORDER-1,dGdI[1][0],dPSIP[1][0]);
        }
        #pragma omp section
        {
            F_LS2(APROP.NUMREFALL,APROP.SIP_P_ORDER-1,dGdI[1][1],dPSIP[1][1]);
        }
    }
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].Zxx=PAIR[NUM].Zxy=PAIR[NUM].Zyx=PAIR[NUM].Zyy=0;
        xI[0]=PAIR[NUM].xCRVAL;
        xI[1]=PAIR[NUM].yCRVAL;
        PAIR[NUM].Zxx=F_CALCVALUE(APROP.SIP_P_ORDER-1,dPSIP[0][0],xI);
        PAIR[NUM].Zxy=F_CALCVALUE(APROP.SIP_P_ORDER-1,dPSIP[0][1],xI);
        PAIR[NUM].Zyx=F_CALCVALUE(APROP.SIP_P_ORDER-1,dPSIP[1][0],xI);
        PAIR[NUM].Zyy=F_CALCVALUE(APROP.SIP_P_ORDER-1,dPSIP[1][1],xI);
//cout <<fixed<< PAIR[NUM].dxGdxI << "	" <<PAIR[NUM].Zxx << endl;
//cout.unsetf(ios::fixed);
    }

//--------------------------------------------------
    F_DELdouble4(2,2,APROP.NUMREFALL,dGdI);
    F_DELdouble3(2,2,dPSIP);
}
void    F_WCS_TANSIP_GPOS_A_CCDPOSITIONS_T(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,j,ij,k,l,kl,ID,ID2,NUM,dCoefNUM;
    double *MA,**MB,**InvMB,*MC;
    dCoefNUM=(int)(0.5*(APROP.SIP_P_ORDER+1-1)*(APROP.SIP_P_ORDER+2-1)+0.5);

       MA = F_NEWdouble1(APROP.CCDNUM+4*dCoefNUM);
       MB = F_NEWdouble2(APROP.CCDNUM+4*dCoefNUM,APROP.CCDNUM+4*dCoefNUM);
    InvMB = F_NEWdouble2(APROP.CCDNUM+4*dCoefNUM,APROP.CCDNUM+4*dCoefNUM);
       MC = F_NEWdouble1(APROP.CCDNUM+4*dCoefNUM);

//--------------------------------------------------
//dA1
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        MA[PAIR[NUM].CHIPID]-= PAIR[NUM].dyGdxI*PAIR[NUM].Zxx;
        MA[PAIR[NUM].CHIPID]-=-PAIR[NUM].dxGdxI*PAIR[NUM].Zyx;
        MA[PAIR[NUM].CHIPID]-= PAIR[NUM].dyGdyI*PAIR[NUM].Zxy;
        MA[PAIR[NUM].CHIPID]-=-PAIR[NUM].dxGdyI*PAIR[NUM].Zyy;
    }
//--------------------------------------------------
//dA2
    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1-1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1-1;j++)
    if(i+j<APROP.SIP_P_ORDER+1-1){
        for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
            MA[APROP.CCDNUM+0*dCoefNUM+ij]+=(PAIR[NUM].dxGdxI-PAIR[NUM].Zxx)*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
            MA[APROP.CCDNUM+1*dCoefNUM+ij]+=(PAIR[NUM].dyGdxI-PAIR[NUM].Zyx)*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
            MA[APROP.CCDNUM+2*dCoefNUM+ij]+=(PAIR[NUM].dxGdyI-PAIR[NUM].Zxy)*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
            MA[APROP.CCDNUM+3*dCoefNUM+ij]+=(PAIR[NUM].dyGdyI-PAIR[NUM].Zyy)*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
        }
    ij++;
    }
//--------------------------------------------------
//dB11
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dxGdxI*PAIR[NUM].dxGdxI;
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dyGdxI*PAIR[NUM].dyGdxI;
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dxGdyI*PAIR[NUM].dxGdyI;
        MB[PAIR[NUM].CHIPID][PAIR[NUM].CHIPID]+=PAIR[NUM].dyGdyI*PAIR[NUM].dyGdyI;
    }
    
//--------------------------------------------------
//dB12
    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1-1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1-1;j++)
    if(i+j<APROP.SIP_P_ORDER+1-1){
        for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
            MB[PAIR[NUM].CHIPID][APROP.CCDNUM+0*dCoefNUM+ij]+= PAIR[NUM].dyGdxI*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
            MB[PAIR[NUM].CHIPID][APROP.CCDNUM+1*dCoefNUM+ij]+=-PAIR[NUM].dxGdxI*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
            MB[PAIR[NUM].CHIPID][APROP.CCDNUM+2*dCoefNUM+ij]+= PAIR[NUM].dyGdyI*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
            MB[PAIR[NUM].CHIPID][APROP.CCDNUM+3*dCoefNUM+ij]+=-PAIR[NUM].dxGdyI*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
        }
    ij++;
    }
//--------------------------------------------------
//dB21
    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1-1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1-1;j++)
    if(i+j<APROP.SIP_P_ORDER+1-1){
        for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
            MB[APROP.CCDNUM+0*dCoefNUM+ij][PAIR[NUM].CHIPID]+= PAIR[NUM].dyGdxI*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
            MB[APROP.CCDNUM+1*dCoefNUM+ij][PAIR[NUM].CHIPID]+=-PAIR[NUM].dxGdxI*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
            MB[APROP.CCDNUM+2*dCoefNUM+ij][PAIR[NUM].CHIPID]+= PAIR[NUM].dyGdyI*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
            MB[APROP.CCDNUM+3*dCoefNUM+ij][PAIR[NUM].CHIPID]+=-PAIR[NUM].dxGdyI*pow(PAIR[NUM].xI,i)*pow(PAIR[NUM].yI,j);
        }
    ij++;
    }
//--------------------------------------------------
//dB22
    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1-1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1-1;j++)
    if(i+j<APROP.SIP_P_ORDER+1-1){
    kl=0;
    for(k=0;k<APROP.SIP_P_ORDER+1-1;k++)
    for(l=0;l<APROP.SIP_P_ORDER+1-1;l++)
    if(k+l<APROP.SIP_P_ORDER+1-1){
        for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
            MB[APROP.CCDNUM+0*dCoefNUM+ij][APROP.CCDNUM+0*dCoefNUM+kl]+=pow(PAIR[NUM].xI,i+k)*pow(PAIR[NUM].yI,j+l);
            MB[APROP.CCDNUM+1*dCoefNUM+ij][APROP.CCDNUM+1*dCoefNUM+kl]+=pow(PAIR[NUM].xI,i+k)*pow(PAIR[NUM].yI,j+l);
            MB[APROP.CCDNUM+2*dCoefNUM+ij][APROP.CCDNUM+2*dCoefNUM+kl]+=pow(PAIR[NUM].xI,i+k)*pow(PAIR[NUM].yI,j+l);
            MB[APROP.CCDNUM+3*dCoefNUM+ij][APROP.CCDNUM+3*dCoefNUM+kl]+=pow(PAIR[NUM].xI,i+k)*pow(PAIR[NUM].yI,j+l);
        }
    kl++;
    }
    ij++;
    }

//--------------------------------------------------
    F_InvM(APROP.CCDNUM+4*dCoefNUM,MB,InvMB);

    for(ID =0;ID <APROP.CCDNUM+4*dCoefNUM;ID ++)
    for(ID2=0;ID2<APROP.CCDNUM+4*dCoefNUM;ID2++)
    MC[ID]+=InvMB[ID][ID2]*MA[ID2];

    for(ID=0;ID<APROP.CCDNUM;ID++)
    CPROP[ID].GLOB_POS[2]+=MC[ID];

//--------------------------------------------------
    F_DELdouble1(MA);
    F_DELdouble2(APROP.CCDNUM+4*dCoefNUM,   MB);
    F_DELdouble2(APROP.CCDNUM+4*dCoefNUM,InvMB);
    F_DELdouble1(MC);

}
void    F_WCS_TANSIP_GPOS_CCDPOSITIONS_XY(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,NUM,ID,CoefNUM,dCoefNUM;
    double ****dGdI,***dPSIP;
    double xI[2];

     CoefNUM=(int)(0.5*(APROP.SIP_P_ORDER+1  )*(APROP.SIP_P_ORDER+2  )+0.5);
    dCoefNUM=(int)(0.5*(APROP.SIP_P_ORDER+1-1)*(APROP.SIP_P_ORDER+2-1)+0.5);

    dGdI  = F_NEWdouble4(2,2,APROP.NUMREFALL,3);
    dPSIP = F_NEWdouble3(2,2,dCoefNUM);
//--------------------------------------------------

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].dxGdxI=PAIR[NUM].dxLdxI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].dyLdxI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].dyGdxI=PAIR[NUM].dyLdxI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].dxLdxI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].dxGdyI=PAIR[NUM].dxLdyI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].dyLdyI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].dyGdyI=PAIR[NUM].dyLdyI*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].dxLdyI*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        dGdI[0][0][NUM][0]=dGdI[0][1][NUM][0]=dGdI[1][0][NUM][0]=dGdI[1][1][NUM][0]=PAIR[NUM].xCRVAL;
        dGdI[0][0][NUM][1]=dGdI[0][1][NUM][1]=dGdI[1][0][NUM][1]=dGdI[1][1][NUM][1]=PAIR[NUM].yCRVAL;
        dGdI[0][0][NUM][2]=PAIR[NUM].dxGdxI;
        dGdI[1][0][NUM][2]=PAIR[NUM].dyGdxI;
        dGdI[0][1][NUM][2]=PAIR[NUM].dxGdyI;
        dGdI[1][1][NUM][2]=PAIR[NUM].dyGdyI;
    }
    #pragma omp parallel num_threads(4)
    #pragma omp sections
    {
    #pragma omp section
        {
            F_LS2(APROP.NUMREFALL,APROP.SIP_P_ORDER-1,dGdI[0][0],dPSIP[0][0]);
        }
        #pragma omp section
        {
            F_LS2(APROP.NUMREFALL,APROP.SIP_P_ORDER-1,dGdI[0][1],dPSIP[0][1]);
        }
        #pragma omp section
        {
            F_LS2(APROP.NUMREFALL,APROP.SIP_P_ORDER-1,dGdI[1][0],dPSIP[1][0]);
        }
        #pragma omp section
        {
            F_LS2(APROP.NUMREFALL,APROP.SIP_P_ORDER-1,dGdI[1][1],dPSIP[1][1]);
        }
    }

//--------------------------------------------------
    double *PSIP[2];

    PSIP[0] = new double[CoefNUM];
    PSIP[1] = new double[CoefNUM];
    for(i=0;i<CoefNUM;i++)
    PSIP[0][i]=PSIP[1][i]=0;

    F_INTSIP(APROP.SIP_P_ORDER,dPSIP[0][0],dPSIP[0][1],PSIP[0]);
    F_INTSIP(APROP.SIP_P_ORDER,dPSIP[1][0],dPSIP[1][1],PSIP[1]);
//--------------------------------------------------
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].xG=PAIR[NUM].yG=0;
        xI[0]=PAIR[NUM].xCRVAL;
        xI[1]=PAIR[NUM].yCRVAL;
        PAIR[NUM].xG=F_CALCVALUE(APROP.SIP_P_ORDER,PSIP[0],xI);
        PAIR[NUM].yG=F_CALCVALUE(APROP.SIP_P_ORDER,PSIP[1],xI);
    }
//--------------------------------------------------
    double **dX;
    dX = F_NEWdouble2(APROP.CCDNUM,3);

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        dX[PAIR[NUM].CHIPID][0]+=1;
        dX[PAIR[NUM].CHIPID][1]+=PAIR[NUM].xG-(PAIR[NUM].xL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].yL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]));
        dX[PAIR[NUM].CHIPID][2]+=PAIR[NUM].yG-(PAIR[NUM].yL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].xL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]));
    }

    double BASE[2]={0};
    BASE[0]=APROP.BASIS_POS[0]-dX[APROP.BASISCID][1]/dX[APROP.BASISCID][0];
    BASE[1]=APROP.BASIS_POS[1]-dX[APROP.BASISCID][2]/dX[APROP.BASISCID][0];

    for(ID=0;ID<APROP.CCDNUM;ID++){
        CPROP[ID].GLOB_POS[0]=dX[ID][1]/dX[ID][0]+BASE[0];
        CPROP[ID].GLOB_POS[1]=dX[ID][2]/dX[ID][0]+BASE[1];
    }

//--------------------------------------------------
    F_DELdouble4(2,2,APROP.NUMREFALL,dGdI);
    F_DELdouble3(2,2,dPSIP);
    F_DELdouble2(APROP.CCDNUM,dX);
}
void    F_WCS_TANSIP_GPOS_ALIGN(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,ID,NM,*NMNUM;
    double **NMSET,NMCOEF[2],NMAVE[2]={0};
    double AC;

    NMNUM = F_NEWint1(APROP->CCDNUM);
    NMSET = F_NEWdouble2(APROP->CCDNUM,2);
//--------------------------------------------------

    if(APROP->ALIGNAXIS==1){
        if(APROP->STDOUT==2)cout << "Align Y axis" << endl;
        for(ID=0;ID<APROP->CCDNUM;ID++)
        if(CPROP[ID].ALIGN==1)
        NMNUM[CPROP[ID].POSID[0]]++;

        for(NM=0;NM<APROP->CCDNUM;NM++)
        if(NMNUM[NM]>1){
            i=0;
            for(ID=0;ID<APROP->CCDNUM;ID++)
            if(CPROP[ID].ALIGN==1)
            if(CPROP[ID].POSID[0]==NM){
            NMSET[i][0]= CPROP[ID].GLOB_POS[1];
            NMSET[i][1]=-CPROP[ID].GLOB_POS[0];
            i++;
            }
            NMNUM[NM]=i;
            F_LS1(NMNUM[NM],1,NMSET,NMCOEF);
            NMAVE[0]+=NMNUM[NM];
            NMAVE[1]+=NMNUM[NM]*atan2(NMCOEF[1],1.0);
        }
    }else{
        if(APROP->STDOUT==2)cout << "Align X axis" << endl;
        for(ID=0;ID<APROP->CCDNUM;ID++)
        if(CPROP[ID].ALIGN==1)
        NMNUM[CPROP[ID].POSID[1]]++;

        for(NM=0;NM<APROP->CCDNUM;NM++)
        if(NMNUM[NM]>1){
            i=0;
            for(ID=0;ID<APROP->CCDNUM;ID++)
            if(CPROP[ID].ALIGN==1)
            if(CPROP[ID].POSID[1]==NM){
            NMSET[i][0]=CPROP[ID].GLOB_POS[0];
            NMSET[i][1]=CPROP[ID].GLOB_POS[1];
            i++;
            }
            NMNUM[NM]=i;
            F_LS1(NMNUM[NM],1,NMSET,NMCOEF);
            NMAVE[0]+=NMNUM[NM];
            NMAVE[1]+=NMNUM[NM]*atan2(NMCOEF[1],1.0);
        }

    }
    if(NMAVE[0]>0){
    AC=-NMAVE[1]/NMAVE[0];
    }else{
    cout << "--------------------------------------------------" << endl;
    cout << "Warning : in F_WCS_TANSIP_GPOS_ALIGN"<<endl;
    cout << "          there are no CCDs which are able to calculate alignment" << endl;
    cout << "--------------------------------------------------" << endl;
    AC=0;
    }

    cout << "ANGLE : " << AC << endl;
//--------------------------------------------------
    double X[2];
    if(APROP->STDOUT==2)cout << "CCD GLOBAL POSITION : " << endl;
    for(ID=0;ID<APROP->CCDNUM;ID++){
        X[0]=CPROP[ID].GLOB_POS[0];
        X[1]=CPROP[ID].GLOB_POS[1];
        CPROP[ID].GLOB_POS[0]=X[0]*cos(AC)-X[1]*sin(AC);
        CPROP[ID].GLOB_POS[1]=X[1]*cos(AC)+X[0]*sin(AC);
        CPROP[ID].GLOB_POS[2]+=AC;
    }
    X[0]=APROP->CRPIX[0];
    X[1]=APROP->CRPIX[1];
    APROP->CRPIX[0]=X[0]*cos(AC)+X[1]*sin(AC);
    APROP->CRPIX[1]=X[1]*cos(AC)-X[0]*sin(AC);

    X[0]=APROP->BASIS_POS[0]-CPROP[APROP->BASISCID].GLOB_POS[0];
    X[1]=APROP->BASIS_POS[1]-CPROP[APROP->BASISCID].GLOB_POS[1];
    for(ID=0;ID<APROP->CCDNUM;ID++){
        CPROP[ID].GLOB_POS[0]+=X[0];
        CPROP[ID].GLOB_POS[1]+=X[1];
    }
    if(APROP->STDOUT==2)
    for(ID=0;ID<APROP->CCDNUM;ID++)
    cout <<fixed<< ID << " : X : " <<CPROP[ID].GLOB_POS[0] << "	: Y : " <<CPROP[ID].GLOB_POS[1] << "	: T : " <<scientific<<CPROP[ID].GLOB_POS[2] << "	: T : " <<fixed<<CPROP[ID].GLOB_POS[2]*180/PI << endl;
    cout.unsetf(ios::scientific);

    APROP->CRPIX[0]-=X[0];
    APROP->CRPIX[1]-=X[1];
    if(APROP->STDOUT==2)cout << "NEW CRPIX : ( " << APROP->CRPIX[0] << " , " << APROP->CRPIX[1] << " )" << endl;
    
//--------------------------------------------------
    F_DELint1(NMNUM);
    F_DELdouble2(APROP->CCDNUM,NMSET);
}
#undef PI
