#include "../include/SpriteSheet.h"
#include <string>
#include <map>


typedef std::map<std::string, int> Map;
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
void SpriteSheet::addAnim(std::string n, Animation a){
    animationMap[n] = a;
}
Animation* SpriteSheet::getAnim(std::string n){
    return &(animationMap[n]);
}
SpriteSheet::SpriteSheet(){}

SpriteSheet::~SpriteSheet()
{
    //
}
int SpriteSheet::getSWidth(){return spriteWidth;}
int SpriteSheet::getSHeight(){return spriteHeight;}
SDL_Rect SpriteSheet::getSprite(int num){
    SDL_Rect r;
    if(rows == 1){
        r.x = (num/rows)*spriteWidth;
        r.y = (num%rows)*spriteHeight;
    }
    else{
        r.x = (num%rows)*spriteWidth;
        r.y = (num/rows)*spriteHeight;
    }
    r.w = spriteWidth;
    r.h = spriteHeight;

    return r;
}


SDL_Texture *SpriteSheet::getTexture() { return tex; }

