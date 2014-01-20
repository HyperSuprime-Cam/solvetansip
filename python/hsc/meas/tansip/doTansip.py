import sys, re, os, math
import hsc.meas.tansip.SLVTS_SWIGLib     as SLVTS
import lsst.afw.cameraGeom.utils      as cameraGeomUtils
import lsst.afw.cameraGeom            as cameraGeom
#import lsst.daf.base                     as dafBase

def doTansip(matchListAllCcd, policy=None, camera=None, rerun=None):
    metaTANSIP = SLVTS.SET_EMPTYMETADATA()
    SLVTSresult=SOLVETANSIP(matchListAllCcd, metaTANSIP, policy=policy, camera=camera, rerun=rerun)
    return SLVTSresult
	
def doTansipQa(matchListAllCcd, policy=None, camera=None, rerun=None):
    metaTANSIP = SLVTS.SET_EMPTYMETADATA()
    SLVTSresult=SOLVETANSIP(matchListAllCcd, metaTANSIP, policy=policy, camera=camera, rerun=rerun)
    return SLVTSresult,metaTANSIP
	
def SOLVETANSIP(matchListAllCcd, metaTANSIP, policy=None, camera=None, rerun=None):
    print '--- doTansip : start ---'

    print '--- doTansip : get APRM ---'
    APRM=SLVTS_APRM(policy)

    print '--- doTansip : get CCD ---'
    CCD=SLVTS_CCD(int(APRM[-1][1]),camera)

    print '--- doTansip : get REF ---'
    REF=SLVTS_REF(matchListAllCcd)
    KV=SLVTS.VS([])
    KV.append('NUM_REF')
    KV.append(str(len(REF)))
    APRM.append(KV)

    print '--- doTansip : SOLVE TANSIP ---'
    SLVTS_Argvs=SLVTS.VVVS([])
    SLVTS_Argvs.append(APRM)
    SLVTS_Argvs.append(CCD)
    SLVTS_Argvs.append(REF)
    WCS=SLVTS.SOLVETANSIP(SLVTS_Argvs)
    SLVTS.SET_METADATA(WCS, metaTANSIP)

    print '--- doTansip : end   ---'
    return WCS


def getwcsList(WCS):
    print '--- getWCSlist ---'
#    return hscTansip.F_WCSA_PLMAIN_GETWCSLIST(WCSA_ASP)
    return WCS

def SLVTS_APRM(policy):
    KVs=SLVTS.VVS([])

    for K in ['INSTR','MODE_CR','MODE_CCDPOS','PRECISION_POS','ORDER_ASIP','ORDER_PSIP','MODE_REJ','CRPIX1','CRPIX2','CRVAL1','CRVAL2','FLAG_STD','FLAG_OUT','DIR_OUT']:
        KV=SLVTS.VS([])
        KV.append(K)
        KV.append(str(policy.get(K)))
        KVs.append(KV)

    KV=SLVTS.VS([])
    KV.append('NUM_CCD')
    if KVs[0][1] == 'SC':
        KV.append('10')
    elif KVs[0][1] == 'HSC':
        KV.append('104')
    else:
        sys.exit('policy "INSTR" must be "SC" or "HSC"')
    KVs.append(KV)

    return KVs

def SLVTS_REF(matchListAllCcd):
    REFs=SLVTS.VVS([])
    CID=0
    for matchList in matchListAllCcd:
        if (matchList):
            for m in matchList:
                REF=SLVTS.VS([])
                REF.append(str(m.getId()))
                REF.append(str(CID))
                REF.append(str(m.getX()))
                REF.append(str(m.getY()))
                REF.append(str(m.getRa()))
                REF.append(str(m.getDec()))
                REFs.append(REF)
        CID+=1

    OUTNAME="./REF.dat"
    FOUT=open(OUTNAME,"w")
    for i in range(len(REFs)):
        print>>FOUT ,REFs[i][0] ,REFs[i][1] ,REFs[i][2] ,REFs[i][3] ,REFs[i][4] ,REFs[i][5]

    return REFs

def SLVTS_CCD(NUMCCD,camera):
    CCDs=SLVTS.VVS([])

    for CID in range(NUMCCD):
        DID=cameraGeom.Id(CID)
        CGeom=cameraGeomUtils.findCcd(camera,DID)
	PS = CGeom.getPixelSize()
        CCD=SLVTS.VS([])
        CCD.append(str(DID.getSerial()))
        CCD.append(str(CGeom.getCenter().getPixels(PS)[0]))
        CCD.append(str(CGeom.getCenter().getPixels(PS)[1]))
        CCD.append(str(CGeom.getOrientation().getYaw().asRadians()))
        CCD.append(str(CGeom.getSize().getPixels(PS)[0]))
        CCD.append(str(CGeom.getSize().getPixels(PS)[1]))
        CCDs.append(CCD)

    OUTNAME="./CCD.dat"
    FOUT=open(OUTNAME,"w")
    for CID in range(NUMCCD):
        print>>FOUT ,CCDs[CID][0] ,CCDs[CID][1] ,CCDs[CID][2] ,CCDs[CID][3] ,CCDs[CID][4] ,CCDs[CID][5]

    return CCDs

