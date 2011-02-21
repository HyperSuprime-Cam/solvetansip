//------------------------------------------------------------
//WCS_SETCC.cc
//for program development
//
//Last modification : 2010/09/15
//------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include "WCS_PROP.h"

using namespace::std;
void    F_WCS_SETCC_APROPfromFILE(char *APROPFILE,CL_APROP *APROP){
// APROP  --------------------------------------------------
    cout << endl << "--- SET APROP ---" << endl;
    cout << "APROPFILENAME : " << APROPFILE << endl;

    int i,j;
    char ***KEYVALUE;

    KEYVALUE = new char**[20];
    for(i=0;i<20;i++){
    KEYVALUE[i] = new char*[2];
    for(j=0;j<2;j++)
    KEYVALUE[i][j] = new char[101];
    }
//----------

    strcpy(KEYVALUE[0][0],"CRPIXMODE:");
    strcpy(KEYVALUE[1][0],"CRPIX1   :");
    strcpy(KEYVALUE[2][0],"CRPIX2   :");
    strcpy(KEYVALUE[3][0],"LSIPORDER:");
    strcpy(KEYVALUE[4][0],"SIPORDER :");
    strcpy(KEYVALUE[5][0],"PSIPORDER:");
    strcpy(KEYVALUE[6][0],"CLIPSIGMA:");
    strcpy(KEYVALUE[7][0],"CHECKFILE:");
    strcpy(KEYVALUE[8][0],"NCCD     :");

    F_GETKEYVALUE10(9,KEYVALUE,APROPFILE);
    
    strcpy(APROP->CRPIXMODE,KEYVALUE[0][1]);
    APROP->CRPIX[0]   =atof(KEYVALUE[1][1]);
    APROP->CRPIX[1]   =atof(KEYVALUE[2][1]);
    APROP->SIP_L_ORDER=atoi(KEYVALUE[3][1]);
    APROP->SIP_ORDER  =atoi(KEYVALUE[4][1]);
    APROP->SIP_P_ORDER=atoi(KEYVALUE[5][1]);
    APROP->CLIP_SIGMA =atof(KEYVALUE[6][1]);	
    APROP->CHECKFILE  =atoi(KEYVALUE[7][1]);	
    APROP->CCDNUM     =atoi(KEYVALUE[8][1]);	

cout << "CRPIXMODE	:" << APROP->CRPIXMODE << endl;
cout << "CCDNUM		:" << APROP->CCDNUM << endl;
cout << "CRPIXX(MANUAL)	:" << APROP->CRPIX[0] << endl;
cout << "CRPIXY(MANUAL)	:" << APROP->CRPIX[1] << endl;
cout << "SIP ABL ORDER 	:" << APROP->SIP_L_ORDER << endl;
cout << "SIP AB ORDER 	:" << APROP->SIP_ORDER << endl;
cout << "SIP ABP ORDER 	:" << APROP->SIP_P_ORDER << endl;
cout << "CLIPPING SIGMA	:" << APROP->CLIP_SIGMA << endl;
cout << "CHECK FILE	:" << APROP->CHECKFILE << endl;
//----------
    for(i=0;i<20;i++)
    for(j=0;j<2;j++)
    delete [] KEYVALUE[i][j];
    for(i=0;i<20;i++)
    delete [] KEYVALUE[i];
    delete [] KEYVALUE;
}
void    F_WCS_SETCC_CPROPfromFILE(char *CPROPFILE,CL_CPROP *CPROP){
// CPROP --------------------------------------------------
    cout << endl << "--- SET CPROP ---" << endl;
    cout << "CPROPFILENAME : " << CPROPFILE << endl;

    int i,PHASE,ID;
    double X[3];
    ifstream fin;
    fin.open(CPROPFILE);
    if(!fin){
        cout << "ERROR : Can't read " << CPROPFILE << endl;
        return;
    }
    while((fin >> ID >> X[0] >> X[1] >> X[2] >> PHASE) !=0){
        CPROP[ID].ID=ID;
        CPROP[ID].GLOB_POS[0]=X[0];
        CPROP[ID].GLOB_POS[1]=X[1];
        CPROP[ID].GLOB_POS[2]=X[2];
        CPROP[ID].PHASE=PHASE;
//cout << "ID: " << CPROP[ID].ID << " X: " << CPROP[ID].GLOB_POS[0] << " Y: " << CPROP[ID].GLOB_POS[1] << " T: " << CPROP[ID].GLOB_POS[2] << " P: " << CPROP[ID].PHASE << endl;
    }
cout << "ID: " << CPROP[0].ID << " X: " << CPROP[0].GLOB_POS[0] << " Y: " << CPROP[0].GLOB_POS[1] << " T: " << CPROP[0].GLOB_POS[2] << " P: " << CPROP[0].PHASE << endl;
cout << "ID: " << CPROP[9].ID << " X: " << CPROP[9].GLOB_POS[0] << " Y: " << CPROP[9].GLOB_POS[1] << " T: " << CPROP[9].GLOB_POS[2] << " P: " << CPROP[9].PHASE << endl;
    fin.close();    
}
void    F_WCS_SETCC_PAIRSIZEfromFILE (CL_APROP *APROP,CL_CPROP *CPROP,char *PAIRFILE){
    cout << endl << "--- SET PAIRSIZE  ---" << endl;
    cout << "PAIRFILENAME  : " <<  PAIRFILE << endl;

    int i,ID,CID;
    double X,Y,RA,DEC;
    ifstream fin;

    for(i=0;i<APROP->CCDNUM;i++)
    CPROP[i].NUMREF=0;
    APROP->NUMREFALL=0;

    fin.open(PAIRFILE);
    while((fin >> ID >> CID >> X >> Y >> RA >> DEC) != 0){
        CPROP[CID].NUMREF+=1;
	APROP->NUMREFALL+=1;
    }
    fin.close();
cout << "NUMREFALL : " << APROP->NUMREFALL << endl;
    
}
#define PI (4*atan(1.0))
void    F_WCS_SETCC_PAIRfromFILE (char *PAIRFILE,CL_CPROP *CPROP,CL_PAIR *PAIR){
    cout << endl << "--- SET PAIR  ---" << endl;
    cout << "PAIRFILENAME  : " <<  PAIRFILE << endl;

    int i,ID,CID;
    double X,Y,RA,DEC;
    ifstream fin;

    fin.open(PAIRFILE);
    i=0;
    while((fin >> ID >> CID >> X >> Y >> RA >> DEC) != 0){
        PAIR[i].ID=ID;
        PAIR[i].CHIPID=CID;
        PAIR[i].FLAG=1;
        PAIR[i].xL=X;
        PAIR[i].yL=Y;
        PAIR[i].xG=CPROP[CID].GLOB_POS[0]+X*cos(CPROP[CID].GLOB_POS[2]/180.0*PI)-Y*sin(CPROP[CID].GLOB_POS[2]/180.0*PI);
        PAIR[i].yG=CPROP[CID].GLOB_POS[1]+X*sin(CPROP[CID].GLOB_POS[2]/180.0*PI)+Y*cos(CPROP[CID].GLOB_POS[2]/180.0*PI);
        PAIR[i].RA=RA;
        PAIR[i].DEC=DEC;
        i++;
    }

}  
void    F_WCS_SETCC_CPROPINITSC(CL_CPROP *CPROP){
    CPROP[0].GLOB_POS[0]=-5250.0;
    CPROP[0].GLOB_POS[1]=    0.0;
    CPROP[0].GLOB_POS[2]=  0.000;
    CPROP[1].GLOB_POS[0]= 3150.0;
    CPROP[1].GLOB_POS[1]=-4200.0;
    CPROP[1].GLOB_POS[2]=  0.000;
    CPROP[2].GLOB_POS[0]=-3150.0;
    CPROP[2].GLOB_POS[1]=    0.0;
    CPROP[2].GLOB_POS[2]=  0.000;
    CPROP[3].GLOB_POS[0]= 1050.0;
    CPROP[3].GLOB_POS[1]=-4200.0;
    CPROP[3].GLOB_POS[2]=  0.000;
    CPROP[4].GLOB_POS[0]=-1050.0;
    CPROP[4].GLOB_POS[1]=    0.0;
    CPROP[4].GLOB_POS[2]=  0.000;
    CPROP[5].GLOB_POS[0]=-1050.0;
    CPROP[5].GLOB_POS[1]=-4200.0;
    CPROP[5].GLOB_POS[2]=  0.000;
    CPROP[6].GLOB_POS[0]= 1050.0;
    CPROP[6].GLOB_POS[1]=    0.0;
    CPROP[6].GLOB_POS[2]=  0.000;
    CPROP[7].GLOB_POS[0]=-3150.0;
    CPROP[7].GLOB_POS[1]=-4200.0;
    CPROP[7].GLOB_POS[2]=  0.000;
    CPROP[8].GLOB_POS[0]= 3150.0;
    CPROP[8].GLOB_POS[1]=    0.0;
    CPROP[8].GLOB_POS[2]=  0.000;
    CPROP[9].GLOB_POS[0]=-5250.0;
    CPROP[9].GLOB_POS[1]=-4200.0;
    CPROP[9].GLOB_POS[2]=  0.000;
}
void    F_WCS_SETCC_CPROPINIT2(CL_CPROP *CPROP){
/*2
    CPROP[0].GLOB_POS[0]=-1050.0;
    CPROP[0].GLOB_POS[1]=    0.0;
    CPROP[0].GLOB_POS[2]=  0.000;
    CPROP[1].GLOB_POS[0]=-1050.5;
    CPROP[1].GLOB_POS[1]=-4200.5;
    CPROP[1].GLOB_POS[2]= 0.0150;//*35->pix
*/
///*SC
    CPROP[0].GLOB_POS[0]=-5250.5;
    CPROP[0].GLOB_POS[1]=    0.0;
    CPROP[0].GLOB_POS[2]=( 1.0)*0.0001*180/PI;//*2200->pix
    CPROP[1].GLOB_POS[0]= 3150.0;
    CPROP[1].GLOB_POS[1]=-4200.5;
    CPROP[1].GLOB_POS[2]=( 2.0)*0.0001*180/PI;//=0.006*n
    CPROP[2].GLOB_POS[0]=-3150.5;
    CPROP[2].GLOB_POS[1]=    0.5;
    CPROP[2].GLOB_POS[2]=(-1.0)*0.0001*180/PI;
    CPROP[3].GLOB_POS[0]= 1050.5;
    CPROP[3].GLOB_POS[1]=-4200.0;
    CPROP[3].GLOB_POS[2]=( 0.5)*0.0001*180/PI;
    CPROP[4].GLOB_POS[0]=-1051.0;
    CPROP[4].GLOB_POS[1]=    1.0;
    CPROP[4].GLOB_POS[2]=( 1.0)*0.0001*180/PI;
    CPROP[5].GLOB_POS[0]=-1050.0;
    CPROP[5].GLOB_POS[1]=-4200.0;
    CPROP[5].GLOB_POS[2]=( 0.0)*0.0001*180/PI;
    CPROP[6].GLOB_POS[0]= 1050.0;
    CPROP[6].GLOB_POS[1]=    0.5;
    CPROP[6].GLOB_POS[2]=(-1.5)*0.0001*180/PI;
    CPROP[7].GLOB_POS[0]=-3150.5;
    CPROP[7].GLOB_POS[1]=-4200.5;
    CPROP[7].GLOB_POS[2]=( 0.0)*0.0001*180/PI;
    CPROP[8].GLOB_POS[0]= 3150.5;
    CPROP[8].GLOB_POS[1]=    0.0;
    CPROP[8].GLOB_POS[2]=(-2.0)*0.0001*180/PI;
    CPROP[9].GLOB_POS[0]=-5250.0;
    CPROP[9].GLOB_POS[1]=-4200.5;
    CPROP[9].GLOB_POS[2]=( 0.5)*0.0001*180/PI;
//*/
}
#undef PI
