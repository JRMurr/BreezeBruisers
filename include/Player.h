#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SDL.h>
#include "Entity.h"


class Player : public Entity {
	protected:
		SDL_Event event; //for input from state manager
		bool using_controller; 
		bool has_disk; //player will act differntly when holding disk
		float walk_speed, dash_speed, dash_distance; //movement varibales
		bool is_dashing; //check to make sure player doesnt break out of dash animation
		float dash_distance_travled; //used to keep track of how long the dash has been going

		float throw_speed;	  //base throw speed of the character
		float time_disk_held; //used as modifer to make disk thrown slower the longer its held
	public:
		virtual void Update() = 0;
		virtual void Draw(SDL_Renderer*) = 0;
		void move_player(float input_dir_x, float input_dir_y, int ticks);
		//void player_dash(float input_dir_x, float input_dir_y, int ticks);
};

#endif // PLAYER_H_INCLUDED
