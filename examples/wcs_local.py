#!/usr/bin/env python

import os
import os.path
import sys
import numpy

import lsst.pipette.readwrite as pipReadWrite
import lsst.pex.policy as pexPolicy
import lsst.obs.hscSim as hscSim
import lsst.obs.suprimecam as scmapper

import hsc.meas.tansip.doTansip as doTansip
#import hsc.meas.tansip.WCS_PL_MAIN       as hscTansip
import lsst.afw.detection as afwDet
import lsst.afw.geom as afwGeom
import lsst.afw.image as afwImage
import lsst.afw.coord as afwCoord
import lsst.pipette.plotter as pipPlot

#WCS_POSITION.F_WCS_POSITION_TEST()

print sys.argv
print sys.argv[1]
matches_address = sys.argv[1]
#mapper = scmapper.SuprimecamMapper(rerun="fh-dc2.9c-default") 
mapper = hscSim.HscSimMapper(rerun="fh-dc2.9c-default")

#plot = pipPlot.Plotter('wcs')
#mapper = scmapper.SuprimecamMapper(rerun="fh-dc2.9c-default") 
#io = pipReadWrite.ReadWrite(mapper, ['visit'], fileKeys=['visit', 'ccd'])
#data = {'visit': 126929}#929-941-

CNUMBER = 0
ANGLE=0

policyPath = os.path.join(os.getenv("SOLVETANSIP_DIR"), "policy", "WCS_MAKEAPROP.paf")
policy = pexPolicy.Policy.createPolicy(policyPath)

#policy.set("LSIPORDER", 1)
#policy.set("SIPORDER", 6)
metadata = doTansip.F_WCS_EMPTYMETADATA()

#wcsList = doTansip.doTansip(matches, policy=policy, camera=mapper.camera)
WCSA_ASP = doTansip.getresultWcs_local(matches_address, metadata, policy=policy, camera=mapper.camera)
#-----------------------------------------------------------------
#Output Functions : WCSA_ASP
#-----------------------------------------------------------------
SIPFILENAME = 'SIPfromWCSA.txt'
doTansip.WCS_OUTPUT_SIP(WCSA_ASP,SIPFILENAME)
doTansip.WCS_INPUT_SIP(WCSA_ASP,SIPFILENAME)
CCDFILENAME = 'CCDfromWCSA.txt'
doTansip.WCS_OUTPUT_CCD(WCSA_ASP,CCDFILENAME)
doTansip.WCS_INPUT_CCD(WCSA_ASP,CCDFILENAME)
#-----------------------------------------------------------------
#Simulation Functions : WCSA_ASP
#-----------------------------------------------------------------
#RANNUM=1;
#REFNUMlist=[3,5,10,20,30,50,2000];
#for REFNUM in range (1,2001):
#    if REFNUM in REFNUMlist:
#        for RANNUM in range (1,10000):
#            SIMFILENAME = 'RREF/SIMULATIONDATA_'+str(REFNUM)+'_'+str(RANNUM)+'.txt'
#            print SIMFILENAME
#            doTansip.WCS_MAKE_RANDDATA(RANNUM,REFNUM,WCSA_ASP,SIMFILENAME)
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : POSITION
#-----------------------------------------------------------------
CCDrefinfo_XY_LOCAL = doTansip.WCS_GET_REFERENCE_XY_LOCAL(WCSA_ASP,0)
print 'LOCAL : ', CCDrefinfo_XY_LOCAL[0]
CCDrefinfo_XY_CRPIX = doTansip.WCS_GET_REFERENCE_XY_LOCALCRPIX(WCSA_ASP,0)
print 'CRPIX : ', CCDrefinfo_XY_CRPIX[0]
CCDrefinfo_XY_RADEC = doTansip.WCS_GET_REFERENCE_XY_RADEC(WCSA_ASP,0)
print 'RADEC : ', CCDrefinfo_XY_RADEC[0]
POSITIONinfo_RADECfromLOCAL = doTansip.WCS_GET_POSITION_RADECfromLOCAL(WCSA_ASP,0,CCDrefinfo_XY_LOCAL[0])
print 'RADEC : ', POSITIONinfo_RADECfromLOCAL
POSITIONinfo_RADECfromCRPIX = doTansip.WCS_GET_POSITION_RADECfromCRPIX(WCSA_ASP,0,CCDrefinfo_XY_CRPIX[0])
print 'RADEC : ', POSITIONinfo_RADECfromCRPIX
POSITIONinfo_LOCALfromRADEC = doTansip.WCS_GET_POSITION_LOCALfromRADEC(WCSA_ASP,0,CCDrefinfo_XY_RADEC[0])
print 'LOCAL : ', POSITIONinfo_LOCALfromRADEC
POSITIONinfo_CRPIXfromRADEC = doTansip.WCS_GET_POSITION_CRPIXfromRADEC(WCSA_ASP,0,CCDrefinfo_XY_RADEC[0])
print 'CRPIX : ', POSITIONinfo_CRPIXfromRADEC

