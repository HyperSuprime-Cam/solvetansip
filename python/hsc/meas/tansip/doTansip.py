import sys, re, os, math
import pyfits
from pyfits import Column
import hsc.meas.tansip.tansipLib      as tansipLib
import hsc.meas.tansip.utils          as tansipUtils
import lsst.afw.cameraGeom.utils      as cameraGeomUtils
import lsst.afw.cameraGeom            as cameraGeom
import lsst.daf.base                  as dafBase


def doTansip(matchLists, policy, camera, **args):
    """
    Determine TANSIP Wcs from matchLists.

    @param matchLists:
        A list of lists of lsst.afw.table.ReferenceMatch.
        For a ccdId, matchLists[ccdId] is a list of
        lsst.afw.table.ReferenceMatch in the CCD ccdId.
        matchLists[ccdId] can be either None or [] if no match in it.
    @param policy:
        An instance of pexPolicy.Policy, expressing analysis parameters.
    @param camera:
        An instance of afw.cameraGeom.DetectorMosaic.

    @param **args: as follows:
    @param needMetadata: (bool) If true, this function additionally returns a
        dafBase.PropertySet() that expresses the state of solvetansip at the
        end of its process.
    @param geomPath: (str) If present, this function outputs camera geometry
        in the specified path, in the .paf format. NEVER set this argument
        the path of existing camera geometry files. The output .paf will only
        contain a "Raft" field. Other fields would be lost if you let this
        function overwrite existing camera geometry files.
    @param dumpDir: (str) If present, this function dumps summary and
        internal states as FITS bin tables into the specified directory.

    @return TanWcsList
        (If needMetadata = true, then (TanWcsList, dafBase.PropertySet)
    """
    print '--- doTansip : start ---'

    APRM = tansipLib.toAnaParam(policy)
    CCD  = tansipLib.getCCDPositionList(camera, len(matchLists))
    REF  = tansipLib.toReferenceMatchList(matchLists)

    print '--- doTansip : SOLVE TANSIP ---'
    SLVTSRESULT = tansipLib.SOLVETANSIP(APRM, CCD, REF)

    metaTANSIP  = tansipLib.GET_METADATA(SLVTSRESULT)
    tansipLib.SHOW_METADATA(SLVTSRESULT, metaTANSIP)

    if "geomPath" in args:
        tansipUtils.writeCCDPositionAsPAF(
            policy.get("INSTR"),
            tansipLib.getCCDPositionList(SLVTSRESULT),
            args["geomPath"]
        )

    if "dumpDir" in args:
        DIR_OUT = args["dumpDir"]
        print "OUTPUT SUMMARY FITS in "+DIR_OUT
        _outputSummary(SLVTSRESULT,DIR_OUT)
        print "OUTPUT FITS BINARY TABLE in "+DIR_OUT
        _outputBinaryTable(SLVTSRESULT,DIR_OUT)

    TANWCS = tansipLib.GET_TANWCS(SLVTSRESULT)

    print '--- doTansip : end   ---'

    if "needMetadata" in args and args["needMetadata"]:
        return TANWCS, metaTANSIP
    else:
        return TANWCS


#-----------------------------------------------------------------
#Output bianry table : slvtsState
#-----------------------------------------------------------------
def _outputSummary(slvtsState,DIR_OUT):
    if os.path.exists(DIR_OUT) == False:
        os.makedirs(DIR_OUT)

    SUMNAME=DIR_OUT+"/solvetansipresult_SUMMARY.fits"

    MODE_CR   =tansipLib.GET_SUM_MODECR(slvtsState)
    MODE_REJ  =tansipLib.GET_SUM_MODEREJ(slvtsState)
    MODE_CCD  =tansipLib.GET_SUM_MODECCD(slvtsState)
    NUM_CCD   =tansipLib.GET_SUM_NUMCCD(slvtsState)
    NUM_REF   =tansipLib.GET_SUM_NUMREF(slvtsState)
    NUM_FIT   =tansipLib.GET_SUM_NUMFIT(slvtsState)
    CRPIX     =tansipLib.GET_SUM_CRPIX(slvtsState)
    CRVAL     =tansipLib.GET_SUM_CRVAL(slvtsState)
    OAPIX     =tansipLib.GET_SUM_OAPIX(slvtsState)
    CD        =tansipLib.GET_SUM_CD(slvtsState)
    ANGLE     =tansipLib.GET_SUM_ANGLE(slvtsState)
    ST_CRPIX_G=tansipLib.GET_SUM_MAX_CRPIX_G(slvtsState)
    CD_COR    =tansipLib.GET_SUM_CD_CORANGLE(slvtsState)
    RMS_SIP   =tansipLib.GET_SUM_RMSASIP(slvtsState)
    RMS_PSIP  =tansipLib.GET_SUM_RMSPSIP(slvtsState)

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
    SUMhdr.update("MAX_X"  ,ST_CRPIX_G[0],"MAXIMUM X position from CRPIX")
    SUMhdr.update("MAX_Y"  ,ST_CRPIX_G[1],"MAXIMUM Y position from CRPIX")
    SUMhdr.update("MIN_X"  ,ST_CRPIX_G[2],"MINIMUM X position from CRPIX")
    SUMhdr.update("MIN_Y"  ,ST_CRPIX_G[3],"MINIMUM Y position from CRPIX")
    SUMhdr.update("AVE_X"  ,ST_CRPIX_G[4],"AVERAGE X position from CRPIX")
    SUMhdr.update("AVE_Y"  ,ST_CRPIX_G[5],"AVERAGE Y position from CRPIX")
    SUMhdr.update("RMSSIPX",RMS_SIP[0],"RMS X of  SIP fitting Error")
    SUMhdr.update("RMSSIPY",RMS_SIP[1],"RMS Y of  SIP fitting Error")
    SUMhdr.update("RMSPSIPX",RMS_PSIP[0],"RMS X of PSIP fitting Error")
    SUMhdr.update("RMSPSIPY",RMS_PSIP[1],"RMS Y of PSIP fitting Error")
    SUMhdu.writeto(SUMNAME,clobber=True)


