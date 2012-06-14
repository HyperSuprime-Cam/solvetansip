
import sys, re, os, math
import signal
import datetime
import time
import numpy
import matplotlib.pyplot as plt

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
    print '--- getWCSlist ---'
    return hscTansip.F_WCSA_PLMAIN_GETWCSLIST(WCSA_ASP)


def memorydelete(WCSA_ASP):
    hscTansip.F_WCSA_PLMAIN_MEMORYDELETE(WCSA_ASP)

#-----------------------------------------------------------------
#Output Functions : WCSA_ASP
#-----------------------------------------------------------------
def WCS_OUTPUT_REFERENCES(WCSA_ASP,REFERENCESFILENAME):
    hscTansip.F_WCSA_PLMAIN_OUTPUTREFERENCES(WCSA_ASP,REFERENCESFILENAME)
def WCS_OUTPUT_SIPFIT(WCSA_ASP,SIPFITFILENAME):
    hscTansip.F_WCSA_PLMAIN_OUTPUTSIPFIT(WCSA_ASP,SIPFITFILENAME)
def WCS_OUTPUT_PSIPFIT(WCSA_ASP,PSIPFITFILENAME):
    hscTansip.F_WCSA_PLMAIN_OUTPUTPSIPFIT(WCSA_ASP,PSIPFITFILENAME)
def WCS_OUTPUT_SIP(WCSA_ASP,SIPFILENAME):
    hscTansip.F_WCSA_PLMAIN_OUTPUTSIP(WCSA_ASP,SIPFILENAME)
def WCS_INPUT_SIP(WCSA_ASP,SIPFILENAME):
    hscTansip.F_WCSA_PLMAIN_INPUTSIP(WCSA_ASP,SIPFILENAME)
def WCS_OUTPUT_CCD(WCSA_ASP,CCDFILENAME):
    hscTansip.F_WCSA_PLMAIN_OUTPUTCCD(WCSA_ASP,CCDFILENAME)
def WCS_INPUT_CCD(WCSA_ASP,CCDFILENAME):
    hscTansip.F_WCSA_PLMAIN_INPUTCCD(WCSA_ASP,CCDFILENAME)
def WCS_OUTPUT_CCDRMS(WCSA_ASP,REFERENCESFILENAME):
    hscTansip.F_WCSA_PLMAIN_OUTPUTCCDRMS(WCSA_ASP,REFERENCESFILENAME)
#-----------------------------------------------------------------
#Simulation Functions : WCSA_ASP
#-----------------------------------------------------------------
def WCS_MAKE_SIMULATIONREFERENCE(HARD,CCDPOSfile,DISTfile,NSCALE,RANNUM,REFNUM):
    hscTansip.F_WCSA_PLMAIN_SIMULATION(HARD,CCDPOSfile,DISTfile,NSCALE,RANNUM,REFNUM)
def WCS_CALC_SIMULATIONDIFF(HARD,CCDPOSfile,DISTfile,CCDoutfile,RESoutfile,WCSA_ASP):
    hscTansip.F_WCSA_PLMAIN_SIMULATIONDIFF(HARD,CCDPOSfile,DISTfile,CCDoutfile,RESoutfile,WCSA_ASP)
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : APROP
#-----------------------------------------------------------------
#def WCS_GET_APROP_CCDNUM(WCSA_ASP):
#    return hscTansip.F_WCSA_PLMAIN_GETAPROP_CCDNUM(WCSA_ASP)
#def WCS_GET_APROP_CRPIX(WCSA_ASP):
#    return hscTansip.F_WCSA_PLMAIN_GETAPROP_CRPIX(WCSA_ASP)
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : SIP (Values of SIP having)
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
#Getting Functions : WCSA_ASP : POSITION (Grid)
#-----------------------------------------------------------------
def WCS_GET_POSITION_RADECfromLOCALGRID(WCSA_ASP,CID,GRID):
    return hscTansip.F_WCSA_PLMAIN_GETPOSITION_RADECfromLOCALGRID(WCSA_ASP,CID,GRID)
