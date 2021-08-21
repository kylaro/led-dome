#ifndef EASY3D_IMGUI_VIEWER_H
#define EASY3D_IMGUI_VIEWER_H

#include <easy3d/viewer/viewer.h>
#include <easy3d/util/timer.h>
#include "../Objects/dome.h"
#include <easy3d/renderer/drawable_points.h>
#include "../PatternsPlus/shared.h"

namespace easy3d {

	class DomeViewer : public Viewer
	{
	public:
		DomeViewer(
			const std::string& title = "Easy3D ImGui Viewer",
			int samples = 4,
			int gl_major = 3,
			int gl_minor = 2,
			bool full_screen = false,
			bool resizable = true,
			int depth_bits = 24,
			int stencil_bits = 8
		);
		virtual void draw() const override;
		//void drawWrapper();
		void initDome();
		Dome* myDome;
		Shared* shared;
		std::vector<easy3d::vec3> points;
		//std::vector<easy3d::vec3> colors;
		PointsDrawable* drawable;
		//void* tickfunc(void) const;
		bool displaying = true;
		

	protected:
		void submitBuffer();
		// Single global context by default, but can be overridden by the user
		bool callback_event_keyboard(int key, int action, int modifiers) override;

	};

}

#endif	// _EASY3D_VIEWER_H_