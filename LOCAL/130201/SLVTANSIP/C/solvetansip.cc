//--------------------------------------------------
//solvetanip.cc
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#include<iostream>
#include<stdio.h>
#include"SLVTANSIP_ANA.h"
#include"SLVTANSIP_CCD.h"
#include"SLVTANSIP_OBJ.h"

using namespace std;
int main(int argc,char *argv[]){
	CL_ANA *ANA;
	char prmfile[100],objfile[100];
	sprintf(prmfile,argv[1]);
	sprintf(objfile,argv[2]);
	
	ANA=new CL_ANA[1];
//SET DATA
	ANA->SET_DATA(prmfile,objfile);
	if(ANA->FLAG_ANA==0)return -1;
//SOLVE DATA
	ANA->SLV_DATA();
//SET EXTRA DATA
	if(ANA->EXTRACALC==1)
	ANA->EXT_DATA();
//OUTPUT DATA

	if(ANA->FILEOUT==1)
	ANA->OUT_DATA();

	ANA->DEL_MEMORY();
	delete [] ANA;
}
