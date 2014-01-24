import sys, re, os, math
import pyfits
from pyfits import Column
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
    SLVTSRESULT=SLVTS.SOLVETANSIP(SLVTS_Argvs)
    SLVTS.SET_METADATA(SLVTSRESULT, metaTANSIP)
    TANWCS=SLVTS.SET_TANWCS(SLVTSRESULT)

    FLAG_OUT=policy.get('FLAG_OUT')
    if FLAG_OUT==1:
        DIR_OUT =policy.get('DIR_OUT')
        print "OUTPUT SUMMARY FITS in "+DIR_OUT
        OUTPUT_SUMMARY(SLVTSRESULT,DIR_OUT)
        print "OUTPUT FITS BINARY TABLE in "+DIR_OUT
        OUTPUT_BTBL(SLVTSRESULT,DIR_OUT)

    print '--- doTansip : end   ---'
    return TANWCS

def getwcsList(TANWCS):
    print '--- getWCSlist ---'
    return TANWCS
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

#    OUTNAME="./REF.dat"
#    FOUT=open(OUTNAME,"w")
#    for i in range(len(REFs)):
 #       print>>FOUT ,REFs[i][0] ,REFs[i][1] ,REFs[i][2] ,REFs[i][3] ,REFs[i][4] ,REFs[i][5]

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

#    OUTNAME="./CCD.dat"
#    FOUT=open(OUTNAME,"w")
#    for CID in range(NUMCCD):
#        print>>FOUT ,CCDs[CID][0] ,CCDs[CID][1] ,CCDs[CID][2] ,CCDs[CID][3] ,CCDs[CID][4] ,CCDs[CID][5]

    return CCDs
