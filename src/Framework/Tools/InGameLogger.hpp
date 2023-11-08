#pragma once

#include  "CompilationConfig.hpp"

#if defined(CA_IN_GAME_LOGGER)

#include <deque>

#include "CA_Export.hpp"
#include  "Graphics/Color.hpp"

namespace CasaEngine
{
	//TODO : create component
#define IN_GAME_LOG(delay, color, fmt, ...) Game::Instance().GetInGameLogger().AddLog(color, fmt, ##__VA_ARGS__)

	class CA_EXPORT InGameLogger
	{
	public:
		InGameLogger();

		void AddLog(Color color, const char* fmt, ...);
		void ShowWindow();

	private:
		struct LogData
		{
			//float delay{}; // in ms
			const char* text{};
			Color color;
		};

		std::deque<LogData> m_Lines;
		unsigned int MaxLines;
	};
}

#else

#define InGameLog(color, fmt, ...) //Game::Instance().GetInGameLogger().AddLog(color, fmt, ##__VA_ARGS__)

#endif