def _outputBinaryTable(slvtsState, DIR_OUT):
    if os.path.exists(DIR_OUT) == False:
        os.makedirs(DIR_OUT)

#CCD-----
    CCDNAME=DIR_OUT+"/solvetansipresult_CCDs.fits"
    CCDRNUM=tansipLib.GET_CCD_NUMREF(slvtsState)
    CCDFNUM=tansipLib.GET_CCD_NUMFIT(slvtsState)
    CCDPOSL=tansipLib.GET_CCD_GPOS_L(slvtsState)
    CCDPOSC=tansipLib.GET_CCD_GPOS_C(slvtsState)
    CCDCR  =tansipLib.GET_CCD_CR(slvtsState)
    CCDOA  =tansipLib.GET_CCD_OA(slvtsState)
    CCDCD  =tansipLib.GET_CCD_CD(slvtsState)
    CCDSORD=tansipLib.GET_CCD_ORDERSIP(slvtsState)
    CCDPORD=tansipLib.GET_CCD_ORDERPSIP(slvtsState)
    CCDSERR=tansipLib.GET_CCD_ERRSIP(slvtsState)
    CCDPERR=tansipLib.GET_CCD_ERRPSIP(slvtsState)
    CCDSCOA=tansipLib.GET_CCD_COEFSIPA(slvtsState)
    CCDSCOB=tansipLib.GET_CCD_COEFSIPB(slvtsState)
    CCDPCOA=tansipLib.GET_CCD_COEFPSIPA(slvtsState)
    CCDPCOB=tansipLib.GET_CCD_COEFPSIPB(slvtsState)

    CCDCOL=[]
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
    REFCID  =tansipLib.GET_REF_CID(slvtsState)
    REFFLAG =tansipLib.GET_REF_FLAG(slvtsState);
    REFPOS_C_RADEC =tansipLib.GET_REF_POS_CELESTIAL_RADEC(slvtsState);
    REFPOS_C_IMWLD =tansipLib.GET_REF_POS_CELESTIAL_IMWLD(slvtsState);
    REFPOS_C_IMPIXL=tansipLib.GET_REF_POS_CELESTIAL_IMPIX_L(slvtsState);
    REFPOS_C_IMPIXG=tansipLib.GET_REF_POS_CELESTIAL_IMPIX_G(slvtsState);
    REFPOS_C_CRPIXL=tansipLib.GET_REF_POS_CELESTIAL_CRPIX_L(slvtsState);
    REFPOS_C_CRPIXG=tansipLib.GET_REF_POS_CELESTIAL_CRPIX_G(slvtsState);
    REFPOS_C_LOCALL=tansipLib.GET_REF_POS_CELESTIAL_LOCAL_L(slvtsState);
    REFPOS_C_LOCALG=tansipLib.GET_REF_POS_CELESTIAL_LOCAL_G(slvtsState);
    REFPOS_CPSIP_CRPIXL=tansipLib.GET_REF_POS_CELESTIAL_PSIP_CRPIX_L(slvtsState);
    REFPOS_CPSIP_CRPIXG=tansipLib.GET_REF_POS_CELESTIAL_PSIP_CRPIX_G(slvtsState);
    REFPOS_CPSIP_LOCALL=tansipLib.GET_REF_POS_CELESTIAL_PSIP_LOCAL_L(slvtsState);
    REFPOS_CPSIP_LOCALG=tansipLib.GET_REF_POS_CELESTIAL_PSIP_LOCAL_G(slvtsState);
    REFPOS_D_LOCALL=tansipLib.GET_REF_POS_DETECTED_LOCAL_L(slvtsState);
    REFPOS_D_LOCALG=tansipLib.GET_REF_POS_DETECTED_LOCAL_G(slvtsState);
    REFPOS_D_CRPIXL=tansipLib.GET_REF_POS_DETECTED_CRPIX_L(slvtsState);
    REFPOS_D_CRPIXG=tansipLib.GET_REF_POS_DETECTED_CRPIX_G(slvtsState);
    REFPOS_D_IMPIXL=tansipLib.GET_REF_POS_DETECTED_IMPIX_L(slvtsState);
    REFPOS_D_IMPIXG=tansipLib.GET_REF_POS_DETECTED_IMPIX_G(slvtsState);
    REFPOS_D_IMWLDL=tansipLib.GET_REF_POS_DETECTED_IMWLD_L(slvtsState);
    REFPOS_D_IMWLDG=tansipLib.GET_REF_POS_DETECTED_IMWLD_G(slvtsState);
    REFPOS_D_RADECL=tansipLib.GET_REF_POS_DETECTED_RADEC_L(slvtsState);
    REFPOS_D_RADECG=tansipLib.GET_REF_POS_DETECTED_RADEC_G(slvtsState);
    REFPOS_DASIP_CRPIXL=tansipLib.GET_REF_POS_DETECTED_ASIP_CRPIX_L(slvtsState);
    REFPOS_DASIP_CRPIXG=tansipLib.GET_REF_POS_DETECTED_ASIP_CRPIX_G(slvtsState);
    REFPOS_DASIP_IMPIXL=tansipLib.GET_REF_POS_DETECTED_ASIP_IMPIX_L(slvtsState);
    REFPOS_DASIP_IMPIXG=tansipLib.GET_REF_POS_DETECTED_ASIP_IMPIX_G(slvtsState);
    REFPOS_DASIP_IMWLDL=tansipLib.GET_REF_POS_DETECTED_ASIP_IMWLD_L(slvtsState);
    REFPOS_DASIP_IMWLDG=tansipLib.GET_REF_POS_DETECTED_ASIP_IMWLD_G(slvtsState);
    REFPOS_DASIP_RADECL=tansipLib.GET_REF_POS_DETECTED_ASIP_RADEC_L(slvtsState);
    REFPOS_DASIP_RADECG=tansipLib.GET_REF_POS_DETECTED_ASIP_RADEC_G(slvtsState);
    REFDIFF=tansipLib.GET_REF_DIFF(slvtsState);
    REFJACO=tansipLib.GET_REF_CAMERAJACOPSIP(slvtsState);

    REFCOL=[]
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
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_CRPIX_L_X",format="D",unit="pixel" ,array=REFPOS_CPSIP_CRPIXL[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_CRPIX_L_Y",format="D",unit="pixel" ,array=REFPOS_CPSIP_CRPIXL[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_CRPIX_G_X",format="D",unit="pixel" ,array=REFPOS_CPSIP_CRPIXG[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_CRPIX_G_Y",format="D",unit="pixel" ,array=REFPOS_CPSIP_CRPIXG[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_LOCAL_L_X",format="D",unit="pixel" ,array=REFPOS_CPSIP_LOCALL[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_LOCAL_L_Y",format="D",unit="pixel" ,array=REFPOS_CPSIP_LOCALL[1]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_LOCAL_G_X",format="D",unit="pixel" ,array=REFPOS_CPSIP_LOCALG[0]))
    REFCOL.append(Column(name="POSITION_CELESTIAL_PSIP_LOCAL_G_Y",format="D",unit="pixel" ,array=REFPOS_CPSIP_LOCALG[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_LOCAL_L_X"      ,format="D",unit="pixel" ,array=REFPOS_D_LOCALL[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_LOCAL_L_Y"      ,format="D",unit="pixel" ,array=REFPOS_D_LOCALL[1]))
    REFCOL.append(Column(name="POSITION_DETECTED_LOCAL_G_X"      ,format="D",unit="pixel" ,array=REFPOS_D_LOCALG[0]))
    REFCOL.append(Column(name="POSITION_DETECTED_LOCAL_G_Y"      ,format="D",unit="pixel" ,array=REFPOS_D_LOCALG[1]))
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
    REFCOL.append(Column(name="DIFF_ASIP_X"                      ,format="D",array=REFDIFF[0]))
    REFCOL.append(Column(name="DIFF_ASIP_Y"                      ,format="D",array=REFDIFF[1]))
    REFCOL.append(Column(name="DIFF_PSIP_X"                      ,format="D",array=REFDIFF[2]))
    REFCOL.append(Column(name="DIFF_PSIP_Y"                      ,format="D",array=REFDIFF[3]))
    REFCOL.append(Column(name="CAMERA_DIST_JACOBIAN"             ,format="D",array=REFJACO))

    REFhdu = pyfits.new_table(REFCOL)
    REFhdu.writeto(REFNAME,clobber=True)

#    print REFNAME
