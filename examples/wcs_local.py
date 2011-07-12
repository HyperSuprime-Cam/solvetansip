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
import hsc.meas.tansip.WCS_CHECK_PY      as WCS_CHECK_PY
import hsc.meas.tansip.WCS_POSITION_PY   as WCS_POSITION_PY
import hsc.meas.tansip.WCS_DISTORTION_PY as WCS_DISTORTION_PY
import hsc.meas.tansip.WCS_READPAIR_PY   as WCS_READPAIR_PY
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

CNUMBER = 1
ANGLE=0
#sources = io.read('src', data, ignore=True)
#md = io.read('calexp_md', data, ignore=True)
#matches = io.readMatches(data, ignore=True)

#ra = []
#dec = []
#raFix = []
#decFix = []
#mag1=[]
#mag2=[]
#for matchList, md in zip(matches, md):
#    wcs = afwImage.makeWcs(md)
#    calib = afwImage.Calib(md)
#    for m in matchList:
#        # Need to convert degrees to radians for catalogue
#        #m.first.setRa(numpy.radians(m.first.getRa()))
#        #m.first.setDec(numpy.radians(m.first.getDec()))
#
#        # Need to recalculate ra,dec for sources
#        #sky = wcs.pixelToSky(m.second.getXAstrom(), m.second.getYAstrom())
#        #m.second.setRa(sky[0])
#        #m.second.setDec(sky[1])
#        
#        ra.append(m.first.getRa())
#        dec.append(m.first.getDec())
#        
#        mag1.append(-2.5 * numpy.log10(m.first.getPsfFlux()))
#        try:
#            mag2.append(calib.getMagnitude(m.second.getApFlux()))
#        except:
#            mag2.append(99.0)
#
#ra = numpy.array(ra)
#dec = numpy.array(dec)
#mag1 = numpy.array(mag1)
#mag2 = numpy.array(mag2)
#print "Magnitude range, catalogue:", mag1.min(), mag1.max()
#print "Magnitude range, sources:", mag2.min(), mag2.max()
#print "Sky range, ra and dec:", ra.min(), ra.max(), dec.min(), dec.max()
#plot.xy(ra, dec)
#plot.histogram(mag1-mag2, [-5, 5], bins=101)

policyPath = os.path.join(os.getenv("SOLVETANSIP_DIR"), "policy", "WCS_MAKEAPROP.paf")
policy = pexPolicy.Policy.createPolicy(policyPath)

#policy.set("LSIPORDER", 1)
#policy.set("SIPORDER", 6)
metadata = hscTansip.F_WCS_EMPTYMETADATA()

#wcsList = doTansip.doTansip(matches, policy=policy, camera=mapper.camera)
WCSACCP   = doTansip.getresultWcs_local(matches_address, metadata, policy=policy, camera=mapper.camera)
print "--- get wcsList ---"
wcsList   = doTansip.getwcsList(WCSACCP)
print "--- get APROP ---"
APROP     = doTansip.getAPROP(WCSACCP)
print "--- get CPROP ---"
CPROP     = doTansip.getCPROP(WCSACCP)
print "--- get CSIP ---"
CSIP      = doTansip.getCSIP(WCSACCP)
print "--- get PAIR ---"
PAIR      = doTansip.getPAIR(WCSACCP)
print "--- get CPROPList ---"
CPROPList = doTansip.getCPROPList(WCSACCP)
print "--- get CSIPList ---"
CSIPList  = doTansip.getCSIPList(WCSACCP)
print "--- solvetansip check ---"
WCS_CHECK_PY.F_WCS_CHECK_CCDPOSITION_SC(CNUMBER,APROP,CPROP)
WCS_CHECK_PY.F_WCS_CHECK_OADISTORTION_SC(CNUMBER,ANGLE,APROP,CPROP,CSIP)
WCS_CHECK_PY.F_WCS_CHECK_OAPOSITION_SC(CNUMBER,APROP,CPROP,CSIP)
#print wcsList
#print APROP
#print CPROP
#print CSIP
#print PAIR
#print CPROPList
#print CSIPList
#pair test
#####print "--- pair test ---"
#####WCS_READPAIR_PY.F_WCS_READPAIR(APROP,PAIR)
#pair test5.57167
#position test
#####print "--- position test ---"
#####X=-3204.81
#####Y=-87.4664
#####RA=5.57167
#####DEC= -0.65657
#####print X
#####print Y
#####print RA
#####print DEC
#####RADEC=WCS_POSITION_PY.F_WCS_POSITION_RADECfromXY(wcsList[0],X,Y)
#####print RADEC[0]
#####print RADEC[1]
#####XY=WCS_POSITION_PY.F_WCS_POSITION_XYfromRADEC(wcsList[0],RA,DEC)
#####print XY[0]
#####print XY[1]
#position test
#distortion test
#####print "--- distortion test ---"

