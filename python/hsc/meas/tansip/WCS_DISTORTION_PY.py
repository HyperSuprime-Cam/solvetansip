#!/usr/bin/env python

import hsc.meas.tansip.WCS_DISTORTION as WCS_DISTORTION
import lsst.afw.coord as afwCoord
def F_WCS_DISTORTION_wcsList_XY(wcs,X,Y):
    CRPIX_C = WCS_DISTORTION.DoubleVector(2)
    CRVAL_C = WCS_DISTORTION.DoubleVector(2)
    CD_C    = WCS_DISTORTION.DoubleVector(4)

    CRPIX      = wcs.getPixelOrigin()
    CRPIX_C[0] = CRPIX.getX()
    CRPIX_C[1] = CRPIX.getY()
    CRVAL      = wcs.getSkyOrigin()
    CRVAL_C[0] = CRVAL.getLongitude(afwCoord.DEGREES)
    CRVAL_C[1] = CRVAL.getLatitude(afwCoord.DEGREES)
    CD      = wcs.getCDMatrix()
    CD_C[0] = CD[0,0]
    CD_C[1] = CD[0,1]
    CD_C[2] = CD[1,0]
    CD_C[3] = CD[1,1]

    wcsMeta = wcs.getFitsMetadata()
#    print wcsMeta

#    wcsString = wcsMeta.toString()
#    print type(wcsString)
#    print wcsString

    A_ORDER = wcsMeta.get("A_ORDER")
#    print "A_ORDER : ", A_ORDER
    SIP_A_C = WCS_DISTORTION.DoubleVector((A_ORDER+1)*(A_ORDER+1))
    ij=0
    for i in range(A_ORDER+1):
        for j in range(A_ORDER+1):
            if(i + j < A_ORDER+1):
               if i + j == 1:
                   SIP_A_C[ij] = 0
               else:
                   SIP_A_C[ij] = wcsMeta.get("A_%d_%d" %(i,j))
               ij+=1;

    B_ORDER=wcsMeta.get("B_ORDER")
#    print "B_ORDER : ", B_ORDER
    SIP_B_C = WCS_DISTORTION.DoubleVector((B_ORDER+1)*(B_ORDER+1))
    ij=0
    for i in range(B_ORDER+1):
        for j in range(B_ORDER+1):
            if(i + j < B_ORDER+1):
               if i + j == 1:
                   SIP_B_C[ij] = 0
               else:
                   SIP_B_C[ij] = wcsMeta.get("B_%d_%d" %(i,j))
               ij+=1;

    MSSR=WCS_DISTORTION.F_WCS_DISTORTION_wcsList_XY(CRPIX_C,CRVAL_C,CD_C,A_ORDER,SIP_A_C,B_ORDER,SIP_B_C,X,Y)
    return MSSR

def F_WCS_DISTORTION_wcsList_RADEC(wcs,RA,DEC):
    CRPIX_C = WCS_DISTORTION.DoubleVector(2)
    CRVAL_C = WCS_DISTORTION.DoubleVector(2)
    CD_C    = WCS_DISTORTION.DoubleVector(4)

    CRPIX      = wcs.getPixelOrigin()
    CRPIX_C[0] = CRPIX.getX()
    CRPIX_C[1] = CRPIX.getY()
    CRVAL      = wcs.getSkyOrigin()
    CRVAL_C[0] = CRVAL.getLongitude(afwCoord.DEGREES)
    CRVAL_C[1] = CRVAL.getLatitude(afwCoord.DEGREES)
    CD      = wcs.getCDMatrix()
    CD_C[0] = CD[0,0]
    CD_C[1] = CD[0,1]
    CD_C[2] = CD[1,0]
    CD_C[3] = CD[1,1]

    wcsMeta = wcs.getFitsMetadata()
#    print wcsMeta

    AP_ORDER = wcsMeta.get("AP_ORDER")
#    print "AP_ORDER : ", AP_ORDER
    SIP_AP_C = WCS_DISTORTION.DoubleVector((AP_ORDER+1)*(AP_ORDER+1))
    ij=0
    for i in range(AP_ORDER+1):
        for j in range(AP_ORDER+1):
            if(i + j < AP_ORDER+1):
               SIP_AP_C[ij] = wcsMeta.get("AP_%d_%d" %(i,j))
               ij+=1;

    BP_ORDER=wcsMeta.get("BP_ORDER")
#    print "BP_ORDER : ", BP_ORDER
    SIP_BP_C = WCS_DISTORTION.DoubleVector((BP_ORDER+1)*(BP_ORDER+1))
    ij=0
    for i in range(BP_ORDER+1):
        for j in range(BP_ORDER+1):
            if(i + j < BP_ORDER+1):
               SIP_BP_C[ij] = wcsMeta.get("BP_%d_%d" %(i,j))
               ij+=1;

    MSSR=WCS_DISTORTION.F_WCS_DISTORTION_wcsList_RADEC(CRPIX_C,CRVAL_C,CD_C,AP_ORDER,SIP_AP_C,BP_ORDER,SIP_BP_C,RA,DEC)
    return MSSR

def F_WCS_DISTORTION_CSIP_XY(CPROP,X,Y):
    MSSR=(0,0,0,0)
    return MSSR
def F_WCS_DISTORTION_CSIP_RADEC(CPROP,RA,DEC):
    MSSR=(0,0,0,0)
    return MSSR
