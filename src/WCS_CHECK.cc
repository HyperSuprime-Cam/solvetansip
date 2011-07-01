//------------------------------------------------------------
//WCS_CHECK.cc
//checking wsc results
//
//Last modification : 2011/06/20
//------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include "hsc/meas/tansip/WCS_CHECK.h"

using namespace std;
void    F_GETKEYVALUE10(int KEYNUM,char ***KEYVALUE,char *FILENAME);
void    F_GETKEYVALUE14(int KEYNUM,char ***KEYVALUE,char *FILENAME);
void    F_WCS_CHECK_GETPOSITION(CL_APROP* ,CL_CPROP*);
void    F_WCS_CHECK_DIFFPOSITION(int NUMBER,CL_APROP* ,CL_CPROP*,CL_CPROP*);
void    F_WCS_CHECK_GETDISTORTION(CL_CSIP*);
void    F_WCS_CHECK_DIFFDISTORTION(int,double*,CL_CSIP*,CL_CSIP*);
void    F_WCS_CHECK_CCDPOSITION_SC(int NUMBER,CL_APROP* APROP,CL_CPROP* CPROPRESULT){
    cout << "--- solvetansip : CCDPOSITIONCHECK ---" << endl;

    CL_CPROP* CPROPCHECK;
    CPROPCHECK = new CL_CPROP[APROP->CCDNUM];
    F_WCS_CHECK_GETPOSITION(APROP,CPROPCHECK);

//--------------------------------------------------
    int ID;
    cout << "Results" << endl;
    for(ID=0;ID<APROP->CCDNUM;ID++)
    cout << ID << "	" << CPROPRESULT[ID].GLOB_POS[0] << "	" << CPROPRESULT[ID].GLOB_POS[1] << "	" << CPROPRESULT[ID].GLOB_POS[2] << endl;
    cout << "Check" << endl;
    for(ID=0;ID<APROP->CCDNUM;ID++)
    cout << ID << "	" << CPROPCHECK[ID].GLOB_POS[0] << "	" << CPROPCHECK[ID].GLOB_POS[1] << "	" << CPROPCHECK[ID].GLOB_POS[2] << endl;

    F_WCS_CHECK_DIFFPOSITION(NUMBER,APROP,CPROPRESULT,CPROPCHECK);
//--------------------------------------------------
    delete [] CPROPCHECK;
}
void    F_WCS_CHECK_GETPOSITION(CL_APROP* APROP,CL_CPROP* CPROP){
    int i,j;
    char ***KEY;
    char Policy[100];

    KEY = F_NEWchar3(3*APROP->CCDNUM,2,100);
    for(i=0;i<APROP->CCDNUM;i++){
    sprintf(KEY[3*i+0][0],"CCD%03d_X :",i);
    sprintf(KEY[3*i+1][0],"CCD%03d_Y :",i);
    sprintf(KEY[3*i+2][0],"CCD%03d_T :",i);
    }
    sprintf(Policy,"../policy/WCS_CCDCHECK_SC.paf");
    
    F_GETKEYVALUE10(3*APROP->CCDNUM,KEY,Policy);

    for(i=0;i<APROP->CCDNUM;i++)
    for(j=0;j<3;j++)
    CPROP[i].GLOB_POS[j]=atof(KEY[3*i+j][1]);

    F_DELchar3(3*APROP->CCDNUM,2,KEY);
}
void    F_WCS_CHECK_DIFFPOSITION(int NUMBER,CL_APROP* APROP,CL_CPROP* CPROPRESULT,CL_CPROP* CPROPCHECK){
    int ID;
    double xL[2];
    double xGR[2],xGC[2];
    char fCout[100],fRout[100],fGout[100];
    ofstream POSCHECKout,POSRESULTout,POSGLOBALout;

    sprintf(fCout,"POSCHECK_%05d.dat" ,NUMBER);
    sprintf(fRout,"POSRESULT_%05d.dat",NUMBER);
    sprintf(fGout,"POSGLOBAL_%05d.dat",NUMBER);
    POSCHECKout.open(fCout);
    POSRESULTout.open(fRout);
    POSGLOBALout.open(fGout);

    xL[0]=1024;
    xL[1]=2048;
    for(ID=0;ID<APROP->CCDNUM;ID++){
        xGR[0]=CPROPRESULT[ID].GLOB_POS[0]+xL[0]*cos(CPROPRESULT[ID].GLOB_POS[2])-xL[1]*sin(CPROPRESULT[ID].GLOB_POS[2]);
        xGR[1]=CPROPRESULT[ID].GLOB_POS[1]+xL[1]*cos(CPROPRESULT[ID].GLOB_POS[2])+xL[0]*sin(CPROPRESULT[ID].GLOB_POS[2]);
        xGC[0]= CPROPCHECK[ID].GLOB_POS[0]+xL[0]*cos( CPROPCHECK[ID].GLOB_POS[2])-xL[1]*sin( CPROPCHECK[ID].GLOB_POS[2]);
        xGC[1]= CPROPCHECK[ID].GLOB_POS[1]+xL[1]*cos( CPROPCHECK[ID].GLOB_POS[2])+xL[0]*sin( CPROPCHECK[ID].GLOB_POS[2]);
POSCHECKout << ID << "	" << xL[0] << "	" << xL[1] << "	" << xGR[0] << "	" << xGR[1] << "	" << CPROPRESULT[ID].GLOB_POS[2] << "	" << xGC[0] << "	" << xGC[1] << "	" << CPROPCHECK[ID].GLOB_POS[2] << endl;
POSRESULTout  << xGR[0] << "	" << xGR[1] << "	" << CPROPRESULT[ID].GLOB_POS[2] << "	" ;
     }
POSRESULTout << endl;

    for(xL[0]=0;xL[0]<2048+1;xL[0]+=512)
    for(xL[1]=0;xL[1]<4096+1;xL[1]+=512)
    for(ID=0;ID<APROP->CCDNUM;ID++){
        xGR[0]=CPROPRESULT[ID].GLOB_POS[0]+xL[0]*cos(CPROPRESULT[ID].GLOB_POS[2])-xL[1]*sin(CPROPRESULT[ID].GLOB_POS[2]);
        xGR[1]=CPROPRESULT[ID].GLOB_POS[1]+xL[1]*cos(CPROPRESULT[ID].GLOB_POS[2])+xL[0]*sin(CPROPRESULT[ID].GLOB_POS[2]);
        xGC[0]= CPROPCHECK[ID].GLOB_POS[0]+xL[0]*cos( CPROPCHECK[ID].GLOB_POS[2])-xL[1]*sin( CPROPCHECK[ID].GLOB_POS[2]);
        xGC[1]= CPROPCHECK[ID].GLOB_POS[1]+xL[1]*cos( CPROPCHECK[ID].GLOB_POS[2])+xL[0]*sin( CPROPCHECK[ID].GLOB_POS[2]);
POSGLOBALout << ID << "	" << xL[0] << "	" << xL[1] << "	" << xGR[0] << "	" << xGR[1] << "	" << CPROPRESULT[ID].GLOB_POS[2] << "	" << xGC[0] << "	" << xGC[1] << "	" << CPROPCHECK[ID].GLOB_POS[2] << endl;
     }
}
void    F_WCS_CHECK_OADISTORTION_SC(int NUMBER,double ANGLE,CL_APROP* APROP,CL_CPROP* CPROP,CL_CSIP* CSIP){
    cout << "--- solvetansip : OADISTORTIONCHECK ---" << endl;
    double ROT[3];

    CL_CSIP* CSIPCHECK;
    CSIPCHECK = new CL_CSIP[1];
//--------------------------------------------------
    F_WCS_CHECK_GETDISTORTION(CSIPCHECK);

//ROTATION : ROTATING RESULT WITH ROT[](POSITION AND ANGLE) (-ANGLE???)
    ROT[0]=CSIP[APROP->CCDNUM].OAPIX[0];//Rotation Centor X
    ROT[1]=CSIP[APROP->CCDNUM].OAPIX[1];//Rotation Centor Y
    ROT[2]=ANGLE;//Rotation ANGLE
//    ROT[2]=0.5*3.14159265;//Rotation ANGLE

    F_WCS_CHECK_DIFFDISTORTION(NUMBER,ROT,CSIP,CSIPCHECK);

////--------------------------------------------------
  //  F_DELdouble1(CSIPCHECK->SIP_AB[0]);
    //F_DELdouble1(CSIPCHECK->SIP_AB[1]);
    delete [] CSIPCHECK;
}
void    F_WCS_CHECK_GETDISTORTION(CL_CSIP* CSIP){

    int i,j,ij;
    double A[10][10],B[10][10];
    char ***KEY;
    char Policy[100];

    KEY = F_NEWchar3(120,2,100);
    sprintf(KEY[0][0],"ORDER    :");
    sprintf(KEY[1][0],"CRPIX1   :");
    sprintf(KEY[2][0],"CRPIX2   :");
    sprintf(KEY[3][0],"SS_0_0   :");
    sprintf(KEY[4][0],"SS_0_1   :");
    sprintf(KEY[5][0],"SS_1_0   :");
    sprintf(KEY[6][0],"SS_1_1   :");
    ij=7;
    for(i=0;i<10;i++)
    for(j=0;j<10;j++)
    if(i+j<10){
        sprintf(KEY[ij][0],"A_%d_%d    :",i,j);
        ij++;
    }
    for(i=0;i<10;i++)
    for(j=0;j<10;j++)
    if(i+j<10){
        sprintf(KEY[ij][0],"B_%d_%d    :",i,j);
        ij++;
    }

    sprintf(Policy,"../policy/WCS_DISTCHECK_SC.paf");
    
    F_GETKEYVALUE14(ij,KEY,Policy);

    CSIP->SIP_AB_ORDER = atoi(KEY[0][1]);
    CSIP->CRPIX[0]     = atof(KEY[1][1]);
    CSIP->CRPIX[1]     = atof(KEY[2][1]);
    CSIP->CD[0][0]     = atof(KEY[3][1]);
    CSIP->CD[0][1]     = atof(KEY[4][1]);
    CSIP->CD[1][0]     = atof(KEY[5][1]);
    CSIP->CD[1][1]     = atof(KEY[6][1]);

    ij=7;
    for(i=0;i<10;i++)
    for(j=0;j<10;j++)
    if(i+j<10)
    A[i][j]=atof(KEY[ij++][1]);

    for(i=0;i<10;i++)
    for(j=0;j<10;j++)
    if(i+j<10)
    B[i][j]=atof(KEY[ij++][1]);

    CSIP->SIP_AB[0] = F_NEWdouble1((CSIP->SIP_AB_ORDER+1)*(CSIP->SIP_AB_ORDER+2));
    CSIP->SIP_AB[1] = F_NEWdouble1((CSIP->SIP_AB_ORDER+1)*(CSIP->SIP_AB_ORDER+2));

    ij=0;
    for(i=0;i<CSIP->SIP_AB_ORDER+1 ;i++)
    for(j=0;j<CSIP->SIP_AB_ORDER+1 ;j++)
    if(i+j<CSIP->SIP_AB_ORDER +1){
        CSIP->SIP_AB[0][ij]=A[i][j];
        ij++;
    }
    ij=0;
    for(i=0;i<CSIP->SIP_AB_ORDER+1 ;i++)
    for(j=0;j<CSIP->SIP_AB_ORDER+1 ;j++)
    if(i+j<CSIP->SIP_AB_ORDER +1){
        CSIP->SIP_AB[1][ij]=B[i][j];
        ij++;
    }

    F_DELchar3(120,2,KEY);
}
void    F_WCS_CHECK_DIFFDISTORTION(int NUMBER,double *ROT,CL_CSIP* CSIPRESULT,CL_CSIP* CSIPCHECK){
    double ixC[2];
    double ixR[2];
    double DIST[2],DISTRESULT[2],DISTCHECK[2];
    double OA[2],SIPOA[2];
    double SS[2][2],T,TM[2][2];
    char fout[100];

ofstream DISTCHECKout;
sprintf(fout,"DISTCHECK_%05d.dat",NUMBER);
DISTCHECKout.open(fout);

    T=atan2(CSIPRESULT->CD[1][0]-(-CSIPRESULT->CD[0][1]),(-CSIPRESULT->CD[0][0])+CSIPRESULT->CD[1][1]);
    cout << "CD rotation : " << T << endl;
    TM[0][0]= cos(-T);
    TM[0][1]=-sin(-T);
    TM[1][0]= sin(-T);
    TM[1][1]= cos(-T);
    SS[0][0]=-(TM[0][0]*(-CSIPRESULT->CD[0][0])+TM[0][1]*CSIPRESULT->CD[1][0]);
    SS[0][1]=-(TM[0][0]*(-CSIPRESULT->CD[0][1])+TM[0][1]*CSIPRESULT->CD[1][1]);
    SS[1][0]= (TM[1][0]*(-CSIPRESULT->CD[0][0])+TM[1][1]*CSIPRESULT->CD[1][0]);
    SS[1][1]= (TM[1][0]*(-CSIPRESULT->CD[0][1])+TM[1][1]*CSIPRESULT->CD[1][1]);
    cout << "SS_1_1 : " << SS[0][0] << endl;
    cout << "SS_1_2 : " << SS[0][1] << endl;
    cout << "SS_2_1 : " << SS[1][0] << endl;
    cout << "SS_2_2 : " << SS[1][1] << endl;

    OA[0]=ROT[0];
    OA[1]=ROT[1];
    SIPOA[0] = F_CALCVALUE(CSIPRESULT->SIP_AB_ORDER,CSIPRESULT->SIP_AB[0],OA)+OA[0];
    SIPOA[1] = F_CALCVALUE(CSIPRESULT->SIP_AB_ORDER,CSIPRESULT->SIP_AB[1],OA)+OA[1];
    DIST[0]  = 3600*( SS[0][0]*SIPOA[0]+SS[0][1]*SIPOA[1]);
    DIST[1]  = 3600*( SS[1][0]*SIPOA[0]+SS[1][1]*SIPOA[1]);
    SIPOA[0] = DIST[0]*cos(-ROT[2]) - DIST[1]*sin(-ROT[2]);
    SIPOA[1] = DIST[0]*sin(-ROT[2]) + DIST[1]*cos(-ROT[2]);

    

    for(ixC[0]=-5000;ixC[0]<5001;ixC[0]+=500)
    for(ixC[1]=-4000;ixC[1]<4001;ixC[1]+=500){
        ixR[0] = (ixC[0])*cos(-ROT[2]) - (ixC[1])*sin(-ROT[2]) + ROT[0];
        ixR[1] = (ixC[0])*sin(-ROT[2]) + (ixC[1])*cos(-ROT[2]) + ROT[1];
        
        DIST[0]=F_CALCVALUE(CSIPCHECK->SIP_AB_ORDER,CSIPCHECK->SIP_AB[0],ixC)+ixC[0];
        DIST[1]=F_CALCVALUE(CSIPCHECK->SIP_AB_ORDER,CSIPCHECK->SIP_AB[1],ixC)+ixC[1];
        DISTCHECK[0]=3600*( CSIPCHECK->CD[0][0]*DIST[0]+CSIPCHECK->CD[0][1]*DIST[1]);
        DISTCHECK[1]=3600*( CSIPCHECK->CD[1][0]*DIST[0]+CSIPCHECK->CD[1][1]*DIST[1]);

        DISTRESULT[0]=F_CALCVALUE(CSIPRESULT->SIP_AB_ORDER,CSIPRESULT->SIP_AB[0],ixR)+ixR[0];
        DISTRESULT[1]=F_CALCVALUE(CSIPRESULT->SIP_AB_ORDER,CSIPRESULT->SIP_AB[1],ixR)+ixR[1];
        DIST[0]=3600*( SS[0][0]*DISTRESULT[0]+SS[0][1]*DISTRESULT[1]);
        DIST[1]=3600*( SS[1][0]*DISTRESULT[0]+SS[1][1]*DISTRESULT[1]);
        DISTRESULT[0] = DIST[0]*cos(-ROT[2]) - DIST[1]*sin(-ROT[2]) - SIPOA[0];
        DISTRESULT[1] = DIST[0]*sin(-ROT[2]) + DIST[1]*cos(-ROT[2]) - SIPOA[1];

DISTCHECKout <<scientific<< ixC[0] << "	" << ixC[1] << "	" << DISTRESULT[0] << "	" << DISTRESULT[1] << "	" << DISTCHECK[0] << "	" << DISTCHECK[1] << endl;
    }

}
void    F_WCS_CHECK_OAPOSITION_SC(int NUMBER,CL_APROP* APROP,CL_CPROP* CPROP,CL_CSIP* CSIP){
    cout << "--- solvetansip : OAPOSITIONCHECK ---" << endl;
    char fout[100];

ofstream OACHECKout;
sprintf(fout,"OAPOSCHECK_%05d.dat",NUMBER);
OACHECKout.open(fout);

    OACHECKout << CSIP[APROP->CCDNUM].OAPIX[0] << "	 " << CSIP[APROP->CCDNUM].OAPIX[1] << endl;
}
