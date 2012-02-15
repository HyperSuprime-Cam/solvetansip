#!/usr/bin/env python

import os
import os.path
import sys
import numpy
import shutil

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

#wcsList = doTansip.doTansip(matches, policy=policy, camera=mapper.camera)
#WCSA_ASP = doTansip.getresultWcs_local(matches_address, metadata, policy=policy, camera=mapper.camera)
#doTansip.WCS_MAKE_SIMULATIONREFERENCE(0,0,0,0.01,1,20)#


#mapper = scmapper.SuprimecamMapper(rerun="fh-dc2.9c-default") 
#mapper = hscSim.HscSimMapper(rerun="fh-dc2.9c-default")
#policyPath = os.path.join(os.getenv("SOLVETANSIP_DIR"), "policy", "WCS_MAKEAPROP.paf")
#policy = pexPolicy.Policy.createPolicy(policyPath)
#metadata = doTansip.F_WCS_EMPTYMETADATA()

DIST_SC = "DIST_SC_SIM.txt"
CCDPOS_SC = "CCDPOS_SC_SIM.txt"
#DIST_SC = "Dummy"
#CCDPOS_SC = "Dummy"
REFNUMlist=[11,15,20,30,50,100,1000];
for REFNUM in range (10,1001):
    if REFNUM in REFNUMlist:
        print 'SC  : ' , REFNUM
        for RANNUM in range (1,101):
            SIMFILENAME = 'RREF/SIMULATIONDATA_SC_'+str(REFNUM)+'_'+str(RANNUM)+'.dat'
#making
            doTansip.WCS_MAKE_SIMULATIONREFERENCE(0,CCDPOS_SC,DIST_SC,0.3,RANNUM,REFNUM)
            shutil.copyfile("SIMULATION.data", SIMFILENAME)
#analysis
#            WCSA_ASP = doTansip.getresultWcs_local(SIMFILENAME, metadata, policy=policy, camera=mapper.camera)
#            doTansip.WCS_CALC_SIMULATIONDIFF(0,CCDPOS_SC,DIST_SC,WCSA_ASP)

DIST_HSC = "DIST_HSC_SIM.txt"
CCDPOS_HSC = "CCDPOS_HSC_SIM.txt"
REFNUMlist=[11,15,20,30,50,100,1000];
for REFNUM in range (10,1001):
    if REFNUM in REFNUMlist:
        print 'HSC : ' , REFNUM
        for RANNUM in range (1,101):
            SIMFILENAME = 'RREF/SIMULATIONDATA_HSC_'+str(REFNUM)+'_'+str(RANNUM)+'.dat'
#making
            doTansip.WCS_MAKE_SIMULATIONREFERENCE(1,CCDPOS_HSC,DIST_HSC,0.3,RANNUM,REFNUM)
            shutil.copyfile("SIMULATION.data", SIMFILENAME)
#analysis
#            WCSA_ASP = doTansip.getresultWcs_local(SIMFILENAME, metadata, policy=policy, camera=mapper.camera)
#            doTansip.WCS_CALC_SIMULATIONDIFF(1,CCDPOS_HSC,DIST_HSC,WCSA_ASP)
