
import sys, re, os, math
import signal
import datetime
import time
import numpy
import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse
from math import atan2
from math import hypot
import pyfits
from pyfits import Column

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
            

    OUTFLAG=policy.get('OUTFLAG')
    OUTDIR =policy.get('OUTDIR')
    WCSA_ASP = hscTansip.F_WCSA_TANSIP_V(matchListAllCcd, metadata, policy, camera)

    if OUTFLAG==1:
        print "OUTPUT FITS BINARY TABLE in "+OUTDIR
        F_OUTPUT_BTBL(WCSA_ASP,OUTDIR)

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

def doTansipQa(matchListAllCcd, policy=None, camera=None, rerun=None):
    print '--- doTansip ---'
    metaTANSIP = hscTansip.F_WCS_EMPTYMETADATA()
    WCSA_ASP = getresultWcs(matchListAllCcd, metaTANSIP, policy, camera)

    return WCSA_ASP, metaTANSIP

def F_WCS_EMPTYMETADATA():
    metadata = hscTansip.F_WCS_EMPTYMETADATA()
    return metadata

def getwcsList(WCSA_ASP):
    print '--- getWCSlist ---'
    return hscTansip.F_WCSA_PLMAIN_GETWCSLIST(WCSA_ASP)


def memorydelete(WCSA_ASP):
    hscTansip.F_WCSA_PLMAIN_MEMORYDELETE(WCSA_ASP)

#-----------------------------------------------------------------
#Output bianry table : WCSA_ASP
#-----------------------------------------------------------------
def F_OUTPUT_BTBL(WCSA_ASP,OUTDIR):
    if os.path.exists(OUTDIR) == False:
	os.makedirs(OUTDIR)    

