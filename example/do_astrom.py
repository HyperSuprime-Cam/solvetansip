#!/usr/bin/env python
#
# Author: FH, original scripts derived from Steve Bickerton's 
# Created: 
# 
"""
%prog [options]                        (runs on a default frame)
%prog [options] fitsFile               (runs on fitsFile)
%prog [options] progId frameId ccdId   (runs on SuprimeCam: progId frameId ccdId)
"""

import sys, re, os, math
import optparse
import eups
import signal
import datetime
import time

import hsc.camera.data                   as data
import hsc.protoPipe                     as pipe
import hsc.protoPipe.utils               as pipeUtils
import hsc.isr.isr                       as isr

import lsst.afw.detection                as afwDet
import lsst.afw.image                    as afwImage
import lsst.afw.coord                    as afwCoord
import lsst.afw.geom                     as afwGeom
import lsst.afw.cameraGeom               as cameraGeom
import lsst.afw.cameraGeom.utils         as cameraGeomUtils
import lsst.daf.base                     as dafBase
import lsst.meas.astrom                  as measAstrom
import lsst.meas.astrom.net              as astromNet
import lsst.meas.astrom.sip              as astromSip
import lsst.meas.astrom.sip.cleanBadPoints as cleanBadPoints

#import hsc.meas.match.matchLib as hscMatch

import lsst.meas.algorithms              as measAlg
import lsst.meas.algorithms.defects      as maDefects
import lsst.meas.algorithms.Psf          as maPsf
import lsst.pex.policy                   as pexPolicy
import lsst.sdqa                         as sdqa

import lsst.meas.utils.sourceMeasurement as srcMeas
import lsst.meas.utils.sourceDetection   as srcDet

import lsst.afw.display.ds9              as ds9


import hsc.meas.tansip.tansip    as tansip
#import pickle

# suppress low level messages
import lsst.pex.logging                  as pexLog
scriptLog = pexLog.getDefaultLog()
scriptLog.setThreshold(pexLog.Log.INFO)



class TimeoutError(RuntimeError):
    pass

def alrmHandler(signum, frame):
    print "SIGALRM ",
    raise TimeoutError 

class Profiler(object):
    def __init__(self, printRealtime):
        self.t0 = time.time()
        self.prev = self.t0
        self.message = []
        self.printRealtime = printRealtime
        
    def elapsed(self, message):
        now = time.time()
        elapsed = now - self.prev
        total = now - self.t0
        self.prev = now
        fullmsg = "%20s:  Elapsed: %6.2f  Total: %6.2f" % (message, elapsed, total)
        self.message.append(fullmsg)
        if self.printRealtime:
            print fullmsg

    def summary(self):
        print "\n".join(self.message)
        



