#!/usr/bin/env python

import os, sys
import os.path

import numpy
import pyfits
from pyfits import Column
import matplotlib.pyplot as plt
import PLOT

def WCS_GET_VALUE(FITS,KEY):
	hdulist = pyfits.open(FITS)
	btdata  = hdulist[1].data
	DATA    = btdata.field
	FORM    = btdata.formats
	NAME    = btdata.names

	VALUE=[]
	for i in range(len(NAME)):
		if NAME[i] == KEY:
			for X in Column(name=NAME[i],format=FORM[i],array=DATA(i)).array:
				VALUE.append(X)

	return VALUE

def WCS_STAT_CCD(visit,BASE,flag_show=0,flag_return=0):
	if not os.path.exists(BASE):
	        sys.exit("Could not be found fitsdata : "+BASE)
	print("BASE fits  : "+BASE)

	BASE_POS=[]
	BASE_POS.append(WCS_GET_VALUE(BASE,"GPOS_X"))
	BASE_POS.append(WCS_GET_VALUE(BASE,"GPOS_Y"))
	BASE_POS.append(WCS_GET_VALUE(BASE,"GPOS_T"))

	FITS=visit+"/solvetansip_CCDresult.fits"
	if not os.path.exists(FITS):
	        sys.exit("Could not be found fitsdata : "+FITS)
	print("visit fits : "+FITS)

	POS=[]
	POS.append(WCS_GET_VALUE(FITS,"GPOS_X"))
	POS.append(WCS_GET_VALUE(FITS,"GPOS_Y"))
	POS.append(WCS_GET_VALUE(FITS,"GPOS_T"))

	DOSX=[]
	DOSY=[]
	DOST=[]
	for i in range(104):
		DOSX.append(POS[0][i]-BASE_POS[0][i])
		DOSY.append(POS[1][i]-BASE_POS[1][i])
		DOST.append(POS[2][i]-BASE_POS[2][i])

#OUTPUT

	OUT_ID=[]
	for i in range(104):
		OUT_ID.append(i)
	OUT_COL=[]
	OUT_COL.append(Column(name="CCDID" ,format="J",array=OUT_ID))
	OUT_COL.append(Column(name="GPOS_X",format="D",array=POS[0]))
	OUT_COL.append(Column(name="GPOS_Y",format="D",array=POS[1]))
	OUT_COL.append(Column(name="GPOS_T",format="D",array=POS[2]))
	OUT_COL.append(Column(name="DGPOSBASE_X",format="D",array=DOSX))
	OUT_COL.append(Column(name="DGPOSBASE_Y",format="D",array=DOSY))
	OUT_COL.append(Column(name="DGPOSBASE_T",format="D",array=DOST))
	OUT_hdu = pyfits.new_table(OUT_COL)
	OUTNAME=visit+"/CCD.fits"
	print("OUT fits   : "+OUTNAME)
	OUT_hdu.writeto(OUTNAME,clobber=True)

