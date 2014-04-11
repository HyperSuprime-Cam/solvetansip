%module  SLVTS_SWIG
%{
#include<iostream>
#include<fstream>
#include<cstring>
#include"../../include/hsc/meas/tansip/SLVTS.h"
#include"../../include/hsc/meas/tansip/SLVTS_GET.h"
%}

%include "std_vector.i"
%include "std_string.i"

%template(VS)  std::vector<std::string>;
%template(VVS) std::vector< std::vector<std::string> >;
%template(VVVS) std::vector< std::vector< std::vector<std::string> > >;
%template(VSLVTS)  std::vector<CL_SLVTS*>;
std::vector< CL_SLVTS* > SOLVETANSIP(std::vector< std::vector< std::vector< std::string > > > SLVTS_Argvs);
%template(VD)  std::vector<double>;
%template(VVD)  std::vector<std::vector<double> >;
%template(VI)  std::vector<int>;
%template(VLLI)  std::vector<long long int>;

%include"../../include/hsc/meas/tansip/SLVTS_GET.h"

