#include "../../include/utilities/Button.h"

// Copy the clips and the gamestate
Button::Button(SDL_Rect *clips, GameState *state, int x, int y) {
	Init(clips, state, x, y);
}

void Button::Init(SDL_Rect *clips, GameState *state, int x, int y) {
	this->state = state;
	for (int n = 0; n < 2; n++)
		this->clips[n] = clips[n];
	this->x = x;
	this->y = y;
}

// get Clips
SDL_Rect Button::getClip(int index) {
	return clips[index % 2];
}

// Get gamestate
GameState *Button::getGameState() {
	return state;
}

int Button::getX() { return x; }
int Button::getY() { return y; }