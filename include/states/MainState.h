#ifndef MAINSTATE_H_INCLUDED
#define MAINSTATE_H_INCLUDED

#include "GameState.h"
#include <stdio.h>
#include "../STexture.h"
#include "../SpriteSheet.h"
#include "../Player.h"


class MainState : public GameState {
    private:
		int totalTicks;
		// The sprite sheet
		SpriteSheet fieldSheet;
		// Player
		Player player;
        //Singleton
        MainState();

    public:
        // Init and clean up
		void Init(SDL_Renderer*);
        void Cleanup();

        // Pause and resume
        void Pause();
        void Resume();

        // Main loop
        void Event(StateManager*, SDL_Event);
        void Update(StateManager*, int);
        void Draw(SDL_Renderer*);

        // Retrieve the instance
        static MainState* Instance() {
            static MainState instance;
            return &instance;
        }
};

#endif // MAINSTATE_H_INCLUDED
