#include "../include/Player.h"
#include <math.h>       /* sqrt  and pow*/
#include "../include/Define.h"

Player::Player() {

}

void Player::Init(float x, float y, int character) {
	this->x = x;
	this->y = y;
	this->character = character;

	// TODO actual character sprite sheet
	Character c = Character::CharArray[this->character];
	sheet.init(c.sheetPath, c.width*8, c.height*8, c.width, c.height);

	initAnimations();

	width = c.width;	// TODO get width from character array
	height = c.height;

	has_disk = false;
	time_disk_held = 0;
	using_controller = false; //TMP!!!!! FIX !!!!!
	dash_distance_travled = 0;

	xVel = 0;
	yVel = 0;

	//controls wasd + space for throw, e for lob and Lshift for special
	inputs[UP] = SDL_SCANCODE_W;
	inputs[DOWN] = SDL_SCANCODE_S;
	inputs[LEFT] = SDL_SCANCODE_A;
	inputs[RIGHT] = SDL_SCANCODE_D;
	inputs[THROW] = SDL_SCANCODE_SPACE;
	inputs[LOB] = SDL_SCANCODE_E;
	inputs[SPECIAL] = SDL_SCANCODE_LSHIFT;

	currentAnimation = sheet.getAnim("IDLERIGHT");
}

void Player::move_player(float input_dir_x, float input_dir_y) {
	if (has_disk)
		return; //dont move when has disk
	//if (is_dashing) {

		//!!!FIX BEFORE ADDING DASHING SHIT WONT WORK YO PUT IN UPDATE!!!!!!!

		/*do dash stuff
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
	else*/ {
		//regular movement
        //Normalize input
        float l = sqrt(input_dir_x*input_dir_x + input_dir_y*input_dir_y);
        if(l!=0){
            input_dir_x/=l;
            input_dir_y/=l;
        }
		Character c = Character::CharArray[character];
		xVel = input_dir_x * c.walkSpeed;	// TODO get walk speed from character array
		yVel = input_dir_y * c.walkSpeed;

		//currentAnimation = sheet.getAnim("RUNUP");

		if(yVel < 0)
            currentAnimation = sheet.getAnim("RUNUP");
        if(yVel > 0)
            currentAnimation = sheet.getAnim("RUNDOWN");
		if(xVel < 0)
            currentAnimation = sheet.getAnim("RUNLEFT");
        if(xVel > 0)
            currentAnimation = sheet.getAnim("RUNRIGHT");
        if(xVel == 0 && yVel == 0 && currentAnimation == sheet.getAnim("RUNRIGHT"))
            currentAnimation = sheet.getAnim("IDLERIGHT");
        else if(xVel == 0 && yVel == 0 && currentAnimation == sheet.getAnim("RUNLEFT"))
            currentAnimation = sheet.getAnim("IDLELEFT");
        else if(xVel == 0 && yVel == 0)
        {
            if(x <= WIDTH/2)
                currentAnimation = sheet.getAnim("IDLERIGHT");
            else
                currentAnimation = sheet.getAnim("IDLELEFT");
        }
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

	const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    float tx=0, ty=0;
    if(control){
        int xAxis = SDL_GameControllerGetAxis(control, SDL_CONTROLLER_AXIS_LEFTX);
        int yAxis = SDL_GameControllerGetAxis(control, SDL_CONTROLLER_AXIS_LEFTY);
        if(yAxis >= 10000)
            ty = 1;
        if(yAxis <= -10000)
            ty = -1;
        if(xAxis >= 10000)
            tx = 1;
        if(xAxis <= -10000)
            tx = -1;
    }
    else{
        if (keystates[inputs[UP]]) {
            ty-=1;
        }
        if (keystates[inputs[RIGHT]]) {
            tx+=1;
        }
        if (keystates[inputs[LEFT]]) {
            tx-=1;
        }
        if (keystates[inputs[DOWN]]) {
            ty+=1;
        }
    }


    move_player(tx,ty);
}

void Player::Update(int ticks) {
	x += (xVel * ticks) / 1000.f; //ticks in ms so dived by 1000 for pixels per second
	y += (yVel * ticks) / 1000.f;

	animTime+=ticks;
    //printf("anim- %d \n",animTime);
	if(x<=0)
        x = 0;
    if(x>WIDTH-width)
        x = WIDTH-width;
    if(y<=0)
        y =0;
    if(y>HEIGHT-height)
        y = HEIGHT-height;

}

entity_type Player::get_type()
{
	return PLAYER;
}

void Player::Draw(SDL_Renderer *screen) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_Rect src = sheet.getSprite(currentAnimation->getFrame(animTime));
	SDL_RenderCopy(screen, sheet.getTexture(), &src, &dst);
}

void Player::initAnimations(){

    Animation IdleRightAnim;
	IdleRightAnim.init("IDLERIGHT");
	IdleRightAnim.addAnim(0, 7, 150);
	sheet.addAnim("IDLERIGHT", IdleRightAnim);

	Animation IdleLeftAnim;
	IdleLeftAnim.init("IDLELEFT");
	IdleLeftAnim.addAnim(8, 15, 150);
	sheet.addAnim("IDLELEFT", IdleLeftAnim);

	Animation RunLeftAnim;
	RunLeftAnim.init("RUNLEFT");
	RunLeftAnim.addAnim(40, 42, 200);
	sheet.addAnim("RUNLEFT", RunLeftAnim);

	Animation RunRightAnim;
	RunRightAnim.init("RUNRIGHT");
	RunRightAnim.addAnim(32, 34, 200);
	sheet.addAnim("RUNRIGHT", RunRightAnim);

	Animation RunDownAnim;
	RunDownAnim.init("RUNDOWN");
	RunDownAnim.addAnim(48, 50, 200);
	sheet.addAnim("RUNDOWN", RunDownAnim);

    Animation RunUpAnim;
	RunUpAnim.init("RUNUP");
	RunUpAnim.addAnim(56, 58, 200);
	sheet.addAnim("RUNUP", RunUpAnim);
}

