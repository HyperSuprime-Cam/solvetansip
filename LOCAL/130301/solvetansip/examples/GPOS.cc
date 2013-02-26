#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;
int main(){
	int i,j,NUM;
	double GPOS[3];
	double SUM[3][400];
	ifstream in;
		
	for(i=0;i<  3;i++)
	for(j=0;j<400;j++)	
	SUM[i][j]=0;

	in.open("matchlist_0902030/GPOS.dat");
	NUM=0;
	while((in >> GPOS[0] >> GPOS[1] >> GPOS[2])!=0){
		SUM[0][3*NUM+0]+=1;
		SUM[1][3*NUM+0]+=GPOS[0];
		SUM[2][3*NUM+0]+=GPOS[0]*GPOS[0];
		SUM[0][3*NUM+1]+=1;
		SUM[1][3*NUM+1]+=GPOS[1];
		SUM[2][3*NUM+1]+=GPOS[1]*GPOS[1];
		SUM[0][3*NUM+2]+=1;
		SUM[1][3*NUM+2]+=GPOS[2];
		SUM[2][3*NUM+2]+=GPOS[2]*GPOS[2];
		NUM++;
	}
	in.close();
	in.open("matchlist_0902034/GPOS.dat");
	NUM=0;
	while((in >> GPOS[0] >> GPOS[1] >> GPOS[2])!=0){
		SUM[0][3*NUM+0]+=1;
		SUM[1][3*NUM+0]+=GPOS[0];
		SUM[2][3*NUM+0]+=GPOS[0]*GPOS[0];
		SUM[0][3*NUM+1]+=1;
		SUM[1][3*NUM+1]+=GPOS[1];
		SUM[2][3*NUM+1]+=GPOS[1]*GPOS[1];
		SUM[0][3*NUM+2]+=1;
		SUM[1][3*NUM+2]+=GPOS[2];
		SUM[2][3*NUM+2]+=GPOS[2]*GPOS[2];
		NUM++;
	}
	in.close();
	in.open("matchlist_0902036/GPOS.dat");
	NUM=0;
	while((in >> GPOS[0] >> GPOS[1] >> GPOS[2])!=0){
		SUM[0][3*NUM+0]+=1;
		SUM[1][3*NUM+0]+=GPOS[0];
		SUM[2][3*NUM+0]+=GPOS[0]*GPOS[0];
		SUM[0][3*NUM+1]+=1;
		SUM[1][3*NUM+1]+=GPOS[1];
		SUM[2][3*NUM+1]+=GPOS[1]*GPOS[1];
		SUM[0][3*NUM+2]+=1;
		SUM[1][3*NUM+2]+=GPOS[2];
		SUM[2][3*NUM+2]+=GPOS[2]*GPOS[2];
		NUM++;
	}
	in.close();
	in.open("matchlist_0902038/GPOS.dat");
	NUM=0;
	while((in >> GPOS[0] >> GPOS[1] >> GPOS[2])!=0){
		SUM[0][3*NUM+0]+=1;
		SUM[1][3*NUM+0]+=GPOS[0];
		SUM[2][3*NUM+0]+=GPOS[0]*GPOS[0];
		SUM[0][3*NUM+1]+=1;
		SUM[1][3*NUM+1]+=GPOS[1];
		SUM[2][3*NUM+1]+=GPOS[1]*GPOS[1];
		SUM[0][3*NUM+2]+=1;
		SUM[1][3*NUM+2]+=GPOS[2];
		SUM[2][3*NUM+2]+=GPOS[2]*GPOS[2];
		NUM++;
	}
	in.close();
	in.open("matchlist_0902042/GPOS.dat");
	NUM=0;
	while((in >> GPOS[0] >> GPOS[1] >> GPOS[2])!=0){
		SUM[0][3*NUM+0]+=1;
		SUM[1][3*NUM+0]+=GPOS[0];
		SUM[2][3*NUM+0]+=GPOS[0]*GPOS[0];
		SUM[0][3*NUM+1]+=1;
		SUM[1][3*NUM+1]+=GPOS[1];
		SUM[2][3*NUM+1]+=GPOS[1]*GPOS[1];
		SUM[0][3*NUM+2]+=1;
		SUM[1][3*NUM+2]+=GPOS[2];
		SUM[2][3*NUM+2]+=GPOS[2]*GPOS[2];
		NUM++;
	}
	in.close();
	in.open("matchlist_0902050/GPOS.dat");
	NUM=0;
	while((in >> GPOS[0] >> GPOS[1] >> GPOS[2])!=0){
		SUM[0][3*NUM+0]+=1;
		SUM[1][3*NUM+0]+=GPOS[0];
		SUM[2][3*NUM+0]+=GPOS[0]*GPOS[0];
		SUM[0][3*NUM+1]+=1;
		SUM[1][3*NUM+1]+=GPOS[1];
		SUM[2][3*NUM+1]+=GPOS[1]*GPOS[1];
		SUM[0][3*NUM+2]+=1;
		SUM[1][3*NUM+2]+=GPOS[2];
		SUM[2][3*NUM+2]+=GPOS[2]*GPOS[2];
		NUM++;
	}
	in.close();

	for(i=0;i<NUM;i++)
	cout << i << "	" <<
		SUM[1][3*i+0]/SUM[0][3*i+0] << "	" <<
		sqrt((SUM[2][3*i+0]-SUM[1][3*i+0]*SUM[1][3*i+0]/SUM[0][3*i+0])/(SUM[0][3*i+0]-1)/(SUM[0][3*i+0])) << "	" <<
		SUM[1][3*i+1]/SUM[0][3*i+1] << "	" <<
		sqrt((SUM[2][3*i+1]-SUM[1][3*i+1]*SUM[1][3*i+1]/SUM[0][3*i+1])/(SUM[0][3*i+1]-1)/(SUM[0][3*i+1])) << "	" <<
		SUM[1][3*i+2]/SUM[0][3*i+2] << "	" <<
		sqrt((SUM[2][3*i+2]-SUM[1][3*i+2]*SUM[1][3*i+2]/SUM[0][3*i+2])/(SUM[0][3*i+2]-1)/(SUM[0][3*i+2])) << endl; 
		
}
