#include "../include/SpriteSheet.h"

void SpriteSheet::init(STexture* t, int tw, int th, int sw, int sh)
{
    tex = t;
    if(tex == NULL){
        printf("WARNING: SpriteSheet texture null");
    }
    totalWidth = tw;
    totalHeight = th;
    spriteWidth = sw;
    spriteHeight = sh;

    cols = totalWidth/spriteWidth;
    rows = totalHeight/spriteHeight;

    //ctor
}
SpriteSheet::SpriteSheet(){
    tex = NULL;
}

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

