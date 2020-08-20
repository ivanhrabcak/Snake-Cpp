#ifndef INPUT_H_
#define INPUT_H_

#include "field.h"

class Input {
    public:
        static Direction *getArrowKeysPressed();
    private:
        static bool getStateOfKey(int key);
};

#endif