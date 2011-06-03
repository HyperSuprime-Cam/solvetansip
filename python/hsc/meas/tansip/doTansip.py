
import sys, re, os, math
import signal
import datetime
import time

import lsst.afw.cameraGeom.utils         as cameraGeomUtils
import hsc.meas.tansip.WCS_PL_MAIN       as hscTansip
import lsst.daf.base                     as dafBase
import lsst.pex.policy as pexPolicy
import lsst.afw.image as afwImage

import lsst.afw.display.ds9              as ds9

# suppress low level messages
import lsst.pex.logging                  as pexLog
scriptLog = pexLog.getDefaultLog()
scriptLog.setThreshold(pexLog.Log.INFO)

def getresultWcs(matchListAllCcd, metadata, policy=None, camera=None, rerun=None):
    print '--- doTansip_getresultWcs ---'
    """ Entry point for calling the global solvetansip fitter.

    Args:
        matchListAllCcd - SourceMatchList, e.g. from runHsc.doRun()
        policy          - pexPolicy; reads our own policy if None
        camera          - cameraGeom
        rerun           - ignored
    """
        
    if not camera:
        raise RuntimeError("no camera passed in to doTansip()")

    defaultFile = pexPolicy.DefaultPolicyFile("SOLVETANSIP", "WCS_MAKEAPROP_Dictionary.paf", "policy")
    defaults = pexPolicy.Policy.createPolicy(defaultFile, defaultFile.getRepositoryPath())
    if policy:
        policy.mergeDefaults(defaults)
    else:
        policy = defaults
    
    print "len(match)=%d order=(%d,%d,%d)" % (len(matchListAllCcd),
                                           policy.get('LSIPORDER'),
                                           policy.get('SIPORDER'),
                                           policy.get('PSIPORDER'))
    for i in range(len(matchListAllCcd)):
        m = matchListAllCcd[i]
        if not m:
            print "empty list for ccd %i: %s" % (i, m)
            matchListAllCcd[i] = []
            
    WCSACCP = hscTansip.F_WCS_TANSIP_V(matchListAllCcd, metadata, policy, camera)
    print '... TAN-SIP fitting done.'
    return WCSACCP

def doTansip(matchListAllCcd, policy=None, camera=None, rerun=None):
    print '--- doTansip ---'
    metaTANSIP = hscTansip.F_WCS_EMPTYMETADATA()
    WCSACCP = getresultWcs(matchListAllCcd, metaTANSIP, policy, camera)

    return WCSACCP.WCSPtr

def getwcsList(WCSACCP):
    return hscTansip.F_WCS_GETWCSLIST(WCSACCP)

def getAPROP(WCSACCP):
    return hscTansip.F_WCS_GETAPROP(WCSACCP)

def getCPROP(WCSACCP):
    return hscTansip.F_WCS_GETCPROP(WCSACCP)

def getCSIP(WCSACCP):
    return hscTansip.F_WCS_GETCSIP(WCSACCP)

def getPAIR(WCSACCP):
    return hscTansip.F_WCS_GETPAIR(WCSACCP)

def getCPROPList(WCSACCP):
    return hscTansip.F_WCS_GETCPROPLIST(WCSACCP)

def getCSIPList(WCSACCP):
    return hscTansip.F_WCS_GETCSIPLIST(WCSACCP)