#CCD-----
    CCDNAME=OUTDIR+"/solvetansip_CCDresult.fits"
    CCDID  =hscTansip.F_WCSA_PLGET_CCD_ID(WCSA_ASP)
    CCDRNUM=hscTansip.F_WCSA_PLGET_CCD_NUMREF(WCSA_ASP)
    CCDFNUM=hscTansip.F_WCSA_PLGET_CCD_NUMFIT(WCSA_ASP)
    CCDPOS =hscTansip.F_WCSA_PLGET_CCD_GPOS(WCSA_ASP)
    CCDCR  =hscTansip.F_WCSA_PLGET_CCD_CR(WCSA_ASP)
    CCDCD  =hscTansip.F_WCSA_PLGET_CCD_CD(WCSA_ASP)
    CCDSORD=hscTansip.F_WCSA_PLGET_CCD_ORDERSIP(WCSA_ASP)
    CCDPORD=hscTansip.F_WCSA_PLGET_CCD_ORDERPSIP(WCSA_ASP)
    CCDSERR=hscTansip.F_WCSA_PLGET_CCD_ERRSIP(WCSA_ASP)
    CCDPERR=hscTansip.F_WCSA_PLGET_CCD_ERRPSIP(WCSA_ASP)
    CCDSCOA=hscTansip.F_WCSA_PLGET_CCD_COEFSIPA(WCSA_ASP)
    CCDSCOB=hscTansip.F_WCSA_PLGET_CCD_COEFSIPB(WCSA_ASP)
    CCDPCOA=hscTansip.F_WCSA_PLGET_CCD_COEFPSIPA(WCSA_ASP)
    CCDPCOB=hscTansip.F_WCSA_PLGET_CCD_COEFPSIPB(WCSA_ASP)

    print CCDPOS[0][0],CCDPOS[1][0],CCDPOS[2][0]
    print CCDPOS[0][49],CCDPOS[1][49],CCDPOS[2][49]
    print CCDPOS[0][104],CCDPOS[1][104],CCDPOS[2][104]
    print CCDCD[0][49],CCDCD[1][49],CCDCD[2][49],CCDCD[3][49]
    print CCDCD[0][104],CCDCD[1][104],CCDCD[2][104],CCDCD[3][104]
    print CCDSCOA[0][0],CCDSCOA[0][49],CCDSCOA[0][104];
    print CCDSCOA[1][0],CCDSCOA[1][49],CCDSCOA[1][104];
    print CCDSCOA[2][0],CCDSCOA[2][49],CCDSCOA[2][104];
    print CCDSCOB[0][0],CCDSCOB[0][49],CCDSCOB[0][104];
    print CCDSCOB[1][0],CCDSCOB[1][49],CCDSCOB[1][104];
    print CCDSCOB[2][0],CCDSCOB[2][49],CCDSCOB[2][104];
    print CCDPCOA[0][0],CCDPCOA[0][49],CCDPCOA[0][104];
    print CCDPCOA[1][0],CCDPCOA[1][49],CCDPCOA[1][104];
    print CCDPCOA[2][0],CCDPCOA[2][49],CCDPCOA[2][104];
    print CCDPCOB[0][0],CCDPCOB[0][49],CCDPCOB[0][104];
    print CCDPCOB[1][0],CCDPCOB[1][49],CCDPCOB[1][104];
    print CCDPCOB[2][0],CCDPCOB[2][49],CCDPCOB[2][104];
    print CCDNAME

    CCDCOL=[]
    CCDCOL.append(Column(name="CCDID"         ,format="J",array=CCDID))
    CCDCOL.append(Column(name="NUM_REF"       ,format="J",array=CCDRNUM))
    CCDCOL.append(Column(name="NUM_FIT"       ,format="J",array=CCDFNUM))
    CCDCOL.append(Column(name="GPOS_X"        ,format="D",unit="pixel",array=CCDPOS[0]))
    CCDCOL.append(Column(name="GPOS_Y"        ,format="D",unit="pixel",array=CCDPOS[1]))
    CCDCOL.append(Column(name="GPOS_T"        ,format="D",unit="radian",array=CCDPOS[2]))
    CCDCOL.append(Column(name="CRPIX_X"       ,format="D",unit="pixel",array=CCDCR[0]))
    CCDCOL.append(Column(name="CRPIX_Y"       ,format="D",unit="pixel",array=CCDCR[1]))
    CCDCOL.append(Column(name="CRVAL_RA"      ,format="D",unit="degree",array=CCDCR[2]))
    CCDCOL.append(Column(name="CRVAL_DEC"     ,format="D",unit="degree",array=CCDCR[3]))
    CCDCOL.append(Column(name="CD1_1"         ,format="D",unit="pixel/degree",array=CCDCD[0]))
    CCDCOL.append(Column(name="CD1_2"         ,format="D",unit="pixel/degree",array=CCDCD[1]))
    CCDCOL.append(Column(name="CD2_1"         ,format="D",unit="pixel/degree",array=CCDCD[2]))
    CCDCOL.append(Column(name="CD2_2"         ,format="D",unit="pixel/degree",array=CCDCD[3]))
    CCDCOL.append(Column(name="ERR_SIP_X_AVE" ,format="D",unit="pixel",array=CCDSERR[0]))
    CCDCOL.append(Column(name="ERR_SIP_X_RMS" ,format="D",unit="pixel",array=CCDSERR[1]))
    CCDCOL.append(Column(name="ERR_SIP_X_MAX" ,format="D",unit="pixel",array=CCDSERR[2]))
    CCDCOL.append(Column(name="ERR_SIP_Y_AVE" ,format="D",unit="pixel",array=CCDSERR[3]))
    CCDCOL.append(Column(name="ERR_SIP_Y_RMS" ,format="D",unit="pixel",array=CCDSERR[4]))
    CCDCOL.append(Column(name="ERR_SIP_Y_MAX" ,format="D",unit="pixel",array=CCDSERR[5]))
    CCDCOL.append(Column(name="ERR_PSIP_X_AVE",format="D",unit="pixel",array=CCDPERR[0]))
    CCDCOL.append(Column(name="ERR_PSIP_X_RMS",format="D",unit="pixel",array=CCDPERR[1]))
    CCDCOL.append(Column(name="ERR_PSIP_X_MAX",format="D",unit="pixel",array=CCDPERR[2]))
    CCDCOL.append(Column(name="ERR_PSIP_Y_AVE",format="D",unit="pixel",array=CCDPERR[3]))
    CCDCOL.append(Column(name="ERR_PSIP_Y_RMS",format="D",unit="pixel",array=CCDPERR[4]))
    CCDCOL.append(Column(name="ERR_PSIP_Y_MAX",format="D",unit="pixel",array=CCDPERR[5]))
    SORDER=int(CCDSORD[-1])
    PORDER=int(CCDPORD[-1])
    SIPNUM=int(0.5*(SORDER+1)*(SORDER+2)+0.5)
    PSIPNUM=int(0.5*(PORDER+1)*(PORDER+2)+0.5)
    CCDCOL.append(Column(name="ORDER_SIP_A",format="J",array=CCDSORD))
    for ORDER in range(SIPNUM):
        CNAME="SIP_A_"+str(ORDER)
        CCDCOL.append(Column(name=CNAME,format="D",array=CCDSCOA[ORDER]))
    CCDCOL.append(Column(name="ORDER_SIP_B",format="J",array=CCDSORD))
    for ORDER in range(SIPNUM):
        CNAME="SIP_B_"+str(ORDER)
        CCDCOL.append(Column(name=CNAME,format="D",array=CCDSCOB[ORDER]))
    CCDCOL.append(Column(name="ORDER_PSIP_A",format="J",array=CCDPORD))
    for ORDER in range(PSIPNUM):
        CNAME="PSIP_A_"+str(ORDER)
        CCDCOL.append(Column(name=CNAME,format="D",array=CCDPCOA[ORDER]))
    CCDCOL.append(Column(name="ORDER_PSIP_B",format="J",array=CCDSORD))
    for ORDER in range(PSIPNUM):
        CNAME="PSIP_B_"+str(ORDER)
        CCDCOL.append(Column(name=CNAME,format="D",array=CCDPCOB[ORDER]))


    CCDhdu = pyfits.new_table(CCDCOL)
    CCDhdu.writeto(CCDNAME,clobber=True)
