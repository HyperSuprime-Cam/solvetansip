%module SLVTANSIP_SWIG
%include "std_string.i"
%include "std_vector.i"

%{
#include"SLVTANSIP_SWIG.h"
%}

%include"SLVTANSIP_SWIG.h"

%template(Vdouble)  std::vector<double>;
%template(VVdouble) std::vector< std::vector<double> >;
