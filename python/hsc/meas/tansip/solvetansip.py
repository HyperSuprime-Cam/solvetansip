import os
import os.path

import numpy

import lsst.afw.geom as afwGeom
import lsst.afw.coord as afwCoord
import lsst.pex.policy as pexPolicy
import lsst.meas.astrom.astrom as measAst

import hsc.meas.tansip as tansip
import hsc.meas.tansip.doTansip as doTansip

from lsst.pex.config import Config
from lsst.pipe.base import ArgumentParser, TaskRunner, CmdLineTask, Struct

class SolveTansipTaskRunner(TaskRunner):
    @staticmethod
    def getTargetList(parsedCmd, **kwargs):
        return [dict(dataRefList=parsedCmd.id.refList, butler=parsedCmd.butler,
                     camera=parsedCmd.butler.mapper.getCameraName(), **kwargs)]

    def __call__(self, args):
        task = self.TaskClass(config=self.config, log=self.log)
        task.run(**args)


class SolveTansipTask(CmdLineTask):
    # XXX Implement proper configuration with pex_config
    ConfigClass = Config
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
        policy.set('NCCD', len(matchLists))

        self.log.info("Processing with solvetansip")
        wcs = doTansip.doTansip(matchLists, policy=policy, camera=cameraGeom)
        wcsList = doTansip.getwcsList(wcs)
        return wcsList

    def convert(self, matchList):
        if matchList is None: # match for this CCD is None
            #return [ None ]
            return None
        xErrKey = matchList[0].second.getTable().getCentroidErrKey()[0,0]
        yErrKey = matchList[0].second.getTable().getCentroidErrKey()[1,1]
        return [tansip.SourceMatch(m.second.getId(), # id for second is ok?
                                   afwCoord.IcrsCoord(m.first.getRa(), m.first.getDec()),
                                   afwGeom.Point2D(m.second.getX(), m.second.getY()),
                                   afwGeom.Point2D(m.second.get(xErrKey), m.second.get(yErrKey)),
                                   m.second.getPsfFlux())
                for m in matchList if (m.first and m.second)] # both ref and src to have valid values

    def read(self, butler, dataRefList):
        self.log.info("Reading match lists")

        matchLists = []
        if True: # FH: this routine is much faster than the below
            astrom = measAst.Astrometry(measAst.MeasAstromConfig())
            for dataRef in dataRefList:
                try:
                    icSrces = dataRef.get('icSrc')
                    packedMatches = dataRef.get('icMatch')
                    ml = astrom.joinMatchListWithCatalog(packedMatches, icSrces)
                except Exception, e:
                    self.log.warn("Unable to read matches for %s. None is inserted: %s" %
                                  (dataRef.dataId, str(e)))
                    ml = None
                matchLists.append(ml)
        else: # FH: this routine is very slow
            for dataRef in dataRefList:
                try:
                    ml = measAst.readMatches(butler, dataRef.dataId)
                except Exception as e:
                    self.log.warn("Unable to read matches for %s: %s" % (dataRef.dataId, e))
                    ml = None
                matchLists.append(ml)

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
        matchLists = [self.convert(ml) for ml in matchLists]
        return self.solve(camera, butler.mapper.camera, matchLists)


class SolveTansipQaTask(SolveTansipTask):
    # XXX Implement proper configuration with pex_config
    ConfigClass = Config
    _DefaultName = "solvetansip"

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
        policy.set('NCCD', len(matchLists)) # num of detectors should work since None is padded for CCDs in failure

        self.log.info("Processing with solvetansip")
        resSolveTansip, metaTansip = doTansip.doTansipQa(matchLists, policy=policy, camera=cameraGeom)
        return Struct(
            resSolveTansip = resSolveTansip,
            metaTansip = metaTansip,
            )

    def run(self, camera, butler, dataRefList, policy=None):
        matchLists = self.read(butler, dataRefList)
        matchListsForSolveTansip = [self.convert(ml) for ml in matchLists]

        dataTansip = self.solve(camera, butler.mapper.camera, matchListsForSolveTansip, policy=policy)

        dataTansip.wcsList = list(doTansip.getwcsList(dataTansip.resSolveTansip))
        dataTansip.matchLists = matchLists
        dataTansip.matchListsForSolveTansip = matchListsForSolveTansip

        return dataTansip
