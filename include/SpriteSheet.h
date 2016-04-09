#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "../include/STexture.h"
#include <SDL.h>
#include <stdio.h>

class SpriteSheet
{
    public:
        SpriteSheet();
        void init(STexture*, int tw, int th, int sw, int sh);
        virtual ~SpriteSheet();

        STexture* tex;
        int totalWidth, totalHeight, spriteWidth, spriteHeight;

        SDL_Rect getSprite(int num);

    protected:

    private:
        int rows, cols;
};

#endif // SPRITESHEET_H
