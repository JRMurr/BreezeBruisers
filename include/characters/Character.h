#ifndef CHARACTER_H
#define CHARACRER_H

// Sepecial move function pointer	TODO figure this stuff out
typedef void (*Special)(void);

// Constansts for each character
struct Character {
	// Character name
	const char *name;
	// Character sprite sheet
	const char *sheetPath;
	// Player dimension
	int width, height;
	// Player Movement stuff
	float walkSpeed, dashSpeed;
	// Special move function pointer	TODO actually figure out
	Special spec;
};

// Number of characters
enum Char_enum{
	BREEZER1,
	NUM_CHARACTERS
};
// Array of characters used to look up character data
//const Character CharArray[];

#endif