//------------------------------------------------------------
//WCS_TANSIP.cc
//main program for wcs in pipeline
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#include<iostream>
#include<cmath>
#include<string.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;

void    F_WCSA_TANSIP(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
//cout << "APROP->STDOUT : " << APROP->STDOUT << endl;
//APROP->STDOUT=2;
//cout << "CHANGE APROP->STDOUT TO 2" << endl; 
clock_t T1,T2,TS,TE;
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--------------------------------------------------" << endl;
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP ---" << endl;
TS=clock();
T1=clock();
//--------------------------------------------------
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : SET ---" << endl;
        F_WCSA_TANSIP_SET_APROP(APROP,APAIR,GSIP);
        F_WCSA_TANSIP_SET_GSIP (APROP,APAIR,GSIP);
        F_WCSA_TANSIP_SET_APAIR(APROP,APAIR,GSIP);
        APAIR->F_WCSA_APAIR_CENTERofOBJECTS();
T2=clock();
if(APROP->STDOUT==2)cout << "SOLVETANSIP SET TIME : " << (T2-T1)/CLOCKS_PER_SEC << " (sec)" <<endl;


    if(APROP->CHECKPARAM == 1){
        cout << "Error : in parameters" << endl;
    }else{
//if rejection
        if(APROP->REJMODE==1){
        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : REJECTING BAD REFERENCES ---" << endl;
            APAIR->F_WCSA_APAIR_REJECTION();
            F_WCSA_TANSIP_SET_GETREJECTIONRESULT(APROP,APAIR,GSIP);
            F_WCSA_TANSIP_SET_APROP(APROP,APAIR,GSIP);
        }
T1=clock();
if(APROP->STDOUT==2)cout << "SOLVETANSIP REJECTION TIME : " << (T1-T2)/CLOCKS_PER_SEC << " (sec)" <<endl;

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION ---" << endl;
        if(APROP->CCDPOSMODE==1||APROP->CCDPOSHMODE==1)
        APAIR->F_WCSA_APAIR_GPOS();
T2=clock();
if(APROP->STDOUT==2)cout << "SOLVETANSIP DETERMINING CCD TIME : " << (T2-T1)/CLOCKS_PER_SEC << " (sec)" <<endl;

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS ---" << endl;
        APAIR->F_WCSA_APAIR_WCS();
T1=clock();
if(APROP->STDOUT==2)cout << "SOLVETANSIP CALC. GLOBAL WCS TIME : " << (T1-T2)/CLOCKS_PER_SEC << " (sec)" <<endl;

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : GETTING GLOBAL SIP ---" << endl;
        F_WCSA_TANSIP_SET_GETWCS(APROP,APAIR,GSIP);
T2=clock();
if(APROP->STDOUT==2)cout << "SOLVETANSIP GETTING GLOBAL SIP TIME : " << (T2-T1)/CLOCKS_PER_SEC << " (sec)" <<endl;

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING LOCAL CCD ---" << endl;
        GSIP->F_WCSA_GSIP_CALCLOCALSIP();
T1=clock();
if(APROP->STDOUT==2)cout << "SOLVETANSIP CALC. LOCAL SIP TIME : " << (T1-T2)/CLOCKS_PER_SEC << " (sec)" <<endl;

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING REFEREMCE PARAMETERS in LOCAL CCD ---" << endl;
        F_WCSA_TANSIP_SET_CALCREFPARAMLOCAL(APROP,APAIR,GSIP);
T2=clock();
if(APROP->STDOUT==2)cout << "SOLVETANSIP CALC. LOCAL RMS TIME : " << (T2-T1)/CLOCKS_PER_SEC << " (sec)" <<endl;
    }
TE=clock();
if(APROP->STDOUT==2)cout << "SOLVETANSIP TOTAL TIME : " << (TE-TS)/CLOCKS_PER_SEC << " (sec)" <<endl;
//cout << GSIP->CSIP[APROP->CCDNUM].GPOS[0] << "	" << GSIP->CSIP[APROP->CCDNUM].GPOS[1] << "	" << GSIP->CSIP[APROP->CCDNUM].GPOS[2] << "	" << endl;
}
