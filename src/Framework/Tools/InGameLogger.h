#ifndef _INGAMELOGGER_H_
#define _INGAMELOGGER_H_

#include "CompilationConfig.h"

#if defined(CA_IN_GAME_LOGGER)

#include <vector>

#include "CA_Export.h"
#include "GameTime.h"

#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	//TODO : create component
#define InGameLog(delay, fmt, ...) Game::Instance().GetInGameLogger().AddLog(delay, fmt, ##__VA_ARGS__)

	/**
	 *
	 */
	class CA_EXPORT InGameLogger
	{
	public:

		void AddLog(float delay, const char* fmt, ...);
		void Update(const GameTime& gameTime_);
		void ShowWindow();

	private:
		struct LogData
		{
			float delay; // in ms
			const char* text;
		};

	private:
		std::vector<LogData> m_Lines;
	};

}


#else

#define InGameLog(delay, fmt, ...) Game::Instance().GetInGameLogger().AddLog(delay, fmt, ##__VA_ARGS__)
#define InGameLogUpdate(gameTime_) Game::Instance().GetInGameLogger().Update(gameTime_)

#endif

#endif