#REF-----

    REFNAME =OUTDIR+"/solvetansip_REFresult.fits"
    REFID   =hscTansip.F_WCSA_PLGET_REF_ID(WCSA_ASP)
    REFCID  =hscTansip.F_WCSA_PLGET_REF_CID(WCSA_ASP)
    REFFLAG =hscTansip.F_WCSA_PLGET_REF_FLAG(WCSA_ASP);
    REFPOSL =hscTansip.F_WCSA_PLGET_REF_POSLOCAL(WCSA_ASP);
    REFPOSG =hscTansip.F_WCSA_PLGET_REF_POSGLOBAL(WCSA_ASP);
    REFPOSR =hscTansip.F_WCSA_PLGET_REF_POSRADEC(WCSA_ASP);
    REFPOSLC=hscTansip.F_WCSA_PLGET_REF_POSLCRPIX(WCSA_ASP);
    REFPOSGC=hscTansip.F_WCSA_PLGET_REF_POSGCRPIX(WCSA_ASP);
    REFDIFFS=hscTansip.F_WCSA_PLGET_REF_DIFFSIP(WCSA_ASP);
    REFDIFFP=hscTansip.F_WCSA_PLGET_REF_DIFFPSIP(WCSA_ASP);
    REFDISTS=hscTansip.F_WCSA_PLGET_REF_CAMERADISTSIP(WCSA_ASP);
    REFDISTP=hscTansip.F_WCSA_PLGET_REF_CAMERADISTPSIP(WCSA_ASP);

    REFCOL=[]
    REFCOL.append(Column(name="ID"                    ,format="K",array=REFID))
    REFCOL.append(Column(name="CHIPID"                ,format="J",array=REFCID))
    REFCOL.append(Column(name="FLAG"                  ,format="J",array=REFFLAG))
    REFCOL.append(Column(name="POSITION_LOCAL_X"      ,format="D",unit="pixel" ,array=REFPOSL[0]))
    REFCOL.append(Column(name="POSITION_LOCAL_Y"      ,format="D",unit="pixel" ,array=REFPOSL[1]))
    REFCOL.append(Column(name="POSITION_LOCALCRPIX_X" ,format="D",unit="pixel" ,array=REFPOSLC[0]))
    REFCOL.append(Column(name="POSITION_LOCALCRPIX_Y" ,format="D",unit="pixel" ,array=REFPOSLC[1]))
    REFCOL.append(Column(name="POSITION_GLOABL_X"     ,format="D",unit="pixel" ,array=REFPOSG[0]))
    REFCOL.append(Column(name="POSITION_GLOABL_Y"     ,format="D",unit="pixel" ,array=REFPOSG[1]))
    REFCOL.append(Column(name="POSITION_GLOABLCRPIX_X",format="D",unit="pixel" ,array=REFPOSGC[0]))
    REFCOL.append(Column(name="POSITION_GLOABLCRPIX_Y",format="D",unit="pixel" ,array=REFPOSGC[1]))
    REFCOL.append(Column(name="POSITION_RA"           ,format="D",unit="degree",array=REFPOSR[0]))
    REFCOL.append(Column(name="POSITION_DEC"          ,format="D",unit="degree",array=REFPOSR[1]))
    REFCOL.append(Column(name="POSITION_DIFFSIP_X"    ,format="D",unit="pixel" ,array=REFDIFFS[0]))
    REFCOL.append(Column(name="POSITION_DIFFSIP_Y"    ,format="D",unit="pixel" ,array=REFDIFFS[1]))
    REFCOL.append(Column(name="POSITION_DIFFPSIP_X"   ,format="D",unit="pixel" ,array=REFDIFFP[0]))
    REFCOL.append(Column(name="POSITION_DIFFPSIP_Y"   ,format="D",unit="pixel" ,array=REFDIFFP[1]))
    REFCOL.append(Column(name="DIST_SIPCONVERGENCE"   ,format="D",array=REFDISTS[0]))
    REFCOL.append(Column(name="DIST_SIPROTATION"      ,format="D",array=REFDISTS[1]))
    REFCOL.append(Column(name="DIST_SIPSHEAR1"        ,format="D",array=REFDISTS[2]))
    REFCOL.append(Column(name="DIST_SIPSHEAR2"        ,format="D",array=REFDISTS[3]))
    REFCOL.append(Column(name="DIST_SIPMAGNIFICATION" ,format="D",array=REFDISTS[4]))
    REFCOL.append(Column(name="DIST_SIPJACOBIAN"      ,format="D",array=REFDISTS[5]))
    REFCOL.append(Column(name="DIST_PSIPCONVERGENCE"  ,format="D",array=REFDISTP[0]))
    REFCOL.append(Column(name="DIST_PSIPROTATION"     ,format="D",array=REFDISTP[1]))
    REFCOL.append(Column(name="DIST_PSIPSHEAR1"       ,format="D",array=REFDISTP[2]))
    REFCOL.append(Column(name="DIST_PSIPSHEAR2"       ,format="D",array=REFDISTP[3]))
    REFCOL.append(Column(name="DIST_PSIPMAGNIFICATION",format="D",array=REFDISTP[4]))
    REFCOL.append(Column(name="DIST_PSIPJACOBIAN"     ,format="D",array=REFDISTP[5]))
    REFhdu = pyfits.new_table(REFCOL)
    REFhdu.writeto(REFNAME,clobber=True)

    print REFNAME
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
def WCS_MAKE_SIMULATIONREFERENCE2(policy,camera,NSCALE,RANNUM,REFNUM):
    hscTansip.F_WCSA_PLMAIN_SIMULATION2(policy,camera,NSCALE,RANNUM,REFNUM)
