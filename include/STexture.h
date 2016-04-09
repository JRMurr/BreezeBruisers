#ifndef STEXTURE_H
#define STEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

// My sdl texture wrapper
class STexture {
	private:
		// The texture
		SDL_Texture *texture;
		// The dimentions
		int width, height;
	public:
		// Initializes
		STexture();
		// Destroys the texture
		~STexture();

		// Create a blank texture
		bool create(int, int, int);
		// Load a texture form a file
		bool load(const char*);
		/// Free the texture
		void free();

		// The implicit cast to a texture
		operator SDL_Texture*();

		// Getters
		int getWidth();
		int getHeight();
};


#endif