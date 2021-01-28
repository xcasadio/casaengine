#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <string>
#include <map>
#include <vector>

#include "CA_Export.h"
#include "Functor.h"

namespace CasaEngine
{
	class CA_EXPORT Console
	{
	public:
		Console();
		~Console();

		void Initialize();
		void ClearLog();

		void Draw();
		void VisibilityToggle();

		void ExecCommand(const char *pCommand_);
		void RegisterCommand(const char *pName, const Functor& function_);

	private:
		void AddLog(const char* fmt, ...);
		std::string GetCommands() const;
		typedef std::map<std::string, Functor> TCommandTable;

		char          m_InputBuf[256];
		std::vector<char*> m_Items;
		bool		  m_IsVisible;
		TCommandTable m_Commands;
		std::string   m_LastLine;
	};
}

#endif