#!/usr/bin/env python
#------------------------------------------------------------
#WCS_MAIN.py
#main program for wcs in pipeline
#1:set parameter(APROP, CPROP, PAIR) from policy
#2:calculate wcs-tansip
#3:set wcs vector
#
#Last modification : 2010/09/15
#------------------------------------------------------------

def main():
    ppPolicy = pipeUtils.getPolicyFile("hscProtopipe", "protoPipe.paf")

if __name__ == '__main__':
    main()


#    F_SET_PARAM();
#    F_WCS_TANSIP();
#    F_SET_WCSVECTOR();
