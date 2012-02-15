//------------------------------------------------------------
//WCS_SIMULATION.cc
//for simulation test
//
//Last modification : 2012/01/25
//------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<cmath>
#include "hsc/meas/tansip/WCS_PL_MAIN.h"
#include "hsc/meas/tansip/WCS_TANSIP.h"
#include "hsc/meas/tansip/WCS_CSIP.h"
#include "hsc/meas/tansip/WCS_PAIR.h"
#include "hsc/meas/tansip/WCS_SIMULATION.h"

using namespace std;
void F_WCSA_SIMULATION_MAIN(int HARD,string CCDPOSfile, string DISTfile, double NSCALE,int RANNUM,int REFNUM){
    CL_GSIP *GSIP;
    char fCCDPOS[100];
    char fDISTORTION[100];
    ifstream in;

    GSIP = new CL_GSIP[1];
    sprintf(fCCDPOS,CCDPOSfile.c_str());
    sprintf(fDISTORTION,DISTfile.c_str());
    if(HARD==0){
        F_WCSA_SIMULATION_INPUT_SIMULATIONBASIS_SC(GSIP);
        GSIP->CSIP = new CL_CSIP[GSIP->CCDNUM];
        GSIP->SIP_AB[0] =F_NEWdouble1((GSIP->SIP_ORDER  +1)*(GSIP->SIP_ORDER  +2));
        GSIP->SIP_AB[1] =F_NEWdouble1((GSIP->SIP_ORDER  +1)*(GSIP->SIP_ORDER  +2));
        GSIP->SIP_ABP[0]=F_NEWdouble1((GSIP->SIP_P_ORDER+1)*(GSIP->SIP_P_ORDER+2));
        GSIP->SIP_ABP[1]=F_NEWdouble1((GSIP->SIP_P_ORDER+1)*(GSIP->SIP_P_ORDER+2));

        F_WCSA_SIMULATION_INPUT_CCDPOSITION_SCfromFile(fCCDPOS,GSIP);
        F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_SCfromFile(fDISTORTION,GSIP);
    }else{
        F_WCSA_SIMULATION_INPUT_SIMULATIONBASIS_HSC(GSIP);
        GSIP->CSIP = new CL_CSIP[GSIP->CCDNUM];
        GSIP->SIP_AB[0] =F_NEWdouble1((GSIP->SIP_ORDER  +1)*(GSIP->SIP_ORDER  +2));
        GSIP->SIP_AB[1] =F_NEWdouble1((GSIP->SIP_ORDER  +1)*(GSIP->SIP_ORDER  +2));
        GSIP->SIP_ABP[0]=F_NEWdouble1((GSIP->SIP_P_ORDER+1)*(GSIP->SIP_P_ORDER+2));
        GSIP->SIP_ABP[1]=F_NEWdouble1((GSIP->SIP_P_ORDER+1)*(GSIP->SIP_P_ORDER+2));

        F_WCSA_SIMULATION_INPUT_CCDPOSITION_HSCfromFile(fCCDPOS,GSIP);
        F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_HSCfromFile(fDISTORTION,GSIP);
    }

    F_WCSA_SIMULATION_MAKE_REFERENCESwithRANDOMNOISE(RANNUM,REFNUM,NSCALE,GSIP);

    delete [] GSIP->CSIP;
    delete [] GSIP->SIP_AB[0];
    delete [] GSIP->SIP_AB[1];
    delete [] GSIP->SIP_ABP[0];
    delete [] GSIP->SIP_ABP[1];
    delete [] GSIP;
}
void F_WCSA_SIMULATION_DIFF(int HARD,std::string CCDPOSfile,std::string DISTfile,CL_WCSA_ASP* WCSA_ASP){
    CL_GSIP *GSIP;
    char fCCDPOS[100];
    char fDISTORTION[100];
    ifstream in;

    GSIP = new CL_GSIP[1];
    sprintf(fCCDPOS,CCDPOSfile.c_str());
    sprintf(fDISTORTION,DISTfile.c_str());
    if(HARD==0){
        F_WCSA_SIMULATION_INPUT_SIMULATIONBASIS_SC(GSIP);
        GSIP->CSIP = new CL_CSIP[GSIP->CCDNUM];
        GSIP->SIP_AB[0] =F_NEWdouble1((GSIP->SIP_ORDER  +1)*(GSIP->SIP_ORDER  +2));
        GSIP->SIP_AB[1] =F_NEWdouble1((GSIP->SIP_ORDER  +1)*(GSIP->SIP_ORDER  +2));
        GSIP->SIP_ABP[0]=F_NEWdouble1((GSIP->SIP_P_ORDER+1)*(GSIP->SIP_P_ORDER+2));
        GSIP->SIP_ABP[1]=F_NEWdouble1((GSIP->SIP_P_ORDER+1)*(GSIP->SIP_P_ORDER+2));

	    F_WCSA_SIMULATION_INPUT_CCDPOSITION_SCfromFile(fCCDPOS,GSIP);
	    F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_SCfromFile(fDISTORTION,GSIP);
	    F_WCSA_SIMULATION_CALC_DIFF_SC(WCSA_ASP,GSIP);
    }else{
        F_WCSA_SIMULATION_INPUT_SIMULATIONBASIS_HSC(GSIP);
        GSIP->CSIP = new CL_CSIP[GSIP->CCDNUM];
        GSIP->SIP_AB[0] =F_NEWdouble1((GSIP->SIP_ORDER  +1)*(GSIP->SIP_ORDER  +2));
        GSIP->SIP_AB[1] =F_NEWdouble1((GSIP->SIP_ORDER  +1)*(GSIP->SIP_ORDER  +2));
        GSIP->SIP_ABP[0]=F_NEWdouble1((GSIP->SIP_P_ORDER+1)*(GSIP->SIP_P_ORDER+2));
        GSIP->SIP_ABP[1]=F_NEWdouble1((GSIP->SIP_P_ORDER+1)*(GSIP->SIP_P_ORDER+2));
	    F_WCSA_SIMULATION_INPUT_CCDPOSITION_HSCfromFile(fCCDPOS,GSIP);
	    F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_HSCfromFile(fDISTORTION,GSIP);
	    F_WCSA_SIMULATION_CALC_DIFF_HSC(WCSA_ASP,GSIP);
    }

    delete [] GSIP->CSIP;
    delete [] GSIP->SIP_AB[0];
    delete [] GSIP->SIP_AB[1];
    delete [] GSIP->SIP_ABP[0];
    delete [] GSIP->SIP_ABP[1];
    delete [] GSIP;
}
//----------------------------------------------------------------------------------------------------


