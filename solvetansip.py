#!/usr/bin/env python
#--------------------------------------------------
#solvetansip.py
#
#Last Update 2013/03/01
#--------------------------------------------------

import os, sys
import os.path
import SLVTANSIP.SLVTANSIP_SWIG as SLVTANSIP
#import SLVTANSIP.SLVTANSIP_TOOL as SLVTANSIP_TOOL

def main(paffile,objfile): 
	print "--- solvetansip.py START ---"
	SLVTANSIP_ANA=SLVTANSIP.SLVTANSIP_SWIG_SET(paffile,objfile);
	SLVTANSIP.SLVTANSIP_SWIG_SLV(SLVTANSIP_ANA);
	SLVTANSIP.SLVTANSIP_SWIG_EXT(SLVTANSIP_ANA);
	OUTFLAG=SLVTANSIP.SLVTANSIP_SWIG_GET_OUTFLAG(SLVTANSIP_ANA);
	OUTDIRCCD=SLVTANSIP.SLVTANSIP_SWIG_GET_OUTDIRCCD(SLVTANSIP_ANA);
	OUTDIROBJ=SLVTANSIP.SLVTANSIP_SWIG_GET_OUTDIROBJ(SLVTANSIP_ANA);
	if OUTFLAG == 1 :
		if not os.path.exists(OUTDIRCCD):
			os.mkdir(OUTDIRCCD)
		if not os.path.exists(OUTDIROBJ):
			os.mkdir(OUTDIROBJ)
	SLVTANSIP.SLVTANSIP_SWIG_OUT(SLVTANSIP_ANA);
	SLVTANSIP.SLVTANSIP_SWIG_DEL(SLVTANSIP_ANA);
	print "--- solvetansip.py END ---"

if __name__ == '__main__':

    paffile = sys.argv[1]
    objfile = sys.argv[2]
    main(paffile,objfile)
