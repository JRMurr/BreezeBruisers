#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include "../STexture.h"
#include "../states/GameState.h"

// Basically a texture with a callback function
class Button {
	private:
		// Button position
		int x, y;
		// The button clips in the button sprite sheet MAYBE 0 default 1 highlighted
		SDL_Rect clips[2];
		// The gamestate to switch to
		GameState *state;
	public:
		// Constructor
		Button(SDL_Rect*, GameState*, int, int);
		void Init(SDL_Rect*, GameState*, int, int);
		// get Clip
		SDL_Rect getClip(int);
		// Get gamestate
		GameState *getGameState();
		// Get x and y
		int getX();
		int getY();
};

#endif