//-----------------------------------------------------------
//APRM.h
//
//Last modification : 2014/01/01
//------------------------------------------------------------
#ifndef APRM_H
#define APRM_H

#include<vector>
#include<string>
#include<iostream>
#include<stdlib.h>

using namespace std;
class CL_APRM{
private:
public:
	string  INSTR;
	string	MODE_CR;
//CCD
	int	NUM_CCD;
	int	MODE_CCDPOS;
	double  PRECISION_CCD;//pixel
//REF
	int	NUM_REF;
	int	NUM_FIT;
	int	NUM_REJ;
	double	CRPIX[2];
	double	CRVAL[2];
	int	ORDER_ASIP;
	int	ORDER_PSIP;
	int	MODE_REJ;
	double	SIGMA_CLIP;

//OUTPUT
	int	FLAG_STD;
	int	FLAG_OUT;
	string	DIR_OUT;

//FUNCTIONs
	void SET_INIT();
	void SET_INPUT(std::vector< std::vector< std::string > > APRM_Argvs);
	void SHOW();
	int  CHECK();
	int  CHECK_MODECR();
	int  CHECK_ORDERASIP();
	int  CHECK_ORDERPSIP();
	void SET_END();
};
#endif