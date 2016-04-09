#include "../../include/states/StateManager.h"

#include "../../include/states/GameState.h"

#include "../../include/STexture.h"

SDL_Renderer *StateManager::screen = NULL;

//!!!!@@@TODO check for collisions and call on_collision on the correct entities


// Initiate game
int StateManager::Init() {
    // Initiate video   TODO initialize everything
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    if(SDL_Init(SDL_INIT_GAMECONTROLLER)<0){
        printf( "Unable to init gamecontroller: %s\n", SDL_GetError() );
        return 1;
    }
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		printf("Unable to init SDL image: %s\n", IMG_GetError());
		return 1;
	}

    window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, WIDTH * SCALE, HEIGHT * SCALE, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return false;
    }

	screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(screen, 0, 0, 0, 0xFF);

	target.create(WIDTH, HEIGHT, SDL_TEXTUREACCESS_TARGET);

    frame_timer.start();

	totalTicks = 0;

	frames = 0;

    quit = false;

    return 0;
}

// Clean up the game
int StateManager::Cleanup() {
    while(!states.empty()) {
        states.top()->Cleanup();
        states.pop();
    }
	SDL_DestroyRenderer(screen);
    SDL_DestroyWindow(window);
	screen = NULL;
	window = NULL;

    SDL_Quit();

    printf("exited cleanly!");

    return 0;
}

// Pop the current state and start a new one
void StateManager::ChangeState(GameState *state) {
    if(!states.empty()) {
        states.top()->Cleanup();
        states.pop();
    }
    states.push(state);
	states.top()->Init(screen);
}

// Return quit
bool StateManager::quitting() {return quit;}

// Quit
void StateManager::Quit() {quit = true;}

// Pause and push state to stack and start new state
void StateManager::PushState(GameState *state) {
    if(!states.empty()) {
        states.top()->Pause();
    }
    states.push(state);
    states.top()->Init(screen);
}

// Delete current state and pop and resume previous state
void StateManager::PopState(int times = 1) {
    while (times > 0) {
        if(!states.empty()) {
            states.top()->Cleanup();
            states.pop();
        }
        if(!states.empty()) {
            states.top()->Resume();
        }
    times--;
    }
}

// Event handeler
void StateManager::Event() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {

            case SDL_QUIT:
                quit = true;
                break;
        }
        if(!states.empty()) {
            states.top()->Event(this, event);
        }
    }
}

// Update
void StateManager::Update() {
    if(!states.empty()) {
        states.top()->Update(this, frame_timer.get_ticks());
    }
}

// Draw
void StateManager::Draw() {
	totalTicks += frame_timer.get_ticks();
    frame_timer.start();
	SDL_SetRenderTarget(screen, target);
    if(!states.empty()) {
        states.top()->Draw(screen);
    }
	SDL_SetRenderTarget(screen, NULL);
	SDL_RenderCopy(screen, target, NULL, NULL);
	SDL_RenderPresent(screen);
	// FPS stuff
	frames++;
	// Cap rate	MAYBE
	/*if (frame_timer.get_ticks() < (1000/60))
		SDL_Delay((1000/60) - frame_timer.get_ticks());*/
	int fps = (frames/ (totalTicks/1000.f));
	/*
	std::stringstream title;
	title.str("");
	title << "Connect 4";// << fps;
	*/
	SDL_SetWindowTitle(window, "Breeze Bruisers");
}
