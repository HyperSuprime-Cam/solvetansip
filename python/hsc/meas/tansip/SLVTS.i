%feature("autodoc", "1");
%module(package="hsc.meas.tansip")  SLVTS
/**
    In this interface file is defined solvetansip interface
    that's independent of the LSST library.
*/

%{
    #include "hsc/meas/tansip/SLVTS_GET.h"
    #include <stdexcept>
%}

%include <std_vector.i>
%include <std_string.i>

%template(DoubleList)  std::vector<double>;
%template(DoubleListList) std::vector< std::vector<double> >;

%template(IntList) std::vector<int>;

%template(ReferenceMatchList) std::vector<hsc::meas::tansip::ReferenceMatch>;
%template(CCDPositionList   ) std::vector<hsc::meas::tansip::CCDPosition   >;

%include <exception.i>
%exception {
    try {
        $action
    } catch (std::exception& e) {
        SWIG_exception(SWIG_RuntimeError, const_cast<char*>(e.what()));
    }
}

%include "hsc/meas/tansip/APRM.h"
%include "hsc/meas/tansip/CCDPosition.h"
%include "hsc/meas/tansip/ReferenceMatch.h"
%include "hsc/meas/tansip/SLVTS.h"
%include"hsc/meas/tansip/SLVTS_GET.h"
