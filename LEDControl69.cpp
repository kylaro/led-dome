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
#include "PatternsPlus/mapping.h"
using namespace std;

//count lines of code in powershell lol:
//(gci -include *.c,*.cpp,*.h -recurse | select-string .).Count
int main()
{

	


	//cout << "Hello CMake." << endl;

	//graphics_test();
	Dome* theDome = new Dome();// one dome object for all
	Shared* sharedObject = new Shared();//a shared object to transfer data between threads
	sharedObject->dome = theDome;

	giveEngineShared(sharedObject);

	std::thread ledthread( runEngine);
	ledthread.detach();
	domeToViewer(theDome, sharedObject);

	return 0;
}
