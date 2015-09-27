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


#include "Base.h"
#include "CA_Assert.h"

#include "SmartPtrPolicies.h"
#include "SmartPtr.h"

#include "DX9Shader.h"
#include "DX9Macro.h"

#include "Log/LogManager.h"
#include "Log/LogVerbose.h"
#include "DX9Renderer.h"
#include "Graphics/Renderer/Renderer.h"

#include "d3dx9core.h"
#include "d3d9.h"
#include "d3dx9shader.h"
#include "dxerr.h"


#include "Graphics/Textures/TextureBase.h"
#include "DX9Texture.h"

namespace CasaEngine
{

////////////////////////////////////////////////////////////
/// Construit le shader à partir de son programme Cg
///
/// \param Program : Programme Cg 
/// \param Type :    Type du shader
///
////////////////////////////////////////////////////////////
DX9Shader::DX9Shader(LPD3DXEFFECT pEffect)
	: m_pEffect(pEffect)
{
	CA_ASSERT(m_pEffect != nullptr, "DX9Shader::DX9Shader() : LPD3DXEFFECT is nullptr");
}


DX9Shader::~DX9Shader()
{
	if (m_pEffect != nullptr)
	{
		m_pEffect->Release();
	}
}


////////////////////////////////////////////////////////////
/// Change la valeur d'un paramètre (scalaire ou vecteur) du shader
///
/// \param Name :  Nom du paramètre
/// \param Value : Valeur du paramètre (quadruplet de flottants)
///
////////////////////////////////////////////////////////////
void DX9Shader::SetParameter(const std::string& Name, const size_t count_, const float* Value)
{
	/*D3DXHANDLE handle;
	
	if (m_pEffect->GetParameterByName(handle, Name.c_str()) != nullptr)
	{
		DXCheck(m_pEffect->SetFloatArray(handle, Value, 4));
	}*/

	//g_pEffect->SetValue( "g_MaterialAmbientColor", &colorMtrlAmbient, sizeof( D3DXCOLOR ) );
	//DXCheck(m_pEffect->SetFloat( Name.c_str(), *Value ));
	DXCheck(m_pEffect->SetFloatArray(Name.c_str(), Value, count_));

	m_pEffect->CommitChanges();
}


////////////////////////////////////////////////////////////
/// Change la valeur d'un paramètre (matrice) du shader
///
/// \param Name :  Nom du paramètre
/// \param Value : Valeur du paramètre (matrice)
///
////////////////////////////////////////////////////////////
void DX9Shader::SetParameter(const std::string& Name, const Matrix4& Value)
{
	D3DXHANDLE handle = m_pEffect->GetParameterByName(nullptr, Name.c_str());
	if (handle != nullptr)
	{
		DXCheck(m_pEffect->SetMatrix(handle, reinterpret_cast<const D3DXMATRIX*>(&Value)));
	}

	//DXCheck(m_pEffect->SetMatrix(Name.c_str(), reinterpret_cast<const D3DXMATRIX*>(&Value.Transpose())));

	m_pEffect->CommitChanges();
}

/**
 * 
 */
void DX9Shader::SetParameter(const std::string& Name, const ITextureBase* Value)
{
	const DX9Texture *pTexture = dynamic_cast<const DX9Texture *>(Value);

	CA_ASSERT(pTexture != nullptr, "DX9Shader::SetParameter() : ITextureBase is not a DX9Texture");

	D3DXHANDLE handle = m_pEffect->GetParameterByName(nullptr, Name.c_str());
	if (handle != nullptr)
	{
		DXCheck(m_pEffect->SetTexture(handle, pTexture->GetDxTexture()));

		/*int tex_idx = m_pConstantTable->GetSamplerIndex(h);

		m_pDevice->SetTexture(tex_idx, texture);    
		m_pDevice->SetSamplerState(tex_idx, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_pDevice->SetSamplerState(tex_idx, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_pDevice->SetSamplerState(tex_idx, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);*/
		m_pEffect->CommitChanges();
	}
}

/**
 * 
 */
ID3DXEffect* DX9Shader::D3DXEffect() const
{
	return m_pEffect;
}


} // namespace CasaEngine
