//--------------------------------------------------
//SLVTANSIP_ANA_FIT.cc
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#include<iostream>
#include<cmath>
#include"SLVTANSIP_ANA.h"

using namespace std;
void CL_ANA::DIV_ASIP(){
	double detCD;
	CCD[NUM_CCD].CD[0][0]=CCD[NUM_CCD].CDASIP[0][1*(ORDER_ASIP+1)+0];
	CCD[NUM_CCD].CD[0][1]=CCD[NUM_CCD].CDASIP[0][0*(ORDER_ASIP+1)+1];
	CCD[NUM_CCD].CD[1][0]=CCD[NUM_CCD].CDASIP[1][1*(ORDER_ASIP+1)+0];
	CCD[NUM_CCD].CD[1][1]=CCD[NUM_CCD].CDASIP[1][0*(ORDER_ASIP+1)+1];
	detCD=CCD[NUM_CCD].CD[0][0]*CCD[NUM_CCD].CD[1][1]-CCD[NUM_CCD].CD[1][0]*CCD[NUM_CCD].CD[0][1];
	CCD[NUM_CCD].InvCD[0][0]= CCD[NUM_CCD].CD[1][1]/detCD;
	CCD[NUM_CCD].InvCD[0][1]=-CCD[NUM_CCD].CD[0][1]/detCD;
	CCD[NUM_CCD].InvCD[1][0]=-CCD[NUM_CCD].CD[1][0]/detCD;
	CCD[NUM_CCD].InvCD[1][1]= CCD[NUM_CCD].CD[0][0]/detCD;

	int i,j,ij;
	ij=0;
	for(i=0;i<ORDER_ASIP+1;i++)
	for(j=0;j<ORDER_ASIP+1;j++)
	if(i+j<ORDER_ASIP+1){
	        CCD[NUM_CCD].ASIP[0][ij]=CCD[NUM_CCD].InvCD[0][0]*CCD[NUM_CCD].CDASIP[0][ij]+CCD[NUM_CCD].InvCD[0][1]*CCD[NUM_CCD].CDASIP[1][ij];
	        CCD[NUM_CCD].ASIP[1][ij]=CCD[NUM_CCD].InvCD[1][0]*CCD[NUM_CCD].CDASIP[0][ij]+CCD[NUM_CCD].InvCD[1][1]*CCD[NUM_CCD].CDASIP[1][ij];
	        ij++;	
	}
	CCD[NUM_CCD].ASIP[0][1*(ORDER_ASIP+1)+0]-=1.0;
	CCD[NUM_CCD].ASIP[1][0*(ORDER_ASIP+1)+1]-=1.0;

	CCD[NUM_CCD].ANGLE=atan2(CCD[NUM_CCD].CD[1][0]-(-1)*CCD[NUM_CCD].CD[0][1],(-1)*CCD[NUM_CCD].CD[0][0]+CCD[NUM_CCD].CD[1][1]);

}
void CL_ANA::DIV_PSIP(){
	double detCD;
	CCD[NUM_CCD].CDP[0][0]=CCD[NUM_CCD].CDPSIP[0][1*(ORDER_PSIP+1)+0];
	CCD[NUM_CCD].CDP[0][1]=CCD[NUM_CCD].CDPSIP[0][0*(ORDER_PSIP+1)+1];
	CCD[NUM_CCD].CDP[1][0]=CCD[NUM_CCD].CDPSIP[1][1*(ORDER_PSIP+1)+0];
	CCD[NUM_CCD].CDP[1][1]=CCD[NUM_CCD].CDPSIP[1][0*(ORDER_PSIP+1)+1];
	detCD=CCD[NUM_CCD].CDP[0][0]*CCD[NUM_CCD].CDP[1][1]-CCD[NUM_CCD].CDP[1][0]*CCD[NUM_CCD].CDP[0][1];
	CCD[NUM_CCD].InvCDP[0][0]= CCD[NUM_CCD].CDP[1][1]/detCD;
	CCD[NUM_CCD].InvCDP[0][1]=-CCD[NUM_CCD].CDP[0][1]/detCD;
	CCD[NUM_CCD].InvCDP[1][0]=-CCD[NUM_CCD].CDP[1][0]/detCD;
	CCD[NUM_CCD].InvCDP[1][1]= CCD[NUM_CCD].CDP[0][0]/detCD;

	int i,j,ij;
	ij=0;
	for(i=0;i<ORDER_PSIP+1;i++)
	for(j=0;j<ORDER_PSIP+1;j++)
	if(i+j<ORDER_PSIP+1){
	        CCD[NUM_CCD].PSIP[0][ij]=CCD[NUM_CCD].InvCDP[0][0]*CCD[NUM_CCD].CDPSIP[0][ij]+CCD[NUM_CCD].InvCDP[0][1]*CCD[NUM_CCD].CDPSIP[1][ij];
	        CCD[NUM_CCD].PSIP[1][ij]=CCD[NUM_CCD].InvCDP[1][0]*CCD[NUM_CCD].CDPSIP[0][ij]+CCD[NUM_CCD].InvCDP[1][1]*CCD[NUM_CCD].CDPSIP[1][ij];
	        ij++;	
	}
	CCD[NUM_CCD].PSIP[0][1*(ORDER_PSIP+1)+0]-=1.0;
	CCD[NUM_CCD].PSIP[1][0*(ORDER_PSIP+1)+1]-=1.0;
}
void CL_ANA::SET_PSIP(){
	CCD[NUM_CCD].PSIP[0][1*(ORDER_PSIP+1)+0]-=1.0;
	CCD[NUM_CCD].PSIP[1][0*(ORDER_PSIP+1)+1]-=1.0;
}
