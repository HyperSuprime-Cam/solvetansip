#!/usr/bin/env python

import os, sys
import os.path

import numpy

import lsst.pipette.readwrite as pipReadWrite
import lsst.pex.policy as pexPolicy
import lsst.obs.hscSim as hscSim
import lsst.obs.suprimecam as scmapper
import hsc.meas.tansip.doTansip as tansip
import lsst.afw.detection as afwDet
import lsst.afw.geom as afwGeom
import lsst.afw.image as afwImage
import lsst.afw.coord as afwCoord
import lsst.pipette.plotter as pipPlot

plot = pipPlot.Plotter('wcs')
    

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
        policy.set("NCCD", nCcd)
    
        WCSA_ASP = tansip.doTansip(matches, policy=policy, camera=mapper.camera)
        wcsList  = tansip.getwcsList(WCSA_ASP)

        wcsList = list(wcsList)
        wcsList.pop() #  last item is a summary
        print 'len(wcsList without last element):', len(wcsList)
  
    else:
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
        

    # below lines are for evaluation of the fitting result
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

    # pixels using okura-kun's functions
    x2_2 = []
    y2_2 = []
    dXY_2 = []    

    for wcs, matchList in zip(wcsList, matches):
        print '** wcs.hasDistortion():', wcs.hasDistortion()
        #print wcs.getFitsMetadata()

        coordRaDec00Radian     = wcs.pixelToSky(0, 0) # should be (1,1)? which is the coodinate origin?
        ra00Degrees = coordRaDec00Radian.getLongitude().asDegrees()
        dec00Degrees = coordRaDec00Radian.getLatitude().asDegrees()
        radec00 = [ra00Degrees, dec00Degrees]
        ccdPosXy = tansip.getxglobal(radec00, WCSA_ASP)
        xCcdPos = ccdPosXy[0]
        yCcdPos = ccdPosXy[1]
        
        for m in matchList:
            # First is catalogue and second is detection
    
            raRef = m.first.getRa()    # getRa() gets an Angle object. needs to convert to float by .asDegrees()
            decRef = m.first.getDec()  # getDec() gets an Angle object. needs to convert to float by .asDegrees()
                        
            xDet = m.second.getXAstrom()
            yDet = m.second.getYAstrom()
    
            ra1.append(raRef.asDegrees())
            dec1.append(decRef.asDegrees())
    
            x1.append(xDet)
            y1.append(yDet)

            # Second is image, which needs to be re-computed from new wcs
            coordRadecFromXyRadian     = wcs.pixelToSky(xDet, yDet)
            ccdpixFromRadec = wcs.skyToPixel(raRef, decRef)
            xFromRadec = ccdpixFromRadec.getX()
            yFromRadec = ccdpixFromRadec.getY()
            x2.append(xFromRadec)
            y2.append(yFromRadec)
    
            ra2.append(coordRadecFromXyRadian.getLongitude().asDegrees())
            dec2.append(coordRadecFromXyRadian.getLatitude().asDegrees())

            # using okura-kun's functions
            radecRef = [raRef.asDegrees(), decRef.asDegrees()]
            xyFromRadec2 = tansip.getxglobal(radecRef, WCSA_ASP)
            xFromRadec2 = xyFromRadec2[0] - xCcdPos  
            yFromRadec2 = xyFromRadec2[1] - yCcdPos
            x2_2.append(xFromRadec2)
            y2_2.append(yFromRadec2)
            
            coordRadecRefRadian = afwCoord.Coord(afwGeom.PointD(raRef.asDegrees(), decRef.asDegrees()))
    
            dSky.append( coordRadecRefRadian.angularSeparation(coordRadecFromXyRadian).asDegrees() * 3600.0 )  # holds in arcsec
            dXY.append( numpy.hypot(xDet-xFromRadec, yDet-yFromRadec) )
            dXY_2.append( numpy.hypot(xDet-xFromRadec2, yDet-yFromRadec2) )            
    
    ra1 = numpy.array(ra1)
    dec1 = numpy.array(dec1)
    ra2 = numpy.array(ra2)
    dec2 = numpy.array(dec2)
    
    x1 = numpy.array(x1)
    y1 = numpy.array(y1)
    x2 = numpy.array(x2)
    y2 = numpy.array(y2)

    x2_2 = numpy.array(x2_2)
    y2_2 = numpy.array(y2_2)

    dRa = (ra2-ra1)*3600
    dDec = (dec2-dec1)*3600
    dSky = numpy.array(dSky)
    
    dX = (x1-x2)
    dY = (y1-y2)

    dX_2 = (x1-x2_2)
    dY_2 = (y1-y2_2)

    dXY = numpy.array(dXY)
    dXY_2 = numpy.array(dXY_2)    
    
    print "RA difference stats (arcsec):", dRa.mean(), dRa.std()
    print "Dec difference stats (arcsec):", dDec.mean(), dDec.std()
    print "X difference stats (pix):", dX.mean(), dX.std()
    print "Y difference stats (pix):", dY.mean(), dY.std()
    print "Offset stats RADec (arcsec):", dSky.mean(), dSky.std()
    print "Offset stats XY (pix):", dXY.mean(), dXY.std()
    print "## with okura-kun's functions"
    print "X_2 difference stats (pix):", dX_2.mean(), dX_2.std()
    print "Y_2 difference stats (pix):", dY_2.mean(), dY_2.std()
    print "Offset stats XY_2 (pix):", dXY_2.mean(), dXY_2.std()


    plot.histogram(dSky, None, bins=bins, clip=3.0, gaussFit=None)
    plot.quivers(ra1, dec1, dRa, dDec, addUnitQuiver=1./3600)
    plot.close()


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
    rerun = "flat-dome-hsc.17"
#    rerun = "flat-nightsky"
#    rerun = "flat-dome"
#    rerun = "fh-sc-1269XXX-sdss-dr8-mitaka"
#    rerun='fh-dc2.16-default'

#    data = {'visit': 126970} # for SC
#    data = {'visit': 126969} # for SC
#    data = {'visit': 220}  # for HSC-SIM

#    visit = 126968  # for SC
#    visit = 126934

    visit = int(sys.argv[1])

    main(hsc_or_sc, rerun, visit)
