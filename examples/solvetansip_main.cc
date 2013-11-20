//------------------------------------------------------------
//solvetansip_main.cc
//
//Last modification : 2012/03/11
//------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<string.h>
#include<fstream>
#include "solvetansip_main.h"
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
void    F_GETKEYVALUE10(int KEYNUM,char ***KEYVALUE,char *FILENAME);
void    solvetansip_MAKEAPROP(CL_APROP *APROP){
    char APROPFILE[100];
    sprintf(APROPFILE,"../policy/WCS_MAKEAPROP.paf");
    int i,j;
    char ***KEYVALUE;

    KEYVALUE = new char**[20];
    for(i=0;i<20;i++){
    KEYVALUE[i] = new char*[2];
    for(j=0;j<2;j++)
    KEYVALUE[i][j] = new char[101];
    }
//----------

    strcpy(KEYVALUE[ 0][0],"CRPIXMODE:");
    strcpy(KEYVALUE[ 1][0],"OAMODE   :");
    strcpy(KEYVALUE[ 2][0],"NCCD     :");
    strcpy(KEYVALUE[ 3][0],"LSIPORDER:");
    strcpy(KEYVALUE[ 4][0],"SIPORDER :");
    strcpy(KEYVALUE[ 5][0],"PSIPORDER:");
    strcpy(KEYVALUE[ 6][0],"CLIPSIGMA:");
    strcpy(KEYVALUE[ 7][0],"CRPIX1   :");
    strcpy(KEYVALUE[ 8][0],"CRPIX2   :");
    strcpy(KEYVALUE[ 9][0],"CRVAL1   :");
    strcpy(KEYVALUE[10][0],"CRVAL2   :");
    strcpy(KEYVALUE[11][0],"CHECKFILE:");
    strcpy(KEYVALUE[12][0],"ALIGNAXIS:");
    strcpy(KEYVALUE[13][0],"BASISCCD :");
    strcpy(KEYVALUE[14][0],"BASISPOSX:");
    strcpy(KEYVALUE[15][0],"BASISPOSY:");
    strcpy(KEYVALUE[16][0],"BASISPOST:");
    strcpy(KEYVALUE[17][0],"STDOUT   :");
    strcpy(KEYVALUE[18][0],"CCDPOS   :");

    F_GETKEYVALUE10(19,KEYVALUE,APROPFILE);
    
    for(i=0;i<10;i++)
    if(KEYVALUE[ 0][1][i]==' '){
    break;
    }else{
    APROP->CRPIXMODE[i]=KEYVALUE[ 0][1][i];
    }
    for(i=0;i<10;i++)
    if(KEYVALUE[ 1][1][i]==' '){
    break;
    }else{
    APROP->OAMODE[i]=KEYVALUE[ 1][1][i];
    }

    APROP->CCDNUM      =atoi(KEYVALUE[ 2][1]);
    APROP->SIP_L_ORDER =atoi(KEYVALUE[ 3][1]);
    APROP->SIP_ORDER   =atoi(KEYVALUE[ 4][1]);
    APROP->SIP_P_ORDER =atoi(KEYVALUE[ 5][1]);
    APROP->CLIP_SIGMA  =atof(KEYVALUE[ 6][1]);
    APROP->CRPIX[0]    =atof(KEYVALUE[ 7][1]);
    APROP->CRPIX[1]    =atof(KEYVALUE[ 8][1]);
    APROP->CRVAL[0]    =atof(KEYVALUE[ 9][1]);
    APROP->CRVAL[1]    =atof(KEYVALUE[10][1]);	
//    APROP->CHECKFILE   =atoi(KEYVALUE[11][1]);	
//    APROP->ALIGNAXIS   =atoi(KEYVALUE[12][1]);	
//    APROP->BASISCID    =atoi(KEYVALUE[13][1]);	
    APROP->BASISPOS[0] =atof(KEYVALUE[14][1]);	
    APROP->BASISPOS[1] =atof(KEYVALUE[15][1]);	
    APROP->BASISPOS[2] =atof(KEYVALUE[16][1]);
    APROP->STDOUT      =atoi(KEYVALUE[17][1]);
    APROP->CCDPOSMODE  =atoi(KEYVALUE[18][1]);

//----------
    for(i=0;i<20;i++)
    for(j=0;j<2;j++)
    delete [] KEYVALUE[i][j];
    for(i=0;i<20;i++)
    delete [] KEYVALUE[i];
    delete [] KEYVALUE;
}
void    F_WCSA_SETREFSIZE_local(string matchlist, CL_APROP* APROP){
    int ID,CID,*CIDNUM;
    double x,y,RA,DEC;
    ifstream in;

    CIDNUM = new int[APROP->CCDNUM+1];
    for(CID=0;CID<APROP->CCDNUM+1;CID++)
    CIDNUM[CID]=0;

    in.open(matchlist.c_str());
    while((in >> ID >> CID >> x >> y >> RA >> DEC)!=0){
        CIDNUM[CID]++;
        CIDNUM[APROP->CCDNUM]++;
    }

    for(CID=0;CID<APROP->CCDNUM;CID++){
    APROP->REFNUM[CID]     = CIDNUM[CID];
    APROP->FITNUM[CID]     = CIDNUM[CID];
    }

    APROP->ALLREFNUM = CIDNUM[APROP->CCDNUM];
    APROP->ALLFITNUM = CIDNUM[APROP->CCDNUM];
    in.close();

    delete [] CIDNUM;
}

