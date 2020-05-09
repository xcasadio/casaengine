#ifndef RENDERER_H
#define RENDERER_H

#include "Base.h"

#include <string>
#include <map>
#include <vector>

#if CA_PLATFORM_WINDOWS || CA_PLATFORM_LINUX || CA_PLATFORM_OSX

#include <windows.h>
#include "SFML/Window/WindowHandle.hpp"

#endif

#include "CA_Export.h"

#include "Graphics/Color.h"

#include "Graphics/Renderer/Enums.h"

#include "Maths/Vector2.h"
#include "Maths/Vector3.h"
#include "Maths/Matrix4.h"
#include "Maths/Rectangle.h"

#include "SFML/System/NonCopyable.hpp"

#include "Graphics/RenderTarget.h"
#include "IO/IFile.h"
#include "Graphics/Viewport.h"
#include "Graphics/TextureTarget.h"
#include "SFML/Window/Window.hpp"
#include "EngineSettings.h"
#include "bgfx.h"

#define CA_DEFAULT_WIDTH 1280
#define CA_DEFAULT_HEIGHT 720

namespace CasaEngine
{
    class CA_EXPORT IRenderer
    {
    public :
		IRenderer();
    	
		void shutdown();

		void Resize(unsigned int width_, unsigned height_);

		void SetClearColor(unsigned char index_, CColor val) const;
		void Initialize(EngineSettings &settings_);

		bool IsDeviceLost() const;
		void SetDeviceLost();

	private:        
		IRenderer(const IRenderer&) = delete;
		IRenderer& operator = (const IRenderer&) = delete;
    	
#if CA_PLATFORM_MOBILE
		void Setup();
#else
		void Setup(sf::Window* pWindow_);
#endif

		bool m_bDeviceLost;	
    };
}

#endif
