#include "time.h"
#include <ctime>
#include <thread>

using namespace std;

long Time::getTimeDelta() {
    timeDelta = time(0) - start;
    return timeDelta / CLOCKS_PER_SEC;
}

void Time::stop() {
    isRunning = false;
}

void Time::reset() {
    start = time(0);
}