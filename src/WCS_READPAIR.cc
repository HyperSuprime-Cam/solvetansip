//------------------------------------------------------------
//WCS_READPAIR.cc
//calculating sky or CCD position
//
//Last modification : 2011/06/01
//------------------------------------------------------------
#include<vector>
#include "hsc/meas/tansip/WCS_READPAIR.h"
#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"


using namespace std;
namespace afwImage = lsst::afw::image;
void F_WCS_READPAIR_ID(CL_APROP *APROP, CL_PAIR *PAIR){
    int NUM;
    for(NUM=0;NUM<10;NUM++)
    cout << NUM << "	" << PAIR[NUM].ID << "	" << PAIR[NUM].FLAG << "	" << PAIR[NUM].xL << "	" << PAIR[NUM].yL << "	" << PAIR[NUM].RA << "	" << PAIR[NUM].DEC << endl;
    cout << "..." << endl;
    cout << "..." << endl;
    cout << "..." << endl;
    for(NUM=APROP->NUMREFALL-10;NUM<APROP->NUMREFALL;NUM++)
    cout << NUM << "	" << PAIR[NUM].ID << "	" << PAIR[NUM].FLAG << "	" << PAIR[NUM].xL << "	" << PAIR[NUM].yL << "	" << PAIR[NUM].RA << "	" << PAIR[NUM].DEC << endl;
}
