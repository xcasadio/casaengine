#ifndef IMGUIADAPTER_H_
#define IMGUIADAPTER_H_

#include "CA_Export.h"
#include "Graphics\Materials\Material.h"
#include <map>

namespace CasaEngine
{
	class CA_EXPORT imguiAdapter
	{
	public:

		static void imguiCreate(float _fontSize = 18.0f);
		static void imguiDestroy();

		static void imguiBeginFrame(unsigned short _width, unsigned short _height, unsigned char _view = 255);
		static void imguiEndFrame();

		static void displayUI4Material(Material &mat_, int x_, int y_, int width_, int height_, bool enabled_);

	private:
		static std::map<int, int> m_Vars;

	};
}

#endif
