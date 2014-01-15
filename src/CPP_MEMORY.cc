//------------------------------------------------------------
//CPP_MEMORY.cc
//NEW and DELETE MEMORYIES
//
//Last modification : 2014/01/01
//Yuki Okura : yuki.okura@nao.ac.jp
//------------------------------------------------------------
#include<iostream>
#include<vector>

//------------------------------------------------------------
//NEW int and double
int*	CPP_MEMORY_NEWint1(int SIZE1){
	int *MAT,i;
	MAT = new int[SIZE1];
	for(i=0;i<SIZE1;i++)MAT[i]=0;
	return MAT;
}
int**	CPP_MEMORY_NEWint2(int SIZE1,int SIZE2){
	int **MAT,i,j;
	MAT = new int*[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new int[SIZE2];
	for(j=0;j<SIZE2;j++)	
	MAT[i][j]=0;
	}
	return MAT;
}
int***	CPP_MEMORY_NEWint3(int SIZE1,int SIZE2,int SIZE3){
	int ***MAT;
	int i,j,k;
	MAT = new int**[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new int*[SIZE2];
	for(j=0;j<SIZE2;j++){
	MAT[i][j] = new int[SIZE3];
	for(k=0;k<SIZE3;k++)
	MAT[i][j][k]=0;
	}}
	return MAT;
}
long long*	CPP_MEMORY_NEWlonglong1(int SIZE1){
	long long *MAT;
	int i;
	MAT = new long long[SIZE1];
	for(i=0;i<SIZE1;i++)MAT[i]=0;
	return MAT;
}
float* 	CPP_MEMORY_NEWfloat1(int SIZE1){
	float *MAT;
	int i;
	MAT = new float[SIZE1];
	for(i=0;i<SIZE1;i++)
	MAT[i]=0;
	return MAT;
}
float** 	CPP_MEMORY_NEWfloat2(int SIZE1,int SIZE2){
	float **MAT;
	int i,j;
	MAT = new float*[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new float[SIZE2];
	for(j=0;j<SIZE2;j++)	
	MAT[i][j]=0;
	}
	return MAT;
}
double*	CPP_MEMORY_NEWdouble1(int SIZE1){
	double *MAT;
	int i;
	MAT = new double[SIZE1];
	for(i=0;i<SIZE1;i++)
	MAT[i]=0;
	return MAT;
}
double**	CPP_MEMORY_NEWdouble2(int SIZE1,int SIZE2){
	double **MAT;
	int i,j;
	MAT = new double*[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new double[SIZE2];
	for(j=0;j<SIZE2;j++)	
	MAT[i][j]=0;
	}
	return MAT;
}
double***	CPP_MEMORY_NEWdouble3(int SIZE1,int SIZE2,int SIZE3){
	double ***MAT;
	int i,j,k;
	MAT = new double**[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new double*[SIZE2];
	for(j=0;j<SIZE2;j++){
	MAT[i][j] = new double[SIZE3];
	for(k=0;k<SIZE3;k++)
	MAT[i][j][k]=0;
	}}
	return MAT;
}
double****	CPP_MEMORY_NEWdouble4(int SIZE1,int SIZE2,int SIZE3,int SIZE4){
	double ****MAT;
	int i,j,k,l;
	MAT = new double***[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new double**[SIZE2];
	for(j=0;j<SIZE2;j++){
	MAT[i][j] = new double*[SIZE3];
	for(k=0;k<SIZE3;k++){
	MAT[i][j][k] = new double[SIZE4];
	for(l=0;l<SIZE4;l++)
	MAT[i][j][k][l]=0;
	}}}

	return MAT;
}
double*****	CPP_MEMORY_NEWdouble5(int SIZE1,int SIZE2,int SIZE3,int SIZE4,int SIZE5){
	double *****MAT;
	int i,j,k,l,m;
	MAT = new double****[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new double***[SIZE2];
	for(j=0;j<SIZE2;j++){
	MAT[i][j] = new double**[SIZE3];
	for(k=0;k<SIZE3;k++){
	MAT[i][j][k] = new double*[SIZE4];
	for(l=0;l<SIZE4;l++){
	MAT[i][j][k][l] = new double[SIZE5];
	for(m=0;m<SIZE5;m++)
	MAT[i][j][k][l][m]=0;
	}}}}
	return MAT;
}
char***		CPP_MEMORY_NEWchar3(int SIZE1,int SIZE2,int SIZE3){
	char ***MAT;
	int i,j,k;
	MAT = new char**[SIZE1];
	for(i=0;i<SIZE1;i++){
	MAT[i] = new char*[SIZE2];
	for(j=0;j<SIZE2;j++){
	MAT[i][j] = new char[SIZE3];
	for(k=0;k<SIZE3;k++)
	MAT[i][j][k]=0;
	}}
	return MAT;
}
char*		CPP_MEMORY_NEWchar1(int SIZE1){
	char *MAT;
	MAT = new char[SIZE1];
	return MAT;
}
std::vector<std::vector<double> >	CPP_MEMORY_RESIZEV2(int SIZE1,int SIZE2){
	int i;
	std::vector<std::vector<double> > MAT;
	std::vector<double> MAT2;
	
	for(i=0;i<SIZE2;i++)
	MAT2.push_back(0.0);
	for(i=0;i<SIZE1;i++)
	MAT.push_back(MAT2);

	return MAT;
}
//------------------------------------------------------------
//DEL int and double

