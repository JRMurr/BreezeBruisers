#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <map>
#include "../include/STexture.h"
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include "../include/Animation.h"

class SpriteSheet
{
    public:
        SpriteSheet();
        void init(const char*, int tw, int th, int sw, int sh);
        virtual ~SpriteSheet();

        int getSWidth();
        int getSHeight();
        void addAnim(std::string, Animation);
        Animation* getAnim(std::string);
        SDL_Rect getSprite(int num);

		SDL_Texture *getTexture();

    protected:

    private:
		STexture tex;
		int totalWidth, totalHeight, spriteWidth, spriteHeight;
        int rows, cols;
        std::map<std::string, Animation> animationMap;
};

#endif // SPRITESHEET_H