#-----------------------------------------------------------------
#Output bianry table : S_RESULT
#-----------------------------------------------------------------
def OUTPUT_SUMMARY(V_S_RESULT,DIR_OUT):
    S_RESULT=V_S_RESULT[0]
    if os.path.exists(DIR_OUT) == False:
	os.makedirs(DIR_OUT)    

    SUMNAME=DIR_OUT+"/solvetansipresult_SUMMARY.fits"

    MODE_CR   =SLVTS.GET_SUM_MODECR(S_RESULT)
    MODE_REJ  =SLVTS.GET_SUM_MODEREJ(S_RESULT)
    MODE_CCD  =SLVTS.GET_SUM_MODECCD(S_RESULT)
    NUM_CCD   =SLVTS.GET_SUM_NUMCCD(S_RESULT)
    NUM_REF   =SLVTS.GET_SUM_NUMREF(S_RESULT)
    NUM_FIT   =SLVTS.GET_SUM_NUMFIT(S_RESULT)
    CRPIX     =SLVTS.GET_SUM_CRPIX(S_RESULT)
    CRVAL     =SLVTS.GET_SUM_CRVAL(S_RESULT)
    OAPIX     =SLVTS.GET_SUM_OAPIX(S_RESULT)
    CD        =SLVTS.GET_SUM_CD(S_RESULT)
    ANGLE     =SLVTS.GET_SUM_ANGLE(S_RESULT)
    ST_CRPIX_G=SLVTS.GET_SUM_MAX_CRPIX_G(S_RESULT)
    CD_COR    =SLVTS.GET_SUM_CD_CORANGLE(S_RESULT)
    RMS_SIP   =SLVTS.GET_SUM_RMSASIP(S_RESULT)
    RMS_PSIP  =SLVTS.GET_SUM_RMSPSIP(S_RESULT)
    
    SUMhdu = pyfits.PrimaryHDU()
    SUMhdr = SUMhdu.header
    SUMhdr.update("MODE_CR" ,MODE_CR ,"CR MODE")
    SUMhdr.update("MODE_REJ",MODE_CCD,"REJECTION MODE(1=REJECTION)")
    SUMhdr.update("MODE_CCD",MODE_REJ,"CCD POSITION MODE(i=DETERMINING CCD POSITIONs)")
    SUMhdr.update("NUM_REF",NUM_REF ,"Number of References")
    SUMhdr.update("NUM_FIT",NUM_FIT ,"Number of References fot fitting")
    SUMhdr.update("CRVAL_1",CRVAL[0],"CRVAL 1")
    SUMhdr.update("CRVAL_2",CRVAL[1],"CRVAL 2")
    SUMhdr.update("CRPIX_1",CRPIX[0],"CRPIX 1")
    SUMhdr.update("CRPIX_2",CRPIX[1],"CRPIX 2")
    SUMhdr.update("OAPIX_1",OAPIX[0],"Position X of Optical Axis")
    SUMhdr.update("OAPIX_2",OAPIX[1],"Position Y of Optical Axis")
    SUMhdr.update("CD1_1"  ,CD[0]   ,"CD Matrix at CRPIX")
    SUMhdr.update("CD1_2"  ,CD[1]   ,"CD Matrix at CRPIX")
    SUMhdr.update("CD2_1"  ,CD[2]   ,"CD Matrix at CRPIX")
    SUMhdr.update("CD2_2"  ,CD[3]   ,"CD Matrix at CRPIX")
    SUMhdr.update("ANGLE"  ,ANGLE   ,"ANGLE from 0.5PI(radian)")
    SUMhdr.update("CDCA1_1",CD_COR[0],"CD Matrix of Corrected Angle")
    SUMhdr.update("CDCA1_2",CD_COR[1],"CD Matrix of Corrected Angle")
    SUMhdr.update("CDCA2_1",CD_COR[2],"CD Matrix of Corrected Angle")
    SUMhdr.update("CDCA2_2",CD_COR[3],"CD Matrix of Corrected Angle")
    SUMhdr.update("MAX_R"  ,ST_CRPIX_G[0],"MAXIMUM Radius from CRPIX")
    SUMhdr.update("MAX_X"  ,ST_CRPIX_G[1],"MAXIMUM X position from CRPIX")
    SUMhdr.update("MAX_Y"  ,ST_CRPIX_G[2],"MAXIMUM Y position from CRPIX")
    SUMhdr.update("MIN_X"  ,ST_CRPIX_G[3],"MINIMUM X position from CRPIX")
    SUMhdr.update("MIN_Y"  ,ST_CRPIX_G[4],"MINIMUM Y position from CRPIX")
    SUMhdr.update("AVE_X"  ,ST_CRPIX_G[5],"AVERAGE X position from CRPIX")
    SUMhdr.update("AVE_Y"  ,ST_CRPIX_G[6],"AVERAGE Y position from CRPIX")
    SUMhdr.update("RMSSIPX",RMS_SIP[0],"RMS X of  SIP fitting Error")
    SUMhdr.update("RMSSIPY",RMS_SIP[1],"RMS Y of  SIP fitting Error")
    SUMhdr.update("RMSPSIPX",RMS_PSIP[0],"RMS X of PSIP fitting Error")
    SUMhdr.update("RMSPSIPY",RMS_PSIP[1],"RMS Y of PSIP fitting Error")
    SUMhdu.writeto(SUMNAME,clobber=True)

def OUTPUT_BTBL(V_S_RESULT,DIR_OUT):
    S_RESULT=V_S_RESULT[0]
    if os.path.exists(DIR_OUT) == False:
	os.makedirs(DIR_OUT)    

