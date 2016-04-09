#ifndef DISK_H_INCLUDED
#define DISK_H_INCLUDED

#include <SDL.h>
#include "Entity.h"

#define DISK_WIDTH
#define DISK_HEIGHT

class Disk : public Entity {
	protected:
		float xVel;
		float yVel;

		bool player_one_threw; //used to check who threw the disk for scoreing
	public:
		Disk();
		void Init(float x, float y, float xVel, float yVel, bool is_player_one); //bool is for keeping track who threw
		void Update(int ticks);
		void Draw(SDL_Renderer*);
		void on_collision(Entity* other);
		entity_type get_type();
		bool did_player_one_throw();
};

#endif 