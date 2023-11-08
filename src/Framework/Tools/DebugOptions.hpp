#pragma once

#include "CA_Export.hpp"
#include <string>

namespace CasaEngine
{
	class CA_EXPORT DebugOptions
	{
	public:
		DebugOptions();

		void Show(std::string &item_, bool val);
		void Activate(std::string &item_, bool val);

		bool ShowPhysicsDebug;
		bool ShowLogInGame;
		bool ShowAxis;
		bool ShowFPS;
		bool IsDebugActivated;
		bool ShowGrid;
	};
}
