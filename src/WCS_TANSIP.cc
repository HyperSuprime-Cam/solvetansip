//------------------------------------------------------------
//WCS_TANSIP.cc
//main program for wcs in pipeline
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#include<iostream>
#include<cmath>
#include<string.h>
#include<omp.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;

void    F_WCSA_TANSIP(CL_APROP *APROP,CL_APAIR *APAIR,CL_GSIP *GSIP){
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--------------------------------------------------" << endl;
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP ---" << endl;
//--------------------------------------------------
    if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : SET ---" << endl;
        F_WCSA_TANSIP_SET_APROP(APROP,APAIR,GSIP);
        F_WCSA_TANSIP_SET_GSIP (APROP,APAIR,GSIP);
        F_WCSA_TANSIP_SET_APAIR(APROP,APAIR,GSIP);
    if(APROP->CHECKPARAM == 1){
        cout << "Error : in parameters" << endl;
    }else{
//if rejection
        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : REJECTING BAD REFERENCES ---" << endl;
        APAIR->F_WCSA_APAIR_REJECTION();
        F_WCSA_TANSIP_SET_GETREJECTIONRESULT(APROP,APAIR,GSIP);
        F_WCSA_TANSIP_SET_APROP(APROP,APAIR,GSIP);

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : DETERMINING CCD POSITION ---" << endl;
        if(APROP->CCDPOSMODE==1)
        APAIR->F_WCSA_APAIR_GPOS();

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS ---" << endl;
        APAIR->F_WCSA_APAIR_WCS();

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : GETTING GLOBAL SIP ---" << endl;
        F_WCSA_TANSIP_SET_GETWCS(APROP,APAIR,GSIP);

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING LOCAL CCD ---" << endl;
        GSIP->F_WCSA_GSIP_CALCLOCALSIP();

        if(APROP->STDOUT==1||APROP->STDOUT==2)cout << "--- WCS_TANSIP : CALCULATING REFEREMCE PARAMETERS in LOCAL CCD ---" << endl;
        F_WCSA_TANSIP_SET_CALCREFPARAMLOCAL(APROP,APAIR,GSIP);
    }
}
