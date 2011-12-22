#!/usr/bin/env python

import os
import os.path
import sys
import numpy

import lsst.pipette.readwrite as pipReadWrite
import lsst.pex.policy as pexPolicy
import lsst.obs.hscSim as hscSim
import lsst.obs.suprimecam as scmapper

import hsc.meas.tansip.doTansip as doTansip
#import hsc.meas.tansip.WCS_PL_MAIN       as hscTansip
import lsst.afw.detection as afwDet
import lsst.afw.geom as afwGeom
import lsst.afw.image as afwImage
import lsst.afw.coord as afwCoord
import lsst.pipette.plotter as pipPlot

#WCS_POSITION.F_WCS_POSITION_TEST()

print sys.argv
print sys.argv[1]
matches_address = sys.argv[1]
mapper = scmapper.SuprimecamMapper(rerun="fh-dc2.9c-default") 

#plot = pipPlot.Plotter('wcs')
#mapper = scmapper.SuprimecamMapper(rerun="fh-dc2.9c-default") 
#io = pipReadWrite.ReadWrite(mapper, ['visit'], fileKeys=['visit', 'ccd'])
#data = {'visit': 126929}#929-941-

CNUMBER = 0
ANGLE=0

policyPath = os.path.join(os.getenv("SOLVETANSIP_DIR"), "policy", "WCS_MAKEAPROP.paf")
policy = pexPolicy.Policy.createPolicy(policyPath)

#policy.set("LSIPORDER", 1)
#policy.set("SIPORDER", 6)
metadata = doTansip.F_WCS_EMPTYMETADATA()

#wcsList = doTansip.doTansip(matches, policy=policy, camera=mapper.camera)
WCSA_ASP = doTansip.getresultWcs_local(matches_address, metadata, policy=policy, camera=mapper.camera)

#-----------------------------------------------------------------
#Getting Functions : WCS : REFERENCES
#-----------------------------------------------------------------
print "--- getting function : references ---"
#ALLrefinfo_ID = doTansip.WCS_GET_REFERENCE_ALL_ID(WCSA_ASP)
#print ALLrefinfo_ID
#ALLrefinfo_CHIPID = doTansip.WCS_GET_REFERENCE_ALL_CHIPID(WCSA_ASP)
#print ALLrefinfo_CHIPID
#ALLrefinfo_FLAG = doTansip.WCS_GET_REFERENCE_ALL_FLAG(WCSA_ASP)
#print ALLrefinfo_FLAG
#ALLrefinfo_XY_LOCAL = doTansip.WCS_GET_REFERENCE_ALL_XY_LOCAL(WCSA_ASP)
#print ALLrefinfo_XY_LOCAL
#ALLrefinfo_XY_RADEC = doTansip.WCS_GET_REFERENCE_ALL_XY_RADEC(WCSA_ASP)
#print ALLrefinfo_XY_RADEC
#ALLrefinfo_XY_GLOBAL = doTansip.WCS_GET_REFERENCE_ALL_XY_GLOBAL(WCSA_ASP)
#print ALLrefinfo_XY_GLOBAL
#ALLrefinfo_XY_GLOBALCRPIX = doTansip.WCS_GET_REFERENCE_ALL_XY_GLOBALCRPIX(WCSA_ASP)
#print ALLrefinfo_XY_GLOBALCRPIX
#ALLrefinfo_XY_LOCALCRPIX = doTansip.WCS_GET_REFERENCE_ALL_XY_LOCALCRPIX(WCSA_ASP)
#print ALLrefinfo_XY_LOCALCRPIX
#ALLrefinfo_XY_IMPIXEL = doTansip.WCS_GET_REFERENCE_ALL_XY_IMPIXEL(WCSA_ASP)
#print ALLrefinfo_XY_IMPIXEL
#ALLrefinfo_XY_IMWORLD = doTansip.WCS_GET_REFERENCE_ALL_XY_IMWORLD(WCSA_ASP)
#print ALLrefinfo_XY_IMWORLD
#ALLrefinfo_CAMERA_CONVERGENCE = doTansip.WCS_GET_REFERENCE_ALL_CAMERA_CONVERGENCE(WCSA_ASP)
#print ALLrefinfo_CAMERA_CONVERGENCE
#ALLrefinfo_CAMERA_ROTATION = doTansip.WCS_GET_REFERENCE_ALL_CAMERA_ROTATION(WCSA_ASP)
#print ALLrefinfo_CAMERA_ROTATION
#ALLrefinfo_CAMERA_SHEAR1 = doTansip.WCS_GET_REFERENCE_ALL_CAMERA_SHEAR1(WCSA_ASP)
#print ALLrefinfo_CAMERA_SHEAR1
#ALLrefinfo_CAMERA_SHEAR2 = doTansip.WCS_GET_REFERENCE_ALL_CAMERA_SHEAR2(WCSA_ASP)
#print ALLrefinfo_CAMERA_SHEAR2
#ALLrefinfo_CAMERA_MAGNIFICATION = doTansip.WCS_GET_REFERENCE_ALL_CAMERA_MAGNIFICATION(WCSA_ASP)
#print ALLrefinfo_CAMERA_MAGNIFICATION
#ALLrefinfo_CAMERA_PCONVERGENCE = doTansip.WCS_GET_REFERENCE_ALL_CAMERA_PCONVERGENCE(WCSA_ASP)
#print ALLrefinfo_CAMERA_PCONVERGENCE
#ALLrefinfo_CAMERA_PROTATION = doTansip.WCS_GET_REFERENCE_ALL_CAMERA_ROTATION(WCSA_ASP)
#print ALLrefinfo_CAMERA_PROTATION
#ALLrefinfo_CAMERA_PSHEAR1 = doTansip.WCS_GET_REFERENCE_ALL_CAMERA_PSHEAR1(WCSA_ASP)
#print ALLrefinfo_CAMERA_PSHEAR1
#ALLrefinfo_CAMERA_PSHEAR2 = doTansip.WCS_GET_REFERENCE_ALL_CAMERA_PSHEAR2(WCSA_ASP)
#print ALLrefinfo_CAMERA_PSHEAR2
#ALLrefinfo_CAMERA_PMAGNIFICATION = doTansip.WCS_GET_REFERENCE_ALL_CAMERA_PMAGNIFICATION(WCSA_ASP)
#print ALLrefinfo_CAMERA_PMAGNIFICATION

