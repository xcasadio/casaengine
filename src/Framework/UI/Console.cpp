#include "Console.h"
#include <string>
#include "Game\Game.h"

namespace CasaEngine
{
	Console::Console()
	{
		m_IsVisible = false;
	}

	Console::~Console()
	{
		for (int i = 0; i < m_Items.size(); i++)
			free(m_Items[i]);
		m_Items.clear();
	}

	void Console::Initialize()
	{
		typedef void (DebugOptions::* T1)(std::string&, bool);

		RegisterCommand("clear", Bind(&Console::ClearLog, *this));
		RegisterCommand("close", Bind(&Console::VisibilityToggle, *this));
		RegisterCommand("help", Bind(&Console::GetCommands, *this));

		RegisterCommand("exit", Bind(&Game::Exit, Game::Instance()));
		RegisterCommand("activate", Bind(&DebugOptions::Activate, Game::Instance().GetDebugOptions()));
		RegisterCommand("show", Bind(&DebugOptions::Show, Game::Instance().GetDebugOptions()));

		// 		Console::Instance().RegisterCommand("vsparam1", Bind(static_cast<T1>(&Shader::SetParameter), m_VertexShader));
		// 		Console::Instance().RegisterCommand("psparam1", Bind(static_cast<T1>(&Shader::SetParameter), m_VertexShader));
		// 		Console::Instance().RegisterCommand("vsparam2", Bind(static_cast<T2>(&Shader::SetParameter), m_VertexShader));
		// 		Console::Instance().RegisterCommand("psparam2", Bind(static_cast<T2>(&Shader::SetParameter), m_VertexShader));
		// 		Console::Instance().RegisterCommand("vsparam3", Bind(static_cast<T3>(&Shader::SetParameter), m_VertexShader));
		// 		Console::Instance().RegisterCommand("psparam3", Bind(static_cast<T3>(&Shader::SetParameter), m_VertexShader));
		// 		Console::Instance().RegisterCommand("shaders",  Bind(&ShaderGame::ChangeShaders,          *this));
		// 		Console::Instance().RegisterCommand("load",     Bind(&ShaderGame::LoadModel,              *this));
		// 		Console::Instance().RegisterCommand("exit",     Bind(&ShaderGame::Exit,                   *this));
	}

	void Console::ClearLog()
	{
		for (int i = 0; i < m_Items.size(); i++)
			free(m_Items[i]);
		m_Items.clear();
		//ScrollToBottom = true;
	}