#PLOT
	PLOT_TITLE="DIFF of GPOS_X from GPOS_BASE"
	PLOT_NAME=visit+"/CCD_DPOSBASE_X.png"
	PLOT.PLOT_SCAT3(POS[0][0:104],POS[1][0:104],DOSX,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_Y from GPOS_BASE"
	PLOT_NAME=visit+"/CCD_DPOSBASE_Y.png"
	PLOT.PLOT_SCAT3(POS[0][0:104],POS[1][0:104],DOSY,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_T from GPOS_BASE"
	PLOT_NAME=visit+"/CCD_DPOSBASE_T.png"
	PLOT.PLOT_SCAT3(POS[0][0:104],POS[1][0:104],DOST,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

#return
	if flag_return == 1:
		POS.append(DOSX)
		POS.append(DOSY)
		POS.append(DOST)
		return POS

def WCS_STAT_CCD_ALL(visitlist,BASE,OUT,flag_show=0):
	POSLIST=[]
	for visit in visitlist:
		POSLIST.append(WCS_STAT_CCD(str(visit),BASE,flag_return=1))

	if os.path.exists(OUT) == False:
		os.makedirs(OUT)

	POSX=[[] for i in range(104)]
	POSY=[[] for i in range(104)]
	POST=[[] for i in range(104)]
	DOSX=[[] for i in range(104)]
	DOSY=[[] for i in range(104)]
	DOST=[[] for i in range(104)]
	for v in range(len(POSLIST)):
		for CCD in range(104):
			POSX[CCD].append(POSLIST[v][0][CCD])
			POSY[CCD].append(POSLIST[v][1][CCD])
			POST[CCD].append(POSLIST[v][2][CCD])
			DOSX[CCD].append(POSLIST[v][3][CCD])
			DOSY[CCD].append(POSLIST[v][4][CCD])
			DOST[CCD].append(POSLIST[v][5][CCD])
	
#output
	OUT_ID=[]
	APOSX=[]
	APOSY=[]
	APOST=[]
	SPOSX=[]
	SPOSY=[]
	SPOST=[]
	ADOSX=[]
	ADOSY=[]
	ADOST=[]
	SDOSX=[]
	SDOSY=[]
	SDOST=[]
	for i in range(104):
		OUT_ID.append(i)
		APOSX.append(numpy.mean(POSX[i]))
		APOSY.append(numpy.mean(POSY[i]))
		APOST.append(numpy.mean(POST[i]))
		SPOSX.append(numpy.std (POSX[i]))
		SPOSY.append(numpy.std (POSY[i]))
		SPOST.append(numpy.std (POST[i]))
		ADOSX.append(numpy.mean(DOSX[i]))
		ADOSY.append(numpy.mean(DOSY[i]))
		ADOST.append(numpy.mean(DOST[i]))
		SDOSX.append(numpy.std (DOSX[i]))
		SDOSY.append(numpy.std (DOSY[i]))
		SDOST.append(numpy.std (DOST[i]))
	OUT_COL=[]
	OUT_COL.append(Column(name="CCDID" ,format="J",array=OUT_ID))
	OUT_COL.append(Column(name="GPOS_X",format="D",array=APOSX))
	OUT_COL.append(Column(name="GPOS_Y",format="D",array=APOSY))
	OUT_COL.append(Column(name="GPOS_T",format="D",array=APOST))
	OUT_COL.append(Column(name="STD_GPOS_X",format="D",array=SPOSX))
	OUT_COL.append(Column(name="STD_GPOS_Y",format="D",array=SPOSY))
	OUT_COL.append(Column(name="STD_GPOS_T",format="D",array=SPOST))
	OUT_COL.append(Column(name="DGPOSBASE_X",format="D",array=ADOSX))
	OUT_COL.append(Column(name="DGPOSBASE_Y",format="D",array=ADOSY))
	OUT_COL.append(Column(name="DGPOSBASE_T",format="D",array=ADOST))
	OUT_COL.append(Column(name="STD_DGPOSBASE_X",format="D",array=SDOSX))
	OUT_COL.append(Column(name="STD_DGPOSBASE_Y",format="D",array=SDOSY))
	OUT_COL.append(Column(name="STD_DGPOSBASE_T",format="D",array=SDOST))
	OUT_hdu = pyfits.new_table(OUT_COL)
	OUTNAME=OUT+"/CCD.fits"
	print("OUT fits   : "+OUTNAME)
	OUT_hdu.writeto(OUTNAME,clobber=True)

	OUTSTAT=OUT+"/CCD_STAT.dat"
	FOUT=open(OUTSTAT,"w")
	for i in range(104):
		print>> FOUT ,OUT_ID[i], len(visitlist), APOSX[i], APOSY[i], APOST[i], SPOSX[i], SPOSY[i], SPOST[i], ADOSX[i], ADOSY[i], ADOST[i], SDOSX[i], SDOSY[i], SDOST[i]
	print "OUT file   : "+ OUTSTAT
#plot

	PLOT_TITLE="STD of GPOS_X"
	PLOT_NAME =OUT+"/CCD_STDPOS_X.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SPOSX,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_Y"
	PLOT_NAME =OUT+"/CCD_STDPOS_Y.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SPOSY,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_T"
	PLOT_NAME =OUT+"/CCD_STDPOS_T.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SPOST,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_X from GPOS_BASE"
	PLOT_NAME =OUT+"/CCD_DPOSBASE_X.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,ADOSX,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_Y from GPOS_BASE"
	PLOT_NAME =OUT+"/CCD_DPOSBASE_Y.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,ADOSY,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="DIFF of GPOS_T from GPOS_BASE"
	PLOT_NAME =OUT+"/CCD_DPOSBASE_T.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,ADOST,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_X from GPOS_BASE"
	PLOT_NAME =OUT+"/CCD_STDBASE_X.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SDOSX,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_Y from GPOS_BASE"
	PLOT_NAME =OUT+"/CCD_STDBASE_Y.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SDOSY,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="STD of GPOS_T from GPOS_BASE"
	PLOT_NAME =OUT+"/CCD_STDBASE_T.png"
	PLOT.PLOT_SCAT3(APOSX,APOSY,SDOST,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)


	DOSXMUL=[]
	DOSYMUL=[]
	DOSTMUL=[]
	for v in range(len(POSLIST)):
		for CCD in range(104):
			DOSXMUL.append(1000*(POSLIST[v][0][CCD]-APOSX[CCD])+APOSX[CCD])
			DOSYMUL.append(1000*(POSLIST[v][1][CCD]-APOSY[CCD])+APOSY[CCD])
			DOSTMUL.append(1000*(POSLIST[v][2][CCD]-APOST[CCD])+APOST[CCD])


	PLOT_TITLE="1000*DPOS_X - 1000*DPOS_Y - 1000*DPOS_T"
	PLOT_NAME =OUT+"/CCD_SCAT.png"
	PLOT.PLOT_SCAT3(DOSXMUL,DOSYMUL,DOSTMUL,title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)


def WCS_STAT_SIPRMS(visit,flag_return=0):
	FITS=str(visit)+"/solvetansip_CCDresult.fits"
	if not os.path.exists(FITS):
	        sys.exit("Could not be found fitsdata : "+FITS)
	print("visit fits : "+FITS)

	ERMS=[]
	ERMS.append(WCS_GET_VALUE(FITS,"ERR_SIP_X_RMS")[-1])
	ERMS.append(WCS_GET_VALUE(FITS,"ERR_SIP_Y_RMS")[-1])
	ERMS.append(WCS_GET_VALUE(FITS,"ERR_PSIP_X_RMS")[-1])
	ERMS.append(WCS_GET_VALUE(FITS,"ERR_PSIP_Y_RMS")[-1])

#return
	if flag_return == 1:
		return ERMS

def WCS_STAT_SIPRMS_ALL(visitlist,OUT,flag_show=0):
#	print("visit list : "+str(visitlist))
	CCDRLIST=[]
	ERMS=[]
	for vl in visitlist:
		CCDRLIST.append(str(vl)+"/solvetansip_CCDresult.fits")
		if not os.path.exists(CCDRLIST[-1]):
		        sys.exit("Could not be found fitsdata : "+CCDRLIST[-1])
		ERMS.append(WCS_STAT_SIPRMS(vl,flag_return=1))
#	print("fits list  : "+str(CCDRLIST))

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

#PLOT
#	PLOT_TITLE="RMS_SIP_X"
#	PLOT_NAME =OUT+"/RMS_SIP_X.png"
#	PLOT.PLOT_PLOT2(visitlist,SRMS[0],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)
#	PLOT_TITLE="RMS_SIP_Y"
#	PLOT_NAME =OUT+"/RMS_SIP_Y.png"
#	PLOT.PLOT_PLOT2(visitlist,SRMS[1],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)
#	PLOT_TITLE="RMS_PSIP_X"
#	PLOT_NAME =OUT+"/RMS_PSIP_X.png"
#	PLOT.PLOT_PLOT2(visitlist,SRMS[2],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)
#	PLOT_TITLE="RMS_PSIP_Y"
#	PLOT_NAME =OUT+"/RMS_PSIP_Y.png"
#	PLOT.PLOT_PLOT2(visitlist,SRMS[3],title=PLOT_TITLE,flag_out=1,name_out=PLOT_NAME,flag_show=flag_show)

	PLOT_TITLE="RMS_SIP"
	flag_out=1
	name_out  =OUT+"/RMS_SIP.png"
	plt.title(PLOT_TITLE)
	plt.plot(visitlist,SRMS[0],'k.')
	plt.plot(visitlist,SRMS[1],'b.')
	plt.plot(visitlist,SRMS[2],'r.')
	plt.plot(visitlist,SRMS[3],'g.')
	plt.legend(["RMS SIP X","RMS SIP Y","RMS PSIP X","RMS PSIP Y"],"upper right")
	if flag_out == 1:
		plt.savefig(name_out)
	if flag_show == 1:
		plt.show()
	plt.close()


def WCS_STAT_REF(visit,flag_show=0,flag_return=0):
	FITS=visit+"/solvetansip_REFresult.fits"
	if not os.path.exists(FITS):
	        sys.exit("Could not be found fitsdata : "+FITS)
	print("visit fits : "+FITS)

	REF=[]
	REF.append(WCS_GET_VALUE(FITS,"ID"))
	REF.append(WCS_GET_VALUE(FITS,"FLAG"))
#!!!
	REF.append(WCS_GET_VALUE(FITS,"POSITION_GLOABL_X"))
#!!!
	REF.append(WCS_GET_VALUE(FITS,"POSITION_GLOABL_Y"))
#!!!
	REF.append(WCS_GET_VALUE(FITS,"POSITION_GLOABLCRPIX_X"))
#!!!
	REF.append(WCS_GET_VALUE(FITS,"POSITION_GLOABLCRPIX_Y"))
	REF.append(WCS_GET_VALUE(FITS,"POSITION_RA"))
	REF.append(WCS_GET_VALUE(FITS,"POSITION_DEC"))
	REF.append(WCS_GET_VALUE(FITS,"POSITION_DIFFSIP_X"))
	REF.append(WCS_GET_VALUE(FITS,"POSITION_DIFFSIP_Y"))
	REF.append(WCS_GET_VALUE(FITS,"POSITION_DIFFPSIP_X"))
	REF.append(WCS_GET_VALUE(FITS,"POSITION_DIFFPSIP_Y"))
	REF.append(WCS_GET_VALUE(FITS,"DIST_PSIPCONVERGENCE"))
	REF.append(WCS_GET_VALUE(FITS,"DIST_PSIPROTATION"))
	REF.append(WCS_GET_VALUE(FITS,"DIST_PSIPSHEAR1"))
	REF.append(WCS_GET_VALUE(FITS,"DIST_PSIPSHEAR2"))
	REF.append(WCS_GET_VALUE(FITS,"DIST_PSIPMAGNIFICATION"))
	REF.append(WCS_GET_VALUE(FITS,"DIST_PSIPJACOBIAN"))
	
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

def WCS_STAT_REF_ALL(visitlist,flag_show=0):
	for visit in visitlist:
		WCS_STAT_REF(str(visit),flag_show=flag_show)


def WCS_CUT_DIST(name=""):
	FIN=open(name,"r")
	vv=[]
	for v in FIN:
		vv.append(v[:-1].split(" "))

	Fout=open(name,"w")
	for B in range(len(vv)):
		if float(vv[B][0])*float(vv[B][0])+float(vv[B][1])*float(vv[B][1]) < 17501*17501:
			print>>Fout, vv[B][0],vv[B][1],vv[B][2],vv[B][3]


def WCS_READ_DIST(name=""):
	FIN=open(name,"r")
	vv=[]
	for v in FIN:
		vv.append(v[:-1].split(" "))
#		print vv[-1]

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

def WCS_MAKE_DIST(visit,BASE):
	BASE_DIST=WCS_READ_DIST(name=BASE)

	FITS=str(visit)+"/solvetansip_CCDresult.fits"
	if not os.path.exists(FITS):
	        sys.exit("Could not be found fitsdata : "+FITS)
	print("visit fits : "+FITS)

	CD=[]
	CD.append(WCS_GET_VALUE(FITS,"CD1_1")[-1])
	CD.append(WCS_GET_VALUE(FITS,"CD1_2")[-1])
	CD.append(WCS_GET_VALUE(FITS,"CD2_1")[-1])
	CD.append(WCS_GET_VALUE(FITS,"CD2_2")[-1])
	OSA =0
	OSB =0
	OPA =0
	OPB =0
	OSA=WCS_GET_VALUE(FITS,"ORDER_SIP_A")[-1]
	OSB=WCS_GET_VALUE(FITS,"ORDER_SIP_B")[-1]
	OPA=WCS_GET_VALUE(FITS,"ORDER_PSIP_A")[-1]
	OPB=WCS_GET_VALUE(FITS,"ORDER_PSIP_B")[-1]
	SIPA=[]
	SIPB=[]
	PIPA=[]
	PIPB=[]
	for j in range(int(0.5*(OSA+1)*(OSA+2)+0.5)):
		KEY="SIP_A_"+str(j)
		SIPA.append(WCS_GET_VALUE(FITS,KEY)[-1])
	SIPA[1*OSA+1]+=1
	for j in range(int(0.5*(OSB+1)*(OSB+2)+0.5)):
		KEY="SIP_B_"+str(j)
		SIPB.append(WCS_GET_VALUE(FITS,KEY)[-1])
	SIPB[0*OSB+1]+=1
	for j in range(int(0.5*(OPA+1)*(OPA+2)+0.5)):
		KEY="PSIP_A_"+str(j)
		PIPA.append(WCS_GET_VALUE(FITS,KEY)[-1])
	PIPA[1*OPA+1]+=1
	for j in range(int(0.5*(OPB+1)*(OPB+2)+0.5)):
		KEY="PSIP_B_"+str(j)
		PIPB.append(WCS_GET_VALUE(FITS,KEY)[-1])
	PIPB[0*OPB+1]+=1

#	print CD[0],CD[1]
#	print CD[2],CD[3]
#	print -CD[0],CD[1]
#	print -CD[2],CD[3]
#	THETA = numpy.arctan((-CD[1]-CD[2])/(-CD[0]+CD[3]))
	THETA = numpy.arctan2((-CD[1]-CD[2]),(-CD[0]+CD[3]))
	print "THETA : "+str(THETA)
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

def WCS_MAKE_DIST_ALL(visitlist,BASE):
	for vl in visitlist:
		WCS_MAKE_DIST(vl,BASE)

def WCS_STAT_DIST(visit,BASE,flag_show=0,flag_return=0):
	BASE_DIST=WCS_READ_DIST(name=BASE)
	DIST=WCS_READ_DIST(name=str(visit)+"/DIST.dat")

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
	

def WCS_STAT_DIST_ALL(visitlist,BASE,OUT,flag_show=0):
	DLIST=[]
	for vl in visitlist:
		DLIST.append(WCS_STAT_DIST(vl,BASE,flag_show=0,flag_return=1))

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







def WCS_STAT_CCDPOSITIONS_BASE(OUTPUT):
	DATA_ID=[]
	for i in range(104):
		DATA_ID.append(i)
	DATA_ID.append(999)
	DATA_GPOSX=[]
	DATA_GPOSY=[]
	DATA_GPOST=[]

	DATA_GPOSX.append( 1.383708e+04)
	DATA_GPOSY.append(-8.877289e+03)
	DATA_GPOST.append( 7.469120e-05)
	DATA_GPOSX.append( 1.383725e+04)
	DATA_GPOSY.append(-4.398709e+03)
	DATA_GPOST.append(-1.665659e-05)
	DATA_GPOSX.append( 1.383761e+04)
	DATA_GPOSY.append( 7.613413e+01)
	DATA_GPOST.append( 1.735006e-04)
	DATA_GPOSX.append( 1.383690e+04)
	DATA_GPOSY.append( 4.553658e+03)
	DATA_GPOST.append(-1.144805e-04)
	DATA_GPOSX.append( 1.171252e+04)
	DATA_GPOSY.append(-1.335221e+04)
	DATA_GPOST.append( 1.039587e-04)
	DATA_GPOSX.append( 1.171310e+04)
	DATA_GPOSY.append(-8.875903e+03)
	DATA_GPOST.append(-3.420824e-04)
	DATA_GPOSX.append( 1.171360e+04)
	DATA_GPOSY.append(-4.399590e+03)
	DATA_GPOST.append(-4.923060e-04)
	DATA_GPOSX.append( 1.171674e+04)
	DATA_GPOSY.append( 7.493897e+01)
	DATA_GPOST.append( 6.835955e-04)
	DATA_GPOSX.append( 1.171440e+04)
	DATA_GPOSY.append( 4.554133e+03)
	DATA_GPOST.append(-4.340825e-04)
	DATA_GPOSX.append( 1.171400e+04)
	DATA_GPOSY.append( 9.029680e+03)
	DATA_GPOST.append(-7.389672e-04)
	DATA_GPOSX.append( 9.590272e+03)
	DATA_GPOSY.append(-1.335146e+04)
	DATA_GPOST.append(-5.760984e-05)
	DATA_GPOSX.append( 9.592058e+03)
	DATA_GPOSY.append(-8.877147e+03)
	DATA_GPOST.append( 7.082408e-04)
	DATA_GPOSX.append( 9.590159e+03)
	DATA_GPOSY.append(-4.395633e+03)
	DATA_GPOST.append(-5.876495e-04)
	DATA_GPOSX.append( 9.589547e+03)
	DATA_GPOSY.append( 7.677580e+01)
	DATA_GPOST.append(-4.771578e-04)
	DATA_GPOSX.append( 9.593906e+03)
	DATA_GPOSY.append( 4.552253e+03)
	DATA_GPOST.append( 5.834373e-04)
	DATA_GPOSX.append( 9.591435e+03)
	DATA_GPOSY.append( 9.029410e+03)
	DATA_GPOST.append(-2.777713e-04)
	DATA_GPOSX.append( 7.465367e+03)
	DATA_GPOSY.append(-1.312957e+04)
	DATA_GPOST.append(-3.123849e-04)
	DATA_GPOSX.append( 7.466197e+03)
	DATA_GPOSY.append(-8.649940e+03)
	DATA_GPOST.append(-3.672525e-04)
	DATA_GPOSX.append( 7.467331e+03)
	DATA_GPOSY.append(-4.175578e+03)
	DATA_GPOST.append(-1.974577e-04)
	DATA_GPOSX.append( 7.468639e+03)
	DATA_GPOSY.append( 7.578869e+01)
	DATA_GPOST.append( 2.371703e-04)
	DATA_GPOSX.append( 7.466856e+03)
	DATA_GPOSY.append( 4.553582e+03)
	DATA_GPOST.append(-1.322223e-04)
	DATA_GPOSX.append( 7.471416e+03)
	DATA_GPOSY.append( 9.026630e+03)
	DATA_GPOST.append( 1.081670e-03)
	DATA_GPOSX.append( 5.341743e+03)
	DATA_GPOSY.append(-1.760145e+04)
	DATA_GPOST.append(-7.541164e-05)
	DATA_GPOSX.append( 5.345727e+03)
	DATA_GPOSY.append(-1.312672e+04)
	DATA_GPOST.append( 3.835604e-04)
	DATA_GPOSX.append( 5.346052e+03)
	DATA_GPOSY.append(-8.650196e+03)
	DATA_GPOST.append( 5.322733e-04)
	DATA_GPOSX.append( 5.345029e+03)
	DATA_GPOSY.append(-4.172566e+03)
	DATA_GPOST.append( 3.251958e-04)
	DATA_GPOSX.append( 5.345543e+03)
	DATA_GPOSY.append( 7.559653e+01)
	DATA_GPOST.append(-1.868312e-04)
	DATA_GPOSX.append( 5.346544e+03)
	DATA_GPOSY.append( 4.553207e+03)
	DATA_GPOST.append( 2.946728e-04)
	DATA_GPOSX.append( 5.349215e+03)
	DATA_GPOSY.append( 9.027948e+03)
	DATA_GPOST.append( 8.433430e-04)
	DATA_GPOSX.append( 5.344581e+03)
	DATA_GPOSY.append( 1.350583e+04)
	DATA_GPOST.append(-1.318643e-04)
	DATA_GPOSX.append( 3.221906e+03)
	DATA_GPOSY.append(-1.760181e+04)
	DATA_GPOST.append( 3.511800e-04)
	DATA_GPOSX.append( 3.219724e+03)
	DATA_GPOSY.append(-1.312782e+04)
	DATA_GPOST.append(-4.412036e-04)
	DATA_GPOSX.append( 3.219289e+03)
	DATA_GPOSY.append(-8.651098e+03)
	DATA_GPOST.append( 1.390213e-04)
	DATA_GPOSX.append( 3.223594e+03)
	DATA_GPOSY.append(-4.174098e+03)
	DATA_GPOST.append( 5.160676e-04)
	DATA_GPOSX.append( 3.222040e+03)
	DATA_GPOSY.append( 7.565137e+01)
	DATA_GPOST.append(-1.498324e-04)
	DATA_GPOSX.append( 3.220970e+03)
	DATA_GPOSY.append( 4.553103e+03)
	DATA_GPOST.append(-3.111269e-04)
	DATA_GPOSX.append( 3.223171e+03)
	DATA_GPOSY.append( 9.027935e+03)
	DATA_GPOST.append( 5.129104e-06)
	DATA_GPOSX.append( 3.221836e+03)
	DATA_GPOSY.append( 1.350611e+04)
	DATA_GPOST.append(-1.861300e-04)
	DATA_GPOSX.append( 1.098033e+03)
	DATA_GPOSY.append(-1.760188e+04)
	DATA_GPOST.append(-5.070104e-06)
	DATA_GPOSX.append( 1.095635e+03)
	DATA_GPOSY.append(-1.312539e+04)
	DATA_GPOST.append(-4.703346e-04)
	DATA_GPOSX.append( 1.097781e+03)
	DATA_GPOSY.append(-8.649973e+03)
	DATA_GPOST.append(-1.584045e-04)
	DATA_GPOSX.append( 1.099015e+03)
	DATA_GPOSY.append(-4.171937e+03)
	DATA_GPOST.append( 1.386608e-04)
	DATA_GPOSX.append( 1.101345e+03)
	DATA_GPOSY.append( 7.609064e+01)
	DATA_GPOST.append( 2.757609e-04)
	DATA_GPOSX.append( 1.099677e+03)
	DATA_GPOSY.append( 4.553509e+03)
	DATA_GPOST.append( 4.620884e-04)
	DATA_GPOSX.append( 1.100324e+03)
	DATA_GPOSY.append( 9.030397e+03)
	DATA_GPOST.append( 2.144049e-04)
	DATA_GPOSX.append( 1.099586e+03)
	DATA_GPOSY.append( 1.350562e+04)
	DATA_GPOST.append( 1.243761e-04)
	DATA_GPOSX.append(-1.025622e+03)
	DATA_GPOSY.append(-1.760240e+04)
	DATA_GPOST.append(-1.225479e-04)
	DATA_GPOSX.append(-1.026982e+03)
	DATA_GPOSY.append(-1.312612e+04)
	DATA_GPOST.append( 1.246569e-04)
	DATA_GPOSX.append(-1.024658e+03)
	DATA_GPOSY.append(-8.650647e+03)
	DATA_GPOST.append(-6.138172e-05)
	DATA_GPOSX.append(-1.023720e+03)
	DATA_GPOSY.append(-4.173763e+03)
	DATA_GPOST.append( 1.279247e-04)
	DATA_GPOSX.append(-1.023302e+03)
	DATA_GPOSY.append( 7.748179e+01)
	DATA_GPOST.append( 8.989901e-04)
	DATA_GPOSX.append(-1.021703e+03)
	DATA_GPOSY.append( 4.552678e+03)
	DATA_GPOST.append( 9.342271e-04)
	DATA_GPOSX.append(-1.024151e+03)
	DATA_GPOSY.append( 9.031731e+03)
	DATA_GPOST.append(-3.044300e-04)
	DATA_GPOSX.append(-1.022769e+03)
	DATA_GPOSY.append( 1.350502e+04)
	DATA_GPOST.append( 1.719886e-04)
	DATA_GPOSX.append(-3.148058e+03)
	DATA_GPOSY.append(-1.760302e+04)
	DATA_GPOST.append(-3.529640e-04)
	DATA_GPOSX.append(-3.149016e+03)
	DATA_GPOSY.append(-1.312559e+04)
	DATA_GPOST.append(-5.494005e-04)
	DATA_GPOSX.append(-3.146674e+03)
	DATA_GPOSY.append(-8.648984e+03)
	DATA_GPOST.append( 1.976112e-05)
	DATA_GPOSX.append(-3.147826e+03)
	DATA_GPOSY.append(-4.174794e+03)
	DATA_GPOST.append(-6.041518e-04)
	DATA_GPOSX.append(-3.145869e+03)
	DATA_GPOSY.append( 7.664209e+01)
	DATA_GPOST.append( 9.691851e-05)
	DATA_GPOSX.append(-3.145573e+03)
	DATA_GPOSY.append( 4.554566e+03)
	DATA_GPOST.append(-2.873973e-05)
	DATA_GPOSX.append(-3.143818e+03)
	DATA_GPOSY.append( 9.030648e+03)
	DATA_GPOST.append( 4.373105e-05)
	DATA_GPOSX.append(-3.145767e+03)
	DATA_GPOSY.append( 1.350623e+04)
	DATA_GPOST.append( 1.547509e-04)
	DATA_GPOSX.append(-5.269144e+03)
	DATA_GPOSY.append(-1.760247e+04)
	DATA_GPOST.append( 2.673054e-04)
	DATA_GPOSX.append(-5.271683e+03)
	DATA_GPOSY.append(-1.312623e+04)
	DATA_GPOST.append(-1.448919e-05)
	DATA_GPOSX.append(-5.271112e+03)
	DATA_GPOSY.append(-8.648356e+03)
	DATA_GPOST.append(-2.587416e-04)
	DATA_GPOSX.append(-5.269933e+03)
	DATA_GPOSY.append(-4.172770e+03)
	DATA_GPOST.append(-1.756895e-04)
	DATA_GPOSX.append(-5.268823e+03)
	DATA_GPOSY.append( 7.729688e+01)
	DATA_GPOST.append( 2.153425e-05)
	DATA_GPOSX.append(-5.268552e+03)
	DATA_GPOSY.append( 4.555698e+03)
	DATA_GPOST.append(-1.449532e-04)
	DATA_GPOSX.append(-5.268477e+03)
	DATA_GPOSY.append( 9.029264e+03)
	DATA_GPOST.append( 1.572254e-04)
	DATA_GPOSX.append(-5.267977e+03)
	DATA_GPOSY.append( 1.350640e+04)
	DATA_GPOST.append(-3.912938e-04)
	DATA_GPOSX.append(-7.397222e+03)
	DATA_GPOSY.append(-1.760097e+04)
	DATA_GPOST.append(-1.082959e-03)
	DATA_GPOSX.append(-7.393967e+03)
	DATA_GPOSY.append(-1.312590e+04)
	DATA_GPOST.append( 6.438946e-06)
	DATA_GPOSX.append(-7.392159e+03)
	DATA_GPOSY.append(-8.648994e+03)
	DATA_GPOST.append( 4.045629e-05)
	DATA_GPOSX.append(-7.395083e+03)
	DATA_GPOSY.append(-4.174520e+03)
	DATA_GPOST.append( 1.736262e-04)
	DATA_GPOSX.append(-7.391540e+03)
	DATA_GPOSY.append( 7.812277e+01)
	DATA_GPOST.append( 1.490976e-04)
	DATA_GPOSX.append(-7.392010e+03)
	DATA_GPOSY.append( 4.555557e+03)
	DATA_GPOST.append( 3.881749e-05)
	DATA_GPOSX.append(-7.392879e+03)
	DATA_GPOSY.append( 9.031991e+03)
	DATA_GPOST.append(-4.336736e-04)
	DATA_GPOSX.append(-7.391362e+03)
	DATA_GPOSY.append( 1.350672e+04)
	DATA_GPOST.append( 4.134590e-05)
	DATA_GPOSX.append(-9.514694e+03)
	DATA_GPOSY.append(-1.312812e+04)
	DATA_GPOST.append( 6.998628e-04)
	DATA_GPOSX.append(-9.515390e+03)
	DATA_GPOSY.append(-8.647940e+03)
	DATA_GPOST.append( 3.412708e-04)
	DATA_GPOSX.append(-9.515610e+03)
	DATA_GPOSY.append(-4.172081e+03)
	DATA_GPOST.append(-1.098505e-04)
	DATA_GPOSX.append(-9.516593e+03)
	DATA_GPOSY.append( 8.035702e+01)
	DATA_GPOST.append(-4.349314e-06)
	DATA_GPOSX.append(-9.515897e+03)
	DATA_GPOSY.append( 4.553949e+03)
	DATA_GPOST.append( 3.251606e-04)
	DATA_GPOSX.append(-9.514914e+03)
	DATA_GPOSY.append( 9.030146e+03)
	DATA_GPOST.append( 1.356535e-04)
	DATA_GPOSX.append(-1.163841e+04)
	DATA_GPOSY.append(-1.312558e+04)
	DATA_GPOST.append( 6.704231e-04)
	DATA_GPOSX.append(-1.163865e+04)
	DATA_GPOSY.append(-8.649008e+03)
	DATA_GPOST.append( 2.038970e-04)
	DATA_GPOSX.append(-1.163967e+04)
	DATA_GPOSY.append(-4.170497e+03)
	DATA_GPOST.append(-2.859758e-05)
	DATA_GPOSX.append(-1.164199e+04)
	DATA_GPOSY.append( 3.017337e+02)
	DATA_GPOST.append(-6.376717e-04)
	DATA_GPOSX.append(-1.164010e+04)
	DATA_GPOSY.append( 4.780126e+03)
	DATA_GPOST.append(-4.552432e-04)
	DATA_GPOSX.append(-1.163850e+04)
	DATA_GPOSY.append( 9.255758e+03)
	DATA_GPOST.append(-2.390071e-04)
	DATA_GPOSX.append(-1.376189e+04)
	DATA_GPOSY.append(-1.312350e+04)
	DATA_GPOST.append( 7.863410e-05)
	DATA_GPOSX.append(-1.376251e+04)
	DATA_GPOSY.append(-8.648981e+03)
	DATA_GPOST.append( 5.826972e-04)
	DATA_GPOSX.append(-1.376175e+04)
	DATA_GPOSY.append(-4.171333e+03)
	DATA_GPOST.append( 1.706390e-05)
	DATA_GPOSX.append(-1.376382e+04)
	DATA_GPOSY.append( 3.035985e+02)
	DATA_GPOST.append(-4.476174e-04)
	DATA_GPOSX.append(-1.376114e+04)
	DATA_GPOSY.append( 4.781697e+03)
	DATA_GPOST.append(-1.008064e-04)
	DATA_GPOSX.append(-1.376072e+04)
	DATA_GPOSY.append( 9.256264e+03)
	DATA_GPOST.append(-1.063618e-04)
	DATA_GPOSX.append(-1.588560e+04)
	DATA_GPOSY.append(-8.649364e+03)
	DATA_GPOST.append( 2.716953e-05)
	DATA_GPOSX.append(-1.588573e+04)
	DATA_GPOSY.append(-4.171300e+03)
	DATA_GPOST.append( 2.226470e-05)
	DATA_GPOSX.append(-1.588699e+04)
	DATA_GPOSY.append( 3.049669e+02)
	DATA_GPOST.append(-7.377701e-04)
	DATA_GPOSX.append(-1.588674e+04)
	DATA_GPOSY.append( 4.782615e+03)
	DATA_GPOST.append(-7.679112e-04)
	DATA_GPOSX.append( 7.500256e+03)
	DATA_GPOSY.append(-1.547316e+04)
	DATA_GPOST.append(-1.965054e-04)
	DATA_GPOSX.append( 7.503732e+03)
	DATA_GPOSY.append( 1.350627e+04)
	DATA_GPOST.append(-1.154499e-05)
	DATA_GPOSX.append(-1.167984e+04)
	DATA_GPOSY.append(-1.547421e+04)
	DATA_GPOST.append( 5.178032e-04)
	DATA_GPOSX.append(-1.167618e+04)
	DATA_GPOSY.append( 1.350529e+04)
	DATA_GPOST.append( 3.193213e-04)
	DATA_GPOSX.append( 0.000000e+00)
	DATA_GPOSY.append( 0.000000e+00)
	DATA_GPOST.append( 0.000000e-00)

	COL=[]
	COL.append(Column(name="CCDID" ,format="J",array=DATA_ID))
	COL.append(Column(name="GPOS_X",format="D",array=DATA_GPOSX))
	COL.append(Column(name="GPOS_Y",format="D",array=DATA_GPOSY))
	COL.append(Column(name="GPOS_T",format="D",array=DATA_GPOST))

	hdu = pyfits.new_table(COL)
	hdu.writeto(OUTPUT,clobber=True)