def WCS_CALC_SIMULATIONDIFF2(CCDoutfile,RESoutfile,WCSA_ASP):
    hscTansip.F_WCSA_PLMAIN_SIMULATIONDIFF2(CCDoutfile,RESoutfile,WCSA_ASP)
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
    return hscTansip.F_WCSA_PLGET_POSITION_RADECfromLOCAL(WCSA_ASP,CID,XY)
def WCS_GET_POSITION_RADECfromCRPIX(WCSA_ASP,CID,XY):
    return hscTansip.F_WCSA_PLGET_POSITION_RADECfromCRPIX(WCSA_ASP,CID,XY)
def WCS_GET_POSITION_LOCALfromRADEC(WCSA_ASP,CID,XY):
    return hscTansip.F_WCSA_PLGET_POSITION_LOCALfromRADEC(WCSA_ASP,CID,XY)
def WCS_GET_POSITION_CRPIXfromRADEC(WCSA_ASP,CID,XY):
    return hscTansip.F_WCSA_PLGET_POSITION_CRPIXfromRADEC(WCSA_ASP,CID,XY)

def WCS_GET_POSITION_CCDIDLOCALfromGLOBAL(WCSA_ASP,XY):
    return hscTansip.F_WCSA_PLGET_POSITION_CCDIDLOCALfromGLOBAL(WCSA_ASP,XY)
