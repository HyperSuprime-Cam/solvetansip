#!/usr/bin/env python
#------------------------------------------------------------
#WCS_MAIN.py
#main program for wcs in pipeline
#1:load parameter(APROP, CPROP, PAIR) from policy
#2:sent to F_WCS_TANSIP_V
#3:output wcs vector
#
#Last modification : 2011/02/22
#------------------------------------------------------------

import sys, re, os, math
import optparse
import eups
import signal
import datetime
import time

import hsc.protoPipe                     as pipe
import hsc.protoPipe.utils               as pipeUtils
import lsst.pex.policy                   as pexPolicy
import lsst.afw.cameraGeom.utils         as cameraGeomUtils
import hsc.camera.data                   as data

import hsc.meas.tansip.WCS_PL_MAIN       as tansip

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

def main():
    print "--- Policy ---" # check
    print "--- Policy : APROP ---" # check
    ppPolicyFile = pipeUtils.getPolicyFile ("protoPipe.paf")
    print ppPolicyFile # check
    ppPolicyFile = "/data/work/okura/HSC/DC2/solvetansip/policy/protoPipe.paf"
    print ppPolicyFile
    ppPolicy = pexPolicy.Policy.createPolicy(ppPolicyFile)    
#    print ppPolicy
    APROPPolicy = pipeUtils.getPolicyFromPolicy(ppPolicy, "tansip")
    print APROPPolicy

    print "--- Policy : CPROP ---" # check
    progId = None
    d = ppPolicy.get("defaultFileInfo")
    if progId is None:
        progId = d.get("progId")
    mgr = data.Manager(progId=progId)#assign .paf file
    geomPolicy = mgr.getGeomPolicy()
    camera = cameraGeomUtils.makeCamera(geomPolicy)
#    print geomPolicy

    print "--- Matchlist ---" # check
    readMatchList = True
    datadir = 'supa_cfhqs'
    frameFile = 'supa_ccd.lis'
    frameList = mkFrameList(datadir, frameFile)
    print frameList

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

#    print "--- metadata ---" # check
#    fileName = datadir+'/'+frameList[0] # just for test. use 1st frame to generate metadata here
#    metadata = afwImage.readMetadata(fileName)

    print "--- F_WCS_TANSIP_V ---" # check
    resultWcs_V = tansip.F_WCS_TANSIP_V(matchListAllCcd,APROPPolicy,camera)#vector of lsst::afw::image::TanWcs::Ptr
#    resultWcs_V = tansip.F_WCS_TANSIP_V(matchListAllCcd,APROPPolicy,camera,metadata, True)#vector of lsst::afw::image::TanWcs::Ptr
##    tansip.F_WCS_TANSIP_TEST(resultWcs_V)
    for i in resultWcs_V:
        print (i.getFitsMetadata()).toString()
#
    print "--- ZZZ ---" # check

if __name__ == '__main__':
    main()


