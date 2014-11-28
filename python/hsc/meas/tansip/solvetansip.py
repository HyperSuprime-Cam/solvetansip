import os

import numpy

import lsst.afw.geom as afwGeom
import lsst.afw.coord as afwCoord
import lsst.pex.policy as pexPolicy
import lsst.meas.astrom.astrom as measAst

import hsc.meas.tansip as tansip
import hsc.meas.tansip.doTansip as doTansip
import hsc.pipe.base.camera as hscCamera

import lsst.pex.config as pexConfig
from lsst.pipe.base import ArgumentParser, TaskRunner, CmdLineTask, Struct

class SolveTansipTaskRunner(TaskRunner):
    @staticmethod
    def getTargetList(parsedCmd, **kwargs):
        return [dict(dataRefList=parsedCmd.id.refList, butler=parsedCmd.butler,
                     camera=parsedCmd.butler.mapper.getCameraName(), **kwargs)]

    def __call__(self, args):
        task = self.TaskClass(config=self.config, log=self.log)
        task.run(**args)


class SolveTansipConfig(pexConfig.Config):
    modeCR = pexConfig.Field(
        dtype=str, default="PIX",
        doc='"AUTO"|"PIX", When "Auto", CRPIX is auto-set. When "PIX" CRPIX is fixed.'
        )
    doComputeCCDPos = pexConfig.Field(
        dtype=bool, default=True,
        doc="Compute CCDs' positions?"
        )
    precPos = pexConfig.Field(
        dtype=float, default=0.02,
        doc="Precision, in pixels, of computed CCDs' positions."
        )
    degree = pexConfig.Field(
        dtype=int, default=9,
        doc="Degree of polynomials to use."
        )
    doReject = pexConfig.Field(
        dtype=bool, default=True,
        doc="Reject bad references?"
        )
    sigmaClip = pexConfig.Field(
        dtype=float, default=2.5,
        doc="Reference are rejected when |dx| > SIGMA_CLIP * sigma."
        )
    verbose = pexConfig.Field(
        dtype=int, default=2,
        doc="0|1|2, Verbosity."
        )

    doWriteNewFits = pexConfig.Field(
        dtype=bool, default=False,
        doc="Write new Fits file (revexp) with re-determined Wcs?"
        )

    # This field may have to be moved to mappers
    geomPath = pexConfig.Field(
        dtype=str, default="%(pointing)05d/%(filter)s/output/CAMERAGEOM-%(visit)07d.paf",
        doc="If not empty, write camera geometry in the specified file."
        )

    dumpDir = pexConfig.Field(
        dtype=str, default="",
        doc="If not empty, dump internal states into the specified directory"
        )

    def getPolicy(self):
        policy = pexPolicy.Policy()
        policy.set("MODE_CR"      , self.modeCR         )
        policy.set("MODE_CCDPOS"  , self.doComputeCCDPos)
        policy.set("PRECISION_POS", self.precPos        )
        policy.set("ORDER_ASIP"   , self.degree         )
        policy.set("ORDER_PSIP"   , self.degree         )
        policy.set("MODE_REJ"     , self.doReject       )
        policy.set("CLIPSIGMA"    , self.sigmaClip      )
        #policy.set("CRPIX1"       , self.               )
        #policy.set("CRPIX2"       , self.               )
        #policy.set("CRVAL1"       , self.               )
        #policy.set("CRVAL2"       , self.               )
        policy.set("FLAG_STD"     , self.verbose        )

        return policy

    def getDoTansipOptionalArgs(self, dataRef):
        def expandPath(path):
            return os.path.join(dataRef.getButler().mapper.root, path % dataRef.dataId)

        args = {}
        if self.dumpDir:
            args["dumpDir"] = expandPath(self.dumpDir)
        if self.doComputeCCDPos and self.geomPath:
            args["geomPath"] = expandPath(self.geomPath)
            args["geomInput"] = dataRef.getButler().mapper.cameraPolicyLocation

        return args


