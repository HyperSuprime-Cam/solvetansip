#!/usr/bin/env python

import os, sys
import os.path

import numpy

#import lsst.pipette.readwrite as pipReadWrite
import lsst.pex.policy as pexPolicy
import lsst.daf.persistence as dafPersist

import hsc.pipe.base.camera as hscCamera
import lsst.meas.astrom.astrom          as measAstrom
import hsc.meas.mosaic.mosaic as hscMosaic

import lsst.obs.hscSim as hscSim
import lsst.obs.suprimecam as scmapper
import hsc.meas.tansip as tansip
import hsc.meas.tansip.doTansip as doTansip
import hsc.meas.tansip.WCS_PL_MAINLib    as hscTansip
import lsst.afw.detection as afwDet
import lsst.afw.geom as afwGeom
import lsst.afw.image as afwImage
import lsst.afw.coord as afwCoord
import lsst.afw.table as afwTable
#import lsst.pipette.plotter as pipPlot
#
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
    elif(hsc_or_sc == 'suprimecam'):
        mapper = scmapper.SuprimecamMapper(rerun=rerun)
    else:
        mapper = scmapper.SuprimecamMapper(rerun=rerun)        
    
    butler = dafPersist.ButlerFactory(mapper=mapper).create()

    # reading matchlist of each CCD in a shot
    dataExp = {'visit': visit}
    dataIdList = [{'visit': visit, 'ccd': ccd} for ccd in range(104)]
#    dataIdList = [{'visit': visit, 'ccd': ccd} for ccd in range(hscCamera.getNumCcds(hsc_or_sc))]

    metadataList = []
    matchLists = []
    for dataId in dataIdList:

        print '*** reading matches: %s'% dataId
        try:
            print '*** querying: %s'% dataId
            matches = measAstrom.readMatches(butler, dataId)
            matchLists.append(matches)        
        except:
            continue
        metadata = butler.get('calexp_md', dataId)
        metadataList.append(metadata)
        if False: # you use only stars.
            matches = hscMosaic.selectStars(matches)

    print '*** len(matchLists): %s'% len(matchLists)
    

    matchListsForSolveTansip = [[
        tansip.SourceMatch(m.first.getId(),
                           afwCoord.IcrsCoord(m.first.getRa(),
                                              m.first.getDec()),
                           afwGeom.Point2D(m.second.getX(), m.second.getY()),
                           afwGeom.Point2D(m.second.get(m.second.getTable().getCentroidErrKey()[0,0]),
                                           m.second.get(m.second.getTable().getCentroidErrKey()[1,1])),
                           m.second.getPsfFlux())
        for m in ml ] for ml in matchLists ]


    # showing CCD ID's which are available
    if True:
        ccdIds = []
        for metaccd in metadataList:
            ccdId = metaccd.get('DET-ID')
            ccdIds.append(ccdId)
            print '*************** available CCD %d' % ccdId
            sys.stdout.flush()
        nCcd = len(ccdIds)
        print '*** len(ccdIds): %s'% len(ccdIds)

    print '---------- reading done.'

    ####import pdb; pdb.set_trace()
    refSchema = matchLists[0][0].first.schema
    fluxKey = refSchema.find("flux").key

    ra = []
    dec = []
    raFix = []
    decFix = []
    mag1=[]
    mag2=[]
    for matchList, md in zip(matchLists, metadataList):

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
            
            ra.append(m.first.getRa().asDegrees())
            dec.append(m.first.getDec().asDegrees())
            
            mag1.append(-2.5 * numpy.log10(m.first.get(fluxKey)) )
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

    if do_solveTansip is True:
        policyPath = os.path.join(os.getenv("SOLVETANSIP_DIR"), "policy", "WCS_MAKEAPROP.paf")
        policy = pexPolicy.Policy.createPolicy(policyPath)

        #policy.set("LSIPORDER", 1)
        #policy.set("SIPORDER", e6)
        policy.set("CRPIXMODE", "AUTO")
#        policy.set("CCDPMODE", 1)   # determines CCD positions?
        policy.set("CCDPMODE", 0)   # determines CCD positions?
        policy.set("NCCD", 100)