def WCS_GET_POSITION_RADECfromCRPIXGRID(WCSA_ASP,CID,GRID):
    return hscTansip.F_WCSA_PLMAIN_GETPOSITION_RADECfromCRPIXGRID(WCSA_ASP,CID,GRID)
def WCS_GET_POSITION_LOCALfromRADECGRID(WCSA_ASP,CID,GRID):
    return hscTansip.F_WCSA_PLMAIN_GETPOSITION_LOCALfromRADECGRID(WCSA_ASP,CID,GRID)
def WCS_GET_POSITION_CRPIXfromRADECGRID(WCSA_ASP,CID,GRID):
    return hscTansip.F_WCSA_PLMAIN_GETPOSITION_CRPIXfromRADECGRID(WCSA_ASP,CID,GRID)

#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : JACOBIAN (Values at arbitrary position)
#-----------------------------------------------------------------
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : JACOBIAN (Grid)
#-----------------------------------------------------------------
def WCS_GET_CRSMA_atLOCALGRID(WCSA_ASP,CID,GRID):
    return hscTansip.F_WCSA_PLMAIN_GETCRSMA_atLOCALGRID(WCSA_ASP,CID,GRID)
def WCS_GET_CRSM_atLOCALGRID(WCSA_ASP,CID,CRSMID,X,Y):
    return hscTansip.F_WCSA_PLMAIN_GETCRSM_atLOCALGRID(WCSA_ASP,CID,CRSMID,X,Y)
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : DISTORTION (Grid)
#-----------------------------------------------------------------
def WCS_GET_DISTORTION_atCRPIXGRID(WCSA_ASP,GRID):
    return hscTansip.F_WCSA_PLMAIN_GETDISTORTION_atCRPIXGRID(WCSA_ASP,GRID)
def WCS_GET_DISTORTION_atRADECGRID(WCSA_ASP,GRID):
    return hscTansip.F_WCSA_PLMAIN_GETDISTORTION_atRADECGRID(WCSA_ASP,GRID)
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

def WCS_GET_REFERENCE_INDIVIDUAL(WCSA_ASP,REFID):
    return hscTansip.F_WCSA_PLMAIN_GETREF(WCSA_ASP,REFID)

#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : CCD (Values of CCD having)
#-----------------------------------------------------------------
#def WCS_GET_CCD_ALL_CCDPOS(WCSA_ASP):#Vector((CCDID, X(pixel), Y(pixel), T(radian)))
#    return hscTansip.F_WCSA_PLMAIN_GETCCDPOSITIONS(WCSA_ASP)
#def WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,CID):#(CCDID, X(pixel), Y(pixel), T(radian))
#    return hscTansip.F_WCSA_PLMAIN_GETCCDPOSITION(WCSA_ASP,CID)
def WCS_GET_CCD_CCDPOS(WCSA_ASP,CID):#(CCDID, X(pixel), Y(pixel), T(radian))
    return hscTansip.F_WCSA_PLMAIN_GETCCDPOSITIONS(WCSA_ASP,CID)


