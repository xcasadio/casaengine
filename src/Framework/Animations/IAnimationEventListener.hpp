#pragma once

#include "CA_Export.hpp"

namespace CasaEngine
{
	class CA_EXPORT IFrameChangeEventListener
	{
	protected:
		~IFrameChangeEventListener() = default;

	public:
		virtual void OnFrameChanged(const char* frameID_) = 0;
	};
}
