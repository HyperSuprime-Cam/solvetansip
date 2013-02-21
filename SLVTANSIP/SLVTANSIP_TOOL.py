#!/usr/bin/env python
#--------------------------------------------------
#SLVTANSIP_TOOL.py
#
#Last Update 2013/03/01
#--------------------------------------------------
import os, sys
import os.path
import pyfits
import math
import matplotlib.pyplot as plt
import SLVTANSIP_SWIG as SLVTANSIP

#ANA
def MAKE_ANAfromfits(CCDDIR):
	ANA=SLVTANSIP.SLVTANSIP_SWIG_MAKE_ANAfromfits(CCDDIR)
	return ANA
def DEL_ANAfromfits(ANA):
	SLVTANSIP_SWIG_DEL_ANAfromfits(ANA)


#--------------------------------------------------
#--------------------------------------------------
#--------------------------------------------------
#POSITION
def GET_TANPOSITION_GLOBAL(ANA,CID,RADEC):
	GLOBAL=SLVTANSIP.SLVTANSIP_SWIG_GET_TANPOSITION_LOCAL(ANA,CID,RADEC)
	return GLOBAL
def GET_TANPOSITION_RADEC(ANA,CID,GLOBAL):
	RADEC=SLVTANSIP.SLVTANSIP_SWIG_GET_TANPOSITION_RADEC(ANA,CID,GLOBAL)
	return RADEC
def GET_SIPPOSITION_GLOBAL(ANA,CID,RADEC):
	GLOBAL=SLVTANSIP.SLVTANSIP_SWIG_GET_SIPPOSITION_LOCAL(ANA,CID,RADEC)
	return GLOBAL
def GET_SIPPOSITION_RADEC(ANA,CID,GLOBAL):
	RADEC=SLVTANSIP.SLVTANSIP_SWIG_GET_SIPPOSITION_RADEC(ANA,CID,GLOBAL)
	return RADEC
