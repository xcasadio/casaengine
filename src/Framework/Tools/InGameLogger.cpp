#include "Base.h"
#include "InGameLogger.h"

#if defined(CA_IN_GAME_LOGGER)

#include "ocornut-imgui/imgui.h"
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
		m_FreeLinePos = 0;
		memset(m_Lines, 0, sizeof(LogData) * NBLOGLINES);

		for (int i=0; i<NBLOGLINES; i++)
		{
			m_Lines[i].isDeleted = true;
		}
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
		
		::free((void *)m_Lines[m_FreeLinePos].text);
		m_Lines[m_FreeLinePos].isDeleted = false;
		m_Lines[m_FreeLinePos].delay = delay_;
		m_Lines[m_FreeLinePos].text = strdup(sBuffer);

		m_FreeLinePos++;

		if (m_FreeLinePos >= NBLOGLINES)
		{
			m_FreeLinePos = 0;
		}
	}

	/**
	 * 
	 */
	void InGameLogger::Update(const GameTime& gameTime_)
	{
 		float time = gameTime_.FrameTime();

		for (int i=0; i<NBLOGLINES; i++)
		{
			m_Lines[i].delay -= time;			

			if (m_Lines[i].delay <= 0.0f)
			{
				m_Lines[i].isDeleted = true;
			}
		}
	}

	/**
	 * 
	 */
	void InGameLogger::ShowWindow()
	{
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
	}

} // namespace CasaEngine

#endif // #if defined(CA_IN_GAME_LOGGER)
