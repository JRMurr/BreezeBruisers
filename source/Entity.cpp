#include "../include/Entity.h"

Size Entity::get_size()
{
	Size s;
	s.x = x;
	s.y = y;
	s.width = width;
	s.height = height;
	return s;
}
