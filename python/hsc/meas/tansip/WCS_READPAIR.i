%module  WCS_READPAIR
%{
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include <vector>
#include "hsc/meas/tansip/WCS_READPAIR.h"
%}

%include "std_vector.i"
%include "std_map.i"

%template(DoubleVector) std::vector<double>;

%include "hsc/meas/tansip/WCS_READPAIR.h"
