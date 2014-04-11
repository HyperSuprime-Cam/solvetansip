#!/usr/bin/env python

import os, sys
import os.path

import numpy
import pyfits
from pyfits import Column
import matplotlib.pyplot as plt
import PLOT
import FITS


#CCD POS
def STAT_CCDPOS(visit,BASE,flag_show=0,flag_return=0):
	FITSNAME=visit+"/solvetansipresult_CCDs.fits"
	if not os.path.exists(FITSNAME):
	        sys.exit("Could not be found fitsdata : "+FITSNAME)
	print("visit fits : "+FITSNAME)
	if not os.path.exists(BASE):
	        sys.exit("Could not be found fitsdata : "+BASE)
	print("BASE fits  : "+BASE)

	POS=[]
	POS.append(FITS.GET_BTBL_VALUE(FITSNAME,"GPOS_C_X"))
	POS.append(FITS.GET_BTBL_VALUE(FITSNAME,"GPOS_C_Y"))
	POS.append(FITS.GET_BTBL_VALUE(FITSNAME,"GPOS_C_T"))
	POS.append(FITS.GET_BTBL_VALUE(FITSNAME,"GPOS_C_TD"))

	BASE_POS=[]
	BASE_POS.append(FITS.GET_BTBL_VALUE(BASE,"GPOS_C_X"))
	BASE_POS.append(FITS.GET_BTBL_VALUE(BASE,"GPOS_C_Y"))
	BASE_POS.append(FITS.GET_BTBL_VALUE(BASE,"GPOS_C_T"))
	BASE_POS.append(FITS.GET_BTBL_VALUE(BASE,"GPOS_C_TD"))

	DOSX=[]
	DOSY=[]
	DOST=[]
	DOSD=[]
	for i in range(104):
		DOSX.append(POS[0][i]-BASE_POS[0][i])
		DOSY.append(POS[1][i]-BASE_POS[1][i])
		DOST.append(POS[2][i]-BASE_POS[2][i])
		DOSD.append(POS[3][i]-BASE_POS[3][i])

#OUTPUT
	OUT_ID=[]
	for i in range(104):
		OUT_ID.append(i)
	OUT_COL=[]
	OUT_COL.append(Column(name="CCDID" ,format="J",array=OUT_ID))
	OUT_COL.append(Column(name="GPOS_C_X",format="D",array=POS[0]))
	OUT_COL.append(Column(name="GPOS_C_Y",format="D",array=POS[1]))
	OUT_COL.append(Column(name="GPOS_C_T",format="D",array=POS[2]))
	OUT_COL.append(Column(name="GPOS_C_TD",format="D",array=POS[3]))
	OUT_COL.append(Column(name="DIFF_GPOS_C_X",format="D",array=DOSX))
	OUT_COL.append(Column(name="DIFF_GPOS_C_Y",format="D",array=DOSY))
	OUT_COL.append(Column(name="DIFF_GPOS_C_T",format="D",array=DOST))
	OUT_COL.append(Column(name="DIFF_GPOS_C_TD",format="D",array=DOSD))
	OUT_hdu = pyfits.new_table(OUT_COL)
	OUTNAME=visit+"/CCD.fits"
	print("OUT fits   : "+OUTNAME)
	OUT_hdu.writeto(OUTNAME,clobber=True)

