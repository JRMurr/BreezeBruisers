#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"
#include <stdio.h>
#include "../STexture.h"
#include "../utilities/Button.h"
#include "MainState.h"
#include "HiddenState.h"
#include <vector>

#define BUTTON_NUMBER 2

class MainMenu : public GameState {
	private:
		// Button class
		std::vector<Button> buttons;
		// Button sheet
		STexture buttonSheet;
		// Button index
		int buttonIndex;
		// Button press ?
		bool press;
		// Just draw the background
		STexture background;
		// Singleton
		MainMenu();
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
		static MainMenu* Instance() {
			static MainMenu instance;
			return &instance;
		}
};

#endif