	void Console::AddLog(const char* fmt, ...)
	{
		char buf[1024];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, 1024, fmt, args);
		buf[1024 - 1] = 0;
		va_end(args);
		m_Items.push_back(strdup(buf));
		//ScrollToBottom = true;
	}

	/*
	static int TextEditCallback(ImGuiTextEditCallbackData* data)
	{
		Console* console = (Console*)data->UserData;
		return 0;//console->TextEditCallback(data);
	}*/

	void Console::Draw()
	{
		if (m_IsVisible == false)
		{
			return;
		}

		int winWidth = Game::Instance().GetWindowSize().x;
		int winHeight = Game::Instance().GetWindowSize().y;
		/*
		ImGui::SetNextWindowSize(ImVec2(winWidth - 100, winHeight - 100), ImGuiSetCond_FirstUseEver);
		if (!ImGui::Begin("Console"))
		{
			ImGui::End();
			return;
		}

		// Display every line as a separate entry so we can change their color or add custom widgets. If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
		// NB- if you have thousands of entries this approach may be too inefficient. You can seek and display only the lines that are visible - CalcListClipping() is a helper to compute this information.
		// If your items are of variable size you may want to implement code similar to what CalcListClipping() does. Or split your data into fixed height items to allow random-seeking into your list.
		ImGui::BeginChild("ScrollingRegion", ImVec2(0,-ImGui::GetItemsLineHeightWithSpacing()));
		if (ImGui::BeginPopupContextWindow())
		{
			ImGui::EndPopup();
		}
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing

		for (int i = 0; i < m_Items.size(); i++)
		{
			const char* item = m_Items[i];
// 			if (!filter.PassFilter(item))
// 				continue;
			ImVec4 col = ImColor(255,255,255); // A better implementation may store a type per-item. For the sample let's just parse the text.
			if (strstr(item, "[error]")) col = ImColor(255,100,100);
			else if (strncmp(item, "# ", 2) == 0) col = ImColor(255,200,150);
			ImGui::PushStyleColor(ImGuiCol_Text, col);
			ImGui::TextUnformatted(item);
			ImGui::PopStyleColor();
		}

// 		if (ScrollToBottom)
// 			ImGui::SetScrollHere();
// 		ScrollToBottom = false;

		ImGui::PopStyleVar();
		ImGui::EndChild();
		ImGui::Separator();

		// Command-line
		if (ImGui::InputText("Input", m_InputBuf, 256,
			ImGuiInputTextFlags_EnterReturnsTrue|ImGuiInputTextFlags_CallbackCompletion|ImGuiInputTextFlags_CallbackHistory,
			TextEditCallback, (void*)this))
		{
			char* input_end = m_InputBuf + strlen(m_InputBuf);
			while (input_end > m_InputBuf && input_end[-1] == ' ') input_end--; *input_end = 0;
			if (m_InputBuf[0])
				ExecCommand(m_InputBuf);
			strcpy(m_InputBuf, "");
		}

		// Demonstrate keeping auto focus on the input box
		if (ImGui::IsItemHovered() || (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
			ImGui::SetKeyboardFocusHere(-1); // Auto focus

		ImGui::End();
		*/
	}

	/*	int TextEditCallback(ImGuiTextEditCallbackData* data)
		{
			//AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
			switch (data->EventFlag)
			{
			case ImGuiInputTextFlags_CallbackCompletion:
				{
					// Example of TEXT COMPLETION

					// Locate beginning of current word
					const char* word_end = data->Buf + data->CursorPos;
					const char* word_start = word_end;
					while (word_start > data->Buf)
					{
						const char c = word_start[-1];
						if (c == ' ' || c == '\t' || c == ',' || c == ';')
							break;
						word_start--;
					}

					// Build a list of candidates
					ImVector<const char*> candidates;
					for (int i = 0; i < Commands.Size; i++)
						if (Strnicmp(Commands[i], word_start, (int)(word_end-word_start)) == 0)
							candidates.push_back(Commands[i]);

					if (candidates.Size == 0)
					{
						// No match
						AddLog("No match for \"%.*s\"!\n", (int)(word_end-word_start), word_start);
					}
					else if (candidates.Size == 1)
					{
						// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
						data->DeleteChars((int)(word_start-data->Buf), (int)(word_end-word_start));
						data->InsertChars(data->CursorPos, candidates[0]);
						data->InsertChars(data->CursorPos, " ");
					}
					else
					{
						// Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
						int match_len = (int)(word_end - word_start);
						for (;;)
						{
							int c = 0;
							bool all_candidates_matches = true;
							for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
								if (i == 0)
									c = toupper(candidates[i][match_len]);
								else if (c != toupper(candidates[i][match_len]))
									all_candidates_matches = false;
							if (!all_candidates_matches)
								break;
							match_len++;
						}

						if (match_len > 0)
						{
							data->DeleteChars((int)(word_start - data->Buf), (int)(word_end-word_start));
							data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
						}

						// List matches
						AddLog("Possible matches:\n");
						for (int i = 0; i < candidates.Size; i++)
							AddLog("- %s\n", candidates[i]);
					}

					break;
				}
			case ImGuiInputTextFlags_CallbackHistory:
				{
					// Example of HISTORY
					const int prev_history_pos = HistoryPos;
					if (data->EventKey == ImGuiKey_UpArrow)
					{
						if (HistoryPos == -1)
							HistoryPos = History.Size - 1;
						else if (HistoryPos > 0)
							HistoryPos--;
					}
					else if (data->EventKey == ImGuiKey_DownArrow)
					{
						if (HistoryPos != -1)
							if (++HistoryPos >= History.Size)
								HistoryPos = -1;
					}

					// A better implementation would preserve the data on the current input line along with cursor position.
					if (prev_history_pos != HistoryPos)
					{
						snprintf(data->Buf, data->BufSize, "%s", (HistoryPos >= 0) ? History[HistoryPos] : "");
						data->BufDirty = true;
						data->CursorPos = data->SelectionStart = data->SelectionEnd = (int)strlen(data->Buf);
					}
				}
			}
			return 0;
		}*/

	void Console::VisibilityToggle()
	{
		m_IsVisible = !m_IsVisible;
	}

	void Console::RegisterCommand(const char* pName, const Functor& function_)
	{
		m_Commands[std::string(pName)] = function_;
	}

	std::string Console::GetCommands() const
	{
		std::string List;
		for (TCommandTable::const_iterator i = m_Commands.begin(); i != m_Commands.end(); ++i)
			List += i->first + " ";

		return List;
	}

	void Console::ExecCommand(const char* pCommand_)
	{
		std::string Command;
		std::istringstream iss(pCommand_);
		iss >> Command;

		AddLog("# %s\n", pCommand_);

		TCommandTable::iterator It = m_Commands.find(std::string(Command));

		if (It != m_Commands.end())
		{
			std::string Params;
			std::getline(iss, Params);

			AddLog(It->second(Params).c_str());
		}
		else
		{
			//m_Look->Error("Unknown command '" + Command + "'");
		}
	}
}