//------------------------------------------------------------
//WCS_TANSIP_SUB.cc
//
//Last modification : 2010/11/15
//------------------------------------------------------------
#include<iostream>
#include<cmath>
#include "hsc/meas/tansip/WCS_TANSIP.h"

#define PI (4*atan(1.0))
using namespace std;

void    F_CDSIP(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,j,ij,FNUM;
    double xi[4],CR[4],InvCD[2][2],CRPIXAVE[2]={0};
    double x[4],xSIP[4],SUM[2][2]={0};
    double *Coef1,*Coef2,*CoefP1,*CoefP2,**dx1,**dx2;

    Coef1 = new double[(APROP.SIP_ORDER+2)*(APROP.SIP_ORDER+1)];
    Coef2 = new double[(APROP.SIP_ORDER+2)*(APROP.SIP_ORDER+1)];
    CoefP1= new double[(APROP.SIP_P_ORDER+2)*(APROP.SIP_P_ORDER+1)];
    CoefP2= new double[(APROP.SIP_P_ORDER+2)*(APROP.SIP_P_ORDER+1)];
    dx1= new double*[(APROP.NUMREFALL)+1];
    dx2= new double*[(APROP.NUMREFALL)+1];
    for(i=0;i<(APROP.NUMREFALL)+1;i++) {
    dx1[i] = new double[3];
    dx2[i] = new double[3];
    }
// measuring CRpix and CRval at CRpix --------------------------------------------------
    for(i=0;i<(APROP.SIP_ORDER+2)*(APROP.SIP_ORDER+1);i++){
        Coef1[i]=Coef2[i]=CoefP1[i]=CoefP2[i]=0;
    }
    for(i=0;i<(APROP.NUMREFALL)+1;i++)
    for(j=0;j<3;j++){
        dx1[i][j]=dx2[i][j]=0;
    }

    CSIP->SIP_AB_ORDER=APROP.SIP_ORDER;
    CSIP->SIP_ABP_ORDER=APROP.SIP_P_ORDER;
    CSIP->ID=APROP.CCDNUM;

    FNUM=0;
    for(i=0;i<APROP.NUMREFALL;i++)
    if(PAIR[i].FLAG == 1){
        dx1[FNUM][0]=dx2[FNUM][0]=PAIR[i].xG; 
        dx1[FNUM][1]=dx2[FNUM][1]=PAIR[i].yG; 
        dx1[FNUM][2]=PAIR[i].RA;
        dx2[FNUM][2]=PAIR[i].DEC;
        if(APROP.CRPIXMODE == "AUTO"){
            CRPIXAVE[0]+=PAIR[i].xG;
            CRPIXAVE[1]+=PAIR[i].yG;
        }  
        FNUM++;
    } 

    if(APROP.CRPIXMODE == "AUTO"){
        CRPIXAVE[0]/=FNUM;
        CRPIXAVE[1]/=FNUM;
        CSIP->CRPIX[0]=CRPIXAVE[0];
        CSIP->CRPIX[1]=CRPIXAVE[1];
    }else{
        CSIP->CRPIX[0]=APROP.CRPIX[0];
        CSIP->CRPIX[1]=APROP.CRPIX[1];
    }  

    for(i=0;i<(APROP.SIP_ORDER+2)*(APROP.SIP_ORDER+1);i++)
    Coef1[i]=Coef2[i]=0;
    F_LS2(FNUM,APROP.SIP_ORDER,dx1,Coef1);
    F_LS2(FNUM,APROP.SIP_ORDER,dx2,Coef2);

    CSIP->CRVAL[0]=CSIP->CRVAL[1]=0;
    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        CSIP->CRVAL[0]+=Coef1[ij]*pow(CSIP->CRPIX[0],i)*pow(CSIP->CRPIX[1],j);
        CSIP->CRVAL[1]+=Coef2[ij]*pow(CSIP->CRPIX[0],i)*pow(CSIP->CRPIX[1],j);
        ij++;	
    }

    CR[0]=CSIP->CRPIX[0];
    CR[1]=CSIP->CRPIX[1];
    CR[2]=CSIP->CRVAL[0];
    CR[3]=CSIP->CRVAL[1];

