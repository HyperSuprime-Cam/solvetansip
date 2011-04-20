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
    double GLOB_POS_Init[3];
    double GLOB_POS[3];
    int ALIGN;//1 = using for aligning CCD position
    int POSID[2];
//    double REL_T_left;
//    double REL_T_above;
//    double REL_T_under;
//    double REL_T_right;
};
#endif


