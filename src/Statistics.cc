//--------------------------------------------------
//Calculating Average and RMS
//
//Last modification : 2010/10/10
//--------------------------------------------------
#include<iostream>      
#include<cmath>

using namespace std;
void	F_RMS(int NUM,double *data,double *STAT){
	int i;
	double SUM[2],VAR;

	if(NUM<2){
                cout << "---------------------------------------------" << endl;
		cout << "Error : Statistics.cc : Can't calculate RMS, because NUM of data is less than 2. NUM = : " << NUM << endl;
		cout << "return 0 " << endl;
                cout << "---------------------------------------------" << endl;
		STAT[0]=STAT[1]=0;
		return;
	}
	STAT[0]=STAT[1]=0;
	SUM[0]=SUM[1]=0;

	for(i=0;i<NUM;i++){
		SUM[0]+=data[i];
		SUM[1]+=data[i]*data[i];
	}
	STAT[0]=SUM[0]/i;
	VAR=(SUM[1]-SUM[0]*SUM[0]/i)/(i-1);
	STAT[1]=sqrt(VAR);

	return;
}
