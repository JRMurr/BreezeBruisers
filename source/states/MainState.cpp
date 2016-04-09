#include "../../include/states/MainState.h"
#include "../../include/Define.h"
MainState::MainState() {
	fieldSheet.init("resources/field.png", 960, 540, 960, 540);
}

void MainState::Init(SDL_Renderer *screen) {
	totalTicks = 0;
	bool pone = true;
	for(int i = 0; i < SDL_NumJoysticks(); i++){
        if(SDL_IsGameController(i)){
            if(pone){
                playerOne.control = SDL_GameControllerOpen(i);
                if(playerOne.control){
                    pone = false;
                }
                else{
                    printf("Error with controller\n");
                }
            }
            else{
                playerTwo.control = SDL_GameControllerOpen(i);
                if(playerTwo.control){
                    break;
                }
                else{
                    printf("Error with controller\n");
                }
            }
        }
	}
	playerOne.Init(0, 0, 0);
	eList.push_back(&playerOne);
	playerTwo.Init(400,0,0);
	eList.push_back(&playerTwo);
}
void MainState::Cleanup() {
}

void MainState::Pause() {}
void MainState::Resume() {}

void MainState::Event(StateManager* game, SDL_Event event) {
    switch(event.type){
    default: playerOne.handle_event(event); playerTwo.handle_event(event);
    }
}

void MainState::Update(StateManager* game, int ticks) {
	totalTicks += ticks;
	playerOne.Update(ticks);
	playerTwo.Update(ticks);
}

void MainState::Draw(SDL_Renderer* screen) {
	SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
	SDL_RenderClear(screen);
	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = WIDTH;
	dst.h = HEIGHT;
	SDL_Rect src = fieldSheet.getSprite(0);
	SDL_RenderCopy(screen, fieldSheet.getTexture(), &src, &dst);

	playerOne.Draw(screen);
    playerTwo.Draw(screen);
	SDL_RenderPresent(screen);

}
