#include "../../include/characters/Character.h"

static Character Breezer1{ "B1", "resources/Monster-squirrel.png", 32, 32, 300, 600, 0 };
static Character Breezer2{ "B2", "resources/Monster-squirrel.png", 32, 32, 150, 600, 0 };
Character Character::CharArray[NUM_CHARACTERS] = { Breezer1, Breezer2 };