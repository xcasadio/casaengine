#include "Base.h"
#include "InGameLogger.h"

#if defined(CA_IN_GAME_LOGGER)

#include "UI/imgui/bgfx-imgui.h"
#include <bgfx/bgfx.h>

#include "Game/Game.h"
#include <stdarg.h>
#include <stdlib.h>
#include "Log/LogManager.h"

namespace CasaEngine
{
	void InGameLogger::AddLog(float delay_, CColor color, const char *fmt, ...)
	{
		static char sBuffer[1024];
		va_list Params;
		va_start(Params, fmt);
		vsprintf(sBuffer, fmt, Params);
		va_end(Params);

		LogData logData;
		logData.delay = delay_;
		logData.text = _strdup(sBuffer);
		logData.color = color;
		m_Lines.push_back(logData);
	}

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

	void InGameLogger::ShowWindow()
	{
		/*bgfx::dbgTextClear();
		unsigned int y = 0;
		for (int i = m_Lines.size() - 1; i >= 0; --i)
		{
			bgfx::dbgTextPrintf(0, y, 0x0f, m_Lines[i].text);
			y++;
		}*/
				
		ImGui::SetNextWindowSize(ImVec2(
			Game::Instance().GetWindowSize().x - 50,
			Game::Instance().GetWindowSize().y - 50));
		ImGui::SetNextWindowPos(ImVec2(0.5f, 0.5f));
		//ImVec2(0,0), 0.3f, 
		if (!ImGui::Begin("Log in game", nullptr, 
			ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings))
		{
			ImGui::End();
			return;
		}

		for (int i = m_Lines.size() - 1; i >= 0; --i)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImColor(m_Lines[i].color.GetRed(), m_Lines[i].color.GetGreen(), m_Lines[i].color.GetBlue()).Value);
			ImGui::TextWrapped(m_Lines[i].text);
			ImGui::PopStyleColor();
		}

		ImGui::End();		
	}

}

#endif
