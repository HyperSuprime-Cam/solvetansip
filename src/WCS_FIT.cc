//------------------------------------------------------------
//WCS_FIT.cc
//
//Last modification : 2010/08/03
//------------------------------------------------------------
#include<iostream>//temp
#include<fstream>
#include<cmath>
#include<string>
#include<sstream>
#include<iomanip>//temp
#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_CPROP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_CSIP.h"

using namespace std;
void    F_CDSIP(CL_APROP,CL_PAIR,CL_CSIP*);
void    F_WCSPIX_TAN(double x[],double CR[],double CD[][2]);
void    F_PIXWCS_TAN(double x[],double CR[],double CD[][2]);
void    F_SIP(int FR,int Order,double x[],double xSIP[],double CR[],double *SIP[2]);
void    F_FLAG(CL_APROP,CL_PAIR*,CL_CSIP*);
void    F_DISP(CL_APROP,CL_PAIR,CL_CSIP*);
void    F_LS2(int dataNUM,int Order,double (*data)[3],double *Coef);
void    F_CHECK(CL_APROP,CL_PAIR,CL_CSIP*);


void    F_WCS_FIT(CL_APROP APROP,CL_PAIR *PAIR,CL_CSIP *CSIP){

cout << "--- F_WCS_TANSIP:FIT:fitting    ---" << endl;
    F_CDSIP(APROP,*PAIR,CSIP);
cout << "--- F_WCS_TANSIP:FIT:rejection  ---" << endl;
    F_FLAG (APROP, PAIR,CSIP);
cout << "--- F_WCS_TANSIP:FIT:re-fitting ---" << endl;
    F_CDSIP(APROP,*PAIR,CSIP);
    F_DISP (APROP,*PAIR,CSIP);
    if(APROP.CHECKFILE==0){
    }else{
    F_CHECK(APROP,*PAIR,CSIP);
    }

}
void    F_CDSIP(CL_APROP APROP,CL_PAIR PAIR,CL_CSIP *CSIP){
    int i,j,ij,FNUM;
    double xi[4],CR[4],InvCD[2][2],CRPIXAVE[2]={0};
    double x[4],xSIP[4],SUM[2][2]={0};
    double *Coef1,*Coef2,*CoefP1,*CoefP2,(*dx1)[3],(*dx2)[3];

    Coef1 = new double[APROP.SIP_ORDER*APROP.SIP_ORDER+1];
    Coef2 = new double[APROP.SIP_ORDER*APROP.SIP_ORDER+1];
    CoefP1= new double[APROP.SIP_ORDER*APROP.SIP_ORDER+1];
    CoefP2= new double[APROP.SIP_ORDER*APROP.SIP_ORDER+1];
    dx1= new double[3*(APROP.refNUM)+1][3];
    dx2= new double[3*(APROP.refNUM)+1][3];
// measuring CRpix and CRval at CRpix --------------------------------------------------

    CSIP->SIP_AB_ORDER=APROP.SIP_ORDER;
    CSIP->SIP_ABP_ORDER=APROP.SIP_P_ORDER;
    CSIP->ID=APROP.CCDNUM;

    FNUM=0;
    for(i=0;i<APROP.refNUM;i++)
    if(PAIR.FLAG[i] == 1){
        dx1[FNUM][0]=dx2[FNUM][0]=PAIR.x[i]; 
        dx1[FNUM][1]=dx2[FNUM][1]=PAIR.y[i]; 
        dx1[FNUM][2]=PAIR.RA[i];
        dx2[FNUM][2]=PAIR.DEC[i];
        if(APROP.CRPIXMODE == "AUTO"){
            CRPIXAVE[0]+=PAIR.x[i];
            CRPIXAVE[1]+=PAIR.y[i];
        }  
        FNUM+=1;
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

    for(i=0;i<APROP.SIP_ORDER*APROP.SIP_ORDER+1;i++)
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
        ij+=1;	
    }

    CR[0]=CSIP->CRPIX[0];
    CR[1]=CSIP->CRPIX[1];
    CR[2]=CSIP->CRVAL[0];
    CR[3]=CSIP->CRVAL[1];

// measuring TANSIP at CRpix --------------------------------------------------

    CSIP->CD[0][0]=CSIP->CD[1][1]=1;
    CSIP->CD[0][1]=CSIP->CD[1][0]=0;

    FNUM=0;
    for(i=0;i<APROP.refNUM;i++)
    if(PAIR.FLAG[i] == 1){
        xi[2]=PAIR.RA[i];
        xi[3]=PAIR.DEC[i];
		
        F_WCSPIX_TAN(xi,CR,CSIP->CD);
        dx1[FNUM][0]=dx2[FNUM][0]=PAIR.x[i]-CR[0]; 
        dx1[FNUM][1]=dx2[FNUM][1]=PAIR.y[i]-CR[1]; 
        dx1[FNUM][2]=xi[0]-CR[0];
        dx2[FNUM][2]=xi[1]-CR[1];   
        FNUM+=1;
    }

    for(i=0;i<APROP.SIP_ORDER*APROP.SIP_ORDER+1;i++)
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
        ij+=1;	
    }

    CSIP->SIP_AB[0][1*(APROP.SIP_ORDER+1)+0]-=1.0;
    CSIP->SIP_AB[1][0*(APROP.SIP_ORDER+1)+1]-=1.0;

    CSIP->FITNUM=FNUM;