def getOutputListHsc():
    outlist = [
        # label    get method        set method       headformat   dataformat   pytype   bits  fitstype
        ["id",     "getId",          "setId",         "%4s",       "%05d",       int,   32,   "I"],
        ["amp",    "getAmpExposureId","setAmpExposureId", "%4s",       "%04d",   int,   32,   "I"],
        ["x",      "getXAstrom",     "setXAstrom",    "%8s",       "%8.3f",     float,   32,   "E"],
        ["xerr",   "getXAstromErr",  "setXAstromErr", "%8s",       "%8.3f",     float,   32,   "E"],
        ["y",      "getYAstrom",     "setYAstrom",    "%8s",       "%8.3f",     float,   32,   "E"],
        ["yerr",   "getYAstromErr",  "setYAstromErr", "%8s",       "%8.3f",     float,   32,   "E"],
        
        ["ra",     "getRa",           "setRa",           "%10s",       "%10.6f",     float,   32,   "E"],
        #["raErr",  "getRaErrForWcs",  "setRaErrForWcs",  "%10s",       "%10.6f",     float,   32,   "E"],
        ["dec",    "getDec",          "setDec",          "%10s",       "%10.6f",     float,   32,   "E"],
        #["decErr", "getDecErrForWcs", "setDecErrForWcs", "%10s",       "%10.6f",     float,   32,   "E"],
        
        ["Ixx",    "getIxx",         "setIxx",        "%9s",       "%9.3f",     float,   32,   "E"],
        ["Ixy",    "getIxy",         "setIxy",        "%9s",       "%9.3f",     float,   32,   "E"],
        ["Iyy",    "getIyy",         "setIyy",        "%9s",       "%9.3f",     float,   32,   "E"],
        ["f_psf",  "getPsfFlux",     "setPsfFlux",    "%11s",      "%11.1f",    float,   32,   "E"],
        ["f_ap",   "getApFlux",      "setApFlux",     "%11s",      "%11.1f",    float,   32,   "E"],
        ["flags",  "getFlagForDetection", "setFlagForDetection",
         "%6s",        "0x%04x",      int,     16,   "I"],
        ]

    # lets put the entries in a dictionary,
    # ... we'll never remember which index has, say, the 'get' method stored.
    dictList = []
    for out in outlist:
        outdict = { "label":out[0],      # The label to use in the header
                    "get": out[1],       # the method to call to get the value
                    "set": out[2],       # the method to call to set the value
                    "headform": out[3],  # the format string (c-style) for the header label
                    "dataform": out[4],  # the format string (c-style) for the data
                    "pytype": out[5],    # the python type function to cast an input value to
                    "dtype": out[5].__name__ + str(out[6]),  # the dtype string (eg int32) for fits header
                    "bits": out[6],      # the number of bits for the value (needed as flags are 16 bit)
                    "fitstype": out[7],  # The fits type (I, E, etc) to write file
                    }
        dictList.append(outdict)
        return dictList
    
def getOutputList(style):
    outputLists = {"hsc" : getOutputListHsc}
    
    if outputLists.has_key(style):
        return (outputLists[style])()
    else:
        return (outputLists["hsc"])()
    

###################################################################
# utility to show the bits set in the flag
###################################################################
def showBits(x, width):
    s = ""
    for i in xrange(width - 1, -1, -1):
        shift = x >> i
        digit = str(shift & 1)
        if (i % 4 == 0 and i > 0):
            digit += "_"
            s += digit
            return s
                                                        
    
# -----------------------------------------------------------
def showMatchListInfo(matchList):
# -----------------------------------------------------------

    print '-------------------------------------------------'
    print '  match List: ', 'num of paris = ', len(matchList)
    print '-------------------------------------------------'

    for sourceMatch in matchList:
        s_ref=sourceMatch.first
        s_det=sourceMatch.second
#        refid = s_ref.getId()  # no ID for reference listed at present
        det_id = s_det.getId()  # this is ID for detected object 
        ra_ref = s_ref.getRa()
        dec_ref = s_ref.getDec()
        x_obj = s_det.getXAstrom()
        y_obj = s_det.getYAstrom()
        x_err = s_det.getXAstromErr()
        y_err = s_det.getYAstromErr()
        flux_psf = s_det.getPsfFlux()
        flux_ap = s_det.getApFlux()
            
        print '#detid: %d ' % det_id,
        print '#ref: ra %f dec %f ' % (ra_ref, dec_ref),
        print '#det:  x %f y %f  ' % (x_obj, y_obj),
        print 'xerr %f yerr %f ' % (x_err, y_err),
        print 'fpsf %f fap %f ' % (flux_psf, flux_ap)


#############################################################
#
# Main body of code
#
#############################################################

