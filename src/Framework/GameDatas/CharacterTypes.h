#pragma once

enum class Orientation : int
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

// Respect the order of the enum CharacterAnimation
enum class AnimationDirectionOffset : int
{
	RIGHT = 0,
	LEFT = 1,
	UP = 2,
	DOWN = 3,
	UP_RIGHT = 4,
	DOWN_RIGHT = 5,
	UP_LEFT = 6,
	DOWN_LEFT = 7,
};