CCDrefinfo_XY_GLOBAL = doTansip.WCS_GET_REFERENCE_XY_GLOBAL(WCSA_ASP,-1)
print 'LOCAL : ', CCDrefinfo_XY_GLOBAL[0]
CCDrefinfo_XY_CRPIX = doTansip.WCS_GET_REFERENCE_XY_GLOBALCRPIX(WCSA_ASP,-1)
print 'CRPIX : ', CCDrefinfo_XY_CRPIX[0]
CCDrefinfo_XY_RADEC = doTansip.WCS_GET_REFERENCE_XY_RADEC(WCSA_ASP,-1)
print 'RADEC : ', CCDrefinfo_XY_RADEC[0]
POSITIONinfo_RADECfromLOCAL = doTansip.WCS_GET_POSITION_RADECfromLOCAL(WCSA_ASP,-1,CCDrefinfo_XY_LOCAL[0])
print 'RADEC : ', POSITIONinfo_RADECfromLOCAL
POSITIONinfo_RADECfromCRPIX = doTansip.WCS_GET_POSITION_RADECfromCRPIX(WCSA_ASP,-1,CCDrefinfo_XY_CRPIX[0])
print 'RADEC : ', POSITIONinfo_RADECfromCRPIX
POSITIONinfo_LOCALfromRADEC = doTansip.WCS_GET_POSITION_LOCALfromRADEC(WCSA_ASP,-1,CCDrefinfo_XY_RADEC[0])
print 'LOCAL : ', POSITIONinfo_LOCALfromRADEC
POSITIONinfo_CRPIXfromRADEC = doTansip.WCS_GET_POSITION_CRPIXfromRADEC(WCSA_ASP,-1,CCDrefinfo_XY_RADEC[0])
print 'CRPIX : ', POSITIONinfo_CRPIXfromRADEC

print ''
GRID=[-1000, -1000,1000, 1000, 1000, 1000]
POSITIONinfo_RADECfromGRID = doTansip.WCS_GET_POSITION_RADECfromGRID(WCSA_ASP,-1,GRID)
print 'RADEC : ', POSITIONinfo_RADECfromGRID[0][0], POSITIONinfo_RADECfromGRID[0][1], POSITIONinfo_RADECfromGRID[0][2], POSITIONinfo_RADECfromGRID[0][3]
print 'RADEC : ', POSITIONinfo_RADECfromGRID[1][0], POSITIONinfo_RADECfromGRID[1][1], POSITIONinfo_RADECfromGRID[1][2], POSITIONinfo_RADECfromGRID[1][3]
print 'RADEC : ', POSITIONinfo_RADECfromGRID[2][0], POSITIONinfo_RADECfromGRID[2][1], POSITIONinfo_RADECfromGRID[2][2], POSITIONinfo_RADECfromGRID[2][3]
print 'RADEC : ', POSITIONinfo_RADECfromGRID[3][0], POSITIONinfo_RADECfromGRID[3][1], POSITIONinfo_RADECfromGRID[3][2], POSITIONinfo_RADECfromGRID[3][3]
print 'RADEC : ', POSITIONinfo_RADECfromGRID[4][0], POSITIONinfo_RADECfromGRID[4][1], POSITIONinfo_RADECfromGRID[4][2], POSITIONinfo_RADECfromGRID[4][3]
print 'RADEC : ', POSITIONinfo_RADECfromGRID[5][0], POSITIONinfo_RADECfromGRID[5][1], POSITIONinfo_RADECfromGRID[5][2], POSITIONinfo_RADECfromGRID[5][3]
print 'RADEC : ', POSITIONinfo_RADECfromGRID[6][0], POSITIONinfo_RADECfromGRID[6][1], POSITIONinfo_RADECfromGRID[6][2], POSITIONinfo_RADECfromGRID[6][3]
print 'RADEC : ', POSITIONinfo_RADECfromGRID[7][0], POSITIONinfo_RADECfromGRID[7][1], POSITIONinfo_RADECfromGRID[7][2], POSITIONinfo_RADECfromGRID[7][3]
print 'RADEC : ', POSITIONinfo_RADECfromGRID[8][0], POSITIONinfo_RADECfromGRID[8][1], POSITIONinfo_RADECfromGRID[8][2], POSITIONinfo_RADECfromGRID[8][3]