# -----------------------------------------------------------
def main(frameList=None, datadir='.', writeMatchList=False, readMatchList=False):
# -----------------------------------------------------------

    #writeMatchList = True


    # identify the root policy file
    ppPolicy = pipeUtils.getPolicyFile("hscProtopipe", "protoPipe.paf")


    nccd = len(frameList)
    print 'Number of CCDs: %d' % (nccd)
    
    matchListAllCcd = []

    # if readMachList is set to False, FITS data is processed
    #  to create matchList is created from FITS data matchList is read from ascii files
    # instead of processing each CCD.
    if readMatchList == False:
        for infile in frameList:

            matchListCcd = None
            
            outfile = datadir+'/out-'+infile
            infile  = datadir+'/'+infile
        
            matchListCcd = reduceOneCcd(infile=infile, outfile=outfile, writeMatchList=writeMatchList, ppPolicy=ppPolicy)
            matchListAllCcd.append(matchListCcd)

    else:
        matchListAllCcd = [] 
        for infile in frameList:

            matchListCcd = None

            outfile = datadir+'/out-'+infile
            infile  = datadir+'/'+infile
        
            basename = re.sub(".dat$", "", outfile)
            if re.search(".fits$", outfile):
                basename = re.sub(".fits$", "", outfile)

            if re.search(".fits$", outfile):
                sourceSet, matchListCcd, hdrInfo = pipe.io.readFits(basename + "-pre")
            else:
                sourceSet, matchListCcd, hdrInfo = pipe.io.readText(basename + "-pre")

            print '=========== ',infile, ' ============'
            showMatchListInfo(matchListCcd)

            matchListAllCcd.append(matchListCcd)        


    # Preparing policy for TanSip fitting

    # load the protoPipe policy file
    # test 
    print "--- Policy ---" # check
    print "--- Policy:APROP ---" # check
#    ppPolicy = pipeUtils.getPolicyFile("core", "protoPipe.paf")
    ppPolicy = pipeUtils.getPolicyFromFile(ppPolicy, None)
    APROPPolicy = pipeUtils.getPolicyFromPolicy(ppPolicy, "tansipPolicyFile", None)

    print "--- Policy:CPROP ---" # check
    mgr = data.Manager(progId=None)
    geomPolicy = mgr.getGeomPolicy()
    camera = cameraGeomUtils.makeCamera(geomPolicy)
    ccdId = 0
    ccd = cameraGeomUtils.findCcd(camera, cameraGeom.Id(ccdId))

    fileName = datadir+'/'+frameList[0] # just for test. use 1st frame to generate metadata here
    print "--- metadata ---" # check
    metadata = afwImage.readMetadata(fileName)

    resultWcs_V = tansip.F_WCS_TANSIP_V(matchListAllCcd,APROPPolicy,camera,metadata, True)#vector of lsst::afw::image::TanWcs::Ptr
#    tansip.F_WCS_TANSIP_TEST(resultWcs_V)


    print '... TAN-SIP fitting done.'
#    for i in resultWcs_V:
 #       print (i.getFitsMetadata()).toString()
#    print (resultWcs.getFitsMetadata()).toString()

    for infile in frameList:

        fileName = datadir+'/'+infile
        basename = re.sub(".fits$", "", infile)
        outFileName = datadir+'/'+'out-'+basename+'-wcs.fits'

        metadata = afwImage.readMetadata(fileName)
        # read/create our MaskedImage
        hdu = 0
        img = afwImage.ImageF(fileName, hdu, metadata)

        print metadata.get("CRPIX1")
        #print metadata.get("B_ORDER")
        #print metadata.get("B_0_0")

        msk = afwImage.MaskU(img.getDimensions(), 0x0)
        var = afwImage.ImageF(img, True) # a very sleazy thing to do!
        mImg = afwImage.MaskedImageF(img, msk, var) # read MaskedImage

        # making exposure with wcs 
        #wcs = afwImage.makeWcs(metadata)
        exposure = afwImage.makeExposure(mImg, resultWcs_V[0])
        print 'wcs pixel origin: ', exposure.getWcs().getPixelOrigin()
        #exposure.setWcs(resultWcs)

        #exposure.getMaskedImage().writeFits(outFileName)
        exposure.writeFits(outFileName)


# -----------------------------------------------------------
def reduceOneCcd(infile=None, outfile="out.fits", ppPolicy=None, hdu=0,
                 bbox=None, display=False, writeMatchList=False):
