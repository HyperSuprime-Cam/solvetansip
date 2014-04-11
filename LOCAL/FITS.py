#!/usr/bin/env python
#--------------------------------------------------
#FITS.py
#
#Last Update 2014/04/01
#Yuki Okura : yuki.okura@nao.ac.jp
#--------------------------------------------------

import os, sys
import os.path
import pyfits
from pyfits import Column
import numpy

#HEAD
def GET_HEAD_VALUE(FITS_IN="IN.fits",KEYNAME="SIMPLE"):
	hdulist = pyfits.open(FITS_IN)
	hduhead = hdulist[0].header
	VALUE   = hduhead[KEYNAME]
	return VALUE
def GET_HEADs_VALUE(FITSLIST_IN=["IN.fits"],KEYNAME="SIMPLE"):
	VALUE=[]
	for F in FITSLIST_IN:
		hdulist = pyfits.open(F)
		hduhead = hdulist[0].header
		VALUE.append(hduhead[KEYNAME])
	return VALUE
def MAKE_HEAD(FITS_OUT="OUT.fits",KEYS=[""],VALUES=[""],COMMENTS=[""]):
	hdu = pyfits.PrimaryHDU()
	hdr = hdu.header

	for i in range(len(KEYS)):
		hdr.update(KEYS[i],VALUES[i],COMMENTS[i])

	hdu.writeto(FITS_OUT,clobber=True)
#BTBL
def SET_BTBL_COLUMN(TYPE_ID,NAME,DATA_IN):
	DATA=[]
	if TYPE_ID==0 :#int
		TYPE="I"
		for i in DATA_IN:
			DATA.append(int(i))
	elif TYPE_ID==1 :#long
		TYPE="K"
		for i in DATA_IN:
			DATA.append(int(i))
	elif TYPE_ID==2 :#float
		TYPE="D"
		for i in DATA_IN:
			DATA.append(float(i))
	elif TYPE_ID==3 :#double
		TYPE="D"
		for i in DATA_IN:
			DATA.append(float(i))

	return Column(name=NAME,format=TYPE,array=numpy.array(DATA))
def GET_BTBL_VALUE(FITS_IN="IN.fits",KEYNAME="FLAG"):
	hdulist = pyfits.open(FITS_IN)
	btdata = hdulist[1].data
	DATA = btdata.field
	FORM = btdata.formats
	NAME = btdata.names
	VALUE=[]
	for i in range(len(NAME)):
		if KEYNAME == NAME[i]:
			for j in DATA(i):
				VALUE.append(j)
	return VALUE
def MAKE_BTBLfromBTBL(FITS_IN="IN.fits",FITS_OUT="OUT.fits",KEYS=[""]):
	hdulist = pyfits.open(FITS_IN)
	btdata = hdulist[1].data
	DATA = btdata.field
	FORM = btdata.formats
	NAME = btdata.names

	COL=[]
	for i in range(0,len(KEYS)):
		for j in range(len(NAME)):
			if KEYS[i] == NAME[j]:
				COL.append(Column(name=NAME[j],format=FORM[j],array=DATA(j)))
	hdu = pyfits.new_table(COL)
	hdu.writeto(FITS_OUT,clobber=True)
def MAKE_ASCIIfromBTBL(FITS_IN="IN.fits",ASCII_OUT="OUT.fits",KEYS=[""],FLAG="",FLAGVAL=-1):
	if os.path.exists(ASCII_OUT) == True:
		print "Overwriting existing file '"+ASCII_OUT+"'"
	hdulist = pyfits.open(FITS_IN)
	btdata = hdulist[1].data
	DATA = btdata.field
	FORM = btdata.formats
	NAME = btdata.names
	OUT = open(ASCII_OUT,"w")

	FLAG_C=-1
	for i in range(len(KEYS)):
		if KEYS[i]==FLAG:
			FLAG_C=i

	COL=[]
	for i in range(0,len(KEYS)):
		for j in range(len(NAME)):
			if KEYS[i] == NAME[j]:
				COL.append(DATA(j))

	for j in range(len(COL[0])):
		for i in range(len(COL)):
			if FLAG_C==-1 or COL[FLAG_C][j]==FLAGVAL:
				print>>OUT , COL[i][j],
		if FLAG_C==-1 or COL[FLAG_C][j]==FLAGVAL:
			print>>OUT
