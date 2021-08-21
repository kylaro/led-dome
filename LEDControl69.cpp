// LEDControl69.cpp : Defines the entry point for the application.
//

#include "LEDControl69.h"
#include "Networking/ledcontrol_tests.h"
#include "Graphics/graphics_test.h"
#include "Objects/dome.h"
#include "Graphics/render.h"
#include "PatternsPlus/pattern.h"
#include <thread>
#include "PatternsPlus/ledengine.h"
using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	//graphics_test();
	Dome* theDome = new Dome();// one dome object for all

	giveEngineDome(theDome);
	std::thread ledthread( run );
	domeToViewer(theDome);

	return 0;
}
