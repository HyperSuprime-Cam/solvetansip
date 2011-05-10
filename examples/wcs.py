#!/usr/bin/env python

import os
import os.path

import numpy

import lsst.pipette.readwrite as pipReadWrite
import lsst.pex.policy as pexPolicy
import lsst.obs.hscSim as hscSim
import hsc.meas.tansip.doTansip as doTansip
import hsc.meas.tansip.WCS_PL_MAIN       as hscTansip
import hsc.meas.tansip.WCS_POSITION_PY as WCS_POSITION_PY
import lsst.afw.detection as afwDet
import lsst.afw.geom as afwGeom
import lsst.afw.image as afwImage
import lsst.afw.coord as afwCoord
import lsst.pipette.plotter as pipPlot

#WCS_POSITION.F_WCS_POSITION_TEST()

plot = pipPlot.Plotter('wcs')

mapper = hscSim.HscSimMapper(rerun="pre-DC2.4")
io = pipReadWrite.ReadWrite(mapper, ['visit'], fileKeys=['visit', 'ccd'])
data = {'visit': 220}

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

wcsList = doTansip.doTansip(matches, policy=policy, camera=mapper.camera)
#wcsList = doTansip.doTansip_meta(matches, metadata, policy=policy, camera=mapper.camera)
#position test
X=9514.66
Y=95.9925
RA=150.766469
DEC=1.966586
print X
print Y
print RA
print DEC
RADEC=WCS_POSITION_PY.F_WCS_POSITION_RADECfromXY(wcsList[0],X,Y)
print RADEC[0]
print RADEC[1]
XY=WCS_POSITION_PY.F_WCS_POSITION_XYfromRADEC(wcsList[0],RA,DEC)
print XY[0]
print XY[1]
#position test


ra1 = []
dec1 = []
ra2 = []
dec2 = []
ra3 = []
dec3 = []
dSky = []
for wcs, matchList in zip(wcsList, matches):
    #print wcs.getFitsMetadata()
    for m in matchList:
        # First is catalogue, which is mistakenly and temporarily in degrees
        ra1.append(m.first.getRa())
        dec1.append(m.first.getDec())
        # Second is image, which needs to be re-computed from new wcs
        sky = wcs.pixelToSky(m.second.getXAstrom(), m.second.getYAstrom())
        ra2.append(sky.getLongitude(afwCoord.DEGREES))
        dec2.append(sky.getLatitude(afwCoord.DEGREES))

        coord1 = afwCoord.Coord(afwGeom.makePointD(m.first.getRa(), m.first.getDec()), afwCoord.DEGREES)
        dSky.append(coord1.angularSeparation(sky, afwCoord.DEGREES) * 3600.0)

#        RADEC=WCS_POSITION_PY.F_WCS_POSITION_RADECfromXY(wcs,m.second.getXAstrom(), m.second.getYAstrom())
#        ra3.append(RADEC[0])
#        dec3.append(RADEC[1])
        

ra1 = numpy.array(ra1)
dec1 = numpy.array(dec1)
ra2 = numpy.array(ra2)
dec2 = numpy.array(dec2)
dRa = (ra2-ra1)*3600
dDec = (dec2-dec1)*3600
#ra3 = numpy.array(ra3)
#dec3 = numpy.array(dec3)
#dRa3 = (ra3-ra1)*3600
#dDec3 = (dec3-dec1)*3600
dSky = numpy.array(dSky)
print "RA difference stats (arcsec):", dRa.mean(), dRa.std()
print "Dec difference stats (arcsec):", dDec.mean(), dDec.std()
#print "RA difference stats (arcsec):", dRa3.mean(), dRa3.std()
#print "Dec difference stats (arcsec):", dDec3.mean(), dDec3.std()
print "Offset stats:", dSky.mean(), dSky.std()
plot.histogram(dSky, None, bins=101, clip=3.0, gaussFit=None)
plot.quivers(ra1, dec1, dRa, dDec, addUnitQuiver=1./3600)
plot.close()
