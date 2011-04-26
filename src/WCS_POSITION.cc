//------------------------------------------------------------
//WCS_POSITION.cc
//calculating sky or CCD position
//
//Last modification : 2011/04/20
//------------------------------------------------------------
#include<vector>
#include "hsc/meas/tansip/WCS_POSITION.h"

using namespace std;
namespace afwImage = lsst::afw::image;
void F_WCS_POSITION_TEST(){
}
double  F_CALCVALUE(int ORDER,double *Coef,double *X);
void    F_InvPROJECTION(double *Pdeg,double *Cdeg,double *PPOINT);
void    F_PROJECTION   (double *Cdeg,double *Pdeg,double *PPOINT);
vector<double> F_WCS_POSITION_RADECfromXY(vector<double> CRPIX_V,vector<double> CRVAL_V,vector<double> CD,int A_ORDER,vector<double> SIP_A,int B_ORDER,vector<double> SIP_B,double X,double Y){
cout << "---F_WCS_POSITION_RADECfromXY---" << endl;
    vector<double> RADEC_V;

/*    cout << "CRPIX : " << CRPIX_V[0] <<" , " << CRPIX_V[1] << endl;
    cout << "CRVAL : " << CRVAL_V[0] <<" , " << CRVAL_V[1] << endl;
    cout << "CD    : " << CD[0] <<" , " << CD[1] << endl;
    cout << "CD    : " << CD[2] <<" , " << CD[3] << endl;
    cout << "XY    : " << X << " , " << Y << endl;
*/
//--------------------------------------------------
    int i;
    double xCRPIX[2],xCRVAL[2],xI[2],*SIP[2],RADEC[2],CRVAL[2];
    
    SIP[0] = new double[(A_ORDER+1)*(A_ORDER+1)];
    SIP[1] = new double[(B_ORDER+1)*(B_ORDER+1)];
    for(i=0;i<(A_ORDER+1)*(A_ORDER+1);i++){
        SIP[0][i]=SIP_A[i];
        SIP[1][i]=SIP_B[i];
    }
    CRVAL[0]=CRVAL_V[0];
    CRVAL[1]=CRVAL_V[1];

    xCRPIX[0]=X-CRPIX_V[0];
    xCRPIX[1]=Y-CRPIX_V[1];

    xCRVAL[0]=F_CALCVALUE(A_ORDER,SIP[0],xCRPIX)+xCRPIX[0];
    xCRVAL[1]=F_CALCVALUE(B_ORDER,SIP[1],xCRPIX)+xCRPIX[1];

    xI[0]=CD[0]*xCRVAL[0]+CD[1]*xCRVAL[1];
    xI[1]=CD[2]*xCRVAL[0]+CD[3]*xCRVAL[1];

    F_InvPROJECTION(xI,RADEC,CRVAL);

    RADEC_V.push_back(RADEC[0]);
    RADEC_V.push_back(RADEC[1]);

    cout << fixed << endl;
    cout << "XY    : " << X << " , " << Y << endl;
    cout << "RADEC : " << RADEC_V[0] << " , " << RADEC_V[1] << endl;
    cout << endl;

//--------------------------------------------------
    delete [] SIP[0];
    delete [] SIP[1];
//--------------------------------------------------
    return RADEC_V;
}
vector<double> F_WCS_POSITION_XYfromRADEC(vector<double> CRPIX_V,vector<double> CRVAL_V,vector<double> CD,int AP_ORDER,vector<double> SIP_AP,int BP_ORDER,vector<double> SIP_BP,double RA,double DEC){
cout << "---F_WCS_POSITION_XYfromRADEC---" << endl;
    vector<double> XY_V;

    int i;
    double xCRPIX[2],xCRVAL[2],xI[2],*PSIP[2],RADEC[2],CRVAL[2],InvCD[2][2];
    
    PSIP[0] = new double[(AP_ORDER+1)*(AP_ORDER+1)];
    PSIP[1] = new double[(BP_ORDER+1)*(BP_ORDER+1)];
    for(i=0;i<(AP_ORDER+1)*(AP_ORDER+1);i++){
        PSIP[0][i]=SIP_AP[i];
        PSIP[1][i]=SIP_BP[i];
    }

    RADEC[0]=RA;
    RADEC[1]=DEC;
    CRVAL[0]=CRVAL_V[0];
    CRVAL[1]=CRVAL_V[1];

    F_PROJECTION(RADEC,xI,CRVAL);

    InvCD[0][0]= CD[3]/(CD[0]*CD[3]-CD[1]*CD[2]);
    InvCD[0][1]=-CD[1]/(CD[0]*CD[3]-CD[1]*CD[2]);
    InvCD[1][0]=-CD[2]/(CD[0]*CD[3]-CD[1]*CD[2]);
    InvCD[1][1]= CD[0]/(CD[0]*CD[3]-CD[1]*CD[2]);

    xCRVAL[0]=InvCD[0][0]*xI[0]+InvCD[0][1]*xI[1];
    xCRVAL[1]=InvCD[1][0]*xI[0]+InvCD[1][1]*xI[1];

    xCRPIX[0]=F_CALCVALUE(AP_ORDER,PSIP[0],xCRVAL)+xCRVAL[0];
    xCRPIX[1]=F_CALCVALUE(BP_ORDER,PSIP[1],xCRVAL)+xCRVAL[1];

    XY_V.push_back(xCRPIX[0]+CRPIX_V[0]);
    XY_V.push_back(xCRPIX[1]+CRPIX_V[1]);

    cout << fixed << endl;
    cout << "XY    : " << XY_V[0]  << " , " << XY_V[1]  << endl;
    cout << "RADEC : " << RADEC[0] << " , " << RADEC[1] << endl;
    cout << endl;

//--------------------------------------------------
    delete [] PSIP[0];
    delete [] PSIP[1];
//--------------------------------------------------
    return XY_V;
}