void    F_WCSA_MAKEGSIP(CL_APROP *APROP, CL_GSIP *GSIP){
    int CID;

    GSIP->F_WCSA_GSIP_SET0();
/*
    for(camGeom::Camera::const_iterator iter(camera->begin()); iter != camera->end(); ++iter) { 
        camGeom::DetectorMosaic::Ptr detMosaic = boost::dynamic_pointer_cast<camGeom::DetectorMosaic>(*iter);

        for(CID=0;CID<APROP->CCDNUM;CID++){
            camGeom::Id detId = camGeom::Id(CID);//serial
            camGeom::Detector::Ptr det = detMosaic->findDetector(detId);
            afwGeom::Point2D offsetXY = det->getCenter();
//            double ccdTiltYaw = (det->getOrientation()).getYaw();
  //          int ccdTiltNQuarter = (det->getOrientation()).getNQuarter();

            GSIP->CSIP[CID].ID=detId.getSerial();
            GSIP->CSIP[CID].GPOS[0]=offsetXY[0];
            GSIP->CSIP[CID].GPOS[1]=offsetXY[1];
            GSIP->CSIP[CID].GPOS[2]=0;//ccdTiltNQuarter * 90.0;//?
            GSIP->CSIP[CID].POSID[0]=detId.getIndex().first;
            GSIP->CSIP[CID].POSID[1]=detId.getIndex().second;
        }
    }
*/}
void    F_WCSA_MAKEPAIR_local(string matchlist,CL_APAIR* APAIR){
    int ID,CID,ALLNUM;
    double x,y,RA,DEC;
    ifstream in;

    APAIR->F_WCSA_APAIR_SET0();
    in.open(matchlist.c_str());
    cout << matchlist.c_str() << endl;
    ALLNUM=0;
    while((in >> ID >> CID >> x >> y >> RA >> DEC)!=0){
        APAIR->PAIR[ALLNUM].ID           =ID;
        APAIR->PAIR[ALLNUM].CHIPID       =CID;
        APAIR->PAIR[ALLNUM].FLAG         =1;
        APAIR->PAIR[ALLNUM].X_LOCAL[0]   =x;
        APAIR->PAIR[ALLNUM].X_LOCAL[1]   =y;
        APAIR->PAIR[ALLNUM].X_RADEC[0]   =RA;
        APAIR->PAIR[ALLNUM].X_RADEC[1]   =DEC;
        APAIR->PAIR[ALLNUM].X_LOCALERR[0]=1;
        APAIR->PAIR[ALLNUM].X_LOCALERR[1]=1;
        APAIR->PAIR[ALLNUM].X_RADECERR[0]=1;
        APAIR->PAIR[ALLNUM].X_RADECERR[1]=1;
        ALLNUM++;
    }
}
int main(int argc, char *argv[]){
    CL_WCSA_ASP *WCSA_ASP;

    WCSA_ASP = new CL_WCSA_ASP[1];
    WCSA_ASP->F_WCS_PLMAIN_NEWWCSA_ASP();

    solvetansip_MAKEAPROP(WCSA_ASP->APROP);
    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_APROP ---" << endl;
    WCSA_ASP->APAIR->CCDNUM=WCSA_ASP->GSIP->CCDNUM=WCSA_ASP->APROP->CCDNUM;
    WCSA_ASP->APROP->F_WCSA_APROP_NEWAPROP();

    string matchlist(argv[1]);
    F_WCSA_SETREFSIZE_local(matchlist,WCSA_ASP->APROP);
    WCSA_ASP->APAIR->ALLREFNUM=WCSA_ASP->GSIP->ALLREFNUM=WCSA_ASP->APROP->ALLREFNUM;
    WCSA_ASP->APAIR->ALLFITNUM=WCSA_ASP->GSIP->ALLFITNUM=WCSA_ASP->APROP->ALLFITNUM;

    WCSA_ASP->APAIR->SIP_ORDER  =WCSA_ASP->GSIP->SIP_ORDER  =WCSA_ASP->APROP->SIP_ORDER;
    WCSA_ASP->APAIR->SIP_P_ORDER=WCSA_ASP->GSIP->SIP_P_ORDER=WCSA_ASP->APROP->SIP_P_ORDER;
    WCSA_ASP->APAIR->SIP_L_ORDER=WCSA_ASP->GSIP->SIP_L_ORDER=WCSA_ASP->APROP->SIP_L_ORDER;

    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APROP->F_WCSA_APROP_SHOWAPROP();

    WCSA_ASP->APAIR->F_WCSA_APAIR_NEWAPAIR();
    WCSA_ASP->GSIP ->F_WCSA_GSIP_NEWGSIP();

    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_GSIP ---" << endl;
    F_WCSA_MAKEGSIP(WCSA_ASP->APROP,WCSA_ASP->GSIP);
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->GSIP->F_WCSA_GSIP_SHOWGSIP();

    if(WCSA_ASP->APROP->STDOUT==1||WCSA_ASP->APROP->STDOUT==2)cout << "--- WCS_PL_MAIN : F_WCS_MAKE_PAIR ---" << endl;
    F_WCSA_MAKEPAIR_local(matchlist,WCSA_ASP->APAIR);
    if(WCSA_ASP->APROP->STDOUT==2) WCSA_ASP->APAIR->F_WCSA_APAIR_SHOWAPAIR();

    F_WCSA_TANSIP(WCSA_ASP->APROP,WCSA_ASP->APAIR,WCSA_ASP->GSIP);

    WCSA_ASP->F_WCS_PLMAIN_DELWCSA_ASP();
    delete WCSA_ASP;
    return 0;
}
