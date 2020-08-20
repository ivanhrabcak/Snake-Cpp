#ifndef TIME_H_
#define TIME_H_

class Time {
    public:        
        static void startTimeThread();
        static long getTimeDelta();
        static void reset();
        static void stop();
    private:
        static volatile long timeDelta;
        static volatile long start;
        static volatile bool isRunning;
        static void updateTimeLoop();
};

#endif