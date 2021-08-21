#include "DomeViewer.h"
#include "../Objects/dome.h"
#include "render.h"
#include <easy3d/renderer/drawable_points.h>
#include <easy3d/util/timer.h>
#include "DomeViewer.h"
#include <easy3d/core/point_cloud.h>
#include <easy3d/renderer/camera.h>

using namespace easy3d;

int domeToViewer(Dome * theDome, Shared * sharedObject) {

    DomeViewer viewer("LED Control 69");
    viewer.myDome = theDome;
    viewer.shared = sharedObject;
    viewer.initDome();
    Camera * cam = viewer.camera();// setOrientation(0, 0);
    cam->setOrientation(0, 0.3); // fix the dome being rotated incorrectly
    
    //Timer<> t;
    //t.set_interval(16, &viewer, &DomeViewer::draw);          // This also works

    return viewer.run();

}

