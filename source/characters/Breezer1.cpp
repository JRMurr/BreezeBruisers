#include "..\..\include\characters\Breezer1.h"

void Breezer1::Init(Size size, float walkSpeed, float dashSpeed, float dashDistance, float throwSpeed){
	x = size.x;
	y = size.y;
	width = size.width;
	height = size.height;
	walk_speed = walkSpeed;
	dash_speed = dashSpeed;
	throw_speed = throwSpeed;

	has_disk = false;
	time_disk_held = 0;
	using_controller = false; //TMP!!!!! FIX !!!!! 
	dash_distance_travled = 0;

	xVel = 0;
	yVel = 0;

	//controls wasd + space for throw, e for lob and Lshift for special
	inputs[UP] = SDLK_w;
	inputs[DOWN] = SDLK_s;
	inputs[LEFT] = SDLK_a;
	inputs[RIGHT] = SDLK_d;
	inputs[THROW] = SDLK_SPACE;
	inputs[LOB] = SDLK_e;
	inputs[SPECIAL] = SDLK_LSHIFT;
}


void Breezer1::Draw(SDL_Renderer *){
}
