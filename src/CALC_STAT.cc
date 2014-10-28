//--------------------------------------------------
//CALC_STST.cc
//
//Yuki Okura : yuki.okura@nao.ac.jp
//Last modification : 2014/01/01
//--------------------------------------------------
#include <iostream>
#include <cmath>
#include <cstdlib>

namespace hsc { namespace meas {
namespace tansip {

using namespace std;

//Calculating Average and RMS
void	CALC_STAT_RMS(int NUM,double *data,double *STAT){
/*	if(NUM<2){
                cout << "---------------------------------------------" << endl;
		cout << "Error : Statistics.cc : Can't calculate RMS, because NUM of data is less than 2. NUM = : " << NUM << endl;
		cout << "return 0 " << endl;
                cout << "---------------------------------------------" << endl;
		STAT[0]=STAT[1]=0;
		return;
	}*/
	STAT[0]=STAT[1]=STAT[2]=0;

	double SUM[3] = {};

	for(int i=0;i<NUM;i++){
        if(isnan(data[i])||isinf(data[i])){
			;
		}else{
			SUM[0]+=1;
			SUM[1]+=data[i];
			SUM[2]+=data[i]*data[i];
		}
	}
	STAT[0]=SUM[0];
	STAT[1]=SUM[1]/SUM[0];
	double VAR=(SUM[2]-SUM[1]*SUM[1]/SUM[0])/(SUM[0]-1);
	STAT[2]=sqrt(VAR);

	return;
}
//Calculating Average and RMS and MAXIMUM
void	CALC_STAT_RMSMAX(int NUM,double *data,double *STAT){
/*	if(NUM<2){
                cout << "---------------------------------------------" << endl;
		cout << "Error : Statistics.cc : Can't calculate RMS, because NUM of data is less than 2. NUM = : " << NUM << endl;
		cout << "return 0 " << endl;
                cout << "---------------------------------------------" << endl;
		STAT[0]=STAT[1]=0;
		return;
	}*/
	STAT[0]=STAT[1]=STAT[2]=STAT[3]=0;

	double SUM[3] = {};

	for(int i=0;i<NUM;i++){
        if(isnan(data[i])||isinf(data[i])){
			;
		}else{
			SUM[0]+=1;
			SUM[1]+=data[i];
			SUM[2]+=data[i]*data[i];
			if(fabs(data[i])>STAT[3])
				STAT[3]=fabs(data[i]);
		}
	}
	STAT[0]=SUM[0];
	STAT[1]=SUM[1]/SUM[0];
	double VAR=(SUM[2]-SUM[1]*SUM[1]/SUM[0])/(SUM[0]-1);
	STAT[2]=sqrt(VAR);

	return;
}

} // namespace tansip
}} // namespace hsc::meas
