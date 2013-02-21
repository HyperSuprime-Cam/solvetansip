//--------------------------------------------------
//SLVTANSIP_OBJ.cc
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#include<iostream>
#include"SLVTANSIP_ANA.h"

using namespace std;

void CL_ANA::SHOW_OBJ(int ID){
	cout <<"--- OBJECT INFO : "<<ID<<" ---"<<endl;
	cout <<"OBJID		: "<<OBJ[ID].ID_OBJ<<endl;
	cout <<"CHIPID		: "<<OBJ[ID].ID_CHIP<<endl;
	cout <<"LOCAL_X		: "<<OBJ[ID].X_LOCAL[0]<<endl;
	cout <<"LOCAL_Y		: "<<OBJ[ID].X_LOCAL[1]<<endl;
	cout <<"GLOBAL_X	: "<<OBJ[ID].X_GLOBL[0]<<endl;
	cout <<"GLOBAL_Y	: "<<OBJ[ID].X_GLOBL[1]<<endl;
	cout <<"LOCALCRPIX_X	: "<<OBJ[ID].X_CRPIXLOCAL[0]<<endl;
	cout <<"LOCALCRPIX_Y	: "<<OBJ[ID].X_CRPIXLOCAL[1]<<endl;
	cout <<"GLOBALCRPIX_X	: "<<OBJ[ID].X_CRPIXGLOBL[0]<<endl;
	cout <<"GLOBALCRPIX_Y	: "<<OBJ[ID].X_CRPIXGLOBL[1]<<endl;
	cout <<"IM_PIXELLOCAL_X	: "<<OBJ[ID].X_IMPXLLOCAL[0]<<endl;
	cout <<"IM_PIXELLOCAL_Y	: "<<OBJ[ID].X_IMPXLLOCAL[1]<<endl;
	cout <<"IM_PIXELGLOBAL_X: "<<OBJ[ID].X_IMPXLGLOBL[0]<<endl;
	cout <<"IM_PIXELGLOBAL_Y: "<<OBJ[ID].X_IMPXLGLOBL[1]<<endl;
	cout <<"IM_WORLD_X	: "<<OBJ[ID].X_IMWLD[0]<<endl;
	cout <<"IM_WORLD_Y	: "<<OBJ[ID].X_IMWLD[1]<<endl;
	cout <<"RA		: "<<OBJ[ID].X_RADEC[0]<<endl;
	cout <<"DEC		: "<<OBJ[ID].X_RADEC[1]<<endl;
}

