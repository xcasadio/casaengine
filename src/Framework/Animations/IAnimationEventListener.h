
#ifndef _IANIMATIONEVENTLISTENER_H_
#define _IANIMATIONEVENTLISTENER_H_

#include "CA_Export.h"

namespace CasaEngine
{
	class CA_EXPORT IFrameChangeEventListener
	{
	public:
		virtual void OnFrameChanged(const char* frameID_) = 0;
	};
} // namespace CasaEngine

#endif // _IANIMATIONEVENTLISTENER_H_
