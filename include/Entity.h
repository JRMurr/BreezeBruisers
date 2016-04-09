#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "SpriteSheet.h"
#include "Animation.h"

enum entity_type{
	PLAYER,
	WALL,
	DISK,
	GOAL
};


struct Size {
	float x, y, width, height;
};

class Entity {
	protected:
		// Position
		float x, y;
		// Width, height
		int width, height;
		// Sprite sheet
		SpriteSheet sheet;

		int animTime = 0;
        Animation* currentAnimation;
	public:
		virtual void Update(int ticks) = 0;
		virtual void Draw(SDL_Renderer*) = 0;
		virtual entity_type get_type() = 0;
		virtual void on_collision(Entity* other) = 0; //deals with collison of other entity
		Size get_size();
};

#endif
