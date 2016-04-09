#ifndef MAINSTATE_H_INCLUDED
#define MAINSTATE_H_INCLUDED

#include "GameState.h"
#include <stdio.h>
#include "../STexture.h"
#include "../SpriteSheet.h"
#include "../Player.h"
#include "../Entity.h"
#include "../Wall.h"
#include <vector> //used for list of entities 

class MainState : public GameState {
    private:
		int totalTicks;
		// The sprite sheet
		SpriteSheet fieldSheet;
		// Player
		Player playerOne;
		Player playerTwo;

		//Middle Wall
		Wall middle_wall;
        //Singleton
        MainState();
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
        static MainState* Instance() {
            static MainState instance;
            return &instance;
        }

		bool check_collision(Entity* A, Entity* B); //checks if A and B are colliding
};

#endif // MAINSTATE_H_INCLUDED
