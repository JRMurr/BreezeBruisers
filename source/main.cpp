#include <SDL.h>
#include "../include/states/StateManager.h"
#include "../include/states/MainState.h"
#include "../include/states/MainMenu.h"

int main(int argc, char** argv) {
	StateManager game;
	if (game.Init() != 0) {
		printf("An error occured during init");
		game.Quit();
	}
	game.PushState(MainMenu::Instance());
	while (!game.quitting()) {
		game.Event();
		game.Update();
		game.Draw();
	}
	game.Cleanup();

	return 0;
}