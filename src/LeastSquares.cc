//--------------------------------------------------
//Calculating Coefficients of Least Squares Fitting 
//Output coefficients of F_LS2 are
//x^0y^0, x^0y^1, x^0y^2, x^0y^3, x^1y^0, x^1y^1, x^1y^2, x^2y^0, x^2y^1, x^3y^0 (in Order = 3)  
//
//Last modification : 2010/11/10
//--------------------------------------------------

#include<cmath>


#ifdef USE_EIGEN
#include <Eigen/Core>
#include <Eigen/LU>
#endif

void    F_InvM(int MNUM,double **Min,double **Mout){

#ifdef USE_EIGEN
    Eigen::MatrixXd input(MNUM, MNUM);
    for (int i = 0; i < MNUM; ++i) {
        for (int j = 0; j < MNUM; ++j) {
            input(i, j) = Min[i][j];
        }
    }
    Eigen::MatrixXd output = input.inverse();
    for (int i = 0; i < MNUM; ++i) {
        for (int j = 0; j < MNUM; ++j) {
            Mout[i][j] = output(i, j);
        }
    }
    return;
#else
    int i,j,k;
    double Mdi,**Mtemp,**Mtemp2,**I,**Itemp;

    Mtemp  = new double*[MNUM];
    Mtemp2 = new double*[MNUM];
    I      = new double*[MNUM];
    Itemp  = new double*[MNUM];
    for(i=0;i<MNUM;i++){
    Mtemp[i]  = new double[MNUM];
    Mtemp2[i] = new double[MNUM];
    I[i]      = new double[MNUM];
    Itemp[i]  = new double[MNUM];
    }

    for(i=0;i<MNUM;i++)
    for(j=0;j<MNUM;j++){
    Mtemp[i][j]=0;
    Mtemp2[i][j]=0;
    I[i][j]=0;
    Itemp[i][j]=0;
    }

    for(i=0;i<MNUM;i++)
    for(j=0;j<MNUM;j++){
        Itemp[i][j]=0;
        if(i==j){
            I[i][j]=1;
        }else{
            I[i][j]=0;
        }
    }         

    for(k=0;k<MNUM;k++){                
        Mdi=Min[k][k];         
        for(i=0;i<MNUM;i++){      
            Min[i][k]=Min[i][k]/Mdi;
              I[i][k]=  I[i][k]/Mdi;
        }                        
	
    for(i=0;i<MNUM;i++) 
    for(j=0;j<MNUM;j++) 
    Mtemp[i][j]=Min[i][j];
    for(j=0;j<MNUM;j++)  
    if(j==k){
    }else{   
            for(i=0;i<MNUM;i++){
            Min[i][j]-=Mtemp[k][j]*Min[i][k];
              I[i][j]-=Mtemp[k][j]*  I[i][k];
            }	
        }
    }      
    for(i=0;i<MNUM;i++) 
    for(j=0;j<MNUM;j++) 
    Mout[i][j]=I[i][j];

    for(i=0;i<MNUM;i++){
    delete [] Mtemp[i];
    delete [] Mtemp2[i];
    delete [] I[i];
    delete [] Itemp[i];
    }
    delete [] Mtemp;
    delete [] Mtemp2;
    delete [] I;
    delete [] Itemp;
#endif	
}
void    F_LS1(int dataNUM,int Order,double **data,double *Coef){
    int i,j,NUM;
    double **XA,**XB,*Z;

    for(i=0;i<Order+1;i++)
    Coef[i]=0;

    XA = new double*[Order+1];
    XB = new double*[Order+1];
     Z = new double[Order+1];
    for(i=0;i<Order+1;i++){
    XA[i] = new double[Order+1];
    XB[i] = new double[Order+1];
    }
	
    for(NUM=0;NUM<dataNUM;NUM++)
    for(i=0;i<Order+1;i++){
        for(j=0;j<Order+1;j++)    
        XA[i][j]+=pow(data[NUM][0],i)*pow(data[NUM][0],j);
        Z[i]+=data[NUM][1]*pow(data[NUM][0],i);
    }                   

    F_InvM(Order+1,XA,XB);

    for(i=0;i<Order+1;i++)
    for(j=0;j<Order+1;j++)
    Coef[i]+=XB[i][j]*Z[j];

    for(i=0;i<Order+1;i++){
    delete [] XA[i];
    delete [] XB[i];
    }
    delete [] XA;
    delete [] XB;
    delete [] Z;
}
void    F_LS2(int dataNUM,int Order,double **data,double *Coef){
    int i,j,k,l,ij,kl,NUM;
    double **XA,**XB,*Z;

    XA = new double*[(Order+1)*(Order+1)];
    XB = new double*[(Order+1)*(Order+1)];
     Z = new double[(Order+1)*(Order+1)];
    for(i=0;i<(Order+1)*(Order+1);i++){
    XA[i] = new double[(Order+1)*(Order+1)];
    XB[i] = new double[(Order+1)*(Order+1)];
    }

    for(i=0;i<(Order+1)*(Order+1);i++){
    for(j=0;j<(Order+1)*(Order+1);j++)
    XA[i][j]=XB[i][j]=0;
    Z[i]=0;
    }
    ij=0;
    for(i=0;i<Order+1;i++)
    for(j=0;j<Order+1;j++)
    if(i+j<Order+1){
    Coef[ij]=0;
    ij++;
    }

    for(NUM=0;NUM<dataNUM;NUM++){
    ij=0;
        for(i=0;i<Order+1;i++)
        for(j=0;j<Order+1;j++)
        if(i+j<Order+1){
            kl=0;
            for(k=0;k<Order+1;k++)
            for(l=0;l<Order+1;l++)
            if(k+l<Order+1){
                XA[ij][kl]+=pow(data[NUM][0],i+k)*pow(data[NUM][1],j+l);
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
            Coef[ij]+=XB[ij][kl]*Z[kl];       
            kl+=1;
        }
        ij+=1;
    }

    for(i=0;i<(Order+1)*(Order+1);i++){
    delete [] XA[i];
    delete [] XB[i];
    }
    delete [] XA;
    delete [] XB;
    delete [] Z;
} 
void    F_LS3_2(int dataNUM,double **data,double *Coef){
    int i,j,k;
    double **XA,**XB,Z[10];

    XA = new double*[10];
    XB = new double*[10];
    for(i=0;i<10;i++){
    XA[i] = new double[10];
    XB[i] = new double[10];
    }

    for(i=0;i<10;i++){
    Z[i]=Coef[i]=0;
    for(j=0;j<10;j++)
    XA[i][j]=XB[i][j]=0;
    }

    for(i=0;i<dataNUM;i++){
        Z[0]+=data[i][3]*1;
        Z[1]+=data[i][3]*data[i][2];
        Z[2]+=data[i][3]*data[i][2]*data[i][2];
        Z[3]+=data[i][3]*data[i][1];
        Z[4]+=data[i][3]*data[i][1]*data[i][2];
        Z[5]+=data[i][3]*data[i][1]*data[i][1];
        Z[6]+=data[i][3]*data[i][0];
        Z[7]+=data[i][3]*data[i][0]*data[i][2];
        Z[8]+=data[i][3]*data[i][0]*data[i][1];
        Z[9]+=data[i][3]*data[i][0]*data[i][0];

        XA[0][0]+=1*1;
        XA[0][1]+=1*data[i][2];
        XA[0][2]+=1*data[i][2]*data[i][2];
        XA[0][3]+=1*data[i][1];
        XA[0][4]+=1*data[i][1]*data[i][2];
        XA[0][5]+=1*data[i][1]*data[i][1];
        XA[0][6]+=1*data[i][0];
        XA[0][7]+=1*data[i][0]*data[i][2];
        XA[0][8]+=1*data[i][0]*data[i][1];
        XA[0][9]+=1*data[i][0]*data[i][0];
        XA[1][1]+=data[i][2]*data[i][2];
        XA[1][2]+=data[i][2]*data[i][2]*data[i][2];
        XA[1][3]+=data[i][2]*data[i][1];
        XA[1][4]+=data[i][2]*data[i][1]*data[i][2];
        XA[1][5]+=data[i][2]*data[i][1]*data[i][1];
        XA[1][6]+=data[i][2]*data[i][0];
        XA[1][7]+=data[i][2]*data[i][0]*data[i][2];
        XA[1][8]+=data[i][2]*data[i][0]*data[i][1];
        XA[1][9]+=data[i][2]*data[i][0]*data[i][0];
        XA[2][2]+=data[i][2]*data[i][2]*data[i][2]*data[i][2];
        XA[2][3]+=data[i][2]*data[i][2]*data[i][1];
        XA[2][4]+=data[i][2]*data[i][2]*data[i][1]*data[i][2];
        XA[2][5]+=data[i][2]*data[i][2]*data[i][1]*data[i][1];
        XA[2][6]+=data[i][2]*data[i][2]*data[i][0];
        XA[2][7]+=data[i][2]*data[i][2]*data[i][0]*data[i][2];
        XA[2][8]+=data[i][2]*data[i][2]*data[i][0]*data[i][1];
        XA[2][9]+=data[i][2]*data[i][2]*data[i][0]*data[i][0];
        XA[3][3]+=data[i][1]*data[i][1];
        XA[3][4]+=data[i][1]*data[i][1]*data[i][2];
        XA[3][5]+=data[i][1]*data[i][1]*data[i][1];
        XA[3][6]+=data[i][1]*data[i][0];
        XA[3][7]+=data[i][1]*data[i][0]*data[i][2];
        XA[3][8]+=data[i][1]*data[i][0]*data[i][1];
        XA[3][9]+=data[i][1]*data[i][0]*data[i][0];
        XA[4][4]+=data[i][1]*data[i][2]*data[i][1]*data[i][2];
        XA[4][5]+=data[i][1]*data[i][2]*data[i][1]*data[i][1];
        XA[4][6]+=data[i][1]*data[i][2]*data[i][0];
        XA[4][7]+=data[i][1]*data[i][2]*data[i][0]*data[i][2];
        XA[4][8]+=data[i][1]*data[i][2]*data[i][0]*data[i][1];
        XA[4][9]+=data[i][1]*data[i][2]*data[i][0]*data[i][0];
        XA[5][5]+=data[i][1]*data[i][1]*data[i][1]*data[i][1];
        XA[5][6]+=data[i][1]*data[i][1]*data[i][0];
        XA[5][7]+=data[i][1]*data[i][1]*data[i][0]*data[i][2];
        XA[5][8]+=data[i][1]*data[i][1]*data[i][0]*data[i][1];
        XA[5][9]+=data[i][1]*data[i][1]*data[i][0]*data[i][0];
        XA[6][6]+=data[i][0]*data[i][0];
        XA[6][7]+=data[i][0]*data[i][0]*data[i][2];
        XA[6][8]+=data[i][0]*data[i][0]*data[i][1];
        XA[6][9]+=data[i][0]*data[i][0]*data[i][0];
        XA[7][7]+=data[i][0]*data[i][2]*data[i][0]*data[i][2];
        XA[7][8]+=data[i][0]*data[i][2]*data[i][0]*data[i][1];
        XA[7][9]+=data[i][0]*data[i][2]*data[i][0]*data[i][0];
        XA[8][8]+=data[i][0]*data[i][1]*data[i][0]*data[i][1];
        XA[8][9]+=data[i][0]*data[i][1]*data[i][0]*data[i][0];
        XA[9][9]+=data[i][0]*data[i][0]*data[i][0]*data[i][0];
    }
    for(i=1;i<10;i++)
    for(j=0;j< i;j++)
    XA[i][j]=XA[j][i];

    F_InvM(10,XA,XB);

    for(i=0;i<10;i++)
    for(j=0;j<10;j++)
    Coef[i]+=XB[i][j]*Z[j];

    for(i=0;i<10;i++){
    delete [] XA[i];
    delete [] XB[i];
    }
    delete [] XA;
    delete [] XB;
}
void    F_LS3(int dataNUM,int Order,double **data,double *Coef){
    int i,j,k,l,m,n,ijk,lmn,NUM;
    double **XA,**XB,*Z;

    XA = new double*[(Order+1)*(Order+1)*(Order+1)];
    XB = new double*[(Order+1)*(Order+1)*(Order+1)];
     Z = new double[(Order+1)*(Order+1)*(Order+1)];
    for(i=0;i<(Order+1)*(Order+1)*(Order+1);i++){
    XA[i] = new double[(Order+1)*(Order+1)*(Order+1)];
    XB[i] = new double[(Order+1)*(Order+1)*(Order+1)];
    }

    for(i=0;i<(Order+1)*(Order+1)*(Order+1);i++){
    for(j=0;j<(Order+1)*(Order+1)*(Order+1);j++)
    XA[i][j]=XB[i][j]=0;
    Z[i]=0;
    }
    ijk=0;
    for(i=0;i<Order+1;i++)
    for(j=0;j<Order+1;j++)
    for(k=0;k<Order+1;k++)
    if(i+j+k<Order+1){
    Coef[ijk]=0;
    ijk++;
    }

    for(NUM=0;NUM<dataNUM;NUM++){
    ijk=0;
        for(i=0;i<Order+1;i++)
        for(j=0;j<Order+1;j++)
        for(k=0;k<Order+1;k++)
        if(i+j+k<Order+1){
            lmn=0;
            for(l=0;l<Order+1;l++)
            for(m=0;m<Order+1;m++)
            for(n=0;n<Order+1;n++)
            if(l+m+n<Order+1){
                XA[ijk][lmn]+=pow(data[NUM][0],i+l)*pow(data[NUM][1],j+m)*pow(data[NUM][2],k+n);
                lmn+=1;
            }
            Z[ijk]+=data[NUM][3]*pow(data[NUM][0],i)*pow(data[NUM][1],j)*pow(data[NUM][2],k);   
            ijk+=1;
        }
    }


    F_InvM((int)((Order+1)*(Order+2)*(Order+3)/2.0/3.0+0.1),XA,XB);

    ijk=0;
    for(i=0;i<Order+1;i++)
    for(j=0;j<Order+1;j++)
    for(k=0;k<Order+1;k++)
    if(i+j+k<Order+1){
        lmn=0;
        for(l=0;l<Order+1;l++)
        for(m=0;m<Order+1;m++)
        for(n=0;n<Order+1;n++)
        if(l+m+n<Order+1){
            Coef[ijk]+=XB[ijk][lmn]*Z[lmn];       
            lmn+=1;
        }
        ijk+=1;
    }

    for(i=0;i<(Order+1)*(Order+1);i++){
    delete [] XA[i];
    delete [] XB[i];
    }
    delete [] XA;
    delete [] XB;
    delete [] Z;
}
/*
void    F_LS2NN(int dataNUM,int Order,double data[][3],double Coef[]){
    int i,j,k,l,NUM;
    double *XA,*XB,*Z;

    XA=(double *)calloc((Order+1)*(Order+1)*(Order+1)*(Order+1),sizeof(double));
    XB=(double *)calloc((Order+1)*(Order+1)*(Order+1)*(Order+1),sizeof(double));
     Z=(double *)calloc(                    (Order+1)*(Order+1),sizeof(double));

    for(i=0;i<Order+1;i++)
    for(j=0;j<Order+1;j++)
    Coef[i+j*(Order+1)]=0;

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

}    */
