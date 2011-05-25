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

#define CHECKstdout 1

using namespace std;
void    F_WCS_TANSIP_SETxG                (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_SETxCRVAL            (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_SETxCRPIX            (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_CENTERofOBJECTS      (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_CR           (int DIR,CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_PROJECTION           (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_OAXIS           (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_PROJECTION      (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_CCDPOSITIONS   (CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_LDIFFVALUES     (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_A_GDIFFVALUES   (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_A_CCDPOSITIONS_T(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_CCDPOSITIONS_XY (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);
void    F_WCS_TANSIP_GPOS_ALIGN          (CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP);

void    F_WCS_TANSIP_GPOS(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int ID;

//obtaining (xI, yI) from (RA, DEC) by projection at CRVAL
    F_WCS_TANSIP_GPOS_PROJECTION(*APROP,CPROP,PAIR,CSIP);

    if(APROP->CCDPOSMODE==1){
    F_WCS_TANSIP_GPOS_CCDPOSITIONS(APROP,CPROP,PAIR,CSIP);
    }else{
        cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : USING INITIAL VALUES for CCD POSITIONS ---" << endl;
        for(ID=0;ID<APROP->CCDNUM;ID++){
        CPROP[ID].GLOB_POS[0]=CPROP[ID].GLOB_POS_Init[0];
        CPROP[ID].GLOB_POS[1]=CPROP[ID].GLOB_POS_Init[1];
        CPROP[ID].GLOB_POS[2]=CPROP[ID].GLOB_POS_Init[2];
         }
    }
}
void    F_WCS_TANSIP_GPOS_PROJECTION(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

//obtaining CRVAL
    if(strcmp(APROP.CRPIXMODE,"VAL")==0){
        cout << "ASSIGNED CRVAL ( " << APROP.CRVAL[0] << " , " << APROP.CRVAL[1] << " )"<< endl;
        CSIP[APROP.CCDNUM].CRVAL[0]=APROP.CRVAL[0];
        CSIP[APROP.CCDNUM].CRVAL[1]=APROP.CRVAL[1];
    }else if(strcmp(APROP.CRPIXMODE,"PIX")==0){
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
        F_WCS_TANSIP_CR(0,APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    }else if(strcmp(APROP.CRPIXMODE,"OAXIS")==0){
        F_WCS_TANSIP_GPOS_OAXIS(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    }else if(strcmp(APROP.CRPIXMODE,"AUTO")==0){
        F_WCS_TANSIP_SETxG(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
        F_WCS_TANSIP_CENTERofOBJECTS(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
        cout << "CRPIX : (" << CSIP[APROP.CCDNUM].CRPIX[0] << " , " << CSIP[APROP.CCDNUM].CRPIX[1] << " )"<<endl;
        F_WCS_TANSIP_SETxCRPIX(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
        F_WCS_TANSIP_CR(0,APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    }

//projection
    F_WCS_TANSIP_PROJECTION(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
}
void    F_WCS_TANSIP_GPOS_OAXIS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    
}
void    F_WCS_TANSIP_GPOS_CCDPOSITIONS(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int Iter,ID,TCHECK;
    CL_CPROP *CPROPI;
    
    CPROPI = new CL_CPROP[APROP->CCDNUM];
//--------------------------------------------------
    F_WCS_TANSIP_GPOS_LDIFFVALUES(*APROP,CPROP,PAIR,CSIP);

    for(Iter=0;;Iter++){
        cout << "T iteration : " << Iter << endl;

        for(ID=0;ID<APROP->CCDNUM;ID++)
        CPROPI[ID].GLOB_POS[2]=CPROP[ID].GLOB_POS[2];

        F_WCS_TANSIP_GPOS_A_GDIFFVALUES(*APROP,CPROP,PAIR,CSIP);
        F_WCS_TANSIP_GPOS_A_CCDPOSITIONS_T(*APROP,CPROP,PAIR,CSIP);

        double MCBASE=CPROP[APROP->BASISCID].GLOB_POS[2]-APROP->BASIS_POS[2];
        for(ID=0;ID<APROP->CCDNUM;ID++)
        CPROP[ID].GLOB_POS[2]-=MCBASE;

if(CHECKstdout==1){
    cout << "--- GLOB_POS Theta ---\n";
    for(ID=0;ID<APROP->CCDNUM;ID++)
    cout <<"CCD : " << ID << " : T : "<< CPROP[ID].GLOB_POS[2] << endl;
}

        if(Iter==10){
            cout << "T iteration didn't converge" << endl;
            break;
        }

        TCHECK=0;
        for(ID=0;ID<APROP->CCDNUM;ID++)
        if(fabs(CPROPI[ID].GLOB_POS[2]-CPROP[ID].GLOB_POS[2])>pow(10,-5.0))
        TCHECK++;

        if(TCHECK==0){
            cout << "T iteration converged" << endl; 
            break;
        }
    }

    F_WCS_TANSIP_GPOS_CCDPOSITIONS_XY(*APROP,CPROP,PAIR,CSIP);
    F_WCS_TANSIP_GPOS_ALIGN(APROP,CPROP,PAIR,CSIP);

//--------------------------------------------------
    delete [] CPROPI;
}
void    F_WCS_TANSIP_GPOS_LDIFFVALUES(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int CID,NUM,CNUM[APROP.CCDNUM],CoefNUM;
    double ****data,***LCoef,****dLCoef;
    cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : CALCULATING L DIFFERENTIAL VALUES (dxL/dxCRval) ---" << endl;

    CoefNUM=(int)(0.5*(APROP.SIP_L_ORDER+1)*(APROP.SIP_L_ORDER+2)+0.1);
    data = new double***[2];
    data[0] = new double**[APROP.CCDNUM];
    data[1] = new double**[APROP.CCDNUM];
    for(CID=0;CID<APROP.CCDNUM;CID++){
    data[0][CID] = new double*[APROP.NUMREFALL];
    data[1][CID] = new double*[APROP.NUMREFALL];
    }
    for(CID=0;CID<APROP.CCDNUM;CID++)
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        data[0][CID][NUM] = new double[3];
        data[1][CID][NUM] = new double[3];
    }
    LCoef = new double**[2];
    LCoef[0] = new double*[APROP.CCDNUM];
    LCoef[1] = new double*[APROP.CCDNUM];
    for(CID=0;CID<APROP.CCDNUM;CID++){
        LCoef[0][CID] = new double[CoefNUM];
        LCoef[1][CID] = new double[CoefNUM];
    }
    dLCoef = new double***[2];
    dLCoef[0] = new double**[2];
    dLCoef[1] = new double**[2];
    dLCoef[0][0] = new double*[APROP.CCDNUM];
    dLCoef[0][1] = new double*[APROP.CCDNUM];
    dLCoef[1][0] = new double*[APROP.CCDNUM];
    dLCoef[1][1] = new double*[APROP.CCDNUM];
    for(CID=0;CID<APROP.CCDNUM;CID++){
        dLCoef[0][0][CID] = new double[CoefNUM];
        dLCoef[0][1][CID] = new double[CoefNUM];
        dLCoef[1][0][CID] = new double[CoefNUM];
        dLCoef[1][1][CID] = new double[CoefNUM];
    }

//--------------------------------------------------
//Calculating CRval of each CCD 
//CRpix is (0,0)
    for(CID=0;CID<APROP.CCDNUM;CID++)
    CNUM[CID]=0;

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        CID=PAIR[NUM].CHIPID;
        data[0][CID][CNUM[CID]][0]=data[1][CID][CNUM[CID]][0]=PAIR[NUM].xL;
        data[0][CID][CNUM[CID]][1]=data[1][CID][CNUM[CID]][1]=PAIR[NUM].yL;
        data[0][CID][CNUM[CID]][2]=PAIR[NUM].xI;
        data[1][CID][CNUM[CID]][2]=PAIR[NUM].yI;
        CNUM[CID]++;
    }
    for(CID=0;CID<APROP.CCDNUM;CID++){
        F_LS2(CNUM[CID],APROP.SIP_L_ORDER,data[0][CID],LCoef[0][CID]);
        F_LS2(CNUM[CID],APROP.SIP_L_ORDER,data[1][CID],LCoef[1][CID]);
    }

//--------------------------------------------------
//xCRval from xI
//xCRpix is xL
//CD matrix and InvCDmMatrix are unit

    double xL[2];
    for(CID=0;CID<APROP.CCDNUM;CID++){
        CSIP[CID].CD[0][0]=CSIP[CID].CD[1][1]=CSIP[CID].InvCD[0][0]=CSIP[CID].InvCD[1][1]=1;
        CSIP[CID].CD[0][1]=CSIP[CID].CD[1][0]=CSIP[CID].InvCD[0][1]=CSIP[CID].InvCD[1][0]=0;
        CSIP[CID].CRPIX[0]=0;
        CSIP[CID].CRPIX[1]=0;
        xL[0]=xL[1]=0;
        CSIP[CID].CRVAL[0]=F_CALCVALUE(APROP.SIP_L_ORDER,LCoef[0][CID],xL);
        CSIP[CID].CRVAL[1]=F_CALCVALUE(APROP.SIP_L_ORDER,LCoef[1][CID],xL);
//cout << CID << " : " << CSIP[CID].CRVAL[0] << "	" <<CSIP[CID].CRVAL[1] << endl;
    }

    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        CID=PAIR[NUM].CHIPID;
        PAIR[NUM].xCRVAL=PAIR[NUM].xI;
        PAIR[NUM].yCRVAL=PAIR[NUM].yI;
    }//InvCD=unit
//--------------------------------------------------
//PSIP fitting for xL by xCRval
//Differential of PSIP coefficiesnts
//Differential values of xL by xCRval
    for(CID=0;CID<APROP.CCDNUM;CID++)
    CNUM[CID]=0;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        CID=PAIR[NUM].CHIPID;
        data[0][CID][CNUM[CID]][0]=data[1][CID][CNUM[CID]][0]=PAIR[NUM].xCRVAL;
        data[0][CID][CNUM[CID]][1]=data[1][CID][CNUM[CID]][1]=PAIR[NUM].yCRVAL;
        data[0][CID][CNUM[CID]][2]=PAIR[NUM].xL;
        data[1][CID][CNUM[CID]][2]=PAIR[NUM].yL;
        CNUM[CID]++;
    }
    for(CID=0;CID<APROP.CCDNUM;CID++){
        F_LS2(CNUM[CID],APROP.SIP_L_ORDER,data[0][CID],LCoef[0][CID]);
        F_LS2(CNUM[CID],APROP.SIP_L_ORDER,data[1][CID],LCoef[1][CID]);
        F_DIFFSIP(APROP.SIP_L_ORDER,LCoef[0][CID],dLCoef[0][0][CID],dLCoef[0][1][CID]);
        F_DIFFSIP(APROP.SIP_L_ORDER,LCoef[1][CID],dLCoef[1][0][CID],dLCoef[1][1][CID]);
    }

    double xI[2],STdata[2][APROP.NUMREFALL],ST[2][2];
//ofstream out;
//out.open("dtemp.dat");
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        CID=PAIR[NUM].CHIPID;
        xI[0]=PAIR[NUM].xCRVAL;
        xI[1]=PAIR[NUM].yCRVAL;
        STdata[0][NUM]=F_CALCVALUE(APROP.SIP_L_ORDER,LCoef[0][CID],xI) - PAIR[NUM].xL;
        STdata[1][NUM]=F_CALCVALUE(APROP.SIP_L_ORDER,LCoef[1][CID],xI) - PAIR[NUM].yL;

        PAIR[NUM].dxLdxI=F_CALCVALUE(APROP.SIP_L_ORDER,dLCoef[0][0][CID],xI);
        PAIR[NUM].dxLdyI=F_CALCVALUE(APROP.SIP_L_ORDER,dLCoef[0][1][CID],xI);
        PAIR[NUM].dyLdxI=F_CALCVALUE(APROP.SIP_L_ORDER,dLCoef[1][0][CID],xI);
        PAIR[NUM].dyLdyI=F_CALCVALUE(APROP.SIP_L_ORDER,dLCoef[1][1][CID],xI);
//out << NUM << "	" << PAIR[NUM].xI << "	" << PAIR[NUM].yI << "	" << PAIR[NUM].dxLdxI << "	" << PAIR[NUM].dxLdyI << "	" << PAIR[NUM].dyLdxI << "	" << PAIR[NUM].dyLdyI << endl;
    }
    F_RMS(APROP.NUMREFALL,STdata[0],ST[0]);
    F_RMS(APROP.NUMREFALL,STdata[1],ST[1]);

    cout << "LOCAL PSIP FITTING : x : AVE : " << ST[0][0] << " : RMS : " << ST[0][1] << endl;
    cout << "LOCAL PSIP FITTING : y : AVE : " << ST[1][0] << " : RMS : " << ST[1][1] << endl;
    cout << endl;
    
//--------------------------------------------------
    for(CID=0;CID<APROP.CCDNUM;CID++){
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    delete [] data[0][CID][NUM];
    delete [] data[1][CID][NUM];
    }
    delete [] data[0][CID];
    delete [] data[1][CID];
    }
    delete [] data[0];
    delete [] data[1];
    delete [] data;
    for(NUM=0;NUM<APROP.CCDNUM;NUM++){
    delete [] LCoef[0][NUM];
    delete [] LCoef[1][NUM];
    }
    delete [] LCoef[0];
    delete [] LCoef[1];
    delete [] LCoef;
    for(NUM=0;NUM<APROP.CCDNUM;NUM++){
    delete [] dLCoef[0][0][NUM];
    delete [] dLCoef[0][1][NUM];
    delete [] dLCoef[1][0][NUM];
    delete [] dLCoef[1][1][NUM];
    }
    delete [] dLCoef[0][0];
    delete [] dLCoef[0][1];
    delete [] dLCoef[1][0];
    delete [] dLCoef[1][1];
    delete [] dLCoef[0];
    delete [] dLCoef[1];
    delete [] dLCoef;
}
void    F_WCS_TANSIP_GPOS_A_GDIFFVALUES  (CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int NUM,CoefNUM,dCoefNUM;
    double **dGdI[2][2],*dPSIP[2][2];
    double xI[2];
    cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : CALCULATING G DIFFERENTIAL VALUES (dxG/dxCRval) ---" << endl;

     CoefNUM=(int)(0.5*(APROP.SIP_P_ORDER+1  )*(APROP.SIP_P_ORDER+2  )+0.5);
    dCoefNUM=(int)(0.5*(APROP.SIP_P_ORDER+1-1)*(APROP.SIP_P_ORDER+2-1)+0.5);

    dGdI[0][0] = new double*[APROP.NUMREFALL];
    dGdI[0][1] = new double*[APROP.NUMREFALL];
    dGdI[1][0] = new double*[APROP.NUMREFALL];
    dGdI[1][1] = new double*[APROP.NUMREFALL];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    dGdI[0][0][NUM] = new double[3];
    dGdI[0][1][NUM] = new double[3];
    dGdI[1][0][NUM] = new double[3];
    dGdI[1][1][NUM] = new double[3];
    }

    dPSIP[0][0] = new double[dCoefNUM];
    dPSIP[0][1] = new double[dCoefNUM];
    dPSIP[1][0] = new double[dCoefNUM];
    dPSIP[1][1] = new double[dCoefNUM];

//--------------------------------------------------
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
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    delete [] dGdI[0][0][NUM];
    delete [] dGdI[0][1][NUM];
    delete [] dGdI[1][0][NUM];
    delete [] dGdI[1][1][NUM];
    }
    delete [] dGdI[0][0];
    delete [] dGdI[0][1];
    delete [] dGdI[1][0];
    delete [] dGdI[1][1];
    delete [] dPSIP[0][0];
    delete [] dPSIP[0][1];
    delete [] dPSIP[1][0];
    delete [] dPSIP[1][1];
}
void    F_WCS_TANSIP_GPOS_A_CCDPOSITIONS_T(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : DETERMINIG CCD ROTATIONS ---" << endl;
    int i,j,ij,k,l,kl,ID,ID2,NUM,dCoefNUM;
    double *MA,**MB,**InvMB,*MC;
    dCoefNUM=(int)(0.5*(APROP.SIP_P_ORDER+1-1)*(APROP.SIP_P_ORDER+2-1)+0.5);

    MA = new double[APROP.CCDNUM+4*dCoefNUM];
    MB = new double*[APROP.CCDNUM+4*dCoefNUM];
    InvMB = new double*[APROP.CCDNUM+4*dCoefNUM];
    MC = new double[APROP.CCDNUM+4*dCoefNUM];
    for(ID=0;ID<APROP.CCDNUM+4*dCoefNUM;ID++){
    MB[ID] = new double[APROP.CCDNUM+4*dCoefNUM];
    InvMB[ID] = new double[APROP.CCDNUM+4*dCoefNUM];
    MA[ID]=0;
    MC[ID]=0;
    for(ID2=0;ID2<APROP.CCDNUM+4*dCoefNUM;ID2++){
    MB[ID][ID2]=0;
    InvMB[ID][ID2]=0;
    }}
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

/*double TAVE=0;
for(ID=0;ID<APROP.CCDNUM;ID++)
TAVE+=CPROP[ID].GLOB_POS[2];
TAVE/=APROP.CCDNUM;
cout << "TAVE : " << TAVE << endl;
cout << endl;*/
//--------------------------------------------------
    delete [] MA;
    delete [] MC;
    for(ID=0;ID<APROP.CCDNUM+4*dCoefNUM;ID++){
    delete [] MB[ID];
    delete [] InvMB[ID];
    }
    delete [] MB;
    delete [] InvMB;
}
void    F_WCS_TANSIP_GPOS_CCDPOSITIONS_XY(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,NUM,ID,CoefNUM,dCoefNUM;
    double **dGdI[2][2],*dPSIP[2][2];
    double xI[2];

     CoefNUM=(int)(0.5*(APROP.SIP_P_ORDER+1  )*(APROP.SIP_P_ORDER+2  )+0.5);
    dCoefNUM=(int)(0.5*(APROP.SIP_P_ORDER+1-1)*(APROP.SIP_P_ORDER+2-1)+0.5);

    dGdI[0][0] = new double*[APROP.NUMREFALL];
    dGdI[0][1] = new double*[APROP.NUMREFALL];
    dGdI[1][0] = new double*[APROP.NUMREFALL];
    dGdI[1][1] = new double*[APROP.NUMREFALL];
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    dGdI[0][0][NUM] = new double[3];
    dGdI[0][1][NUM] = new double[3];
    dGdI[1][0][NUM] = new double[3];
    dGdI[1][1][NUM] = new double[3];
    }
    dPSIP[0][0] = new double[dCoefNUM];
    dPSIP[0][1] = new double[dCoefNUM];
    dPSIP[1][0] = new double[dCoefNUM];
    dPSIP[1][1] = new double[dCoefNUM];
//--------------------------------------------------
    cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : FITTING DIFFERENTIAL dG ---" << endl;
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
    cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : INTEGRATING DIFFERENTIAL PSIP---" << endl;
    double *PSIP[2];

    PSIP[0] = new double[CoefNUM];
    PSIP[1] = new double[CoefNUM];
    for(i=0;i<CoefNUM;i++)
    PSIP[0][i]=PSIP[1][i]=0;

    F_INTSIP(APROP.SIP_P_ORDER,dPSIP[0][0],dPSIP[0][1],PSIP[0]);
    F_INTSIP(APROP.SIP_P_ORDER,dPSIP[1][0],dPSIP[1][1],PSIP[1]);
//--------------------------------------------------
    cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : DETERMINIG GLOBAL POSITIONS---" << endl;
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
        PAIR[NUM].xG=PAIR[NUM].yG=0;
        xI[0]=PAIR[NUM].xCRVAL;
        xI[1]=PAIR[NUM].yCRVAL;
        PAIR[NUM].xG=F_CALCVALUE(APROP.SIP_P_ORDER,PSIP[0],xI);
        PAIR[NUM].yG=F_CALCVALUE(APROP.SIP_P_ORDER,PSIP[1],xI);
    }
//--------------------------------------------------
    cout << "--- WCS_TANSIP : DETERMINING CCD POSITION : DETERMINIG CCD X AND Y---" << endl;
    double **dX;

    dX = new double*[APROP.CCDNUM];
    for(ID=0;ID<APROP.CCDNUM;ID++){
    dX[ID] = new double[3];
    for(i=0;i<3;i++)
    dX[ID][i] = 0;
    }

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
if(CHECKstdout==1){
    cout << "--- GLOB_POS X and Y ---\n";
    for(ID=0;ID<APROP.CCDNUM;ID++)
    cout <<fixed<< ID << " : " << CPROP[ID].GLOB_POS[0] << "	"  << CPROP[ID].GLOB_POS[1] << endl;
    cout.unsetf(ios::fixed);
}
//--------------------------------------------------
    for(NUM=0;NUM<APROP.NUMREFALL;NUM++){
    delete [] dGdI[0][0][NUM];
    delete [] dGdI[0][1][NUM];
    delete [] dGdI[1][0][NUM];
    delete [] dGdI[1][1][NUM];
    }
    delete [] dGdI[0][0];
    delete [] dGdI[0][1];
    delete [] dGdI[1][0];
    delete [] dGdI[1][1];
    delete [] dPSIP[0][0];
    delete [] dPSIP[0][1];
    delete [] dPSIP[1][0];
    delete [] dPSIP[1][1];
    delete [] PSIP[0];
    delete [] PSIP[1];
}
#define PI (4*atan(1.0))
void    F_WCS_TANSIP_GPOS_ALIGN(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,ID,NM,*NMNUM;
    double **NMSET,NMCOEF[2],NMAVE[2]={0};
    double AC;

    NMNUM = new int[APROP->CCDNUM];
    for(NM=0;NM<APROP->CCDNUM;NM++)
    NMNUM[NM]=0;
    NMSET = new double*[APROP->CCDNUM];
    for(NM=0;NM<APROP->CCDNUM;NM++)
    NMSET[NM] = new double[2];
//--------------------------------------------------

    if(APROP->ALIGNAXIS==1){
        cout << "Align Y axis" << endl;
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
        cout << "Align X axis" << endl;
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
if(CHECKstdout==1)
    cout << "Angle correction : "<< AC << endl;

//--------------------------------------------------
    double X[2];
    cout << "CCD GLOBAL POSITION : " << endl;
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
    APROP->CRPIX[0]-=X[0];
    APROP->CRPIX[1]-=X[1];
    cout << "NEW CRPIX : ( " << APROP->CRPIX[0] << " , " << APROP->CRPIX[1] << " )" << endl;
    
    for(ID=0;ID<APROP->CCDNUM;ID++)
    cout <<fixed<< ID << " : X : " <<CPROP[ID].GLOB_POS[0] << "	: Y : " <<CPROP[ID].GLOB_POS[1] << "	: T : " <<scientific<<CPROP[ID].GLOB_POS[2] << "	: T : " <<fixed<<CPROP[ID].GLOB_POS[2]*180/PI << endl;
    cout.unsetf(ios::scientific);
    cout << endl;
//--------------------------------------------------
    delete [] NMNUM;
    for(NM=0;NM<APROP->CCDNUM;NM++)
    delete [] NMSET[NM];
}
#undef PI
