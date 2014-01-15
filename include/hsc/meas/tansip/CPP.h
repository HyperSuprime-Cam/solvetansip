//------------------------------------------------------------
//CPP.h
//
//Last modification : 2014/01/01
//Yuki Okura : yuki.okura@nao.ac.jp
//------------------------------------------------------------
#ifndef CPP_H
#define CPP_H

#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
//CPP_MEMORY
int*		CPP_MEMORY_NEWint1(int SIZE1);
int**		CPP_MEMORY_NEWint2(int SIZE1,int SIZE2);
int***		CPP_MEMORY_NEWint3(int SIZE1,int SIZE2,int SIZE3);
long long*	CPP_MEMORY_NEWlonglong1(int SIZE1);
double*		CPP_MEMORY_NEWdouble1(int SIZE1);
 float*		CPP_MEMORY_NEWfloat1 (int SIZE1);
 float**	CPP_MEMORY_NEWfloat2 (int SIZE1,int SIZE2);
double**	CPP_MEMORY_NEWdouble2(int SIZE1,int SIZE2);
double***	CPP_MEMORY_NEWdouble3(int SIZE1,int SIZE2,int SIZE3);
double****	CPP_MEMORY_NEWdouble4(int SIZE1,int SIZE2,int SIZE3,int SIZE4);
double*****	CPP_MEMORY_NEWdouble5(int SIZE1,int SIZE2,int SIZE3,int SIZE4,int SIZE5);
char*		CPP_MEMORY_NEWchar1(int SIZE1);
char***		CPP_MEMORY_NEWchar3(int SIZE1,int SIZE2,int SIZE3);
std::vector<std::vector<double> >	CPP_MEMORY_RESIZEV2(int SIZE1,int SIZE2);
void	CPP_MEMORY_DELint1(int SIZE1,int *MAT);
void	CPP_MEMORY_DELint2(int SIZE1,int SIZE2,int **MAT);
void	CPP_MEMORY_DELint3(int SIZE1,int SIZE2,int SIZE3,int ***MAT);
void	CPP_MEMORY_DELlonglong1(int SIZE1,long long *MAT);
void	CPP_MEMORY_DELfloat1 (int SIZE1,float  *MAT);
void	CPP_MEMORY_DELfloat2 (int SIZE1,int SIZE2,float  **MAT);
void	CPP_MEMORY_DELdouble1(int SIZE1,double *MAT);
void	CPP_MEMORY_DELdouble2(int SIZE1,int SIZE2,double **MAT);
void	CPP_MEMORY_DELdouble3(int SIZE1,int SIZE2,int SIZE3,double ***MAT);
void	CPP_MEMORY_DELdouble4(int SIZE1,int SIZE2,int SIZE3,int SIZE4,double ****MAT);
void	CPP_MEMORY_DELdouble5(int SIZE1,int SIZE2,int SIZE3,int SIZE4,int SIZE5,double *****MAT);
void	CPP_MEMORY_DELchar1(int SIZE1,char *MAT);
void	CPP_MEMORY_DELchar3(int SIZE1,int SIZE2,int SIZE3,char ***MAT);

#endif
