

#include "DomeViewer.h"
#include <easy3d/util/timer.h>
#include <easy3d/core/point_cloud.h>
#include <easy3d/renderer/drawable_points.h>
#include "../Networking/ledcontrol.h"
#include "../PatternsPlus/helpers.h"
#include <chrono>
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

	
	int buffer_i = 0;

	void DomeViewer::submitBuffer() {
		printf("->\n", shared->bufferPipe);
		shared->submitPipe = 1;
		shared->keyPressedPipe = 0; // we are treating submission as not a keypress..
		buffer_i = 0;
	}

	bool DomeViewer::callback_event_keyboard(int key, int action, int modifiers) {
		if (action == 1) {
			switch (key) {
				case 257:
					//printf("ENTER");
					
					submitBuffer();
					
					buffer_i = 0;
					break;
				case 259:
					//printf("BACKSPACE");
					shared->bufferPipe[buffer_i] = 0;
					buffer_i = buffer_i > 0 ? buffer_i - 1 : 0;
					printf("\b \b");
					break;
				case 262: // right arrow
				case 265: // up arrow
					shared->directionPipe = 1;
					break;
				case 264: // down arrow
				case 263: // left arrow
					shared->directionPipe = -1;
					break;
				case 32: ///spacebar
					shared->spacePressedPipe = 1;
				default:
					if (key >= 65 && key <= 90) {
						key += 32;//convert to lower case for all letters lol i hate all this caps
					}
					shared->bufferPipe[buffer_i] = key;
					buffer_i = buffer_i < BUFFER_LEN-2 ? buffer_i + 1 : BUFFER_LEN-2;//hope this never happens - typing more than 90 without submitting lol
					printf("%c", key);
					//shared->bufferPipe[buffer_i] = key;
			}
			//printf("{key:%d , action:%d, modifiers:%d}\n", key, action, modifiers);
			
			
			shared->keyPressedPipe = key;
		}
		else if (action == 2) {
			//this is when we are holding down a key;
			shared->keyHeldPipe = key;
		}
		else if (action == 0) {
			//this is when we release a key
			shared->keyHeldPipe = 0;
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
		auto now = std::chrono::high_resolution_clock::now();
		uint32_t beginNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
		colors.clear();
		
		if (shared->calibratingPipe) {

			for (int e = 0; e < myDome->struts.size(); e++) {
				Strut* edge = myDome->struts[e];
				
				if (e == shared->selectedEdgePipe) {
					colors.push_back(easy3d::vec3(0, 1, 0));//start pixel is green;
					for (int i = 1; i < edge->numLEDs - 1; i++) {
						colors.push_back(easy3d::vec3(0,0,1));
					}
					colors.push_back(easy3d::vec3(1, 0, 0));
				}
				else {
					if (edge->confirmed) {
						for (int i = 0; i < edge->numLEDs; i++) {
							colors.push_back(easy3d::vec3(0, 0.5, 0));
						}
					}
					else {
						for (int i = 0; i < edge->numLEDs; i++) {
							colors.push_back(easy3d::vec3(0, 0, 0));
						}
						
					}
					
				}
				
				

			}
		}
		else {
			//In here is normal drawing
			for (Strut* edge : myDome->struts) {
				for (LED* led : edge->leds) {
					//points.push_back(easy3d::vec3(led->x, led->y, led->z));
					//colors.push_back(easy3d::vec3(edge->letter == 1 ? 1 : edge->letter == 2 ? 0.5 : 0, 1 - edge->letter / 4.0f, edge->letter / 4.0f));
					colors.push_back(easy3d::vec3(getLED(led->index, shared->viewReal)->r / 256.0f, getLED(led->index, shared->viewReal)->g / 256.0f, getLED(led->index, shared->viewReal)->b / 256.0f));
				}
			}
		}
		
		now = std::chrono::high_resolution_clock::now();
		uint32_t endNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
		uint32_t elapsed = endNanos - beginNanos;
		//std::cout << elapsed << "\t\t color pushing back " << std::endl;
		now = std::chrono::high_resolution_clock::now();
		beginNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();


		drawable->update_color_buffer(colors);


		Viewer::update();
		Viewer::draw();
		now = std::chrono::high_resolution_clock::now();
		endNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
		elapsed = endNanos - beginNanos;
		//std::cout << elapsed << "\t\t other drawing time" << std::endl;
	}



}