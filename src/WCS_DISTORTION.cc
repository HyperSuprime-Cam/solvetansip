//------------------------------------------------------------
//WCS_DISTORTION.cc
//calculating DISTORTION
//
//Last modification : 2011/05/30
//------------------------------------------------------------
#include<vector>
#include "hsc/meas/tansip/WCS_DISTORTION.h"
#include "hsc/meas/tansip/WCS_TANSIP.h"

using namespace std;
namespace afwImage = lsst::afw::image;
double  F_CALCVALUE(int ORDER,double *Coef,double *X);
void    F_InvPROJECTION(double *Pdeg,double *Cdeg,double *PPOINT);
void    F_PROJECTION   (double *Cdeg,double *Pdeg,double *PPOINT);
vector<double> F_WCS_DISTORTION_wcsList_XY(vector<double> CRPIX_V,vector<double> CRVAL_V,vector<double> CD,int A_ORDER,vector<double> SIP_A,int B_ORDER,vector<double> SIP_B,double X,double Y){
    vector<double> MSSR;

/*    cout << "CRPIX : " << CRPIX_V[0] <<" , " << CRPIX_V[1] << endl;
    cout << "CRVAL : " << CRVAL_V[0] <<" , " << CRVAL_V[1] << endl;
    cout << "CD    : " << CD[0] <<" , " << CD[1] << endl;
    cout << "CD    : " << CD[2] <<" , " << CD[3] << endl;
    cout << "XY    : " << X << " , " << Y << endl;
*/
//--------------------------------------------------
    int i;
    double xCRPIX[2],*dSIP[2][2],*SIP[2],dGI[2][2];
    double CAMERA_MAGNIFICATION,CAMERA_SHEAR[2],CAMERA_ROTATION;

    SIP[0] = new double[(A_ORDER+1)*(A_ORDER+1)];
    SIP[1] = new double[(B_ORDER+1)*(B_ORDER+1)];
    dSIP[0][0] = new double[(A_ORDER+1)*(A_ORDER+1)];
    dSIP[1][0] = new double[(B_ORDER+1)*(B_ORDER+1)];
    dSIP[0][1] = new double[(A_ORDER+1)*(A_ORDER+1)];
    dSIP[1][1] = new double[(B_ORDER+1)*(B_ORDER+1)];
    for(i=0;i<(A_ORDER+1)*(A_ORDER+1);i++)
    SIP[0][i]=SIP_A[i];
    for(i=0;i<(B_ORDER+1)*(B_ORDER+1);i++)
    SIP[1][i]=SIP_B[i];

    SIP[0][1*(A_ORDER+1)+0]+=1;
    SIP[1][0*(B_ORDER+1)+1]+=1;

    F_DIFFSIP(A_ORDER,SIP[0],dSIP[0][0],dSIP[0][1]);
    F_DIFFSIP(B_ORDER,SIP[1],dSIP[1][0],dSIP[1][1]);

    xCRPIX[0]=X-CRPIX_V[0];
    xCRPIX[1]=Y-CRPIX_V[1];

    dGI[0][0]=F_CALCVALUE(A_ORDER,dSIP[0][0],xCRPIX);
    dGI[0][1]=F_CALCVALUE(A_ORDER,dSIP[0][1],xCRPIX);
    dGI[1][0]=F_CALCVALUE(B_ORDER,dSIP[1][0],xCRPIX);
    dGI[1][1]=F_CALCVALUE(B_ORDER,dSIP[1][1],xCRPIX);

    CAMERA_MAGNIFICATION=0.5*hypot(dGI[0][0]+dGI[1][1],dGI[1][0]-dGI[0][1]);
    CAMERA_SHEAR[0]     =0.5*(dGI[0][0]-dGI[1][1])/CAMERA_MAGNIFICATION;
    CAMERA_SHEAR[1]     =0.5*(dGI[1][0]+dGI[0][1])/CAMERA_MAGNIFICATION;
    CAMERA_ROTATION     =atan2((dGI[1][0]-dGI[0][1]),(dGI[0][0]+dGI[1][1]));

    MSSR.push_back(CAMERA_MAGNIFICATION);
    MSSR.push_back(CAMERA_SHEAR[0]     );
    MSSR.push_back(CAMERA_SHEAR[1]     );
    MSSR.push_back(CAMERA_ROTATION     );

//--------------------------------------------------
    delete []  SIP[0];
    delete []  SIP[1];
    delete [] dSIP[0][0];
    delete [] dSIP[1][0];
    delete [] dSIP[0][1];
    delete [] dSIP[1][1];
//--------------------------------------------------
    return MSSR;
}
vector<double> F_WCS_DISTORTION_wcsList_RADEC(vector<double> CRPIX_V,vector<double> CRVAL_V,vector<double> CD,int AP_ORDER,vector<double> SIP_AP,int BP_ORDER,vector<double> SIP_BP,double RA,double DEC){
    vector<double> MSSR;

    int i;
    double xCRVAL[2],xI[2],*dPSIP[2][2],*PSIP[2],RADEC[2],CRVAL[2],InvCD[2][2],dGI[2][2];
    double CAMERA_MAGNIFICATION,CAMERA_SHEAR[2],CAMERA_ROTATION;

    PSIP[0] = new double[(AP_ORDER+1)*(AP_ORDER+1)];
    PSIP[1] = new double[(BP_ORDER+1)*(BP_ORDER+1)];
    dPSIP[0][0] = new double[(AP_ORDER+1)*(AP_ORDER+1)];
    dPSIP[1][0] = new double[(BP_ORDER+1)*(BP_ORDER+1)];
    dPSIP[0][1] = new double[(AP_ORDER+1)*(AP_ORDER+1)];
    dPSIP[1][1] = new double[(BP_ORDER+1)*(BP_ORDER+1)];

    for(i=0;i<(AP_ORDER+1)*(AP_ORDER+1);i++)
    PSIP[0][i]=SIP_AP[i];
    for(i=0;i<(BP_ORDER+1)*(BP_ORDER+1);i++)
    PSIP[1][i]=SIP_BP[i];

    PSIP[0][1*(AP_ORDER+1)+0]+=1;
    PSIP[1][0*(BP_ORDER+1)+1]+=1;

    F_DIFFSIP(AP_ORDER,PSIP[0],dPSIP[0][0],dPSIP[0][1]);
    F_DIFFSIP(BP_ORDER,PSIP[1],dPSIP[1][0],dPSIP[1][1]);

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

    dGI[0][0]=F_CALCVALUE(AP_ORDER,dPSIP[0][0],xCRVAL);
    dGI[0][1]=F_CALCVALUE(AP_ORDER,dPSIP[0][1],xCRVAL);
    dGI[1][0]=F_CALCVALUE(BP_ORDER,dPSIP[1][0],xCRVAL);
    dGI[1][1]=F_CALCVALUE(BP_ORDER,dPSIP[1][1],xCRVAL);

    CAMERA_MAGNIFICATION=0.5*hypot(dGI[0][0]+dGI[1][1],dGI[1][0]-dGI[0][1]);
    CAMERA_SHEAR[0]     =0.5*(dGI[0][0]-dGI[1][1])/CAMERA_MAGNIFICATION;
    CAMERA_SHEAR[1]     =0.5*(dGI[1][0]+dGI[0][1])/CAMERA_MAGNIFICATION;
    CAMERA_ROTATION     =atan2((dGI[1][0]-dGI[0][1]),(dGI[0][0]+dGI[1][1]));

    MSSR.push_back(CAMERA_MAGNIFICATION);
    MSSR.push_back(CAMERA_SHEAR[0]     );
    MSSR.push_back(CAMERA_SHEAR[1]     );
    MSSR.push_back(CAMERA_ROTATION     );

//--------------------------------------------------
    delete []  PSIP[0];
    delete []  PSIP[1];
    delete [] dPSIP[0][0];
    delete [] dPSIP[1][0];
    delete [] dPSIP[0][1];
    delete [] dPSIP[1][1];
//--------------------------------------------------
    return MSSR;
}
vector<double> F_WCS_DISTORTION_CSIP_XY(vector<double> CRPIX_V,vector<double> CRVAL_V,vector<double> CD,int AP_ORDER,vector<double> SIP_AP,int BP_ORDER,vector<double> SIP_BP,double RA,double DEC){
    vector<double> MSSR;
    return MSSR;
}
vector<double> F_WCS_DISTORTION_CSIP_RADEC(vector<double> CRPIX_V,vector<double> CRVAL_V,vector<double> CD,int AP_ORDER,vector<double> SIP_AP,int BP_ORDER,vector<double> SIP_BP,double RA,double DEC){
    vector<double> MSSR;
    return MSSR;
}