class SolveTansipTask(CmdLineTask):
    # XXX Implement proper configuration with pex_config
    ConfigClass = SolveTansipConfig
    _DefaultName = "solvetansip"
    RunnerClass = SolveTansipTaskRunner

    @classmethod
    def _makeArgumentParser(cls):
        parser = ArgumentParser(name=cls._DefaultName)
        parser.add_id_argument(name="--id", datasetType="raw", level="Ccd",
                               help="data ID, e.g. --id visit=12345")
        return parser

    def solve(self, camera, butler, dataRef, matchLists):
        """
        Determine TANSIP Wcs from matchLists.

        @param camera: (str) Camera's name. Used to load a default PAF
            (= $SOLVETANSIP_DIR/policy/%(camera)s.paf).
            Note the value in the default PAF file is overridden by
            command line arguments.
        @param butler: Butler.
        @param dataRef: ButlerDataRef that specifies an exposure.
            This is used to determine output file paths.
        @param matchLists:
            A list of lists of lsst.afw.table.ReferenceMatch.
            For a ccdId, matchLists[ccdId] is a list of
            lsst.afw.table.ReferenceMatch in the CCD ccdId.
            matchLists[ccdId] can be either None or [] if no match in it.

        @return TanWcsList
        """
        policyPath = os.path.join(os.environ["SOLVETANSIP_DIR"], "policy", camera + ".paf")
        self.log.info("Solvetansip policy override: %s" % policyPath)
        override = pexPolicy.Policy.createPolicy(policyPath)
        defaults = pexPolicy.Policy.createPolicy(os.path.join(os.environ["SOLVETANSIP_DIR"],
                                                              "policy", "WCS_MAKEAPROP.paf"))
        policy = self.config.getPolicy()
        policy.mergeDefaults(override)
        policy.mergeDefaults(defaults)

        self.log.info("Processing with solvetansip")
        return doTansip.doTansip(
            matchLists, policy, butler.mapper.camera,
            **self.config.getDoTansipOptionalArgs(dataRef)
        )

    def read(self, butler, dataRefList, nCcd = None):
        """
        reading matchlists from files.
        resultant matchlists are sorted order by ccd = 0,1,2,..., nCcd-1, where nCcd is given by user or by camera name.
        None is inserted for ccds without matchlist available.
        """
        self.log.info("Reading match lists")
        self.log.info("match lists are sorted to be incremental and ascending by ccd")

        if nCcd:
            self.log.info("number of matches to read is given by user: %d" % nCcd)
        else:
            nCcd = hscCamera.getNumCcds(butler.mapper.getCameraName())
            self.log.info("number of matches to read is set by camera name to: %d" % nCcd)

        matchLists = [ None for i in range(nCcd) ]

        if True: # FH: this routine is much faster than the below
            astrom = measAst.Astrometry(measAst.MeasAstromConfig())
            for dataRef in dataRefList:
                ccd = dataRef.dataId['ccd']
                try:
                    icSrces = dataRef.get('icSrc')
                    packedMatches = dataRef.get('icMatch')
                    ml = astrom.joinMatchListWithCatalog(packedMatches, icSrces)
                    matchLists[ccd] = ml
                except Exception, e:
                    self.log.warn("Unable to read matches for %s. None is inserted: %s" %
                                  (dataRef.dataId, str(e)))
        else: # FH: this routine is very slow
            for dataRef in dataRefList:
                ccd = dataRef.dataId['ccd']
                try:
                    ml = measAst.readMatches(butler, dataRef.dataId)
                    matchLists[ccd] = ml
                except Exception as e:
                    self.log.warn("Unable to read matches for %s: %s" % (dataRef.dataId, e))

        if False:
            ra = []
            dec = []
            for matches in matchLists:
                for m in matches:
                    ra.append(m.first.getRa())
                    dec.append(m.first.getDec())

            ra = numpy.array(ra)
            dec = numpy.array(dec)
            print "Magnitude range, sources:", mag2.min(), mag2.max()
            print "Sky range, ra and dec:", ra.min(), ra.max(), dec.min(), dec.max()
        return matchLists

    def run(self, camera, butler, dataRefList):
        matchLists = self.read(butler, dataRefList)
        return self.solve(camera, butler, dataRefList[0], matchLists)


class SolveTansipQaTask(SolveTansipTask):
    # XXX Implement proper configuration with pex_config
    ConfigClass = SolveTansipConfig
    _DefaultName = "solvetansip"

    def writeResultantFitsFiles(self, butler, visit, wcsList):
        """ writing fits with new wcs. assumes wcsList is aligned like ccd=0,1,2,..nCcd-1 """
        dataId = {'visit': visit}
        for ccdId, wcs in enumerate(wcsList):
            dataId['ccd'] = ccdId
            try:
                exposure = butler.get('calexp', dataId)
                exposure.setWcs(wcs)
                self.log.info("writing a new fits file with new wcs for %s" % dataId)
                butler.put(exposure, 'revexp', dataId)
            except Exception, e:
                self.log.warn("failed to create new fits: %s" % (e))

    def solve(self, camera, butler, dataRef, matchLists, policy=None):
        """
        Determine TANSIP Wcs from matchLists.

        @param camera: (str) Camera's name. Used to load a default PAF
            (= $SOLVETANSIP_DIR/policy/%(camera)s.paf).
            Note the value in the default PAF file is overridden by
            command line arguments.
        @param butler: Butler. Its mapper must be CameraMapper
        @param dataRef: ButlerDataRef that specifies an exposure.
            This is used to determine output file paths.
        @param matchLists:
            A list of lists of lsst.afw.table.ReferenceMatch.
            For a ccdId, matchLists[ccdId] is a list of
            lsst.afw.table.ReferenceMatch in the CCD ccdId.
            matchLists[ccdId] can be either None or [] if no match in it.

        @return Struct(
            resSolveTansip: TanWcsList
            metaTansip: dafBase.PropertySet
            )
        """

        if policy is not None:
            policyPath = policy
        else:
            policyPath = os.path.join(os.environ["SOLVETANSIP_DIR"], "policy", camera + ".paf")
        self.log.info("Solvetansip policy override: %s" % policyPath)
        override = pexPolicy.Policy.createPolicy(policyPath)
        defaults = pexPolicy.Policy.createPolicy(os.path.join(os.environ["SOLVETANSIP_DIR"],
                                                              "policy", "WCS_MAKEAPROP.paf"))
        policy = self.config.getPolicy()
        policy.mergeDefaults(override)
        policy.mergeDefaults(defaults)

        self.log.info("Processing with solvetansip")
        resSolveTansip, metaTansip = doTansip.doTansip(
            matchLists, policy, butler.mapper.camera,
            needMetadata = True,
            **self.config.getDoTansipOptionalArgs(dataRef)
        )
        return Struct(
            resSolveTansip = resSolveTansip,
            metaTansip = metaTansip
            )

    def run(self, camera, butler, dataRefList, policy=None):
        matchLists = self.read(butler, dataRefList)
        dataTansip = self.solve(camera, butler, dataRefList[0], matchLists, policy=policy)

        dataTansip.wcsList = list(dataTansip.resSolveTansip)
        dataTansip.matchLists = matchLists

        if self.config.doWriteNewFits:
            visit = dataRefList[0].dataId['visit']
            self.writeResultantFitsFiles(butler, visit, dataTansip.wcsList)

        return dataTansip
