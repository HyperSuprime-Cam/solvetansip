#!/usr/bin/env python

import os, sys
import os.path

import numpy

import lsst.pipette.readwrite as pipReadWrite
import lsst.pex.policy as pexPolicy
import lsst.obs.hscSim as hscSim
import lsst.obs.suprimecam as scmapper
from hsc.meas.tansip.doTansip import doTansip
import lsst.afw.detection as afwDet
import lsst.afw.geom as afwGeom
import lsst.afw.image as afwImage
import lsst.afw.coord as afwCoord
#import lsst.pipette.plotter as pipPlot
#plot = pipPlot.Plotter('wcs')
    

# Need setup a modified obs_subaru for policy/HscSimMapper.paf
# for writing new FITS files re-calibrated with solveTansip in corr/ directory

def main(hsc_or_sc, rerun, visit):    

    do_solveTansip = True
    do_writeNewWcs = True # New FITS file will be created
    #do_writeNewWcs = False # Only solve 

    data = {'visit': visit} # for SC
    
    if (hsc_or_sc == 'hsc'):
        mapper = hscSim.HscSimMapper(rerun=rerun)
    elif(hsc_or_sc == 'sc'):
        mapper = scmapper.SuprimecamMapper(rerun=rerun)
    else:
        mapper = scmapper.SuprimecamMapper(rerun=rerun)        
    
    #mapper = hscSim.HscSimMapper(rerun="pre-DC2.4")
    io = pipReadWrite.ReadWrite(mapper, ['visit'], fileKeys=['visit', 'ccd'])
    #data = {'visit': 220}
    #data = data
    
    sources = io.read('src', data, ignore=True)
    metadata = io.read('calexp_md', data, ignore=True)
    matches = io.readMatches(data, ignore=True)

    # showing CCD ID's which are available
    if True:
        ccdIds = []
        for metaccd in metadata:
            ccdId = metaccd.get('DET-ID')
            ccdIds.append(ccdId)
            print '*************** available CCD %d' % ccdId
            sys.stdout.flush()
        nCcd = len(ccdIds)

    print '---------- reading done.'
    
    ra = []
    dec = []
    raFix = []
    decFix = []
    mag1=[]
    mag2=[]
    for matchList, md in zip(matches, metadata):

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
#    plot.xy(ra, dec)
    bins = 101
    histRange = [-2, 2] 
#    plot.histogram(mag1-mag2, histRange, bins=bins, gaussFit=True)
    
    if do_solveTansip == True:
        policyPath = os.path.join(os.getenv("SOLVETANSIP_DIR"), "policy", "WCS_MAKEAPROP.paf")
        policy = pexPolicy.Policy.createPolicy(policyPath)
    
        #policy.set("LSIPORDER", 1)
        #policy.set("SIPORDER", 6)
#        policy.set("NCCD", nCcd)
        policy.set("NCCD", nCcd)
    
        wcsList = doTansip(matches, policy=policy, camera=mapper.camera)
        wcsList2 = doTansip.getwcsList(WCSA_ASP)

        wcsList = list(wcsList)
        wcsList.pop() #  last item is a summary
        print 'len(wcsList without last element):', len(wcsList)
  
    else:
        ####io = pipReadWrite.ReadWrite(mapper, ['visit'], fileKeys=['visit', 'ccd'])
        ####data = {'visit': 220}
        #data = {'visit': 200}
    
        ## Furusawa's memo
        ## the below gets a list of corrected frames
        ## corrFiles = io.read('calexp', data, ignore=True) ### deduced from pipette::readwrite.py::write()
        ## the below gets a list of metadata(hdr incl. wcs) of corrected frames
        ##md = io.read('calexp_md', data, ignore=True)
        #matches = io.readMatches(data, ignore=True)
        
        wcsList = []
        for md in metadata:
            wcs = afwImage.makeWcs(md)
            wcsList.append(wcs)


    if do_writeNewWcs == True:
        dataId = data.copy()
        #for i, wcs in enumerate(wcsList):
        for ccdId, wcs in zip(ccdIds, wcsList):        
            dataId['ccd'] = ccdId
            print 'dataId: ', dataId
            corrFile = io.read('calexp', dataId, ignore=True)
            exposure = corrFile[0]
            writeFitsWithNewWcs(exposure, wcs, dataId, io)
        

    ra1 = []
    dec1 = []
    ra2 = []
    dec2 = []
    dSky = []
    
    x1 = []
    y1 = []
    x2 = []
    y2 = []
    dXY = []
    
    for wcs, matchList in zip(wcsList, matches):
        #print wcs.getFitsMetadata()
        for m in matchList:
            # First is catalogue, which is mistakenly and temporarily in degrees
    
            raRef = m.first.getRa()
            decRef = m.first.getDec()
    
            xDet = m.second.getXAstrom()
            yDet = m.second.getYAstrom()
    
            ra1.append(raRef)
            dec1.append(decRef)
    
            x1.append(xDet)
            y1.append(yDet)
    
            # Second is image, which needs to be re-computed from new wcs
            radecFromXY     = wcs.pixelToSky(xDet, yDet)
            ccdpixFromRaDec = wcs.skyToPixel(raRef, decRef)
            xFromRaDec = ccdpixFromRaDec.getX()
            yFromRaDec = ccdpixFromRaDec.getY()
            x2.append(xFromRaDec)
            y2.append(yFromRaDec)
    
