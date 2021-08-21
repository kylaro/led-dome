#include "Debug.h"
#include "../helpers.h""
//#include "../../Networking/ledcontrol.h"

void Debug::run(bool real) {
	
	static int i = 0;
	LED* led = shared->mapping->phiLeds[i];
	int led_index = led->index;
	if (shared->spacePressedPipe) {

		shared->spacePressedPipe = 0;
		setLED(led_index, 0, real);
		int skips = 0;
		while (skips < 2) {
			i++;
			led = shared->mapping->phiLeds[i];

			while (led->confirmed == false) {
				i++;
				i %= shared->mapping->phiLeds.size();
				led = shared->mapping->phiLeds[i];
				
			}
			skips++;
		}
		
		led_index = led->index;
		setLED(shared->mapping->phiLeds[i]->index, wheel(i*16), real);
		printf("\ni=%d\nledindex=%d\nledphi=%f\n", i,led_index,mapping->getLEDPhi(led));

		i += 0;
	}
	

	
	updateLEDs(real);

}