#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include <SDL.h>
#include "Entity.h"

class Wall : public Entity {
	public:
		void Init(float x, float y, int width, int height);
		void Update(int ticks);
		void Draw(SDL_Renderer*);
		entity_type get_type();
		void on_collision(Entity* other);
};

#endif 
