#ifndef STATEMANAGER_H_INCLUDED
#define STATEMANAGER_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stack>
#include <stdio.h>
#include <sstream>

#include "../utilities/Timer.h"
#include "../Define.h"
#include "../STexture.h"

class GameState;

class StateManager {
    private:
        std::stack<GameState*> states;
        // Display window
        SDL_Window* window;
        // The render target
		STexture target;
        // Frame timer
        Timer frame_timer;
		// Total ticks
		int totalTicks;
		// Frame Count
		int frames;
        // Quit bool
        bool quit;
    public:
        // Init and clean up
        int Init();
        int Cleanup();

        // Return bool for quitting
        bool quitting();

        // Set quit to true
        void Quit();

        // Managing functions
        void ChangeState(GameState*);
        void PushState(GameState*);
        void PopState(int);

        // Main Loop functions
        void Event();
        void Update();
        void Draw();

		// Display render testing static
		static SDL_Renderer* screen;
};

#endif // STATEMANAGER_H_INCLUDED
