//------------------------------------------------------------
//WCS_PL_GET.cc
//getting program for wcs in pipeline
//
//Last modification : 2012/06/15
//------------------------------------------------------------
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include "hsc/meas/tansip/WCS_PL_MAIN.h"
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;

//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP Values
//-----------------------------------------------------------------
int F_WCSA_PLGET_CCDNUM(CL_WCSA_ASP* WCSA_ASP){
    return WCSA_ASP->APROP->CCDNUM;
}
int F_WCSA_PLGET_ALLREFNUM(CL_WCSA_ASP* WCSA_ASP){
    return WCSA_ASP->APROP->ALLREFNUM;
}
int F_WCSA_PLGET_ALLFITNUM(CL_WCSA_ASP* WCSA_ASP){
    return WCSA_ASP->APROP->ALLFITNUM;
}
std::vector< double > F_WCSA_PLGET_CRPIX(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > CRPIX(2);
    CRPIX[0]=WCSA_ASP->APROP->CRPIX[0];
    CRPIX[1]=WCSA_ASP->APROP->CRPIX[1];
    return CRPIX;
}
std::vector< double > F_WCSA_PLGET_CRVAL(CL_WCSA_ASP* WCSA_ASP){
    std::vector< double > CRVAL(2);
    CRVAL[0]=WCSA_ASP->APROP->CRVAL[0];
    CRVAL[1]=WCSA_ASP->APROP->CRVAL[1];
    return CRVAL;
}
std::vector< double > F_WCSA_PLGET_REFNUM(CL_WCSA_ASP* WCSA_ASP){
    int CID;
    std::vector< double > REFNUM;
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++)
    REFNUM.push_back(WCSA_ASP->GSIP->CSIP[CID].REFNUM);

    return REFNUM;
}
std::vector< double > F_WCSA_PLGET_FITNUM(CL_WCSA_ASP* WCSA_ASP){
    int CID;
    std::vector< double > FITNUM;
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++)
    FITNUM.push_back(WCSA_ASP->GSIP->CSIP[CID].FITNUM);

    return FITNUM;
}
std::vector< double > F_WCSA_PLGET_SIPRMSX(CL_WCSA_ASP* WCSA_ASP){
    int CID;
    std::vector< double > SIPRMS;
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++)
    SIPRMS.push_back(WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[0][1]);

    return SIPRMS;
}
std::vector< double > F_WCSA_PLGET_SIPRMSY(CL_WCSA_ASP* WCSA_ASP){
    int CID;
    std::vector< double > SIPRMS;
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++)
    SIPRMS.push_back(WCSA_ASP->GSIP->CSIP[CID].SIP_AB_ERR[1][1]);

    return SIPRMS;
}
std::vector< double > F_WCSA_PLGET_PSIPRMSX(CL_WCSA_ASP* WCSA_ASP){
    int CID;
    std::vector< double > SIPRMS;
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++)
    SIPRMS.push_back(WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[0][1]);

    return SIPRMS;
}
std::vector< double > F_WCSA_PLGET_PSIPRMSY(CL_WCSA_ASP* WCSA_ASP){
    int CID;
    std::vector< double > SIPRMS;
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++)
    SIPRMS.push_back(WCSA_ASP->GSIP->CSIP[CID].SIP_ABP_ERR[1][1]);

    return SIPRMS;
}
//-----------------------------------------------------------------
//Getting Functions : CCD Info
//-----------------------------------------------------------------
std::vector< int > F_WCSA_PLGET_CCD_ID(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< int > CID;
    for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++)
    CID.push_back(WCSA_ASP->GSIP->CSIP[ID].ID);

    return CID;
}
std::vector< int > F_WCSA_PLGET_CCD_NUMREF(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< int > RNUM;
    for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++)
    RNUM.push_back(WCSA_ASP->GSIP->CSIP[ID].REFNUM);

    return RNUM;
}
std::vector< int > F_WCSA_PLGET_CCD_NUMFIT(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< int > FNUM;
    for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++)
    FNUM.push_back(WCSA_ASP->GSIP->CSIP[ID].FITNUM);

    return FNUM;
}
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_GPOS(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > POSX,POSY,POST;
    std::vector< std::vector< double > > CCDPOS;
    for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++){
	POSX.push_back(WCSA_ASP->GSIP->CSIP[ID].GPOS[0]);
	POSY.push_back(WCSA_ASP->GSIP->CSIP[ID].GPOS[1]);
	POST.push_back(WCSA_ASP->GSIP->CSIP[ID].GPOS[2]);
    }
    CCDPOS.push_back(POSX);
    CCDPOS.push_back(POSY);
    CCDPOS.push_back(POST);

    return CCDPOS;
}
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_CR(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > CRP1,CRP2,CRV1,CRV2;
    std::vector< std::vector< double > > CCDCR;
    for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++){
	CRP1.push_back(WCSA_ASP->GSIP->CSIP[ID].CRPIX[0]);
	CRP2.push_back(WCSA_ASP->GSIP->CSIP[ID].CRPIX[1]);
	CRV1.push_back(WCSA_ASP->GSIP->CSIP[ID].CRVAL[0]);
	CRV2.push_back(WCSA_ASP->GSIP->CSIP[ID].CRVAL[1]);
    }
	CCDCR.push_back(CRP1);
	CCDCR.push_back(CRP2);
	CCDCR.push_back(CRV1);
	CCDCR.push_back(CRV2);

    return CCDCR;
}
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_CD(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > CD11,CD12,CD21,CD22;
    std::vector< std::vector< double > > CCDCD;
    for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++){
	CD11.push_back(WCSA_ASP->GSIP->CSIP[ID].CD[0][0]);
	CD12.push_back(WCSA_ASP->GSIP->CSIP[ID].CD[0][1]);
	CD21.push_back(WCSA_ASP->GSIP->CSIP[ID].CD[1][0]);
	CD22.push_back(WCSA_ASP->GSIP->CSIP[ID].CD[1][1]);
    }
	CCDCD.push_back(CD11);
	CCDCD.push_back(CD12);
	CCDCD.push_back(CD21);
	CCDCD.push_back(CD22);

    return CCDCD;
}
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_ERRSIP(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > ERRXA,ERRXB,ERRXC,ERRYA,ERRYB,ERRYC;
    std::vector< std::vector< double > >  CCDERR;
    for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++){
	ERRXA.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_AB_ERR[0][0]);
	ERRXB.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_AB_ERR[0][1]);
	ERRXC.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_AB_ERR[0][2]);
	ERRYA.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_AB_ERR[1][0]);
	ERRYB.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_AB_ERR[1][1]);
	ERRYC.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_AB_ERR[1][2]);
    }
	CCDERR.push_back(ERRXA);
	CCDERR.push_back(ERRXB);
	CCDERR.push_back(ERRXC);
	CCDERR.push_back(ERRYA);
	CCDERR.push_back(ERRYB);
	CCDERR.push_back(ERRYC);

    return CCDERR;
}
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_ERRPSIP(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > ERRXA,ERRXB,ERRXC,ERRYA,ERRYB,ERRYC;
    std::vector< std::vector< double > >  CCDERR;
    for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++){
	ERRXA.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_ABP_ERR[0][0]);
	ERRXB.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_ABP_ERR[0][1]);
	ERRXC.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_ABP_ERR[0][2]);
	ERRYA.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_ABP_ERR[1][0]);
	ERRYB.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_ABP_ERR[1][1]);
	ERRYC.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_ABP_ERR[1][2]);
    }
	CCDERR.push_back(ERRXA);
	CCDERR.push_back(ERRXB);
	CCDERR.push_back(ERRXC);
	CCDERR.push_back(ERRYA);
	CCDERR.push_back(ERRYB);
	CCDERR.push_back(ERRYC);

    return CCDERR;
}
std::vector< int > F_WCSA_PLGET_CCD_ORDERSIP(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< int > SORD;
    for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++)
    SORD.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_ORDER);

    return SORD;
}
std::vector< int > F_WCSA_PLGET_CCD_ORDERPSIP(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< int > PORD;
    for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++)
    PORD.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_P_ORDER);

    return PORD;
}
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_COEFSIPA(CL_WCSA_ASP* WCSA_ASP){
    int ID,ORDER,S_ORDER;
    std::vector< double > COEF;
    std::vector< std::vector< double > >  CCDCOEF;

    S_ORDER=WCSA_ASP->GSIP->CSIP[WCSA_ASP->APROP->CCDNUM].SIP_ORDER;
    for(ORDER=0;ORDER<(0.5*(S_ORDER+1)*(S_ORDER+2)+0.5);ORDER++){
        for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++){
	    COEF.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_AB[0][ORDER]);
        }
        CCDCOEF.push_back(COEF);
        COEF.clear();
    }
    return CCDCOEF;
}
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_COEFSIPB(CL_WCSA_ASP* WCSA_ASP){
    int ID,ORDER,S_ORDER;
    std::vector< double > COEF;
    std::vector< std::vector< double > >  CCDCOEF;

    S_ORDER=WCSA_ASP->GSIP->CSIP[WCSA_ASP->APROP->CCDNUM].SIP_ORDER;
    for(ORDER=0;ORDER<(0.5*(S_ORDER+1)*(S_ORDER+2)+0.5);ORDER++){
        for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++){
	    COEF.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_AB[1][ORDER]);
        }
        CCDCOEF.push_back(COEF);
        COEF.clear();
    }
    return CCDCOEF;
}
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_COEFPSIPA(CL_WCSA_ASP* WCSA_ASP){
    int ID,ORDER,S_ORDER;
    std::vector< double > COEF;
    std::vector< std::vector< double > >  CCDCOEF;

    S_ORDER=WCSA_ASP->GSIP->CSIP[WCSA_ASP->APROP->CCDNUM].SIP_ORDER;
    for(ORDER=0;ORDER<(0.5*(S_ORDER+1)*(S_ORDER+2)+0.5);ORDER++){
        for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++){
	    COEF.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_ABP[0][ORDER]);
        }
        CCDCOEF.push_back(COEF);
        COEF.clear();
    }
    return CCDCOEF;
}
std::vector< std::vector< double > > F_WCSA_PLGET_CCD_COEFPSIPB(CL_WCSA_ASP* WCSA_ASP){
    int ID,ORDER,S_ORDER;
    std::vector< double > COEF;
    std::vector< std::vector< double > >  CCDCOEF;

    S_ORDER=WCSA_ASP->GSIP->CSIP[WCSA_ASP->APROP->CCDNUM].SIP_ORDER;
    for(ORDER=0;ORDER<(0.5*(S_ORDER+1)*(S_ORDER+2)+0.5);ORDER++){
        for(ID=0;ID<WCSA_ASP->APROP->CCDNUM+1;ID++){
	    COEF.push_back(WCSA_ASP->GSIP->CSIP[ID].SIP_ABP[1][ORDER]);
        }
        CCDCOEF.push_back(COEF);
        COEF.clear();
    }
    return CCDCOEF;
}
//-----------------------------------------------------------------
//Getting Functions : REF Info
//-----------------------------------------------------------------
std::vector< long long int > F_WCSA_PLGET_REF_ID(CL_WCSA_ASP* WCSA_ASP){
    long long int ID;
    std::vector< long long int > RID;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++)
    RID.push_back(WCSA_ASP->APAIR->PAIR[ID].ID);

    return RID;
}
std::vector< int > F_WCSA_PLGET_REF_CID(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< int > CID;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++)
    CID.push_back(WCSA_ASP->APAIR->PAIR[ID].CHIPID);

    return CID;
}
std::vector< int > F_WCSA_PLGET_REF_FLAG(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< int > FLAG;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++)
    FLAG.push_back(WCSA_ASP->APAIR->PAIR[ID].FLAG);

    return FLAG;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_POSLOCAL(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > X,Y;
    std::vector< std::vector< double > > XY;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++){
        X.push_back(WCSA_ASP->APAIR->PAIR[ID].X_LOCAL[0]);
        Y.push_back(WCSA_ASP->APAIR->PAIR[ID].X_LOCAL[1]);
    }
    XY.push_back(X);
    XY.push_back(Y);

    return XY;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_POSGLOBAL(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > X,Y;
    std::vector< std::vector< double > > XY;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++){
        X.push_back(WCSA_ASP->APAIR->PAIR[ID].X_GLOBAL[0]);
        Y.push_back(WCSA_ASP->APAIR->PAIR[ID].X_GLOBAL[1]);
    }
    XY.push_back(X);
    XY.push_back(Y);

    return XY;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_POSRADEC(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > X,Y;
    std::vector< std::vector< double > > XY;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++){
        X.push_back(WCSA_ASP->APAIR->PAIR[ID].X_RADEC[0]);
        Y.push_back(WCSA_ASP->APAIR->PAIR[ID].X_RADEC[1]);
    }
    XY.push_back(X);
    XY.push_back(Y);

    return XY;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_POSLCRPIX(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > X,Y;
    std::vector< std::vector< double > > XY;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++){
        X.push_back(WCSA_ASP->APAIR->PAIR[ID].X_LOCALCRPIX[0]);
        Y.push_back(WCSA_ASP->APAIR->PAIR[ID].X_LOCALCRPIX[1]);
    }
    XY.push_back(X);
    XY.push_back(Y);

    return XY;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_POSGCRPIX(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > X,Y;
    std::vector< std::vector< double > > XY;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++){
        X.push_back(WCSA_ASP->APAIR->PAIR[ID].X_GLOBALCRPIX[0]);
        Y.push_back(WCSA_ASP->APAIR->PAIR[ID].X_GLOBALCRPIX[1]);
    }
    XY.push_back(X);
    XY.push_back(Y);

    return XY;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_DIFFSIP(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > X,Y;
    std::vector< std::vector< double > > XY;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++){
        X.push_back(WCSA_ASP->APAIR->PAIR[ID].DIFF_SIP[0]);
        Y.push_back(WCSA_ASP->APAIR->PAIR[ID].DIFF_SIP[1]);
    }
    XY.push_back(X);
    XY.push_back(Y);

    return XY;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_DIFFPSIP(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > X,Y;
    std::vector< std::vector< double > > XY;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++){
        X.push_back(WCSA_ASP->APAIR->PAIR[ID].DIFF_PSIP[0]);
        Y.push_back(WCSA_ASP->APAIR->PAIR[ID].DIFF_PSIP[1]);
    }
    XY.push_back(X);
    XY.push_back(Y);

    return XY;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_CAMERADISTSIP(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > CONV,ROT,SHR1,SHR2,MAG,JAC;
    std::vector< std::vector< double > > DIST;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++){
        CONV.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_CONVROT[0]);
         ROT.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_CONVROT[1]);
        SHR1.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_SHEAR[0]);
        SHR2.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_SHEAR[1]);
         MAG.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_MAGNIFICATION);
         JAC.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_JACOBIAN);
    }
    DIST.push_back(CONV);
    DIST.push_back(ROT);
    DIST.push_back(SHR1);
    DIST.push_back(SHR2);
    DIST.push_back(MAG);
    DIST.push_back(JAC);

    return DIST;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_CAMERADISTPSIP(CL_WCSA_ASP* WCSA_ASP){
    int ID;
    std::vector< double > CONV,ROT,SHR1,SHR2,MAG,JAC;
    std::vector< std::vector< double > > DIST;
    for(ID=0;ID<WCSA_ASP->APROP->ALLREFNUM;ID++){
        CONV.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_PCONVROT[0]);
         ROT.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_PCONVROT[1]);
        SHR1.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_PSHEAR[0]);
        SHR2.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_PSHEAR[1]);
         MAG.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_PMAGNIFICATION);
         JAC.push_back(WCSA_ASP->APAIR->PAIR[ID].CAMERA_PJACOBIAN);
    }
    DIST.push_back(CONV);
    DIST.push_back(ROT);
    DIST.push_back(SHR1);
    DIST.push_back(SHR2);
    DIST.push_back(MAG);
    DIST.push_back(JAC);

    return DIST;
}
 
