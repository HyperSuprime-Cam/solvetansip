//--------------------------------------------------
//Calculating Coefficients of Least Squares Fitting 
//Output coefficients of F_LS2 are
//x^0y^0, x^0y^1, x^0y^2, x^0y^3, x^1y^0, x^1y^1, x^1y^2, x^2y^0, x^2y^1, x^3y^0 (in Order = 3)  
//
//Last modification : 2010/07/01
//--------------------------------------------------

#include<math.h>
#include<stdio.h>      
#include<stdlib.h>
void    F_InvM(int MNUM,double *Min,double *Mout){
    int i,j,k;
    double **Min2,**Mout2;
    double Mdi,**Mtemp,**Mtemp2,**I,**Itemp;

    Min2  =(double **)calloc(MNUM*MNUM,sizeof(double *));
    Mout2 =(double **)calloc(MNUM*MNUM,sizeof(double *));
    Mtemp =(double **)calloc(MNUM*MNUM,sizeof(double *));
    Mtemp2=(double **)calloc(MNUM*MNUM,sizeof(double *));
    I     =(double **)calloc(MNUM*MNUM,sizeof(double *));
    Itemp =(double **)calloc(MNUM*MNUM,sizeof(double *));
    for(i=0;i<MNUM;i++){
        Min2[i]  =NULL;
        Mout2[i] =NULL;
        Mtemp[i] =NULL;
        Mtemp2[i]=NULL;
        I[i]     =NULL;
        Itemp[i] =NULL;
    }
    for(i=0;i<MNUM;i++){
        Min2[i]  =(double *)calloc(MNUM*MNUM,sizeof(double));
        Mout2[i] =(double *)calloc(MNUM*MNUM,sizeof(double));
        Mtemp [i]=(double *)calloc(MNUM*MNUM,sizeof(double));
        Mtemp2[i]=(double *)calloc(MNUM*MNUM,sizeof(double));
        I[i]     =(double *)calloc(MNUM*MNUM,sizeof(double));
        Itemp[i] =(double *)calloc(MNUM*MNUM,sizeof(double));
    }


    for(i=0;i<MNUM;i++)
    for(j=0;j<MNUM;j++){
        Itemp[i][j]=0;
        Min2[i][j]=Min[i*MNUM+j];
        if(i==j){
            I[i][j]=1;
        }else{
            I[i][j]=0;
        }
    }         

    for(k=0;k<MNUM;k++){                
        Mdi=Min2[k][k];         
        for(i=0;i<MNUM;i++){      
            Min2[i][k]=Min2[i][k]/Mdi;
               I[i][k]=   I[i][k]/Mdi;
        }                        
	
    for(i=0;i<MNUM;i++) 
    for(j=0;j<MNUM;j++) 
    Mtemp[i][j]=Min2[i][j];
    for(j=0;j<MNUM;j++)  
    if(j==k){
    }else{   
            for(i=0;i<MNUM;i++){
            Min2[i][j]-=Mtemp[k][j]*Min2[i][k];
               I[i][j]-=Mtemp[k][j]*   I[i][k];
            }	
        }
    }      
    for(i=0;i<MNUM;i++) 
    for(j=0;j<MNUM;j++) 
    Mout[i*MNUM+j]=I[i][j];

    for(i=0;i<MNUM;i++){
        free(Min2[i]  );
        free(Mout2[i] );
        free(Mtemp[i] );
        free(Mtemp2[i]);
        free(I[i]     );
        free(Itemp[i] );
    }
    free(Min2  );
    free(Mout2 );
    free(Mtemp );
    free(Mtemp2);
    free(I     );
    free(Itemp );
	
}
void    F_LS1(int dataNUM,int Order,double data[][2],double Coef[]){
    int i,j,NUM;
    double *XA,*XB,*Z;

    XA=(double *)calloc((Order+1)*(Order+1),sizeof(double));
    XB=(double *)calloc((Order+1)*(Order+1),sizeof(double));
     Z=(double *)calloc(          (Order+1),sizeof(double));
	
    for(NUM=0;NUM<dataNUM;NUM++)
    for(i=0;i<Order+1;i++){
        for(j=0;j<Order+1;j++)    
        XA[i+j*(Order+1)]+=pow(data[NUM][0],i)*pow(data[NUM][0],j);
        Z[i]+=data[NUM][1]*pow(data[NUM][0],i);
    }                   

    F_InvM(Order+1,XA,XB);
	
    for(i=0;i<Order+1;i++)
    for(j=0;j<Order+1;j++)
    Coef[i]+=XB[i+j*(Order+1)]*Z[j];

    free(XA);
    free(XB);
    free( Z);
}
void    F_LS2(int dataNUM,int Order,double (*data)[3],double Coef[]){
    int i,j,k,l,ij,kl,NUM;
    double *XA,*XB,*Z;

    XA=(double *)calloc((Order+1)*(Order+1)*(Order+1)*(Order+1),sizeof(double));
    XB=(double *)calloc((Order+1)*(Order+1)*(Order+1)*(Order+1),sizeof(double));
     Z=(double *)calloc(                    (Order+1)*(Order+1),sizeof(double));

    for(NUM=0;NUM<dataNUM;NUM++){
    ij=0;
        for(i=0;i<Order+1;i++)
        for(j=0;j<Order+1;j++)
        if(i+j<Order+1){
            kl=0;
            for(k=0;k<Order+1;k++)
            for(l=0;l<Order+1;l++)
            if(k+l<Order+1){
                XA[ij+(int)((Order+1)*(Order+2)*0.5+0.1)*kl]+=pow(data[NUM][0],i+k)*pow(data[NUM][1],j+l);
                kl+=1;
            }
            Z[ij]+=data[NUM][2]*pow(data[NUM][0],i)*pow(data[NUM][1],j);   
            ij+=1;
        }
    }

    F_InvM((int)((Order+1)*(Order+2)*0.5+0.1),XA,XB);

    ij=0;
    for(i=0;i<Order+1;i++)
    for(j=0;j<Order+1;j++)
    if(i+j<Order+1){
        kl=0;
        for(k=0;k<Order+1;k++)
        for(l=0;l<Order+1;l++)
        if(k+l<Order+1){
            Coef[ij]+=XB[ij+(int)((Order+1)*(Order+2)*0.5+0.1)*kl]*Z[kl];       
            kl+=1;
        }
        ij+=1;
    }
    free(XA);
    free(XB);
    free( Z);
}   
void    F_LS2NN(int dataNUM,int Order,double data[][3],double Coef[]){
    int i,j,k,l,NUM;
    double *XA,*XB,*Z;

    XA=(double *)calloc((Order+1)*(Order+1)*(Order+1)*(Order+1),sizeof(double));
    XB=(double *)calloc((Order+1)*(Order+1)*(Order+1)*(Order+1),sizeof(double));
     Z=(double *)calloc(                    (Order+1)*(Order+1),sizeof(double));

    for(NUM=0;NUM<dataNUM;NUM++)
    for(i=0;i<Order+1;i++)
    for(j=0;j<Order+1;j++){
        for(k=0;k<Order+1;k++)
        for(l=0;l<Order+1;l++)                         
        XA[i+j*(Order+1)+(k+l*(Order+1))*(Order+1)*(Order+1)]+=pow(data[NUM][0],i+k)*pow(data[NUM][1],j+l);
        Z[i+j*(Order+1)]+=data[NUM][2]*pow(data[NUM][0],i)*pow(data[NUM][1],j);   
    }

    F_InvM((Order+1)*(Order+1),XA,XB);

    for(i=0;i<Order+1;i++)
    for(j=0;j<Order+1;j++)
    for(k=0;k<Order+1;k++)
    for(l=0;l<Order+1;l++)
    Coef[i+j*(Order+1)]+=XB[i+j*(Order+1)+(k+l*(Order+1))*(Order+1)*(Order+1)]*Z[k+l*(Order+1)];      

    free(XA);
    free(XB);
    free( Z); 

}    
