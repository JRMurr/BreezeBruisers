#include "../include/Player.h"
#include <math.h>       /* sqrt  and pow*/
#include "../include/Define.h"

#define MAX_TIME_HOLD_DISK 1500 //1.5 secs

#define TMP_THROW_SPEED 400

#define DASH_DURATION 125	//.125 secs

Player::Player() {

}

void Player::Init(float x, float y, int character) {
	this->x = x;
	this->y = y;
	this->character = character;

	// TODO actual character sprite sheet
	Character c = Character::CharArray[this->character];
	sheet.init(c.sheetPath, c.width * 8, c.height * 8, c.width, c.height);

	initAnimations();

	width = c.width;	// TODO get width from character array
	height = c.height;

	//has_disk = false;
	Disk* disk = NULL;
	time_disk_held = 0;
	time_dashing = 0;

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
	if (disk || time_dashing >0)
		return; //dont move when has disk or is dashing
	//regular movement
	//Normalize input
	float l = sqrt(input_dir_x*input_dir_x + input_dir_y*input_dir_y);
	if (l != 0) {
		input_dir_x /= l;
		input_dir_y /= l;
	}
	Character c = Character::CharArray[character];
	xVel = input_dir_x * c.walkSpeed;	// TODO get walk speed from character array
	yVel = input_dir_y * c.walkSpeed;

	//currentAnimation = sheet.getAnim("RUNUP");

	if (xVel == 0 && yVel == 0) {
		if (x >= WIDTH / 2)
			currentAnimation = sheet.getAnim("IDLELEFT");
		if (x < WIDTH / 2)
			currentAnimation = sheet.getAnim("IDLERIGHT");
	}
	if (yVel < 0)
		currentAnimation = sheet.getAnim("RUNUP");
	if (yVel > 0)
		currentAnimation = sheet.getAnim("RUNDOWN");
	if (xVel < 0)
		currentAnimation = sheet.getAnim("RUNLEFT");
	if (xVel > 0)
		currentAnimation = sheet.getAnim("RUNRIGHT");
	if (xVel == 0 && yVel == 0 && currentAnimation == sheet.getAnim("RUNRIGHT"))
		currentAnimation = sheet.getAnim("IDLERIGHT");
	if (xVel == 0 && yVel == 0 && currentAnimation == sheet.getAnim("RUNLEFT"))
		currentAnimation = sheet.getAnim("IDLELEFT");
}

void Player::dash(float input_dir_x, float input_dir_y) {
	if (time_dashing > 0 || disk)
		return;//do nothing if already dashing or has disk
	if (input_dir_x == 0 && input_dir_y == 0)
		return;
	//Normalize input
	float l = sqrt(input_dir_x*input_dir_x + input_dir_y*input_dir_y);
	if (l != 0) {
		input_dir_x /= l;
		input_dir_y /= l;
	}
	Character c = Character::CharArray[character];
	xVel = input_dir_x * c.dashSpeed;	
	yVel = input_dir_y * c.dashSpeed;

	if (xVel == 0 && yVel == 0) {
		if (x >= WIDTH / 2)
			currentAnimation = sheet.getAnim("IDLELEFT");
		if (x < WIDTH / 2)
			currentAnimation = sheet.getAnim("IDLERIGHT");
	}
	if (yVel < 0)
		currentAnimation = sheet.getAnim("RUNUP");
	if (yVel > 0)
		currentAnimation = sheet.getAnim("RUNDOWN");
	if (xVel < 0)
		currentAnimation = sheet.getAnim("RUNLEFT");
	if (xVel > 0)
		currentAnimation = sheet.getAnim("RUNRIGHT");
	if (xVel == 0 && yVel == 0 && currentAnimation == sheet.getAnim("RUNRIGHT"))
		currentAnimation = sheet.getAnim("IDLERIGHT");
	if (xVel == 0 && yVel == 0 && currentAnimation == sheet.getAnim("RUNLEFT"))
		currentAnimation = sheet.getAnim("IDLELEFT");
	time_dashing = 1; //initalset
}

void Player::on_collision(Entity* other_ptr, int ticks) {
	entity_type other_type = other_ptr->get_type();
	if (other_type == DISK) {
		Disk* tmp = dynamic_cast<Disk*>(other_ptr);
		if (tmp->can_grab()) {
			//colides with disk
			time_dashing = 0;
			if (x >= WIDTH / 2)
				currentAnimation = sheet.getAnim("IDLELEFT");
			if (x < WIDTH / 2)
				currentAnimation = sheet.getAnim("IDLERIGHT");

			//hide disk
			disk = tmp;
			xVel = 0;
			yVel = 0;
		}

	}
	else {
		x -= xVel*(ticks / 1000.f);
		//y -= yVel*(ticks / 1000.f);
	}
}

