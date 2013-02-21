#!/usr/bin/env python
#--------------------------------------------------
#MAKE_Mlist.py
#
#Last Update 2013/03/01
#--------------------------------------------------

import sys,os
import os.path
import pyfits
import numpy


def main(mlistname,mlist):
	out2=open("test.dat","w")
	out=open(mlist,"w")
	for CID in range(104):
		mlistCID=mlistname+"%03d"%CID+".fits"
		if os.path.exists(mlistCID):
			print mlistCID
			hdulist=pyfits.open(mlistCID)
			btdata =hdulist[1].data
			ID   =btdata.field("ref_id")
			FLAG =btdata.field("flags")
			XY   =btdata.field("src_centroid_sdss")
			RADEC=btdata.field("ref_coord")
		for i in range(len(ID)):
			if FLAG[i][5] == False:
				print >> out, ID[i], CID, XY[i][0], XY[i][1], 180/3.14159265*RADEC[i][0], 180/3.14159265*RADEC[i][1]
#	print ID
#	print  numpy.savetxt(sys.stdout, FLAG, fmt='%d')
#	print XY
#	print RADEC

if __name__ == '__main__':
	
	mlistname = sys.argv[1]
	mlist     = sys.argv[2]
	main(mlistname,mlist)








