#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>

enum entity_type{
	PLAYER,
	WALL,
	DISK
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
		// TODO Sprite sheet
		// SpriteSheet *s;

		entity_type eType; //entity type enum

	public:
		virtual void Update() = 0;
		virtual void Draw(SDL_Renderer*) = 0;
		entity_type get_type();
		virtual void on_collision(Entity* other) = 0; //deals with collison of other entity
		Size get_size();
};

#endif