#include "ImGuiAdapter.h"
#include "imgui/bgfx-imgui.h"

namespace CasaEngine
{
	std::map<int, int> ImGuiAdapter::m_Vars;

	void ImGuiAdapter::Create(float _fontSize)
	{
		::imguiCreate(_fontSize);
	}

	void ImGuiAdapter::Destroy()
	{
		::imguiDestroy();
	}

	void ImGuiAdapter::BeginFrame(unsigned short _width, unsigned short _height, unsigned char _view /*= 255*/)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(_width, _height);
		//Get status of mouse and keyboard
		::imguiBeginFrame(0, 0, 0, 0, _width, _height);
	}

	void ImGuiAdapter::EndFrame()
	{
		::imguiEndFrame();
	}

	void ImGuiAdapter::DisplayUI4Material(Material &mat_, int x_, int y_, int width_, int height_, bool enabled_)
	{
		int id = (int)(&mat_);

		if (m_Vars.find(id) == m_Vars.end())
		{
			m_Vars[id] = 0;
		}
		/*
		::imguiBeginScrollArea((std::string("Material ") + mat_.GetName()).c_str(), x_, y_, width_, height_, &m_Vars[id], enabled_);
		::imguiSeparatorLine();

		::imguiCollapse("Test collapse", "sub text", false, true);

		::imguiSlider("Texture repetition U", mat_.m_Texture0Repeat.x, 0.01f, 100.0f, 0.1f);
		::imguiSeparator();
		::imguiSlider("Texture repetition V", mat_.m_Texture0Repeat.y, 0.01f, 100.0f, 0.1f);

		::imguiEndScrollArea();
		*/
	}
}
