#!/usr/bin/env python
#--------------------------------------------------
#PLOT.py
#
#Last Update 2013/11/01
#Yuki Okura : yuki.okura@nao.ac.jp
#--------------------------------------------------

import os, sys
import os.path
import numpy
import math 
import matplotlib.pyplot as plt
import matplotlib.cm as cm

def PLOT_PLOT2(v1,v2,title="",flag_out=0,name_out="output.png",flag_show=0):
	if not len(v1) == len (v2):
		print("v1 and v2 have different length")
		return
	plt.title(title)
	plt.plot(v1,v2,'k.')
	if flag_out == 1:
		plt.savefig(name_out)
	if flag_show == 1:
		plt.show()
	plt.close()


def PLOT_SCAT3(v1,v2,v3,title="",flag_out=0,name_out="output.png",flag_show=0):
	if not len(v1) == len (v2):
		print("v1 and v2 have different length")
		return
	if not len(v1) == len (v3):
		print("v1 and v3 have different length")
		return
	plt.title(title)
	DATA=plt.scatter(v1,v2,c=v3)
	plt.colorbar(DATA)
	if flag_out == 1:
		plt.savefig(name_out)
	if flag_show == 1:
		plt.show()
	plt.close()

def PLOT_E(v1,v2,v3,v4,scale,title="",flag_out=0,name_out="output.png",flag_show=0):
	if not len(v1) == len (v2):
		print("v1 and v2 have different length")
		return
	if not len(v1) == len (v3):
		print("v1 and v3 have different length")
		return
	if not len(v1) == len (v4):
		print("v1 and v4 have different length")
		return
	E1 = []
	E2 = []
	for i in range(len(v1)):
		E=math.hypot(v3[i],v4[i])
		T=math.atan2(v4[i],v3[i])
		E1.append( E*math.cos(0.5*T))
		E2.append( E*math.sin(0.5*T))

	plt.title(title)
	A=plt.quiver(v1,v2,E1,E2,scale=(float)(scale),width=0.005,headwidth=0,pivot='middle')
	plt.quiverkey(A,0.95,0.95,0.1,"0.1")
	plt.axis('scaled')
	if flag_out == 1:
		plt.savefig(name_out)
	if flag_show == 1:
		plt.show()
	plt.close()

