#include "DebugOptions.h"
#include <string>
#include "Game\Game.h"

namespace CasaEngine
{
	DebugOptions::DebugOptions() :
		ShowPhysicsDebug(false),
		ShowLogInGame(false),
		ShowAxis(false),
		ShowFPS(false),
		IsDebugActivated(false),
		ShowGrid(false)
	{
	}

	void DebugOptions::Activate(std::string& item_, bool val)
	{
		if (item_ == "editor")
		{
			IsDebugActivated = val;
		}
	}

	void DebugOptions::Show(std::string& item_, bool val)
	{
		if (item_ == "axis")
		{
			ShowAxis = val;
		}
		else if (item_ == "fps")
		{
			ShowFPS = val;
		}
		else if (item_ == "log")
		{
			ShowLogInGame = val;
		}
	}
}