# -----------------------------------------------------------
    frameId=None
    ccdId =None
    progId=None
        
    if not ppPolicy:
        ppPolicy = pipeUtils.getPolicyFile("hscProtopipe", "protoPipe.paf")

    printRealtime = True
    profiler = Profiler(printRealtime)

    isForMonet = True
        
    maPsf.display = display
    displayScale = "histequ"
    if display and isinstance(display, bool):
        display = dict(raw = True,
                       isr = True,
                       corrected = True,
                       subtracted = True,
                       detected = True,
                       )
    else:
        display = {}

        
    basename = re.sub(".dat$", "", outfile)
    if re.search(".fits$", outfile):
        basename = re.sub(".fits$", "", outfile)
    
        
    # load the protoPipe policy file
    ppPolicy = pipeUtils.getPolicyFromFile(ppPolicy, None)
    #
    # Get defaults
    #
    d = ppPolicy.get("defaultFileInfo")
    if frameId is None:
        frameId = d.get("frameId")
    if ccdId is None:
        ccdId = d.get("ccdId")
    if progId is None:
        progId = d.get("progId")

        
    mgr      = data.Manager(progId=progId)

#    print '===='
#    print mgr.getGeomPolicy()

    camera = cameraGeomUtils.makeCamera(mgr.getGeomPolicy())
    ccd    = cameraGeomUtils.findCcd(camera, cameraGeom.Id(ccdId))

    fileName = infile
#    fileName = mgr.getRawFilename(frameId, ccdId, progId)
#    fileName = "sgagp_RH080801object187_satsuki.fits"
#    fileName = "ssb.fits"
    metadata = afwImage.readMetadata(fileName)

    # read/create our MaskedImage
    img = afwImage.ImageF(fileName, hdu, metadata)
    msk = afwImage.MaskU(img.getDimensions(), 0x0)
    var = afwImage.ImageF(img, True) # a very sleazy thing to do!
    mImg = afwImage.MaskedImageF(img, msk, var) # read MaskedImage

    filt = mgr.getFilter(frameId)

    # values we want in the primary header of the output fits table
    hdrInfo = {
        "FRAMEID" : frameId,
        "CCDID"   : mgr.getCcdId(ccdId),
        "PROGID"  : progId,

        # boresight coords
        "RA2000"      : metadata.get('RA')[0],
        "DEC2000"     : metadata.get('DEC')[0],
#        "RA2000"  : metadata.get('RA2000')[0],
#        "DEC2000" : metadata.get('DEC2000')[0],

        # other details
#        "MJD"     : metadata.get("MJD")[0],
#        "TIMESYS" : metadata.get("TIMESYS")[0],
        "EXPTIME" : metadata.get("EXPTIME")[0],
        "GAIN"    : metadata.get("GAIN")[0],
#        "SEEING"  : metadata.get("SEEING")[0],
        }


    
    if display and display["raw"]:
        ds9.mtv(mImg, frame=1, title="Raw")

    pexLog.Log(pexLog.Log.INFO, "Reducing file: " + fileName)

    ##########################################################################
    ### get all policy files ###

    cgPolicy       = pipeUtils.getPolicyFromPolicy(ppPolicy, "cgPolicyFile", None)         # cameraGeom
    bpPolicy       = pipeUtils.getFileFromPolicy(ppPolicy, "cgPolicyFile", None)           # badpix
    crPolicy       = pipeUtils.getPolicyFromPolicy(ppPolicy, "crPolicyFile", None)         # Cosmic rays
    satPolicy      = pipeUtils.getPolicyFromPolicy(ppPolicy, "satPolicyFile", None)        # Saturation
    bgPolicy       = pipeUtils.getPolicyFromPolicy(ppPolicy, "bgPolicyFile",
                                                   "parameters.backgroundPolicy")          # background
    subBgPolicy    = pipeUtils.getPolicyFromPolicy(ppPolicy, "bgPolicyFile",
                                                   "parameters.subtractBackground")        # background
    sdPolicy       = pipeUtils.getPolicyFromPolicy(ppPolicy, "sdPolicyFile", None)         # source detection
    moPolicy       = pipeUtils.getPolicyFromPolicy(ppPolicy, "moPolicyFile",
                                                   "measureObjects")                       # measure objects
    wcsPolicy      = pipeUtils.getPolicyFromPolicy(ppPolicy, "wcsPolicyFile", None)        # wcs
    psfPolicy      = pipeUtils.getPolicyFromPolicy(ppPolicy, "psfPolicyFile",
                                                   "parameters")                           # psf

        
    wcs = afwImage.makeWcs(metadata)
    pixscale = 3600*math.sqrt(wcs.pixArea(wcs.getSkyOrigin()))
    FWHM = 2.0
    psf = measAlg.createPSF("SingleGaussian", 15, 15, FWHM/(2*math.sqrt(2*math.log(2))))

    mImg.getMask().addMaskPlane("DETECTED")
    mImg.getMask().addMaskPlane("SAT")
    mImg.getMask().addMaskPlane("CR")
    exposure = afwImage.makeExposure(mImg, wcs)
    exposure.setMetadata(metadata)

    bgPolicy.set("binsize", 256) # sleazy flat

    sdPolicy.set("thresholdValue", 4.0)
    
    wcsPolicy.set("numBrightStars", 250)
    wcsPolicy.set("matchThreshold", 20.0) #perhaps sketchy
    #wcsPolicy.set("calculateSip", True)  #perhaps sketchy
    wcsPolicy.set("calculateSip", False)  #perhaps sketchy
    wcsPolicy.set("distanceForCatalogueMatchinArcsec", 2.0)
    #wcsPolicy.set("distanceForCatalogueMatchinArcsec", 100.0)
    #wcsPolicy.set("wcsToleranceInArcsec", 2.0)
    wcsPolicy.set("sipOrder", 4)
    wcsPolicy.set("defaultFilterName", "SORTMAG")