//-----------------------------------------------------------------
//Getting Functions : CCD Regions
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLGET_CORNAR(CL_WCSA_ASP* WCSA_ASP,int CID){
    std::vector< double > CCDCORNAR;
    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        if(CID<100-0.5){
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
	    CCDCORNAR.push_back(0.0);
	    CCDCORNAR.push_back(0.0);
        }else{
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
            CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
	    CCDCORNAR.push_back(0.0);
	    CCDCORNAR.push_back(0.0);
        }
    }else{
	    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++)
            if(CID<100-0.5){
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
	        CCDCORNAR.push_back(0.0);
	        CCDCORNAR.push_back(0.0);
            }else{
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
                CCDCORNAR.push_back(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]));
    	        CCDCORNAR.push_back(0.0);
    	        CCDCORNAR.push_back(0.0);
            }
    }
    return CCDCORNAR;
}
std::vector< double > F_WCSA_PLGET_DISTCORRCORNAR(CL_WCSA_ASP* WCSA_ASP,int CID){
    double LOCAL[2],IMPIXEL[2];
    std::vector< double > DISTCORRCORNAR;
    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        if(CID<100-0.5){
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
	    DISTCORRCORNAR.push_back(0.0);
	    DISTCORRCORNAR.push_back(0.0);
        }else{
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
	    DISTCORRCORNAR.push_back(0.0);
	    DISTCORRCORNAR.push_back(0.0);
        }
    }else{
	    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++)
            if(CID<100-0.5){
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
	    DISTCORRCORNAR.push_back(0.0);
	    DISTCORRCORNAR.push_back(0.0);
            }else{
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(IMPIXEL[0]);
            DISTCORRCORNAR.push_back(IMPIXEL[1]);
	    DISTCORRCORNAR.push_back(0.0);
	    DISTCORRCORNAR.push_back(0.0);
            }
    }
    return DISTCORRCORNAR;
}
std::vector< double > F_WCSA_PLGET_DISTCORRCORNAR_N(CL_WCSA_ASP* WCSA_ASP,int CID,int N){
    double LOCAL[2],IMPIXEL[2];
    std::vector< double > DISTCORRCORNAR;
    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        if(CID<100-0.5){
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
	    DISTCORRCORNAR.push_back(0.0);
	    DISTCORRCORNAR.push_back(0.0);
        }else{
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CID,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
	    DISTCORRCORNAR.push_back(0.0);
	    DISTCORRCORNAR.push_back(0.0);
        }
    }else{
	    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++)
            if(CID<100-0.5){
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
	    DISTCORRCORNAR.push_back(0.0);
	    DISTCORRCORNAR.push_back(0.0);
            }else{
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(WCSA_ASP->APROP->CCDNUM,LOCAL,IMPIXEL);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[0]-LOCAL[0])+LOCAL[0]);
            DISTCORRCORNAR.push_back(N*(IMPIXEL[1]-LOCAL[1])+LOCAL[1]);
	    DISTCORRCORNAR.push_back(0.0);
	    DISTCORRCORNAR.push_back(0.0);
            }
    }
    return DISTCORRCORNAR;
}
std::vector< double > F_WCSA_PLGET_RADECCORNAR(CL_WCSA_ASP* WCSA_ASP,int CID){
    double LOCAL[2],RADEC[2];
    std::vector< double > RADECCORNAR;
    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        if(CID<100-0.5){
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(CID,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(CID,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(CID,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(CID,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
	    RADECCORNAR.push_back(0.0);
	    RADECCORNAR.push_back(0.0);
        }else{
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(CID,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(CID,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(CID,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(CID,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
	    RADECCORNAR.push_back(0.0);
	    RADECCORNAR.push_back(0.0);
        }
    }else{
	    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++)
            if(CID<100-0.5){
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(WCSA_ASP->APROP->CCDNUM,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(WCSA_ASP->APROP->CCDNUM,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(WCSA_ASP->APROP->CCDNUM,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(WCSA_ASP->APROP->CCDNUM,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
	    RADECCORNAR.push_back(0.0);
	    RADECCORNAR.push_back(0.0);
            }else{
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(WCSA_ASP->APROP->CCDNUM,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(WCSA_ASP->APROP->CCDNUM,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+4096*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(WCSA_ASP->APROP->CCDNUM,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
            LOCAL[0]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-2048*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            LOCAL[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000*sin(WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+2048*cos(WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
            WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(WCSA_ASP->APROP->CCDNUM,LOCAL,RADEC);
            RADECCORNAR.push_back(RADEC[0]);
            RADECCORNAR.push_back(RADEC[1]);
	    RADECCORNAR.push_back(0.0);
	    RADECCORNAR.push_back(0.0);
            }
    }
    return RADECCORNAR;
}
std::vector< int > F_WCSA_PLGET_INDEX(CL_WCSA_ASP *WCSA_ASP){
    int CID;
    std::vector< int > INDEX;
    
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++){
    INDEX.push_back((int)(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]/fabs(WCSA_ASP->GSIP->CSIP[CID].GPOS[0])*(fabs((WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+1024)/2048)+0.1)));
    INDEX.push_back((int)(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]/fabs(WCSA_ASP->GSIP->CSIP[CID].GPOS[1])*(fabs((WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000)/2048)+0.1)));
//    cout << CID << "	" << WCSA_ASP->GSIP->CSIP[CID].GPOS[0]/(2048)  << "	" << WCSA_ASP->GSIP->CSIP[CID].GPOS[1]/(2048) <<"	"  << (int)(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]/fabs(WCSA_ASP->GSIP->CSIP[CID].GPOS[0])*(fabs((WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+1024)/2048)+0.1)) << "	" << (int)(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]/fabs(WCSA_ASP->GSIP->CSIP[CID].GPOS[1])*(fabs(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]/2048)+0.1)) << endl;
    }
    return INDEX;
}
//-----------------------------------------------------------------
//Getting Functions : POSITIONs
//-----------------------------------------------------------------

std::vector< double > F_WCSA_PLGET_POSITION_RADECfromLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    int CHIPID;
    double LOCAL[2],RD[2];
    std::vector< double > RADEC(2);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }
    LOCAL[0]=XY[0];
    LOCAL[1]=XY[1];
    WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(CHIPID,LOCAL,RD);
    RADEC[0]=RD[0];
    RADEC[1]=RD[1];

    return RADEC;
}
std::vector< double > F_WCSA_PLGET_POSITION_RADECfromCRPIX(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    int CHIPID;
    double XCRPIX[2],RD[2];
    std::vector< double > RADEC(2);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    XCRPIX[0]=XY[0];
    XCRPIX[1]=XY[1];
    WCSA_ASP->GSIP->F_WCSA_GSIP_XCRPIXtoXRADEC(CHIPID,XCRPIX,RD);
    RADEC[0]=RD[0];
    RADEC[1]=RD[1];

    return RADEC;
}
std::vector< double > F_WCSA_PLGET_POSITION_LOCALfromRADEC(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    int CHIPID;
    double RADEC[2],RD[2];
    std::vector< double > LOCAL(2);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    RADEC[0]=XY[0];
    RADEC[1]=XY[1];
    WCSA_ASP->GSIP->F_WCSA_GSIP_XRADECtoXLOCAL(CHIPID,RADEC,RD);
    LOCAL[0]=RD[0];
    LOCAL[1]=RD[1];

    return LOCAL;
}
std::vector< double > F_WCSA_PLGET_POSITION_CRPIXfromRADEC(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    int CHIPID;
    double RADEC[2],RD[2];
    std::vector< double > XCRPIX(2);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    RADEC[0]=XY[0];
    RADEC[1]=XY[1];
    WCSA_ASP->GSIP->F_WCSA_GSIP_XRADECtoXCRPIX(CHIPID,RADEC,RD);
    XCRPIX[0]=RD[0];
    XCRPIX[1]=RD[1];

    return XCRPIX;
}

std::vector< double > F_WCSA_PLGET_POSITION_GLOBALfromCCDIDLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    std::vector< double > X_GLOBAL(2);
    int CCDID=(int)(CID+0.5);
    X_GLOBAL[0]=WCSA_ASP->GSIP->CSIP[CCDID].GPOS[0]+XY[0]*cos(WCSA_ASP->GSIP->CSIP[CCDID].GPOS[2])-XY[1]*sin(WCSA_ASP->GSIP->CSIP[CCDID].GPOS[2]);
    X_GLOBAL[1]=WCSA_ASP->GSIP->CSIP[CCDID].GPOS[1]+XY[1]*cos(WCSA_ASP->GSIP->CSIP[CCDID].GPOS[2])+XY[0]*sin(WCSA_ASP->GSIP->CSIP[CCDID].GPOS[2]);

    return X_GLOBAL;
}
std::vector< double > F_WCSA_PLGET_POSITION_CCDIDLOCALfromGLOBAL(CL_WCSA_ASP* WCSA_ASP,std::vector< double > XY){
    std::vector< double > CCDIDLOCAL(3);
    int CID,CHECK=0;
    double XLOCAL[2];
//cout << XY[0] << "	" << XY[1] << endl;
    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++){
        XLOCAL[0]=(XY[0]-WCSA_ASP->GSIP->CSIP[CID].GPOS[0])*cos(-WCSA_ASP->GSIP->CSIP[CID].GPOS[2])-(XY[1]-WCSA_ASP->GSIP->CSIP[CID].GPOS[1])*sin(-WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
        XLOCAL[1]=(XY[1]-WCSA_ASP->GSIP->CSIP[CID].GPOS[1])*cos(-WCSA_ASP->GSIP->CSIP[CID].GPOS[2])+(XY[0]-WCSA_ASP->GSIP->CSIP[CID].GPOS[0])*sin(-WCSA_ASP->GSIP->CSIP[CID].GPOS[2]);
//cout << CID << "	" << XLOCAL[0] << "	" << XLOCAL[1] << endl;
        if(XLOCAL[0]>0&&XLOCAL[0]<2048&&XLOCAL[1]>0&&XLOCAL[1]<4096){
            CCDIDLOCAL[0]=CID;
            CCDIDLOCAL[1]=XLOCAL[0];
            CCDIDLOCAL[2]=XLOCAL[1];
            CHECK=1;
            break;
        }
    }
cout << CHECK << "	" << CID << "	" << XLOCAL[0] << "	" << XLOCAL[1] << endl;
    if(CHECK==0){
        cout << "No CCDs(2048,4096) have the global position : " << XY[0] << " , " << XY[1]<<endl;
            CCDIDLOCAL[0]=0;
            CCDIDLOCAL[1]=0;
            CCDIDLOCAL[2]=0;
    }
cout << CHECK << "	" << CID << "	" << XLOCAL[0] << "	" << XLOCAL[1] << endl;

    return CCDIDLOCAL;
}
std::vector< double > F_WCSA_PLGET_POSITION_IMPIXELfromLOCAL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    int CHIPID;
    double LOCAL[2],IM_PIXEL[2];
    std::vector< double > IMPIXEL(2);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }
    LOCAL[0]=XY[0];
    LOCAL[1]=XY[1];
    WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXIMPIXEL(CHIPID,LOCAL,IM_PIXEL);
    IMPIXEL[0]=IM_PIXEL[0];
    IMPIXEL[1]=IM_PIXEL[1];

    return IMPIXEL;
}
std::vector< double > F_WCSA_PLGET_POSITION_LOCALfromIMPIXEL(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > XY){
    int CHIPID;
    double IMPIXEL[2],LOCAL[2];
    std::vector< double > XLOCAL(2);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    IMPIXEL[0]=XY[0];
    IMPIXEL[1]=XY[1];
    WCSA_ASP->GSIP->F_WCSA_GSIP_XIMPIXELtoXLOCAL(CHIPID,IMPIXEL,LOCAL);
    XLOCAL[0]=IMPIXEL[0];
    XLOCAL[1]=IMPIXEL[1];

    return XLOCAL;
}
//-----------------------------------------------------------------
//Getting Functions : GRID POSITIONs
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLGET_POSITION_RADECfromLOCALGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID){
    int CHIPID;
    double LOCAL[2],RD[2];
    std::vector< double > RADEC(4);
    std::vector< std::vector< double > > GRIDRADEC;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    for(LOCAL[0]=GRID[0];LOCAL[0]<GRID[2]+0.5*GRID[4];LOCAL[0]+=GRID[4])
    for(LOCAL[1]=GRID[1];LOCAL[1]<GRID[3]+0.5*GRID[5];LOCAL[1]+=GRID[5]){
//    WCSA_ASP->GSIP->CSIP[CHIPID].F_WCSA_CSIP_XLOCALtoXRADEC(LOCAL,RD);
    WCSA_ASP->GSIP->F_WCSA_GSIP_XLOCALtoXRADEC(CHIPID,LOCAL,RD);
        RADEC[0]=LOCAL[0];
        RADEC[1]=LOCAL[1];
        RADEC[2]=RD[0];
        RADEC[3]=RD[1];
        GRIDRADEC.push_back(RADEC);
    }

    return GRIDRADEC;
}
std::vector< std::vector< double > > F_WCSA_PLGET_POSITION_RADECfromCRPIXGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID){
    int CHIPID;
    double CRPIX[2],RD[2];
    std::vector< double > RADEC(4);
    std::vector< std::vector< double > > GRIDRADEC;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    for(CRPIX[0]=GRID[0];CRPIX[0]<GRID[2]+0.5*GRID[4];CRPIX[0]+=GRID[4])
    for(CRPIX[1]=GRID[1];CRPIX[1]<GRID[3]+0.5*GRID[5];CRPIX[1]+=GRID[5]){
        WCSA_ASP->GSIP->F_WCSA_GSIP_XCRPIXtoXRADEC(CHIPID,CRPIX,RD);
        RADEC[0]=CRPIX[0];
        RADEC[1]=CRPIX[1];
        RADEC[2]=RD[0];
        RADEC[3]=RD[1];
        GRIDRADEC.push_back(RADEC);
    }

    return GRIDRADEC;
}
std::vector< std::vector< double > > F_WCSA_PLGET_POSITION_LOCALfromRADECGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID){
    int CHIPID;
    double RADEC[2],RD[2];
    std::vector< double > LOCAL(4);
    std::vector< std::vector< double > > GRIDLOCAL;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    for(RADEC[0]=GRID[0];RADEC[0]<GRID[2]+0.5*GRID[4];RADEC[0]+=GRID[4])
    for(RADEC[1]=GRID[1];RADEC[1]<GRID[3]+0.5*GRID[5];RADEC[1]+=GRID[5]){
        WCSA_ASP->GSIP->F_WCSA_GSIP_XRADECtoXLOCAL(CHIPID,RADEC,RD);
        LOCAL[0]=RADEC[0];
        LOCAL[1]=RADEC[1];
        LOCAL[2]=RD[0];
        LOCAL[3]=RD[1];
        GRIDLOCAL.push_back(LOCAL);
    }

    return GRIDLOCAL;
}
std::vector< std::vector< double > > F_WCSA_PLGET_POSITION_CRPIXfromRADECGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID){
    int CHIPID;
    double RADEC[2],RD[2];
    std::vector< double > CRPIX(4);
    std::vector< std::vector< double > > GRIDCRPIX;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    for(RADEC[0]=GRID[0];RADEC[0]<GRID[2]+0.5*GRID[4];RADEC[0]+=GRID[4])
    for(RADEC[1]=GRID[1];RADEC[1]<GRID[3]+0.5*GRID[5];RADEC[1]+=GRID[5]){
        WCSA_ASP->GSIP->F_WCSA_GSIP_XRADECtoXLOCAL(CHIPID,RADEC,RD);
        CRPIX[0]=RADEC[0];
        CRPIX[1]=RADEC[1];
        CRPIX[2]=RD[0];
        CRPIX[3]=RD[1];
        GRIDCRPIX.push_back(CRPIX);
    }

    return GRIDCRPIX;
}
//-----------------------------------------------------------------
//Getting Functions : GRID JACOBIANs
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLGET_CRSMA_atLOCALGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID){
    int CHIPID;
    double LOCAL[2],RD[6];
    std::vector< double > CRSMA(8);
    std::vector< std::vector< double > > GRIDCRSMA;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    for(LOCAL[0]=GRID[0];LOCAL[0]<GRID[2]+0.5*GRID[4];LOCAL[0]+=GRID[4])
    for(LOCAL[1]=GRID[1];LOCAL[1]<GRID[3]+0.5*GRID[5];LOCAL[1]+=GRID[5]){
//    WCSA_ASP->GSIP->CSIP[CHIPID].F_WCSA_CSIP_XLOCALtoXRADEC(LOCAL,RD);
    WCSA_ASP->GSIP->F_WCSA_GSIP_CRSMAatXLOCAL(CHIPID,LOCAL,RD);
        CRSMA[0]=LOCAL[0];
        CRSMA[1]=LOCAL[1];
        CRSMA[2]=RD[0];
        CRSMA[3]=RD[1];
        CRSMA[4]=RD[2];
        CRSMA[5]=RD[3];
        CRSMA[6]=RD[4];
        CRSMA[7]=RD[5];
        GRIDCRSMA.push_back(CRSMA);
    }

    return GRIDCRSMA;
}
std::vector< std::vector< double > > F_WCSA_PLGET_CRSMA_atCRPIXGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID){
}
std::vector< std::vector< double > > F_WCSA_PLGET_CRSMA_atRADECGRID(CL_WCSA_ASP* WCSA_ASP,int CID,std::vector< double > GRID){
}
std::vector< std::vector< double > > F_WCSA_PLGET_CRSM_atLOCALGRID(CL_WCSA_ASP* WCSA_ASP,int CID,int CRSMID,std::vector< double > X,std::vector< double > Y){
    int CHIPID,intX,intY;
    double LOCAL[2],CRSM[6],OUTDATA;
    std::vector< double > VCRSM_YFIX;
    std::vector< std::vector< double > > VCRSM;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CHIPID=CID;
    }else{
        CHIPID=WCSA_ASP->APROP->CCDNUM;
    }

    LOCAL[0]=0.5*(X[0]+X[X.size()]);
    LOCAL[1]=0.5*(Y[0]+Y[Y.size()]);
    WCSA_ASP->GSIP->F_WCSA_GSIP_CRSMAatXLOCAL(CHIPID,LOCAL,CRSM);
    OUTDATA=CRSM[CRSMID];
    for(intY=0;intY<Y.size();intY++){
    for(intX=0;intX<X.size();intX++){
	LOCAL[0]=X[intX];
	LOCAL[1]=Y[intY];
        if(hypot(LOCAL[0],LOCAL[1])<20000){
        WCSA_ASP->GSIP->F_WCSA_GSIP_CRSMAatXLOCAL(CHIPID,LOCAL,CRSM);
	VCRSM_YFIX.push_back(CRSM[CRSMID]);
        }else{
        VCRSM_YFIX.push_back(OUTDATA);
        }
    }
        VCRSM.push_back(VCRSM_YFIX);
        VCRSM_YFIX.clear();
    }

    return VCRSM;
}
//-----------------------------------------------------------------
//Getting Functions : GRID DISTORTIONs 
//-----------------------------------------------------------------
std::vector< std::vector< double > > F_WCSA_PLGET_DISTORTION_atCRPIXGRID(CL_WCSA_ASP* WCSA_ASP,std::vector< double > GRID){
    double CRPIX[2],RD[2],RDINIT[2];
    std::vector< double > RADEC(6);
    std::vector< std::vector< double > > GRIDRADEC;

    for(CRPIX[0]=GRID[0];CRPIX[0]<GRID[2]+0.5*GRID[4];CRPIX[0]+=GRID[4])
    for(CRPIX[1]=GRID[1];CRPIX[1]<GRID[3]+0.5*GRID[5];CRPIX[1]+=GRID[5]){
        WCSA_ASP->GSIP->F_WCSA_GSIP_XCRPIXtoXRADEC(WCSA_ASP->APROP->CCDNUM,CRPIX,RD);
        WCSA_ASP->GSIP->F_WCSA_GSIP_XCRPIXtoXRADEC(-1,CRPIX,RDINIT);
        RADEC[0]=CRPIX[0];
        RADEC[1]=CRPIX[1];
        RADEC[2]=RD[0];
        RADEC[3]=RD[1];
        RADEC[4]=RDINIT[0];
        RADEC[5]=RDINIT[1];
        GRIDRADEC.push_back(RADEC);
    }

    return GRIDRADEC;
}
std::vector< std::vector< double > > F_WCSA_PLGET_DISTORTION_atRADECGRID(CL_WCSA_ASP* WCSA_ASP,std::vector< double > GRID){
    double RADEC[2],RD[2],RDINIT[2];
    std::vector< double > CRPIX(6);
    std::vector< std::vector< double > > GRIDCRPIX;

    for(RADEC[0]=GRID[0];RADEC[0]<GRID[2]+0.5*GRID[4];RADEC[0]+=GRID[4])
    for(RADEC[1]=GRID[1];RADEC[1]<GRID[3]+0.5*GRID[5];RADEC[1]+=GRID[5]){
        WCSA_ASP->GSIP->F_WCSA_GSIP_XRADECtoXCRPIX(WCSA_ASP->APROP->CCDNUM,RADEC,RD);
        WCSA_ASP->GSIP->F_WCSA_GSIP_XRADECtoXCRPIX(-1,RADEC,RDINIT);
        CRPIX[0]=RADEC[0];
        CRPIX[1]=RADEC[1];
        CRPIX[2]=RD[0];
        CRPIX[3]=RD[1];
        CRPIX[4]=RDINIT[0];
        CRPIX[5]=RDINIT[1];
        GRIDCRPIX.push_back(CRPIX);
    }

    return GRIDCRPIX;
}
//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : REFERNCE
//-----------------------------------------------------------------
std::vector< double > F_WCSA_PLGET_REF_ID(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_ID;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_ID.push_back(WCSA_ASP->APAIR->PAIR[RID].ID);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_ID.push_back(WCSA_ASP->APAIR->PAIR[RID].ID);
    }

    return REFINFO_ID;
}
std::vector< double > F_WCSA_PLGET_REF_CHIPID(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CHIPID;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CHIPID.push_back(WCSA_ASP->APAIR->PAIR[RID].CHIPID);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CHIPID.push_back(WCSA_ASP->APAIR->PAIR[RID].CHIPID);
    }

    return REFINFO_CHIPID;
}
std::vector< double > F_WCSA_PLGET_REF_FLAG(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_FLAG;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_FLAG.push_back(WCSA_ASP->APAIR->PAIR[RID].FLAG);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_FLAG.push_back(WCSA_ASP->APAIR->PAIR[RID].FLAG);
    }

    return REFINFO_FLAG;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYLOCAL(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYLOCAL(2);
    std::vector< std::vector< double > > REFINFO_XYLOCALS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYLOCAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[0];
            REFINFO_XYLOCAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[1];
            REFINFO_XYLOCALS.push_back(REFINFO_XYLOCAL);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYLOCAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[0];
            REFINFO_XYLOCAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[1];
            REFINFO_XYLOCALS.push_back(REFINFO_XYLOCAL);
        }
    }

    return REFINFO_XYLOCALS;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYRADEC(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYRADEC(2);
    std::vector< std::vector< double > > REFINFO_XYRADECS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYRADEC[0]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[0];
            REFINFO_XYRADEC[1]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[1];
            REFINFO_XYRADECS.push_back(REFINFO_XYRADEC);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYRADEC[0]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[0];
            REFINFO_XYRADEC[1]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[1];
            REFINFO_XYRADECS.push_back(REFINFO_XYRADEC);
        }
    }

    return REFINFO_XYRADECS;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYGLOBAL(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYGLOBAL(2);
    std::vector< std::vector< double > > REFINFO_XYGLOBALS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYGLOBAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[0];
            REFINFO_XYGLOBAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[1];
            REFINFO_XYGLOBALS.push_back(REFINFO_XYGLOBAL);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYGLOBAL[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[0];
            REFINFO_XYGLOBAL[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[1];
            REFINFO_XYGLOBALS.push_back(REFINFO_XYGLOBAL);
        }
    }

    return REFINFO_XYGLOBALS;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYGLOBALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYGLOBALCRPIX(2);
    std::vector< std::vector< double > > REFINFO_XYGLOBALCRPIXS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYGLOBALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[0];
            REFINFO_XYGLOBALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[1];
            REFINFO_XYGLOBALCRPIXS.push_back(REFINFO_XYGLOBALCRPIX);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYGLOBALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[0];
            REFINFO_XYGLOBALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[1];
            REFINFO_XYGLOBALCRPIXS.push_back(REFINFO_XYGLOBALCRPIX);
        }
    }

    return REFINFO_XYGLOBALCRPIXS;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYLOCALCRPIX(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYLOCALCRPIX(2);
    std::vector< std::vector< double > > REFINFO_XYLOCALCRPIXS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYLOCALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[0];
            REFINFO_XYLOCALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[1];
            REFINFO_XYLOCALCRPIXS.push_back(REFINFO_XYLOCALCRPIX);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYLOCALCRPIX[0]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[0];
            REFINFO_XYLOCALCRPIX[1]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[1];
            REFINFO_XYLOCALCRPIXS.push_back(REFINFO_XYLOCALCRPIX);
        }
    }

    return REFINFO_XYLOCALCRPIXS;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYIMPIXEL(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYIMPIXEL(2);
    std::vector< std::vector< double > > REFINFO_XYIMPIXELS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYIMPIXEL[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[0];
            REFINFO_XYIMPIXEL[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[1];
            REFINFO_XYIMPIXELS.push_back(REFINFO_XYIMPIXEL);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYIMPIXEL[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[0];
            REFINFO_XYIMPIXEL[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[1];
            REFINFO_XYIMPIXELS.push_back(REFINFO_XYIMPIXEL);
        }
    }

    return REFINFO_XYIMPIXELS;
}
std::vector< std::vector< double > > F_WCSA_PLGET_REF_XYIMWORLD(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_XYIMWORLD(2);
    std::vector< std::vector< double > > REFINFO_XYIMWORLDS;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID){
            REFINFO_XYIMWORLD[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[0];
            REFINFO_XYIMWORLD[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[1];
            REFINFO_XYIMWORLDS.push_back(REFINFO_XYIMWORLD);
        }
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++){
            REFINFO_XYIMWORLD[0]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[0];
            REFINFO_XYIMWORLD[1]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[1];
            REFINFO_XYIMWORLDS.push_back(REFINFO_XYIMWORLD);
        }
    }

    return REFINFO_XYIMWORLDS;
}
std::vector< double > F_WCSA_PLGET_REF_CAMERACONV(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERACONV;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERACONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[0]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERACONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[0]);
    }

    return REFINFO_CAMERACONV;
}
std::vector< double > F_WCSA_PLGET_REF_CAMERAROT(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAROT;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[1]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[1]);
    }

    return REFINFO_CAMERAROT;
}
std::vector< double > F_WCSA_PLGET_REF_CAMERASHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERASHEAR1;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERASHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[0]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERASHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[0]);
    }

    return REFINFO_CAMERASHEAR1;
}
std::vector< double > F_WCSA_PLGET_REF_CAMERASHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERASHEAR2;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERASHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[1]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERASHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[1]);
    }

    return REFINFO_CAMERASHEAR2;
}
std::vector< double > F_WCSA_PLGET_REF_CAMERAMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAMAGNIFICATION;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_MAGNIFICATION);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_MAGNIFICATION);
    }

    return REFINFO_CAMERAMAGNIFICATION;
}
std::vector< double > F_WCSA_PLGET_REF_CAMERAPCONV(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAPCONV;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAPCONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[0]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAPCONV.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[0]);
    }

    return REFINFO_CAMERAPCONV;
}
std::vector< double > F_WCSA_PLGET_REF_CAMERAPROT(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAPROT;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAPROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[1]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAPROT.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[1]);
    }

    return REFINFO_CAMERAPROT;
}
std::vector< double > F_WCSA_PLGET_REF_CAMERAPSHEAR1(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAPSHEAR1;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAPSHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[0]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAPSHEAR1.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[0]);
    }

    return REFINFO_CAMERAPSHEAR1;
}
std::vector< double > F_WCSA_PLGET_REF_CAMERAPSHEAR2(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAPSHEAR2;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAPSHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[1]);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAPSHEAR2.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[1]);
    }

    return REFINFO_CAMERAPSHEAR2;
}
std::vector< double > F_WCSA_PLGET_REF_CAMERAPMAGNIFICATION(CL_WCSA_ASP* WCSA_ASP, int CID){
    int RID;
    std::vector< double > REFINFO_CAMERAPMAGNIFICATION;

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        if(WCSA_ASP->APAIR->PAIR[RID].CHIPID==CID)
        REFINFO_CAMERAPMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PMAGNIFICATION);
    }else{
        for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
        REFINFO_CAMERAPMAGNIFICATION.push_back(WCSA_ASP->APAIR->PAIR[RID].CAMERA_PMAGNIFICATION);
    }

    return REFINFO_CAMERAPMAGNIFICATION;
}

