

#include "DomeViewer.h"
#include <easy3d/util/timer.h>
#include <easy3d/core/point_cloud.h>
#include <easy3d/renderer/drawable_points.h>
#include "../Networking/ledcontrol.h"
namespace easy3d {

	std::vector<vec3> colors;

	DomeViewer::DomeViewer(
		const std::string& title /* = "Easy3D ImGui Viewer" */,
		int samples /* = 4 */,
		int gl_major /* = 3 */,
		int gl_minor /* = 2 */,
		bool full_screen /* = false */,
		bool resizable /* = true */,
		int depth_bits /* = 24 */,
		int stencil_bits /* = 8 */
	)
		: Viewer(title, samples, gl_major, gl_minor, full_screen, resizable, depth_bits, stencil_bits)
	{

	}
	/*
		Ideas for keyboard input:
		ability to select parts of the dome for
		calibration routines
	*/
	/*
		key: number of key
		action: 1 is press, 0 is release
		modifiers: 1 is shift, 2 is control, 4 is alt
	*/

	char buffer[100];
	int buffer_i = 0;

	void submitBuffer() {
		printf("->\n%s\n",buffer);
	}

	bool DomeViewer::callback_event_keyboard(int key, int action, int modifiers) {
		if (action == 1) {
			switch (key) {
				case 257:
					//printf("ENTER");
					buffer[buffer_i] = 0;
					submitBuffer();
					while (buffer_i != 0) {
						buffer[buffer_i] = 0;
						buffer_i -= 1;
					}
					buffer_i = 0;
					break;
				case 259:
					//printf("BACKSPACE");
					buffer[buffer_i] = 0;
					buffer_i = buffer_i > 0 ? buffer_i - 1 : 0;
					printf("\b \b");
					break;
				default:
					buffer[buffer_i] = key;
					buffer_i = buffer_i < 90 ? buffer_i + 1 : 90;//hope this never happens - typing more than 90 without submitting lol
					printf("%c", key);
			}
			//printf("{key:%d , action:%d, modifiers:%d}\n", key, action, modifiers);
			
			buffer[buffer_i] = key;
			myDome->dataPipe = 1;
		}
		return false;
	}



	void DomeViewer::initDome() {
		//myDome = new Dome();
		for (Strut* edge : myDome->struts) {
			for (LED* led : edge->leds) {
				points.push_back(easy3d::vec3(led->x, led->y, led->z));
				//colors.push_back(easy3d::vec3(edge->letter == 1 ? 1 : edge->letter == 2 ? 0.5 : 0, 1 - edge->letter / 4.0f, edge->letter / 4.0f));
				colors.push_back(easy3d::vec3(getLED(led->index)->r / 256.0f, getLED(led->index)->g / 256.0f, getLED(led->index)->b / 256.0f));
			}
		}

		/*for (Strut* edge : myDome->struts) { //Uses just edges 
			Node* from = edge->startNode;
			Node* to = edge->endNode;
			for (float x = 0; x < 1.0f; x += 0.01)//This needs to actually make LEDs not just dots lol
			{
				float new_x = from->x + (to->x - from->x) * x;
				float new_y = from->y + (to->y - from->y) * x;
				float new_z = from->z + (to->z - from->z) * x;
				points.push_back(easy3d::vec3(new_x, new_y, new_z));
				colors.push_back(easy3d::vec3(edge->letter == 1 ? 1 : edge->letter == 2 ? 0.5 : 0, 1- edge->letter / 4.0f, edge->letter/4.0f));
			}
		}*/
		/*
		for (Node* node : myDome->nodes) {
			for (Node* neighbor : node->neighborNodes) {
				if (neighbor == NULL) {
					continue;
				}
				for (float x = 0; x < 1.0f; x += 0.01)//This needs to actually make LEDs not just dots lol
				{
					float new_x = neighbor->x + (node->x - neighbor->x)* x;
					float new_y = neighbor->y + (node->y - neighbor->y) * x;
					float new_z = neighbor->z + (node->z - neighbor->z) * x;
					points.push_back(easy3d::vec3(new_x, new_y, new_z));
					colors.push_back(easy3d::vec3(0, 0, 1));
				}
				
			}
			//std::cout << node->x << " " << node->y << " " << node->z << std::endl;
			points.push_back(easy3d::vec3(node->x, node->y, node->z));
			colors.push_back(easy3d::vec3(node->x / 5.0f, node->y / 5.0f, node->z / 5.0f));
		}*/

		//DomeViewer viewer("Hello");
		//viewer.tickfunc = ledcalcs;

		drawable = new PointsDrawable("leds");


		drawable->update_vertex_buffer(points);
		drawable->update_color_buffer(colors);
		drawable->set_point_size(12);
		drawable->set_impostor_type(PointsDrawable::SPHERE);
		drawable->set_coloring_method(State::SCALAR_FIELD);
		drawable->set_lighting(false);

		Viewer::add_drawable(drawable);
	}


	//Running at about 133 FPS when nothing else
	void DomeViewer::draw() const {
		//drawable->set_point_size(5);
		
		colors.clear();
		for (Strut* edge : myDome->struts) {
			for (LED* led : edge->leds) {
				//points.push_back(easy3d::vec3(led->x, led->y, led->z));
				//colors.push_back(easy3d::vec3(edge->letter == 1 ? 1 : edge->letter == 2 ? 0.5 : 0, 1 - edge->letter / 4.0f, edge->letter / 4.0f));
				colors.push_back(easy3d::vec3(getLED(led->index)->r / 256.0f, getLED(led->index)->g / 256.0f, getLED(led->index)->b / 256.0f));
			}
		}

		drawable->update_color_buffer(colors);

		Viewer::update();
		Viewer::draw();
	}



}