#    wcsPolicy.set("defaultFilterName", "mag")
#    wcsPolicy.set("defaultFilterName", "W-S-I+")

    #psfPolicy.set("algorithm", "SingleGaussian")
    #crPolicy.set("minSigma", 6.0)
    
    moPolicy.set("apRadius", 7.0)

    profiler.elapsed("Initialization")


    wcsOnly = False #True
    

    #########################################################################
    # Detection
    #########################################################################
    if (not wcsOnly):
        footprintSetPositive, footprintSetNegative = srcDet.detectSources(exposure, psf, sdPolicy)

        if display and display["detected"]:
            ds9.mtv(exposure.getMaskedImage(), frame=4, title="Post detect")

    profiler.elapsed("Detection")

    #########################################################################
    # Measurement
    #########################################################################
    if (not wcsOnly):
        footprintList = [ [footprintSetPositive.getFootprints(), False] ]
        sourceSet = srcMeas.sourceMeasurement(exposure, psf, footprintList, moPolicy)

    #sourceSet = pipe.io.readText("pre-" + re.sub(".dat$", "", outfile))
    
        if display and display["detected"]:
            if False:
                xcArr, ycArr = [], []
            for source in sourceSet:
                xc, yc = source.getXAstrom() - mImg.getX0(), source.getYAstrom() - mImg.getY0()
                if False:
                    ds9.dot("%d" % (source.getId()), xc, yc + 30, frame=4)
                if True:
                    ds9.dot("o", xc, yc, size = 2, frame=4)
                else:
                    xcArr.append(xc)
                    ycArr.append(yc)
            if False:                       # needs changes to ds9.py
                ds9.dot("o", xcArr, ycArr, size = 2, frame=4)

            
        ###########################################

        # remove nan's from the coords
        tmpSourceSet = []
        for source in sourceSet:
            xc, yc = source.getXAstrom(), source.getYAstrom()

            # stash the RaDec based on the header wcs
            radec = wcs.pixelToSky(afwGeom.makePointD(xc, yc))
            source.setRa(radec.getLongitude(afwCoord.DEGREES))
            source.setDec(radec.getLatitude(afwCoord.DEGREES))

            # This checks for NaN ... NaN does not equal itself
            if ( xc != xc or yc != yc ): 
                continue

            tmpSourceSet.append([source.getPsfFlux(), source])

        goodTmpSourceSet = sorted(tmpSourceSet, key=lambda x: x[0], reverse=True)[:]

        goodSourceSet = afwDet.SourceSet()
        for flux, source in goodTmpSourceSet:
            goodSourceSet.append(source)

        sourceSet = goodSourceSet[0:500]

        if display and display["detected"]:
            if False:
                xcArr, ycArr = [], []
            for source in sourceSet:
                xc, yc = source.getXAstrom() - mImg.getX0(), source.getYAstrom() - mImg.getY0()
                if False:
                    ds9.dot("%d" % (source.getId()), xc, yc + 30, frame=4)
                if True:
                    ds9.dot("o", xc, yc, size = 6, frame=4, ctype="red")
                else:
                    xcArr.append(xc)
                    ycArr.append(yc)
            if False:                       # needs changes to ds9.py
                ds9.dot("o", xcArr, ycArr, size = 2, frame=4)


        
    profiler.elapsed("Measurement")
    
    #########################################################################
    # pre-output - in case wcs doesn't converge (we'll overwrite this later)
    #########################################################################
    
    # create a phony matchList
    if (not wcsOnly):
        matchList = []
        if re.search(".fits$", outfile):
            pipe.io.writeFits(sourceSet, matchList, hdrInfo, basename + "-pre")
        else:
            pipe.io.writeText(sourceSet, matchList, hdrInfo, basename + "-pre")

        exposure.getMaskedImage().writeFits(basename + "-mImg.fits")
    else: # wcsOnly
        matchList = []
        if re.search(".fits$", outfile):
            sourceSet, matchList, hdrInfo = pipe.io.readFits(basename + "-pre")
        else:
            sourceSet, matchList, hdrInfo = pipe.io.readText(basename + "-pre")

        
    #########################################################################
    # WCS
    #########################################################################
    # wcsSucceeded = False
    if True:  # not isForMonet:
        date1 = datetime.datetime.now().strftime("%a %Y-%m-%d %H:%M:%S")


        matchList, wcs2 = measAstrom.determineWcs(wcsPolicy, exposure, sourceSet)

        if writeMatchList == True:
            if re.search(".fits$", outfile):
                pipe.io.writeFits(sourceSet, matchList, hdrInfo, basename + "-pre")
                # testing text output
                #pipe.io.writeText(sourceSet, matchList, hdrInfo, basename + "-pre")
            else:
                pipe.io.writeText(sourceSet, matchList, hdrInfo, basename + "-pre")


            outMatchListName = infile + '.matchList.dat'
            print 'Writing matchList into %s ...' % outMatchListName
            f=open(outMatchListName, "w")
            for sourceMatch in matchList:
                s_ref=sourceMatch.first
                s_det=sourceMatch.second

                det_id = s_det.getId()
                ra_ref = s_ref.getRa()
                dec_ref = s_ref.getDec()
                x_obj = s_det.getXAstrom()
                y_obj = s_det.getYAstrom()
                x_err = s_det.getXAstromErr()
                y_err = s_det.getYAstromErr()
                flux_psf = s_det.getPsfFlux()
                flux_ap = s_det.getApFlux()
                f.write('%4d  100  ' % det_id)  # 100 is magic number for identifying stars in the list
                f.write('%f %f ' % (x_obj, y_obj))
                f.write('%f %f ' % (ra_ref, dec_ref))
                f.write('%f %f ' % (x_err, y_err))
                f.write('%f %f ' % (flux_psf, flux_ap))
                f.write('\n')
            f.close()


        print '=========== ',infile, ' ============'
        showMatchListInfo(matchList)

        # Calling Okura-kun's WCS-fitting Function
        #configfile_directory = '.'
        #tansip.fitWcsTansip(matchList, configfile_directory, True)
        #return 0


        return matchList


