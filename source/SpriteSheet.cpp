#include "../include/SpriteSheet.h"

void SpriteSheet::init(const char *texture_path, int tw, int th, int sw, int sh)
{
	if (!tex.load(texture_path)){
        printf("WARNING: SpriteSheet texture failed to load");
    }
    totalWidth = tw;
    totalHeight = th;
    spriteWidth = sw;
    spriteHeight = sh;

    cols = totalWidth/spriteWidth;
    rows = totalHeight/spriteHeight;

    //ctor
}
SpriteSheet::SpriteSheet(){}

SpriteSheet::~SpriteSheet()
{
    //
}

SDL_Rect SpriteSheet::getSprite(int num){
    SDL_Rect r;
    r.x = (num%cols)*spriteWidth;
    r.y = (num/rows)*spriteHeight;
    r.w = spriteWidth;
    r.h = spriteHeight;

    return r;
}

SDL_Texture *SpriteSheet::getTexture() { return tex; }

