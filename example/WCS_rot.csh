#! /bin/csh -f
#----------------------------------------------------------------------------------------------------
#WCS_rot.csh
#for developping WCS-TANSIP proramme
#making reference catalog (with WCS_MAKECPROP.paf)
#calculating Coeficients and outputting checkfiles
#Last Modification : 2010/10/01
#----------------------------------------------------------------------------------------------------

g++ WCS_MAKEMATCHCATALOG.cc ../test/WCS_PROP.cc ../src/GETKEYVALUE.cc -lm -o WCS_MAKEMATCHCATALOG ; ./WCS_MAKEMATCHCATALOG
g++ WCS_MAIN.cc ../src/WCS_TANSIP.cc ../src/WCS_TANSIP_SUB.cc ../src/WCS_TANSIP_GPOS_SUB.cc ../test/WCS_PROP.cc src/GETKEYVALUE.cc ../src/LeastSquares.cc ../src/WCS_WCSCCD.cc ../test/WCS_TESTCHECK.cc -o WCS_MAIN ; ./WCS_MAIN

