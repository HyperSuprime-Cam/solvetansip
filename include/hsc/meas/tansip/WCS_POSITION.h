//-----------------------------------------------------------
//WCS_POSITION.h
//
//Last modification : 2011/04/20
//------------------------------------------------------------
#include<vector>
#include "lsst/afw/image/TanWcs.h"

using namespace std;
vector<double> F_WCS_POSITION_RADECfromXY(vector<double> CRPIX,vector<double> CRVAL,vector<double> CD,int A_ORDER ,vector<double> SIP_A ,int B_ORDER ,vector<double> SIP_B ,double X,double Y);
vector<double> F_WCS_POSITION_XYfromRADEC(vector<double> CRPIX,vector<double> CRVAL,vector<double> CD,int AP_ORDER,vector<double> SIP_AP,int BP_ORDER,vector<double> SIP_BP,double X,double Y);
