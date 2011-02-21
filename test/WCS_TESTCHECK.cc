#include<iostream>
#include<fstream>
#include<cstdio>
#include "../include/hsc/meas/tansip/WCS_APROP.h"
#include "../include/hsc/meas/tansip/WCS_CPROP.h"
#include "../include/hsc/meas/tansip/WCS_PAIR.h"
#include "../include/hsc/meas/tansip/WCS_CSIP.h"


using namespace::std;
void    F_WCS_CHECK(CL_APROP APROP,CL_CPROP* CPROP,CL_PAIR* PAIR,CL_CSIP* CSIP){
    int i,j,k,ij;
    char fhead[100];
    ofstream Chead;
//--------------------------------------------------
cout << scientific;
    cout << "\n--- Check ---\n";
    cout << "CRPIX  : " << CSIP[APROP.CCDNUM].CRPIX[0] << " , " << CSIP[APROP.CCDNUM].CRPIX[1] << endl;
    cout << "CRVAL  : " << CSIP[APROP.CCDNUM].CRVAL[0] << " , " << CSIP[APROP.CCDNUM].CRVAL[1] << endl;
    cout << endl;
    cout << "CD_1_1 : " << CSIP[APROP.CCDNUM].CD[0][0] << endl;
    cout << "CD_1_2 : " << CSIP[APROP.CCDNUM].CD[0][1] << endl;
    cout << "CD_2_1 : " << CSIP[APROP.CCDNUM].CD[1][0] << endl;
    cout << "CD_2_2 : " << CSIP[APROP.CCDNUM].CD[1][1] << endl;
    cout << endl;
    for(i=0;i<0.5*(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2);i++)
    cout << "Coef_x : " << i << "	" << CSIP[APROP.CCDNUM].SIP_AB[0][i] << endl;
    for(i=0;i<0.5*(APROP.SIP_ORDER+1)*(APROP.SIP_ORDER+2);i++)
    cout << "Coef_y : " << i << "	" << CSIP[APROP.CCDNUM].SIP_AB[1][i] << endl;

    cout << "--- GLOB_POS ---" << endl;
cout << fixed;
    for(i=0;i<APROP.CCDNUM;i++)
    cout << "CCD : " << i << " : x : " << fixed << CPROP[i].GLOB_POS[0] << endl << "CCD : " << i << " : y : " <<fixed <<  CPROP[i].GLOB_POS[1] << endl << "CCD : " << i << " : t : " <<scientific <<  CPROP[i].GLOB_POS[2] << endl;
// output header --------------------------------------------------
    for(i=0;i<APROP.CCDNUM+1;i++){
        if(i==APROP.CCDNUM){
        sprintf(fhead,"test/Head_GLOBAL.dat",i);
	}else{
        sprintf(fhead,"test/Head_%03d.dat",i);
	}
        Chead.open(fhead);
        Chead << "ID        : " << CSIP[i].ID << endl;
        Chead << "FITNUM    : " << CSIP[i].FITNUM << endl;
        Chead << "CRVAL_1   : " << CSIP[i].CRVAL[0] << endl;
        Chead << "CRVAL_2   : " << CSIP[i].CRVAL[1] << endl;
        Chead << "CRPIX_1   : " << CSIP[i].CRPIX[0] << endl;
        Chead << "CRPIX_2   : " << CSIP[i].CRPIX[1] << endl;
        Chead << "CD_1_1    : " << CSIP[i].CD[0][0] << endl;
        Chead << "CD_1_2    : " << CSIP[i].CD[0][1] << endl;
        Chead << "CD_2_1    : " << CSIP[i].CD[1][0] << endl;
        Chead << "CD_2_2    : " << CSIP[i].CD[1][1] << endl;
        Chead << "A_ORDER   : " << CSIP[i].SIP_AB_ORDER << endl;
        ij=0;
        for(k=0;k<APROP.SIP_ORDER+1;k++)
        for(j=0;j<APROP.SIP_ORDER+1;j++)
        if(k+j<APROP.SIP_ORDER+1){
        Chead << "A_" << k << "_" << j << "     : " << CSIP[i].SIP_AB[0][ij] << endl;
        ij++;
        }
        Chead << "B_ORDER   : " << CSIP[i].SIP_AB_ORDER << endl;
        ij=0;
        for(k=0;k<APROP.SIP_ORDER+1;k++)
        for(j=0;j<APROP.SIP_ORDER+1;j++)
        if(k+j<APROP.SIP_ORDER+1){
        Chead << "B_" << k << "_" << j << "     : " << CSIP[i].SIP_AB[1][ij] << endl;
        ij++;
        }
        Chead << "SIPABAVE_1: " << CSIP[i].SIP_AB_AVE[0] << endl;
        Chead << "SIPABAVE_2: " << CSIP[i].SIP_AB_AVE[1] << endl;
        Chead << "SIPABRMS_1: " << CSIP[i].SIP_AB_RMS[0] << endl;
        Chead << "SIPABRMS_2: " << CSIP[i].SIP_AB_RMS[1] << endl;
        Chead << "AP_ORDER  : " << CSIP[i].SIP_ABP_ORDER << endl;
        Chead << "BP_ORDER  : " << CSIP[i].SIP_ABP_ORDER << endl;
        ij=0;
        for(k=0;k<APROP.SIP_P_ORDER+1;k++)
        for(j=0;j<APROP.SIP_P_ORDER+1;j++)
        if(k+j<APROP.SIP_P_ORDER+1){
        Chead << "AP_" << k << "_" << j << "    : " << CSIP[i].SIP_ABP[0][ij] << endl;
        ij++;
        }
        ij=0;
        for(k=0;k<APROP.SIP_P_ORDER+1;k++)
        for(j=0;j<APROP.SIP_P_ORDER+1;j++)
        if(k+j<APROP.SIP_P_ORDER+1){
        Chead << "BP_" << k << "_" << j << "    : " << CSIP[i].SIP_ABP[1][ij] << endl;
        ij++;
        }
        Chead.close();
    }
//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------
}
void    F_WCS_TEST(){
}
/*
void    F_CHECK(CL_APROP APROP ,CL_PAIR *PAIR ,CL_CSIP *CSIP){
    int i,CID;
    string outname, outname_global;
    ostringstream oss, oss_global;
    ofstream outcheckfile, outcheckfile_global;

    oss_global.str("");
    oss_global << "temp/TANSIPFIT_checkfile_global.dat";
    outname_global = oss_global.str();

    cout << "checkfile : " << outname_global << endl;
    outcheckfile_global.open(outname_global.c_str(), ios::out);

    for(i=0;i<APROP.NUMREFALL;i++) {
      if(PAIR[i].FLAG==1){
	outcheckfile_global << setprecision(6) << fixed << PAIR[i].CHIPID << "\t" 
			    << PAIR[i].x << "\t" << PAIR[i].y << "\t" 
			    << PAIR[i].RA << "\t" << PAIR[i].DEC << "\t" 
			    << PAIR[i].xSIP << "\t" << PAIR[i].ySIP << "\t" 
			    << PAIR[i].RAfit << "\t" << PAIR[i].DECfit << endl;
      }
    }
    outcheckfile_global.close();
    cout << "checkfiles done. " << endl;
}*/