#PLOT
	PLOT_TITLE="DIFF of GPOS_C_X from GPOS_BASE"
	PLOT_NAME=visit+"/CCD_DIFF_POS_C_X.png"
	PLOT.PLOT_SCAT3(POS[0][0:104],POS[1][0:104],DOSX,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_C_Y from GPOS_BASE"
	PLOT_NAME=visit+"/CCD_DIFF_POS_C_Y.png"
	PLOT.PLOT_SCAT3(POS[0][0:104],POS[1][0:104],DOSY,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_C_T from GPOS_BASE"
	PLOT_NAME=visit+"/CCD_DIFF_POS_C_T.png"
	PLOT.PLOT_SCAT3(POS[0][0:104],POS[1][0:104],DOST,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_C_TD from GPOS_BASE"
	PLOT_NAME=visit+"/CCD_DIFF_POS_C_D.png"
	PLOT.PLOT_SCAT3(POS[0][0:104],POS[1][0:104],DOSD,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

#return
	if flag_return == 1:
		POS.append(DOSX)
		POS.append(DOSY)
		POS.append(DOST)
		POS.append(DOSD)
		return POS

def STAT_CCDPOS_ALL(visitlist,BASE,OUT,flag_show=0):
	POSLIST=[]
	for visit in visitlist:
		POSLIST.append(STAT_CCDPOS(str(visit),BASE,flag_return=1))

	if os.path.exists(OUT) == False:
		os.makedirs(OUT)

	POSX=[[] for i in range(104)]
	POSY=[[] for i in range(104)]
	POST=[[] for i in range(104)]
	POSD=[[] for i in range(104)]
	DOSX=[[] for i in range(104)]
	DOSY=[[] for i in range(104)]
	DOST=[[] for i in range(104)]
	DOSD=[[] for i in range(104)]
	for LIST in POSLIST:
		for CCD in range(104):
			POSX[CCD].append(LIST[0][CCD])
			POSY[CCD].append(LIST[1][CCD])
			POST[CCD].append(LIST[2][CCD])
			POSD[CCD].append(LIST[3][CCD])
			DOSX[CCD].append(LIST[4][CCD])
			DOSY[CCD].append(LIST[5][CCD])
			DOST[CCD].append(LIST[6][CCD])
			DOSD[CCD].append(LIST[7][CCD])

#output
	OUT_ID=[]
	APOSX=[]
	APOSY=[]
	APOST=[]
	APOSD=[]
	SPOSX=[]
	SPOSY=[]
	SPOST=[]
	SPOSD=[]
	ADOSX=[]
	ADOSY=[]
	ADOST=[]
	ADOSD=[]
	SDOSX=[]
	SDOSY=[]
	SDOST=[]
	SDOSD=[]
	for i in range(104):
		OUT_ID.append(i)
		APOSX.append(numpy.mean(POSX[i]))
		APOSY.append(numpy.mean(POSY[i]))
		APOST.append(numpy.mean(POST[i]))
		APOSD.append(numpy.mean(POSD[i]))
		SPOSX.append(numpy.std (POSX[i]))
		SPOSY.append(numpy.std (POSY[i]))
		SPOST.append(numpy.std (POST[i]))
		SPOSD.append(numpy.std (POSD[i]))
		ADOSX.append(numpy.mean(DOSX[i]))
		ADOSY.append(numpy.mean(DOSY[i]))
		ADOST.append(numpy.mean(DOST[i]))
		ADOSD.append(numpy.mean(DOSD[i]))
		SDOSX.append(numpy.std (DOSX[i]))
		SDOSY.append(numpy.std (DOSY[i]))
		SDOST.append(numpy.std (DOST[i]))
		SDOSD.append(numpy.std (DOSD[i]))

	OUT_COL=[]
	OUT_COL.append(Column(name="CCDID" ,format="J",array=OUT_ID))
	OUT_COL.append(Column(name="GPOS_C_X",format="D",array=APOSX))
	OUT_COL.append(Column(name="GPOS_C_Y",format="D",array=APOSY))
	OUT_COL.append(Column(name="GPOS_C_T",format="D",array=APOST))
	OUT_COL.append(Column(name="GPOS_C_TD",format="D",array=APOSD))
	OUT_COL.append(Column(name="STD_GPOS_C_X",format="D",array=SPOSX))
	OUT_COL.append(Column(name="STD_GPOS_C_Y",format="D",array=SPOSY))
	OUT_COL.append(Column(name="STD_GPOS_C_T",format="D",array=SPOST))
	OUT_COL.append(Column(name="STD_GPOS_C_TD",format="D",array=SPOSD))
	OUT_COL.append(Column(name="AVE_DIFF_GPOS_C_X",format="D",array=ADOSX))
	OUT_COL.append(Column(name="AVE_DIFF_GPOS_C_Y",format="D",array=ADOSY))
	OUT_COL.append(Column(name="AVE_DIFF_GPOS_C_T",format="D",array=ADOST))
	OUT_COL.append(Column(name="AVE_DIFF_GPOS_C_TD",format="D",array=ADOSD))
	OUT_COL.append(Column(name="STD_DIFF_GPOS_X",format="D",array=SDOSX))
	OUT_COL.append(Column(name="STD_DIFF_GPOS_Y",format="D",array=SDOSY))
	OUT_COL.append(Column(name="STD_DIFF_GPOS_T",format="D",array=SDOST))
	OUT_COL.append(Column(name="STD_DIFF_GPOS_TD",format="D",array=SDOSD))
	OUT_hdu = pyfits.new_table(OUT_COL)
	OUTNAME=OUT+"/CCD_STAT.fits"
	print("OUT fits   : "+OUTNAME)
	OUT_hdu.writeto(OUTNAME,clobber=True)

	OUTSTAT=OUT+"/CCD_STAT.dat"
	FOUT=open(OUTSTAT,"w")
	for i in range(104):
		print>> FOUT ,OUT_ID[i], len(visitlist), APOSX[i], APOSY[i], APOST[i], SPOSX[i], SPOSY[i], SPOST[i], ADOSX[i], ADOSY[i], ADOST[i], SDOSX[i], SDOSY[i], SDOST[i]
	print "OUT file   : "+ OUTSTAT

#plot
	PLOT_TITLE="STD of GPOS_C_X"
	PLOT_NAME =OUT+"/STD_GPOS_C_X.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SPOSX,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_C_Y"
	PLOT_NAME =OUT+"/STD_GPOS_C_Y.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SPOSY,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_C_T"
	PLOT_NAME =OUT+"/STD_GPOS_C_T.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SPOST,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_C_TD"
	PLOT_NAME =OUT+"/STD_GPOS_C_TD.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SPOSD,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_C_X from GPOS_BASE"
	PLOT_NAME =OUT+"/DIFF_GPOS_C_X.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,ADOSX,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_C_Y from GPOS_BASE"
	PLOT_NAME =OUT+"/DIFF_GPOS_C_Y.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,ADOSY,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_C_T from GPOS_BASE"
	PLOT_NAME =OUT+"/DIFF_GPOS_C_T.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,ADOST,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_C_T from GPOS_BASE"
	PLOT_NAME =OUT+"/DIFF_GPOS_C_TD.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,ADOSD,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_C_X from GPOS_BASE"
	PLOT_NAME =OUT+"/STD_DIFF_GPOS_C_X.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SDOSX,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_C_Y from GPOS_BASE"
	PLOT_NAME =OUT+"/STD_DIFF_GPOS_C_Y.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SDOSY,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_C_T from GPOS_BASE"
	PLOT_NAME =OUT+"/STD_DIFF_GPOS_C_T.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SDOST,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_C_TD from GPOS_BASE"
	PLOT_NAME =OUT+"/STD_DIFF_GPOS_C_TD.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SDOSD,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)


	DOSXMUL=[]
	DOSYMUL=[]
	DOSTMUL=[]
	DOSDMUL=[]
	for LIST in POSLIST:
		for CCD in range(104):
			DOSXMUL.append(1000*(LIST[0][CCD]-APOSX[CCD])+APOSX[CCD])
			DOSYMUL.append(1000*(LIST[1][CCD]-APOSY[CCD])+APOSY[CCD])
			DOSTMUL.append(1000*(LIST[2][CCD]-APOST[CCD])+APOST[CCD])
			DOSDMUL.append(1000*(LIST[3][CCD]-APOSD[CCD])+APOSD[CCD])


	PLOT_TITLE="1000*DPOS_X - 1000*DPOS_Y - 1000*DPOS_T"
	PLOT_NAME =OUT+"/CCD_SCAT_T.png"
	PLOT.PLOT_SCAT3(DOSXMUL,DOSYMUL,DOSTMUL,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)
	PLOT_TITLE="1000*DPOS_X - 1000*DPOS_Y - 1000*DPOS_D"
	PLOT_NAME =OUT+"/CCD_SCAT_D.png"
	PLOT.PLOT_SCAT3(DOSXMUL,DOSYMUL,DOSDMUL,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)


def STAT_SIPRMS(visit,flag_return=0):
	FITSNAME=str(visit)+"/solvetansipresult_CCDs.fits"
	if not os.path.exists(FITSNAME):
	        sys.exit("Could not be found fitsdata : "+FITSNAME)
	print("visit fits : "+FITSNAME)
	POS=[]
	POS.append(FITS.GET_BTBL_VALUE(FITSNAME,"GPOS_C_X"))
	POS.append(FITS.GET_BTBL_VALUE(FITSNAME,"GPOS_C_Y"))


	ERMS=[]
	ERMS.append(FITS.GET_BTBL_VALUE(FITSNAME,"ERR_SIP_X_RMS")[-1])
	ERMS.append(FITS.GET_BTBL_VALUE(FITSNAME,"ERR_SIP_Y_RMS")[-1])
	ERMS.append(FITS.GET_BTBL_VALUE(FITSNAME,"ERR_PSIP_X_RMS")[-1])
	ERMS.append(FITS.GET_BTBL_VALUE(FITSNAME,"ERR_PSIP_Y_RMS")[-1])

#return
	if flag_return == 1:
		return ERMS

def STAT_SIPRMS_ALL(visitlist,OUT,flag_show=0):
	CCDRLIST=[]
	ERMS=[]
	for vl in visitlist:
		CCDRLIST.append(str(vl)+"/solvetansipresult_CCDs.fits")
		if not os.path.exists(CCDRLIST[-1]):
		        sys.exit("Could not be found fitsdata : "+CCDRLIST[-1])
		ERMS.append(STAT_SIPRMS(vl,flag_return=1))

	SRMS1=[]
	SRMS2=[]
	SRMS3=[]
	SRMS4=[]
	for vl in range(len(visitlist)):
		SRMS1.append(ERMS[vl][0])
		SRMS2.append(ERMS[vl][1])
		SRMS3.append(ERMS[vl][2])
		SRMS4.append(ERMS[vl][3])

	SRMS=[]
	SRMS.append(SRMS1)
	SRMS.append(SRMS2)
	SRMS.append(SRMS3)
	SRMS.append(SRMS4)

	visitvalue=[]
	for vl in visitlist:
		visitvalue.append(int(vl.split("/")[-1]))	

	PLOT_TITLE="RMS_SIP"
	flag_out=1
	name_out  =OUT+"/RMS_SIP.png"
	plt.title(PLOT_TITLE)
	plt.plot(visitvalue,SRMS[0],'k.')
	plt.plot(visitvalue,SRMS[1],'b.')
	plt.plot(visitvalue,SRMS[2],'r.')
	plt.plot(visitvalue,SRMS[3],'g.')
	plt.legend(["RMS SIP X","RMS SIP Y","RMS PSIP X","RMS PSIP Y"],"upper right")
	if flag_out == 1:
		plt.savefig(name_out)
	if flag_show == 1:
		plt.show()
	plt.close()


#REF
def STAT_REF(visit,flag_show=0,flag_return=0):
	FITSNAME=visit+"/solvetansipresult_REFs.fits"
	if not os.path.exists(FITSNAME):
	        sys.exit("Could not be found fitsdata : "+FITSNAME)
	print("visit fits : "+FITSNAME)

	REF=[]
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"ID_OBJ"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"FLAG_OBJ"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"POSITION_DETECTED_LOCAL_G_X"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"POSITION_DETECTED_LOCAL_G_Y"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"POSITION_DETECTED_CRPIX_G_X"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"POSITION_DETECTED_CRPIX_G_Y"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"POSITION_CELESTIAL_RA"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"POSITION_CELESTIAL_DEC"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"DIFF_ASIP_X"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"DIFF_ASIP_Y"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"DIFF_PSIP_X"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"DIFF_PSIP_Y"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"CAMERA_DIST_CONVERGENCE"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"CAMERA_DIST_CONVERGENCE"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"CAMERA_DIST_CONVERGENCE"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"CAMERA_DIST_CONVERGENCE"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"CAMERA_DIST_CONVERGENCE"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"CAMERA_DIST_ROTATION"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"CAMERA_DIST_SHEAR1"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"CAMERA_DIST_SHEAR2"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"CAMERA_DIST_MAGNIFICATION"))
	REF.append(FITS.GET_BTBL_VALUE(FITSNAME,"CAMERA_DIST_JACOBIAN"))

	IL=[]
	for i in range(len(REF[0])):
		IL.append(len(REF[0])-i-1)

	for i in range(len(REF[0])):
		if(REF[1][IL[i]] == 0):
			for j in range(len(REF)):
				REF[j].pop(IL[i])

#plot
	PLOT_TITLE="GLOBAL_X - GLOBAL_Y - DIFF SIP X"
	PLOT_NAME =visit+"/DIFF_SIPX.png"
	PLOT.PLOT_SCAT3(REF[2],REF[3],REF[8],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="GLOBAL_X - GLOBAL_Y - DIFF SIP Y"
	PLOT_NAME =visit+"/DIFF_SIPY.png"
	PLOT.PLOT_SCAT3(REF[2],REF[3],REF[9],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="GLOBAL_X - GLOBAL_Y - DIFF PSIP X"
	PLOT_NAME =visit+"/DIFF_PSIPX.png"
	PLOT.PLOT_SCAT3(REF[2],REF[3],REF[10],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="GLOBAL_X - GLOBAL_Y - DIFF PSIP Y"
	PLOT_NAME =visit+"/DIFF_PSIPY.png"
	PLOT.PLOT_SCAT3(REF[2],REF[3],REF[11],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="GLOBAL_X - GLOBAL_Y - CAMERA COMVERGENCE"
	PLOT_NAME =visit+"/CAMERACONV_PSIP.png"
	PLOT.PLOT_SCAT3(REF[2],REF[3],REF[12],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="GLOBAL_X - GLOBAL_Y - CAMERA ROTATION"
	PLOT_NAME =visit+"/CAMERAROT_PSIP.png"
	PLOT.PLOT_SCAT3(REF[2],REF[3],REF[13],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="GLOBAL_X - GLOBAL_Y - CAMERA SHEAR1"
	PLOT_NAME =visit+"/CAMERASHR1_PSIP.png"
	PLOT.PLOT_SCAT3(REF[2],REF[3],REF[14],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="GLOBAL_X - GLOBAL_Y - CAMERA SHEAR2"
	PLOT_NAME =visit+"/CAMERASHR2_PSIP.png"
	PLOT.PLOT_SCAT3(REF[2],REF[3],REF[15],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="GLOBAL_X - GLOBAL_Y - CAMERA MAGNIFICATION"
	PLOT_NAME =visit+"/CAMERAMAG_PSIP.png"
	PLOT.PLOT_SCAT3(REF[2],REF[3],REF[16],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="GLOBAL_X - GLOBAL_Y - CAMERA JACOBIAN"
	PLOT_NAME =visit+"/CAMERAJACO_PSIP.png"
	PLOT.PLOT_SCAT3(REF[2],REF[3],REF[17],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

def STAT_REF_ALL(visitlist,flag_show=0):
	for visit in visitlist:
		STAT_REF(str(visit),flag_show=flag_show)

#DIST
def CUT_DIST(name=""):
	FIN=open(name,"r")
	vv=[]
	for v in FIN:
		vv.append(v[:-1].split(" "))

	Fout=open(name,"w")
	for B in range(len(vv)):
		if float(vv[B][0])*float(vv[B][0])+float(vv[B][1])*float(vv[B][1]) < 17501*17501:
			print>>Fout, vv[B][0],vv[B][1],vv[B][2],vv[B][3]


def READ_DIST(name=""):
	FIN=open(name,"r")
	vv=[]
	for v in FIN:
		vv.append(v[:-1].split(" "))

	X=[]
	Y=[]
	V=[]
	W=[]
	for i in range(len(vv)):
		X.append(vv[i][0])
		Y.append(vv[i][1])
		V.append(vv[i][2])
		W.append(vv[i][3])
	Z=[]
	Z.append(X)
	Z.append(Y)
	Z.append(V)
	Z.append(W)
	return Z

def MAKE_DIST(visit,BASE):
	BASE_DIST=READ_DIST(name=BASE)

#	FITSNAME=str(visit)+"/solvetansipresult_SUMMARY.fits"
#	THETA=FITS.GET_HEAD_VALUE(FITSNAME,"ANGLE")
#	print THETA

	FITSNAME=str(visit)+"/solvetansipresult_CCDs.fits"
	if not os.path.exists(FITSNAME):
	        sys.exit("Could not be found fitsdata : "+FITSNAME)
	print("visit fits : "+FITSNAME)

	CD=[]
	CD.append(FITS.GET_BTBL_VALUE(FITSNAME,"CD1_1")[-1])
	CD.append(FITS.GET_BTBL_VALUE(FITSNAME,"CD1_2")[-1])
	CD.append(FITS.GET_BTBL_VALUE(FITSNAME,"CD2_1")[-1])
	CD.append(FITS.GET_BTBL_VALUE(FITSNAME,"CD2_2")[-1])
	OSA =0
	OSB =0
	OPA =0
	OPB =0
	OSA=FITS.GET_BTBL_VALUE(FITSNAME,"ORDER_SIP_A")[-1]
	OSB=FITS.GET_BTBL_VALUE(FITSNAME,"ORDER_SIP_B")[-1]
	OPA=FITS.GET_BTBL_VALUE(FITSNAME,"ORDER_PSIP_A")[-1]
	OPB=FITS.GET_BTBL_VALUE(FITSNAME,"ORDER_PSIP_B")[-1]
	SIPA=[]
	SIPB=[]
	PIPA=[]
	PIPB=[]
	for j in range(int(0.5*(OSA+1)*(OSA+2)+0.5)):
		KEY="SIP_A_"+str(j)
		SIPA.append(FITS.GET_BTBL_VALUE(FITSNAME,KEY)[-1])
	SIPA[1*OSA+1]+=1
	for j in range(int(0.5*(OSB+1)*(OSB+2)+0.5)):
		KEY="SIP_B_"+str(j)
		SIPB.append(FITS.GET_BTBL_VALUE(FITSNAME,KEY)[-1])
	SIPB[0*OSB+1]+=1
	for j in range(int(0.5*(OPA+1)*(OPA+2)+0.5)):
		KEY="PSIP_A_"+str(j)
		PIPA.append(FITS.GET_BTBL_VALUE(FITSNAME,KEY)[-1])
	PIPA[1*OPA+1]+=1
	for j in range(int(0.5*(OPB+1)*(OPB+2)+0.5)):
		KEY="PSIP_B_"+str(j)
		PIPB.append(FITS.GET_BTBL_VALUE(FITSNAME,KEY)[-1])
	PIPB[0*OPB+1]+=1

	THETA = numpy.arctan2((-CD[1]-CD[2]),(-CD[0]+CD[3]))
	print "THETA : ",THETA
	SCALE = 0.17/60.0/60.0

	FCD=[]
	FCD.append(-(numpy.cos(-THETA)*(-CD[0])-numpy.sin(-THETA)*(-CD[2])))
	FCD.append(-(numpy.cos(-THETA)*( CD[1])-numpy.sin(-THETA)*( CD[3])))
	FCD.append( (numpy.sin(-THETA)*(-CD[0])+numpy.cos(-THETA)*(-CD[2])))
	FCD.append( (numpy.sin(-THETA)*( CD[1])+numpy.cos(-THETA)*( CD[3])))
#	print FCD[0],FCD[1]
#	print FCD[2],FCD[3]
#	print -FCD[0],FCD[1]
#	print -FCD[2],FCD[3]
	SCD=[]
	SCD.append(FCD[0]/(-SCALE))
	SCD.append(FCD[1]/(-SCALE))
	SCD.append(FCD[2]/( SCALE))
	SCD.append(FCD[3]/( SCALE))
#	print SCD[0],SCD[1]
#	print SCD[2],SCD[3]

	FOUT=open(str(visit)+"/DIST.dat","w")

	DISTXY=[]
	PX=[]
	PY=[]
	PDX=[]
	PDY=[]
	DDX=[]
	DDY=[]

	for B in range(len(BASE_DIST[0])):
		FX=float(BASE_DIST[0][B])
		FY=float(BASE_DIST[1][B])

		X=FX*numpy.cos(THETA)-FY*numpy.sin(THETA)
		Y=FY*numpy.cos(THETA)+FX*numpy.sin(THETA)
		MX=[]
		MY=[]
		MX.append(1.0)
		MY.append(1.0)
		for i in range(1,10):
			MX.append(X*MX[i-1])
			MY.append(Y*MY[i-1])

		DISTX=0.0
		DISTY=0.0
		PISTX=0.0
		PISTY=0.0
		ij=0
		for i in range(OSA+1):
			for j in range(OSA+1):
				if i+j<OSA+0.5:
					DISTX+=SIPA[ij]*MX[i]*MY[j]
					ij+=1
		ij=0
		for i in range(OSB+1):
			for j in range(OSB+1):
				if i+j<OSB+0.5:
					DISTY+=SIPB[ij]*MX[i]*MY[j]
					ij+=1
		ij=0
		for i in range(OPA+1):
			for j in range(OPA+1):
				if i+j<OPA+0.5:
					PISTX+=PIPA[ij]*MX[i]*MY[j]
					ij+=1
		ij=0
		for i in range(OPB+1):
			for j in range(OPB+1):
				if i+j<OPB+0.5:
					PISTY+=PIPB[ij]*MX[i]*MY[j]
					ij+=1

		FDISTX=DISTX*numpy.cos(-THETA)-DISTY*numpy.sin(-THETA)
		FDISTY=DISTY*numpy.cos(-THETA)+DISTX*numpy.sin(-THETA)
#		FCDISTX=FCD[0]*FDISTX+FCD[1]*FDISTY
#		FCDISTY=FCD[2]*FDISTX+FCD[3]*FDISTY
		SCDISTX=SCD[0]*FDISTX+SCD[1]*FDISTY
		SCDISTY=SCD[2]*FDISTX+SCD[3]*FDISTY
	
		PX.append(FX)
		PY.append(FY)
		PDX.append(SCDISTX)
		PDY.append(SCDISTY)
		DDX.append(SCDISTX-float(BASE_DIST[2][B]))
		DDY.append(SCDISTY-float(BASE_DIST[3][B]))
		print>>FOUT, PX[-1], PY[-1], PDX[-1], PDY[-1], DDX[-1], DDY[-1]

def MAKE_DIST_ALL(visitlist,BASE):
	for vl in visitlist:
		MAKE_DIST(vl,BASE)

def STAT_DIST(visit,BASE,flag_show=0,flag_return=0):
	BASE_DIST=READ_DIST(name=BASE)
	DIST=READ_DIST(name=str(visit)+"/DIST.dat")

	PX=[]
	PY=[]
	PDX=[]
	PDY=[]
	DDX=[]
	DDY=[]
	for B in range(len(BASE_DIST[0])):
		PX.append (float(BASE_DIST[0][B]))
		PY.append (float(BASE_DIST[1][B]))
		PDX.append(float(DIST[2][B]))
		PDY.append(float(DIST[3][B]))
		DDX.append(float(DIST[2][B])-float(BASE_DIST[2][B]))
		DDY.append(float(DIST[3][B])-float(BASE_DIST[3][B]))
		
	PLOT.PLOT_SCAT3(PX,PY,DDX,title="distortion SIP_X",flag_out=1,name_out=str(visit)+"/DIST_SIP_X.png",flag_show=flag_show)
	PLOT.PLOT_SCAT3(PX,PY,DDY,title="distortion SIP_Y",flag_out=1,name_out=str(visit)+"/DIST_SIP_Y.png",flag_show=flag_show)

#return
	if flag_return == 1:
		DISTXY=[]
		DISTXY.append(PX)
		DISTXY.append(PY)
		DISTXY.append(PDX)
		DISTXY.append(PDY)
		DISTXY.append(DDX)
		DISTXY.append(DDY)
		return DISTXY


def STAT_DIST_ALL(visitlist,BASE,OUT,flag_show=0):
	DLIST=[]
	for vl in visitlist:
		DLIST.append(STAT_DIST(vl,BASE,flag_show=0,flag_return=1))

	FOUT=open(OUT+"/DIST_AVE.dat","w")
	DOUT=open(OUT+"/DIST_DIFF.dat","w")
	MvlX=[]
	MvlY=[]
	SvlX=[]
	SvlY=[]
	DMvlX=[]
	DMvlY=[]
	DSvlX=[]
	DSvlY=[]
	for B in range(len(DLIST[0][0])):
		DvlX=[]
		DvlY=[]
		DDvlX=[]
		DDvlY=[]
		for vl in range(len(DLIST)):
			DvlX.append( float(DLIST[vl][2][B]))
			DvlY.append( float(DLIST[vl][3][B]))
			DDvlX.append(float(DLIST[vl][4][B]))
			DDvlY.append(float(DLIST[vl][5][B]))
		MvlX.append (numpy.mean(DvlX))
		MvlY.append (numpy.mean(DvlY))
		SvlX.append (numpy.std (DvlX))
		SvlY.append (numpy.std (DvlY))
		DMvlX.append(numpy.mean(DDvlX))
		DMvlY.append(numpy.mean(DDvlY))
		DSvlX.append(numpy.std (DDvlX))
		DSvlY.append(numpy.std (DDvlY))
		print>>FOUT, DLIST[0][0][B], DLIST[0][1][B], MvlX[-1], MvlY[-1], SvlX[-1], SvlY[-1]
		print>>DOUT, DLIST[0][0][B], DLIST[0][1][B],DMvlX[-1],DMvlY[-1],DSvlX[-1],DSvlY[-1]

	PLOT.PLOT_SCAT3(DLIST[0][0],DLIST[0][1], MvlX,title="mean distortion SIP_X"     ,flag_out=1,name_out=OUT+"/DIST_MEAN_SIP_X.png",flag_show=flag_show)
	PLOT.PLOT_SCAT3(DLIST[0][0],DLIST[0][1], MvlY,title="mean distortion SIP_Y"     ,flag_out=1,name_out=OUT+"/DIST_MEAN_SIP_Y.png",flag_show=flag_show)
	PLOT.PLOT_SCAT3(DLIST[0][0],DLIST[0][1], SvlX,title="std  distortion SIP_X"     ,flag_out=1,name_out=OUT+"/DIST_STD_SIP_X.png" ,flag_show=flag_show)
	PLOT.PLOT_SCAT3(DLIST[0][0],DLIST[0][1], SvlY,title="std  distortion SIP_Y"     ,flag_out=1,name_out=OUT+"/DIST_STD_SIP_Y.png" ,flag_show=flag_show)
	PLOT.PLOT_SCAT3(DLIST[0][0],DLIST[0][1],DMvlX,title="mean distortion-diff SIP_X",flag_out=1,name_out=OUT+"/DIST_MEAN_SIP_X.png",flag_show=flag_show)
	PLOT.PLOT_SCAT3(DLIST[0][0],DLIST[0][1],DMvlY,title="mean distortion-diff SIP_Y",flag_out=1,name_out=OUT+"/DIST_MEAN_SIP_Y.png",flag_show=flag_show)
	PLOT.PLOT_SCAT3(DLIST[0][0],DLIST[0][1],DSvlX,title="std  distortion-diff SIP_X",flag_out=1,name_out=OUT+"/DIST_STD_SIP_X.png" ,flag_show=flag_show)
	PLOT.PLOT_SCAT3(DLIST[0][0],DLIST[0][1],DSvlY,title="std  distortion-diff SIP_Y",flag_out=1,name_out=OUT+"/DIST_STD_SIP_Y.png" ,flag_show=flag_show)

