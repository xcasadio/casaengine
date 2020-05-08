#ifndef DEBUGOPTIONS_H
#define DEBUGOPTIONS_H

#include "CA_Export.h"
#include <string>

namespace CasaEngine
{
	/**
	 *
	 */
	class CA_EXPORT DebugOptions
	{
	public:
		DebugOptions();
		~DebugOptions();

		void Show(std::string &item_, bool val);
		void Activate(std::string &item_, bool val);

		bool ShowLogInGame;
		bool ShowAxis;
		bool ShowFPS;
		bool IsDebugActivated;

	}; // struct EditorOptions
}

#endif // DEBUGOPTIONS_H
