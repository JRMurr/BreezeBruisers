#ifndef DISK_H_INCLUDED
#define DISK_H_INCLUDED

#include <SDL.h>
#include "Entity.h"

#define DISK_WIDTH 16
#define DISK_HEIGHT 16

class Disk : public Entity {
	protected:
		float xVel;
		float yVel;
		//bool on_player; //used when collides with player so it wont be drawn
		// Pointers to the players scores
		int *LScore, *RScore;
		// if someone scored
		bool reset;
		bool grababble;
	public:
		Disk();
		void Init(float x, float y, float xVel, float yVel);
		void Update(int ticks);
		void Draw(SDL_Renderer*);
		void on_collision(Entity* other, int);
		entity_type get_type();
		void setScore(int*, int*);
		bool scored();
		bool can_grab();
		bool on_player;
};

#endif
