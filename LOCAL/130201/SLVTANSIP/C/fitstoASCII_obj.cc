//--------------------------------------------------
//fitstoASCII_obj.cc
//
//
//Last Update 2013/02/01
//--------------------------------------------------
#include<iostream>
#include<fstream>
#include<fitsio.h>
#include<string.h>

using namespace std;
int main(int argc ,char *argv[]){
	int i,DIRLEN;
	char DOT[1],DIR[100];
	char FITSNAME[100],ASCIINAME[100];
	ofstream out;


cout <<argv[1]<<endl;
cout <<argv[2]<<endl;
cout <<argv[3]<<endl;
cout <<argv[4]<<endl;
cout <<argv[5]<<endl;
cout <<argv[6]<<endl;
cout <<argv[7]<<endl;

	sprintf(FITSNAME,argv[1]);
	sprintf(DOT,".");

	for(i=strlen(FITSNAME)-1;i>-0.5;i--)
	if(FITSNAME[i]==DOT[0]){
		DIRLEN=i;
		break;
	}
	for(i=0;i<DIRLEN;i++)
	ASCIINAME[i]=FITSNAME[i];
	ASCIINAME[DIRLEN+0]='.';
	ASCIINAME[DIRLEN+1]='d';
	ASCIINAME[DIRLEN+2]='a';
	ASCIINAME[DIRLEN+3]='t';
	ASCIINAME[DIRLEN+4]='\0';
cout << ASCIINAME <<endl;
	out.open(ASCIINAME);
	
	int status=0;
	long NUM_ROW;
	int NUM_COL;
	char CID[100],CCHIP[100],CX[100],CY[100],CRA[100],CDEC[100];
	int NID,NCHIP,NX,NY,NRA,NDEC;
	int TID,TCHIP,TX,TY,TRA,TDEC;
	long repeat,width;
	int *nuval,anynul,hdutype;
	fitsfile *fptr;

	fits_open_file(&fptr,FITSNAME,READONLY,&status);
	fits_report_error(stderr,status);

	fits_movabs_hdu(fptr,2,&hdutype,&status);
	fits_report_error(stderr,status);
	fits_get_num_rows(fptr,&NUM_ROW,&status);
	fits_report_error(stderr,status);
	fits_get_num_cols(fptr,&NUM_COL,&status);
	fits_report_error(stderr,status);

	sprintf(CID  ,argv[2]);
	sprintf(CCHIP,argv[3]);
	sprintf(CX   ,argv[4]);
	sprintf(CY   ,argv[5]);
	sprintf(CRA  ,argv[6]);
	sprintf(CDEC ,argv[7]);

	fits_get_colnum(fptr,CASEINSEN,CID  ,&NID  ,&status);
	fits_report_error(stderr,status);
	fits_get_colnum(fptr,CASEINSEN,CCHIP,&NCHIP,&status);
	fits_report_error(stderr,status);
	fits_get_colnum(fptr,CASEINSEN,CX   ,&NX   ,&status);
	fits_report_error(stderr,status);
	fits_get_colnum(fptr,CASEINSEN,CY   ,&NY   ,&status);
	fits_report_error(stderr,status);
	fits_get_colnum(fptr,CASEINSEN,CRA  ,&NRA  ,&status);
	fits_report_error(stderr,status);
	fits_get_colnum(fptr,CASEINSEN,CDEC ,&NDEC ,&status);
	fits_report_error(stderr,status);

	fits_get_coltype(fptr,NID  ,&TID  ,&repeat,&width,&status);
	fits_report_error(stderr,status);
	fits_get_coltype(fptr,NCHIP,&TCHIP,&repeat,&width,&status);
	fits_report_error(stderr,status);
	fits_get_coltype(fptr,NX   ,&TX   ,&repeat,&width,&status);
	fits_report_error(stderr,status);
	fits_get_coltype(fptr,NY   ,&TY   ,&repeat,&width,&status);
	fits_report_error(stderr,status);
	fits_get_coltype(fptr,NRA  ,&TRA  ,&repeat,&width,&status);
	fits_report_error(stderr,status);
	fits_get_coltype(fptr,NDEC ,&TDEC ,&repeat,&width,&status);
	fits_report_error(stderr,status);

	long long int *ARID,*ARCHIP;
	double *ARX,*ARY,*ARRA,*ARDEC;
	ARID    = new long long[NUM_ROW];
	ARCHIP  = new long long[NUM_ROW];
	ARX     = new double[NUM_ROW];
	ARY     = new double[NUM_ROW];
	ARRA    = new double[NUM_ROW];
	ARDEC   = new double[NUM_ROW];

	fits_read_col(fptr,TID  ,NID  , 1,1,NUM_ROW,nuval,ARID  ,&anynul,&status);
	fits_report_error(stderr,status);
	fits_read_col(fptr,TCHIP,NCHIP, 1,1,NUM_ROW,nuval,ARCHIP,&anynul,&status);
	fits_report_error(stderr,status);
	fits_read_col(fptr,TX   ,NX   , 1,1,NUM_ROW,nuval,ARX   ,&anynul,&status);
	fits_report_error(stderr,status);
	fits_read_col(fptr,TY   ,NY   , 1,1,NUM_ROW,nuval,ARY   ,&anynul,&status);
	fits_report_error(stderr,status);
	fits_read_col(fptr,TRA  ,NRA  , 1,1,NUM_ROW,nuval,ARRA  ,&anynul,&status);
	fits_report_error(stderr,status);
	fits_read_col(fptr,TDEC ,NDEC , 1,1,NUM_ROW,nuval,ARDEC ,&anynul,&status);
	fits_report_error(stderr,status);

	fits_close_file(fptr,&status);
	fits_report_error(stderr,status);

	int NUM;
	for(NUM=0;NUM<NUM_ROW;NUM++)
	out << ARID[NUM]<<"	"<<
		ARCHIP[NUM]<<"	"<<
		ARX[NUM]<<"	"<<
		ARY[NUM]<<"	"<<
		ARRA[NUM]<<"	"<<
		ARDEC[NUM]<<endl;

	delete [] ARID;
	delete [] ARCHIP;
	delete [] ARX;
	delete [] ARY;
	delete [] ARRA;
	delete [] ARDEC;
}
