#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>

class Entity {
	protected:
		// Position
		float x, y;
		// Width, height
		int width, height;
		// TODO Sprite sheet
		// SpriteSheet *s;
	public:
		virtual void Update() = 0;
		virtual void Draw(SDL_Renderer*) = 0;
};

#endif