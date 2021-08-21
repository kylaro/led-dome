#include "XBOX.h"
#include "stdlib.h"
namespace xbox {
	CXBOXController* Player1;
	CXBOXController* Player2;

	

	void init() {
		Player1 = new CXBOXController(P1);
		Player2 = new CXBOXController(P2);
	}

	CXBOXController* getP(int p) {
		CXBOXController* Player;
		if (p == P1) {
			Player = Player1;
		}
		else {
			Player = Player2;
		}
		if (Player == NULL) {
			init();
			if (p == P1) {
				Player = Player1;
			}
			else {
				Player = Player2;
			}
		}

		if (Player->IsConnected()) {
			return Player;
		}/*
		else {
			printf("new joystick\n");
			free(Player);
			Player = new CXBOXController(p);
			if (Player->IsConnected()) {
				return Player;
			}
			else {
				return NULL;
			}
		}*/

	}
	int getPress(int p, int button) {
		CXBOXController* player = getP(p);
		if (player == NULL) {
			return 0;
		}
		return player->getButtonPress(button);
	}
	int getHeld(int p, int button) {
		CXBOXController* player = getP(p);
		if (player == NULL) {
			return 0;
		}
		return player->getButtonHeld(button);
	}

	int xinput_buttons[NUM_XINPUT_BUTTONS] = {
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		XINPUT_GAMEPAD_START,
		XINPUT_GAMEPAD_BACK,
		XINPUT_GAMEPAD_LEFT_THUMB,
		XINPUT_GAMEPAD_RIGHT_THUMB,
		XINPUT_GAMEPAD_LEFT_SHOULDER,
		XINPUT_GAMEPAD_RIGHT_SHOULDER,
		XINPUT_GAMEPAD_A,
		XINPUT_GAMEPAD_B,
		XINPUT_GAMEPAD_X,
		XINPUT_GAMEPAD_Y
	};

	int getDpadUpPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_DPAD_UP);
	}
	int getDpadUpHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_DPAD_UP);
	}

	int getDpadDownPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_DPAD_DOWN);
	}
	int getDpadDownHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_DPAD_DOWN);
	}
	int getDpadLeftPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_DPAD_LEFT);
	}
	int getDpadLeftHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_DPAD_LEFT);
	}

	int getDpadRightPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_DPAD_RIGHT);
	}
	int getDpadRightHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_DPAD_RIGHT);
	}

	int getStartPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_START);
	}
	int getStartHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_START);
	}

	int getBackPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_BACK);
	}
	int getBackHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_BACK);
	}

	int getLeftThumbPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_LEFT_THUMB);
	}
	int getLeftThumbHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_LEFT_THUMB);
	}

	int getRightThumbPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_RIGHT_THUMB);
	}
	int getRightThumbHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_RIGHT_THUMB);
	}

	int getLeftShoulderPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_LEFT_SHOULDER);
	}
	int getLeftShoulderHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_LEFT_SHOULDER);
	}

	int getRightShoulderPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_RIGHT_SHOULDER);
	}
	int getRightShoulderHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_RIGHT_SHOULDER);
	}

	int getAPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_A);
	}
	int getAHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_A);
	}

	int getBPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_B);
	}
	int getBHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_B);
	}

	int getXPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_X);
	}
	int getXHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_X);
	}

	int getYPress(int p) {
		return getPress(p, XINPUT_GAMEPAD_Y);
	}
	int getYHeld(int p) {
		return getHeld(p, XINPUT_GAMEPAD_Y);
	}
	
	



	int anyHeld(int p) {
		CXBOXController* player = getP(p);
		if (player == NULL) {
			return 0;
		}
		for (int i = 0; i < NUM_XINPUT_BUTTONS; i++) {
			int button = xinput_buttons[i];
			if (player->getButtonHeld(button)) {
				return 1;
			}
		}
		return 0;
	}
	
	int anyPressed(int p) {
		CXBOXController* player = getP(p);
		if (player == NULL) {
			return 0;
		}
		for (int i = 0; i < NUM_XINPUT_BUTTONS; i++) {
			int button = xinput_buttons[i];
			if (player->getButtonPress(button) ){
				return 1;
			}
		}
		return 0;
	}

	void rumble(int p) {
		static double rumble1 = 0;
		static double rumble2 = 0;

	}

	void vibrate(int p, double val) {
		CXBOXController* Player = getP(p);
		if (Player == NULL) {
			return;
		}
		if (val < 0) {
			val = 0;
		}
		if (val > 1) {
			val = 1;
		}

		Player->Vibrate(val*65535.0, val*65535.0);
	}

	//-1 is left, 0 is none, 1 is right
	double getRightThumbY(int p) {
		CXBOXController* Player = getP(p);
		if (Player == NULL) {
			return 0;
		}
		return Player->getRightThumbY();
		//return 0;
	}
	//-1 is left, 0 is none, 1 is right
	double getLeftThumbstickX(int p) {
		CXBOXController* Player = getP(p);
		if (Player == NULL) {
			return 0;
		}
		return Player->getLeftThumbX();
		//return 0;
	}

	double getLeftThumbAngle(int p) {
		CXBOXController* Player = getP(p);
		if (Player == NULL) {
			return 0;
		}
		return Player->getLeftThumbAngle();
		//return 0;
	}

	int getLeftThumbActive(int p) {
		CXBOXController* Player = getP(p);
		if (Player == NULL) {
			return 0;
		}
		return Player->getLeftThumbActive();
			
	}


}//end of namespace xbox
	