XSTR=POSITIONinfo_RADECfromGRID[1][2]-0.1
YSTR=POSITIONinfo_RADECfromGRID[1][3]-0.1
XEND=POSITIONinfo_RADECfromGRID[1][2]+0.1
YEND=POSITIONinfo_RADECfromGRID[1][3]+0.1
GRID[0]=XSTR
GRID[1]=YSTR
GRID[2]=XEND
GRID[3]=YEND
GRID[4]=0.1
GRID[5]=0.1
POSITIONinfo_LOCALfromGRID = doTansip.WCS_GET_POSITION_LOCALfromGRID(WCSA_ASP,-1,GRID)
print 'LOCAL : ', POSITIONinfo_LOCALfromGRID[0][0], POSITIONinfo_LOCALfromGRID[0][1], POSITIONinfo_LOCALfromGRID[0][2], POSITIONinfo_LOCALfromGRID[0][3]
print 'LOCAL : ', POSITIONinfo_LOCALfromGRID[1][0], POSITIONinfo_LOCALfromGRID[1][1], POSITIONinfo_LOCALfromGRID[1][2], POSITIONinfo_LOCALfromGRID[1][3]
print 'LOCAL : ', POSITIONinfo_LOCALfromGRID[2][0], POSITIONinfo_LOCALfromGRID[2][1], POSITIONinfo_LOCALfromGRID[2][2], POSITIONinfo_LOCALfromGRID[2][3]
print 'LOCAL : ', POSITIONinfo_LOCALfromGRID[3][0], POSITIONinfo_LOCALfromGRID[3][1], POSITIONinfo_LOCALfromGRID[3][2], POSITIONinfo_LOCALfromGRID[3][3]
print 'LOCAL : ', POSITIONinfo_LOCALfromGRID[4][0], POSITIONinfo_LOCALfromGRID[4][1], POSITIONinfo_LOCALfromGRID[4][2], POSITIONinfo_LOCALfromGRID[4][3]
print 'LOCAL : ', POSITIONinfo_LOCALfromGRID[5][0], POSITIONinfo_LOCALfromGRID[5][1], POSITIONinfo_LOCALfromGRID[5][2], POSITIONinfo_LOCALfromGRID[5][3]
print 'LOCAL : ', POSITIONinfo_LOCALfromGRID[6][0], POSITIONinfo_LOCALfromGRID[6][1], POSITIONinfo_LOCALfromGRID[6][2], POSITIONinfo_LOCALfromGRID[6][3]
print 'LOCAL : ', POSITIONinfo_LOCALfromGRID[7][0], POSITIONinfo_LOCALfromGRID[7][1], POSITIONinfo_LOCALfromGRID[7][2], POSITIONinfo_LOCALfromGRID[7][3]
print 'LOCAL : ', POSITIONinfo_LOCALfromGRID[8][0], POSITIONinfo_LOCALfromGRID[8][1], POSITIONinfo_LOCALfromGRID[8][2], POSITIONinfo_LOCALfromGRID[8][3]


