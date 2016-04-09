#include "../../include/states/MainState.h"

MainState::MainState() {
	spriteSheet.load("resources/sprites.png");
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
	SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
	SDL_RenderClear(screen);
}
