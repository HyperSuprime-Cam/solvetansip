
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

def doTansip_getresultWcs(matchListAllCcd, metaTANSIP, policy=None, camera=None, rerun=None):
    print '--- doTansip_getresultWcs ---'
    """ Entry point for calling the global solvetansip fitter.

    Args:
        matchListAllCcd - SourceMatchList, e.g. from runHsc.doRun()
        policy          - pexPolicy; reads our own policy if None
        camera          - cameraGeom
        rerun           - ignored
    """
    
    if not policy:
        policyPath = os.path.join(os.getenv("SOLVETANSIP_DIR"), "policy", "WCS_MAKEAPROP.paf")
        policy = pexPolicy.Policy.createPolicy(policyPath)
    if not policy:
        raise RuntimeError("no policy available to doTansip()")
        
    if not camera:
        raise RuntimeError("no camera passed in to doTansip()")
    
    print "len(match)=%d order=(%d,%d,%d)" % (len(matchListAllCcd),
                                           policy.get('LSIPORDER'),
                                           policy.get('SIPORDER'),
                                           policy.get('PSIPORDER'))
    for i in range(len(matchListAllCcd)):
        m = matchListAllCcd[i]
        if not m:
            print "empty list for ccd %i: %s" % (i, m)
            matchListAllCcd[i] = []
            
    WCSCCP = hscTansip.F_WCS_TANSIP_V(matchListAllCcd, metaTANSIP, policy, camera)
    print '... TAN-SIP fitting done.'
    return WCSCCP

def doTansip(matchListAllCcd, policy=None, camera=None, rerun=None):
    print '--- doTansip ---'
    metaTANSIP = hscTansip.F_WCS_EMPTYMETADATA()
    WCSCCP = doTansip_getresultWcs(matchListAllCcd, metaTANSIP, policy, camera)
    resultWcs_V = WCSCCP.WCSPtr

    return resultWcs_V

def doTansip_CCP(matchListAllCcd, CPROP, CSIP, PAIR, policy=None, camera=None, rerun=None):
    print '--- doTansip ---'

    metaTANSIP = hscTansip.F_WCS_EMPTYMETADATA()
    WCSCCP = doTansip_getresultWcs(matchListAllCcd, metaTANSIP, policy, camera)
    resultWcs_V = WCSCCP.WCSPtr
    CPROP[0] = WCSCCP.CPROP
    CSIP[0] = WCSCCP.CSIP    PAIR[0] = WCSCCP.PAIR

    return resultWcs_V

def doTansip_meta(matchListAllCcd, metadata, policy=None, camera=None, rerun=None):
    print '--- doTansip_meta ---'
    metaTANSIP = hscTansip.F_WCS_EMPTYMETADATA()
    WCSCCP = doTansip_getresultWcs(matchListAllCcd, metaTANSIP, policy, camera)
    resultWcs_V = WCSCCP.WCSPtr
#add metaTANSIP in metadata
#
#
    return resultWcs_V