#        policy.set("NCCD", nCcd)
        policy.set("LSIPORDER", 3) #SIP ORDER of AP and BP

        if nCcd > 10:
            policy.set("SIPORDER", 9) ##SIP ORDER of A and B
            policy.set("PSIPORDER", 9) #SIP ORDER of AP and BP
            policy.set("PREORDER", 9) #PREDICTED SIP ORDER of AP and BP
        else:
            policy.set("SIPORDER", 5) ##SIP ORDER of A and B
            policy.set("PSIPORDER", 5) #SIP ORDER of AP and BP
            policy.set("PREORDER", 5) #PREDICTED SIP ORDER of AP and BP

        solvetansipOutput = doTansip.doTansip(matchListsForSolveTansip, policy=policy, camera=mapper.camera)
        wcsList  = doTansip.getwcsList(solvetansipOutput)

        #doTansip.memorydelete()

        wcsList = list(wcsList)
        wcsList.pop() #  last item is a summary
        print 'len(wcsList without last element):', len(wcsList)
  
    else:
        wcsList = []
        for md in metadata:
            wcs = afwImage.makeWcs(md)
            wcsList.append(wcs)


    if do_writeNewWcs == True:
        dataId = {'visit': visit} 
        #for i, wcs in enumerate(wcsList):
        for ccdId, wcs in zip(ccdIds, wcsList):        
            dataId['ccd'] = ccdId
            print 'dataId: ', dataId
            corrFile = butler.get('calexp', dataId)
            #exposure = corrFile[0]
            exposure = corrFile
            writeFitsWithNewWcs(exposure, wcs, dataId, butler)
        

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

    for wcs, matchList in zip(wcsList, matchLists):
        print '** wcs.hasDistortion():', wcs.hasDistortion()
        #print wcs.getFitsMetadata()

        #import pdb
        #pdb.set_trace()
   
        coordRaDec00 = wcs.pixelToSky(0, 0) # should be (1,1)? which is the coodinate origin?
        radec00 = [coordRaDec00.getLongitude().asDegrees(), coordRaDec00.getLatitude().asDegrees()]
        ccdPosXy = doTansip.getxglobal(radec00, solvetansipOutput)
        xCcdPos = ccdPosXy[0]
        yCcdPos = ccdPosXy[1]

        pix0 = afwGeom.Point2D(123, 456)
        sky = wcs.pixelToSky(pix0)
        pix1 = wcs.skyToPixel(sky)
        print pix0, pix1, pix0 - pix1
        print wcs.getFitsMetadata().toString()
        

        for m in matchList:
            # First is catalogue and second is detection
            #radec = m.first.getRaDec() # somehow this does not work. probably, due to simple catalog
            raAngle = m.first.getRa()
            decAngle = m.first.getDec()
            radec = afwCoord.Coord(raAngle, decAngle)            
            ra1.append(raAngle.asDegrees())
            dec1.append(decAngle.asDegrees())
    
            xDet = m.second.getX()
            yDet = m.second.getY()
            x1.append(xDet)
            y1.append(yDet)

            # Second is image, which needs to be re-computed from new wcs
            coordRadecFromXy = wcs.pixelToSky(xDet, yDet)
            ra2.append(coordRadecFromXy.getLongitude().asDegrees())
            dec2.append(coordRadecFromXy.getLatitude().asDegrees())

            ccdpixFromRadec = wcs.skyToPixel(raAngle, decAngle)
            x2.append(ccdpixFromRadec.getX())
            y2.append(ccdpixFromRadec.getY())

            # using okura-kun's functions
            radecRef = [raAngle.asDegrees(), decAngle.asDegrees()]
            xyFromRadec2 = doTansip.getxglobal(radecRef, solvetansipOutput)
            x2_2.append(xyFromRadec2[0] - xCcdPos)
            y2_2.append(xyFromRadec2[1] - yCcdPos)

            dSky.append(radec.angularSeparation(coordRadecFromXy).asDegrees() * 3600.0 )  # holds in arcsec
            dXY.append(numpy.hypot(xDet-ccdpixFromRadec.getX(), yDet-ccdpixFromRadec.getY()))
            dXY_2.append(numpy.hypot(xDet-xyFromRadec2[0], yDet-xyFromRadec2[1]))
    
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


    if False:
        plot.histogram(dSky, None, bins=bins, clip=3.0, gaussFit=None)
        plot.quivers(ra1, dec1, dRa, dDec, addUnitQuiver=1./3600)
        plot.close()


def writeFitsWithNewWcs(exposure, wcs, dataId, butler):

    exposure.setWcs(wcs)
    butler.log.log(butler.log.INFO, "writing a new FITS file with new WCS for %s" % dataId)
    try:
        #butler.outButler.put(exposure, 'revexp', dataId)
        butler.put(exposure, 'revexp', dataId)        
    except Exception, e:
        print "failed to write something: %s" % (e)


if __name__ == '__main__':

#    hsc_or_sc = 'suprimecam'
#    hsc_or_sc = 'hscsim'

    hsc_or_sc = sys.argv[1]
    visit = int(sys.argv[2])
    if len(sys.argv) == 4:
        rerun = sys.argv[3]
    else:
        rerun = None
 
    main(hsc_or_sc, rerun, visit)
