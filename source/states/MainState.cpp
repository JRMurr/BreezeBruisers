#include "../../include/states/MainState.h"

MainState::MainState() {
	//spriteSheet.load("resources/test.png");
}

void MainState::Init(SDL_Renderer *screen) {
	totalTicks = 0;
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
	//SDL_RenderCopy(screen, spriteSheet, NULL, NULL);
}