#            s1 = sourceMatch.first
#            s2 = sourceMatch.second
#            # output a value according to the output list defined above
#            for output in getOutputList("hsc"):
#                if re.search("^(ra|dec)$", output["label"]):
#                    s = s1
#                else:
#                    s = s2
#                  getMethod = getattr(s, output["get"])
#                    if re.search("x", output["dataform"]):
#                        value = getMethod()
#                        print "%s " % (showBits(value, 16)),
#                        print output["dataform"] % (value),
#                    else:
#                        print output["dataform"] % (getMethod()),
#                        print "\n",

        # std::vector< det::SourceMatch > lsst::meas::astrom::sip::MatchSrcToCatalogue::getMatches
         # lsst::afw::detection::SourceMatch::SourceMatch(Source::Ptr const & s1,
        #                                               Source::Ptr const & s2,
        #                                               double dist
        #                                               ) [inline]


        date2 = datetime.datetime.now().strftime("%a %Y-%m-%d %H:%M:%S")
        print "Match times: ", date1, date2

        # see if we got a new wcs ... there must be a better way
        c1 = wcs.pixelToSky(1.0, 1.0)
        c2 = wcs2.pixelToSky(1.0, 1.0)

        wcsTol = 1.0e-9
        if ( abs(c1[0] - c2[0]) < wcsTol  and  abs(c1[1] - c2[1]) < wcsTol ):
            wcsSucceeded = True
        print "WCS: ", len(matchList), wcsSucceeded

        
        # put the sources on the new wcs
        for s in sourceSet:
            c = wcs2.pixelToSky(s.getXAstrom(), s.getYAstrom())
            s.setRa(c[0])
            s.setDec(c[1])
            s.setAmpExposureId(mgr.getCcdId(ccdId));


        if False:
            for m in matchList:
                ra1, dec1 = m.first.getRa(), m.first.getDec()
                ra2, dec2 = m.second.getRa(), m.second.getDec()
                print "Foooo:   ", ra1, ra2, dec1, dec2
            
        #sys.exit(1)
            
    profiler.elapsed("WCS")

    
    #########################################################################
    # Output
    #########################################################################
    if re.search(".fits$", outfile):
        pipe.io.writeFits(sourceSet, matchList, hdrInfo, basename)
    else:
        pipe.io.writeText(sourceSet, matchList, hdrInfo, basename)

    # Note: input can be loaded with
    #sourceSetIn = pipe.io.readText(re.sub(".dat$", "", outfile))
    #sourceSetIn2 = pipe.io.readFits(re.sub(".fits$", "", outfile))


    #########################################################################
    # PSF estimation
    #########################################################################

    if False:
    ######if not isForMonet:
        date1 = datetime.datetime.now().strftime("%a %Y-%m-%d %H:%M:%S")
        sdqaRatings = sdqa.SdqaRatingSet()
        psf, cellSet = maPsf.getPsf(exposure, sourceSet, psfPolicy.get("psfDeterminationPolicy"), sdqaRatings)
        date2 = datetime.datetime.now().strftime("%a %Y-%m-%d %H:%M:%S")
        print "Psf times: ", date1, date2
        psfOutfile = basename + "-psf.boost"
        pipeUtils.psfIO(psfOutfile, "w", psf)

    # use new wcs/psf to remeasure fainter sources?
    profiler.elapsed("PSF")
    

    #-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    #-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


