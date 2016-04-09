#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include <SDL.h>

// timer class it is used to measure elapsed time
class Timer {
private:
    // time the timer was started
    int start_ticks;

    // time the timer was paused
    int paused_ticks;

    // timer status variables
    bool started;
    bool paused;

public:
    // constructor
    Timer();

    // basic timer functions
    void start();
    void pause();
    void resume();
    void stop();

    // get timers ticks
    int get_ticks();

    // returns timers status
    bool is_started();
    bool is_paused();
};


#endif // TIMER_H_INCLUDED