def GET_OBJPOSITION_GLOBAL(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	ID = btdata.field("OBJID")
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("X_GLOBAL")
	YG = btdata.field("Y_GLOBAL")
	GLOBAL_ALL=[]
	for i in range(len(ID)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=[XG[i],YG[i]]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=[XG[i],YG[i]]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJSIPPOSITION_GLOBAL(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	ID = btdata.field("OBJID")
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("X_GLOBAL_TANSIPfromRADEC")
	YG = btdata.field("Y_GLOBAL_TANSIPfromRADEC")
	GLOBAL_ALL=[]
	for i in range(len(ID)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=[XG[i],YG[i]]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=[XG[i],YG[i]]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJTANPOSITION_GLOBAL(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	ID = btdata.field("OBJID")
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("X_GLOBAL_TANfromRADEC")
	YG = btdata.field("Y_GLOBAL_TANfromRADEC")
	GLOBAL_ALL=[]
	for i in range(len(ID)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=[XG[i],YG[i]]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=[XG[i],YG[i]]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJPOSITION_RADEC(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	ID = btdata.field("OBJID")
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("RA")
	YG = btdata.field("DEC")
	RADEC_ALL=[]
	for i in range(len(ID)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				RADEC=[XG[i],YG[i]]
				RADEC_ALL.append(RADEC)
			elif CID == CCDID[i]:
				RADEC=[XG[i],YG[i]]
				RADEC_ALL.append(RADEC)
	return RADEC_ALL
def GET_OBJSIPPOSITION_RADEC(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	ID = btdata.field("OBJID")
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("RA_TANSIPfromGLOBAL")
	YG = btdata.field("DEC_TANSIPfromGLOBAL")
	RADEC_ALL=[]
	for i in range(len(ID)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				RADEC=[XG[i],YG[i]]
				RADEC_ALL.append(RADEC)
			elif CID == CCDID[i]:
				RADEC=[XG[i],YG[i]]
				RADEC_ALL.append(RADEC)
	return RADEC_ALL
def GET_OBJTANPOSITION_RADEC(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	ID = btdata.field("OBJID")
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("RA_TANfromGLOBAL")
	YG = btdata.field("DEC_TANfromGLOBAL")
	RADEC_ALL=[]
	for i in range(len(ID)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				RADEC=[XG[i],YG[i]]
				RADEC_ALL.append(RADEC)
			elif CID == CCDID[i]:
				RADEC=[XG[i],YG[i]]
				RADEC_ALL.append(RADEC)
	return RADEC_ALL

def GET_OBJPOSITION_GLOBAL_X(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("X_GLOBAL")
	GLOBAL_ALL=[]
	for i in range(len(XG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJPOSITION_GLOBAL_Y(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	YG = btdata.field("Y_GLOBAL")
	GLOBAL_ALL=[]
	for i in range(len(YG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL

def GET_OBJPOSITION_CRPIXGLOBAL_X(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("X_CRPIXGLOBAL")
	GLOBAL_ALL=[]
	for i in range(len(XG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJPOSITION_CRPIXGLOBAL_Y(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	YG = btdata.field("Y_CRPIXGLOBAL")
	GLOBAL_ALL=[]
	for i in range(len(YG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJSIPPOSITION_GLOBAL_X(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("X_GLOBAL_TANSIPfromRADEC")
	GLOBAL_ALL=[]
	for i in range(len(XG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJSIPPOSITION_GLOBAL_Y(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	YG = btdata.field("Y_GLOBAL_TANSIPfromRADEC")
	GLOBAL_ALL=[]
	for i in range(len(YG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJSIPPOSITION_CRPIXGLOBAL_X(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("X_CRPIXGLOBAL_TANSIPfromRADEC")
	GLOBAL_ALL=[]
	for i in range(len(XG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJSIPPOSITION_CRPIXGLOBAL_Y(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	YG = btdata.field("Y_CRPIXGLOBAL_TANSIPfromRADEC")
	GLOBAL_ALL=[]
	for i in range(len(YG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJTANPOSITION_GLOBAL_X(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("X_GLOBAL_TANfromRADEC")
	GLOBAL_ALL=[]
	for i in range(len(XG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJTANPOSITION_GLOBAL_Y(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	YG = btdata.field("Y_GLOBAL_TANfromRADEC")
	GLOBAL_ALL=[]
	for i in range(len(YG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJTANPOSITION_CRPIXGLOBAL_X(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("X_CRPIXGLOBAL_TANfromRADEC")
	GLOBAL_ALL=[]
	for i in range(len(XG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=XG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL
def GET_OBJTANPOSITION_CRPIXGLOBAL_Y(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	YG = btdata.field("Y_CRPIXGLOBAL_TANfromRADEC")
	GLOBAL_ALL=[]
	for i in range(len(YG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
			elif CID == CCDID[i]:
				GLOBAL=YG[i]
				GLOBAL_ALL.append(GLOBAL)
	return GLOBAL_ALL

def GET_OBJPOSITION_RADEC_X(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("RA")
	RADEC_ALL=[]
	for i in range(len(XG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				RADEC=XG[i]
				RADEC_ALL.append(RADEC)
			elif CID == CCDID[i]:
				RADEC=XG[i]
				RADEC_ALL.append(RADEC)
	return RADEC_ALL
def GET_OBJPOSITION_RADEC_Y(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	YG = btdata.field("DEC")
	RADEC_ALL=[]
	for i in range(len(YG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				RADEC=YG[i]
				RADEC_ALL.append(RADEC)
			elif CID == CCDID[i]:
				RADEC=YG[i]
				RADEC_ALL.append(RADEC)
	return RADEC_ALL
def GET_OBJSIPPOSITION_RADEC_X(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("RA_TANSIPfromGLOBAL")
	RADEC_ALL=[]
	for i in range(len(XG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				RADEC=XG[i]
				RADEC_ALL.append(RADEC)
			elif CID == CCDID[i]:
				RADEC=XG[i]
				RADEC_ALL.append(RADEC)
	return RADEC_ALL
def GET_OBJSIPPOSITION_RADEC_Y(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	YG = btdata.field("DEC_TANSIPfromGLOBAL")
	RADEC_ALL=[]
	for i in range(len(YG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				RADEC=YG[i]
				RADEC_ALL.append(RADEC)
			elif CID == CCDID[i]:
				RADEC=YG[i]
				RADEC_ALL.append(RADEC)
	return RADEC_ALL
def GET_OBJTANPOSITION_RADEC_X(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	XG = btdata.field("RA_TANfromGLOBAL")
	RADEC_ALL=[]
	for i in range(len(XG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				RADEC=XG[i]
				RADEC_ALL.append(RADEC)
			elif CID == CCDID[i]:
				RADEC=XG[i]
				RADEC_ALL.append(RADEC)
	return RADEC_ALL
def GET_OBJTANPOSITION_RADEC_Y(OBJDIR,CID,FLAG):
	fitsname=OBJDIR+"/SLVTANSIP_OBJECTS.fits"
	hdulist = pyfits.open(fitsname)
	btdata = hdulist[1].data
	OBJFLAG = btdata.field("OBJFLAG")
	CCDID = btdata.field("DET-ID")
	YG = btdata.field("DEC_TANfromGLOBAL")
	RADEC_ALL=[]
	for i in range(len(YG)):
		if OBJFLAG[i] == FLAG or FLAG == -1 :
			if   CID == -1:
				RADEC=YG[i]
				RADEC_ALL.append(RADEC)
			elif CID == CCDID[i]:
				RADEC=YG[i]
				RADEC_ALL.append(RADEC)
	return RADEC_ALL
def GET_CCDGRIDPOSITION():
	CCDGRIDPOSITION=[]
	CCDGRIDPOSITION.append([14,4])
	CCDGRIDPOSITION.append([15,4])
	CCDGRIDPOSITION.append([15,5])
	CCDGRIDPOSITION.append([14,5])
	return
#--------------------------------------------------
#--------------------------------------------------
#--------------------------------------------------
#--------------------------------------------------
#PLOT
def PLOT_CCD_GLOBAL(ANA,CID,plot):
	CCDNUM=SLVTANSIP.SLVTANSIP_SWIG_GET_CCDNUM(ANA)
	CORNAR=SLVTANSIP.SLVTANSIP_SWIG_GET_CORNAR_GLOBAL(ANA)
	if CID > -0.5 and CID < CCDNUM-0.5:
		plt.plot([CORNAR[4*CID+0][0],CORNAR[4*CID+1][0]],[CORNAR[4*CID+0][1],CORNAR[4*CID+1][1]],color="#777777")
		plt.plot([CORNAR[4*CID+1][0],CORNAR[4*CID+2][0]],[CORNAR[4*CID+1][1],CORNAR[4*CID+2][1]],color="#777777")
		plt.plot([CORNAR[4*CID+2][0],CORNAR[4*CID+3][0]],[CORNAR[4*CID+2][1],CORNAR[4*CID+3][1]],color="#777777")
		plt.plot([CORNAR[4*CID+3][0],CORNAR[4*CID+0][0]],[CORNAR[4*CID+3][1],CORNAR[4*CID+0][1]],color="#777777")
	elif CID == -1:
		for i in range(CCDNUM):
			plt.plot([CORNAR[4*i+0][0]    ,CORNAR[4*i+1][0]]   ,[CORNAR[4*i+0][1],CORNAR[4*i+1][1]] ,color="#777777")
			plt.plot([CORNAR[4*i+1][0]    ,CORNAR[4*i+2][0]]   ,[CORNAR[4*i+1][1],CORNAR[4*i+2][1]] ,color="#777777")
			plt.plot([CORNAR[4*i+2][0]    ,CORNAR[4*i+3][0]]   ,[CORNAR[4*i+2][1],CORNAR[4*i+3][1]] ,color="#777777")
			plt.plot([CORNAR[4*i+3][0]    ,CORNAR[4*i+0][0]]   ,[CORNAR[4*i+3][1],CORNAR[4*i+0][1]] ,color="#777777")
			plt.text( CORNAR[4*i+0][0]+150,CORNAR[4*i+0][1]+200,"{0}".format(str(i).zfill(3)),size=9,color="#777777")
			CRPIX=SLVTANSIP.SLVTANSIP_SWIG_GET_CRPIX (ANA,-1);
			plt.plot(CRPIX[0],CRPIX[1],'rx')
	else :
		print "Error PLOT_CCD_GLOBAL : there is no CCD having DET-ID : ", CID
	plt.axis('scaled')
def PLOT_CCD_RADEC(ANA,CID,plot):
	CCDNUM      =SLVTANSIP.SLVTANSIP_SWIG_GET_CCDNUM(ANA)
	CORNAR_GLOBAL=SLVTANSIP.SLVTANSIP_SWIG_GET_CORNAR_GLOBAL(ANA)
	CORNAR      =GET_SIPPOSITION_RADEC(ANA,-1,CORNAR_GLOBAL)
	if CID > -0.5 and CID < CCDNUM-0.5:
	        plt.plot([CORNAR[4*CID+0][0],CORNAR[4*CID+1][0]],[CORNAR[4*CID+0][1],CORNAR[4*CID+1][1]],color="#777777")
	        plt.plot([CORNAR[4*CID+1][0],CORNAR[4*CID+2][0]],[CORNAR[4*CID+1][1],CORNAR[4*CID+2][1]],color="#777777")
	        plt.plot([CORNAR[4*CID+2][0],CORNAR[4*CID+3][0]],[CORNAR[4*CID+2][1],CORNAR[4*CID+3][1]],color="#777777")
	        plt.plot([CORNAR[4*CID+3][0],CORNAR[4*CID+0][0]],[CORNAR[4*CID+3][1],CORNAR[4*CID+0][1]],color="#777777")
		plt.axis('scaled')
	elif CID == -1:
		for i in range(CCDNUM):
		        plt.plot([CORNAR[4*i+0][0]     ,CORNAR[4*i+1][0]]    ,[CORNAR[4*i+0][1],CORNAR[4*i+1][1]] ,color="#777777")
		        plt.plot([CORNAR[4*i+1][0]     ,CORNAR[4*i+2][0]]    ,[CORNAR[4*i+1][1],CORNAR[4*i+2][1]] ,color="#777777")
		        plt.plot([CORNAR[4*i+2][0]     ,CORNAR[4*i+3][0]]    ,[CORNAR[4*i+2][1],CORNAR[4*i+3][1]] ,color="#777777")
		        plt.plot([CORNAR[4*i+3][0]     ,CORNAR[4*i+0][0]]    ,[CORNAR[4*i+3][1],CORNAR[4*i+0][1]] ,color="#777777")
			plt.text( CORNAR[4*i+0][0]-0.08,CORNAR[4*i+0][1]-0.04,"{0}".format(str(i).zfill(3)),size=9,color="#777777")
			CRVAL=SLVTANSIP.SLVTANSIP_SWIG_GET_CRVAL (ANA,-1);
			plt.plot(CRVAL[0],CRVAL[1],'rx')
			plt.axis('scaled')
	else :
		print "Error PLOT_CCD_GLOBAL : there is no CCD having DET-ID : ", CID
def PLOT_CCD_GRID (ANA,CID,plot):
	print "test"

#CCDPOSITION
def SHOW_CCDPOSITION_GLOBAL(ANA,CCDID,OUTFLAG,EPSFLAG,PNGFLAG):
	CCDNUM=SLVTANSIP.SLVTANSIP_SWIG_GET_CCDNUM(ANA)
	if CCDID > -0.5 and CCDID < CCDNUM-0.5:
		title = "CCDPOSITION_GLOBAL : CCD = %03d"%CCDID
		plt.title(title)
	elif CCDID == -1:
		plt.title("CCDPOSITION_GLOBAL")
	else :
		print "Error PLOT_CCDPOSITION_GLOBAL : there is no CCD having DET-ID : ", CID
		return
	CCDDIR=SLVTANSIP.SLVTANSIP_SWIG_GET_OUTDIRCCD(ANA)
	PLOT_CCD_GLOBAL(ANA,CCDID,plt)
	if EPSFLAG == 1 :
		if CCDID > -0.5 and CCDID < CCDNUM-0.5:
			FIGDIR=CCDDIR+"/CCDPOSITION_GLOBAL_CCD"+"%03d"%CCDID+".eps"
			plt.savefig(FIGDIR,dpi=600)
		elif CCDID == -1:
			FIGDIR=CCDDIR+"/CCDPOSITION_GLOBAL_GLOBAL.eps"
			plt.savefig(FIGDIR,dpi=600)
	if PNGFLAG == 1 :
		if CCDID > -0.5 and CCDID < CCDNUM-0.5:
			FIGDIR=CCDDIR+"/CCDPOSITION_GLOBAL_CCD"+"%03d"%CCDID+".png"
			plt.savefig(FIGDIR,dpi=600)
		elif CCDID == -1:
			FIGDIR=CCDDIR+"/CCDPOSITION_GLOBAL_GLOBAL.png"
			plt.savefig(FIGDIR,dpi=600)
	if OUTFLAG == 1 :
		plt.show()
def SHOW_CCDPOSITION_RADEC(ANA,CCDID,OUTFLAG,EPSFLAG,PNGFLAG):
	CCDNUM=SLVTANSIP.SLVTANSIP_SWIG_GET_CCDNUM(ANA)
	if CCDID > -0.5 and CCDID < CCDNUM-0.5:
		title = "CCDPOSITION_GLOBAL : CCD = %03d"%CCDID
		plt.title(title)
	elif CCDID == -1:
		plt.title("CCDPOSITION_RADEC")
	else :
		print "Error PLOT_CCDPOSITION_GLOBAL : there is no CCD having DET-ID : ", CID
		return
	CCDDIR=SLVTANSIP.SLVTANSIP_SWIG_GET_OUTDIRCCD(ANA)
	PLOT_CCD_RADEC(ANA,CCDID,plt)
	if EPSFLAG == 1 :
		if CCDID > -0.5 and CCDID < CCDNUM-0.5:
			FIGDIR=CCDDIR+"/CCDPOSITION_RADEC_CCD"+"%03d"%CCDID+".eps"
			plt.savefig(FIGDIR,dpi=600)
		elif CCDID == -1:
			FIGDIR=CCDDIR+"/CCDPOSITION_RADEC_GLOBAL.eps"
			plt.savefig(FIGDIR,dpi=600)
	if PNGFLAG == 1 :
		if CCDID > -0.5 and CCDID < CCDNUM-0.5:
			FIGDIR=CCDDIR+"/CCDPOSITION_RADEC_CCD"+"%03d"%CCDID+".png"
			plt.savefig(FIGDIR,dpi=600)
		elif CCDID == -1:
			FIGDIR=CCDDIR+"/CCDPOSITION_RADEC_GLOBAL.png"
			plt.savefig(FIGDIR,dpi=600)
	if OUTFLAG == 1 :
		plt.show()

#OBJPOSITION
def SHOW_OBJPOSITION_GLOBAL(ANA,OBJDIR,OBJFLAG,CCDID,OUTFLAG,EPSFLAG,PNGFLAG):
	CCDNUM=SLVTANSIP.SLVTANSIP_SWIG_GET_CCDNUM(ANA)
	if CCDID > -0.5 and CCDID < CCDNUM-0.5:
		plt.title("OBJECT_POSITION_GLOBAL")
		psize=3
		vwidth=25
	elif CCDID == -1:
		plt.title("OBJECT_POSITION_GLOBAL")
		psize=2
		vwidth=50
	else :
		print "Error PLOT_CCDPOSITION_GLOBAL : there is no CCD having DET-ID : ", CID
		return
#GET_POSITION
	GLOBAL_ALL_X=GET_OBJPOSITION_GLOBAL_X(OBJDIR,CCDID,OBJFLAG)
	GLOBAL_ALL_Y=GET_OBJPOSITION_GLOBAL_Y(OBJDIR,CCDID,OBJFLAG)
	plt.plot(GLOBAL_ALL_X,GLOBAL_ALL_Y,"kx",alpha=1.0,markersize=psize)
	GLOBAL_SIP_X=GET_OBJSIPPOSITION_GLOBAL_X(OBJDIR,CCDID,OBJFLAG)
	GLOBAL_SIP_Y=GET_OBJSIPPOSITION_GLOBAL_Y(OBJDIR,CCDID,OBJFLAG)
#	plt.plot(GLOBAL_SIP_X,GLOBAL_SIP_Y,"b+",alpha=1.0,markersize=psize)
	GLOBAL_TAN_X=GET_OBJTANPOSITION_GLOBAL_X(OBJDIR,CCDID,OBJFLAG)
	GLOBAL_TAN_Y=GET_OBJTANPOSITION_GLOBAL_Y(OBJDIR,CCDID,OBJFLAG)
#	plt.plot(GLOBAL_TAN_X,GLOBAL_TAN_Y,"g4",alpha=1.0,markersize=psize)
	dGLOBAL_TAN_X=[]
	dGLOBAL_TAN_Y=[]
	dGLOBAL_SIP_X=[]
	dGLOBAL_SIP_Y=[]
	for i in range(len(GLOBAL_ALL_X)):
		dGLOBAL_TAN_X.append(GLOBAL_TAN_X[i]-GLOBAL_ALL_X[i])
		dGLOBAL_TAN_Y.append(GLOBAL_TAN_Y[i]-GLOBAL_ALL_Y[i])
		dGLOBAL_SIP_X.append(GLOBAL_SIP_X[i]-GLOBAL_ALL_X[i])
		dGLOBAL_SIP_Y.append(GLOBAL_SIP_Y[i]-GLOBAL_ALL_Y[i])
	plt.quiver(GLOBAL_ALL_X,GLOBAL_ALL_Y,dGLOBAL_TAN_X,dGLOBAL_TAN_Y,units="xy",scale=1,width=vwidth,headwidth=2,headlength=5,color="g")
	plt.quiver(GLOBAL_ALL_X,GLOBAL_ALL_Y,dGLOBAL_SIP_X,dGLOBAL_SIP_Y,units="xy",scale=1,width=vwidth,headwidth=2,headlength=5,color="b")

	PLOT_CCD_GLOBAL(ANA,CCDID,plt)
	if EPSFLAG == 1 :
		if CCDID > -0.5 and CCDID < CCDNUM-0.5:
			FIGDIR=OBJDIR+"/OBJECT_POSITION_CCD"+"%03d"%CCDID+".eps"
			plt.savefig(FIGDIR,dpi=600)
		elif CCDID == -1:
			FIGDIR=OBJDIR+"/OBJECT_POSITION_GLOBAL.eps"
			plt.savefig(FIGDIR,dpi=600)
	if PNGFLAG == 1 :
		if CCDID > -0.5 and CCDID < CCDNUM-0.5:
			FIGDIR=OBJDIR+"/OBJECT_POSITION_CCD"+"%03d"%CCDID+".png"
			plt.savefig(FIGDIR,dpi=600)
		elif CCDID == -1:
			FIGDIR=OBJDIR+"/OBJECT_POSITION_GLOBAL.png"
			plt.savefig(FIGDIR,dpi=600)
	if OUTFLAG == 1 :
		plt.show()
	plt.clf()

def SHOW_OBJPOSITION_RADEC(ANA,OBJDIR,OBJFLAG,CCDID,OUTFLAG,EPSFLAG,PNGFLAG):
	CCDNUM=SLVTANSIP.SLVTANSIP_SWIG_GET_CCDNUM(ANA)
	if CCDID > -0.5 and CCDID < CCDNUM-0.5:
		plt.title("OBJECT_POSITION_RADEC")
		psize=5
		vwidth=0.0015
	elif CCDID == -1:
		plt.title("OBJECT_POSITION_RADEC")
		psize=3
		vwidth=0.0025
	else :
		print "Error PLOT_CCDPOSITION_GLOBAL : there is no CCD having DET-ID : ", CID
		return

#GET_POSITION
	RADEC_ALL_X=GET_OBJPOSITION_RADEC_X(OBJDIR,CCDID,OBJFLAG)
	RADEC_ALL_Y=GET_OBJPOSITION_RADEC_Y(OBJDIR,CCDID,OBJFLAG)
	plt.plot(RADEC_ALL_X,RADEC_ALL_Y,"kx",alpha=1.0,markersize=psize)
	RADEC_SIP_X=GET_OBJSIPPOSITION_RADEC_X(OBJDIR,CCDID,OBJFLAG)
	RADEC_SIP_Y=GET_OBJSIPPOSITION_RADEC_Y(OBJDIR,CCDID,OBJFLAG)
#	plt.plot(RADEC_SIP_X,RADEC_SIP_Y,"b+",alpha=1.0,markersize=psize)
	RADEC_TAN_X=GET_OBJTANPOSITION_RADEC_X(OBJDIR,CCDID,OBJFLAG)
	RADEC_TAN_Y=GET_OBJTANPOSITION_RADEC_Y(OBJDIR,CCDID,OBJFLAG)
#	plt.plot(RADEC_TAN_X,RADEC_TAN_Y,"g1",alpha=1.0,markersize=psize)
	dRADEC_SIP_X=[]
	dRADEC_SIP_Y=[]
	dRADEC_TAN_X=[]
	dRADEC_TAN_Y=[]
	for i in range(len(RADEC_ALL_X)):
		dRADEC_SIP_X.append(RADEC_SIP_X[i]-RADEC_ALL_X[i])
		dRADEC_SIP_Y.append(RADEC_SIP_Y[i]-RADEC_ALL_Y[i])
		dRADEC_TAN_X.append(RADEC_TAN_X[i]-RADEC_ALL_X[i])
		dRADEC_TAN_Y.append(RADEC_TAN_Y[i]-RADEC_ALL_Y[i])
	plt.quiver(RADEC_ALL_X,RADEC_ALL_Y,dRADEC_TAN_X,dRADEC_TAN_Y,units="xy",scale=1,width=vwidth,headwidth=2,headlength=5,color="g")
	plt.quiver(RADEC_ALL_X,RADEC_ALL_Y,dRADEC_SIP_X,dRADEC_SIP_Y,units="xy",scale=1,width=vwidth,headwidth=2,headlength=5,color="b")



	PLOT_CCD_RADEC(ANA,CCDID,plt)
	if EPSFLAG == 1 :
		if CCDID > -0.5 and CCDID < CCDNUM-0.5:
			FIGDIR=OBJDIR+"/OBJECT_POSITION_RADEC_CCD"+"%03d"%CCDID+".eps"
			plt.savefig(FIGDIR,dpi=600)
		elif CCDID == -1:
			FIGDIR=OBJDIR+"/OBJECT_POSITION_RADEC_GLOBAL.eps"
			plt.savefig(FIGDIR,dpi=600)
	if PNGFLAG == 1 :
		if CCDID > -0.5 and CCDID < CCDNUM-0.5:
			FIGDIR=OBJDIR+"/OBJECT_POSITION_RADEC_CCD"+"%03d"%CCDID+".png"
			plt.savefig(FIGDIR,dpi=600)
		elif CCDID == -1:
			FIGDIR=OBJDIR+"/OBJECT_POSITION_RADEC_GLOBAL.png"
			plt.savefig(FIGDIR,dpi=600)
	if OUTFLAG == 1 :
		plt.show()
	plt.clf()
def SHOW_OBJDISTORTION_GLOBAL(ANA,OBJDIR,OBJFLAG,CCDID,OUTFLAG,EPSFLAG,PNGFLAG):
	CCDNUM=SLVTANSIP.SLVTANSIP_SWIG_GET_CCDNUM(ANA)
#GET_POSITION
	GLOBAL_ALL_X=GET_OBJPOSITION_CRPIXGLOBAL_X(OBJDIR,CCDID,OBJFLAG)
	GLOBAL_ALL_Y=GET_OBJPOSITION_CRPIXGLOBAL_Y(OBJDIR,CCDID,OBJFLAG)
	GLOBAL_SIP_X=GET_OBJSIPPOSITION_CRPIXGLOBAL_X(OBJDIR,CCDID,OBJFLAG)
	GLOBAL_SIP_Y=GET_OBJSIPPOSITION_CRPIXGLOBAL_Y(OBJDIR,CCDID,OBJFLAG)
	GLOBAL_TAN_X=GET_OBJTANPOSITION_CRPIXGLOBAL_X(OBJDIR,CCDID,OBJFLAG)
	GLOBAL_TAN_Y=GET_OBJTANPOSITION_CRPIXGLOBAL_Y(OBJDIR,CCDID,OBJFLAG)

	GLOBAL_R_ALL=[]
	dGLOBAL_TAN_R=[]
	dGLOBAL_TAN_T=[]
	dGLOBAL_SIP_R=[]
	dGLOBAL_SIP_T=[]
	for i in range(len(GLOBAL_ALL_X)):
		GLOBAL_RT=math.hypot(GLOBAL_TAN_Y[i]-GLOBAL_ALL_Y[i],GLOBAL_TAN_X[i]-GLOBAL_ALL_X[i])
		GLOBAL_RS=math.hypot(GLOBAL_SIP_Y[i]-GLOBAL_ALL_Y[i],GLOBAL_SIP_X[i]-GLOBAL_ALL_X[i])
		GLOBAL_T =math.atan2(GLOBAL_ALL_Y[i],GLOBAL_ALL_X[i])
		GLOBAL_PT=math.atan2(GLOBAL_TAN_Y[i]-GLOBAL_ALL_Y[i],GLOBAL_TAN_X[i]-GLOBAL_ALL_X[i])
		GLOBAL_PS=math.atan2(GLOBAL_SIP_Y[i]-GLOBAL_ALL_Y[i],GLOBAL_SIP_X[i]-GLOBAL_ALL_X[i])
		GLOBAL_R_ALL.append(math.hypot(GLOBAL_ALL_X[i],GLOBAL_ALL_Y[i]))
		dGLOBAL_TAN_R.append(GLOBAL_RT*math.cos(GLOBAL_PT-GLOBAL_T))
		dGLOBAL_TAN_T.append(GLOBAL_RT*math.sin(GLOBAL_PT-GLOBAL_T))
		dGLOBAL_SIP_R.append(GLOBAL_RS*math.cos(GLOBAL_PS-GLOBAL_T))
		dGLOBAL_SIP_T.append(GLOBAL_RS*math.sin(GLOBAL_PS-GLOBAL_T))

	plt.title("OBJECT_DISTORTION_CRPIXGLOBAL : RADIUS v.s. RADIAL TAN DISTORTION ")
	plt.plot(GLOBAL_R_ALL,dGLOBAL_TAN_R,"g+")
	if EPSFLAG == 1 :
		FIGDIR=OBJDIR+"/OBJECT_DISTORTION_RADIAL_TAN_CRPIXGLOBAL.eps"
		plt.savefig(FIGDIR,dpi=600)
	if PNGFLAG == 1 :
		FIGDIR=OBJDIR+"/OBJECT_DISTORTION_RADIAL_TAN_CRPIXGLOBAL.png"
		plt.savefig(FIGDIR,dpi=600)
	if OUTFLAG == 1 :
		plt.show()
	plt.clf()

	plt.title("OBJECT_DISTORTION_CRPIXGLOBAL : RADIUS v.s. TANGENTIAL TAN DISTORTION ")
	plt.plot(GLOBAL_R_ALL,dGLOBAL_TAN_T,"g+")
	if EPSFLAG == 1 :
		FIGDIR=OBJDIR+"/OBJECT_DISTORTION_TANGENTIAL_TAN_CRPIXGLOBAL.eps"
		plt.savefig(FIGDIR,dpi=600)
	if PNGFLAG == 1 :
		FIGDIR=OBJDIR+"/OBJECT_DISTORTION_TANGENTIAL_TAN_CRPIXGLOBAL.png"
		plt.savefig(FIGDIR,dpi=600)
	if OUTFLAG == 1 :
		plt.show()
	plt.clf()

	plt.title("OBJECT_DISTORTION_CRPIXGLOBAL : RADIUS v.s. RADIAL SIP DISTORTION ")
	plt.plot(GLOBAL_R_ALL,dGLOBAL_SIP_R,"b+")
	if EPSFLAG == 1 :
		FIGDIR=OBJDIR+"/OBJECT_DISTORTION_RADIAL_SIP_CRPIXGLOBAL.eps"
		plt.savefig(FIGDIR,dpi=600)
	if PNGFLAG == 1 :
		FIGDIR=OBJDIR+"/OBJECT_DISTORTION_RADIAL_SIP_CRPIXGLOBAL.png"
		plt.savefig(FIGDIR,dpi=600)
	if OUTFLAG == 1 :
		plt.show()
	plt.clf()

	plt.title("OBJECT_DISTORTION_CRPIXGLOBAL : RADIUS v.s. TANGENTIAL SIP DISTORTION ")
	plt.plot(GLOBAL_R_ALL,dGLOBAL_SIP_T,"b+")
	if EPSFLAG == 1 :
		FIGDIR=OBJDIR+"/OBJECT_DISTORTION_TANGENTIAL_SIP_CRPIXGLOBAL.eps"
		plt.savefig(FIGDIR,dpi=600)
	if PNGFLAG == 1 :
		FIGDIR=OBJDIR+"/OBJECT_DISTORTION_TANGENTIAL_SIP_CRPIXGLOBAL.png"
		plt.savefig(FIGDIR,dpi=600)
	if OUTFLAG == 1 :
		plt.show()
	plt.clf()

def SHOW_DENSITY(ANA,CCDID,OUTFLAG,EPSFLAG,PNGFLAG):
	print "test"
	