GRID=[-10000, -10000,10000, 10000, 10000, 10000]
JACOBIANinfo_atGRID = doTansip.WCS_GET_CRSMA_atLOCALGRID(WCSA_ASP,-1,GRID)
print 'RADEC : ', JACOBIANinfo_atGRID[0][0], JACOBIANinfo_atGRID[0][1], JACOBIANinfo_atGRID[0][2], JACOBIANinfo_atGRID[0][3], JACOBIANinfo_atGRID[0][4], JACOBIANinfo_atGRID[0][5], JACOBIANinfo_atGRID[0][6], JACOBIANinfo_atGRID[0][7]
print 'RADEC : ', JACOBIANinfo_atGRID[1][0], JACOBIANinfo_atGRID[1][1], JACOBIANinfo_atGRID[1][2], JACOBIANinfo_atGRID[1][3], JACOBIANinfo_atGRID[1][4], JACOBIANinfo_atGRID[1][5], JACOBIANinfo_atGRID[1][6], JACOBIANinfo_atGRID[1][7]
print 'RADEC : ', JACOBIANinfo_atGRID[2][0], JACOBIANinfo_atGRID[2][1], JACOBIANinfo_atGRID[2][2], JACOBIANinfo_atGRID[2][3], JACOBIANinfo_atGRID[2][4], JACOBIANinfo_atGRID[2][5], JACOBIANinfo_atGRID[2][6], JACOBIANinfo_atGRID[2][7]
print 'RADEC : ', JACOBIANinfo_atGRID[3][0], JACOBIANinfo_atGRID[3][1], JACOBIANinfo_atGRID[3][2], JACOBIANinfo_atGRID[3][3], JACOBIANinfo_atGRID[3][4], JACOBIANinfo_atGRID[3][5], JACOBIANinfo_atGRID[3][6], JACOBIANinfo_atGRID[3][7]
print 'RADEC : ', JACOBIANinfo_atGRID[4][0], JACOBIANinfo_atGRID[4][1], JACOBIANinfo_atGRID[4][2], JACOBIANinfo_atGRID[4][3], JACOBIANinfo_atGRID[4][4], JACOBIANinfo_atGRID[4][5], JACOBIANinfo_atGRID[4][6], JACOBIANinfo_atGRID[4][7]
print 'RADEC : ', JACOBIANinfo_atGRID[5][0], JACOBIANinfo_atGRID[5][1], JACOBIANinfo_atGRID[5][2], JACOBIANinfo_atGRID[5][3], JACOBIANinfo_atGRID[5][4], JACOBIANinfo_atGRID[5][5], JACOBIANinfo_atGRID[5][6], JACOBIANinfo_atGRID[5][7]
print 'RADEC : ', JACOBIANinfo_atGRID[6][0], JACOBIANinfo_atGRID[6][1], JACOBIANinfo_atGRID[6][2], JACOBIANinfo_atGRID[6][3], JACOBIANinfo_atGRID[6][4], JACOBIANinfo_atGRID[6][5], JACOBIANinfo_atGRID[6][6], JACOBIANinfo_atGRID[6][7]
print 'RADEC : ', JACOBIANinfo_atGRID[7][0], JACOBIANinfo_atGRID[7][1], JACOBIANinfo_atGRID[7][2], JACOBIANinfo_atGRID[7][3], JACOBIANinfo_atGRID[7][4], JACOBIANinfo_atGRID[7][5], JACOBIANinfo_atGRID[7][6], JACOBIANinfo_atGRID[7][7]
print 'RADEC : ', JACOBIANinfo_atGRID[8][0], JACOBIANinfo_atGRID[8][1], JACOBIANinfo_atGRID[8][2], JACOBIANinfo_atGRID[8][3], JACOBIANinfo_atGRID[8][4], JACOBIANinfo_atGRID[8][5], JACOBIANinfo_atGRID[8][6], JACOBIANinfo_atGRID[8][7]

