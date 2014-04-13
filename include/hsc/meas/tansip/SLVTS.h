//-----------------------------------------------------------
//SLVTS.h
//class solvetansip
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef SLVTS_H
#define SLVTS_H

#include<vector>
#include<string>

#include"hsc/meas/tansip/APRM.h"
#include"hsc/meas/tansip/CCD.h"
#include"hsc/meas/tansip/REF.h"

class CL_SLVTS{
private:
public:
	CL_APRM* APRM;//class anaysis parameters
	CL_CCDs* CCDs;//class CCDs 
	CL_REFs* REFs;//class references

//FUNCTIONs
	void SET_INIT();//setting initial values
	void SET_INPUT(std::vector< std::vector< std::vector< std::string > > > SLVTS_Argvs);//setting input information
	void SET_END();//deleting memories
	int  CHECK_INPUT();//checking input values
	void CALC_WCS();//main calculation of solvetansip
};

std::vector< CL_SLVTS* > SOLVETANSIP(std::vector< std::vector< std::vector< std::string > > > SLVTS_Argvs);//called by lsst for calculating solvetansip
void SET_END(std::vector< CL_SLVTS* > SOLVETANSIP);//called by lsst pipeline for destruction
#endif
