#include "../include/STexture.h"

#include "../include/states/StateManager.h"

// The constructor
STexture::STexture() {
	texture = NULL;
	width = 0;
	height = 0;
}

// Destroy the texture
STexture::~STexture() {
	SDL_DestroyTexture(texture);
}

// Create a blank texture
bool STexture::create(int w, int h, int texture_access = SDL_TEXTUREACCESS_STREAMING) {
	// Create the texture 
	texture = SDL_CreateTexture(StateManager::screen, SDL_PIXELFORMAT_RGBA8888, texture_access, w, h);
	if (texture == NULL)
		return false;
	width = w;
	height = h;
	return true;
}

// Load a texture form a file
bool STexture::load(const char *file) {
	// Load the image and check
	SDL_Surface *img = IMG_Load(file);
	if (img == NULL) {
		printf("Unable to load texture: %s\n", IMG_GetError());
		return false;
	}

	// Convert the surface to a texture
	texture = SDL_CreateTextureFromSurface(StateManager::screen, img);
	if (texture == NULL) {
		printf("Unable to convert the surface to a texture: %s\n", SDL_GetError());
		return false;
	}

	width = img->w;
	height = img->h;

	SDL_FreeSurface(img);

	return true;
}

// Destroy the texture
void STexture::free() {
	SDL_DestroyTexture(texture);
	width = 0;
	height = 0;
}

// Cast to a SDL_Texture*
STexture::operator SDL_Texture *() {
	return texture;
}

// Getters
int STexture::getWidth() { return width; }
int STexture::getHeight() { return height; }