def WCS_GET_POSITION_GLOBALfromCCDIDLOCAL(WCSA_ASP,CCDID,XY):
    return hscTansip.F_WCSA_PLGET_POSITION_GLOBALfromCCDIDLOCAL(WCSA_ASP,CCDID,XY)
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : POSITION (Grid)
#-----------------------------------------------------------------
def WCS_GET_POSITION_RADECfromLOCALGRID(WCSA_ASP,CID,GRID):
    return hscTansip.F_WCSA_PLGET_POSITION_RADECfromLOCALGRID(WCSA_ASP,CID,GRID)
def WCS_GET_POSITION_RADECfromCRPIXGRID(WCSA_ASP,CID,GRID):
    return hscTansip.F_WCSA_PLGET_POSITION_RADECfromCRPIXGRID(WCSA_ASP,CID,GRID)
def WCS_GET_POSITION_LOCALfromRADECGRID(WCSA_ASP,CID,GRID):
    return hscTansip.F_WCSA_PLGET_POSITION_LOCALfromRADECGRID(WCSA_ASP,CID,GRID)
def WCS_GET_POSITION_CRPIXfromRADECGRID(WCSA_ASP,CID,GRID):
    return hscTansip.F_WCSA_PLGET_POSITION_CRPIXfromRADECGRID(WCSA_ASP,CID,GRID)

#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : JACOBIAN (Values at arbitrary position)
#-----------------------------------------------------------------
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : JACOBIAN (Grid)
#-----------------------------------------------------------------
def WCS_GET_CRSMA_atLOCALGRID(WCSA_ASP,CID,GRID):
    return hscTansip.F_WCSA_PLGET_CRSMA_atLOCALGRID(WCSA_ASP,CID,GRID)
def WCS_GET_CRSM_atLOCALGRID(WCSA_ASP,CID,CRSMID,X,Y):
    return hscTansip.F_WCSA_PLGET_CRSM_atLOCALGRID(WCSA_ASP,CID,CRSMID,X,Y)
def WCS_GET_CONVSHEAR_atLOCALGRID(WCSA_ASP,CID,X,Y):
    return hscTansip.F_WCSA_PLGET_CONVSHEAR_atLOCALGRID(WCSA_ASP,CID,X,Y)
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : DISTORTION (Grid)
#-----------------------------------------------------------------
def WCS_GET_DISTORTION_atCRPIXGRID(WCSA_ASP,GRID):
    return hscTansip.F_WCSA_PLGET_DISTORTION_atCRPIXGRID(WCSA_ASP,GRID)
