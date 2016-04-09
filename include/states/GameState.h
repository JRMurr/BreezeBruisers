#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <SDL.h>

#include "StateManager.h"

// Abstract class for game states
class GameState {
    public:
        // Init and clean up
        virtual void Init(SDL_Renderer*) = 0;
        virtual void Cleanup() = 0;

        // Pause and resume
        virtual void Pause() = 0;
        virtual void Resume() = 0;

        // Main loop
        virtual void Event(StateManager*, SDL_Event) = 0;
        virtual void Update(StateManager*, int) = 0;
        virtual void Draw(SDL_Renderer*) = 0;
};

#endif // GAMESTATE_H_INCLUDED