print ''
X_GLOBAL=(500,500);
POSITIONinfo_CCDIDLOCAL = doTansip.WCS_GET_POSITION_CCDIDLOCALfromGLOBAL(WCSA_ASP,X_GLOBAL)
print 'CCDID : ', POSITIONinfo_CCDIDLOCAL[0],' : XY : ',POSITIONinfo_CCDIDLOCAL[1],POSITIONinfo_CCDIDLOCAL[2]
CCDID=int(POSITIONinfo_CCDIDLOCAL[0])
X_LOCAL=(POSITIONinfo_CCDIDLOCAL[1],POSITIONinfo_CCDIDLOCAL[2])
POSITIONinfo_GLOBAL = doTansip.WCS_GET_POSITION_GLOBALfromCCDIDLOCAL(WCSA_ASP,CCDID,X_LOCAL)
print POSITIONinfo_GLOBAL
X_GLOBAL=(100000,100000);
POSITIONinfo_CCDIDLOCAL = doTansip.WCS_GET_POSITION_CCDIDLOCALfromGLOBAL(WCSA_ASP,X_GLOBAL)
print 'CCDID : ', POSITIONinfo_CCDIDLOCAL[0],' : XY : ',POSITIONinfo_CCDIDLOCAL[1],POSITIONinfo_CCDIDLOCAL[2]
print ''
#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : REFERENCES
#-----------------------------------------------------------------
print "--- getting function : references ---"
print "--- getting function : references : ID ---"
CCDrefinfo_ID = doTansip.WCS_GET_REFERENCE_ID(WCSA_ASP,0)
print CCDrefinfo_ID[0]
print CCDrefinfo_ID[1]
ALLrefinfo_ID = doTansip.WCS_GET_REFERENCE_ID(WCSA_ASP,-1)
print ALLrefinfo_ID[0]
print ALLrefinfo_ID[1]
print "--- getting function : references : CHIPID ---"
CCDrefinfo_CHIPID = doTansip.WCS_GET_REFERENCE_CHIPID(WCSA_ASP,0)
print CCDrefinfo_CHIPID[0]
print CCDrefinfo_CHIPID[1]
ALLrefinfo_CHIPID = doTansip.WCS_GET_REFERENCE_CHIPID(WCSA_ASP,-1)
print ALLrefinfo_CHIPID[0]
print ALLrefinfo_CHIPID[1]
print "--- getting function : references : FLAG ---"
CCDrefinfo_FLAG = doTansip.WCS_GET_REFERENCE_FLAG(WCSA_ASP,0)
print CCDrefinfo_FLAG[0]
print CCDrefinfo_FLAG[1]
ALLrefinfo_FLAG = doTansip.WCS_GET_REFERENCE_FLAG(WCSA_ASP,-1)
print ALLrefinfo_FLAG[0]
print ALLrefinfo_FLAG[1]
print "--- getting function : references : XY_LOCAL ---"
CCDrefinfo_XY_LOCAL = doTansip.WCS_GET_REFERENCE_XY_LOCAL(WCSA_ASP,0)
print CCDrefinfo_XY_LOCAL[0]
print CCDrefinfo_XY_LOCAL[1]
ALLrefinfo_XY_LOCAL = doTansip.WCS_GET_REFERENCE_XY_LOCAL(WCSA_ASP,-1)
print ALLrefinfo_XY_LOCAL[0]
print ALLrefinfo_XY_LOCAL[1]
print "--- getting function : references : XY_RADEC ---"
CCDrefinfo_XY_RADEC = doTansip.WCS_GET_REFERENCE_XY_RADEC(WCSA_ASP,0)
print CCDrefinfo_XY_RADEC[0]
print CCDrefinfo_XY_RADEC[1]
ALLrefinfo_XY_RADEC = doTansip.WCS_GET_REFERENCE_XY_RADEC(WCSA_ASP,-1)
print ALLrefinfo_XY_RADEC[0]
print ALLrefinfo_XY_RADEC[1]
print "--- getting function : references : XY_GLOBAL ---"
CCDrefinfo_XY_GLOBAL = doTansip.WCS_GET_REFERENCE_XY_GLOBAL(WCSA_ASP,0)
print CCDrefinfo_XY_GLOBAL[0]
print CCDrefinfo_XY_GLOBAL[1]
ALLrefinfo_XY_GLOBAL = doTansip.WCS_GET_REFERENCE_XY_GLOBAL(WCSA_ASP,-1)
print ALLrefinfo_XY_GLOBAL[0]
print ALLrefinfo_XY_GLOBAL[1]
print "--- getting function : references : XY_GLOBALCRPIX ---"
CCDrefinfo_XY_GLOBALCRPIX = doTansip.WCS_GET_REFERENCE_XY_GLOBALCRPIX(WCSA_ASP,0)
print CCDrefinfo_XY_GLOBALCRPIX[0]
print CCDrefinfo_XY_GLOBALCRPIX[1]
ALLrefinfo_XY_GLOBALCRPIX = doTansip.WCS_GET_REFERENCE_XY_GLOBALCRPIX(WCSA_ASP,-1)
print ALLrefinfo_XY_GLOBALCRPIX[0]
print ALLrefinfo_XY_GLOBALCRPIX[1]
print "--- getting function : references : XY_LOCALCRPIX ---"
CCDrefinfo_XY_LOCALCRPIX = doTansip.WCS_GET_REFERENCE_XY_LOCALCRPIX(WCSA_ASP,0)
print CCDrefinfo_XY_LOCALCRPIX[0]
print CCDrefinfo_XY_LOCALCRPIX[1]
ALLrefinfo_XY_LOCALCRPIX = doTansip.WCS_GET_REFERENCE_XY_LOCALCRPIX(WCSA_ASP,-1)
print ALLrefinfo_XY_LOCALCRPIX[0]
print ALLrefinfo_XY_LOCALCRPIX[1]
print "--- getting function : references : XY_IMPIXEL ---"
CCDrefinfo_XY_IMPIXEL = doTansip.WCS_GET_REFERENCE_XY_IMPIXEL(WCSA_ASP,0)
print CCDrefinfo_XY_IMPIXEL[0]
print CCDrefinfo_XY_IMPIXEL[1]
ALLrefinfo_XY_IMPIXEL = doTansip.WCS_GET_REFERENCE_XY_IMPIXEL(WCSA_ASP,-1)
print ALLrefinfo_XY_IMPIXEL[0]
print ALLrefinfo_XY_IMPIXEL[1]
print "--- getting function : references : XY_IMWORLD ---"
CCDrefinfo_XY_IMWORLD = doTansip.WCS_GET_REFERENCE_XY_IMWORLD(WCSA_ASP,0)
print CCDrefinfo_XY_IMWORLD[0]
print CCDrefinfo_XY_IMWORLD[1]
ALLrefinfo_XY_IMWORLD = doTansip.WCS_GET_REFERENCE_XY_IMWORLD(WCSA_ASP,-1)
print ALLrefinfo_XY_IMWORLD[0]
print ALLrefinfo_XY_IMWORLD[1]
print "--- getting function : references : CONVERGENCE ---"
CCDrefinfo_CAMERA_CONVERGENCE = doTansip.WCS_GET_REFERENCE_CAMERA_CONVERGENCE(WCSA_ASP,0)
print CCDrefinfo_CAMERA_CONVERGENCE[0]
print CCDrefinfo_CAMERA_CONVERGENCE[1]
ALLrefinfo_CAMERA_CONVERGENCE = doTansip.WCS_GET_REFERENCE_CAMERA_CONVERGENCE(WCSA_ASP,-1)
print ALLrefinfo_CAMERA_CONVERGENCE[0]
print ALLrefinfo_CAMERA_CONVERGENCE[1]
print "--- getting function : references : ROTATION ---"
CCDrefinfo_CAMERA_ROTATION = doTansip.WCS_GET_REFERENCE_CAMERA_ROTATION(WCSA_ASP,0)
print CCDrefinfo_CAMERA_ROTATION[0]
print CCDrefinfo_CAMERA_ROTATION[1]
ALLrefinfo_CAMERA_ROTATION = doTansip.WCS_GET_REFERENCE_CAMERA_ROTATION(WCSA_ASP,-1)
print ALLrefinfo_CAMERA_ROTATION[0]
print ALLrefinfo_CAMERA_ROTATION[1]
print "--- getting function : references : SHEAR1 ---"
CCDrefinfo_CAMERA_SHEAR1 = doTansip.WCS_GET_REFERENCE_CAMERA_SHEAR1(WCSA_ASP,0)
print CCDrefinfo_CAMERA_SHEAR1[0]
print CCDrefinfo_CAMERA_SHEAR1[1]
ALLrefinfo_CAMERA_SHEAR1 = doTansip.WCS_GET_REFERENCE_CAMERA_SHEAR1(WCSA_ASP,-1)
print ALLrefinfo_CAMERA_SHEAR1[0]
print ALLrefinfo_CAMERA_SHEAR1[1]
print "--- getting function : references : SHEAR2 ---"
CCDrefinfo_CAMERA_SHEAR2 = doTansip.WCS_GET_REFERENCE_CAMERA_SHEAR2(WCSA_ASP,0)
print CCDrefinfo_CAMERA_SHEAR2[0]
print CCDrefinfo_CAMERA_SHEAR2[1]
ALLrefinfo_CAMERA_SHEAR2 = doTansip.WCS_GET_REFERENCE_CAMERA_SHEAR2(WCSA_ASP,-1)
print ALLrefinfo_CAMERA_SHEAR2[0]
print ALLrefinfo_CAMERA_SHEAR2[1]
print "--- getting function : references : MAGNIFICATION ---"
CCDrefinfo_CAMERA_MAGNIFICATION = doTansip.WCS_GET_REFERENCE_CAMERA_MAGNIFICATION(WCSA_ASP,0)
print CCDrefinfo_CAMERA_MAGNIFICATION[0]
print CCDrefinfo_CAMERA_MAGNIFICATION[1]
ALLrefinfo_CAMERA_MAGNIFICATION = doTansip.WCS_GET_REFERENCE_CAMERA_MAGNIFICATION(WCSA_ASP,-1)
print ALLrefinfo_CAMERA_MAGNIFICATION[0]
print ALLrefinfo_CAMERA_MAGNIFICATION[1]
print "--- getting function : references : PCONVERGENCE ---"
CCDrefinfo_CAMERA_PCONVERGENCE = doTansip.WCS_GET_REFERENCE_CAMERA_PCONVERGENCE(WCSA_ASP,0)
print CCDrefinfo_CAMERA_PCONVERGENCE[0]
print CCDrefinfo_CAMERA_PCONVERGENCE[1]
ALLrefinfo_CAMERA_PCONVERGENCE = doTansip.WCS_GET_REFERENCE_CAMERA_PCONVERGENCE(WCSA_ASP,-1)
print ALLrefinfo_CAMERA_PCONVERGENCE[0]
print ALLrefinfo_CAMERA_PCONVERGENCE[1]
print "--- getting function : references : PROTATION ---"
CCDrefinfo_CAMERA_PROTATION = doTansip.WCS_GET_REFERENCE_CAMERA_PROTATION(WCSA_ASP,0)
print CCDrefinfo_CAMERA_PROTATION[0]
print CCDrefinfo_CAMERA_PROTATION[1]
ALLrefinfo_CAMERA_PROTATION = doTansip.WCS_GET_REFERENCE_CAMERA_PROTATION(WCSA_ASP,-1)
print ALLrefinfo_CAMERA_PROTATION[0]
print ALLrefinfo_CAMERA_PROTATION[1]
print "--- getting function : references : PSHEAR1 ---"
CCDrefinfo_CAMERA_PSHEAR1 = doTansip.WCS_GET_REFERENCE_CAMERA_PSHEAR1(WCSA_ASP,0)
print CCDrefinfo_CAMERA_PSHEAR1[0]
print CCDrefinfo_CAMERA_PSHEAR1[1]
ALLrefinfo_CAMERA_PSHEAR1 = doTansip.WCS_GET_REFERENCE_CAMERA_PSHEAR1(WCSA_ASP,-1)
print ALLrefinfo_CAMERA_PSHEAR1[0]
print ALLrefinfo_CAMERA_PSHEAR1[1]
print "--- getting function : references : PSHEAR2 ---"
CCDrefinfo_CAMERA_PSHEAR2 = doTansip.WCS_GET_REFERENCE_CAMERA_PSHEAR2(WCSA_ASP,0)
print CCDrefinfo_CAMERA_PSHEAR2[0]
print CCDrefinfo_CAMERA_PSHEAR2[1]
ALLrefinfo_CAMERA_PSHEAR2 = doTansip.WCS_GET_REFERENCE_CAMERA_PSHEAR2(WCSA_ASP,-1)
print ALLrefinfo_CAMERA_PSHEAR2[0]
print ALLrefinfo_CAMERA_PSHEAR2[1]
print "--- getting function : references : PMAGNIFICATION ---"
CCDrefinfo_CAMERA_PMAGNIFICATION = doTansip.WCS_GET_REFERENCE_CAMERA_PMAGNIFICATION(WCSA_ASP,0)
print CCDrefinfo_CAMERA_PMAGNIFICATION[0]
print CCDrefinfo_CAMERA_PMAGNIFICATION[1]
ALLrefinfo_CAMERA_PMAGNIFICATION = doTansip.WCS_GET_REFERENCE_CAMERA_PMAGNIFICATION(WCSA_ASP,-1)
print ALLrefinfo_CAMERA_PMAGNIFICATION[0]
print ALLrefinfo_CAMERA_PMAGNIFICATION[1]

