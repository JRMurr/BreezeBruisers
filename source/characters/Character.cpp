#include "../../include/characters/Character.h"
//w,h,walkspeed,dashspeed,throwspeed
static Character Breezer1{ "B1", "resources/Monster-squirrel.png", 32, 32, 200, 500, 400, 0 };
static Character Breezer2{ "B2", "resources/Monster-squirrel.png", 32, 32, 150, 600, 500, 0 };
Character Character::CharArray[NUM_CHARACTERS] = { Breezer1, Breezer2 };