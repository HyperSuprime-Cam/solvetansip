//-----------------------------------------------------------
//WCS_DISTORTION.h
//
//Last modification : 2011/05/30
//------------------------------------------------------------
#include<vector>
#include "lsst/afw/image/TanWcs.h"

using namespace std;
vector<double> F_WCS_DISTORTION_wcsList_XY(vector<double> CRPIX,vector<double> CRVAL,vector<double> CD,int A_ORDER ,vector<double> SIP_A ,int B_ORDER ,vector<double> SIP_B ,double X,double Y);
vector<double> F_WCS_DISTORTION_wcsList_RADEC(vector<double> CRPIX,vector<double> CRVAL,vector<double> CD,int AP_ORDER,vector<double> SIP_AP,int BP_ORDER,vector<double> SIP_BP,double X,double Y);
vector<double> F_WCS_DISTORTION_CSIP_XY(vector<double> CRPIX,vector<double> CRVAL,vector<double> CD,int A_ORDER ,vector<double> SIP_A ,int B_ORDER ,vector<double> SIP_B ,double X,double Y);
vector<double> F_WCS_DISTORTION_CSIP_RADEC(vector<double> CRPIX,vector<double> CRVAL,vector<double> CD,int A_ORDER ,vector<double> SIP_A ,int B_ORDER ,vector<double> SIP_B ,double X,double Y);
