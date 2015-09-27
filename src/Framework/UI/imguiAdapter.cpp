#include "imguiAdapter.h"

#include "imgui\bgfx_imgui.h"


namespace CasaEngine
{
	std::map<int, int> imguiAdapter::m_Vars;

	/**
	 * 
	 */
	unsigned short imguiAdapter::imguiCreate(const void* _data /*= NULL*/, uint32_t _size /*= 0*/, float _fontSize /*= 15.0f*/)
	{
		return ::imguiCreate().idx;
	}

	/**
	 * 
	 */
	void imguiAdapter::imguiDestroy()
	{
		::imguiDestroy();
	}

	/**
	 * 
	 */
	void imguiAdapter::imguiBeginFrame(unsigned short _width, unsigned short _height, unsigned char _view /*= 255*/)
	{
		::imguiBeginFrame(_width, _height);
	}

	/**
	 * 
	 */
	void imguiAdapter::imguiBeginFrame(unsigned short _width, unsigned short _height, 
		unsigned short _surfaceWidth, unsigned short _surfaceHeight, unsigned char _view /*= 255*/)
	{
		::imguiBeginFrame(_width, _height, _surfaceWidth, _surfaceHeight, _view);
	}

	/**
	 * 
	 */
	void imguiAdapter::imguiEndFrame()
	{
		::imguiEndFrame();
	}

	/**
	 * 
	 */
	void imguiAdapter::displayUI4Material(Material &mat_, int x_, int y_, int width_, int height_, bool enabled_)
	{
		int id = (int)(&mat_);

		if (m_Vars.find(id) == m_Vars.end())
		{
			m_Vars[id] = 0;
		}

		::imguiBeginScrollArea((std::string("Material ") + mat_.GetName()).c_str(), x_, y_, width_, height_, &m_Vars[id], enabled_);
		::imguiSeparatorLine();

		::imguiCollapse("Test collapse", "sub text", false, true);

		::imguiSlider("Texture repetition U", mat_.m_Texture0Repeat.x, 0.01f, 100.0f, 0.1f);
		::imguiSeparator();
		::imguiSlider("Texture repetition V", mat_.m_Texture0Repeat.y, 0.01f, 100.0f, 0.1f);

		::imguiEndScrollArea();
	}

} // namespace CasaEngine
