#include  "InGameLogger.hpp"

#if defined(CA_IN_GAME_LOGGER)

#include  "Game/Game.hpp"
#include <cstdarg>

namespace CasaEngine
{
	InGameLogger::InGameLogger() :
		MaxLines(500)
	{
		//m_Lines.resize(MaxLines);
	}

	void InGameLogger::AddLog(Color color, const char* fmt, ...)
	{
		static char s_buffer[1024];
		va_list Params;
		va_start(Params, fmt);
		vsprintf(s_buffer, fmt, Params);
		va_end(Params);

		LogData log_data;
		log_data.text = _strdup(s_buffer);
		log_data.color = color;

		if (m_Lines.size() == MaxLines)
		{
			m_Lines.pop_back();
		}

		m_Lines.push_front(log_data);
	}

	void InGameLogger::ShowWindow()
	{
		ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Logs", nullptr, ImGuiWindowFlags_None))
		{
			for (auto& m_Line : m_Lines)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImColor(m_Line.color.GetRed(), m_Line.color.GetGreen(), m_Line.color.GetBlue()).Value);
				ImGui::TextWrapped(m_Line.text);
				ImGui::PopStyleColor();
			}
		}

		ImGui::End();
	}
}

#endif