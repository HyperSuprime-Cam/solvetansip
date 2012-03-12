#!/bin/csh -f

g++ solvetansip_main.cc ../src/WCS_TANSIP.cc ../src/WCS_APROP.cc ../src/WCS_CSIP.cc ../src/WCS_PAIR.cc ../src/WCS_TANSIP_SET.cc ../src/WCS_TANSIP_SUB.cc ../src/LeastSquares.cc ../src/GETKEYVALUE.cc ../src/Statistics.cc -I ../include -lm -o solvetansip_main
./solvetansip_main RREF/SIMULATIONDATA_HSC_15_1.dat 
