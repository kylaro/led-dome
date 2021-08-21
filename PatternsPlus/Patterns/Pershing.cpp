#include "Pershing.h"
#include "../helpers.h""
#include "../Effects/Shimmer.h"
#include "../Interface/XBOX.h"
#include "../Effects/Firework.h"

void Pershing::init() {
	snake1 = new SnakeEffect(ledInterface, shared->mapping);
	snake2 = new SnakeEffect(ledInterface, shared->mapping);
	snake1->player = P1;
	snake2->player = P2;
	snake1->init();
	snake2->init();
	effectEngine->apply(snake1);
	effectEngine->apply(snake2);
}

void Pershing::release() {
	snake1->release();
	snake2->release();
}

void Pershing::run(bool real) {
	static int initted = 0;
	if (initted == 0) {
		init();
		initted = 1;
	}

	//Check if snakes ate little bugs...
	int snake1_i = snake1->curNode->led->index;
	int snake2_i = snake2->curNode->led->index;
	for (Firefly* fly : fireflies) {
		int fly_i = fly->curNode->led->index;
		//i could have a list of snakes but whatever
		if (fly_i == snake1_i) {
			snake1->feed(0.01);
			fly->release();
		}
		if (fly_i == snake2_i) {
			snake2->feed(0.01);
			fly->release();
		}
	}
	//check if snake1 intersects snake 2's tail
	int snake1_i2 = snake1->curNode->led->index;
	int snake2_i2 = snake2->curNode->led->index;
	for (int i = snake2->trail_k; i < snake2->trail.size(); i++) {
		ihsv_f hsv = snake2->trail[i];
		if (hsv.i == snake1_i2) {
			snake1->release();
			snake1 = new SnakeEffect(ledInterface, shared->mapping);
			snake1->player = P1;

			snake1->init();

			effectEngine->apply(snake1);

		}
	}
	for (int i = snake1->trail_k; i < snake1->trail.size(); i++) {
		ihsv_f hsv = snake1->trail[i];
		if (hsv.i == snake2_i2) {
			snake2->release();
			snake2 = new SnakeEffect(ledInterface, shared->mapping);

			snake2->player = P2;

			snake2->init();

			effectEngine->apply(snake2);
		}
	}




	Firefly* littlebug = new Firefly(ledInterface, shared->mapping);
	effectEngine->apply(littlebug);
	fireflies.push_back(littlebug);

	if (xbox::getYHeld(P1) || xbox::getYHeld(P2)) {
		for (int i = 0; i < 10; i++) {
			Shimmer* shim = new Shimmer(ledInterface, shared->mapping);
			shim->duration = 100 + rand() % 2000;
			effectEngine->apply(shim);
		}
	}

	if (xbox::getXHeld(P1) || xbox::getXHeld(P2)) {
		for (int i = 0; i < 20; i++) {
			Blink* blink = new Blink(ledInterface, shared->mapping);
			blink->duration = 1000 + rand() % 200;
			effectEngine->apply(blink);
		}
	}

	int p1_press = xbox::getBPress(P1);
	int p2_press = xbox::getBPress(P2);
	if (p1_press) {
		Firework* fire = new Firework(ledInterface, shared->mapping);
		fire->giveEngine(effectEngine);
		effectEngine->apply(fire);
		if (rumble1 > 0) {
			xbox::vibrate(P1, 1);
		}
		else {
			if (rumble1 > -1)
				xbox::vibrate(P1, 0);
		}


		rumble1 -= 0.2;

	}
	else {

		if (rumble1 > 0 && rumble1 < 1) {
			xbox::vibrate(P1, 1);
			rumble1 -= 0.2;
		}
		else {
			rumble1 = 1;
		}
		if (rumble1 == 1) {
			xbox::vibrate(P1, 0);
			rumble1 = 1.05;
		}

	}


	if (p2_press) {


		Firework* fire = new Firework(ledInterface, shared->mapping);
		fire->giveEngine(effectEngine);
		effectEngine->apply(fire);


		if (rumble2 > 0) {
			xbox::vibrate(P2, 1);
		}
		else {
			if (rumble2 > -1)
				xbox::vibrate(P2, 0);
		}


		rumble2 -= 0.2;
	}
	else {


		//
		if (rumble2 > 0 && rumble2 < 1) {
			xbox::vibrate(P2, 1);
			rumble2 -= 0.2;
		}
		else {
			rumble2 = 1;
		}
		if (rumble2 == 1) {
			xbox::vibrate(P2, 0);
			rumble2 = 1.05;
		}

	}

}