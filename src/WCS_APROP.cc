//------------------------------------------------------------
//WCS_APROP.cc
//
//Last modification : 2011/10/01
//------------------------------------------------------------
#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string.h>
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
void    CL_APROP::F_WCSA_APROP_NEWAPROP(){
    REFNUM = F_NEWint1(CCDNUM);
    FITNUM = F_NEWint1(CCDNUM);
}
void    CL_APROP::F_WCSA_APROP_DELAPROP(){
    F_DELint1(REFNUM);
    F_DELint1(FITNUM);
}
void    CL_APROP::F_WCSA_APROP_SHOWAPROP(){
    int CID;
    cout << "-- APROP CHECK --" << endl;
//    cout << "INSTRUMENT  : " << INSTRUMENT   << endl;
    cout << "CRPIXMODE   : " << CRPIXMODE   << endl;;
    cout << "REJECTMODE  : " << REJMODE   << endl;
    cout << "OAMODE      : " << OAMODE   << endl;
    cout << "CCDPOSMODE  : " << CCDPOSMODE  << endl;
    cout << "CCDPOSHMODE : " << CCDPOSHMODE  << endl;
    cout << "ALLREFNUM   : " << ALLREFNUM   << endl;
//    for(CID=0;CID<CCDNUM;CID++)
//    cout << "REFNUM      : " << CID << " : " <<  REFNUM[CID] << endl;
    cout << "ALLFITNUM   : " << ALLFITNUM   << endl;
//    for(CID=0;CID<CCDNUM;CID++)
//    cout << "FITNUM      : " << CID << " : " <<  FITNUM[CID] << endl;
    cout << "CRPIX1      : " << CRPIX[0]    << endl;
    cout << "CRPIX2      : " << CRPIX[1]    << endl;
    cout << "CRVAL1      : " << CRVAL[0]    << endl;
    cout << "CRVAL2      : " << CRVAL[1]    << endl;
    cout << "SIP_L_ORDER : " << SIP_L_ORDER << endl;
    cout << "SIP_ORDER   : " << SIP_ORDER   << endl;
    cout << "SIP_PORDER  : " << SIP_P_ORDER << endl;
    cout << "ISIP_ORDER  : " << SIP_ORDER_INIT<< endl;
    cout << "IPSIP_ORDER : " << SIP_P_ORDER_INIT<< endl;
    cout << "CRIP_SIGMA  : " << CLIP_SIGMA  << endl;
    cout << "BASISPOSX   : " << BASISPOS[0] << endl;
    cout << "BASISPOSY   : " << BASISPOS[1] << endl;
    cout << "BASISPOST   : " << BASISPOS[2] << endl;
    cout << "CCDNUM      : " << CCDNUM      << endl;
    cout << "STDOUT      : " << STDOUT      << endl;
    cout <<endl;
}
/*DEL*/
void	CL_APROP::F_WCSA_APROP_CHECKCRPIXMODE(){
    if(strcmp(CRPIXMODE,"AUTO")==0||strcmp(CRPIXMODE,"PIX")==0||strcmp(CRPIXMODE,"VAL")==0||strcmp(CRPIXMODE,"OAXIS")==0){
        if(STDOUT==1||STDOUT==2)cout << "OK : CRPIXMODE" << endl;
    }else{
        cout << "CRPIXMODE is '" << CRPIXMODE << "'"<< endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning : CRPIXMODE isn't 'AUTO' or 'PIX' or 'VAL' or 'OAXIS'" << endl;
        sprintf(CRPIXMODE,"AUTO");
        cout << "Warning : SET CRPIXMODE : " << CRPIXMODE << endl;
        cout << "---------------------------------------------" << endl;
    }
}
void	CL_APROP::F_WCSA_APROP_CHECKCCDPOSMODE(){
    if(CCDPOSMODE==0||CCDPOSMODE==1){
        if(STDOUT==1||STDOUT==2)cout << "OK : CCDPOSMODE" << endl;
    }else{
        cout << "CCDPMODE is " << CCDPOSMODE << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning : CCDPMODE isn't 0 or 1" << endl;
        CCDPOSMODE=0;
        cout << "Warning : SET CCDPMODE : " << CCDPOSMODE << endl;
        cout << "---------------------------------------------" << endl;
    }
}
void	CL_APROP::F_WCSA_APROP_CHECKSIPORDER(){
    if(SIP_ORDER>0.5&&SIP_ORDER<15.5){
        if(STDOUT==1||STDOUT==2)cout << "OK : SIP_ORDER" << endl;
    }else{
        cout << "SIPORDER is " << SIP_ORDER << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning :  SIPORDER isn't a number between 1 and 15" << endl;
        SIP_ORDER=9;
        cout << "Warning : SET SIPORDER : " << SIP_ORDER << endl;
        cout << "---------------------------------------------" << endl;
    }
}
void	CL_APROP::F_WCSA_APROP_CHECKPSIPORDER(){
    if(SIP_P_ORDER>0.5&&SIP_P_ORDER<15.5){
        if(STDOUT==1||STDOUT==2)cout << "OK : SIP_P_ORDER" << endl;
    }else{
        cout << "PSIP_ORDER is " << SIP_P_ORDER << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning : PSIPORDER isn't a number between 1 and 15" << endl;
        SIP_P_ORDER=9;
        cout << "Warning : SET PSIPORDER : " << SIP_P_ORDER << endl;
        cout << "---------------------------------------------" << endl;
    }
}
void	CL_APROP::F_WCSA_APROP_CHECKLSIPORDER(){
    if(SIP_L_ORDER>1.5&&SIP_L_ORDER<15.5){
        if(STDOUT==1||STDOUT==2)cout << "OK : SIP_L_ORDER" << endl;
    }else{
        cout << "LSIP_ORDER is " << SIP_L_ORDER << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Warning : LSIPORDER isn't a number between 2 and 15" << endl;
        SIP_L_ORDER=3;
        cout << "Warning : SET LSIPORDER : " << SIP_L_ORDER << endl;
        cout << "---------------------------------------------" << endl;
    }
}
void	CL_APROP::F_WCSA_APROP_CHECKFITNUM(){
    if(ALLFITNUM==0){
        cout << "---------------------------------------------" << endl;
        cout << "Error : THERE IS NO REFERENCES" << endl;
        cout << "---------------------------------------------" << endl;
        CHECKPARAM=1;
    }else{
        if(STDOUT==1||STDOUT==2)cout << "OK : ALLFITNUM" << endl;
    }
///Error : in ORDER
    if(ALLFITNUM<0.5*(SIP_ORDER+1)*(SIP_ORDER+2)+1){
    cout << "---------------------------------------------" << endl;
    cout << "Warning : NUMBER OF REFERENCES ARE NOT ENOUGH TO FITTING WITH ORDER : " << SIP_ORDER << endl;
    cout << "---------------------------------------------" << endl;
    int ORDER;
    for(ORDER=SIP_ORDER+1;ORDER<1;ORDER--)
    if(ALLFITNUM>0.5*(SIP_ORDER+1)*(SIP_ORDER+2)+1){
    SIP_ORDER=ORDER;
    cout << "          SET SIPORDER : " << ORDER << endl;
    break;
    }}else{
        if(STDOUT==1||STDOUT==2)cout << "OK : SIP_ORDER <-> REFERENCE NUM" << endl;
    }
    if(ALLFITNUM<0.5*(SIP_P_ORDER+1)*(SIP_P_ORDER+2)+1){
    cout << "---------------------------------------------" << endl;
    cout << "Warning : NUMBER OF REFERENCES ARE NOT ENOUGH TO FITTING WITH ORDER : " << SIP_P_ORDER << endl;
    cout << "---------------------------------------------" << endl;
    int PORDER;
    for(PORDER=SIP_P_ORDER+1;PORDER<1;PORDER--)
    if(ALLFITNUM>0.5*(SIP_P_ORDER+1)*(SIP_P_ORDER+2)+1){
    SIP_P_ORDER=PORDER;
    cout << "          SET PSIPORDER : " << PORDER << endl;
    break;
    }}else{
        if(STDOUT==1||STDOUT==2)cout << "OK : SIP_P_ORDER <-> REFERENCE NUM" << endl;
    }
}
void	CL_APROP::F_WCSA_APROP_CHECKCCDFITNUM(){
    int CID;
///Error : in 0 NUM
   for(CID=0;CID<CCDNUM;CID++)
    if(FITNUM[CID]<(int)(0.5*(SIP_L_ORDER+1)*(SIP_L_ORDER+2)+0.5)){
    cout << "---------------------------------------------" << endl;
    cout << "Warning : NUMBER OF REFERENCE in CCD " << CID << " is " << FITNUM[CID] << endl;
    CCDPOSMODE=0;
    CCDPOSHMODE=0;
    cout << "          USING INITIAL VALUES FOR CCD POSITIONS " << endl;
    cout << "---------------------------------------------" << endl;
    }else{
        if(STDOUT==1||STDOUT==2)cout << "OK : NUMBER OF REFERENCE in CCD " << CID << " IS " << FITNUM[CID] << endl;
    }
}