refinfo = doTansip.WCS_GET_REFERENCE_INIDIVIDUAL(WCSA_ASP,0)
print refinfo
refinfo = doTansip.WCS_GET_REFERENCE_INIDIVIDUAL(WCSA_ASP,7)
print refinfo
refinfo = doTansip.WCS_GET_REFERENCE_INIDIVIDUAL(WCSA_ASP,-1)
print refinfo
refinfo = doTansip.WCS_GET_REFERENCE_INIDIVIDUAL(WCSA_ASP,1000000000)
print refinfo

#-----------------------------------------------------------------
#Getting Functions : WCSA_ASP : CCD
#-----------------------------------------------------------------
print "--- getting function : ccd ---"
ccdpositions = doTansip.WCS_GET_CCD_ALL_CCDPOS(WCSA_ASP)
print ccdpositions
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,0)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,1)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,2)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,3)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,4)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,5)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,6)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,7)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,8)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,9)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,10)
print ccdposition
ccdposition = doTansip.WCS_GET_CCD_CCD_CCDPOS(WCSA_ASP,-1)
print ccdposition

#-----------------------------------------------------------------
#Getting Functions : OLD
#-----------------------------------------------------------------
print "--- get wcsList ---"
wcsList = doTansip.getwcsList(WCSA_ASP)
print wcsList
print "--- get references ---"
references = doTansip.getreferences(WCSA_ASP)
#print references
print "--- get RADEC ---"
X_GLOBAL = (0.0,0.0)
RADEC = doTansip.getradec(X_GLOBAL,WCSA_ASP)
print X_GLOBAL
print RADEC
print "--- get X_GLOBAL ---"
X_GLOBAL = doTansip.getxglobal(RADEC,WCSA_ASP)
print RADEC
print X_GLOBAL
print "--- get RADEC ---"
X_GLOBAL = (2000.0,2000.0)
RADEC = doTansip.getradec(X_GLOBAL,WCSA_ASP)
print X_GLOBAL
print RADEC
print "--- get X_GLOBAL ---"
X_GLOBAL = doTansip.getxglobal(RADEC,WCSA_ASP)
print RADEC
print X_GLOBAL
#print "--- get PAIR ID ---"
#PAIR_ID = doTansip.getpair_ID(WCSA_ASP)
#print PAIR_ID
#print "--- get PAIR CHIPID ---"
#PAIR_CHIPID = doTansip.getpair_CHIPID(WCSA_ASP)
#print PAIR_CHIPID
#print "--- get PAIR FLAG ---"
#PAIR_FLAG = doTansip.getpair_FLAG(WCSA_ASP)
#print PAIR_FLAG
#print "--- get PAIR RA ---"
#PAIR_RA = doTansip.getpair_RA(WCSA_ASP)
#print PAIR_RA
#print "--- get PAIR DEC ---"
#PAIR_DEC = doTansip.getpair_DEC(WCSA_ASP)
#print PAIR_DEC
#print "--- get PAIR IM_WORLD_X ---"
#PAIR_IM_WORLD_X = doTansip.getpair_IM_WORLD_X(WCSA_ASP)
#print PAIR_IM_WORLD_X
#print "--- get PAIR IM_WORLD_Y ---"
#PAIR_IM_WORLD_Y = doTansip.getpair_IM_WORLD_Y(WCSA_ASP)
#print PAIR_IM_WORLD_Y
#print "--- get PAIR IM_PIXEL_X ---"
#PAIR_IM_PIXEL_X = doTansip.getpair_IM_PIXEL_X(WCSA_ASP)
#print PAIR_IM_PIXEL_X
#print "--- get PAIR IM_PIXEL_Y ---"
#PAIR_IM_PIXEL_Y = doTansip.getpair_IM_PIXEL_Y(WCSA_ASP)
#print PAIR_IM_PIXEL_Y
#print "--- get PAIR CRPIX_X ---"
#PAIR_CRPIX_X = doTansip.getpair_CRPIX_X(WCSA_ASP)
#print PAIR_CRPIX_X
#print "--- get PAIR CRPIX_Y ---"
#PAIR_CRPIX_Y = doTansip.getpair_CRPIX_Y(WCSA_ASP)
#print PAIR_CRPIX_Y
#print "--- get PAIR GLOBAL_X ---"
#PAIR_GLOBAL_X = doTansip.getpair_GLOBAL_X(WCSA_ASP)
#print PAIR_GLOBAL_X
#print "--- get PAIR GLOBAL_Y ---"
#PAIR_GLOBAL_Y = doTansip.getpair_GLOBAL_Y(WCSA_ASP)
#print PAIR_GLOBAL_Y
#print "--- get PAIR LOCAL_X ---"
#PAIR_LOCAL_X = doTansip.getpair_LOCAL_X(WCSA_ASP)
#print PAIR_LOCAL_X
#print "--- get PAIR LOCAL_Y ---"
#PAIR_LOCAL_Y = doTansip.getpair_LOCAL_Y(WCSA_ASP)
#print PAIR_LOCAL_Y

doTansip.memorydelete(WCSA_ASP)
