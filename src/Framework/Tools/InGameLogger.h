#ifndef _INGAMELOGGER_H_
#define _INGAMELOGGER_H_

#include "CompilationConfig.h"

#if defined(CA_IN_GAME_LOGGER)

#include <vector>

#include "CA_Export.h"
#include "GameTime.h"
#include "Singleton.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
#define InGameLog(delay, fmt, ...) InGameLogger::Instance().AddLog(delay, fmt, ##__VA_ARGS__)
#define InGameLogUpdate(gameTime_) InGameLogger::Instance().Update(gameTime_)

	/**
	 *  
	 */
	class CA_EXPORT InGameLogger :
		public CSingleton<InGameLogger>
	{
	MAKE_SINGLETON(InGameLogger)

	private:
		struct LogData
		{
			float delay; // in ms
			const char *text;			
			bool isDeleted;
		};

	private:
		InGameLogger();
		~InGameLogger();

	public:

		void AddLog(float delay, const char *fmt, ...);
		void Update(const GameTime& gameTime_);
		void ShowWindow();

	private:
// 		typedef std::vector<LogData> LogDatas;
// 		typedef std::vector<LogData>::iterator LogDataIt;
// 		
// 		LogDatas m_Lines;
#define NBLOGLINES 512
		unsigned int m_FreeLinePos;
		LogData m_Lines[NBLOGLINES];
	};

} // namespace CasaEngine


#else
	
#define InGameLog(delay, fmt, ...) InGameLogger::Instance().AddLog(delay, fmt, ##__VA_ARGS__)
#define InGameLogUpdate(gameTime_) InGameLogger::Instance().Update(gameTime_)

#endif // #if defined(CA_IN_GAME_LOGGER)

#endif // _INGAMELOGGER_H_