std::vector< double > F_WCSA_PLGET_REF(CL_WCSA_ASP* WCSA_ASP, boost::int64_t REFID){
    int RID,CHECK=0,i;
    std::vector< double > REFINFO(27);

    for(RID=0;RID<WCSA_ASP->APROP->ALLREFNUM-0.5;RID++)
    if(REFID==WCSA_ASP->APAIR->PAIR[RID].ID){
        REFINFO[ 0]=WCSA_ASP->APAIR->PAIR[RID].ID;
        REFINFO[ 1]=WCSA_ASP->APAIR->PAIR[RID].CHIPID;
        REFINFO[ 2]=WCSA_ASP->APAIR->PAIR[RID].FLAG;
        REFINFO[ 3]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[0];
        REFINFO[ 4]=WCSA_ASP->APAIR->PAIR[RID].X_LOCAL[1];
        REFINFO[ 5]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[0];
        REFINFO[ 6]=WCSA_ASP->APAIR->PAIR[RID].X_RADEC[1];
        REFINFO[ 7]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[0];
        REFINFO[ 8]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBAL[1];
        REFINFO[ 9]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[0];
        REFINFO[10]=WCSA_ASP->APAIR->PAIR[RID].X_GLOBALCRPIX[1];
        REFINFO[11]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[0];
        REFINFO[12]=WCSA_ASP->APAIR->PAIR[RID].X_LOCALCRPIX[1];
        REFINFO[13]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[0];
        REFINFO[14]=WCSA_ASP->APAIR->PAIR[RID].X_IM_WORLD[1];
        REFINFO[15]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[0];
        REFINFO[16]=WCSA_ASP->APAIR->PAIR[RID].X_IM_PIXEL[1];
        REFINFO[17]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[0];
        REFINFO[18]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_CONVROT[1];
        REFINFO[19]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[0];
        REFINFO[20]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_SHEAR[1];
        REFINFO[21]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_MAGNIFICATION;
        REFINFO[22]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[0];
        REFINFO[23]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_PCONVROT[1];
        REFINFO[24]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[0];
        REFINFO[25]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_PSHEAR[1];
        REFINFO[26]=WCSA_ASP->APAIR->PAIR[RID].CAMERA_PMAGNIFICATION;
        CHECK=1;
        break;
    }
    if(CHECK==0){
        cout << "Warning : in WCS_GET_REFERENCE_INIDIVIDUAL(F_WCSA_PLGET_REF)" << endl;
        cout << "        : There is no reference having ID = " << REFID << endl;
        for(i=0;i<27;i++)
        REFINFO[i]=0;
    }

    return REFINFO;
}