// measuring TANSIP at CRpix --------------------------------------------------

    CSIP->CD[0][0]=CSIP->CD[1][1]=1;
    CSIP->CD[0][1]=CSIP->CD[1][0]=0;

    FNUM=0;
    for(i=0;i<APROP.NUMREFALL;i++)
    if(PAIR[i].FLAG == 1){
        xi[2]=PAIR[i].RA;
        xi[3]=PAIR[i].DEC;
		
        F_WCSPIX_TAN(xi,CR,CSIP->CD);
        dx1[FNUM][0]=dx2[FNUM][0]=PAIR[i].xG-CR[0]; 
        dx1[FNUM][1]=dx2[FNUM][1]=PAIR[i].yG-CR[1]; 
        dx1[FNUM][2]=xi[0]-CR[0];
        dx2[FNUM][2]=xi[1]-CR[1];   
        FNUM++;
    }

    for(i=0;i<(APROP.SIP_ORDER+2)*(APROP.SIP_ORDER+1);i++)
    Coef1[i]=Coef2[i]=0;

    F_LS2(FNUM,APROP.SIP_ORDER,dx1,Coef1);
    F_LS2(FNUM,APROP.SIP_ORDER,dx2,Coef2);

    CSIP->CD[0][0]=Coef1[1*(APROP.SIP_ORDER+1)+0];
    CSIP->CD[0][1]=Coef1[0*(APROP.SIP_ORDER+1)+1];
    CSIP->CD[1][0]=Coef2[1*(APROP.SIP_ORDER+1)+0];
    CSIP->CD[1][1]=Coef2[0*(APROP.SIP_ORDER+1)+1]; 

    InvCD[0][0]= CSIP->CD[1][1]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    InvCD[0][1]=-CSIP->CD[0][1]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    InvCD[1][0]=-CSIP->CD[1][0]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);
    InvCD[1][1]= CSIP->CD[0][0]/(CSIP->CD[0][0]*CSIP->CD[1][1]-CSIP->CD[1][0]*CSIP->CD[0][1]);

    ij=0;
    for(i=0;i<APROP.SIP_ORDER+1;i++)
    for(j=0;j<APROP.SIP_ORDER+1;j++)
    if(i+j<APROP.SIP_ORDER+1){
        CSIP->SIP_AB[0][ij]=InvCD[0][0]*Coef1[ij]+InvCD[0][1]*Coef2[ij];
        CSIP->SIP_AB[1][ij]=InvCD[1][0]*Coef1[ij]+InvCD[1][1]*Coef2[ij];
        ij++;	
    }

    CSIP->SIP_AB[0][1*(APROP.SIP_ORDER+1)+0]-=1.0;
    CSIP->SIP_AB[1][0*(APROP.SIP_ORDER+1)+1]-=1.0;

    CSIP->FITNUM=FNUM;

// measuring InvTANSIP at CRpix --------------------------------------------------
    FNUM=0;
    for(i=0;i<APROP.NUMREFALL;i++)
    if(PAIR[i].FLAG == 1){
        xi[2]=PAIR[i].RA;
        xi[3]=PAIR[i].DEC;
	
        F_WCSPIX_TAN(xi,CR,CSIP->CD);
        dx1[FNUM][0]=dx2[FNUM][0]=xi[0]-CR[0]; 
        dx1[FNUM][1]=dx2[FNUM][1]=xi[1]-CR[1]; 
        dx1[FNUM][2]=PAIR[i].xG-CR[0];
        dx2[FNUM][2]=PAIR[i].yG-CR[1];   
        FNUM++;
    }   

    for(i=0;i<(APROP.SIP_P_ORDER+2)*(APROP.SIP_P_ORDER+1);i++)
    CoefP1[i]=CoefP2[i]=0;
    F_LS2(FNUM,APROP.SIP_P_ORDER,dx1,CoefP1);
    F_LS2(FNUM,APROP.SIP_P_ORDER,dx2,CoefP2);

    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        CSIP->SIP_ABP[0][ij]=CoefP1[ij];
        CSIP->SIP_ABP[1][ij]=CoefP2[ij];
        ij++;	
    }

    CSIP->SIP_ABP[0][1*(APROP.SIP_ORDER+1)+0]-=1.0;
    CSIP->SIP_ABP[1][0*(APROP.SIP_ORDER+1)+1]-=1.0;

