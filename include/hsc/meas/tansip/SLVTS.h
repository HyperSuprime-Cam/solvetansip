//-----------------------------------------------------------
//SLVTS.h
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef SLVTS_H
#define SLVTS_H

#include<vector>
#include<string>

// FH added - start
#include "lsst/pex/policy/Policy.h"
#include "lsst/afw/cameraGeom/Camera.h"
#include "lsst/afw/image/TanWcs.h"
#include"hsc/meas/tansip/SourceMatch.h"
// FH added - end

#include"hsc/meas/tansip/APRM.h"
#include"hsc/meas/tansip/CCD.h"
#include"hsc/meas/tansip/REF.h"

class CL_SLVTS{
private:
public:
	CL_APRM* APRM;
	CL_CCDs* CCDs;
	CL_REFs* REFs;

//FUNCTIONs
	void SET_INIT();
	void SET_INPUT(std::vector< std::vector< std::vector< std::string > > > SLVTS_Argvs);
	int  CHECK_INPUT();
	void CALC_WCS();
};

std::vector< CL_SLVTS* > SOLVETANSIP(std::vector< std::vector< std::vector< std::string > > > SLVTS_Argvs);
#endif