//-----------------------------------------------------------------
//Getting Functions : WCSA_ASP : CCD
//-----------------------------------------------------------------
/*std::vector< std::vector< double > >F_WCSA_PLMAIN_GETCCDPOSITIONS(CL_WCSA_ASP* WCSA_ASP){
    std::vector< std::vector< double > > CCDPOSITIONS;
    std::vector< double > CCDPOSITION(4);
    int CID;

    for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++){
        CCDPOSITION[0]=WCSA_ASP->GSIP->CSIP[CID].ID;
        CCDPOSITION[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0];
        CCDPOSITION[2]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1];
        CCDPOSITION[3]=WCSA_ASP->GSIP->CSIP[CID].GPOS[2];
        CCDPOSITIONS.push_back(CCDPOSITION);

    }
    
    return CCDPOSITIONS;
}
std::vector< double > F_WCSA_PLMAIN_GETCCDPOSITION(CL_WCSA_ASP* WCSA_ASP,int CID){
    std::vector< double > CCDPOSITION(4);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CCDPOSITION[0]=WCSA_ASP->GSIP->CSIP[CID].ID;
        CCDPOSITION[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0];
        CCDPOSITION[2]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1];
        CCDPOSITION[3]=WCSA_ASP->GSIP->CSIP[CID].GPOS[2];
    }else{
        cout << "Warning : in WCS_GET_CCD_CCD_CCDPOS(F_WCSA_PLMAIN_GETCCDPOSITIONS)" << endl;
        cout << "        : CID must be between 0 and " << WCSA_ASP->APROP->CCDNUM-1 << endl;
        cout << "        : but assinged " << CID << endl;
        CCDPOSITION[0]=CCDPOSITION[1]=CCDPOSITION[2]=CCDPOSITION[3]=0;
    }
    
    return CCDPOSITION;
}*/
std::vector< std::vector< double > > F_WCSA_PLGET_CCDPOSITIONS(CL_WCSA_ASP* WCSA_ASP,int CID){
    std::vector< std::vector< double > > CCDPOSITIONS;
    std::vector< double > CCDPOSITION(4);

    if(CID>-0.5&&CID<WCSA_ASP->APROP->CCDNUM-0.5){
        CCDPOSITION[0]=WCSA_ASP->GSIP->CSIP[CID].ID;
        CCDPOSITION[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0];
        CCDPOSITION[2]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1];
        CCDPOSITION[3]=WCSA_ASP->GSIP->CSIP[CID].GPOS[2];
        CCDPOSITIONS.push_back(CCDPOSITION);
        return CCDPOSITIONS;
    }else{
        for(CID=0;CID<WCSA_ASP->APROP->CCDNUM;CID++){
            CCDPOSITION[0]=WCSA_ASP->GSIP->CSIP[CID].ID;
            CCDPOSITION[1]=WCSA_ASP->GSIP->CSIP[CID].GPOS[0];
            CCDPOSITION[2]=WCSA_ASP->GSIP->CSIP[CID].GPOS[1];
            CCDPOSITION[3]=WCSA_ASP->GSIP->CSIP[CID].GPOS[2];
            CCDPOSITIONS.push_back(CCDPOSITION);
        }
        return CCDPOSITIONS;
    }    
}
