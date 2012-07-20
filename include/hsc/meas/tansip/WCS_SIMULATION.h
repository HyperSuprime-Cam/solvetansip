//------------------------------------------------------------
//WCS_SIMULATION.h
//for simulation test
//
//Last modification : 2012/01/25
//------------------------------------------------------------
#ifndef WCS_SIM_H
#define WCS_SIM_H
#include<string>
#include "hsc/meas/tansip/WCS_CSIP.h"
#include "hsc/meas/tansip/WCS_PL_MAIN.h"

void F_WCSA_SIMULATION_MAIN(int, std::string, std::string, double NSCALE, int RANNUM, int REFNUM);//(0:SC,1:HSC),(1:CCDPOS from file),(1:DISTORTION from file)
void F_WCSA_SIMULATION_DIFF(int HARD,std::string CCDPOSfile,std::string DISTfile,std::string CCDoutfile,std::string RESoutfile,CL_WCSA_ASP* WCSA_ASP);
void F_WCSA_SIMULATION_MAIN2(CL_APROP *APROP,CL_GSIP *GSIP, double NSCALE,int RANNUM,int REFNUM);
void F_WCSA_SIMULATION_DIFF2(std::string CCDoutfile,std::string RESoutfile,CL_WCSA_ASP* WCSA_ASP);

void F_WCSA_SIMULATION_INPUT_SIMULATIONBASIS_SC(CL_GSIP*);
void F_WCSA_SIMULATION_INPUT_SIMULATIONBASIS_HSC(CL_GSIP*);
void F_WCSA_SIMULATION_INPUT_CCDPOSITION_SC(CL_GSIP*);
void F_WCSA_SIMULATION_INPUT_CCDPOSITION_SCfromFile(char *,CL_GSIP*);
void F_WCSA_SIMULATION_INPUT_CCDPOSITION_HSC(CL_GSIP*);
void F_WCSA_SIMULATION_INPUT_CCDPOSITION_HSCfromFile(char *,CL_GSIP*);
void F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_SC(CL_GSIP*);
void F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_SCfromFile(char *,CL_GSIP*);
void F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_HSC(CL_GSIP*);
void F_WCSA_SIMULATION_INPUT_CDSIPDISTORTION_HSCfromFile(char *,CL_GSIP*);
void F_WCSA_SIMULATION_MAKE_REFERENCESwithRANDOMNOISE(int RANNUM,int REFNUM, double NSCALE,CL_GSIP*);
void F_WCSA_SIMULATION_MAKE_REFERENCESwithRANDOMNOISE2(int RANNUM,int REFNUM, double NSCALE,CL_GSIP*);
void F_WCSA_SIMULATION_CALC_DIFF_SC  (CL_WCSA_ASP* ,CL_GSIP* ,std::string CCDoutfile,std::string RESoutfile);
void F_WCSA_SIMULATION_CALC_DIFF_HSC (CL_WCSA_ASP* ,CL_GSIP* ,std::string CCDoutfile,std::string RESoutfile);
void F_WCSA_SIMULATION_CALC_DIFF_HSC2(CL_WCSA_ASP* WCSA_ASP,std::string CCDoutfile,std::string RESoutfile);
void F_WCSA_SIMULATION_CALC_DIFF_HSCP(CL_WCSA_ASP* WCSA_ASP,std::string CCDoutfile,std::string RESoutfile);
#endif
