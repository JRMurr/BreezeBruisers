#ifndef GOAL_H_INCLUDED
#define GOAL_H_INCLUDED

#include <SDL.h>
#include "Wall.h"


class Goal : public Wall {
	public:
		entity_type get_type();
};

#endif 