#CCD-----
    CCDNAME=DIR_OUT+"/solvetansipresult_CCDs.fits"
    CCDID  =SLVTS.GET_CCD_ID(S_RESULT)
    CCDRNUM=SLVTS.GET_CCD_NUMREF(S_RESULT)
    CCDFNUM=SLVTS.GET_CCD_NUMFIT(S_RESULT)
    CCDPOSL=SLVTS.GET_CCD_GPOS_L(S_RESULT)
    CCDPOSC=SLVTS.GET_CCD_GPOS_C(S_RESULT)
    CCDCR  =SLVTS.GET_CCD_CR(S_RESULT)
    CCDOA  =SLVTS.GET_CCD_OA(S_RESULT)
    CCDCD  =SLVTS.GET_CCD_CD(S_RESULT)
    CCDSORD=SLVTS.GET_CCD_ORDERSIP(S_RESULT)
    CCDPORD=SLVTS.GET_CCD_ORDERPSIP(S_RESULT)
    CCDSERR=SLVTS.GET_CCD_ERRSIP(S_RESULT)
    CCDPERR=SLVTS.GET_CCD_ERRPSIP(S_RESULT)
    CCDSCOA=SLVTS.GET_CCD_COEFSIPA(S_RESULT)
    CCDSCOB=SLVTS.GET_CCD_COEFSIPB(S_RESULT)
    CCDPCOA=SLVTS.GET_CCD_COEFPSIPA(S_RESULT)
    CCDPCOB=SLVTS.GET_CCD_COEFPSIPB(S_RESULT)

    CCDCOL=[]
    CCDCOL.append(Column(name="ID_CCD"        ,format="J",array=CCDID))
    CCDCOL.append(Column(name="NUM_REF"       ,format="J",array=CCDRNUM))
    CCDCOL.append(Column(name="NUM_FIT"       ,format="J",array=CCDFNUM))
    CCDCOL.append(Column(name="GPOS_L_X"      ,format="D",unit="pixel",array=CCDPOSL[0]))
    CCDCOL.append(Column(name="GPOS_L_Y"      ,format="D",unit="pixel",array=CCDPOSL[1]))
    CCDCOL.append(Column(name="GPOS_L_T"      ,format="D",unit="radian",array=CCDPOSL[2]))
    CCDCOL.append(Column(name="GPOS_L_TD"     ,format="D",unit="degree",array=CCDPOSL[3]))
    CCDCOL.append(Column(name="GPOS_C_X"      ,format="D",unit="pixel",array=CCDPOSC[0]))
    CCDCOL.append(Column(name="GPOS_C_Y"      ,format="D",unit="pixel",array=CCDPOSC[1]))
    CCDCOL.append(Column(name="GPOS_C_T"      ,format="D",unit="radian",array=CCDPOSC[2]))
    CCDCOL.append(Column(name="GPOS_C_TD"     ,format="D",unit="degree",array=CCDPOSC[3]))
    CCDCOL.append(Column(name="CRVAL_RA"      ,format="D",unit="degree",array=CCDCR[2]))
    CCDCOL.append(Column(name="CRVAL_DEC"     ,format="D",unit="degree",array=CCDCR[3]))
    CCDCOL.append(Column(name="CRPIX_X"       ,format="D",unit="pixel",array=CCDCR[0]))
    CCDCOL.append(Column(name="CRPIX_Y"       ,format="D",unit="pixel",array=CCDCR[1]))
    CCDCOL.append(Column(name="OAPIX_X"       ,format="D",unit="pixel",array=CCDOA[0]))
    CCDCOL.append(Column(name="OAPIX_Y"       ,format="D",unit="pixel",array=CCDOA[1]))
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

    REFNAME =DIR_OUT+"/solvetansipresult_REFs.fits"
    REFID   =SLVTS.GET_REF_ID(S_RESULT)
    REFCID  =SLVTS.GET_REF_CID(S_RESULT)
    REFFLAG =SLVTS.GET_REF_FLAG(S_RESULT);
    REFPOS_C_RADEC =SLVTS.GET_REF_POS_CELESTIAL_RADEC(S_RESULT);
    REFPOS_C_IMWLD =SLVTS.GET_REF_POS_CELESTIAL_IMWLD(S_RESULT);
    REFPOS_C_IMPIXL=SLVTS.GET_REF_POS_CELESTIAL_IMPIX_L(S_RESULT);
    REFPOS_C_IMPIXG=SLVTS.GET_REF_POS_CELESTIAL_IMPIX_G(S_RESULT);
    REFPOS_C_CRPIXL=SLVTS.GET_REF_POS_CELESTIAL_CRPIX_L(S_RESULT);
    REFPOS_C_CRPIXG=SLVTS.GET_REF_POS_CELESTIAL_CRPIX_G(S_RESULT);
    REFPOS_C_LOCALL=SLVTS.GET_REF_POS_CELESTIAL_LOCAL_L(S_RESULT);
    REFPOS_C_LOCALG=SLVTS.GET_REF_POS_CELESTIAL_LOCAL_G(S_RESULT);
    REFPOS_C_LOCALC=SLVTS.GET_REF_POS_CELESTIAL_LOCAL_C(S_RESULT);
    REFPOS_CPSIP_CRPIXL=SLVTS.GET_REF_POS_CELESTIAL_PSIP_CRPIX_L(S_RESULT);
    REFPOS_CPSIP_CRPIXG=SLVTS.GET_REF_POS_CELESTIAL_PSIP_CRPIX_G(S_RESULT);
    REFPOS_CPSIP_LOCALL=SLVTS.GET_REF_POS_CELESTIAL_PSIP_LOCAL_L(S_RESULT);
    REFPOS_CPSIP_LOCALG=SLVTS.GET_REF_POS_CELESTIAL_PSIP_LOCAL_G(S_RESULT);
    REFPOS_CPSIP_LOCALC=SLVTS.GET_REF_POS_CELESTIAL_PSIP_LOCAL_C(S_RESULT);
    REFPOS_D_LOCALL=SLVTS.GET_REF_POS_DETECTED_LOCAL_L(S_RESULT);
    REFPOS_D_LOCALG=SLVTS.GET_REF_POS_DETECTED_LOCAL_G(S_RESULT);
    REFPOS_D_LOCALC=SLVTS.GET_REF_POS_DETECTED_LOCAL_C(S_RESULT);
    REFPOS_D_CRPIXL=SLVTS.GET_REF_POS_DETECTED_CRPIX_L(S_RESULT);
    REFPOS_D_CRPIXG=SLVTS.GET_REF_POS_DETECTED_CRPIX_G(S_RESULT);
    REFPOS_D_IMPIXL=SLVTS.GET_REF_POS_DETECTED_IMPIX_L(S_RESULT);
    REFPOS_D_IMPIXG=SLVTS.GET_REF_POS_DETECTED_IMPIX_G(S_RESULT);
    REFPOS_D_IMWLDL=SLVTS.GET_REF_POS_DETECTED_IMWLD_L(S_RESULT);
    REFPOS_D_IMWLDG=SLVTS.GET_REF_POS_DETECTED_IMWLD_G(S_RESULT);
    REFPOS_D_RADECL=SLVTS.GET_REF_POS_DETECTED_RADEC_L(S_RESULT);
    REFPOS_D_RADECG=SLVTS.GET_REF_POS_DETECTED_RADEC_G(S_RESULT);
    REFPOS_DASIP_CRPIXL=SLVTS.GET_REF_POS_DETECTED_ASIP_CRPIX_L(S_RESULT);
    REFPOS_DASIP_CRPIXG=SLVTS.GET_REF_POS_DETECTED_ASIP_CRPIX_G(S_RESULT);
    REFPOS_DASIP_IMPIXL=SLVTS.GET_REF_POS_DETECTED_ASIP_IMPIX_L(S_RESULT);
    REFPOS_DASIP_IMPIXG=SLVTS.GET_REF_POS_DETECTED_ASIP_IMPIX_G(S_RESULT);
    REFPOS_DASIP_IMWLDL=SLVTS.GET_REF_POS_DETECTED_ASIP_IMWLD_L(S_RESULT);
    REFPOS_DASIP_IMWLDG=SLVTS.GET_REF_POS_DETECTED_ASIP_IMWLD_G(S_RESULT);
    REFPOS_DASIP_RADECL=SLVTS.GET_REF_POS_DETECTED_ASIP_RADEC_L(S_RESULT);
    REFPOS_DASIP_RADECG=SLVTS.GET_REF_POS_DETECTED_ASIP_RADEC_G(S_RESULT);
    REFDISTP=SLVTS.GET_REF_CAMERADISTPSIP(S_RESULT);

    REFCOL=[]
    REFCOL.append(Column(name="ID_OBJ"                           ,format="K",array=REFID))
    REFCOL.append(Column(name="ID_CCD"                           ,format="J",array=REFCID))
    REFCOL.append(Column(name="FLAG_OBJ"                         ,format="J",array=REFFLAG))
    REFCOL.append(Column(name="POSITION_CELESTIAL_RA"            ,format="D",unit="degree",array=REFPOS_C_RADEC[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_DEC"           ,format="D",unit="degree",array=REFPOS_C_RADEC[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_IMWLD_X"       ,format="D",unit="degree",array=REFPOS_C_IMWLD[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_IMWLD_Y"       ,format="D",unit="degree",array=REFPOS_C_IMWLD[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_IMPIX_L_X"     ,format="D",unit="pixel" ,array=REFPOS_C_IMPIXL[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_IMPIX_L_Y"     ,format="D",unit="pixel" ,array=REFPOS_C_IMPIXL[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_IMPIX_G_X"     ,format="D",unit="pixel" ,array=REFPOS_C_IMPIXG[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_IMPIX_G_Y"     ,format="D",unit="pixel" ,array=REFPOS_C_IMPIXG[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_CRPIX_L_X"     ,format="D",unit="pixel" ,array=REFPOS_C_CRPIXL[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_CRPIX_L_Y"     ,format="D",unit="pixel" ,array=REFPOS_C_CRPIXL[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_CRPIX_G_X"     ,format="D",unit="pixel" ,array=REFPOS_C_CRPIXG[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_CRPIX_G_Y"     ,format="D",unit="pixel" ,array=REFPOS_C_CRPIXG[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_LOCAL_L_X"     ,format="D",unit="pixel" ,array=REFPOS_C_LOCALL[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_LOCAL_L_Y"     ,format="D",unit="pixel" ,array=REFPOS_C_LOCALL[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_LOCAL_G_X"     ,format="D",unit="pixel" ,array=REFPOS_C_LOCALG[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_LOCAL_G_Y"     ,format="D",unit="pixel" ,array=REFPOS_C_LOCALG[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_LOCAL_C_X"     ,format="D",unit="pixel" ,array=REFPOS_C_LOCALC[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_LOCAL_C_Y"     ,format="D",unit="pixel" ,array=REFPOS_C_LOCALC[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_CRPIX_L_X",format="D",unit="pixel" ,array=REFPOS_CPSIP_CRPIXL[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_CRPIX_L_Y",format="D",unit="pixel" ,array=REFPOS_CPSIP_CRPIXL[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_CRPIX_G_X",format="D",unit="pixel" ,array=REFPOS_CPSIP_CRPIXG[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_CRPIX_G_Y",format="D",unit="pixel" ,array=REFPOS_CPSIP_CRPIXG[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_LOCAL_L_X",format="D",unit="pixel" ,array=REFPOS_CPSIP_LOCALL[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_LOCAL_L_Y",format="D",unit="pixel" ,array=REFPOS_CPSIP_LOCALL[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_LOCAL_G_X",format="D",unit="pixel" ,array=REFPOS_CPSIP_LOCALG[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_LOCAL_G_Y",format="D",unit="pixel" ,array=REFPOS_CPSIP_LOCALG[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_LOCAL_C_X",format="D",unit="pixel" ,array=REFPOS_CPSIP_LOCALC[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_LOCAL_C_Y",format="D",unit="pixel" ,array=REFPOS_CPSIP_LOCALC[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_LOCAL_L_X"      ,format="D",unit="pixel" ,array=REFPOS_D_LOCALL[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_LOCAL_L_Y"      ,format="D",unit="pixel" ,array=REFPOS_D_LOCALL[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_LOCAL_G_X"      ,format="D",unit="pixel" ,array=REFPOS_D_LOCALG[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_LOCAL_G_Y"      ,format="D",unit="pixel" ,array=REFPOS_D_LOCALG[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_LOCAL_C_X"      ,format="D",unit="pixel" ,array=REFPOS_D_LOCALC[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_LOCAL_C_Y"      ,format="D",unit="pixel" ,array=REFPOS_D_LOCALC[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_CRPIX_L_X"      ,format="D",unit="pixel" ,array=REFPOS_D_CRPIXL[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_CRPIX_L_Y"      ,format="D",unit="pixel" ,array=REFPOS_D_CRPIXL[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_CRPIX_G_X"      ,format="D",unit="pixel" ,array=REFPOS_D_CRPIXG[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_CRPIX_G_Y"      ,format="D",unit="pixel" ,array=REFPOS_D_CRPIXG[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_IMPIX_L_X"      ,format="D",unit="pixel" ,array=REFPOS_D_IMPIXL[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_IMPIX_L_Y"      ,format="D",unit="pixel" ,array=REFPOS_D_IMPIXL[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_IMPIX_G_X"      ,format="D",unit="pixel" ,array=REFPOS_D_IMPIXG[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_IMPIX_G_Y"      ,format="D",unit="pixel" ,array=REFPOS_D_IMPIXG[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_IMWLD_L_X"      ,format="D",unit="degree",array=REFPOS_D_IMWLDL[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_IMWLD_L_Y"      ,format="D",unit="degree",array=REFPOS_D_IMWLDL[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_IMWLD_G_X"      ,format="D",unit="degree",array=REFPOS_D_IMWLDG[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_IMWLD_G_Y"      ,format="D",unit="degree",array=REFPOS_D_IMWLDG[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_RA_L"           ,format="D",unit="degree",array=REFPOS_D_RADECL[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_DEC_L"          ,format="D",unit="degree",array=REFPOS_D_RADECL[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_RA_G"           ,format="D",unit="degree",array=REFPOS_D_RADECG[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_DEC_G"          ,format="D",unit="degree",array=REFPOS_D_RADECG[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_CRPIX_L_X" ,format="D",unit="pixel" ,array=REFPOS_DASIP_CRPIXL[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_CRPIX_L_Y" ,format="D",unit="pixel" ,array=REFPOS_DASIP_CRPIXL[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_CRPIX_G_X" ,format="D",unit="pixel" ,array=REFPOS_DASIP_CRPIXG[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_CRPIX_G_Y" ,format="D",unit="pixel" ,array=REFPOS_DASIP_CRPIXG[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_IMPIX_L_X" ,format="D",unit="pixel" ,array=REFPOS_DASIP_IMPIXL[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_IMPIX_L_Y" ,format="D",unit="pixel" ,array=REFPOS_DASIP_IMPIXL[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_IMPIX_G_X" ,format="D",unit="pixel" ,array=REFPOS_DASIP_IMPIXG[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_IMPIX_G_Y" ,format="D",unit="pixel" ,array=REFPOS_DASIP_IMPIXG[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_IMWLD_L_X" ,format="D",unit="degree",array=REFPOS_DASIP_IMWLDL[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_IMWLD_L_Y" ,format="D",unit="degree",array=REFPOS_DASIP_IMWLDL[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_IMWLD_G_X" ,format="D",unit="degree",array=REFPOS_DASIP_IMWLDG[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_IMWLD_G_Y" ,format="D",unit="degree",array=REFPOS_DASIP_IMWLDG[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_RA_L"      ,format="D",unit="degree",array=REFPOS_DASIP_RADECL[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_DEC_L"     ,format="D",unit="degree",array=REFPOS_DASIP_RADECL[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_RA_G"      ,format="D",unit="degree",array=REFPOS_DASIP_RADECG[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_ASIP_DEC_G"     ,format="D",unit="degree",array=REFPOS_DASIP_RADECG[1]))
    REFCOL.append(Column(name="CAMERA_DIST_CONVERGENCE"          ,format="D",array=REFDISTP[0]))
    REFCOL.append(Column(name="CAMERA_DIST_ROTATION"             ,format="D",array=REFDISTP[1]))
    REFCOL.append(Column(name="CAMERA_DIST_SHEAR1"               ,format="D",array=REFDISTP[2]))
    REFCOL.append(Column(name="CAMERA_DIST_SHEAR2"               ,format="D",array=REFDISTP[3]))
    REFCOL.append(Column(name="CAMERA_DIST_MAGNIFICATION"        ,format="D",array=REFDISTP[4]))
    REFCOL.append(Column(name="CAMERA_DIST_JACOBIAN"             ,format="D",array=REFDISTP[5]))

    REFhdu = pyfits.new_table(REFCOL)
    REFhdu.writeto(REFNAME,clobber=True)

#    print REFNAME
