//------------------------------------------------------------
//WCS_CPROP.h
//
//Last modification : 2011/02/22
//------------------------------------------------------------
#ifndef WCS_CPROP_H
#define WCS_CPROP_H
class CL_CPROP{//Chip property
private:
public:
    int ID;
    int NUMREF;
    int PHASE;//for position determination
    double GLOB_POS[3];
};
#endif


