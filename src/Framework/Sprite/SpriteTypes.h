

#ifndef SPRITETYPES_H_
#define SPRITETYPES_H_

namespace CasaEngine
{
	typedef enum
	{
		// Summary:
		//     No rotations specified.
		SPRITE_EFFECT_NONE = 0,
		//
		// Summary:
		//     Rotate 180 degrees about the Y axis before rendering.
		SPRITE_EFFECT_FLIP_HORIZONTALLY = 1,
		//
		// Summary:
		//     Rotate 180 degrees about the X axis before rendering.
		SPRITE_EFFECT_FLIP_VERTICALLY = 2,
	} eSpriteEffects;
}

#endif // SPRITETYPES_H_
