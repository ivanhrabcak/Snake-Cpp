#include "input.h"
#include "field.h"

#ifdef _WIN32
    #include <windows.h>
    #define LEFT_ARROW 0x25
    #define UP_ARROW 0x26
    #define RIGHT_ARROW 0x27
    #define DOWN_ARROW 0x28
    #define ESCAPE 0x1B
#endif
#ifdef __unix__
    #include <X11/extensions/XInput.h>
    #include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
    #define LEFT_ARROW 0xff51
    #define UP_ARROW 0xff52
    #define RIGHT_ARROW 0xff53
    #define DOWN_ARROW 0xff54
    #define ESCAPE 0xff1b
#endif

#define sizeofarray(x) sizeof(x) / sizeof(x[0])

Direction *Input::getArrowKeysPressed() {
    bool left = getStateOfKey(LEFT_ARROW);
    bool right = getStateOfKey(RIGHT_ARROW);
    bool up = getStateOfKey(UP_ARROW);
    bool down = getStateOfKey(DOWN_ARROW);

    int numberOfKeysPressed = left +
                              right +
                              up +
                              down;

    if (numberOfKeysPressed == 0) {
        return NULL;
    }

    Direction *keysPressed = new Direction[numberOfKeysPressed];
    int index = 0;
    if (left) {
        keysPressed[index] = LEFT;
        index++;
    }
    if (right) {
        keysPressed[index] = RIGHT;
        index++;
    }
    if (down) {
        keysPressed[index] = DOWN;
        index++;
    }
    if (up) {
        keysPressed[index] = UP;
        index++;
    }

    return keysPressed;
}

bool Input::getStateOfKey(int key) {
    #ifdef _WIN32
        return GetAsyncKeyState(key);
    #endif
    #ifdef __unix__
        Display *g_pDisplay = XOpenDisplay((char*) 0); 
        KeySym keySym = key;
        if(g_pDisplay == NULL) {
            return false;
        }
        
        char szKey[32];
        int iKeyCodeToFind = XKeysymToKeycode(g_pDisplay, keySym);
        
        XQueryKeymap(g_pDisplay, szKey);
        XCloseDisplay(g_pDisplay);

        return szKey[iKeyCodeToFind / 8] & (1 << (iKeyCodeToFind % 8));
    #endif
}