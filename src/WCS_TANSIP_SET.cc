//------------------------------------------------------------
//WCS_TANSIP_SET.cc
//Checking and setting parameters
//
//Last modification : 2010/04/01
//------------------------------------------------------------
#include<iostream>
#include<cmath>
#include<string.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
void    F_WCS_TANSIP_SET(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int CID,CID2,NUM;

//CHECKING PARAM
    cout << "--- WCS_TANSIP : SET : CHEKING PARAMERTERS---" << endl;
    APROP->CHECKPARAM=0;

    if(strcmp(APROP->CRPIXMODE,"AUTO")==0||strcmp(APROP->CRPIXMODE,"PIX")==0||strcmp(APROP->CRPIXMODE,"VAL")==0){
    }else{
        cout << "CRPIXMODE is " << APROP->CRPIXMODE << endl;
        cout << "Error : CRPIXMODE must be 'AUTO' or 'PIX' or 'VAL'" << endl;
        APROP->CHECKPARAM=1;
    }
    if(APROP->SIP_ORDER<0.5||APROP->SIP_ORDER>9.5){
        cout << "SIPORDER is " << APROP->SIP_ORDER << endl;
        cout << "Error : you must select from between 1 to 9 for SIPORDER" << endl;
        APROP->CHECKPARAM=1;
    }
    if(APROP->SIP_P_ORDER<0.5||APROP->SIP_P_ORDER>9.5){
        cout << "PSIP_ORDER is " << APROP->SIP_P_ORDER << endl;
        cout << "Error : you must select from between 1 to 9 for PSIPORDER" << endl;
        APROP->CHECKPARAM=1;
    }
    if(APROP->SIP_L_ORDER<0.5||APROP->SIP_L_ORDER>9.5){
        cout << "LSIP_ORDER is " << APROP->SIP_L_ORDER << endl;
        cout << "Error : you must select from between 1 to 9 for LSIPORDER" << endl;
        APROP->CHECKPARAM=1;
    }
    for(CID=0;CID<APROP->CCDNUM;CID++)
    for(CID2=CID+1;CID2<APROP->CCDNUM;CID2++)
    if(hypot(CPROP[CID].GLOB_POS[0]-CPROP[CID2].GLOB_POS[0],CPROP[CID].GLOB_POS[1]-CPROP[CID2].GLOB_POS[1])<2000){
        cout << "CID ;  " << CID << " : GLOB_POS x : " << CPROP[CID].GLOB_POS[0] << " : GLOB_POS y : " << CPROP[CID].GLOB_POS[1] << endl;
        cout << "CID ;  " << CID2 << " : GLOB_POS x : " << CPROP[CID2].GLOB_POS[0] << " : GLOB_POS y : " << CPROP[CID2].GLOB_POS[1] << endl;
        cout << "Error : Separation between CHIPID : " << CID << " and " << CID2 << " is under 2000" << endl;
        APROP->CHECKPARAM=1;
    }
    int ALIGNNUM=0;
    for(CID=0;CID<APROP->CCDNUM;CID++)
    if(CPROP[CID].ALIGN==1)
    ALIGNNUM++;
    if(ALIGNNUM<2){
    cout << endl << "--------------------------------------------------" << endl;
    cout << "Warning : in F_WCS_TANSIP_SET : CPROP[].ALIGN" << endl;
    cout << "          Number of CCDs used for CCD alignment is under 2" << endl;
    cout << "          Using 000 - 009 CCDs for CCD alignment" << endl;
    cout << "--------------------------------------------------" << endl<< endl ;
    CPROP[0].ALIGN=CPROP[1].ALIGN=CPROP[2].ALIGN=CPROP[3].ALIGN=CPROP[4].ALIGN=CPROP[5].ALIGN=CPROP[6].ALIGN=CPROP[7].ALIGN=CPROP[8].ALIGN=CPROP[9].ALIGN=1;
    }
//SET INITIAL
    cout << "--- WCS_TANSIP : SET : SETTING INITAL VALUES---" << endl;
    for(CID=0;CID<APROP->CCDNUM;CID++){
    CPROP[CID].GLOB_POS_Init[0]=CPROP[CID].GLOB_POS[0];
    CPROP[CID].GLOB_POS_Init[1]=CPROP[CID].GLOB_POS[1];
    CPROP[CID].GLOB_POS_Init[2]=CPROP[CID].GLOB_POS[2];
    }
    for(NUM=0;NUM<APROP->NUMREFALL;NUM++){
        PAIR[NUM].xG_Init=PAIR[NUM].xG=CPROP[PAIR[NUM].CHIPID].GLOB_POS[0]+PAIR[NUM].xL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])-PAIR[NUM].yL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
        PAIR[NUM].yG_Init=PAIR[NUM].yG=CPROP[PAIR[NUM].CHIPID].GLOB_POS[1]+PAIR[NUM].yL*cos(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2])+PAIR[NUM].xL*sin(CPROP[PAIR[NUM].CHIPID].GLOB_POS[2]);
    }
}
