#!/usr/bin/env python

import os
import os.path

import numpy

import lsst.daf.persistence as dafPersist
import lsst.afw.geom as afwGeom
import lsst.afw.image as afwImage
import lsst.afw.coord as afwCoord
import lsst.pex.policy as pexPolicy
import lsst.obs.suprimecam as obsSc
import lsst.meas.astrom.astrom as measAst

import hsc.meas.tansip as tansip
import hsc.meas.tansip.doTansip as doTansip
#import hsc.meas.tansip.WCS_PL_MAIN       as hscTansip
#import hsc.meas.tansip.WCS_CHECK_PY      as WCS_CHECK_PY
#import hsc.meas.tansip.WCS_POSITION_PY   as WCS_POSITION_PY
#import hsc.meas.tansip.WCS_DISTORTION_PY as WCS_DISTORTION_PY
#import hsc.meas.tansip.WCS_READPAIR_PY   as WCS_READPAIR_PY

#WCS_POSITION.F_WCS_POSITION_TEST()

mapper = obsSc.SuprimecamMapper(rerun="solvetansip")
butler = dafPersist.ButlerFactory(mapper=mapper).create()
matchLists = [ measAst.readMatches(butler, {'visit':126969, 'ccd': ccd}) for ccd in range(10) ]

if False:
    ra = []
    dec = []
    raFix = []
    decFix = []
    mag1=[]
    mag2=[]
    for matches in matchLists:
        for m in matches:
            # Need to convert degrees to radians for catalogue
            #m.first.setRa(numpy.radians(m.first.getRa()))
            #m.first.setDec(numpy.radians(m.first.getDec()))

            # Need to recalculate ra,dec for sources
            #sky = wcs.pixelToSky(m.second.getXAstrom(), m.second.getYAstrom())
            #m.second.setRa(sky[0])
            #m.second.setDec(sky[1])

            ra.append(m.first.getRa())
            dec.append(m.first.getDec())

#            mag1.append(-2.5 * numpy.log10(m.first.getFlux()))
#            try:
#                mag2.append(calib.getMagnitude(m.second.getApFlux()))
#            except:
#                mag2.append(99.0)

    ra = numpy.array(ra)
    dec = numpy.array(dec)
    #mag1 = numpy.array(mag1)
    #mag2 = numpy.array(mag2)
    #print "Magnitude range, catalogue:", mag1.min(), mag1.max()
    #print "Magnitude range, sources:", mag2.min(), mag2.max()
    print "Sky range, ra and dec:", ra.min(), ra.max(), dec.min(), dec.max()

policyPath = os.path.join(os.getenv("SOLVETANSIP_DIR"), "policy", "suprimecam.paf")
policy = pexPolicy.Policy.createPolicy(policyPath)
policy.set('NCCD', len(matchLists))

matchLists = [[tansip.SourceMatch(m.second.getId(),
                                  afwCoord.IcrsCoord(m.first.getRa(), m.first.getDec()),
                                  afwGeom.Point2D(m.second.getX(), m.second.getY()),
                                  afwGeom.Point2D(m.second.get(m.second.getTable().getCentroidErrKey()[0,0]),
                                                  m.second.get(m.second.getTable().getCentroidErrKey()[1,1])),
                                  m.second.getPsfFlux())
               for m in ml ] for ml in matchLists]
wcs = doTansip.doTansip(matchLists, policy=policy, camera=mapper.camera)
wcsList = doTansip.getwcsList(wcs)
print wcsList

del mapper
del butler
del policyPath
del policy
del matchLists
del m
del ml
del wcsList
del wcs
