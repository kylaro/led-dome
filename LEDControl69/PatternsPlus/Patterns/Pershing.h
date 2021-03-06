#ifndef PERSHING_H
#define PERSHING_H
#include "../pattern.h"
#include "../Effects/SnakeEffect.h"
#include "../Effects/Firefly.h"
#include "../Effects/Blink.h"
#include "../Effects/Firework.h"
#include "../Effects/Sweeps.h"
#include "../Effects/RainbowFirefly.h"
#include "../Effects/RGBEff.h"
class Pershing : public Pattern {
public:
	using Pattern::Pattern;

	void init();
	void run(bool real);
	void release();
	char name[40] = "empty";

	RGBEff* rgbeff = NULL;
	Sweeps* fullRainbow = NULL;
	SnakeEffect * snake1;
	SnakeEffect* snake2;

	std::vector<RainbowFirefly* > rainbowflies;
	std::vector<Firefly* > fireflies;
	double rumble1 = 0;
	double rumble2 = 0;
	void vibrate(int p, int toggle, double intensity);

	void killSnake1();
	void killSnake2();

};


#endif