#####MSSR=WCS_DISTORTION_PY.F_WCS_DISTORTION_wcsList_XY(wcsList[0],X,Y)
#####print X,Y,MSSR[0], MSSR[1], MSSR[2], MSSR[3]
#####X=0
#####Y=0
#####MSSR=WCS_DISTORTION_PY.F_WCS_DISTORTION_wcsList_XY(wcsList[0],X,Y)
#####print X,Y,MSSR[0], MSSR[1], MSSR[2], MSSR[3]
#####X=2000
#####Y=4000
#####MSSR=WCS_DISTORTION_PY.F_WCS_DISTORTION_wcsList_XY(wcsList[0],X,Y)
#####print X,Y,MSSR[0], MSSR[1], MSSR[2], MSSR[3]
#####MSSR=WCS_DISTORTION_PY.F_WCS_DISTORTION_wcsList_RADEC(wcsList[0],RA,DEC)
#####print RA,DEC,MSSR[0], MSSR[1], MSSR[2], MSSR[3]
#####RA=5.0
#####DEC=-0.5
#####MSSR=WCS_DISTORTION_PY.F_WCS_DISTORTION_wcsList_RADEC(wcsList[0],RA,DEC)
#####print RA,DEC,MSSR[0], MSSR[1], MSSR[2], MSSR[3]
#####RA=5.5
#####DEC=-1.0
#####MSSR=WCS_DISTORTION_PY.F_WCS_DISTORTION_wcsList_RADEC(wcsList[0],RA,DEC)
#####print RA,DEC,MSSR[0], MSSR[1], MSSR[2], MSSR[3]
#####MSSR=WCS_DISTORTION_PY.F_WCS_DISTORTION_CSIP_XY(CPROPList[0],X,Y)
#####print MSSR[0], MSSR[1], MSSR[2], MSSR[3]
#####MSSR=WCS_DISTORTION_PY.F_WCS_DISTORTION_CSIP_RADEC(CPROPList[0],RA,DEC)
#####print MSSR[0], MSSR[1], MSSR[2], MSSR[3]
#distortion test


#####ra1 = []
#####dec1 = []
#####ra2 = []
#####dec2 = []
#####ra3 = []
#####dec3 = []
#####dSky = []
#####for wcs, matchList in zip(wcsList, matches):
#####    #print wcs.getFitsMetadata()
#####    for m in matchList:
#####        # First is catalogue, which is mistakenly and temporarily in degrees
#####        ra1.append(m.first.getRa()*180./numpy.pi)
#####        dec1.append(m.first.getDec()*180./numpy.pi)
#####        # Second is image, which needs to be re-computed from new wcs
#####        sky = wcs.pixelToSky(m.second.getXAstrom(), m.second.getYAstrom())
#####        ra2.append(sky.getLongitude(afwCoord.DEGREES))
#####        dec2.append(sky.getLatitude(afwCoord.DEGREES))
#####
#####        coord1 = afwCoord.Coord(afwGeom.Point2D(m.first.getRa(), m.first.getDec()), afwCoord.DEGREES)
#        coord1 = afwCoord.Coord(afwGeom.makePointD(m.first.getRa(), m.first.getDec()), afwCoord.DEGREES)
#####        ###dSky.append(coord1.angularSeparation(sky, afwCoord.DEGREES) * 3600.0) ### --> did not work properly
#####        dSky.append(coord1.angularSeparation(sky, afwCoord.RADIANS) * 180./numpy.pi)
#####
#        RADEC=WCS_POSITION_PY.F_WCS_POSITION_RADECfromXY(wcs,m.second.getXAstrom(), m.second.getYAstrom())
#        ra3.append(RADEC[0])
#        dec3.append(RADEC[1])
        

#####ra1 = numpy.array(ra1)
#####dec1 = numpy.array(dec1)
#####ra2 = numpy.array(ra2)
#####dec2 = numpy.array(dec2)
#####dRa = (ra2-ra1)*3600
#####dDec = (dec2-dec1)*3600
#ra3 = numpy.array(ra3)
#dec3 = numpy.array(dec3)
#dRa3 = (ra3-ra1)*3600
#dDec3 = (dec3-dec1)*3600
#####dSky = numpy.array(dSky)
#####print "RA difference stats (arcsec):", dRa.mean(), dRa.std()
#####print "Dec difference stats (arcsec):", dDec.mean(), dDec.std()
#print "RA difference stats (arcsec):", dRa3.mean(), dRa3.std()
#print "Dec difference stats (arcsec):", dDec3.mean(), dDec3.std()
#####print "Offset stats:", dSky.mean(), dSky.std()
#####plot.histogram(dSky, None, bins=101, clip=3.0, gaussFit=None)
#####plot.quivers(ra1, dec1, dRa, dDec, addUnitQuiver=1./3600)
#####plot.close()