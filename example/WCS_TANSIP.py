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

import hsc.meas.tansip.tansip              as tansip
#import hsc.meas.solve.tansip_solveLib     as tansip
#import tansip_solveLib     as tansip

# suppress low level messages
import lsst.pex.logging                  as pexLog

#############################################################
#
# Main body of code
#
#############################################################
from types import *

print "--- AAA ---" # check
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
            
#        print '#detid: %d ' % det_id,
 #       print '#ref: ra %f dec %f ' % (ra_ref, dec_ref),
  #      print '#det:  x %f y %f  ' % (x_obj, y_obj),
   #     print 'xerr %f yerr %f ' % (x_err, y_err),
    #    print 'fpsf %f fap %f ' % (flux_psf, flux_ap)
def mkFrameList(datadir, framefile):

    frameList = []
    framefile = datadir + '/' + framefile

    for line in open(framefile): 
        if line[0].startswith('#') == False:
            line = line.split()
            ccdid = line[0] 
            #ccdfile = 'ssb_ccd' + ccdid + '.fits'
            ccdfile = ccdid

            frameList.append(ccdfile)

    return frameList

#def main():
def main(frameList=None, datadir='.', writeMatchList=False, readMatchList=False):
    print "--- Policy ---" # check
    print "--- Policy:APROP ---" # check

    ppPolicy = pipeUtils.getPolicyFile("hscProtopipe", "protoPipe.paf")
#    print ppPolicy # check

    ppPolicy = pipeUtils.getPolicyFromFile(ppPolicy, None)
#    print ppPolicy # check

    APROPPolicy = pipeUtils.getPolicyFromPolicy(ppPolicy, "tansipPolicyFile", None)
#    print "APROPPolicy : ",APROPPolicy #check
	
    print "--- Policy:CPROP ---" # check
    progId = None
    d = ppPolicy.get("defaultFileInfo")
    if progId is None:
        progId = d.get("progId")
    mgr = data.Manager(progId=progId)#assign .paf file
    geomPolicy = mgr.getGeomPolicy()
    camera = cameraGeomUtils.makeCamera(geomPolicy)

    print "--- Matchlist ---" # check
    if readMatchList == True:
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

    print "--- metadata ---" # check
    fileName = datadir+'/'+frameList[0] # just for test. use 1st frame to generate metadata here
    metadata = afwImage.readMetadata(fileName)

    print "--- F_WCS_TANSIP ---" # check
    resultWcs_V = tansip.F_WCS_TANSIP_V(matchListAllCcd,APROPPolicy,camera,metadata, True)#vector of lsst::afw::image::TanWcs::Ptr
#    tansip.F_WCS_TANSIP_TEST(resultWcs_V)
#    for i in resultWcs_V:
 #       print (i.getFitsMetadata()).toString()

    print "--- ZZZ ---" # check

if __name__ == '__main__':

    if False:
        xy0 = afwImage.PointI(1150, 1250)
        bbox = afwImage.BBox(xy0, 512, 512)
    else:
        bbox = None


    progId='CFHQS'
    frameId='SUPA0100518'

    datadir = 'supa_cfhqs'          # data directory which contains FITS data and frameFile 
    frameFile = 'supa_ccd.lis' # ascii table listing FITS file names

    frameList = mkFrameList(datadir, frameFile)

    print '==== input frame list ==='
    print frameList

#    main()
    main(frameList, datadir, readMatchList=True)

