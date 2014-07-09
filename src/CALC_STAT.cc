//--------------------------------------------------
//CALC_STST.cc
//
//Yuki Okura : yuki.okura@nao.ac.jp
//Last modification : 2014/01/01
//--------------------------------------------------
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
#define INFMIN pow(10.0,-10.0)
//Making Random values distributed Gaussian with RMS = 1.0
void	CALC_STAT_GAUSSUNIT(int srandNUM, int RNDNUM, double *RNDSET){
	int NUM,DIV;
	double RNDValue,RNDValue2;
	srand(srandNUM);

	for(NUM=0;NUM<RNDNUM;NUM++)
	RNDSET[NUM]=0;

	NUM=0;
	DIV=1000000;
	for(;;){
		RNDValue =10.0/DIV*(rand()%(DIV*2)-DIV);
		RNDValue2=1.0/DIV*(rand()%DIV);
		if(RNDValue2>INFMIN)
		if(RNDValue2<exp(-RNDValue*RNDValue)-exp(-10*10)){
			RNDSET[NUM]=RNDValue*sqrt(2);
			NUM++;
		}
		if(NUM>RNDNUM)
		break;
	}
}
#undef INFMIN
//Calculating Average and RMS
void	CALC_STAT_RMS(int NUM,double *data,double *STAT){
	int i;
	double SUM[3],VAR;

/*	if(NUM<2){
                cout << "---------------------------------------------" << endl;
		cout << "Error : Statistics.cc : Can't calculate RMS, because NUM of data is less than 2. NUM = : " << NUM << endl;
		cout << "return 0 " << endl;
                cout << "---------------------------------------------" << endl;
		STAT[0]=STAT[1]=0;
		return;
	}*/
	STAT[0]=STAT[1]=STAT[2]=0;
	SUM[0]=SUM[1]=SUM[2]=0;

	for(i=0;i<NUM;i++)
        if(isnan(data[i])||isinf(data[i])){
	}else{
		SUM[0]+=1;
		SUM[1]+=data[i];
		SUM[2]+=data[i]*data[i];
	}
	STAT[0]=SUM[0];
	STAT[1]=SUM[1]/SUM[0];
	VAR=(SUM[2]-SUM[1]*SUM[1]/SUM[0])/(SUM[0]-1);
	STAT[2]=sqrt(VAR);

	return;
}
//Calculating Average and RMS and MAXIMUM
void	CALC_STAT_RMSMAX(int NUM,double *data,double *STAT){
	int i;
	double SUM[3],VAR;

/*	if(NUM<2){
                cout << "---------------------------------------------" << endl;
		cout << "Error : Statistics.cc : Can't calculate RMS, because NUM of data is less than 2. NUM = : " << NUM << endl;
		cout << "return 0 " << endl;
                cout << "---------------------------------------------" << endl;
		STAT[0]=STAT[1]=0;
		return;
	}*/
	STAT[0]=STAT[1]=STAT[2]=STAT[3]=0;
	SUM[0]=SUM[1]=SUM[2]=0;

	for(i=0;i<NUM;i++)
        if(isnan(data[i])||isinf(data[i])){
	}else{
		SUM[0]+=1;
		SUM[1]+=data[i];
		SUM[2]+=data[i]*data[i];
                if(fabs(data[i])>STAT[3])
                STAT[3]=fabs(data[i]);
	}
	STAT[0]=SUM[0];
	STAT[1]=SUM[1]/SUM[0];
	VAR=(SUM[2]-SUM[1]*SUM[1]/SUM[0])/(SUM[0]-1);
	STAT[2]=sqrt(VAR);

	return;
}
