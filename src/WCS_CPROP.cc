//------------------------------------------------------------
//WCS_CPROP.cc
//
//Last modification : 2010/08/03
//------------------------------------------------------------

#include "hsc/meas/tansip/WCS_APROP.h"
#include "hsc/meas/tansip/WCS_CPROP.h"
#include "lsst/afw/cameraGeom/Camera.h"
#include "lsst/afw/detection/Source.h"
#include "lsst/afw/detection/SourceMatch.h"
using namespace std;
namespace afwdetect = lsst::afw::detection;
namespace afwGeom = lsst::afw::geom; 
namespace camGeom = lsst::afw::cameraGeom;
void    F_MAKECPROP(lsst::afw::cameraGeom::Camera::Ptr &camera,vector< vector<afwdetect::SourceMatch> > const &matchlist,CL_APROP *APROP,CL_CPROP *CPROP){
    int ID;

    APROP->refNUM=0;
    for(camGeom::Camera::const_iterator iter(camera->begin()); iter != camera->end(); ++iter) { 
        camGeom::DetectorMosaic::Ptr detMosaic = boost::shared_dynamic_cast<camGeom::DetectorMosaic>(*iter);

        for(ID=0;ID<APROP->CCDNUM;ID++){
            camGeom::Id detId = camGeom::Id(ID);//serial
            camGeom::Detector::Ptr det = detMosaic->findDetector(detId);
            afwGeom::Point2D offsetXY = det->getCenter();
//            double ccdTiltYaw = (det->getOrientation()).getYaw();
  //          int ccdTiltNQuarter = (det->getOrientation()).getNQuarter();

            CPROP[ID].ID=detId.getSerial();
            CPROP[ID].GLOB_POS[0]=offsetXY[0];
            CPROP[ID].GLOB_POS[1]=offsetXY[1];
            CPROP[ID].GLOB_POS[2]=0;//ccdTiltNQuarter * 90.0;//?
            CPROP[ID].NUM =matchlist[ID].size();
            APROP->refNUM+=matchlist[ID].size();
        }
    }
}
