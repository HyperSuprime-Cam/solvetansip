
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
            
    WCSA_ASP = hscTansip.F_WCSA_TANSIP_V(matchListAllCcd, metadata, policy, camera)
    print '... TAN-SIP fitting done.'
    return WCSA_ASP

def getresultWcs_local(matchList_address, metadata, policy=None, camera=None, rerun=None):
    print '--- doTansip_getresultWcs ---'
    """ Entry point for calling the global solvetansip fitter.

    Args:
        matchList_address - local address of matchlist txt
        policy            - pexPolicy; reads our own policy if None
        camera            - cameraGeom
        rerun             - ignored
    """
        
    if not camera:
        raise RuntimeError("no camera passed in to doTansip()")

    defaultFile = pexPolicy.DefaultPolicyFile("SOLVETANSIP", "WCS_MAKEAPROP_Dictionary.paf", "policy")
    defaults = pexPolicy.Policy.createPolicy(defaultFile, defaultFile.getRepositoryPath())
    if policy:
        policy.mergeDefaults(defaults)
    else:
        policy = defaults
          
    print matchList_address
    print type(matchList_address)
  
    WCSA_ASP = hscTansip.F_WCSA_TANSIP_V_local(matchList_address, metadata, policy, camera)
    print '... TAN-SIP fitting done.'
    return WCSA_ASP

def doTansip(matchListAllCcd, policy=None, camera=None, rerun=None):
    print '--- doTansip ---'
    metaTANSIP = hscTansip.F_WCS_EMPTYMETADATA()
    WCSA_ASP = getresultWcs(matchListAllCcd, metaTANSIP, policy, camera)

    return WCSA_ASP

def getwcsList(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETWCSLIST(WCSA_ASP)

def getccdpositions(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETCCDPOSITIONS(WCSA_ASP)

def getreferences(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETREFERENCES(WCSA_ASP)

def getradec(X_GLOBAL,WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETRADEC(X_GLOBAL,WCSA_ASP)

def getxglobal(RADEC,WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETX_GLOBAL(RADEC,WCSA_ASP)
#GET PAIR
def getpair_ID(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_ID(WCSA_ASP)
def getpair_CHIPID(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_CHIPID(WCSA_ASP)
def getpair_FLAG(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_FLAG(WCSA_ASP)
def getpair_RA(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_RA(WCSA_ASP)
def getpair_DEC(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_DEC(WCSA_ASP)
def getpair_IM_WORLD_X(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_IM_WORLD_X(WCSA_ASP)
def getpair_IM_WORLD_Y(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_IM_WORLD_Y(WCSA_ASP)
def getpair_IM_PIXEL_X(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_IM_PIXEL_X(WCSA_ASP)
def getpair_IM_PIXEL_Y(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_IM_PIXEL_Y(WCSA_ASP)
def getpair_CRPIX_X(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_CRPIX_X(WCSA_ASP)
def getpair_CRPIX_Y(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_CRPIX_Y(WCSA_ASP)
def getpair_GLOBAL_X(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_GLOBAL_X(WCSA_ASP)
def getpair_GLOBAL_Y(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_GLOBAL_Y(WCSA_ASP)
def getpair_LOCAL_X(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_LOCAL_X(WCSA_ASP)
def getpair_LOCAL_Y(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETPAIR_LOCAL_Y(WCSA_ASP)
