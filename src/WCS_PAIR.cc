//------------------------------------------------------------
//WCS_CPROP.cc
//
//Last modification : 2010/08/03
//------------------------------------------------------------
#include<fstream>//temp
#include<cmath>
#include<vector>
#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_CPROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "lsst/afw/detection/Source.h"
#include "lsst/afw/detection/SourceMatch.h"
#define PI (2*atan(1.0))
using namespace std;
namespace afwdetect = lsst::afw::detection;
void    F_MAKEPAIR(vector< vector<afwdetect::SourceMatch> > const &matchlist,CL_APROP *APROP,CL_CPROP* CPROP,CL_PAIR* PAIR){
    int CID,NUM,ALLNUM;
ofstream PAIRout("data/PAIR.dat");//temp

    ALLNUM=0;
    for(CID=0;CID<APROP->CCDNUM;CID++)
    for(NUM=0;NUM<CPROP[CID].NUM;NUM++){
        PAIR->refID[ALLNUM] =matchlist[CID][NUM].first->getId();
        PAIR->CHIPID[ALLNUM]=CID;
        PAIR->FLAG[ALLNUM]  =1;
        PAIR->RA[ALLNUM]    =matchlist[CID][NUM].first->getRa();
        PAIR->DEC[ALLNUM]   =matchlist[CID][NUM].first->getDec();
        PAIR->x[ALLNUM]     =matchlist[CID][NUM].second->getXAstrom()*cos(CPROP[CID].GLOB_POS[2]/180.0*PI)-matchlist[CID][NUM].second->getYAstrom()*sin(CPROP[CID].GLOB_POS[2]/180.0*PI)+CPROP[CID].GLOB_POS[0];
        PAIR->y[ALLNUM]     =matchlist[CID][NUM].second->getYAstrom()*cos(CPROP[CID].GLOB_POS[2]/180.0*PI)+matchlist[CID][NUM].second->getXAstrom()*sin(CPROP[CID].GLOB_POS[2]/180.0*PI)+CPROP[CID].GLOB_POS[1];
        PAIR->xErr[ALLNUM]  =matchlist[CID][NUM].second->getXAstromErr();
        PAIR->yErr[ALLNUM]  =matchlist[CID][NUM].second->getYAstromErr();
        PAIR->RAErr[ALLNUM] =1;
        PAIR->DECErr[ALLNUM]=1;
PAIRout << PAIR->refID[ALLNUM] << "	" << PAIR->FLAG[ALLNUM] << "	" << PAIR->x[ALLNUM] << "	" << PAIR->y[ALLNUM] << "	" << PAIR->RA[ALLNUM] << "	" << PAIR->DEC[ALLNUM] << endl;//temp
        ALLNUM+=1;
    }
    APROP->refNUM=ALLNUM;
PAIRout.close();//temp
}
#undef PI
