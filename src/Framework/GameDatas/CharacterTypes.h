#ifndef CHARACTER_TYPES_H_
#define CHARACTER_TYPES_H_


enum orientation
{
	UP = 0x1,
	DOWN = 0x2,
	LEFT = 0x4,
	RIGHT = 0x8,

	UP_LEFT = LEFT | UP,
	DOWN_LEFT = LEFT | DOWN,
	UP_RIGHT = RIGHT | UP,
	DOWN_RIGHT = RIGHT | DOWN
};


#endif
