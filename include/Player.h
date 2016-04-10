#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SDL.h>
#include "Entity.h"
#include "characters/Character.h"
#include "Disk.h"

enum generic_input {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	THROW,
	LOB,
	SPECIAL
};

class Player : public Entity {
	protected:
		//SDL_Event event; //for input from state manager
		SDL_Scancode inputs[7]; //7 since thats how many inputs there are
		// Which character they are
		int character;
		//bool has_disk; //player will act differntly when holding disk
		Disk* disk;
		bool is_dashing; //check to make sure player doesnt break out of dash animation
		float dash_distance_travled; //used to keep track of how long the dash has been going

		float throw_speed;	  //base throw speed of the character
		float time_disk_held; //used as modifer to make disk thrown slower the longer its held

		float xVel;
		float yVel;

	public:
		// Initialize player
		Player();
		SDL_GameController* control;
		void Init(float, float, int);
		void Update(int ticks);
		void Draw(SDL_Renderer*);
		void move_player(float input_dir_x, float input_dir_y);
		void on_collision(Entity* other, int); //player deals with collison of other entity
		void handle_event(SDL_Event event);
		void initAnimations();
		bool using_controller();
		void setInputs(SDL_Scancode*);
		entity_type get_type();
		//void player_dash(float input_dir_x, float input_dir_y, int ticks);
};

#endif // PLAYER_H_INCLUDED
