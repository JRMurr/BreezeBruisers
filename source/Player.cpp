#include "../include/Player.h"
#include <math.h>       /* sqrt  and pow*/

void Player::move_player(float input_dir_x, float input_dir_y, int ticks) {
	if (is_dashing) {
		//do dash stuff
		if (dash_distance_travled < dash_distance) {
			//only do stuff if still need to move more
			float x_distance = (input_dir_x * dash_speed * ticks) / 1000.f;
			float y_distance = (input_dir_y * dash_speed * ticks) / 1000.f;
			dash_distance_travled += sqrt(pow(x_distance, 2) + pow(y_distance, 2)); //based pythag thereom, good shit right there (chorus right there)
			x += x_distance;
			y += y_distance;
		}
		else {
			//reset dash variables since dash distance has been covered
			dash_distance_travled = 0;
			is_dashing = false;
		}
	}
	else {
		//regular movement
		x += ((input_dir_x * walk_speed * ticks) / 1000.f); //ticks is miliseconds so divide by 1000
		y += ((input_dir_y * walk_speed * ticks) / 1000.f);
	}
}