def WCS_GET_DISTORTION_atRADECGRID(WCSA_ASP,GRID):
    return hscTansip.F_WCSA_PLGET_DISTORTION_atRADECGRID(WCSA_ASP,GRID)
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : REFERENCES (Values of References having)
#-----------------------------------------------------------------
def WCS_GET_REFERENCE_ID(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_ID(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CHIPID(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CHIPID(WCSA_ASP,CID)
def WCS_GET_REFERENCE_FLAG(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_FLAG(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_LOCAL(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_XYLOCAL(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_RADEC(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_XYRADEC(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_GLOBAL(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_XYGLOBAL(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_GLOBALCRPIX(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_XYGLOBALCRPIX(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_LOCALCRPIX(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_XYLOCALCRPIX(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_IMPIXEL(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_XYIMPIXEL(WCSA_ASP,CID)
def WCS_GET_REFERENCE_XY_IMWORLD(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_XYIMWORLD(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_CONVERGENCE(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CAMERACONV(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_ROTATION(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CAMERAROT(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_SHEAR1(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CAMERASHEAR1(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_SHEAR2(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CAMERASHEAR2(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_MAGNIFICATION(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CAMERAMAGNIFICATION(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_PCONVERGENCE(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CAMERAPCONV(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_PROTATION(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CAMERAPROT(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_PSHEAR1(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CAMERAPSHEAR1(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_PSHEAR2(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CAMERAPSHEAR2(WCSA_ASP,CID)
def WCS_GET_REFERENCE_CAMERA_PMAGNIFICATION(WCSA_ASP,CID):
    return hscTansip.F_WCSA_PLGET_REF_CAMERAPMAGNIFICATION(WCSA_ASP,CID)

def WCS_GET_REFERENCE_INDIVIDUAL(WCSA_ASP,REFID):
    return hscTansip.F_WCSA_PLGET_REF(WCSA_ASP,REFID)

#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : CCD (Values of CCD having)
#-----------------------------------------------------------------
#def WCS_GET_CCD_ALL_CCDPOS(WCSA_ASP):#Vector((CCDID, X(pixel), Y(pixel), T(radian)))
#    return hscTansip.F_WCSA_PLMAIN_GETCCDPOSITIONS(WCSA_ASP)
#def WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,CID):#(CCDID, X(pixel), Y(pixel), T(radian))
#    return hscTansip.F_WCSA_PLMAIN_GETCCDPOSITION(WCSA_ASP,CID)
def WCS_GET_CCD_CCDPOS(WCSA_ASP,CID):#(CCDID, X(pixel), Y(pixel), T(radian))
    return hscTansip.F_WCSA_PLGET_CCDPOSITIONS(WCSA_ASP,CID)


#-----------------------------------------------------------------
#plotting figures : WCSA_ASP : field
#-----------------------------------------------------------------
def WCS_PLOTMPL_CCDREGIONS(WCSA_ASP,CID):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    CRPIX  = hscTansip.F_WCSA_PLGET_CRPIX(WCSA_ASP)
    CORNAR = hscTansip.F_WCSA_PLGET_CORNAR(WCSA_ASP,CID)
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

def WCS_PLOTMPL_DISTCORRCCDREGIONS(WCSA_ASP,CID):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    CRPIX  = hscTansip.F_WCSA_PLGET_CRPIX(WCSA_ASP)
    DISTCORRCORNAR = hscTansip.F_WCSA_PLGET_DISTCORRCORNAR(WCSA_ASP,CID)
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

def WCS_PLOTMPL_DISTCORRCCDREGIONS_N(WCSA_ASP,CID,N):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    CRPIX  = hscTansip.F_WCSA_PLGET_CRPIX(WCSA_ASP)
    DISTCORRCORNAR = hscTansip.F_WCSA_PLGET_DISTCORRCORNAR_N(WCSA_ASP,CID,N)
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

def WCS_PLOTMPL_RADECCCDREGIONS(WCSA_ASP,CID):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    CRVAL  = hscTansip.F_WCSA_PLGET_CRVAL(WCSA_ASP)
    RADECCORNAR = hscTansip.F_WCSA_PLGET_RADECCORNAR(WCSA_ASP,CID)
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

def WCS_PLOTMPL_CONVERGENCE(WCSA_ASP,CID,dx,dy):
    WCS_PLOTMPL_CRSM(WCSA_ASP,CID,0,dx,dy)

def WCS_PLOTMPL_ROTATION(WCSA_ASP,CID,dx,dy):
    WCS_PLOTMPL_CRSM(WCSA_ASP,CID,1,dx,dy)

def WCS_PLOTMPL_SHEAR1(WCSA_ASP,CID,dx,dy):
    WCS_PLOTMPL_CRSM(WCSA_ASP,CID,2,dx,dy)

def WCS_PLOTMPL_SHEAR2(WCSA_ASP,CID,dx,dy):
    WCS_PLOTMPL_CRSM(WCSA_ASP,CID,3,dx,dy)

def WCS_PLOTMPL_MAGNIFICATION(WCSA_ASP,CID,dx,dy):
    WCS_PLOTMPL_CRSM(WCSA_ASP,CID,4,dx,dy)

def WCS_PLOTMPL_CRSM(WCSA_ASP,CID,CRSMID,dx,dy):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    CRPIX  = hscTansip.F_WCSA_PLGET_CRPIX(WCSA_ASP)
    CORNAR = hscTansip.F_WCSA_PLGET_CORNAR(WCSA_ASP,CID)
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
    

def WCS_PLOTMPL_DISTORTION_V(dx,dy):
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
            ulistYFIX.append(500)
            vlistYFIX.append(500)
        ulist.append(ulistYFIX)
        vlist.append(vlistYFIX)
    print ulist
    print vlist
    plt.quiver(x,y,ulist,vlist,units="x")
    title = "DISTORTION : IM_PIXEL to GLOBAL"
    plt.axis('scaled')
    plt.title(title,fontsize=20)
    plt.show()
    
def WCS_PLOTMPL_CONVSHEAR_2D(WCSA_ASP,CID,dx,dy):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    CRPIX  = hscTansip.F_WCSA_PLGET_CRPIX(WCSA_ASP)
    CORNAR = hscTansip.F_WCSA_PLGET_CORNAR(WCSA_ASP,CID)
    a=plt.subplot(111,aspect='equal')

    if CID > -0.5 and CID < CCDNUM-0.5:
        x=numpy.arange(0,2048+0.5,dx)
        y=numpy.arange(0,4096+0.5,dy)
        Zco = WCS_GET_CRSM_atLOCALGRID(WCSA_ASP,CID,0,x,y)
        Zs1 = WCS_GET_CRSM_atLOCALGRID(WCSA_ASP,CID,2,x,y)
        Zs2 = WCS_GET_CRSM_atLOCALGRID(WCSA_ASP,CID,3,x,y)
        for j, w in enumerate(y):
            for i, v in enumerate(x):
                co = Zco[j][i]
                sh = hypot(Zs2[j][i],Zs1[j][i])
                PA = 180/3.14152965*0.5*atan2(Zs2[j][i],Zs1[j][i])
                E = Ellipse((v,w),100*(co+10*sh),100*(co-10*sh),PA,ec="#000000",fc="none")
                a.add_artist(E)
        plt.plot([0000,2048],[0000,0000],color="#777777")
        plt.plot([2048,2048],[0000,4096],color="#777777")
        plt.plot([2048,0000],[4096,4096],color="#777777")
        plt.plot([0000,0000],[4096,0000],color="#777777")
        title = "CONVERGENCE AND SHEAR : CCD : {0} /n 100*size 10*ellipticity".format(str(CID).zfill(3))
    else:
        x=numpy.arange(-18000,18000+0.5,dx)
        y=numpy.arange(-18000,18000+0.5,dy)
        Zco = WCS_GET_CRSM_atLOCALGRID(WCSA_ASP,CID,0,x,y)
        Zs1 = WCS_GET_CRSM_atLOCALGRID(WCSA_ASP,CID,2,x,y)
        Zs2 = WCS_GET_CRSM_atLOCALGRID(WCSA_ASP,CID,3,x,y)
        for j, w in enumerate(y):
            for i, v in enumerate(x):
                co = Zco[j][i]
                sh = hypot(Zs2[j][i],Zs1[j][i])
                PA = 180/3.14152965*0.5*atan2(Zs2[j][i],Zs1[j][i])
                E = Ellipse((v,w),1000*(co+10*sh),1000*(co-10*sh),PA,ec="#000000",fc="none")
                a.add_artist(E)
        for i in range(0,CCDNUM):
            plt.plot([CORNAR[10*i+0],CORNAR[10*i+2]],[CORNAR[10*i+1],CORNAR[10*i+3]],color="#777777")
            plt.plot([CORNAR[10*i+2],CORNAR[10*i+4]],[CORNAR[10*i+3],CORNAR[10*i+5]],color="#777777")
            plt.plot([CORNAR[10*i+4],CORNAR[10*i+6]],[CORNAR[10*i+5],CORNAR[10*i+7]],color="#777777")
            plt.plot([CORNAR[10*i+6],CORNAR[10*i+0]],[CORNAR[10*i+7],CORNAR[10*i+1]],color="#777777")
            plt.text(CORNAR[10*i+0]+200,CORNAR[10*i+1]+200,"{0}".format(str(i).zfill(3)),size=9,color="#777777")
        plt.plot([CRPIX[0]-500,CRPIX[0]+500],[CRPIX[1]-500,CRPIX[1]+500],color="#FFFFFF")
        plt.plot([CRPIX[0]-500,CRPIX[0]+500],[CRPIX[0]+500,CRPIX[1]-500],color="#FFFFFF")
        plt.text(CRPIX[0]+500,CRPIX[1]-500,"CRPIX",size=9,color="#FFFFFF")
        title = "CONVERGENCE AND SHEAR : GLOBAL /n 1000*size 10*ellipticity"
    plt.axis('scaled')
    plt.title(title,fontsize=20)
    plt.show()
#-----------------------------------------------------------------
#plotting figures : WCSA_ASP : CCD
#-----------------------------------------------------------------

def WCS_PLOTMPL_REFNUM(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLGET_INDEX(WCSA_ASP)
    REFNUM = hscTansip.F_WCSA_PLGET_REFNUM(WCSA_ASP)
    X, Y, Z = WCS_PLOTMPL_SETXYZ_INDEX(WCSA_ASP,CCDNUM,REFNUM)
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
    
def WCS_PLOTMPL_FITNUM(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLGET_INDEX(WCSA_ASP)
    FITNUM = hscTansip.F_WCSA_PLGET_FITNUM(WCSA_ASP)
    X, Y, Z = WCS_PLOTMPL_SETXYZ_INDEX(WCSA_ASP,CCDNUM,FITNUM)
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
    
def WCS_PLOTMPL_REJNUM(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLGET_INDEX(WCSA_ASP)
    REFNUM = hscTansip.F_WCSA_PLGET_REFNUM(WCSA_ASP)
    FITNUM = hscTansip.F_WCSA_PLGET_FITNUM(WCSA_ASP)
    REJNUM=[0 for i in range(CCDNUM)]
    for i in range(0,CCDNUM):
        REJNUM[i]=REFNUM[i]-FITNUM[i]
    X, Y, Z = WCS_PLOTMPL_SETXYZ_INDEX(WCSA_ASP,CCDNUM,REJNUM)
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
    
def WCS_PLOTMPL_SETXYZ_INDEX(WCSA_ASP,CCDNUM, VALUE):
    INDEX  = hscTansip.F_WCSA_PLGET_INDEX(WCSA_ASP)
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

def WCS_PLOTMPL_RMSSIPX(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLGET_INDEX(WCSA_ASP)
    SIPRMS = hscTansip.F_WCSA_PLGET_SIPRMSX(WCSA_ASP)
    X, Y, Z = WCS_PLOTMPL_SETXYZ_INDEX(WCSA_ASP,CCDNUM,SIPRMS)
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
    
def WCS_PLOTMPL_RMSSIPY(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLGET_INDEX(WCSA_ASP)
    SIPRMS = hscTansip.F_WCSA_PLGET_SIPRMSY(WCSA_ASP)
    X, Y, Z = WCS_PLOTMPL_SETXYZ_INDEX(WCSA_ASP,CCDNUM,SIPRMS)
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
    
def WCS_PLOTMPL_RMSPSIPX(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLGET_INDEX(WCSA_ASP)
    SIPRMS = hscTansip.F_WCSA_PLGET_PSIPRMSX(WCSA_ASP)
    X, Y, Z = WCS_PLOTMPL_SETXYZ_INDEX(WCSA_ASP,CCDNUM,SIPRMS)
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
    
def WCS_PLOTMPL_RMSPSIPY(WCSA_ASP):
    CCDNUM = hscTansip.F_WCSA_PLGET_CCDNUM(WCSA_ASP)
    INDEX  = hscTansip.F_WCSA_PLGET_INDEX(WCSA_ASP)
    SIPRMS = hscTansip.F_WCSA_PLGET_PSIPRMSY(WCSA_ASP)
    X, Y, Z = WCS_PLOTMPL_SETXYZ_INDEX(WCSA_ASP,CCDNUM,SIPRMS)
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
