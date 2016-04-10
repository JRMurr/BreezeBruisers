#include "../../include/states/MainMenu.h"

// Just load background
MainMenu::MainMenu() {
	background.load("resources/menuBG.png");
	buttonSheet.load("resources/buttons.png");
	SDL_Rect offsets[2];
	// The button offsets
	offsets[0].x = 0;
	offsets[0].y = 0;
	offsets[0].w = 100;
	offsets[0].h = 100;
	offsets[1].x = 100;
	offsets[1].y = 0;
	offsets[1].w = 100;
	offsets[1].h = 100;
	Button first(offsets, MainState::Instance(), ((WIDTH) / 3) - offsets[0].w/2, (HEIGHT - 100));
	buttons.push_back(first);
	offsets[0].x = 0;
	offsets[0].y = 100;
	offsets[1].x = 100;
	offsets[1].y = 100;
	Button second(offsets, NULL, ((WIDTH) / 3)*2 - offsets[1].w/2, (HEIGHT - 100));
	buttons.push_back(second);
	buttonIndex = 0;
	press = false;
}

// Just do nothing
void MainMenu::Init(SDL_Renderer *screen) {
	buttonIndex = 0;
	press = false;
}

// Cleans up aka nothing for now
void MainMenu::Cleanup() {

}

// Pause and resume aka nothing
void MainMenu::Pause() {

}

void MainMenu::Resume() {
	press = false;
}

// Main loop
// event handling
void MainMenu::Event(StateManager *game, SDL_Event event) {
	int x, y;
	switch (event.type) {
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&x, &y);
			for (int n = 0; n < BUTTON_NUMBER; n++)
				if (x/SCALE > buttons[n].getX() && x/SCALE < buttons[n].getX() + buttons[n].getClip(0).w &&
					y/SCALE > buttons[n].getY() && y/SCALE < buttons[n].getY() + buttons[n].getClip(0).h) {
					buttonIndex = n;
					break;
				}
			break;
		case SDL_MOUSEBUTTONDOWN:
			press = event.button.button == SDL_BUTTON_LEFT;
		case SDL_KEYDOWN:
			SDL_Scancode code = event.key.keysym.scancode;
			if (code == SDL_SCANCODE_W)
				buttonIndex = buttonIndex > 0 ? buttonIndex - 1 : BUTTON_NUMBER - 1;
			else if (code == SDL_SCANCODE_S)
				buttonIndex = (buttonIndex + 1) % BUTTON_NUMBER;
			else if (code == SDL_SCANCODE_RETURN)
				press = true;
            else if(code == SDL_SCANCODE_H)
                game->PushState(HiddenState::Instance());
	}
}
// update TODO idk yet
void MainMenu::Update(StateManager *game, int ticks) {
	if (press && buttons[buttonIndex].getGameState())
		game->PushState(buttons[buttonIndex].getGameState());
	else if (press && !buttons[buttonIndex].getGameState())
		game->Quit();
}
// Draw the background and the buttons
void MainMenu::Draw(SDL_Renderer *screen) {
	// Clear the screen
	SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
	SDL_RenderClear(screen);

	// background
	SDL_RenderCopy(screen, background, NULL, NULL);
	// draw buttons
	for (int n = 0; n < BUTTON_NUMBER; n++) {
		int selected = buttonIndex == n ? 1 : 0;
		SDL_Rect src{ buttons[n].getClip(selected).x, buttons[n].getClip(selected).y, buttons[n].getClip(selected).w, buttons[n].getClip(selected).h };
		SDL_Rect dst{ buttons[n].getX(), buttons[n].getY(), buttons[n].getClip(selected).w, buttons[n].getClip(selected).h };
		SDL_RenderCopy(screen, buttonSheet, &src, &dst);
	}
}

