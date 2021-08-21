// LEDControl69.cpp : Defines the entry point for the application.
//

#include "LEDControl69.h"
#include "Networking/ledcontrol_tests.h"
#include "Graphics/graphics_test.h"
#include "Objects/dome.h"
#include "Graphics/render.h"
#include <thread>
using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	//graphics_test();
	
	std::thread one(testChase);
	domeToViewer();

	return 0;
}
