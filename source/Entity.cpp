#include "..\include\Entity.h"

entity_type Entity::get_type()
{
	return eType;
}

Size Entity::get_size()
{
	Size s;
	s.x = x;
	s.y = y;
	s.width = width;
	s.height = height;
	return s;
}
