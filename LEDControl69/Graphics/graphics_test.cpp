#include <easy3d/util/logging.h>
#include <easy3d/viewer/viewer.h>
#include <easy3d/renderer/drawable_points.h>
#include <easy3d/util/timer.h>
#include "DomeViewer.h"
#include <easy3d/core/point_cloud.h>
#include "graphics_test.h"

using namespace easy3d;



int graphics_test() {
    // Initialize logging.
    //logging::initialize();

    // Create a point cloud
    PointCloud* cloud = new PointCloud;
    std::vector<vec3> points;
    std::vector<vec3> colors;
    // Add some points. Here we add 100 points on a 10*10 grid.
    for (float i = -5; i < 5; ++i) {
        for (float j = -5; j < 5; ++j) {
            for (float k = -5; k < 5; ++k) {

                //cloud->add_vertex(vec3(i, j, k));// z = 0: all points are on XY plane
                points.push_back(vec3(i, j, k));
                colors.push_back(vec3(abs(0.5), abs(0), abs(k / 5.0f)));

            }
        }

    }

    DomeViewer viewer("Hello");

    PointsDrawable* drawable = new PointsDrawable("leds");


    drawable->update_vertex_buffer(points);
    drawable->update_color_buffer(colors);
    drawable->set_point_size(10);
    drawable->set_impostor_type(PointsDrawable::SPHERE);
    drawable->set_coloring_method(State::SCALAR_FIELD);
    drawable->set_lighting(false);


    viewer.add_drawable(drawable);

    //Timer<> t;
    //t.set_interval(16, &viewer, &DomeViewer::draw);          // This also works

    return viewer.run();
}