#! /bin/csh

g++ solvetansip.cc ../src/*.cc -I ../include/hsc/meas/tansip -lm -lcfitsio -openmp -o solvetansip
