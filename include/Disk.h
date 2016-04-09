#ifndef DISK_H_INCLUDED
#define DISK_H_INCLUDED

#include <SDL.h>
#include "Entity.h"

#define DISK_WIDTH 32
#define DISK_HEIGHT 32

class Disk : public Entity {
	protected:
		float xVel;
		float yVel;

	public:
		Disk();
		void Init(float x, float y, float xVel, float yVel);
		void Update(int ticks);
		void Draw(SDL_Renderer*);
		void on_collision(Entity* other);
		entity_type get_type();
};

#endif 