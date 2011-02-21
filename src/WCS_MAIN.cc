//------------------------------------------------------------
//WCS_MAIN.cc
//main program for wcs program development
//1:set parameter(APROP, CPROP, PAIR) from file
//2:calculate wcs-tansip
//3:
//with [src/X.cc] [include/Y.h]
//
//Last modification : 2010/10/01
//------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include "WCS_MAINCC.h"

int main(int argc,char *argv[]){
// SET(CC) --------------------------------------------------
    char APROPFILE[100],CPROPFILE[100],PAIRFILE[100];
    CL_APROP  APROP;
    CL_CPROP *CPROP;
    CL_PAIR  *PAIR;
    CL_CSIP  *CSIP;
/*
    sprintf(APROPFILE,"paf/WCS_MAKEAPROP.paf");
    sprintf(CPROPFILE,"paf/WCS_MAKECPROP.paf");
    sprintf( PAIRFILE,"pair/matchlist_HSC.dat");
*/
/*    sprintf(APROPFILE,"paf/WCS_MAKEAPROP_100.paf");
    sprintf(CPROPFILE,"paf/WCS_MAKECPROP_100.paf");
    sprintf( PAIRFILE,"pair/matchlist_100.dat");
*/
/*
    sprintf(APROPFILE,"paf/WCS_MAKEAPROP_SC.paf");
    sprintf(CPROPFILE,"paf/WCS_MAKECPROP_SC.paf");
    sprintf( PAIRFILE,"pair/matchlist_price-101541.dat");
//    sprintf( PAIRFILE,"pair/matchlist_price-101541_scaled.dat");
*/
///*
    sprintf(APROPFILE,"paf/WCS_MAKEAPROP_oldSC.paf");
    sprintf(CPROPFILE,"paf/WCS_MAKECPROP_oldSC.paf");
    sprintf( PAIRFILE,"pair/matchlist_SUPW0021251.dat");
//*/
/*
    sprintf(APROPFILE,"paf/WCS_MAKEAPROP_2.paf");
    sprintf(CPROPFILE,"paf/WCS_MAKECPROP_2.paf");
    sprintf( PAIRFILE,"pair/matchlist_2.dat");
*/
//APROP
    F_WCS_SETCC_APROPfromFILE(APROPFILE,&APROP);

    CPROP = new CL_CPROP[APROP.CCDNUM];
    CSIP  = new CL_CSIP[APROP.CCDNUM+1];
    int CID;
    for(CID=0;CID<APROP.CCDNUM+1;CID++){
        CSIP[CID].SIP_AB[0]  = new double[(APROP.SIP_ORDER+2)*(APROP.SIP_ORDER+1)];
        CSIP[CID].SIP_AB[1]  = new double[(APROP.SIP_ORDER+2)*(APROP.SIP_ORDER+1)];
        CSIP[CID].SIP_ABP[0] = new double[(APROP.SIP_P_ORDER+2)*(APROP.SIP_P_ORDER+1)];
        CSIP[CID].SIP_ABP[1] = new double[(APROP.SIP_P_ORDER+2)*(APROP.SIP_P_ORDER+1)];
    }

//CPROP
    F_WCS_SETCC_CPROPfromFILE(CPROPFILE, CPROP);
//    F_WCS_SETCC_CPROPINITSC(CPROP);
/*
    F_WCS_SETCC_CPROPINIT2(CPROP);
*/
//PAIRSIZE
    F_WCS_SETCC_PAIRSIZEfromFILE (&APROP, CPROP, PAIRFILE);
    PAIR = new CL_PAIR[APROP.NUMREFALL];
//PAIR
    F_WCS_SETCC_PAIRfromFILE (PAIRFILE , CPROP, PAIR);

// WCS --------------------------------------------------

//WCS GLOBAL
    F_WCS_TANSIP_GPOS(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    F_WCS_TANSIP(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
//WCS GLOBAL
    F_WCS_TANSIP_GPOS(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    F_WCS_TANSIP(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
//WCS GLOBAL
    F_WCS_TANSIP_GPOS(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    F_WCS_TANSIP(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
//WCS GLOBAL
    F_WCS_TANSIP_GPOS(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);
    F_WCS_TANSIP(APROP,CPROP,PAIR,&CSIP[APROP.CCDNUM]);

//WCS each CCD
    F_WSC_WCSCCD(APROP,CPROP,PAIR,CSIP);

// TEST--------------------------------------------------

    F_WCS_CHECK(APROP,CPROP,PAIR,CSIP);
    F_WCS_TEST();

//--------------------------------------------------
    delete [] CPROP;
    delete [] PAIR;
    for(CID=0;CID<APROP.CCDNUM+1;CID++){
        delete [] CSIP[CID].SIP_AB[0];
        delete [] CSIP[CID].SIP_AB[1];
        delete [] CSIP[CID].SIP_ABP[0];
        delete [] CSIP[CID].SIP_ABP[1];
    }
    delete [] CSIP;
}
