#ifndef HIDDENSTATE_H_INCLUDED
#define HIDDENSTATE_H_INCLUDED

#include "GameState.h"
#include <stdio.h>
#include "../STexture.h"
#include "../SpriteSheet.h"
#include "../Player.h"
#include "../Entity.h"
#include "../Wall.h"
#include "../Disk.h"
#include <vector> //used for list of entities

class HiddenState : public GameState {
    private:
		int totalTicks;
		int discCounter;
		int nextX, nextY;
		// The sprite sheet
		SpriteSheet fieldSheet;
		// Player
		Player playerOne;

		Disk disk;
		// "SCORE"
		int score;
        //Singleton
        HiddenState();
		//list of entites
		std::vector<Entity*> eList;
    public:
        // Init and clean up
		void Init(SDL_Renderer*);
        void Cleanup();

        // Pause and resume
        void Pause();
        void Resume();

        // Main loop
        void Event(StateManager*, SDL_Event);
        void Update(StateManager*, int);
        void Draw(SDL_Renderer*);

        // Retrieve the instance
        static HiddenState* Instance() {
            static HiddenState instance;
            return &instance;
        }

		bool check_collision(Entity* A, Entity* B); //checks if A and B are colliding
};

#endif // MAINSTATE_H_INCLUDED
