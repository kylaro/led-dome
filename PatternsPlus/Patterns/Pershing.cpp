#include "Pershing.h"
#include "../helpers.h""
#include "../Effects/Shimmer.h"
#include "../Interface/XBOX.h"
#include "../Effects/SnakeFirework.h"

#include "../vectormath.h"

void Pershing::init() {
	snake1 = new SnakeEffect(ledInterface, shared->mapping);
	snake2 = new SnakeEffect(ledInterface, shared->mapping);
	snake1->player = P1;
	snake2->player = P2;
	//snake1->init();
	//snake2->init();
	//effectEngine->apply(snake1);
	//effectEngine->apply(snake2);
	
	SnakeFirework* fire1 = new SnakeFirework(ledInterface, shared->mapping);
	fire1->giveEngine(effectEngine);
	fire1->snake = snake1;
	effectEngine->apply(fire1);

	SnakeFirework* fire2 = new SnakeFirework(ledInterface, shared->mapping);
	fire2->giveEngine(effectEngine);
	fire2->snake = snake2;
	effectEngine->apply(fire2);
}

void Pershing::release() {
	snake1->release();
	snake2->release();
}


void Pershing::killSnake1() {
	for (LLnode* node : snake1->pastNodes) {
		Shimmer* shim = new Shimmer(ledInterface, mapping);
		shim->duration = rand() % 1000 + 200;
		shim->led = node->led;
		effectEngine->apply(shim);
	}
	snake1->release();
	snake1 = new SnakeEffect(ledInterface, shared->mapping);
	snake1->player = P1;

	SnakeFirework* fire = new SnakeFirework(ledInterface, shared->mapping);
	fire->giveEngine(effectEngine);
	fire->snake = snake1;
	effectEngine->apply(fire);
	vibrate(P1, 1, 0.1);
	vibrate(P2, 1, 0.1);
}
void Pershing::killSnake2() {
	for (LLnode* node : snake2->pastNodes) {
		Shimmer* shim = new Shimmer(ledInterface, mapping);
		shim->duration = rand() % 1000 + 200;
		shim->led = node->led;
		effectEngine->apply(shim);
	}
	snake2->release();
	snake2 = new SnakeEffect(ledInterface, shared->mapping);
	snake2->player = P2;

	SnakeFirework* fire = new SnakeFirework(ledInterface, shared->mapping);
	fire->giveEngine(effectEngine);
	fire->snake = snake2;
	effectEngine->apply(fire);
	vibrate(P2, 1, 0.1);
	vibrate(P1, 1, 0.1);
}