#-----------------------------------------------------------------
#plotting figures : WCSA_ASP : field
#-----------------------------------------------------------------
def WCS_PLOT_CCDREGIONS(WCSA_ASP,CID):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    CRPIX  = hscTansip.F_WCSA_PLMAIN_GET_CRPIX(WCSA_ASP)
    CORNAR = hscTansip.F_WCSA_PLMAIN_GET_CORNAR(WCSA_ASP,CID)
    if CID > -0.5 and CID < CCDNUM-0.5:
        plt.plot([CORNAR[0],CORNAR[2]],[CORNAR[1],CORNAR[3]],color="#777777")
        plt.plot([CORNAR[2],CORNAR[4]],[CORNAR[3],CORNAR[5]],color="#777777")
        plt.plot([CORNAR[4],CORNAR[6]],[CORNAR[5],CORNAR[7]],color="#777777")
        plt.plot([CORNAR[6],CORNAR[0]],[CORNAR[7],CORNAR[1]],color="#777777")
        title = "CCD : {0}".format(str(CID).zfill(3))
    else:
        for i in range(0,CCDNUM):
            plt.plot([CORNAR[10*i+0],CORNAR[10*i+2]],[CORNAR[10*i+1],CORNAR[10*i+3]],color="#777777")
            plt.plot([CORNAR[10*i+2],CORNAR[10*i+4]],[CORNAR[10*i+3],CORNAR[10*i+5]],color="#777777")
            plt.plot([CORNAR[10*i+4],CORNAR[10*i+6]],[CORNAR[10*i+5],CORNAR[10*i+7]],color="#777777")
            plt.plot([CORNAR[10*i+6],CORNAR[10*i+0]],[CORNAR[10*i+7],CORNAR[10*i+1]],color="#777777")
            plt.text(CORNAR[10*i+0]+200,CORNAR[10*i+1]+200,"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        plt.plot([CRPIX[0]-500,CRPIX[0]+500],[CRPIX[1]-500,CRPIX[1]+500],color="#FFFFFF")
        plt.plot([CRPIX[0]-500,CRPIX[0]+500],[CRPIX[0]+500,CRPIX[1]-500],color="#FFFFFF")
        plt.text(CRPIX[0]+500,CRPIX[1]-500,"CRPIX",size=9,color="#FFFFFF")
        title = "GLOBAL"
    plt.axis('scaled')
    plt.title(title,fontsize=20)
    plt.show()

def WCS_PLOT_DISTCORRCCDREGIONS(WCSA_ASP,CID):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    CRPIX  = hscTansip.F_WCSA_PLMAIN_GET_CRPIX(WCSA_ASP)
    DISTCORRCORNAR = hscTansip.F_WCSA_PLMAIN_GET_DISTCORRCORNAR(WCSA_ASP,CID)
    if CID > -0.5 and CID < CCDNUM-0.5:
        plt.plot([DISTCORRCORNAR[0],DISTCORRCORNAR[2]],[DISTCORRCORNAR[1],DISTCORRCORNAR[3]],color="#777777")
        plt.plot([DISTCORRCORNAR[2],DISTCORRCORNAR[4]],[DISTCORRCORNAR[3],DISTCORRCORNAR[5]],color="#777777")
        plt.plot([DISTCORRCORNAR[4],DISTCORRCORNAR[6]],[DISTCORRCORNAR[5],DISTCORRCORNAR[7]],color="#777777")
        plt.plot([DISTCORRCORNAR[6],DISTCORRCORNAR[0]],[DISTCORRCORNAR[7],DISTCORRCORNAR[1]],color="#777777")
        title = "CCD : {0}".format(str(CID).zfill(3))
    else:
        for i in range(0,CCDNUM):
            plt.plot([DISTCORRCORNAR[10*i+0],DISTCORRCORNAR[10*i+2]],[DISTCORRCORNAR[10*i+1],DISTCORRCORNAR[10*i+3]],color="#777777")
            plt.plot([DISTCORRCORNAR[10*i+2],DISTCORRCORNAR[10*i+4]],[DISTCORRCORNAR[10*i+3],DISTCORRCORNAR[10*i+5]],color="#777777")
            plt.plot([DISTCORRCORNAR[10*i+4],DISTCORRCORNAR[10*i+6]],[DISTCORRCORNAR[10*i+5],DISTCORRCORNAR[10*i+7]],color="#777777")
            plt.plot([DISTCORRCORNAR[10*i+6],DISTCORRCORNAR[10*i+0]],[DISTCORRCORNAR[10*i+7],DISTCORRCORNAR[10*i+1]],color="#777777")
            plt.text(DISTCORRCORNAR[10*i+0]+200,DISTCORRCORNAR[10*i+1]+200,"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        plt.plot([CRPIX[0]-500,CRPIX[0]+500],[CRPIX[1]-500,CRPIX[1]+500],color="#333333")
        plt.plot([CRPIX[0]-500,CRPIX[0]+500],[CRPIX[0]+500,CRPIX[1]-500],color="#333333")
        plt.text(CRPIX[0]+500,CRPIX[1]-500,"CRPIX",size=9,color="#333333")
        title = "CORRECTED POSITION OF CCDS"
    plt.axis('scaled')
    plt.title(title,fontsize=20)
    plt.show()

def WCS_PLOT_DISTCORRCCDREGIONS_N(WCSA_ASP,CID,N):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    CRPIX  = hscTansip.F_WCSA_PLMAIN_GET_CRPIX(WCSA_ASP)
    DISTCORRCORNAR = hscTansip.F_WCSA_PLMAIN_GET_DISTCORRCORNAR_N(WCSA_ASP,CID,N)
    if CID > -0.5 and CID < CCDNUM-0.5:
        plt.plot([DISTCORRCORNAR[0],DISTCORRCORNAR[2]],[DISTCORRCORNAR[1],DISTCORRCORNAR[3]],color="#777777")
        plt.plot([DISTCORRCORNAR[2],DISTCORRCORNAR[4]],[DISTCORRCORNAR[3],DISTCORRCORNAR[5]],color="#777777")
        plt.plot([DISTCORRCORNAR[4],DISTCORRCORNAR[6]],[DISTCORRCORNAR[5],DISTCORRCORNAR[7]],color="#777777")
        plt.plot([DISTCORRCORNAR[6],DISTCORRCORNAR[0]],[DISTCORRCORNAR[7],DISTCORRCORNAR[1]],color="#777777")
        title = "CCD : {0}".format(str(CID).zfill(3))
    else:
        for i in range(0,CCDNUM):
            plt.plot([DISTCORRCORNAR[10*i+0],DISTCORRCORNAR[10*i+2]],[DISTCORRCORNAR[10*i+1],DISTCORRCORNAR[10*i+3]],color="#777777")
            plt.plot([DISTCORRCORNAR[10*i+2],DISTCORRCORNAR[10*i+4]],[DISTCORRCORNAR[10*i+3],DISTCORRCORNAR[10*i+5]],color="#777777")
            plt.plot([DISTCORRCORNAR[10*i+4],DISTCORRCORNAR[10*i+6]],[DISTCORRCORNAR[10*i+5],DISTCORRCORNAR[10*i+7]],color="#777777")
            plt.plot([DISTCORRCORNAR[10*i+6],DISTCORRCORNAR[10*i+0]],[DISTCORRCORNAR[10*i+7],DISTCORRCORNAR[10*i+1]],color="#777777")
            plt.text(DISTCORRCORNAR[10*i+0]+200,DISTCORRCORNAR[10*i+1]+200,"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        plt.plot([CRPIX[0]-500,CRPIX[0]+500],[CRPIX[1]-500,CRPIX[1]+500],color="#333333")
        plt.plot([CRPIX[0]-500,CRPIX[0]+500],[CRPIX[0]+500,CRPIX[1]-500],color="#333333")
        plt.text(CRPIX[0]+500,CRPIX[1]-500,"CRPIX",size=9,color="#333333")
        title = "CORRECTED POSITION OF CCDS"
    plt.axis('scaled')
    plt.title(title,fontsize=20)
    plt.show()

def WCS_PLOT_RADECCCDREGIONS(WCSA_ASP,CID):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    CRVAL  = hscTansip.F_WCSA_PLMAIN_GET_CRVAL(WCSA_ASP)
    RADECCORNAR = hscTansip.F_WCSA_PLMAIN_GET_RADECCORNAR(WCSA_ASP,CID)
    if CID > -0.5 and CID < CCDNUM-0.5:
        plt.plot([RADECCORNAR[0],RADECCORNAR[2]],[RADECCORNAR[1],RADECCORNAR[3]],color="#777777")
        plt.plot([RADECCORNAR[2],RADECCORNAR[4]],[RADECCORNAR[3],RADECCORNAR[5]],color="#777777")
        plt.plot([RADECCORNAR[4],RADECCORNAR[6]],[RADECCORNAR[5],RADECCORNAR[7]],color="#777777")
        plt.plot([RADECCORNAR[6],RADECCORNAR[0]],[RADECCORNAR[7],RADECCORNAR[1]],color="#777777")
        title = "CCD : {0}".format(str(CID).zfill(3))
    else:
        for i in range(0,CCDNUM):
            plt.plot([RADECCORNAR[10*i+0],RADECCORNAR[10*i+2]],[RADECCORNAR[10*i+1],RADECCORNAR[10*i+3]],color="#777777")
            plt.plot([RADECCORNAR[10*i+2],RADECCORNAR[10*i+4]],[RADECCORNAR[10*i+3],RADECCORNAR[10*i+5]],color="#777777")
            plt.plot([RADECCORNAR[10*i+4],RADECCORNAR[10*i+6]],[RADECCORNAR[10*i+5],RADECCORNAR[10*i+7]],color="#777777")
            plt.plot([RADECCORNAR[10*i+6],RADECCORNAR[10*i+0]],[RADECCORNAR[10*i+7],RADECCORNAR[10*i+1]],color="#777777")
            plt.text(RADECCORNAR[10*i+0]+0.01-0.09,RADECCORNAR[10*i+1]+0.01,"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        plt.plot([CRVAL[0]-0.025,CRVAL[0]+0.025],[CRVAL[1]-0.025,CRVAL[1]+0.025],color="#333333")
        plt.plot([CRVAL[0]-0.025,CRVAL[0]+0.025],[CRVAL[0]+0.025,CRVAL[1]-0.025],color="#333333")
        plt.text(CRVAL[0]+0.025,CRVAL[1]-0.025,"CRVAL",size=9,color="#333333")
        title = "RADEC POSITION OF CCDS"
    plt.axis('scaled')
    plt.title(title,fontsize=20)
    plt.show()

def WCS_PLOT_CONVERGENCE(WCSA_ASP,CID,dx,dy):
    WCS_PLOT_CRSM(WCSA_ASP,CID,0,dx,dy)

def WCS_PLOT_ROTATION(WCSA_ASP,CID,dx,dy):
    WCS_PLOT_CRSM(WCSA_ASP,CID,1,dx,dy)

def WCS_PLOT_SHEAR1(WCSA_ASP,CID,dx,dy):
    WCS_PLOT_CRSM(WCSA_ASP,CID,2,dx,dy)

def WCS_PLOT_SHEAR2(WCSA_ASP,CID,dx,dy):
    WCS_PLOT_CRSM(WCSA_ASP,CID,3,dx,dy)

def WCS_PLOT_MAGNIFICATION(WCSA_ASP,CID,dx,dy):
    WCS_PLOT_CRSM(WCSA_ASP,CID,4,dx,dy)

def WCS_PLOT_CRSM(WCSA_ASP,CID,CRSMID,dx,dy):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    CRPIX  = hscTansip.F_WCSA_PLMAIN_GET_CRPIX(WCSA_ASP)
    CORNAR = hscTansip.F_WCSA_PLMAIN_GET_CORNAR(WCSA_ASP,CID)
    if CID > -0.5 and CID < CCDNUM-0.5:
        x=numpy.arange(0,2048+0.5,dx)
        y=numpy.arange(0,4096+0.5,dy)
        X, Y = numpy.meshgrid(x,y)
        Z = WCS_GET_CRSM_atLOCALGRID(WCSA_ASP,CID,CRSMID,x,y)
        Zlist=[]
        for j, w in enumerate(y):
            ZlistYFIX=[]
            for i, v in enumerate(x):
                ZlistYFIX.append(Z[j][i])
            Zlist.append(ZlistYFIX)
        plt.pcolor(X,Y,Zlist)
#        plt.plot([CORNAR[0],CORNAR[2]],[CORNAR[1],CORNAR[3]],color="#777777")
#        plt.plot([CORNAR[2],CORNAR[4]],[CORNAR[3],CORNAR[5]],color="#777777")
#        plt.plot([CORNAR[4],CORNAR[6]],[CORNAR[5],CORNAR[7]],color="#777777")
#        plt.plot([CORNAR[6],CORNAR[0]],[CORNAR[7],CORNAR[1]],color="#777777")
        if   CRSMID == 0:
            title = "CONVERGENCE : CCD : {0}".format(str(CID).zfill(3))
        elif CRSMID == 1:
            title = "ROTATION : CCD : {0}".format(str(CID).zfill(3))
        elif CRSMID == 2:
            title = "SHEAR1 : CCD : {0}".format(str(CID).zfill(3))
        elif CRSMID == 3:
            title = "SHEAR2 : CCD : {0}".format(str(CID).zfill(3))
        elif CRSMID == 4:
            title = "MAGNIFICATION : CCD : {0}".format(str(CID).zfill(3))
    else:
        x=numpy.arange(-18000,18000+0.5,dx)
        y=numpy.arange(-18000,18000+0.5,dy)
        X, Y = numpy.meshgrid(x,y)
        Z = WCS_GET_CRSM_atLOCALGRID(WCSA_ASP,CID,CRSMID,x,y)
        Zlist=[]
        for j, w in enumerate(y):
            ZlistYFIX=[]
            for i, v in enumerate(x):
                ZlistYFIX.append(Z[j][i])
            Zlist.append(ZlistYFIX)
        plt.pcolor(X,Y,Zlist)
        for i in range(0,CCDNUM):
            plt.plot([CORNAR[10*i+0],CORNAR[10*i+2]],[CORNAR[10*i+1],CORNAR[10*i+3]],color="#777777")
            plt.plot([CORNAR[10*i+2],CORNAR[10*i+4]],[CORNAR[10*i+3],CORNAR[10*i+5]],color="#777777")
            plt.plot([CORNAR[10*i+4],CORNAR[10*i+6]],[CORNAR[10*i+5],CORNAR[10*i+7]],color="#777777")
            plt.plot([CORNAR[10*i+6],CORNAR[10*i+0]],[CORNAR[10*i+7],CORNAR[10*i+1]],color="#777777")
            plt.text(CORNAR[10*i+0]+200,CORNAR[10*i+1]+200,"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        plt.plot([CRPIX[0]-500,CRPIX[0]+500],[CRPIX[1]-500,CRPIX[1]+500],color="#FFFFFF")
        plt.plot([CRPIX[0]-500,CRPIX[0]+500],[CRPIX[0]+500,CRPIX[1]-500],color="#FFFFFF")
        plt.text(CRPIX[0]+500,CRPIX[1]-500,"CRPIX",size=9,color="#FFFFFF")
        if   CRSMID == 0:
            title = "CONVERGENCE : GLOBAL"
        elif CRSMID == 1:
            title = "ROTATION : GLOBAL"
        elif CRSMID == 2:
            title = "SHEAR1 : GLOBAL"
        elif CRSMID == 3:
            title = "SHEAR2 : GLOBAL"
        elif CRSMID == 4:
            title = "MAGNIFICATION : GLOBAL"
    plt.axis('scaled')
    plt.colorbar()
    plt.title(title,fontsize=20)
    plt.show()
    

def WCS_PLOT_DISTORTION_V(dx,dy):
    x=numpy.arange(-1000,1000+0.5,dx)
    y=numpy.arange(-1000,1000+0.5,dy)
    print x
    print y
    ulist=[]
    vlist=[]
    for j, l in enumerate(y):
        ulistYFIX=[]
        vlistYFIX=[]
        for i, k in enumerate(x):
            ulistYFIX.append(500*i)
            vlistYFIX.append(500)
        ulist.append(ulistYFIX)
        vlist.append(vlistYFIX)
    print ulist
    print vlist
    plt.quiver(x,y,ulist,vlist,color="r")
    title = "DISTORTION : IM_PIXEL to GLOBAL"
    plt.axis('scaled')
    plt.title(title,fontsize=20)
    plt.show()
#-----------------------------------------------------------------
#plotting figures : WCSA_ASP : CCD
#-----------------------------------------------------------------

def WCS_PLOT_REFNUM(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLMAIN_GET_INDEX(WCSA_ASP)
    REFNUM = hscTansip.F_WCSA_PLMAIN_GET_REFNUM(WCSA_ASP)
    X, Y, Z = WCS_PLOT_SETXYZ_INDEX(WCSA_ASP,CCDNUM,REFNUM)
    plt.pcolor(X,Y,Z)
    for i in range(0,CCDNUM):
        if i < 100:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        else:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
    title = "NUMBER OF REFERENCES : GLOBAL"
    plt.axis('scaled')
    plt.colorbar()
    plt.title(title,fontsize=20)
    plt.show()
    
def WCS_PLOT_FITNUM(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLMAIN_GET_INDEX(WCSA_ASP)
    FITNUM = hscTansip.F_WCSA_PLMAIN_GET_FITNUM(WCSA_ASP)
    X, Y, Z = WCS_PLOT_SETXYZ_INDEX(WCSA_ASP,CCDNUM,FITNUM)
    plt.pcolor(X,Y,Z)
    for i in range(0,CCDNUM):
        if i < 100:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        else:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
    title = "NUMBER OF FITTINGS : GLOBAL"
    plt.axis('scaled')
    plt.colorbar()
    plt.title(title,fontsize=20)
    plt.show()
    
def WCS_PLOT_REJNUM(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLMAIN_GET_INDEX(WCSA_ASP)
    REFNUM = hscTansip.F_WCSA_PLMAIN_GET_REFNUM(WCSA_ASP)
    FITNUM = hscTansip.F_WCSA_PLMAIN_GET_FITNUM(WCSA_ASP)
    REJNUM=[0 for i in range(CCDNUM)]
    for i in range(0,CCDNUM):
        REJNUM[i]=REFNUM[i]-FITNUM[i]
    X, Y, Z = WCS_PLOT_SETXYZ_INDEX(WCSA_ASP,CCDNUM,REJNUM)
    plt.pcolor(X,Y,Z)
    for i in range(0,CCDNUM):
        if i < 100:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        else:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
    title = "NUMBER OF REJECTEDS : GLOBAL"
    plt.axis('scaled')
    plt.colorbar()
    plt.title(title,fontsize=20)
    plt.show()
    
def WCS_PLOT_SETXYZ_INDEX(WCSA_ASP,CCDNUM, VALUE):
    INDEX  = hscTansip.F_WCSA_PLMAIN_GET_INDEX(WCSA_ASP)
    AVE=0
    for i in range(0,CCDNUM):
        AVE+=VALUE[i]/CCDNUM
    if CCDNUM > 11:
        x=numpy.arange(-7.0,8.0+0.5,1.0)
        y=numpy.arange(-8.0,8.0+0.5,1.0)
        n=16
        m=15
        Z = [[AVE for j in range(m)] for i in range(n)]
    else:
        x=numpy.arange(-2.0,3.0+0.5,1.0)
        y=numpy.arange(-2.0,2.0+0.5,1.0)
        n=4
        m=5
        Z = [[AVE for j in range(m)] for i in range(n)]
    X, Y = numpy.meshgrid(x,y)
    if CCDNUM > 11:
        for i in range(0,CCDNUM):
            if i < 100:
                Z[INDEX[2*i+1]+8+0][INDEX[2*i+0]+7]=VALUE[i]
                Z[INDEX[2*i+1]+8+1][INDEX[2*i+0]+7]=VALUE[i]
            else:
                Z[INDEX[2*i+1]+8][INDEX[2*i+0]+7+0]=VALUE[i]
                Z[INDEX[2*i+1]+8][INDEX[2*i+0]+7+1]=VALUE[i]
    else:
        for i in range(0,CCDNUM):
            Z[INDEX[2*i+1]+2+0][INDEX[2*i+0]+2]=VALUE[i]
            Z[INDEX[2*i+1]+2+1][INDEX[2*i+0]+2]=VALUE[i]
    return X, Y, Z

def WCS_PLOT_RMSSIPX(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLMAIN_GET_INDEX(WCSA_ASP)
    SIPRMS = hscTansip.F_WCSA_PLMAIN_GET_SIPRMSX(WCSA_ASP)
    X, Y, Z = WCS_PLOT_SETXYZ_INDEX(WCSA_ASP,CCDNUM,SIPRMS)
    plt.pcolor(X,Y,Z)
    for i in range(0,CCDNUM):
        if i < 100:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        else:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
    title = "RMS(pix) OF SIP A : GLOBAL"
    plt.axis('scaled')
    plt.colorbar()
    plt.title(title,fontsize=20)
    plt.show()
    
def WCS_PLOT_RMSSIPY(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLMAIN_GET_INDEX(WCSA_ASP)
    SIPRMS = hscTansip.F_WCSA_PLMAIN_GET_SIPRMSY(WCSA_ASP)
    X, Y, Z = WCS_PLOT_SETXYZ_INDEX(WCSA_ASP,CCDNUM,SIPRMS)
    plt.pcolor(X,Y,Z)
    for i in range(0,CCDNUM):
        if i < 100:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        else:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
    title = "RMS(pix) OF SIP B : GLOBAL"
    plt.axis('scaled')
    plt.colorbar()
    plt.title(title,fontsize=20)
    plt.show()
    
def WCS_PLOT_RMSPSIPX(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLMAIN_GET_INDEX(WCSA_ASP)
    SIPRMS = hscTansip.F_WCSA_PLMAIN_GET_PSIPRMSX(WCSA_ASP)
    X, Y, Z = WCS_PLOT_SETXYZ_INDEX(WCSA_ASP,CCDNUM,SIPRMS)
    plt.pcolor(X,Y,Z)
    for i in range(0,CCDNUM):
        if i < 100:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        else:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
    title = "RMS(pix) OF PSIP A : GLOBAL"
    plt.axis('scaled')
    plt.colorbar()
    plt.title(title,fontsize=20)
    plt.show()
    
def WCS_PLOT_RMSPSIPY(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLMAIN_GET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLMAIN_GET_INDEX(WCSA_ASP)
    SIPRMS = hscTansip.F_WCSA_PLMAIN_GET_PSIPRMSY(WCSA_ASP)
    X, Y, Z = WCS_PLOT_SETXYZ_INDEX(WCSA_ASP,CCDNUM,SIPRMS)
    plt.pcolor(X,Y,Z)
    for i in range(0,CCDNUM):
        if i < 100:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+1],[INDEX[2*i+1]+0,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+1,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+2],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+2,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        else:
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+0],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+2],[INDEX[2*i+1]+0,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+2,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+1],color="#777777")
            plt.plot([INDEX[2*i+0]+0,INDEX[2*i+0]+0],[INDEX[2*i+1]+1,INDEX[2*i+1]+0],color="#777777")
            plt.text(INDEX[2*i+0],INDEX[2*i+1],"{0}".format(str(i).zfill(3)),size=9,color="#777777")
    title = "RMS(pix) OF PSIP B : GLOBAL"
    plt.axis('scaled')
    plt.colorbar()
    plt.title(title,fontsize=20)
    plt.show()
    
    
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
