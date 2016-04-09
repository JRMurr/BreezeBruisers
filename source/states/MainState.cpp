#include "../../include/states/MainState.h"
#include "../../include/Define.h"
#include <iostream>
MainState::MainState() {
	fieldSheet.init("resources/field.png", 960, 540, 960, 540);
}

void MainState::Init(SDL_Renderer *screen) {
	totalTicks = 0;
	middle_wall.Init(WIDTH / 2 - 10, 0, 20, HEIGHT);
	eList.push_back(&middle_wall);
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

	//tmp disk stuff
	disk.Init(5, HEIGHT / 2, 20, 100);
	eList.push_back(&disk);
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
	disk.Update(ticks);

	//check for collisions
	for (int j = 0; j < eList.size(); j++) {
		for (int k = j+1; k < eList.size(); k++) {
			if (check_collision(eList[j], eList[k])) {
				eList[j]->on_collision(eList[k], ticks);
				eList[k]->on_collision(eList[j], ticks);
				//std::cout << "dank" << "\n";
			}
		}
	}
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

	middle_wall.Draw(screen);
	playerOne.Draw(screen);
    playerTwo.Draw(screen);
	disk.Draw(screen);
	SDL_RenderPresent(screen);

}

bool MainState::check_collision(Entity * A, Entity * B){
	//The sides of the rectangles
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	Size a_size = A->get_size();
	Size b_size = B->get_size();

	//Calculate the sides of rect A
	leftA = a_size.x;
	rightA = a_size.x + a_size.width;
	topA = a_size.y;
	bottomA = a_size.y + a_size.height;

	//Calculate the sides of rect B
	leftB = b_size.x;
	rightB = b_size.x + b_size.width;
	topB = b_size.y;
	bottomB = b_size.y + b_size.height;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
