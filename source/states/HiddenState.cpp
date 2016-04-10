#include "../../include/states/HiddenState.h"
#include "../../include/Define.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
HiddenState::HiddenState() {
	fieldSheet.init("resources/field.png", 960, 540, 960, 540);
	numberSheet.init("resources/numbers.png",320,64,32,64);
}

void HiddenState::Init(SDL_Renderer *screen) {
	totalTicks = 0;
	bool pone = true;
	for(int i = 0; i < SDL_NumJoysticks(); i++){
        if(SDL_IsGameController(i)){
            if(pone){
                playerOne.control = SDL_GameControllerOpen(i);
                if(playerOne.control){
                    break;
                }
                else{
                    printf("Error with controller\n");
                }
            }
        }
	}
	playerOne.Init(0, 136, 0);

	goals[0].Init(-1, 0, 1, HEIGHT);
	goals[1].Init(WIDTH, 0, 1, HEIGHT);


	//tmp disk stuff
	float angle = (rand() % (360))* 3.14159265 / 180;
	nextX = rand() % 430;
	nextY = rand() % 280;


	disk.Init(220, 150, cos(angle)*250, sin(angle)*250);
	disk.setScore(&score, &score);
	discCounter = 1;

	eList.push_back(&playerOne);
	eList.push_back(&disk);
	eList.push_back(&goals[0]);
	eList.push_back(&goals[1]);
}
void HiddenState::Cleanup() {
	while (!eList.empty())
		eList.pop_back();
}

void HiddenState::Pause() {}
void HiddenState::Resume() {}

void HiddenState::Event(StateManager* game, SDL_Event event) {
    switch(event.type){
    default: playerOne.handle_event(event);
    }
}

void HiddenState::Update(StateManager* game, int ticks) {
	totalTicks += ticks;
	if((totalTicks/5000) + 1 > discCounter){
        Disk* d = new Disk;
        float angle = (rand() % (360))* 3.14159265 / 180;
        d->Init(nextX,nextY, cos(angle)*250, sin(angle)*250);
		d->setScore(&score, &score);
        nextX = rand() % 430;
        nextY = rand() % 280;
        eList.push_back(d);
        discCounter++;
        printf("made disc %d\n",(totalTicks/2)%5000 + 1 );
	}
	for(int i = 0; i < eList.size(); i++){
        eList[i]->Update(ticks);
	}

	//check for collisions
	for (int j = 0; j < eList.size(); j++) {
		for (int k = j+1; k < eList.size(); k++) {
			if (check_collision(eList[j], eList[k])) {
				eList[j]->on_collision(eList[k], ticks);
				eList[k]->on_collision(eList[j], ticks);
				if (eList[j]->get_type() == PLAYER || eList[k]->get_type() == PLAYER)
					game->PopState(1);
				//std::cout << "dank" << "\n";
			}
		}
	}
}

void HiddenState::Draw(SDL_Renderer* screen) {
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
    for(int i = 0; i < eList.size(); i++){
        eList[i]->Draw(screen);
	}

    SDL_Rect next;
    next.x = nextX;
    next.y = nextY;
    next.w = 16;
    next.h = 16;
    SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
    SDL_RenderFillRect(screen, &next);
	SDL_RenderPresent(screen);

}

bool HiddenState::check_collision(Entity * A, Entity * B){
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
void HiddenState::DrawScore(SDL_Renderer* screen){
    SDL_Rect dst;
    SDL_Rect src;
	dst.x = (WIDTH/2)-numberSheet.getSWidth();
	dst.y = (HEIGHT-numberSheet.getSHeight())/2;
	dst.w = numberSheet.getSWidth();
	dst.h = numberSheet.getSHeight();
	src = numberSheet.getSprite(discCounter/10);
    SDL_RenderCopy(screen, numberSheet.getTexture(),&src,&dst);
    dst.x = (WIDTH/2);
    src = numberSheet.getSprite(discCounter%10);
    SDL_RenderCopy(screen, numberSheet.getTexture(),&src,&dst);

}
