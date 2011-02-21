//------------------------------------------------------------
//WCS_MAKEMATCHCATALOG.cc
//MAKE MATCH CATALOG for tansip
//
//Last modification : 2010/09/15
//------------------------------------------------------------
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<stdio.h>
#include"include/WCS_CPROP.h"

using namespace::std;
void    F_WCS_SETCC_CPROPfromFILE(char *CPROPFILE,CL_CPROP *CPROP);
void    F_SIP(int FR,int Order,double x[],double xSIP[],double CR[],double *SIP[2]);
void    F_PIXWCS_TAN(double x[],double CR[],double CD[][2]);
int main(){
    int i,j,ID;
    double CRVAL[2],CRPIX[2];
    double CD[2][2],*SIP[2],SIPPol[2][10][10]={0};
    CL_CPROP CPROP[104];
    char CPROPFILE[100],fout[100],fout2[100];
    ofstream out,out2;

    SIP[0] = new double[100];
    SIP[1] = new double[100];

int MAXORDER;
/*
    int NUMCCD=104;
    sprintf(CPROPFILE,"paf/WCS_MAKECPROP.paf");
    sprintf(fout,"pair/matchlist_HSC.dat");
    sprintf(fout2,"pair/matchlist_HSC_SUB.dat");
    MAXORDER=5;
*/
///*
    int NUMCCD=10;
    sprintf(CPROPFILE,"../paf/WCS_MAKECPROP_SC.paf");
    sprintf(fout,"../pair/matchlist_SC.dat");
    sprintf(fout2,"../pair/matchlist_SC_SUB.dat");
    MAXORDER=3;
//*/
/*
    int NUMCCD=2;
    sprintf(CPROPFILE,"paf/WCS_MAKECPROP_2.paf");
    sprintf(fout,"pair/matchlist_2.dat");
    sprintf(fout2,"pair/matchlist_2_SUB.dat");
    MAXORDER=3;
*/
//CPROP
    F_WCS_SETCC_CPROPfromFILE(CPROPFILE, CPROP);

// set parameter--------------------------------------------------
    out.open(fout);
    out2.open(fout2);
    out.setf(ios::scientific);
    out2.setf(ios::scientific);

    CRPIX[0]=0.000000;
    CRPIX[1]=0.000000;
    CRVAL[0]=5.000000;
    CRVAL[1]=5.000000;

cout << "CRPIX : " << CRPIX[0] << " , " << CRPIX[1] << endl;
cout << "CRVAL : " << CRVAL[0] << " , " << CRVAL[1] << endl;

    CD[0][0]=-0.0000467;
    CD[0][1]= 0.0000000;
    CD[1][0]= 0.0000000;
    CD[1][1]= 0.0000467;

cout << "CD_1_1 : " << CD[0][0] << endl;
cout << "CD_1_2 : " << CD[0][1] << endl;
cout << "CD_2_1 : " << CD[1][0] << endl;
cout << "CD_2_2 : " << CD[1][1] << endl;

    SIPPol[0][0][0]=0;
    SIPPol[0][1][0]=0;
    SIPPol[0][0][1]=0;
    SIPPol[0][2][0]=10*pow(20000,-2);
    SIPPol[0][1][1]=20*pow(20000,-2);
    SIPPol[0][0][2]=30*pow(20000,-2);
    SIPPol[0][3][0]=40*pow(20000,-3);
    SIPPol[0][2][1]=50*pow(20000,-3);
    SIPPol[0][1][2]=60*pow(20000,-3);
    SIPPol[0][0][3]=70*pow(20000,-3);
    SIPPol[0][4][0]=80*pow(20000,-4);
    SIPPol[0][3][1]=90*pow(20000,-4);
    SIPPol[0][2][2]=10*pow(20000,-4);
    SIPPol[0][1][3]=20*pow(20000,-4);
    SIPPol[0][0][4]=30*pow(20000,-4);
    SIPPol[0][5][0]=40*pow(20000,-5);
    SIPPol[0][4][1]=50*pow(20000,-5);
    SIPPol[0][3][2]=60*pow(20000,-5);
    SIPPol[0][2][3]=70*pow(20000,-5);
    SIPPol[0][1][4]=80*pow(20000,-5);
    SIPPol[0][0][5]=90*pow(20000,-5);/*
    SIPPol[0][6][0]= 6*pow(20000,-6);
    SIPPol[0][5][1]=0;
    SIPPol[0][4][2]=0;
    SIPPol[0][3][3]=0;
    SIPPol[0][2][4]=0;
    SIPPol[0][1][5]=0;
    SIPPol[0][0][6]=0;
    SIPPol[0][7][0]= 7*pow(20000,-7);
    SIPPol[0][6][1]=0;
    SIPPol[0][5][2]=0;
    SIPPol[0][4][3]=0;
    SIPPol[0][3][4]=0;
    SIPPol[0][2][5]=0;
    SIPPol[0][1][6]=0;
    SIPPol[0][0][7]=0;
    SIPPol[0][8][0]= 8*pow(20000,-8);
    SIPPol[0][7][1]=0;
    SIPPol[0][6][2]=0;
    SIPPol[0][5][3]=0;
    SIPPol[0][4][4]=0;
    SIPPol[0][3][5]=0;
    SIPPol[0][2][6]=0;
    SIPPol[0][1][7]=0;
    SIPPol[0][0][8]=0;
    SIPPol[0][9][0]= 9*pow(20000,-9);
    SIPPol[0][8][1]=0;
    SIPPol[0][7][2]=0;
    SIPPol[0][6][3]=0;
    SIPPol[0][5][4]=0;
    SIPPol[0][4][5]=0;
    SIPPol[0][3][6]=0;
    SIPPol[0][2][7]=0;
    SIPPol[0][1][8]=0;
    SIPPol[0][0][9]=0;*/

    SIPPol[1][0][0]=0;
    SIPPol[1][1][0]=0;
    SIPPol[1][0][1]=0;
    SIPPol[1][2][0]=10*pow(20000,-2);
    SIPPol[1][1][1]=20*pow(20000,-2);
    SIPPol[1][0][2]=30*pow(20000,-2);
    SIPPol[1][3][0]=40*pow(20000,-3);
    SIPPol[1][2][1]=50*pow(20000,-3);
    SIPPol[1][1][2]=60*pow(20000,-3);
    SIPPol[1][0][3]=70*pow(20000,-3);
    SIPPol[1][4][0]=80*pow(20000,-4);
    SIPPol[1][3][1]=90*pow(20000,-4);
    SIPPol[1][2][2]=10*pow(20000,-4);
    SIPPol[1][1][3]=20*pow(20000,-4);
    SIPPol[1][0][4]=30*pow(20000,-4);
    SIPPol[1][5][0]=40*pow(20000,-5);
    SIPPol[1][4][1]=50*pow(20000,-5);
    SIPPol[1][3][2]=60*pow(20000,-5);
    SIPPol[1][2][3]=70*pow(20000,-5);
    SIPPol[1][1][4]=80*pow(20000,-5);
    SIPPol[1][0][5]=90*pow(20000,-5);/*
    SIPPol[1][6][0]=0;
    SIPPol[1][5][1]=0;
    SIPPol[1][4][2]=0;
    SIPPol[1][3][3]=0;
    SIPPol[1][2][4]=0;
    SIPPol[1][1][5]=0;
    SIPPol[1][0][6]= 6*pow(20000,-6);
    SIPPol[1][7][0]=0;
    SIPPol[1][6][1]=0;
    SIPPol[1][5][2]=0;
    SIPPol[1][4][3]=0;
    SIPPol[1][3][4]=0;
    SIPPol[1][2][5]=0;
    SIPPol[1][1][6]=0;
    SIPPol[1][0][7]= 7*pow(20000,-7);
    SIPPol[1][8][0]=0;
    SIPPol[1][7][1]=0;
    SIPPol[1][6][2]=0;
    SIPPol[1][5][3]=0;
    SIPPol[1][4][4]=0;
    SIPPol[1][3][5]=0;
    SIPPol[1][2][6]=0;
    SIPPol[1][1][7]=0;
    SIPPol[1][0][8]= 8*pow(20000,-8);
    SIPPol[1][9][0]=0;
    SIPPol[1][8][1]=0;
    SIPPol[1][7][2]=0;
    SIPPol[1][6][3]=0;
    SIPPol[1][5][4]=0;
    SIPPol[1][4][5]=0;
    SIPPol[1][3][6]=0;
    SIPPol[1][2][7]=0;
    SIPPol[1][1][8]=0;
    SIPPol[1][0][9]= 9*pow(20000,-9);*/

cout << "--- SIP ---" << endl;
cout << "x : x^0,y^0 : " << SIPPol[0][0][0] << endl;
cout << "x : x^1,y^0 : " << SIPPol[0][1][0] << endl;
cout << "x : x^0,y^1 : " << SIPPol[0][0][1] << endl;
cout << "x : x^2,y^0 : " << SIPPol[0][2][0] << endl;
cout << "x : x^1,y^1 : " << SIPPol[0][1][1] << endl;
cout << "x : x^0,y^2 : " << SIPPol[0][0][2] << endl;
cout << "x : x^3,y^0 : " << SIPPol[0][3][0] << endl;
cout << "x : x^2,y^1 : " << SIPPol[0][2][1] << endl;
cout << "x : x^1,y^2 : " << SIPPol[0][1][2] << endl;
cout << "x : x^0,y^3 : " << SIPPol[0][0][3] << endl;
cout << "x : x^4,y^0 : " << SIPPol[0][4][0] << endl;
cout << "x : x^3,y^1 : " << SIPPol[0][3][1] << endl;
cout << "x : x^2,y^2 : " << SIPPol[0][2][2] << endl;
cout << "x : x^1,y^3 : " << SIPPol[0][1][3] << endl;
cout << "x : x^0,y^4 : " << SIPPol[0][0][4] << endl;
cout << "x : x^5,y^0 : " << SIPPol[0][5][0] << endl;
cout << "x : x^4,y^1 : " << SIPPol[0][4][1] << endl;
cout << "x : x^3,y^2 : " << SIPPol[0][3][2] << endl;
cout << "x : x^2,y^3 : " << SIPPol[0][2][3] << endl;
cout << "x : x^1,y^4 : " << SIPPol[0][1][4] << endl;
cout << "x : x^0,y^5 : " << SIPPol[0][0][5] << endl;/*
cout << "x : x^6,y^0 : " << SIPPol[0][6][0] << endl;
cout << "x : x^7,y^0 : " << SIPPol[0][7][0] << endl;
cout << "x : x^8,y^0 : " << SIPPol[0][8][0] << endl;
cout << "x : x^9,y^0 : " << SIPPol[0][9][0] << endl;*/

cout << "y : x^0,y^0 : " << SIPPol[1][0][0] << endl;
cout << "y : x^1,y^0 : " << SIPPol[1][1][0] << endl;
cout << "y : x^0,y^1 : " << SIPPol[1][0][1] << endl;
cout << "y : x^2,y^0 : " << SIPPol[1][2][0] << endl;
cout << "y : x^1,y^1 : " << SIPPol[1][1][1] << endl;
cout << "y : x^0,y^2 : " << SIPPol[1][0][2] << endl;
cout << "y : x^3,y^0 : " << SIPPol[1][3][0] << endl;
cout << "y : x^2,y^1 : " << SIPPol[1][2][1] << endl;
cout << "y : x^1,y^2 : " << SIPPol[1][1][2] << endl;
cout << "y : x^0,y^3 : " << SIPPol[1][0][3] << endl;
cout << "y : x^4,y^0 : " << SIPPol[1][4][0] << endl;
cout << "y : x^3,y^1 : " << SIPPol[1][3][1] << endl;
cout << "y : x^2,y^2 : " << SIPPol[1][2][2] << endl;
cout << "y : x^1,y^3 : " << SIPPol[1][1][3] << endl;
cout << "y : x^0,y^4 : " << SIPPol[1][0][4] << endl;
cout << "y : x^5,y^0 : " << SIPPol[1][5][0] << endl;
cout << "y : x^4,y^1 : " << SIPPol[1][4][1] << endl;
cout << "y : x^3,y^2 : " << SIPPol[1][3][2] << endl;
cout << "y : x^2,y^3 : " << SIPPol[1][2][3] << endl;
cout << "y : x^1,y^4 : " << SIPPol[1][1][4] << endl;
cout << "y : x^0,y^5 : " << SIPPol[1][0][5] << endl;/*
cout << "y : x^0,y^6 : " << SIPPol[1][0][6] << endl;
cout << "y : x^0,y^7 : " << SIPPol[1][0][7] << endl;
cout << "y : x^0,y^8 : " << SIPPol[1][0][8] << endl;
cout << "y : x^0,y^9 : " << SIPPol[1][0][9] << endl;*/

    int ij=0;
    for(i=0;i<MAXORDER+1;i++)
    for(j=0;j<MAXORDER+1;j++)
    if(i+j<MAXORDER+1){
        SIP[0][ij]=SIPPol[0][i][j];
        SIP[1][ij]=SIPPol[1][i][j];
        ij++;	
    }
//--------------------------------------------------
#define PI (4*atan(1.0))
#define LP 180

    int k;
    double Lxy[2],Gxy[2],GxySIP[4];
    double CR[4];

    CR[0]=CRPIX[0];
    CR[1]=CRPIX[1];
    CR[2]=CRVAL[0];
    CR[3]=CRVAL[1];

    k=0;
    for(ID=0;ID<NUMCCD;ID++)
    for(i=0;i<10;i++)
    for(j=0;j<10;j++){
        Lxy[0]=200*i;
        Lxy[1]=400*j;
        Gxy[0]=CPROP[ID].GLOB_POS[0]+(Lxy[0]*cos(CPROP[ID].GLOB_POS[2]/180.0*PI)-Lxy[1]*sin(CPROP[ID].GLOB_POS[2]/180.0*PI));
        Gxy[1]=CPROP[ID].GLOB_POS[1]+(Lxy[0]*sin(CPROP[ID].GLOB_POS[2]/180.0*PI)+Lxy[1]*cos(CPROP[ID].GLOB_POS[2]/180.0*PI));

        F_SIP(0,MAXORDER,Gxy,GxySIP,CR,SIP);
        F_PIXWCS_TAN(GxySIP,CR,CD);
        out << k << "	" << ID << "	" << Lxy[0] << "	" << Lxy[1] << "	" << GxySIP[2] << "	" << GxySIP[3] << endl;
        out2 << Gxy[0] << "	" << Gxy[1] << "	" << GxySIP[0] << "	" << GxySIP[1] << "	" << GxySIP[2] << "	" << GxySIP[3] << endl;
        k++;
    }


//--------------------------------------------------
    delete [] SIP[0];
    delete [] SIP[1];

}
void    F_SIP(int FR,int Order,double x[],double xSIP[],double CR[],double *SIP[2]){//detecting xSIP correcting by SIP
    int i,j,ij;

    xSIP[0]=x[0];
    xSIP[1]=x[1];
    ij=0;
    for(i=0;i<Order+1;i++)
    for(j=0;j<Order+1;j++)
    if(i+j<Order+1){
        if(i==0&&j==0){
        }else if(i==1&&j==0&&FR==0){
        }else if(i==0&&j==1&&FR==0){
        }else{
            xSIP[0]+=pow(x[0]-CR[0],i)*pow(x[1]-CR[1],j)*SIP[0][ij];
            xSIP[1]+=pow(x[0]-CR[0],i)*pow(x[1]-CR[1],j)*SIP[1][ij];
        }
        ij++;
    }
}
void    F_PIXWCS_TAN(double x[],double CR[],double CD[][2]){
    double Pdeg[2];//projected x,y (deg)
    double NRAD[2];//native psi,theta (RAD)
	
    Pdeg[0]=(x[0]-CR[0])*CD[0][0]+(x[1]-CR[1])*CD[0][1];
    Pdeg[1]=(x[0]-CR[0])*CD[1][0]+(x[1]-CR[1])*CD[1][1];

    NRAD[0]=atan2(Pdeg[0],-Pdeg[1]);	
    NRAD[1]=atan(180/PI/sqrt(Pdeg[0]*Pdeg[0]+Pdeg[1]*Pdeg[1]));
    if(NRAD[0]<0)
    NRAD[0]+=2*PI;                                     
    if(NRAD[0]>2*PI)
    NRAD[0]-=2*PI;

    x[3]=180/PI*asin(sin(NRAD[1])*sin(CR[3]/180*PI)+cos(NRAD[1])*cos(NRAD[0]-LP/180*PI)*cos(CR[3]/180*PI));//-90deg - 90deg
    x[2]=180/PI*atan2(-cos(NRAD[1])*sin(NRAD[0]-LP/180*PI),sin(NRAD[1])*cos(CR[3]/180*PI)-cos(NRAD[1])*cos(NRAD[0]-LP/180*PI)*sin(CR[3]/180*PI))+CR[2];
}               
#undef PI
#undef LP
