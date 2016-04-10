#ifndef MAINSTATE_H_INCLUDED
#define MAINSTATE_H_INCLUDED

#include "GameState.h"
#include <stdio.h>
#include "../STexture.h"
#include "../SpriteSheet.h"
#include "../Player.h"
#include "../Entity.h"
#include "../Wall.h"
#include "../Disk.h"
#include "../Goal.h"
#include <vector> //used for list of entities

class MainState : public GameState {
    private:
		int totalTicks;
		// The sprite sheet
		SpriteSheet fieldSheet;
		SpriteSheet numberSheet;
		// Player
		Player playerOne;
		Player playerTwo;
		// Middle wall
		Wall middle_wall;
		// The disk
		Disk disk;
		// The goals
		Goal goals[2];
		int leftScore, rightScore;
		// Serve
		bool serve;
        //Singleton
        MainState();
		//list of entites
		std::vector<Entity*> eList;
    public:
        Mix_Chunk* hitOne = NULL;
        Mix_Chunk* hitTwo = NULL;
        Mix_Chunk* scoreMusic = NULL;
        Mix_Music* bgmusic = NULL;
        // Init and clean up
		void Init(SDL_Renderer*);
		void reset();
        void Cleanup();

        // Pause and resume
        void Pause();
        void Resume();

        // Main loop
        void Event(StateManager*, SDL_Event);
        void Update(StateManager*, int);
        void Draw(SDL_Renderer*);
        void DrawScore(SDL_Renderer*);
        // Retrieve the instance
        static MainState* Instance() {
            static MainState instance;
            return &instance;
        }

		bool check_collision(Entity* A, Entity* B); //checks if A and B are colliding
};

#endif // MAINSTATE_H_INCLUDED
