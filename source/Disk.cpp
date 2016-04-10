#include "../include/Disk.h"
#include "../include/Define.h"
#include <math.h>

#define SPEED_THRESHOLD 100
Disk::Disk() {
	xVel = 0;
	yVel = 0;
	this->width = DISK_WIDTH;
	this->height = DISK_HEIGHT;
	LScore = NULL;
	RScore = NULL;

	sheet.init("resources/disc.png", 144, 144, 48, 48);
	Animation Idle;
	Idle.init("IDLE");
	Idle.addAnim(0, 2, 50);
	sheet.addAnim("IDLE", Idle);
	currentAnimation = sheet.getAnim("IDLE");
}

void Disk::Init(float x, float y, float xVel, float yVel) {
	this->x = x;
	this->y = y;
	this->xVel = xVel;
	this->yVel = yVel;
	this->on_player = false;

	currentAnimation = sheet.getAnim("IDLE");

	reset = false;
	grababble = false;
	if (xVel == 0 && yVel == 0)
		grababble = true; //if not moving its grabbable
}

void Disk::on_collision(Entity* other_ptr, int) {
	entity_type other_type = other_ptr->get_type();
	if (other_type == PLAYER && grababble) {
		//set velocity to 0 and wait for player to do stuff
		xVel = 0;
		yVel = 0;
		on_player = true;
	}
	else if (other_type == WALL) {
		//add check to allow disk through middle wall but still hit obsticales that it should hit

		//should never flip x dir hopefully maybe idk i program sometimes
		//yVel *= -1;

	}
	else if (other_type == GOAL) {
		//score stuff
		//xVel = 0;
		//yVel = 0;

		reset = true;

		if (other_ptr->get_size().x < WIDTH / 2)
			(*RScore)++;
		else
			(*LScore)++;

		// Bounce off goals to make hidden game work
		if (xVel < 0)
			x = other_ptr->get_size().x + other_ptr->get_size().width;
		else
			x = other_ptr->get_size().x - width;
		xVel *= -1;
	}
	else if (other_type == DISK){



		//how in the fuck did 2 disks get spawned and collide
	}
}

void Disk::Draw(SDL_Renderer *screen) {
	if (!on_player) {

		SDL_Rect dst;
		dst.x = x;
		dst.y = y;
		dst.w = width;
		dst.h = height;
		SDL_Rect src;
		if(currentAnimation!=NULL)
            src = sheet.getSprite(currentAnimation->getFrame(animTime));
        else
        {
            int a = 0;
            float ang = atan2(yVel,xVel)*180/3.14;
            if(ang > 0){
                if(ang < 22.5) a = 3;
                if(ang >= 22.5 && ang < 67.5) a = 5;
                if(ang >= 67.5 && ang < 112.5) a = 6;
                if(ang >= 112.5 && ang < 157.5) a = 4;
                if(ang >= 157.5 && ang < 180) a = 3;
            }
            else{
                if(ang > -22.5) a = 3;
                if(ang <= -22.5 && ang > -67.5) a = 4;
                if(ang <= -67.5 && ang > -112.5) a = 6;
                if(ang <= -112.5 && ang > -157.5) a = 5;
                if(ang <= -157.5 && ang > -180) a = 3;
            }

            src = sheet.getSprite(a);
        }
		SDL_RenderCopy(screen, sheet.getTexture(), &src, &dst);

		/*
		//!!!TMP
		SDL_Rect dst;
		dst.x = x;
		dst.y = y;
		dst.w = width;
		dst.h = height;
		SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
		SDL_RenderFillRect(screen, &dst);
		*/
	}
}

entity_type Disk::get_type(){
	return DISK;
}

void Disk::Update(int ticks) {
	if (!on_player) {
		if (xVel < SPEED_THRESHOLD && xVel > 0) {
			//going right
			xVel = SPEED_THRESHOLD;
		}
		else if (xVel > -SPEED_THRESHOLD && xVel < 0) {
			//going left
			xVel = -SPEED_THRESHOLD;
		}
		if (y < 0 || y > HEIGHT - height) {
			//flip velocity if went over edges
			yVel *= -1;
			// Rest the disk y if out of bounds
			y = y < 0 ? 0 : HEIGHT - height;
		}
		/*if(x<0){
            xVel*=-1;
            x = 0;
		}
		if(x>WIDTH-width){
            xVel*=-1;
            x = WIDTH-width;
		}*/

        float speed = sqrt(xVel*xVel + yVel*yVel);
        if(speed > 200){
            currentAnimation = NULL;
        }
        else{
            currentAnimation = sheet.getAnim("IDLE");
        }


		x += (xVel * ticks) / 1000.f; //ticks in ms so dived by 1000 for pixels per second
		y += (yVel * ticks) / 1000.f;

		//update grabable
		if (x > WIDTH / 2 && xVel > 0) {
			//crossed middle going right
			grababble = true;
		}
		else if (x < WIDTH / 2 - width && xVel < 0) {
			grababble = true;
		}

		animTime += ticks;
	}

}


bool Disk::can_grab() {
	return grababble;
}

void Disk::setScore(int *ls, int *rs) {
	LScore = ls;
	RScore = rs;
}

bool Disk::scored() {
	return reset;
}