print "--- getting function : references : ID ---"
CCDrefinfo_ID = doTansip.WCS_GET_REFERENCE_CCD_ID(WCSA_ASP,0)
print CCDrefinfo_ID[0]
print CCDrefinfo_ID[1]
print CCDrefinfo_ID[2]
print CCDrefinfo_ID[3]
print CCDrefinfo_ID[4]
print "--- getting function : references : CHIPID ---"
CCDrefinfo_CHIPID = doTansip.WCS_GET_REFERENCE_CCD_CHIPID(WCSA_ASP,0)
print CCDrefinfo_CHIPID[0]
print CCDrefinfo_CHIPID[1]
print CCDrefinfo_CHIPID[2]
print CCDrefinfo_CHIPID[3]
print CCDrefinfo_CHIPID[4]
print "--- getting function : references : FLAG ---"
CCDrefinfo_FLAG = doTansip.WCS_GET_REFERENCE_CCD_FLAG(WCSA_ASP,0)
print CCDrefinfo_FLAG[0]
print CCDrefinfo_FLAG[1]
print CCDrefinfo_FLAG[2]
print CCDrefinfo_FLAG[3]
print CCDrefinfo_FLAG[4]
print "--- getting function : references : XY_LOCAL ---"
CCDrefinfo_XY_LOCAL = doTansip.WCS_GET_REFERENCE_CCD_XY_LOCAL(WCSA_ASP,0)
print CCDrefinfo_XY_LOCAL[0]
print CCDrefinfo_XY_LOCAL[1]
print CCDrefinfo_XY_LOCAL[2]
print CCDrefinfo_XY_LOCAL[3]
print CCDrefinfo_XY_LOCAL[4]
print "--- getting function : references : XY_RADEC ---"
CCDrefinfo_XY_RADEC = doTansip.WCS_GET_REFERENCE_CCD_XY_RADEC(WCSA_ASP,0)
print CCDrefinfo_XY_RADEC[0]
print CCDrefinfo_XY_RADEC[1]
print CCDrefinfo_XY_RADEC[2]
print CCDrefinfo_XY_RADEC[3]
print CCDrefinfo_XY_RADEC[4]
print "--- getting function : references : XY_GLOBAL ---"
CCDrefinfo_XY_GLOBAL = doTansip.WCS_GET_REFERENCE_CCD_XY_GLOBAL(WCSA_ASP,0)
print CCDrefinfo_XY_GLOBAL[0]
print CCDrefinfo_XY_GLOBAL[1]
print CCDrefinfo_XY_GLOBAL[2]
print CCDrefinfo_XY_GLOBAL[3]
print CCDrefinfo_XY_GLOBAL[4]
print "--- getting function : references : XY_GLOBALCRPIX ---"
CCDrefinfo_XY_GLOBALCRPIX = doTansip.WCS_GET_REFERENCE_CCD_XY_GLOBALCRPIX(WCSA_ASP,0)
print CCDrefinfo_XY_GLOBALCRPIX[0]
print CCDrefinfo_XY_GLOBALCRPIX[1]
print CCDrefinfo_XY_GLOBALCRPIX[2]
print CCDrefinfo_XY_GLOBALCRPIX[3]
print CCDrefinfo_XY_GLOBALCRPIX[4]
print "--- getting function : references : XY_LOCALCRPIX ---"
CCDrefinfo_XY_LOCALCRPIX = doTansip.WCS_GET_REFERENCE_CCD_XY_LOCALCRPIX(WCSA_ASP,0)
print CCDrefinfo_XY_LOCALCRPIX[0]
print CCDrefinfo_XY_LOCALCRPIX[1]
print CCDrefinfo_XY_LOCALCRPIX[2]
print CCDrefinfo_XY_LOCALCRPIX[3]
print CCDrefinfo_XY_LOCALCRPIX[4]
print "--- getting function : references : XY_IMPIXEL ---"
CCDrefinfo_XY_IMPIXEL = doTansip.WCS_GET_REFERENCE_CCD_XY_IMPIXEL(WCSA_ASP,0)
print CCDrefinfo_XY_IMPIXEL[0]
print CCDrefinfo_XY_IMPIXEL[1]
print CCDrefinfo_XY_IMPIXEL[2]
print CCDrefinfo_XY_IMPIXEL[3]
print CCDrefinfo_XY_IMPIXEL[4]
print "--- getting function : references : XY_IMWORLD ---"
CCDrefinfo_XY_IMWORLD = doTansip.WCS_GET_REFERENCE_CCD_XY_IMWORLD(WCSA_ASP,0)
print CCDrefinfo_XY_IMWORLD[0]
print CCDrefinfo_XY_IMWORLD[1]
print CCDrefinfo_XY_IMWORLD[2]
print CCDrefinfo_XY_IMWORLD[3]
print CCDrefinfo_XY_IMWORLD[4]
print "--- getting function : references : CONVERGENCE ---"
CCDrefinfo_CAMERA_CONVERGENCE = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_CONVERGENCE(WCSA_ASP,0)
print CCDrefinfo_CAMERA_CONVERGENCE[0]
print CCDrefinfo_CAMERA_CONVERGENCE[1]
print CCDrefinfo_CAMERA_CONVERGENCE[2]
print CCDrefinfo_CAMERA_CONVERGENCE[3]
print CCDrefinfo_CAMERA_CONVERGENCE[4]
print "--- getting function : references : ROTATION ---"
CCDrefinfo_CAMERA_ROTATION = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_ROTATION(WCSA_ASP,0)
print CCDrefinfo_CAMERA_ROTATION[0]
print CCDrefinfo_CAMERA_ROTATION[1]
print CCDrefinfo_CAMERA_ROTATION[2]
print CCDrefinfo_CAMERA_ROTATION[3]
print CCDrefinfo_CAMERA_ROTATION[4]
print "--- getting function : references : SHEAR1 ---"
CCDrefinfo_CAMERA_SHEAR1 = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_SHEAR1(WCSA_ASP,0)
print CCDrefinfo_CAMERA_SHEAR1[0]
print CCDrefinfo_CAMERA_SHEAR1[1]
print CCDrefinfo_CAMERA_SHEAR1[2]
print CCDrefinfo_CAMERA_SHEAR1[3]
print CCDrefinfo_CAMERA_SHEAR1[4]
print "--- getting function : references : SHEAR2 ---"
CCDrefinfo_CAMERA_SHEAR2 = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_SHEAR2(WCSA_ASP,0)
print CCDrefinfo_CAMERA_SHEAR2[0]
print CCDrefinfo_CAMERA_SHEAR2[1]
print CCDrefinfo_CAMERA_SHEAR2[2]
print CCDrefinfo_CAMERA_SHEAR2[3]
print CCDrefinfo_CAMERA_SHEAR2[4]
print "--- getting function : references : MAGNIFICATION ---"
CCDrefinfo_CAMERA_MAGNIFICATION = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_MAGNIFICATION(WCSA_ASP,0)
print CCDrefinfo_CAMERA_MAGNIFICATION[0]
print CCDrefinfo_CAMERA_MAGNIFICATION[1]
print CCDrefinfo_CAMERA_MAGNIFICATION[2]
print CCDrefinfo_CAMERA_MAGNIFICATION[3]
print CCDrefinfo_CAMERA_MAGNIFICATION[4]
print "--- getting function : references : PCONVERGENCE ---"
CCDrefinfo_CAMERA_PCONVERGENCE = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_PCONVERGENCE(WCSA_ASP,0)
print CCDrefinfo_CAMERA_PCONVERGENCE[0]
print CCDrefinfo_CAMERA_PCONVERGENCE[1]
print CCDrefinfo_CAMERA_PCONVERGENCE[2]
print CCDrefinfo_CAMERA_PCONVERGENCE[3]
print CCDrefinfo_CAMERA_PCONVERGENCE[4]
print "--- getting function : references : PROTATION ---"
CCDrefinfo_CAMERA_PROTATION = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_PROTATION(WCSA_ASP,0)
print CCDrefinfo_CAMERA_PROTATION[0]
print CCDrefinfo_CAMERA_PROTATION[1]
print CCDrefinfo_CAMERA_PROTATION[2]
print CCDrefinfo_CAMERA_PROTATION[3]
print CCDrefinfo_CAMERA_PROTATION[4]
print "--- getting function : references : PSHEAR1 ---"
CCDrefinfo_CAMERA_PSHEAR1 = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_PSHEAR1(WCSA_ASP,0)
print CCDrefinfo_CAMERA_PSHEAR1[0]
print CCDrefinfo_CAMERA_PSHEAR1[1]
print CCDrefinfo_CAMERA_PSHEAR1[2]
print CCDrefinfo_CAMERA_PSHEAR1[3]
print CCDrefinfo_CAMERA_PSHEAR1[4]
print "--- getting function : references : PSHEAR2 ---"
CCDrefinfo_CAMERA_PSHEAR2 = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_PSHEAR2(WCSA_ASP,0)
print CCDrefinfo_CAMERA_PSHEAR2[0]
print CCDrefinfo_CAMERA_PSHEAR2[1]
print CCDrefinfo_CAMERA_PSHEAR2[2]
print CCDrefinfo_CAMERA_PSHEAR2[3]
print CCDrefinfo_CAMERA_PSHEAR2[4]
print "--- getting function : references : PMAGNIFICATION ---"
CCDrefinfo_CAMERA_PMAGNIFICATION = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_PMAGNIFICATION(WCSA_ASP,0)
print CCDrefinfo_CAMERA_PMAGNIFICATION[0]
print CCDrefinfo_CAMERA_PMAGNIFICATION[1]
print CCDrefinfo_CAMERA_PMAGNIFICATION[2]
print CCDrefinfo_CAMERA_PMAGNIFICATION[3]
print CCDrefinfo_CAMERA_PMAGNIFICATION[4]
#CCDrefinfo_ID = doTansip.WCS_GET_REFERENCE_CCD_ID(WCSA_ASP,-1)
#print CCDrefinfo_ID
#CCDrefinfo_CHIPID = doTansip.WCS_GET_REFERENCE_CCD_CHIPID(WCSA_ASP,-1)
#print CCDrefinfo_CHIPID
#CCDrefinfo_FLAG = doTansip.WCS_GET_REFERENCE_CCD_FLAG(WCSA_ASP,-1)
#print CCDrefinfo_FLAG
#CCDrefinfo_XY_LOCAL = doTansip.WCS_GET_REFERENCE_CCD_XY_LOCAL(WCSA_ASP,-1)
#print CCDrefinfo_XY_LOCAL
#CCDrefinfo_XY_RADEC = doTansip.WCS_GET_REFERENCE_CCD_XY_RADEC(WCSA_ASP,-1)
#print CCDrefinfo_XY_RADEC
#CCDrefinfo_XY_GLOBAL = doTansip.WCS_GET_REFERENCE_CCD_XY_GLOBAL(WCSA_ASP,-1)
#print CCDrefinfo_XY_GLOBAL
#CCDrefinfo_XY_GLOBALCRPIX = doTansip.WCS_GET_REFERENCE_CCD_XY_GLOBALCRPIX(WCSA_ASP,-1)
#print CCDrefinfo_XY_GLOBALCRPIX
#CCDrefinfo_XY_LOCALCRPIX = doTansip.WCS_GET_REFERENCE_CCD_XY_LOCALCRPIX(WCSA_ASP,-1)
#print CCDrefinfo_XY_LOCALCRPIX
#CCDrefinfo_XY_IMPIXEL = doTansip.WCS_GET_REFERENCE_CCD_XY_IMPIXEL(WCSA_ASP,-1)
#print CCDrefinfo_XY_IMPIXEL
#CCDrefinfo_XY_IMWORLD = doTansip.WCS_GET_REFERENCE_CCD_XY_IMWORLD(WCSA_ASP,-1)
#print CCDrefinfo_XY_IMWORLD
#CCDrefinfo_XY_IMWORLD = doTansip.WCS_GET_REFERENCE_CCD_XY_IMWORLD(WCSA_ASP,-1)
#print CCDrefinfo_XY_IMWORLD
#CCDrefinfo_CAMERA_CONVERGENCE = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_CONVERGENCE(WCSA_ASP,-1)
#print CCDrefinfo_CAMERA_CONVERGENCE
#CCDrefinfo_CAMERA_ROTATION = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_ROTATION(WCSA_ASP,-1)
#print CCDrefinfo_CAMERA_ROTATION
#CCDrefinfo_CAMERA_SHEAR1 = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_SHEAR1(WCSA_ASP,-1)
#print CCDrefinfo_CAMERA_SHEAR1
#CCDrefinfo_CAMERA_SHEAR2 = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_SHEAR2(WCSA_ASP,-1)
#print CCDrefinfo_CAMERA_SHEAR2
#CCDrefinfo_CAMERA_MAGNIFICATION = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_MAGNIFICATION(WCSA_ASP,-1)
#print CCDrefinfo_CAMERA_MAGNIFICATION
#CCDrefinfo_CAMERA_PCONVERGENCE = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_PCONVERGENCE(WCSA_ASP,-1)
#print CCDrefinfo_CAMERA_PCONVERGENCE
#CCDrefinfo_CAMERA_PROTATION = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_ROTATION(WCSA_ASP,-1)
#print CCDrefinfo_CAMERA_PROTATION
#CCDrefinfo_CAMERA_PSHEAR1 = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_SHEAR1(WCSA_ASP,-1)
#print CCDrefinfo_CAMERA_PSHEAR1
#CCDrefinfo_CAMERA_PSHEAR2 = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_SHEAR2(WCSA_ASP,-1)
#print CCDrefinfo_CAMERA_PSHEAR2
#CCDrefinfo_CAMERA_PMAGNIFICATION = doTansip.WCS_GET_REFERENCE_CCD_CAMERA_MAGNIFICATION(WCSA_ASP,-1)
#print CCDrefinfo_CAMERA_PMAGNIFICATION

