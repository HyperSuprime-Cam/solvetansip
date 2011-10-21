#!/usr/bin/env python

import os
import os.path

import numpy

import lsst.pipette.readwrite as pipReadWrite
import lsst.pex.policy as pexPolicy
import lsst.obs.hscSim as hscSim
import lsst.obs.suprimecam as scmapper

import hsc.meas.tansip.doTansip as doTansip
import hsc.meas.tansip.WCS_PL_MAIN       as hscTansip
#import hsc.meas.tansip.WCS_CHECK_PY      as WCS_CHECK_PY
#import hsc.meas.tansip.WCS_POSITION_PY   as WCS_POSITION_PY
#import hsc.meas.tansip.WCS_DISTORTION_PY as WCS_DISTORTION_PY
#import hsc.meas.tansip.WCS_READPAIR_PY   as WCS_READPAIR_PY
import lsst.afw.detection as afwDet
import lsst.afw.geom as afwGeom
import lsst.afw.image as afwImage
import lsst.afw.coord as afwCoord
import lsst.pipette.plotter as pipPlot

#WCS_POSITION.F_WCS_POSITION_TEST()

plot = pipPlot.Plotter('wcs')
#mapper = hscSim.HscSimMapper(rerun="fh-dc2.9-sc") fh-dc2.9-sc/
#mapper = hscSim.HscSimMapper(rerun="pre-DC2.4")
mapper = scmapper.SuprimecamMapper(rerun="fh-dc2.9c-default") 
io = pipReadWrite.ReadWrite(mapper, ['visit'], fileKeys=['visit', 'ccd'])
#data = {'visit': 220}
data = {'visit': 126913}#929-941-
CNUMBER = 401
ANGLE=0
#ANGLE = 0.067195176
#ANGLE = 0.116745074
#ANGLE = 0.224152636
#ANGLE = 0.25096962
#ANGLE = 0.303757103
#ANGLE = 0.354205845
#ANGLE = 0.402612552
#ANGLE = 0.448043472
#ANGLE = 0.490245534
#ANGLE = 0.530815712
#ANGLE = 0.569361308
#ANGLE = 0.605507077
sources = io.read('src', data, ignore=True)
md = io.read('calexp_md', data, ignore=True)
matches = io.readMatches(data, ignore=True)

ra = []
dec = []
raFix = []
decFix = []
mag1=[]
mag2=[]
for matchList, md in zip(matches, md):
    wcs = afwImage.makeWcs(md)
    calib = afwImage.Calib(md)
    for m in matchList:
        # Need to convert degrees to radians for catalogue
        #m.first.setRa(numpy.radians(m.first.getRa()))
        #m.first.setDec(numpy.radians(m.first.getDec()))

        # Need to recalculate ra,dec for sources
        #sky = wcs.pixelToSky(m.second.getXAstrom(), m.second.getYAstrom())
        #m.second.setRa(sky[0])
        #m.second.setDec(sky[1])
        
        ra.append(m.first.getRa())
        dec.append(m.first.getDec())
        
        mag1.append(-2.5 * numpy.log10(m.first.getPsfFlux()))
        try:
            mag2.append(calib.getMagnitude(m.second.getApFlux()))
        except:
            mag2.append(99.0)

ra = numpy.array(ra)
dec = numpy.array(dec)
mag1 = numpy.array(mag1)
mag2 = numpy.array(mag2)
print "Magnitude range, catalogue:", mag1.min(), mag1.max()
print "Magnitude range, sources:", mag2.min(), mag2.max()
print "Sky range, ra and dec:", ra.min(), ra.max(), dec.min(), dec.max()
#plot.xy(ra, dec)
#plot.histogram(mag1-mag2, [-5, 5], bins=101)

policyPath = os.path.join(os.getenv("SOLVETANSIP_DIR"), "policy", "WCS_MAKEAPROP.paf")
policy = pexPolicy.Policy.createPolicy(policyPath)

#policy.set("LSIPORDER", 1)
#policy.set("SIPORDER", 6)
metadata = hscTansip.F_WCS_EMPTYMETADATA()

#wcsList = doTansip.doTansip(matches, policy=policy, camera=mapper.camera)
WCSA_ASP   = doTansip.getresultWcs_local(matches_address, metadata, policy=policy, camera=mapper.camera)
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
