
import sys, re, os, math
import signal
import datetime
import time

import lsst.afw.cameraGeom.utils         as cameraGeomUtils
import hsc.meas.tansip.WCS_PL_MAINLib    as hscTansip
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
#    print type(matchList_address)
  
    WCSA_ASP = hscTansip.F_WCSA_TANSIP_V_local(matchList_address, metadata, policy, camera)
    print '... TAN-SIP fitting done.'
    return WCSA_ASP

def doTansip(matchListAllCcd, policy=None, camera=None, rerun=None):
    print '--- doTansip ---'
    metaTANSIP = hscTansip.F_WCS_EMPTYMETADATA()
    WCSA_ASP = getresultWcs(matchListAllCcd, metaTANSIP, policy, camera)

    return WCSA_ASP
def F_WCS_EMPTYMETADATA():
    metadata = hscTansip.F_WCS_EMPTYMETADATA()
    return metadata

def getwcsList(WCSA_ASP):
    return hscTansip.F_WCSA_PLMAIN_GETWCSLIST(WCSA_ASP)


def memorydelete(WCSA_ASP):
    hscTansip.F_WCSA_PLMAIN_MEMORYDELETE(WCSA_ASP)

#-----------------------------------------------------------------
#Output Functions : WCSA_ASP
#-----------------------------------------------------------------
def WCS_OUTPUT_SIP(WCSA_ASP,SIPFILENAME):
    hscTansip.F_WCSA_PLMAIN_OUTPUTSIP(WCSA_ASP,SIPFILENAME)
def WCS_INPUT_SIP(WCSA_ASP,SIPFILENAME):
    hscTansip.F_WCSA_PLMAIN_INPUTSIP(WCSA_ASP,SIPFILENAME)
def WCS_OUTPUT_CCD(WCSA_ASP,CCDFILENAME):
    hscTansip.F_WCSA_PLMAIN_OUTPUTCCD(WCSA_ASP,CCDFILENAME)
def WCS_INPUT_CCD(WCSA_ASP,CCDFILENAME):
    hscTansip.F_WCSA_PLMAIN_INPUTCCD(WCSA_ASP,CCDFILENAME)
#-----------------------------------------------------------------
#Simulation Functions : WCSA_ASP
#-----------------------------------------------------------------
def WCS_MAKE_SIMULATIONREFERENCE(HARD,CCDPOSfile,DISTfile,NSCALE,RANNUM,REFNUM):
    hscTansip.F_WCSA_PLMAIN_SIMULATION(HARD,CCDPOSfile,DISTfile,NSCALE,RANNUM,REFNUM)
def WCS_CALC_SIMULATIONDIFF(HARD,CCDPOSfile,DISTfile,CCDoutfile,RESoutfile,WCSA_ASP):
    hscTansip.F_WCSA_PLMAIN_SIMULATIONDIFF(HARD,CCDPOSfile,DISTfile,CCDoutfile,RESoutfile,WCSA_ASP)
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : SIP (Values of SIP having)
#-----------------------------------------------------------------


#-----------------------------------------------------------------
#Getting Functions : WCS : POSITION
#-----------------------------------------------------------------

#-----------------------------------------------------------------
#Getting Functions : WCS : SIP
#-----------------------------------------------------------------

#-----------------------------------------------------------------
#Getting Functions : WCS : CCD
#-----------------------------------------------------------------
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : POSITION (Values at arbitrary position)
#-----------------------------------------------------------------
def WCS_GET_POSITION_RADECfromLOCAL(WCSA_ASP,CID,XY):
    return hscTansip.F_WCSA_PLMAIN_GETPOSITION_RADECfromLOCAL(WCSA_ASP,CID,XY)
def WCS_GET_POSITION_RADECfromCRPIX(WCSA_ASP,CID,XY):
    return hscTansip.F_WCSA_PLMAIN_GETPOSITION_RADECfromCRPIX(WCSA_ASP,CID,XY)
def WCS_GET_POSITION_LOCALfromRADEC(WCSA_ASP,CID,XY):
    return hscTansip.F_WCSA_PLMAIN_GETPOSITION_LOCALfromRADEC(WCSA_ASP,CID,XY)
def WCS_GET_POSITION_CRPIXfromRADEC(WCSA_ASP,CID,XY):
    return hscTansip.F_WCSA_PLMAIN_GETPOSITION_CRPIXfromRADEC(WCSA_ASP,CID,XY)

def WCS_GET_POSITION_CCDIDLOCALfromGLOBAL(WCSA_ASP,XY):
    return hscTansip.F_WCSA_PLMAIN_GETPOSITION_CCDIDLOCALfromGLOBAL(WCSA_ASP,XY)
def WCS_GET_POSITION_GLOBALfromCCDIDLOCAL(WCSA_ASP,CCDID,XY):
    return hscTansip.F_WCSA_PLMAIN_GETPOSITION_GLOBALfromCCDIDLOCAL(WCSA_ASP,CCDID,XY)
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : REFERENCES (Values of References having)
#-----------------------------------------------------------------
def WCS_GET_REFERENCE_ID(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_ID(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CHIPID(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CHIPID(WCSA_ASP,CID)
def WCS_GET_REFERENCE_FLAG(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_FLAG(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_LOCAL(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_XYLOCAL(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_RADEC(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_XYRADEC(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_GLOBAL(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_XYGLOBAL(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_GLOBALCRPIX(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_XYGLOBALCRPIX(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_LOCALCRPIX(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_XYLOCALCRPIX(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_IMPIXEL(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_XYIMPIXEL(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_IMWORLD(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_XYIMWORLD(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_CONVERGENCE(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CAMERACONV(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_ROTATION(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CAMERAROT(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_SHEAR1(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CAMERASHEAR1(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_SHEAR2(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CAMERASHEAR2(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_MAGNIFICATION(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CAMERAMAGNIFICATION(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_PCONVERGENCE(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CAMERAPCONV(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_PROTATION(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CAMERAPROT(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_PSHEAR1(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CAMERAPSHEAR1(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_PSHEAR2(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CAMERAPSHEAR2(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_PMAGNIFICATION(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLMAIN_GETREF_CAMERAPMAGNIFICATION(WCSA_ASP,CID)

def WCS_GET_REFERENCE_INIDIVIDUAL(WCSA_ASP,REFID):
    return hscTansip.F_WCSA_PLMAIN_GETREF(WCSA_ASP,REFID)

#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : CCD (Values of CCD having)
#-----------------------------------------------------------------
def WCS_GET_CCD_ALL_CCDPOS(WCSA_ASP):#Vector((CCDID, X(pixel), Y(pixel), T(radian)))
    return hscTansip.F_WCSA_PLMAIN_GETCCDPOSITIONS(WCSA_ASP)
def WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,CID):#(CCDID, X(pixel), Y(pixel), T(radian))
    return hscTansip.F_WCSA_PLMAIN_GETCCDPOSITION(WCSA_ASP,CID)

#-----
#OLD
#-----

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