// measuring InvTANSIP at CRpix --------------------------------------------------
    FNUM=0;
    for(i=0;i<APROP.refNUM;i++)
    if(PAIR.FLAG[i] == 1){
        xi[2]=PAIR.RA[i];
        xi[3]=PAIR.DEC[i];
	
        F_WCSPIX_TAN(xi,CR,CSIP->CD);
        dx1[FNUM][0]=dx2[FNUM][0]=xi[0]-CR[0]; 
        dx1[FNUM][1]=dx2[FNUM][1]=xi[1]-CR[1]; 
        dx1[FNUM][2]=PAIR.x[i]-CR[0];
        dx2[FNUM][2]=PAIR.y[i]-CR[1];   
        FNUM+=1;
    }   

    for(i=0;i<APROP.SIP_P_ORDER*APROP.SIP_P_ORDER+1;i++)
    CoefP1[i]=CoefP2[i]=0;
    F_LS2(FNUM,APROP.SIP_P_ORDER,dx1,CoefP1);
    F_LS2(FNUM,APROP.SIP_P_ORDER,dx2,CoefP2);

    ij=0;
    for(i=0;i<APROP.SIP_P_ORDER+1;i++)
    for(j=0;j<APROP.SIP_P_ORDER+1;j++)
    if(i+j<APROP.SIP_P_ORDER+1){
        CSIP->SIP_ABP[0][ij]=CoefP1[ij];
        CSIP->SIP_ABP[1][ij]=CoefP2[ij];
        ij+=1;	
    }

    CSIP->SIP_ABP[0][1*(APROP.SIP_ORDER+1)+0]-=1.0;
    CSIP->SIP_ABP[1][0*(APROP.SIP_ORDER+1)+1]-=1.0;

