import os
import os.path

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
    doWriteNewFits = pexConfig.Field(
        dtype=bool, default=False,
        doc="Write new Fits file (revexp) with re-determined Wcs?"
        )

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

    def solve(self, camera, cameraGeom, matchLists):
        policyPath = os.path.join(os.environ["SOLVETANSIP_DIR"], "policy", camera + ".paf")
        self.log.info("Solvetansip policy override: %s" % policyPath)
        policy = pexPolicy.Policy.createPolicy(policyPath)
        defaults = pexPolicy.Policy.createPolicy(os.path.join(os.environ["SOLVETANSIP_DIR"],
                                                              "policy", "WCS_MAKEAPROP.paf"))
        policy.mergeDefaults(defaults)

        self.log.info("Processing with solvetansip")
        wcs = doTansip.doTansip(matchLists, policy=policy, camera=cameraGeom)
        wcsList = doTansip.getwcsList(wcs)
        return wcsList

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
        return self.solve(camera, butler.mapper.camera, matchLists)


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

    def solve(self, camera, cameraGeom, matchLists, policy=None):
        if policy is not None:
            policyPath = policy
        else:
            policyPath = os.path.join(os.environ["SOLVETANSIP_DIR"], "policy", camera + ".paf")
        self.log.info("Solvetansip policy override: %s" % policyPath)
        policy = pexPolicy.Policy.createPolicy(policyPath)
        defaults = pexPolicy.Policy.createPolicy(os.path.join(os.environ["SOLVETANSIP_DIR"],
                                                              "policy", "WCS_MAKEAPROP.paf"))
        policy.mergeDefaults(defaults)

        self.log.info("Processing with solvetansip")
        resSolveTansip, metaTansip = doTansip.doTansipQa(matchLists, policy=policy, camera=cameraGeom)
        return Struct(
            resSolveTansip = resSolveTansip,
            metaTansip = metaTansip,
            )

    def run(self, camera, butler, dataRefList, policy=None):
        matchLists = self.read(butler, dataRefList)
        dataTansip = self.solve(camera, butler.mapper.camera, matchLists, policy=policy)

        dataTansip.wcsList = list(doTansip.getwcsList(dataTansip.resSolveTansip))
        dataTansip.matchLists = matchLists

        if self.config.doWriteNewFits:
            visit = dataRefList[0].dataId['visit']
            self.writeResultantFitsFiles(butler, visit, dataTansip.wcsList)

        return dataTansip