void Player::handle_event(SDL_Event e) {

	const Uint8 *keystates = SDL_GetKeyboardState(NULL);

	float tx = 0, ty = 0;
	if (control) {
		int xAxis = SDL_GameControllerGetAxis(control, SDL_CONTROLLER_AXIS_LEFTX);
		int yAxis = SDL_GameControllerGetAxis(control, SDL_CONTROLLER_AXIS_LEFTY);
		if (yAxis >= 10000)
			ty = 1;
		if (yAxis <= -10000)
			ty = -1;
		if (xAxis >= 10000)
			tx = 1;
		if (xAxis <= -10000)
			tx = -1;
	}
	else {
		if (keystates[inputs[UP]]) {
			ty -= 1;
		}
		if (keystates[inputs[RIGHT]]) {
			tx += 1;
		}
		if (keystates[inputs[LEFT]]) {
			tx -= 1;
		}
		if (keystates[inputs[DOWN]]) {
			ty += 1;
		}
	}

	if (!disk) {//does not have disk
		if (time_dashing == 0) {
			if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == inputs[LOB]) || 
				(e.type == SDL_CONTROLLERBUTTONDOWN && e.cbutton.button == SDL_CONTROLLER_BUTTON_B && SDL_GameControllerGetButton(control, SDL_CONTROLLER_BUTTON_B)))
				dash(tx, ty);
			else
				move_player(tx, ty);
		}
			
	}
	else {
		//has disk so check for throw button
		if (keystates[inputs[THROW]] || SDL_GameControllerGetButton(control, SDL_CONTROLLER_BUTTON_A)) {
			throw_disk(tx, ty);
		}
	}
}

void Player::throw_disk(float tx, float ty) {
	if (x < WIDTH / 2 && tx < 0)
		tx = 0; //dont throw behine on left
	if (x > WIDTH / 2 && tx >0)
		tx = 0; //dont throw behind on right

	float x_throw_speed = 0;
	float y_throw_speed = 0;
	if (tx != 0) {
		x_throw_speed = (tx * TMP_THROW_SPEED) * ((float)(MAX_TIME_HOLD_DISK - time_disk_held) / MAX_TIME_HOLD_DISK);
	}

	if (ty != 0) {
		y_throw_speed = (ty * TMP_THROW_SPEED) * ((float)(MAX_TIME_HOLD_DISK - time_disk_held) / MAX_TIME_HOLD_DISK);
	}


	if (y_throw_speed != 0 && x_throw_speed == 0)
		x_throw_speed = 100; //add some x dir so it doesnt go perfectly vertical

	if (y_throw_speed == 0 && x_throw_speed == 0)
		x_throw_speed = TMP_THROW_SPEED / 3; //if not holding throw horizontal
	if (x > WIDTH / 2 && x_throw_speed > 0)
		x_throw_speed *= -1;

	float x_spawn = x + width + disk->get_size().width + 15;
	if (x > WIDTH / 2)
		x_spawn = x - disk->get_size().width - 15;
	disk->Init(x_spawn, y, x_throw_speed, y_throw_speed);
	disk = NULL;
}

void Player::Update(int ticks) {
	if (!disk) {//does not have disk
		time_disk_held = 0;
		x += (xVel * ticks) / 1000.f; //ticks in ms so dived by 1000 for pixels per second
		y += (yVel * ticks) / 1000.f;


		//printf("anim- %d \n",animTime);
		if (x <= 0)
			x = 0;
		if (x > WIDTH - width)
			x = WIDTH - width;
		if (y <= 0)
			y = 0;
		if (y > HEIGHT - height)
			y = HEIGHT - height;
	}
	else {
		//has disk
		time_disk_held += ticks;
		if (time_disk_held > MAX_TIME_HOLD_DISK) {
			throw_disk(0, 0);
		}
	}

	if (time_dashing > 0) {
		//dash checks
		if (time_dashing < DASH_DURATION)
			time_dashing += ticks;
		else {
			time_dashing = 0;
			xVel = 0;
			yVel = 0;
		}
			
	}
	animTime += ticks;

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
	if(time_dashing > 0)
		SDL_SetTextureColorMod(sheet.getTexture(), 255, 0, 0);
	else if(disk)
		SDL_SetTextureColorMod(sheet.getTexture(), 150, 150, 150);
	else
		SDL_SetTextureColorMod(sheet.getTexture(), 255, 255, 255);
	SDL_RenderCopy(screen, sheet.getTexture(), &src, &dst);
}

void Player::initAnimations() {

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

bool Player::using_controller() {
	return control != NULL;
}

void Player::setInputs(SDL_Scancode *newInputs) {
	for (int n = 0; n < SPECIAL + 1; n++)
		inputs[n] = newInputs[n];
}