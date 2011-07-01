//------------------------------------------------------------
//GETKEYVALUE.cc
//obtaining value of keyword
//
//Last modification : 2010/07/14
//------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<cstring>

using namespace::std;
void    F_GETKEYVALUE10(int KEYNUM,char ***KEYVALUE,char *FILENAME){
    int i,j,k,NUMCONF;
    char S[200][101];
    ifstream fin;

    fin.open(FILENAME);
    if(!fin){
        cout << "ERROR : Can't read " << FILENAME << endl;
        return;
    }
    i=0;
    while((fin.getline(S[i],100,'\n')) !=NULL)
    i++;
    NUMCONF=i;

    for(j=0;j<KEYNUM;j++){
        for(i=0;i<NUMCONF;i++)
        if(KEYVALUE[j][0][0] == '\0' || S[i][0] == '\0'){
            break;
        }else if(strncmp(S[i],KEYVALUE[j][0],10) == 0){
            for(k=0;k<10;k++)
            KEYVALUE[j][1][k]=S[i][k+10];
            break;
        }
        if(i==NUMCONF){
        cout << "Some error occured in some parameters of " << FILENAME << ":" << KEYVALUE[j][0] << endl;
        KEYVALUE[j][1][0]=0;
        KEYVALUE[j][1][1]='\0';
        break;
        }
    }
    fin.close();
}

void    F_GETKEYVALUE14(int KEYNUM,char ***KEYVALUE,char *FILENAME){
    int i,j,k,NUMCONF;
    char S[200][101];
    ifstream fin;

    fin.open(FILENAME);
    if(!fin){
        cout << "ERROR : Can't read " << FILENAME << endl;
        return;
    }
    i=0;
    while((fin.getline(S[i],100,'\n')) !=NULL)
    i++;
    NUMCONF=i;

    for(j=0;j<KEYNUM;j++){
        for(i=0;i<NUMCONF;i++)
        if(KEYVALUE[j][0][0] == '\0' || S[i][0] == '\0'){
            break;
        }else if(strncmp(S[i],KEYVALUE[j][0],10) == 0){
            for(k=0;k<14;k++)
            KEYVALUE[j][1][k]=S[i][k+10];
            break;
        }
        if(i==NUMCONF){
        cout << "Some error occured in some parameters of " << FILENAME << ":" << KEYVALUE[j][0] << endl;
        KEYVALUE[j][1][0]=0;
        KEYVALUE[j][1][1]='\0';
        break;
        }
    }
    fin.close();
}
