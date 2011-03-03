//------------------------------------------------------------
//WCS_TANSIP.cc
//main program for wcs in pipeline
//
//Last modification : 2010/10/01
//------------------------------------------------------------
#include<iostream>
#include<cmath>
#include "hsc/meas/tansip/WCS_PL_MAIN.h"
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;

void    F_WCS_TANSIP(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
cout << endl;
cout << "--- F_WCS_TANSIP : SIP FITTING : FITTING    ---" << endl;
    F_CDSIP(APROP,CPROP,PAIR,CSIP);
cout << "--- F_WCS_TANSIP : SIP FITTING : REJECTION  ---" << endl;
    F_FLAG (APROP, PAIR,CSIP);
cout << "--- F_WCS_TANSIP : SIP FITTING : RE-FITTING ---" << endl;
    F_CDSIP(APROP,CPROP,PAIR,CSIP);
//cout << "--- F_WCS_TANSIP : SIP FITTING : DONE ---" << endl;
//    F_DISP (APROP, PAIR,CSIP);
}
void    F_WCS_TANSIP_GPOS(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

/*    int PHASE;

cout << endl;
    for(PHASE=1;PHASE<10;PHASE++){
cout << "--- F_WCS_TANSIP:GLOVAL POSITION:Phase "<<PHASE<<"    ---" << endl;
    F_GPOS(PHASE,APROP,CPROP,PAIR,CSIP);
    }*/
cout << "--- F_WCS_TANSIP : GLOBAL POSITION ---" << endl;
    F_PROJECTIONPOINT(APROP,*CPROP,PAIR,CSIP);
    F_PROJECTION(APROP,*CPROP,PAIR,CSIP);
    F_LPFITTING_DIFFPAIR(APROP,*CPROP,PAIR,CSIP);
    F_CHANGEdxLtodxG(APROP,CPROP,PAIR,CSIP);
//    F_CHANGEdxLtodxG(APROP,CPROP,PAIR,CSIP);
  //  F_CHANGEdxLtodxG(APROP,CPROP,PAIR,CSIP);
//    F_CHANGEdxLtodxGNOROT(APROP,*CPROP,PAIR,CSIP);
    F_FITINTdxGdxI(APROP,*CPROP,PAIR,CSIP);
    F_FITGPOS(APROP,CPROP,PAIR,CSIP);
}
