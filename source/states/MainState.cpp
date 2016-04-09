#include "../../include/states/MainState.h"
#include "../../include/Define.h"
#include <iostream>
MainState::MainState() {
	fieldSheet.init("resources/field.png", 960, 540, 960, 540);
}

void MainState::Init(SDL_Renderer *screen) {
	totalTicks = 0;
	player.Init(0, 0, 0);
	middle_wall.Init(WIDTH / 2, 0, 20, HEIGHT);
	eList.push_back(&player);
	eList.push_back(&middle_wall);
}
void MainState::Cleanup() {
}

void MainState::Pause() {}
void MainState::Resume() {}

void MainState::Event(StateManager* game, SDL_Event event) {
    switch(event.type){
    default: player.handle_event(event);
    }
}

void MainState::Update(StateManager* game, int ticks) {
	totalTicks += ticks;
	player.Update(ticks);

	//check for collisions
	for (int j = 0; j < eList.size(); j++) {
		for (int k = j+1; k < eList.size(); k++) {
			if (check_collision(eList[j], eList[k])) {
				eList[j]->on_collision(eList[k]);
				eList[k]->on_collision(eList[j]);
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

	player.Draw(screen);
	middle_wall.Draw(screen);
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
	bottomA = a_size.y + a_size.width;

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
