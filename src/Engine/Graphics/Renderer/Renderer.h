//==========================================================
// CasaEngine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc.,
// 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA.
//
// E-mail : laurent.gom@gmail.com
//==========================================================

#ifndef RENDERER_H
#define RENDERER_H

#include "Base.h"

#include <string>
#include <map>
#include <vector>

#if CA_PLATFORM_WINDOWS || CA_PLATFORM_LINUX || CA_PLATFORM_OSX

#include <windows.h>
#include "SFML/Window/WindowHandle.hpp"

#endif // if DESKSTOP

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
    ////////////////////////////////////////////////////////////
    /// Classe de base pour les systèmes de rendu
    ////////////////////////////////////////////////////////////
    class CA_EXPORT IRenderer
    {
    public :

		static void Destroy();
		static IRenderer& Get();

	private:
		IRenderer();
		~IRenderer();

	public:

		/**
		 * 
		 */
		void Resize(unsigned int width_, unsigned height_);

		/**
		 * 
		 */
		void SetClearColor(unsigned char index_, CColor val);

		/**
		 * 
		 */
		void Initialize(EngineSettings &settings_);

		//----------------------------------------------------------
		// 
		//----------------------------------------------------------
		bool IsDeviceLost() const;

		//----------------------------------------------------------
		// 
		//----------------------------------------------------------
		void SetDeviceLost();

    protected :

        /**
         * 
         */
#if CA_PLATFORM_MOBILE
        void Setup();
#else
		void Setup(sf::Window *pWindow_);
#endif // CA_PLATFORM_ANDROID

        
	private:
		IRenderer(const IRenderer&);
		IRenderer& operator = (const IRenderer&);

    private :

        /**
         * 
         */
        static IRenderer s_Instance;

		bool m_bDeviceLost;	
    };

} // namespace CasaEngine


#endif // RENDERER_H
