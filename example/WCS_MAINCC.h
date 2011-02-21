//------------------------------------------------------------
//WCS_MAINCC.h
//for program development
//
//Last modification : 2010/09/15
//------------------------------------------------------------
#ifndef WCS_MAINCC_H
#define WCS_MAINCC_H

#include "../include/WCS_APROP.h"
#include "../include/WCS_CPROP.h"
#include "../include/WCS_PAIR.h"
#include "../include/WCS_CSIP.h"

void    F_WCS_SETCC_APROPfromFILE(char *,CL_APROP *);
void    F_WCS_SETCC_CPROPfromFILE(char *,CL_CPROP *);
void    F_WCS_SETCC_PAIRSIZEfromFILE(CL_APROP *,CL_CPROP *,char *);
void    F_WCS_SETCC_PAIRfromFILE (char *,CL_CPROP *,CL_PAIR *);
void    F_WCS_SETCC_CPROPINITSC(CL_CPROP*);
void    F_WCS_SETCC_CPROPINIT2(CL_CPROP*);
void    F_WCS_TANSIP(CL_APROP,CL_CPROP *,CL_PAIR *,CL_CSIP *);
void    F_WCS_TANSIP_GPOS(CL_APROP,CL_CPROP *,CL_PAIR *,CL_CSIP *);
void    F_WSC_WCSCCD(CL_APROP,CL_CPROP *,CL_PAIR *,CL_CSIP *);
void    F_WCS_CHECK(CL_APROP,CL_CPROP*,CL_PAIR*,CL_CSIP*);
void    F_WCS_TEST();

#endif
