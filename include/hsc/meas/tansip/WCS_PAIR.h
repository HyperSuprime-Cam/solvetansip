//------------------------------------------------------------
//WCS_PAIR.h
//
//Last modification : 2011/04/04
//------------------------------------------------------------
#ifndef WCS_PAIR_H
#define WCS_PAIR_H
class CL_PAIR{
private:
public:
//Input values
    int ID;
    int CHIPID;
    double xL;//Local position(pix)
    double yL;
    double RA;//Celestical position(deg)
    double DEC;
    double xErr;
    double yErr;
    double RAErr;
    double DECErr;
//for calculation
    int FLAG;
    double xG;//Global position(pix)
    double yG;
    double xG_Init;//Global position(pix)
    double yG_Init;
    double xI;//Relative Projected position(deg), having 0 at CRVAL
    double yI;//Intermediate world coodinate
    double xCRPIX;//Relative position from CRpix(pix) in Global coordinate
    double yCRPIX;
    double xCRVAL;//Relative position from CRval(pix) in Global coordinate
    double yCRVAL;//Intermediate pixel coodinate
    double xLCRPIX;//Relative position from CRpix(pix) in Local coordinate
    double yLCRPIX;
    double xLCRVAL;//Relative position from CRval(pix) in Local coordinate
    double yLCRVAL;//Intermediate pixel coodinate
    double dxLdxI;//Diferential value of xL by xCRPIX
    double dxLdyI;
    double dyLdxI;
    double dyLdyI;
    double dxGdxI;//Diferential value of xG by xCRPIX
    double dxGdyI;
    double dyGdxI;
    double dyGdyI;
    double Zxx;//Fitting value of SIP dxGdxI 
    double Zyx;
    double Zxy;
    double Zyy;
//for check
    double GxSIPErr;
    double GySIPErr;
    double GxPSIPErr;
    double GyPSIPErr;
    double GxLErr;//SIP->PSIP
    double GyLErr;//SIP->PSIP
    double GxIErr;//PSIP->SIP
    double GyIErr;//PSIP->SIP
    double LxSIPErr;
    double LySIPErr;
    double LxPSIPErr;
    double LyPSIPErr;
    double LxLErr;//SIP->PSIP
    double LyLErr;//SIP->PSIP
    double LxIErr;//PSIP->SIP
    double LyIErr;//PSIP->SIP
    double CAMERA_MAGNIFICATION;//Magnification by camera, calculated in only CCD determination mode
    double CAMERA_SHEAR[2];//Shear by camera
    double CAMERA_ROTATION;//Rotation by camera
};
#endif
