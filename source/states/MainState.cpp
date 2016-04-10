#include "../../include/states/MainState.h"
#include "../../include/Define.h"
#include <iostream>

#define WAIT_TIME 500
#define SCORE_LIMIT 15
MainState::MainState() {
	middle_wall.Init(WIDTH / 2 - 10, 0, 20, HEIGHT);
	eList.push_back(&middle_wall);
	bool pone = true;
	for (int i = 0; i < SDL_NumJoysticks(); i++){
		if (SDL_IsGameController(i)){
			if (pone){
				playerOne.control = SDL_GameControllerOpen(i);
				if (playerOne.control){
					pone = false;
				}
				else{
					printf("Error with controller\n");
				}
			}
			else{
				playerTwo.control = SDL_GameControllerOpen(i);
				if (playerTwo.control){
					break;
				}
				else{
					printf("Error with controller\n");
				}
			}
		}
	}
	eList.push_back(&playerOne);
	eList.push_back(&playerTwo);
	eList.push_back(&goals[0]);
	eList.push_back(&goals[1]);
	eList.push_back(&disk);

	// initialize the goals
	// Left then right
	goals[0].Init(-DISK_WIDTH/2-1, 0, 1, HEIGHT);
	goals[1].Init(WIDTH + DISK_WIDTH/2, 0, 1, HEIGHT);

	disk.setScore(&leftScore, &rightScore);

	fieldSheet.init("resources/field.png", 960, 540, 960, 540);
	numberSheet.init("resources/numbers.png",320,64,32,64);

	
}

void MainState::Init(SDL_Renderer *screen) {
	totalTicks = 0;

	playerOne.Init(0, (HEIGHT - playerOne.get_size().height)/2, 0);
	playerTwo.Init(400, (HEIGHT - playerTwo.get_size().height) / 2, 1);
	if (!playerTwo.using_controller()) {
		SDL_Scancode inputs[SPECIAL + 1] = {
			SDL_SCANCODE_UP,
			SDL_SCANCODE_DOWN,
			SDL_SCANCODE_LEFT,
			SDL_SCANCODE_RIGHT,
			SDL_SCANCODE_RSHIFT
		};
		// TODO other keys
		playerTwo.setInputs(inputs);
	}
	//tmp disk stuff
	leftScore = 0, rightScore = 0;
	disk.Init(0, HEIGHT / 2 - playerOne.get_size().height/2 +3, 0, 0);
	playerOne.wait(WAIT_TIME);
	playerTwo.wait(WAIT_TIME);
}

void MainState::reset() {
	playerOne.Init(0, (HEIGHT - playerOne.get_size().height) / 2, 0);
	playerTwo.Init(400, (HEIGHT - playerTwo.get_size().height) / 2, 0);
	if (!playerTwo.using_controller()) {
		SDL_Scancode inputs[SPECIAL + 1] = {
			SDL_SCANCODE_UP,
			SDL_SCANCODE_DOWN,
			SDL_SCANCODE_LEFT,
			SDL_SCANCODE_RIGHT,
			SDL_SCANCODE_RSHIFT
		};
		// TODO other keys
		playerTwo.setInputs(inputs);
	}
	if (serve)
		disk.Init(0, HEIGHT / 2 - playerOne.get_size().height / 2, 0, 0);
	else
		disk.Init(WIDTH - playerTwo.get_size().width + 1, HEIGHT / 2 - playerTwo.get_size().height / 2, 0, 0);

	playerOne.wait(WAIT_TIME);
	playerTwo.wait(WAIT_TIME);
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

	if (disk.scored()) {
		serve = disk.get_size().x < WIDTH / 2;
		reset();
	}
	if (leftScore >= SCORE_LIMIT || rightScore >= SCORE_LIMIT) {
		game->PopState(1);
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

    DrawScore(screen);

	middle_wall.Draw(screen);
	playerOne.Draw(screen);
    playerTwo.Draw(screen);
	disk.Draw(screen);
	SDL_RenderPresent(screen);

}
void MainState::DrawScore(SDL_Renderer* screen){
    SDL_Rect dst;
    SDL_Rect src;
	dst.x = (WIDTH/3)-numberSheet.getSWidth();
	dst.y = (HEIGHT-numberSheet.getSHeight())/2;
	dst.w = numberSheet.getSWidth();
	dst.h = numberSheet.getSHeight();
	src = numberSheet.getSprite(leftScore/10);
    SDL_RenderCopy(screen, numberSheet.getTexture(),&src,&dst);
    dst.x = (WIDTH/3);
    src = numberSheet.getSprite(leftScore%10);
    SDL_RenderCopy(screen, numberSheet.getTexture(),&src,&dst);
    dst.x = (WIDTH*2/3)-numberSheet.getSWidth();
    src = numberSheet.getSprite(rightScore/10);
    SDL_RenderCopy(screen, numberSheet.getTexture(),&src,&dst);
    dst.x = (WIDTH*2/3);
    src = numberSheet.getSprite(rightScore%10);
    SDL_RenderCopy(screen, numberSheet.getTexture(),&src,&dst);
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
