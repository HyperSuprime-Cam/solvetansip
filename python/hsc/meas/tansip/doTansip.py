import sys, re, os, math
import signal
import datetime
import time

import lsst.afw.cameraGeom.utils         as cameraGeomUtils
import hsc.meas.tansip.WCS_PL_MAIN       as hscTansip
import lsst.daf.base                     as dafBase

import lsst.afw.display.ds9              as ds9

# suppress low level messages
import lsst.pex.logging                  as pexLog
scriptLog = pexLog.getDefaultLog()
scriptLog.setThreshold(pexLog.Log.INFO)

def doTansip(matchListAllCcd, policy=None, camera=None, rerun=None):
    """ Entry point for calling the global solvetansip fitter.

    Args:
        matchListAllCcd   - SourceMatchList, e.g. from reduceOneCcd.doOneCcd()
        ppPolicyFile      ? 
    """
    
    # load the policy contents from the ppPolicy file
    #if not ppPolicyFile:
    #    ppPolicyFile = pipeUtils.getPolicyFile("protoPipeDC1.paf")
    #ppPolicy = pexPolicy.Policy.createPolicy(ppPolicyFile)

    #APROPPolicy = pipeUtils.getPolicyFromPolicy(ppPolicy, "tansipPolicyFile")
    APROPPolicy = policy
    
    # dataManager for geometry information
    #if not mgr:
    #    mgr      = data.Manager(instrument="HSC", rerun=rerun)
    #camera = cameraGeomUtils.makeCamera(mgr.getGeomPolicy())

    print "len(match)=%d order=(%d,%d)" % (len(matchListAllCcd),
                                           APROPPolicy.get('SIPORDER'),
                                           APROPPolicy.get('PSIPORDER'))
    for i in range(len(matchListAllCcd)):
        m = matchListAllCcd[i]
        if not m:
            print "empty list for ccd %i: %s" % (i, m)
            matchListAllCcd[i] = []
            
    resultWcs_V = hscTansip.F_WCS_TANSIP_V(matchListAllCcd, APROPPolicy, camera)

    print '... TAN-SIP fitting done.'
    print 'size of resultWcs_V: ', len(resultWcs_V)

    return resultWcs_V
