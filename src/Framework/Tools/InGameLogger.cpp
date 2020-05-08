#include "Base.h"
#include "InGameLogger.h"

#if defined(CA_IN_GAME_LOGGER)

#include "bgfx.h"

#include "Game/Game.h"
#include <stdarg.h>
#include <stdlib.h>
#include "Log/LogManager.h"

namespace CasaEngine
{
	SINGLETON_IMPL(InGameLogger)

	/**
	 * 
	 */
	InGameLogger::InGameLogger() 
	{
	}

	/**
	 * 
	 */
	InGameLogger::~InGameLogger() { }

	/**
	 * 
	 */
	void InGameLogger::AddLog(float delay_, const char *fmt, ...)
	{
		static char sBuffer[8192];
		va_list Params;
		va_start(Params, fmt);
		vsprintf(sBuffer, fmt, Params);
		va_end(Params);

		LogData logData;
		logData.delay = delay_;
		logData.text = _strdup(sBuffer);
		m_Lines.push_back(logData);
	}

	/**
	 * 
	 */
	void InGameLogger::Update(const GameTime& gameTime_)
	{
		const float time = gameTime_.FrameTime();

		for (int i=0; i<m_Lines.size(); i++)
		{
			m_Lines[i].delay -= time;
		}

		bool needDelete = true;
		
		while (needDelete)
		{
			needDelete = false;
			for (std::vector<LogData>::iterator it = m_Lines.begin(); it != m_Lines.end(); it++)
			{
				if (it->delay <= 0.0f)
				{
					m_Lines.erase(it);
					needDelete = true;
					break;					
				}
			}
		}
	}

	/**
	 * 
	 */
	void InGameLogger::ShowWindow()
	{
		bgfx::dbgTextClear();
		int y = 0;
		for (int i = m_Lines.size() - 1; i >= 0; --i)
		{
			bgfx::dbgTextPrintf(0, y, 0x0f, m_Lines[i].text);
			y++;
		}
		
		/*
		ImGui::SetNextWindowSize(ImVec2(
			Game::Instance()->GetWindow()->getSize().x - 50,
			Game::Instance()->GetWindow()->getSize().y - 50));
		ImGui::SetNextWindowPosCenter();

		if (!ImGui::Begin("Log in game", nullptr, ImVec2(0,0), 0.3f, 
			ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings))
		{
			ImGui::End();
			return;
		}

		for (unsigned int i=m_FreeLinePos + 1; i<m_FreeLinePos + NBLOGLINES; i++)
		{
			int index = i > NBLOGLINES ? i - NBLOGLINES : i;

			if (m_Lines[index].isDeleted == false)
			{
				//ImGui::PushStyleColor(ImGuiCol_Text, ImColor(CColor::Green.GetRed(), CColor::Green.GetGreen(), CColor::Green.GetBlue()));
				ImGui::TextWrapped(m_Lines[index].text);
				//ImGui::PopStyleColor();
			}
		}

		ImGui::End();
		*/
	}

}

#endif // #if defined(CA_IN_GAME_LOGGER)