void F_WCSA_SIMULATION_INPUT_SIMULATIONBASIS_SC(CL_GSIP* GSIP){
    GSIP->CCDNUM=10;
    GSIP->SIP_ORDER=5;
    GSIP->SIP_P_ORDER=5;
}
void F_WCSA_SIMULATION_INPUT_SIMULATIONBASIS_HSC(CL_GSIP* GSIP){
    GSIP->CCDNUM=100;
    GSIP->SIP_ORDER=9;
    GSIP->SIP_P_ORDER=9;
}
void F_WCSA_SIMULATION_INPUT_CCDPOSITION_SCfromFile(char *filename,CL_GSIP* GSIP){
    int i,j;
    ifstream in;
    in.open(filename);

    if(!in){
        cout << filename << " can not be open." << endl;
        cout << "Using default values." << endl;
        F_WCSA_SIMULATION_INPUT_CCDPOSITION_SC(GSIP);
    }else{
        for(i=0;i<10;i++)
        for(j=0;j< 3;j++)
        in >> GSIP->CSIP[i].GPOS[j];
    }
}
void F_WCSA_SIMULATION_INPUT_CCDPOSITION_SC(CL_GSIP* GSIP){
    GSIP->CSIP[  0].GPOS[0]= 3272.00;
    GSIP->CSIP[  0].GPOS[1]=   50.00;
    GSIP->CSIP[  0].GPOS[2]= 0.00000;
    GSIP->CSIP[  1].GPOS[0]= 1124.00;
    GSIP->CSIP[  1].GPOS[1]=   50.00;
    GSIP->CSIP[  1].GPOS[2]= 0.00000;
    GSIP->CSIP[  2].GPOS[0]=-1024.00;
    GSIP->CSIP[  2].GPOS[1]=   50.00;
    GSIP->CSIP[  2].GPOS[2]= 0.00000;
    GSIP->CSIP[  3].GPOS[0]= 3272.00;
    GSIP->CSIP[  3].GPOS[1]=-4146.00;
    GSIP->CSIP[  3].GPOS[2]= 0.00000;
    GSIP->CSIP[  4].GPOS[0]= 1124.00;
    GSIP->CSIP[  4].GPOS[1]=-4146.00;
    GSIP->CSIP[  4].GPOS[2]= 0.00000;
    GSIP->CSIP[  5].GPOS[0]=-1024.00;
    GSIP->CSIP[  5].GPOS[1]=-4146.00;
    GSIP->CSIP[  5].GPOS[2]= 0.00000;
    GSIP->CSIP[  6].GPOS[0]=-5320.00;
    GSIP->CSIP[  6].GPOS[1]=   50.00;
    GSIP->CSIP[  6].GPOS[2]= 0.00000;
    GSIP->CSIP[  7].GPOS[0]=-3172.00;
    GSIP->CSIP[  7].GPOS[1]=   50.00;
    GSIP->CSIP[  7].GPOS[2]= 0.00000;
    GSIP->CSIP[  8].GPOS[0]=-5320.00;
    GSIP->CSIP[  8].GPOS[1]=-4146.00;
    GSIP->CSIP[  8].GPOS[2]= 0.00000;
    GSIP->CSIP[  9].GPOS[0]=-3172.00;
    GSIP->CSIP[  9].GPOS[1]=-4146.00;
}
void F_WCSA_SIMULATION_INPUT_CCDPOSITION_HSCfromFile(char *filename,CL_GSIP* GSIP){
    int i,j;
    ifstream in;
    in.open(filename);
    
    if(!in){
        cout << filename << " can not be open." << endl;
        cout << "Using default values." << endl;
        F_WCSA_SIMULATION_INPUT_CCDPOSITION_HSC(GSIP);
    }else{
        for(i=0;i<100;i++)
        for(j=0;j<  3;j++)
        in >> GSIP->CSIP[i].GPOS[j];
    }
}
void F_WCSA_SIMULATION_INPUT_CCDPOSITION_HSC(CL_GSIP* GSIP){
    GSIP->CSIP[  0].GPOS[0]=- 9514.700;
    GSIP->CSIP[  0].GPOS[1]=    37.350;
    GSIP->CSIP[  0].GPOS[2]=  0.000000;
    GSIP->CSIP[  1].GPOS[0]=  7466.700;
    GSIP->CSIP[  1].GPOS[1]=- 4133.350;
    GSIP->CSIP[  1].GPOS[2]=  0.000000;
    GSIP->CSIP[  2].GPOS[0]=- 7392.000;
    GSIP->CSIP[  2].GPOS[1]=    37.350;
    GSIP->CSIP[  2].GPOS[2]=  0.000000;
    GSIP->CSIP[  3].GPOS[0]=  5344.000;
    GSIP->CSIP[  3].GPOS[1]=- 4133.350;
    GSIP->CSIP[  3].GPOS[2]=  0.000000;
    GSIP->CSIP[  4].GPOS[0]=- 5269.300;
    GSIP->CSIP[  4].GPOS[1]=    37.350;
    GSIP->CSIP[  4].GPOS[2]=  0.000000;
    GSIP->CSIP[  5].GPOS[0]=  3221.300;
    GSIP->CSIP[  5].GPOS[1]=- 4133.350;
    GSIP->CSIP[  5].GPOS[2]=  0.000000;
    GSIP->CSIP[  6].GPOS[0]=- 3146.700;
    GSIP->CSIP[  6].GPOS[1]=    37.350;
    GSIP->CSIP[  6].GPOS[2]=  0.000000;
    GSIP->CSIP[  7].GPOS[0]=  1098.700;
    GSIP->CSIP[  7].GPOS[1]=- 4133.350;
    GSIP->CSIP[  7].GPOS[2]=  0.000000;
    GSIP->CSIP[  8].GPOS[0]=- 1024.000;
    GSIP->CSIP[  8].GPOS[1]=    37.350;
    GSIP->CSIP[  8].GPOS[2]=  0.000000;
    GSIP->CSIP[  9].GPOS[0]=- 1024.000;
    GSIP->CSIP[  9].GPOS[1]=- 4133.350;
    GSIP->CSIP[  9].GPOS[2]=  0.000000;
    GSIP->CSIP[ 10].GPOS[0]=  1098.700;
    GSIP->CSIP[ 10].GPOS[1]=    37.350;
    GSIP->CSIP[ 10].GPOS[2]=  0.000000;
    GSIP->CSIP[ 11].GPOS[0]=- 3146.700;
    GSIP->CSIP[ 11].GPOS[1]=- 4133.350;
    GSIP->CSIP[ 11].GPOS[2]=  0.000000;
    GSIP->CSIP[ 12].GPOS[0]=  3221.300;
    GSIP->CSIP[ 12].GPOS[1]=    37.350;
    GSIP->CSIP[ 12].GPOS[2]=  0.000000;
    GSIP->CSIP[ 13].GPOS[0]=- 5269.300;
    GSIP->CSIP[ 13].GPOS[1]=- 4133.350;
    GSIP->CSIP[ 13].GPOS[2]=  0.000000;
    GSIP->CSIP[ 14].GPOS[0]=  5344.000;
    GSIP->CSIP[ 14].GPOS[1]=    37.350;
    GSIP->CSIP[ 14].GPOS[2]=  0.000000;
    GSIP->CSIP[ 15].GPOS[0]=- 7392.000;
    GSIP->CSIP[ 15].GPOS[1]=- 4133.350;
    GSIP->CSIP[ 15].GPOS[2]=  0.000000;
    GSIP->CSIP[ 16].GPOS[0]=  7466.700;
    GSIP->CSIP[ 16].GPOS[1]=    37.350;
    GSIP->CSIP[ 16].GPOS[2]=  0.000000;
    GSIP->CSIP[ 17].GPOS[0]=- 9514.700;
    GSIP->CSIP[ 17].GPOS[1]=- 4133.350;
    GSIP->CSIP[ 17].GPOS[2]=  0.000000;
    GSIP->CSIP[ 18].GPOS[0]=  9589.300;
    GSIP->CSIP[ 18].GPOS[1]=    37.350;
    GSIP->CSIP[ 18].GPOS[2]=  0.000000;
    GSIP->CSIP[ 19].GPOS[0]=-11637.300;
    GSIP->CSIP[ 19].GPOS[1]=- 4133.350;
    GSIP->CSIP[ 19].GPOS[2]=  0.000000;
    GSIP->CSIP[ 20].GPOS[0]= 11712.000;
    GSIP->CSIP[ 20].GPOS[1]=    37.350;
    GSIP->CSIP[ 20].GPOS[2]=  0.000000;
    GSIP->CSIP[ 21].GPOS[0]=-13760.000;
    GSIP->CSIP[ 21].GPOS[1]=- 4133.350;
    GSIP->CSIP[ 21].GPOS[2]=  0.000000;
    GSIP->CSIP[ 22].GPOS[0]= 13834.700;
    GSIP->CSIP[ 22].GPOS[1]=    37.350;
    GSIP->CSIP[ 22].GPOS[2]=  0.000000;
    GSIP->CSIP[ 23].GPOS[0]=-15882.700;
    GSIP->CSIP[ 23].GPOS[1]=- 4133.350;
    GSIP->CSIP[ 23].GPOS[2]=  0.000000;
    GSIP->CSIP[ 24].GPOS[0]=- 9514.700;
    GSIP->CSIP[ 24].GPOS[1]=  4512.350;
    GSIP->CSIP[ 24].GPOS[2]=  0.000000;
    GSIP->CSIP[ 25].GPOS[0]=  7466.700;
    GSIP->CSIP[ 25].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 25].GPOS[2]=  0.000000;
    GSIP->CSIP[ 26].GPOS[0]=- 7392.000;
    GSIP->CSIP[ 26].GPOS[1]=  4512.350;
    GSIP->CSIP[ 26].GPOS[2]=  0.000000;
    GSIP->CSIP[ 27].GPOS[0]=  5344.000;
    GSIP->CSIP[ 27].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 27].GPOS[2]=  0.000000;
    GSIP->CSIP[ 28].GPOS[0]=- 5269.300;
    GSIP->CSIP[ 28].GPOS[1]=  4512.350;
    GSIP->CSIP[ 28].GPOS[2]=  0.000000;
    GSIP->CSIP[ 29].GPOS[0]=  3221.300;
    GSIP->CSIP[ 29].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 29].GPOS[2]=  0.000000;
    GSIP->CSIP[ 30].GPOS[0]=- 3146.700;
    GSIP->CSIP[ 30].GPOS[1]=  4512.350;
    GSIP->CSIP[ 30].GPOS[2]=  0.000000;
    GSIP->CSIP[ 31].GPOS[0]=  1098.700;
    GSIP->CSIP[ 31].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 31].GPOS[2]=  0.000000;
    GSIP->CSIP[ 32].GPOS[0]=- 1024.000;
    GSIP->CSIP[ 32].GPOS[1]=  4512.350;
    GSIP->CSIP[ 32].GPOS[2]=  0.000000;
    GSIP->CSIP[ 33].GPOS[0]=- 1024.000;
    GSIP->CSIP[ 33].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 33].GPOS[2]=  0.000000;
    GSIP->CSIP[ 34].GPOS[0]=  1098.700;
    GSIP->CSIP[ 34].GPOS[1]=  4512.350;
    GSIP->CSIP[ 34].GPOS[2]=  0.000000;
    GSIP->CSIP[ 35].GPOS[0]=- 3146.700;
    GSIP->CSIP[ 35].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 35].GPOS[2]=  0.000000;
    GSIP->CSIP[ 36].GPOS[0]=  3221.300;
    GSIP->CSIP[ 36].GPOS[1]=  4512.350;
    GSIP->CSIP[ 36].GPOS[2]=  0.000000;
    GSIP->CSIP[ 37].GPOS[0]=- 5269.300;
    GSIP->CSIP[ 37].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 37].GPOS[2]=  0.000000;
    GSIP->CSIP[ 38].GPOS[0]=  5344.000;
    GSIP->CSIP[ 38].GPOS[1]=  4512.350;
    GSIP->CSIP[ 38].GPOS[2]=  0.000000;
    GSIP->CSIP[ 39].GPOS[0]=- 7392.000;
    GSIP->CSIP[ 39].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 39].GPOS[2]=  0.000000;
    GSIP->CSIP[ 40].GPOS[0]=  7466.700;
    GSIP->CSIP[ 40].GPOS[1]=  4512.350;
    GSIP->CSIP[ 40].GPOS[2]=  0.000000;
    GSIP->CSIP[ 41].GPOS[0]=- 9514.700;
    GSIP->CSIP[ 41].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 41].GPOS[2]=  0.000000;
    GSIP->CSIP[ 42].GPOS[0]=  9589.300;
    GSIP->CSIP[ 42].GPOS[1]=  4512.350;
    GSIP->CSIP[ 42].GPOS[2]=  0.000000;
    GSIP->CSIP[ 43].GPOS[0]=-11637.300;
    GSIP->CSIP[ 43].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 43].GPOS[2]=  0.000000;
    GSIP->CSIP[ 44].GPOS[0]= 11712.000;
    GSIP->CSIP[ 44].GPOS[1]=  4512.350;
    GSIP->CSIP[ 44].GPOS[2]=  0.000000;
    GSIP->CSIP[ 45].GPOS[0]=-13760.000;
    GSIP->CSIP[ 45].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 45].GPOS[2]=  0.000000;
    GSIP->CSIP[ 46].GPOS[0]= 13834.700;
    GSIP->CSIP[ 46].GPOS[1]=  4512.350;
    GSIP->CSIP[ 46].GPOS[2]=  0.000000;
    GSIP->CSIP[ 47].GPOS[0]=-15882.700;
    GSIP->CSIP[ 47].GPOS[1]=- 8608.350;
    GSIP->CSIP[ 47].GPOS[2]=  0.000000;
    GSIP->CSIP[ 48].GPOS[0]=- 9514.700;
    GSIP->CSIP[ 48].GPOS[1]=  8987.350;
    GSIP->CSIP[ 48].GPOS[2]=  0.000000;
    GSIP->CSIP[ 49].GPOS[0]=  7466.700;
    GSIP->CSIP[ 49].GPOS[1]=-13083.350;
    GSIP->CSIP[ 49].GPOS[2]=  0.000000;
    GSIP->CSIP[ 50].GPOS[0]=- 7392.000;
    GSIP->CSIP[ 50].GPOS[1]=  8987.350;
    GSIP->CSIP[ 50].GPOS[2]=  0.000000;
    GSIP->CSIP[ 51].GPOS[0]=  5344.000;
    GSIP->CSIP[ 51].GPOS[1]=-13083.350;
    GSIP->CSIP[ 51].GPOS[2]=  0.000000;
    GSIP->CSIP[ 52].GPOS[0]=- 5269.300;
    GSIP->CSIP[ 52].GPOS[1]=  8987.350;
    GSIP->CSIP[ 52].GPOS[2]=  0.000000;
    GSIP->CSIP[ 53].GPOS[0]=  3221.300;
    GSIP->CSIP[ 53].GPOS[1]=-13083.350;
    GSIP->CSIP[ 53].GPOS[2]=  0.000000;
    GSIP->CSIP[ 54].GPOS[0]=- 3146.700;
    GSIP->CSIP[ 54].GPOS[1]=  8987.350;
    GSIP->CSIP[ 54].GPOS[2]=  0.000000;
    GSIP->CSIP[ 55].GPOS[0]=  1098.700;
    GSIP->CSIP[ 55].GPOS[1]=-13083.350;
    GSIP->CSIP[ 55].GPOS[2]=  0.000000;
    GSIP->CSIP[ 56].GPOS[0]=- 1024.000;
    GSIP->CSIP[ 56].GPOS[1]=  8987.350;
    GSIP->CSIP[ 56].GPOS[2]=  0.000000;
    GSIP->CSIP[ 57].GPOS[0]=- 1024.000;
    GSIP->CSIP[ 57].GPOS[1]=-13083.350;
    GSIP->CSIP[ 57].GPOS[2]=  0.000000;
    GSIP->CSIP[ 58].GPOS[0]=  1098.700;
    GSIP->CSIP[ 58].GPOS[1]=  8987.350;
    GSIP->CSIP[ 58].GPOS[2]=  0.000000;
    GSIP->CSIP[ 59].GPOS[0]=- 3146.700;
    GSIP->CSIP[ 59].GPOS[1]=-13083.350;
    GSIP->CSIP[ 59].GPOS[2]=  0.000000;
    GSIP->CSIP[ 60].GPOS[0]=  3221.300;
    GSIP->CSIP[ 60].GPOS[1]=  8987.350;
    GSIP->CSIP[ 60].GPOS[2]=  0.000000;
    GSIP->CSIP[ 61].GPOS[0]=- 5269.300;
    GSIP->CSIP[ 61].GPOS[1]=-13083.350;
    GSIP->CSIP[ 61].GPOS[2]=  0.000000;
    GSIP->CSIP[ 62].GPOS[0]=  5344.000;
    GSIP->CSIP[ 62].GPOS[1]=  8987.350;
    GSIP->CSIP[ 62].GPOS[2]=  0.000000;
    GSIP->CSIP[ 63].GPOS[0]=- 7392.000;
    GSIP->CSIP[ 63].GPOS[1]=-13083.350;
    GSIP->CSIP[ 63].GPOS[2]=  0.000000;
    GSIP->CSIP[ 64].GPOS[0]=  7466.700;
    GSIP->CSIP[ 64].GPOS[1]=  8987.350;
    GSIP->CSIP[ 64].GPOS[2]=  0.000000;
    GSIP->CSIP[ 65].GPOS[0]=- 9514.700;
    GSIP->CSIP[ 65].GPOS[1]=-13083.350;
    GSIP->CSIP[ 65].GPOS[2]=  0.000000;
    GSIP->CSIP[ 66].GPOS[0]=  9589.300;
    GSIP->CSIP[ 66].GPOS[1]=  8987.350;
    GSIP->CSIP[ 66].GPOS[2]=  0.000000;
    GSIP->CSIP[ 67].GPOS[0]=-11637.300;
    GSIP->CSIP[ 67].GPOS[1]=-13083.350;
    GSIP->CSIP[ 67].GPOS[2]=  0.000000;
    GSIP->CSIP[ 68].GPOS[0]= 11712.000;
    GSIP->CSIP[ 68].GPOS[1]=  8987.350;
    GSIP->CSIP[ 68].GPOS[2]=  0.000000;
    GSIP->CSIP[ 69].GPOS[0]=-13760.000;
    GSIP->CSIP[ 69].GPOS[1]=-13083.350;
    GSIP->CSIP[ 69].GPOS[2]=  0.000000;
    GSIP->CSIP[ 70].GPOS[0]=- 7392.000;
    GSIP->CSIP[ 70].GPOS[1]= 13462.350;
    GSIP->CSIP[ 70].GPOS[2]=  0.000000;
    GSIP->CSIP[ 71].GPOS[0]=  5344.000;
    GSIP->CSIP[ 71].GPOS[1]=-17558.350;
    GSIP->CSIP[ 71].GPOS[2]=  0.000000;
    GSIP->CSIP[ 72].GPOS[0]=- 5269.300;
    GSIP->CSIP[ 72].GPOS[1]= 13462.350;
    GSIP->CSIP[ 72].GPOS[2]=  0.000000;
    GSIP->CSIP[ 73].GPOS[0]=  3221.300;
    GSIP->CSIP[ 73].GPOS[1]=-17558.350;
    GSIP->CSIP[ 73].GPOS[2]=  0.000000;
    GSIP->CSIP[ 74].GPOS[0]=- 3146.700;
    GSIP->CSIP[ 74].GPOS[1]= 13462.350;
    GSIP->CSIP[ 74].GPOS[2]=  0.000000;
    GSIP->CSIP[ 75].GPOS[0]=  1098.700;
    GSIP->CSIP[ 75].GPOS[1]=-17558.350;
    GSIP->CSIP[ 75].GPOS[2]=  0.000000;
    GSIP->CSIP[ 76].GPOS[0]=- 1024.000;
    GSIP->CSIP[ 76].GPOS[1]= 13462.350;
    GSIP->CSIP[ 76].GPOS[2]=  0.000000;
    GSIP->CSIP[ 77].GPOS[0]=- 1024.000;
    GSIP->CSIP[ 77].GPOS[1]=-17558.350;
    GSIP->CSIP[ 77].GPOS[2]=  0.000000;
    GSIP->CSIP[ 78].GPOS[0]=  1098.700;
    GSIP->CSIP[ 78].GPOS[1]= 13462.350;
    GSIP->CSIP[ 78].GPOS[2]=  0.000000;
    GSIP->CSIP[ 79].GPOS[0]=- 3146.700;
    GSIP->CSIP[ 79].GPOS[1]=-17558.350;
    GSIP->CSIP[ 79].GPOS[2]=  0.000000;
    GSIP->CSIP[ 80].GPOS[0]=  3221.300;
    GSIP->CSIP[ 80].GPOS[1]= 13462.350;
    GSIP->CSIP[ 80].GPOS[2]=  0.000000;
    GSIP->CSIP[ 81].GPOS[0]=- 5269.300;
    GSIP->CSIP[ 81].GPOS[1]=-17558.350;
    GSIP->CSIP[ 81].GPOS[2]=  0.000000;
    GSIP->CSIP[ 82].GPOS[0]=  5344.000;
    GSIP->CSIP[ 82].GPOS[1]= 13462.350;
    GSIP->CSIP[ 82].GPOS[2]=  0.000000;
    GSIP->CSIP[ 83].GPOS[0]=- 7392.000;
    GSIP->CSIP[ 83].GPOS[1]=-17558.350;
    GSIP->CSIP[ 83].GPOS[2]=  0.000000;
    GSIP->CSIP[ 84].GPOS[0]=  9589.300;
    GSIP->CSIP[ 84].GPOS[1]=- 4437.650;
    GSIP->CSIP[ 84].GPOS[2]=  0.000000;
    GSIP->CSIP[ 85].GPOS[0]=-11637.300;
    GSIP->CSIP[ 85].GPOS[1]=   341.650;
    GSIP->CSIP[ 85].GPOS[2]=  0.000000;
    GSIP->CSIP[ 86].GPOS[0]= 11712.000;
    GSIP->CSIP[ 86].GPOS[1]=- 4437.650;
    GSIP->CSIP[ 86].GPOS[2]=  0.000000;
    GSIP->CSIP[ 87].GPOS[0]=-13760.000;
    GSIP->CSIP[ 87].GPOS[1]=   341.650;
    GSIP->CSIP[ 87].GPOS[2]=  0.000000;
    GSIP->CSIP[ 88].GPOS[0]= 13834.700;
    GSIP->CSIP[ 88].GPOS[1]=- 4437.650;
    GSIP->CSIP[ 88].GPOS[2]=  0.000000;
    GSIP->CSIP[ 89].GPOS[0]=-15882.700;
    GSIP->CSIP[ 89].GPOS[1]=   341.650;
    GSIP->CSIP[ 89].GPOS[2]=  0.000000;
    GSIP->CSIP[ 90].GPOS[0]=  9589.300;
    GSIP->CSIP[ 90].GPOS[1]=- 8912.650;
    GSIP->CSIP[ 90].GPOS[2]=  0.000000;
    GSIP->CSIP[ 91].GPOS[0]=-11637.300;
    GSIP->CSIP[ 91].GPOS[1]=  4816.650;
    GSIP->CSIP[ 91].GPOS[2]=  0.000000;
    GSIP->CSIP[ 92].GPOS[0]= 11712.000;
    GSIP->CSIP[ 92].GPOS[1]=- 8912.650;
    GSIP->CSIP[ 92].GPOS[2]=  0.000000;
    GSIP->CSIP[ 93].GPOS[0]=-13760.000;
    GSIP->CSIP[ 93].GPOS[1]=  4816.650;
    GSIP->CSIP[ 93].GPOS[2]=  0.000000;
    GSIP->CSIP[ 94].GPOS[0]= 13834.700;
    GSIP->CSIP[ 94].GPOS[1]=- 8912.650;
    GSIP->CSIP[ 94].GPOS[2]=  0.000000;
    GSIP->CSIP[ 95].GPOS[0]=-15882.700;
    GSIP->CSIP[ 95].GPOS[1]=  4816.650;
    GSIP->CSIP[ 95].GPOS[2]=  0.000000;
    GSIP->CSIP[ 96].GPOS[0]=  9589.300;
    GSIP->CSIP[ 96].GPOS[1]=-13387.650;
    GSIP->CSIP[ 96].GPOS[2]=  0.000000;
    GSIP->CSIP[ 97].GPOS[0]=-11637.300;
    GSIP->CSIP[ 97].GPOS[1]=  9291.650;
    GSIP->CSIP[ 97].GPOS[2]=  0.000000;
    GSIP->CSIP[ 98].GPOS[0]= 11712.000;
    GSIP->CSIP[ 98].GPOS[1]=-13387.650;
    GSIP->CSIP[ 98].GPOS[2]=  0.000000;
    GSIP->CSIP[ 99].GPOS[0]=-13760.000;
    GSIP->CSIP[ 99].GPOS[1]=  9291.650;
    GSIP->CSIP[ 99].GPOS[2]=  0.000000;
}
void F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_SCfromFile(char *filename,CL_GSIP* GSIP){
    int i,j;
    double etc;
    ifstream in;
    in.open(filename);
    
    if(!in){
        cout << filename << " can not be open." << endl;
        cout << "Using default values." << endl;
        F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_SC(GSIP);
    }else{
    
        in >> etc;
        in >> etc;
        in >> etc;
        in >> GSIP->SIP_ORDER;
        in >> GSIP->SIP_P_ORDER;
        in >> etc;
        in >> etc;
        in >> etc;
        in >> etc;
        in >> etc;
        in >> GSIP->CRPIX[0];
        in >> GSIP->CRPIX[1];
        in >> GSIP->CRVAL[0];
        in >> GSIP->CRVAL[1];
        in >> GSIP->CD[0][0];
        in >> GSIP->CD[0][1];
        in >> GSIP->CD[1][0];
        in >> GSIP->CD[1][1];

        for(i=0;i< 2;i++)
        for(j=0;j<21;j++)
        in >> GSIP->SIP_AB[i][j];
        for(i=0;i< 2;i++)
        for(j=0;j<21;j++)
        in >> GSIP->SIP_ABP[i][j];
    }
}
void F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_SC(CL_GSIP* GSIP){
    GSIP->CD[0][0]=-5.6*pow(10,-5);
    GSIP->CD[0][1]= 0.0;
    GSIP->CD[1][0]= 0.0;
    GSIP->CD[1][1]= 5.6*pow(10,-5);

    GSIP->SIP_AB[0][ 0]= 0.00000;
    GSIP->SIP_AB[0][ 1]= 0.00000;
    GSIP->SIP_AB[0][ 2]=-1.00000*pow(10,- 7);
    GSIP->SIP_AB[0][ 3]= 1.25000*pow(10,-11);
    GSIP->SIP_AB[0][ 4]=-1.00000*pow(10,-15);
    GSIP->SIP_AB[0][ 5]=-5.00000*pow(10,-19);
    GSIP->SIP_AB[0][ 6]= 0.00000;
    GSIP->SIP_AB[0][ 7]=-3.50000*pow(10,- 7);
    GSIP->SIP_AB[0][ 8]=-5.00000*pow(10,-10);
    GSIP->SIP_AB[0][ 9]= 4.00000*pow(10,-15);
    GSIP->SIP_AB[0][10]= 2.50000*pow(10,-18);
    GSIP->SIP_AB[0][11]=-3.50000*pow(10,- 7);
    GSIP->SIP_AB[0][12]= 8.75000*pow(10,-12);
    GSIP->SIP_AB[0][13]= 2.75000*pow(10,-15);
    GSIP->SIP_AB[0][14]=-7.75000*pow(10,-20);
    GSIP->SIP_AB[0][15]=-5.00000*pow(10,-10);
    GSIP->SIP_AB[0][16]= 2.50000*pow(10,-15);
    GSIP->SIP_AB[0][17]= 4.50000*pow(10,-18);
    GSIP->SIP_AB[0][18]= 2.50000*pow(10,-15);
    GSIP->SIP_AB[0][19]=-1.25000*pow(10,-19);
    GSIP->SIP_AB[0][20]= 2.50000*pow(10,-18);

    GSIP->SIP_AB[1][ 0]= 0.00000;
    GSIP->SIP_AB[1][ 1]= 0.00000;
    GSIP->SIP_AB[1][ 2]=-5.25000*pow(10,- 7);
    GSIP->SIP_AB[1][ 3]=-5.00000*pow(10,-10);
    GSIP->SIP_AB[1][ 4]= 4.75000*pow(10,-15);
    GSIP->SIP_AB[1][ 5]= 2.50000*pow(10,-18);
    GSIP->SIP_AB[1][ 6]= 0.00000;
    GSIP->SIP_AB[1][ 7]=-2.50000*pow(10,- 7);
    GSIP->SIP_AB[1][ 8]=-1.25000*pow(10,-11);
    GSIP->SIP_AB[1][ 9]= 2.50000*pow(10,-15);
    GSIP->SIP_AB[1][10]= 5.00000*pow(10,-19);
    GSIP->SIP_AB[1][11]=-1.50000*pow(10,- 7);
    GSIP->SIP_AB[1][12]=-5.00000*pow(10,-10);
    GSIP->SIP_AB[1][13]= 3.25000*pow(10,-15);
    GSIP->SIP_AB[1][14]= 4.00000*pow(10,-18);
    GSIP->SIP_AB[1][15]= 3.75000*pow(10,-12);
    GSIP->SIP_AB[1][16]= 2.50000*pow(10,-15);
    GSIP->SIP_AB[1][17]= 3.75000*pow(10,-19);
    GSIP->SIP_AB[1][18]= 1.25000*pow(10,-16);
    GSIP->SIP_AB[1][19]= 2.50000*pow(10,-18);
    GSIP->SIP_AB[1][20]=-1.00000*pow(10,-19);

    GSIP->SIP_ABP[0][ 0]= 0.00000;
    GSIP->SIP_ABP[0][ 1]= 3.75000*pow(10,- 8);
    GSIP->SIP_ABP[0][ 2]= 9.50000*pow(10,- 8);
    GSIP->SIP_ABP[0][ 3]=-1.25000*pow(10,-11);
    GSIP->SIP_ABP[0][ 4]= 1.25000*pow(10,-15);
    GSIP->SIP_ABP[0][ 5]= 5.50000*pow(10,-19);
    GSIP->SIP_ABP[0][ 6]=-4.00000*pow(10,- 5);
    GSIP->SIP_ABP[0][ 7]= 3.75000*pow(10,- 7);
    GSIP->SIP_ABP[0][ 8]= 5.00000*pow(10,-10);
    GSIP->SIP_ABP[0][ 9]=-3.50000*pow(10,-15);
    GSIP->SIP_ABP[0][10]=-2.25000*pow(10,-18);
    GSIP->SIP_ABP[0][11]= 3.75000*pow(10,- 7);
    GSIP->SIP_ABP[0][12]=-8.50000*pow(10,-12);
    GSIP->SIP_ABP[0][13]=-2.25000*pow(10,-15);
    GSIP->SIP_ABP[0][14]= 6.00000*pow(10,-20);
    GSIP->SIP_ABP[0][15]= 5.00000*pow(10,-10);
    GSIP->SIP_ABP[0][16]=-2.00000*pow(10,-15);
    GSIP->SIP_ABP[0][17]=-4.00000*pow(10,-18);
    GSIP->SIP_ABP[0][18]=-2.25000*pow(10,-15);
    GSIP->SIP_ABP[0][19]= 1.25000*pow(10,-19);
    GSIP->SIP_ABP[0][20]=-2.00000*pow(10,-18);

    GSIP->SIP_ABP[1][ 0]= 0.00000;
    GSIP->SIP_ABP[1][ 1]=-2.50000*pow(10,- 5);
    GSIP->SIP_ABP[1][ 2]= 5.50000*pow(10,- 7);
    GSIP->SIP_ABP[1][ 3]= 5.00000*pow(10,-10);
    GSIP->SIP_ABP[1][ 4]=-4.00000*pow(10,-15);
    GSIP->SIP_ABP[1][ 5]=-2.25000*pow(10,-18);
    GSIP->SIP_ABP[1][ 6]=-1.25000*pow(10,- 6);
    GSIP->SIP_ABP[1][ 7]= 2.50000*pow(10,- 7);
    GSIP->SIP_ABP[1][ 8]= 1.50000*pow(10,-11);
    GSIP->SIP_ABP[1][ 9]=-2.00000*pow(10,-15);
    GSIP->SIP_ABP[1][10]=-5.50000*pow(10,-19);
    GSIP->SIP_ABP[1][11]= 1.25000*pow(10,- 7);
    GSIP->SIP_ABP[1][12]= 5.00000*pow(10,-10);
    GSIP->SIP_ABP[1][13]=-2.50000*pow(10,-15);
    GSIP->SIP_ABP[1][14]=-3.25000*pow(10,-18);
    GSIP->SIP_ABP[1][15]=-3.50000*pow(10,-12);
    GSIP->SIP_ABP[1][16]=-2.25000*pow(10,-15);
    GSIP->SIP_ABP[1][17]=-4.00000*pow(10,-19);
    GSIP->SIP_ABP[1][18]= 3.00000*pow(10,-17);
    GSIP->SIP_ABP[1][19]=-2.25000*pow(10,-18);
    GSIP->SIP_ABP[1][20]=-1.00000*pow(10,-19);
}
void F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_HSCfromFile(char *filename,CL_GSIP* GSIP){
    int i,j;
    double etc;
    ifstream in;
    in.open(filename);
    
    if(!in){
        cout << filename << " can not be open." << endl;
        cout << "Using default values." << endl;
        F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_HSC(GSIP);
    }else{
    
        in >> etc;
        in >> etc;
        in >> etc;
        in >> GSIP->SIP_ORDER;
        in >> GSIP->SIP_P_ORDER;
        in >> etc;
        in >> etc;
        in >> etc;
        in >> etc;
        in >> etc;
        in >> GSIP->CRPIX[0];
        in >> GSIP->CRPIX[1];
        in >> GSIP->CRVAL[0];
        in >> GSIP->CRVAL[1];
        in >> GSIP->CD[0][0];
        in >> GSIP->CD[0][1];
        in >> GSIP->CD[1][0];
        in >> GSIP->CD[1][1];

        for(i=0;i< 2;i++)
        for(j=0;j<55;j++)
        in >> GSIP->SIP_AB[i][j];
        for(i=0;i< 2;i++)
        for(j=0;j<55;j++)
        in >> GSIP->SIP_ABP[i][j];
    }
}
void F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_HSC(CL_GSIP* GSIP){
    GSIP->CD[0][0]=-4.7*pow(10,-5);
    GSIP->CD[0][1]= 0.0;
    GSIP->CD[1][0]= 0.0;
    GSIP->CD[1][1]= 4.7*pow(10,-5);
    
    GSIP->SIP_AB[0][0]  =  0.000000;
    GSIP->SIP_AB[0][1]  = -1.750000e-10;
    GSIP->SIP_AB[0][2]  =  2.500000e-14;
    GSIP->SIP_AB[0][3]  = -1.250000e-17;
    GSIP->SIP_AB[0][4]  = -3.000000e-22;
    GSIP->SIP_AB[0][5]  =  1.000000e-25;
    GSIP->SIP_AB[0][6]  =  1.500000e-30;
    GSIP->SIP_AB[0][7]  = -3.750000e-34;
    GSIP->SIP_AB[0][8]  = -3.500000e-39;
    GSIP->SIP_AB[0][9]  =  7.500000e-43;
    GSIP->SIP_AB[0][10] =  0.0000000;
    GSIP->SIP_AB[0][11] =  8.000000e-11;
    GSIP->SIP_AB[0][12] = -1.000000e-10;
    GSIP->SIP_AB[0][13] =  7.000000e-20;
    GSIP->SIP_AB[0][14] = -6.250000e-21;
    GSIP->SIP_AB[0][15] =  1.250000e-27;
    GSIP->SIP_AB[0][16] = -1.000000e-28;
    GSIP->SIP_AB[0][17] = -1.750000e-36;
    GSIP->SIP_AB[0][18] =  1.000000e-37;
    GSIP->SIP_AB[0][19] =  2.000000e-12;
    GSIP->SIP_AB[0][20] =  8.750000e-17;
    GSIP->SIP_AB[0][21] = -1.500000e-21;
    GSIP->SIP_AB[0][22] =  8.000000e-25;
    GSIP->SIP_AB[0][23] =  1.000000e-29;
    GSIP->SIP_AB[0][24] = -5.000000e-33;
    GSIP->SIP_AB[0][25] =  1.250000e-38;
    GSIP->SIP_AB[0][26] = -3.750000e-42;
    GSIP->SIP_AB[0][27] = -1.000000e-10;
    GSIP->SIP_AB[0][28] = -4.000000e-20;
    GSIP->SIP_AB[0][29] = -1.250000e-20;
    GSIP->SIP_AB[0][30] =  4.250000e-27;
    GSIP->SIP_AB[0][31] = -3.500000e-28;
    GSIP->SIP_AB[0][32] = -9.750000e-36;
    GSIP->SIP_AB[0][33] =  4.000000e-37;
    GSIP->SIP_AB[0][34] = -4.500000e-20;
    GSIP->SIP_AB[0][35] = -3.000000e-24;
    GSIP->SIP_AB[0][36] =  1.500000e-29;
    GSIP->SIP_AB[0][37] = -4.750000e-33;
    GSIP->SIP_AB[0][38] = -1.500000e-37;
    GSIP->SIP_AB[0][39] =  7.000000e-41;
    GSIP->SIP_AB[0][40] = -7.000000e-21;
    GSIP->SIP_AB[0][41] =  2.000000e-27;
    GSIP->SIP_AB[0][42] = -3.500000e-28;
    GSIP->SIP_AB[0][43] = -1.000000e-35;
    GSIP->SIP_AB[0][44] =  6.000000e-37;
    GSIP->SIP_AB[0][45] =  3.000000e-28;
    GSIP->SIP_AB[0][46] =  2.750000e-32;
    GSIP->SIP_AB[0][47] =  2.750000e-38;
    GSIP->SIP_AB[0][48] = -4.500000e-41;
    GSIP->SIP_AB[0][49] = -1.000000e-28;
    GSIP->SIP_AB[0][50] = -3.750000e-36;
    GSIP->SIP_AB[0][51] =  4.000000e-37;
    GSIP->SIP_AB[0][52] = -5.500000e-37;
    GSIP->SIP_AB[0][53] = -6.000000e-41;
    GSIP->SIP_AB[0][54] =  9.500000e-38;

    GSIP->SIP_AB[1][0]  =  0.000000;
    GSIP->SIP_AB[1][1]  =  0.000000;
    GSIP->SIP_AB[1][2]  = -7.750000e-11;
    GSIP->SIP_AB[1][3]  = -1.000000e-10;
    GSIP->SIP_AB[1][4]  =  3.500000e-19;
    GSIP->SIP_AB[1][5]  = -7.000000e-21;
    GSIP->SIP_AB[1][6]  = -4.500000e-29;
    GSIP->SIP_AB[1][7]  = -1.000000e-28;
    GSIP->SIP_AB[1][8]  =  2.750000e-37;
    GSIP->SIP_AB[1][9]  =  9.500000e-38;
    GSIP->SIP_AB[1][10] =  7.500000e-10;
    GSIP->SIP_AB[1][11] = -4.250000e-15;
    GSIP->SIP_AB[1][12] = -1.000000e-17;
    GSIP->SIP_AB[1][13] =  3.000000e-23;
    GSIP->SIP_AB[1][14] =  8.000000e-28;
    GSIP->SIP_AB[1][15] =  3.000000e-32;
    GSIP->SIP_AB[1][16] =  8.750000e-35;
    GSIP->SIP_AB[1][17] = -3.000000e-40;
    GSIP->SIP_AB[1][18] =  4.000000e-44;
    GSIP->SIP_AB[1][19] = -1.500000e-10;
    GSIP->SIP_AB[1][20] = -1.000000e-10;
    GSIP->SIP_AB[1][21] =  4.750000e-19;
    GSIP->SIP_AB[1][22] = -1.250000e-20;
    GSIP->SIP_AB[1][23] = -1.000000e-27;
    GSIP->SIP_AB[1][24] = -3.500000e-28;
    GSIP->SIP_AB[1][25] =  3.750000e-36;
    GSIP->SIP_AB[1][26] =  4.000000e-37;
    GSIP->SIP_AB[1][27] = -4.500000e-17;
    GSIP->SIP_AB[1][28] =  1.000000e-22;
    GSIP->SIP_AB[1][29] =  6.500000e-25;
    GSIP->SIP_AB[1][30] = -1.250000e-30;
    GSIP->SIP_AB[1][31] = -6.000000e-34;
    GSIP->SIP_AB[1][32] =  2.000000e-39;
    GSIP->SIP_AB[1][33] = -2.500000e-42;
    GSIP->SIP_AB[1][34] =  3.500000e-20;
    GSIP->SIP_AB[1][35] = -6.250000e-21;
    GSIP->SIP_AB[1][36] = -9.000000e-28;
    GSIP->SIP_AB[1][37] = -3.500000e-28;
    GSIP->SIP_AB[1][38] =  4.000000e-36;
    GSIP->SIP_AB[1][39] =  6.000000e-37;
    GSIP->SIP_AB[1][40] =  6.500000e-25;
    GSIP->SIP_AB[1][41] = -8.000000e-32;
    GSIP->SIP_AB[1][42] = -7.750000e-33;
    GSIP->SIP_AB[1][43] =  5.500000e-39;
    GSIP->SIP_AB[1][44] =  8.750000e-42;
    GSIP->SIP_AB[1][45] =  7.500000e-29;
    GSIP->SIP_AB[1][46] = -1.000000e-28;
    GSIP->SIP_AB[1][47] =  2.000000e-36;
    GSIP->SIP_AB[1][48] =  4.000000e-37;
    GSIP->SIP_AB[1][49] = -3.250000e-33;
    GSIP->SIP_AB[1][50] = -3.000000e-39;
    GSIP->SIP_AB[1][51] =  2.250000e-41;
    GSIP->SIP_AB[1][52] = -2.750000e-37;
    GSIP->SIP_AB[1][53] =  1.000000e-37;
    GSIP->SIP_AB[1][54] =  5.250000e-42;

    GSIP->SIP_ABP[0][0]  =  0.000000;
    GSIP->SIP_ABP[0][1]  =  4.000000e-10;
    GSIP->SIP_ABP[0][2]  = -3.000000e-14;
    GSIP->SIP_ABP[0][3]  =  1.250000e-17;
    GSIP->SIP_ABP[0][4]  =  3.750000e-22;
    GSIP->SIP_ABP[0][5]  = -1.250000e-25;
    GSIP->SIP_ABP[0][6]  = -1.750000e-30;
    GSIP->SIP_ABP[0][7]  =  4.750000e-34;
    GSIP->SIP_ABP[0][8]  =  4.500000e-39;
    GSIP->SIP_ABP[0][9]  = -1.000000e-42;
    GSIP->SIP_ABP[0][10] =  0.000000;
    GSIP->SIP_ABP[0][11] = -8.250000e-11;
    GSIP->SIP_ABP[0][12] =  1.000000e-10;
    GSIP->SIP_ABP[0][13] = -4.250000e-20;
    GSIP->SIP_ABP[0][14] =  4.000000e-20;
    GSIP->SIP_ABP[0][15] = -1.500000e-27;
    GSIP->SIP_ABP[0][16] =  1.250000e-28;
    GSIP->SIP_ABP[0][17] =  1.500000e-36;
    GSIP->SIP_ABP[0][18] =  3.500000e-38;
    GSIP->SIP_ABP[0][19] = -2.250000e-12;
    GSIP->SIP_ABP[0][20] = -1.250000e-16;
    GSIP->SIP_ABP[0][21] =  1.750000e-21;
    GSIP->SIP_ABP[0][22] = -7.500000e-25;
    GSIP->SIP_ABP[0][23] = -1.500000e-29;
    GSIP->SIP_ABP[0][24] =  6.500000e-33;
    GSIP->SIP_ABP[0][25] = -1.250000e-38;
    GSIP->SIP_ABP[0][26] =  4.000000e-42;
    GSIP->SIP_ABP[0][27] =  1.000000e-10;
    GSIP->SIP_ABP[0][28] =  8.750000e-20;
    GSIP->SIP_ABP[0][29] =  8.250000e-20;
    GSIP->SIP_ABP[0][30] = -5.500000e-27;
    GSIP->SIP_ABP[0][31] =  3.750000e-28;
    GSIP->SIP_ABP[0][32] =  1.000000e-35;
    GSIP->SIP_ABP[0][33] =  1.250000e-37;
    GSIP->SIP_ABP[0][34] =  5.250000e-20;
    GSIP->SIP_ABP[0][35] =  4.500000e-24;
    GSIP->SIP_ABP[0][36] = -9.000000e-30;
    GSIP->SIP_ABP[0][37] =  6.750000e-34;
    GSIP->SIP_ABP[0][38] =  2.000000e-37;
    GSIP->SIP_ABP[0][39] = -9.500000e-41;
    GSIP->SIP_ABP[0][40] =  4.250000e-20;
    GSIP->SIP_ABP[0][41] = -2.750000e-27;
    GSIP->SIP_ABP[0][42] =  3.750000e-28;
    GSIP->SIP_ABP[0][43] =  1.250000e-35;
    GSIP->SIP_ABP[0][44] =  2.000000e-37;
    GSIP->SIP_ABP[0][45] = -3.500000e-28;
    GSIP->SIP_ABP[0][46] = -4.250000e-32;
    GSIP->SIP_ABP[0][47] = -9.000000e-38;
    GSIP->SIP_ABP[0][48] =  8.500000e-41;
    GSIP->SIP_ABP[0][49] =  1.250000e-28;
    GSIP->SIP_ABP[0][50] =  4.250000e-36;
    GSIP->SIP_ABP[0][51] =  1.250000e-37;
    GSIP->SIP_ABP[0][52] =  7.000000e-37;
    GSIP->SIP_ABP[0][53] =  9.500000e-41;
    GSIP->SIP_ABP[0][54] =  4.750000e-38;

    GSIP->SIP_ABP[1][0]  =  0.000000;
    GSIP->SIP_ABP[1][1]  =  0.000000;
    GSIP->SIP_ABP[1][2]  =  8.000000e-11;
    GSIP->SIP_ABP[1][3]  =  1.000000e-10;
    GSIP->SIP_ABP[1][4]  = -3.500000e-19;
    GSIP->SIP_ABP[1][5]  =  4.250000e-20;
    GSIP->SIP_ABP[1][6]  =  1.750000e-28;
    GSIP->SIP_ABP[1][7]  =  1.250000e-28;
    GSIP->SIP_ABP[1][8]  = -1.500000e-36;
    GSIP->SIP_ABP[1][9]  =  4.750000e-38;
    GSIP->SIP_ABP[1][10] = -8.500000e-10;
    GSIP->SIP_ABP[1][11] =  4.500000e-15;
    GSIP->SIP_ABP[1][12] =  1.500000e-17;
    GSIP->SIP_ABP[1][13] = -3.750000e-23;
    GSIP->SIP_ABP[1][14] = -2.000000e-26;
    GSIP->SIP_ABP[1][15] =  4.500000e-32;
    GSIP->SIP_ABP[1][16] = -9.500000e-35;
    GSIP->SIP_ABP[1][17] =  2.000000e-40;
    GSIP->SIP_ABP[1][18] = -3.250000e-44;
    GSIP->SIP_ABP[1][19] =  1.500000e-10;
    GSIP->SIP_ABP[1][20] =  1.000000e-10;
    GSIP->SIP_ABP[1][21] = -4.500000e-19;
    GSIP->SIP_ABP[1][22] =  8.250000e-20;
    GSIP->SIP_ABP[1][23] =  1.500000e-27;
    GSIP->SIP_ABP[1][24] =  3.750000e-28;
    GSIP->SIP_ABP[1][25] = -8.000000e-36;
    GSIP->SIP_ABP[1][26] =  1.250000e-37;
    GSIP->SIP_ABP[1][27] =  5.000000e-17;
    GSIP->SIP_ABP[1][28] = -2.250000e-22;
    GSIP->SIP_ABP[1][29] = -8.750000e-25;
    GSIP->SIP_ABP[1][30] =  1.250000e-30;
    GSIP->SIP_ABP[1][31] =  1.500000e-33;
    GSIP->SIP_ABP[1][32] = -2.500000e-39;
    GSIP->SIP_ABP[1][33] =  2.500000e-42;
    GSIP->SIP_ABP[1][34] =  1.250000e-20;
    GSIP->SIP_ABP[1][35] =  4.000000e-20;
    GSIP->SIP_ABP[1][36] =  1.250000e-27;
    GSIP->SIP_ABP[1][37] =  3.750000e-28;
    GSIP->SIP_ABP[1][38] = -8.000000e-36;
    GSIP->SIP_ABP[1][39] =  2.000000e-37;
    GSIP->SIP_ABP[1][40] = -7.500000e-25;
    GSIP->SIP_ABP[1][41] =  2.500000e-30;
    GSIP->SIP_ABP[1][42] =  1.000000e-32;
    GSIP->SIP_ABP[1][43] = -5.000000e-39;
    GSIP->SIP_ABP[1][44] = -1.500000e-41;
    GSIP->SIP_ABP[1][45] = -1.000000e-28;
    GSIP->SIP_ABP[1][46] =  1.250000e-28;
    GSIP->SIP_ABP[1][47] = -3.250000e-36;
    GSIP->SIP_ABP[1][48] =  1.250000e-37;
    GSIP->SIP_ABP[1][49] =  4.000000e-33;
    GSIP->SIP_ABP[1][50] = -8.750000e-39;
    GSIP->SIP_ABP[1][51] = -3.000000e-41;
    GSIP->SIP_ABP[1][52] =  4.750000e-37;
    GSIP->SIP_ABP[1][53] =  3.500000e-38;
    GSIP->SIP_ABP[1][54] = -7.000000e-42;
}
void F_WCSA_SIMULATION_MAKE_REFERENCESwithRANDOMNOISE(int RANNUM,int REFNUM, double NSCALE,CL_GSIP* GSIP){
    int NUM,CID;
    long TREFNUM;
    double RX[2],RANDSET[REFNUM*104*2];
    CL_PAIR PAIR;
    srand(RANNUM);
    ofstream fout;

    fout.open("SIMULATION.data");
    F_GaussUnit(RANNUM,REFNUM*GSIP->CCDNUM*2,RANDSET);

//    GSIP->InvCD[0][0]= GSIP->CD[1][1]/(GSIP->CD[0][0]*GSIP->CD[1][1]-GSIP->CD[1][0]*GSIP->CD[0][1]);
  //  GSIP->InvCD[0][1]=-GSIP->CD[0][1]/(GSIP->CD[0][0]*GSIP->CD[1][1]-GSIP->CD[1][0]*GSIP->CD[0][1]);
    //GSIP->InvCD[1][0]=-GSIP->CD[1][0]/(GSIP->CD[0][0]*GSIP->CD[1][1]-GSIP->CD[1][0]*GSIP->CD[0][1]);
    //GSIP->InvCD[1][1]= GSIP->CD[0][0]/(GSIP->CD[0][0]*GSIP->CD[1][1]-GSIP->CD[1][0]*GSIP->CD[0][1]);
    GSIP->CRPIX[0]=0.0;
    GSIP->CRPIX[1]=0.0;
    GSIP->CRVAL[0]=0.0;
    GSIP->CRVAL[1]=0.0;

    TREFNUM=0;
    for(CID=0;CID<GSIP->CCDNUM;CID++)
    for(NUM=0;NUM<REFNUM;NUM++){
        RX[0]=rand()%2048;
        RX[1]=rand()%4096;
        PAIR.ID=TREFNUM;
        PAIR.CHIPID=CID;
        PAIR.X_LOCAL[0]=RX[0];
        PAIR.X_LOCAL[1]=RX[1];
        PAIR.X_GLOBAL[0]=GSIP->CSIP[CID].GPOS[0]+RX[0]*cos(GSIP->CSIP[CID].GPOS[2])-RX[1]*sin(GSIP->CSIP[CID].GPOS[2]);
        PAIR.X_GLOBAL[1]=GSIP->CSIP[CID].GPOS[1]+RX[1]*cos(GSIP->CSIP[CID].GPOS[2])+RX[0]*sin(GSIP->CSIP[CID].GPOS[2]);
        PAIR.X_CRPIX[0]=PAIR.X_GLOBAL[0]-GSIP->CRPIX[0];
        PAIR.X_CRPIX[1]=PAIR.X_GLOBAL[1]-GSIP->CRPIX[1];
        PAIR.X_IM_PIXEL[0]=F_CALCVALUE(GSIP->SIP_ORDER,GSIP->SIP_AB[0],PAIR.X_CRPIX)+PAIR.X_CRPIX[0];
        PAIR.X_IM_PIXEL[1]=F_CALCVALUE(GSIP->SIP_ORDER,GSIP->SIP_AB[1],PAIR.X_CRPIX)+PAIR.X_CRPIX[1];
        PAIR.X_IM_WORLD[0]=GSIP->CD[0][0]*PAIR.X_IM_PIXEL[0]+GSIP->CD[0][1]*PAIR.X_IM_PIXEL[1];
        PAIR.X_IM_WORLD[1]=GSIP->CD[1][0]*PAIR.X_IM_PIXEL[0]+GSIP->CD[1][1]*PAIR.X_IM_PIXEL[1];
        F_InvPROJECTION(PAIR.X_IM_WORLD,PAIR.X_RADEC,GSIP->CRVAL);
        fout << fixed << setprecision(6) << PAIR.ID << "	" << PAIR.CHIPID << "	" << PAIR.X_LOCAL[0]+NSCALE*RANDSET[2*TREFNUM+0] << "	" << PAIR.X_LOCAL[1]+NSCALE*RANDSET[2*TREFNUM+1] << "	" << setw(6) << PAIR.X_RADEC[0] << "	" << setw(6) << PAIR.X_RADEC[1] << endl;
        TREFNUM++;
    }
}
void F_WCSA_SIMULATION_CALC_DIFF_SC(CL_WCSA_ASP* WCSA_ASP ,CL_GSIP* GSIP_SIM){
    int CID;
    int Xmin[2],Xmax[2];

    Xmax[0]=Xmax[1]=-100000;
    Xmin[0]=Xmin[1]= 100000;
    for(CID=0;CID<WCSA_ASP->GSIP->CCDNUM;CID++){
        if(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048>Xmax[0])
        Xmax[0]=(int)(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+2048);
        if(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096>Xmax[1])
        Xmax[1]=(int)(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+4096);
        if(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000<Xmin[0])
        Xmin[0]=(int)(WCSA_ASP->GSIP->CSIP[CID].GPOS[0]+0000);
        if(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000<Xmin[1])
        Xmin[1]=(int)(WCSA_ASP->GSIP->CSIP[CID].GPOS[1]+0000);
    }


    int i,j,ij;
    double dSIP[2][6*6],dSIPD[2][6*6];
    ij=0;
    for(i=0;i<GSIP_SIM->SIP_ORDER+1;i++)
    for(j=0;j<GSIP_SIM->SIP_ORDER+1;j++)
    if(i+j<GSIP_SIM->SIP_ORDER+1){
        dSIP[0][ij] =WCSA_ASP->GSIP->CSIP[10].InvCD[0][0]*WCSA_ASP->GSIP->CSIP[10].SIP_AB[0][ij]+WCSA_ASP->GSIP->CSIP[10].InvCD[0][1]*WCSA_ASP->GSIP->CSIP[10].SIP_AB[1][ij];
        dSIP[1][ij] =WCSA_ASP->GSIP->CSIP[10].InvCD[1][0]*WCSA_ASP->GSIP->CSIP[10].SIP_AB[0][ij]+WCSA_ASP->GSIP->CSIP[10].InvCD[1][1]*WCSA_ASP->GSIP->CSIP[10].SIP_AB[1][ij];
        dSIPD[0][ij]=GSIP_SIM->CD[0][0]*dSIP[0][ij]+GSIP_SIM->CD[0][1]*dSIP[1][ij];
        dSIPD[1][ij]=GSIP_SIM->CD[1][0]*dSIP[0][ij]+GSIP_SIM->CD[1][1]*dSIP[1][ij];
        dSIP[0][ij] =dSIPD[0][ij] - GSIP_SIM->SIP_AB[0][ij];
        dSIP[1][ij] =dSIPD[1][ij] - GSIP_SIM->SIP_AB[1][ij];
        ij++;
    }

    int X[2],NUM[3];
    double Xd[2],DIF[2],*DIFdata[3],DIFMAX[3],STAT[3][2];
    DIFdata[0] = F_NEWdouble1((Xmax[0]-Xmin[0]+1)*(Xmax[1]-Xmin[1]+1));
    DIFdata[1] = F_NEWdouble1((Xmax[0]-Xmin[0]+1)*(Xmax[1]-Xmin[1]+1));
    DIFdata[2] = F_NEWdouble1((Xmax[0]-Xmin[0]+1)*(Xmax[1]-Xmin[1]+1));

    NUM[0]=NUM[1]=NUM[2]=0;
    DIFMAX[0]=DIFMAX[1]=DIFMAX[2]=0;
    for(X[0]=Xmin[0];X[0]<Xmax[0]+1;X[0]++){
    if(X[0]%100==0)
    cout  <<"\r"<<"XLOOP : " << X[0] << " / " << Xmax[0] << flush;
    for(X[1]=Xmin[1];X[1]<Xmax[1]+1;X[1]++){
        Xd[0]=(double)X[0];
        Xd[1]=(double)X[1];
        DIF[0]=F_CALCVALUE(GSIP_SIM->SIP_ORDER,dSIP[0],Xd);
        DIF[1]=F_CALCVALUE(GSIP_SIM->SIP_ORDER,dSIP[1],Xd);     

        DIFdata[0][NUM[0]++]=sqrt(DIF[0]*DIF[0]+DIF[1]*DIF[1]);
        if(DIFMAX[0]<sqrt(DIF[0]*DIF[0]+DIF[1]*DIF[1]))
        DIFMAX[0]=sqrt(DIF[0]*DIF[0]+DIF[1]*DIF[1]);
	if(hypot(X[0],X[1])<WCSA_ASP->APAIR->MAXFRAD){
	    DIFdata[1][NUM[1]++]=sqrt(DIF[0]*DIF[0]+DIF[1]*DIF[1]);
            if(DIFMAX[1]<sqrt(DIF[0]*DIF[0]+DIF[1]*DIF[1]))
            DIFMAX[1]=sqrt(DIF[0]*DIF[0]+DIF[1]*DIF[1]);
	}else{
	    DIFdata[2][NUM[2]++]=sqrt(DIF[0]*DIF[0]+DIF[1]*DIF[1]);
            if(DIFMAX[2]<sqrt(DIF[0]*DIF[0]+DIF[1]*DIF[1]))
            DIFMAX[2]=sqrt(DIF[0]*DIF[0]+DIF[1]*DIF[1]);
	}
    }
    }
    cout << endl;
    
    F_RMS(NUM[0],DIFdata[0],STAT[0]);
    F_RMS(NUM[1],DIFdata[1],STAT[1]);
    F_RMS(NUM[2],DIFdata[2],STAT[2]);
    cout << "AVE : " << STAT[0][0] << "	"<< STAT[1][0] << "	" << STAT[2][0] << endl;
    cout << "SDV : " << STAT[0][1] << "	"<< STAT[1][1] << "	" << STAT[2][1] << endl;
    cout << "MAX : " << DIFMAX[0] << "	"<< DIFMAX[1] << "	" << DIFMAX[2] << endl;
//-----
    cout << scientific;
    cout << WCSA_ASP->GSIP->CSIP[0].GPOS[0] << "	" << GSIP_SIM->CSIP[0].GPOS[0] << endl;
    cout << WCSA_ASP->GSIP->CSIP[0].GPOS[1] << "	" << GSIP_SIM->CSIP[0].GPOS[1] << endl;
    cout << WCSA_ASP->GSIP->CSIP[0].GPOS[2] << "	" << GSIP_SIM->CSIP[0].GPOS[2] << endl;
    cout << WCSA_ASP->GSIP->CSIP[1].GPOS[0] << "	" << GSIP_SIM->CSIP[1].GPOS[0] << endl;
    cout << WCSA_ASP->GSIP->CSIP[1].GPOS[1] << "	" << GSIP_SIM->CSIP[1].GPOS[1] << endl;
    cout << WCSA_ASP->GSIP->CSIP[1].GPOS[2] << "	" << GSIP_SIM->CSIP[1].GPOS[2] << endl;
    cout << WCSA_ASP->GSIP->CSIP[2].GPOS[0] << "	" << GSIP_SIM->CSIP[2].GPOS[0] << endl;
    cout << WCSA_ASP->GSIP->CSIP[2].GPOS[1] << "	" << GSIP_SIM->CSIP[2].GPOS[1] << endl;
    cout << WCSA_ASP->GSIP->CSIP[2].GPOS[2] << "	" << GSIP_SIM->CSIP[2].GPOS[2] << endl;
    cout << WCSA_ASP->GSIP->CSIP[3].GPOS[0] << "	" << GSIP_SIM->CSIP[3].GPOS[0] << endl;
    cout << WCSA_ASP->GSIP->CSIP[3].GPOS[1] << "	" << GSIP_SIM->CSIP[3].GPOS[1] << endl;
    cout << WCSA_ASP->GSIP->CSIP[3].GPOS[2] << "	" << GSIP_SIM->CSIP[3].GPOS[2] << endl;
    cout << WCSA_ASP->GSIP->CSIP[4].GPOS[0] << "	" << GSIP_SIM->CSIP[4].GPOS[0] << endl;
    cout << WCSA_ASP->GSIP->CSIP[4].GPOS[1] << "	" << GSIP_SIM->CSIP[4].GPOS[1] << endl;
    cout << WCSA_ASP->GSIP->CSIP[4].GPOS[2] << "	" << GSIP_SIM->CSIP[4].GPOS[2] << endl;
    cout << WCSA_ASP->GSIP->CSIP[5].GPOS[0] << "	" << GSIP_SIM->CSIP[5].GPOS[0] << endl;
    cout << WCSA_ASP->GSIP->CSIP[5].GPOS[1] << "	" << GSIP_SIM->CSIP[5].GPOS[1] << endl;
    cout << WCSA_ASP->GSIP->CSIP[5].GPOS[2] << "	" << GSIP_SIM->CSIP[5].GPOS[2] << endl;
    cout << WCSA_ASP->GSIP->CSIP[6].GPOS[0] << "	" << GSIP_SIM->CSIP[6].GPOS[0] << endl;
    cout << WCSA_ASP->GSIP->CSIP[6].GPOS[1] << "	" << GSIP_SIM->CSIP[6].GPOS[1] << endl;
    cout << WCSA_ASP->GSIP->CSIP[6].GPOS[2] << "	" << GSIP_SIM->CSIP[6].GPOS[2] << endl;
    cout << WCSA_ASP->GSIP->CSIP[7].GPOS[0] << "	" << GSIP_SIM->CSIP[7].GPOS[0] << endl;
    cout << WCSA_ASP->GSIP->CSIP[7].GPOS[1] << "	" << GSIP_SIM->CSIP[7].GPOS[1] << endl;
    cout << WCSA_ASP->GSIP->CSIP[7].GPOS[2] << "	" << GSIP_SIM->CSIP[7].GPOS[2] << endl;
    cout << WCSA_ASP->GSIP->CSIP[8].GPOS[0] << "	" << GSIP_SIM->CSIP[8].GPOS[0] << endl;
    cout << WCSA_ASP->GSIP->CSIP[8].GPOS[1] << "	" << GSIP_SIM->CSIP[8].GPOS[1] << endl;
    cout << WCSA_ASP->GSIP->CSIP[8].GPOS[2] << "	" << GSIP_SIM->CSIP[8].GPOS[2] << endl;
    cout << WCSA_ASP->GSIP->CSIP[9].GPOS[0] << "	" << GSIP_SIM->CSIP[9].GPOS[0] << endl;
    cout << WCSA_ASP->GSIP->CSIP[9].GPOS[1] << "	" << GSIP_SIM->CSIP[9].GPOS[1] << endl;
    cout << WCSA_ASP->GSIP->CSIP[9].GPOS[2] << "	" << GSIP_SIM->CSIP[9].GPOS[2] << endl;
    cout.unsetf(ios::scientific);
//-----
//-----
//-----
    F_DELdouble1(DIFdata[0]);
    F_DELdouble1(DIFdata[1]);
    F_DELdouble1(DIFdata[2]);
}
void F_WCSA_SIMULATION_CALC_DIFF_HSC(CL_WCSA_ASP* WCSA_ASP,CL_GSIP* GSIP_SIM){
}
