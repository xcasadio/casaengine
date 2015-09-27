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

#include <string>
#include <bgfx.h>

#include "Graphics/Renderer/Renderer.h"

#include "Maths/Matrix4.h"
#include "Log/Logger.h"
#include "Exceptions.h"
#include "Log/LogManager.h"
#include "Parsers/Ini/INIReader.h"

#include "Resources/ResourceManager.h"
#include "Resources/MediaManager.h"
#include "StringUtils.h"
#include <stdint.h>
#include "bx/string.h"
#include "Graphics/bgfx_utils.h"
#include "EngineSettings.h"

#include "imgui/bgfx_imgui.h"

namespace CasaEngine
{
////////////////////////////////////////////////////////////
// Données statiques
////////////////////////////////////////////////////////////
IRenderer IRenderer::s_Instance;

/////////////////////////////////////////////////////////////
/// Constructeur
///
////////////////////////////////////////////////////////////
IRenderer::IRenderer() :
	m_bDeviceLost(false)
{
	VertexPositionColor::init();
	VertexPositionTexture::init();
	VertexPositionColorTexture::init();
	VertexPositionNormalTexture::init();
	VertexPositionColorNormalTexture::init();
}


/////////////////////////////////////////////////////////////
/// Destructeur
///
////////////////////////////////////////////////////////////
IRenderer::~IRenderer()
{

}

/////////////////////////////////////////////////////////////
/// Détruit le renderer
///
////////////////////////////////////////////////////////////
void IRenderer::Destroy()
{
	bgfx::shutdown();
}


/////////////////////////////////////////////////////////////
/// Renvoie l'instance du renderer
///
/// \return Référence sur l'instance du renderer
///
////////////////////////////////////////////////////////////
IRenderer& IRenderer::Get()
{
    return s_Instance;
}


////////////////////////////////////////////////////////////
/// Initialise le renderer
///
/// \param Hwnd : Handle du contrôle de rendu
///
////////////////////////////////////////////////////////////
void IRenderer::Initialize(EngineSettings &settings_)
{
	bgfx::init(settings_.RendererType, BGFX_PCI_ID_NONE, 0, ::new ::bgfx_utils::CallbackStub());

	//Setup(m_pWindow_); // desktop
	//Setup(); // mobile

	bgfx::reset(settings_.WindowWidth, settings_.WindowHeight, BGFX_RESET_NONE);
	bgfx::setDebug(BGFX_DEBUG_TEXT);
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, (uint32_t) CColor::CornflowerBlue.ToRGBA()
		, 1.0f
		, 0
		);

//     CheckCaps();
// 
//     CA_INFO("Rendering system : %s\n", GetRendererDesc().c_str());
//     CA_INFO("Supported functionalities :\n");
// 
//     for (std::map<Capability::TCapability, bool>::const_iterator i = m_Capabilities.begin(); 
// 		i != m_Capabilities.end(); 
// 		++i)
// 	{
//         CA_INFO("\t\t* %s\t%s\n", 
// 			(i->second ? "OK " : "NO "),
// 			CapToString(i->first).c_str());
// 	}
}

////////////////////////////////////////////////////////////
/// 
///
////////////////////////////////////////////////////////////
bool IRenderer::IsDeviceLost() const
{
	return m_bDeviceLost;
}

////////////////////////////////////////////////////////////
/// 
///
////////////////////////////////////////////////////////////
void IRenderer::SetDeviceLost()
{
	m_bDeviceLost = true;
}

/**
 * 
 */
void IRenderer::SetClearColor(unsigned char index_, CColor val)
{
	bgfx::setClearColor(index_, (uint32_t) val.ToRGBA());
}

/**
 * 
 */
void IRenderer::Resize(unsigned int width_, unsigned height_)
{
	//TODO
}

} // namespace CasaEngine
