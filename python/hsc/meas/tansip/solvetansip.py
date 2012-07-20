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
from lsst.pipe.base import Task


class SolveTansipTask(Task):
    ConfigClass = Config

    def run(self, camera, butler, dataRefList):
        self.log.info("Reading match lists")
        
        matchLists = [measAst.readMatches(butler, dataRef.dataId) for dataRef in dataRefList]

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

        policyPath = os.path.join(os.environ["SOLVETANSIP_DIR"], "policy", camera + ".paf")
        self.log.info("Solvetansip policy: %s" % policyPath)
        policy = pexPolicy.Policy.createPolicy(policyPath)
        policy.set('NCCD', len(matchLists))

        self.log.info("Generating inputs")
        inputList = []
        for ml in matchLists:
            xErrKey = ml[0].second.getTable().getCentroidErrKey()[0,0]
            yErrKey = ml[0].second.getTable().getCentroidErrKey()[1,1]
            inputList.append([tansip.SourceMatch(m.second.getId(),
                                                 afwCoord.IcrsCoord(m.first.getRa(), m.first.getDec()),
                                                 afwGeom.Point2D(m.second.getX(), m.second.getY()),
                                                 afwGeom.Point2D(m.second.get(xErrKey), m.second.get(yErrKey)),
                                                 m.second.getPsfFlux())
                              for m in ml])

        self.log.info("Processing with solvetansip")
        wcs = doTansip.doTansip(inputList, policy=policy, camera=butler.mapper.camera)
        self.log.info("Solvetansip results:")
        wcsList = doTansip.getwcsList(wcs)
        print wcsList
