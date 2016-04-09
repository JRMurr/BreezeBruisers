#include "../include/Wall.h"


void Wall::Init(float x, float y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Wall::on_collision(Entity* other_ptr) {
	//IM A MOTHA FUCKIN WALL
	return;
}

void Wall::Draw(SDL_Renderer* screen) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
	SDL_RenderFillRect(screen, &dst);
}

entity_type Wall::get_type() {
	return WALL;
}

void Wall::Update(int ticks) {
	//STILL A MOTHA FUKIN WALL
	return;
}