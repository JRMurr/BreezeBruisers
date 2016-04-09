#include "../../include/utilities/Timer.h"

//timer costructor
Timer::Timer() {
    // set start values for variables
    start_ticks = 0;
    paused_ticks = 0;
    paused = false;
    started = false;
}

// start timer
void Timer::start() {
    started = true;

    paused = false;

    start_ticks = SDL_GetTicks();
}

// stop timer
void Timer::pause() {
    if ((started == true) && (paused == false))
    {
        paused = true;

        paused_ticks = SDL_GetTicks() - start_ticks;
    }
}

// resume the timer
void Timer::resume() {
    if (paused == true)
    {
        paused = false;

        start_ticks = SDL_GetTicks() - paused_ticks;

        paused_ticks = 0;
    }
}

// stop the timer
void Timer::stop () {
    started = false;

    paused = false;
}

// get the number off ticks passed from start
int Timer::get_ticks() {
    if(started == true)
    {
        if (paused == true)
        {
            return paused_ticks;
        }
        else
        {
            return SDL_GetTicks() - start_ticks;
        }
    }
    return 0;
}

// return start and pause state
bool Timer::is_started() {return started;}

bool Timer::is_paused() {return paused;}
