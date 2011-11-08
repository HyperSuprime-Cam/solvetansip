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
import hsc.meas.tansip.WCS_PL_MAIN       as hscTansip
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
metadata = hscTansip.F_WCS_EMPTYMETADATA()

#wcsList = doTansip.doTansip(matches, policy=policy, camera=mapper.camera)
WCSA_ASP = doTansip.getresultWcs_local(matches_address, metadata, policy=policy, camera=mapper.camera)
print "--- get wcsList ---"
wcsList = doTansip.getwcsList(WCSA_ASP)
print wcsList
print "--- get ccd positions ---"
ccdpositions = doTansip.getccdpositions(WCSA_ASP)
print ccdpositions
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
