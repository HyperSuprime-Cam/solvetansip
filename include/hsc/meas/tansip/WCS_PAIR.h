//------------------------------------------------------------
//WCS_PAIR.h
//
//Last modification : 2011/02/22
//------------------------------------------------------------
#ifndef WCS_PAIR_H
#define WCS_PAIR_H
class CL_PAIR{
private:
public:
    int ID;
    int CHIPID;
    int FLAG;
    double xL;//Local
    double yL;
    double RA;
    double DEC;
    double xI;//Inter
    double yI;
    double xG;//Global
    double yG;
    double dxLdxI;
    double dxLdyI;
    double dyLdxI;
    double dyLdyI;
    double dxGdxI;
    double dxGdyI;
    double dyGdxI;
    double dyGdyI;
    double xSIP;
    double ySIP;
    double RAfit;
    double DECfit;
    double xErr;
    double yErr;
    double RAErr;
    double DECErr;
};
#endif