//fitting value --------------------------------------------------

    FNUM=0;
    for(i=0;i<APROP.refNUM;i++)
    if(PAIR.FLAG[i]==1){
        x[0]=PAIR.x[i];
        x[1]=PAIR.y[i];
        x[2]=PAIR.RA[i];
        x[3]=PAIR.DEC[i];
        F_SIP(0,APROP.SIP_ORDER,x,xSIP,CR,CSIP->SIP_AB);
        PAIR.xSIP[i]=xSIP[0];
        PAIR.ySIP[i]=xSIP[1];
        F_PIXWCS_TAN(xSIP,CR,CSIP->CD);
        PAIR.RAfit[i] =xSIP[2];
        PAIR.DECfit[i]=xSIP[3];
        F_WCSPIX_TAN(x,CR,CSIP->CD);
        SUM[0][0]+=(xSIP[0]-x[0]);
        SUM[1][0]+=(xSIP[1]-x[1]);
        SUM[0][1]+=(xSIP[0]-x[0])*(xSIP[0]-x[0]);
        SUM[1][1]+=(xSIP[1]-x[1])*(xSIP[1]-x[1]);
        FNUM+=1;
    }
    CSIP->SIP_AB_AVE[0]=SUM[0][0]/FNUM;
    CSIP->SIP_AB_AVE[1]=SUM[1][0]/FNUM;
    CSIP->SIP_AB_SIGMA[0]=sqrt((SUM[0][1]-SUM[0][0]*SUM[0][0]/FNUM)/(FNUM-1));
    CSIP->SIP_AB_SIGMA[1]=sqrt((SUM[1][1]-SUM[1][0]*SUM[1][0]/FNUM)/(FNUM-1));

    delete [] Coef1;
    delete [] Coef2;
    delete [] CoefP1;
    delete [] CoefP2;
    delete [] dx1;
    delete [] dx2;
}
#define LP 180
#define PI (4*atan(1.0))
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
        ij+=1;
    }
}
#undef LP
#undef PI
// FLAG ----------------------------------------------------------------------------------------------------
void    F_FLAG(CL_APROP APROP,CL_PAIR *PAIR,CL_CSIP *CSIP){
    int i,j;
    double CR[4],dataSi[4],dataSIPi[4],DIFF[2][3]={{0}},ave[2],var[2];
    double *DIFFi[2];

    DIFFi[0]= new double[APROP.refNUM];
    DIFFi[1]= new double[APROP.refNUM];

    CR[0]=CSIP->CRPIX[0];
    CR[1]=CSIP->CRPIX[1];
    CR[2]=CSIP->CRVAL[0];
    CR[3]=CSIP->CRVAL[1];

    for(i=0;i<APROP.refNUM;i++){
        dataSi[0]=PAIR->x[i];
        dataSi[1]=PAIR->y[i];
        dataSi[2]=PAIR->RA[i];
        dataSi[3]=PAIR->DEC[i];

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
    for(i=0;i<APROP.refNUM;i++)
    if(fabs(DIFFi[0][i]-ave[0])>APROP.CLIP_SIGMA*var[0]||fabs(DIFFi[1][i]-ave[1])>APROP.CLIP_SIGMA*var[1]){
        PAIR->FLAG[i]=0;
        j++;
    }
cout << "RejNUM:" << j << endl;

    delete [] DIFFi[0];
    delete [] DIFFi[1];
}
void    F_DISP(CL_APROP APROP,CL_PAIR PAIR,CL_CSIP *CSIP){
    int i,j;
    double CR[4],dataSi[4],dataSIPi[4]={0},DIFF[2][3]={{0}};
    double *DIFFi[2];

    DIFFi[0]= new double[APROP.refNUM];
    DIFFi[1]= new double[APROP.refNUM];
	
    CR[0]=CSIP->CRPIX[0];
    CR[1]=CSIP->CRPIX[1];
    CR[2]=CSIP->CRVAL[0];
    CR[3]=CSIP->CRVAL[1];

    for(i=0;i<APROP.refNUM;i++)
    if(PAIR.FLAG[i]==1){
        dataSi[0]=PAIR.x[i];
        dataSi[1]=PAIR.y[i];
        dataSi[2]=PAIR.RA[i];
        dataSi[3]=PAIR.DEC[i];

        F_SIP(0,CSIP->SIP_AB_ORDER,dataSi,dataSIPi,CR,CSIP->SIP_AB); 
        F_PIXWCS_TAN(dataSIPi,CR,CSIP->CD);     
        DIFFi[0][i]=(dataSi[2]-dataSIPi[2]);
        DIFFi[1][i]=(dataSi[3]-dataSIPi[3]);    
        DIFF[0][0]+=1;
        DIFF[1][0]+=1;
        DIFF[0][1]+=(dataSi[2]-dataSIPi[2]);
        DIFF[1][1]+=(dataSi[3]-dataSIPi[3]);
        DIFF[0][2]+=(dataSi[2]-dataSIPi[2])*(dataSi[2]-dataSIPi[2]);
        DIFF[1][2]+=(dataSi[3]-dataSIPi[3])*(dataSi[3]-dataSIPi[3]);
    }
    CSIP->SIP_AB_DISP[0]=sqrt((DIFF[0][2]-DIFF[0][1]*DIFF[0][1]/DIFF[0][0])/(DIFF[0][0]-1));
    CSIP->SIP_AB_DISP[1]=sqrt((DIFF[1][2]-DIFF[1][1]*DIFF[1][1]/DIFF[1][0])/(DIFF[1][0]-1));

    for(i=0;i<2;i++)
    for(j=0;j<3;j++)
    DIFF[i][j]=0;

    for(i=0;i<APROP.refNUM;i++)
    if(PAIR.FLAG[i]==1){
        dataSi[0]=PAIR.x[i];
        dataSi[1]=PAIR.y[i];
        dataSi[2]=PAIR.RA[i];
        dataSi[3]=PAIR.DEC[i];

        F_WCSPIX_TAN(dataSi,CR,CSIP->CD);     
        F_SIP(1,CSIP->SIP_ABP_ORDER,dataSi,dataSIPi,CR,CSIP->SIP_ABP); 
        DIFFi[0][i]=(PAIR.x[i]-dataSIPi[0]);
        DIFFi[1][i]=(PAIR.y[i]-dataSIPi[1]);    
        DIFF[0][0]+=1;
        DIFF[1][0]+=1;
        DIFF[0][1]+=(PAIR.x[i]-dataSIPi[0]);
        DIFF[1][1]+=(PAIR.y[i]-dataSIPi[1]);
        DIFF[0][2]+=(PAIR.x[i]-dataSIPi[0])*(PAIR.x[i]-dataSIPi[0]);
        DIFF[1][2]+=(PAIR.y[i]-dataSIPi[1])*(PAIR.y[i]-dataSIPi[1]);
    }

    CSIP->SIP_ABP_DISP[0]=sqrt((DIFF[0][2]-DIFF[0][1]*DIFF[0][1]/DIFF[0][0])/(DIFF[0][0]-1));
    CSIP->SIP_ABP_DISP[1]=sqrt((DIFF[1][2]-DIFF[1][1]*DIFF[1][1]/DIFF[1][0])/(DIFF[1][0]-1));

    delete [] DIFFi[0];
    delete [] DIFFi[1];
}
#define PI (2*atan(1.0))
void    F_WSC_eachCHIP(CL_APROP APROP,CL_CPROP *CPROP,CL_PAIR PAIR,CL_CSIP* CSIP){
    int ID,i,j,ij,*NUM;
    double *SUM[2][2],x[4],CR[4];

    NUM = new int[APROP.CCDNUM];
    SUM[0][0] = new double[APROP.CCDNUM];
    SUM[0][1] = new double[APROP.CCDNUM];
    SUM[1][0] = new double[APROP.CCDNUM];
    SUM[1][1] = new double[APROP.CCDNUM];

    CR[0]=CSIP[APROP.CCDNUM].CRPIX[0];
    CR[1]=CSIP[APROP.CCDNUM].CRPIX[1];
    CR[2]=CSIP[APROP.CCDNUM].CRVAL[0];
    CR[3]=CSIP[APROP.CCDNUM].CRVAL[1];
    for(ID=0;ID<APROP.CCDNUM;ID++)
    NUM[ID]=SUM[0][0][ID]=SUM[0][1][ID]=SUM[1][0][ID]=SUM[1][1][ID]=0;

    for(i=0;i<APROP.refNUM;i++)
    if(PAIR.FLAG[i]==1){
        x[2]=PAIR.RA[i];
        x[3]=PAIR.DEC[i];
        F_WCSPIX_TAN(x,CR,CSIP[APROP.CCDNUM].CD);
        SUM[0][0][PAIR.CHIPID[i]]+=(PAIR.xSIP[i]-x[0]);
        SUM[1][0][PAIR.CHIPID[i]]+=(PAIR.ySIP[i]-x[1]);
        SUM[0][1][PAIR.CHIPID[i]]+=(PAIR.xSIP[i]-x[0])*(PAIR.xSIP[i]-x[0]);
        SUM[1][1][PAIR.CHIPID[i]]+=(PAIR.ySIP[i]-x[1])*(PAIR.ySIP[i]-x[1]);
//        SUM[0][0][PAIR.CHIPID[i]]+=(PAIR.RAfit[i]-PAIR.RA[i]);
  //      SUM[1][0][PAIR.CHIPID[i]]+=(PAIR.DECfit[i]-PAIR.DEC[i]);
    //    SUM[0][1][PAIR.CHIPID[i]]+=(PAIR.RAfit[i]-PAIR.RA[i])*(PAIR.RAfit[i]-PAIR.RA[i]);
      //  SUM[1][1][PAIR.CHIPID[i]]+=(PAIR.DECfit[i]-PAIR.DEC[i])*(PAIR.DECfit[i]-PAIR.DEC[i]);
        NUM[PAIR.CHIPID[i]]+=1;
    }
    for(ID=0;ID<APROP.CCDNUM;ID++){
cout << ID << " : " << NUM[ID] << endl;
        CSIP[ID].SIP_AB_AVE[0]  =SUM[0][0][ID]/NUM[ID];
        CSIP[ID].SIP_AB_AVE[1]  =SUM[1][0][ID]/NUM[ID];
        CSIP[ID].SIP_AB_SIGMA[0]=sqrt((SUM[0][1][ID]-SUM[0][0][ID]*SUM[0][0][ID]/NUM[ID])/(NUM[ID]-1));
        CSIP[ID].SIP_AB_SIGMA[1]=sqrt((SUM[1][1][ID]-SUM[1][0][ID]*SUM[1][0][ID]/NUM[ID])/(NUM[ID]-1));
    }

    for(ID=0;ID<APROP.CCDNUM;ID++){

        CSIP[ID].FITNUM=CSIP[APROP.CCDNUM].FITNUM;
        CSIP[ID].CRVAL[0]=CSIP[APROP.CCDNUM].CRVAL[0];
        CSIP[ID].CRVAL[1]=CSIP[APROP.CCDNUM].CRVAL[1];
        CSIP[ID].CRPIX[0]=-(CPROP[ID].GLOB_POS[0]-CSIP[APROP.CCDNUM].CRPIX[0])*cos(CPROP[ID].GLOB_POS[2]/180.0*PI)-(CPROP[ID].GLOB_POS[1]-CSIP[APROP.CCDNUM].CRPIX[1])*sin(CPROP[ID].GLOB_POS[2]/180.0*PI);
        CSIP[ID].CRPIX[1]=-(CPROP[ID].GLOB_POS[1]-CSIP[APROP.CCDNUM].CRPIX[1])*cos(CPROP[ID].GLOB_POS[2]/180.0*PI)+(CPROP[ID].GLOB_POS[0]-CSIP[APROP.CCDNUM].CRPIX[0])*sin(CPROP[ID].GLOB_POS[2]/180.0*PI);
        CSIP[ID].CD[0][0]=CSIP[APROP.CCDNUM].CD[0][0];
        CSIP[ID].CD[0][1]=CSIP[APROP.CCDNUM].CD[0][1];
        CSIP[ID].CD[1][0]=CSIP[APROP.CCDNUM].CD[1][0];
        CSIP[ID].CD[1][1]=CSIP[APROP.CCDNUM].CD[1][1];
        CSIP[ID].SIP_AB_ORDER =CSIP[APROP.CCDNUM].SIP_AB_ORDER;
        CSIP[ID].SIP_ABP_ORDER=CSIP[APROP.CCDNUM].SIP_ABP_ORDER;
        
        ij=0;
        for(i=0;i<CSIP[APROP.CCDNUM].SIP_AB_ORDER+1;i++)
        for(j=0;j<CSIP[APROP.CCDNUM].SIP_AB_ORDER+1;j++)
        if(i+j<CSIP->SIP_AB_ORDER+1) {
            CSIP[ID].SIP_AB[0][ij] = CSIP[APROP.CCDNUM].SIP_AB[0][ij];
            CSIP[ID].SIP_AB[1][ij] = CSIP[APROP.CCDNUM].SIP_AB[1][ij];
            ij+=1;
        }

        ij=0;
        for(i=0;i<CSIP[APROP.CCDNUM].SIP_ABP_ORDER+1;i++)
        for(j=0;j<CSIP[APROP.CCDNUM].SIP_ABP_ORDER+1;j++)
        if(i+j<CSIP->SIP_ABP_ORDER+1) {
            CSIP[ID].SIP_ABP[0][ij] = CSIP[APROP.CCDNUM].SIP_ABP[0][ij];
            CSIP[ID].SIP_ABP[1][ij] = CSIP[APROP.CCDNUM].SIP_ABP[1][ij];
            ij+=1;
        }        
    }

    delete [] NUM;
    delete [] SUM[0][0];
    delete [] SUM[0][1];
    delete [] SUM[1][0];
    delete [] SUM[1][1];
}
#undef PI
void    F_CHECK(CL_APROP APROP ,CL_PAIR PAIR ,CL_CSIP *CSIP){
    int i,CID;
    string outname, outname_global;
    ostringstream oss, oss_global;
    ofstream outcheckfile, outcheckfile_global;

    oss_global.str("");
    oss_global << "temp/TANSIPFIT_checkfile_global.dat";
    outname_global = oss_global.str();

    cout << "checkfile : " << outname_global << endl;
    outcheckfile_global.open(outname_global.c_str(), ios::out);

    for(i=0;i<APROP.refNUM;i++) {
      if(PAIR.FLAG[i]==1){
	outcheckfile_global << setprecision(6) << fixed << PAIR.CHIPID[i] << "\t" 
			    << PAIR.x[i] << "\t" << PAIR.y[i] << "\t" 
			    << PAIR.RA[i] << "\t" << PAIR.DEC[i] << "\t" 
			    << PAIR.xSIP[i] << "\t" << PAIR.ySIP[i] << "\t" 
			    << PAIR.RAfit[i] << "\t" << PAIR.DECfit[i] << endl;
      }
    }
    outcheckfile_global.close();
    cout << "checkfiles done. " << endl;
}
