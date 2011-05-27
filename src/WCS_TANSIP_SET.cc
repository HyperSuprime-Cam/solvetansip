//------------------------------------------------------------
//WCS_TANSIP_SET.cc
//Checking and setting parameters
//
//Last modification : 2010/05/20
//------------------------------------------------------------
#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
void    F_WCS_SETDEFAULTPOSITIONS_SC(CL_CPROP *CPROP);
void    F_WCS_SETDEFAULTPOSITIONS_HSC(CL_CPROP *CPROP);
void    F_WCS_TANSIP_SET(CL_APROP *APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int CID,CID2,NUM;

//CHECKING PARAM
    cout << "--- WCS_TANSIP : SET : CHEKING PARAMERTERS---" << endl;
    APROP->CHECKPARAM=0;

    if(strcmp(APROP->CRPIXMODE,"AUTO")==0||strcmp(APROP->CRPIXMODE,"PIX")==0||strcmp(APROP->CRPIXMODE,"VAL")==0||strcmp(APROP->CRPIXMODE,"OAXIS")==0){
    }else{
        cout << "CRPIXMODE is " << APROP->CRPIXMODE << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning : CRPIXMODE isn't 'AUTO' or 'PIX' or 'VAL' or 'OAXIS'" << endl;
        sprintf(APROP->CRPIXMODE,"AUTO");
        cout << "Warning : SET CRPIXMODE : " << APROP->CRPIXMODE << endl;
        cout << "---------------------------------------------" << endl;
    }
    if(APROP->CCDPOSMODE==0||APROP->CCDPOSMODE==1){
    }else{
        cout << "CCDPMODE is " << APROP->CCDPOSMODE << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning : CCDPMODE isn't 0 or 1" << endl;
        APROP->CCDPOSMODE=0;
        cout << "Warning : SET CCDPMODE : " << APROP->CCDPOSMODE << endl;
        cout << "---------------------------------------------" << endl;
    }
    if(APROP->SIP_ORDER<0.5||APROP->SIP_ORDER>9.5){
        cout << "SIPORDER is " << APROP->SIP_ORDER << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning :  SIPORDER isn't a number between 1 and 9" << endl;
        APROP->SIP_ORDER=9;
        cout << "Warning : SET SIPORDER : " << APROP->SIP_ORDER << endl;
        cout << "---------------------------------------------" << endl;
    }
    if(APROP->SIP_P_ORDER<0.5||APROP->SIP_P_ORDER>9.5){
        cout << "PSIP_ORDER is " << APROP->SIP_P_ORDER << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning : PSIPORDER isn't a number between 1 and 9" << endl;
        APROP->SIP_P_ORDER=9;
        cout << "Warning : SET PSIPORDER : " << APROP->SIP_P_ORDER << endl;
        cout << "---------------------------------------------" << endl;
    }
    if(APROP->SIP_L_ORDER<1.5||APROP->SIP_L_ORDER>9.5){
        cout << "LSIP_ORDER is " << APROP->SIP_L_ORDER << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning : LSIPORDER isn't a number between 2 and 9" << endl;
        APROP->SIP_L_ORDER=3;
        cout << "Warning : SET LSIPORDER : " << APROP->SIP_L_ORDER << endl;
        cout << "---------------------------------------------" << endl;
    }
    for(CID=0;CID<APROP->CCDNUM;CID++){
        if(APROP->BASISCID==CID)
        break;

        if(APROP->CCDNUM-1==CID){        
        cout << "BASISCCD is " << APROP->BASISCID << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning : in BASISCCD" << endl;
        APROP->BASISCID=0;
        cout << "Warning : SET BASISCCD : " << APROP->BASISCID << endl;
        cout << "---------------------------------------------" << endl;
        }
    }


    for(CID=0;CID<APROP->CCDNUM;CID++)
    for(CID2=CID+1;CID2<APROP->CCDNUM;CID2++)
    if(hypot(CPROP[CID].GLOB_POS[0]-CPROP[CID2].GLOB_POS[0],CPROP[CID].GLOB_POS[1]-CPROP[CID2].GLOB_POS[1])<2000){
        cout << "CID ;  " << CID << " : GLOB_POS x : " << CPROP[CID].GLOB_POS[0] << " : GLOB_POS y : " << CPROP[CID].GLOB_POS[1] << endl;
        cout << "CID ;  " << CID2 << " : GLOB_POS x : " << CPROP[CID2].GLOB_POS[0] << " : GLOB_POS y : " << CPROP[CID2].GLOB_POS[1] << endl;
        if(APROP->CCDNUM<11){
        F_WCS_SETDEFAULTPOSITIONS_SC(CPROP);
        }else{
        F_WCS_SETDEFAULTPOSITIONS_HSC(CPROP);
        }
        cout << "---------------------------------------------" << endl;
        cout << "Warning : Separation between CHIPID : " << CID << " and " << CID2 << " is under 2000" << endl;
        cout << "          USING DEFAULT VALUES FOR CCD POSITIONS " << endl;
        cout << "---------------------------------------------" << endl;
        break;
    }
    int ALIGNNUM=0;
    for(CID=0;CID<APROP->CCDNUM;CID++)
    if(CPROP[CID].ALIGN==1)
    ALIGNNUM++;
    if(ALIGNNUM<2){
    cout << "---------------------------------------------" << endl;
    cout << "Warning : in F_WCS_TANSIP_SET : CPROP[].ALIGN" << endl;
    cout << "          Number of CCDs used for CCD alignment is under 2" << endl;
    cout << "          Using 000 - 009 CCDs for CCD alignment" << endl;
    cout << "---------------------------------------------" << endl;
    CPROP[0].ALIGN=CPROP[1].ALIGN=CPROP[2].ALIGN=CPROP[3].ALIGN=CPROP[4].ALIGN=CPROP[5].ALIGN=CPROP[6].ALIGN=CPROP[7].ALIGN=CPROP[8].ALIGN=CPROP[9].ALIGN=1;
    }

///Error : in ORDER

    if(APROP->NUMREFALL<0.5*(APROP->SIP_ORDER+1)*(APROP->SIP_ORDER+2)+1){
    cout << "---------------------------------------------" << endl;
    cout << "Warning : NUMBER OF REFERENCES ARE NOT ENOUGH TO FITTING WITH ORDER : " << APROP->SIP_ORDER << endl;
    cout << "---------------------------------------------" << endl;
    int ORDER;
    for(ORDER=APROP->SIP_ORDER+1;ORDER<1;ORDER--)
    if(APROP->NUMREFALL>0.5*(APROP->SIP_ORDER+1)*(APROP->SIP_ORDER+2)+1){
    APROP->SIP_ORDER=ORDER;
    cout << "          SET SIPORDER : " << ORDER << endl;
    break;
    }}

    if(APROP->NUMREFALL<0.5*(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)+1){
    cout << "---------------------------------------------" << endl;
    cout << "Warning : NUMBER OF REFERENCES ARE NOT ENOUGH TO FITTING WITH ORDER : " << APROP->SIP_P_ORDER << endl;
    cout << "---------------------------------------------" << endl;
    int PORDER;
    for(PORDER=APROP->SIP_P_ORDER+1;PORDER<1;PORDER--)
    if(APROP->NUMREFALL>0.5*(APROP->SIP_P_ORDER+1)*(APROP->SIP_P_ORDER+2)+1){
    APROP->SIP_P_ORDER=PORDER;
    cout << "          SET PSIPORDER : " << PORDER << endl;
    break;
    }}

///Error : in 0 NUM
    for(CID=0;CID<APROP->CCDNUM;CID++)
    if(CPROP[CID].NUMREF==0){
    cout << "---------------------------------------------" << endl;
    cout << "Warning : NUMBER OF REFERENCE in CCD " << CID << " IS 0" << endl;
    APROP->CCDPOSMODE=0;
    cout << "          USING INITIAL VALUES FOR CCD POSITIONS " << endl;
    cout << "---------------------------------------------" << endl;
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
void    F_WCS_SETDEFAULTPOSITIONS_SC(CL_CPROP *CPROP){
}
void    F_WCS_SETDEFAULTPOSITIONS_HSC(CL_CPROP *CPROP){
    CPROP[  0].GLOB_POS[0]=- 9514.700;
    CPROP[  0].GLOB_POS[1]=-   96.000;
    CPROP[  0].GLOB_POS[2]=  0.000000;
    CPROP[  1].GLOB_POS[0]=  7466.700;
    CPROP[  1].GLOB_POS[1]=- 4266.700;
    CPROP[  1].GLOB_POS[2]=  0.000000;
    CPROP[  2].GLOB_POS[0]=- 7392.000;
    CPROP[  2].GLOB_POS[1]=-   96.000;
    CPROP[  2].GLOB_POS[2]=  0.000000;
    CPROP[  3].GLOB_POS[0]=  5344.000;
    CPROP[  3].GLOB_POS[1]=- 4266.700;
    CPROP[  3].GLOB_POS[2]=  0.000000;
    CPROP[  4].GLOB_POS[0]=- 5269.300;
    CPROP[  4].GLOB_POS[1]=-   96.000;
    CPROP[  4].GLOB_POS[2]=  0.000000;
    CPROP[  5].GLOB_POS[0]=  3221.300;
    CPROP[  5].GLOB_POS[1]=- 4266.700;
    CPROP[  5].GLOB_POS[2]=  0.000000;
    CPROP[  6].GLOB_POS[0]=- 3146.700;
    CPROP[  6].GLOB_POS[1]=-   96.000;
    CPROP[  6].GLOB_POS[2]=  0.000000;
    CPROP[  7].GLOB_POS[0]=  1098.700;
    CPROP[  7].GLOB_POS[1]=- 4266.700;
    CPROP[  7].GLOB_POS[2]=  0.000000;
    CPROP[  8].GLOB_POS[0]=- 1024.000;
    CPROP[  8].GLOB_POS[1]=-   96.000;
    CPROP[  8].GLOB_POS[2]=  0.000000;
    CPROP[  9].GLOB_POS[0]=- 1024.000;
    CPROP[  9].GLOB_POS[1]=- 4266.700;
    CPROP[  9].GLOB_POS[2]=  0.000000;
    CPROP[ 10].GLOB_POS[0]=  1098.700;
    CPROP[ 10].GLOB_POS[1]=-   96.000;
    CPROP[ 10].GLOB_POS[2]=  0.000000;
    CPROP[ 11].GLOB_POS[0]=- 3146.700;
    CPROP[ 11].GLOB_POS[1]=- 4266.700;
    CPROP[ 11].GLOB_POS[2]=  0.000000;
    CPROP[ 12].GLOB_POS[0]=  3221.300;
    CPROP[ 12].GLOB_POS[1]=-   96.000;
    CPROP[ 12].GLOB_POS[2]=  0.000000;
    CPROP[ 13].GLOB_POS[0]=- 5269.300;
    CPROP[ 13].GLOB_POS[1]=- 4266.700;
    CPROP[ 13].GLOB_POS[2]=  0.000000;
    CPROP[ 14].GLOB_POS[0]=  5344.000;
    CPROP[ 14].GLOB_POS[1]=-   96.000;
    CPROP[ 14].GLOB_POS[2]=  0.000000;
    CPROP[ 15].GLOB_POS[0]=- 7392.000;
    CPROP[ 15].GLOB_POS[1]=- 4266.700;
    CPROP[ 15].GLOB_POS[2]=  0.000000;
    CPROP[ 16].GLOB_POS[0]=  7466.700;
    CPROP[ 16].GLOB_POS[1]=-   96.000;
    CPROP[ 16].GLOB_POS[2]=  0.000000;
    CPROP[ 17].GLOB_POS[0]=- 9514.700;
    CPROP[ 17].GLOB_POS[1]=- 4266.700;
    CPROP[ 17].GLOB_POS[2]=  0.000000;
    CPROP[ 18].GLOB_POS[0]=  9589.300;
    CPROP[ 18].GLOB_POS[1]=-   96.000;
    CPROP[ 18].GLOB_POS[2]=  0.000000;
    CPROP[ 19].GLOB_POS[0]=-11637.300;
    CPROP[ 19].GLOB_POS[1]=- 4266.700;
    CPROP[ 19].GLOB_POS[2]=  0.000000;
    CPROP[ 20].GLOB_POS[0]= 11712.000;
    CPROP[ 20].GLOB_POS[1]=-   96.000;
    CPROP[ 20].GLOB_POS[2]=  0.000000;
    CPROP[ 21].GLOB_POS[0]=-13760.000;
    CPROP[ 21].GLOB_POS[1]=- 4266.700;
    CPROP[ 21].GLOB_POS[2]=  0.000000;
    CPROP[ 22].GLOB_POS[0]= 13834.700;
    CPROP[ 22].GLOB_POS[1]=-   96.000;
    CPROP[ 22].GLOB_POS[2]=  0.000000;
    CPROP[ 23].GLOB_POS[0]=-15882.700;
    CPROP[ 23].GLOB_POS[1]=- 4266.700;
    CPROP[ 23].GLOB_POS[2]=  0.000000;
    CPROP[ 24].GLOB_POS[0]=- 9514.700;
    CPROP[ 24].GLOB_POS[1]=  4379.000;
    CPROP[ 24].GLOB_POS[2]=  0.000000;
    CPROP[ 25].GLOB_POS[0]=  7466.700;
    CPROP[ 25].GLOB_POS[1]=- 8741.700;
    CPROP[ 25].GLOB_POS[2]=  0.000000;
    CPROP[ 26].GLOB_POS[0]=- 7392.000;
    CPROP[ 26].GLOB_POS[1]=  4379.000;
    CPROP[ 26].GLOB_POS[2]=  0.000000;
    CPROP[ 27].GLOB_POS[0]=  5344.000;
    CPROP[ 27].GLOB_POS[1]=- 8741.700;
    CPROP[ 27].GLOB_POS[2]=  0.000000;
    CPROP[ 28].GLOB_POS[0]=- 5269.300;
    CPROP[ 28].GLOB_POS[1]=  4379.000;
    CPROP[ 28].GLOB_POS[2]=  0.000000;
    CPROP[ 29].GLOB_POS[0]=  3221.300;
    CPROP[ 29].GLOB_POS[1]=- 8741.700;
    CPROP[ 29].GLOB_POS[2]=  0.000000;
    CPROP[ 30].GLOB_POS[0]=- 3146.700;
    CPROP[ 30].GLOB_POS[1]=  4379.000;
    CPROP[ 30].GLOB_POS[2]=  0.000000;
    CPROP[ 31].GLOB_POS[0]=  1098.700;
    CPROP[ 31].GLOB_POS[1]=- 8741.700;
    CPROP[ 31].GLOB_POS[2]=  0.000000;
    CPROP[ 32].GLOB_POS[0]=- 1024.000;
    CPROP[ 32].GLOB_POS[1]=  4379.000;
    CPROP[ 32].GLOB_POS[2]=  0.000000;
    CPROP[ 33].GLOB_POS[0]=- 1024.000;
    CPROP[ 33].GLOB_POS[1]=- 8741.700;
    CPROP[ 33].GLOB_POS[2]=  0.000000;
    CPROP[ 34].GLOB_POS[0]=  1098.700;
    CPROP[ 34].GLOB_POS[1]=  4379.000;
    CPROP[ 34].GLOB_POS[2]=  0.000000;
    CPROP[ 35].GLOB_POS[0]=- 3146.700;
    CPROP[ 35].GLOB_POS[1]=- 8741.700;
    CPROP[ 35].GLOB_POS[2]=  0.000000;
    CPROP[ 36].GLOB_POS[0]=  3221.300;
    CPROP[ 36].GLOB_POS[1]=  4379.000;
    CPROP[ 36].GLOB_POS[2]=  0.000000;
    CPROP[ 37].GLOB_POS[0]=- 5269.300;
    CPROP[ 37].GLOB_POS[1]=- 8741.700;
    CPROP[ 37].GLOB_POS[2]=  0.000000;
    CPROP[ 38].GLOB_POS[0]=  5344.000;
    CPROP[ 38].GLOB_POS[1]=  4379.000;
    CPROP[ 38].GLOB_POS[2]=  0.000000;
    CPROP[ 39].GLOB_POS[0]=- 7392.000;
    CPROP[ 39].GLOB_POS[1]=- 8741.700;
    CPROP[ 39].GLOB_POS[2]=  0.000000;
    CPROP[ 40].GLOB_POS[0]=  7466.700;
    CPROP[ 40].GLOB_POS[1]=  4379.000;
    CPROP[ 40].GLOB_POS[2]=  0.000000;
    CPROP[ 41].GLOB_POS[0]=- 9514.700;
    CPROP[ 41].GLOB_POS[1]=- 8741.700;
    CPROP[ 41].GLOB_POS[2]=  0.000000;
    CPROP[ 42].GLOB_POS[0]=  9589.300;
    CPROP[ 42].GLOB_POS[1]=  4379.000;
    CPROP[ 42].GLOB_POS[2]=  0.000000;
    CPROP[ 43].GLOB_POS[0]=-11637.300;
    CPROP[ 43].GLOB_POS[1]=- 8741.700;
    CPROP[ 43].GLOB_POS[2]=  0.000000;
    CPROP[ 44].GLOB_POS[0]= 11712.000;
    CPROP[ 44].GLOB_POS[1]=  4379.000;
    CPROP[ 44].GLOB_POS[2]=  0.000000;
    CPROP[ 45].GLOB_POS[0]=-13760.000;
    CPROP[ 45].GLOB_POS[1]=- 8741.700;
    CPROP[ 45].GLOB_POS[2]=  0.000000;
    CPROP[ 46].GLOB_POS[0]= 13834.700;
    CPROP[ 46].GLOB_POS[1]=  4379.000;
    CPROP[ 46].GLOB_POS[2]=  0.000000;
    CPROP[ 47].GLOB_POS[0]=-15882.700;
    CPROP[ 47].GLOB_POS[1]=- 8741.700;
    CPROP[ 47].GLOB_POS[2]=  0.000000;
    CPROP[ 48].GLOB_POS[0]=- 9514.700;
    CPROP[ 48].GLOB_POS[1]=  8854.000;
    CPROP[ 48].GLOB_POS[2]=  0.000000;
    CPROP[ 49].GLOB_POS[0]=  7466.700;
    CPROP[ 49].GLOB_POS[1]=-13216.700;
    CPROP[ 49].GLOB_POS[2]=  0.000000;
    CPROP[ 50].GLOB_POS[0]=- 7392.000;
    CPROP[ 50].GLOB_POS[1]=  8854.000;
    CPROP[ 50].GLOB_POS[2]=  0.000000;
    CPROP[ 51].GLOB_POS[0]=  5344.000;
    CPROP[ 51].GLOB_POS[1]=-13216.700;
    CPROP[ 51].GLOB_POS[2]=  0.000000;
    CPROP[ 52].GLOB_POS[0]=- 5269.300;
    CPROP[ 52].GLOB_POS[1]=  8854.000;
    CPROP[ 52].GLOB_POS[2]=  0.000000;
    CPROP[ 53].GLOB_POS[0]=  3221.300;
    CPROP[ 53].GLOB_POS[1]=-13216.700;
    CPROP[ 53].GLOB_POS[2]=  0.000000;
    CPROP[ 54].GLOB_POS[0]=- 3164.700;
    CPROP[ 54].GLOB_POS[1]=  8854.000;
    CPROP[ 54].GLOB_POS[2]=  0.000000;
    CPROP[ 55].GLOB_POS[0]=  1098.700;
    CPROP[ 55].GLOB_POS[1]=-13216.700;
    CPROP[ 55].GLOB_POS[2]=  0.000000;
    CPROP[ 56].GLOB_POS[0]=- 1024.000;
    CPROP[ 56].GLOB_POS[1]=  8854.000;
    CPROP[ 56].GLOB_POS[2]=  0.000000;
    CPROP[ 57].GLOB_POS[0]=- 1024.000;
    CPROP[ 57].GLOB_POS[1]=-13216.700;
    CPROP[ 57].GLOB_POS[2]=  0.000000;
    CPROP[ 58].GLOB_POS[0]=  1098.700;
    CPROP[ 58].GLOB_POS[1]=  8854.000;
    CPROP[ 58].GLOB_POS[2]=  0.000000;
    CPROP[ 59].GLOB_POS[0]=- 3146.700;
    CPROP[ 59].GLOB_POS[1]=-13216.700;
    CPROP[ 59].GLOB_POS[2]=  0.000000;
    CPROP[ 60].GLOB_POS[0]=  3221.300;
    CPROP[ 60].GLOB_POS[1]=  8854.000;
    CPROP[ 60].GLOB_POS[2]=  0.000000;
    CPROP[ 61].GLOB_POS[0]=- 5269.300;
    CPROP[ 61].GLOB_POS[1]=-13216.700;
    CPROP[ 61].GLOB_POS[2]=  0.000000;
    CPROP[ 62].GLOB_POS[0]=  5344.000;
    CPROP[ 62].GLOB_POS[1]=  8854.000;
    CPROP[ 62].GLOB_POS[2]=  0.000000;
    CPROP[ 63].GLOB_POS[0]=- 7392.000;
    CPROP[ 63].GLOB_POS[1]=-13216.700;
    CPROP[ 63].GLOB_POS[2]=  0.000000;
    CPROP[ 64].GLOB_POS[0]=  7466.700;
    CPROP[ 64].GLOB_POS[1]=  8854.000;
    CPROP[ 64].GLOB_POS[2]=  0.000000;
    CPROP[ 65].GLOB_POS[0]=- 9514.700;
    CPROP[ 65].GLOB_POS[1]=-13216.700;
    CPROP[ 65].GLOB_POS[2]=  0.000000;
    CPROP[ 66].GLOB_POS[0]=  9589.300;
    CPROP[ 66].GLOB_POS[1]=  8854.000;
    CPROP[ 66].GLOB_POS[2]=  0.000000;
    CPROP[ 67].GLOB_POS[0]=-11637.300;
    CPROP[ 67].GLOB_POS[1]=-13216.700;
    CPROP[ 67].GLOB_POS[2]=  0.000000;
    CPROP[ 68].GLOB_POS[0]= 11712.000;
    CPROP[ 68].GLOB_POS[1]=  8854.000;
    CPROP[ 68].GLOB_POS[2]=  0.000000;
    CPROP[ 69].GLOB_POS[0]=-13760.000;
    CPROP[ 69].GLOB_POS[1]=-13216.700;
    CPROP[ 69].GLOB_POS[2]=  0.000000;
    CPROP[ 70].GLOB_POS[0]=- 7392.000;
    CPROP[ 70].GLOB_POS[1]= 13329.000;
    CPROP[ 70].GLOB_POS[2]=  0.000000;
    CPROP[ 71].GLOB_POS[0]=  5344.000;
    CPROP[ 71].GLOB_POS[1]=-17691.700;
    CPROP[ 71].GLOB_POS[2]=  0.000000;
    CPROP[ 72].GLOB_POS[0]=- 5269.300;
    CPROP[ 72].GLOB_POS[1]= 13329.000;
    CPROP[ 72].GLOB_POS[2]=  0.000000;
    CPROP[ 73].GLOB_POS[0]=  3221.300;
    CPROP[ 73].GLOB_POS[1]=-17691.700;
    CPROP[ 73].GLOB_POS[2]=  0.000000;
    CPROP[ 74].GLOB_POS[0]=- 3146.700;
    CPROP[ 74].GLOB_POS[1]= 13329.000;
    CPROP[ 74].GLOB_POS[2]=  0.000000;
    CPROP[ 75].GLOB_POS[0]=  1098.700;
    CPROP[ 75].GLOB_POS[1]=-17691.700;
    CPROP[ 75].GLOB_POS[2]=  0.000000;
    CPROP[ 76].GLOB_POS[0]=- 1024.000;
    CPROP[ 76].GLOB_POS[1]= 13329.000;
    CPROP[ 76].GLOB_POS[2]=  0.000000;
    CPROP[ 77].GLOB_POS[0]=- 1024.000;
    CPROP[ 77].GLOB_POS[1]=-17691.700;
    CPROP[ 77].GLOB_POS[2]=  0.000000;
    CPROP[ 78].GLOB_POS[0]=  1098.700;
    CPROP[ 78].GLOB_POS[1]= 13329.000;
    CPROP[ 78].GLOB_POS[2]=  0.000000;
    CPROP[ 79].GLOB_POS[0]=- 3146.700;
    CPROP[ 79].GLOB_POS[1]=-17691.700;
    CPROP[ 79].GLOB_POS[2]=  0.000000;
    CPROP[ 80].GLOB_POS[0]=  3221.300;
    CPROP[ 80].GLOB_POS[1]= 13329.000;
    CPROP[ 80].GLOB_POS[2]=  0.000000;
    CPROP[ 81].GLOB_POS[0]=- 5269.300;
    CPROP[ 81].GLOB_POS[1]=-17691.700;
    CPROP[ 81].GLOB_POS[2]=  0.000000;
    CPROP[ 82].GLOB_POS[0]=  5344.000;
    CPROP[ 82].GLOB_POS[1]= 13329.000;
    CPROP[ 82].GLOB_POS[2]=  0.000000;
    CPROP[ 83].GLOB_POS[0]=- 7392.000;
    CPROP[ 83].GLOB_POS[1]=-17691.700;
    CPROP[ 83].GLOB_POS[2]=  0.000000;
    CPROP[ 84].GLOB_POS[0]=  9589.300;
    CPROP[ 84].GLOB_POS[1]=- 4571.000;
    CPROP[ 84].GLOB_POS[2]=  0.000000;
    CPROP[ 85].GLOB_POS[0]=-11637.300;
    CPROP[ 85].GLOB_POS[1]=   208.300;
    CPROP[ 85].GLOB_POS[2]=  0.000000;
    CPROP[ 86].GLOB_POS[0]= 11712.000;
    CPROP[ 86].GLOB_POS[1]=- 4571.000;
    CPROP[ 86].GLOB_POS[2]=  0.000000;
    CPROP[ 87].GLOB_POS[0]=-13760.000;
    CPROP[ 87].GLOB_POS[1]=   208.300;
    CPROP[ 87].GLOB_POS[2]=  0.000000;
    CPROP[ 88].GLOB_POS[0]= 13834.700;
    CPROP[ 88].GLOB_POS[1]=- 4571.000;
    CPROP[ 88].GLOB_POS[2]=  0.000000;
    CPROP[ 89].GLOB_POS[0]=-15882.700;
    CPROP[ 89].GLOB_POS[1]=   208.300;
    CPROP[ 89].GLOB_POS[2]=  0.000000;
    CPROP[ 90].GLOB_POS[0]=  9589.300;
    CPROP[ 90].GLOB_POS[1]=- 9046.000;
    CPROP[ 90].GLOB_POS[2]=  0.000000;
    CPROP[ 91].GLOB_POS[0]=-11637.300;
    CPROP[ 91].GLOB_POS[1]=  4683.300;
    CPROP[ 91].GLOB_POS[2]=  0.000000;
    CPROP[ 92].GLOB_POS[0]= 11712.000;
    CPROP[ 92].GLOB_POS[1]=- 9046.000;
    CPROP[ 92].GLOB_POS[2]=  0.000000;
    CPROP[ 93].GLOB_POS[0]=-13760.000;
    CPROP[ 93].GLOB_POS[1]=  4683.300;
    CPROP[ 93].GLOB_POS[2]=  0.000000;
    CPROP[ 94].GLOB_POS[0]= 13834.700;
    CPROP[ 94].GLOB_POS[1]=- 9460.000;
    CPROP[ 94].GLOB_POS[2]=  0.000000;
    CPROP[ 95].GLOB_POS[0]=-15882.700;
    CPROP[ 95].GLOB_POS[1]=  4683.300;
    CPROP[ 95].GLOB_POS[2]=  0.000000;
    CPROP[ 96].GLOB_POS[0]=  9589.300;
    CPROP[ 96].GLOB_POS[1]=-13521.000;
    CPROP[ 96].GLOB_POS[2]=  0.000000;
    CPROP[ 97].GLOB_POS[0]=-11637.300;
    CPROP[ 97].GLOB_POS[1]=  9158.300;
    CPROP[ 97].GLOB_POS[2]=  0.000000;
    CPROP[ 98].GLOB_POS[0]= 11712.000;
    CPROP[ 98].GLOB_POS[1]=-13521.000;
    CPROP[ 98].GLOB_POS[2]=  0.000000;
    CPROP[ 99].GLOB_POS[0]=-13760.000;
    CPROP[ 99].GLOB_POS[1]=  9158.300;
    CPROP[ 99].GLOB_POS[2]=  0.000000;
}