//--------------------------------------------------

    delete [] Coef1;
    delete [] Coef2;
    delete [] CoefP1;
    delete [] CoefP2;
    for(i=0;i<(APROP.NUMREFALL)+1;i++){
    delete [] dx1[i];
    delete [] dx2[i];
    }
    delete [] dx1;
    delete [] dx2;
}
#define LP 180
void    F_WCSPIX_TAN(double x[],double CR[],double CD[][2]){
    double NRAD[2];//native psi,theta (RAD)
    double Pdeg[2];//projected x,y (deg)
    double CDMAT[2];              
	
    NRAD[1]=asin(sin(x[3]/180*PI)*sin(CR[3]/180*PI)+cos(x[3]/180*PI)*cos(CR[3]/180*PI)*cos(x[2]/180*PI-CR[2]/180*PI));
    NRAD[0]=atan2(-cos(x[3]/180*PI)*sin(x[2]/180*PI-CR[2]/180*PI),sin(x[3]/180*PI)*cos(CR[3]/180*PI)-cos(x[3]/180*PI)*sin(CR[3]/180*PI)*cos(x[2]/180*PI-CR[2]/180*PI))+LP/180*PI;

    Pdeg[0]= 180/PI/tan(NRAD[1])*sin(NRAD[0]);
    Pdeg[1]=-180/PI/tan(NRAD[1])*cos(NRAD[0]);

    CDMAT[0]=(CD[1][1]*Pdeg[0]-CD[0][1]*Pdeg[1])/(CD[0][0]*CD[1][1]-CD[0][1]*CD[1][0]);
    CDMAT[1]=(CD[0][0]*Pdeg[1]-CD[1][0]*Pdeg[0])/(CD[0][0]*CD[1][1]-CD[0][1]*CD[1][0]);   
    x[0]=CDMAT[0]+CR[0];
    x[1]=CDMAT[1]+CR[1];                                                       
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
// FLAG ----------------------------------------------------------------------------------------------------
void    F_FLAG(CL_APROP APROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,j;
    double CR[4],dataSi[4],dataSIPi[4],DIFF[2][3]={{0}},ave[2],var[2];
    double *DIFFi[2];

    DIFFi[0]= new double[APROP.NUMREFALL];
    DIFFi[1]= new double[APROP.NUMREFALL];
    for(i=0;i<APROP.NUMREFALL;i++)
    DIFFi[0][i]=DIFFi[1][i]=0;

    CR[0]=CSIP->CRPIX[0];
    CR[1]=CSIP->CRPIX[1];
    CR[2]=CSIP->CRVAL[0];
    CR[3]=CSIP->CRVAL[1];

    for(i=0;i<APROP.NUMREFALL;i++){
        dataSi[0]=PAIR[i].xG;
        dataSi[1]=PAIR[i].yG;
        dataSi[2]=PAIR[i].RA;
        dataSi[3]=PAIR[i].DEC;

        F_SIP(0,CSIP->SIP_AB_ORDER,dataSi,dataSIPi,CR,CSIP->SIP_AB); 
        F_WCSPIX_TAN(dataSi,CR,CSIP->CD);     
        DIFFi[0][i]=(dataSi[0]-dataSIPi[0]);
        DIFFi[1][i]=(dataSi[1]-dataSIPi[1]);    
        DIFF[0][0]+=1;
        DIFF[1][0]+=1;
        DIFF[0][1]+=(dataSi[0]-dataSIPi[0]);
        DIFF[1][1]+=(dataSi[1]-dataSIPi[1]);
        DIFF[0][2]+=(dataSi[0]-dataSIPi[0])*(dataSi[0]-dataSIPi[0]);
        DIFF[1][2]+=(dataSi[1]-dataSIPi[1])*(dataSi[1]-dataSIPi[1]);
    }
    ave[0]=DIFF[0][1]/DIFF[0][0];
    ave[1]=DIFF[1][1]/DIFF[1][0];
    var[0]=sqrt((DIFF[0][2]-DIFF[0][1]*DIFF[0][1]/DIFF[0][0])/(DIFF[0][0]-1));
    var[1]=sqrt((DIFF[1][2]-DIFF[1][1]*DIFF[1][1]/DIFF[1][0])/(DIFF[1][0]-1));

    j=0;
    for(i=0;i<APROP.NUMREFALL;i++)
    if(fabs(DIFFi[0][i]-ave[0])>APROP.CLIP_SIGMA*var[0]*0.5||fabs(DIFFi[1][i]-ave[1])>APROP.CLIP_SIGMA*var[1]*0.5){
        PAIR[i].FLAG=0;
        j++;
    }
cout << "RejNUM:" << j << endl;

    delete [] DIFFi[0];
    delete [] DIFFi[1];
}
#undef LP
#undef PI
