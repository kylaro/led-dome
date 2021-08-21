#include "CXBOXController.h"
#include <stdlib.h>     /* malloc, free, rand */

/*
XINPUT_GAMEPAD_DPAD_UP          0x00000001
XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
XINPUT_GAMEPAD_START            0x00000010
XINPUT_GAMEPAD_BACK             0x00000020
XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
XINPUT_GAMEPAD_A                0x1000
XINPUT_GAMEPAD_B                0x2000
XINPUT_GAMEPAD_X                0x4000
XINPUT_GAMEPAD_Y                0x8000
*/

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
int CXBOXController::getButtonPress(int button) {
    if (this->IsConnected()) {
        return this->buttons[button]->isPressed();
    }
    else {
        return 0;
    }

}
double CXBOXController::getLeftThumbAngle() {
    return this->leftStick->getAngle();
}
double CXBOXController::getLeftThumbX() {
    return this->leftStick->getX();
}
double CXBOXController::getRightThumbY() {
    return this->leftStick->getRightY();
}

int CXBOXController::getLeftThumbActive() {
    return this->leftStick->getActive();
}


int CXBOXController::getButtonHeld(int button) {
    if (this->IsConnected()) {
        return this->buttons[button]->isHeld();
    }
    else {
        return 0;
    }
    
}

CXBOXController::CXBOXController(int playerNumber)
{
    
    // Set the Controller Number
    _controllerNum = playerNumber - 1;
   // _controllerState = (ximalloc(sizeof(XINPUT_STATE));
    for (int i = 0; i < NUM_XINPUT_BUTTONS; i++) {
        buttons[xinput_buttons[i]] = new Button(this, xinput_buttons[i]);
    }
    this->leftStick = new Thumbstick(this);
    
}

XINPUT_STATE CXBOXController::GetState()
{

    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    XInputGetState(_controllerNum, &_controllerState);

    return _controllerState;
}

bool CXBOXController::IsConnected()
{
    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    DWORD Result = XInputGetState(_controllerNum, &_controllerState);

    if (Result == ERROR_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CXBOXController::Vibrate(int leftVal, int rightVal)
{
    // Create a Vibraton State
    XINPUT_VIBRATION Vibration;

    // Zeroise the Vibration
    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    Vibration.wLeftMotorSpeed = leftVal;
    Vibration.wRightMotorSpeed = rightVal;

    // Vibrate the controller
    XInputSetState(_controllerNum, &Vibration);
}