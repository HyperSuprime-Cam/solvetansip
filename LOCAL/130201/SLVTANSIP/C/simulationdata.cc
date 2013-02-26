#include<iostream>
#include<fstream>
#include<cstring>
#include<stdlib.h>
#include<cmath>

using namespace std;
void    F_InvPROJECTION(double *Pdeg,double *Cdeg,double *PPOINT);
int main(int argc,char *argv[]){
	double GPOS[100][3];
	double LOCAL[2],CRPIX[2],IMW[2],IMP[2],RADEC[2];
	double CD[2][2];
	double SIP[2][10][10];
	char fin[3][100],fccd[100];
	int x[2],dx[2],i,j,CID;
	ifstream in;
	in.open(argv[1]);
	
	while((in>>fin[0]>>fin[1]>>fin[2])!=0){
		if(strcmp("ICD_1_1:",fin[0])==0)
		CD[0][0]=atof(fin[1]);
		if(strcmp("ICD_1_2:",fin[0])==0)
		CD[0][1]=atof(fin[1]);
		if(strcmp("ICD_2_1:",fin[0])==0)
		CD[1][0]=atof(fin[1]);
		if(strcmp("ICD_2_2:",fin[0])==0)
		CD[1][1]=atof(fin[1]);
		for(i=0;i<100;i++){
			sprintf(fccd,"HSCIGPOS%03d_X:",i);
			if(strcmp(fccd,fin[0])==0)
			GPOS[i][0]=atof(fin[1]);
			sprintf(fccd,"HSCIGPOS%03d_Y:",i);
			if(strcmp(fccd,fin[0])==0)
			GPOS[i][1]=atof(fin[1]);
			sprintf(fccd,"HSCIGPOS%03d_T:",i);
			if(strcmp(fccd,fin[0])==0)
			GPOS[i][2]=atof(fin[1]);
		}
		for(i=0;i<10;i++)
		for(j=0;j<10;j++){
			sprintf(fccd,"IA_%d_%d:",i,j);
			if(strcmp(fccd,fin[0])==0)
			SIP[0][i][j]=atof(fin[1]);
			sprintf(fccd,"IB_%d_%d:",i,j);
			if(strcmp(fccd,fin[0])==0)
			SIP[1][i][j]=atof(fin[1]);
		}
	}
	dx[0]=200;
	dx[1]=400;
	dx[0]=400;
	dx[1]=800;
	double CRVAL[2];
	CRVAL[0]=CRVAL[1]=0;
	int ID=0;
	for(CID=0;CID<100;CID++)
	for(x[0]=0;x[0]<2048;x[0]+=dx[0])
	for(x[1]=0;x[1]<4096;x[1]+=dx[1]){
		CRPIX[0]=GPOS[CID][0]+x[0];
		CRPIX[1]=GPOS[CID][1]+x[1];
		IMW[0]=CD[0][0]*CRPIX[0]+CD[0][1]*CRPIX[1];
		IMW[1]=CD[1][0]*CRPIX[0]+CD[1][1]*CRPIX[1];
		F_InvPROJECTION(IMW,RADEC,CRVAL);
		cout <<ID << "	" << CID << "	" <<
			 x[0] << "	" << x[1] <<"	"<<
			RADEC[0] << "	" << RADEC[1] << endl;
		ID++;
	}
}
#define PI (4*atan(1.0))
#define LP 180
void    F_InvPROJECTION(double *Pdeg,double *Cdeg,double *PPOINT){
    double NRAD[2];//native psi,theta (RAD)
	
    NRAD[0]=atan2(Pdeg[0],-Pdeg[1]);	
    NRAD[1]=atan(180/PI/sqrt(Pdeg[0]*Pdeg[0]+Pdeg[1]*Pdeg[1]));
    if(NRAD[0]<0)
    NRAD[0]+=2*PI;                                     
    if(NRAD[0]>2*PI)
    NRAD[0]-=2*PI;

    Cdeg[1]=180/PI*asin(sin(NRAD[1])*sin(PPOINT[1]/180*PI)+cos(NRAD[1])*cos(NRAD[0]-LP/180*PI)*cos(PPOINT[1]/180*PI));//-90deg - 90deg
    Cdeg[0]=180/PI*atan2(-cos(NRAD[1])*sin(NRAD[0]-LP/180*PI),sin(NRAD[1])*cos(PPOINT[1]/180*PI)-cos(NRAD[1])*cos(NRAD[0]-LP/180*PI)*sin(PPOINT[1]/180*PI))+PPOINT[0];
}