refinfo = doTansip.WCS_GET_REFERENCE_INIDIVIDUAL(WCSA_ASP,0)
print refinfo
refinfo = doTansip.WCS_GET_REFERENCE_INIDIVIDUAL(WCSA_ASP,7)
print refinfo
refinfo = doTansip.WCS_GET_REFERENCE_INIDIVIDUAL(WCSA_ASP,-1)
print refinfo
refinfo = doTansip.WCS_GET_REFERENCE_INIDIVIDUAL(WCSA_ASP,1000000000)
print refinfo

#-----------------------------------------------------------------
#Getting Functions : WCS : CCD
#-----------------------------------------------------------------
print "--- getting function : ccd ---"
ccdpositions = doTansip.WCS_GET_CCD_ALL_CCDPOS(WCSA_ASP)
print ccdpositions
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,0)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,1)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,2)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,3)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,4)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,5)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,6)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,7)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,8)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,9)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,10)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,-1)
print ccdposition

#-----------------------------------------------------------------
#Getting Functions : OLD
#-----------------------------------------------------------------
print "--- get wcsList ---"
wcsList = doTansip.getwcsList(WCSA_ASP)
print wcsList
print "--- get references ---"
references = doTansip.getreferences(WCSA_ASP)
#print references
print "--- get RADEC ---"
X_GLOBAL = (0.0,0.0)
RADEC = doTansip.getradec(X_GLOBAL,WCSA_ASP)
print X_GLOBAL
print RADEC
print "--- get X_GLOBAL ---"
X_GLOBAL = doTansip.getxglobal(RADEC,WCSA_ASP)
print RADEC
print X_GLOBAL
print "--- get RADEC ---"
X_GLOBAL = (2000.0,2000.0)
RADEC = doTansip.getradec(X_GLOBAL,WCSA_ASP)
print X_GLOBAL
print RADEC
print "--- get X_GLOBAL ---"
X_GLOBAL = doTansip.getxglobal(RADEC,WCSA_ASP)
print RADEC
print X_GLOBAL
#print "--- get PAIR ID ---"
#PAIR_ID = doTansip.getpair_ID(WCSA_ASP)
#print PAIR_ID
#print "--- get PAIR CHIPID ---"
#PAIR_CHIPID = doTansip.getpair_CHIPID(WCSA_ASP)
#print PAIR_CHIPID
#print "--- get PAIR FLAG ---"
#PAIR_FLAG = doTansip.getpair_FLAG(WCSA_ASP)
#print PAIR_FLAG
#print "--- get PAIR RA ---"
#PAIR_RA = doTansip.getpair_RA(WCSA_ASP)
#print PAIR_RA
#print "--- get PAIR DEC ---"
#PAIR_DEC = doTansip.getpair_DEC(WCSA_ASP)
#print PAIR_DEC
#print "--- get PAIR IM_WORLD_X ---"
#PAIR_IM_WORLD_X = doTansip.getpair_IM_WORLD_X(WCSA_ASP)
#print PAIR_IM_WORLD_X
#print "--- get PAIR IM_WORLD_Y ---"
#PAIR_IM_WORLD_Y = doTansip.getpair_IM_WORLD_Y(WCSA_ASP)
#print PAIR_IM_WORLD_Y
#print "--- get PAIR IM_PIXEL_X ---"
#PAIR_IM_PIXEL_X = doTansip.getpair_IM_PIXEL_X(WCSA_ASP)
#print PAIR_IM_PIXEL_X
#print "--- get PAIR IM_PIXEL_Y ---"
#PAIR_IM_PIXEL_Y = doTansip.getpair_IM_PIXEL_Y(WCSA_ASP)
#print PAIR_IM_PIXEL_Y
#print "--- get PAIR CRPIX_X ---"
#PAIR_CRPIX_X = doTansip.getpair_CRPIX_X(WCSA_ASP)
#print PAIR_CRPIX_X
#print "--- get PAIR CRPIX_Y ---"
#PAIR_CRPIX_Y = doTansip.getpair_CRPIX_Y(WCSA_ASP)
#print PAIR_CRPIX_Y
#print "--- get PAIR GLOBAL_X ---"
#PAIR_GLOBAL_X = doTansip.getpair_GLOBAL_X(WCSA_ASP)
#print PAIR_GLOBAL_X
#print "--- get PAIR GLOBAL_Y ---"
#PAIR_GLOBAL_Y = doTansip.getpair_GLOBAL_Y(WCSA_ASP)
#print PAIR_GLOBAL_Y
#print "--- get PAIR LOCAL_X ---"
#PAIR_LOCAL_X = doTansip.getpair_LOCAL_X(WCSA_ASP)
#print PAIR_LOCAL_X
#print "--- get PAIR LOCAL_Y ---"
#PAIR_LOCAL_Y = doTansip.getpair_LOCAL_Y(WCSA_ASP)
#print PAIR_LOCAL_Y
