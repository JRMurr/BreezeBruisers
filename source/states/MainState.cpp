#include "../../include/states/MainState.h"

MainState::MainState() {
<<<<<<< HEAD
	//spriteSheet.load("resources/test.png");
=======
	fieldTexture.load("resources/field.png");
>>>>>>> 064a23abbf61ce69e633ae5978c6361f942346ee
}

void MainState::Init(SDL_Renderer *screen) {
	totalTicks = 0;
	fieldSheet.init(&fieldTexture,960,540,32,32);
}
void MainState::Cleanup() {
}

void MainState::Pause() {}
void MainState::Resume() {}

void MainState::Event(StateManager* game, SDL_Event event) {

}

void MainState::Update(StateManager* game, int ticks) {
	totalTicks += ticks;
}

void MainState::Draw(SDL_Renderer* screen) {
	SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
	SDL_RenderClear(screen);
<<<<<<< HEAD
	//SDL_RenderCopy(screen, spriteSheet, NULL, NULL);
=======
	SDL_Rect dst;
	dst.x = 20;
	dst.y = 100;
	dst.w = 100;
	dst.h = 100;
	SDL_Rect src = fieldSheet.getSprite(0);
	SDL_RenderCopy(screen,fieldTexture,&src,&dst);
	SDL_RenderPresent(screen);
>>>>>>> 064a23abbf61ce69e633ae5978c6361f942346ee
}