void Pershing::run(bool real) {
	static int initted = 0;
	if (initted == 0) {
		init();
		initted = 1;
	}
	int snake1_alive = snake1->initted;
	int snake2_alive = snake2->initted;
	//Check if snakes ate little bugs...
	
	
	int snake1_size = snake1->pastNodes.size();
	int snake2_size = snake2->pastNodes.size();

	for (Firefly* fly : fireflies) {
		if (fly->done == 1) {
			continue;
		}
		int fly_i = fly->curNode->led->index;
		//i could have a list of snakes but whatever
		
		if (snake1_alive) {
			int snake1_i = snake1->curNode->led->index;
			for (int i = 0; i < snake1_size; i++) {
				
				snake1_i = snake1->pastNodes[i]->led->index;
				if (fly_i == snake1_i) {
					
					fly->release();
					if (i > snake1_size - 5) {
						if (snake1->length < 10) {
							snake1->feed(3);
						}
						else if (snake1->length < 100) {
							snake1->feed(2);
						}
						else {
							snake1->feed(1);
						}
						
						vibrate(P1, 1, 0.6);
					}
				}
			}
		}
		
		if (snake2_alive) {
			int snake2_i = snake2->curNode->led->index;
			for (int i = 0; i < snake2_size; i++) {
				
				snake2_i = snake2->pastNodes[i]->led->index;
				if (fly_i == snake2_i) {
					
					fly->release();
					if (i > snake2_size - 5) {
						if (snake2->length < 10) {
							snake2->feed(3);
						}
						else if (snake2->length < 100) {
							snake2->feed(2);
						}
						else {
							snake2->feed(1);
						}
						vibrate(P2, 1, 0.6);
					}
					
				}
			}
		}
		

	}
	//check if snake1 intersects snake 2's tail or node
	if (snake1_alive && snake2_alive) {
		int shouldKill1 = 0;
		int shouldKill2 = 0;
		//checking if they've hit any past nodes
		for (LLnode* snake2_node : snake2->pastNodes) {
			if (snake1->curNode->led->index == snake2_node->led->index) {
				//snake 1 hit snakke 2
				shouldKill1 = 1;
				break;
			}
		}
		for (LLnode* snake1_node : snake1->pastNodes) {
			if (snake2->curNode->led->index == snake1_node->led->index) {
				shouldKill2 = 1;
				break;
			}
		}
		if (shouldKill1) {
			killSnake1();
		}
		if (shouldKill2) {
			killSnake2();
		}

		if (shouldKill1 && shouldKill2) {
			for (int i = 0; i < 25; i++) {
				Firework* fire = new Firework(ledInterface, shared->mapping);
				fire->giveEngine(effectEngine);
				effectEngine->apply(fire);
			}
		}

	}
	snake1_alive = snake1->initted;
	snake2_alive = snake2->initted;
	if (snake1_alive && snake2_alive){
		int shouldKill1 = 0;
		int shouldKill2 = 0;
		if (snake1->curNode->nodeImpact() && snake1->prevNode->nodeImpact()) {
			xyz_f snake1_node_xyz = snake1->curNode->node->xyz;
			//check if line between curnode and prev node intersects with every line formed by 2 of snake2's nodes
			xyz_f snake1_p1 = snake1->prevNode->led->xyz;
			xyz_f snake1_p2 = snake1->curNode->led->xyz;
			//First let's get snake1's 2D coordinates
			xy_f snake1_xy1 = projectPoint(snake1_node_xyz, snake1_p1);
			xy_f snake1_xy2 = projectPoint(snake1_node_xyz, snake1_p2);
			for (int i = 1; i < snake2->pastNodes.size(); i++) {
				if (snake2->pastNodes[i]->nodeImpact() && snake2->pastNodes[i - 1]->nodeImpact()) {
					//Then let's get snake2's 2D coordinates
					xyz_f snake2_p1 = snake2->pastNodes[i]->led->xyz;
					xyz_f snake2_p2 = snake2->pastNodes[i - 1]->led->xyz;
					xy_f snake2_xy1 = projectPoint(snake1_node_xyz, snake2_p1);
					xy_f snake2_xy2 = projectPoint(snake1_node_xyz, snake2_p2);
					//Then run the line intersection between them
					if (linesIntersect(snake1_xy1, snake1_xy2, snake2_xy1, snake2_xy2)) {
						shouldKill1 = 1;
					}
				}
				

				
			}
			

			
			
			
			
			

		}
		//this is for when they impact a node
		/*if (snake1->curNode->nodeImpact()) {
			for (LLnode* snake2_node : snake2->pastNodes) {
				if (snake2_node->myNode == snake1->curNode->myNode) {
					shouldKill1 = 1;

					break;
				}
			}
		}
		if (snake2->curNode->nodeImpact()) {
			for (LLnode* snake1_node : snake1->pastNodes) {
				if (snake1_node->myNode == snake2->curNode->myNode) {
					shouldKill2 = 1;

					break;
				}
			}
		}*/
		if (shouldKill1) {
			killSnake1();
		}
		if (shouldKill2) {
			killSnake2();
		}
	}

	
	int otherStuff = 0;
	if (xbox::getYHeld(P1) || xbox::getYHeld(P2)) {
		for (int i = 0; i < 10; i++) {
			Shimmer* shim = new Shimmer(ledInterface, shared->mapping);
			shim->duration = 100 + rand() % 2000;
			effectEngine->apply(shim);
		}
		otherStuff = 1;
	}

	if (xbox::getXHeld(P1) || xbox::getXHeld(P2)) {
		for (int i = 0; i < 20; i++) {
			Blink* blink = new Blink(ledInterface, shared->mapping);
			blink->duration = 1000 + rand() % 200;
			effectEngine->apply(blink);
		}
		otherStuff = 1;
	}
	if (otherStuff == 0) {
		Firefly* littlebug = new Firefly(ledInterface, shared->mapping);
		effectEngine->apply(littlebug);
		fireflies.push_back(littlebug);
	}
	

	/*
	int p1_press = xbox::getBPress(P1);
	int p2_press = xbox::getBPress(P2);
	if (p1_press) {
		Firework* fire = new Firework(ledInterface, shared->mapping);
		fire->giveEngine(effectEngine);
		effectEngine->apply(fire);
		vibrate(P1, 1, 0.2);
	}
	else {
		vibrate(P1, 0, 0.2);
	}


	if (p2_press) {


		Firework* fire = new Firework(ledInterface, shared->mapping);
		fire->giveEngine(effectEngine);
		effectEngine->apply(fire);
		vibrate(P2, 0, 0.2);
	}
	else {
		vibrate(P2, 0, 0.2);
	}*/

	vibrate(P1, 0, 0.2);
	vibrate(P2, 0, 0.2);


	if ((xbox::getRightShoulderPress(P1) && xbox::getLeftShoulderHeld(P1) && xbox::getBackHeld(P1) && xbox::getStartHeld(P1)) || (xbox::getRightShoulderPress(P2) && xbox::getLeftShoulderHeld(P2) && xbox::getBackHeld(P2) && xbox::getStartHeld(P2)) ){

		//start a new game
		release();
		init();
	}

}







//toggle of 1 means it turns it on
//toggle of 0 means it carries on whats happening
//intensity is how much rumble decreases each
void Pershing::vibrate(int p, int toggle, double intensity) {
	static double rumble1 = 0;
	static double rumble2 = 0;
	if (p == P1) {
		if (toggle) {

			if (rumble1 > 0) {
				xbox::vibrate(P1, 1);
			}
			else {
				if (rumble1 > -1)
					xbox::vibrate(P1, 0);
			}


			rumble1 -= intensity;

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
	}
	else if (p == P2) {
		if (toggle) {

		}if (rumble2 > 0) {
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