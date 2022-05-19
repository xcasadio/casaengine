#pragma once

#include "CA_Export.h"

namespace CasaEngine
{
	class CA_EXPORT IFrameChangeEventListener
	{
	public:
		virtual void OnFrameChanged(const char* frameID_) = 0;
	};
}
