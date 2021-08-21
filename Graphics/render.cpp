#include "DomeViewer.h"
#include "../Objects/dome.h"
#include "render.h"
#include <easy3d/renderer/drawable_points.h>
#include <easy3d/util/timer.h>
#include "DomeViewer.h"
#include <easy3d/core/point_cloud.h>
#include <easy3d/renderer/camera.h>

using namespace easy3d;

int domeToViewer() {

    /*
	std::vector<easy3d::vec3> points;
	std::vector<easy3d::vec3> colors;
	
	
	for (Node* node : dome->nodes) {
		//std::cout << node->x << " " << node->y << " " << node->z << std::endl;
		points.push_back(easy3d::vec3(node->x, node->y, node->z));
		colors.push_back(easy3d::vec3(node->x/5.0f, node->y / 5.0f, node->z / 5.0f));
	}

    DomeViewer viewer("Hello");
    //viewer.tickfunc = ledcalcs;

    PointsDrawable* drawable = new PointsDrawable("leds");


    drawable->update_vertex_buffer(points);
    drawable->update_color_buffer(colors);
    drawable->set_point_size(10);
    drawable->set_impostor_type(PointsDrawable::SPHERE);
    drawable->set_coloring_method(State::SCALAR_FIELD);
    drawable->set_lighting(false);


    viewer.add_drawable(drawable);
    */

    DomeViewer viewer("LED Control 69");
    viewer.initDome();
    Camera * cam = viewer.camera();// setOrientation(0, 0);
    cam->setOrientation(0, 0.3); // fix the dome being rotated incorrectly
    
    //Timer<> t;
    //t.set_interval(16, &viewer, &DomeViewer::draw);          // This also works

    return viewer.run();

}

