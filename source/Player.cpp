#include "../include/Player.h"
#include <math.h>       /* sqrt  and pow*/

void Player::move_player(float input_dir_x, float input_dir_y) {
	if (has_disk)
		return; //dont move when has disk
	if (is_dashing) {

		//!!!FIX BEFORE ADDING DASHING SHIT WONT WORK YO PUT IN UPDATE!!!!!!!

		//do dash stuff
		if (dash_distance_travled < dash_distance) {
			//only do stuff if still need to move more
			float x_distance = input_dir_x * dash_speed;
			float y_distance = input_dir_y * dash_speed;
			dash_distance_travled += (float)sqrt(pow(x_distance, 2) + pow(y_distance, 2)); //based pythag thereom, good shit right there (chorus right there)
			xVel += x_distance;
			yVel += y_distance;
		}
		else {
			//reset dash variables since dash distance has been covered
			dash_distance_travled = 0;
			is_dashing = false;
		}
	}
	else {
		//regular movement
		xVel += input_dir_x * walk_speed;
		yVel += input_dir_y * walk_speed;
	}
}

void Player::on_collision(Entity* other_ptr){
	entity_type other_type = other_ptr->get_type();
	if(other_type == DISK) {
		//colides with disk

		//destruct disk
		has_disk = true;
	}
	else {
		Size other_size = other_ptr->get_size();
		{//right and bottom overlap checks
			// wall or player if they are magic and get to other side of map
			float my_right = x + width;
			float my_bottom = y + height;

			float xOverlap = my_right - other_size.x;
			float yOverlap = my_bottom - other_size.y;
			if (xOverlap < 0)
				xOverlap = 0; //if not overlapping in x set it to 0
			if (yOverlap < 0)
				yOverlap = 0; //if not overllaping in y set it to 0

			if (xOverlap > yOverlap)
				x -= xOverlap; //overlapping more in x so move left
			else
				y -= yOverlap;
		}
		
		{//left and top overlap checks
			float other_right = other_size.x + other_size.width;
			float other_bottom = other_size.y + other_size.height;

			float xOverlap = other_right - x;
			float yOverlap = other_bottom - y;

			if (xOverlap < 0)
				xOverlap = 0; //if not overlapping in x set it to 0
			if (yOverlap < 0)
				yOverlap = 0; //if not overllaping in y set it to 0

			if (xOverlap > yOverlap)
				x += xOverlap; //overlapping more in x so more right
			else
				y += yOverlap;
		}

	}
}

void Player::handle_event(SDL_Event e){
	if (e.type == SDL_KEYDOWN) {
		SDL_Keycode eKey = e.key.keysym.sym;
		if (eKey == inputs[UP]) {
			move_player(0, 1);
		}else if (eKey == inputs[RIGHT]) {
			move_player(1, 0);
		}else if (eKey == inputs[LEFT]) {
			move_player(-1, 0);
		}else if (eKey == inputs[DOWN]) {
			move_player(0, -1);
		}else if (eKey == inputs[THROW]) {

		}else if (eKey == inputs[LOB]) {

		}
		else if (eKey == inputs[SPECIAL]) {

		}
	}
}

void Player::Update(int ticks) {
	x += (xVel * ticks) / 1000.f; //ticks in ms so dived by 1000 for pixels per second
	y += (yVel * ticks) / 1000.f; 
}

//entity_type Player::get_type()
//{
//	return PLAYER;
//}

