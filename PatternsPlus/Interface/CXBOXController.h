#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

// No MFC
#define WIN32_LEAN_AND_MEAN
//#define WINDOWS_IGNORE_PACKING_MISMATCH
// We need the Windows Header and the XInput Header
#include <windows.h>
#include <XInput.h>
#include "Button.h"
#include "Thumbstick.h"
class Button;
class Thumbstick;
#include <unordered_map>
// Now, the XInput Library
// NOTE: COMMENT THIS OUT IF YOU ARE NOT USING
// A COMPILER THAT SUPPORTS THIS METHOD OF LINKING LIBRARIES
#pragma comment(lib, "XInput.lib")
#define NUM_XINPUT_BUTTONS 14

// XBOX Controller Class Definition
class CXBOXController
{
private:
    XINPUT_STATE _controllerState;
    int _controllerNum;
    Thumbstick * leftStick;
public:
    CXBOXController(int playerNumber);
    XINPUT_STATE GetState();
    bool IsConnected();
    void Vibrate(int leftVal = 0, int rightVal = 0);
    std::unordered_map<int, Button*> buttons;
    int getButtonHeld(int button);
    int getButtonPress(int button);
    double getLeftThumbAngle();
    double getLeftThumbX();
    int getLeftThumbActive();
};

#endif