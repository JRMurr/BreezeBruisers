#ifndef BREEZER1_H_INCLUDED
#define BREEZER1_H_INCLUDED

#include "../Player.h"

class Breezer1 : public Player {
	public:
		void Init(Size size, float walkSpeed, float dashSpeed, float dashDistance, float throwSpeed);
		void Draw(SDL_Renderer*);
};

#endif // PLAYER_H_INCLUDED