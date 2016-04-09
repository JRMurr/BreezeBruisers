#include "../include/Disk.h"
#include "../include/Define.h"
Disk::Disk() {
	xVel = 0;
	yVel = 0;
	this->width = DISK_WIDTH;
	this->height = DISK_HEIGHT;
}

void Disk::Init(float x, float y, float xVel, float yVel) {
	this->x = x;
	this->y = y;
	this->xVel = xVel;
	this->yVel = yVel;
}

void Disk::on_collision(Entity* other_ptr) {
	entity_type other_type = other_ptr->get_type();
	if (other_type == PLAYER) {
		//set velocity to 0 and wait for player to do stuff
		xVel = 0;
		yVel = 0;
	}
	else if (other_type == WALL) {
		//add check to allow disk through middle wall but still hit obsticales that it should hit

		//should never flip x dir hopefully maybe idk i program sometimes
		//yVel *= -1;

	}
	else if (other_type == GOAL) {
		//score stuff
		xVel = 0;
		yVel = 0;
	}
	else {
		//how in the fuck did 2 disks get spawned and collide
	}
}

void Disk::Draw(SDL_Renderer *screen) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_Rect src = sheet.getSprite(currentAnimation->getFrame(animTime));
	SDL_RenderCopy(screen, sheet.getTexture(), &src, &dst);
}

entity_type Disk::get_type(){
	return DISK;
}

void Disk::Update(int ticks) {
	if (y < 0 || y > HEIGHT - height) {
		//flip velocity if went over edges
		yVel *= -1;
		// Rest the disk y if out of bounds
		y = y < 0 ? 0 : HEIGHT - height;
	}

	x += (xVel * ticks) / 1000.f; //ticks in ms so dived by 1000 for pixels per second
	y += (yVel * ticks) / 1000.f;

	animTime += ticks;
}