void	CPP_MEMORY_DELint1(int SIZE1,int *MAT){
	delete [] MAT;
}
void	CPP_MEMORY_DELint2(int SIZE1,int SIZE2,int **MAT){
	int i;
	for(i=0;i<SIZE1;i++)
	delete [] MAT[i];
	delete [] MAT;
}
void	CPP_MEMORY_DELint3(int SIZE1,int SIZE2,int SIZE3,int ***MAT){
	int i,j;
	for(i=0;i<SIZE1;i++){
	for(j=0;j<SIZE2;j++)
	delete [] MAT[i][j];
	delete [] MAT[i];
        }
	delete [] MAT;
}
void	CPP_MEMORY_DELlonglong1 (int SIZE1,long long *MAT){
	delete [] MAT;
}
void	CPP_MEMORY_DELfloat1 (int SIZE1,float  *MAT){
	delete [] MAT;
}
void	CPP_MEMORY_DELfloat2 (int SIZE1,int SIZE2,float  **MAT){
	int i;
	for(i=0;i<SIZE1;i++)
	delete [] MAT[i];
	delete [] MAT;
}
void	CPP_MEMORY_DELdouble1(int SIZE1,double *MAT){
	delete [] MAT;
}
void	CPP_MEMORY_DELdouble2(int SIZE1,int SIZE2,double **MAT){
	int i;
	for(i=0;i<SIZE1;i++)
	delete [] MAT[i];
	delete [] MAT;
}
void	CPP_MEMORY_DELdouble3(int SIZE1,int SIZE2,int SIZE3,double ***MAT){
	int i,j;
	for(i=0;i<SIZE1;i++){
	for(j=0;j<SIZE2;j++)
	delete [] MAT[i][j];
	delete [] MAT[i];
        }
	delete [] MAT;
}
void	CPP_MEMORY_DELdouble4(int SIZE1,int SIZE2,int SIZE3,int SIZE4,double ****MAT){
	int i,j,k;
	for(i=0;i<SIZE1;i++){
	for(j=0;j<SIZE2;j++){
	for(k=0;k<SIZE3;k++)
	delete [] MAT[i][j][k];
	delete [] MAT[i][j];
        }
	delete [] MAT[i];
        }
	delete [] MAT;
}
void	CPP_MEMORY_DELdouble5(int SIZE1,int SIZE2,int SIZE3,int SIZE4,int SIZE5,double *****MAT){
	int i,j,k,l;
	for(i=0;i<SIZE1;i++){
	for(j=0;j<SIZE2;j++){
	for(k=0;k<SIZE3;k++){
	for(l=0;l<SIZE4;l++)
	delete [] MAT[i][j][k][l];
	delete [] MAT[i][j][k];
        }
	delete [] MAT[i][j];
        }
	delete [] MAT[i];
        }
	delete [] MAT;
}
void	CPP_MEMORY_DELchar1(int SIZE1,char *MAT){
	delete [] MAT;
}

void	CPP_MEMORY_DELchar3(int SIZE1,int SIZE2,int SIZE3,char ***MAT){
	int i,j;
	for(i=0;i<SIZE1;i++){
	for(j=0;j<SIZE2;j++)
	delete [] MAT[i][j];
	delete [] MAT[i];
        }
	delete [] MAT;
}

