//------------------------------------------------------------
//WCS_TANSIP.cc
//main program for wcs in pipeline
//
//Last modification : 2010/04/01
//------------------------------------------------------------
#include<iostream>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
void    F_WCS_TANSIP(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    cout << "--------------------------------------------------" << endl;
    cout << "--- WCS_TANSIP ---" << endl;

//--------------------------------------------------
    cout << "--- WCS_TANSIP : SET ---" << endl;
    F_WCS_TANSIP_SET(&APROP,CPROP,PAIR,CSIP);
    if(APROP.CHECKPARAM == 1){
    cout << "Error : in parameters" << endl;
    }else{
//--------------------------------------------------
    cout << "--- WCS_TANSIP : DETERMINING CCD POSITION ---" << endl;
    F_WCS_TANSIP_GPOS(&APROP,CPROP,PAIR,CSIP);

//--------------------------------------------------
    cout << "--- WCS_TANSIP : CALCULATING GLOBAL WCS ---" << endl;
    F_WCS_TANSIP_WCS(APROP,CPROP,PAIR,CSIP);

//--------------------------------------------------
    cout << "--- WCS_TANSIP : CALCULATING LOCAL CCD ---" << endl;
    F_WCS_TANSIP_CCD(APROP,CPROP,PAIR,CSIP);

//--------------------------------------------------
    }
}
