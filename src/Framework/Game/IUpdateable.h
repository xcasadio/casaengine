
#ifndef _IUPDATEABLE_H_
#define _IUPDATEABLE_H_

#include "CA_Export.h"
#include "GameTime.h"

namespace CasaEngine
{
	/////////////////////////////////////////////////////////////
	/// IUpdateable
	/////////////////////////////////////////////////////////////
	class CA_EXPORT IUpdateable
	{
	public:
		virtual void Update(GameTime& gameTime_) = 0;
	};
} // namespace CasaEngine

#endif // _IUPDATEABLE_H_
