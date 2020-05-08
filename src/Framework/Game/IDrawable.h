
#ifndef _IDRAWABLE_H_
#define _IDRAWABLE_H_

#include "CA_Export.h"
#include "GameTime.h"

namespace CasaEngine
{
	/////////////////////////////////////////////////////////////
	/// IDrawable
	/////////////////////////////////////////////////////////////
	class CA_EXPORT IDrawable
	{
	public:
		virtual void Render(GameTime& gameTime_) = 0;		
	};
}

#endif // _IUPDATEABLE_H_