def mkFrameList(datadir, framefile):

    frameList = []
    #datadir='data'
    #framefile = datadir + '/' + 'hsc_5ccd.lis'
    #framefile = datadir + '/' + 'ccd.lis'
    framefile = datadir + '/' + framefile

    for line in open(framefile): 
        if line[0].startswith('#') == False:
            line = line.split()
            ccdid = line[0] 
            #ccdfile = 'ssb_ccd' + ccdid + '.fits'
            ccdfile = ccdid

            frameList.append(ccdfile)

    return frameList


#############################################################
# end
#############################################################

if __name__ == '__main__':

    if False:
        xy0 = afwImage.PointI(1150, 1250)
        bbox = afwImage.BBox(xy0, 512, 512)
    else:
        bbox = None


    datadir = 'supa_cfhqs'          # data directory which contains FITS data and frameFile 
    frameFile = 'supa_ccd.lis' # ascii table listing FITS file names
#    datadir = 'cosmosTest'          # data directory which contains FITS data and frameFile 
#    frameFile = 'hsc_3ccd.lis' # ascii table listing FITS file names

#    frameFile = 'cosmosTest.lis' # ascii table listing FITS file names
#    frameFile = 'hsc_104ccd.lis'

    frameList = mkFrameList(datadir, frameFile)

    print '==== input frame list ==='
    print frameList


    #main(frameList, datadir, writeMatchList=True, readMatchList=False)
    main(frameList, datadir, readMatchList=True)
