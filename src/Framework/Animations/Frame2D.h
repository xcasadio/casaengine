
#ifndef _FRAME2D_H_
#define _FRAME2D_H_

#include <string>
#include "CA_Export.h"
#include "Maths\Vector2.h"

namespace CasaEngine
{
	/////////////////////////////////////////////////////////////
	/// Sprite
	/////////////////////////////////////////////////////////////
	struct CA_EXPORT Frame2D
	{
	public:
		//unsigned int spriteID;
		const char* spriteID;
		float time;
		Vector2I origin;
		//Sprite Effect
	};
} // namespace CasaEngine

#endif // _FRAME2D_H_