#            ra2.append(radecFromXY.getLongitude(afwCoord.DEGREES))
#            dec2.append(radecFromXY.getLatitude(afwCoord.DEGREES))
            ra2.append(radecFromXY.getLongitude())
            dec2.append(radecFromXY.getLatitude())
    
            #radecRefDegree = afwCoord.Coord(afwGeom.makePointD(raRef, decRef), afwCoord.DEGREES)
            radecRefDegree = afwCoord.Coord(afwGeom.PointD(raRef, decRef), afwCoord.DEGREES)            
    
            dSky.append( radecRefDegree.angularSeparation(radecFromXY, afwCoord.DEGREES) * 3600.0 )
            dXY.append(numpy.sqrt(
                (xDet - xFromRaDec)*(xDet - xFromRaDec) + (yDet - yFromRaDec)*(yDet - yFromRaDec)
                ))
    
    ra1 = numpy.array(ra1)
    dec1 = numpy.array(dec1)
    ra2 = numpy.array(ra2)
    dec2 = numpy.array(dec2)
    
    x1 = numpy.array(x1)
    y1 = numpy.array(y1)
    x2 = numpy.array(x2)
    y2 = numpy.array(y2)
    
    dRa = (ra2-ra1)*3600
    dDec = (dec2-dec1)*3600
    dSky = numpy.array(dSky)
    
    dX = (x1-x2)
    dY = (y1-y2)
    dXY = numpy.array(dXY)
    
    print "RA difference stats (arcsec):", dRa.mean(), dRa.std()
    print "Dec difference stats (arcsec):", dDec.mean(), dDec.std()
    print "X difference stats (pix):", dX.mean(), dX.std()
    print "Y difference stats (pix):", dY.mean(), dY.std()
    print "Offset stats RADec (arcsec):", dSky.mean(), dSky.std()
    print "Offset stats XY (pix):", dXY.mean(), dXY.std()

    #plot.histogram(dSky, None, bins=bins, clip=3.0, gaussFit=None)
    #plot.quivers(ra1, dec1, dRa, dDec, addUnitQuiver=1./3600)
    #plot.close()


def writeFitsWithNewWcs(exposure, wcs, dataId, pipRW):

    print '*** Writing New FITS Files with New WCS for %s ...' % dataId

    exposure.setWcs(wcs)
    pipRW.outButler.put(exposure, 'revexp', dataId)
        


if __name__ == '__main__':

    hsc_or_sc = 'sc'
#    hsc_or_sc = 'hsc'
    do_solveTansip = True
    do_writeNewWcs = True # New FITS file will be created
    #do_writeNewWcs = False # Only solve 
    rerun = "fh-hsc.17"
#    rerun = "flat-nightsky"
#    rerun = "flat-dome"
#    rerun = "fh-sc-1269XXX-sdss-dr8-mitaka"
#    rerun='fh-dc2.16-default'

#    data = {'visit': 126970} # for SC
#    data = {'visit': 126969} # for SC
#    data = {'visit': 220}  # for HSC-SIM

#    visit = 126968  # for SC
    visit = 126934

    main(hsc_or_sc, rerun, visit)
